//******************************************************************************
/**
 *
 * @file	player_event.c
 * @brief	���@�C�x���g
 * @author	kagaya
 * @data	05.08.03
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"
#include "player.h"
#include "field_event.h"
#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "field_cutin.h"
#include "field_hideneff.h"

#include "field_encount.h"
#include "encount_set.h"

#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"

#include "sway_grass_enc.h"		//for SwayGrass_InitSwayGrass

//#include "..\system/snd_tool.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_KABE_COUNT

#define DRAW_RESET_NEW

//--------------------------------------------------------------
//	�ċA�v��
//--------------------------------------------------------------
#define RET_FALSE	(FALSE)
#define RET_TRUE	(TRUE)
#define RET_AGAIN	(TRUE+1)

//--------------------------------------------------------------
///	��o��@�㏸����
//--------------------------------------------------------------
#define TAKI_UP_FRAME_Y (64)
#define TAKI_UP_FRAME_Z (64)
#define TAKI_UP_FRAME_Z_START (32)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	CUTIN_PARAM�\����
//--------------------------------------------------------------
typedef struct
{
	u32 set_flag;
	int jiki_sex;
	POKEMON_PARAM *poke_param;
	TCB_PTR tcb_cutin;
}CUTIN_PARAM;

//--------------------------------------------------------------
///	KAIRIKI_WORK�\���́@���̓C�x���g
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int dir;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
}KAIRIKI_WORK;

#define KAIRIKI_WORK_SIZE (sizeof(KAIRIKI_WORK))

//--------------------------------------------------------------
///	SNOWBALL_WORK�\���́@��ʃC�x���g
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
}SNOWBALL_WORK;

#define SNOWBALL_WORK_SIZE (sizeof(SNOWBALL_WORK))

//--------------------------------------------------------------
///	NAMINORI_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int dir;
	int frame;
	CUTIN_PARAM cutin;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	EOA_PTR eoa_poke;
}NAMINORI_WORK;

#define NAMINORI_WORK_SIZE (sizeof(NAMINORI_WORK))

//--------------------------------------------------------------
///	NAMINORI_END_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int dir;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	EOA_PTR eoa_poke;
}NAMINORI_END_WORK;

#define NAMINORI_END_WORK_SIZE (sizeof(NAMINORI_END_WORK))

//--------------------------------------------------------------
///	ROCKRIDE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int dir;
	int count;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	EOA_PTR eoa_poke;
	CUTIN_PARAM cutin;
	FLDMAPFUNC_WORK* hiden_eff;
}ROCKRIDE_WORK;

#define ROCKRIDE_WORK_SIZE (sizeof(ROCKRIDE_WORK))

//--------------------------------------------------------------
///	TAKINOBORI_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int dir;
	int frame;
	int target_gx;
	int target_gy;
	int target_gz;
	fx32 count_vec;
	VecFx32 add_val;
	VecFx32 target_vec;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	CUTIN_PARAM cutin;
	FLDMAPFUNC_WORK* hiden_eff;
}TAKINOBORI_WORK;

#define TAKINOBORI_WORK_SIZE (sizeof(TAKINOBORI_WORK))

//--------------------------------------------------------------
//	NUMA_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int count;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
}NUMA_WORK;

#define NUMA_WORK_SIZE (sizeof(NUMA_WORK))

//--------------------------------------------------------------
///	 BUMPPOST_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
}BUMPPOST_WORK;

#define BUMPPOST_WORK_SIZE (sizeof(BUMPPOST_WORK))

//==============================================================================
//	static
//==============================================================================
static void (* const DATA_RequestTbl[HERO_REQBIT_MAX])( PLAYER_STATE_PTR jiki );

static int JikiEventCheck_MoveHitEvent(
	FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag );
static int JikiEventCheck_KeyOFFEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag );

static int JikiEventCheck_Kairiki(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val );
static void JikiEvent_KairikiSet(
		int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj );
static BOOL JikiEvent_Kairiki( GMEVENT_CONTROL *ev );

static void JikiEvent_NaminoriSet( FIELDSYS_WORK *fsys, int dir );
static void JikiEvent_NaminoriCall( FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin );
static BOOL JikiEvent_Naminori( GMEVENT_CONTROL *ev );

static int JikiEventCheck_NaminoriEnd(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val );
static void JikiEvent_NaminoriEndSet( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static BOOL JikiEvent_NaminoriEnd( GMEVENT_CONTROL *ev );

static int JikiEventCheck_BumpPost(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val );
static void JikiEvent_BumpPostSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static BOOL JikiEvent_BumpPost( GMEVENT_CONTROL *ev );

static int JikiEventCheck_TakiKudari(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val );

static int JikiEventCheck_SwampDeep(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val );
static void JikiEvent_SwampDeepSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static BOOL JikiEvent_SwampDeep( GMEVENT_CONTROL *ev );

static int JikiEventCheck_ForceMoveHitEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, HERO_EVBIT flag );

static int JikiEventCheck_SnowBall( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static void JikiEvent_SnowBallSet(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj );
static BOOL JikiEvent_SnowBall( GMEVENT_CONTROL *ev );

static void JikiEvent_KabeNoboriSet( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki );
static void JikiEvent_KabeNoboriCall( FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin );
static BOOL JikiEvent_KabeNobori( GMEVENT_CONTROL *ev );
int (* const DATA_KabeNoboriEventTbl[])( ROCKRIDE_WORK *work );

static TAKINOBORI_WORK * TakiNoboriWorkInit(
		FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin );
static BOOL JikiEvent_TakiNobori( GMEVENT_CONTROL *ev );
int (* const DATA_TakiNoboriEventTbl[])( TAKINOBORI_WORK *work );
int (* const DATA_TakiKudariEventTbl[])( TAKINOBORI_WORK *work );

static void JikiReportVIntrTcb( TCB_PTR tcb, void *wk );

static void Jiki_CutInParamInit( FIELDSYS_WORK *fsys, POKEMON_PARAM *para, CUTIN_PARAM *cutin );
static void Jiki_CutInSet( FIELDSYS_WORK *fsys, CUTIN_PARAM *cutin );
static int Jiki_CutInEndCheck( CUTIN_PARAM *cutin );

static void Jiki_DrawReset( PLAYER_STATE_PTR jiki, int code );
static FIELD_OBJ_PTR Jiki_DirOBJSearch( PLAYER_STATE_PTR jiki, int dir );
static void * Jiki_EventWorkAlloc( int size );
static void Jiki_EventWorkFree( void *work );
static POKEMON_PARAM * Jiki_PokeParaPartyGet( FIELDSYS_WORK *fsys, int no );

//==============================================================================
//	���@�@���N�G�X�g
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	req		���N�G�X�g HERO_REQBIT_NORMAL��
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestSet( PLAYER_STATE_PTR jiki, u32 req )
{
	Player_RequestBit_ON( jiki, req );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g��t
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_Request( PLAYER_STATE_PTR jiki )
{
	u32 i = 0;
	u32 req = Player_RequestBit_Get( jiki );
	do{ if((req&0x01)){DATA_RequestTbl[i](jiki);} req >>= 1; }while( ++i < HERO_REQBIT_MAX );
	Player_RequestBit_Set( jiki, HERO_REQBIT_NON );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�Q�����s��
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Normal( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_FORM_NORMAL, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
	
	Player_FormSet( jiki, HERO_FORM_NORMAL );
	Player_MoveSpeedClear( jiki );
	
	{
		EOA_PTR eoa = Player_JointEoaGet( jiki );
		if( eoa != NULL ){ FE_EoaDelete( eoa ); }
		Player_JointEoaSet( jiki, NULL );
	}
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@���]�Ԃ�
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Cycle( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_FORM_CYCLE, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
	Player_FormSet( jiki, HERO_FORM_CYCLE );
	Player_MoveSpeedClear( jiki );
	
	{
		EOA_PTR eoa = Player_JointEoaGet( jiki );
		if( eoa != NULL ){ FE_EoaDelete( eoa ); }
		Player_JointEoaSet( jiki, NULL );
	}
	
	Snd_SePlay( SE_BICYCLE );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�Ȃ݂̂��
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Naminori( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_FORM_SWIM, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
	Player_FormSet( jiki, HERO_FORM_SWIM );
	Player_MoveSpeedClear( jiki );
	
	{
		EOA_PTR eoa = Player_JointEoaGet( jiki );
		if( eoa != NULL ){ FE_EoaDelete( eoa ); }
		Player_JointEoaSet( jiki, NULL );
	}
	
	{
		int dir = Player_DirGet( jiki );
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
		EOA_PTR eoa = FE_FldOBJNamiPokeSet( fldobj, 0, 0, dir, TRUE );	//���ڑ� ���W��0
		Player_JointEoaSet( jiki, eoa );
	}
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�����𖳌���
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_UnderOFF( PLAYER_STATE_PTR jiki )
{
	Player_MoveBitSet_UnderOFF( jiki, TRUE );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�������
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Water( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_WATER, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�ނ莩�@�ɕ\���ύX
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Fishing( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_FISHING, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�|�P�b�`�ɕ\���ύX
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Poketch( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_POKETCH, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@�Z�[�u�ɕ\���ύX
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Save( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_SAVE, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
}

//--------------------------------------------------------------
/**
 * ���@���N�G�X�g�@���΂ɕ\���ύX
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiReq_Banzai( PLAYER_STATE_PTR jiki )
{
	int code;
	
	code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_BANZAI, Player_SexGet(jiki) );
	Jiki_DrawReset( jiki, code );
}

//--------------------------------------------------------------
///	���N�G�X�g�����e�[�u�� ���т�HERO_REQBIT_NON���Ɉ�v
//--------------------------------------------------------------
static void (* const DATA_RequestTbl[HERO_REQBIT_MAX])( PLAYER_STATE_PTR jiki ) =
{
	JikiReq_Normal,	//HERO_REQBIT_NORMAL
	JikiReq_Cycle,	//HERO_REQBIT_CYCLE
	JikiReq_Naminori,	//HERO_REQBIT_SWIM
	JikiReq_UnderOFF,	//HERO_REQBIT_UNDER_OFF
	JikiReq_Water,		//HERO_REQBIT_WATER
	JikiReq_Fishing,	//HERO_REQBIT_FISHING
	JikiReq_Poketch,	//HERO_REQBIT_POKETCH
	JikiReq_Save,		//HERO_REQBIT_SAVE
	JikiReq_Banzai,		//HERO_REQBIT_BANZAI
};

//==============================================================================
//	���@�C�x���g����
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�C�x���g�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕��� DIR_UP��
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=���@�C�x���g����
 */
