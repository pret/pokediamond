//==============================================================================
/**
 * @file	contest.c
 * @brief	�R���e�X�g
 * @author	matsuda
 * @date	2005.11.15(��)
 *
 * �t�B�[���h�Ƃ��̐ڑ��Ȃǂ���ɂ��
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "con_tool.h"
#include "actin.h"
#include "visual.h"
#include "dance.h"
#include "con_result.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"

#include "poketool/pokeparty.h"
#include "system/pm_rtc.h"
#include "communication/communication.h"
#include "comm_command_contest.h"
#include "field/comm_field_state.h"
#include "msgdata/msg_cmsg_acting.h"
#include "include/application/imageClip/imc_sys.h"
#include "field\eventflag.h"
#include "field\sysflag.h"
#include "savedata\config.h"
#include "savedata/perapvoice.h"
#include "system/brightness.h"

#include "field/tvtopic_extern.h"
#include "savedata/tv_work.h"
#include "savedata/contest_savedata.h"
#include "savedata/record.h"
#include "savedata/fnote_mem.h"

#include "application/p_status/ribbon.h"

#include "itemtool/itemsym.h"
#include "itemtool/itemequip.h"
#include "itemtool/item.h"


//==============================================================================
//
//	�t�B�[���h���牉�Z�͕���ւ̐ڑ�
//
//==============================================================================

//==============================================================================
//	�\���̒�`
//==============================================================================
typedef struct{
	int seq;
	int debug_mode;
}EV_ACTING_WORK;

typedef struct{
	CONTEST_SYSTEM *consys;		///<��check�@�����ȓ�����E�o�������܂�܂ł̎b��
	EV_ACTING_WORK *eaw;
	int seq;
	int local_seq;
	int debug_mode;
}EV_SUB_ACTING_WORK;


typedef struct{
	int seq;
	int clip_set;
}EV_VISUAL_WORK;

typedef struct{
	CONTEST_SYSTEM *consys;		///<��check�@�����ȓ�����E�o�������܂�܂ł̎b��
	int seq;
	int clip_set;
}EV_SUB_VISUAL_WORK;

typedef struct{
	CONTEST_SYSTEM *consys;		///<��check�@�����ȓ�����E�o�������܂�܂ł̎b��
	int seq;
}EV_SIO_CONTEST_WORK;



//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static CONTEST_SYSTEM * Contest_SystemWorkAlloc(void);
static void Contest_SystemWorkFree(CONTEST_SYSTEM *consys);
static void contest_srand(CONTEST_SYSTEM *consys);
u16 contest_rand(CONTEST_SYSTEM *consys);
void EventCmd_ContestSioProc(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_ContestSio(GMEVENT_CONTROL * event);
BOOL Contest_SioParamInitSet(CONTEST_SYSTEM *consys);
BOOL Contest_SioFastDataEndCheck(CONTEST_SYSTEM *consys);
BOOL Contest_SioCommDataEndCheck(CONTEST_SYSTEM *consys);
static void ContestComm_SioFastData(TCB_PTR tcb, void *work);
CONTEST_SYSTEM * Contest_SystemCreate(const CONTEST_INIT_DATA *cid);
void Contest_SystemExit(CONTEST_SYSTEM *consys);
void ConScr_JudgeNameGet(CONTEST_SYSTEM *consys, int judge_no, WORDSET *wordset, u32 buf_id);
void ConScr_BreederNameGet(CONTEST_SYSTEM *consys, int breeder_no, WORDSET *wordset, u32 buf_id);
void ConScr_NickNameGet(CONTEST_SYSTEM *consys, int breeder_no, WORDSET *wordset, u32 buf_id);
static BOOL GMEVENT_Sub_Contest(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_ContestOnlyGame(GMEVENT_CONTROL * event);
static void Contest_ImageClipInitDataCreate(CONTEST_SYSTEM *consys);
static void Contest_ImageClipInitDataFree(CONTEST_SYSTEM *consys);
static void Contest_SioImcData(CONTEST_SYSTEM *consys);
static void ContestComm_ImcData(TCB_PTR tcb, void *work);
static void SioEtcDataSet(CONTEST_SYSTEM *consys, int breeder_no, CON_ETC_SIO_DATA *etc_data);
static void ConScr_FlashMain(TCB_PTR tcb, void *work);
static int Contest_PlayerPopularityGet(POKEMON_PARAM *my_pp, int con_type);
static void Contest_CpuParamCreate(CONTEST_SYSTEM *consys, int hof_flag, int zenkoku_zukan_flag);
#ifdef PM_DEBUG
static BOOL GMEVENT_DebugConStart(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_DebugCon(GMEVENT_CONTROL * event);
void EventCmd_DebugConProc(GMEVENT_CONTROL * event, int debug_mode);
static void ContestDebug_ImageClipDebugAccessorySet(CONTEST_SYSTEM *consys);
static void ContestDebug_ImageClipDebugAccessoryFree(CONTEST_SYSTEM *consys);
#endif

//==============================================================================
//	PROC�f�[�^
//==============================================================================
FS_EXTERN_OVERLAY(contest);
FS_EXTERN_OVERLAY(ol_imageclip);

/// ���Z�͕���v���Z�X��`�f�[�^
const PROC_DATA ContestActinProcData = {
	ActinProc_Init,
	ActinProc_Main,
	ActinProc_End,
	FS_OVERLAY_ID(contest),
};

/// �_���X����v���Z�X��`�f�[�^
const PROC_DATA ContestDanceProcData = {
	DanceProc_Init,
	DanceProc_Main,
	DanceProc_End,
	FS_OVERLAY_ID(contest),
};

/// �r�W���A������v���Z�X��`�f�[�^
const PROC_DATA ContestVisualProcData = {
	VisualProc_Init,
	VisualProc_Main,
	VisualProc_End,
	FS_OVERLAY_ID(contest),
};

/// �R���e�X�g���ʔ��\��ʃv���Z�X��`�f�[�^
const PROC_DATA ContestResultProcData = {
	ConresProc_Init,
	ConresProc_Main,
	ConresProc_End,
	FS_OVERLAY_ID(contest),
};

const PROC_DATA IMC_SYS_Proc = {
	IMC_ProcContestInit,
	IMC_ProcContestMain,
	IMC_ProcContestEnd,
	FS_OVERLAY_ID(ol_imageclip),
};


//==============================================================================
//	�f�[�^
//==============================================================================
///�J�����̃t���b�V���E�F�C�g�e�[�u���f�[�^�F�m�[�}��
ALIGN4 static const u8 CameraFlashWait_Normal[][3] = {
	{20, 20, 0xff},
	{15, 25, 0xff},
};
///�J�����̃t���b�V���E�F�C�g�e�[�u���f�[�^�F�X�[�p�[
ALIGN4 static const u8 CameraFlashWait_Super[][4] = {
	{10, 10, 30, 0xff},
	{15, 15, 15, 0xff},
};
///�J�����̃t���b�V���E�F�C�g�e�[�u���f�[�^�F�n�C�p�[
ALIGN4 static const u8 CameraFlashWait_Hyper[][5] = {
	{10, 8, 20, 28, 0xff},
	{15, 15, 8, 8, 0xff},
};
///�J�����̃t���b�V���E�F�C�g�e�[�u���f�[�^�F�}�X�^�[
ALIGN4 static const u8 CameraFlashWait_Master[][6] = {
	{8, 8, 8, 8, 30, 0xff},
	{15,15,8,8,20,0xff},
};



#ifdef PM_DEBUG	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   �f�o�b�O�R���e�X�g�Ăяo��
 *
 * @param   fsys		
 * @param   debug_mode		DEBUG_CON_???
 */
