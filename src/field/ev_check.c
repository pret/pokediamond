//============================================================================================
/**
 * @file	ev_check.c	
 * @brief	�C�x���g�����`�F�b�N�V�X�e��
 * @author	Sousuke Tamada
 * @date	01.03.29
 *
 * 05.07.04 Hiroyuki Nakamura
 */
//============================================================================================
#include "common.h"

#include "system/snd_tool.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/clact_tool.h"
#include "fieldsys.h"
#include "field_clact.h"
#include "fld_menu.h"
#include "sxy.h"
#include "script.h"

#define EV_CHECK_H_GLOBAL
#include "ev_check.h"
#include "eventdata.h"		//�]�[�����̃C�x���g�f�[�^�Q�Ƃ̂���

#include "fld_debug.h"

#include "field_event.h"
#include "field_encount.h"
#include "player_event_arrowmat.h"

#include "ev_mapchange.h"

#include "script.h"
#include "zonedata.h"
#include "mapdefine.h"
#include "poketool/pokeparty.h"

#include "fieldobj.h"

#include "ev_trainer.h"
#include "communication/wh_config.h"
#include "communication/wh.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_field.h"
#include "comm_direct_counter.h"
#include "comm_field_state.h"
#include "comm_vsroom.h"
#include "comm_player.h"
#include "underground/ug_manager.h"
#include "honey_tree_enc.h"

#include "map_attr.h"
#include "ev_pokemon.h"		//EvPoke_Enable2vs2Battle

#include "field\eventflag.h"

#include "..\fielddata\script\common_scr_def.h"
#include "..\fielddata\script\hiden_def.h"
#include "..\fielddata\script\bg_attr_def.h"
#include "..\fielddata\script\r201_def.h"
#include "..\fielddata\script\safari_def.h"
#include "..\fielddata\script\battle_room_def.h"
#include "..\fielddata\script\tv_def.h"
#include "../fielddata/script/union_def.h"

#define	SCRID_COMMON_MSG	0

#include "field_3d_anime_ev.h"

#include "map_jump_def.h"
#include "map_jump.h"

#include "situation_local.h"

#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/sodateyadata.h"
#include "savedata/record.h"
#include "sodateya.h"

#include "syswork.h"
#include "sysflag.h"

#include "gym.h"
#include "poison_effect.h"
#include "fieldmap_work.h"

#include "battle\wazano_def.h"
#include "comm_union_beacon.h"

#include "btl_searcher.h"

#include "system/debug_flag.h"

#include "sway_grass_enc.h"

#include "spray.h"
#include "pokepark_sys.h"
#include "field_poketch.h"


//#define	DEBUG_ALL_EXIT_CONNECT
//============================================================================================
//	�萔��`
//============================================================================================
#define	ALL_KEY		( PAD_KEY_UP | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT )

#define	PAD_BUTTON_MENU		( PAD_BUTTON_X )		// ���j���[�{�^��
#define	PAD_BUTTON_BENRI	( PAD_BUTTON_Y )		// �֗��{�^��


///�Ń_���[�W���󂯂����
#define	POISON_STEP_MAX		(4)

///�Ȃ��x�v�Z�������
#define FRIENDCALC_STEP_MAX	(128)

//============================================================================================
//
//
//
//============================================================================================
static BOOL EvCheck_ExitByPush(FIELDSYS_WORK * fsys, const EV_REQUEST * req);
static  u16 EvCheck_TalkMapAttr(FIELDSYS_WORK * repw, MATR matr);

static BOOL CheckEncountEvent(FIELDSYS_WORK * fsys);
static BOOL CheckMoveEvent(FIELDSYS_WORK * fsys);// ������Ƃ̃C�x���g�N���`�F�b�N
static BOOL CheckPosEvent(FIELDSYS_WORK * fsys);
static BOOL CheckExit(FIELDSYS_WORK * fsys, const int x, const int z, const u8 inAttr);
static BOOL CheckSodateya( FIELDSYS_WORK *fsys );
static BOOL CheckPoison(FIELDSYS_WORK * fsys);
static BOOL CheckSafariStep(FIELDSYS_WORK * fsys);
static BOOL CheckBtlSearcher(FIELDSYS_WORK * fsys);
static BOOL CheckPokeSearcher(FIELDSYS_WORK * fsys);
static BOOL CheckBoardStart( FIELDSYS_WORK * repw );
static BOOL CheckSpray( FIELDSYS_WORK *fsys );

static BOOL CheckFriendCalcStepCount( FIELDSYS_WORK *fsys );
static void DoFriendCalcStepCount( FIELDSYS_WORK *fsys );

//�c�[���֐�
static void GetNowPos(const FIELDSYS_WORK * fsys, int *x, int *z);
static void GetFrontPos(const FIELDSYS_WORK * fsys, int * x, int * z);
static void GetMovePos(const FIELDSYS_WORK * fsys, int dir, int * x, int * z);
static u8 GetNowAttr(const FIELDSYS_WORK * fsys);
static u8 GetFrontAttr(const FIELDSYS_WORK * fsys);

static BOOL GetConnectData(const FIELDSYS_WORK * fsys, int x, int z, LOCATION_WORK * next);

