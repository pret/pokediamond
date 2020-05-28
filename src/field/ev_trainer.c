/******************************************************************************
/**
 *
 * @file	ev_trainer.c
 * @brief	トレーナー視線イベント
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
#define EYE_MEET_MOVE_TCB_PRI (0xff)					///<視線移動TCBプライオリティ　超適当
#define EYE_MEET_GYOE_END_WAIT (30)						///<!マーク出現後の間　フレーム単位
#define EYE_MEET_MOVE_END_WAIT (8)						///<視線移動後の間　フレーム単位

//--------------------------------------------------------------
///	視線移動処理番号
//--------------------------------------------------------------
enum
{
	SEQNO_TRMOVE_INIT = 0,
	SEQNO_TRMOVE_OBJMOVE_WAIT,							///<動作停止待ち
	SEQNO_TRMOVE_JIKIMOVE_WAIT,							///<自機動作終了待ち
	SEQNO_TRMOVE_DIR_CHANGE,							///<方向変更
	SEQNO_TRMOVE_DIR_CHANGE_WAIT,						///<方向変更待ち
	SEQNO_TRMOVE_GYOE_SET,								///<!セット
	SEQNO_TRMOVE_GYOE_WAIT,								///<!待ち
	SEQNO_TRMOVE_HIDE_PULLOFF_SET,						///<隠れ蓑脱ぎセット
	SEQNO_TRMOVE_HIDE_PULLOFF_WAIT,						///<隠れ蓑終了待ち
	SEQNO_TRMOVE_GYOE_END_WAIT,							///<!終了後待ち
	SEQNO_TRMOVE_MOVE_RANGE_CHECK,						///<移動距離チェック
	SEQNO_TRMOVE_MOVE_START,							///<移動開始
	SEQNO_TRMOVE_MOVE,									///<移動中
	SEQNO_TRMOVE_MOVE_END_WAIT,							///<移動終了後待ち
	SEQNO_TRMOVE_JIKI_TURN_SET,							///<自機振り向きセット
	SEQNO_TRMOVE_JIKI_TURN,								///<自機振り向き
	SEQNO_TRMOVE_ACMD_END,								///<アニメ終了
	SEQNO_TRMOVE_END,									///<終了
};

//--------------------------------------------------------------
//	デバッグ
//--------------------------------------------------------------

//==============================================================================
//	typedef strcut
//==============================================================================
//--------------------------------------------------------------
///	視線ヒット格納
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
//	視線イベントワーク
//--------------------------------------------------------------
typedef struct
{
	int seq_no;											///<処理番号
	FIELDSYS_WORK *fsys;								///<FIELDSYS_WORK *
	FIELD_OBJ_PTR fldobj;								///<FIELD_OBJ_PTR
	TCB_PTR tcb_eye_meet;								///<TCB_PTR
}EYE_MEET_EVENT_WORK;

#define EYE_MEET_EVENT_WORK_SIZE (sizeof(EYE_MEET_EVENT_WORK)) ///<EYE_MEET_EVENT_WORKサイズ

//--------------------------------------------------------------
//	視線ヒット移動処理用ワーク
//--------------------------------------------------------------
typedef struct
{
	int seq_no;											///<処理番号
	int end_flag;										///<終了フラグ
	int dir;											///<移動方向
	int range;											///<移動距離
	int gyoe_type;										///<!タイプ
	int tr_type;										///<トレーナータイプ
	int sisen_no;										///<視線番号
	int count;											///<移動カウント
	EOA_PTR gyoe;										///<ギョエーEOA_PTR
	FIELD_OBJ_PTR fldobj;								///<移動を行うFIELD_OBJ_PTR
	PLAYER_STATE_PTR jiki;								///<自機PLAYER_STATE_PTR
}EYE_MEET_MOVE_WORK;

#define EYE_MEET_MOVE_WORK_SIZE (sizeof(EYE_MEET_MOVE_WORK)) ///<EYE_MEET_MOVE_WORKサイズ

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
//	トレーナー視線処理
//==============================================================================
//--------------------------------------------------------------
/**
 * トレーナー視線イベントチェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	vs2		ダブルバトル可能か TRUE=可能 FALSE=不可
 * @retval	int		TRUE=トレーナー視線イベント発動
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
	
	if( hit0.tr_type == SCR_EYE_TR_TYPE_SINGLE ){						//シングル
		FIELD_OBJ_PTR fldobj;
		EYE_MEET_HITDATA hit1;
		
		EventSet_Script( fsys, SCRID_TRAINER_MOVE_BATTLE, hit0.fldobj ); //スクリプト起動
		
		if( vs2 == FALSE || TrainerEyeCheck(fsys,fos,player,hit0.fldobj,&hit1) == FALSE ){
			EventSet_TrainerEyeData( fsys, hit0.fldobj,					//シングルセット
				hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_SINGLE, SCR_EYE_TR_0 );
			OS_Printf( "トレーナーシングルヒット\n" );
			return( TRUE );
		}
		
		EventSet_TrainerEyeData( fsys, hit0.fldobj,
			hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_TAG, SCR_EYE_TR_0 );
		EventSet_TrainerEyeData( fsys, hit1.fldobj,
			hit1.range, hit1.dir, hit1.scr_id, hit1.tr_id,
				SCR_EYE_TR_TYPE_TAG, SCR_EYE_TR_1 );
		
		OS_Printf( "トレーナータッグヒット　ダブル\n" );
		return( TRUE );
	}
	
	if( hit0.tr_type == SCR_EYE_TR_TYPE_DOUBLE ){						//ダブル
		FIELD_OBJ_PTR fldobj;
		EYE_MEET_HITDATA hit1;
		
		if( vs2 == FALSE ){												//ダブル不可
			return( FALSE );
		}
		
		fldobj = TrainerPairCheck( fsys, fos, hit0.fldobj, hit0.tr_id );
		TrainerEyeHitDataSet( &hit1, fldobj, hit0.range, hit0.dir );
		
		EventSet_Script( fsys, SCRID_TRAINER_MOVE_BATTLE, hit0.fldobj );//スクリプト起動
		
		EventSet_TrainerEyeData( fsys, hit0.fldobj,
				hit0.range, hit0.dir, hit0.scr_id, hit0.tr_id,
				SCR_EYE_TR_TYPE_DOUBLE, SCR_EYE_TR_0 );
		EventSet_TrainerEyeData( fsys, hit1.fldobj,
				hit1.range, hit1.dir, hit1.scr_id, hit1.tr_id,
				SCR_EYE_TR_TYPE_DOUBLE, SCR_EYE_TR_1 );
		
		OS_Printf( "トレーナーダブルヒット\n" );
		return( TRUE );
	}
	
	GF_ASSERT( 0 && "EvTrainerEyeCheck() 視線タイプ不正\n" );
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * トレーナー視線チェック
 * @param	fsys	FIELDSYS_WORK *
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	nonobj	対象外とするOBJ NULL=存在しない
 * @param	hit		EYE_MEET_HITDATA *
 * @retval	int		TRUE=トレーナー視線ヒット
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
					TrainerEyeHitDataSet( hit, fldobj, range, dir );		//未戦闘
					return( TRUE );
				}
			}
		}
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * 視線ヒットした情報を格納する
 * @param	hit		EYE_MEET_HITDATA
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	視線距離
 * @param	dir		移動方向
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
 * イベントタイプ取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		EV_TYPE_TRAINER等
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
//	視線チェック
//==============================================================================
//--------------------------------------------------------------
/**
 * トレーナー視線チェック　グローバル
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	jiki		PLAYER_STATE_PTR
 * @param	hit_dir		視線ヒット時の移動方向。DIR_UP等
 * @retval	int			視線ヒット時の自機までのグリッド距離。EYE_CHECK_NOHIT=エラー
 */
