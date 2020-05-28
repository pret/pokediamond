/**
 *	@file	mail.c
 *	@brief	���[���V�X�e��
 *	@author	Miyuki Iwasaw
 *	@date	06.02.07
 */

#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "savedata/mail_util.h"
#include "savedata/config.h"
#include "savedata/record.h"
#include "application/mail/mail_param.h"
#include "application/mail/mailview.h"
#include "application/pms_input.h"
#include "mail_snd_def.h"

enum{
	MAILCASE_INIT,
	MAILCASE_WAIT,
	MAILCASE_END,
	WORDCASE_INIT,
	WORDCASE_WAIT,
	WORDCASE_END,
};

//���[���V�X�e�����C�����[�N
typedef struct _MAIL_MAIN_DAT{
	int	heapID;	///<�q�[�vID
	u16	ret_val;	///<���^�[���l
	u16	ret_no;		///<���^�[���ҏWNO

	void	*app_wk;	///<�ȈՉ�b���W���[�����[�N�̕ۑ�
	PROC*	proc;		///<�T�u�v���Z�X���[�N
	MAIL_TMP_DATA *dat;	///<���[���f�[�^�e���|����

	PMS_DATA	tmpPms;	//<�ȈՉ�b�e���|����
}MAIL_MAIN_DAT;

//�v���g�^�C�v�錾�@���[�J��
//================================================================
///�I�[�o�[���C�v���Z�X
static PROC_RESULT MailSysProc_Init( PROC *proc,int *seq);
static PROC_RESULT MailSysProc_Main( PROC *proc,int *seq);
static PROC_RESULT MailSysProc_End( PROC *proc,int *seq);

//================================================================
///�f�[�^��`�G���A
//================================================================
///�I�[�o�[���C�v���Z�X��`�f�[�^
const PROC_DATA MailSysProcData = {
	MailSysProc_Init,
	MailSysProc_Main,
	MailSysProc_End,
	NO_OVERLAY_ID,
};

MAIL_PARAM* MailSys_GetWorkCreate(SAVEDATA* savedata,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID);
MAIL_PARAM* MailSys_GetWorkView(SAVEDATA* savedata,MAILBLOCK_ID blockID,u16 dataID,int heapID);
MAIL_PARAM* MailSys_GetWorkViewPoke(SAVEDATA* savedata,POKEMON_PARAM* poke,int heapID);
MAIL_PARAM* MailSys_GetWorkViewPrev(SAVEDATA* savedata,u8 designNo,int heapID);
BOOL MailSys_IsDataCreate(MAIL_PARAM* wk);
int MailSys_PushDataToSave(MAIL_PARAM* wk,MAILBLOCK_ID blockID,u8 dataID);
int MailSys_PushDataToSavePoke(MAIL_PARAM* wk,POKEMON_PARAM* poke);
void MailSys_ReleaseCallWork(MAIL_PARAM* wk);
int	MailSys_MoveMailPoke2Paso(MAIL_BLOCK* block,POKEMON_PARAM* poke,int heapID);
int	MailSys_MoveMailPaso2Poke(MAIL_BLOCK* block,u16 id,POKEMON_PARAM* poke,int heapID);


MAIL_TMP_DATA* MailSys_AllocTmpData(const MAIL_DATA* org,int heapID);
void MailSys_ReleaseTmpData(MAIL_TMP_DATA* tmp);
void MailSys_SetTmpData(MAIL_DATA* org,MAIL_TMP_DATA* tmp);




/**
 *	@brief	���[����ʌĂяo�����[�N�쐬(Create)
 *
 *	@retval	NULL	�V�K�쐬�̈悪�Ȃ�
 *	@retval ���[�N�|�C���^	���[���쐬��ʌĂяo��
 */