static void SetEscapeData(FIELDSYS_WORK * fsys);

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �C�x���g�`�F�b�N���N�G�X�g�̏�����
 *
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g�\����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ClearRequest( EV_REQUEST * req )
{
	req->TalkCheck  = FALSE;
	req->StepCheck  = FALSE;
	req->MenuOpen   = FALSE;
	req->CnvButton  = FALSE;
	req->MatCheck   = FALSE;
	req->PushCheck  = FALSE;
	req->MoveCheck  = FALSE;
	req->FloatCheck = FALSE;

	req->DebugMenu   = FALSE;
	req->DebugBattle = FALSE;

	req->DebugHook = FALSE;
	req->DebugKeyPush = FALSE;
	
	req->Site = DIR_NOT;
	req->PushSite = DIR_NOT;
}

//--------------------------------------------------------------------------------------------
/**
 * �C�x���g�`�F�b�N���N�G�X�g�̃Z�b�g
 *
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g�\����
 * @param	trg		�L�[�g���K�[���
 * @param	cont	�L�[�������
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SetRequest( EV_REQUEST * req, FIELDSYS_WORK * repw, u16 trg, u16 cont )
{

	int	st;
	int	val;
	int dir;

	ClearRequest(req);

	st  = Player_MoveStateGet( repw->player );		// ���@�̏��
	val = Player_MoveValueGet( repw->player );		// ���@�̈ړ����
	dir = Player_DirGet( repw->player );			// ���@�̕���
	req->trg = trg;
	req->cont = cont;



	if( st == OBJ_MOVE_STATE_END || st == OBJ_MOVE_STATE_OFF ){
//		if( GetHeroMoveSpeed() != HERO_MOVE_SPEED_MAX ){
			if( trg & PAD_BUTTON_MENU ){
				req->MenuOpen = TRUE;
			}
			if( trg & PAD_BUTTON_BENRI ){
				req->CnvButton = TRUE;
			}
			if( trg & PAD_BUTTON_DECIDE ){
				req->TalkCheck = TRUE;
			}
			if( trg & PAD_BUTTON_CANCEL ){
				req->FloatCheck = TRUE;
			}
//		}
		if( cont & ALL_KEY ){
			req->MatCheck = TRUE;
		}
		if( cont & ALL_KEY ){
			req->PushCheck = TRUE;
		}
	}

	if( st == OBJ_MOVE_STATE_END && val == OBJ_MOVE_VALUE_WALK ){
		req->MoveCheck = TRUE;
	}

	// ����ړ��I���^�C�~���O���H
	if (st == OBJ_MOVE_STATE_END) {
		req->StepCheck = TRUE;
	}

	if ((dir == DIR_UP && (cont & PAD_KEY_UP))
			|| ((dir == DIR_DOWN) && (cont & PAD_KEY_DOWN))
			|| ((dir == DIR_LEFT) && (cont & PAD_KEY_LEFT))
			|| ((dir == DIR_RIGHT) && (cont & PAD_KEY_RIGHT))
	   ) {
		req->PushSite = dir;
	} else {
		req->PushSite = DIR_NOT;
	}
	
//�㉺�D��̂Ƃ�����玩�@�Ǝ��̃L�[���͊֐��ɕύX 060317 kaga
#if 0
	// �ړ������̃��N�G�X�g
	if( cont & PAD_KEY_UP ){
		req->Site = DIR_UP;
	}else if( cont & PAD_KEY_DOWN ){
		req->Site = DIR_DOWN;
	}else if( cont & PAD_KEY_LEFT ){
		req->Site = DIR_LEFT;
	}else if( cont & PAD_KEY_RIGHT ){
		req->Site = DIR_RIGHT;
	}
#else
	req->Site = Player_KeyDirGet( repw->player, trg, cont );
#endif
	
	// �ȉ��̓f�o�b�O�@�\�̔����`�F�b�N
#ifdef	PM_DEBUG
	if( cont & PAD_BUTTON_R ){
		req->DebugKeyPush = TRUE;
		
		//R�{�^���������Ă���Ƃ��͊e��C�x���g�̔�����}����
		req->MoveCheck = FALSE;
		req->StepCheck = FALSE;
		req->MatCheck = FALSE;
		req->PushCheck = FALSE;

		if( req->MenuOpen ){
			req->MenuOpen = FALSE;
			req->DebugMenu = TRUE;
		}
	}

/*
	if( st == OBJ_MOVE_STATE_END || st == OBJ_MOVE_STATE_OFF ){
		if( cont & PAD_BUTTON_R ){
			// �f�o�b�O�o�g��
			if( (cont & PAD_BUTTON_START) && !(req->DebugMenu) ){ 
				req->DebugBattle = TRUE;
			}
		}
	}
*/
#endif	// PM_DEBUG

}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @breif	���ނ�ɓ���Ȃ��C�x���g�`�F�b�N
 * @param	req		���N�G�X�g�\���̂ւ̃|�C���^
 * @param	fsys	�Q�[�����䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�C�x���g��������
 * @retval	FALSE	�C�x���g�������Ȃ�����
 *
 *
 * R201�ł̃C�x���g��p�B���ɂ�����Ȃ��L�q�̊֐��Ȃ̂�
 * ���Ƃł��������܂Ƃ��ȏ����������l����
 */
//--------------------------------------------------------------------------------------------
static BOOL GrassStepInCheck(const EV_REQUEST * req, FIELDSYS_WORK * fsys)
{
	int st  = Player_MoveStateGet( fsys->player );		// ���@�̏��
	if (fsys->location->zone_id != ZONE_ID_R201) {
		return FALSE;
	}
	if (SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata)) == FALSE) {
		return FALSE;
	}
	if (st == OBJ_MOVE_STATE_OFF) {
#if 0	//���@�̏�Ԃ���L�[���͂�����l�ɂ��� 060317 kaga
		if (req->PushSite != DIR_NOT && MATR_IsGrass(GetFrontAttr(fsys))) {
			return TRUE;
		}
#elif 1
		{
			int val = Player_MoveValueGet( fsys->player );	//���@�����Ԃ��擾
			
			if( (s8)req->Site != DIR_NOT &&					//�L�[��������Ă���
				val == OBJ_MOVE_VALUE_WALK ){				//���@�̏�Ԃ͈ړ��ł���
				int x,z;
				GetMovePos( fsys, req->Site, &x, &z );		//�ړ���̃A�g���r���[�g�擾
				if (MATR_IsGrass(GetAttributeLSB(fsys, x, z))) {
					return TRUE;
				}
			}else{
				if( (s8)req->PushSite != DIR_NOT &&			//���@�̌����ɃL�[��������Ă���
					MATR_IsGrass(GetFrontAttr(fsys))) {		//�����̐�̃A�g���r���[�g���擾
					return TRUE;
				}
			}
		}
#endif
	} else if (st == OBJ_MOVE_STATE_END) {
		int x, z;
		GetMovePos(fsys, req->Site, &x, &z);
		if (MATR_IsGrass(GetAttributeLSB(fsys, x, z))) {
			return TRUE;
		}
	}
	
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �C�x���g�N���`�F�b�N
 *
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g
 *
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 *
 *	���N�G�X�g�����Ƀ`�F�b�N�v���O�������Ăяo���A�C�x���g���N������
 */
//--------------------------------------------------------------------------------------------
int CheckRequest(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{

	//����X�N���v�g�i�V�[���N���X�N���v�g�j�`�F�b�N
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}
	
	//�g���[�i�[�����`�F�b�N
	{
		if( req->DebugKeyPush == FALSE ){
			BOOL flag = EvPoke_Enable2vs2Battle(SaveData_GetTemotiPokemon(repw->savedata));
			
			if( SysFlag_PairCheck(SaveData_GetEventWork(repw->savedata)) == 1 ){
				flag = TRUE;		//�A��������Ȃ�_�u���\
			}
			
			if( EvTrainerEyeCheck(repw,flag) == TRUE ){
				Player_MoveStateClear( repw->player );
				FieldOBJSys_MovePauseAll( repw->fldobjsys );
				return TRUE;
			}
		}
	}
	
	//����ړ��`�F�b�N
	if (req->MoveCheck) {
		//������������ǂ����t���O�̍X�V
		SysFlag_OneStepReset( SaveData_GetEventWork(repw->savedata) );
		//IncRecord( CNT_WALK );
		if( CheckMoveEvent( repw ) == TRUE ){
			return TRUE;
		}
	}
	//���ނ�ɓ���Ȃ��C�x���g�`�F�b�N
	if (GrassStepInCheck(req, repw)) {
		EventSet_Script( repw, SCRID_POS_R201_STOP, NULL );
		return TRUE;
	}

	//���@�C�x���g�`�F�b�N
	{
		HERO_EVBIT evbit = HERO_EVBIT_NON;
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
		
		if (SysFlag_KairikiCheck( SaveData_GetEventWork(repw->savedata) )) {
			evbit |= HERO_EVBIT_PERMIT_KAIRIKI;
		}
		
		if( EvPoke_CheckWaza(SaveData_GetTemotiPokemon(repw->savedata),
					WAZANO_TAKINOBORI) != 0xff) {
			evbit |= HERO_EVBIT_PREMIT_TAKINOBORI;
		}
		
		if( Player_EventMoveCheck(repw,repw->player,dir,evbit) == TRUE ){
			return( TRUE );
		}
	}
	
	//���@����`�F�b�N�i����ړ� ���邢�� �U������j
	if(req->StepCheck ){
		// �G���J�E���g
		if (CheckEncountEvent(repw)) {
			return TRUE;
		}


		// �Ŕ`�F�b�N
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	//�����]���ł��܂����삵�Ȃ��̂ŁA�����ł��Ŕ`�F�b�N ( FR/LG �̃}�l )
	if( req->MatCheck && Player_DirGet(repw->player) == req->Site ){
		// �Ŕ`�F�b�N
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	// ��b
	if( req->TalkCheck ){

		{	// OBJ�Ƃ̉�b�`�F�b�N
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;

				if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
					Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
				}
				if (FieldOBJ_EventTypeGet(obj) != EV_TYPE_MSG) {
					EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
				} else {
					EventSet_Script( repw, SCRID_COMMON_MSG, obj );
				}
				return TRUE;
			}
		}

		{	// BG�̘b�������`�F�b�N
			int	id;
			
			id = TalkBgEventCheck(
					repw,
					(void *)EventData_GetNowBgTalkData( repw ),
					EventData_GetNowBgTalkDataSize( repw ) );

			if( id != EVENT_ID_NONE ){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}

		{	// ���h��؃`�F�b�N
			int id;
			if (HTE_CheckHoneyTree(repw,&id)){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}

		{
			int id;
			id = EvCheck_TalkMapAttr(repw, GetFrontAttr(repw));
			if (id != EVENT_ID_NONE) {
				EventSet_Script(repw, id, NULL);
				return TRUE;
			}

		}
	}

	if (req->PushCheck) {
		if (EvCheck_ExitByPush(repw, req) == TRUE) {
			SetEscapeData(repw);
			return TRUE;
		}
	}

	// �ȉ��́A��l���̈ʒu�����֌W�ȃC�x���g
	//
	// �֗��{�^���`�F�b�N
	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	}

	// ���j���[�`�F�b�N
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
        FieldMenuInit( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	// �퓬�e�X�g��
	if( req->DebugBattle ){
		DebugFieldEncount( repw );	//�������ŃG���J�E���g�Z�b�g
		return TRUE;
	}

	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �Ŕ̃C�x���g�N���`�F�b�N
 * @param	reqw	�t�B�[���h�f�[�^
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------
static BOOL CheckBoardStart( FIELDSYS_WORK * repw )
{
	FIELD_OBJ_PTR obj;
	int	id;

	// OBJ�Ŕ`�F�b�N
	if( TalkAutoObjBoardEventCheck( repw, &obj ) == TRUE ){
		EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
		return TRUE;
	}

	// BG�Ŕ`�F�b�N
	id = TalkAutoBgBoardEventCheck(
			repw,(void *)EventData_GetNowBgTalkData(repw),EventData_GetNowBgTalkDataSize(repw));
	if( id != EVENT_ID_NONE ){
		EventSet_Script( repw, id, NULL );
		return TRUE;
	}

	return FALSE;
}


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �Y�z���̃C�x���g�N���`�F�b�N  by k.ohno
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------

BOOL CheckRequestUG( EV_REQUEST * req, FIELDSYS_WORK * repw )
{
    u8 bTalkCheck = FALSE;
    //06.04.06 �n���ɏ��߂č~�肽���̋����C�x���g�����̂��߂ɒǉ�
	//����X�N���v�g�i�V�[���N���X�N���v�g�j�`�F�b�N
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID()))){
        return FALSE;
    }
    UgMgrKeyCountDown();
    if( req->TalkCheck ){    // ��b--> �Y�z��p���j���[
        UgMgrTalkCheck(bTalkCheck);
        return FALSE;
    }
    if( req->MenuOpen ){	// ��l���̈ʒu�����֌W�ȃC�x���g
        UgMgrMenuCheck();
        return FALSE;
    }

    if(UgMgrTouchCheck()){ //�^�b�`�p�l���̑���Ɋւ������
        return FALSE;
    }
	
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return FALSE;
	}
