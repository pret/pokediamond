//============================================================================================
/**
 * @file	field_encount.c
 * @brief	�t�B�[���h�G���J�E���g�`�F�b�N���N��
 * @date	2005.07.28
 * @author	tamada		�����p�����l�������Ă�
 *
 * 2005.12.18	�G���J�E���g�`�F�b�N�������폜�Aencount_set.c�Ɉړ�����
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"

#include "field_encount.h"
#include "eventcmd.h"
#include "encount_effect.h"
#include "encount_set.h"
#include "field_battle.h"

#include "ev_mapchange.h"

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "sway_grass_enc.h"
#include "system/wipe.h"

#include "poketool/tr_tool.h"

#include "mapdata_warp.h"			//WARPDATA_GetRevivalLocation
#include "situation_local.h"		//Situation_Get�`
#include "system/brightness.h"
#include "script.h"
#include "scr_tool.h"
#include "mapdefine.h"
#include "..\fielddata\script\common_scr_def.h"		//SCRID_GAME_OVER_RECOVER_PC
#include "sysflag.h"
#include "communication/communication.h"   // �Ƃ������蒠�ւ̋L�^�̂���
//#include "comm_direct_counter.h"
#include "comm_field_state.h"
#include "b_tower_fld.h"
#include "fld_move_poke.h"
#include "pokepark_sys.h"

#include "battle/trno_def.h"

#include "savedata/tv_work.h"
#include "tv_topic.h"		//TVTOPIC_Entry_Watch_Capture
#include "field/tvtopic_extern.h"
#include "fld_enceff_data.h"
#include "field/b_tower_ev.h"

#include "savedata/record.h"
#include "poketool/poke_number.h"
#include "poketool/status_rcv.h"
#include "syswork.h"

#include "battle/attr_def.h"

//============================================================================================
//============================================================================================
static void AddScoreByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam );
static void WriteFNoteByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam );

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static inline int DmyEffNo(void)
{
	return gf_mtRand() % ENCOUNT_NUM;
}

//============================================================================================
//
//
//	�C�x���g�[���R�}���h�F�퓬
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_BattleProc(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	BATTLE_PARAM * battle_param = FieldEvent_GetSpecialWork(event);
	int *seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		//�퓬�v���Z�X�o�^
		FieldBattle_SetProc(fsys, battle_param);
		(*seq) ++;
		break;
	case 1:
		//�T�u�v���Z�X�i�퓬�j�I���҂�
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			break;
		}
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�퓬�Ăяo��
 * @param	event			�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	battle_param	�퓬�p�p�����[�^�ւ̃|�C���^
 * 
 * �����Ƃ��Ď󂯎����BATTLE_PARAM�͉�����܂���B
 * �Ăяo�����ŊǗ����Ă��������B
 */
//-----------------------------------------------------------------------------
void EventCmd_BattleProc(GMEVENT_CONTROL * event, BATTLE_PARAM * battle_param)
{
	FieldEvent_Call(event, GMEVENT_Sub_BattleProc, battle_param);
}


//============================================================================================
//
//
//	�C�x���g�R�}���h�F�|�P�����G���J�E���g�Ăяo��
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
typedef struct {
	int * winlose_flag;
	int effect_no;
	int bgm_no;
    int netTargetID;
	BATTLE_PARAM	*battle_param;
}EV_BATTLE_WORK;

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static EV_BATTLE_WORK * EBW_Create(BATTLE_PARAM * btlprm, int effect_no, int bgm_no,
		int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_BATTLE_WORK));
	ebw->winlose_flag = winlose_flag;
	if (winlose_flag != NULL) {
		*winlose_flag = 0;
	}
	ebw->effect_no = effect_no;
	ebw->bgm_no = bgm_no;
	ebw->battle_param = btlprm;
	return ebw;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static void EBW_Delete(EV_BATTLE_WORK * ebw)
{
	//�o�g���p�����[�^�j��
	BattleParam_Delete(ebw->battle_param);

	sys_FreeMemoryEz(ebw);
}
#if 0	//<<20060609 del
//-----------------------------------------------------------------------------
/**
 * @brief	FIGHT_TYPE�ƃg���[�i�[ID����BGM�����肷��
 */