MAIL_PARAM* MailSys_GetWorkCreate(SAVEDATA* savedata,
		MAILBLOCK_ID blockID,u8 poke_pos,u8 design,int heapID)
{
	MAIL_PARAM* wk;
	MAIL_BLOCK* pBlock;
	int id;
	
	//���[���Z�[�u�f�[�^�u���b�N�擾
	pBlock = SaveData_GetMailBlock(savedata); 

	//���W���[���Ăяo���p�̃��[�N���쐬
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));

	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	wk->designNo = design;
	wk->poke_pos = poke_pos;
	wk->pBlock = pBlock;

	//�Ăяo�����[�h�ݒ�
	wk->mode = MAIL_MODE_CREATE;
	wk->blockID = blockID;	//�f�[�^�u���b�NID�擾
	wk->dataID = 0;	//ID��0������
	wk->savedata = savedata;

	//�f�[�^�e���|�����쐬
	wk->pDat = MailData_CreateWork(heapID);
	MailData_Clear(wk->pDat);

	//�����f�[�^�i�[(�f�U�C��No�͖����ɂ��ČĂяo��)
	MailData_CreateFromSaveData(wk->pDat,MAIL_DESIGN_NULL,poke_pos,savedata);
	return wk;
}

/**
 *	@brief	���[����ʌĂяo�����[�N�쐬(View)
 *
 *	@retval	NULL	�V�K�쐬�̈悪�Ȃ�
 *	@retval ���[�N�|�C���^	���[���`���ʌĂяo��
 */
MAIL_PARAM* MailSys_GetWorkView(SAVEDATA* savedata,MAILBLOCK_ID blockID,u16 dataID,int heapID)
{
	MAIL_PARAM* wk;
	MAIL_BLOCK* pBlock;

	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));

	//�Ăяo�����[�h�ݒ�
	wk->mode = MAIL_MODE_VIEW;
	wk->blockID = blockID;
	wk->dataID = dataID;
	wk->savedata = savedata;
	
	//���[���Z�[�u�f�[�^�u���b�N�擾
	pBlock = SaveData_GetMailBlock(savedata); 
	wk->pBlock = pBlock;
	
	//�Z�[�u�f�[�^�擾
	wk->pDat = MAIL_AllocMailData(pBlock,blockID,dataID,heapID);
	return wk;
}

/**
 *	@brief	���[����ʌĂяo�����[�N�쐬(View/POKEMON_PARAM)
 */
MAIL_PARAM* MailSys_GetWorkViewPoke(SAVEDATA* savedata,POKEMON_PARAM* poke,int heapID)
{
	MAIL_PARAM* wk;
	
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	
	//�Ăяo�����[�h�ݒ�
	wk->mode = MAIL_MODE_VIEW;
	wk->savedata = savedata;
	
	//���[�N���擾
	wk->pDat = MailData_CreateWork(heapID);
	//���[���f�[�^�擾
	PokeParaGet(poke,ID_PARA_mail_data,wk->pDat);
	return wk;
}

/**
 *	@brief	���[����ʌĂяo�����[�N�쐬(View/�󃁁[���v���r���[)
 */
MAIL_PARAM* MailSys_GetWorkViewPrev(SAVEDATA* savedata,u8 designNo,int heapID)
{
	MAIL_PARAM* wk;
	
	wk = sys_AllocMemoryLo(heapID,sizeof(MAIL_PARAM));
	MI_CpuClear8(wk,sizeof(MAIL_PARAM));
	
	//�Ăяo�����[�h�ݒ�
	wk->mode = MAIL_MODE_VIEW;
	wk->savedata = savedata;

	//���[�N���擾
	wk->pDat = MailData_CreateWork(heapID);

	//�f�U�C��No�̂ݐݒ�
	MailData_SetDesignNo(wk->pDat,designNo);	
	return wk;
}

/**
 *	@brief	���O�̃��W���[���Ăяo���Ńf�[�^���쐬���ꂽ���ǂ����H
 */
BOOL MailSys_IsDataCreate(MAIL_PARAM* wk)
{
	return wk->ret_val;
}

/**
 *	@brief	���O�̃��W���[���Ăяo���ō쐬���ꂽ�f�[�^���Z�[�u�f�[�^�ɔ��f
 */
