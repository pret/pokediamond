//******************************************************************************
/**
 *
 * @file	player_event.c
 * @brief	自機イベント
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
//	再帰要求
//--------------------------------------------------------------
#define RET_FALSE	(FALSE)
#define RET_TRUE	(TRUE)
#define RET_AGAIN	(TRUE+1)

//--------------------------------------------------------------
///	滝登り　上昇時間
//--------------------------------------------------------------
#define TAKI_UP_FRAME_Y (64)
#define TAKI_UP_FRAME_Z (64)
#define TAKI_UP_FRAME_Z_START (32)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	CUTIN_PARAM構造体
//--------------------------------------------------------------
typedef struct
{
	u32 set_flag;
	int jiki_sex;
	POKEMON_PARAM *poke_param;
	TCB_PTR tcb_cutin;
}CUTIN_PARAM;

//--------------------------------------------------------------
///	KAIRIKI_WORK構造体　怪力イベント
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
///	SNOWBALL_WORK構造体　雪玉イベント
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
///	NAMINORI_WORK構造体
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
///	NAMINORI_END_WORK構造体
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
///	ROCKRIDE_WORK構造体
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
///	TAKINOBORI_WORK構造体
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
//	NUMA_WORK構造体
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
///	 BUMPPOST_WORK構造体
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
//	自機　リクエスト
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機リクエストセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	req		リクエスト HERO_REQBIT_NORMAL等
 * @retval	nothing
 */
//--------------------------------------------------------------
void Player_RequestSet( PLAYER_STATE_PTR jiki, u32 req )
{
	Player_RequestBit_ON( jiki, req );
}

//--------------------------------------------------------------
/**
 * 自機リクエスト受付
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
 * 自機リクエスト　２足歩行に
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
 * 自機リクエスト　自転車に
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
 * 自機リクエスト　なみのりに
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
		EOA_PTR eoa = FE_FldOBJNamiPokeSet( fldobj, 0, 0, dir, TRUE );	//即接続 座標は0
		Player_JointEoaSet( jiki, eoa );
	}
}

//--------------------------------------------------------------
/**
 * 自機リクエスト　足元を無効化
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
 * 自機リクエスト　水遣りへ
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
 * 自機リクエスト　釣り自機に表示変更
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
 * 自機リクエスト　ポケッチに表示変更
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
 * 自機リクエスト　セーブに表示変更
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
 * 自機リクエスト　万歳に表示変更
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
///	リクエスト処理テーブル 並びはHERO_REQBIT_NON等に一致
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
//	自機イベント発動
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機イベント発動チェック
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向 DIR_UP等
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=自機イベント発動
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
//	移動ヒット系イベント
//==============================================================================
//--------------------------------------------------------------
/**
 * 移動ヒット系イベント発動チェック
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向 DIR_UP等
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=イベント発動 FALSE=無し
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
//	常時発動系イベント
//==============================================================================
//--------------------------------------------------------------
/**
 * 常時発動イベント発動チェック
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向 DIR_UP等
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=イベント発動 FALSE=無し
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
//	イベント　かいりき
//==============================================================================
//--------------------------------------------------------------
/**
 * かいりき移動チェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		進行方向 DIR_UP等
 * @param	val		dirによる自機状態 OBJ_MOVE_VALUE_STOP等
 * @retval	int		TRUE=かいりき発動
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
	
		OS_Printf( "かいりき岩がみつかりました　" );
		
		{
			u32 ret = FieldOBJ_MoveHitCheckDir( fldobj, dir );
			ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;	//移動制限は無視
			
			if( ret != FLDOBJ_MOVE_HIT_BIT_NON ){
				OS_Printf( "岩は障害物により押す事が出来ません\n" );
				return( FALSE );
			}
		}
	
		//さらに出入り口チェックが必要
		OS_Printf( "かいりき開始！！\n" );
		JikiEvent_KairikiSet( dir, fsys, jiki, fldobj );
		return( TRUE );
	}
}

//--------------------------------------------------------------
/**
 * かいりきイベント発動
 * @param	dir		移動する方向
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	対象のFIELD_OBJ_PTR
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
 * かいりきイベント 
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
//	なみのり開始
//==============================================================================
//--------------------------------------------------------------
/**
 * なみのりイベント発動
 * @param	dir		配置する方向
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

	//揺れ草クリア
	SwayGrass_InitSwayGrass(fsys->SwayGrass);
	
	FieldEvent_Set( fsys, JikiEvent_Naminori, work );
}

//--------------------------------------------------------------
/**
 * なみのりサブイベント発動
 * @param	dir		配置する方向
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
 * なみのりイベント発動　外部呼出し
 * @param	dir		配置する方向
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
 * なみのりイベント発動　サブイベント呼出し
 * @param	event	GMEVENT_CONTROL
 * @param	dir		波乗りを行う方向　DIR_UP等
 * @param	poke_useno	秘伝技を使用した手持ちポケモン番号
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
 * 自機イベントアトリビュートチェック　なみのり
 * @param	attr	アトリビュート
 * @retval	int		TRUE=波乗り地形
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
 * 自機イベントアトリビュートチェック　なみのり
 * @param	nattr	現在地のアトリビュート
 * @param	fattr	時期前のアトリビュート
 * @retval	int		TRUE=波乗り地形
 */