//--------------------------------------------------------------
int Player_EventMoveCheck(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag )
{
	if( Player_MoveBitCheck_Force(jiki) == TRUE ){
		if( JikiEventCheck_ForceMoveHitEvent(fsys,jiki,flag) == TRUE ){
			return( TRUE );
		}
		
		return( FALSE );
	}
	
	if( Player_MoveStartCheck(jiki,dir) == FALSE ){
		return( FALSE );
	}
	
	if( dir == DIR_NOT ){
		if( JikiEventCheck_KeyOFFEvent(fsys,jiki,dir,flag) == TRUE ){
			return( TRUE );
		}
		
		return( FALSE );
	}
	
	if( JikiEventCheck_MoveHitEvent(fsys,jiki,dir,flag) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

#if 0
int Player_EventMoveCheck(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag )
{
	if( Player_MoveBitCheck_Force(jiki) == TRUE ){
		if( JikiEventCheck_ForceMoveHitEvent(fsys,jiki,flag) == TRUE ){
			return( TRUE );
		}
		
		return( FALSE );
	}
	
	if( dir == DIR_NOT ){
		if( JikiEventCheck_KeyOFFEvent(fsys,jiki,dir,flag) == TRUE ){
			return( TRUE );
		}
		
		return( FALSE );
	}
	
	if( Player_MoveStartCheck(jiki,dir) == FALSE ){
		return( FALSE );
	}
	
	if( JikiEventCheck_MoveHitEvent(fsys,jiki,dir,flag) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}
#endif

//==============================================================================
//	�ړ��q�b�g�n�C�x���g
//==============================================================================
//--------------------------------------------------------------
/**
 * �ړ��q�b�g�n�C�x���g�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕��� DIR_UP��
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=�C�x���g���� FALSE=����
 */
//--------------------------------------------------------------
static int JikiEventCheck_MoveHitEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag )
{
	int val = Player_MoveSelectValueCheck( jiki, dir );
	
	if( (flag & HERO_EVBIT_PERMIT_KAIRIKI) ){
		if( JikiEventCheck_Kairiki(fsys,jiki,dir,val) == TRUE ){
			return( TRUE );
		}
	}
	
	if( (flag & HERO_EVBIT_PREMIT_TAKINOBORI) ){
		if( JikiEventCheck_TakiKudari(fsys,jiki,dir,val) == TRUE ){
			return( TRUE );
		}
	}
	
	if( JikiEventCheck_NaminoriEnd(fsys,jiki,dir,val) == TRUE ){
		return( TRUE );
	}
	
#if 0	
	if( JikiEventCheck_BumpPost(fsys,jiki,dir,val) == TRUE ){
		return( TRUE );
	}
#endif
	
	if( JikiEventCheck_SwampDeep(fsys,jiki,dir,val) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�펞�����n�C�x���g
//==============================================================================
//--------------------------------------------------------------
/**
 * �펞�����C�x���g�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�L�[���͕��� DIR_UP��
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=�C�x���g���� FALSE=����
 */
//--------------------------------------------------------------
static int JikiEventCheck_KeyOFFEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, HERO_EVBIT flag )
{
	int val = Player_MoveSelectValueCheck( jiki, dir );
	
	if( JikiEventCheck_SwampDeep(fsys,jiki,dir,val) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�C�x���g�@�����肫
//==============================================================================
//--------------------------------------------------------------
/**
 * �����肫�ړ��`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @param	val		dir�ɂ�鎩�@��� OBJ_MOVE_VALUE_STOP��
 * @retval	int		TRUE=�����肫����
 */
//--------------------------------------------------------------
static int JikiEventCheck_Kairiki(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val )
{
	if( val != OBJ_MOVE_VALUE_WALK ){
		return( FALSE );
	}
	
	{
		FIELD_OBJ_PTR fldobj = Jiki_DirOBJSearch( jiki, dir );
	
		if( fldobj == NULL ){
			return( FALSE );
		}
	
		{
			int code = FieldOBJ_OBJCodeGet( fldobj );
			
			if( code != ROCK ){
				return( FALSE );
			}
		}
	
		OS_Printf( "�����肫�₪�݂���܂����@" );
		
		{
			u32 ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
			ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;	//�ړ������͖���
			
			if( ret != FLDOBJ_MOVE_HIT_BIT_NON ){
				OS_Printf( "��͏�Q���ɂ�艟�������o���܂���\n" );
				return( FALSE );
			}
		}
	
		//����ɏo������`�F�b�N���K�v
		OS_Printf( "�����肫�J�n�I�I\n" );
		JikiEvent_KairikiSet( dir, fsys, jiki, fldobj );
		return( TRUE );
	}
}

//--------------------------------------------------------------
/**
 * �����肫�C�x���g����
 * @param	dir		�ړ��������
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	�Ώۂ�FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_KairikiSet(
		int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	KAIRIKI_WORK *work = Jiki_EventWorkAlloc( KAIRIKI_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->jiki = jiki;
	FieldEvent_Set( fsys, JikiEvent_Kairiki, work );
}

//--------------------------------------------------------------
/**
 * �����肫�C�x���g 
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_Kairiki( GMEVENT_CONTROL *ev )
{
	KAIRIKI_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR jikiobj = Player_FieldOBJGet( work->jiki );
	FIELD_OBJ_PTR fldobj = work->fldobj;
	
	switch( work->seq_no ){
	case 0:
		if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){
			break;
		}
		
		if( FieldOBJ_AcmdSetCheck(jikiobj) == FALSE ){
			if( Player_MoveCancellCheck(work->jiki) == FALSE ){
				break;
			}
		}
		
		{
			int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_WALK_U_16F );
			FieldOBJ_AcmdSet( fldobj, code );
			
			code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_STAY_WALK_U_8F );
			FieldOBJ_AcmdSet( jikiobj, code );
			
			Snd_SePlay( SE_KAIRIKI );
		}
		
		work->seq_no++;
		break;
	case 1:
		if( FieldOBJ_AcmdEndCheck(fldobj) == FALSE ){
			break;
		}
		
		if( FieldOBJ_AcmdEndCheck(jikiobj) == FALSE ){
			break;
		}
		
		FieldOBJ_AcmdEnd( fldobj );
		FieldOBJ_AcmdEnd( jikiobj );
		work->seq_no++;
	case 2:
		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�Ȃ݂̂�J�n
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ȃ݂̂�C�x���g����
 * @param	dir		�z�u�������
 * @param	fsys	FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_NaminoriSet( FIELDSYS_WORK *fsys, int dir )
{
	NAMINORI_WORK *work = Jiki_EventWorkAlloc( NAMINORI_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( work->jiki );

	//�h�ꑐ�N���A
	SwayGrass_InitSwayGrass(fsys->SwayGrass);
	
	FieldEvent_Set( fsys, JikiEvent_Naminori, work );
}

//--------------------------------------------------------------
/**
 * �Ȃ݂̂�T�u�C�x���g����
 * @param	dir		�z�u�������
 * @param	fsys	FIELDSYS_WORK *
 * @param	cutin	CUTIN_PARAM *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_NaminoriCall( FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin )
{
	NAMINORI_WORK *work = Jiki_EventWorkAlloc( NAMINORI_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( work->jiki );
	work->cutin = *cutin;
	
	FieldEvent_Call( fsys->event, JikiEvent_Naminori, work );
}

//--------------------------------------------------------------
/**
 * �Ȃ݂̂�C�x���g�����@�O���ďo��
 * @param	dir		�z�u�������
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventNaminoriStart( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	JikiEvent_NaminoriSet( fsys, dir );
}

//--------------------------------------------------------------
/**
 * �Ȃ݂̂�C�x���g�����@�T�u�C�x���g�ďo��
 * @param	event	GMEVENT_CONTROL
 * @param	dir		�g�����s�������@DIR_UP��
 * @param	poke_useno	��`�Z���g�p�����莝���|�P�����ԍ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_NaminoriCall( GMEVENT_CONTROL *event, int dir, int poke_useno )
{
	CUTIN_PARAM cutin;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	POKEMON_PARAM *para = Jiki_PokeParaPartyGet( fsys, poke_useno );
	
	Jiki_CutInParamInit( fsys, para, &cutin );
	JikiEvent_NaminoriCall( fsys, dir, &cutin );
}

//--------------------------------------------------------------
/**
 * ���@�C�x���g�A�g���r���[�g�`�F�b�N�@�Ȃ݂̂�
 * @param	attr	�A�g���r���[�g
 * @retval	int		TRUE=�g���n�`
 */
//--------------------------------------------------------------
/*
int Player_EventAttrCheck_Naminori( PLAYER_STATE_PTR jiki, u32 attr )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_MapAttrKindCheck_Water(fldobj,attr) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}
*/
//--------------------------------------------------------------
/**
 * ���@�C�x���g�A�g���r���[�g�`�F�b�N�@�Ȃ݂̂�
 * @param	nattr	���ݒn�̃A�g���r���[�g
 * @param	fattr	�����O�̃A�g���r���[�g
 * @retval	int		TRUE=�g���n�`
 */
//--------------------------------------------------------------
int Player_EventAttrCheck_Naminori( PLAYER_STATE_PTR jiki, u32 nattr, u32 fattr )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );

	// �ڂ̑O����
	if( MATR_IsWater(fattr) == TRUE ){
		// ���̏�ɂ��Ȃ����OK
		if( MATR_IsBridge(nattr) == TRUE || MATR_IsBridgeFlag(nattr) == TRUE ){
			if( FieldOBJ_StatusBitCheck_Bridge(fldobj) == TRUE ){
				return( FALSE );
			}
		}
		return( TRUE );
	}
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �g���C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_Naminori( GMEVENT_CONTROL *ev )
{
	NAMINORI_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0: //��`�Z����
		{
			//int code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_SP, Player_SexGet(work->jiki) );
			//Jiki_DrawReset( work->jiki, code );
			
			//�t�F�[�h�A�E�g �� �ǉ��g�`�ǂݍ��� �� BGM�Đ�
			Snd_FieldBgmSetSpecial( work->fsys, 0 );			//���]��BGM�N���A
			Snd_FadeOutNextPlayCall( work->fsys, SEQ_NAMINORI, BGM_FADE_FIELD_MODE );
		}
		
		work->seq_no++;
		work->seq_no++;	//case 1���p�X����
		break;
	case 1:	//��`�Z�҂�
		work->frame++;
			
		if( work->frame > 10 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 2:	//�J�b�g�C������
		if( work->cutin.set_flag == TRUE ){
			Jiki_CutInSet( work->fsys, &work->cutin );
			work->seq_no++;
		}else{
			work->seq_no = 4;
		}
		
		break;
	case 3:	//�J�b�g�C���I���`�F�b�N
		if( Jiki_CutInEndCheck(&work->cutin) == TRUE ){
			work->seq_no++;
		}
		
		break;
	case 4:
		{	//1�O���b�h��Ƀ|�P�����o��
			int gx = Player_NowGPosXGet( work->jiki ) +
				FieldOBJ_DirAddValueGX( work->dir );
			int gz = Player_NowGPosZGet( work->jiki ) +
				FieldOBJ_DirAddValueGZ( work->dir );
			work->eoa_poke = FE_FldOBJNamiPokeSet( work->fldobj, gx, gz, work->dir, FALSE );
			
			Player_JointEoaSet( work->jiki, work->eoa_poke );
			Player_FormSet( work->jiki, HERO_FORM_SWIM );
		}
		
		work->seq_no++;
		break;
	case 5:	//���ɖ߂�
		work->frame++;
			
		if( work->frame > 10 ){
			int code = Player_FormSexOBJCodeGet( HERO_FORM_NORMAL, Player_SexGet(work->jiki) );
			Jiki_DrawReset( work->jiki, code );
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 6:
		if( FieldOBJ_AcmdSetCheck(work->fldobj) == TRUE ){
			int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_JUMP_U_1G_8F );
			FieldOBJ_AcmdSet( work->fldobj, code );
			work->seq_no++;
		}
		
		break;
	case 7:
		if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
			break;
		}
		
		FieldOBJ_AcmdEnd( work->fldobj );
		FE_FldOBJNamiPokeJointFlagSet( work->eoa_poke, TRUE );
		
		{
			int code = Player_FormSexOBJCodeGet( HERO_FORM_SWIM, Player_SexGet(work->jiki) );
			Jiki_DrawReset( work->jiki, code );
		}
		
		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�g���I��
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ȃ݂̂�I���`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @param	val		dir�ɂ�鎩�@�ړ��󋵁@OBJ_MOVE_VALUE_STOP��
 * @retval	int		TRUE=�g���I���J�n
 */
//--------------------------------------------------------------
static int JikiEventCheck_NaminoriEnd(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val )
{
	if( val != OBJ_MOVE_VALUE_WALK || Player_FormGet(jiki) != HERO_FORM_SWIM ){
		return( FALSE );
	}
	
	{
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		u32 ret = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( ret == JIKI_MOVE_HIT_BIT_WATER ){
			return( FALSE );
		}
		
		ret &= ~JIKI_MOVE_HIT_BIT_WATER;
			
		if( ret != JIKI_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
	}
	
	OS_Printf( "�㗤�J�n\n" );
	JikiEvent_NaminoriEndSet( dir, fsys, jiki );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �Ȃ݂̂�I���C�x���g����
 * @param	dir		�ړ�����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_NaminoriEndSet( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	NAMINORI_END_WORK *work = Jiki_EventWorkAlloc( NAMINORI_END_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = jiki;
	work->fldobj = Player_FieldOBJGet( jiki );
	work->eoa_poke = Player_JointEoaGet( jiki );
	GF_ASSERT( work->eoa_poke != NULL && "JikiEvent_NaminoriEndSet()�Ȃ݂̂�|�P����������" );

	FieldEvent_Set( fsys, JikiEvent_NaminoriEnd, work );
}

//--------------------------------------------------------------
/**
 * �g���I���C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_NaminoriEnd( GMEVENT_CONTROL *ev )
{
	NAMINORI_END_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0:
		if( FieldOBJ_AcmdSetCheck(work->fldobj) == TRUE ){
			int code = Player_FormSexOBJCodeGet( HERO_FORM_NORMAL, Player_SexGet(work->jiki) );
			Jiki_DrawReset( work->jiki, code );
			
			code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_JUMP_U_1G_8F );
			FieldOBJ_AcmdSet( work->fldobj, code );
			FE_FldOBJNamiPokeJointFlagSet( work->eoa_poke, FALSE );
			work->seq_no++;
		}
		
		break;
	case 1:
		if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
			break;
		}
		
		FieldOBJ_AcmdEnd( work->fldobj );
		FE_EoaDelete( work->eoa_poke );
		Player_JointEoaSet( work->jiki, NULL );
		Player_FormSet( work->jiki, HERO_FORM_NORMAL );
		
		//�t�F�[�h�A�E�g �� �ǉ��g�`�ǂݍ��� �� BGM�Đ�
		Snd_FadeOutNextPlayCall( work->fsys, 
						 Snd_FieldBgmNoGetNonBasicBank(work->fsys,work->fsys->location->zone_id), 
						 BGM_FADE_FIELD_MODE );

		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�Ԏ~��
//==============================================================================
//--------------------------------------------------------------
/**
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @param	val		dir�ɂ�鎩�@�ړ��󋵁@OBJ_MOVE_VALUE_STOP��
 * @retval	int		TRUE=�Ԏ~�߃C�x���g�J�n
 */
//--------------------------------------------------------------
static int JikiEventCheck_BumpPost(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val )
{
	if( Player_FormGet(jiki) != HERO_FORM_CYCLE ){
		return( FALSE );
	}
	
	{
		MATR attr = Player_NextDirAttrGet( jiki, dir );
		
		if( MATR_IsBumpPost(attr) == FALSE ){
			return( FALSE );
		}
	}
	
	OS_Printf( "�Ԏ~�߃q�b�g\n" );
	JikiEvent_BumpPostSet( fsys, jiki );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �Ԏ~�߃C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_BumpPostSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	BUMPPOST_WORK *work = Jiki_EventWorkAlloc( BUMPPOST_WORK_SIZE );
	work->fsys = fsys;
	work->jiki = jiki;
	FieldEvent_Set( fsys, JikiEvent_BumpPost, work );
}

//--------------------------------------------------------------
/**
 * �Ԏ~�߃C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_BumpPost( GMEVENT_CONTROL *ev )
{
	BUMPPOST_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0:
		Player_RequestSet( work->jiki, HERO_REQBIT_NORMAL );
		Player_Request( work->jiki );
		work->seq_no++;
		break;
	case 1:
		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�ꉺ��
//==============================================================================
//--------------------------------------------------------------
/**
 * �ꉺ��`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @param	val		dir�ɂ�鎩�@�ړ��󋵁@OBJ_MOVE_VALUE_STOP��
 * @retval	int		TRUE=�ꉺ��J�n
 */
//--------------------------------------------------------------
static int JikiEventCheck_TakiKudari(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val )
{
	if(	dir != DIR_DOWN ||
		val != OBJ_MOVE_VALUE_WALK ||
		Player_FormGet(jiki) != HERO_FORM_SWIM ){
		return( FALSE );
	}
	
	{
		MATR attr = Player_NextDirAttrGet( jiki, dir );
		
		if( MATR_IsWaterFall(attr) == FALSE ){
			return( FALSE );
		}
	}
	
	OS_Printf( "�ꉺ��q�b�g\n" );
	Player_EventTakiNoboriStart( fsys, dir );
	return( TRUE );
}

//==============================================================================
//	�[����
//==============================================================================
//--------------------------------------------------------------
/**
 * �[�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		�i�s���� DIR_UP��
 * @param	val		dir�ɂ�鎩�@��� OBJ_MOVE_VALUE_STOP��
 * @retval	int		TRUE=�[�����C�x���g����
 */
//--------------------------------------------------------------
static int JikiEventCheck_SwampDeep(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, int dir, int val )
{
#if 0
	if( Player_MoveBitCheck_DeepSwampOFF(jiki) == TRUE ||
		Player_MoveStateGet(jiki) != OBJ_MOVE_STATE_END ){
		return( FALSE );
	}
#else
	if( Player_MoveBitCheck_DeepSwampOFF(jiki) == TRUE ){
		return( FALSE );
	}
#endif
	
	{
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		MATR attr = FieldOBJ_NowMapAttrGet( fldobj );
		
		if( MATR_IsSwampDeep(attr) != TRUE && MATR_IsSwampGrassDeep(attr) != TRUE ){
			return( FALSE );
		}
	}
	
	JikiEvent_SwampDeepSet( fsys, jiki );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �[�����C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_SwampDeepSet( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	NUMA_WORK *work = Jiki_EventWorkAlloc( NUMA_WORK_SIZE );
	
	work->fsys = fsys;
	work->jiki = jiki;
	FieldEvent_Set( fsys, JikiEvent_SwampDeep, work );
}

//--------------------------------------------------------------
/**
 * �[�����C�x���g
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_SwampDeep( GMEVENT_CONTROL *ev )
{
	NUMA_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
	
	switch( work->seq_no ){
	case 0:
		Snd_SePlay( SE_DEEP_MARSH_FALL_DOWN );
		work->seq_no++;
	case 1:
		if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){
			if( Player_MoveCancellCheck(work->jiki) == FALSE ){
				break;
			}
		}
		
		if( work->count >= 10 ){
			Snd_SePlay( SE_DEEP_MARSH_FALL_OUT );
			Player_MoveBitSet_DeepSwampOFF( work->jiki, TRUE );
			Jiki_EventWorkFree( work );
			return( TRUE );
		}
		
		work->seq_no++;
	case 2:
		{
			int now_dir = Player_DirGet( work->jiki );
			u32 code, trg = sys.trg, prs = sys.cont;
			int dir = Player_KeyDirGet( work->jiki, trg, prs );
			
			if( dir == DIR_NOT || dir == now_dir ){
				break;
			}
			
			work->seq_no = 1;
			work->count++;
			
			{
				MATR attr = FieldOBJ_NowMapAttrGet( fldobj );
				
				if( MATR_IsSwampGrassDeep(attr) == TRUE ){
					FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( ev );
					BATTLE_PARAM *outBattleParam;
				
					if( SetKeyRandEncount(fsys,&outBattleParam)	 == TRUE ){
						Player_MoveBitSet_DeepSwampOFF( work->jiki, TRUE );
						Jiki_EventWorkFree( work );
						FieldEncount_Change( fsys, ev, outBattleParam );
						return( FALSE );
					}
				}
			}
			
			if( work->count < 10 ){
				code = AC_STAY_WALK_U_2F;
			}else{
				code = AC_STAY_JUMP_U_8F;
				FieldOBJ_StatusBitSet_AttrOffsOFF( fldobj, TRUE );
			}
			
			code = FieldOBJ_AcmdCodeDirChange( dir, code );
			Player_AcmdSet( work->jiki, code );
		}
		
		break;
	}
	
	return( FALSE );
}

//==============================================================================
//	�����ړ����q�b�g�C�x���g
//==============================================================================
//--------------------------------------------------------------
/**
 * �ړ��q�b�g�n�C�x���g�����`�F�b�N
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=�C�x���g���� FALSE=����
 */
//--------------------------------------------------------------
static int JikiEventCheck_ForceMoveHitEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, HERO_EVBIT flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){			//�ړ���
		return( FALSE );
	}
	
	if( JikiEventCheck_SnowBall(fsys,jiki) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�����ړ��C�x���g�@��ʔj��
//==============================================================================
//--------------------------------------------------------------
/**
 * ��ʔj��`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=�C�x���g����
 */
//--------------------------------------------------------------
static int JikiEventCheck_SnowBall( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	if( Player_MoveSpeedGet(jiki) < JIKI_SPEED_SNOWBALL_BREAK ){
		return( FALSE );
	}
	
	{
		int dir = Player_DirMoveGet( jiki );
		FIELD_OBJ_PTR fldobj = Jiki_DirOBJSearch( jiki, dir );
	
		if( fldobj == NULL ){
			return( FALSE );
		}
	
		{
			int code = FieldOBJ_OBJCodeGet( fldobj );
				
			if( code != SNOWBALL ){
				return( FALSE );
			}
		}
		
		OS_Printf( "��ʔj��\n" );
		
		FieldOBJ_DrawSnowBallBreakSet( fldobj );
		FieldOBJ_Delete( fldobj );
		Snd_SePlay( SE_KISSAKI_GYM_BREAK );
	}
	
	return( FALSE );
}

#if 0	// old
static int JikiEventCheck_SnowBall( FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	if( Player_MoveSpeedGet(jiki) < JIKI_SPEED_SNOWBALL_BREAK ){
		return( FALSE );
	}
	
	{
		int dir = Player_DirMoveGet( jiki );
		FIELD_OBJ_PTR fldobj = Jiki_DirOBJSearch( jiki, dir );
	
		if( fldobj == NULL ){
			return( FALSE );
		}
	
		{
			int code = FieldOBJ_OBJCodeGet( fldobj );
				
			if( code != SNOWBALL ){
				return( FALSE );
			}
		}
		
		OS_Printf( "��ʔj��C�x���g����\n" );
	
		JikiEvent_SnowBallSet( fsys, jiki, fldobj );
	}
	
	return( TRUE );
}
#endif

//--------------------------------------------------------------
/**
 * ��ʔj��C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	�Ώۂ�FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_SnowBallSet(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj )
{
	SNOWBALL_WORK *work = Jiki_EventWorkAlloc( SNOWBALL_WORK_SIZE );
	
	work->seq_no = 0;
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->jiki = jiki;
	FieldEvent_Set( fsys, JikiEvent_SnowBall, work );
}

//--------------------------------------------------------------
/**
 * ��ʃC�x���g 
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_SnowBall( GMEVENT_CONTROL *ev )
{
	SNOWBALL_WORK *work = FieldEvent_GetSpecialWork( ev );
	FIELD_OBJ_PTR jikiobj = Player_FieldOBJGet( work->jiki );
	FIELD_OBJ_PTR fldobj = work->fldobj;
	
	switch( work->seq_no ){
	case 0:
		if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){
			break;
		}
		
		if( FieldOBJ_AcmdSetCheck(jikiobj) == FALSE ){
			if( Player_MoveCancellCheck(work->jiki) == FALSE ){
				break;
			}
		}
		
		work->seq_no++;
	case 1:
		FieldOBJ_Delete( fldobj );
		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	��`�@���ׂ̂ڂ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ���ׂ̂ڂ�C�x���g����
 * @param	dir		�ړ�����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_KabeNoboriSet( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	ROCKRIDE_WORK *work = Jiki_EventWorkAlloc( ROCKRIDE_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = jiki;
	work->fldobj = Player_FieldOBJGet( jiki );
	
	FieldEvent_Set( fsys, JikiEvent_KabeNobori, work );
}

//--------------------------------------------------------------
/**
 * ���ׂ̂ڂ�T�u�C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		�ړ�����
 * @param	cutin	CUTIN_PARAM *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_KabeNoboriCall( FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin )
{
	ROCKRIDE_WORK *work = Jiki_EventWorkAlloc( ROCKRIDE_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( work->jiki );
	work->cutin = *cutin;
	
	FieldEvent_Call( fsys->event, JikiEvent_KabeNobori, work );
}

//--------------------------------------------------------------
/**
 * �ǂ̂ڂ�C�x���g�O������
 * @param	dir		�ړ�����
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventKabeNoboriStart( int dir, FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki )
{
	JikiEvent_KabeNoboriSet( dir, fsys, jiki );
}

//--------------------------------------------------------------
/**
 * �ǂ̂ڂ�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		�ړ�����
 * @param	poke_useno	��`�Z���g�p�����莝���|�P�����ԍ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_KabeNoboriCall( GMEVENT_CONTROL *event, int dir, int poke_useno )
{
	CUTIN_PARAM cutin;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	POKEMON_PARAM *para = Jiki_PokeParaPartyGet( fsys, poke_useno );
	
	Jiki_CutInParamInit( fsys, para, &cutin );
	JikiEvent_KabeNoboriCall( fsys, dir, &cutin );
}

//--------------------------------------------------------------
/**
 * ���@�C�x���g�A�g���r���[�g�`�F�b�N�@�Ǐ��
 * @param	attr	�A�g���r���[�g
 * @param	dir		�i������ DIR_UP��
 * @retval	int		TRUE=�Ǐ��n�`
 */
//--------------------------------------------------------------
int Player_EventAttrCheck_KabeNobori( u32 attr, int dir )
{
	switch( dir ){
	case DIR_UP:
	case DIR_DOWN:
		if( MATR_IsRockClimV(attr) == TRUE ){
			return( TRUE );
		}
		break;
	case DIR_LEFT:
	case DIR_RIGHT:
		if( MATR_IsRockClimH(attr) == TRUE ){
			return( TRUE );
		}
		break;
	}
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_KabeNobori( GMEVENT_CONTROL *ev )
{
	int ret;
	ROCKRIDE_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	do{
		ret = DATA_KabeNoboriEventTbl[work->seq_no]( work );
	}while( ret == RET_AGAIN );
	
	if( ret == RET_TRUE ){
		Jiki_EventWorkFree( work );
	}
	
	return( (BOOL)ret );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g �J�b�g�C���@0
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_CutIn0( ROCKRIDE_WORK *work )
{
	Jiki_CutInSet( work->fsys, &work->cutin );
	
	work->seq_no++;
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g �J�b�g�C���@1
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_CutIn1( ROCKRIDE_WORK *work )
{
	if( Jiki_CutInEndCheck(&work->cutin) == TRUE ){
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 0
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_0( ROCKRIDE_WORK *work )
{
	int gx = Player_NowGPosXGet( work->jiki ) + FieldOBJ_DirAddValueGX( work->dir );
	int gz = Player_NowGPosZGet( work->jiki ) + FieldOBJ_DirAddValueGZ( work->dir );
	work->eoa_poke = FE_FldOBJRockRidePoke_Add( work->fldobj, gx, gz, work->dir, FALSE );
	
	// �G�t�F�N�g�I�u�W�F����
	work->hiden_eff = FLD_HIDENEFF_RockClime_Start( work->fsys );
	Snd_SePlay( SE_ROCKCLIMB );
	
	work->seq_no++;
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 1
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_1( ROCKRIDE_WORK *work )
{
	if( FieldOBJ_AcmdSetCheck(work->fldobj) == TRUE ){
		int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_JUMP_U_1G_8F );
		FieldOBJ_AcmdSet( work->fldobj, code );
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 2
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_2( ROCKRIDE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == TRUE ){
		work->seq_no++;
		FE_FldOBJRockRidePokeJointFlagSet( work->eoa_poke, TRUE );
	}
		
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 3
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_3( ROCKRIDE_WORK *work )
{
	if( FieldOBJ_AcmdSetCheck(work->fldobj) == TRUE ){
		int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_WALK_U_4F );
		FieldOBJ_AcmdSet( work->fldobj, code );
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 4
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_4( ROCKRIDE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( RET_FALSE );
	}
	
	{
		int dir = FieldOBJ_DirMoveGet( work->fldobj );
		MATR attr = FieldOBJ_NextDirAttrGet( work->fldobj, dir );
		
		if( Player_EventAttrCheck_KabeNobori(attr,dir) == TRUE ){
			work->seq_no = 5;
			return( RET_AGAIN );
		}
	}
	
	OS_Printf( "�ǃA�g���r���[�g�ł͂Ȃ�\n" );
	
	{
		int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_JUMP_U_1G_8F );
		FieldOBJ_AcmdSet( work->fldobj, code );
		
		work->count = 0;
		work->seq_no++;
		FE_FldOBJRockRidePokeJointFlagSet( work->eoa_poke, FALSE );
	}

	// �q�f���G�t�F�N�g�j��
	FLD_HIDENEFF_RockClime_End( work->hiden_eff );	
	work->hiden_eff = NULL;
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �Ǐ��C�x���g 5
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=�ċA�v��
 */
//--------------------------------------------------------------
static int RockRideEvent_5( ROCKRIDE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( RET_FALSE );
	}
	
	FieldOBJ_AcmdEnd( work->fldobj );
	FE_EoaDelete( work->eoa_poke );
	return( RET_TRUE );
}

//--------------------------------------------------------------
///	�Ǐ��C�x���g�e�[�u��
//--------------------------------------------------------------
static int (* const DATA_KabeNoboriEventTbl[])( ROCKRIDE_WORK *work ) =
{
	RockRideEvent_CutIn0,
	RockRideEvent_CutIn1,
	RockRideEvent_0,
	RockRideEvent_1,
	RockRideEvent_2,
	RockRideEvent_3,
	RockRideEvent_4,
	RockRideEvent_5,
};

//==============================================================================
//	�����̂ڂ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ��o�胏�[�N�Z�b�g
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		�ړ����� DIR_UP��
 * @retval	TAKINOBORI_WORK	TAKINOBORI_WORK *
 */
//--------------------------------------------------------------
static TAKINOBORI_WORK * TakiNoboriWorkInit(
		FIELDSYS_WORK *fsys, int dir, const CUTIN_PARAM *cutin )
{
	TAKINOBORI_WORK *work = Jiki_EventWorkAlloc( TAKINOBORI_WORK_SIZE );
	
	work->dir = dir;
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( fsys->player );
	
	if( cutin != NULL ){
		work->cutin = *cutin;
	}
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �����̂ڂ�C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		�ړ�����
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventTakiNoboriStart( FIELDSYS_WORK *fsys, int dir )
{
	TAKINOBORI_WORK *work = TakiNoboriWorkInit( fsys, dir, NULL );
	FieldEvent_Set( fsys, JikiEvent_TakiNobori, work );
}

//--------------------------------------------------------------
/**
 * �����̂ڂ�T�u�C�x���g����
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		�ړ�����
 * @param	
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_TakiNoboriCall( GMEVENT_CONTROL *event, int dir, int poke_useno )
{
	CUTIN_PARAM cutin;
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	POKEMON_PARAM *para = Jiki_PokeParaPartyGet( fsys, poke_useno );
	Jiki_CutInParamInit( fsys, para, &cutin );
	
	{
		TAKINOBORI_WORK *work = TakiNoboriWorkInit( fsys, dir, &cutin );
		FieldEvent_Call( event, JikiEvent_TakiNobori, work );
	}
}

//--------------------------------------------------------------
/**
 * ��o��C�x���g
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_TakiNobori( GMEVENT_CONTROL *ev )
{
	int ret;
	TAKINOBORI_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	do{
		if( work->dir == DIR_UP ){
			ret = DATA_TakiNoboriEventTbl[work->seq_no]( work );
		}else{
			ret = DATA_TakiKudariEventTbl[work->seq_no]( work );
		}
	}while( ret == RET_AGAIN );
	
	if( ret == RET_TRUE ){
		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * ��o��@�J�b�g�C�� 0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiNobori_CutIn0( TAKINOBORI_WORK *work )
{
	if( work->cutin.set_flag == TRUE ){
		Jiki_CutInSet( work->fsys, &work->cutin );
		work->seq_no++;
		return( RET_FALSE );
	}
	
	work->seq_no = 2;
	return( RET_TRUE );
}

//--------------------------------------------------------------
/**
 * ��o��@�J�b�g�C�� 1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiNobori_CutIn1( TAKINOBORI_WORK *work )
{
	if( Jiki_CutInEndCheck(&work->cutin) == TRUE ){
		Snd_SePlay( SE_TAKINOBORI );
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * ��o��@0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiNobori_0( TAKINOBORI_WORK *work )
{																//�Q�O���b�h��
	int x,z;
	VecFx32 now_vec,calc_vec;
	
	x = FieldOBJ_NowPosGX_Get( work->fldobj ) + (FieldOBJ_DirAddValueGX( DIR_UP ) << 1);
	z = FieldOBJ_NowPosGZ_Get( work->fldobj ) + (FieldOBJ_DirAddValueGZ( DIR_UP ) << 1);
	
	FieldOBJTool_GridCenterPosGet( x, z, &work->target_vec );
	FieldOBJTool_GetHeight( work->fsys, &work->target_vec );
	
	work->target_gx = x;
	work->target_gy = SIZE_H_GRID_FX32( work->target_vec.y );
	work->target_gz = z;
	
	FieldOBJ_VecPosGet( work->fldobj, &now_vec );
	
	GF_ASSERT( now_vec.z > work->target_vec.z && "TakiNobori_0()z���W�ُ�" );
	GF_ASSERT( now_vec.y < work->target_vec.y && "TakiNobori_0()y���W�ُ�" );
	
	calc_vec.x = 0;
	calc_vec.y = work->target_vec.y - now_vec.y;
	calc_vec.z = work->target_vec.z - now_vec.z;
	calc_vec.y /= TAKI_UP_FRAME_Y;
	calc_vec.z /= TAKI_UP_FRAME_Z;
	work->add_val = calc_vec;

	// �G�t�F�N�g����
	work->hiden_eff = FLD_HIDENEFF_Takinobori_Start( work->fsys );
	
	work->seq_no++;
#ifdef DEBUG_JIKI_TAKIKUDARI_BUG_ON
	return( RET_AGAIN );
#else
	return( RET_FALSE );
#endif
}

//--------------------------------------------------------------
/**
 * ��o��@1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiNobori_1( TAKINOBORI_WORK *work )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( work->fldobj, &vec );
	
	vec.y += work->add_val.y;
	
	if( vec.y > work->target_vec.y ){
		vec.y = work->target_vec.y;
	}
	
	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	work->frame++;
	
	if( work->frame >= TAKI_UP_FRAME_Z_START ){
		work->frame = 0;
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * ��o��@2
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiNobori_2( TAKINOBORI_WORK *work )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( work->fldobj, &vec );
	
	vec.y += work->add_val.y;
	
	if( vec.y > work->target_vec.y ){
		vec.y = work->target_vec.y;
	}
	
	vec.z += work->add_val.z;
	
	if( vec.z < work->target_vec.z ){
		vec.z = work->target_vec.z;
	}
	
	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	work->frame++;
	
	if( work->frame < TAKI_UP_FRAME_Z ){
		return( RET_FALSE );
	}
	
	GF_ASSERT( vec.z == work->target_vec.z && "��o��@���W�ُ�\n" );
	GF_ASSERT( vec.y == work->target_vec.y && "��o��@���W�ُ�\n" );
	
//	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	FieldOBJ_NowPosGX_Set( work->fldobj, work->target_gx );
	FieldOBJ_NowPosGY_Set( work->fldobj, work->target_gy );
	FieldOBJ_NowPosGZ_Set( work->fldobj, work->target_gz );
	FieldOBJ_GPosUpdate( work->fldobj );
	
	// �G�t�F�N�g�I��
	FLD_HIDENEFF_Takinobori_End( work->hiden_eff );
	return( RET_TRUE );
}

//--------------------------------------------------------------
///	��o�蓮��e�[�u��
//--------------------------------------------------------------
static int (* const DATA_TakiNoboriEventTbl[])( TAKINOBORI_WORK *work ) =
{
	TakiNobori_CutIn0,
	TakiNobori_CutIn1,
	TakiNobori_0,
	TakiNobori_1,
	TakiNobori_2,
};

//--------------------------------------------------------------
/**
 * �ꂭ����@�J�b�g�C�� 0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiKudari_CutIn0( TAKINOBORI_WORK *work )
{
	if( work->cutin.set_flag == TRUE ){
		Jiki_CutInSet( work->fsys, &work->cutin );
		work->seq_no++;
		return( RET_FALSE );
	}
	
	work->seq_no = 2;
	return( RET_AGAIN );
}

//--------------------------------------------------------------
/**
 * �ꉺ��@�J�b�g�C�� 1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiKudari_CutIn1( TAKINOBORI_WORK *work )
{
	if( Jiki_CutInEndCheck(&work->cutin) == TRUE ){
		Snd_SePlay( SE_TAKINOBORI );
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �ꉺ��@0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiKudari_0( TAKINOBORI_WORK *work )
{																//�Q�O���b�h��
	int x,z;
	VecFx32 now_vec,calc_vec;
	
	x = FieldOBJ_NowPosGX_Get( work->fldobj ) + (FieldOBJ_DirAddValueGX( DIR_DOWN ) << 1);
	z = FieldOBJ_NowPosGZ_Get( work->fldobj ) + (FieldOBJ_DirAddValueGZ( DIR_DOWN ) << 1);
	
	FieldOBJTool_GridCenterPosGet( x, z, &work->target_vec );
	FieldOBJTool_GetHeight( work->fsys, &work->target_vec );
	
	work->count_vec = 0;
	
	work->target_gx = x;
	work->target_gy = SIZE_H_GRID_FX32( work->target_vec.y );
	work->target_gz = z;
	
	FieldOBJ_VecPosGet( work->fldobj, &now_vec );
	
	GF_ASSERT( now_vec.z < work->target_vec.z && "TakiKudari_0()z���W�ُ�" );
	GF_ASSERT( now_vec.y > work->target_vec.y && "TakiKudari_0()y���W�ُ�" );
	
#ifdef PM_DEBUG
	{
		VecFx32 center;
		x = FieldOBJ_NowPosGX_Get( work->fldobj );
		z = FieldOBJ_NowPosGZ_Get( work->fldobj );
		FieldOBJTool_GridCenterPosGet( x, z, &center );
		if( now_vec.z != center.z ){
			OS_Printf( "now_vec.z = %x center z = %x\n", now_vec.z, center.z );
			GF_ASSERT( 0 && "���@���W������Ă���" );
		}
	}
#endif
	
	calc_vec.x = 0;
	calc_vec.y = work->target_vec.y - now_vec.y;
	calc_vec.z = work->target_vec.z - now_vec.z;
	OS_Printf( "����������@���� %x\n", calc_vec.z );
	calc_vec.y /= TAKI_UP_FRAME_Y;
	calc_vec.z /= TAKI_UP_FRAME_Z;
	work->add_val = calc_vec;
	OS_Printf( "����������@���x�@%x\n", calc_vec.z );

	// �G�t�F�N�g����
	work->hiden_eff = FLD_HIDENEFF_Takinobori_Start( work->fsys );
	
	work->seq_no++;
#ifdef DEBUG_JIKI_TAKIKUDARI_BUG_ON
	return( RET_AGAIN );
#else
	return( RET_FALSE );
#endif
}

//--------------------------------------------------------------
/**
 * �ꉺ��@1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiKudari_1( TAKINOBORI_WORK *work )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( work->fldobj, &vec );
	
	vec.z += work->add_val.z;
	
	if( vec.z > work->target_vec.z ){
		vec.z = work->target_vec.z;
	}else{
		work->count_vec += work->add_val.z;
	}
	
	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	work->frame++;
	
	if( work->frame >= TAKI_UP_FRAME_Z_START ){
		work->frame = 0;
		work->seq_no++;
	}
	
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * �ꉺ��@2
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE��
 */
//--------------------------------------------------------------
static int TakiKudari_2( TAKINOBORI_WORK *work )
{
	VecFx32 vec;
	
	FieldOBJ_VecPosGet( work->fldobj, &vec );
	
	vec.y += work->add_val.y;
	
	if( vec.y < work->target_vec.y ){
		vec.y = work->target_vec.y;
	}
	
	vec.z += work->add_val.z;
	
	if( vec.z > work->target_vec.z ){
		vec.z = work->target_vec.z;
	}else{
		work->count_vec += work->add_val.z;
	}
	
	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	work->frame++;
	
	if( work->frame < TAKI_UP_FRAME_Z ){
		return( RET_FALSE );
	}
	
	GF_ASSERT( vec.z == work->target_vec.z && "��o��@���W�ُ�\n" );
	GF_ASSERT( vec.y == work->target_vec.y && "��o��@���W�ُ�\n" );
//	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	FieldOBJ_NowPosGX_Set( work->fldobj, work->target_gx );
	FieldOBJ_NowPosGY_Set( work->fldobj, work->target_gy );
	FieldOBJ_NowPosGZ_Set( work->fldobj, work->target_gz );
	FieldOBJ_GPosUpdate( work->fldobj );
	
	OS_Printf( "Z�ړ����� %x\n", work->count_vec );

	// �G�t�F�N�g�I��
	FLD_HIDENEFF_Takinobori_End( work->hiden_eff );
	
	return( RET_TRUE );
}

//--------------------------------------------------------------
///	�ꉺ�蓮��e�[�u��
//--------------------------------------------------------------
static int (* const DATA_TakiKudariEventTbl[])( TAKINOBORI_WORK *work ) =
{
	TakiKudari_CutIn0,
	TakiKudari_CutIn1,
	TakiKudari_0,
	TakiKudari_1,
	TakiKudari_2,
};

//==============================================================================
//	�R���e�X�g
//==============================================================================
//--------------------------------------------------------------
///	CONTEST_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
	FIELD_OBJ_PTR fldobj;
	int seq_no;
	int sex;
	TCB_PTR tcb_acmd;
}CONTEST_WORK;

#define CONTEST_WORK_SIZE (sizeof(CONTEST_WORK))

//--------------------------------------------------------------
///	�R���e�X�g���@�A�j��
//--------------------------------------------------------------
static const FIELD_OBJ_ACMD_LIST DATA_ContestHeroAcmdTbl_0[] =
{
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 2 },	//0
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 2 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 1 },	//1
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_D, 1 },					//2
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },					//3
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ ACMD_END, 0 },
};

static const FIELD_OBJ_ACMD_LIST DATA_ContestHeroAcmdTbl_1[] =
{
	{ AC_DIR_D, 1 },					//0
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },					//1
	{ AC_DIR_L, 1 },
	{ AC_DIR_U, 1 },
	{ AC_DIR_R, 1 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 1 },	//2
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 1 },
	{ AC_DIR_D, 1 },{ AC_WAIT_1F, 2 },	//3
	{ AC_DIR_L, 1 },{ AC_WAIT_1F, 3 },
	{ AC_DIR_U, 1 },{ AC_WAIT_1F, 4 },
	{ AC_DIR_R, 1 },{ AC_WAIT_1F, 5 },
	
	{ AC_DIR_D, 1 },
	{ ACMD_END, 0 },
};

static void JikiEvent_ContestHeroChangeSet( FIELDSYS_WORK *fsys );
static BOOL JikiEvent_ContestHeroChange( GMEVENT_CONTROL *ev );

//--------------------------------------------------------------
/**
 * �R���e�X�g���ւ��@�T�u�C�x���g�Ăяo��
 * @param	event	GMEVENT_CONTROL
 * @retval	nothing
 */
//--------------------------------------------------------------
void EventCmd_ContestHeroChange( GMEVENT_CONTROL *event )
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork( event );
	JikiEvent_ContestHeroChangeSet( fsys );
}

//--------------------------------------------------------------
/**
 * �R���e�X�g���ւ��C�x���g����
 * @param	fsys	FIELDSYS_WORK *
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventContestHeroChangeStart( FIELDSYS_WORK *fsys )
{
	CONTEST_WORK *work = Jiki_EventWorkAlloc( CONTEST_WORK_SIZE );
	
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( work->jiki );
	work->sex = Player_SexGet( work->jiki );
	
	FieldEvent_Set( fsys, JikiEvent_ContestHeroChange, work );
}

//--------------------------------------------------------------
/**
 * ���@�T�u�C�x���g�Z�b�g�@�R���e�X�g���ւ�����
 * @param	event	GMEVENT_CONTROL
 * @retval	nothing
 */
//--------------------------------------------------------------
static void JikiEvent_ContestHeroChangeSet( FIELDSYS_WORK *fsys )
{
	CONTEST_WORK *work = Jiki_EventWorkAlloc( CONTEST_WORK_SIZE );
	
	work->fsys = fsys;
	work->jiki = fsys->player;
	work->fldobj = Player_FieldOBJGet( work->jiki );
	work->sex = Player_SexGet( work->jiki );
	
	FieldEvent_Call( fsys->event, JikiEvent_ContestHeroChange, work );
}

//--------------------------------------------------------------
/**
 * �R���e�X�g���ւ��C�x���g
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=�C�x���g�I��
 */
//--------------------------------------------------------------
static BOOL JikiEvent_ContestHeroChange( GMEVENT_CONTROL *ev )
{
	CONTEST_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0:
		work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_ContestHeroAcmdTbl_0 );
		work->seq_no++;
		break;
	case 1:
		if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == TRUE ){
			int code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_CONTEST, work->sex );
			Jiki_DrawReset( work->jiki, code );
			FieldOBJ_AcmdListEnd( work->tcb_acmd );
			work->tcb_acmd = FieldOBJ_AcmdListSet( work->fldobj, DATA_ContestHeroAcmdTbl_1 );
			work->seq_no++;
		}
		
		break;
	case 2:
		if( FieldOBJ_AcmdListEndCheck(work->tcb_acmd) == TRUE ){
			FieldOBJ_AcmdListEnd( work->tcb_acmd );
			Jiki_EventWorkFree( work );
			return( TRUE );
		}
		
		break;
	}
	
	return( FALSE );
}

//==============================================================================
//	�|�P�b�`�L�����Z��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�|�P�b�`�łȂ���΃|�P�b�`��Ԃ�
 * @param	jiki	PLAYER_STATE_PTR	
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventPoketchChange( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == FALSE ){
		return;
	}
	
	{
		int form = Player_FormGet( jiki );
		if( form != HERO_FORM_NORMAL ){ return; }
	}
	
	{
		int objcode = FieldOBJ_OBJCodeGet( fldobj );
	
		if( objcode == POKEHERO || objcode == POKEHEROINE ){
			return;
		}
	}
	
	{
		u32 req = Player_RequestBit_Get( jiki );
		Player_RequestSet( jiki, HERO_REQBIT_POKETCH );
		Player_Request( jiki );
		Player_RequestSet( jiki, req );
	}
}