int MailSys_PushDataToSave(MAIL_PARAM* wk,MAILBLOCK_ID blockID,u8 dataID)
{
	if(!MailSys_IsDataCreate(wk)){
		return 0;	//�쐬����Ă��Ȃ�
	}
	MAIL_AddMailFormWork(wk->pBlock,blockID,dataID,wk->pDat);
	return 1;
}

/**
 *	@brief	���O�̃��W���[���Ăяo���ō쐬���ꂽ�f�[�^���Z�[�u�f�[�^�ɔ��f(Poke)
 */
int MailSys_PushDataToSavePoke(MAIL_PARAM* wk,POKEMON_PARAM* poke)
{
	if(!MailSys_IsDataCreate(wk)){
		return 0;	//�쐬����Ă��Ȃ�
	}
	PokeParaPut(poke,ID_PARA_mail_data,wk->pDat);
	return 1;
}

/**
 *	@brief	���[�����W���[���Ăяo�����[�N�����
 */
void MailSys_ReleaseCallWork(MAIL_PARAM* wk)
{
	//�f�[�^�e���|�������m�ۂ��Ă����ꍇ�͉��
	if(wk->pDat != NULL){
		sys_FreeMemoryEz(wk->pDat);
	}
	sys_FreeMemoryEz(wk);
}

/**
 *	@brief	�|�P�������[�����p�\���[���Ɉړ�
 *
 *	@retval	MAILDATA_NULLID	�󂫂��Ȃ��̂œ]���ł��Ȃ�
 *	@retval	"���̑�"�@�]�������f�[�^ID
 */
int	MailSys_MoveMailPoke2Paso(MAIL_BLOCK* block,POKEMON_PARAM* poke,int heapID)
{
	int id;
	int itemno = ITEM_DUMMY_DATA;
	MAIL_DATA* src = NULL;

	//�󂫗̈挟��
	id = MAIL_SearchNullID(block,MAILBLOCK_PASOCOM);
	if(id == MAILDATA_NULLID){
		return MAILDATA_NULLID;
	}
	//���[�N�쐬
	src = MailData_CreateWork(heapID);

	//�|�P�������烁�[�����擾
	PokeParaGet(poke,ID_PARA_mail_data,src);

	//�p�\�R���̈�Ƀf�[�^�R�s�[
	MAIL_AddMailFormWork(block,MAILBLOCK_PASOCOM,id,src);

	//�|�P�������烁�[�����O��
	MailData_Clear(src);
	PokeParaPut(poke,ID_PARA_mail_data,src);
	PokeParaPut(poke,ID_PARA_item,&itemno);

	//�̈���
	sys_FreeMemoryEz(src);

	return id;
}

/**
 *	@brief	�p�\���[�����|�P�����Ɉړ�
 *
 *	@retval	MAILDATA_NULLID ID���s���Ȃ̂łȂɂ����Ȃ�����
 *	@retval	"���̑�"�@�]�������f�[�^ID
 */
int	MailSys_MoveMailPaso2Poke(MAIL_BLOCK* block,u16 id,POKEMON_PARAM* poke,int heapID)
{
	int itemno = ITEM_DUMMY_DATA;
	MAIL_DATA* src = NULL;

	//���[���f�[�^���擾
	src = MAIL_AllocMailData(block,MAILBLOCK_PASOCOM,id,heapID);
	if(src == NULL){
		return MAILDATA_NULLID;
	}
	//���[���̃f�U�C��No����A�C�e��No�ɕ���
	itemno = MailItemNumGet(MailData_GetDesignNo(src));
	//�|�P�����Ƀ��[�����ڂ�
	PokeParaPut(poke,ID_PARA_mail_data,src);
	PokeParaPut(poke,ID_PARA_item,&itemno);

	//�p�\�R���̈�̃f�[�^������
	MAIL_DelMailData(block,MAILBLOCK_PASOCOM,id);

	//�̈���
	sys_FreeMemoryEz(src);
	return id;
}


/**
 *	@brief	���[���f�[�^�@�e���|�����쐬
 *
 *	�������Ń��������A���P�[�g����̂ŕK���Ăяo������
 *	�@MailSys_ReleaseTmpData()�ŉ�����邱��
 */
