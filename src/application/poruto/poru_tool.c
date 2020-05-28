/**
 *	@file	poru_tool.c
 *	@brief	�|���g�P�[�X���f���R���g���[��(�풓)
 *	@date	06.03.01
 *	@author	Miyuki Iwasawa
 */

#include "common.h"
#include "system/procsys.h"
#include "system/msgdata.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/window.h"
#include "gflib/number_str.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_poruto_select.h"

#include "application/poru_tool.h"
#include "savedata/poruto_util.h"
#include "porusys.h"
#include "porudemo.h"

//�f�[�^��`
#include "porudata.dat"

#define BUFSIZ_PLVMSG	(10)

typedef enum{
 SEQ_CASE_INIT,
 SEQ_CASE_WAIT,
 SEQ_PSEL_WAIT,
 SEQ_PST_WAIT,
 SEQ_DEMO_CALL,
 SEQ_DEMO_WAIT,
 SEQ_COND_CALL,
 SEQ_COND_WAIT,
 SEQ_FINISH,
};

///�|���g�R���g���[�����C�����[�N
typedef struct _PORUTO_MAIN_DAT{
	int heapID;	///<�q�[�vID
	int seq;	///<�V�[�P���X����
	
	u8	pokePos;
	u8	pokePara;
	u16	pokeNo;
	PORUTO_PARAM* param;

	void *app_work;	///<�T�u�v���Z�X�p���[�N
	PROC*	proc;	///<�T�u�v���Z�X���[�N
}PORUTO_MAIN_DAT;

///�I�[�o�[���C�v���Z�X��`
static PROC_RESULT PoruSys_Init(PROC* proc,int* seq);
static PROC_RESULT PoruSys_Main(PROC* proc,int* seq);
static PROC_RESULT PoruSys_End(PROC* proc,int* seq);

const PROC_DATA PorutoSysProcData = {
	PoruSys_Init,
	PoruSys_Main,
	PoruSys_End,
	NO_OVERLAY_ID,
};

static void PoruSys_SaveDataPut(PORUTO_MAIN_DAT* wk);
//==============================================================
//�T�u�V�[�P���X�v���g�^�C�v
static int seq_CaseInit(PORUTO_MAIN_DAT* wk);
static int seq_CaseWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeListWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeStatusWait(PORUTO_MAIN_DAT* wk);
static int seq_PoruDemoCall(PORUTO_MAIN_DAT* wk);
static int seq_PoruDemoWait(PORUTO_MAIN_DAT* wk);
static int seq_PokeConditionCall(PORUTO_MAIN_DAT* wk);
static int seq_PokeConditionWait(PORUTO_MAIN_DAT* wk);

/**
 *	@brief	�|���g�V�X�e���Ăяo�����[�N�f�[�^�쐬
 *
 *	���K�� PorutoSys_ReleaseCallWork()�֐��ŉ�����邱�ƁI
 */
PORUTO_PARAM* PorutoSys_CreateCallWork(SAVEDATA* savedata,int heapID)
{
	PORUTO_PARAM* wk;
	PORUTO_DATA* dat;
	PORU_LIST* pl;
	WORDSET* wset;
//	STRBUF	*lvbuf;
	u8	param[PORUTO_PARAID_NUM];
	u8 i = 0,ct = 0,j = 0;
	u8	flags = 0;
	
	wk = sys_AllocMemory(heapID,sizeof(PORUTO_PARAM));
	MI_CpuClear8(wk,sizeof(PORUTO_PARAM));

	//�Z�[�u�f�[�^�u���b�N�擾
	wk->poruSave = SaveData_GetPorutoBlock(savedata);
	wk->mySave = SaveData_GetMyStatus(savedata);
	wk->ppSave = SaveData_GetTemotiPokemon(savedata);
	wk->itemSave = SaveData_GetMyItem(savedata);
	wk->configSave = SaveData_GetConfig(savedata);

#if 0
	{
		MSGDATA_MANAGER* msgman;
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
				NARC_msg_poruto_select_dat,heapID);
		lvbuf = MSGMAN_AllocString(msgman,mes_p_select_04_01);
		MSGMAN_Delete(msgman);
	}