//-----------------------------------------------------------------------------
static u16 GetBGMID(const BATTLE_PARAM * bp)
{
	return Snd_BattleBgmGet(bp->fight_type,bp->trainer_id[CLIENT_NO_ENEMY]); 
}
#endif
//-----------------------------------------------------------------------------
/**
 * @brief
 * @param	ebw			�퓬�V�[�P���X���[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static BOOL EBW_CheckResult(EV_BATTLE_WORK * ebw)
{
	BOOL win_flag;

	if (ebw->winlose_flag != NULL) {
		*(ebw->winlose_flag) = ebw->battle_param->win_lose_flag;
	}

	win_flag = BattleParam_IsWinResult(ebw->battle_param->win_lose_flag);
	return win_flag;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�o�g����̃p�����[�^���f
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	ebw			�퓬�V�[�P���X���[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void BattleParam_RefrectResult(const BATTLE_PARAM * btlprm, FIELDSYS_WORK * fsys)
{
	if (btlprm->fight_type & FIGHT_TYPE_DEBUG) {
		//�f�o�b�O�ΐ�ł͎莝���̏������������Ȃ�
		return;
	}
	BattleParam_UpdateGameData(btlprm, fsys);
#if 0
	if (BattleParam_IsWinResult(btlprm->win_lose_flag)) {
		//���������ꍇ
		BattleParam_UpdateGameData(btlprm, fsys);
	} else {
		//�s�k�����ꍇ
	}
#endif

}

//-----------------------------------------------------------------------------
/**
 * @brief	�ʏ�퓬�C�x���g�V�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 * �G���J�E���g�G�t�F�N�g���퓬���t�B�[���h���A���s���B
 * �Q�[���I�[�o�[�����ւ̕��������i�\��j
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NormalBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		//�n�a�i�|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//�퓬���ʔ��f�i������A�莝���|�P������ԁAetc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		if ( (ebw->battle_param->fight_type == FIGHT_TYPE_1vs1_YASEI)||
			 (ebw->battle_param->fight_type == FIGHT_TYPE_MOVE)||
			 (ebw->battle_param->fight_type == FIGHT_TYPE_2vs2_YASEI) ){			//�쐶��
			TVTOPIC_Entry_Watch_Capture(fsys,ebw->battle_param->TVWatchBattleWork,
					ebw->battle_param->win_lose_flag);
		}
		//�퓬�I����̏���
		if (EBW_CheckResult(ebw) == FALSE) {
			//�S�ł̏ꍇ�͂����ŏI��������
			EBW_Delete(ebw);
			return TRUE;
		}

		//�A������퓬��͎莝������
		if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){
			//�A������Ȃ̂Ŏ莝����
			PokeParty_RecoverAll(SaveData_GetTemotiPokemon(fsys->savedata));
		}

		//�X�R�A���Z
		AddScoreByBattle(fsys, ebw->battle_param);
		//�`���m�[�g�L��
		WriteFNoteByBattle(fsys, ebw->battle_param);
		
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//�n�a�i�|�[�Y�N���A
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void EventCmd_NormalBattle(GMEVENT_CONTROL * event,
		BATTLE_PARAM * btlprm, int effect_no, int bgm_no, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create(btlprm, effect_no, bgm_no, winlose_flag);
	FieldEvent_Call(event, GMEVENT_NormalBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�킢���ʂ�o�^
 * @param	status  win_lose_flag
 * @retval	�Ȃ�
 */
//-----------------------------------------------------------------------------

static void wifiFriendWriteBattleResult(int status,FIELDSYS_WORK* fsys)
{
    switch(status & 0x0f){
      case FIGHT_WIN:		///�퓬����
      case FIGHT_ENEMY_ESCAPE:		///���肪������
        CommInfoSetBattleResult(fsys->savedata,1);
        break;
      case FIGHT_LOSE:		///�퓬����
      case FIGHT_ESCAPE:		///������
        CommInfoSetBattleResult(fsys->savedata,-1);
        break;
    }
}

//-----------------------------------------------------------------------------
/**
 * @brief	�ʐM�퓬�C�x���g�V�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CommBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//�퓬�I����̏���
        // �Ƃ������蒠�ɏ��s����������
        wifiFriendWriteBattleResult(ebw->battle_param->win_lose_flag,fsys);

		//���z�ΐ�p�̃Q�[���f�[�^�A�b�v�f�[�g�����i������Ƃ��j
		BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);
        {
            RECORD* pRecord = SaveData_GetRecord(fsys->savedata);
            RECORD_Score_Add(pRecord, SCORE_ID_COMM_BATTLE_COUNT);
        }
#if 0
		if (EBW_CheckResult(ebw) == FALSE) {
			/* �������Ƃ��̏��� */
		}
#endif

		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//�C�x���g�R�}���h�F�t�F�[�h�C��
//		EventCmd_FieldFadeIn(event);
//		(*seq) ++;
//		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	WIFI�퓬�C�x���g�V�[�P���X    k.ohno�쐬
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_WiFiBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:

		Snd_DataSetByScene( SND_SCENE_BATTLE, ebw->bgm_no, 1 );	//�o�g���ȍĐ�
        
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;
	case 1:
        {
            // �Ƃ������蒠�ɏ��s����������
            wifiFriendWriteBattleResult(ebw->battle_param->win_lose_flag, fsys);

            //���z�ΐ�p�̃Q�[���f�[�^�A�b�v�f�[�g�����i������Ƃ��j
			BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);

        }
        {
            RECORD* pRecord = SaveData_GetRecord(fsys->savedata);
            RECORD_Score_Add(pRecord, SCORE_ID_COMM_BATTLE_COUNT);
        }
        
#if 0	//�ʐM�ΐ�Ȃ̂Ŕs�k���̕���͂���Ȃ��͂�	2006.04.24 tamada
		//�퓬�I����̏���
		if (EBW_CheckResult(ebw) == FALSE) {

			//�S�ł̏ꍇ�͂����ŏI��������
			EBW_Delete(ebw);
			return TRUE;
		}
		BattleParam_RefrectResult(ebw->battle_param, fsys);