//--------------------------------------------------------------
/**
 * ���@�|�P�b�`��Ԃł���΃L�����Z������
 * @param	jiki	PLAYER_STATE_PTR	
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_EventPoketchCancel( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_StatusBit_DrawInitCompCheck(fldobj) == FALSE ){
		return;
	}
	
	{
		int form = Player_FormGet( jiki );
		if( form != HERO_FORM_NORMAL ){ return; }
	}
	
	{
		int objcode = FieldOBJ_OBJCodeGet( fldobj );
	
		if( objcode != POKEHERO && objcode != POKEHEROINE ){
			return;
		}
	}
	
	{
		u32 req = Player_RequestBit_Get( jiki );
		Player_RequestSet( jiki, HERO_REQBIT_NORMAL );
		Player_Request( jiki );
		Player_RequestSet( jiki, req );
	}
}

//==============================================================================
//	���|�[�g�`��
//==============================================================================
//--------------------------------------------------------------
///	REP_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int form;
	FIELDSYS_WORK *fsys;
	PLAYER_STATE_PTR jiki;
}REP_WORK;

#define REP_WORK_SIZE (sizeof(REP_WORK))

//--------------------------------------------------------------
/**
 * ���|�[�g�`�揈���ǉ��B
 * ���@�`�Ԃ��k���ȊO�ł���Ή������Ȃ��B
 * @param	fsys	FIELDSYS_WORK
 * @retval	TCB_PTR	���|�[�g�`�揈��TCB_PTR �������Ȃ��ꍇ�ANULL
 */