#endif
	dat = PorutoData_AllocWork(heapID);
	wset = WORDSET_CreateEx(1,WORDSET_DEFAULT_BUFLEN,heapID);	


	//�|���g�f�[�^�擾
	for(i = 0;i < PORUTO_STOCK_MAX;i++){
		PORUTO_GetData(wk->poruSave,i,dat);

		if(!PorutoData_IsEnable(dat)){
			continue;
		}
		PorutoData_GetParamArray(dat,param);

		//�e��f�[�^�擾
		pl = &(wk->list[ct]);
		
		pl->id = i;
		pl->level = PorutoData_GetLevel(dat);
		pl->flavor = param[PORUTO_PARAID_FLAVOR];
		pl->taste = param[PORUTO_PARAID_TASTE];

#if 0
		pl->lvbuf = STRBUF_Create(BUFSIZ_PLVMSG,heapID);

		//�|���g���x��������W�J
		WORDSET_RegisterNumber(wset,0,pl->level,2,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
		WORDSET_ExpandStr(wset,pl->lvbuf,lvbuf);
#endif
		flags = 1;
		for(j = 0;j < 5;j++){
			if(param[j+PORUTO_PARAID_SPICY]){
				pl->flags |= flags;
			}
			flags <<= 1;
		}
		pl->valid = pl->view = 1;
		pl->myid = ct++;
		pl->next = pl->prev = 0xFF;
	}

	//���[�N���
	WORDSET_Delete(wset);
	sys_FreeMemoryEz(dat);
//	STRBUF_Delete(lvbuf);
	
	wk->porunum = ct;	//�|���g�������擾
	wk->ret_view = 5;	//�|���g�P�[�X�����\�[�g���[�h(�����)
	return wk;
}

/**
 *	@brief	�|���g�P�[�X�Ăяo�����[�N���������
 */
void PorutoSys_ReleaseCallWork(PORUTO_PARAM* pp)
{
	int i;

#if 0
	for(i = 0;i < pp->porunum;i++){
		if(pp->list[i].lvbuf != NULL){
			STRBUF_Delete(pp->list[i].lvbuf);
		}
	}
#endif
	sys_FreeMemoryEz(pp);
}

//------------------------------------------------------
/**
 *	@brief	�T�u�v���Z�X�Ăяo������
 *	@param	proc	�T�u�v���Z�X�|�C���^
 */
//------------------------------------------------------
static BOOL PorutoSysProcCall(PROC** proc)
{
	if(*proc){
		if(ProcMain(*proc)){
			PROC_Delete(*proc);
			*proc = NULL;
			return TRUE;
		}
	}
	return FALSE;
}

/**
 *	@brief	�|���g�V�X�e���Ăяo��
 **/
static PROC_RESULT PoruSys_Init(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = NULL;
	void* pp = PROC_GetParentWork(proc);

	//���[�N�G���A�擾
	HeapStatePush();

	//�q�[�v�쐬
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_PORUTO,0x1000);
	
	wk = PROC_AllocWork(proc,sizeof(PORUTO_MAIN_DAT),HEAPID_PORUTO);
	MI_CpuClear8(wk,sizeof(PORUTO_MAIN_DAT));

	//
	wk->heapID = HEAPID_PORUTO;
	//��ʃ��[�N�|�C���^�ۑ�
	wk->param = pp;

	return PROC_RES_FINISH;
}

/**
 *	@brief	�|���g�R���g���[�����C��
 */
static PROC_RESULT PoruSys_Main(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = (PORUTO_MAIN_DAT*)PROC_GetWork(proc);

	switch(*seq){
	case SEQ_CASE_INIT:
		*seq = seq_CaseInit(wk);
		break;
	case SEQ_CASE_WAIT:
		*seq = seq_CaseWait(wk);
		break;
	case SEQ_PSEL_WAIT:
		*seq = seq_PokeListWait(wk);
		break;
	case SEQ_PST_WAIT:
		*seq = seq_PokeStatusWait(wk);
		break;
	case SEQ_DEMO_CALL:
		*seq = seq_PoruDemoCall(wk);
		break;
	case SEQ_DEMO_WAIT:
		*seq = seq_PoruDemoWait(wk);
		break;
	case SEQ_COND_CALL:
		*seq = seq_PokeConditionCall(wk);
		break;
	case SEQ_COND_WAIT:
		*seq = seq_PokeConditionWait(wk);
		break;
	case SEQ_FINISH:
		return PROC_RES_FINISH;
	}
	
	return PROC_RES_CONTINUE;
}

/**
 *	@brief	�|���g�R���g���[���I��
 */
static PROC_RESULT	PoruSys_End(PROC* proc,int* seq)
{
	PORUTO_MAIN_DAT* wk = (PORUTO_MAIN_DAT*)PROC_GetWork(proc);

	//�Z�[�u�f�[�^���f
	PoruSys_SaveDataPut(wk);

	//���[�N���
	PROC_FreeWork(proc);
	
	HeapStatePop();
	HeapStateCheck(wk->heapID);
	
	sys_DeleteHeap(wk->heapID);
	return PROC_RES_FINISH;
}