MAIL_TMP_DATA* MailSys_AllocTmpData(const MAIL_DATA* org,int heapID)
{
	u16	i;
	MAIL_TMP_DATA* tmp;

	tmp = sys_AllocMemory(heapID,sizeof(MAIL_TMP_DATA));
	MI_CpuClear8(tmp,sizeof(MAIL_TMP_DATA));
	
	tmp->val = 0;

	tmp->writerID = MailData_GetWriterID(org);
	tmp->name = STRBUF_Create(BUFLEN_PERSON_NAME,heapID);
	STRBUF_SetStringCode(tmp->name,MailData_GetWriterName((MAIL_DATA*)org));
	tmp->design = MailData_GetDesignNo(org);
	tmp->lang = MailData_GetCountryCode(org);
	tmp->ver = MailData_GetCasetteVersion(org);

	for(i = 0;i < MAILDAT_ICONMAX;i++){
		tmp->icon[i].dat = MailData_GetIconParamByIndex(org,i,MAIL_ICONPRM_ALL);
	}
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		PMSDAT_Copy(&tmp->msg[i],MailData_GetMsgByIndex((MAIL_DATA*)org,i));
	}
	return tmp;
}

/**
 *	@brief	���[���f�[�^�@�e���|�������
 *
 *	��MailSys_AllocTmpData()�Ŋm�ۂ����������̈���J������
 */
void MailSys_ReleaseTmpData(MAIL_TMP_DATA* tmp)
{
	if(tmp->name != NULL){
		STRBUF_Delete(tmp->name);
	}
	sys_FreeMemoryEz(tmp);
}

/**
 *	@brief	���[���f�[�^�@�e���|�����f�[�^�����o��
 */
void MailSys_SetTmpData(MAIL_DATA* org,MAIL_TMP_DATA* tmp)
{
	u16	i;

	//�ȈՕ��R�s�[
	for(i = 0;i < MAILDAT_MSGMAX;i++){
		MailData_SetMsgByIndex(org,&tmp->msg[i],i);
	}

	//�f�[�^��L�������邽�߂Ƀf�U�C��NO��ݒ�
	MailData_SetDesignNo(org,tmp->design);
}

//------------------------------------------------------------------
/**
 * @brief	�T�u�v���Z�X�Ăяo������
 * @param	proc	�T�u�v���Z�X�|�C���^��ێ����郏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
static BOOL MailSysProcCall(PROC ** proc)
{
	if (*proc) {
		if (ProcMain(*proc)) {
			PROC_Delete(*proc);
			*proc = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 *	@brief	���[���쐬�Ăяo���@������
 */
static PROC_RESULT MailSysProc_Init(PROC* proc,int* seq)
{
	MAIL_MAIN_DAT* wk = NULL;
	MAIL_PARAM* pp = (MAIL_PARAM*)PROC_GetParentWork(proc);
	
	//���[�N�G���A�擾
	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_MAILSYS,0x1000);
	wk = PROC_AllocWork(proc,sizeof(MAIL_MAIN_DAT),HEAPID_MAILSYS);
	MI_CpuClear8(wk,sizeof(MAIL_MAIN_DAT));

	//�q�[�vID�ۑ�
	wk->heapID = HEAPID_MAILSYS;

	//�f�[�^�e���|�����쐬
	wk->dat = MailSys_AllocTmpData(pp->pDat,wk->heapID);
	wk->dat->configSave = SaveData_GetConfig(pp->savedata);

	if(pp->mode == MAIL_MODE_CREATE){
		//�����i���o�[���i�[����Ă���̂ŁA��ʃ��[�N����擾����
		wk->dat->design = pp->designNo;	//�f�U�C��No�K�p
	}
	if(wk->dat->design >= MAIL_DESIGN_MAX){
		wk->dat->design = 0;
	}
	wk->dat->val = pp->mode;

	return PROC_RES_FINISH;
}

/**
 *	@brief	���[���쐬���C��
 */