#endif	PM_DEBUG
	return FALSE;
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �ΐ핔�����̃C�x���g�N���`�F�b�N  by k.ohno
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------

BOOL CheckRequestVSRoom( EV_REQUEST * req, FIELDSYS_WORK * repw )
{
	if (req->PushCheck) {  // �o��
		if (req->PushSite == DIR_DOWN && MATR_IsDownMat(GetNowAttr(repw))) {
            EventSet_Script( repw, SCRID_BATTLE_ROOM_EXIT, NULL );
			return TRUE;
		}
	}
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID())) ||
       !CommDirectIsMoveState()){
        return FALSE;
    }
    
	// ��b  ��b�Ɋւ��Ă̓N���C�A���g�����ŏ������\�Ȃ̂ŏ�Ɠ����ɂȂ�
    // ������CommPlayer�͏���
	if( req->TalkCheck ){
		{	// OBJ�Ƃ̉�b�`�F�b�N
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;
                if(MV_PLAYER != FieldOBJ_MoveCodeGet(obj)){ // ���̃v���[���[�̏ꍇ
                    if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
                        Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
                    }
                    EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
                    return TRUE;
                }
			}
		}
	}
    if( req->TalkCheck ){    // ��b--> 
        EventCmd_VSRoomTrainer(repw);
        return TRUE;
    }
	// �֗��{�^���`�F�b�N
/*	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	} */
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
	    FieldMenuInitVS( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return FALSE;
	}
#endif	PM_DEBUG
	return FALSE;
}


static int MyStatusCheck( void );