/**
 *	@brief	�|���g�Z�[�u�f�[�^�����o��
 */
static void PoruSys_SaveDataPut(PORUTO_MAIN_DAT* wk)
{
	u8 i = 0,flag = 0;
	PORU_LIST* pl;
	
	for(i = 0;i < wk->param->porunum;i++){
		pl = &wk->param->list[i];
		
		if(pl->del){	//�f�[�^�폜
			PORUTO_DelData(wk->param->poruSave,pl->id);
			flag = 1;
		}
	}
	if(!flag){
		return;
	}
	//�f�[�^����
	PORUTO_DataAdjust(wk->param->poruSave);
}

//============================================================
//�T�u�V�[�P���X

/**
 *	@brief	�|���g�P�[�X������
 */
static int seq_CaseInit(PORUTO_MAIN_DAT* wk)
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(porutocase);

	static const PROC_DATA CaseProcData = {
		PoruCase_Init,
		PoruCase_Main,
		PoruCase_End,
		FS_OVERLAY_ID(porutocase),
//		NO_OVERLAY_ID,
	};
	
	wk->proc = PROC_Create(&CaseProcData,wk->param,wk->heapID);
	return SEQ_CASE_WAIT;	
}

/**
 *	@brief	�|���g�P�[�X�I���҂�
 */
static int seq_CaseWait(PORUTO_MAIN_DAT* wk)
{
	PLIST_DATA* pld;
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_CASE_WAIT;
	}
	//�I������
	if(wk->param->ret_mode == PCASE_RET_CANCEL){
		return SEQ_FINISH;
	}
	//���^�[�����[�h����U�N���A
	wk->param->ret_mode = 0;

	//�|�P�������X�g�Ăяo��
	pld = sys_AllocMemory( wk->heapID, sizeof(PLIST_DATA) );
	MI_CpuClear8( pld,sizeof(PLIST_DATA) );
	pld->pp = wk->param->ppSave;
	pld->myitem = wk->param->itemSave;
	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_PORUTO;
	pld->cfg = wk->param->configSave;

	wk->proc = PROC_Create(&PokeListProcData,pld,wk->heapID);
	wk->app_work = (void*)pld;

	return SEQ_PSEL_WAIT;
}

/**
 *	@brief	�|�P�������X�g�I���҂�
 */
static int seq_PokeListWait(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PLIST_DATA *pld;
	PSTATUS_DATA* psd;
	static const u8 PST_PageTbl[] = {
		PST_PAGE_CONDITION,	// �u�R���f�B�V�����v
		PST_PAGE_RET,			// �u���ǂ�v
		PST_PAGE_MAX
	};
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_PSEL_WAIT;
	}
	
	//�߂�l�`�F�b�N
	pld = (PLIST_DATA*)wk->app_work;
	pos = pld->ret_sel;
	wk->pokePos = pos;	///�莝���i���o�[�ۑ�
	sys_FreeMemoryEz(wk->app_work);
	
	if(pos == PL_SEL_POS_EXIT){
		return SEQ_CASE_INIT;	//�|���g�P�[�X�ɖ߂�
	}

	//�|�P�����X�e�[�^�X���Ăяo��
	//
	psd = sys_AllocMemory( wk->heapID, sizeof(PSTATUS_DATA) );

	psd->ppd  = wk->param->ppSave;
	psd->cfg = wk->param->configSave;
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = pos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = PST_MODE_PORUTO;
	psd->ev_contest = 1;
	psd->perap = NULL;
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet(psd,wk->param->mySave);

	wk->proc = PROC_Create(&PokeStatusProcData,pld,wk->heapID);
	
	wk->app_work = (void*)psd;
	return SEQ_PST_WAIT;
}

/**
 *	@brief	�|�P�����X�e�[�^�X�I���҂�
 */
static int seq_PokeStatusWait(PORUTO_MAIN_DAT* wk)
{
	PSTATUS_DATA* psd;
	u8	ret;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_PST_WAIT;
	}
	
	//�߂�l�`�F�b�N
	psd = (PSTATUS_DATA*)wk->app_work;
	ret = psd->ret_mode;
	
	//�|�P�������؂�ւ���ꂽ�̂��`�F�b�N����
	wk->pokePos = psd->pos;	///�莝���i���o�[�ۑ�
	
	sys_FreeMemoryEz(wk->app_work);
	
	if(ret == PST_RET_CANCEL){
		return SEQ_CASE_INIT;	//�|���g�P�[�X�ɖ߂�
	}

	//�I�����ꂽ�|���g�������
	wk->param->list[wk->param->selID].del = 1;
	//���^�[�����[�h��1���i�[
	wk->param->ret_mode = 1;
	//�|���g��^����f�����Ăяo��
	//
	return SEQ_DEMO_CALL;
}