//--------------------------------------------------------------
int Player_EventAttrCheck_Naminori( PLAYER_STATE_PTR jiki, u32 nattr, u32 fattr )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );

	// 目の前が水
	if( MATR_IsWater(fattr) == TRUE ){
		// 橋の上にいなければOK
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
 * 波乗りイベント 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
 */
//--------------------------------------------------------------
static BOOL JikiEvent_Naminori( GMEVENT_CONTROL *ev )
{
	NAMINORI_WORK *work = FieldEvent_GetSpecialWork( ev );
	
	switch( work->seq_no ){
	case 0: //秘伝技発動
		{
			//int code = Player_FormSexOBJCodeGet( HERO_DRAWFORM_SP, Player_SexGet(work->jiki) );
			//Jiki_DrawReset( work->jiki, code );
			
			//フェードアウト → 追加波形読み込み → BGM再生
			Snd_FieldBgmSetSpecial( work->fsys, 0 );			//自転車BGMクリア
			Snd_FadeOutNextPlayCall( work->fsys, SEQ_NAMINORI, BGM_FADE_FIELD_MODE );
		}
		
		work->seq_no++;
		work->seq_no++;	//case 1をパスする
		break;
	case 1:	//秘伝技待ち
		work->frame++;
			
		if( work->frame > 10 ){
			work->frame = 0;
			work->seq_no++;
		}
		
		break;
	case 2:	//カットイン発動
		if( work->cutin.set_flag == TRUE ){
			Jiki_CutInSet( work->fsys, &work->cutin );
			work->seq_no++;
		}else{
			work->seq_no = 4;
		}
		
		break;
	case 3:	//カットイン終了チェック
		if( Jiki_CutInEndCheck(&work->cutin) == TRUE ){
			work->seq_no++;
		}
		
		break;
	case 4:
		{	//1グリッド先にポケモン出現
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
	case 5:	//元に戻す
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
//	波乗り終了
//==============================================================================
//--------------------------------------------------------------
/**
 * なみのり終了チェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		進行方向 DIR_UP等
 * @param	val		dirによる自機移動状況　OBJ_MOVE_VALUE_STOP等
 * @retval	int		TRUE=波乗り終了開始
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
	
	OS_Printf( "上陸開始\n" );
	JikiEvent_NaminoriEndSet( dir, fsys, jiki );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * なみのり終了イベント発動
 * @param	dir		移動方向
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
	GF_ASSERT( work->eoa_poke != NULL && "JikiEvent_NaminoriEndSet()なみのりポケモンが無い" );

	FieldEvent_Set( fsys, JikiEvent_NaminoriEnd, work );
}

//--------------------------------------------------------------
/**
 * 波乗り終了イベント 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
		
		//フェードアウト → 追加波形読み込み → BGM再生
		Snd_FadeOutNextPlayCall( work->fsys, 
						 Snd_FieldBgmNoGetNonBasicBank(work->fsys,work->fsys->location->zone_id), 
						 BGM_FADE_FIELD_MODE );

		Jiki_EventWorkFree( work );
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	車止め
//==============================================================================
//--------------------------------------------------------------
/**
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		進行方向 DIR_UP等
 * @param	val		dirによる自機移動状況　OBJ_MOVE_VALUE_STOP等
 * @retval	int		TRUE=車止めイベント開始
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
	
	OS_Printf( "車止めヒット\n" );
	JikiEvent_BumpPostSet( fsys, jiki );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 車止めイベント発動
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
 * 車止めイベント 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
//	滝下り
//==============================================================================
//--------------------------------------------------------------
/**
 * 滝下りチェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		進行方向 DIR_UP等
 * @param	val		dirによる自機移動状況　OBJ_MOVE_VALUE_STOP等
 * @retval	int		TRUE=滝下り開始
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
	
	OS_Printf( "滝下りヒット\n" );
	Player_EventTakiNoboriStart( fsys, dir );
	return( TRUE );
}

//==============================================================================
//	深い沼
//==============================================================================
//--------------------------------------------------------------
/**
 * 深い沼チェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		進行方向 DIR_UP等
 * @param	val		dirによる自機状態 OBJ_MOVE_VALUE_STOP等
 * @retval	int		TRUE=深い沼イベント発動
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
 * 深い沼イベント発動
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
 * 深い沼イベント
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
//	強制移動中ヒットイベント
//==============================================================================
//--------------------------------------------------------------
/**
 * 移動ヒット系イベント発動チェック
 * @param	fsys	FIELDSYS_WORK
 * @param	jiki	PLAYER_STATE_PTR
 * @param	flag	HERO_EVBIT
 * @retval	int		TRUE=イベント発動 FALSE=無し
 */
//--------------------------------------------------------------
static int JikiEventCheck_ForceMoveHitEvent(
		FIELDSYS_WORK *fsys, PLAYER_STATE_PTR jiki, HERO_EVBIT flag )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){			//移動中
		return( FALSE );
	}
	
	if( JikiEventCheck_SnowBall(fsys,jiki) == TRUE ){
		return( TRUE );
	}
	
	return( FALSE );
}

//==============================================================================
//	強制移動イベント　雪玉破壊
//==============================================================================
//--------------------------------------------------------------
/**
 * 雪玉破壊チェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=イベント発動
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
		
		OS_Printf( "雪玉破壊\n" );
		
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
		
		OS_Printf( "雪玉破壊イベント発動\n" );
	
		JikiEvent_SnowBallSet( fsys, jiki, fldobj );
	}
	
	return( TRUE );
}
#endif

//--------------------------------------------------------------
/**
 * 雪玉破壊イベント発動
 * @param	fsys	FIELDSYS_WORK *
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	対象のFIELD_OBJ_PTR
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
 * 雪玉イベント 
 * @param ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
//	秘伝　かべのぼり
//==============================================================================
//--------------------------------------------------------------
/**
 * かべのぼりイベント発動
 * @param	dir		移動方向
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
 * かべのぼりサブイベント発動
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		移動方向
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
 * 壁のぼりイベント外部窓口
 * @param	dir		移動方向
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
 * 壁のぼりサブイベント呼び出し
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		移動方向
 * @param	poke_useno	秘伝技を使用した手持ちポケモン番号
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
 * 自機イベントアトリビュートチェック　壁上り
 * @param	attr	アトリビュート
 * @param	dir		進入方向 DIR_UP等
 * @retval	int		TRUE=壁上り地形
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
 * 壁上りイベント 
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
 * 壁上りイベント カットイン　0
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
 * 壁上りイベント カットイン　1
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
 * 壁上りイベント 0
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
 */
//--------------------------------------------------------------
static int RockRideEvent_0( ROCKRIDE_WORK *work )
{
	int gx = Player_NowGPosXGet( work->jiki ) + FieldOBJ_DirAddValueGX( work->dir );
	int gz = Player_NowGPosZGet( work->jiki ) + FieldOBJ_DirAddValueGZ( work->dir );
	work->eoa_poke = FE_FldOBJRockRidePoke_Add( work->fldobj, gx, gz, work->dir, FALSE );
	
	// エフェクトオブジェ生成
	work->hiden_eff = FLD_HIDENEFF_RockClime_Start( work->fsys );
	Snd_SePlay( SE_ROCKCLIMB );
	
	work->seq_no++;
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * 壁上りイベント 1
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
 * 壁上りイベント 2
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
 * 壁上りイベント 3
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
 * 壁上りイベント 4
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
	
	OS_Printf( "壁アトリビュートではない\n" );
	
	{
		int code = FieldOBJ_AcmdCodeDirChange( work->dir, AC_JUMP_U_1G_8F );
		FieldOBJ_AcmdSet( work->fldobj, code );
		
		work->count = 0;
		work->seq_no++;
		FE_FldOBJRockRidePokeJointFlagSet( work->eoa_poke, FALSE );
	}

	// ヒデンエフェクト破棄
	FLD_HIDENEFF_RockClime_End( work->hiden_eff );	
	work->hiden_eff = NULL;
	return( RET_FALSE );
}

//--------------------------------------------------------------
/**
 * 壁上りイベント 5
 * @param	work	ROCKRIDE_WORK *
 * @retval	int		RET_AGAIN=再帰要求
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
///	壁上りイベントテーブル
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
//	たきのぼり
//==============================================================================
//--------------------------------------------------------------
/**
 * 滝登りワークセット
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		移動方向 DIR_UP等
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
 * たきのぼりイベント発動
 * @param	fsys	FIELDSYS_WORK *
 * @param	dir		移動方向
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
 * たきのぼりサブイベント発動
 * @param	event	GMEVENT_CONTROL*
 * @param	dir		移動方向
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
 * 滝登りイベント
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
 * 滝登り　カットイン 0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝登り　カットイン 1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝登り　0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
 */
//--------------------------------------------------------------
static int TakiNobori_0( TAKINOBORI_WORK *work )
{																//２グリッド先
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
	
	GF_ASSERT( now_vec.z > work->target_vec.z && "TakiNobori_0()z座標異常" );
	GF_ASSERT( now_vec.y < work->target_vec.y && "TakiNobori_0()y座標異常" );
	
	calc_vec.x = 0;
	calc_vec.y = work->target_vec.y - now_vec.y;
	calc_vec.z = work->target_vec.z - now_vec.z;
	calc_vec.y /= TAKI_UP_FRAME_Y;
	calc_vec.z /= TAKI_UP_FRAME_Z;
	work->add_val = calc_vec;

	// エフェクト生成
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
 * 滝登り　1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝登り　2
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
	
	GF_ASSERT( vec.z == work->target_vec.z && "滝登り　座標異常\n" );
	GF_ASSERT( vec.y == work->target_vec.y && "滝登り　座標異常\n" );
	
//	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	FieldOBJ_NowPosGX_Set( work->fldobj, work->target_gx );
	FieldOBJ_NowPosGY_Set( work->fldobj, work->target_gy );
	FieldOBJ_NowPosGZ_Set( work->fldobj, work->target_gz );
	FieldOBJ_GPosUpdate( work->fldobj );
	
	// エフェクト終了
	FLD_HIDENEFF_Takinobori_End( work->hiden_eff );
	return( RET_TRUE );
}

//--------------------------------------------------------------
///	滝登り動作テーブル
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
 * 滝くだり　カットイン 0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝下り　カットイン 1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝下り　0
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
 */
//--------------------------------------------------------------
static int TakiKudari_0( TAKINOBORI_WORK *work )
{																//２グリッド先
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
	
	GF_ASSERT( now_vec.z < work->target_vec.z && "TakiKudari_0()z座標異常" );
	GF_ASSERT( now_vec.y > work->target_vec.y && "TakiKudari_0()y座標異常" );
	
#ifdef PM_DEBUG
	{
		VecFx32 center;
		x = FieldOBJ_NowPosGX_Get( work->fldobj );
		z = FieldOBJ_NowPosGZ_Get( work->fldobj );
		FieldOBJTool_GridCenterPosGet( x, z, &center );
		if( now_vec.z != center.z ){
			OS_Printf( "now_vec.z = %x center z = %x\n", now_vec.z, center.z );
			GF_ASSERT( 0 && "自機座標がずれている" );
		}
	}
#endif
	
	calc_vec.x = 0;
	calc_vec.y = work->target_vec.y - now_vec.y;
	calc_vec.z = work->target_vec.z - now_vec.z;
	OS_Printf( "たきくだり　差分 %x\n", calc_vec.z );
	calc_vec.y /= TAKI_UP_FRAME_Y;
	calc_vec.z /= TAKI_UP_FRAME_Z;
	work->add_val = calc_vec;
	OS_Printf( "たきくだり　速度　%x\n", calc_vec.z );

	// エフェクト生成
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
 * 滝下り　1
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
 * 滝下り　2
 * @param	work	TAKINOBORI_WORK
 * @retval	int		RET_FALSE等
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
	
	GF_ASSERT( vec.z == work->target_vec.z && "滝登り　座標異常\n" );
	GF_ASSERT( vec.y == work->target_vec.y && "滝登り　座標異常\n" );
//	FieldOBJ_VecPosSet( work->fldobj, &vec );
	
	FieldOBJ_NowPosGX_Set( work->fldobj, work->target_gx );
	FieldOBJ_NowPosGY_Set( work->fldobj, work->target_gy );
	FieldOBJ_NowPosGZ_Set( work->fldobj, work->target_gz );
	FieldOBJ_GPosUpdate( work->fldobj );
	
	OS_Printf( "Z移動距離 %x\n", work->count_vec );

	// エフェクト終了
	FLD_HIDENEFF_Takinobori_End( work->hiden_eff );
	
	return( RET_TRUE );
}

//--------------------------------------------------------------
///	滝下り動作テーブル
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
//	コンテスト
//==============================================================================
//--------------------------------------------------------------
///	CONTEST_WORK構造体
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
///	コンテスト自機アニメ
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
 * コンテスト着替え　サブイベント呼び出し
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
 * コンテスト着替えイベント発動
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
 * 自機サブイベントセット　コンテスト着替え発動
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
 * コンテスト着替えイベント
 * @param	ev	GMEVENT_CONTROL *
 * @retval	BOOL	TRUE=イベント終了
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
//	ポケッチキャンセル
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機ポケッチでなければポケッチ状態に
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
 * 自機ポケッチ状態であればキャンセルする
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
//	レポート描画
//==============================================================================
//--------------------------------------------------------------
///	REP_WORK構造体
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
 * レポート描画処理追加。
 * 自機形態が徒歩以外であれば何もしない。
 * @param	fsys	FIELDSYS_WORK
 * @retval	TCB_PTR	レポート描画処理TCB_PTR 何もしない場合、NULL
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
 * レポート描画処理削除
 * @param	tcb		Player_ReportDrawProcSet()の戻り値。NULLの場合は何もしない
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
 * レポート描画処理
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
//	カットインパーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * CURIN_PARAM初期化
 * @param	fsys	FIELDSYS_WORK *
 * @param	para	カットインで表示させるPOKEMON_PARAM *
 * @param	cutin	初期化するCUTIN_PARAM *
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
 * CURIN_PARAMからカットイン追加
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
 * CURIN_PARAMからカットイン終了チェック
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
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機表示系リセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	code	表示するOBJコード HERO等
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
 * 自機位置から指定方向にフィールドOBJがいるか
 * @param	jiki			PLAYER_STATE_PTR
 * @param	dir				指定方向。DIR_UP等
 * @retval	FIELD_OBJ_PTR	NULL=いない
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
 * イベント用ワークメモリ確保
 * @param	size	ワークサイズ
 * @retval	void*	確保したワーク
 */
//--------------------------------------------------------------
static void * Jiki_EventWorkAlloc( int size )
{
	void *work = sys_AllocMemoryLo( HEAPID_FIELD, size );
	GF_ASSERT( work != NULL && "Jiki_EventWorkAlloc()ワーク確保失敗" );
	memset( work, 0, size );
	
	return( work );
}

//--------------------------------------------------------------
/**
 * イベント用ワークメモリ開放
 * @param	work	開放するワーク
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_EventWorkFree( void *work )
{
	sys_FreeMemory( HEAPID_FIELD, work );
}

//--------------------------------------------------------------
/**
 * ポケモン手持ち番号からPOKEMON_PARAM取得
 * @param	fsys	FIELDSYS_WORK
 * @param	no		手持ち番号
 * @retval	POKEMON_PARAM*	POKEMON_PARAM *
 */
//--------------------------------------------------------------
static POKEMON_PARAM * Jiki_PokeParaPartyGet( FIELDSYS_WORK *fsys, int no )
{
	POKEMON_PARAM *para = PokeParty_GetMemberPointer(
			SaveData_GetTemotiPokemon(fsys->savedata), no );
	return( para );
}