static PROC_RESULT MailSysProc_Main(PROC *proc,int* seq)
{
	MAIL_MAIN_DAT* wk = PROC_GetWork(proc);
	MAIL_PARAM* pp = (MAIL_PARAM*)PROC_GetParentWork(proc);

	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(mailview);
	FS_EXTERN_OVERLAY(overlay_pmsi);
	
	// �v���Z�X��`�f�[�^
	static const PROC_DATA MailViewProcData = {
		MailViewProc_Init,
		MailViewProc_Main,
		MailViewProc_End,
		FS_OVERLAY_ID(mailview),
	};
	static const PROC_DATA PMSProcData = {
		PMSInput_Init,
		PMSInput_Main,
		PMSInput_Quit,
		FS_OVERLAY_ID(overlay_pmsi),
	};

	switch(*seq){
	case MAILCASE_INIT:
		wk->dat->val = pp->mode;	//���샂�[�h�l���A
		wk->proc = PROC_Create(&MailViewProcData,wk->dat,wk->heapID);
		*seq = MAILCASE_WAIT;
		break;
	case MAILCASE_WAIT:
		if(!MailSysProcCall(&wk->proc)){
			break;
		}
		switch(wk->dat->val){
		case VIEW_END_CANCEL:
			*seq = MAILCASE_END;
			break;
		case VIEW_END_DECIDE:
			*seq = MAILCASE_END;
			break;
		default:
			*seq = WORDCASE_INIT;	
			break;
		}
		break;
	case MAILCASE_END:
		//�f�[�^�擾
		if(	pp->mode == MAIL_MODE_CREATE){
			if(	wk->dat->val == VIEW_END_DECIDE){
				MailSys_SetTmpData(pp->pDat,wk->dat);	//���[���f�[�^����������
				//�X�R�A���Z����
				RECORD_Score_Add(SaveData_GetRecord(pp->savedata),SCORE_ID_WRITE_MAIL);
				pp->ret_val = 1;	//�߂�l�ݒ�
			}else{
				pp->ret_val = 0;	//�߂�l�ݒ�
			}
		}
		return PROC_RES_FINISH;
	case WORDCASE_INIT:
		wk->app_wk = PMSI_PARAM_Create( PMSI_MODE_SENTENCE,
				PMSI_GUIDANCE_DEFAULT,pp->savedata, wk->heapID);

		//�����f�[�^�Z�b�g
		if(PMSDAT_IsEnabled(&(wk->dat->msg[wk->dat->cntNo]))){
			//���ɓ��͕�������
			PMSDAT_Copy(&(wk->tmpPms),&(wk->dat->msg[wk->dat->cntNo]));
		}else{
			//�܂���
			PMSDAT_Init(&(wk->tmpPms),PMS_TYPE_MAIL);	
		}
		PMSI_PARAM_SetInitializeDataSentence(wk->app_wk,&(wk->tmpPms));
		
		wk->proc = PROC_Create(&PMSProcData,wk->app_wk,wk->heapID);
		*seq = WORDCASE_WAIT;
		break;
	case WORDCASE_WAIT:
		if(!MailSysProcCall(&wk->proc)){
			break;
		}
		// �ȈՉ�b�擾
		if(	PMSI_PARAM_CheckCanceled(wk->app_wk) == FALSE)
//			&& PMSI_PARAM_CheckModified(wk->app_wk) == TRUE)
		{
			//�ύX������Ώ����߂�
			PMSI_PARAM_GetInputDataSentence( wk->app_wk,  &(wk->dat->msg[wk->dat->cntNo]));
		}
		PMSI_PARAM_Delete(wk->app_wk);
		*seq = MAILCASE_INIT;	
		break;
	}
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	���[���쐬�I��
 */
static PROC_RESULT MailSysProc_End(PROC *proc,int* seq)
{
	MAIL_MAIN_DAT	*wk = PROC_GetWork(proc);

	//���[���f�[�^�e���|�����̈���
	MailSys_ReleaseTmpData(wk->dat);

	//���[�N�G���A���
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);

	sys_DeleteHeap(wk->heapID);

	return PROC_RES_FINISH;
}

//===========================================================================
//�f�o�b�O�p���[�`��
//===========================================================================