//--------------------------------------------------------------
TCB_PTR Player_ReportDrawProcSet( FIELDSYS_WORK *fsys )
{
	PLAYER_STATE_PTR jiki = fsys->player;
	int form = Player_FormGet( jiki );
	
	if( form != HERO_FORM_NORMAL ){
		return( NULL );
	}
	
	{
		TCB_PTR tcb;
		FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
		REP_WORK *work = sys_AllocMemoryLo( HEAPID_FIELD, REP_WORK_SIZE );
		work->seq_no = 0;
		work->fsys = fsys;
		work->jiki = jiki;
		work->form = form;
		
		FieldOBJ_MovePauseClear( fldobj );
		Player_RequestSet( jiki, HERO_REQBIT_SAVE );
		Player_Request( jiki );
		
//		tcb = VIntrTCB_Add( JikiReportVIntrTcb, work, 0xffff );
		tcb = TCB_Add( JikiReportVIntrTcb, work, 0xffff );
		GF_ASSERT( tcb != NULL && "Player_ReportDrawProcSet() tcb error" );
		return( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ���|�[�g�`�揈���폜
 * @param	tcb		Player_ReportDrawProcSet()�̖߂�l�BNULL�̏ꍇ�͉������Ȃ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_ReportDrawProcDelete( TCB_PTR tcb )
{
	if( tcb == NULL ){
		return;
	}
	
	{
		REP_WORK *work = TCB_GetWork( tcb );
		PLAYER_STATE_PTR jiki = work->jiki;
		int code = Player_FormSexOBJCodeGet( HERO_FORM_NORMAL, Player_SexGet(jiki) );
		JikiReq_Normal( jiki );
		sys_FreeMemoryEz( work );
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ���|�[�g�`�揈��
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work
 * @retval	nothing
 */
//--------------------------------------------------------------
#if 0
static void JikiReportVIntrTcb( TCB_PTR tcb, void *wk )
{
	REP_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
	BLACT_WORK_PTR act = FieldOBJ_DrawBlAct00_BlActPtrGet( fldobj );
	
	if( act != NULL ){
		FieldOBJ_DrawProcCall( fldobj );
		BLACT_Draw( act );
		G3_SwapBuffers( GX_SORTMODE_AUTO, SwapBuffMode );
	}
}
#else
static void JikiReportVIntrTcb( TCB_PTR tcb, void *wk )
{
	REP_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( work->jiki );
	FieldOBJ_DrawProcCall( fldobj );
}
#endif

//==============================================================================
//	�J�b�g�C���p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * CURIN_PARAM������
 * @param	fsys	FIELDSYS_WORK *
 * @param	para	�J�b�g�C���ŕ\��������POKEMON_PARAM *
 * @param	cutin	����������CUTIN_PARAM *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_CutInParamInit( FIELDSYS_WORK *fsys, POKEMON_PARAM *para, CUTIN_PARAM *cutin )
{
	cutin->set_flag = TRUE;
	cutin->poke_param = para;
	cutin->jiki_sex = Player_SexGet( fsys->player );
}

//--------------------------------------------------------------
/**
 * CURIN_PARAM����J�b�g�C���ǉ�
 * @param	fsys	FIELDSYS_WORK *
 * @param	cutin	CUTIN_PARAM *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_CutInSet( FIELDSYS_WORK *fsys, CUTIN_PARAM *cutin  )
{
	cutin->tcb_cutin = FieldCutIn_Init(
			fsys, CUTIN_TYPE_HIDEN, cutin->poke_param, cutin->jiki_sex );
}

//--------------------------------------------------------------
/**
 * CURIN_PARAM����J�b�g�C���I���`�F�b�N
 * @param	fsys	FIELDSYS_WORK *
 * @param	cutin	CUTIN_PARAM *
 * @retval	nothing
 */
//--------------------------------------------------------------
static int Jiki_CutInEndCheck( CUTIN_PARAM *cutin )
{
	if( FieldCutIn_EndCheck(cutin->tcb_cutin) == TRUE ){
		FieldCutIn_End( cutin->tcb_cutin );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�\���n���Z�b�g
 * @param	jiki	PLAYER_STATE_PTR
 * @param	code	�\������OBJ�R�[�h HERO��
 * @retval	nothing
 */
//--------------------------------------------------------------
#ifdef DRAW_RESET_NEW
static void Jiki_DrawReset( PLAYER_STATE_PTR jiki, int code )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	FieldOBJ_BlActDummyDrawReset( fldobj, code );
}
#else
static void Jiki_DrawReset( PLAYER_STATE_PTR jiki, int code )
{
	int ret,old;
	CONST_FIELD_OBJ_SYS_PTR fos;
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	fos = FieldOBJ_FieldOBJSysGet( fldobj );
	
	old = FieldOBJ_OBJCodeGet( fldobj );
	FieldOBJ_DrawDelete( fldobj );
	
	FieldOBJ_BlActResm_ResIDGuestUseCheckDelete( fos, old, fldobj );
	FieldOBJ_DrawResetAlone( fldobj, code );
}
#endif

//--------------------------------------------------------------
/**
 * ���@�ʒu����w������Ƀt�B�[���hOBJ�����邩
 * @param	jiki			PLAYER_STATE_PTR
 * @param	dir				�w������BDIR_UP��
 * @retval	FIELD_OBJ_PTR	NULL=���Ȃ�
 */
//--------------------------------------------------------------
static FIELD_OBJ_PTR Jiki_DirOBJSearch( PLAYER_STATE_PTR jiki, int dir )
{
	int x = Player_NowGPosXGet( jiki ) + FieldOBJ_DirAddValueGX( dir );
	int z = Player_NowGPosZGet( jiki ) + FieldOBJ_DirAddValueGZ( dir );
	CONST_FIELD_OBJ_SYS_PTR fos = FieldOBJ_FieldOBJSysGet( Player_FieldOBJGet(jiki) );
	FIELD_OBJ_PTR fldobj = FieldOBJ_SearchGPos( fos, x, z );
	
	return( fldobj );
}

//--------------------------------------------------------------
/**
 * �C�x���g�p���[�N�������m��
 * @param	size	���[�N�T�C�Y
 * @retval	void*	�m�ۂ������[�N
 */
//--------------------------------------------------------------
static void * Jiki_EventWorkAlloc( int size )
{
	void *work = sys_AllocMemoryLo( HEAPID_FIELD, size );
	GF_ASSERT( work != NULL && "Jiki_EventWorkAlloc()���[�N�m�ێ��s" );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * �C�x���g�p���[�N�������J��
 * @param	work	�J�����郏�[�N
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_EventWorkFree( void *work )
{
	sys_FreeMemory( HEAPID_FIELD, work );
}

//--------------------------------------------------------------
/**
 * �|�P�����莝���ԍ�����POKEMON_PARAM�擾
 * @param	fsys	FIELDSYS_WORK
 * @param	no		�莝���ԍ�
 * @retval	POKEMON_PARAM*	POKEMON_PARAM *
 */
//--------------------------------------------------------------
static POKEMON_PARAM * Jiki_PokeParaPartyGet( FIELDSYS_WORK *fsys, int no )
{
	POKEMON_PARAM *para = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(fsys->savedata), no );
	return( para );
}

