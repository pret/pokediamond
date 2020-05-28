//******************************************************************************
/**
 *
 * @file	player_move.c
 * @brief	���@����
 * @author	kagaya
 * @data	05.08.05
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fieldobj.h"
#include "player.h"
#include "map_tool.h"

#include "system/snd_tool.h"

#include "savedata\record.h"

#ifdef PLAYER_DEBUG
#include "field_effect.h"
#endif

#ifdef PLAYER_DEBUG_MOVE
#include "div_map.h"
#endif

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	�f�o�b�O�V���{��
//--------------------------------------------------------------
//----
#ifdef PLAYER_DEBUG
//----

//----
#endif
//----

//--------------------------------------------------------------
///	�ǃq�b�g��p�A�j���R�[�h
//--------------------------------------------------------------
#define JIKI_WALL_HIT_AC_STAY_WALK_U	(AC_STAY_WALK_U_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_D	(AC_STAY_WALK_D_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_L	(AC_STAY_WALK_L_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_R	(AC_STAY_WALK_R_16F)

//--------------------------------------------------------------
///	�U�������p�A�j���R�[�h
//--------------------------------------------------------------
//#define JIKI_TURN_AC_STAY_WALK_U		(AC_STAY_WALK_U_4F)
#define JIKI_TURN_AC_STAY_WALK_U		(AC_STAY_WALK_U_2F)

//--------------------------------------------------------------
///	���s��p�A�j���R�[�h
//--------------------------------------------------------------
#define JIKI_WALK_AC_WALK_U		(AC_WALK_U_8F)
//#define JIKI_WALK_AC_WALK_U		(AC_WALK_U_7F)

//--------------------------------------------------------------
///	�����`�F�b�N�A����V���{��
//--------------------------------------------------------------
enum
{
	UNDER_NOTHING = 0,										///<��������
	UNDER_ICE,												///<�X
	UNDER_SAND,												///<����
	UNDER_TAKEOFF_LEFT,										///<�W�����v��@��
	UNDER_TAKEOFF_RIGHT,									///<�W�����v��@�E
	UNDER_CYCLING_ROAD_DOWN_4,								///<�T�C�N�����O���[�h����
	
	UNDER_MAX,												///<������ލő�
};

//--------------------------------------------------------------
///	�����X�@�X�Ύ���
//--------------------------------------------------------------
enum
{
	ICE_SLOPE_FLAT = 0,										///<����
	ICE_SLOPE_UP,											///<���
	ICE_SLOPE_DOWN,											///<����
};

//--------------------------------------------------------------
///	�ʏ�ړ����
//--------------------------------------------------------------
enum
{
	NORMAL_MOVE_STOP = 0,									///<��~
	NORMAL_MOVE_WALK,										///<�ړ�
	NORMAL_MOVE_TURN,										///<��~
};

//--------------------------------------------------------------
///	���]�Ԉړ���ށ@�R��
//--------------------------------------------------------------
enum
{
	CYCLE3_MOVE_STOP = 0,									///<��~
	CYCLE3_MOVE_WALK,										///<�ړ�
	CYCLE3_MOVE_TURN,										///<��~
	CYCLE3_MOVE_BRAKE,										///<����
};

//--------------------------------------------------------------
///	���]�Ԉړ���ށ@�S��
//--------------------------------------------------------------
enum
{
	CYCLE4_MOVE_STOP = 0,									///<��~
	CYCLE4_MOVE_WALK,										///<�ړ�
	CYCLE4_MOVE_TURN,										///<��~
	CYCLE4_MOVE_BRAKE,										///<����
};

//==============================================================================
//	typedef struc
//==============================================================================
typedef struct
{
	BOOL (*check)(MATR);
	u32 type;
}UNDER_ATTR_CHECK;

//==============================================================================
//	static
//==============================================================================
static int Jiki_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir );
static void Jiki_MoveStartInit( PLAYER_STATE_PTR jiki, int dir, u16 key_trg, u16 key_prs );
static void Jiki_UnderOFFReset( PLAYER_STATE_PTR jiki );
static void Jiki_WalkSEPlay( PLAYER_STATE_PTR jiki );

static int Jiki_UnderControl( PLAYER_STATE_PTR jiki, int dir );
#ifdef PLAYER_DEBUG
static u32 Jiki_UnderControlDEBUG( PLAYER_STATE_PTR jiki, int dir, u16 key_prs );
#endif
static u32 Jiki_UnderCheck( PLAYER_STATE_PTR jiki, int dir );
const UNDER_ATTR_CHECK DATA_Jiki_UnderAttrCheckTbl[];
static int Jiki_UnderMove( PLAYER_STATE_PTR jiki, u32 under, int key_dir );
static int (* const DATA_Jiki_UnderMoveTbl[UNDER_MAX])( PLAYER_STATE_PTR jiki, int key_dir );

static void UnderForceMoveClear( PLAYER_STATE_PTR jiki );
static int UnderIce_SlopeCheck( PLAYER_STATE_PTR jiki, int dir );
static int UnderIce_SlopeSpeedAdd( PLAYER_STATE_PTR jiki, int slope );
static void UnderIce_AcmdSet( PLAYER_STATE_PTR jiki, int dir );

static void Jiki_MoveSet( 
		PLAYER_STATE_PTR jiki, DMC_CONST_PTR dmc, int dir, u16 key_trg, u16 key_prs );

static void Jiki_MoveNormal( PLAYER_STATE_PTR jiki,
	FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs );
static int Jiki_MoveNormalSelectValueSet( PLAYER_STATE_PTR jiki, int dir );
static int Jiki_MoveNormalSelectValue( int type );
static int Jiki_MoveNormalAttrAcmdWalkGet( FIELD_OBJ_PTR fldobj, MATR attr, int ac );
static int Jiki_MoveNormalSelect( PLAYER_STATE_PTR jiki, int dir );
static void Jiki_MoveNormalStop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveNormalWalk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveNormalTurn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );

static void Jiki_MoveCycle( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycleGearChange( PLAYER_STATE_PTR jiki, u16 trg );
extern int Jiki_MoveCycleAcmdCodeGet( PLAYER_STATE_PTR jiki, int dir );
static int Jiki_MoveCycleSpeedUp( PLAYER_STATE_PTR jiki );
static int Jiki_MoveCycleSpeedDown( PLAYER_STATE_PTR jiki );

static void Jiki_MoveCycle3( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs );
static int Jiki_MoveCycle3SelectValueSet( PLAYER_STATE_PTR jiki, int dir );
static int Jiki_MoveCycle3SelectValue( int type );
static int Jiki_MoveCycle3Select( PLAYER_STATE_PTR jiki, int dir );
static void Jiki_MoveCycle3Stop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle3Walk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle3Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle3Brake(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );

static void Jiki_MoveCycle4( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs );
static int Jiki_MoveCycle4SelectValueSet( PLAYER_STATE_PTR jiki, int dir );
static int Jiki_MoveCycle4SelectValue( int tyep );
static int Jiki_MoveCycle4Select( PLAYER_STATE_PTR jiki, int dir );
static void Jiki_MoveCycle4Stop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle4Walk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle4Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs );
static void Jiki_MoveCycle4Brake(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int di, u16 trg, u16 prs );

static u32 Jiki_MoveHitCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );

static int Jiki_MoveHitCheck_Jump( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_MoveHitCheck_Exit( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_MoveHitCheck_TakeOff( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_MoveHitCheck_Water( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_MoveHitCheck_BridgeHV( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_MoveHitCheck_NotCycle( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );

static int Jiki_KeyDirXGet( u16 key_prs );
static int Jiki_KeyDirZGet( u16 key_prs );
static int Jiki_InputKeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs );

static int Jiki_WallHitAcmdCodeCheck( int code );
static void Jiki_WalkCount( PLAYER_STATE_PTR jiki );
static int Jiki_UnderBridgeHVCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir );
static int Jiki_UnderCyclingRoadCheck( PLAYER_STATE_PTR jiki, u32 attr, int dir );

static void Jiki_AcmdSet( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, u32 ac );

//==============================================================================
//	debug
//==============================================================================
#ifdef PLAYER_DEBUG_MOVE
static int DEBUG_Jiki_Move( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs );
#endif

//==============================================================================
//	���@����
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����֐�
 * @param	jiki		PLAYER_STATE_PTR
 * @param	dmc			DMC_PTR
 * @param	dir		�ړ����Ăق��������BDIR_UP���BDIR_NOT=key_trg,key_prs���玩���ŕ�������o��
 * @param	touch		�|�P�b�`�^�b�` TRUE=�G��Ă��� FALSE=�G��Ă��Ȃ�
 * @param	key_trg		�L�[�g���K
 * @param	key_prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveControl(
	PLAYER_STATE_PTR jiki, DMC_CONST_PTR dmc, int dir, u16 key_trg, u16 key_prs, BOOL touch )
{
	if( dir == DIR_NOT ){
		dir = Jiki_InputKeyDirGet( jiki, key_trg, key_prs );
	}
	
	Jiki_MoveCycleGearChange( jiki, key_trg );
	
	if( Jiki_MoveStartCheck(jiki,dir) == FALSE ){
		return;
	}
	
	Jiki_MoveStartInit( jiki, dir, key_trg, key_prs );
	Player_Request( jiki );
	
#ifdef PLAYER_DEBUG
	if( Jiki_UnderControlDEBUG(jiki,dir,key_prs) == TRUE ){
		return;
	}
#else
	if( Jiki_UnderControl(jiki,dir) == TRUE ){
		Player_EventPoketchCancel( jiki );
		return;
	}
#endif
	
	if( Player_FormGet(jiki) == HERO_FORM_NORMAL ){			//�|�P�b�`
		int ret = Jiki_MoveNormalSelectValueSet( jiki, dir );
		
		if( ret != NORMAL_MOVE_STOP ){
			Player_EventPoketchCancel( jiki );
		}else if( touch == TRUE ){
			Player_EventPoketchChange( jiki );
		}
	}
	
	Jiki_MoveSet( jiki, dmc, dir, key_trg, key_prs );
	Jiki_UnderOFFReset( jiki );
	Jiki_WalkSEPlay( jiki );
}

//--------------------------------------------------------------
/**
 * ���@�ړ��J�n�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
int Player_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir )
{
	return( Jiki_MoveStartCheck(jiki,dir) );
}

//--------------------------------------------------------------
/**
 * ���@�ړ��J�n�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
static int Jiki_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir )
{
	int code;
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
		return( TRUE );											//�R�}���h�Z�b�g�\
	}
	
	if( dir == DIR_NOT ){
		return( FALSE );
	}
	
	code = FieldOBJ_AcmdCodeGet( fldobj );
	
	if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){				//�ǃq�b�g�̓L�����Z���\
#if 0
		if( FieldOBJ_MoveHitCheckDir(fldobj,dir) != FLDOBJ_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
		
		return( TRUE );
#else
		u32 ret = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( ret == JIKI_MOVE_HIT_BIT_NON ){
			return( TRUE );
		}
		
		if( ret == JIKI_MOVE_HIT_BIT_WATER && Player_FormGet(jiki) == HERO_FORM_SWIM ){
			return( TRUE );		//�O�����g���ok
		}
			
		return( FALSE );
#endif		
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����J�n���ɖ��񏉊����������
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�ړ�������� DIR_UP��
 * @param	key_trg	�L�[�g���K
 * @param	key_prs	�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveStartInit( PLAYER_STATE_PTR jiki, int dir, u16 key_trg, u16 key_prs )
{
	Player_InputKeyDirSet( jiki,								//�ړ�����ۂ̓��̓L�[���Z�b�g
			Jiki_KeyDirXGet(key_prs), Jiki_KeyDirZGet(key_prs) );
	
	Player_MoveBitSet_StepOFF( jiki );
}

//--------------------------------------------------------------
/**
 * �ړ��ɂ�鑫����������
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_UnderOFFReset( PLAYER_STATE_PTR jiki )
{
	if( Player_MoveBitCheck_Step(jiki) == TRUE &&
		Player_MoveValueGet(jiki) == OBJ_MOVE_VALUE_WALK ){
		Player_MoveBitSet_UnderOFF( jiki, FALSE );
		
		if( Player_MoveBitCheck_DeepSwampOFF(jiki) == TRUE ){
			Player_MoveBitSet_DeepSwampOFF( jiki, FALSE );
			FieldOBJ_StatusBitSet_AttrOffsOFF( Player_FieldOBJGet(jiki), FALSE );
		}
	}
}

//--------------------------------------------------------------
/**
 * �ړ��ɂ��SE�Đ�
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_WalkSEPlay( PLAYER_STATE_PTR jiki )
{
	if( Player_MoveValueGet(jiki) == OBJ_MOVE_VALUE_WALK ){
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		MATR next,now = FieldOBJ_NowMapAttrGet( fldobj );
		
		{
			int ac = FieldOBJ_AcmdCodeGet( fldobj );
			int dir = FieldOBJ_AcmdCodeDirGet( ac );
			
			if( dir == DIR_NOT ){
				next = now;
			}else{
				next = FieldOBJ_NextDirAttrGet( fldobj, dir );
			}
		}
		
		if( FieldOBJ_MapAttrKindCheck_Snow(fldobj,now) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_YUKIASHI );
		}
		
		if( MATR_IsPoolCheck(now) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_FOOT3_0 );
		}
		
		if( MATR_IsShoal(now) == TRUE ){
			Snd_SePlay( SEQ_SE_DP_FOOT3_1 );
		}
		
		if( MATR_IsSand(now) == TRUE ){
//			Snd_SePlay( SE_SUNA );
		}
		
		if( MATR_IsSwamp(now) == TRUE && MATR_IsSwampDeep(now) != TRUE ){
			Snd_SePlay( SE_SHALLOW_MARSH_WALK );
		}
		
#if 0	//�Փˉ��Əd�Ȃ����ہA�Փˉ����ڗ����Ȃ��Ȃ��Ă��܂�
		if( MATR_IsLongGrass(now) == TRUE || MATR_IsLongGrass(next) == TRUE ){
			Snd_SePlay( SE_LONG_GRASS_WALK );
		}
#else
		{
			int code = FieldOBJ_AcmdCodeGet( fldobj );
			
			if( Jiki_WallHitAcmdCodeCheck(code) == FALSE ){
				if( MATR_IsLongGrass(now) == TRUE || MATR_IsLongGrass(next) == TRUE ){
					Snd_SePlay( SE_LONG_GRASS_WALK );
				}
			}
		}		
#endif
	}
}

#if 0
		int ac = Player_AcmdCodeGet( jiki );
		u32 foot = Player_SEWalkLRNumGet( jiki );
			
		switch( ac ){
		case AC_DASH_U_4F:
		case AC_DASH_D_4F:
		case AC_DASH_L_4F:
		case AC_DASH_R_4F:
			{
				if( MATR_IsGrass(attr) == TRUE ){
					if( foot == 0 ){ Snd_SePlay( SEQ_SE_DP_FOOT1_0); }
					else{ Snd_SePlay( SEQ_SE_DP_FOOT1_1 ); }
				}else if( MATR_IsLongGrass(attr) == TRUE ){
					if( foot == 0 ){ Snd_SePlay( SEQ_SE_DP_FOOT4_0); }
					else{ Snd_SePlay( SEQ_SE_DP_FOOT4_1 ); }
				}else if( MATR_IsSand(attr) == TRUE ){ 
					if( foot == 0 ){ Snd_SePlay( SEQ_SE_DP_FOOT2_0); }
					else{ Snd_SePlay( SEQ_SE_DP_FOOT2_1 ); }
				}else if( MATR_IsWater(attr) == TRUE ){
					if( foot == 0 ){ Snd_SePlay( SEQ_SE_DP_FOOT3_0); }
					else{ Snd_SePlay( SEQ_SE_DP_FOOT3_1 ); }
				}else{
					if( foot == 0 ){ Snd_SePlay( SEQ_SE_DP_FOOT0_0); }
					else{ Snd_SePlay( SEQ_SE_DP_FOOT0_1 ); }
				}
				
				Player_SEWalkLRNumInc( jiki );
			}
#endif

//==============================================================================
//	���@�@�X�e�[�^�X
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�̓���󋵂��X�V�B
 * �X�V���ꂽ����Player_MoveStateGet()�Ŏ擾�B
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveStateUpdate( PLAYER_STATE_PTR jiki )
{
	int val,state,code;
	CONST_FIELD_OBJ_PTR fldobj;
	
	val = Player_MoveValueGet( jiki );
	state = Player_MoveStateGet( jiki );
	fldobj = Player_FieldOBJGet( jiki );
	
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
	
	{															//�����ړ�
		u32 under = Jiki_UnderCheck( jiki, DIR_NOT );
		if( under != UNDER_NOTHING && under != UNDER_CYCLING_ROAD_DOWN_4 ){
			Player_MoveStateSet( jiki, OBJ_MOVE_STATE_ON );
			return;
		}
	}
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){				//����^������
		switch( val ){
		case OBJ_MOVE_VALUE_STOP:
			break;
		case OBJ_MOVE_VALUE_WALK:
			code = FieldOBJ_AcmdCodeGet( fldobj );
			
			if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){
				break;
			}
			
			if( state == OBJ_MOVE_STATE_OFF || state == OBJ_MOVE_STATE_END ){
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_START );
			}else{
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_ON );
			}
			break;
		case OBJ_MOVE_VALUE_TURN:
			Player_MoveStateSet( jiki, OBJ_MOVE_STATE_ON );
			break;
		}
		
		return;
	}
	
	if( FieldOBJ_AcmdEndCheck(fldobj) == TRUE ){				//����I��
		switch( val ){
		case OBJ_MOVE_VALUE_STOP:
			break;
		case OBJ_MOVE_VALUE_WALK:
			switch( state ){
			case OBJ_MOVE_STATE_OFF:
				break;
			case OBJ_MOVE_STATE_END:
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
				break;
			default:
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_END );
			}
			
			break;
		case OBJ_MOVE_VALUE_TURN:
			switch( state ){
			case OBJ_MOVE_STATE_OFF:
				break;
			case OBJ_MOVE_STATE_END:
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
				break;
			default:
				Player_MoveStateSet( jiki, OBJ_MOVE_STATE_END );
			}
			
			break;
		}
		
		return;
	}
}

//--------------------------------------------------------------
/**
 * ���@�̓���󋵂��N���A
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveStateClear( PLAYER_STATE_PTR jiki )
{
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
	Player_MoveSpeedClear( jiki );
}

//--------------------------------------------------------------
/**
 * ���@���십����~�\�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�\�BFALSE=�s��
 */