/**
 *	@brief	�|���g�f���Ăяo��
 */
static int seq_PoruDemoCall(PORUTO_MAIN_DAT* wk)
{
	// �I�[�o�[���CID�錾
	FS_EXTERN_OVERLAY(porutocase);
	static const PROC_DATA DemoProcData = {
		PoruDemo_Init,
		PoruDemo_Main,
		PoruDemo_End,
		FS_OVERLAY_ID(porutocase),
//		NO_OVERLAY_ID,
	};
	PORUDEMO_PARAM* prm;
	
	prm = sys_AllocMemory(wk->heapID,sizeof(PORUDEMO_PARAM));
	MI_CpuClear8(prm,sizeof(PORUDEMO_PARAM));
	
	//���n���p�����[�^�擾
	prm->flavor = wk->param->list[wk->param->selID].flavor;
	prm->poruto = PORUTO_GetDataAlloc(wk->param->poruSave,
		wk->param->list[wk->param->selID].id,wk->heapID);
	prm->pp = PokeParty_GetMemberPointer(wk->param->ppSave,wk->pokePos);
	prm->msg_spd = CONFIG_GetMsgPrintSpeed(wk->param->configSave);
	prm->win_type = CONFIG_GetWindowType(wk->param->configSave);

	//�v���Z�X�R�[��
	wk->proc = PROC_Create(&DemoProcData,prm,wk->heapID);
	wk->app_work = prm;

	return SEQ_DEMO_WAIT;
}

/**
 *	@brief	�|���g�f���I���҂�
 */
static int seq_PoruDemoWait(PORUTO_MAIN_DAT* wk)
{
	PORUDEMO_PARAM* prm;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_DEMO_WAIT;
	}
	//���[�N���
	prm = (PORUDEMO_PARAM*)wk->app_work;
	sys_FreeMemoryEz(prm->poruto);
	sys_FreeMemoryEz(prm);
	return SEQ_COND_CALL;
}

/**
 *	@brief	�R���f�B�V�����Ăяo��
 */
static int seq_PokeConditionCall(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PSTATUS_DATA* psd;
	PORUTO_DATA*	dat;

	static const u8 PST_PageTbl[] = {
		PST_PAGE_CONDITION,	// �u�R���f�B�V�����v
		PST_PAGE_MAX
	};
	
	//�|�P�����X�e�[�^�X���Ăяo��(�R���f�B�V�����ω�)
	//
	psd = sys_AllocMemory( wk->heapID, sizeof(PSTATUS_DATA) );
	//�|���g�p�����[�^���|�P�����ɔ��f
	dat = PORUTO_GetDataAlloc(wk->param->poruSave,
			wk->param->list[wk->param->selID].id,wk->heapID);

	psd->ppd  = wk->param->ppSave;
	psd->cfg = wk->param->configSave;
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = wk->pokePos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = PST_MODE_CONDITION;
	psd->poruto  = dat;
	psd->ev_contest = 1;
	psd->perap = NULL;
	PokeStatus_PageSet( psd, PST_PageTbl);
	PokeStatus_PlayerSet(psd,wk->param->mySave);

	wk->proc = PROC_Create(&PokeStatusProcData,psd,wk->heapID);
	
	wk->app_work = (void*)psd;
	return SEQ_COND_WAIT;
}

/**
 *	@brief	�R���f�B�V�����\���I���҂�
 */
static int seq_PokeConditionWait(PORUTO_MAIN_DAT* wk)
{
	u8	pos;
	PSTATUS_DATA* psd;
	PORUTO_DATA*	dat;
	
	if(!PorutoSysProcCall(&wk->proc)){
		return SEQ_COND_WAIT;
	}
	psd = (PSTATUS_DATA*)wk->app_work;
	sys_FreeMemoryEz(psd->poruto);
	sys_FreeMemoryEz(wk->app_work);

#if 0
	//�|���g�p�����[�^���|�P�����ɔ��f
	dat = PORUTO_GetDataAlloc(wk->param->poruSave,
			wk->param->list[wk->param->selID].id,wk->heapID);
	PoruSys_PoruPara2Poke(dat,
		PokeParty_GetMemberPointer(wk->param->ppSave,wk->pokePos));
	sys_FreeMemoryEz(dat);
#endif

	//�|���g���X�g�֖߂�
	return SEQ_CASE_INIT;
}

