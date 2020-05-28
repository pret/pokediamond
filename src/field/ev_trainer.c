/******************************************************************************
/**
 *
 * @file	ev_trainer.c
 * @brief	�g���[�i�[�����C�x���g
 * @author	kagaya
 * @data	05.10.03
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "fieldobj.h"
#include "player.h"
#include "ev_trainer.h"
#include "field_encount.h"
#include "field_effect.h"
														//add nohara
#include "script.h"										//StartFieldScript
#include "..\fielddata\script\trainer_def.h"			//SCRID_TRAINER_MOVE_BATTLE

//==============================================================================
//	define
//==============================================================================
#define EYE_MEET_MOVE_TCB_PRI (0xff)					///<�����ړ�TCB�v���C�I���e�B�@���K��
#define EYE_MEET_GYOE_END_WAIT (30)						///<!�}�[�N�o����̊ԁ@�t���[���P��
#define EYE_MEET_MOVE_END_WAIT (8)						///<�����ړ���̊ԁ@�t���[���P��

//--------------------------------------------------------------
///	�����ړ������ԍ�
//--------------------------------------------------------------
enum
{
	SEQNO_TRMOVE_INIT = 0,
	SEQNO_TRMOVE_OBJMOVE_WAIT,							///<�����~�҂�
	SEQNO_TRMOVE_JIKIMOVE_WAIT,							///<���@����I���҂�
	SEQNO_TRMOVE_DIR_CHANGE,							///<�����ύX
	SEQNO_TRMOVE_DIR_CHANGE_WAIT,						///<�����ύX�҂�
	SEQNO_TRMOVE_GYOE_SET,								///<!�Z�b�g
	SEQNO_TRMOVE_GYOE_WAIT,								///<!�҂�
	SEQNO_TRMOVE_HIDE_PULLOFF_SET,						///<�B�ꖪ�E���Z�b�g
	SEQNO_TRMOVE_HIDE_PULLOFF_WAIT,						///<�B�ꖪ�I���҂�
	SEQNO_TRMOVE_GYOE_END_WAIT,							///<!�I����҂�
	SEQNO_TRMOVE_MOVE_RANGE_CHECK,						///<�ړ������`�F�b�N
	SEQNO_TRMOVE_MOVE_START,							///<�ړ��J�n
	SEQNO_TRMOVE_MOVE,									///<�ړ���
	SEQNO_TRMOVE_MOVE_END_WAIT,							///<�ړ��I����҂�
	SEQNO_TRMOVE_JIKI_TURN_SET,							///<���@�U������Z�b�g
	SEQNO_TRMOVE_JIKI_TURN,								///<���@�U�����
	SEQNO_TRMOVE_ACMD_END,								///<�A�j���I��
	SEQNO_TRMOVE_END,									///<�I��
};

//--------------------------------------------------------------
//	�f�o�b�O
//--------------------------------------------------------------

//==============================================================================
//	typedef strcut
//==============================================================================
//--------------------------------------------------------------
///	�����q�b�g�i�[
//--------------------------------------------------------------
typedef struct
{
	int range;
	int dir;
	int scr_id;
	int tr_id;
	int tr_type;
	FIELD_OBJ_PTR fldobj;
}EYE_MEET_HITDATA;

//--------------------------------------------------------------
//	�����C�x���g���[�N
//--------------------------------------------------------------
typedef struct
{
	int seq_no;											///<�����ԍ�
	FIELDSYS_WORK *fsys;								///<FIELDSYS_WORK *
	FIELD_OBJ_PTR fldobj;								///<FIELD_OBJ_PTR
	TCB_PTR tcb_eye_meet;								///<TCB_PTR
}EYE_MEET_EVENT_WORK;

#define EYE_MEET_EVENT_WORK_SIZE (sizeof(EYE_MEET_EVENT_WORK)) ///<EYE_MEET_EVENT_WORK�T�C�Y

//--------------------------------------------------------------
//	�����q�b�g�ړ������p���[�N
//--------------------------------------------------------------
typedef struct
{
	int seq_no;											///<�����ԍ�
	int end_flag;										///<�I���t���O
	int dir;											///<�ړ�����
	int range;											///<�ړ�����
	int gyoe_type;										///<!�^�C�v
	int tr_type;										///<�g���[�i�[�^�C�v
	int sisen_no;										///<�����ԍ�
	int count;											///<�ړ��J�E���g
	EOA_PTR gyoe;										///<�M���G�[EOA_PTR
	FIELD_OBJ_PTR fldobj;								///<�ړ����s��FIELD_OBJ_PTR
	PLAYER_STATE_PTR jiki;								///<���@PLAYER_STATE_PTR
}EYE_MEET_MOVE_WORK;

#define EYE_MEET_MOVE_WORK_SIZE (sizeof(EYE_MEET_MOVE_WORK)) ///<EYE_MEET_MOVE_WORK�T�C�Y

//==============================================================================
//	static
//==============================================================================
static int TrainerEyeCheck( FIELDSYS_WORK *fsys, FIELD_OBJ_SYS_PTR fos,
		PLAYER_STATE_PTR jiki, CONST_FIELD_OBJ_PTR nonobj, EYE_MEET_HITDATA *hit );
static void TrainerEyeHitDataSet(
		EYE_MEET_HITDATA *hit, FIELD_OBJ_PTR fldobj, int range, int dir );
static int TrainerEventTypeGet( CONST_FIELD_OBJ_PTR fldobj );

static int TrEyeLangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int *hit_dir );
static int TrEyeLineCheckParam( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki );
static int TrEyeLineCheck(CONST_FIELD_OBJ_PTR fldobj,int dir, int range, int x, int z, int y );
int (* const TrEyeLineCheckTbl[])(CONST_FIELD_OBJ_PTR,int range,int x,int z,int y);

static int TrEyeLineMoveHitCheck( CONST_FIELD_OBJ_PTR fldobj, int dir, int range );
static int FldOBJTrainerIDGet( FIELD_OBJ_PTR fldobj );
static FIELD_OBJ_PTR TrainerPairCheck(
		FIELDSYS_WORK *fsys, FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR tr_obj, int tr_id );

static TCB_PTR TrEyeMeetMoveAddTcb( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe_type, int tr_type, int sisen_no );
static int TrEyeMeetMoveEndCheck( TCB_PTR tcb );
static void TrEyeMeetMoveEnd( TCB_PTR tcb );
static void TrEyeMeetMoveTCB( TCB_PTR tcb, void *wk );
int (* const DATA_EyeMeetMoveTbl[])( EYE_MEET_MOVE_WORK *work );

//==============================================================================
//	�g���[�i�[��������
//==============================================================================
//--------------------------------------------------------------
/**
 * �g���[�i�[�����C�x���g�`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	vs2		�_�u���o�g���\�� TRUE=�\ FALSE=�s��
 * @retval	int		TRUE=�g���[�i�[�����C�x���g����
 */