//--------------------------------------------------------------
int Player_MoveForceStopCheck( PLAYER_STATE_PTR jiki )
{
	int val,state,code;
	CONST_FIELD_OBJ_PTR fldobj;
	
	val = Player_MoveValueGet( jiki );
	state = Player_MoveStateGet( jiki );
	
	if( val == OBJ_MOVE_VALUE_STOP ){
		return( TRUE );
	}
	
	if( val == OBJ_MOVE_VALUE_TURN ){
		return( TRUE );
	}
	
	if( val == OBJ_MOVE_VALUE_WALK ){
		if( state == OBJ_MOVE_STATE_OFF || state == OBJ_MOVE_STATE_END ){
			return( TRUE );
		}
		
		fldobj = Player_FieldOBJGet( jiki );
		
		if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
			return( TRUE );
		}
		
		code = FieldOBJ_AcmdCodeGet( fldobj );
		
		if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���@���십����~
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		������������BDIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_MoveForceStop( PLAYER_STATE_PTR jiki, int dir )
{
	FIELD_OBJ_PTR fldobj;
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
	
	fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_GPosUpdate( fldobj );
	
	FieldOBJ_AcmdFree( fldobj );
	FieldOBJ_AcmdSet( fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_DIR_U) );
}

#if 0
void Player_MoveForceStop( PLAYER_STATE_PTR jiki, int dir )
{
	FIELD_OBJ_PTR fldobj;
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	Player_MoveStateSet( jiki, OBJ_MOVE_STATE_OFF );
	
	fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DrawStatusSet( fldobj, DRAW_STA_STOP );
	FieldOBJ_GPosUpdate( fldobj );
	
//	FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_ACMD|FLDOBJ_STA_BIT_ACMD_END );
}
#endif