#endif

		(*seq) ++;
		break;
	case 2:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�o�g���^���[���[�J���퓬�C�x���g�V�[�P���X by iwasawa
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 * �G���J�E���g�G�t�F�N�g���o�g���^���[�퓬���t�B�[���h���A���s���B
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_TowerLocalBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//���z�ΐ�p�̃Q�[���f�[�^�A�b�v�f�[�g�����i������Ƃ��j
		BattleParam_UpdateGameDataOfVirtualBattle(ebw->battle_param, fsys);
		//�^���[�p�ΐ팋�ʃA�b�v�f�[�g����
		BtlTower_BattleRecordUpdate(fsys,&(ebw->battle_param->btr));

		//�퓬�I����̏���
		if (EBW_CheckResult(ebw) == FALSE) {
			//�s�폈��
		}else{
			
//			UpdateBattleResult(event, ebw);		
		}

		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 4:
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 5:
		EBW_Delete(ebw);
		return TRUE;
	}
	return FALSE;
}

/**
 *	@brief	�o�g���^���[�@���[�J���o�g���C�x���g�o�^
 */
static void EventCmd_TowerLocalBattleCall(GMEVENT_CONTROL * event,
		BATTLE_PARAM * param, int effect_no, int bgm_no, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create(param, effect_no, bgm_no, winlose_flag);
	FieldEvent_Call(event, GMEVENT_TowerLocalBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�o�g���^���[���[�J���ΐ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	trainer_id	�g���[�i�[�w��f�[�^
 * @param	fight_type	�퓬���
 * @param	heapID		�q�[�vID
 * @param	winlose_flag	�퓬���ʂ��󂯎��t���O
 */
//-----------------------------------------------------------------------------
void EventCmd_TowerLocalBattle(GMEVENT_CONTROL * event,BTOWER_SCRWORK* wk, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *param;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//�o�g���f�[�^������
	param = BtlTower_CreateBattleParam(wk,fsys);
	
	//�Ăяo�����C�x���g�o�^
	EventCmd_TowerLocalBattleCall( event,param,
								   FLD_EncEffSpDataEffectNoPackGet( param ),
								   FLD_EncEffSpDataBgmNoPackGet( param ),
								   winlose_flag);
}





















//============================================================================================
//
//
//				�쐶�G���J�E���g
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	int effect_no;
	int bgm_no;
	int *winlose_flag;
	BATTLE_PARAM	*battle_param;
}EV_WILD_BATTLE_WORK;


static BOOL GMEVENT_NormalWildBattle(GMEVENT_CONTROL * event);
static BOOL GMEVENT_SafariBattle(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static EV_WILD_BATTLE_WORK* EWBW_Create( BATTLE_PARAM * btlprm, int effect_no, int bgm_no,
		int * winlose_flag )
{
	EV_WILD_BATTLE_WORK	* ewbw;
	ewbw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_WILD_BATTLE_WORK));
	ewbw->winlose_flag = winlose_flag;
	if (winlose_flag != NULL) {
		*winlose_flag = 0;
	}
	ewbw->effect_no = effect_no;
	ewbw->bgm_no = bgm_no;
	ewbw->battle_param = btlprm;
	ewbw->seq = 0;
	return ewbw;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static void EWBW_Delete(EV_WILD_BATTLE_WORK * ewbw)
{
	//�o�g���p�����[�^�j��
	BattleParam_Delete(ewbw->battle_param);

	sys_FreeMemoryEz(ewbw);
}

//-----------------------------------------------------------------------------
/**
 * �t�B�[���h�G���J�E���g�C�x���g�Z�b�g
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	ioBattleParam	�o�g���p�����[�^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FieldEncount_Set(FIELDSYS_WORK * fsys, BATTLE_PARAM *ioBattleParam)
{

	if ( SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		EV_BATTLE_WORK * ebw;
		ebw = EBW_Create(	ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Set(fsys, GMEVENT_SafariBattle,ebw);
	}else{
		EV_WILD_BATTLE_WORK *ewbw;
		
		ewbw = EWBW_Create( ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Set(fsys, GMEVENT_NormalWildBattle,ewbw);
	}
}

//-----------------------------------------------------------------------------
/**
 * �t�B�[���h�G���J�E���g�C�x���g�`�F���W
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	ioBattleParam	�o�g���p�����[�^
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FieldEncount_Change(FIELDSYS_WORK * fsys, GMEVENT_CONTROL * event, BATTLE_PARAM *ioBattleParam)
{

	if ( SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		EV_BATTLE_WORK * ebw;
		ebw = EBW_Create(	ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Change(event, GMEVENT_SafariBattle,ebw);
	}else{
		EV_WILD_BATTLE_WORK *ewbw;
		ewbw = EWBW_Create( ioBattleParam,
							FLD_EncEffSpDataEffectNoPackGet( ioBattleParam ),
							FLD_EncEffSpDataBgmNoPackGet( ioBattleParam ),
							NULL );
		FieldEvent_Change(event, GMEVENT_NormalWildBattle,ewbw);
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�ʏ�쐶��C�x���g�V�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 * �T�u�C�x���g�Ƃ��āA�ʏ�퓬�C�x���g�V�[�P���X���R�[������
 * 
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_NormalWildBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_WILD_BATTLE_WORK *ewbw;
	fsys = FieldEvent_GetFieldSysWork(event);
	ewbw = FieldEvent_GetSpecialWork(event);

	switch (ewbw->seq) {
	case 0:
		//�n�a�i�|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//�쐶���J�E���g�A�b�v
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event,ewbw->effect_no, ewbw->bgm_no);
		ewbw->seq++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		ewbw->seq++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ewbw->battle_param);
		ewbw->seq++;
		break;

	case 3:
		//�퓬���ʔ��f�i������A�莝���|�P������ԁAetc...)
		BattleParam_RefrectResult(ewbw->battle_param, fsys);
		TVTOPIC_Entry_Watch_Capture(fsys,ewbw->battle_param->TVWatchBattleWork,
				ewbw->battle_param->win_lose_flag);
		//�퓬�I����̏���
		if (BattleParam_IsWinResult(ewbw->battle_param->win_lose_flag) == FALSE) {
			//�S�ł̏ꍇ�͂����ŏI��������
			EWBW_Delete(ewbw);
			//�h�ꑐ���Z�b�g
			SwayGrass_InitSwayGrass(fsys->SwayGrass);
			FieldEvent_Change(event, GMEVENT_NormalGameOver, NULL);
			return FALSE;
		}

		//�A������퓬��͎莝������
		if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata))){
			//�A������Ȃ̂Ŏ莝����
			PokeParty_RecoverAll(SaveData_GetTemotiPokemon(fsys->savedata));
		}

		//�X�R�A���Z
		AddScoreByBattle(fsys, ewbw->battle_param);
		//�`���m�[�g�L��
		WriteFNoteByBattle(fsys, ewbw->battle_param);
		
		//�퓬�I����h�ꑐ�p���`�F�b�N
		if (SwayGrass_CheckValid( fsys->SwayGrass )){
			if (SwayGrass_IsSwayEncRetern(fsys->SwayGrass)){	//�h�ꑐ�G���J�E���g���A
				if ( ( !(ewbw->battle_param->win_lose_flag==FIGHT_WIN) ) &&
						( !(ewbw->battle_param->win_lose_flag==FIGHT_POKE_GET) ) ){		//������
					//�h�ꑐ���Z�b�g
					SwayGrass_InitSwayGrass(fsys->SwayGrass);
				}
			}else{//�ʏ�擪���A�������́A�h�ꑐ�ł��~�ߕ��A�̂Ƃ�
				//�h�ꑐ���Z�b�g
				SwayGrass_InitSwayGrass(fsys->SwayGrass);
			}
		}
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		ewbw->seq++;
		break;
	case 4:
		//�ړ��|�P��������
		FLD_MP_SetAfferBattle(fsys, ewbw->battle_param);
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		ewbw->seq++;
		break;
	case 5:
		if (SwayGrass_CheckValid( fsys->SwayGrass )){	//�h�ꑐ�G���J�E���g���A
			SwayGrass_SetChain(	fsys, ewbw->battle_param->win_lose_flag, fsys->SwayGrass);
			//���Z�b�g
			SwayGrass_SetSwayGrassAnime(fsys, fsys->SwayGrass);
		}
		ewbw->seq++;
		break;
	case 6:
		if (SwayGrass_CheckSwayGrassAnimeEnd(fsys->SwayGrass)){
			//�n�a�i�|�[�Y�N���A
			FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
			EWBW_Delete(ewbw);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

#include "../fielddata/script/safari_def.h"
//-----------------------------------------------------------------------------
/**
 * @brief	�T�t�@���C�x���g�V�[�P���X
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE		�C�x���g�I��
 * @retval	FALSE		�C�x���g�p����
 *
 * �T�u�C�x���g�Ƃ��āA�T�t�@���C�x���g�V�[�P���X���R�[������
 * 
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_SafariBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;
	u16 *safari_ball;

	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);
	safari_ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));

    switch (*seq) {
	case 0:
		//�n�a�i�|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//�쐶���J�E���g�A�b�v
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//�퓬���ʔ��f�i������A�莝���|�P������ԁAetc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		if (ebw->battle_param->win_lose_flag == FIGHT_POKE_GET) {
			TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
			POKEMON_PARAM * pp = PokeParty_GetMemberPointer(
					ebw->battle_param->poke_party[CLIENT_NO_ENEMY], 0);
			TVTOPIC_SafariTemp_Set(tvwk, pp);
		}

		//�A������͂Ȃ�
		
		//�X�R�A���Z
		AddScoreByBattle(fsys, ebw->battle_param);
		
		//�퓬�I����̏���
		if ((*safari_ball) == 0 && ebw->battle_param->win_lose_flag != FIGHT_POKE_GET){
			//�T�t�@���{�[�����Ȃ��Ȃ�����T�t�@���Q�[�g�֖߂�
			LOCATION_WORK *next;
			next = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
			EventCmd_MapChangeByLocation(event, next);
			//�T�t�@���{�[�������Ȃ���
///			OS_Printf("�T�t�@���{�[�����Ȃ��Ȃ�܂���\n");
		}
		//�`���m�[�g�L�q
		WriteFNoteByBattle( fsys, ebw->battle_param );

		(*seq) ++;
		break;

	case 4:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//�n�a�i�|�[�Y�N���A
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		if ((*safari_ball) == 0){
			if (ebw->battle_param->win_lose_flag == FIGHT_POKE_GET) {
				//�t�B�[���h�ŃA�i�E���X���Ă���Q�[�g�ֈړ��A�I��
				EventCall_Script(event, SCRID_SAFARI_ANNOUNCE_BALL, NULL, NULL);
			} else {
				//�퓬��ʓ��ŃA�i�E���X�ς݂Ȃ̂Œ��ڃQ�[�g�ֈړ��A�I��
				EventCall_Script(event, SCRID_SAFARI_END_GATE, NULL, NULL);
			}
		} else {
			BOX_DATA * box = SaveData_GetBoxData(fsys->savedata);
			POKEPARTY * party = SaveData_GetTemotiPokemon(fsys->savedata);
			if (BOXDAT_GetEmptyTrayNumber(box) == BOXDAT_TRAYNUM_ERROR
					&& PokeParty_GetPokeCount(party) == 6) {
				EventCall_Script(event, SCRID_SAFARI_ANNOUNCE_BOX_FULL, NULL, NULL);
			}
		}
		(*seq) ++;
		break;
	case 7:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//============================================================================================
//
//
//				���h��G���J�E���g
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F���h��G���J�E���g��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	winlose_flag	�퓬���ʂ��󂯎��t���O
 */
//-----------------------------------------------------------------------------
void EventCmd_HoneyTreeBattle(GMEVENT_CONTROL * event, int * winlose_flag)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//�h�ꑐ���Z�b�g
	SwayGrass_InitSwayGrass(fsys->SwayGrass);
	
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->bg_id = BG_ID_BASIC;		//��{�w�i�w��
	btlprm->ground_id = GROUND_ID_GRAVEL;	//��{�n�ʎw��
	//���h��G���J�E���g�f�[�^���Z�b�g
	SetHoneyTreeEncountData(fsys, btlprm);
	
	//�쐶���J�E���g�A�b�v
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);

	EventCmd_NormalBattle( event, btlprm,
						   FLD_EncEffSpDataEffectNoPackGet( btlprm ),
						   FLD_EncEffSpDataBgmNoPackGet( btlprm ),
						   winlose_flag);
}


//============================================================================================
//
//
//				�|�P�����i���o�[�ƃ��x�����w�肵�Ė쐶��(�X�N���v�g�Ŏg�p)
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�|�P�����i���o�[�ƃ��x�����w�肵�Ė쐶��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	monsno		�|�P�����i���o�[
 * @param	level		���x��
 * @param	winlose_flag	�퓬���ʂ��󂯎��t���O
 * @param	densetsu		�`���|�P�����G���J�E���g���ǂ����̃t���O
 *
 * ��densetsu�t���O��TRUE��n���ƃG���J�E���g���b�Z�[�W��
 * �u��������яo�����v�ł͂Ȃ��u���������ꂽ�v�ɂȂ�܂�
 */
//-----------------------------------------------------------------------------
void EventCmd_WildBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level, int * winlose_flag,BOOL densetsu)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//�h�ꑐ���Z�b�g
	SwayGrass_InitSwayGrass(fsys->SwayGrass);

	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);

	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	//�G���J�E���g�f�[�^���Z�b�g
	SetWildEncountData(fsys, monsno, level, btlprm);

	/*
	//�@battle_status_flag
	//	�ɃZ�b�g����悤�ɂ���I
	*/
	if(densetsu){
		//�`���|�P�����G���J�E�g�Ȃ�t���O�𗧂ĂăG���J�E���g���b�Z�[�W��ς���
		btlprm->battle_status_flag |= BATTLE_STATUS_FLAG_DENSETSU_BATTLE;
	}
	/*
		��������A�C�e���̎w�肪�K�v�����H
	*/

	//�쐶���J�E���g�A�b�v
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
	
	EventCmd_NormalBattle(event, btlprm, FLD_EncEffSpDataEffectNoPackGet( btlprm ), FLD_EncEffSpDataBgmNoPackGet( btlprm ), winlose_flag);
}

//============================================================================================
//============================================================================================
#include "../fielddata/script/d10r0101_def.h"		//SCRID_D10R0101_FINISH
//-----------------------------------------------------------------------------
/**
 * @brief		�C�x���g�F�|�P�p�[�N�퓬
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_PokeParkBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	EV_BATTLE_WORK * ebw;
	int * seq;

	fsys = FieldEvent_GetFieldSysWork(event);
	ebw = FieldEvent_GetSpecialWork(event);
	seq = FieldEvent_GetSeqWork(event);

    switch (*seq) {
	case 0:
		//�n�a�i�|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		//�쐶���J�E���g�A�b�v
		RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//�퓬���ʔ��f�i������A�莝���|�P������ԁAetc...)
		BattleParam_RefrectResult(ebw->battle_param, fsys);
		//�|�P�p�[�N�p�̐퓬���ʔ��f
		PokeParkSys_ReflectBattleResult(fsys, ebw->battle_param);
		
		//�A������͂Ȃ�
		
		//�X�R�A���Z
		AddScoreByBattle(fsys, ebw->battle_param);
		//�퓬�I����̏���
		(*seq) ++;
		break;

	case 4:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//�n�a�i�|�[�Y�N���A
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		EBW_Delete(ebw);
		if (PokeParkSys_GetBallCount(fsys) == 0) {
			EventChange_Script(event, SCRID_D10R0101_FINISH, NULL);
			return FALSE;
		} else {
			return TRUE;
		}
		break;
	}
	return FALSE;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void EventSet_PokeParkBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM * btlprm)
{
	EV_BATTLE_WORK * ebw;
	ebw = EBW_Create( btlprm,
				      FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet(btlprm),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_PokeParkBattle, ebw);
}


//============================================================================================
//
//
//						�ŏ��̃C�x���g��(�X�N���v�g�Ŏg�p)
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�ŏ��̃C�x���g��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	monsno		�|�P�����i���o�[
 * @param	level		���x��
 */
//-----------------------------------------------------------------------------
void EventCmd_FirstBattle(GMEVENT_CONTROL * event, u16 monsno, u8 level)
{
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_YASEI);

	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	//�G���J�E���g�f�[�^���Z�b�g
	SetWildEncountData(fsys, monsno, level, btlprm);

	//�퓬������p�t���O
	btlprm->battle_status_flag = BATTLE_STATUS_FLAG_FIRST_BATTLE;

	/*
		��������A�C�e���̎w�肪�K�v�����H
	*/

	//�쐶���J�E���g�A�b�v
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_ENCOUNT);

	EventCmd_NormalBattle( event, btlprm,
						   FLD_EncEffSpDataEffectNoPackGet( btlprm ),
						   FLD_EncEffSpDataBgmNoPackGet( btlprm ),
						   NULL);
}

//============================================================================================
//
//
//			�ߊl�f��
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�ߊl�f��
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CaptureDemo(GMEVENT_CONTROL * event)
{
	EV_BATTLE_WORK * ebw = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		//�n�a�i�|�[�Y
		FieldOBJSys_MovePauseAll( fsys->fldobjsys );
		// �C�x���g�R�}���h�F�G���J�E���g�G�t�F�N�g�Ăяo��
		EventCmd_EncountEffect(event, ebw->effect_no, ebw->bgm_no);
		(*seq) ++;
		break;
	case 1:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 2:
		//�C�x���g�R�}���h�F�퓬�v���Z�X
		EventCmd_BattleProc(event, ebw->battle_param);
		(*seq) ++;
		break;

	case 3:
		//�퓬���ʔ��f�i������A�莝���|�P������ԁAetc...)
		//�Ȃɂ����f���Ȃ��B
		(*seq) ++;
		break;

	case 4:
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X���A
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 5:
		//�n�a�i�|�[�Y�N���A
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		//�C�x���g�R�}���h�F�t�F�[�h�C��
		EventCmd_FieldFadeIn(event);
		(*seq) ++;
		break;
	case 6:
		EBW_Delete(ebw);
		return TRUE;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�T�u�C�x���g�Ăяo���F�ߊl�f��
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 */
//-----------------------------------------------------------------------------
void EventCmd_CaptureDemo(GMEVENT_CONTROL * event)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM * btlprm;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);

	btlprm = BattleParam_CreateForGetDemo(HEAPID_WORLD, fsys);
	ebw = EBW_Create( btlprm,
				      FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet(btlprm),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CaptureDemo, ebw);
}

//============================================================================================
//
//
//				�g���[�i�[�ΐ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�g���[�i�[�ΐ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	trainer_id	�g���[�i�[�w��f�[�^
 * @param	fight_type	�퓬���
 * @param	heapID		�q�[�vID
 * @param	winlose_flag	�퓬���ʂ��󂯎��t���O
 */
//-----------------------------------------------------------------------------
void EventCmd_TrainerBattle(GMEVENT_CONTROL * event, int tr_id_0, int tr_id_1, int partner_id,
		 int heapID, int * winlose_flag)
{
	u32 fight_type;
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	FIELDSYS_WORK * fsys;

	fsys = FieldEvent_GetFieldSysWork(event);

	if( (tr_id_1 != 0) && (tr_id_0 != tr_id_1) ){
		if (partner_id == 0) {
			fight_type = FIGHT_TYPE_TAG_BATTLE;
		} else {
		//�A��������Ȃ�A�K��AI�}���`
			fight_type = FIGHT_TYPE_AI_MULTI;
		}

	//�_�u��
	}else if( tr_id_0 == tr_id_1 ){
		fight_type = FIGHT_TYPE_2vs2_TRAINER;

	}else{
		fight_type = FIGHT_TYPE_TRAINER;
	}
	//�h�ꑐ���Z�b�g
	SwayGrass_InitSwayGrass(fsys->SwayGrass);

	/* �g���[�i�[��Ȃ̂Ŗ쐶��̃p�����[�^�ŐF�X�㏑�� */

	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_WORLD, fight_type);

	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->trainer_id[CLIENT_NO_ENEMY] = tr_id_0;
	btlprm->trainer_id[CLIENT_NO_ENEMY2] = tr_id_1;
	btlprm->trainer_id[CLIENT_NO_MINE2] = partner_id;

	//�g���[�i�[�f�[�^����
	TT_EncountTrainerDataMake( btlprm, fsys->savedata, heapID );

	//�g���[�i�[��J�E���g�A�b�v
	RECORD_Inc(SaveData_GetRecord(fsys->savedata), RECID_BTL_TRAINER);

	EventCmd_NormalBattle(event, btlprm, FLD_EncEffSpDataEffectNoPackGet( btlprm ), FLD_EncEffSpDataBgmNoPackGet( btlprm ), winlose_flag);
}

//============================================================================================
//
//
//				�ʐM�ΐ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�ʐM�ΐ�C�x���g�Z�b�g
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_CommBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����

    btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_SIO);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�키�莝���̔z����������ΐ�C�x���g�Z�b�g
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_TemotiListBattle(GMEVENT_CONTROL * event,const u8* temotiList, int fightType)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetTemotiListParamGameData(btlprm, fsys, temotiList);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	WIFI�ʐM�ΐ�C�x���g�Z�b�g
 * @param	event
 */
//-----------------------------------------------------------------------------
void EventCmd_WifiBattle(GMEVENT_CONTROL * event,int targetID, int lvLimit,BOOL bSingle)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
    if(bSingle){
        btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_1vs1_SIO);
    }
    else{
        btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_2vs2_SIO);
    }
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByWiFiGameData(btlprm, fsys, lvLimit);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
    ebw->netTargetID = targetID;
	FieldEvent_Call(event, GMEVENT_WiFiBattle, ebw);
}


//-----------------------------------------------------------------------------
/**
 * @brief	�ʐM�ΐ핔���ł̑ΐ�C�x���g
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_CommDirectBattle(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EV_BATTLE_WORK * ebw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		FieldEvent_Call(event, GMEVENT_CommBattle, ebw);
		(*seq) ++;
		break;
	case 1:
		CommFieldStateEnterBattleRoom( fsys );
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	�ʐM�ΐ핔���ł̑ΐ�C�x���g�N��
 * @param	fsys
 * @param	temotilist
 * @param	fightType
 */
//-----------------------------------------------------------------------------
void EventSet_CommDirectBattle(FIELDSYS_WORK * fsys, const u8 * temotiList, int fightType)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetTemotiListParamGameData(btlprm, fsys, temotiList);

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_CommDirectBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�ʐM�ΐ핔���ł̑ΐ�C�x���g�N���i�C�ӂ�POKEPARTY���Z�b�g�ł���j
 *
 * @param	fsys
 * @param	temotilist
 * @param	fightType
 */
//-----------------------------------------------------------------------------
void EventSet_CommDirectMixBattle(FIELDSYS_WORK * fsys, const POKEPARTY* party, int fightType)
{
	EV_BATTLE_WORK * ebw;
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����

    btlprm = BattleParam_Create(HEAPID_WORLD, fightType);

	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetCommBattle( btlprm, fsys, party, NULL );

	ebw = EBW_Create( btlprm,
					  FLD_EncEffSpDataEffectNoPackGet( btlprm ),
					  FLD_EncEffSpDataBgmNoPackGet( btlprm ),
					  NULL);
	FieldEvent_Set(fsys, GMEVENT_CommDirectBattle, ebw);
}

//-----------------------------------------------------------------------------
/**
 * �퓬�X�R�A���Z(�^���[�E�ʐM���Ή�)
 * 
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inBattleParam	�o�g���p����
 * 
 * @return	none
 * 
 */
//-----------------------------------------------------------------------------
static void AddScoreByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam )
{
	POKEMON_PARAM * pp;
	u32 fight_type = inBattleParam->fight_type;
	int win_lose_flg = inBattleParam->win_lose_flag;
	
	if (fight_type&FIGHT_TYPE_SIO){
		return;
	}

	if (fight_type&FIGHT_TYPE_TOWER){
		return;
	}

	if ( (fight_type == FIGHT_TYPE_1vs1_YASEI)||
		 (fight_type == FIGHT_TYPE_MOVE)||
		 (fight_type == FIGHT_TYPE_2vs2_YASEI) ){			//�쐶��
		if (win_lose_flg == FIGHT_WIN){	//�������Ƃ�
			//�X�R�A���Z�F�쐶�폟��
			RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_WILD_BATTLE_WIN );
		}else if(win_lose_flg == FIGHT_POKE_GET){		//�߂܂����Ƃ�
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
			
			//�V���I�E�}�Ӄ|�P�������H
			if ( PMNumber_GetPokeNumber( PM_NUMBER_SHINOU, PokeParaGet(pp,ID_PARA_monsno,0) ) ){
				//�X�R�A���Z�F�V���I�E�}�Ӄ|�P�����Q�b�g
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_SINOU );
			}else{
				//�X�R�A���Z�F�V���I�E�}�ӊO�|�P�����Q�b�g
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_WORLD );
			}
		}
	}else if ( (fight_type&FIGHT_TYPE_TRAINER)||
			   (fight_type&FIGHT_TYPE_TAG) ){			//�g���[�i�[��
		//����������Z
		if (win_lose_flg == FIGHT_WIN){
			//�X�R�A���Z�F�g���[�i�[�폟��
			RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_TRAINER_BATTLE_WIN );
		}
	}else if ( (fight_type&FIGHT_TYPE_SAFARI)||
			   (fight_type&FIGHT_TYPE_POKE_PARK) ){	//�T�t�@���E�|�P�p�[�N
		//�߂܂�������Z
		if (win_lose_flg == FIGHT_POKE_GET){
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
			//�V���I�E�}�Ӄ|�P�������H
			if ( PMNumber_GetPokeNumber( PM_NUMBER_SHINOU, PokeParaGet(pp,ID_PARA_monsno,0) ) ){
				//�X�R�A���Z�F�V���I�E�}�Ӄ|�P�����Q�b�g
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_SINOU );
			}else{
				//�X�R�A���Z�F�V���I�E�}�ӊO�|�P�����Q�b�g
				RECORD_Score_Add( SaveData_GetRecord(fsys->savedata), SCORE_ID_POKE_GET_WORLD );
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * �퓬��`���m�[�g�L��(�^���[�E�ʐM�E�|�P�p�[�N���Ή�)
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inBattleParam	�o�g���p����
 * 
 * @return	none
 * 
 */
//-----------------------------------------------------------------------------
static void WriteFNoteByBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam )
{
	POKEMON_PARAM * pp;
	u32 fight_type = inBattleParam->fight_type;
	int win_lose_flg = inBattleParam->win_lose_flag;
	
	if (fight_type&FIGHT_TYPE_SIO){
		return;
	}

	if (fight_type&FIGHT_TYPE_TOWER){
		return;
	}

	if ( fight_type&FIGHT_TYPE_POKE_PARK ){
		return;
	}

	if ( (fight_type == FIGHT_TYPE_1vs1_YASEI)||
		 (fight_type == FIGHT_TYPE_MOVE)||
		 (fight_type == FIGHT_TYPE_2vs2_YASEI)||
		 (fight_type == FIGHT_TYPE_SAFARI)){			//�쐶��
		FNOTE_WK_POKE *wk;
		if (win_lose_flg == FIGHT_WIN){	//�������Ƃ�
			//�J�E���g�A�b�v
			fsys->encount.WinPokeCount++;//�l�̐U��؂�͉������ĂȂ��ł�
			//5�C�ȏ�Ńm�[�g�L��
			if (fsys->encount.WinPokeCount >= 5){
				pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[CLIENT_NO_ENEMY], 0);
				wk = FNOTE_PokemonDownDataMake(
						SaveData_GetPlayTime(fsys->savedata),
						PokeParaGet(pp,ID_PARA_monsno,0),
						PokeParaGet(pp,ID_PARA_sex,0),
						inBattleParam->time_zone, HEAPID_WORLD );
/*
				wk = FNOTE_PokemonDownDataMake( PokeParaGet(pp,ID_PARA_monsno,0),
									    		PokeParaGet(pp,ID_PARA_sex,0),
											    inBattleParam->time_zone, HEAPID_WORLD );
*/
				FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_POKEMON );
			}
		}else if(win_lose_flg == FIGHT_POKE_GET){		//�߂܂����Ƃ�
			int client;
			//�߂܂����|�P�����̈ʒu���擾
			client = inBattleParam->get_pokemon_client;
			pp = PokeParty_GetMemberPointer(
					inBattleParam->poke_party[client], 0);
			//�m�[�g�L��
			wk = FNOTE_PokemonGetDataMake(
					SaveData_GetPlayTime(fsys->savedata),
					PokeParaGet(pp,ID_PARA_monsno,0),
					PokeParaGet(pp,ID_PARA_sex,0),
					inBattleParam->time_zone, HEAPID_WORLD );
//
/*
			wk = FNOTE_PokemonGetDataMake( PokeParaGet(pp,ID_PARA_monsno,0),
				    					   PokeParaGet(pp,ID_PARA_sex,0),
										   inBattleParam->time_zone, HEAPID_WORLD );
*/
			FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_POKEMON );
		}
	}else if ( (fight_type&FIGHT_TYPE_TRAINER)||
			   (fight_type&FIGHT_TYPE_TAG) ){			//�g���[�i�[��
		if (win_lose_flg == FIGHT_WIN){
			//�m�[�g�L��
			FNOTE_DataMakeSaveTrainer(
				fsys->fnote,
				fsys->location->zone_id,
				inBattleParam->trainer_id[CLIENT_NO_ENEMY],
				HEAPID_WORLD );
/*
			FNOTE_WK_TRAINER *wk;
			wk = FNOTE_TrainerDataMake( fsys->location->zone_id,
										inBattleParam->trainer_id[CLIENT_NO_ENEMY],
										HEAPID_WORLD );
			FNOTE_DataSave( fsys->fnote, wk, FNOTE_TYPE_TRAINER );
*/
		}
	}

}

#ifdef PM_DEBUG

//============================================================================================
//
//
//			�f�o�b�O�p
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O�p
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldEncount(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_EVENT, FIGHT_TYPE_DEBUG|FIGHT_TYPE_1vs1);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);
	
	//�����ɒn��G���J�E���g�f�[�^���Z�b�g
	DebugSetEncountData( NULL, GROUND_ENCOUNT, btlprm );
	
	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}
//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O�p
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldEncount2vs2(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_EVENT, FIGHT_TYPE_2vs2_TRAINER|FIGHT_TYPE_DEBUG);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);

	btlprm->trainer_id[CLIENT_NO_ENEMY]=gf_rand()%16+1;
	//�g���[�i�[�f�[�^����
	TT_EncountTrainerDataMake(btlprm,fsys->savedata,HEAPID_WORLD);

	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}
//-----------------------------------------------------------------------------
/**
 *	�f�o�b�O�p
 */
//-----------------------------------------------------------------------------
BOOL DebugFieldTrainerEncount(FIELDSYS_WORK * fsys)
{
	BATTLE_PARAM *btlprm;
	//�o�g���p�����[�^�̃A���P�[�V�����ƃ|�P�����p�[�e�B�̏�����
	btlprm = BattleParam_Create(HEAPID_WORLD, FIGHT_TYPE_TRAINER|FIGHT_TYPE_DEBUG);
	//�莝���|�P�����ȂǃZ�b�g
	BattleParam_SetParamByGameData(btlprm, fsys);
	
	btlprm->trainer_id[CLIENT_NO_ENEMY]=gf_rand()%247+1;
	//�g���[�i�[�f�[�^����
	TT_EncountTrainerDataMake(btlprm,fsys->savedata,HEAPID_WORLD);
	
	FieldEncount_Set(fsys, btlprm);

	return TRUE;
}

#endif	//PM_DEBUG