static int MyStatusCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;
	for(i=1;i<5;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	return (result>=1);
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	���j�I�����[����p�C�x���g�N���`�F�b�N
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g
 * @param	repw	�Q�[�����䃏�[�N�ւ̃|�C���^
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 */
//--------------------------------------------------------------------------------------------
BOOL CheckRequestUnion(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{
	//�b���������
	//�i�ǉ��\��j

	// �ʐM�ڑ����������ꍇ�͐�΂ɃC�x���g���J�n�����Ȃ�
//	if(CommStateIsUnionParentConnectSuccess()){
	if(WH_GetBitmap()&0xfe){
		OS_Printf("�ڑ����Ȃ̂ŁA�C�x���g�͔��������Ȃ� bitmap=%02x status=%d connectnum=%d\n", WH_GetBitmap(), MyStatusCheck(), CommGetConnectNum());
		if(MyStatusCheck() && CommGetConnectNum()>1){

			// �����ɘb���������܂���
			EventSet_Script( repw, SCRID_CONNECT_UNION_RECEIVE_OBJ, NULL );
			return TRUE;
		}
		return FALSE;
	}

	//���j�I�����[���C�x���g�`�F�b�N�F��b�iNPC�ցj
	if( req->TalkCheck ){
		// OBJ�Ƃ̉�b�`�F�b�N
		FIELD_OBJ_PTR obj;
		if( TalkObjEventCheck( repw, &obj ) == TRUE ){
			if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
				Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
			}
            CommStateChildReserve(); // �q�@�Ƃ��ĂȂ���̂Őe�@�ɂ͂Ȃ�Ȃ�
			EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
			return TRUE;
		}
	}

	//���j�I�����[���C�x���g�`�F�b�N�F�o����
	if (req->MoveCheck && MATR_IsWarpPoint(GetNowAttr(repw))) {
		EventSet_UnionRoomMapChangeOut(repw);
		return TRUE;
	}

	//���j�I�����[���C�x���g�`�F�b�N�F���j���[�i�f�o�b�O�܂ށj
	//	�֗��{�^��������Ȃ�΃`�F�b�N�͂��̂�����
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
	    FieldMenuInitUnion( repw );

		// ���Z�����Ƀr�[�R����������
		Union_BeaconChange( UNION_PARENT_MODE_BUSY );	
		CommStateUnionPause();

		OS_TPrintf("MENU OPEN\n");
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}


//--------------------------------------------------------------------------------------------
/**
 * �o�g���^���[��p�C�x���g�N���`�F�b�N
 *
 * @param	req		�C�x���g�`�F�b�N���N�G�X�g
 *
 * @retval	"TRUE = �C�x���g����"
 * @retval	"FALSE = �C�x���g�����Ȃ�"
 *
 *	���N�G�X�g�����Ƀ`�F�b�N�v���O�������Ăяo���A�C�x���g���N������
 */