//--------------------------------------------------------------
void DebugContest_FieldConnectStart(FIELDSYS_WORK *fsys, int debug_mode)
{
	EV_ACTING_WORK *eaw;
	
	eaw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_ACTING_WORK));
	MI_CpuClear8(eaw, sizeof(EV_ACTING_WORK));
	eaw->debug_mode = debug_mode;
	FieldEvent_Set(fsys, GMEVENT_DebugConStart, eaw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�R���e�X�g�F���Z�͕���C�x���g�V�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 * �G���J�E���g�G�t�F�N�g�����t�B�[���h���A���s���B
 * �Q�[���I�[�o�[�����ւ̕��������i�\��j
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_DebugConStart(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_ACTING_WORK *eaw;
	
	fsys = FieldEvent_GetFieldSysWork(event);
	eaw = FieldEvent_GetSpecialWork(event);

	switch (eaw->seq) {
	case 0:
		EventCmd_FieldFadeOut(event);
		eaw->seq++;
		break;
	case 1:
		EventCmd_DebugConProc(event, eaw->debug_mode);
		eaw->seq++;
		break;
	case 2:
		EventCmd_FieldFadeIn(event);
		eaw->seq++;
		break;
	case 3:
		sys_FreeMemoryEz(eaw);
		return TRUE;
	}
	return FALSE;
}

void EventCmd_DebugConProc(GMEVENT_CONTROL * event, int debug_mode)
{
	EV_SUB_ACTING_WORK *esaw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_SUB_ACTING_WORK));
	MI_CpuClear8(esaw, sizeof(EV_SUB_ACTING_WORK));
	esaw->debug_mode = debug_mode;
	FieldEvent_Call(event, GMEVENT_Sub_DebugCon, esaw);
}

static BOOL GMEVENT_Sub_DebugCon(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SUB_ACTING_WORK *esaw = FieldEvent_GetSpecialWork(event);
	
	switch (esaw->seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		esaw->seq ++;
		break;
	case 1:
		//��check	����������������Ȃ��̂ŁA�Ƃ肠���������ŃR���e�X�g�S�̃q�[�v�쐬
		{
			POKEMON_PARAM * poke;
			STRBUF *myname;
			const MYSTATUS *my_status;
			CONTEST_INIT_DATA cid;
			
			poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), 0);
			my_status = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
			myname = MyStatus_CreateNameString(my_status, HEAPID_WORLD);
			
			cid.type = gf_rand() % CONTYPE_MAX;//CONTYPE_STYLE;
			cid.rank = CONRANK_NORMAL;
			cid.mode = CONMODE_GRAND;
			cid.my_pp = poke;
			cid.player_name_str = myname;
			cid.my_status = my_status;
			cid.imc_save = SaveData_GetImcSaveData(fsys->savedata);
			cid.config = SaveData_GetConfig(fsys->savedata);
			if(sys.cont & PAD_BUTTON_Y){
				cid.rank = CONRANK_SUPER;
			}
			else if(sys.cont & PAD_BUTTON_X){
				cid.rank = CONRANK_HYPER;
			}
			else if(sys.cont & PAD_BUTTON_START){
				cid.rank = CONRANK_MASTER;
			}
			esaw->consys = Contest_SystemCreate(&cid);
			
			STRBUF_Delete(myname);
		}
		
		esaw->seq ++;
		break;
	case 2:		//���ꂼ��̕�����Ăяo��
		switch(esaw->debug_mode){
		case DEBUG_CON_ACTIN:
			EventCmd_CallSubProc(event, &ContestActinProcData, esaw->consys);
			esaw->seq++;
			break;
		case DEBUG_CON_VISUAL:
			//�f�o�b�O���[�h�ł͎����̃N���b�v�f�[�^�����Ȃ��̂ŁA�����ŃZ�b�g
			ImcSaveData_SetContestPokeData_Easy(esaw->consys->c_game.imc_data[0], 
				esaw->consys->c_game.pp[0], -1);
			ImcSaveData_SetContestBgId(esaw->consys->c_game.imc_data[0], 0);
			ImcSaveData_SetContestRank(esaw->consys->c_game.imc_data[0], 
				esaw->consys->c_game.rank);

			EventCmd_CallSubProc(event, &ContestVisualProcData, esaw->consys);
			esaw->seq++;
			break;
		case DEBUG_CON_CLIP_VISUAL:
			switch(esaw->local_seq){
			case 0:
				Contest_ImageClipInitDataCreate(esaw->consys);
				ContestDebug_ImageClipDebugAccessorySet(esaw->consys);	//�f�o�b�O�f�[�^�Z�b�g
				EventCmd_CallSubProc(event, &IMC_SYS_Proc, esaw->consys->icpw);
				esaw->local_seq++;
				break;
			case 1:
				ContestDebug_ImageClipDebugAccessoryFree(esaw->consys);	//�f�o�b�O�f�[�^�J��
				Contest_ImageClipInitDataFree(esaw->consys);
				esaw->local_seq++;
				break;
			default:
				EventCmd_CallSubProc(event, &ContestVisualProcData, esaw->consys);
				esaw->local_seq = 0;
				esaw->seq++;
				break;
			}
			break;
		case DEBUG_CON_DANCE:
			//�f�o�b�O���[�h�ł͎����̃N���b�v�f�[�^�����Ȃ��̂ŁA�����ŃZ�b�g
			ImcSaveData_SetContestPokeData_Easy(esaw->consys->c_game.imc_data[0], 
				esaw->consys->c_game.pp[0], -1);
			ImcSaveData_SetContestBgId(esaw->consys->c_game.imc_data[0], 0);
			ImcSaveData_SetContestRank(esaw->consys->c_game.imc_data[0], 
				esaw->consys->c_game.rank);

			EventCmd_CallSubProc(event, &ContestDanceProcData, esaw->consys);
			esaw->seq++;
			break;
		case DEBUG_CON_RESULT:
			EventCmd_CallSubProc(event, &ContestResultProcData, esaw->consys);
			esaw->seq++;
			break;
		}
		break;
	case 3:
		//��check�@�o�������������Ȃ��̂ŁA�Ƃ肠���������ŃR���e�X�g�S�̃q�[�v���
		Contest_SystemExit(esaw->consys);
		
		EventCmd_StartFieldMap(event);
		esaw->seq ++;
		break;
	case 4:
		sys_FreeMemoryEz(esaw);
		return TRUE;
	}
	return FALSE;
}

#endif	//PM_DEBUG ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//==============================================================================
//	�ʐM�R���e�X�g�����
//==============================================================================
void EventCmd_ContestSioProc(GMEVENT_CONTROL * event)
{
	EV_SIO_CONTEST_WORK *escw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_SIO_CONTEST_WORK));
	MI_CpuClear8(escw, sizeof(EV_SIO_CONTEST_WORK));
	FieldEvent_Call(event, GMEVENT_Sub_ContestSio, escw);
}

static BOOL GMEVENT_Sub_ContestSio(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SIO_CONTEST_WORK *escw = FieldEvent_GetSpecialWork(event);
	enum{
		SIOSEQ_FINISH_FIELD,
		SIOSEQ_INIT,
		SIOSEQ_FAST_WAIT,
		SIOSEQ_IMC_TIMING,
		SIOSEQ_IMC_TIMING_WAIT,
		SIOSEQ_IMC_CALL,
		SIOSEQ_IMC_SEND,
		SIOSEQ_IMC_SEND_WAIT,
		SIOSEQ_VISUAL_CALL,
		SIOSEQ_DANCE_CALL,
		SIOSEQ_ACTIN_CALL,
		SIOSEQ_SYS_EXIT,
		SIOSEQ_SIO_END,
		SIOSEQ_START_FIELD,
		SIOSEQ_END,
	};
		
	switch (escw->seq) {
	case SIOSEQ_FINISH_FIELD:
		EventCmd_FinishFieldMap(event);
		escw->seq ++;
		break;
	case SIOSEQ_INIT:
		//��check	����������������Ȃ��̂ŁA�Ƃ肠���������ŃR���e�X�g�S�̃q�[�v�쐬
		{
			POKEMON_PARAM * poke;
			STRBUF *myname;
			const MYSTATUS *my_status;
			CONTEST_INIT_DATA cid;
			poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), 0);
			my_status = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
			myname = MyStatus_CreateNameString(my_status, HEAPID_WORLD);

			cid.type = CONTYPE_STYLE;
			cid.rank = CONRANK_NORMAL;
			cid.mode = CONMODE_GRAND;
			cid.my_pp = poke;
			cid.player_name_str = myname;
			cid.my_status = my_status;
			cid.imc_save = SaveData_GetImcSaveData(fsys->savedata);
			cid.config = SaveData_GetConfig(fsys->savedata);
			escw->consys = Contest_SystemCreate(&cid);
			
			STRBUF_Delete(myname);
		}
		
		//�ʐM�f�[�^�Z�b�g���^�X�N�o�^�ŏ����ʐM�J�n
		Contest_SioParamInitSet(escw->consys);
		
		escw->seq++;
		break;
	case SIOSEQ_FAST_WAIT:
		if(Contest_SioFastDataEndCheck(escw->consys) == TRUE){
			escw->seq ++;
		}
		break;
	case SIOSEQ_IMC_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_CALL_IMC);
		escw->seq++;
		break;
	case SIOSEQ_IMC_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_CALL_IMC) == TRUE){
			escw->seq++;
		}
		break;
	case SIOSEQ_IMC_CALL:
		Contest_ImageClipInitDataCreate(escw->consys);
	#ifdef PM_DEBUG
		ContestDebug_ImageClipDebugAccessorySet(escw->consys);
	#endif
		EventCmd_CallSubProc(event, &IMC_SYS_Proc, escw->consys->icpw);
		escw->seq++;
		break;
	case SIOSEQ_IMC_SEND:
	#ifdef PM_DEBUG
		ContestDebug_ImageClipDebugAccessoryFree(escw->consys);
	#endif
		Contest_ImageClipInitDataFree(escw->consys);
		Contest_SioImcData(escw->consys);
		escw->seq++;
		break;
	case SIOSEQ_IMC_SEND_WAIT:
		if(Contest_SioCommDataEndCheck(escw->consys) == TRUE){
			escw->seq++;
		}
		break;
	case SIOSEQ_VISUAL_CALL:
		EventCmd_CallSubProc(event, &ContestVisualProcData, escw->consys);
		escw->seq ++;
		break;
	case SIOSEQ_DANCE_CALL:
		EventCmd_CallSubProc(event, &ContestDanceProcData, escw->consys);
		escw->seq ++;
		break;
	case SIOSEQ_ACTIN_CALL:
		EventCmd_CallSubProc(event, &ContestActinProcData, escw->consys);
		escw->seq ++;
		break;
	case SIOSEQ_SYS_EXIT:
		//��check�@�o�������������Ȃ��̂ŁA�Ƃ肠���������ŃR���e�X�g�S�̃q�[�v���
		Contest_SystemExit(escw->consys);
		escw->seq++;
		break;
	case SIOSEQ_SIO_END:
//		CommStateExitBattle();  // �ʐM�I�������ړ����܂��� 2006.01.05 k.ohno
		escw->seq++;
		break;
	case SIOSEQ_START_FIELD:
		EventCmd_StartFieldMap(event);
		escw->seq ++;
		break;
	default:
		GF_ASSERT(0 && "�s���ȃV�[�P���X�ł�");
		//break;	//END�ɗ��Ƃ�
	case SIOSEQ_END:
		sys_FreeMemoryEz(escw);
		return TRUE;
	}
	return FALSE;
}




//==============================================================================
//	�X�N���v�g����� �����
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g����̃R���e�X�g�Ăяo��
 *
 * @param   event		
 * @param   consys		
 */