//--------------------------------------------------------------
int EvTrainer_EyeLangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int *hit_dir )
{
	return( TrEyeLangeCheck(fldobj,jiki,hit_dir) );
}

//--------------------------------------------------------------
/**
 * トレーナー視線範囲チェック
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	jiki		PLAYER_STATE_PTR
 * @param	hit_dir		視線ヒット時の移動方向。DIR_UP等
 * @retval	int			視線ヒット時の自機までのグリッド距離。EYE_CHECK_NOHIT=エラー
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
	
	if( type == EV_TYPE_TRAINER_EYEALL ){						//4方向
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
 * トレーナー視線チェック
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	dir		視線方向　DIR_UP等
 * @param	range	視線距離
 * @param	x		自機グリッドX
 * @param	z		自機グリッドz
 * @param	y		自機高さ
 * @retval	int		自機へのグリッド距離　EYE_CHECK_NOHIT=ヒットなし
 */
//--------------------------------------------------------------
static int TrEyeLineCheck( CONST_FIELD_OBJ_PTR fldobj, int dir, int range, int x, int z, int y )
{
	return( TrEyeLineCheckTbl[dir](fldobj,range,x,z,y) );
}

//--------------------------------------------------------------
/**
 * トレーナー視線チェック　上
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	視線距離
 * @param	jx		自機グリッドX
 * @param	jz		自機グリッドz
 * @param	jy		自機高さ
 * @retval	int		自機への距離　0=ヒットなし
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
 * トレーナー視線チェック　下
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	視線距離
 * @param	jx		自機グリッドX
 * @param	jz		自機グリッドz
 * @param	jy		自機高さ
 * @retval	int		自機への距離　0=ヒットなし
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
 * トレーナー視線チェック　左
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	視線距離
 * @param	jx		自機グリッドX
 * @param	jz		自機グリッドz
 * @param	jy		自機高さ
 * @retval	int		自機への距離　0=ヒットなし
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
 * トレーナー視線チェック　右
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	range	視線距離
 * @param	jx		自機グリッドX
 * @param	jz		自機グリッドz
 * @param	jy		自機高さ
 * @retval	int		自機への距離　0=ヒットなし
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
///	視線チェックテーブル
//--------------------------------------------------------------
static int (* const TrEyeLineCheckTbl[])(CONST_FIELD_OBJ_PTR,int range,int jx,int jz,int jy) =
{
	TrEyeLineCheck_Up,
	TrEyeLineCheck_Down,
	TrEyeLineCheck_Left,
	TrEyeLineCheck_Right,
};

//==============================================================================
//	視線判定　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 視線範囲移動判定
 * @param	fldobj		チェック対象FIELD_OBJ_PTR
 * @param	dir			移動方向
 * @param	range		移動距離
 * @retval	int			TRUE=移動不可
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
		ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;						//移動制限を無視する
		
		if( ret ){
			return( TRUE );										//移動制限以外でヒット
		}
		
		x += FieldOBJ_DirAddValueGX( dir );
		z += FieldOBJ_DirAddValueGZ( dir );
	}
	
	ret = FieldOBJ_MoveHitCheckNow( fldobj, x, y, z, dir );
	ret &= ~FLDOBJ_MOVE_HIT_BIT_LIM;							//移動制限を無視する
	
	if( ret == FLDOBJ_MOVE_HIT_BIT_OBJ ){						//OBJ衝突(自機)のみ
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * フィールドOBJからトレーナーID取得
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		トレーナーID
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
 * フィールドOBJからトレーナーID取得　グローバル
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	int		トレーナーID
 */