//--------------------------------------------------------------------------------------------
int CheckRequestBTower(const EV_REQUEST * req, FIELDSYS_WORK * repw)
{

	//����X�N���v�g�i�V�[���N���X�N���v�g�j�`�F�b�N
	if (req->DebugKeyPush == FALSE && SpScriptSearch(repw, SP_SCRID_SCENE_CHANGE) == TRUE) {
		return TRUE;
	}

#if 0
	//�g���[�i�[�����`�F�b�N
	{
		if( req->DebugKeyPush == FALSE ){
			BOOL flag = EvPoke_Enable2vs2Battle(SaveData_GetTemotiPokemon(repw->savedata));
			
			if( SysFlag_PairCheck(SaveData_GetEventWork(repw->savedata)) == 1 ){
				flag = TRUE;		//�A��������Ȃ�_�u���\
			}
			
			if( EvTrainerEyeCheck(repw,flag) == TRUE ){
				return TRUE;
			}
		}
	}
	
	//����ړ��`�F�b�N
	if (req->MoveCheck) {
		//������������ǂ����t���O�̍X�V
		SysFlag_OneStepReset( SaveData_GetEventWork(repw->savedata) );
		//IncRecord( CNT_WALK );
		if( CheckMoveEvent( repw ) == TRUE ){
			return TRUE;
		}
		//�|�W���`�F�b�N
		if ( GYM_CheckSteelLift(repw) ){
			return TRUE;
		}
	}
	//���ނ�ɓ���Ȃ��C�x���g�`�F�b�N
	if (GrassStepInCheck(req, repw)) {
		EventSet_Script( repw, SCRID_POS_R201_STOP, NULL );
		return TRUE;
	}

	//���@�C�x���g�`�F�b�N
	{
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
		HERO_EVBIT evbit;
		evbit = HERO_EVBIT_NON;
		if (SysFlag_KairikiCheck( SaveData_GetEventWork(repw->savedata) )) {
			evbit |= HERO_EVBIT_PERMIT_KAIRIKI;
		}
		if( Player_EventMoveCheck(repw,repw->player,dir,evbit) == TRUE ){
			return( TRUE );
		}
	}
	
	//���@����`�F�b�N�i����ړ� ���邢�� �U������j
	if(req->StepCheck ){
		int dir = Player_KeyDirGet( repw->player, req->trg, req->cont );
        if( JikiEventCheck_ArrowMat(repw,repw->player,dir) == TRUE ){
            return( TRUE );
        }
        
		// �G���J�E���g
		if (CheckEncountEvent(repw)) {
			return TRUE;
		}


		// �Ŕ`�F�b�N
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}

	//�����]���ł��܂����삵�Ȃ��̂ŁA�����ł��Ŕ`�F�b�N ( FR/LG �̃}�l )
	if( req->MatCheck && Player_DirGet(repw->player) == req->Site ){
		// �Ŕ`�F�b�N
		if( CheckBoardStart(repw) == TRUE ){
			return TRUE;
		}
	}
#endif
	// ��b
	if( req->TalkCheck ){

		{	// OBJ�Ƃ̉�b�`�F�b�N
			FIELD_OBJ_PTR obj;
			if( TalkObjEventCheck( repw, &obj ) == TRUE ){
				EVENT_WORK * ev_work;

				if( Player_MoveForceStopCheck( repw->player ) == TRUE ){
					Player_MoveForceStop( repw->player, Player_DirGet(repw->player) );
				}
				if (FieldOBJ_EventTypeGet(obj) != EV_TYPE_MSG) {
					EventSet_Script( repw, FieldOBJ_EventIDGet(obj), obj );
				} else {
					EventSet_Script( repw, SCRID_COMMON_MSG, obj );
				}
				return TRUE;
			}
		}

		{	// BG�̘b�������`�F�b�N
			int	id;
			
			id = TalkBgEventCheck(
					repw,
					(void *)EventData_GetNowBgTalkData( repw ),
					EventData_GetNowBgTalkDataSize( repw ) );

			if( id != EVENT_ID_NONE ){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}
#if 0
		{	// ���h��؃`�F�b�N
			int id;
			if (HTE_CheckHoneyTree(repw,&id)){
				EventSet_Script( repw, id, NULL );
				return TRUE;
			}
		}
#endif
		{
			int id;
			id = EvCheck_TalkMapAttr(repw, GetFrontAttr(repw));
			if (id != EVENT_ID_NONE) {
				EventSet_Script(repw, id, NULL);
				return TRUE;
			}

		}
	}

	if (req->PushCheck) {
		if (EvCheck_ExitByPush(repw, req) == TRUE) {
			return TRUE;
		}
	}

	// �ȉ��́A��l���̈ʒu�����֌W�ȃC�x���g
	//
	// �֗��{�^���`�F�b�N
	if( req->CnvButton ){
		if( FieldConvButtonEventInit( repw ) == TRUE ){
			return TRUE;
		}
	}

	// ���j���[�`�F�b�N
	if( req->MenuOpen ){
		Snd_SePlay( SE_WIN_OPEN );
        FieldMenuInit( repw );
		return TRUE;
	}
#ifdef	PM_DEBUG
	if( req->DebugMenu ){
		Snd_SePlay( SE_WIN_OPEN );
		FieldDebugListSet( repw );
		return TRUE;
	}
#endif	PM_DEBUG

	return FALSE;
}


//============================================================================================
//
//
//				�C�x���g�N���`�F�b�N�F�ʃ`�F�b�N���[�`��
//
//
//============================================================================================

//------------------------------------------------------------------
//------------------------------------------------------------------
static BOOL CheckEncountEvent(FIELDSYS_WORK * fsys)
{
	int x, z;
	GetNowPos(fsys, &x, &z);
	if (SysFlag_PokeParkCheck(SaveData_GetEventWork(fsys->savedata)) == TRUE) {
		if (PokeParkSys_CheckEncount(fsys, x, z) == TRUE) {
			EventSet_PokeParkBattle(fsys, PokeParkSys_SetBattleParam(fsys));
			return TRUE;
		} else {
			return FALSE;
		}
	}
#ifdef	PM_DEBUG
	if( DebugFlagData.encount_flag == 0 &&
		ZoneData_GetEncountFlag(fsys->location->zone_id) &&
		FieldEncount_Check( fsys ) == TRUE) {
		return TRUE;
	}
#else
	// �G���J�E���g
	if( ZoneData_GetEncountFlag(fsys->location->zone_id) &&
		FieldEncount_Check( fsys ) == TRUE) {
		return TRUE;
	}
#endif	PM_DEBUG
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�N���`�F�b�N�F�o�����i�������݁j
 * @param	fsys	�Q�[�����䃏�[�N�ւ̃|�C���^
 * @param	req		���N�G�X�g�\���̂ւ̃|�C���^
 * @retval	TRUE	�C�x���g�N������
 * @retval	FALSE	�C�x���g�N���Ȃ�
 */
//------------------------------------------------------------------
static BOOL EvCheck_ExitByPush(FIELDSYS_WORK * fsys, const EV_REQUEST * req)
{
	int door_id;
	int x;
	int z;
	int dir;
	u8	attr;
	LOCATION_WORK cnct;

	//�������ݑ�������Ă��Ȃ��ꍇ�A�`�F�b�N���Ȃ�
	if (req->PushSite == DIR_NOT) {
		return FALSE;
	}

	//�i���W���v�b�V������
	if (GYM_CheckCombatWall(fsys)){
		return TRUE;
	}

	//�i�s��������O���i�s�s�\�łȂ��ꍇ�A�`�F�b�N�͂��Ȃ�
	GetFrontPos(fsys, &x, &z);
	if (GetHitAttr(fsys, x, z) == 0) {
		return FALSE;
	}

	//�i�s��������O�̏o�����`�F�b�N
	if (GetConnectData(fsys, x, z, &cnct) && req->PushSite != DIR_NOT) {
		attr = GetAttributeLSB(fsys, x, z);
		if (MATR_IsDoor(attr)) {
			MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
							0, 0, req->PushSite, M_JUMP_DOOR);
			return TRUE;
		}
#ifdef	DEBUG_ALL_EXIT_CONNECT
		//2006.03.04
		//����́A�h�A�ȊO�ł��ڑ������݂���ꍇ�͂Ƃ肠�����Ȃ��ł��܂��B
		//���̂��������ƃA�g���r���[�g������̂Ŕp�~����\��
		EventSet_EasyMapChange(fsys, cnct.zone_id, cnct.door_id,
				0,0, Player_DirGet(fsys->player));
		return TRUE;
#endif
	}

	//���݂̑����ʒu�̏o�����`�F�b�N
	GetNowPos(fsys, &x, &z);

	// �}�b�g�`�F�b�N
	attr = GetAttributeLSB( fsys, x, z );
	if( MATR_IsRightMat(attr)||MATR_IsRightNoArrowMat(attr) ){
		if( req->PushSite != DIR_RIGHT ){
			return FALSE;
		}
	}else if( MATR_IsLeftMat(attr)||MATR_IsLeftNoArrowMat(attr) ){
		if( req->PushSite != DIR_LEFT ){
			return FALSE;
		}
	}else if( MATR_IsDownMat(attr)||MATR_IsDownNoArrowMat(attr) ){
		if( req->PushSite != DIR_DOWN ){
			return FALSE;
		}
	}else if( MATR_IsRightStairs(attr) ){	//�E�K�i
		if( req->PushSite != DIR_RIGHT ){
			return FALSE;
		}
	}else if( MATR_IsLeftStairs(attr) ){	//���K�i
		if( req->PushSite != DIR_LEFT ){
			return FALSE;
		}
	}

	if (GetConnectData(fsys, x, z, &cnct) == FALSE) {
		return FALSE;
	}


	{
		int type;
		if (MATR_IsDoor(attr)){					//�h�A
			type = M_JUMP_DOOR;
		}else if(MATR_IsRightStairs(attr)){		//�K�i
			type = M_JUMP_STAIRS;
		}else if(MATR_IsLeftStairs(attr)){		//�K�i
			type = M_JUMP_STAIRS;
		}else if (MATR_IsRightMat(attr) || MATR_IsRightNoArrowMat(attr)
				|| MATR_IsLeftMat(attr) || MATR_IsLeftNoArrowMat(attr)
				|| MATR_IsDownMat(attr) || MATR_IsDownNoArrowMat(attr)){
			MJUMP_ChangeMapByLocation(	fsys, cnct.zone_id, cnct.door_id,
										0, 0, req->PushSite);
			return TRUE;
		}else{
			return FALSE;
		}

		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, req->PushSite, type);
	}
	
	return TRUE;
}



//--------------------------------------------------------------------------------------------
/**
 * @brief	�}�b�v�A�g���r���[�g�b�������C�x���g�`�F�b�N
 * @param	repw	�Q�[�����䃏�[�N�ւ̃|�C���^
 * @param	matr	�}�b�v�A�g���r���[�g�̒l
 * @retval	EVENT_ID_NONE	
 * @retval	����ȊO		�X�N���v�g��ID�w��
 */