//==============================================================================
//	��������
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@��������
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕��� DIR_UP��
 * @retval	int		TRUE=��������ɂ��ړ�
 */
//--------------------------------------------------------------
static int Jiki_UnderControl( PLAYER_STATE_PTR jiki, int dir )
{
	u32 ret = Jiki_UnderCheck( jiki, dir );
	ret = Jiki_UnderMove( jiki, ret, dir );
	
	return( ret );
}

#ifdef PLAYER_DEBUG
static u32 Jiki_UnderControlDEBUG( PLAYER_STATE_PTR jiki, int dir, u16 key_prs )
{
	if( (key_prs & DEBUG_WALK_PAD) == 0 ){
		return( Jiki_UnderControl(jiki,dir) );
	}
	
	UnderForceMoveClear( jiki );
	Player_MoveBitSet_UnderOFF( jiki, TRUE );
	return( FALSE );
}
#endif

//==============================================================================
//	�����`�F�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�����`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		UNDER_NOTHING��
 */
//--------------------------------------------------------------
static u32 Jiki_UnderCheck( PLAYER_STATE_PTR jiki, int dir )
{
	int i = UNDER_NOTHING;
	u32 attr = FieldOBJ_NowMapAttrGet( Player_FieldOBJGet(jiki) );
	
	if( Jiki_UnderCyclingRoadCheck(jiki,attr,dir) == TRUE ){
		return( UNDER_CYCLING_ROAD_DOWN_4 );
	}
	
	if( Player_MoveBitCheck_UnderOFF(jiki) == TRUE ){
		return( UNDER_NOTHING );
	}
	
	do{
		if( DATA_Jiki_UnderAttrCheckTbl[i].check(attr) == TRUE ){
			return( DATA_Jiki_UnderAttrCheckTbl[i].type );
		}
		
		i++;
	}while( DATA_Jiki_UnderAttrCheckTbl[i].check != NULL );
	
	return( UNDER_NOTHING );
}

//--------------------------------------------------------------
///	�����`�F�b�N�e�[�u���@UNDER_MAX�̕��тɈ�v
//--------------------------------------------------------------
static const UNDER_ATTR_CHECK DATA_Jiki_UnderAttrCheckTbl[] =
{
	{ MATR_IsIce,			UNDER_ICE },
	{ MATR_IsShiftingSand,	UNDER_SAND },
	{ MATR_IsTakeOffLeft,	UNDER_TAKEOFF_LEFT },
	{ MATR_IsTakeOffRight,	UNDER_TAKEOFF_RIGHT },
	
	{ NULL, UNDER_MAX },	//�I�[
};

//==============================================================================
//	�����ړ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �����ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	under	UNDER_NOTHING��
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A��
 */