//--------------------------------------------------------------
int EvTrainerFldOBJTrainerIDGet( FIELD_OBJ_PTR fldobj )
{
	return( FldOBJTrainerIDGet(fldobj) );
}

//--------------------------------------------------------------
/**
 * 同一のトレーナーIDを持つ相方を探す
 * @param	fsys	FIELDSYS_WORK
 * @param	fos		FIELD_OBJ_SYS_PTR
 * @param	tr_obj	相方を探しているFIELD_OBJ_PTR
 * @param	tr_id	トレーナーID
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
	
	GF_ASSERT( 0 && "TrainerPairCheck() ペア不在…\n" );
	return( NULL );
}

//==============================================================================
//	視線ヒットによる移動
//==============================================================================
//--------------------------------------------------------------
/**
 * 視線移動処理追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		移動方向
 * @param	range	移動距離
 * @param	gyoe	!マーク制御
 * @param	tr_type	トレーナータイプ
 * @param	work_pos 視線ヒットワーク要素数 0=視線主 1=ペア
 * @retval	tcb		移動処理TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR EvTrainerEyeMoveSet( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe, int tr_type, int work_pos )
{
	return( TrEyeMeetMoveAddTcb(fldobj,jiki,dir,range,gyoe,tr_type,work_pos) );
}

//--------------------------------------------------------------
/**
 * 視線移動処理終了チェック
 * @param	tcb		EvTrainerEyeMoveSet()の戻り値
 * @retval	int 	TRUE=終了　FALSE=まだ
 */