//--------------------------------------------------------------------------------------------
u16 EvCheck_TalkMapAttr(FIELDSYS_WORK * repw, MATR matr)
{
	int dir = Player_DirGet(repw->player);

	if (MATR_IsPC(matr) && dir == DIR_UP) {
		return SCRID_PC_ON;
	}else if (MATR_IsLittleBookRack01(matr)) {
		return SCRID_LITTLE_RACK1;
	}else if (MATR_IsLittleBookRack02(matr)) {
		return SCRID_LITTLE_RACK2;
	}else if (MATR_IsBookRack01(matr)) {
		return SCRID_RACK1;
	}else if (MATR_IsBookRack02(matr)) {
		return SCRID_RACK2;
	}else if (MATR_IsTrashBox(matr)) {
		return SCRID_TRASH_BOX;
	}else if (MATR_IsShopBookRack01(matr)) {
		return SCRID_SHOP_RACK1;
	}else if (MATR_IsShopBookRack02(matr)) {
		return SCRID_SHOP_RACK2;
	}else if (MATR_IsShopBookRack03(matr)) {
		return SCRID_SHOP_RACK3;
	}else if (MATR_IsWaterFall(matr)) {
		return SCRID_HIDEN_TAKINOBORI;
	}else if (MATR_IsMap(matr)) {
		return SCRID_TMAP_BG;
	}else if (MATR_IsBumpPost(matr)) {
		return SCRID_BUMP_POST;
	}else if (MATR_IsTV(matr) && dir == DIR_UP) {
		return SCRID_TV;
	}

	if( Player_EventAttrCheck_KabeNobori(matr,dir) ){
		return SCRID_HIDEN_KABENOBORI;
	}

	if( Player_FormGet(repw->player) != HERO_FORM_SWIM ){
		MYSTATUS * my = SaveData_GetMyStatus(repw->savedata);
		int	gx = Player_NowGPosXGet(repw->player);
		int	gz = Player_NowGPosZGet(repw->player);
		int	natr = GetAttributeLSB(repw, gx, gz);
		if( Player_EventAttrCheck_Naminori(repw->player,natr,matr)
				&& MyStatus_GetBadgeFlag(my, BADGE_ID_C05)){
			if( EvPoke_CheckWaza(SaveData_GetTemotiPokemon(repw->savedata),
						WAZANO_NAMINORI) != 0xff) {
				return SCRID_HIDEN_NAMINORI;
			}
		}
	}

	return EVENT_ID_NONE;
}

//-------------------------------------------------------------
/**
 * @brief	������Ƃ̃C�x���g�N���`�F�b�N
 * @param	fsys	�Q�[�����䃏�[�N�ւ̃|�C���^
 * @param
 * 
 * @retval	BOOL		TRUE:����	FALSE:�Ȃ�
 */
//-------------------------------------------------------------
static BOOL CheckMoveEvent(FIELDSYS_WORK * fsys)
{
	u8	attr;
	int x,z;
	int dir;

	//�|�W���`�F�b�N
	if ( GYM_CheckSteelLift(fsys) ){
		return TRUE;
	}
	
	//�����ړ����`�F�b�N
	dir = Player_DirGet( fsys->player );
	if( JikiEventCheck_ArrowMat(fsys,fsys->player,dir) == TRUE ){
		return( TRUE );
	}
        
	x = Player_NowGPosXGet(fsys->player);
	z = Player_NowGPosZGet(fsys->player);
	
	attr = GetAttributeLSB( fsys, x, z );
	
	if ( CheckPosEvent(fsys) == TRUE ) return TRUE;		// ���W�����C�x���g�`�F�b�N
	if ( CheckExit( fsys, x, z, attr) == TRUE ){
		SetEscapeData(fsys);
		return TRUE;	// �o������`�F�b�N
	}
///	if ( PosAttrCheck(attr) == TRUE ) return TRUE;		// �A�g���r���[�g�����`�F�b�N
	if ( Player_MoveBitCheck_Force(fsys->player) ) {
		//���@�������ړ����͕�����������鏈���̓t�b�N�����
		return FALSE;
	}

	Field_SendPoketchInfo( fsys, POKETCH_SEND_PEDOMATER, 1 );

	if ( CheckPoison( fsys ) == TRUE ) return TRUE;		// �Ń_���[�W����
	if ( CheckSafariStep(fsys) == TRUE ) return TRUE;	// �T�t�@�������`�F�b�N
	if ( CheckSodateya( fsys )==TRUE ) return TRUE;		// ��ĉ�����
	if ( CheckBtlSearcher( fsys )==TRUE ) return TRUE;	// �o�g���T�[�`���[����
	if ( CheckPokeSearcher( fsys )==TRUE ) return TRUE;	// �|�P�T�[�`���[����
///	if ( StepCountCheck(attr) == TRUE ) return TRUE;	// �����J�E���g�֘A�`�F�b�N
	if ( CheckSpray( fsys ) == TRUE )	return	TRUE;	// �X�v���[�����`�F�b�N

	// 128���������Ƃ�1��Ȃ��ǌv�Z
	if( CheckFriendCalcStepCount( fsys ) ){
		DoFriendCalcStepCount( fsys );
	}

	SysWork_ParkWalkCountPlus(SaveData_GetEventWork(fsys->savedata));
	return FALSE;
}

//-------------------------------------------------------------
/**
 * @brief	POS�C�x���g�`�F�b�N
 * @param	fsys	�Q�[�����䃏�[�N�ւ̃|�C���^
 * 
 * @retval	BOOL		TRUE:����	FALSE:�Ȃ�
 */
//-------------------------------------------------------------
static BOOL CheckPosEvent(FIELDSYS_WORK * fsys)
{
	u16	id;
	id = PosEventCheck(
			fsys,
			(void *)EventData_GetNowPosEventData( fsys ),
			EventData_GetNowPosEventDataSize( fsys ) );
	if( id != EVENT_ID_NONE ){
		EventSet_Script( fsys, id, NULL );
		return TRUE;
	}
	return FALSE;
}

//-------------------------------------------------------------
//	 �o������̃`�F�b�N���f�[�^�Z�b�g
//-------------------------------------------------------------
static BOOL CheckExit(FIELDSYS_WORK * fsys, const int x, const int z, const u8 inAttr)
{
	LOCATION_WORK cnct;

	if (GetConnectData(fsys, x, z, &cnct) == FALSE) {
		return FALSE;
	}
	
	//�G�X�J���[�^�[
	if( MATR_IsEscalator(inAttr) == TRUE ){
		int dir = Player_DirGet( fsys->player );
		if (dir == DIR_LEFT){	//������
			dir = DIR_RIGHT;	//�t�F�[�h�C�����͉E����
		}else if (dir == DIR_RIGHT){	//�E����
			dir = DIR_LEFT;	//�t�F�[�h�C�����͍�����
		}else{
			GF_ASSERT(0&&"���@�̌������s��");
			return FALSE;
		}
		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, dir, M_JUMP_ESCA);
		return TRUE;
	}else if ( MATR_IsEscalatorNonRet(inAttr) == TRUE ){
		int dir = Player_DirGet( fsys->player );
		if ( (dir!=DIR_LEFT)&&(dir!=DIR_RIGHT) ){
			GF_ASSERT( 0&&"���@�̌������s��" );
			return FALSE;
		}
		MJUMP_ChangeMap(fsys, cnct.zone_id, cnct.door_id,
						0, 0, dir, M_JUMP_ESCA);
		return TRUE;
	}
	//��������ݍ��݃}�b�g
	if (MATR_IsUpMat(inAttr)||MATR_IsUpNoArrowMat(inAttr)){
		MJUMP_ChangeMapByLocation(	fsys, cnct.zone_id, cnct.door_id,
										0, 0, DIR_UP);
		return TRUE;
	}
    // ���[�v�|�C���g
    if(MATR_IsWarpPoint(inAttr)){
        EventCmd_WarpPoint(fsys, cnct.zone_id, cnct.door_id);
		return TRUE;
    }
	