//======================================================
//�O�����J�֐�
//======================================================

/**
 *	@brief	�|���g�f�[�^�Ɛ��i���炻�̃|���g���D�����������Ԃ�
 */
PORU_FAVOLITE PoruSys_IsFavolite(PORUTO_DATA *dat,u8 seikaku)
{
	u8 prm[PORUTO_PARAID_NUM];
	u8	flavor,suki,kirai;
	u8	sid,kid;
	
	sid = poruto_f2char[seikaku][0];
	kid = poruto_f2char[seikaku][1];

	if(sid == PORUTO_FTYPE_MIX){
		//�D�������Ȃ�
		return PORU_FAVOLITE_NRM;
	}

	//�|���g�p�����[�^�擾
	PorutoData_GetParamArray(dat,prm);
	flavor = prm[PORUTO_PARAID_FLAVOR];

	suki = prm[sid+PORUTO_PARAID_SPICY];
	kirai = prm[kid+PORUTO_PARAID_SPICY];

	if(suki == kirai){
		return PORU_FAVOLITE_NRM;
	}
	if(suki > kirai){
		return PORU_FAVOLITE_SUKI;
	}else{
		return PORU_FAVOLITE_KIRAI;
	}
}

/**
 *	@brief	���i����ǂ̖����D�����������Ԃ�
 *
 *	@param	�|�P�����̐��iNo
 *	@param	mode	PORU_FAVOLITE_SUKI:�D���Ȗ��^�C�v��Ԃ�
 *					PORU_FAVOLITE_KIRAI:�L���C�Ȗ��^�C�v��Ԃ�
 *
 *	@retval	PORUTO_FTYPE_SPICY	�h��
 *	@retval	PORUTO_FTYPE_ASTR	���Ԃ�
 *	@retval	PORUTO_FTYPE_SWEET	���܂�
 *	@retval	PORUTO_FTYPE_BITTER	�ꂢ
 *	@retval	PORUTO_FTYPE_SOUR	�����ς�
 *	@retval	PORUTO_FTYPE_MIX	�D���������Ȃ�
 */
u8	PoruSys_GetFavolite(u8 seikaku,PORU_FAVOLITE mode)
{
	if(mode == PORU_FAVOLITE_SUKI){
		return poruto_f2char[seikaku][0];
	}else{
		return poruto_f2char[seikaku][1];
	}
	return PORUTO_FTYPE_MIX;
}

/**
 *	@brief	�|���g�p�����[�^���|�P�����p�����[�^��Push����
 */
void PoruSys_PoruPara2Poke(PORUTO_DATA* dat,POKEMON_PARAM* poke)
{
	u8 i,ct;
	u8 seikaku,friend;
	u8	sid,kid;
	float ftmp;
	int	pokeprm[6];
	u8	prm[PORUTO_PARAID_NUM];
	u8	up[PORUTO_PARAID_NUM];
	
	//���iNo�擾
	seikaku = PokeSeikakuGet(poke);
	sid = poruto_f2char[seikaku][0];
	kid = poruto_f2char[seikaku][1];

	//���ݒl�擾
	PorutoData_GetParamArray(dat,prm);
	
	for(i = 0;i<6;i++){
		pokeprm[i] = PokeParaGet(poke,ID_PARA_style+i,NULL);
	}
	/*
	ID_PARA_style,				//�������悳
	ID_PARA_beautiful,			//��������
	ID_PARA_cute,				//���킢��
	ID_PARA_clever,				//��������
	ID_PARA_strong,				//�����܂���
	ID_PARA_fur,				//�щ�
	*/
	//�㏸�l�擾
	ct = 0;
	for(i = PORUTO_PARAID_SPICY;i <= PORUTO_PARAID_TASTE;i++){
		up[ct++] = prm[i];	
	}
	//�D�������p�����[�^�␳
	if(sid != PORUTO_FTYPE_MIX){
		ftmp = (float)up[sid]*1.1f;
		up[sid] = (u8)ftmp;	
		ftmp = (float)up[kid]*0.9f;
		up[kid] = (u8)ftmp;
	}
	//�p�����[�^���Z
	for(i = 0;i < 6;i++){
		pokeprm[i] += up[i];
		if(pokeprm[i] > 255){
			pokeprm[i] = 255;
		}
		PokeParaPut(poke,ID_PARA_style+i,&pokeprm[i]);
	}
	//�����x�㏸(�ꗥ1+)
	friend = PokeParaGet(poke,ID_PARA_friend,NULL);	
	if(friend < 255){
		++friend;
		PokeParaPut(poke,ID_PARA_friend,&friend);
	}
}