//--------------------------------------------------------------
int EvTrainerEyeMoveEndCheck( TCB_PTR tcb )
{
	GF_ASSERT( tcb != NULL && "EvTrainerEyeMoveEndCheck() tcb = NULL" );
	return( TrEyeMeetMoveEndCheck(tcb) );
}

//--------------------------------------------------------------
/**
 * 視線移動処理終了
 * @param	tcb		EvTrainerEyeMoveSet()の戻り値
 * @retval	nothing
 */
//--------------------------------------------------------------
void EvTrainerEyeMoveEnd( TCB_PTR tcb )
{
	TrEyeMeetMoveEnd( tcb );
}

//--------------------------------------------------------------
/**
 * 視線移動処理追加
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @param	dir		移動方向
 * @param	range	移動距離
 * @retval	TCB_PTR	移動処理を行うTCB_PTR
 */
//--------------------------------------------------------------
static TCB_PTR TrEyeMeetMoveAddTcb( FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki,
		int dir, int range, int gyoe_type, int tr_type, int sisen_no )
{
	TCB_PTR tcb;
	EYE_MEET_MOVE_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_MOVE_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetMoveAddTcb()ワーク確保失敗" );
	
	memset( work, 0, EYE_MEET_MOVE_WORK_SIZE );
	
	work->dir = dir;
	work->range = range;
	work->gyoe_type = gyoe_type;
	work->tr_type = tr_type;
	work->sisen_no = sisen_no;
	work->fldobj = fldobj;
	work->jiki = jiki;
	
	tcb = TCB_Add( TrEyeMeetMoveTCB, work, EYE_MEET_MOVE_TCB_PRI );
	GF_ASSERT( tcb != NULL && "TrEyeMeetMoveAddTcb()TCB追加失敗" );
	
	return( tcb );
}

//--------------------------------------------------------------
/**
 * 視線移動処理終了チェック
 * @param	tcb		TrEyeMeetMoveAddTcb()の戻り値TCB_PTR
 * @retval	int		TRUE=終了
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
 * 視線移動処理終了
 * @param	tcb		TrEyeMeetMoveAddTcb()の戻り値TCB_PTR
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
 * 視線移動処理　TCB
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
 * 視線移動　初期化
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　OBJ動作終了待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　自機移動終了待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
		OS_Printf( "トレーナー動作コード=0x%x\n", code );
		
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
 * 視線移動　移動先へ向きを変える 
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　移動先へ向きを変える　待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　びっくりマーク出現
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　びっくりマーク表示終了待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　隠れ蓑脱ぎ
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　隠れ蓑脱ぎ終了待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　びっくりマーク表示終了後の間
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　移動距離チェック
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int EyeMeetMove_MoveRangeCheck( EYE_MEET_MOVE_WORK *work )
{
	if( work->range <= 1 ){									//自機目の前 移動する必要なし
		work->seq_no = SEQNO_TRMOVE_MOVE_END_WAIT;
		return( TRUE );	
	}

	work->seq_no = SEQNO_TRMOVE_MOVE_START;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 視線移動　移動開始
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　移動中
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int EyeMeetMove_Move( EYE_MEET_MOVE_WORK *work )
{
	if( FieldOBJ_AcmdEndCheck(work->fldobj) == FALSE ){
		return( FALSE );
	}
	
	work->range--;											//一歩減らす
	work->seq_no = SEQNO_TRMOVE_MOVE_RANGE_CHECK;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 視線移動　移動終了後、自機の方向へ向かせる
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　自機を振り向かせる
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　自機振り向き終了待ち
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
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
 * 視線移動　アニメ終了
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int EyeMeetMove_AcmdEnd( EYE_MEET_MOVE_WORK *work )
{
	FieldOBJ_AcmdEnd( work->fldobj );
//	FieldOBJ_StatusBit_OFF( work->fldobj, FLDOBJ_STA_BIT_PAUSE_MOVE );	//ポーズかけっぱ
	FieldOBJ_MoveCodeChange( work->fldobj, MV_DMY );
	
	work->seq_no = SEQNO_TRMOVE_END;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * 視線移動　終了
 * @param	work	EYE_MEET_MOVE_WORK
 * @retval	int		TRUE=再帰
 */
