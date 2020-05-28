//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_data.h
 *	@brief		木の実ミキサー　データ管理部
 *	@author		tomoya takahashi
 *	@data		2006.05.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_DATA_H__
#define __NMIX_GAME_DATA_H__


#include "nmix_game_comm.h"

#include "savedata/poruto_util.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_DATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *		共通定数定義
 *
 */
//-----------------------------------------------------------------------------


#define NMIX_SOOP_SCORE_MAX	(9999)	// 得点最大

// 点移動距離スープスピード変更マクロ
#define NMIX_SOOP_SPEED		( 160 )
#define NMIX_SOOP_SPEED_GET(x)	( (x) * NMIX_SOOP_SPEED )
#define NMIX_SOOP_SPEED_RESET(x) ( (x) / NMIX_SOOP_SPEED )

// 回転計算半径
#define NMIX_SOOP_ROTA_GET_R	( 68 )


// スープ回転何かが起こる速度
#define NMIX_SOOP_KOBORE	( 3640 )
#define NMIX_SOOP_KOGE		( 910 )

// 再度こぼれたり、こげたりする　タイミング
#define NMIX_SOOP_KOBORE_RETIME	( 30 )
#define NMIX_SOOP_KOGE_RETIME	( 30 * 3 )

// 最大回転スピード
#define NMIX_SOOP_MAX_ROTA	( NMIX_SOOP_KOBORE )

// スープ拡大率最大
#define NMIX_SOOP_MAX_SCALE	( FX32_CONST( 0.25f ) )

// 回転角度を求める計算
GLOBAL s32	NMIX_DATA_CalcRota( int x, int y, int last_x, int last_y, int center_x, int center_y );


