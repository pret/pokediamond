//============================================================================================
/**
 * @file	scr_trainer.c
 * @bfief	�X�N���v�g�R�}���h�F�g���[�i�[�֘A
 * @author	Satoshi Nohara
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "battle/battle_common.h"	//���C���N���[�h�ɕK�v
#include "poketool/tr_tool.h"		//TT_TrainerMessageGet
#include "ev_trainer.h"				//EvTrainer
#include "field_encount.h"			//DebugFieldEncount
#include "field_battle.h"			//BattleParam_IsWinResult
#include "ev_pokemon.h"				//EvPoke_Add


//============================================================================================
//
//	�v�����g�^�C�v�錾
//
//============================================================================================
BOOL EvCmdEyeTrainerMoveSet( VM_MACHINE * core );
BOOL EvCmdEyeTrainerMoveCheck( VM_MACHINE * core );
BOOL EvCmdEyeTrainerTypeGet( VM_MACHINE * core );
BOOL EvCmdEyeTrainerIdGet( VM_MACHINE * core );
BOOL EvCmdTrainerIdGet( VM_MACHINE * core );
BOOL EvCmdTrainerBattleSet( VM_MACHINE * core );
BOOL EvCmdTrainerMultiBattleSet( VM_MACHINE * core );
BOOL EvCmdTrainerTalkTypeGet( VM_MACHINE * core );
BOOL EvCmdRevengeTrainerTalkTypeGet( VM_MACHINE * core );
BOOL EvCmdTrainerTypeGet( VM_MACHINE * core );
BOOL EvCmdTrainerBgmSet( VM_MACHINE * core );
BOOL EvCmdTrainerLose( VM_MACHINE * core );
BOOL EvCmdTrainerLoseCheck( VM_MACHINE * core );
BOOL EvCmdSeacretPokeRetryCheck( VM_MACHINE * core );
BOOL EvCmd2vs2BattleCheck( VM_MACHINE * core );
BOOL EvCmdDebugBattleSet( VM_MACHINE * core );
BOOL EvCmdDebugTrainerFlagSet( VM_MACHINE * core );
BOOL EvCmdDebugTrainerFlagOnJump( VM_MACHINE * core );


//============================================================================================
//
//	�R�}���h
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �����F�g���[�i�[�ړ��Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdEyeTrainerMoveSet( VM_MACHINE * core )
{
	int* range;
	int* scr_id;
	int* tr_id;
	int* tr_type;
	int* dir;
	TCB_PTR* tcb;
	FIELD_OBJ_PTR* fldobj;
	PLAYER_STATE_PTR player;
	FIELDSYS_WORK* fsys = core->fsys;
	u16 pos				= VMGetWorkValue(core);								//�����f�[�^��0,1���H

	//�����f�[�^��0,1���H
	if( pos == 0 ){
		range	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_RANGE );	//
		dir		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_DIR );	//
		scr_id	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_SCR_ID );	//
		tr_id	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_ID );		//
		tr_type	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_TYPE );		//
		fldobj	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_FLDOBJ );	//
		tcb		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR0_TCB );
	}else{
		range	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_RANGE );	//
		dir		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_DIR );	//
		scr_id	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_SCR_ID );	//
		tr_id	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_ID );		//
		tr_type	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_TYPE );		//
		fldobj	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_FLDOBJ );	//
		tcb		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TR1_TCB );
	}

	player	= fsys->player;													//��l��

	//GMEVENT_Call_TrEyeMeetEventStart( fsys, core->event_work, *fldobj, 
	//									EvCall_TrEyeMeetMoveAddTcb(*fldobj,player,*dir,*range) );
	
	//�����ړ��������邽�߂ɓ���|�[�Y������
//	FieldOBJ_MovePauseClear( *fldobj );

	*tcb = EvTrainerEyeMoveSet( *fldobj, player, *dir, *range, 0, *tr_type, pos );
	//OS_Printf( "\n===========%d\n", (*tcb) );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����F�g���[�i�[�ړ��I���`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdEyeTrainerMoveCheck( VM_MACHINE * core )
{
	TCB_PTR* tcb;
	u16 pos		= VMGetWorkValue(core);					//�����f�[�^��0,1���H
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = 0;

	if( pos == SCR_EYE_TR_0 ){
		tcb	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TR0_TCB );
	}else{
		tcb	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TR1_TCB );
	}

	//�o�^����Ă��Ȃ���
	if( *tcb == NULL ){
		*ret_wk = 1;
		return 1;
	}

	if( EvTrainerEyeMoveEndCheck(*tcb) == TRUE ){
		EvTrainerEyeMoveEnd( *tcb );
		*tcb = NULL;	//�N���A����Ȃ��Ƃ܂�����
		*ret_wk = 1;
	}
	
	//return"1"��Ԃ��Ȃ��ƃ`�F�b�N�����[�v���Ă��܂��̂Œ��ӁI
	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �����F�g���[�i�[�^�C�v�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 *
 * TR0_TYPE�ɌŒ�I
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdEyeTrainerTypeGet( VM_MACHINE * core )
{
	u16* type	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TR0_TYPE );		//TR0_TYPE�Œ�
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = *type;
	//OS_Printf( "\n===========%d\n", (*type) );
	//OS_Printf( "\n===========%d\n", (*ret_wk) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �����F�g���[�i�[ID�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdEyeTrainerIdGet( VM_MACHINE * core )
{
	u16* tr_id_0	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TR0_ID );		//
	u16* tr_id_1	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TR1_ID );		//
	u16 pos			= VMGetWorkValue(core);					//�����f�[�^��0,1���H
	u16* ret_wk		= VMGetWork( core );

	//OS_Printf( "\n===========%d\n", pos );
	//OS_Printf( "\n===========%d\n", (*tr_id_0) );
	//OS_Printf( "\n===========%d\n", (*tr_id_1) );
	//OS_Printf( "\n===========%d\n", (*ret_wk) );
	*ret_wk = (pos == SCR_EYE_TR_0) ? (*tr_id_0) : (*tr_id_1);
	//OS_Printf( "\n===========%d\n", (*tr_id_0) );
	//OS_Printf( "\n===========%d\n", (*tr_id_1) );
	//OS_Printf( "\n===========%d\n", (*ret_wk) );
	return 0;
}


//============================================================================================
//
//	�퓬�֘A(������)
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[ID�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerIdGet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	u16* script_id			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_SCRIPT_ID );
	u16* wk					= VMGetWork( core );

	//�X�N���v�gID����A�g���[�i�[ID���擾
	*wk = GetTrainerIdByScriptId( *script_id );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�퓬�Ăяo��
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerBattleSet( VM_MACHINE * core )
{
	u32 fight_type;
	FIELDSYS_WORK * fsys	= core->fsys;
	u16* script_id			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_SCRIPT_ID );
	BOOL* win_flag			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_FLAG );
	u16 tr_id_0				= VMGetWorkValue(core);
	u16 tr_id_1				= VMGetWorkValue(core);
	u16 partner_id;

	partner_id = 0;
	if (SysFlag_PairCheck(SaveData_GetEventWork(core->fsys->savedata)) == 1) {
		partner_id = SysWork_PairTrainerIDGet( SaveData_GetEventWork(fsys->savedata) );
	}

	EventCmd_TrainerBattle(core->event_work, tr_id_0, tr_id_1, partner_id, HEAPID_WORLD, win_flag);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�ΐ�Ăяo���i�}���`�o�g���j
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerMultiBattleSet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	BOOL* win_flag			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_FLAG );
	u16 partner_id			= VMGetWorkValue(core);
	u16 tr_id_0				= VMGetWorkValue(core);
	u16 tr_id_1				= VMGetWorkValue(core);

	//OS_Printf( "partner_id = %d\n", partner_id );
	EventCmd_TrainerBattle(core->event_work, tr_id_0, tr_id_1, partner_id, HEAPID_WORLD, win_flag);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[��b�̎�ގ擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerTalkTypeGet( VM_MACHINE * core )
{
	u16 btl_type,lr,start_type,after_type,one_type;
	u16* script_id			= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_SCRIPT_ID );
	u16* wk1				= VMGetWork( core );
	u16* wk2				= VMGetWork( core );
	u16* wk3				= VMGetWork( core );

	//�X�N���v�gID����A�g���[�i�[ID���擾�A�_�u���o�g���^�C�v���擾
	btl_type = CheckTrainer2vs2Type( GetTrainerIdByScriptId(*script_id) );

	//�V���O�����_�u�����`�F�b�N
	if( btl_type == 0 ){
		//�V���O��
		start_type = TRMSG_FIGHT_START;
		after_type = TRMSG_FIGHT_AFTER;
		one_type   = 0;
	}else{
		//�_�u��
		lr = GetTrainerLRByScriptId( *script_id );

		if( lr == 0 ){
			//��
			start_type = TRMSG_FIGHT_START_1;
			after_type = TRMSG_FIGHT_AFTER_1;
			one_type = TRMSG_POKE_ONE_1;
		}else{
			//�E
			start_type = TRMSG_FIGHT_START_2;
			after_type = TRMSG_FIGHT_AFTER_2;
			one_type = TRMSG_POKE_ONE_2;
		}
	}

	*wk1 = start_type;
	*wk2 = after_type;
	*wk3 = one_type;

	//OS_Printf( "start_type = %d\n", *wk1 );
	//OS_Printf( "after_type = %d\n", *wk2 );
	//OS_Printf( "one_type = %d\n", *wk3 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �Đ�g���[�i�[��b�̎�ގ擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdRevengeTrainerTalkTypeGet( VM_MACHINE * core )
{
	u16 btl_type,lr,start_type,after_type,one_type;
	u16* script_id			= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_SCRIPT_ID );
	u16* wk1				= VMGetWork( core );
	u16* wk2				= VMGetWork( core );
	u16* wk3				= VMGetWork( core );

	//�X�N���v�gID����A�g���[�i�[ID���擾�A�_�u���o�g���^�C�v���擾
	btl_type = CheckTrainer2vs2Type( GetTrainerIdByScriptId(*script_id) );

	//�V���O�����_�u�����`�F�b�N
	if( btl_type == 0 ){
		//�V���O��
		start_type = TRMSG_REVENGE_FIGHT_START;
		after_type = 0;
		one_type   = 0;
	}else{
		//�_�u��
		lr = GetTrainerLRByScriptId( *script_id );

		if( lr == 0 ){
			//��
			start_type = TRMSG_REVENGE_FIGHT_START_1;
			after_type = 0;
			one_type   = TRMSG_POKE_ONE_1;
		}else{
			//�E
			start_type = TRMSG_REVENGE_FIGHT_START_2;
			after_type = 0;
			one_type   = TRMSG_POKE_ONE_2;
		}
	}

	*wk1 = start_type;
	*wk2 = after_type;
	*wk3 = one_type;

	//OS_Printf( "start_type = %d\n", *wk1 );
	//OS_Printf( "after_type = %d\n", *wk2 );
	//OS_Printf( "one_type = %d\n", *wk3 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�^�C�v�擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerTypeGet( VM_MACHINE * core )
{
	u16* script_id	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_SCRIPT_ID );
	u16* ret_wk		= VMGetWork( core );

	//�X�N���v�gID����A�g���[�i�[ID���擾�A�_�u���o�g���^�C�v���擾
	*ret_wk = CheckTrainer2vs2Type( GetTrainerIdByScriptId(*script_id) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[BGM�Đ�
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerBgmSet( VM_MACHINE * core )
{
	u16 tr_id = VMGetWorkValue(core);
	Snd_EyeBgmSet( Snd_EyeBgmGet(tr_id) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�s�k
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerLose( VM_MACHINE * core )
{
	EventCmd_NormalLose( core->event_work );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �g���[�i�[�s�k�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdTrainerLoseCheck( VM_MACHINE * core )
{
	BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16* ret_wk		= VMGetWork( core );

	*ret_wk = BattleParam_IsWinResult(*win_flag);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �B���|�P�����퓬�@�Đ�s�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeacretPokeRetryCheck( VM_MACHINE * core )
{
	BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16* ret_wk		= VMGetWork( core );

	*ret_wk = BattleParam_IsSeacretPokeRetry(*win_flag);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �z�z�|�P�����퓬�@�Đ�s�`�F�b�N
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdHaifuPokeRetryCheck( VM_MACHINE * core )
{
	BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16* ret_wk		= VMGetWork( core );

	*ret_wk = BattleParam_IsHaifuPokeRetry(*win_flag);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �莝���`�F�b�N 2vs2���\���擾
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmd2vs2BattleCheck( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = EvPoke_Enable2vs2Battle(SaveData_GetTemotiPokemon(core->fsys->savedata));
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�o�b�N�퓬�Ăяo��(������)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdDebugBattleSet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	BOOL * win_flag			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_FLAG );

	//�C�x���g���؂�ւ���Ă��܂��̂ŉ��I�I�I
	//DebugFieldEncount( fsys );
	
	//�C�x���g�R�[���Ȃ̂ŁA�X�N���v�g�ɕ��A���܂��B
	//EventCmd_TrainerBattle( core->event_work, 0 );
	//EventCmd_TrainerBattle( core->event_work, 0, FIGHT_TYPE_TRAINER, HEAPID_WORLD ,win_flag );
	EventCmd_TrainerBattle( core->event_work, 1, 0, 0, HEAPID_WORLD ,win_flag );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�o�b�N�g���[�i�[�t���O�Z�b�g(10����ROM�p�A���Ƃō폜���܂��I)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdDebugTrainerFlagSet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR* fldobj;
	FIELDSYS_WORK * fsys = core->fsys;

	fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );

	SetEventFlagTrainer( FieldOBJ_FieldSysWorkGet(*fldobj), FieldOBJ_OBJIDGet(*fldobj) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * �f�o�b�N�g���[�i�[�t���O�Z�b�g(10����ROM�p�A���Ƃō폜���܂��I)
 *
 * @param	core		���z�}�V������\���̂ւ̃|�C���^
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdDebugTrainerFlagOnJump( VM_MACHINE * core )
{
	int ret;
	s32	pos;
	FIELD_OBJ_PTR* fldobj;
	FIELDSYS_WORK* fsys = core->fsys;

	fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );

	pos = (s32)VMGetU32(core);

	ret = CheckEventFlagTrainer( FieldOBJ_FieldSysWorkGet(*fldobj), FieldOBJ_OBJIDGet(*fldobj) );

	//�t���O��ON�Ȃ�W�����v
	if( ret == TRUE ){
		VMJump( core, (VM_CODE *)(core->PC+pos) );	//JUMP
		//VM_End( core );
		return 1;			//10��ROM�̂��肬��̕ύX�ɑΏ����邽�߉��I�I�I�I�I
	}

	return 0;
}