//--------------------------------------------------------------
static int EyeMeetMove_End( EYE_MEET_MOVE_WORK *work )
{
	work->end_flag = TRUE;
	return( FALSE );
}

//--------------------------------------------------------------
///	視線移動処理テーブル
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
//	スクリプトコマンド
//	add nohara
//==============================================================================
#if 0
//--------------------------------------------------------------
/**
 * 視線イベント起動 
 * @param	fsys		FIELDSYS_WORK
 * @param	fldobj		対象フィールドOBJ
 * @param	tcb			視線移動TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void TrEyeMeetEventStart( FIELDSYS_WORK *fsys, FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	EYE_MEET_EVENT_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_EVENT_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetEventStart()ワーク確保失敗" );
	
	memset( work, 0, EYE_MEET_EVENT_WORK_SIZE );
	
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->tcb_eye_meet = tcb;
	
	FieldEvent_Set( fsys, TrEyeMeetEvent, work );
}

//--------------------------------------------------------------
/**
 * 視線イベント終了
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
 * 視線イベント
 * @param	ev		GMEVENT_CONTROL	*
 * @retval	BOOL	TRUE=イベント終了
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
 * トレーナー視線移動TCB追加
 * @param	fldobj	対象のFIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE
 * @param	dir		移動方向
 * @param	range	移動距離
 * @retval	TCB_PTR	視線移動TCB_PTR
 */
//--------------------------------------------------------------
TCB_PTR EvCall_TrEyeMeetMoveAddTcb(
		FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki, int dir, int range )
{
	return( TrEyeMeetMoveAddTcb(fldobj,jiki,dir,range) );
}

//--------------------------------------------------------------
/**
 * トレーナー視線距離取得
 * @param	fldobj	対象FIELD_OBJ_PTR
 * @param	jiki	PLAYER_STATE_PTR
 * @retval	int		視線距離。ヒットなし=-1
 */
//--------------------------------------------------------------
int EvCall_TrEyeRangeCheck( CONST_FIELD_OBJ_PTR fldobj, PLAYER_STATE_PTR jiki )
{
	int dir;
	return( TrEyeLangeCheck(fldobj,jiki,&dir) );
}

//--------------------------------------------------------------
/**
 * 視線イベント起動 
 * @param	fsys		FIELDSYS_WORK
 * @param	fldobj		対象フィールドOBJ
 * @param	tcb			視線移動TCB_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void GMEVENT_Call_TrEyeMeetEventStart(
		FIELDSYS_WORK *fsys, GMEVENT_CONTROL * event, FIELD_OBJ_PTR fldobj, TCB_PTR tcb )
{
	EYE_MEET_EVENT_WORK *work;
	
	work = sys_AllocMemoryLo( HEAPID_FIELD, EYE_MEET_EVENT_WORK_SIZE );
	GF_ASSERT( work != NULL && "TrEyeMeetEventStart()ワーク確保失敗" );
	
	memset( work, 0, EYE_MEET_EVENT_WORK_SIZE );
	
	work->fsys = fsys;
	work->fldobj = fldobj;
	work->tcb_eye_meet = tcb;
	
	FieldEvent_Call( event, TrEyeMeetEvent, work );
}
#endif