//--------------------------------------------------------------
void EventCmd_ContestProc(GMEVENT_CONTROL * event, CONTEST_SYSTEM *consys)
{
	EV_SIO_CONTEST_WORK *escw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_SIO_CONTEST_WORK));
	MI_CpuClear8(escw, sizeof(EV_SIO_CONTEST_WORK));
	escw->consys = consys;
	switch(consys->c_game.mode){
	case CONMODE_CHARM:
	case CONMODE_ACTIVE:
	case CONMODE_GRAND:
		FieldEvent_Call(event, GMEVENT_Sub_Contest, escw);
		break;
	default:
		FieldEvent_Call(event, GMEVENT_Sub_ContestOnlyGame, escw);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g����̃R���e�X�g�Ăяo�����C���^�X�N
 *
 * @param   event		
 */
//--------------------------------------------------------------
static BOOL GMEVENT_Sub_Contest(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SIO_CONTEST_WORK *escw = FieldEvent_GetSpecialWork(event);
	enum{
		SSEQ_FIELD_FINISH,
		SSEQ_INIT_WAIT,
		SSEQ_INIT_TIMING,
		SSEQ_INIT_TIMING_WAIT,
		SSEQ_IMC_CALL,
		SSEQ_IMC_WAIT,
		SSEQ_IMC_END,
		SSEQ_VISUAL_CALL,
		SSEQ_DANCE_CALL,
		SSEQ_ACTIN_CALL,
		SSEQ_RESULT_CALL,
		SSEQ_SIO_END,
		SSEQ_FIELD_START,
		SSEQ_END,
	};
	
	switch (escw->seq) {
	case SSEQ_FIELD_FINISH:
		EventCmd_FinishFieldMap(event);
		escw->seq ++;
		break;
	case SSEQ_INIT_WAIT:
		if(escw->consys->sio_flag == FALSE || Contest_SioCommDataEndCheck(escw->consys) == TRUE){
			escw->seq ++;
		}
		break;
	case SSEQ_INIT_TIMING:
		if(escw->consys->sio_flag == TRUE){
			CommTimingSyncStart(CONSIO_TIMING_START);
		}
		escw->seq++;
		break;
	case SSEQ_INIT_TIMING_WAIT:
		if(escw->consys->sio_flag == TRUE){
			if(CommIsTimingSync(CONSIO_TIMING_START) == TRUE){
				escw->seq++;
			}
		}
		else{
			escw->seq++;
		}
		break;
	case SSEQ_IMC_CALL:
		Contest_ImageClipInitDataCreate(escw->consys);
		EventCmd_CallSubProc(event, &IMC_SYS_Proc, escw->consys->icpw);
		escw->seq++;
		break;
	case SSEQ_IMC_WAIT:
		Contest_ImageClipInitDataFree(escw->consys);
		if(escw->consys->sio_flag == TRUE){
			Contest_SioImcData(escw->consys);
			escw->seq++;
		}
		else{
			escw->seq = SSEQ_IMC_END;
		}
		break;
	case SSEQ_IMC_END:
		if(escw->consys->sio_flag == FALSE || Contest_SioCommDataEndCheck(escw->consys) == TRUE){
			escw->seq++;
		}
		break;
		
	case SSEQ_VISUAL_CALL:
		EventCmd_CallSubProc(event, &ContestVisualProcData, escw->consys);
		escw->seq ++;
		break;
	case SSEQ_DANCE_CALL:
		if(escw->consys->c_game.mode == CONMODE_ACTIVE || 
				escw->consys->c_game.mode == CONMODE_GRAND){
			EventCmd_CallSubProc(event, &ContestDanceProcData, escw->consys);
		}
		escw->seq ++;
		break;
	case SSEQ_ACTIN_CALL:
		if(escw->consys->c_game.mode == CONMODE_CHARM || 
				escw->consys->c_game.mode == CONMODE_GRAND){
			EventCmd_CallSubProc(event, &ContestActinProcData, escw->consys);
		}
		escw->seq ++;
		break;
	case SSEQ_RESULT_CALL:
		EventCmd_CallSubProc(event, &ContestResultProcData, escw->consys);
		escw->seq ++;
		break;
	case SSEQ_SIO_END:
//		CommStateExitBattle();  // �ʐM�I�������ړ����܂��� 2006.01.05 k.ohno
		escw->seq++;
		break;
	case SSEQ_FIELD_START:
		EventCmd_StartFieldMap(event);
		escw->seq ++;
		break;
	default:
		GF_ASSERT(0 && "�s���ȃV�[�P���X");
		//break;	����END�ɗ��Ƃ�
	case SSEQ_END:
		sys_FreeMemoryEz(escw);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g����̃R���e�X�g�Ăяo�����C���^�X�N(���K�E�`���[�g���A���p)
 *
 * @param   event		
 */
//--------------------------------------------------------------
static BOOL GMEVENT_Sub_ContestOnlyGame(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_SIO_CONTEST_WORK *escw = FieldEvent_GetSpecialWork(event);
	enum{
		ONLYSEQ_FIELD_FINISH,
		ONLYSEQ_IMC_CALL,
		ONLYSEQ_IMC_WAIT,
		ONLYSEQ_IMC_END,
		ONLYSEQ_VISUAL_CALL,
		ONLYSEQ_DANCE_CALL,
		ONLYSEQ_ACTIN_CALL,
		ONLYSEQ_RESULT_CALL,
		ONLYSEQ_FIELD_START,
		ONLYSEQ_END,
	};
	
	switch (escw->seq) {
	case ONLYSEQ_FIELD_FINISH:
		EventCmd_FinishFieldMap(event);
		escw->seq ++;
		break;

	case ONLYSEQ_IMC_CALL:
		switch(escw->consys->c_game.mode){
		case CONMODE_VISUAL_PRACTICE:
		case CONMODE_VISUAL_TUTORIAL:
			Contest_ImageClipInitDataCreate(escw->consys);
			EventCmd_CallSubProc(event, &IMC_SYS_Proc, escw->consys->icpw);
			break;
		}
		escw->seq++;
		break;
	case ONLYSEQ_IMC_WAIT:
		switch(escw->consys->c_game.mode){
		case CONMODE_VISUAL_PRACTICE:
		case CONMODE_VISUAL_TUTORIAL:
			Contest_ImageClipInitDataFree(escw->consys);
			break;
		}
		escw->seq++;
		break;
	case ONLYSEQ_IMC_END:
		escw->seq++;
		break;
		
	case ONLYSEQ_VISUAL_CALL:
		switch(escw->consys->c_game.mode){
		case CONMODE_VISUAL_PRACTICE:
		case CONMODE_VISUAL_TUTORIAL:
			EventCmd_CallSubProc(event, &ContestVisualProcData, escw->consys);
			break;
		}
		escw->seq ++;
		break;
	case ONLYSEQ_DANCE_CALL:
		switch(escw->consys->c_game.mode){
		case CONMODE_DANCE_PRACTICE:
		case CONMODE_DANCE_TUTORIAL:
			ConTool_PracticeDanceImcSet(escw->consys);
			EventCmd_CallSubProc(event, &ContestDanceProcData, escw->consys);
			break;
		}
		escw->seq ++;
		break;
	case ONLYSEQ_ACTIN_CALL:
		switch(escw->consys->c_game.mode){
		case CONMODE_ACTIN_PRACTICE:
		case CONMODE_ACTIN_TUTORIAL:
			EventCmd_CallSubProc(event, &ContestActinProcData, escw->consys);
			break;
		}
		escw->seq ++;
		break;

	case ONLYSEQ_RESULT_CALL:
//		EventCmd_CallSubProc(event, &ContestResultProcData, escw->consys);
		
		//���ʔ��\��ʂ��\������Ȃ��̂ŁA�����ōŏI���ʂ����v�Z����
		{
			s32 score[BREEDER_MAX];
			int i, ranking;
			
			switch(escw->consys->c_game.mode){
			case CONMODE_VISUAL_PRACTICE:
			case CONMODE_VISUAL_TUTORIAL:
				for(i = 0; i < BREEDER_MAX; i++){
					score[i] = ConTool_HeartNumGet_BP(escw->consys, i) 
						+ ConTool_HeartNumGet_Clip(escw->consys, i);
				}
				break;
			case CONMODE_DANCE_PRACTICE:
			case CONMODE_DANCE_TUTORIAL:
				for(i = 0; i < BREEDER_MAX; i++){
					score[i] = escw->consys->c_game.score[i].dance;
				}
				break;
			case CONMODE_ACTIN_PRACTICE:
			case CONMODE_ACTIN_TUTORIAL:
				for(i = 0; i < BREEDER_MAX; i++){
					score[i] = escw->consys->c_game.score[i].actin;
				}
				break;
			}
			
			//�v���C���[�̏��ʂ������ׂ�(���_�̏ꍇ�̓v���C���[�D��)
			ranking = 0;
			for(i = 1; i < BREEDER_MAX; i++){
				if(score[0] < score[i]){
					ranking++;
				}
			}
			escw->consys->c_game.score[0].final_ranking = ranking;
		}
		escw->seq++;
		break;

	case ONLYSEQ_FIELD_START:
		EventCmd_StartFieldMap(event);
		escw->seq ++;
		break;
	default:
		GF_ASSERT(0 && "�s���ȃV�[�P���X");
		//break;	����END�ɗ��Ƃ�
	case ONLYSEQ_END:
		sys_FreeMemoryEz(escw);
		return TRUE;
	}
	return FALSE;
}



//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e�����[�N��Alloc����
 *
 * @retval  �R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static CONTEST_SYSTEM * Contest_SystemWorkAlloc(void)
{
	CONTEST_SYSTEM *consys;
	int i;
	
	consys = sys_AllocMemory(HEAPID_CONTEST, sizeof(CONTEST_SYSTEM));
	MI_CpuClear8(consys, sizeof(CONTEST_SYSTEM));
	consys->c_game.my_breeder_no = 0;
	consys->c_game.player_num = 1;
	consys->c_game.cpu_num = BREEDER_MAX - 1;
	return consys;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e�����[�N���
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Contest_SystemWorkFree(CONTEST_SYSTEM *consys)
{
	sys_FreeMemoryEz(consys);
}


//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e�����[�N���쐬����
 *
 * @param   contest_type		�R���e�X�g�^�C�v(CONTYPE_???)
 * @param   contest_rank		�R���e�X�g�����N(CONRANK_???)
 * @param   contest_mode		�R���e�X�g���[�h(CONMODE_???)
 * @param   my_pp				�o�ꂳ���鎩���̎莝���|�P�����ւ̃|�C���^
 * @param   player_name_str		�v���C���[���ւ̃|�C���^
 * @param   my_status			�}�C�X�e�[�^�X�ւ̃|�C���^
 *
 * @retval  �쐬�����R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
CONTEST_SYSTEM * Contest_SystemCreate(const CONTEST_INIT_DATA *cid)
{
	CONTEST_SYSTEM *consys;
	int cpu_num = BREEDER_MAX - 1;
	int i;
	
#if 0	//HEAPID_BASE_APP���炾�ƃ��������m�ۏo���Ȃ��Ȃ����̂�HEAPID_WORLD������悤��
		//�ύX�B�@�ʓc����Ɋm�F�ς� 2006.04.05(��)
	sys_CreateHeap(HEAPID_BASE_APP, HEAPID_CONTEST, CONTEST_ALLOC_SIZE);
#else
	sys_CreateHeap(HEAPID_WORLD, HEAPID_CONTEST, CONTEST_ALLOC_SIZE);
#endif
	consys = Contest_SystemWorkAlloc();
	
	consys->push_random_seed = gf_get_seed();
	contest_srand(consys);

	consys->c_game.type = cid->type;
	consys->c_game.rank = cid->rank;
	consys->c_game.mode = cid->mode;
	consys->c_game.theme = ConTool_ThemeRandomSelect(cid->rank, FALSE);
	consys->c_game.server_no = consys->c_game.my_breeder_no;
	consys->c_game.my_version = CONTEST_VERSION;
	consys->c_game.server_version = consys->c_game.my_version;
	consys->c_game.special_judge_no = 1;//contest_rand(consys) % JUDGE_MAX;

	consys->imc_save = cid->imc_save;
	consys->config = cid->config;
	consys->sv = cid->sv;
	consys->my_pp = cid->my_pp;
	consys->temoti_pos = cid->temoti_pos;
	consys->my_status = cid->my_status;
	consys->hof_flag = cid->hof_flag;
	consys->zenkoku_zukan_flag = cid->zenkoku_zukan_flag;
	
	//�C���[�W�N���b�v�̈�쐬
	for(i = 0; i < BREEDER_MAX; i++){
		consys->c_game.imc_data[i] = ImcSaveData_ContestAllocWork(HEAPID_CONTEST);
	}
	
	//�R���f�[�^�Z�b�g
	ConTool_JudgeEntry(consys, HEAPID_WORLD, consys->c_game.special_judge_no, 
		consys->c_game.type, consys->c_game.rank);
	
	//PokeParty�쐬
	consys->poke_party = PokeParty_AllocPartyWork(HEAPID_CONTEST);
	//PokePara�쐬
	for(i = 0; i < BREEDER_MAX; i++){
		consys->c_game.pp[i] = PokemonParam_AllocWork(HEAPID_CONTEST);
	}

	//�؃��b�v
	for(i = 0; i < BREEDER_MAX; i++){
		consys->perap_voice[i] = PERAPVOICE_AllocWork(HEAPID_CONTEST);
	}
	PERAPVOICE_CopyData(consys->perap_voice[0], cid->perap_voice);
	
	//�������g�̃p�����[�^��F�X�Z�b�g
	{
		//�����̃|�P�����Z�b�g
		PokeCopyPPtoPP(cid->my_pp, consys->c_game.pp[0]);
		
		//�u���[�_�[���Z�b�g(�e�����u���[�_�[���ł͂Ȃ��̂�)
		consys->c_game.breeder_name_str[0] = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_CONTEST);
		STRBUF_Copy(consys->c_game.breeder_name_str[0], cid->player_name_str);

		//���ʃZ�b�g
		consys->c_game.player_sex[0] = MyStatus_GetMySex(cid->my_status);
		
		//���i�Z�b�g
		consys->c_game.character[0] = BRD_CHARACTER_ELITE;

		//�l�C�Z�b�g
		consys->c_game.popularity[0] 
			= Contest_PlayerPopularityGet(consys->c_game.pp[0], consys->c_game.type);
		
		//OBJ�R�[�h
		if(ConTool_PracticeModeCheck(consys) == FALSE){
			if(MyStatus_GetMySex(cid->my_status) == PM_MALE){
				consys->c_game.obj_code[0] = CONTESTHERO;
			}
			else{
				consys->c_game.obj_code[0] = CONTESTHEROINE;
			}
		}
		else{	//���K�̎��̓m�[�}����l��
			if(MyStatus_GetMySex(cid->my_status) == PM_MALE){
				consys->c_game.obj_code[0] = HERO;
			}
			else{
				consys->c_game.obj_code[0] = HEROINE;
			}
		}
	}
	
	//CPU�̃G���g���[�ƃp�����[�^����
	Contest_CpuParamCreate(consys, cid->hof_flag, cid->zenkoku_zukan_flag);
	
	//���Z����J�n���̕��уZ�b�g
	if(ConTool_PracticeModeCheck(consys) == TRUE){
		//���K
		for(i = 0; i < BREEDER_MAX; i++){
			consys->actin_sort[i] = BREEDER_MAX - i - 1;
		}
	}
	else{	//�ʏ�
		for(i = 0; i < BREEDER_MAX; i++){
			consys->actin_sort[i] = i;
		}
	}

	return consys;
}

//--------------------------------------------------------------
/**
 * @brief   CPU�u���[�_�[�̃G���g���[�ƃp�����[�^����
 *
 * @param   consys					�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   hof_flag				�a������t���O(TRUE:�a�����肵�Ă���)
 * @param   zenkoku_zukan_flag		�S���}�ӓ���t���O(TRUE:���肵�Ă���)
 *
 * �ʐM����CPU�u���[�_�[�̍ăG���g���[�̎������ꂪ�g�p�o���܂�
 */
//--------------------------------------------------------------
static void Contest_CpuParamCreate(CONTEST_SYSTEM *consys, int hof_flag, int zenkoku_zukan_flag)
{
	int cpu_num = BREEDER_MAX - 1;
	int i;
	
	//CPU�u���[�_�[�Z�b�g
	ConTool_CpuBreederEntry(consys, HEAPID_WORLD, cpu_num, 
		consys->c_game.type, consys->c_game.rank, consys->c_game.mode,
		hof_flag, zenkoku_zukan_flag);
	
	//CPU�̃|�P�����p�����[�^�쐬
	for(i = 1; i < BREEDER_MAX; i++){
		ConTool_BreederPokeParaCreate(&consys->c_game.bd[i], consys->c_game.pp[i], HEAPID_CONTEST);
	}
	
	//�u���[�_�[���Z�b�g(�e�����u���[�_�[���ł͂Ȃ��̂�)
	for(i = 1; i < BREEDER_MAX; i++){
		if(consys->c_game.breeder_name_str[i] == NULL){
			consys->c_game.breeder_name_str[i] = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_CONTEST);
		}
		PokeParaGet(consys->c_game.pp[i], ID_PARA_oyaname_buf, consys->c_game.breeder_name_str[i]);
	}
	
	//���ʃZ�b�g
	for(i = 1; i < BREEDER_MAX; i++){
		consys->c_game.player_sex[i] = consys->c_game.bd[i].sex;
	}
	
	//���i�Z�b�g
	for(i = 1; i < BREEDER_MAX; i++){
		consys->c_game.character[i] = consys->c_game.bd[i].character;
	}

	//�l�C�Z�b�g
	for(i = 1; i < BREEDER_MAX; i++){
		consys->c_game.popularity[i] = consys->c_game.bd[i].popularity;
	}
	
	//OBJ�R�[�h
	for(i = 1; i < BREEDER_MAX; i++){
		consys->c_game.obj_code[i] = consys->c_game.bd[i].obj_code;
	}

	//CPU�u���[�_�[�̃C���[�W�N���b�v�Z�b�g
	ConTool_CpuBreederImcSet(consys, HEAPID_WORLD);
}

//--------------------------------------------------------------
/**
 * @brief   Contest_SystemCreate���g�p���č�����R���e�X�g�V�X�e�����[�N���������
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Contest_SystemExit(CONTEST_SYSTEM *consys)
{
	int i;
	
	sys_FreeMemoryEz(consys->poke_party);
	for(i = 0; i < BREEDER_MAX; i++){
		sys_FreeMemoryEz(consys->c_game.pp[i]);
		STRBUF_Delete(consys->c_game.breeder_name_str[i]);
		sys_FreeMemoryEz(consys->c_game.imc_data[i]);
		sys_FreeMemoryEz(consys->perap_voice[i]);
	}

	//�����_���̎한�A
	gf_srand(consys->push_random_seed);

	Contest_SystemWorkFree(consys);
	sys_DeleteHeap(HEAPID_CONTEST);
}

//--------------------------------------------------------------
/**
 * @brief   �v���C���[�̐l�C���擾����
 *
 * @param   my_pp			�����̃|�P�����ւ̃|�C���^
 * @param   con_type		�R���e�X�g�^�C�v
 *
 * @retval  �l�C
 */
//--------------------------------------------------------------
static int Contest_PlayerPopularityGet(POKEMON_PARAM *my_pp, int con_type)
{
	int popularity, rank, ribbon;
	
	popularity = 1;
	for(rank = CONRANK_NORMAL; rank <= CONRANK_MASTER; rank++){
		switch(con_type){
		case CONTYPE_STYLE:
			ribbon = PokeParaGet(my_pp, ID_PARA_trial_stylemedal_normal + rank, NULL);
			break;
		case CONTYPE_BEAUTIFUL:
			ribbon = PokeParaGet(my_pp, ID_PARA_trial_beautifulmedal_normal + rank, NULL);
			break;
		case CONTYPE_CUTE:
			ribbon = PokeParaGet(my_pp, ID_PARA_trial_cutemedal_normal + rank, NULL);
			break;
		case CONTYPE_CLEVER:
			ribbon = PokeParaGet(my_pp, ID_PARA_trial_clevermedal_normal + rank, NULL);
			break;
		case CONTYPE_STRONG:
			ribbon = PokeParaGet(my_pp, ID_PARA_trial_strongmedal_normal + rank, NULL);
			break;
		default:
			GF_ASSERT(0);
			break;
		}

		if(ribbon == 0){
			break;
		}
		popularity++;
	}
	return popularity;
}

//--------------------------------------------------------------
/**
 * @brief   �C���[�W�N���b�v��ʌĂяo���悤�̏������f�[�^�쐬
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Contest_ImageClipInitDataCreate(CONTEST_SYSTEM *consys)
{
	IMC_CONTEST_PROC_WORK *icpw;
	
	ImcSaveData_ClaenContestData(consys->c_game.imc_data[consys->c_game.my_breeder_no]);

	icpw = sys_AllocMemory(HEAPID_CONTEST, sizeof( IMC_CONTEST_PROC_WORK ) );
	MI_CpuClear8(icpw, sizeof(IMC_CONTEST_PROC_WORK));

	icpw->p_poke_para = consys->c_game.pp[consys->c_game.my_breeder_no];
	icpw->p_imc_one_data = 
		consys->c_game.imc_data[consys->c_game.my_breeder_no];
	icpw->theme = consys->c_game.theme;
	if(consys->sio_flag == TRUE){
		icpw->rank = CONRANK_IMC_SIO;
	}
	else{
		icpw->rank = consys->c_game.rank;
	}
	icpw->mode = consys->c_game.mode;
	icpw->type = consys->c_game.type;
	icpw->cp_imc_item = 
		ImcSaveData_GetItemSaveData(consys->imc_save);
	icpw->p_comm_data = &consys->imc_local;
	icpw->cp_config = consys->config;
	icpw->cp_tr = consys->my_status;
	consys->icpw = icpw;
	
	OS_TPrintf("�C���[�W�N���b�v�������e�[�}��%d, consys->theme = %d\n", icpw->theme, consys->c_game.theme);
}

//--------------------------------------------------------------
/**
 * @brief   �C���[�W�N���b�v��ʌĂяo���悤�̏������f�[�^���
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Contest_ImageClipInitDataFree(CONTEST_SYSTEM *consys)
{
	sys_FreeMemoryEz(consys->icpw);
	consys->icpw = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�̍ŏ��̒ʐM����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ContestComm_SioFastData(TCB_PTR tcb, void *work)
{
	CONTEST_SYSTEM *consys = work;
	enum{
		FASTSEQ_FAST_TIMING,
		FASTSEQ_FAST_TIMING_WAIT,
		FASTSEQ_FAST_SEND,
		FASTSEQ_FAST_WAIT,

		FASTSEQ_POKE_TIMING,
		FASTSEQ_POKE_TIMING_WAIT,
		FASTSEQ_POKE_SEND,
		FASTSEQ_POKE_WAIT,

		FASTSEQ_POKE_RESEND_TIMING,
		FASTSEQ_POKE_RESEND_TIMING_WAIT,
		FASTSEQ_POKE_RESEND,
		FASTSEQ_POKE_RESEND_WAIT,

		FASTSEQ_BD_TIMING,
		FASTSEQ_BD_TIMING_WAIT,
		FASTSEQ_BD_SEND,
		FASTSEQ_BD_WAIT,

		FASTSEQ_BD_RESEND_TIMING,
		FASTSEQ_BD_RESEND_TIMING_WAIT,
		FASTSEQ_BD_RESEND,
		FASTSEQ_BD_RESEND_WAIT,

		FASTSEQ_NAME_TIMING,
		FASTSEQ_NAME_TIMING_WAIT,
		FASTSEQ_NAME_SEND,
		FASTSEQ_NAME_WAIT,

		FASTSEQ_NAME_RESEND_TIMING,
		FASTSEQ_NAME_RESEND_TIMING_WAIT,
		FASTSEQ_NAME_RESEND,
		FASTSEQ_NAME_RESEND_WAIT,

		FASTSEQ_PERAP_TIMING,
		FASTSEQ_PERAP_TIMING_WAIT,
		FASTSEQ_PERAP_SEND,
		FASTSEQ_PERAP_WAIT,

		FASTSEQ_PERAP_RESEND_TIMING,
		FASTSEQ_PERAP_RESEND_TIMING_WAIT,
		FASTSEQ_PERAP_RESEND,
		FASTSEQ_PERAP_RESEND_WAIT,

		FASTSEQ_ETC_TIMING,
		FASTSEQ_ETC_TIMING_WAIT,
		FASTSEQ_ETC_SEND,
		FASTSEQ_ETC_WAIT,

		FASTSEQ_ETC_RESEND_TIMING,
		FASTSEQ_ETC_RESEND_TIMING_WAIT,
		FASTSEQ_ETC_RESEND,
		FASTSEQ_ETC_RESEND_WAIT,

		FASTSEQ_JUDGE_TIMING,
		FASTSEQ_JUDGE_TIMING_WAIT,
		FASTSEQ_JUDGE_SEND,
		FASTSEQ_JUDGE_WAIT,
	};
	
	switch(consys->seq){
	case FASTSEQ_FAST_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_FAST_PARAM);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_FAST_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_FAST_PARAM) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_FAST_SEND:
		if(CommContestSendFastParam(consys) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_FAST_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;
		
	case FASTSEQ_POKE_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_POKE);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_POKE_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_POKE) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_POKE_SEND:
		//�e�u���[�_�[�������̃|�P�����p�����[�^�𑗐M
		//�����̖��O�͍��͂܂�0�ԃu���[�_�[�̈ʒu�ɂ���̂ŁA�S��0�ԃu���[�_�[�̖��O�𑗐M
		if(CommContestSendPokePara(consys, consys->c_game.my_breeder_no, 
				consys->c_game.pp[0]) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_POKE_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;
		
	case FASTSEQ_POKE_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_POKE_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_POKE_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_POKE_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_POKE_RESEND:
		//�e�u���[�_�[�̃|�P�����p�����[�^���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
		#if 0	//�S���܂Ƃ߂đ��M����悤�ɕύX
			if(CommContestSendPokePara(consys, consys->work, 
					consys->c_game.pp[consys->work]) == TRUE){
				consys->seq++;
			}
		#else
			if(CommContestSendPokeParaAll(consys, consys->c_game.pp) == TRUE){
				consys->seq++;
			}
		#endif
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_POKE_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
		#if 0	//�S���܂Ƃ߂đ��M����悤�ɕύX
			consys->work++;
			if(consys->work < BREEDER_MAX){
				consys->seq--;
			}
			else{
				consys->work = 0;
				consys->seq++;
			}
		#else
			consys->seq++;
		#endif
		}
		break;
	
	case FASTSEQ_BD_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_BD);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_BD_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_BD) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_BD_SEND:
		//�e�u���[�_�[�������̃u���[�_�[�f�[�^�𑗐M
		//�����̖��O�͍��͂܂�0�ԃu���[�_�[�̈ʒu�ɂ���̂ŁA�S��0�ԃu���[�_�[�̖��O�𑗐M
		if(CommContestSendBreederData(consys, consys->c_game.my_breeder_no, 
				&consys->c_game.bd[0]) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_BD_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;
	
	case FASTSEQ_BD_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_BD_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_BD_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_BD_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_BD_RESEND:
		//�e�u���[�_�[�̃u���[�_�[�f�[�^���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
			if(CommContestSendBreederData(consys, consys->work, 
					&consys->c_game.bd[consys->work]) == TRUE){
				consys->seq++;
			}
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_BD_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
			consys->work++;
			if(consys->work < BREEDER_MAX){
				consys->seq--;
			}
			else{
				consys->work = 0;
				consys->seq++;
			}
		}
		break;

	case FASTSEQ_NAME_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_NAME);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_NAME_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_NAME) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_NAME_SEND:
		//�e�u���[�_�[�������̖��O�𑗐M
		//�����̖��O�͍��͂܂�0�ԃu���[�_�[�̈ʒu�ɂ���̂ŁA�S��0�ԃu���[�_�[�̖��O�𑗐M
		if(CommContestSendNameData(consys, consys->c_game.my_breeder_no,
				consys->c_game.breeder_name_str[0]) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_NAME_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;

	case FASTSEQ_NAME_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_NAME_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_NAME_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_NAME_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_NAME_RESEND:
		//�e�u���[�_�[�̖��O���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
			if(CommContestSendNameData(consys, consys->work,
					consys->c_game.breeder_name_str[consys->work]) == TRUE){
				consys->seq++;
			}
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_NAME_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
			consys->work++;
			if(consys->work < BREEDER_MAX){
				consys->seq--;
			}
			else{
				consys->work = 0;
				consys->seq++;
			}
		}
		break;

	case FASTSEQ_PERAP_TIMING:
		//perap_voice[0]�ɂ��f�[�^����M�����̂ŁA���M�O�Ɏ�M���ď㏑������鎖���Ȃ��悤��
		//huge_buf�ɐ�ɃR�s�[���Ă���
		MI_CpuCopy8(consys->perap_voice[0], consys->huge_buf, PERAPVOICE_GetWorkSize());
		
		CommTimingSyncStart(CONSIO_TIMING_PERAP);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_PERAP_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_PERAP) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_PERAP_SEND:
		//�e�u���[�_�[�������̂؃��b�v�f�[�^�𑗐M
		//�����̂؃��b�v�f�[�^�͂܂�0�ԃu���[�_�[�̈ʒu�ɂ���̂ŁA�S��0�ԃu���[�_�[�ő��M
		if(CommContestSendPerap(consys, consys->c_game.my_breeder_no, NULL) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_PERAP_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;

	case FASTSEQ_PERAP_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_PERAP_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_PERAP_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_PERAP_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_PERAP_RESEND:
		//�e�u���[�_�[�̃|�P�����p�����[�^���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
			if(CommContestSendPerap(consys, consys->work, 
					consys->perap_voice[consys->work]) == TRUE){
				consys->seq++;
			}
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_PERAP_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
			consys->work++;
			if(consys->work < BREEDER_MAX){
				consys->seq--;
			}
			else{
				consys->work = 0;
				consys->seq++;
			}
		}
		break;

	case FASTSEQ_ETC_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_ETC);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_ETC_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_ETC) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_ETC_SEND:
		//�e�u���[�_�[�������ׂ̍����f�[�^�Q�𑗐M
		//�����̃f�[�^�͂܂�0�ԃu���[�_�[�̈ʒu�ɂ���̂ŁA�S��0�ԃu���[�_�[�ő��M
		{
			CON_ETC_SIO_DATA etc_data;
			
			SioEtcDataSet(consys, 0, &etc_data);
			if(CommContestSendEtcData(consys, consys->c_game.my_breeder_no, 
					&etc_data) == TRUE){
				consys->seq++;
			}
		}
		break;
	case FASTSEQ_ETC_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;
		
	case FASTSEQ_ETC_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_ETC_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_ETC_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_ETC_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_ETC_RESEND:
		//�e�u���[�_�[�̃p�����[�^���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
			CON_ETC_SIO_DATA etc_data;
			
			SioEtcDataSet(consys, consys->work, &etc_data);
			if(CommContestSendEtcData(consys, consys->work, &etc_data) == TRUE){
				consys->seq++;
			}
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_ETC_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
			consys->work++;
			if(consys->work < BREEDER_MAX){
				consys->seq--;
			}
			else{
				consys->work = 0;
				consys->seq++;
			}
		}
		break;

	case FASTSEQ_JUDGE_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_JUDGE);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_JUDGE_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_JUDGE) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_JUDGE_SEND:
		//�e�������Ă���R���f�[�^�S�Ă���đ��M
		if(CommContestSendJudgeData(consys, consys->c_game.my_breeder_no, 
				consys->c_game.jd) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_JUDGE_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;

	default:
		{//��check�@��ŕς���(�v���C���[�̐��ʂ͂������ǁACPU�̐��ʂ̓u���[�_�[�f�[�^��
		 //����M���Ă��鏊���������Đ��ʂ𑗂�悤�ɂ���)
			//���ʃZ�b�g
			int i;
			const MYSTATUS *my_status;
			for(i = 0; i < consys->c_game.player_num; i++){
				my_status = CommInfoGetMyStatus(i);
				consys->c_game.player_sex[i] = MyStatus_GetMySex(my_status);
			}
			for( ; i < BREEDER_MAX; i++){
				consys->c_game.player_sex[i] = consys->c_game.bd[i].sex;
			}
		}
		
		//�C���[�W�N���b�v����M�o�b�t�@�ɕK�v�ȃV�X�e���f�[�^�Z�b�g
		{
			consys->imc_local.server_no = consys->c_game.server_no;
			consys->imc_local.my_net_id = consys->c_game.my_net_id;
			consys->imc_local.sio_flag = TRUE;
			consys->imc_local.player_num = consys->c_game.player_num;
		}
		
		consys->sio_tcb = NULL;
		consys->seq = 0;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�̏ꍇ�̃��[�N�����p�����[�^�ݒ���s���B
 * @param   consys		
 * @retval  TRUE:�����ݒ萬���B�@FALSE:���s
 */
//--------------------------------------------------------------
BOOL Contest_SioParamInitSet(CONTEST_SYSTEM *consys)
{
	int connect_num, net_id;

	if(CommIsInitialize() == FALSE){
		return FALSE;
	}
	
	consys->sio_flag = TRUE;
	
	connect_num = CommGetConnectNum();
	net_id = CommGetCurrentID();

	{//�S�����a������A�S���}�ӓ���ς݂��`�F�b�N
		int i;
		MYSTATUS *my_status;
		
		//�S�����a������ς݂��`�F�b�N
		for(i = 0; i < connect_num; i++){
			my_status = CommInfoGetMyStatus(i);
			GF_ASSERT(my_status != NULL);
			if(MyStatus_GetDpClearFlag(my_status) == 0){
				break;
			}
		}
		if(i != connect_num){
			consys->hof_flag = FALSE;
			OS_TPrintf("�a�����肵�Ă��Ȃ��v���C���[������\n");
		}
		else{
			consys->hof_flag = TRUE;
			OS_TPrintf("�S���a������ς�\n");
		}

		//�S�����S���}�ӓ���ς݂��`�F�b�N
		for(i = 0; i < connect_num; i++){
			my_status = CommInfoGetMyStatus(i);
			GF_ASSERT(my_status != NULL);
			if(MyStatus_GetDpZenkokuFlag(my_status) == 0){
				break;
			}
		}
		if(i != connect_num){
			consys->zenkoku_zukan_flag = FALSE;
			OS_TPrintf("�S���}�ӂ���Ȃ��v���C���[������\n");
		}
		else{
			consys->zenkoku_zukan_flag = TRUE;
			OS_TPrintf("�S���S���}��\n");
		}

		//�S���̓a������A�S���}�ӓ���t���O���擾������ɁA���������
		//CPU�u���[�_�[���ăG���g���[
		Contest_CpuParamCreate(consys, consys->hof_flag, consys->zenkoku_zukan_flag);
	}
	
	consys->c_game.my_net_id = net_id;
	consys->c_game.cpu_num = BREEDER_MAX - connect_num;
	consys->c_game.player_num = connect_num;
	consys->c_game.my_breeder_no = net_id;
	consys->c_game.my_version = CONTEST_VERSION;
	consys->c_game.theme = ConTool_ThemeRandomSelect(consys->c_game.rank, TRUE);

	OS_TPrintf("�ڑ��l����%d\n", connect_num);
	OS_TPrintf("������netID��%d\n", consys->c_game.my_net_id);
	OS_TPrintf("CPU�̐l����%d\n", consys->c_game.cpu_num);
	
	//�ʐM���[�h���R���e�X�g��
	CommCommandContestInitialize(consys);
	
	//�ŏ��̒ʐM���s���^�X�N�𐶐�
	consys->sio_tcb = TCB_Add(ContestComm_SioFastData, consys, 10);
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�ʐM�̍ŏ��̃f�[�^�������I���������m�F
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I���B�@FALSE:���s��
 */
//--------------------------------------------------------------
BOOL Contest_SioFastDataEndCheck(CONTEST_SYSTEM *consys)
{
	return Contest_SioCommDataEndCheck(consys);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�ʐM�̃f�[�^�������I���������m�F
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�I���B�@FALSE:���s��
 */
//--------------------------------------------------------------
BOOL Contest_SioCommDataEndCheck(CONTEST_SYSTEM *consys)
{
	if(consys->sio_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �C���[�W�N���b�v�����f�[�^�𑗎�M����
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * �C���[�W�N���b�v��ʏI����ɌĂԂ��ƂŁA�����f�[�^�𑗎�M���܂��B
 */
//--------------------------------------------------------------
static void Contest_SioImcData(CONTEST_SYSTEM *consys)
{
	GF_ASSERT(consys->sio_tcb == NULL);
	consys->seq = 0;
	consys->sio_tcb = TCB_Add(ContestComm_ImcData, consys, 10);
}

//--------------------------------------------------------------
/**
 * @brief   �C���[�W�N���b�v�����f�[�^����M
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ContestComm_ImcData(TCB_PTR tcb, void *work)
{
	CONTEST_SYSTEM *consys = work;
	enum{
		FASTSEQ_IMC_TIMING,
		FASTSEQ_IMC_TIMING_WAIT,
		FASTSEQ_IMC_SEND,
		FASTSEQ_IMC_WAIT,

		FASTSEQ_IMC_RESEND_TIMING,
		FASTSEQ_IMC_RESEND_TIMING_WAIT,
		FASTSEQ_IMC_RESEND,
		FASTSEQ_IMC_RESEND_WAIT,
	};
	
	switch(consys->seq){
	case FASTSEQ_IMC_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_IMC);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_IMC_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_IMC) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_IMC_SEND:
		//�e�u���[�_�[�������̃|�P�����p�����[�^�𑗐M
		if(CommContestSendClipData(consys, consys->c_game.my_breeder_no, 
				consys->c_game.imc_data[consys->c_game.my_breeder_no]) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_IMC_WAIT:
		if(consys->recieve_count >= consys->c_game.player_num){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;

	case FASTSEQ_IMC_RESEND_TIMING:
		CommTimingSyncStart(CONSIO_TIMING_IMC_RESEND);
		consys->recieve_count = 0;
		consys->seq++;
		break;
	case FASTSEQ_IMC_RESEND_TIMING_WAIT:
		if(CommIsTimingSync(CONSIO_TIMING_IMC_RESEND) == TRUE){
			consys->seq++;
		}
		break;
	case FASTSEQ_IMC_RESEND:
		//�e�u���[�_�[�̃|�P�����p�����[�^���󂯎�����e���ACPU�̕����܂߂čđ��M����
		if(consys->c_game.my_breeder_no == consys->c_game.server_no){
			if(CommContestSendClipDataAll(consys, consys->c_game.imc_data) == TRUE){
				consys->seq++;
			}
		}
		else{
			consys->seq++;
		}
		break;
	case FASTSEQ_IMC_RESEND_WAIT:
		if(consys->recieve_count > 0){
			consys->recieve_count = 0;
			consys->seq++;
		}
		break;
	
	default:
		consys->sio_tcb = NULL;
		consys->seq = 0;
		TCB_Delete(tcb);
		return;
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�R�������擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   judge_no	�R���ԍ�
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_JudgeNameGet(CONTEST_SYSTEM *consys, int judge_no, WORDSET *wordset, u32 buf_id)
{
	WORDSET_RegisterJudgeName(wordset, buf_id, consys->c_game.jd[judge_no].name_id);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�u���[�_�[�����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   entry_no	�G���g���[�ԍ�
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_BreederNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, u32 buf_id)
{
	int sex, breeder_no;
	
	breeder_no = ConTool_BreederNoGet(entry_no);
	WORDSET_RegisterWord(wordset, buf_id, consys->c_game.breeder_name_str[breeder_no], 
		consys->c_game.player_sex[breeder_no], TRUE, PM_LANG);
	//RegisterWord(wordset, buf_id, consys->c_game.breeder_name_str[breeder_no], NULL);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�|�P�����̃j�b�N�l�[�����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   entry_no	�G���g���[�ԍ�
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_NickNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, u32 buf_id)
{
	POKEMON_PASO_PARAM * ppp;
	int breeder_no;
	
	breeder_no = ConTool_BreederNoGet(entry_no);
	ppp = PPPPointerGet(consys->c_game.pp[breeder_no]);
	WORDSET_RegisterPokeNickName(wordset, buf_id, ppp);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�R���e�X�g�����N�����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_RankNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id)
{
	u32 str_id;
	
	str_id = ConTool_GetRankMsgID(consys->c_game.rank, consys->c_game.mode, consys->sio_flag);
	WORDSET_RegisterContestRank(wordset, buf_id, str_id);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�R���e�X�g�^�C�v��(�R���e�X�g����)���擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_TypeNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id)
{
	u32 str_id;
	
	str_id = ConTool_GetTypeMsgID(consys->c_game.type, consys->c_game.mode);
	WORDSET_RegisterContestType(wordset, buf_id, str_id);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�D�������u���[�_�[�̖��O���擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_VictoryBreederNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id)
{
	int victory_breeder, entry_no;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(consys->c_game.score[i].final_ranking == 0){
			break;
		}
	}
	victory_breeder = i;
	entry_no = ConTool_EntryNoGet(victory_breeder);
	ConScr_BreederNameGet(consys, entry_no, wordset, buf_id);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�D�������u���[�_�[�̃|�P�����j�b�N�l�[�����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 */
//--------------------------------------------------------------
void ConScr_VictoryNickNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id)
{
	int victory_breeder, entry_no;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(consys->c_game.score[i].final_ranking == 0){
			break;
		}
	}
	victory_breeder = i;
	entry_no = ConTool_EntryNoGet(victory_breeder);
	ConScr_NickNameGet(consys, entry_no, wordset, buf_id);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�D���������ɖႦ��A�C�e���ԍ����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �A�C�e���ԍ�
 */
//--------------------------------------------------------------
u32 ConScr_VictoryItemNoGet(CONTEST_SYSTEM *consys)
{
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�ʐM�����҂����ߑ��M
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   timing_no		�^�C�~���O�ԍ�
 *
 * ��ʐM�̎��͉������܂���
 */
//--------------------------------------------------------------
void ConScr_SioTimingSend(CONTEST_SYSTEM *consys, u8 timing_no)
{
	if(consys->sio_flag == FALSE){
		return;
	}
	CommTimingSyncStart(timing_no);
}

//--------------------------------------------------------------
/**
 * @brief   �X�N���v�g�p���߁F�ʐM�����A��M�҂�
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   timing_no		�^�C�~���O�ԍ�
 *
 * @retval  TRUE:������ꂽ�B�@FALSE:�҂���
 *
 * ��ʐM�̎���TRUE�݂̂��Ԃ�܂�
 */
//--------------------------------------------------------------
BOOL ConScr_SioTimingCheck(CONTEST_SYSTEM *consys, u8 timing_no)
{
	if(consys->sio_flag == FALSE){
		return TRUE;
	}
	
	if(CommIsTimingSync(timing_no) == TRUE){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���Q�����Ă����R���e�X�g�Ŏ��������ʂ����������擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  ����(0�I���W���ł��B 0=1�ʁA1=2�ʁA2=3�ʁA3=4��)
 */
//--------------------------------------------------------------
int ConScr_RankingCheck(CONTEST_SYSTEM *consys)
{
	return consys->c_game.score[consys->c_game.my_breeder_no].final_ranking;
}

//--------------------------------------------------------------
/**
 * @brief   �D�������u���[�_�[�̃G���g���[�ԍ����擾����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �G���g���[�ԍ�
 */
//--------------------------------------------------------------
int ConScr_VictoryEntryNoGet(CONTEST_SYSTEM *consys)
{
	int victory_breeder;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(consys->c_game.score[i].final_ranking == 0){
			return ConTool_EntryNoGet(i);
		}
	}
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   �����̃G���g���[�ԍ����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �G���g���[�ԍ�
 */
//--------------------------------------------------------------
int ConScr_MyEntryNoGet(CONTEST_SYSTEM *consys)
{
	return ConTool_EntryNoGet(consys->c_game.my_breeder_no);
}

//--------------------------------------------------------------
/**
 * @brief   OBJ�R�[�h���擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   entry_no	�G���g���[�ԍ�
 *
 * @retval  OBJ�R�[�h
 */
//--------------------------------------------------------------
int ConScr_OBJCodeGet(CONTEST_SYSTEM *consys, int entry_no)
{
	int breeder_no;
	int code;
	
	{
		int i;
		for(i = 0; i < 4; i++){
			OS_TPrintf("%d��code = %d\n", i, consys->c_game.obj_code[i]);
		}
	}
	breeder_no = ConTool_BreederNoGet(entry_no);
	code = consys->c_game.obj_code[breeder_no];
	OS_TPrintf("code = %d, breeder_no = %d, entry_no = %d\n", code, breeder_no, entry_no);
	return code;
}

//--------------------------------------------------------------
/**
 * @brief   �l�C���擾����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   entry_no		�G���g���[�ԍ�
 *
 * @retval  �l�C
 */
//--------------------------------------------------------------
int ConScr_PopularityGet(CONTEST_SYSTEM *consys, int entry_no)
{
	int breeder_no;
	
	breeder_no = ConTool_BreederNoGet(entry_no);
	return consys->c_game.popularity[breeder_no];
}

//--------------------------------------------------------------
/**
 * @brief   ��t�i���o�[(�V���O��DESK_SINGLE�A�}���`DESK_MULTI, ���KDESK_PRACTICE)���擾
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  ��t�i���o�[
 */
//--------------------------------------------------------------
int ConScr_DeskModeGet(CONTEST_SYSTEM *consys)
{
	enum{//��con_reception.ev�ɂ��铯����define��`�Ɣԍ�������Ȃ��悤�ɒ��ӂ��鎖�I�I
		DESK_SINGLE = 0,	//�V���O��
		DESK_MULTI,			//�}���`
		DESK_PRACTICE,		//���K
	};
	
	if(consys->sio_flag == TRUE){
		return DESK_MULTI;
	}
	if(ConTool_PracticeModeCheck(consys) == TRUE){
		return DESK_PRACTICE;
	}
	return DESK_SINGLE;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�V�X�e�����[�N���烉���N�⃂�[�h�Ȃǂ��擾����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  ��t�i���o�[
 */
//--------------------------------------------------------------
void ConScr_EntryParamGet(CONTEST_SYSTEM *consys, u16 *rank, u16 *type, u16 *mode, u16 *temoti_pos)
{
	*rank = consys->c_game.rank;
	*type = consys->c_game.type;
	*mode = consys->c_game.mode;
	*temoti_pos = consys->temoti_pos;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�p�̃��b�Z�[�W����ݒ���s��
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ConScr_MsgPrintFlagSet(CONTEST_SYSTEM *consys)
{
	ConTool_MsgPrintFlagSet(consys->sio_flag);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�p�̃��b�Z�[�W����ݒ�����Z�b�g����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ConScr_MsgPrintFlagReset(CONTEST_SYSTEM *consys)
{
	ConTool_MsgPrintFlagReset();
}

//--------------------------------------------------------------
/**
 * @brief   �Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{�������Ɏ����Ă��邩�`�F�b�N
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:���Ɏ����Ă���(�D���o���ς�)�B�@FALSE:�����Ă��Ȃ�
 */
//--------------------------------------------------------------
BOOL ConScr_HaveRibbonCheck(CONTEST_SYSTEM *consys)
{
	u32 ribbon;
	
	ribbon = ConTool_RibbonIDGet(consys->c_game.rank, consys->c_game.type);
	if(PokeParaGet(consys->my_pp, ribbon, NULL) == 0){
		OS_TPrintf("�D���������ɖႦ�郊�{���͂܂������Ă��Ȃ�\n");
		return FALSE;	//�܂������Ă��Ȃ�
	}
	
	OS_TPrintf("�D�����{���͊��Ɏ����Ă���\n");
	return TRUE;	//���Ɏ����Ă���
}

//--------------------------------------------------------------
/**
 * @brief   ���Q�����Ă���R���e�X�g�ŗD���������ɖႦ�郊�{���̖��O���擾����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   wordset		���[�h�Z�b�g�I�u�W�F�N�g
 * @param   buf_id		���Ԃ̃o�b�t�@�ɓo�^���邩
 * @param   heap_id		�q�[�vID
 */
//--------------------------------------------------------------
void ConScr_RibbonItemNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id, int heap_id)
{
	u32 ribbon_id, str_id;
	
	switch(consys->c_game.type){
	case CONTYPE_STYLE:
		ribbon_id = RIBBON_ID_COOL + consys->c_game.rank;
		break;
	case CONTYPE_BEAUTIFUL:
		ribbon_id = RIBBON_ID_BEAUTY + consys->c_game.rank;
		break;
	case CONTYPE_CUTE:
		ribbon_id = RIBBON_ID_CUTE + consys->c_game.rank;
		break;
	case CONTYPE_CLEVER:
		ribbon_id = RIBBON_ID_GENEASU + consys->c_game.rank;
		break;
	case CONTYPE_STRONG:
		ribbon_id = RIBBON_ID_PAWAFURU + consys->c_game.rank;
		break;
	default:
		GF_ASSERT(0);
		return;
	}
	str_id = RIBBON_DataGet(ribbon_id, RIBBON_PARA_NAME);
	WORDSET_RegisterRibbonName( wordset, buf_id, str_id );
}

//--------------------------------------------------------------
/**
 * @brief   �D���������ɖႦ��A�N�Z�T���ԍ����擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �A�N�Z�T���ԍ�(�D�����Ă��Ȃ� or ���Ɍ��E���������Ă���ꍇ��0xffff���Ԃ�܂�)
 */
//--------------------------------------------------------------
u32 ConScr_AcceNoGet(CONTEST_SYSTEM *consys)
{
	u32 acce_no = IMC_ACCE_MAX;
	
	if(consys->c_game.score[consys->c_game.my_breeder_no].final_ranking > 0){
		OS_TPrintf("�A�N�Z�T���[�F�D�����ĂȂ��̂Ŏ擾�Ȃ�\n");
		return 0xffff;	//�D���ł͂Ȃ�
	}
	
	switch(consys->c_game.type){
	case CONTYPE_STYLE:
		switch(consys->c_game.rank){
		case CONRANK_NORMAL:
			acce_no = IMC_ACCE_RIBBON01;
			break;
		case CONRANK_SUPER:
			acce_no = IMC_ACCE_BALLOON01;
			break;
		case CONRANK_HYPER:
			acce_no = IMC_ACCE_HAT01;
			break;
		case CONRANK_MASTER:
			acce_no = IMC_ACCE_STAGE01;
			break;
		}
		break;
	case CONTYPE_BEAUTIFUL:
		switch(consys->c_game.rank){
		case CONRANK_NORMAL:
			acce_no = IMC_ACCE_RIBBON02;
			break;
		case CONRANK_SUPER:
			acce_no = IMC_ACCE_BALLOON02;
			break;
		case CONRANK_HYPER:
			acce_no = IMC_ACCE_HAT02;
			break;
		case CONRANK_MASTER:
			acce_no = IMC_ACCE_STAGE02;
			break;
		}
		break;
	case CONTYPE_CUTE:
		switch(consys->c_game.rank){
		case CONRANK_NORMAL:
			acce_no = IMC_ACCE_RIBBON00;
			break;
		case CONRANK_SUPER:
			acce_no = IMC_ACCE_BALLOON00;
			break;
		case CONRANK_HYPER:
			acce_no = IMC_ACCE_HAT00;
			break;
		case CONRANK_MASTER:
			acce_no = IMC_ACCE_STAGE00;
			break;
		}
		break;
	case CONTYPE_CLEVER:
		switch(consys->c_game.rank){
		case CONRANK_NORMAL:
			acce_no = IMC_ACCE_RIBBON04;
			break;
		case CONRANK_SUPER:
			acce_no = IMC_ACCE_BALLOON04;
			break;
		case CONRANK_HYPER:
			acce_no = IMC_ACCE_HAT04;
			break;
		case CONRANK_MASTER:
			acce_no = IMC_ACCE_STAGE03;
			break;
		}
		break;
	case CONTYPE_STRONG:
		switch(consys->c_game.rank){
		case CONRANK_NORMAL:
			acce_no = IMC_ACCE_RIBBON03;
			break;
		case CONRANK_SUPER:
			acce_no = IMC_ACCE_BALLOON03;
			break;
		case CONRANK_HYPER:
			acce_no = IMC_ACCE_HAT03;
			break;
		case CONRANK_MASTER:
			acce_no = IMC_ACCE_HYOSHODAI00;
			break;
		}
		break;
	}

	GF_ASSERT(acce_no != IMC_ACCE_MAX);
	OS_TPrintf("�A�N�Z�T���[�Facce_no = %d\n", acce_no);
	
	//�A�N�Z�T�����ǉ��o���邩���`�F�b�N
	{
		IMC_SAVEDATA* imc;
		IMC_ITEM_SAVEDATA* imc_item;

		imc	= SaveData_GetImcSaveData(consys->sv);
		imc_item = ImcSaveData_GetItemSaveData(imc);	//�A�C�e���Z�[�u�f�[�^�擾
		if(ImcSaveData_CheckAcceAdd(imc_item, acce_no, 1) == FALSE){
			OS_TPrintf("�A�N�Z�T���[�F����ȏ�Add�o���Ȃ��̂Ŏ擾���Ȃ�\n");
			return 0xffff;	//�ǉ��s�\
		}
	}
	
	OS_TPrintf("�A�N�Z�T���[�FAdd�\\n");
	return acce_no;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̃t���b�V���G�t�F�N�g����^�X�N�𐶐�����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   entry_no		�G���g���[�ԍ�
 */
//--------------------------------------------------------------
void ConScr_FlashTaskCreate(CONTEST_SYSTEM *consys, int entry_no)
{
	CONSCR_CAMERA_FLASH *flash;
	
	GF_ASSERT(consys->conscr_flash == NULL);
	
	flash = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(CONSCR_CAMERA_FLASH));
	MI_CpuClear8(flash, sizeof(CONSCR_CAMERA_FLASH));
	
	flash->breeder_no = ConTool_BreederNoGet(entry_no);
	
	{
		int tbl_no;
		
		tbl_no = consys->c_game.character[flash->breeder_no] & 1;
		if(consys->sio_flag == TRUE){
			flash->wait_tbl = CameraFlashWait_Master[tbl_no];
		}
		else{
			switch(consys->c_game.rank){
			case CONRANK_NORMAL:
				flash->wait_tbl = CameraFlashWait_Normal[tbl_no];
				break;
			case CONRANK_SUPER:
				flash->wait_tbl = CameraFlashWait_Super[tbl_no];
				break;
			case CONRANK_HYPER:
				flash->wait_tbl = CameraFlashWait_Hyper[tbl_no];
				break;
			case CONRANK_MASTER:
			default:
				flash->wait_tbl = CameraFlashWait_Master[tbl_no];
				break;
			}
		}
	}
	
	flash->tcb = TCB_Add(ConScr_FlashMain, consys, 100);
	consys->conscr_flash = flash;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̃t���b�V���G�t�F�N�g���I�����Ă��邩�`�F�b�N����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�I�����Ă���B�@FALSE:�G�t�F�N�g��
 */
//--------------------------------------------------------------
BOOL ConScr_FlashTaskCheck(CONTEST_SYSTEM *consys)
{
	if(consys->conscr_flash == NULL){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̃t���b�V���G�t�F�N�g���C���^�X�N
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ConScr_FlashMain(TCB_PTR tcb, void *work)
{
	CONTEST_SYSTEM *consys = work;
	CONSCR_CAMERA_FLASH *flash = consys->conscr_flash;
	
	if(IsFinishedBrightnessChg(MASK_MAIN_DISPLAY) == FALSE){
		return;
	}
	
	switch(flash->seq){
	case 0:
		flash->wait++;
		if(flash->wait > flash->wait_tbl[flash->count]){
			ChangeBrightnessRequest(CON_CAMERA_FLASH_FRAME, BRIGHTNESS_NORMAL, 
				CON_CAMERA_FLASH_EVY, PLANEMASK_ALL, MASK_MAIN_DISPLAY);
			Snd_SePlay(SEQ_SE_DP_CON_014);
			flash->count++;
			flash->wait = 0;
			if(flash->wait_tbl[flash->count] == 0xff){
				flash->seq++;
			}
		}
		break;
	default:
		sys_FreeMemoryEz(consys->conscr_flash);
		consys->conscr_flash = NULL;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �D�������u���[�_�[�̐F�X�ȃf�[�^���擾
 *
 * @param   victory_entry		�D�������u���[�_�[�̃G���g���[�ԍ�
 * @param   sio_flag			�ʐM�ΐ킩�ǂ���(TRUE:�ʐM�ΐ�)
 * @param   cpu_flag			�D�������̂�CPU���ǂ���(TRUE:CPU�AFALSE:�v���C���[)
 * @param   tutorial			TRUE:�`���[�g���A��
 * @param   practice			TRUE:���K
 */
//--------------------------------------------------------------
void ConScr_VictoryParamGet(CONTEST_SYSTEM *consys, 
	int *victory_entry, int *sio_flag, int *cpu_flag, int *tutorial, int *practice)
{
	int victory_breeder;
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(consys->c_game.score[i].final_ranking == 0){
			break;
		}
	}
	victory_breeder = i;
	*victory_entry = ConTool_EntryNoGet(victory_breeder);
	*sio_flag = consys->sio_flag;
	if(victory_breeder >= consys->c_game.player_num){
		*cpu_flag = TRUE;
	}
	else{
		*cpu_flag = FALSE;
	}
	
	*tutorial = FALSE;
	*practice = FALSE;
	switch(consys->c_game.mode){
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_ACTIN_PRACTICE:
		*tutorial = TRUE;
		break;
	case CONMODE_VISUAL_TUTORIAL:
	case CONMODE_DANCE_TUTORIAL:
	case CONMODE_ACTIN_TUTORIAL:
		*practice = TRUE;
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�I����A�e��p�����[�^�̍X�V����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ConScr_EndParamSet(CONTEST_SYSTEM *consys, SAVEDATA *sv, u32 place_id, FNOTE_DATA *f_note)
{
	int first_ribbon_get;
	
	first_ribbon_get = FALSE;
	
	switch(consys->c_game.mode){
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_VISUAL_TUTORIAL:
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_DANCE_TUTORIAL:
	case CONMODE_ACTIN_PRACTICE:
	case CONMODE_ACTIN_TUTORIAL:
		return;		//�{�ԂłȂ��Ȃ牽���Z�b�g���Ȃ�
	}
	
	if(consys->sio_flag == FALSE){
		//-- ��ʐM�̎��݂̂̏��� --//
		
		//�}�X�^�[�����N�D���Ȃ�΃t���O�Z�b�g
		{
			EVENTWORK *ev;
			ev = SaveData_GetEventWork(consys->sv);
			if(consys->c_game.mode == CONMODE_GRAND && consys->c_game.rank >= CONRANK_MASTER 
					&& ConScr_RankingCheck(consys) == 0){
				if(SysFlag_ConMasterCheck(ev, consys->c_game.type) == 0){
					SysFlag_ConMasterSet(ev, consys->c_game.type);
				}
			}
		}
		
		//���{���̃Z�b�g
		if(ConScr_RankingCheck(consys) == 0){
			int ribbon;
			u8 flag = TRUE;
			
			ribbon = ConTool_RibbonIDGet(consys->c_game.rank, consys->c_game.type);
			if(PokeParaGet(consys->my_pp, ribbon, NULL) == 0){
				first_ribbon_get = TRUE;	//�܂���ɓ��ꂽ���̂Ȃ����{��
			}
			PokeParaPut(consys->my_pp, ribbon, &flag);
		}
		
		//�e���r�Z�b�g
		{
			TV_WORK *tvwk;
			
			tvwk = SaveData_GetTvWork(consys->sv);
			TVTOPIC_ContestTemp_Set(tvwk, consys->my_pp, 
				consys->c_game.type, consys->c_game.rank, 
				consys->c_game.score[consys->c_game.my_breeder_no].final_ranking + 1);
		}
		
		//�J�E���^�[���X�R�A
		{
			RECORD *rec;
			
			rec = SaveData_GetRecord(consys->sv);
			RECORD_Inc(rec, RECID_CONTEST_ENTRY);
			if(ConScr_RankingCheck(consys) == 0){
				RECORD_Inc(rec, RECID_CONTEST_GPX);
				RECORD_Score_Add(rec, SCORE_ID_CONTEST_GRANDPRIX);
			}
			if(first_ribbon_get == TRUE){
				RECORD_Inc(rec, RECID_CONTEST_RIBBON_GET);
			}
		}
		
		//�}�ӌ����t���O�Z�b�g
		{
			int i;
			ZUKAN_WORK *zw;
			
			zw = SaveData_GetZukanWork(consys->sv);
			for(i = consys->c_game.player_num; i < BREEDER_MAX; i++){
				ZukanWork_SetPokeSee(zw, consys->c_game.pp[i]);
			}
		}
	}
	else{
		//-- �ʐM�ΐ�̎��݂̂̏��� --//
		//�ʐM�ΐ퐬�ыL�^
		CONDATA_RecordAdd(consys->sv, consys->c_game.type, 
			consys->c_game.score[consys->c_game.my_breeder_no].final_ranking);

		//�J�E���^�[���X�R�A
		{
			RECORD *rec;
			
			rec = SaveData_GetRecord(consys->sv);
			RECORD_Inc(rec, RECID_CONTEST_COMM_ENTRY);
			if(ConScr_RankingCheck(consys) == 0){
				RECORD_Inc(rec, RECID_CONTEST_COMM_GPX);
				RECORD_Score_Add(rec, SCORE_ID_COMM_CONTEST_GRANDPRIX);
			}
		}
		
		//�`���m�[�g
		{
			void *buf;
			FNOTE_DATA *fd;
			
			buf = FNOTE_SioContestDataMake(
				consys->c_game.score[consys->c_game.my_breeder_no].final_ranking + 1, 
				HEAPID_WORLD);
			fd = SaveData_GetFNote(consys->sv);
//			FNOTE_DataSave(FNOTE_SavePageGet(fd, TRUE), buf, FNOTE_TYPE_SIO);
			FNOTE_DataSave(f_note, buf, FNOTE_TYPE_SIO);
		}
	}
	
	
	//-- ��ʐM�E�ʐM���ʂ̏��� --//
	
	//�G��̃Z�b�g
	if(ConScr_RankingCheck(consys) == 0){
		IMC_SAVEDATA *imc_sv;
		IMC_CONTEST_SAVEDATA *con_sv;
		
		imc_sv = SaveData_GetImcSaveData(consys->sv);
		con_sv = ImcSaveData_GetContestSaveData(imc_sv, consys->c_game.type);
		ImcSaveData_ClaenContestData(con_sv);
		ImcSaveData_CopyContest(con_sv, consys->c_game.imc_data[consys->c_game.my_breeder_no]);
		ImcSaveData_SetComplateFlagContestData(con_sv);
	}
	
	//�Ȃ��x�㏸
	if(ConScr_RankingCheck(consys) == 0){
		FriendCalc(consys->my_pp, 
			FRIEND_CONTEST_VICTORY, place_id);
	}
}


//==============================================================================
//	
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g��p�̃����_���̎평����
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void contest_srand(CONTEST_SYSTEM *consys)
{
	gf_srand((GF_RTC_GetTimeBySecond() * (gf_get_seed() + 10)) & 0xffff);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g��p�̃����_���擾�֐�
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @retval  �����_���l
 */
//--------------------------------------------------------------
u16 contest_rand(CONTEST_SYSTEM *consys)
{
	return gf_rand();
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g��p�̃����_���擾�֐�
 *          �����_�����擾���邽�тɎ��n���A�����_���l�ƐV��������󂯎��
 *
 * @param   seed			�����_���̎�
 * @param   new_seed		�����_���v�Z��̐V��������󂯎�郏�[�N�ւ̃|�C���^
 *
 * @retval  �����_���l
 */
//--------------------------------------------------------------
u16 contest_fix_rand(u32 seed, u32 *new_seed)
{
	u32 rand;
	
	rand = gf_fix_rand(seed);
	*new_seed = rand;
	return rand / 65536L;
}

//--------------------------------------------------------------
/**
 * @brief   CON_ETC_SIO_DATA�̃p�����[�^���Z�b�g����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�Ώۃu���[�_�[
 * @param   etc_data		�p�����[�^�����
 */
//--------------------------------------------------------------
static void SioEtcDataSet(CONTEST_SYSTEM *consys, int breeder_no, CON_ETC_SIO_DATA *etc_data)
{
	etc_data->player_sex = consys->c_game.player_sex[breeder_no];
	etc_data->character = consys->c_game.character[breeder_no];
	etc_data->popularity = consys->c_game.popularity[breeder_no];
	etc_data->obj_code = consys->c_game.obj_code[breeder_no];
}




//==============================================================================
//	�f�o�b�O�֐�
//==============================================================================
#ifdef PM_DEBUG			//==========================
//--------------------------------------------------------------
/**
 * @brief   �C���[�W�N���b�v�f�o�b�O�p�ɃA�N�Z�T���[��S�ăZ�b�g
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * Contest_ImageClipInitDataCreate�̊֐���ɌĂяo���Ă�������
 */
//--------------------------------------------------------------
static void ContestDebug_ImageClipDebugAccessorySet(CONTEST_SYSTEM *consys)
{
	IMC_CONTEST_PROC_WORK *icpw;
	IMC_ITEM_SAVEDATA *imcsave;
	
	GF_ASSERT(consys->icpw != NULL);
	icpw = consys->icpw;
	
	imcsave = ImcSaveData_ItemAllocWork(HEAPID_CONTEST);
	Debug_ImcSaveData_SetItemData(imcsave);

	icpw->cp_imc_item = imcsave;
}

//--------------------------------------------------------------
/**
 * @brief   �f�o�b�O�p�ɃZ�b�g�����A�N�Z�T���̈���J��
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * Contest_ImageClipInitDataFree�֐����ĂԂ�����ɂ���Ńf�o�b�O�̈�̉�������Ă�������
 */
//--------------------------------------------------------------
static void ContestDebug_ImageClipDebugAccessoryFree(CONTEST_SYSTEM *consys)
{
	IMC_CONTEST_PROC_WORK *icpw;
	IMC_ITEM_SAVEDATA *imcsave;
	icpw = consys->icpw;
	imcsave = (void*)icpw->cp_imc_item;
	sys_FreeMemoryEz(imcsave);
}
#endif		//========== PM_DEBUG ===========