#ifdef	DEBUG_ALL_EXIT_CONNECT
	//2006.03.04
	//�A�g���r���[�g���Ȃ����o����������ꍇ�A�Ƃ肠�����Ȃ�
	//�ŏI�I�ɂ͂��̏����͑S�ẴA�g���r���[�g�����낦�Εs�v�ƂȂ�
	if (
			MATR_IsLeftStairs(inAttr) ||
			MATR_IsRightStairs(inAttr) ||
			MATR_IsDownMat(inAttr) ||
//			MATR_IsUpMat(inAttr) ||
			MATR_IsLeftMat(inAttr) ||
			MATR_IsRightMat(inAttr) ||
			MATR_IsDownNoArrowMat(inAttr) ||
//			MATR_IsUpNoArrowMat(inAttr) ||
			MATR_IsLeftNoArrowMat(inAttr) ||
			MATR_IsRightNoArrowMat(inAttr)) {
		//��ɂ̂��ĉ������ރ^�C�v�̃A�g���r���[�g�̏ꍇ�͖�������
		return FALSE;
	}
	EventSet_EasyMapChange(fsys, cnct.zone_id, cnct.door_id,
			0,0, Player_DirGet(fsys->player));
	
	return TRUE;
#endif

/**	
			//����
			//�B�����Ƃ���
			//���[�v�|�C���g
			//���Ƃ���
			//OBJ�ʒu�ێ����[�v�|�C���g
*/	

	return FALSE;
}

//==============================================================================
/**
 * $brief   ��ĉ��`�F�b�N�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckSodateya( FIELDSYS_WORK *fsys )
{
	POKEPARTY     *myparty  = SaveData_GetTemotiPokemon(fsys->savedata);
	SODATEYA_WORK *sodateya = SaveData_GetSodateyaWork(fsys->savedata);
	
	// ��ĉ��P����������
	if (PokeSodateya( sodateya, myparty, fsys ) == TRUE) {
		RECORD *record = SaveData_GetRecord(fsys->savedata);
		
		// �^�}�S�����܂ꂽ�񐔂��{�P
		RECORD_Inc( record, RECID_TAMAGO_HATCHING );
		// �X�R�A���Z
		RECORD_Score_Add( record, SCORE_ID_EGG_HATCHING );
		
		// �^�}�S���z�������C�x���g����
		EventSet_Script(fsys, SCRID_EGG_HATCHING, NULL);
		

		return TRUE;
	} else {
		return FALSE;
	}
}

//==============================================================================
/**
 * $brief   �o�g���T�[�`���[�`�F�b�N�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckBtlSearcher( FIELDSYS_WORK *fsys )
{
	BS_StepCountUp( fsys );
	return FALSE;
}

//==============================================================================
/**
 * $brief   �|�P�T�[�`���[�`�F�b�N�Ăяo��
 *
 * @param   fsys		
 *
 * @retval  BOOL		
 */
//==============================================================================
static BOOL CheckPokeSearcher( FIELDSYS_WORK *fsys )
{
	SwayGrass_ChargePokeSearcher(fsys);
	return FALSE;
}

//==============================================================================
/**
 * $brief   �X�v���[����
 *
 * @param   fsys		
 *
 * @retval  BOOL		TRUE��������A�X�v���[���ʐ؂ꂽ���b�Z�[�W�\��
 */
