//******************************************************************************
/**
 *
 * @file	player_move.c
 * @brief	自機動作
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
//	デバッグシンボル
//--------------------------------------------------------------
//----
#ifdef PLAYER_DEBUG
//----

//----
#endif
//----

//--------------------------------------------------------------
///	壁ヒット専用アニメコード
//--------------------------------------------------------------
#define JIKI_WALL_HIT_AC_STAY_WALK_U	(AC_STAY_WALK_U_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_D	(AC_STAY_WALK_D_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_L	(AC_STAY_WALK_L_16F)
#define JIKI_WALL_HIT_AC_STAY_WALK_R	(AC_STAY_WALK_R_16F)

//--------------------------------------------------------------
///	振り向き専用アニメコード
//--------------------------------------------------------------
//#define JIKI_TURN_AC_STAY_WALK_U		(AC_STAY_WALK_U_4F)
#define JIKI_TURN_AC_STAY_WALK_U		(AC_STAY_WALK_U_2F)

//--------------------------------------------------------------
///	歩行専用アニメコード
//--------------------------------------------------------------
#define JIKI_WALK_AC_WALK_U		(AC_WALK_U_8F)
//#define JIKI_WALK_AC_WALK_U		(AC_WALK_U_7F)

//--------------------------------------------------------------
///	足元チェック、操作シンボル
//--------------------------------------------------------------
enum
{
	UNDER_NOTHING = 0,										///<何も無し
	UNDER_ICE,												///<氷
	UNDER_SAND,												///<流砂
	UNDER_TAKEOFF_LEFT,										///<ジャンプ台　左
	UNDER_TAKEOFF_RIGHT,									///<ジャンプ台　右
	UNDER_CYCLING_ROAD_DOWN_4,								///<サイクリングロード下り
	
	UNDER_MAX,												///<足元種類最大
};

//--------------------------------------------------------------
///	足元氷　傾斜識別
//--------------------------------------------------------------
enum
{
	ICE_SLOPE_FLAT = 0,										///<平ら
	ICE_SLOPE_UP,											///<上り
	ICE_SLOPE_DOWN,											///<下り
};

//--------------------------------------------------------------
///	通常移動種類
//--------------------------------------------------------------
enum
{
	NORMAL_MOVE_STOP = 0,									///<停止
	NORMAL_MOVE_WALK,										///<移動
	NORMAL_MOVE_TURN,										///<停止
};

//--------------------------------------------------------------
///	自転車移動種類　３速
//--------------------------------------------------------------
enum
{
	CYCLE3_MOVE_STOP = 0,									///<停止
	CYCLE3_MOVE_WALK,										///<移動
	CYCLE3_MOVE_TURN,										///<停止
	CYCLE3_MOVE_BRAKE,										///<制動
};

//--------------------------------------------------------------
///	自転車移動種類　４速
//--------------------------------------------------------------
enum
{
	CYCLE4_MOVE_STOP = 0,									///<停止
	CYCLE4_MOVE_WALK,										///<移動
	CYCLE4_MOVE_TURN,										///<停止
	CYCLE4_MOVE_BRAKE,										///<制動
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
//	自機動作
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機動作関数
 * @param	jiki		PLAYER_STATE_PTR
 * @param	dmc			DMC_PTR
 * @param	dir		移動してほしい方向。DIR_UP等。DIR_NOT=key_trg,key_prsから自動で方向割り出し
 * @param	touch		ポケッチタッチ TRUE=触れている FALSE=触れていない
 * @param	key_trg		キートリガ
 * @param	key_prs		キープレス
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
	
	if( Player_FormGet(jiki) == HERO_FORM_NORMAL ){			//ポケッチ
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
 * 自機移動開始チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
 */
//--------------------------------------------------------------
int Player_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir )
{
	return( Jiki_MoveStartCheck(jiki,dir) );
}

//--------------------------------------------------------------
/**
 * 自機移動開始チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
 */