//--------------------------------------------------------------
int EvTrainerEyeCheck( FIELDSYS_WORK *fsys, BOOL vs2 )
{
	EYE_MEET_HITDATA hit0;
	FIELD_OBJ_SYS_PTR fos = fsys->fldobjsys;
	PLAYER_STATE_PTR player = fsys->player;
	
	if( TrainerEyeCheck(fsys,fos,player,NULL,&hit0) == FALSE ){
		return( FALSE );
	}
	
	if( hit0.tr_type == SCR_EYE_TR_TYPE_SINGLE ){						//�V���O��
		FIELD_OBJ_PTR fldobj;
		EYE_MEET_HITDATA hit1;
		
		EventSet_Script( fsys, SCRID_TRAINER_MOVE_BATTLE, hit0.fldobj ); //�X�N���v�g�N��
		
		if( vs2 == FALSE || TrainerEyeCheck(fsys,fos,player,hit0.fldobj,&hit1) == FALSE ){
			EventSet_TrainerEyeData( fsys, hit0.fldobj,					//�V���O���Z�b�g
				hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_SINGLE, SCR_EYE_TR_0 );
			OS_Printf( "�g���[�i�[�V���O���q�b�g\n" );
			return( TRUE );
		}
		
		EventSet_TrainerEyeData( fsys, hit0.fldobj,
			hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_TAG, SCR_EYE_TR_0 );
		EventSet_TrainerEyeData( fsys, hit1.fldobj,
			hit1.range, hit1.dir, hit1.scr_id, hit1.tr_id,
				SCR_EYE_TR_TYPE_TAG, SCR_EYE_TR_1 );
		
		OS_Printf( "�g���[�i�[�^�b�O�q�b�g�@�_�u��\n" );
		return( TRUE );
	}
	
	if( hit0.tr_type == SCR_EYE_TR_TYPE_DOUBLE ){						//�_�u��
		FIELD_OBJ_PTR fldobj;
		EYE_MEET_HITDATA hit1;
		
		if( vs2 == FALSE ){												//�_�u���s��
			return( FALSE );
		}
		
		fldobj = TrainerPairCheck( fsys, fos, hit0.fldobj, hit0.tr_id );
		TrainerEyeHitDataSet( &hit1, fldobj, hit0.range, hit0.dir );
		
		EventSet_Script( fsys, SCRID_TRAINER_MOVE_BATTLE, hit0.fldobj );//�X�N���v�g�N��
		
		EventSet_TrainerEyeData( fsys, hit0.fldobj,
				hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_DOUBLE, SCR_EYE_TR_0 );
		EventSet_TrainerEyeData( fsys, hit1.fldobj,
				hit1.range, hit1.dir, hit1.scr_id, hit1.tr_id,
				SCR_EYE_TR_TYPE_DOUBLE, SCR_EYE_TR_1 );
		
		OS_Printf( "�g���[�i�[�_�u���q�b�g\n" );
		return( TRUE );
	}
	
	GF_ASSERT( 0 && "EvTrainerEyeCheck() �����^�C�v�s��\n" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	nonobj	�ΏۊO�Ƃ���OBJ NULL=���݂��Ȃ�
 * @param	hit		EYE_MEET_HITDATA *
 * @retval	int		TRUE=�g���[�i�[�����q�b�g
 */
//--------------------------------------------------------------
static int TrainerEyeCheck( FIELDSYS_WORK *fsys, FIELD_OBJ_SYS_PTR fos,
		PLAYER_STATE_PTR jiki, CONST_FIELD_OBJ_PTR nonobj, EYE_MEET_HITDATA *hit )
{
	int i,range,dir;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	fldobj = NULL;
	range = EYE_CHECK_NOHIT;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&i,FLDOBJ_STA_BIT_USE) ){
		if( nonobj == NULL || (nonobj != fldobj) ){
			range = TrEyeLangeCheck( fldobj, jiki, &dir );
		
			if( range != EYE_CHECK_NOHIT ){
				if( CheckEventFlagTrainer(fsys,FldOBJTrainerIDGet(fldobj)) == FALSE ){
					TrainerEyeHitDataSet( hit, fldobj, range, dir );		//���퓬
					return( TRUE );
				}
			}
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����q�b�g���������i�[����
 * @param	hit		EYE_MEET_HITDATA
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	��������
 * @param	dir		�ړ�����
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrainerEyeHitDataSet(
		EYE_MEET_HITDATA *hit, FIELD_OBJ_PTR fldobj, int range, int dir )
{
	hit->range = range;
	hit->dir = dir;
	hit->scr_id = FieldOBJ_EventIDGet( fldobj );
	hit->tr_id = GetTrainerIdByScriptId( hit->scr_id );
	hit->tr_type = CheckTrainer2vs2Type( hit->tr_id );
	hit->fldobj = fldobj;
}

//--------------------------------------------------------------
/**
 * �C�x���g�^�C�v�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		EV_TYPE_TRAINER��
 */
//--------------------------------------------------------------
static int TrainerEventTypeGet( CONST_FIELD_OBJ_PTR fldobj )
{
	int type = FieldOBJ_EventTypeGet( fldobj );
	
	switch( type ){
	case EV_TYPE_TRAINER_KYORO:
	case EV_TYPE_TRAINER_SPIN_STOP_L:
	case EV_TYPE_TRAINER_SPIN_STOP_R:
	case EV_TYPE_TRAINER_SPIN_MOVE_L:
	case EV_TYPE_TRAINER_SPIN_MOVE_R:
		type = EV_TYPE_TRAINER;
		break;
	}
	
	return( type );
}

//==============================================================================
//	�����`�F�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N�@�O���[�o��
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	jiki		PLAYER_STATE_PTR
 * @param	hit_dir		�����q�b�g���̈ړ������BDIR_UP��
 * @retval	int			�����q�b�g���̎��@�܂ł̃O���b�h�����BEYE_CHECK_NOHIT=�G���[
 */
//--------------------------------------------------------------
int EvTrainer_EyeLangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int *hit_dir )
{
	return( TrEyeLangeCheck(fldobj,jiki,hit_dir) );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����͈̓`�F�b�N
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	jiki		PLAYER_STATE_PTR
 * @param	hit_dir		�����q�b�g���̈ړ������BDIR_UP��
 * @retval	int			�����q�b�g���̎��@�܂ł̃O���b�h�����BEYE_CHECK_NOHIT=�G���[
 */
//--------------------------------------------------------------
static int TrEyeLangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int *hit_dir )
{
	int type,range,dir,jx,jz,ret;
	
	type = TrainerEventTypeGet( fldobj );
	
	if( type == EV_TYPE_TRAINER ){
		jx = Player_NowGPosXGet( jiki );
		jz = Player_NowGPosZGet( jiki );
		dir = FieldOBJ_DirDispGet( fldobj );
		range = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_0 );
		
		ret = TrEyeLineCheck( fldobj, dir, range, jx, jz, 0 );
		
		if( ret != EYE_CHECK_NOHIT ){
			if( TrEyeLineMoveHitCheck(fldobj,dir,ret) == FALSE ){
				*hit_dir = dir;
				return( ret );
			}
		}
		
		return( EYE_CHECK_NOHIT );
	}
	
	if( type == EV_TYPE_TRAINER_EYEALL ){						//4����
		jx = Player_NowGPosXGet( jiki );
		jz = Player_NowGPosZGet( jiki );
		range = FieldOBJ_ParamGet( fldobj, FLDOBJ_PARAM_0 );
		
		dir = DIR_UP;
		
		do{
			ret = TrEyeLineCheck( fldobj, dir, range, jx, jz, 0 );
			
			if( ret != EYE_CHECK_NOHIT ){
				if( TrEyeLineMoveHitCheck(fldobj,dir,ret) == FALSE ){
					*hit_dir = dir;
					return( ret );
				}
			}
			
			dir++;
		}while( dir < DIR_4_MAX );
		
		return( EYE_CHECK_NOHIT );
	}
	
	return( EYE_CHECK_NOHIT );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		���������@DIR_UP��
 * @param	range	��������
 * @param	x		���@�O���b�hX
 * @param	z		���@�O���b�hz
 * @param	y		���@����
 * @retval	int		���@�ւ̃O���b�h�����@EYE_CHECK_NOHIT=�q�b�g�Ȃ�
 */
//--------------------------------------------------------------
static int TrEyeLineCheck( CONST_FIELD_OBJ_PTR fldobj, int dir, int range, int x, int z, int y )
{
	return( TrEyeLineCheckTbl[dir](fldobj,range,x,z,y) );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N�@��
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	��������
 * @param	jx		���@�O���b�hX
 * @param	jz		���@�O���b�hz
 * @param	jy		���@����
 * @retval	int		���@�ւ̋����@0=�q�b�g�Ȃ�
 */
//--------------------------------------------------------------
static int TrEyeLineCheck_Up( CONST_FIELD_OBJ_PTR fldobj, int range, int jx, int jz, int jy )
{
	int x,z;
	
	x = FieldOBJ_NowPosGX_Get( fldobj );
	
	if( x == jx ){
		z = FieldOBJ_NowPosGZ_Get( fldobj );
		
		if( jz < z && jz >= (z-range) ){
			return( z - jz );
		}
	}
	
	return( EYE_CHECK_NOHIT );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N�@��
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	��������
 * @param	jx		���@�O���b�hX
 * @param	jz		���@�O���b�hz
 * @param	jy		���@����
 * @retval	int		���@�ւ̋����@0=�q�b�g�Ȃ�
 */
//--------------------------------------------------------------
static int TrEyeLineCheck_Down( CONST_FIELD_OBJ_PTR fldobj, int range, int jx, int jz, int jy )
{
	int x,z;
	
	x = FieldOBJ_NowPosGX_Get( fldobj );
	
	if( x == jx ){
		z = FieldOBJ_NowPosGZ_Get( fldobj );
		
		if( jz > z && jz <= (z+range) ){
			return( jz - z );
		}
	}
	
	return( EYE_CHECK_NOHIT );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N�@��
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	��������
 * @param	jx		���@�O���b�hX
 * @param	jz		���@�O���b�hz
 * @param	jy		���@����
 * @retval	int		���@�ւ̋����@0=�q�b�g�Ȃ�
 */
//--------------------------------------------------------------
static int TrEyeLineCheck_Left( CONST_FIELD_OBJ_PTR fldobj, int range, int jx, int jz, int jy )
{
	int x,z;
	
	z = FieldOBJ_NowPosGZ_Get( fldobj );
	
	if( z == jz ){
		x = FieldOBJ_NowPosGX_Get( fldobj );
		
		if( jx < x && jx >= (x-range) ){
			return( x - jx );
		}
	}
	
	return( EYE_CHECK_NOHIT );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����`�F�b�N�@�E
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	��������
 * @param	jx		���@�O���b�hX
 * @param	jz		���@�O���b�hz
 * @param	jy		���@����
 * @retval	int		���@�ւ̋����@0=�q�b�g�Ȃ�
 */
//--------------------------------------------------------------
static int TrEyeLineCheck_Right( CONST_FIELD_OBJ_PTR fldobj, int range, int jx, int jz, int jy )
{
	int x,z;
	
	z = FieldOBJ_NowPosGZ_Get( fldobj );
	
	if( z == jz ){
		x = FieldOBJ_NowPosGX_Get( fldobj );
		
		if( jx > x && jx <= (x+range) ){
			return( jx - x );
		}
	}
	
	return( EYE_CHECK_NOHIT );
}

//--------------------------------------------------------------
///	�����`�F�b�N�e�[�u��
//--------------------------------------------------------------
static int (* const TrEyeLineCheckTbl[])(CONST_FIELD_OBJ_PTR,int range,int jx,int jz,int jy) =
{
	TrEyeLineCheck_Up,
	TrEyeLineCheck_Down,
	TrEyeLineCheck_Left,
	TrEyeLineCheck_Right,
};

//==============================================================================
//	��������@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �����͈͈ړ�����
 * @param	fldobj		�`�F�b�N�Ώ�FIELD_OBJ_PTR
 * @param	dir			�ړ�����
 * @param	range		�ړ�����
 * @retval	int			TRUE=�ړ��s��
 */
//--------------------------------------------------------------
static int TrEyeLineMoveHitCheck( CONST_FIELD_OBJ_PTR fldobj, int dir, int range )
{
	int i,x,z,y;
	u32 ret;
	
	if( range == 0 ){
		return( TRUE );
	}
	
	x = FieldOBJ_NowPosGX_Get( fldobj );
	z = FieldOBJ_NowPosGZ_Get( fldobj );
	y = FieldOBJ_NowPosGY_Get( fldobj );
	
	x += FieldOBJ_DirAddValueGX( dir );
	z += FieldOBJ_DirAddValueGZ( dir );
	
	for( i = 0; i < (range-1); i++ ){
		ret = FieldOBJ_MoveHitCheckNow( fldobj, x, y, z, dir );
		ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;						//�ړ������𖳎�����
		
		if( ret ){
			return( TRUE );										//�ړ������ȊO�Ńq�b�g
		}
		
		x += FieldOBJ_DirAddValueGX( dir );
		z += FieldOBJ_DirAddValueGZ( dir );
	}
	
	ret = FieldOBJ_MoveHitCheckNow( fldobj, x, y, z, dir );
	ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;							//�ړ������𖳎�����
	
	if( ret == FLDOBJ_MOVE_HIT_BIT_OBJ ){						//OBJ�Փ�(���@)�̂�
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����g���[�i�[ID�擾
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		�g���[�i�[ID
 */
//--------------------------------------------------------------
static int FldOBJTrainerIDGet( FIELD_OBJ_PTR fldobj )
{
	int scr_id;
	
	scr_id = FieldOBJ_EventIDGet( fldobj );
	return( GetTrainerIdByScriptId(scr_id) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ����g���[�i�[ID�擾�@�O���[�o��
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		�g���[�i�[ID
 */
//--------------------------------------------------------------
int EvTrainerFldOBJTrainerIDGet( FIELD_OBJ_PTR fldobj )
{
	return( FldOBJTrainerIDGet(fldobj) );
}

//--------------------------------------------------------------
/**
 * ����̃g���[�i�[ID����������T��
 * @param	fsys	FIELDSYS_WORK
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	tr_obj	������T���Ă���FIELD_OBJ_PTR
 * @param	tr_id	�g���[�i�[ID
 * @retval	fldobj	FIELD_OBJ_PTR
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR TrainerPairCheck(
		FIELDSYS_WORK *fsys, FIELD_OBJ_SYS_PTR fos, FIELD_OBJ_PTR tr_obj, int tr_id )
{
	int i;
	FIELD_OBJ_PTR fldobj;
	
	i = 0;
	
	while( FieldOBJSys_FieldOBJSearch(fos,&fldobj,&i,FLDOBJ_STA_BIT_USE) ){
		if( fldobj != tr_obj ){
			int type = TrainerEventTypeGet( fldobj );
			
			if( type == EV_TYPE_TRAINER || type == EV_TYPE_TRAINER_EYEALL ){
				if( tr_id == FldOBJTrainerIDGet(fldobj) ){
					return( fldobj );
				}
			}
		}
	}
	
	GF_ASSERT( 0 && "TrainerPairCheck() �y�A�s�݁c\n" );
	return( NULL );
}

//==============================================================================
//	�����q�b�g�ɂ��ړ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �����ړ������ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�ړ�����
 * @param	range	�ړ�����
 * @param	gyoe	!�}�[�N����
 * @param	tr_type	�g���[�i�[�^�C�v
 * @param	work_pos �����q�b�g���[�N�v�f�� 0=������ 1=�y�A
 * @retval	tcb		�ړ�����TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR EvTrainerEyeMoveSet( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe, int tr_type, int work_pos )
{
	return( TrEyeMeetMoveAddTcb(fldobj,jiki,dir,range,gyoe,tr_type,work_pos) );
}

//--------------------------------------------------------------
/**
 * �����ړ������I���`�F�b�N
 * @param	tcb		EvTrainerEyeMoveSet()�̖߂�l
 * @retval	int 	TRUE=�I���@FALSE=�܂�
 */
//--------------------------------------------------------------
int EvTrainerEyeMoveEndCheck( TCB_PTR tcb )
{
	GF_ASSERT( tcb != NULL && "EvTrainerEyeMoveEndCheck() tcb = NULL" );
	return( TrEyeMeetMoveEndCheck(tcb) );
}

//--------------------------------------------------------------
/**
 * �����ړ������I��
 * @param	tcb		EvTrainerEyeMoveSet()�̖߂�l
 * @retval	nothing
 */
//--------------------------------------------------------------
void EvTrainerEyeMoveEnd( TCB_PTR tcb )
{
	TrEyeMeetMoveEnd( tcb );
}

//--------------------------------------------------------------
/**
 * �����ړ������ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�ړ�����
 * @param	range	�ړ�����
 * @retval	TCB_PTR	�ړ��������s��TCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR TrEyeMeetMoveAddTcb( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe_type, int tr_type, int sisen_no )
{
	TCB_PTR tcb;
	EYE_MEET_MOVE_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_MOVE_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetMoveAddTcb()���[�N�m�ێ��s" );
	
	memset( work, 0, EYE_MEET_MOVE_WORK_SIZE );
	
	work->dir = dir;
	work->range = range;
	work->gyoe_type = gyoe_type;
	work->tr_type = tr_type;
	work->sisen_no = sisen_no;
	work->fldobj = fldobj;
	work->jiki = jiki;
	
	tcb = TCB_Add( TrEyeMeetMoveTCB, work, EYE_MEET_MOVE_TCB_PRI );
	GF_ASSERT( tcb != NULL && "TrEyeMeetMoveAddTcb()TCB�ǉ����s" );
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * �����ړ������I���`�F�b�N
 * @param	tcb		TrEyeMeetMoveAddTcb()�̖߂�lTCB_PTR
 * @retval	int		TRUE=�I��
 */
//--------------------------------------------------------------
static int TrEyeMeetMoveEndCheck( TCB_PTR tcb )
{
	EYE_MEET_MOVE_WORK *work;
	work = TCB_GetWork( tcb );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * �����ړ������I��
 * @param	tcb		TrEyeMeetMoveAddTcb()�̖߂�lTCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrEyeMeetMoveEnd( TCB_PTR tcb )
{
	EYE_MEET_MOVE_WORK *work;
	
	work = TCB_GetWork( tcb );
	sys_FreeMemory( HEAPID_FIELD, work );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * �����ړ������@TCB
 * @param	tcb		TCB_PTR
 * @param	wk		TCB work
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrEyeMeetMoveTCB( TCB_PTR tcb, void *wk )
{
	EYE_MEET_MOVE_WORK *work;
	
	work = wk;
	
	while( DATA_EyeMeetMoveTbl[work->seq_no](work) == TRUE ){};
}

//--------------------------------------------------------------
/**
 * �����ړ��@������
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_Init( EYE_MEET_MOVE_WORK *work )
{
	FIELD_OBJ_PTR fldobj = work->fldobj;
	
	if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
		FieldOBJ_MovePauseClear( fldobj );
	}
	
	work->seq_no = SEQNO_TRMOVE_OBJMOVE_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@OBJ����I���҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_OBJMoveWait( EYE_MEET_MOVE_WORK *work )
{
	FIELD_OBJ_PTR fldobj = work->fldobj;
	
	if( FieldOBJ_StatusBitCheck_Move(fldobj) == TRUE ){
		return( FALSE );
	}
	
	FieldOBJ_DirDispDrawSet( work->fldobj, work->dir );
	FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );
	
	work->seq_no = SEQNO_TRMOVE_JIKIMOVE_WAIT;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@���@�ړ��I���҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_JikiMoveWait( EYE_MEET_MOVE_WORK *work )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
	
	if( FieldOBJ_AcmdEndCheck(fldobj) == FALSE ){
		return( FALSE );
	}
	
	{
		u32 code = FieldOBJ_MoveCodeGet( work->fldobj );
		OS_Printf( "�g���[�i�[����R�[�h=0x%x\n", code );
		
		switch( code ){
		case MV_HIDE_SNOW:
		case MV_HIDE_SAND:
		case MV_HIDE_GRND:
		case MV_HIDE_KUSA:
			work->seq_no = SEQNO_TRMOVE_HIDE_PULLOFF_SET;
			return( TRUE );
		}
	}
	
	work->seq_no = SEQNO_TRMOVE_DIR_CHANGE;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ���֌�����ς��� 
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_DirChange( EYE_MEET_MOVE_WORK *work )
{
	int code;
	
	if( FieldOBJ_AcmdSetCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	GF_ASSERT( work->dir != DIR_NOT );
	code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_DIR_U );
	FieldOBJ_AcmdSet( work->fldobj, code );
	work->seq_no = SEQNO_TRMOVE_DIR_CHANGE_WAIT;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ���֌�����ς���@�҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_DirChangeWait( EYE_MEET_MOVE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->seq_no = SEQNO_TRMOVE_GYOE_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�т�����}�[�N�o��
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_GyoeSet( EYE_MEET_MOVE_WORK *work )
{
	work->gyoe = FE_FldOBJGyoe_Add( work->fldobj, GYOE_GYOE, FALSE );
	work->seq_no = SEQNO_TRMOVE_GYOE_WAIT;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�т�����}�[�N�\���I���҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_GyoeWait( EYE_MEET_MOVE_WORK *work )
{
	if( FE_Gyoe_EndCheck(work->gyoe) == TRUE ){
		EOA_Delete( work->gyoe );
		work->seq_no = SEQNO_TRMOVE_GYOE_END_WAIT;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�B�ꖪ�E��
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_HidePullOFFSet( EYE_MEET_MOVE_WORK *work )
{
	FieldOBJ_AcmdSet( work->fldobj, AC_HIDE_PULLOFF );
	work->seq_no = SEQNO_TRMOVE_HIDE_PULLOFF_WAIT;
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�B�ꖪ�E���I���҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_HidePullOFFWait( EYE_MEET_MOVE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == TRUE ){
		work->seq_no = SEQNO_TRMOVE_GYOE_END_WAIT;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�т�����}�[�N�\���I����̊�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_GyoeEndWait( EYE_MEET_MOVE_WORK *work )
{
	work->count++;
	
	if( work->count >= EYE_MEET_GYOE_END_WAIT ){
		work->count = 0;
		work->seq_no = SEQNO_TRMOVE_MOVE_RANGE_CHECK;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ������`�F�b�N
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_MoveRangeCheck( EYE_MEET_MOVE_WORK *work )
{
	if( work->range <= 1 ){									//���@�ڂ̑O �ړ�����K�v�Ȃ�
		work->seq_no = SEQNO_TRMOVE_MOVE_END_WAIT;
		return( TRUE );	
	}

	work->seq_no = SEQNO_TRMOVE_MOVE_START;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ��J�n
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_MoveStart( EYE_MEET_MOVE_WORK *work )
{
	int code;

	if( FieldOBJ_AcmdSetCheck(work->fldobj) == TRUE ){
		code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_WALK_U_8F );
		FieldOBJ_AcmdSet( work->fldobj, code );
		work->seq_no = SEQNO_TRMOVE_MOVE;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ���
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_Move( EYE_MEET_MOVE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->range--;											//������炷
	work->seq_no = SEQNO_TRMOVE_MOVE_RANGE_CHECK;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�ړ��I����A���@�̕����֌�������
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_MoveEndWait( EYE_MEET_MOVE_WORK *work )
{
	work->count++;
	
	if( work->count < EYE_MEET_MOVE_END_WAIT ){
		return( FALSE );
	}
	
	work->count = 0;
	work->seq_no = SEQNO_TRMOVE_JIKI_TURN_SET;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@���@��U���������
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_JikiTurnSet( EYE_MEET_MOVE_WORK *work )
{
	int code,turn_dir;
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( work->jiki );
	
	turn_dir = FieldOBJTool_DirRange(
			FieldOBJ_NowPosGX_Get(fldobj), FieldOBJ_NowPosGZ_Get(fldobj),
			FieldOBJ_NowPosGX_Get(work->fldobj), FieldOBJ_NowPosGZ_Get(work->fldobj) );
	
	if( Player_DirGet(work->jiki) != turn_dir &&
		(work->sisen_no == 0 || work->tr_type == SCR_EYE_TR_TYPE_TAG) ){
		if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
			FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
			code = FieldOBJ_AcmdCodeDirChange( turn_dir, AC_DIR_U );
			FieldOBJ_AcmdSet( fldobj, code );
			
			work->seq_no = SEQNO_TRMOVE_JIKI_TURN;
		}
	}else{
		work->seq_no = SEQNO_TRMOVE_ACMD_END;
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@���@�U������I���҂�
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_JikiTurn( EYE_MEET_MOVE_WORK *work )
{
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( work->jiki );
	
	if( FieldOBJ_AcmdEndCheck(fldobj) == FALSE ){
		return( FALSE );
	}
	
	FieldOBJ_AcmdEnd( fldobj );
	work->seq_no = SEQNO_TRMOVE_ACMD_END;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�A�j���I��
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_AcmdEnd( EYE_MEET_MOVE_WORK *work )
{
	FieldOBJ_AcmdEnd( work->fldobj );
//	FieldOBJ_StatusBit_OFF( work->fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );	//�|�[�Y��������
	FieldOBJ_MoveCodeChange( work->fldobj, MV_DMY );
	
	work->seq_no = SEQNO_TRMOVE_END;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�I��
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=�ċA
 */
//--------------------------------------------------------------
static int EyeMeetMove_End( EYE_MEET_MOVE_WORK *work )
{
	work->end_flag = TRUE;
	return( FALSE );
}

//--------------------------------------------------------------
///	�����ړ������e�[�u��
//--------------------------------------------------------------
static int (* const DATA_EyeMeetMoveTbl[])( EYE_MEET_MOVE_WORK *work ) =
{
	EyeMeetMove_Init,
	EyeMeetMove_OBJMoveWait,
	EyeMeetMove_JikiMoveWait,
	EyeMeetMove_DirChange,
	EyeMeetMove_DirChangeWait,
	EyeMeetMove_GyoeSet,
	EyeMeetMove_GyoeWait,
	EyeMeetMove_HidePullOFFSet,
	EyeMeetMove_HidePullOFFWait,
	EyeMeetMove_GyoeEndWait,
	EyeMeetMove_MoveRangeCheck,
	EyeMeetMove_MoveStart,
	EyeMeetMove_Move,
	EyeMeetMove_MoveEndWait,
	EyeMeetMove_JikiTurnSet,
	EyeMeetMove_JikiTurn,
	EyeMeetMove_AcmdEnd,
	EyeMeetMove_End,
};

//==============================================================================
//	�X�N���v�g�R�}���h
//	add nohara
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * �����C�x���g�N�� 
 * @param	fsys		FIELDSYS_WORK
 * @param	fldobj		�Ώۃt�B�[���hOBJ
 * @param	tcb			�����ړ�TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrEyeMeetEventStart( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	EYE_MEET_EVENT_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_EVENT_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetEventStart()���[�N�m�ێ��s" );
	
	memset( work, 0, EYE_MEET_EVENT_WORK_SIZE );
	
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->tcb_eye_meet = tcb;
	
	FieldEvent_Set( fsys, TrEyeMeetEvent, work );
}

//--------------------------------------------------------------
/**
 * �����C�x���g�I��
 * @param	work		EYE_MEET_EVENT_WORK
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrEyeMeetEventEnd( EYE_MEET_EVENT_WORK *work )
{
	sys_FreeMemory( HEAPID_FIELD, work );
}

//--------------------------------------------------------------
/**
 * �����C�x���g
 * @param	ev		GMEVENT_CONTROL	*
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL TrEyeMeetEvent( GMEVENT_CONTROL *ev )
{
	EYE_MEET_EVENT_WORK *work;
	
	work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0:
		if( TrEyeMeetMoveEndCheck(work->tcb_eye_meet) == TRUE ){
			work->seq_no++;
		}
		
		break;
	case 1:
		work->seq_no++;
		break;
	case 2:
		TrEyeMeetMoveEnd( work->tcb_eye_meet );
		TrEyeMeetEventEnd( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[�����ړ�TCB�ǉ�
 * @param	fldobj	�Ώۂ�FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE
 * @param	dir		�ړ�����
 * @param	range	�ړ�����
 * @retval	TCB_PTR	�����ړ�TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR EvCall_TrEyeMeetMoveAddTcb(
		FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int dir, int range )
{
	return( TrEyeMeetMoveAddTcb(fldobj,jiki,dir,range) );
}

//--------------------------------------------------------------
/**
 * �g���[�i�[���������擾
 * @param	fldobj	�Ώ�FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		���������B�q�b�g�Ȃ�=-1
 */
//--------------------------------------------------------------
int EvCall_TrEyeRangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki )
{
	int dir;
	return( TrEyeLangeCheck(fldobj,jiki,&dir) );
}

//--------------------------------------------------------------
/**
 * �����C�x���g�N�� 
 * @param	fsys		FIELDSYS_WORK
 * @param	fldobj		�Ώۃt�B�[���hOBJ
 * @param	tcb			�����ړ�TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void GMEVENT_Call_TrEyeMeetEventStart(
		FIELDSYS_WORK *fsys, GMEVENT_CONTROL * event, FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	EYE_MEET_EVENT_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_EVENT_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetEventStart()���[�N�m�ێ��s" );
	
	memset( work, 0, EYE_MEET_EVENT_WORK_SIZE );
	
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->tcb_eye_meet = tcb;
	
	FieldEvent_Call( event, TrEyeMeetEvent, work );
}
#endif