//==============================================================================
static BOOL CheckSpray( FIELDSYS_WORK *fsys )
{
	return Spray_DecSpray(fsys->savedata, fsys);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A������@�Ȃ��x����
 *
 *	@param	fsys	�t�B�[���h�V�X�e��
 *
 *	@retval	TRUE	�Ȃ��x�v�Z����
 *	@retval	FALSE	�Ȃ��x�v�Z���Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL CheckFriendCalcStepCount( FIELDSYS_WORK *fsys )
{
	u16 step;
	EVENTWORK* ev;
	BOOL ret = FALSE;

	ev = SaveData_GetEventWork( fsys->savedata );
	step = SysWork_FriendlyStepCountGet( ev );
	step ++;
	if( step >= FRIENDCALC_STEP_MAX ){
		step = 0;
		ret = TRUE;
	}
	SysWork_FriendlyStepCountSet( ev, step );
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�Ȃ��x�v�Z���s��
 *
 *	@param	fsys	�t�B�[���h�V�X�e��
 */
//-----------------------------------------------------------------------------
static void DoFriendCalcStepCount( FIELDSYS_WORK *fsys )
{
	int i, max;
	POKEMON_PARAM * pp;
	POKEPARTY *party  = SaveData_GetTemotiPokemon(fsys->savedata);
	u16 placeID = ZoneData_GetPlaceNameID(fsys->location->zone_id);

	max = PokeParty_GetPokeCount(party);

	for( i=0; i<max; i++ ){
		pp = PokeParty_GetMemberPointer(party, i);
		FriendCalc( pp, FRIEND_TSUREARUKI, placeID );
	}
}



//==============================================================================
//==============================================================================
//-------------------------------------------------------------
/**
 * @brief	�Ń_���[�W�`�F�b�N
 * @param	fsys		�t�B�[���h����f�[�^�ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ��łɂ�鎀�S�_���[�W����
 *
 * �����œŃG�t�F�N�g�̌Ăяo�����s���Ă���
 */
//-------------------------------------------------------------
static BOOL CheckPoison(FIELDSYS_WORK * fsys)
{
	POKEPARTY     *myparty  = SaveData_GetTemotiPokemon(fsys->savedata);
	u16 *poison_step = Situation_GetPoisonStepCount(SaveData_GetSituation(fsys->savedata));
	(*poison_step) ++;
	(*poison_step) %= POISON_STEP_MAX;
	if (*poison_step != 0) {
		return FALSE;
	}

	switch (EvPoke_PoisonDamage(myparty, ZoneData_GetPlaceNameID(fsys->location->zone_id))){
	case FLD_POISON_NODAMAGE:
		return FALSE;
	case FLD_POISON_DAMAGE:
		POISON_EFFE_Start(fsys->fldmap->poisoneffect);
		return FALSE;
	case FLD_POISON_DEAD:
		POISON_EFFE_Start(fsys->fldmap->poisoneffect);
		EventSet_Script(fsys, SCRID_POISON_DEAD, NULL);
		return TRUE;
	}
	return FALSE;
}
//==============================================================================
//==============================================================================
//-------------------------------------------------------------
/**
 * @brief	�T�t�@�������`�F�b�N
 * @param	fsys		�t�B�[���h����f�[�^�ւ̃|�C���^
 * @return	BOOL	TRUE�̂Ƃ������I���C�x���g����
 *
 */
//-------------------------------------------------------------
static BOOL CheckSafariStep(FIELDSYS_WORK * fsys)
{
	u16 * safari_ball;
	u16 * safari_step;
	//�T�t�@�����[�h�łȂ���΃`�F�b�N���Ȃ�
	if (SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) == FALSE) {
		return FALSE;
	}

	safari_ball = Situation_GetSafariBallCount(SaveData_GetSituation(fsys->savedata));
	if (*safari_ball == 0) {
		EventSet_Script(fsys, SCRID_SAFARI_ANNOUNCE_BALL, NULL);
		return TRUE;
	}

	safari_step = Situation_GetSafariStepCount(SaveData_GetSituation(fsys->savedata));
	(*safari_step) ++;
	OS_Printf("SAFARI STEP=%d\n",*safari_step);
	if (*safari_step >= 500) {
		EventSet_Script(fsys, SCRID_SAFARI_ANNOUNCE_TIME, NULL);
		return TRUE;
	}

	return FALSE;
}

//============================================================================================
//
//
//		�C�x���g�N���`�F�b�N�p�c�[���֐�
//
//
//============================================================================================
//-------------------------------------------------------------
//-------------------------------------------------------------
static void GetNowPos(const FIELDSYS_WORK * fsys, int *x, int *z)
{
	*x = Player_NowGPosXGet(fsys->player);
	*z = Player_NowGPosZGet(fsys->player);
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static void GetFrontPos(const FIELDSYS_WORK * fsys, int * x, int * z)
{
	int dir;
	dir = Player_DirGet(fsys->player);
	GetMovePos(fsys, dir, x, z);
}

//-------------------------------------------------------------
//-------------------------------------------------------------
static void GetMovePos(const FIELDSYS_WORK * fsys, int dir, int * x, int * z)
{
	GetNowPos(fsys, x, z);
	switch (dir) {
	case DIR_UP:
		*z -= 1;
		break;
	case DIR_DOWN:
		*z += 1;
		break;
	case DIR_LEFT:
		*x -= 1;
		break;
	case DIR_RIGHT:
		*x += 1;
		break;
	default:
		GF_ASSERT_MSG("���@�̕�������������\n",0);
	}
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static u8 GetNowAttr(const FIELDSYS_WORK * fsys)
{
	int x,z;
	GetNowPos(fsys, &x, &z);
	return GetAttributeLSB(fsys, x, z);
}

//-------------------------------------------------------------
/**
 */
//-------------------------------------------------------------
static u8 GetFrontAttr(const FIELDSYS_WORK * fsys)
{
	int x,z;
	GetFrontPos(fsys, &x, &z);
	return GetAttributeLSB(fsys, x, z);
}


//-------------------------------------------------------------
/**
 * @brief	�ڑ��f�[�^�̎擾
 * @param	fsys		�t�B�[���h����f�[�^�ւ̃|�C���^
 * @param	x			�ڑ��f�[�^��T��X�ʒu�i�O���b�h�P�ʁj
 * @param	z			�ڑ��f�[�^��T��Y�ʒu�i�O���b�h�P�ʁj
 * @retval	CONNECT_DATA	�ڑ��f�[�^�̃A�h���X
 * @retval	NULL			�ڑ��f�[�^���Ȃ������ꍇ
 */
//-------------------------------------------------------------
static BOOL GetConnectData(const FIELDSYS_WORK * fsys, int x, int z,
		LOCATION_WORK * next)
{
	const CONNECT_DATA * connect;
	int door_id;
	door_id = EventData_SearchNowConnectIDByXZ(fsys, x, z);
	if (door_id == -1) {
		return FALSE;
	}
	connect = EventData_GetNowConnectDataByID(fsys, door_id);
	if (connect == NULL) {
		return FALSE;
	}
	if (connect->link_door_id == SPECIAL_SPEXIT01) {
		GF_ASSERT(connect->link_zone_id == ZONE_ID_SPECIAL);
		*next = *(Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata)));
	} else {
		SetLocation(next, connect->link_zone_id, connect->link_door_id,
				connect->x, connect->z, DIR_DOWN);
	}
	{
		//�����邱�ƂɂȂ�o�����̏����o���Ă���
		LOCATION_WORK * ent = Situation_GetEntranceLocation(SaveData_GetSituation(fsys->savedata));
		SetLocation(ent, fsys->location->zone_id, door_id, x, z, Player_DirGet(fsys->player));
	}
	return TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �G�X�P�[�v�f�[�^�Z�b�g
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inX				���A�w���p
 * @param	inZ				���A�y���W
 * @param	inDir			���������̌���
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetEscapeDataCore(FIELDSYS_WORK * fsys, const int inX, const int inZ, const int inDir)
{
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);
	(*escape) = *(fsys->location);
	escape->dir = inDir;
	escape->grid_x = inX;
	escape->grid_z = inZ;
	if (inDir == DIR_UP){
		(escape->grid_z)++;
	}
	escape->zone_id = fsys->location->zone_id;
	escape->door_id = DOOR_ID_JUMP_CODE;
}

//--------------------------------------------------------------------------------------------
/**
 * �G�X�P�[�v�f�[�^�Z�b�g
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetEscapeData(FIELDSYS_WORK * fsys)
{
	int x,z;
	LOCATION_WORK cnct;
	
	GetNowPos(fsys, &x, &z);
	if ( GetConnectData(fsys, x, z, &cnct) ) {
		if (ZoneData_IsSinouField(fsys->location->zone_id) == TRUE
				&& ZoneData_IsSinouField(cnct.zone_id) == FALSE) {
			SetEscapeDataCore(fsys, x, z, Player_DirGet(fsys->player));
		}
	}else{
		GetFrontPos(fsys, &x, &z);
		if ( GetConnectData(fsys, x, z, &cnct) ) {
			if (ZoneData_IsSinouField(fsys->location->zone_id) == TRUE
					&& ZoneData_IsSinouField(cnct.zone_id) == FALSE) {
				SetEscapeDataCore(fsys, x, z, Player_DirGet(fsys->player));
			}
		}
	}
}