//--------------------------------------------------------------
static int Jiki_MoveStartCheck( PLAYER_STATE_PTR jiki, int dir )
{
	int code;
	FIELD_OBJ_PTR fldobj;
	
	fldobj = Player_FieldOBJGet( jiki );
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){
		return( TRUE );											//コマンドセット可能
	}
	
	if( dir == DIR_NOT ){
		return( FALSE );
	}
	
	code = FieldOBJ_AcmdCodeGet( fldobj );
	
	if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){				//壁ヒットはキャンセル可能
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
			return( TRUE );		//前水＆波乗りok
		}
			
		return( FALSE );
#endif		
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 動作開始時に毎回初期化するもの
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		移動する方向 DIR_UP等
 * @param	key_trg	キートリガ
 * @param	key_prs	キープレス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveStartInit( PLAYER_STATE_PTR jiki, int dir, u16 key_trg, u16 key_prs )
{
	Player_InputKeyDirSet( jiki,								//移動する際の入力キーをセット
			Jiki_KeyDirXGet(key_prs), Jiki_KeyDirZGet(key_prs) );
	
	Player_MoveBitSet_StepOFF( jiki );
}

//--------------------------------------------------------------
/**
 * 移動による足元無効操作
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
 * 移動によるSE再生
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
		
#if 0	//衝突音と重なった際、衝突音が目立たなくなってしまう
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
//	自機　ステータス
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機の動作状況を更新。
 * 更新された情報はPlayer_MoveStateGet()で取得。
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
	
	{															//強制移動
		u32 under = Jiki_UnderCheck( jiki, DIR_NOT );
		if( under != UNDER_NOTHING && under != UNDER_CYCLING_ROAD_DOWN_4 ){
			Player_MoveStateSet( jiki, OBJ_MOVE_STATE_ON );
			return;
		}
	}
	
	if( FieldOBJ_AcmdSetCheck(fldobj) == FALSE ){				//動作真っ盛り
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
	
	if( FieldOBJ_AcmdEndCheck(fldobj) == TRUE ){				//動作終了
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
 * 自機の動作状況をクリア
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
 * 自機動作強制停止可能チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=可能。FALSE=不可
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
 * 自機動作強制停止
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		向かせる方向。DIR_UP等
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
//	足元制御
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機足元制御
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向 DIR_UP等
 * @retval	int		TRUE=足元制御による移動
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
//	足元チェック
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機足元チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		UNDER_NOTHING等
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
///	足元チェックテーブル　UNDER_MAXの並びに一致
//--------------------------------------------------------------
static const UNDER_ATTR_CHECK DATA_Jiki_UnderAttrCheckTbl[] =
{
	{ MATR_IsIce,			UNDER_ICE },
	{ MATR_IsShiftingSand,	UNDER_SAND },
	{ MATR_IsTakeOffLeft,	UNDER_TAKEOFF_LEFT },
	{ MATR_IsTakeOffRight,	UNDER_TAKEOFF_RIGHT },
	
	{ NULL, UNDER_MAX },	//終端
};

//==============================================================================
//	足元移動
//==============================================================================
//--------------------------------------------------------------
/**
 * 足元移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	under	UNDER_NOTHING等
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ
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
 * 足元移動　何も無し UNDER_NOTHING
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
 */