//-----------------------------------------------------------------------------
/**
 *
 *		子データ
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	子データ
//=====================================
typedef struct {
	int x;
	int y;
	int last_x;
	int last_y;
	s32 rota;
	BOOL last_touch_flg;
} NMIX_DATA_KO;
GLOBAL void NMIX_DATA_KoInit( NMIX_DATA_KO* p_data );
GLOBAL void NMIX_DATA_KoMain( NMIX_DATA_KO* p_data );
GLOBAL void NMIX_DATA_KoMake( NUTMIX_ONE* p_commdata, NMIX_DATA_KO* p_data );



//-----------------------------------------------------------------------------
/**
 *				親のみ必要なもの
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	スープ状態管理データ
//=====================================
typedef struct {
	u32	soop_type;	// 現在スープタイプ
	u32	rota_count;	// 回転数カウント
	s32 now_rota;	// 現在回転角度
	s32	sp_rota;	// 回転スピード

	BOOL ok_area;	// 大丈夫エリア
} NMIX_DATA_SOOP;

GLOBAL u16 NMIX_DATA_SoopRota( NMIX_DATA_SOOP* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 rota_way );
GLOBAL u16 NMIX_DATA_SoopGetRota( const NMIX_DATA_SOOP* cp_data );
GLOBAL u32 NMIX_DATA_SoopGetRotaCount( const NMIX_DATA_SOOP* cp_data );
GLOBAL void NMIX_DATA_SoopSetType( NMIX_DATA_SOOP* p_data, int type );
GLOBAL s32 NMIX_DATA_SoopGetRotaSpeed( const NMIX_DATA_SOOP* cp_data );

//-------------------------------------
//	スープスピードにより変わるデータ管理部
//=====================================
typedef struct {
	u32 koge_count;			// こげｶｳﾝﾀ
	u32 kobosi_count;		// こぼしｶｳﾝﾀ
	// こげ
	u32 speed_none_count;	// こげ続けている時間
	// こぼれ
	u32 speed_over_count;	// こぼれ続けている時間

	// エフェクトリクエスト
	u32 koge_eff;
	BOOL first_koge_eff;
	BOOL kobosi_eff;
} NMIX_DATA_SOOP_SPEED;

GLOBAL void NMIX_DATA_SoopSpeedMain( NMIX_DATA_SOOP_SPEED* p_data, s32 speed, int soop_type );
GLOBAL BOOL NMIX_DATA_SoopSpeedKobore( s32 speed, int soop_type );
GLOBAL BOOL NMIX_DATA_SoopSpeedKoge( s32 speed, int soop_type );
GLOBAL fx32 NMIX_DATA_SoopSpeedGraScale( u16 speed, int soop_type );


//-------------------------------------
//	回転方向管理
//=====================================
typedef struct {
	int rota_way_req;	// 回転してほしい方向
	int rota_way_count;	// 次の方向チェックまでのカウント値
	int left_par;		// 左の出るパーセンテージ　乱数は最大５	初期は2としておく, 2以下なら左　大きいなら右　右が出たらleft_parを足し 左が出たらleft_parを引く
	BOOL rota_way_chg;
} NMIX_DATA_ROTA_WAY_CONT;
GLOBAL void NMIX_DATA_RotaWayCont_Init( NMIX_DATA_ROTA_WAY_CONT* p_work );
GLOBAL void NMIX_DATA_RotaWayCont_Main( NMIX_DATA_ROTA_WAY_CONT* p_work, int soop_type, s32 speed, BOOL team_work );

GLOBAL BOOL NMIX_DATA_RotaWayReverseCheck( const NMIX_DATA_ROTA_WAY_CONT* cp_work, s32 speed );

//-------------------------------------
//	スープ進化管理
//=====================================
typedef struct {
	int next_time;
	int rota_alpha;
	int soop_type;	// 今のスープタイプ
} NMIX_DATA_SOOP_ADD;
GLOBAL BOOL NMIX_DATA_SoopAdd_Main( NMIX_DATA_SOOP_ADD* p_work, NMIX_DATA_SOOP* p_soop );
#define NMIX_DATA_SOOPADD_NEXT_TIME	( 20*30 )	// 強制変更タイム
#define NMIX_DATA_SOOP_COOK_MAX_TIME	( NMIX_DATA_SOOPADD_NEXT_TIME * 3 )	// 調理時間の最大


//-------------------------------------
//	チームワークプレイ管理
//=====================================
typedef struct {
	int team_work_time;	// TEAMWORKを発揮した時間
	int team_work_time_add_wait;
	BOOL team_work_time_add_flg;	// TRUE	TEAMWORK得点中
	BOOL team_work_req;	// エフェクト発射リクエスト
} NMIX_DATA_TEAMWORK;
GLOBAL void NMIX_DATA_TeamWork_Main( NMIX_DATA_TEAMWORK* p_work, const NUTMIX_GAME_COMM_PACK* cp_comm_pack, int comm_count, s32 speed, int soop_type, BOOL ok_area, BOOL reverse );
#define NMIX_DATA_TEAMWORK_AREA	( 32 )	// 半径これいないに入っているかチェックする
#define NMIX_DATA_TEAMWORK_EFF_TIMING	( 1 )	// ~カウントに１かいだす
#define NMIX_DATA_TEAMWORK_EFF_ADD_WAIT	( 4 )	// 最低でもこのシンク数一緒にいないと、TEAMWORK得点がはいらない


//-------------------------------------
//	全体管理部分
//=====================================
typedef struct {
	u32	cook_time;	// 調理時間
	u32 poruto_type;	// ポルトのタイプ
	u32 poruto_lv;		// ポルトのレベル
	NMIX_DATA_ROTA_WAY_CONT rota_waycont;
	NMIX_DATA_SOOP soop_cont;
	NMIX_DATA_SOOP_SPEED soop_speed_data;
	NMIX_DATA_SOOP_ADD soop_add;
	NMIX_DATA_TEAMWORK team_work;
} NMIX_DATA_OYA;

GLOBAL void NMIX_DATA_OyaInit( NMIX_DATA_OYA* p_data );
GLOBAL BOOL NMIX_DATA_OyaMain( NMIX_DATA_OYA* p_data, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count );
GLOBAL void NMIX_DATA_OyaCommDataMake( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );
GLOBAL void NMIX_DATA_OyaCookCountAdd( NMIX_DATA_OYA* p_data );
GLOBAL void NMIX_DATA_OyaCommDataMake_Init( NMIX_DATA_OYA* p_data, NUTMIX_OYA* p_oya, int comm_count );

GLOBAL void NMIX_DATA_OyaCalcPorutoData( NMIX_DATA_OYA* p_data, PORUTO_DATA* p_poruto, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, u32 heapID );

GLOBAL void NMIX_DATA_OyaCommDataMake_Result( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );

#ifdef NMIX_DEBUG_DUMMY_RESULT_ON
GLOBAL void NMIX_DATA_OyaCommDataMake_Result_MaxDebug( NMIX_DATA_OYA* p_data, NUTMIX_GAME_COMM_PACK* p_comm_pack, int comm_count );
#endif // NMIX_DEBUG_DUMMY_RESULT_ON


#undef	GLOBAL
#endif		// __NMIX_GAME_DATA_H__