//--------------------------------------------------------------
static int Jiki_UnderMove( PLAYER_STATE_PTR jiki, u32 under, int key_dir )
{
	if( DATA_Jiki_UnderMoveTbl[under](jiki,key_dir) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�������� UNDER_NOTHING
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_Nothing( PLAYER_STATE_PTR jiki, int key_dir )
{
	UnderForceMoveClear( jiki );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�X UNDER_ICE
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_Ice( PLAYER_STATE_PTR jiki, int key_dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
//	int slope,dir = FieldOBJ_DirDispGet( fldobj );				//��Q���A�U������ւ̑Ή�����
	int dir = FieldOBJ_DirMoveGet( fldobj );
	int slope = UnderIce_SlopeCheck( jiki, dir );
	u32 hit = Player_MoveHitCheck( jiki, fldobj, dir );
	
	Player_MoveBitSet_Force( jiki, TRUE );
	
	if( hit != JIKI_MOVE_HIT_BIT_NON ){							//��Q��
		UnderForceMoveClear( jiki );
		
		if( slope != ICE_SLOPE_UP ){
			Player_MoveBitSet_UnderOFF( jiki, TRUE );
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
			return( FALSE );
		}
		
		dir = FieldOBJTool_DirFlip( dir );
		hit = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( hit != JIKI_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
		
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
		Player_MoveBitSet_UnderOFF( jiki, TRUE );				//���藎����A��~
		Player_MoveBitSet_Force( jiki, TRUE );					//�ēx�Z�b�g
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
		
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		return( TRUE );
	}
	
	if( UnderIce_SlopeSpeedAdd(jiki,slope) == FALSE ){			//���x�s���ō�z���s��
		UnderForceMoveClear( jiki );
		
		dir = FieldOBJTool_DirFlip( dir );
		hit = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( hit != JIKI_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
		
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
		Player_MoveBitSet_UnderOFF( jiki, TRUE );				//���藎����A��~
		Player_MoveBitSet_Force( jiki, TRUE );					//�ēx�Z�b�g
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
	}else{
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		UnderIce_AcmdSet( jiki, dir );
	}
	
//	Snd_SePlay( SE_KOORI_FLOOR );
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@���� UNDER_ICE
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_Sand( PLAYER_STATE_PTR jiki, int key_dir )
{
	u32 ret;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int dir = FieldOBJ_DirMoveGet( fldobj );
	
	Snd_SePlay( SE_DRIFT_SAND );
	
	if( dir == DIR_UP ){
		if( Player_FormGet(jiki) == HERO_FORM_CYCLE &&			//����
			Player_MoveSpeedGet(jiki) >= JIKI_SPEED_3 ){
			
			if( key_dir == DIR_UP ){
				Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_D_2F) );
				Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
				return( TRUE );
			}
		}
	
		dir = FieldOBJTool_DirFlip( dir );
		ret = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( ret != JIKI_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
		
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
		Player_MoveSpeedClear( jiki );
		Player_MoveBitSet_Force( jiki, TRUE );					//�ēx�Z�b�g
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveBitSet_SandFloatSet( jiki, TRUE );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
		return( TRUE );
	}else if( dir == DIR_DOWN ){								//����
		if( Player_MoveBitCheck_SandFloat(jiki) == FALSE ){
			Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_D_2F) );
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
			
			if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
				Player_MoveSpeedSet( jiki, JIKI_SPEED_3 );
			}
			
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
			return( TRUE );
		}else{
			FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
			Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
			Player_MoveBitSet_Force( jiki, TRUE );					//�ēx�Z�b�g
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
			Player_MoveBitSet_SandFloatSet( jiki, TRUE );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
			return( TRUE );
		}
	}
	
	OS_Printf( "���E�����ő�������\n" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�W�����v��@���i��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_TakeOFFLeft( PLAYER_STATE_PTR jiki, int key_dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int dir = FieldOBJ_DirMoveGet( fldobj );
	
	if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
		Snd_SePlay( SE_BICYCLE_JUMP3 );
		Jiki_AcmdSet( jiki, fldobj, AC_JUMPHI_R_3G_32F );
	}else{
		Jiki_AcmdSet( jiki, fldobj, AC_JUMPHI_R_1G_16F );
	}
	
	Player_MoveBitSet_Force( jiki, TRUE );
	Player_MoveBitSet_ForceSaveSpeed( jiki, TRUE );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�W�����v��@�E�i��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_TakeOFFRight( PLAYER_STATE_PTR jiki, int key_dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int dir = FieldOBJ_DirMoveGet( fldobj );
	
	if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
		Snd_SePlay( SE_BICYCLE_JUMP3 );
		Jiki_AcmdSet( jiki, fldobj, AC_JUMPHI_L_3G_32F );
	}else{
		Jiki_AcmdSet( jiki, fldobj, AC_JUMPHI_L_1G_16F );
	}
	
	Player_MoveBitSet_Force( jiki, TRUE );
	Player_MoveBitSet_ForceSaveSpeed( jiki, TRUE );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����ړ��@�T�C�N�����O���[�h����
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	�L�[���͕���
 * @retval	int		TRUE=�����ړ��A���@FALSE=�����ړ�����
 */
//--------------------------------------------------------------
static int UnderMove_CyclingRoadDown4( PLAYER_STATE_PTR jiki, int key_dir )
{
	int dir = DIR_DOWN;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	u32 ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( ret == JIKI_MOVE_HIT_BIT_NON ){
#if 1	//���K
//		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_2F) );
//		Player_MoveBitSet_Force( jiki, TRUE ); //�T�C�N�����O���[�h�����ړ��͒ʏ�ړ�
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveSpeedSet( jiki, JIKI_SPEED_CYCLE4_TOP );
#else	//�T�C�N�����O����A�����ړ��ɂ��s�����
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_2F) );
		Player_MoveBitSet_Force( jiki, TRUE );
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveSpeedSet( jiki, JIKI_SPEED_CYCLE4_TOP );
#endif
		return( TRUE );
	}else{
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_DIR_D) );
		Player_MoveSpeedClear( jiki );
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
		Player_MoveBitSet_CycleBrake( jiki, FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
///	�����ړ��e�[�u�� UNDER_MAX�̕��тɈ�v
//--------------------------------------------------------------
static int (* const DATA_Jiki_UnderMoveTbl[UNDER_MAX])( PLAYER_STATE_PTR jiki, int key_dir ) =
{
	UnderMove_Nothing,	//UNDER_NOTHING
	UnderMove_Ice,		//UNDER_ICE
	UnderMove_Sand,		//UNDER_SAND
	UnderMove_TakeOFFLeft,	//UNDE_TAKEOFF_LEFT
	UnderMove_TakeOFFRight,	//UNDE_TAKEOFF_RIGHT
	UnderMove_CyclingRoadDown4,	//UNDER_CYCLING_ROAD_DOWN_4
};

//==============================================================================
//	�����@�����@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �����ړ������
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void UnderForceMoveClear( PLAYER_STATE_PTR jiki )
{
	if( Player_MoveBitCheck_Force(jiki) == TRUE ){
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		
		if( Player_MoveBitCheck_ForceSaveSpeed(jiki) == FALSE ){
			Player_MoveSpeedClear( jiki );
		}
		
		Player_MoveBitSet_Force( jiki, FALSE );
		Player_MoveBitSet_ForceSaveSpeed( jiki, FALSE );
		Player_MoveBitSet_SandFloatSet( jiki, FALSE );
	}
}

//--------------------------------------------------------------
/**
 * �X�@�X�΃`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�ړ��������
 * @retval	int		ICE_SLOPE_FLAT��
 */
//--------------------------------------------------------------
static int UnderIce_SlopeCheck( PLAYER_STATE_PTR jiki, int dir )
{
	int ret;
	VecFx32 now,next;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	
	FieldOBJ_VecPosGet( fldobj, &now );
	next = now;
	
	FieldOBJTool_VecPosDirAdd( dir, &next, GRID_HALF_FX32 / 2 );	//�ړ��������Ԓn�_��
	ret = FieldOBJTool_GetHeight( fsys, &next );
	
	if( ret == FALSE || now.y == next.y ){
		return( ICE_SLOPE_FLAT );
	}
	
	if( now.y > next.y ){
		return( ICE_SLOPE_DOWN );
	}
	
	return( ICE_SLOPE_UP );
}

//--------------------------------------------------------------
/**
 * ���݂̑��x�ƌX�΂̉e��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	slope	ICE_SLOPE_FLAT��
 * @retval	int		TRUE=�ړ��@FALSE=�ړ��s��
 */
//--------------------------------------------------------------
static int UnderIce_SlopeSpeedAdd( PLAYER_STATE_PTR jiki, int slope )
{
	int speed = Player_MoveSpeedGet( jiki );
	
	if( slope == ICE_SLOPE_UP ){								//���
		speed--;
		
		if( speed < JIKI_SPEED_0 ){
			return( FALSE );
		}
	}else if( slope == ICE_SLOPE_DOWN ){						//����
		speed++;
		
		if( speed > JIKI_SPEED_3 ){
			speed = JIKI_SPEED_3;
		}
	}
	
	Player_MoveSpeedSet( jiki, speed );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * ���݂̑��x�ɂ��킹���A�j���R�}���h�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void UnderIce_AcmdSet( PLAYER_STATE_PTR jiki, int dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int code = AC_WALK_U_4F;
	int speed = Player_MoveSpeedGet( jiki );
	
	switch( speed ){
	case JIKI_SPEED_1: code = AC_WALK_U_3F; break;
	case JIKI_SPEED_2: code = AC_WALK_U_2F; break;
	case JIKI_SPEED_3: code = AC_WALK_U_2F; break;
	}
	
	code = FieldOBJ_AcmdCodeDirChange( dir, code );
	Jiki_AcmdSet( jiki, fldobj, code );
}

//==============================================================================
//	���@����
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@����
 * @param	jiki		PLAYER_STATE_PTR
 * @param	dmc			DMC_PTR
 * @param	dir			�ړ���������BDIR_UP��
 * @param	key_trg		�L�[�g���K
 * @param	key_prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveSet( 
		PLAYER_STATE_PTR jiki, DMC_CONST_PTR dmc, int dir, u16 key_trg, u16 key_prs )
{
	int form = Player_FormGet( jiki );
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	switch( form ){
	case HERO_FORM_NORMAL:
	case HERO_FORM_SWIM:
		Jiki_MoveNormal( jiki, fldobj, dmc, dir, key_trg, key_prs );
		break;
	case HERO_FORM_CYCLE:
		Jiki_MoveCycle( jiki, fldobj, dmc, dir, key_trg, key_prs );
		break;
	default:
		GF_ASSERT( 0 && "Jiki_MoveSet() �s���ȃt�H�[��" );
		break;
	}
}

//==============================================================================
//	�ʏ�ړ�
//==============================================================================
//--------------------------------------------------------------
/**
 * �ʏ�ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveNormal( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs )
{
	int ret;
	
#ifdef PLAYER_DEBUG_MOVE
	if( DEBUG_Jiki_Move(jiki,fldobj,dmc,dir,trg,prs) == TRUE ){
		return;
	}
#endif
	
	ret = Jiki_MoveNormalSelectValueSet( jiki, dir );
	
	switch( ret ){
	case NORMAL_MOVE_STOP:
		Jiki_MoveNormalStop( jiki, fldobj, dir, trg, prs );
		break;
	case NORMAL_MOVE_WALK:
		Jiki_MoveNormalWalk( jiki, fldobj, dir, trg, prs );
		break;
	case NORMAL_MOVE_TURN:
		Jiki_MoveNormalTurn( jiki, fldobj, dir, trg, prs );
		break;
	}
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�ړ��I���Ə�ԃZ�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕����BDIR_UP��
 * @retval	int		NORMAL_MOVE_STOP��
 */
//--------------------------------------------------------------
static int Jiki_MoveNormalSelectValueSet( PLAYER_STATE_PTR jiki, int dir )
{
	int sel = Jiki_MoveNormalSelect( jiki, dir );
	int val = Jiki_MoveNormalSelectValue( sel );
	
	Player_MoveValueSet( jiki, val );
	return( sel );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�ړ��I��->��Ԃ�
 * @param	type	NORMAL_MOVE_STOP��
 * @retval	int		OBJ_MOVE_VALUE_STOP��
 */
//--------------------------------------------------------------
static int Jiki_MoveNormalSelectValue( int type )
{
	switch( type ){
	case NORMAL_MOVE_STOP:	return( OBJ_MOVE_VALUE_STOP );
	case NORMAL_MOVE_WALK:	return( OBJ_MOVE_VALUE_WALK );
	case NORMAL_MOVE_TURN:	return( OBJ_MOVE_VALUE_TURN );
	}
	
	GF_ASSERT( 0 && "Jiki_MoveNormalSelectValue()�ُ�Ȓl" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�A�g���r���[�g�ɂ��ړ��A�j���[�V�����R�[�h�I��
 * @param	attr	�A�g���r���[�g
 * @param	ac		�{�����s����A�j���[�V�����R�[�h
 * @retval	int		�A�j���[�V�����R�[�h
 */
//--------------------------------------------------------------
static int Jiki_MoveNormalAttrAcmdWalkGet( FIELD_OBJ_PTR fldobj, MATR attr, int ac )
{
	if( MATR_IsSnowDeepMost(attr) == TRUE ){
		return( AC_WALK_U_32F );
	}
	
	if( MATR_IsSnowDeep(attr) == TRUE ){
		return( AC_WALK_U_16F );
	}
	
	if( MATR_IsShallowSnow(attr) == TRUE ){
		return( AC_WALK_U_8F );
	}
/*	
	if( FieldOBJ_MapAttrKindCheck_Snow(fldobj,attr) ){
		return( ac );
	}
*/	
	return( ac );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�ړ��I��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕����BDIR_UP��
 * @retval	int		NORMAL_MOVE_STOP��
 */
//--------------------------------------------------------------
static int Jiki_MoveNormalSelect( PLAYER_STATE_PTR jiki, int dir )
{
	int m_dir;
	
	if( dir == DIR_NOT ){
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
		return( NORMAL_MOVE_STOP );
	}
	
	m_dir = Player_DirGet( jiki );
	
	if( m_dir != dir && Player_MoveValueGet(jiki) != OBJ_MOVE_VALUE_WALK ){
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_TURN );
		return( NORMAL_MOVE_TURN );
	}
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
	return( NORMAL_MOVE_WALK );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@��~
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveNormalStop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	int code;
	
	code = FieldOBJ_AcmdCodeDirChange( FieldOBJ_DirDispGet(fldobj), AC_DIR_U );
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveNormalWalk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	u32 ret;
	int code;
	
	ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( Player_FormGet(jiki) != HERO_FORM_SWIM ){
		if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
			code = AC_JUMP_U_2G_16F;
		}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
			code = JIKI_WALL_HIT_AC_STAY_WALK_U;
		
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );						//�ǃq�b�g���͋���
		}else{	
			code = JIKI_WALK_AC_WALK_U;
			
			{
				PLAYER_SAVE_DATA *save = Player_SaveDataPtrGet( jiki );
				
				if( Player_SaveDataDashCheck(save) == TRUE ){
					if( Player_KeyDashCheck(jiki,prs) == TRUE ){
						code = AC_DASH_U_4F;
					}
				}
			}
			
			code = Jiki_MoveNormalAttrAcmdWalkGet(
					fldobj, FieldOBJ_NowMapAttrGet(fldobj), code );
			Jiki_WalkCount( jiki );
			Player_MoveBitSet_StepON( jiki );
		}
	}else{
		if( ret == JIKI_MOVE_HIT_BIT_NON || ret == JIKI_MOVE_HIT_BIT_WATER ){
			code = JIKI_WALK_AC_WALK_U;
			code = Jiki_MoveNormalAttrAcmdWalkGet(
					fldobj, FieldOBJ_NowMapAttrGet(fldobj), code );
			Jiki_WalkCount( jiki );
			Player_MoveBitSet_StepON( jiki );
		}else{	
			code = JIKI_WALL_HIT_AC_STAY_WALK_U;
		
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );						//�ǃq�b�g���͋���
		}
	}
	
	code = FieldOBJ_AcmdCodeDirChange( dir, code );
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * �ʏ�ړ��@�U�����
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveNormalTurn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	int code;
	
	code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
	Jiki_AcmdSet( jiki, fldobj, code );
	FieldOBJ_DirMoveSet( fldobj, dir );							//������
}

//==============================================================================
//	���]�Ԉړ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ���]�Ԉړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs )
{
	int ret;
	
#ifdef PLAYER_DEBUG_MOVE
	if( DEBUG_Jiki_Move(jiki,fldobj,dmc,dir,trg,prs) == TRUE ){
		return;
	}
#endif
	
	if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
		Jiki_MoveCycle4( jiki, fldobj, dmc, dir, trg, prs );
	}else{
		Jiki_MoveCycle3( jiki, fldobj, dmc, dir, trg, prs );
	}
}

//--------------------------------------------------------------
/**
 * �R���@�S���̐؂�ւ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		�L�[�g���K
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycleGearChange( PLAYER_STATE_PTR jiki, u16 trg )
{
	if( Player_FormGet(jiki) != HERO_FORM_CYCLE ){
		return;
	}
	
	if( (trg & JIKI_GEAR_CHG_BUTTON) ){
		int gear = GEAR_4;
		
		if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){			//���݂S��
			gear = GEAR_3;
#if 0		
			if( Player_MoveSpeedGet(jiki) >= JIKI_SPEED_BRAKE_ON ){	//�u���[�L�J�n��?
				Player_MoveBitSet_CycleBrake( jiki, TRUE );
			}else{
				Player_MoveBitSet_CycleBrake( jiki, FALSE );
			}
#endif
		}
		
		Player_SaveDataGetGearSet( jiki, gear );
		
		if( gear == GEAR_3 ){
			Snd_SePlay( SE_BICYCLE_GEAR2 );
		}else{
			Snd_SePlay( SE_BICYCLE_GEAR );
		}
	}
}

//--------------------------------------------------------------
/**
 * ���x����A�j���[�V�����R�[�h
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		����
 * @retval	int		AC_WALK_U_4F��
 */
//--------------------------------------------------------------
int Jiki_MoveCycleAcmdCodeGet( PLAYER_STATE_PTR jiki, int dir )
{
	int code;
	
	code = AC_WALK_U_6F;
	
	switch( Player_MoveSpeedGet(jiki) ){
	case JIKI_SPEED_1: code = AC_WALK_U_4F; break;
	case JIKI_SPEED_2: code = AC_WALK_U_3F; break;
	case JIKI_SPEED_3: code = AC_WALK_U_2F; break;
	}
	
	code = FieldOBJ_AcmdCodeDirChange( dir, code );
	return( code );
}

//--------------------------------------------------------------
/**
 * ����
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�ō���
 */
//--------------------------------------------------------------
static int Jiki_MoveCycleSpeedUp( PLAYER_STATE_PTR jiki )
{
	int speed = Player_MoveSpeedAdd( jiki, JIKI_SPEED_VALUE_1, JIKI_SPEED_CYCLE4_TOP );
	
	if( Player_MoveBitCheck_CycleBrake(jiki) == FALSE ){		//�u���[�L����
		if( speed >= JIKI_SPEED_BRAKE_ON ){
			Player_MoveBitSet_CycleBrake( jiki, TRUE );
		}
	}
	
	if( speed == JIKI_SPEED_CYCLE4_TOP ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ����
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		���x������
 */
//--------------------------------------------------------------
static int Jiki_MoveCycleSpeedDown( PLAYER_STATE_PTR jiki )
{
	int flag = TRUE;
	int speed = Player_MoveSpeedGet( jiki );
	
	speed--;
	
	if( speed < 0 ){
		speed = 0;
		flag = FALSE;
	}
	
	Player_MoveSpeedSet( jiki, speed );
	
	if( Player_MoveBitCheck_CycleBrake(jiki) == TRUE ){
		if( speed == 0 ){
			Player_MoveBitSet_CycleBrake( jiki, FALSE );
		}
	}
	
	return( flag );
}

//==============================================================================
//	���]�Ԉړ��@�R��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���]�Ԉړ��@�R��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs )
{
	int ret = Jiki_MoveCycle3SelectValueSet( jiki, dir );
	
	switch( ret ){
	case CYCLE3_MOVE_STOP:
		Jiki_MoveCycle3Stop( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE3_MOVE_WALK:
		Jiki_MoveCycle3Walk( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE3_MOVE_TURN:
		Jiki_MoveCycle3Turn( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE3_MOVE_BRAKE:
		Jiki_MoveCycle3Brake( jiki, fldobj, dir, trg, prs );
		break;
	}
}

//--------------------------------------------------------------
/**
 * ���]�ԂR���ړ��@�ړ��I���Ə�ԃZ�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle3SelectValueSet( PLAYER_STATE_PTR jiki, int dir )
{
	int sel = Jiki_MoveCycle3Select( jiki, dir );
	int val = Jiki_MoveCycle3SelectValue( sel );
	
	Player_MoveValueSet( jiki, val );
	return( sel );
}

//--------------------------------------------------------------
/**
 * �O���ړ��@�ړ��I��->��Ԃ�
 * @param	type	CYCLE3_MOVE_STOP��
 * @retval	int		OBJ_MOVE_VALUE_STOP��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle3SelectValue( int type )
{
	switch( type ){
	case CYCLE3_MOVE_STOP:	return( OBJ_MOVE_VALUE_STOP );
	case CYCLE3_MOVE_WALK:	return( OBJ_MOVE_VALUE_WALK );
	case CYCLE3_MOVE_TURN:	return( OBJ_MOVE_VALUE_TURN );
	case CYCLE3_MOVE_BRAKE:	return( OBJ_MOVE_VALUE_WALK );
	}
	
	GF_ASSERT( 0 && "Jiki_MoveCycle3SelectValue()�ُ�Ȓl" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * ���]�ԂR���ړ��@�ړ��I��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle3Select( PLAYER_STATE_PTR jiki, int dir )
{
	int m_dir;
	
	if( dir == DIR_NOT ){
		if( Player_MoveBitCheck_CycleBrake(jiki) == TRUE ){
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
			return( CYCLE3_MOVE_BRAKE );
		}
		
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
		return( CYCLE3_MOVE_STOP );
	}
	
	m_dir = Player_DirGet( jiki );
	Player_MoveBitSet_CycleBrake( jiki, FALSE );
	
	if( m_dir != dir && Player_MoveValueGet(jiki) != OBJ_MOVE_VALUE_WALK ){
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_TURN );
		return( CYCLE3_MOVE_TURN );
	}
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
	return( CYCLE3_MOVE_WALK );
}

//--------------------------------------------------------------
/**
 * ���]�ԂR�ړ��@��~
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3Stop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	int code;
	
	code = FieldOBJ_AcmdCodeDirChange( FieldOBJ_DirDispGet(fldobj), AC_DIR_U );
	Jiki_AcmdSet( jiki, fldobj, code );
	Player_MoveSpeedClear( jiki );
}

//--------------------------------------------------------------
/**
 * ���]�ԂR�ړ��@�ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3Walk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	u32 ret;
	int code;
	
	ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
		code = AC_JUMP_U_2G_16F;
		Jiki_WalkCount( jiki );
		Player_MoveBitSet_StepON( jiki );
	}else if( (ret & JIKI_MOVE_HIT_BIT_TAKE_OFF) ){
		code = AC_WALK_U_3F;
		Jiki_WalkCount( jiki );
		Player_MoveBitSet_StepON( jiki );
		Player_MoveBitSet_Force( jiki, TRUE );				//���񋭐��W�����v��
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		code = AC_DIR_U;
		dir = FieldOBJ_DirMoveGet( fldobj );
		FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
		Player_MoveSpeedClear( jiki );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == FALSE ){		//��{���֎~����
			code = JIKI_WALL_HIT_AC_STAY_WALK_U;
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
			Player_MoveSpeedClear( jiki );
		}else{
			code = AC_DIR_U;
			dir = FieldOBJ_DirMoveGet( fldobj );
			FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
			Player_MoveSpeedClear( jiki );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
		}
	}else{
		code = AC_WALK_U_3F;
		Jiki_WalkCount( jiki );
		Player_MoveBitSet_StepON( jiki );
		Player_MoveSpeedSet( jiki, JIKI_SPEED_CYCLE3 );
	}
	
	code = FieldOBJ_AcmdCodeDirChange( dir, code );
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * ���]�ԂR�ړ��@�U�����
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	Player_MoveSpeedClear( jiki );
	
	if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == TRUE ){		//��{���֎~����
		//�������Ȃ�
	}else{
		int code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
		Jiki_AcmdSet( jiki, fldobj, code );
		FieldOBJ_DirMoveSet( fldobj, dir );							//������
		Player_MoveSpeedClear( jiki );
	}
}

//--------------------------------------------------------------
/**
 * ���]�ԂR�ړ��@�u���[�L
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3Brake(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	u32 ret;
	int code,speed = Jiki_MoveCycleSpeedDown( jiki );
	dir = Player_DirMoveGet( jiki );
	ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_JUMP_U_2G_16F );
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
		Player_MoveSpeedClear( jiki );
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		speed = FALSE;
		code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
		
		if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
			Snd_SePlay( SEQ_SE_DP_WALL_HIT );
		}
		
		FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
		Player_MoveSpeedClear( jiki );
	}else{
		code = Jiki_MoveCycleAcmdCodeGet( jiki, dir );
	}
	
	if( speed == FALSE ){
		Player_MoveBitSet_CycleBrake( jiki, FALSE );
	}
	
	Jiki_AcmdSet( jiki, fldobj, code );
}

//==============================================================================
//	���]�Ԉړ��@�S��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���]�Ԉړ��@�S��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs )
{
	int ret = Jiki_MoveCycle4SelectValueSet( jiki, dir );
	
	switch( ret ){
	case CYCLE4_MOVE_STOP:
		Jiki_MoveCycle4Stop( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE4_MOVE_WALK:
		Jiki_MoveCycle4Walk( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE4_MOVE_TURN:
		Jiki_MoveCycle4Turn( jiki, fldobj, dir, trg, prs );
		break;
	case CYCLE4_MOVE_BRAKE:
		Jiki_MoveCycle4Brake( jiki, fldobj, dir, trg, prs );
		break;
	}
}

//--------------------------------------------------------------
/**
 * ���]�ԂS���ړ��@�ړ��I���Ə�ԃZ�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle4SelectValueSet( PLAYER_STATE_PTR jiki, int dir )
{
	int sel = Jiki_MoveCycle4Select( jiki, dir );
	int val = Jiki_MoveCycle4SelectValue( sel );
	
	Player_MoveValueSet( jiki, val );
	return( sel );
}

//--------------------------------------------------------------
/**
 * �S���ړ��@�ړ��I��->��Ԃ�
 * @param	type	CYCLE3_MOVE_STOP��
 * @retval	int		OBJ_MOVE_VALUE_STOP��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle4SelectValue( int type )
{
	switch( type ){
	case CYCLE4_MOVE_STOP:	return( OBJ_MOVE_VALUE_STOP );
	case CYCLE4_MOVE_WALK:	return( OBJ_MOVE_VALUE_WALK );
	case CYCLE4_MOVE_TURN:	return( OBJ_MOVE_VALUE_TURN );
	case CYCLE4_MOVE_BRAKE:	return( OBJ_MOVE_VALUE_WALK );
	}
	
	GF_ASSERT( 0 && "Jiki_MoveCycle4SelectValue()�ُ�Ȓl" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * ���]�ԂS���ړ��@�ړ��I��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕���
 * @retval	int		FALSE=�ړ��J�n�s��
 */
//--------------------------------------------------------------
static int Jiki_MoveCycle4Select( PLAYER_STATE_PTR jiki, int dir )
{
	int m_dir,speed;
	
	speed = Player_MoveSpeedGet( jiki );
	
	if( dir == DIR_NOT ){
		if( speed < JIKI_SPEED_BRAKE_ON ){
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
			return( CYCLE4_MOVE_STOP );
		}
		
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		return( CYCLE4_MOVE_BRAKE );
	}
	
	m_dir = Player_DirGet( jiki );
	
	if( m_dir != dir && Player_MoveValueGet(jiki) != OBJ_MOVE_VALUE_WALK ){
		if( speed < JIKI_SPEED_BRAKE_ON ){
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_TURN );
			return( CYCLE4_MOVE_TURN );
		}
		
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		return( CYCLE4_MOVE_BRAKE );
	}
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
	return( CYCLE4_MOVE_WALK );
}

//--------------------------------------------------------------
/**
 * ���]�ԂS�ړ��@��~
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4Stop(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	int code;
	
	code = FieldOBJ_AcmdCodeDirChange( FieldOBJ_DirDispGet(fldobj), AC_DIR_U );
	Jiki_AcmdSet( jiki, fldobj, code );
	Player_MoveSpeedClear( jiki );
}

//--------------------------------------------------------------
/**
 * ���]�ԂS�ړ��@�ړ�
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4Walk(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	u32 ret;
	int code;
	
	ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_JUMP_U_2G_16F );
		Jiki_MoveCycleSpeedUp( jiki );
		Jiki_WalkCount( jiki );
		Player_MoveBitSet_StepON( jiki );
	}else if( (ret & JIKI_MOVE_HIT_BIT_TAKE_OFF) ){
		if( Player_MoveSpeedGet(jiki) >= JIKI_SPEED_3 ){
			code = Jiki_MoveCycleAcmdCodeGet( jiki, dir );
			Player_MoveBitSet_StepON( jiki );
			Player_MoveBitSet_Force( jiki, TRUE );				//���񋭐��W�����v��
		}else{
			code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
		
			FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
			Player_MoveSpeedClear( jiki );
		}
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		dir = FieldOBJ_DirMoveGet( fldobj );
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
		FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
		Player_MoveSpeedClear( jiki );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == FALSE ){		//��{���֎~����
			code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
			Player_MoveSpeedClear( jiki );
		}else{
			dir = FieldOBJ_DirMoveGet( fldobj );
			code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
			Player_MoveSpeedClear( jiki );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//�ړ�����ۂ̓��̓L�[���N���A
		}
	}else{
		code = Jiki_MoveCycleAcmdCodeGet( jiki, dir );
		Jiki_MoveCycleSpeedUp( jiki );
		Jiki_WalkCount( jiki );
		Player_MoveBitSet_StepON( jiki );
	}
	
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * ���]�ԂS�ړ��@�U�����
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	Player_MoveSpeedClear( jiki );
	
	if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == TRUE ){		//��{���֎~����
		//�������Ȃ�
	}else{
		int code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
		Jiki_AcmdSet( jiki, fldobj, code );
		FieldOBJ_DirMoveSet( fldobj, dir );							//������
		Player_MoveSpeedClear( jiki );
	}
}

//--------------------------------------------------------------
/**
 * ���]�ԂS�ړ��@�u���[�L
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		�ړ�����
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4Brake(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	u32 ret;
	int code,speed = Jiki_MoveCycleSpeedDown( jiki );
	dir = Player_DirMoveGet( jiki );
	ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_JUMP_U_2G_16F );
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
		Player_MoveSpeedClear( jiki );
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		speed = FALSE;
		code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
		
		if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
			Snd_SePlay( SEQ_SE_DP_WALL_HIT );
		}
		
		FieldOBJ_DirMoveSet( fldobj, dir );					//�ǃq�b�g���͋���
		Player_MoveSpeedClear( jiki );
	}else{	
		code = Jiki_MoveCycleAcmdCodeGet( jiki, dir );
	}
	
	if( speed == FALSE ){
		Player_MoveBitSet_CycleBrake( jiki, FALSE );
	}
	
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * ���@�A�j���[�V�����R�}���h�R�[�h�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	�Ώ�FIELD_OBJ_PTR
 * @param	ac		�A�j���R�[�hAC_DIR_U��
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_AcmdSet( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, u32 ac )
{
	Player_AcmdCodeSet( jiki, ac );
	FieldOBJ_AcmdSet( fldobj, ac );
}

//==============================================================================
//	�ړ��`�F�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�ړ��`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	u32		�q�b�g�r�b�g�BJIKI_MOVE_HIT_BIT_NON��
 */
//--------------------------------------------------------------
u32 Player_MoveHitCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	u32 ret,hit;
	
	ret = JIKI_MOVE_HIT_BIT_NON;
	hit = Jiki_MoveHitCheck( jiki, fldobj, dir );
	
	if( (hit & (FLDOBJ_MOVE_HIT_BIT_ATTR|FLDOBJ_MOVE_HIT_BIT_HEIGHT)) ){
		ret |= JIKI_MOVE_HIT_BIT_ATTR;
		
		if( Jiki_MoveHitCheck_Exit(jiki,fldobj,dir) ){
			ret |= JIKI_MOVE_HIT_BIT_EXIT;
		}
	}
	
	if( (hit & FLDOBJ_MOVE_HIT_BIT_OBJ) ){
		ret |= JIKI_MOVE_HIT_BIT_OBJ;
	}
	
	if( Jiki_MoveHitCheck_Jump(jiki,fldobj,dir) ){
		ret |= JIKI_MOVE_HIT_BIT_JUMP;
	}
	
	if( Jiki_MoveHitCheck_TakeOff(jiki,fldobj,dir) == TRUE ){
		ret |= JIKI_MOVE_HIT_BIT_TAKE_OFF;
	}
	
	if( Jiki_MoveHitCheck_Water(jiki,fldobj,dir) == TRUE ){
		ret |= JIKI_MOVE_HIT_BIT_WATER;
	}
	
	if( Jiki_MoveHitCheck_BridgeHV(jiki,fldobj,dir) == TRUE ){
		ret |= JIKI_MOVE_HIT_BIT_BRIDGEHV | JIKI_MOVE_HIT_BIT_ATTR;
	}
	
	if( Jiki_MoveHitCheck_NotCycle(jiki,fldobj,dir) == TRUE ){
		ret |= JIKI_MOVE_HIT_BIT_ATTR;
	}
	
	return( ret );
}

//--------------------------------------------------------------
/**
 * ���@�ړ��`�F�b�N�@���C��
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	u32		�q�b�g�r�b�g�BJIKI_MOVE_HIT_BIT_NON��
 */
//--------------------------------------------------------------
static u32 Jiki_MoveHitCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	VecFx32 vec;
	u32 ret,hit;
	int x = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
	int y = FieldOBJ_NowPosGY_Get( fldobj );
	int z = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
	FieldOBJ_VecPosGet( fldobj, &vec );
	
	ret = FLDOBJ_MOVE_HIT_BIT_NON;
	
	if( FieldOBJ_MoveHitCheckLimit(fldobj,x,y,z) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_LIM;
	}
	
	{
		s8 flag;
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		
		if( MPTL_CheckHitWallEx(fsys,&vec,x,z,&flag) == TRUE ){
			ret |= FLDOBJ_MOVE_HIT_BIT_ATTR;
			
			if( flag != HIT_RES_EQUAL ){
				ret |= FLDOBJ_MOVE_HIT_BIT_HEIGHT;
			}
		}
	}
	
	if( FieldOBJ_MoveHitCheckAttr(fldobj,x,z,dir) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_ATTR;
	}
	
	if( FieldOBJ_MoveHitCheckFellow(fldobj,x,y,z) == TRUE ){
		ret |= FLDOBJ_MOVE_HIT_BIT_OBJ;
	}
	
	return( ret );
}

//--------------------------------------------------------------
/**
 * �W�����v�A�g���r���[�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=dir�ɃW�����v�A�g���r���[�g�A��
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_Jump( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
		
		switch( dir ){
		case DIR_UP:	if( MATR_IsJumpUp(attr) == TRUE ){ return( TRUE ); } break;
		case DIR_DOWN:	if( MATR_IsJumpDown(attr) == TRUE ){ return( TRUE ); } break;
		case DIR_LEFT:	if( MATR_IsJumpLeft(attr) == TRUE ){ return( TRUE ); } break;
		case DIR_RIGHT:	if( MATR_IsJumpRight(attr) == TRUE ){ return( TRUE ); } break;
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �o������A�g���r���[�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=dir�ɏo���������
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_Exit( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
		
		switch( dir ){
		case DIR_UP:	if( MATR_IsUpMat(attr) == TRUE ){ return( TRUE ); }
		case DIR_DOWN:	if( MATR_IsDownMat(attr) == TRUE ){ return( TRUE ); }
		case DIR_LEFT:	if( MATR_IsLeftMat(attr) == TRUE ){ return( TRUE ); }
		case DIR_RIGHT:	if( MATR_IsRightMat(attr) == TRUE ){ return( TRUE ); }
		}
		
		gx += FieldOBJ_DirAddValueGX( dir );
		gz += FieldOBJ_DirAddValueGZ( dir );
		attr = GetAttributeLSB( fsys, gx, gz );
		
		if( MATR_IsDoor(attr) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �W�����v��q�b�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=dir�ɃW�����v��A�g���r���[�g�A��
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_TakeOff( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
		
		if( dir == DIR_RIGHT && MATR_IsTakeOffLeft(attr) ){
			return( TRUE );
		}
		
		if( dir == DIR_LEFT && MATR_IsTakeOffRight(attr) ){
			return( TRUE );
		}
	}	
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���q�b�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=dir��A���A�g���r���[�g
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_Water( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
		
		if( FieldOBJ_MapAttrKindCheck_Water(fldobj,attr) ){
			return( TRUE );
		}
	}	
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���]�Ԉ�{���A�g���r���[�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=��Q���q�b�g
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_BridgeHV( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
	
		if( Player_FormGet(jiki) == HERO_FORM_CYCLE ){
			if( FieldOBJ_MapAttrKindCheck_BridgeV(fldobj,attr) == TRUE ){
				if( dir == DIR_UP || dir == DIR_DOWN ){
					return( FALSE );
				}
			
				return( TRUE );
			}
		
			if( FieldOBJ_MapAttrKindCheck_BridgeH(fldobj,attr) == TRUE ){
				if( dir == DIR_LEFT || dir == DIR_RIGHT ){
					return( FALSE );
				}
				
				return( TRUE );
			}
		}else{	//��{���͎��]�ԈȊO�ړ��s��
			if( FieldOBJ_MapAttrKindCheck_BridgeV(fldobj,attr) == TRUE ||
				FieldOBJ_MapAttrKindCheck_BridgeH(fldobj,attr) == TRUE ){
				return( TRUE );
			}
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ���]�Ԉړ��s�A�g���r���[�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�ړ����� DIR_UP��
 * @retval	int		TRUE=dir��A���]�Ԃł͈ړ��s��
 */
//--------------------------------------------------------------
static int Jiki_MoveHitCheck_NotCycle( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT && Player_FormGet(jiki) == HERO_FORM_CYCLE ){
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		int gx = FieldOBJ_NowPosGX_Get( fldobj ) + FieldOBJ_DirAddValueGX( dir );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj ) + FieldOBJ_DirAddValueGZ( dir );
		MATR attr = GetAttributeLSB( fsys, gx, gz );
		
		if( FieldOBJ_MapAttrKindCheck_Water(fldobj,attr) ){ return( TRUE ); }
		if( FieldOBJ_MapAttrKindCheck_Snow(fldobj,attr) ){ return( TRUE ); }
		if( MATR_IsLongGrass(attr) ){ return( TRUE ); }
		if(	MATR_IsSwamp(attr) ){ return( TRUE ); }
		if(	MATR_IsSwampGrass(attr) ){ return( TRUE ); }
	}	
	
	return( FALSE );
}

//==============================================================================
//	����p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �L�[�g���K�A�v���X���牟����Ă���������擾
 * @param	jiki		PLAYER_STATE_PTR
 * @param	key_trg 	�L�[�g���K
 * @param	key_prs		�L�[�v���X
 * @retval	int			������Ă�������BDIR_UP��
 */
//--------------------------------------------------------------
int Player_KeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	return( Jiki_InputKeyDirGet(jiki,key_trg,key_prs) );
}

//--------------------------------------------------------------
/**
 * �L�[�v���X���牟����Ă���X�������擾
 * @param	key_prs		�L�[�v���X
 * @retval	int			������Ă�������BDIR_UP��
 */
//--------------------------------------------------------------
static int Jiki_KeyDirXGet( u16 key_prs )
{
	if( (key_prs & PAD_KEY_LEFT) ){
		return( DIR_LEFT );
	}
	
	if( (key_prs & PAD_KEY_RIGHT) ){
		return( DIR_RIGHT );
	}
	
	return( DIR_NOT );
}

//--------------------------------------------------------------
/**
 * �L�[�v���X���牟����Ă���Z�������擾
 * @param	key_prs		�L�[�v���X
 * @retval	int			������Ă�������BDIR_UP��
 */
//--------------------------------------------------------------
static int Jiki_KeyDirZGet( u16 key_prs )
{
	if( (key_prs & PAD_KEY_UP) ){
		return( DIR_UP );
	}
	
	if( (key_prs & PAD_KEY_DOWN) ){
		return( DIR_DOWN );
	}
	
	return( DIR_NOT );
}

//--------------------------------------------------------------
/**
 * ���@���̓L�[�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @retval	int		DIR_UP���@�L�[��������Ă������
 */
//--------------------------------------------------------------
static int Jiki_InputKeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	int key_dir_x = Jiki_KeyDirXGet( key_prs );
	int key_dir_z = Jiki_KeyDirZGet( key_prs );
	
	if( key_dir_x == DIR_NOT ){									//����������̏ꍇ��Z�D��
		return( key_dir_z );
	}
	
	if( key_dir_z == DIR_NOT ){									//Z�L�[���� X�L�[�Ԃ�
		return( key_dir_x );
	}
	
	{															//�΂߉���
		int move_dir = Player_DirMoveGet( jiki );
		int input_x = Player_InputKeyDirXGet( jiki );
		int input_z = Player_InputKeyDirZGet( jiki );
		
		if( move_dir != DIR_NOT ){					//�ړ������ƈ�v���Ȃ�������Z�D��ŕԂ�
			if( key_dir_x == input_x && key_dir_z == input_z ){	//�ߋ��ɉ������������p��
				return( move_dir );								//�ړ����ƈ�v���������Ԃ�
			}
			
			if( key_dir_z != input_z ){							//�V�K�΂߉�����Z�D��ŕԂ�
				return( key_dir_z );
			}
			
			return( key_dir_x );
		}
		
		return( key_dir_z );									//Z�D��ŕԂ�
	}
	
	return( DIR_NOT );
}

#if 0	//old
static int Jiki_InputKeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	int key_dir_x = Jiki_KeyDirXGet( key_prs );
	int key_dir_z = Jiki_KeyDirZGet( key_prs );
	
	if( key_dir_x == DIR_NOT ){									//����������̏ꍇ��Z�D��
		return( key_dir_z );
	}
	
	if( key_dir_z == DIR_NOT ){									//Z�L�[���� X�L�[�Ԃ�
		return( key_dir_x );
	}
	
	{															//�΂߉���
		int move_dir = Player_DirMoveGet( jiki );
		
		if( move_dir != DIR_NOT ){
			if( key_dir_x == move_dir || key_dir_z == move_dir ){	//�΂߂̓��ǂꂩ���ړ�����
				return( move_dir );								//�ړ����ƈ�v���������Ԃ�
			}
		}
		
		return( key_dir_z );									//��v���Ȃ��ꍇ��Z�D��
	}
	
	return( DIR_NOT );
}
#endif

//--------------------------------------------------------------
/**
 * ����L�����Z���\�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�\
 */
//--------------------------------------------------------------
int Player_MoveCancellCheck( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
		return( TRUE );
	}
	
	{
		int code = FieldOBJ_AcmdCodeGet( fldobj );
		
		if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){			//�ǃq�b�g�̓L�����Z���\
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �ǃq�b�g�A�j���[�V�����R�[�h�`�F�b�N
 * @param	code	AC_DIR_U��
 * @retval	int		TRUE=�ǃq�b�g�R�[�h FALSE=�Ⴄ
 */
//--------------------------------------------------------------
static int Jiki_WallHitAcmdCodeCheck( int code )
{
	switch( code ){
	case JIKI_WALL_HIT_AC_STAY_WALK_U:
	case JIKI_WALL_HIT_AC_STAY_WALK_D:
	case JIKI_WALL_HIT_AC_STAY_WALK_L:
	case JIKI_WALL_HIT_AC_STAY_WALK_R:
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * B�_�b�V���`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	prs		�L�[�v���X
 * @retval	int		TRUE=B�_�b�V��
 */
//--------------------------------------------------------------
int Player_KeyDashCheck( PLAYER_STATE_PTR jiki, u16 prs )
{
	if( (prs & JIKI_DASH_BUTTON) ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * B�_�b�V���R�[�h�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=B�_�b�V���A�j�� FALSE=�Ⴄ
 */
//--------------------------------------------------------------
int Player_AcmdCodeDashCheck( PLAYER_STATE_PTR jiki )
{
	u32 code = Player_AcmdCodeGet( jiki );
	
	switch( code ){
	case AC_DASH_U_4F:
	case AC_DASH_D_4F:
	case AC_DASH_L_4F:
	case AC_DASH_R_4F:
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �w������Ɉړ������悤�Ƃ���Ƃǂ��Ȃ邩�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		���� DIR_UP���B
 * @retval	int		OBJ_MOVE_VALUE_STOP��
 */
//--------------------------------------------------------------
int Player_MoveSelectValueCheck( PLAYER_STATE_PTR jiki, int dir )
{
	int sel,val,form = Player_FormGet( jiki );
	
	switch( form ){
	case HERO_FORM_NORMAL:
	case HERO_FORM_SWIM:
		sel = Jiki_MoveNormalSelect( jiki, dir );
		val = Jiki_MoveNormalSelectValue( sel );
		break;
	case HERO_FORM_CYCLE:
		if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
			sel = Jiki_MoveCycle4Select( jiki, dir );
			val = Jiki_MoveCycle4SelectValue( sel );
		}else{
			sel = Jiki_MoveCycle4Select( jiki, dir );
			val = Jiki_MoveCycle4SelectValue( sel );
		}
		
		break;
	default:
		val = OBJ_MOVE_VALUE_STOP;
		GF_ASSERT( 0 && "Player_MoveSelectValueCheck()�s���Ȍ`��" );
	}
	
	return( val );
}

//--------------------------------------------------------------
/**
 * �w�肳�ꂽ�L�[��񂩂玩�@�������ۂɎw�肷��A�j���[�V�����R�}���h�R�[�h���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		�L�[�g���K
 * @param	prs		�L�[�v���X
 * @param	speed	JIKI_FRAME_SPEED_32F��
 * @param	dash	�_�b�V���t���O TRUE=�_�b�V���\�@FALSE=�_�b�V���s��
 * @param	hit     HIT�t���O TRUE=HIT������@FALSE=HIT�����Ȃ�
 * @retval	u32		�A�j���R�[�hAC_WALK_D_8F��
 */
//--------------------------------------------------------------
u32 Player_KeyMoveSelectAcmdCodeGet(
		PLAYER_STATE_PTR jiki, u16 trg, u16 prs, int speed, int dash,int hit )
{
	u32 code;
	int dir = Jiki_InputKeyDirGet( jiki, trg, prs );
	int val = Player_MoveSelectValueCheck( jiki, dir );
	
	Player_MoveValueSet( jiki, val );
	
	if( val == OBJ_MOVE_VALUE_STOP ){
		dir = Player_DirGet( jiki );
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
		return( code );
	}
	
	if( val == OBJ_MOVE_VALUE_TURN ){
		code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
		return( code );
	}
	
	{
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		u32 ret = hit;
        //Player_MoveHitCheck( jiki, fldobj, dir );
        
		if( (ret & JIKI_MOVE_HIT_BIT_JUMP) ){
			code = AC_JUMP_U_2G_16F;
		}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
			code = JIKI_WALL_HIT_AC_STAY_WALK_U;
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
		}else{
			switch( speed ){
			case JIKI_FRAME_SPEED_32F:	code = AC_WALK_U_32F; break;
			case JIKI_FRAME_SPEED_16F:	code = AC_WALK_U_16F; break;
			case JIKI_FRAME_SPEED_8F:	code = AC_WALK_U_8F; break;
			case JIKI_FRAME_SPEED_6F:	code = AC_WALK_U_6F; break;
			case JIKI_FRAME_SPEED_4F:	code = AC_WALK_U_4F; break;
			case JIKI_FRAME_SPEED_2F:	code = AC_WALK_U_2F; break;
			default: code = AC_WALK_U_32F;
			}
			
			if( dash == TRUE && Player_KeyDashCheck(jiki,prs) == TRUE ){
				code = AC_DASH_U_4F;
			}
		}
		code = FieldOBJ_AcmdCodeDirChange( dir, code );
		return( code );
	}
    return ACMD_NOT;
}

//--------------------------------------------------------------
/**
 * ���@���A�j���[�V�����R�}���h���Z�b�g�ł��邩�ǂ���
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�\ FALSE=�s��
 */
//--------------------------------------------------------------
int Player_AcmdSetCheck( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	return( FieldOBJ_AcmdSetCheck(fldobj) );
}

//--------------------------------------------------------------
/**
 * ���@�A�j���[�V�����R�}���h�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	ac		�A�j���R�[�hAC_DIR_U��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_AcmdSet( PLAYER_STATE_PTR jiki, u32 ac )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	Jiki_AcmdSet( jiki, fldobj, ac );
}

//--------------------------------------------------------------
/**
 * ���@�̈ʒu����w�������̃A�g���r���[�g���擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @retval	u32		MATR
 */
//--------------------------------------------------------------
u32 Player_NextDirAttrGet( PLAYER_STATE_PTR jiki, int dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	return( FieldOBJ_NextDirAttrGet(fldobj,dir) );
}

//--------------------------------------------------------------
/**
 * ���@�̈ʒu����w�������̃O���b�h���W�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP��
 * @param	gx		�O���b�hX���W�i�[��
 * @param	gz		�O���b�hZ���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DirNextGridPosGet( PLAYER_STATE_PTR jiki, int dir, int *gx, int *gz )
{
	*gx = Player_NowGPosXGet( jiki ) + FieldOBJ_DirAddValueGX( dir );
	*gz = Player_NowGPosZGet( jiki ) + FieldOBJ_DirAddValueGZ( dir );
}

//--------------------------------------------------------------
/**
 * ���@�̑O���ʒu�̃O���b�h���W�擾
 * @param	jiki	PLAYER_STATE_PTR
 * @param	gx		�O���b�hX���W�i�[��
 * @param	gz		�O���b�hZ���W�i�[��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_DirFrontGridPosGet( PLAYER_STATE_PTR jiki, int *gx, int *gz )
{
	int dir = Player_DirGet( jiki );
	Player_DirNextGridPosGet( jiki, dir, gx, gz );
}

//--------------------------------------------------------------
/**
 * ���R�[�h�@�����J�E���g
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_WalkCount( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	RECORD *rc = SaveData_GetRecord( fsys->savedata );
	RECORD_Inc( rc, RECID_WALK_COUNT );
}

//--------------------------------------------------------------
/**
 * ������{���A�g���r���[�g�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		�U������������
 * @retval	int		TRUE=��{���q�b�g
 */
//--------------------------------------------------------------
static int Jiki_UnderBridgeHVCheck( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir )
{
	if( dir != DIR_NOT ){
		MATR attr = FieldOBJ_NowMapAttrGet( fldobj );
		
		if( FieldOBJ_MapAttrKindCheck_BridgeV(fldobj,attr) == TRUE ){
			if( dir == DIR_UP || dir == DIR_DOWN ){
				return( FALSE );
			}
			
			return( TRUE );
		}
		
		if( FieldOBJ_MapAttrKindCheck_BridgeH(fldobj,attr) == TRUE ){
			if( dir == DIR_LEFT || dir == DIR_RIGHT ){
				return( FALSE );
			}
				
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �T�C�N�����O���[�h�`�F�b�N
 * @param	jiki	PLAYER_STATE_PTR
 * @param	attr	�A�g���r���[�g
 * @param	dir		���͕���
 * @retval	int		TRUE=�T�C�N�����O���[�h
 */
//--------------------------------------------------------------
static int Jiki_UnderCyclingRoadCheck( PLAYER_STATE_PTR jiki, u32 attr, int dir )
{
	if( dir != DIR_NOT ){
		return( FALSE );
	}
	
	if( Player_FormGet(jiki) != HERO_FORM_CYCLE ){
		return( FALSE );
	}
	
	if( Player_MoveBitCheck_CyclingRoad(jiki) == FALSE ){
		return( FALSE );
	}
	
	{
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		
		if( FieldOBJ_MapAttrKindCheck_Bridge(fldobj,attr) == TRUE ){
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//==============================================================================
//	�f�o�b�O
//==============================================================================
//----
#ifdef PLAYER_DEBUG_MOVE
//----
/***************************************************************
 * �f�o�b�O�p�v���g�^�C�v
 **************************************************************/

//==============================================================================
//	�f�o�b�O�ړ����C��
//==============================================================================
//--------------------------------------------------------------
/**
 * �f�o�b�O������
 * @param
 * @retval
 */
//--------------------------------------------------------------
void DEBUG_Player_Init( PLAYER_STATE_PTR jiki )
{
}

//--------------------------------------------------------------
//	�A�j���[�V�����R�}���h�`�F�b�N
//--------------------------------------------------------------
static int DEBUG_JikiAcmdCheck(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
#if 0
	u32 code;
	
	if( (prs & DEBUG_WALK_PAD) == 0 ){
		return( FALSE );
	}
	
	dir = Player_DirGet( jiki );
	
	if( (trg & PAD_BUTTON_B) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_JUMPHI_L_1G_16F );
		FieldOBJ_AcmdSet( fldobj, code );
		return( TRUE );
	}

	if( (trg & PAD_BUTTON_Y) ){
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_JUMPHI_L_3G_32F );
		FieldOBJ_AcmdSet( fldobj, code );
		return( TRUE );
	}
#endif
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �f�o�b�O�ړ�
 * @param
 * @retval	int		TRUE=�f�o�b�O�ړ�
 */
//--------------------------------------------------------------
static int DEBUG_Jiki_Move( PLAYER_STATE_PTR jiki,
		FIELD_OBJ_PTR fldobj, DMC_CONST_PTR dmc, int dir, u16 trg, u16 prs )
{
	int map_dir,ret;

//-------------------------------------------
	if( DEBUG_JikiAcmdCheck(jiki,fldobj,dir,trg,prs) == TRUE ){
		return( TRUE );
	}
//-------------------------------------------

	if( dir == DIR_NOT || (prs & DEBUG_WALK_PAD) == 0 ){
		return( FALSE );
	}
	
	map_dir = MAP_LOAD_UP;
	
	switch( dir ){
	case DIR_UP:	break;
	case DIR_DOWN:	map_dir = MAP_LOAD_DOWN; break;
	case DIR_LEFT:	map_dir = MAP_LOAD_LEFT; break;
	case DIR_RIGHT: map_dir = MAP_LOAD_RIGHT; break;
	}
	
	if( CheckNextGridIO(map_dir,dmc,&ret) != FALSE ){
		ret = FieldOBJ_AcmdCodeDirChange( dir, AC_WALK_U_2F );
		Jiki_AcmdSet( jiki, fldobj, ret );
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveSpeedClear( jiki );
	}
	
	Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_STOP );
	return( TRUE );
}
//----
#endif //PLAYER_DEBUG_MOVE
//----