//--------------------------------------------------------------
static int UnderMove_Nothing( PLAYER_STATE_PTR jiki, int key_dir )
{
	UnderForceMoveClear( jiki );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 足元移動　氷 UNDER_ICE
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
 */
//--------------------------------------------------------------
static int UnderMove_Ice( PLAYER_STATE_PTR jiki, int key_dir )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
//	int slope,dir = FieldOBJ_DirDispGet( fldobj );				//障害物、振り向きへの対応から
	int dir = FieldOBJ_DirMoveGet( fldobj );
	int slope = UnderIce_SlopeCheck( jiki, dir );
	u32 hit = Player_MoveHitCheck( jiki, fldobj, dir );
	
	Player_MoveBitSet_Force( jiki, TRUE );
	
	if( hit != JIKI_MOVE_HIT_BIT_NON ){							//障害物
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
		Player_MoveBitSet_UnderOFF( jiki, TRUE );				//ずり落ち後、停止
		Player_MoveBitSet_Force( jiki, TRUE );					//再度セット
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
		
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		return( TRUE );
	}
	
	if( UnderIce_SlopeSpeedAdd(jiki,slope) == FALSE ){			//速度不足で坂越え不可
		UnderForceMoveClear( jiki );
		
		dir = FieldOBJTool_DirFlip( dir );
		hit = Player_MoveHitCheck( jiki, fldobj, dir );
		
		if( hit != JIKI_MOVE_HIT_BIT_NON ){
			return( FALSE );
		}
		
		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
		Player_MoveBitSet_UnderOFF( jiki, TRUE );				//ずり落ち後、停止
		Player_MoveBitSet_Force( jiki, TRUE );					//再度セット
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
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
 * 足元移動　流砂 UNDER_ICE
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
 */
//--------------------------------------------------------------
static int UnderMove_Sand( PLAYER_STATE_PTR jiki, int key_dir )
{
	u32 ret;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	int dir = FieldOBJ_DirMoveGet( fldobj );
	
	Snd_SePlay( SE_DRIFT_SAND );
	
	if( dir == DIR_UP ){
		if( Player_FormGet(jiki) == HERO_FORM_CYCLE &&			//上れる
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
		Player_MoveBitSet_Force( jiki, TRUE );					//再度セット
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveBitSet_SandFloatSet( jiki, TRUE );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
		return( TRUE );
	}else if( dir == DIR_DOWN ){								//下り
		if( Player_MoveBitCheck_SandFloat(jiki) == FALSE ){
			Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_D_2F) );
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
			
			if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){
				Player_MoveSpeedSet( jiki, JIKI_SPEED_3 );
			}
			
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
			return( TRUE );
		}else{
			FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR|FLDOBJ_STA_BIT_PAUSE_ANM );
			Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_16F) );
			Player_MoveBitSet_Force( jiki, TRUE );					//再度セット
			Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
			Player_MoveBitSet_SandFloatSet( jiki, TRUE );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
			return( TRUE );
		}
	}
	
	OS_Printf( "左右方向で足元流砂\n" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 足元移動　ジャンプ台　左進入
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
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
 * 足元移動　ジャンプ台　右進入
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
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
 * 足元移動　サイクリングロード下り
 * @param	jiki	PLAYER_STATE_PTR
 * @param	key_dir	キー入力方向
 * @retval	int		TRUE=足元移動アリ　FALSE=足元移動無し
 */
//--------------------------------------------------------------
static int UnderMove_CyclingRoadDown4( PLAYER_STATE_PTR jiki, int key_dir )
{
	int dir = DIR_DOWN;
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	u32 ret = Player_MoveHitCheck( jiki, fldobj, dir );
	
	if( ret == JIKI_MOVE_HIT_BIT_NON ){
#if 1	//正規
//		FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
		Jiki_AcmdSet( jiki, fldobj, FieldOBJ_AcmdCodeDirChange(dir,AC_WALK_U_2F) );
//		Player_MoveBitSet_Force( jiki, TRUE ); //サイクリングロード強制移動は通常移動
		Player_MoveValueSet( jiki, OBJ_MOVE_VALUE_WALK );
		Player_MoveSpeedSet( jiki, JIKI_SPEED_CYCLE4_TOP );
#else	//サイクリング下り、強制移動による不具合発生
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
///	足元移動テーブル UNDER_MAXの並びに一致
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
//	足元　強制　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 強制移動後消去
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
 * 氷　傾斜チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		移動する方向
 * @retval	int		ICE_SLOPE_FLAT等
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
	
	FieldOBJTool_VecPosDirAdd( dir, &next, GRID_HALF_FX32 / 2 );	//移動方向中間地点へ
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
 * 現在の速度と傾斜の影響
 * @param	jiki	PLAYER_STATE_PTR
 * @param	slope	ICE_SLOPE_FLAT等
 * @retval	int		TRUE=移動可　FALSE=移動不可
 */
//--------------------------------------------------------------
static int UnderIce_SlopeSpeedAdd( PLAYER_STATE_PTR jiki, int slope )
{
	int speed = Player_MoveSpeedGet( jiki );
	
	if( slope == ICE_SLOPE_UP ){								//上り
		speed--;
		
		if( speed < JIKI_SPEED_0 ){
			return( FALSE );
		}
	}else if( slope == ICE_SLOPE_DOWN ){						//下り
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
 * 現在の速度にあわせたアニメコマンドセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
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
//	自機動作
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機動作
 * @param	jiki		PLAYER_STATE_PTR
 * @param	dmc			DMC_PTR
 * @param	dir			移動する方向。DIR_UP等
 * @param	key_trg		キートリガ
 * @param	key_prs		キープレス
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
		GF_ASSERT( 0 && "Jiki_MoveSet() 不正なフォーム" );
		break;
	}
}

//==============================================================================
//	通常移動
//==============================================================================
//--------------------------------------------------------------
/**
 * 通常移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 通常移動　移動選択と状態セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向。DIR_UP等
 * @retval	int		NORMAL_MOVE_STOP等
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
 * 通常移動　移動選択->状態へ
 * @param	type	NORMAL_MOVE_STOP等
 * @retval	int		OBJ_MOVE_VALUE_STOP等
 */
//--------------------------------------------------------------
static int Jiki_MoveNormalSelectValue( int type )
{
	switch( type ){
	case NORMAL_MOVE_STOP:	return( OBJ_MOVE_VALUE_STOP );
	case NORMAL_MOVE_WALK:	return( OBJ_MOVE_VALUE_WALK );
	case NORMAL_MOVE_TURN:	return( OBJ_MOVE_VALUE_TURN );
	}
	
	GF_ASSERT( 0 && "Jiki_MoveNormalSelectValue()異常な値" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * 通常移動　アトリビュートによる移動アニメーションコード選択
 * @param	attr	アトリビュート
 * @param	ac		本来実行するアニメーションコード
 * @retval	int		アニメーションコード
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
 * 通常移動　移動選択
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向。DIR_UP等
 * @retval	int		NORMAL_MOVE_STOP等
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
 * 通常移動　停止
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 通常移動　移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
			
			FieldOBJ_DirMoveSet( fldobj, dir );						//壁ヒット時は強制
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
			
			FieldOBJ_DirMoveSet( fldobj, dir );						//壁ヒット時は強制
		}
	}
	
	code = FieldOBJ_AcmdCodeDirChange( dir, code );
	Jiki_AcmdSet( jiki, fldobj, code );
}

//--------------------------------------------------------------
/**
 * 通常移動　振り向き
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveNormalTurn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	int code;
	
	code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
	Jiki_AcmdSet( jiki, fldobj, code );
	FieldOBJ_DirMoveSet( fldobj, dir );							//強制で
}

//==============================================================================
//	自転車移動
//==============================================================================
//--------------------------------------------------------------
/**
 * 自転車移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * ３速　４速の切り替え
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		キートリガ
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
		
		if( Player_SaveDataGetGearGet(jiki) == GEAR_4 ){			//現在４速
			gear = GEAR_3;
#if 0		
			if( Player_MoveSpeedGet(jiki) >= JIKI_SPEED_BRAKE_ON ){	//ブレーキ開始か?
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
 * 速度からアニメーションコード
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		方向
 * @retval	int		AC_WALK_U_4F等
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
 * 加速
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=最高速
 */
//--------------------------------------------------------------
static int Jiki_MoveCycleSpeedUp( PLAYER_STATE_PTR jiki )
{
	int speed = Player_MoveSpeedAdd( jiki, JIKI_SPEED_VALUE_1, JIKI_SPEED_CYCLE4_TOP );
	
	if( Player_MoveBitCheck_CycleBrake(jiki) == FALSE ){		//ブレーキ無し
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
 * 減速
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		速度がある
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
//	自転車移動　３速
//==============================================================================
//--------------------------------------------------------------
/**
 * 自転車移動　３速
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 自転車３速移動　移動選択と状態セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
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
 * 三速移動　移動選択->状態へ
 * @param	type	CYCLE3_MOVE_STOP等
 * @retval	int		OBJ_MOVE_VALUE_STOP等
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
	
	GF_ASSERT( 0 && "Jiki_MoveCycle3SelectValue()異常な値" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * 自転車３速移動　移動選択
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
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
 * 自転車３移動　停止
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 自転車３移動　移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
		Player_MoveBitSet_Force( jiki, TRUE );				//次回強制ジャンプ台
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		code = AC_DIR_U;
		dir = FieldOBJ_DirMoveGet( fldobj );
		FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
		Player_MoveSpeedClear( jiki );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == FALSE ){		//一本橋禁止方向
			code = JIKI_WALL_HIT_AC_STAY_WALK_U;
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
			Player_MoveSpeedClear( jiki );
		}else{
			code = AC_DIR_U;
			dir = FieldOBJ_DirMoveGet( fldobj );
			FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
			Player_MoveSpeedClear( jiki );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
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
 * 自転車３移動　振り向き
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle3Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	Player_MoveSpeedClear( jiki );
	
	if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == TRUE ){		//一本橋禁止方向
		//何もしない
	}else{
		int code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
		Jiki_AcmdSet( jiki, fldobj, code );
		FieldOBJ_DirMoveSet( fldobj, dir );							//強制で
		Player_MoveSpeedClear( jiki );
	}
}

//--------------------------------------------------------------
/**
 * 自転車３移動　ブレーキ
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
		
		FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
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
//	自転車移動　４速
//==============================================================================
//--------------------------------------------------------------
/**
 * 自転車移動　４速
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dmc		DMC_PTR
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 自転車４速移動　移動選択と状態セット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
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
 * ４速移動　移動選択->状態へ
 * @param	type	CYCLE3_MOVE_STOP等
 * @retval	int		OBJ_MOVE_VALUE_STOP等
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
	
	GF_ASSERT( 0 && "Jiki_MoveCycle4SelectValue()異常な値" );
	return( OBJ_MOVE_VALUE_STOP );
}

//--------------------------------------------------------------
/**
 * 自転車４速移動　移動選択
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		キー入力方向
 * @retval	int		FALSE=移動開始不可
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
 * 自転車４移動　停止
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
 * 自転車４移動　移動
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
			Player_MoveBitSet_Force( jiki, TRUE );				//次回強制ジャンプ台
		}else{
			code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
		
			FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
			Player_MoveSpeedClear( jiki );
		}
	}else if( (ret & JIKI_MOVE_HIT_BIT_BRIDGEHV) ){
		dir = FieldOBJ_DirMoveGet( fldobj );
		code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
		FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
		Player_MoveSpeedClear( jiki );
		Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
	}else if( ret != JIKI_MOVE_HIT_BIT_NON ){
		if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == FALSE ){		//一本橋禁止方向
			code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_WALL_HIT_AC_STAY_WALK_U );
			
			if( (ret & JIKI_MOVE_HIT_BIT_EXIT) == 0 ){
				Snd_SePlay( SEQ_SE_DP_WALL_HIT );
			}
			
			FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
			Player_MoveSpeedClear( jiki );
		}else{
			dir = FieldOBJ_DirMoveGet( fldobj );
			code = FieldOBJ_AcmdCodeDirChange( dir, AC_DIR_U );
			FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
			Player_MoveSpeedClear( jiki );
			Player_InputKeyDirSet( jiki, DIR_NOT, DIR_NOT );	//移動する際の入力キーをクリア
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
 * 自転車４移動　振り向き
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_MoveCycle4Turn(
		PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, int dir, u16 trg, u16 prs )
{
	Player_MoveSpeedClear( jiki );
	
	if( Jiki_UnderBridgeHVCheck(jiki,fldobj,dir) == TRUE ){		//一本橋禁止方向
		//何もしない
	}else{
		int code = FieldOBJ_AcmdCodeDirChange( dir, JIKI_TURN_AC_STAY_WALK_U );
		Jiki_AcmdSet( jiki, fldobj, code );
		FieldOBJ_DirMoveSet( fldobj, dir );							//強制で
		Player_MoveSpeedClear( jiki );
	}
}

//--------------------------------------------------------------
/**
 * 自転車４移動　ブレーキ
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ *
 * @param	dir		移動方向
 * @param	trg		キートリガ
 * @param	prs		キープレス
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
		
		FieldOBJ_DirMoveSet( fldobj, dir );					//壁ヒット時は強制
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
 * 自機アニメーションコマンドコードセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	対象FIELD_OBJ_PTR
 * @param	ac		アニメコードAC_DIR_U等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Jiki_AcmdSet( PLAYER_STATE_PTR jiki, FIELD_OBJ_PTR fldobj, u32 ac )
{
	Player_AcmdCodeSet( jiki, ac );
	FieldOBJ_AcmdSet( fldobj, ac );
}

//==============================================================================
//	移動チェック
//==============================================================================
//--------------------------------------------------------------
/**
 * 自機移動チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	u32		ヒットビット。JIKI_MOVE_HIT_BIT_NON等
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
 * 自機移動チェック　メイン
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	u32		ヒットビット。JIKI_MOVE_HIT_BIT_NON等
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
 * ジャンプアトリビュートチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=dirにジャンプアトリビュートアリ
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
 * 出入り口アトリビュートチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=dirに出入り口あり
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
 * ジャンプ台ヒットチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=dirにジャンプ台アトリビュートアリ
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
 * 水ヒットチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=dir先、水アトリビュート
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
 * 自転車一本橋アトリビュートチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=障害物ヒット
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
		}else{	//一本橋は自転車以外移動不可
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
 * 自転車移動不可アトリビュートチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		移動方向 DIR_UP等
 * @retval	int		TRUE=dir先、自転車では移動不可
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
//	動作パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * キートリガ、プレスから押されている方向を取得
 * @param	jiki		PLAYER_STATE_PTR
 * @param	key_trg 	キートリガ
 * @param	key_prs		キープレス
 * @retval	int			押されている方向。DIR_UP等
 */
//--------------------------------------------------------------
int Player_KeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	return( Jiki_InputKeyDirGet(jiki,key_trg,key_prs) );
}

//--------------------------------------------------------------
/**
 * キープレスから押されているX方向を取得
 * @param	key_prs		キープレス
 * @retval	int			押されている方向。DIR_UP等
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
 * キープレスから押されているZ方向を取得
 * @param	key_prs		キープレス
 * @retval	int			押されている方向。DIR_UP等
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
 * 自機入力キー取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		キートリガ
 * @param	prs		キープレス
 * @retval	int		DIR_UP等　キーが押されている方向
 */
//--------------------------------------------------------------
static int Jiki_InputKeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	int key_dir_x = Jiki_KeyDirXGet( key_prs );
	int key_dir_z = Jiki_KeyDirZGet( key_prs );
	
	if( key_dir_x == DIR_NOT ){									//一方向押しの場合はZ優先
		return( key_dir_z );
	}
	
	if( key_dir_z == DIR_NOT ){									//Zキー無し Xキー返し
		return( key_dir_x );
	}
	
	{															//斜め押し
		int move_dir = Player_DirMoveGet( jiki );
		int input_x = Player_InputKeyDirXGet( jiki );
		int input_z = Player_InputKeyDirZGet( jiki );
		
		if( move_dir != DIR_NOT ){					//移動方向と一致しない方向をZ優先で返す
			if( key_dir_x == input_x && key_dir_z == input_z ){	//過去に押した方向を継続
				return( move_dir );								//移動中と一致する方向を返す
			}
			
			if( key_dir_z != input_z ){							//新規斜め押しはZ優先で返す
				return( key_dir_z );
			}
			
			return( key_dir_x );
		}
		
		return( key_dir_z );									//Z優先で返す
	}
	
	return( DIR_NOT );
}

#if 0	//old
static int Jiki_InputKeyDirGet( PLAYER_STATE_PTR jiki, u16 key_trg, u16 key_prs )
{
	int key_dir_x = Jiki_KeyDirXGet( key_prs );
	int key_dir_z = Jiki_KeyDirZGet( key_prs );
	
	if( key_dir_x == DIR_NOT ){									//一方向押しの場合はZ優先
		return( key_dir_z );
	}
	
	if( key_dir_z == DIR_NOT ){									//Zキー無し Xキー返し
		return( key_dir_x );
	}
	
	{															//斜め押し
		int move_dir = Player_DirMoveGet( jiki );
		
		if( move_dir != DIR_NOT ){
			if( key_dir_x == move_dir || key_dir_z == move_dir ){	//斜めの内どれかが移動方向
				return( move_dir );								//移動中と一致する方向を返す
			}
		}
		
		return( key_dir_z );									//一致しない場合はZ優先
	}
	
	return( DIR_NOT );
}
#endif

//--------------------------------------------------------------
/**
 * 動作キャンセル可能チェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=可能
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
		
		if( Jiki_WallHitAcmdCodeCheck(code) == TRUE ){			//壁ヒットはキャンセル可能
			return( TRUE );
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 壁ヒットアニメーションコードチェック
 * @param	code	AC_DIR_U等
 * @retval	int		TRUE=壁ヒットコード FALSE=違う
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
 * Bダッシュチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	prs		キープレス
 * @retval	int		TRUE=Bダッシュ
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
 * Bダッシュコードチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=Bダッシュアニメ FALSE=違う
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
 * 指定方向に移動させようとするとどうなるかチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		方向 DIR_UP等。
 * @retval	int		OBJ_MOVE_VALUE_STOP等
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
		GF_ASSERT( 0 && "Player_MoveSelectValueCheck()不正な形状" );
	}
	
	return( val );
}

//--------------------------------------------------------------
/**
 * 指定されたキー情報から自機が動く際に指定するアニメーションコマンドコードを取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	trg		キートリガ
 * @param	prs		キープレス
 * @param	speed	JIKI_FRAME_SPEED_32F等
 * @param	dash	ダッシュフラグ TRUE=ダッシュ可能　FALSE=ダッシュ不可
 * @param	hit     HITフラグ TRUE=HITを見る　FALSE=HITを見ない
 * @retval	u32		アニメコードAC_WALK_D_8F等
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
 * 自機がアニメーションコマンドをセットできるかどうか
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		TRUE=可能 FALSE=不可
 */
//--------------------------------------------------------------
int Player_AcmdSetCheck( PLAYER_STATE_PTR jiki )
{
	FIELD_OBJ_PTR fldobj = Player_FieldOBJGet( jiki );
	return( FieldOBJ_AcmdSetCheck(fldobj) );
}

//--------------------------------------------------------------
/**
 * 自機アニメーションコマンドセット
 * @param	jiki	PLAYER_STATE_PTR
 * @param	ac		アニメコードAC_DIR_U等
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
 * 自機の位置から指定方向先のアトリビュートを取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
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
 * 自機の位置から指定方向先のグリッド座標取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		DIR_UP等
 * @param	gx		グリッドX座標格納先
 * @param	gz		グリッドZ座標格納先
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
 * 自機の前方位置のグリッド座標取得
 * @param	jiki	PLAYER_STATE_PTR
 * @param	gx		グリッドX座標格納先
 * @param	gz		グリッドZ座標格納先
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
 * レコード　歩数カウント
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
 * 足元一本橋アトリビュートチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		振り向かせる方向
 * @retval	int		TRUE=一本橋ヒット
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
 * サイクリングロードチェック
 * @param	jiki	PLAYER_STATE_PTR
 * @param	attr	アトリビュート
 * @param	dir		入力方向
 * @retval	int		TRUE=サイクリングロード
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
//	デバッグ
//==============================================================================
//----
#ifdef PLAYER_DEBUG_MOVE
//----
/***************************************************************
 * デバッグ用プロトタイプ
 **************************************************************/

//==============================================================================
//	デバッグ移動メイン
//==============================================================================
//--------------------------------------------------------------
/**
 * デバッグ初期化
 * @param
 * @retval
 */
//--------------------------------------------------------------
void DEBUG_Player_Init( PLAYER_STATE_PTR jiki )
{
}

//--------------------------------------------------------------
//	アニメーションコマンドチェック
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
 * デバッグ移動
 * @param
 * @retval	int		TRUE=デバッグ移動
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
