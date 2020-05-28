//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys.c
 *@brief	お天気システム
 *@author	tomoya takahashi
 *@data		2005.04.25
 *
 *	このシステムは、OAM　フォグ　BG２　を使用します。
 *
 *	新天候登録手順
 *	１：ヘッダの列挙体に新天候の定数名を追加
 *	２：グラフィック（セル、BG）を追加するときは、天気グラフィックファイルテーブルに追加
 *	３：コントロールタスク関数を作成し、WeatherSysDataテーブルにデータを設定
 *	４：コントロールタスク関数内は、シーケンスで管理することを決まりにしているので、
 *	　　初期化、フェードイン、メイン、フェードアウト、破棄のシーケンスに分けて天候を作成
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "fieldmap_work.h"
#include "field_glb_state.h"

#include "system/clact_util.h"
#include "system/render_oam.h"

#include "field/weather_sys.naix"

#include "system/arc_util.h"
#include "field_hblank.h"

#include "system/snd_tool.h"
#include "system/laster.h"

#define __WEATHER_SYS_H_GLOBAL
#include "weather_sys.h"


#define USE_HEAPID	( HEAPID_FIELD )
//#define USE_HEAPID	( HEAPID_WEATHER )



//-----------------------------------------------------------------------------
/**
 *
 *					天気管理システム
 * 
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *			定数定義
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//		天気変更タスク定数
//=====================================
enum{
	WEATHER_CHENGE_NOW_FADEOUT_START,
	WEATHER_CHENGE_NOW_FADEOUT,
	WEATHER_CHENGE_NEXT_INIT_START,
	WEATHER_CHENGE_NEXT_INIT,
	WEATHER_CHENGE_NEXT_FADEIN_START,
	WEATHER_CHENGE_END,
	
	WEATHER_CHENGE_NONE,		// リクエスト無し状態
};

//-------------------------------------
//		天気変更タスク定数
//=====================================
enum{
	WEATHER_CHENGE_WL_NEXT_INIT_START,
	WEATHER_CHENGE_WL_NEXT_INIT,
	WEATHER_CHENGE_WL_NOW_FADEOUTIN_START,
	WEATHER_CHENGE_WL_NOW_FADEOUTIN,
	WEATHER_CHENGE_WL_END,
};

//-------------------------------------
//	天気変更種類
//=====================================
enum{
	WEATHER_CHANGE_SINGLE_TASK,
	WEATHER_CHANGE_MULTI_TASK,
};


#define WEATHER_TCB_CHG_PRI			( 0 )
#define WEATHER_TCB_DIV_LOAD_PRI	( 1 )
#define WEATHER_TCB_CIRCLEINIT_PRI	( 120 )
#define WEATHER_TCB_CIRCLEEND_PRI	( 128 )


#define WEATHER_SND_FADE_OUT_SYNC	( 0 )


//-----------------------------------------------------------------------------
/**
 *			構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	天気管理システム
//	
//=====================================
typedef struct _WEATHER_MANAGER{
	// 天気システム
	WEATHER_CONT_PTR	weather_sys;

	// 管理データ
	int now_play_weather;	// 実行中の天気

	// 変更フェード用データ
	int next_play_weather;	// 次に実行する天気
	int chenge_seq;			// 天気変更シーケンス
	int booking_weather;		// 変更後設定天気	（天気変更中に天気変更リクエストが来たときに格納）
	TCB_PTR tcb;			// 天気変更TCB
} WEATHER_MANAGER;

//-----------------------------------------------------------------------------
/**
 *			プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeTcb( TCB_PTR tcb, void* work );
static void WEATHER_ChangeWithLastTcb( TCB_PTR tcb, void* work );
static int WEATHER_ChangeReqFuncNoGet( int now_weather, int next_weather );

//-----------------------------------------------------------------------------
/**
 *		実装部
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	天気で使用するヒープ領域の作成
 *
 *	@param	heapid	親ヒープ
 */
//-----------------------------------------------------------------------------
void WEATHER_CreateHeap( u32 heapid )
{
	//sys_CreateHeap( heapid, HEAPID_WEATHER, 0xa000 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気で使用するヒープ領域の破棄
 */
//-----------------------------------------------------------------------------
void WEATHER_DeleteHeap( void )
{
	//sys_DeleteHeap( HEAPID_WEATHER );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気管理システム作成
 *
 *	@param	fsys		フィールドシステムワーク
 *
 *	@return	天気管理システム
 *
 *
 */
//-----------------------------------------------------------------------------
WEATHER_MANAGER_PTR WEATHER_Init( FIELDSYS_WORK * fsys )
{
	WEATHER_MANAGER_PTR	wmp;	

	// 天気管理システムメモリ確保
	wmp = sys_AllocMemory( USE_HEAPID, sizeof(WEATHER_MANAGER) );
	memset( wmp, 0, sizeof(WEATHER_MANAGER) );

	// 天気システム作成
	wmp->weather_sys = InitWeatherSys( fsys );

	// 管理データ初期化
	wmp->now_play_weather = WEATHER_SYS_SUNNY;

	// 天気変更タスクデータ
	wmp->next_play_weather = WEATHER_SYS_SUNNY;
	wmp->chenge_seq = WEATHER_CHENGE_NONE;
	wmp->tcb = NULL;
	wmp->booking_weather = WEATHER_SYS_NUM;

	// OAM描画
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );


	return wmp;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気管理システム破棄
 *
 *	@param	pWes	天気管理システム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WEATHER_Delete( WEATHER_MANAGER_PTR pWes )
{
	// 変更TCB破棄
	if( pWes->tcb ){
		TCB_Delete( pWes->tcb );
	}
	
	// 天気システム破棄
	DestWeatherSys( &pWes->weather_sys );

	memset( pWes, 0, sizeof(WEATHER_MANAGER) );
	sys_FreeMemoryEz( pWes );
	pWes = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気設定　直ちに指定した天気になります。
 *
 *	@param	pWes	天気管理システム
 *	@param	no		天気ナンバー
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
void WEATHER_Set( WEATHER_MANAGER_PTR pWes, int no )
{
	BOOL check;

	// 変更中
	GF_ASSERT( pWes->chenge_seq == WEATHER_CHENGE_NONE );

	if( pWes->now_play_weather == no ){
		return ;
	}
	
	// 今の天気破棄
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_DEST, pWes->now_play_weather );
	GF_ASSERT( check );	// 破棄失敗

	// 次の天気開始
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_INIT, no );
	GF_ASSERT( check );	// 初期化失敗
	check = ControlWeatherSys( pWes->weather_sys, WEATHER_SYS_START_NOFADE, no );
	GF_ASSERT( check );	// 開始失敗

	// 実行天気設定
	pWes->now_play_weather = no;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気変更リクエスト　今までの天気をフェードアウトさせ、徐々に指定した天気になります。
 *
 *	@param	pWes		天気管理システム
 *	@param	no			天気ナンバー
 *
 *	@retval	TRUE		リクエスト成功
 *	@retval	FALSE		リクエスト失敗	実行中のリクエストがある
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WEATHER_ChengeReq( WEATHER_MANAGER_PTR pWes, int no )
{
	int change_mode;

	// 実行中のリクエストがあるかチェック
	if( pWes->chenge_seq != WEATHER_CHENGE_NONE ){
		pWes->booking_weather = no;	// 予約
		return TRUE;
	}

	// 今の天気が一緒なら何もしない
	if( pWes->now_play_weather == no ){
		return TRUE;
	}

	GF_ASSERT( pWes->tcb == NULL );
	
	// 次の天気のデータ設定
	pWes->next_play_weather = no;

	change_mode = WEATHER_ChangeReqFuncNoGet( pWes->now_play_weather ,pWes->next_play_weather );

	if( change_mode == WEATHER_CHANGE_SINGLE_TASK ){
		pWes->chenge_seq = WEATHER_CHENGE_NOW_FADEOUT_START;
		// タスク登録
		pWes->tcb = TCB_Add( WEATHER_ChangeTcb, pWes, WEATHER_TCB_CHG_PRI );
	}else{
		pWes->chenge_seq = WEATHER_CHENGE_WL_NEXT_INIT_START;
		// タスク登録
		pWes->tcb = TCB_Add( WEATHER_ChangeWithLastTcb, pWes, WEATHER_TCB_CHG_PRI );
	}


	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在実行中の天気
 *
 *	@param	pWes	ワーク
 *
 *	@return	天気ナンバー
 */
//-----------------------------------------------------------------------------
u32 WEATHER_GetNow( WEATHER_MANAGER_PTR pWes )
{
	return pWes->now_play_weather;
}


//----------------------------------------------------------------------------
/**
 *	@brief	前のものを出しつつ次の物を出す
 *
 *	@param	pWes	天候ワーク
 *	@param	no		変更ナンバー
 *
 *	@retval	TRUE		リクエスト成功
 *	@retval	FALSE		リクエスト失敗	実行中のリクエストがある
 */
//-----------------------------------------------------------------------------
BOOL WEATHER_ChengeReqWithLast( WEATHER_MANAGER_PTR pWes, int no )
{

	// 実行中のリクエストがあるかチェック
	if( pWes->chenge_seq != WEATHER_CHENGE_NONE ){
		pWes->booking_weather = no;	// 予約
		return TRUE;
	}

	// 今の天気が一緒なら何もしない
	if( pWes->now_play_weather == no ){
		return TRUE;
	}

	GF_ASSERT( pWes->tcb == NULL );
	
	// 次の天気のデータ設定
	pWes->next_play_weather = no;
	pWes->chenge_seq = WEATHER_CHENGE_WL_NEXT_INIT_START;

	// タスク登録
	pWes->tcb = TCB_Add( WEATHER_ChangeWithLastTcb, pWes, WEATHER_TCB_CHG_PRI );

	return TRUE;
}


//-----------------------------------------------------------------------------
/**
 *		天気管理システム	プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気変更タスク
 *
 *	@param	tcb		タスクワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeTcb( TCB_PTR tcb, void* work )
{
	WEATHER_MANAGER_PTR wmp = work;
	BOOL check;

	switch( wmp->chenge_seq ){
	// 今の天気フェードアウト	開始
	case WEATHER_CHENGE_NOW_FADEOUT_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_END, wmp->now_play_weather );
		GF_ASSERT( check );		// フェードアウト処理開始失敗
		wmp->chenge_seq++;
		break;
		
	// 今の天気フェードアウト	終了待ち
	case WEATHER_CHENGE_NOW_FADEOUT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->now_play_weather );
		if( check != WEATHER_SYS_MOVE_DO ){
			check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_DEST, wmp->now_play_weather );
			GF_ASSERT( check );	// 破棄失敗
			wmp->chenge_seq++;
		}
		break;

	// 分割初期化スタート
	case WEATHER_CHENGE_NEXT_INIT_START:
		OS_Printf( "フェードイン開始\n" );
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_INIT_DIV, wmp->next_play_weather );
		GF_ASSERT( check );		// 初期化失敗
		wmp->chenge_seq++;
		break;
		
	// 分割初期化終了待ち
	case WEATHER_CHENGE_NEXT_INIT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->next_play_weather );
		if( check != WEATHER_SYS_MOVE_INIT ){
			wmp->chenge_seq++;
		}
		break;
		
	// 次の天気フェードイン		開始
	case WEATHER_CHENGE_NEXT_FADEIN_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_START, wmp->next_play_weather );
		GF_ASSERT( check );		// フェードイン開始失敗
		wmp->chenge_seq++;

		wmp->now_play_weather = wmp->next_play_weather;
		wmp->next_play_weather = WEATHER_SYS_SUNNY;
		
		break;
		
	// タスク終了
	case WEATHER_CHENGE_END:
		wmp->chenge_seq = WEATHER_CHENGE_NONE;	// リクエストなし状態にする
		wmp->tcb = NULL;
		TCB_Delete( tcb );

		// 予約チェック
		if( wmp->booking_weather != WEATHER_SYS_NUM ){
			// wmp->booking_weatherの天気に変更する
			WEATHER_ChengeReq( wmp, wmp->booking_weather );
			wmp->booking_weather = WEATHER_SYS_NUM;
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気変更タスク		WithLast
 *
 *	@param	tcb		タスクワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void WEATHER_ChangeWithLastTcb( TCB_PTR tcb, void* work )
{
	WEATHER_MANAGER_PTR wmp = work;
	BOOL check;

	switch( wmp->chenge_seq ){
	// 分割読み込み開始
	case WEATHER_CHENGE_WL_NEXT_INIT_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_INIT_DIV, wmp->next_play_weather );
		GF_ASSERT( check );		// 初期化失敗
		wmp->chenge_seq++;
		break;

	// 分割読み込み終了チェック
	case WEATHER_CHENGE_WL_NEXT_INIT:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->next_play_weather );
		if( check != WEATHER_SYS_MOVE_INIT ){
			wmp->chenge_seq++;
		}
		break;
		
	// フェード開始
	case WEATHER_CHENGE_WL_NOW_FADEOUTIN_START:
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_END_NOFOG, wmp->now_play_weather );
		GF_ASSERT( check );		// フェードアウト処理開始失敗
		check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_START_WITHFOG, wmp->next_play_weather );
		GF_ASSERT( check );		// フェードイン開始失敗
		wmp->chenge_seq++;
		break;
		
	// フェード終了チェック
	case WEATHER_CHENGE_WL_NOW_FADEOUTIN:
		check = CheckMoveWeatherSys( wmp->weather_sys, wmp->now_play_weather );
		if( check != WEATHER_SYS_MOVE_DO ){
			check = ControlWeatherSys( wmp->weather_sys, WEATHER_SYS_DEST, wmp->now_play_weather );
			GF_ASSERT( check );	// 破棄失敗
			wmp->chenge_seq++;
		}
		break;
		
	case WEATHER_CHENGE_WL_END:
		wmp->now_play_weather = wmp->next_play_weather;
		wmp->next_play_weather = WEATHER_SYS_SUNNY;
		
		wmp->chenge_seq = WEATHER_CHENGE_NONE;	// リクエストなし状態にする
		wmp->tcb = NULL;
		TCB_Delete( tcb );


		// 予約チェック
		if( wmp->booking_weather != WEATHER_SYS_NUM ){
			// wmp->booking_weatherの天気に変更する
			WEATHER_ChengeReq( wmp, wmp->booking_weather );
			wmp->booking_weather = WEATHER_SYS_NUM;
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気変更
 *
 *	@param	now_weather		今の天気
 *	@param	next_weather	次の天気
 *
 *	@retval	WEATHER_CHANGE_SINGLE_TASK	SINGLEタスクでの変更
 *	@ratval WEATHER_CHANGE_MULTI_TASK	MULTIタスクでの変更
 */
//----------------------------------	-------------------------------------------
static int WEATHER_ChangeReqFuncNoGet( int now_weather, int next_weather )
{
	int ret = WEATHER_CHANGE_SINGLE_TASK;
	
	switch( now_weather ){
	case WEATHER_SYS_SNOW:		// 雪		OAM FOG
		if( (next_weather == WEATHER_SYS_SNOWSTORM) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;

	case WEATHER_SYS_SNOWSTORM:	// 吹雪		OAM FOG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
		
	case WEATHER_SYS_SNOW_STORM_BG:// BG使用吹雪	OAM FOG BG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOWSTORM) ||
			(next_weather == WEATHER_SYS_SNOWSTORM_H) ){
		
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
		
	case WEATHER_SYS_SNOWSTORM_H:	// 北海道雪	OAM FOG BG
		if( (next_weather == WEATHER_SYS_SNOW) ||
			(next_weather == WEATHER_SYS_SNOW_STORM_BG) ||
			(next_weather == WEATHER_SYS_SNOWSTORM) ){
			ret = WEATHER_CHANGE_MULTI_TASK;
		}
		break;
	
	default:
		break;
	}

	return ret;
}




//-----------------------------------------------------------------------------
/**
 *
 *		天気システム
 *
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------
#define		WEATHER_RES_NUM	(4)		// 管理するリソースの数
#define		WEATEHR_OBJ_MAX	(64)	// オブジェクト最大数
#define		WEATEHR_OBJDATA_MAX	(64)// オブジェクトデータ最大数
#define		WEATHER_RENDER_X		(0)	// レンダラ横
#define		WEATHER_RENDER_Y		(0)	// レンダラ縦
#define		WEATHER_RENDER_WIDTH	(255<< FX32_SHIFT)	// レンダラ幅
#define		WEATHER_RENDER_HEIGHT	(192 << FX32_SHIFT)	// レンダラ高さ

#define WEATHER_OBJ_MINTURN_X	(-64*FX32_ONE)
#define WEATHER_OBJ_MINTURN_Y	(-64*FX32_ONE)
#define WEATHER_OBJ_MAXTURN_X	(WEATHER_RENDER_WIDTH + 64*FX32_ONE)
#define WEATHER_OBJ_MAXTURN_Y	(WEATHER_RENDER_HEIGHT + 64*FX32_ONE)

#define		WEATHER_CONTROL_PRI	(4)		// 天気管理タスクの優先度
#define		WEATHER_CLACT_DRAW_TCB_PRI	(10)	// 天気アクター描画タスク
#define		WEATHER_OBJ_PRI		(5)		// 天気オブジェタスクの優先度
#define		WEATHER_SYS_BG_2_DRAW_PRI	(1)	// お天気システムBG表示順位
#define		WEATHER_GRAPHIC_NONE	(0xffffffff)	// グラフィックなし

#define		SCREEN_SIZE (32 * 32)
#define		WEATHER_PLTT_OFS	(6)		// 使用するパレット
#define		WEATHER_LIGHT		(2)		// 天気用ライト

#define		WEATHER_FOG_DEPTH_DEFAULT	( 0x6F6F )	// フォグデフォルト値
#define		WEATHER_FOG_SLOPE_DEFAULT	( 3 )

#define WH_COLOR_R(x)	( ((x) >> GX_RGB_R_SHIFT) & 0x1f )
#define WH_COLOR_G(x)	( ((x) >> GX_RGB_G_SHIFT) & 0x1f )
#define WH_COLOR_B(x)	( ((x) >> GX_RGB_B_SHIFT) & 0x1f )

// フォグフェード用
#define FOG_DEPTH_COUNT_MAX		(127)
#define FOG_TBL_SUB_FADEIN	( 1 )
#define FOG_TBL_SUB_FADEOUT	( -1 )

//-------------------------------------
//	BGデータ
//=====================================
#define WEATHER_BG_CONTROL_NUM	( 9 )


//-------------------------------------
//		デフォルトシーケンス
//=====================================
enum{
	WEATHER_SEQ_INIT=0,		// 初期化
	WEATHER_SEQ_FADEIN,		// フェードイン
	WEATHER_SEQ_NO_FADE,	// フェード無し時の初期化
	WEATHER_SEQ_MAIN,		// メイン処理
	WEATHER_SEQ_FADEOUT,	// フェードアウト
	WEATHER_SEQ_DEST,		// 完全破棄
};

//-------------------------------------
//	フォグ設定定数
//=====================================
enum{
	WEATHER_FOG_NONE,		// フォグの設定なし
	WEATEHR_FOG_NEW,		// フォグを新しく初期化して開始
	WEATHER_FOG_WITH,		// 前のフォグ設定を残しつつ開始
};


//-------------------------------------
//	雨管理関数定数
//=====================================
#define	WEATHER_RAIN_TIMING_MIN		(1)							// 雨を出すタイミング最小
#define WEATHER_RAIN_TIMING_MAX		(8)						// 雨を出すタイミング最大
#define WEATHER_RAIN_TIMING_ADD		(1)							// タイミングを減らす数
#define WEATHER_RAIN_ADD_START		(1)							// 最初の同時に雨を登録する数
#define WEATHER_RAIN_ADD_TIMING		(1)							// 雨のタイミングをこれ回変更したら１回増やす
#define WEATHER_RAIN_ADD			(2)							// 登録する数を増やす数
#define	WEATHER_RAIN_ADD_MAIN		(20)						// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_RAIN_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_RAIN_NOFADE_OBJ_START_DUST_NUM	( 10 )			// 何個単位で変化させるか
#define	WEATHER_RAIN_NOFADE_OBJ_START_DUST_MOVE	( 1 )			// ずらして動作させる値

/*== フォグ ==*/
#define	WEATHER_RAIN_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_RAIN_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_RAIN_FOG_START		(0)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_RAIN_FOG_START_END	(0)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_RAIN_FOG_OFS		(0x300)

/*== 雨オブジェクト ==*/
#define WEATHER_RAIN_SPEED_X		(-5)						// 横に進むスピード
#define WEATHER_RAIN_SPEED_Y		(10)						// たてに進むスピードベース
#define	WEATHER_RAIN_END_MIN		(1)							// 終了カウンタ最小
#define WEATHER_RAIN_END_MAX		(3)							// 終了カウンタ最大
#define	WEATHER_RAIN_START_X_BASE	(0)							// ベースになるX開始座標
#define	WEATHER_RAIN_MUL_X			(15)						// ベースに雨の種類分足す値
#define	WEATHER_RAIN_START_X_MAX	(270)						// X開始座標乱数の最大値
#define	WEATHER_RAIN_START_Y		(-96)						// Y開始座標
#define	WEATHER_RAIN_SPEED_ERR		(20)						// スピード補正値

/*== 雨グラフィック構成データ ==*/
#define WEATHER_RAIN_GRAPHIC_CELL	( 0 )
#define WEATHER_RAIN_GRAPHIC_BG		( WEATHER_GRAPHIC_NONE )

//-------------------------------------
//	雪管理関数定数
//=====================================
#define	WEATHER_SNOW_TIMING_MIN		(8)				// 雪を出すタイミング最小
#define WEATHER_SNOW_TIMING_MAX		(20)				// 雪を出すタイミング最大
#define WEATHER_SNOW_TIMING_ADD		(5)					// タイミングを減らす数
#define	WEATHER_SNOW_ADD_TIMING		(1)					// １度のオブジェ登録数を増やすタイミング
#define	WEATHER_SNOW_ADD			(0)					// オブジェ登録数を足す値
#define WEATHER_SNOW_MAIN			(1)					// メインではこれだけ登録

/*== フェード無し開始の時 ==*/
#define WEATHER_SNOW_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_SNOW_NOFADE_OBJ_START_DUST_NUM	( 2 )			// 何個ずつずらすか
#define	WEATHER_SNOW_NOFADE_OBJ_START_DUST_MOVE	( 24 )			// ずらして動作させる値

/*== フォグ ==*/
#define	WEATHER_SNOW_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_SNOW_FOG_TIMING_END	(2)							// に１回フォグテーブルを操作
#define WEATHER_SNOW_FOG_START		(16)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_FOG_START_END	(32)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_FOG_OFS		(0x300)

/*== 雪オブジェクト ==*/
#define	WEATHER_SNOW_ADD_TMG_X_BASE	(4)					// 雪のスピードを足すタイミング
#define	WEATHER_SNOW_ADD_TMG_X_RAN	(2)					// 雪のスピードを足すタイミング乱数値
#define	WEATHER_SNOW_ADD_TMG_Y_BASE	(1)					// 雪のスピードを足すタイミング
#define	WEATHER_SNOW_ADD_TMG_Y_RAN	(2)					// 雪のスピードを足すタイミング乱数値

#define	WEATHER_SNOW_START_X_BASE	(-32)						// ベースになるX開始座標
#define	WEATHER_SNOW_START_X_MAX	(414)						// X開始座標乱数の最大値
#define WEATHER_SNOW_OBJ_NUM		(4)					// オブジェ種類

#define WEATHER_SNOW_OBJ_AUTODEST_TIMING_MAX ( 60 )	// 自滅タイム　最大
#define WEATHER_SNOW_OBJ_AUTODEST_TIMING_MIN ( 4 )	// 自滅タイム　最小

/*== 雪グラフィック構成データ ==*/
#define WEATHER_SNOW_GRAPHIC_CELL	( 3 )
#define WEATHER_SNOW_GRAPHIC_BG		( WEATHER_GRAPHIC_NONE )


//-------------------------------------
//	吹雪管理関数定数
//=====================================
#define	WEATHER_SSNOW_TIMING_MIN		(3)							// 雨を出すタイミング最小
#define WEATHER_SSNOW_TIMING_MAX		(30)						// 雨を出すタイミング最大
#define WEATHER_SSNOW_TIMING_ADD		(5)							// タイミングを減らす数
#define WEATHER_SSNOW_ADD_START			(1)							// 最初の同時に雨を登録する数
#define WEATHER_SSNOW_ADD_TIMING		(2)							// 雨のタイミングをこれ回変更したら１回増やす
#define WEATHER_SSNOW_ADD				(1)							// 登録する数を増やす数
#define WEATHER_SSNOW_ADD_END			(-3)							// 登録する数を増やす数
#define	WEATHER_SSNOW_ADD_MAIN			(6)							// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_SSNOW_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM		( 2 )			// 何個ずつずらすか
#define	WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE	( 3 )			// ずらして動作させる値

/*== フォグ ==*/
#define	WEATHER_SSNOW_FOG_TIMING		(2)							// に１回フォグテーブルを操作
#define	WEATHER_SSNOW_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_SSNOW_FOG_START			(8)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SSNOW_FOG_START_END		(0)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SSNOW_FOG_OFS			(-0x200)

/*== 雪オブジェクト ==*/
#define WEATHER_SSNOW_SPEED_X		(-1)						// 横に進むスピード
#define	WEATHER_SSNOW_END_MIN		(4)							// 終了カウンタ最小
#define WEATHER_SSNOW_END_MAX		(46)						// 終了カウンタ最大
#define WEATHER_SSNOW_END_NUM		(WEATHER_SSNOW_END_MAX - WEATHER_SSNOW_END_MIN)	// カウンタの値の数
#define	WEATHER_SSNOW_END_DIV		((WEATHER_SSNOW_END_NUM / 3)+1)	// オブジェクトの種類を計算するとき割る値
#define	WEATHER_SSNOW_START_X_BASE	(-20)						// ベースになるX開始座標
#define	WEATHER_SSNOW_MUL_X			(20)						// ベースに雪の種類分足す値
#define	WEATHER_SSNOW_START_X_MAX	(420)						// X開始座標乱数の最大値
#define	WEATHER_SSNOW_START_Y		(-8)						// Y開始座標
#define	WEATHER_SSNOW_SPEED_ADD_TMG	(20)						// X座標のスピードを上げるタイミング

#define	WEATHER_SSNOW_ADD_SP_TMG_NUM (4)						// スピードを変更するタイミングの数
#define	WEATHER_SSNOW_ADD_SP_TMG_TMG (200)						// スピードを変更するタイミングのタイミング

/*== 吹雪グラフィック構成データ ==*/
#define WEATHER_SSNOW_GRAPHIC_CELL	( 1 )
#define WEATHER_SSNOW_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

/*== 吹雪BGグラフィック構成データ ==*/
#define WEATHER_SSNOW_BG_GRAPHIC_CELL	( 1 )
#define WEATHER_SSNOW_BG_GRAPHIC_BG	( 0 )


//-----------------------
// 北海道雪
//=======================
#define	WEATHER_SNOW_S_TIMING_MIN		(1)							// 雪を出すタイミング最小
#define WEATHER_SNOW_S_TIMING_MAX		(12)						// 雪を出すタイミング最大
#define WEATHER_SNOW_S_TIMING_ADD		(4)							// タイミングを減らす数
#define WEATHER_SNOW_S_ADD_START		(4)							// 最初の同時に雪を登録する数
#define WEATHER_SNOW_S_ADD_TIMING		(2)							// 雪のタイミングをこれ回変更したら１回増やす
#define WEATHER_SNOW_S_ADD				(3)							// 登録する数を増やす数
#define WEATHER_SNOW_S_ADD_END			(-4)							// 登録する数を増やす数
#define	WEATHER_SNOW_S_ADD_MAIN			(10)						// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_SNOW_S_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_NUM	( 2 )		// １ずつずらして動作させる
#define	WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_MOVE	( 2 )		// １ずつずらして動作させる

/*== フォグ ==*/
#define	WEATHER_SNOW_S_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_SNOW_S_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_SNOW_S_FOG_START		(16)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_S_FOG_START_END	(20)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_S_FOG_OFS	(-0x400)

/*== BG ==*/
#define WEATHER_SNOW_S_BG_ALP_TIM_S	(6)		// アルファを１上げるタイミング
#define WEATHER_SNOW_S_BG_ALP_TIM_E	(8)		// アルファを１下げるタイミング

// オブジェ 
#define	WEATHER_SNOW_S_END_MIN		(18)						// 終了カウンタ最小
#define WEATHER_SNOW_S_END_MAX		(24)						// 終了カウンタ最大
#define WEATHER_SNOW_S_START_X		(256)						// 横から出すときのX座標
#define WEATHER_SNOW_S_START_X_RAN	(24)						// 横から出すときのX座標
#define	WEATHER_SNOW_S_START_Y_BASE	(-32)							// ベースになるY開始座標
#define	WEATHER_SNOW_S_START_Y_MAX	(168)						// X開始座標乱数の最大値

#define	WEATHER_SNOW_S_SPEED_ADD_TMG (10)						// X座標のスピードを上げるタイミング

#define	WEATHER_SNOW_S_ADD_SP_TMG_NUM (4)						// スピードを変更するタイミングの数
#define	WEATHER_SNOW_S_ADD_SP_CHG_TMG (512)						// スピードを変更するタイミングのタイミング

#define WEATHER_SNOW_S_ADD_SP_TMG		(4)						// スピードを変更するタイミング
#define WEATHER_SNOW_S_SP_UP			(8)						// この値以上の横スピードのときは派手にする
static const int WEATHER_SSNOW_SPEED_X_SML[WEATHER_SNOW_S_ADD_SP_TMG_NUM] = {-4,-6,-8,-10};
static const int WEATHER_SSNOW_SPEED_Y_SML[WEATHER_SNOW_S_ADD_SP_TMG_NUM] = {2,4,2,4};	// たてに進むスピード

//#define WEATHER_SNOW_S_BG_ALPHA0	(4)
//#define WEATHER_SNOW_S_BG_ALPHA1	(8)
//#define WEATHER_SNOE_S_BG_ALPHA_DEF	(16)

/*== 猛吹雪BGグラフィック構成データ ==*/
#define WEATHER_SNOW_S_GRAPHIC_CELL	( 9 )
#define WEATHER_SNOW_S_GRAPHIC_BG	( 0 )


//-------------------------------------
//	砂嵐管理関数定数
//=====================================
#define	WEATHER_STORM_TIMING_MIN		(1)							// 砂を出すタイミング最小
#define WEATHER_STORM_TIMING_MAX		(15)						// 砂を出すタイミング最大
#define WEATHER_STORM_TIMING_ADD		(2)							// タイミングを減らす数
#define WEATHER_STORM_TIMING_ADD_END	(1)							// タイミングを減らす数
#define WEATHER_STORM_ADD_START			(1)							// 最初の同時に雨を登録する数
#define WEATHER_STORM_ADD_TIMING		(4)							// 砂のタイミングをこれ回変更したら１回増やす
#define WEATHER_STORM_ADD				(2)							// 登録する数を増やす数
#define WEATHER_STORM_ADD_END			(-3)							// 登録する数を増やす数
#define	WEATHER_STORM_ADD_MAIN			(8)							// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_STORM_NOFADE_OBJ_START_NUM	( 24 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM		( 2 )			// 何個ずつずらして動作させるか
#define	WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE	( 2 )			// １ずつずらして動作させる

/*== フォグ ==*/
#define	WEATHER_STORM_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_STORM_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_STORM_FOG_START			(0)							// このカウント動いてからフォグテーブルを操作
#define WEATHER_STORM_FOG_START_END		(31)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_STORM_FOG_OFS	( 28399 )
#define WEATHER_STORM_FOG_SLOPE	( 3 )								// 砂嵐スロープ


/*== BG ==*/
#define WEATHER_STORM_BG_ALP_TIM_S	(32)		// アルファを１上げるタイミング
#define WEATHER_STORM_BG_ALP_TIM_E	(24)		// アルファを１下げるタイミング
#define WEATHER_STORM_BG_ALP_S_END	( 3 )
#define WEATHER_STORM_BG_ALP_E_END	( 0 )
#define WEATHER_STORM_BG_ALP_DEF	( 16 )

#define WEATHER_STORM_BG_ALP_STRONG_WIND	(4)	// すごい風のときのα値


/*== 砂オブジェクト ==*/
#define	WEATHER_STORM_END_MIN		(15)						// 終了カウンタ最小
#define WEATHER_STORM_END_MAX		(35)						// 終了カウンタ最大
#define WEATHER_STORM_END_NUM		(WEATHER_STORM_END_MAX - WEATHER_STORM_END_MIN)	// カウンタの値の数
#define	WEATHER_STORM_END_DIV		((WEATHER_STORM_END_NUM / 4)+1)	// オブジェクトの種類を計算するとき割る値
#define	WEATHER_STORM_START_X1		(262)						// ベースになるX開始座標	よこ用
#define	WEATHER_STORM_START_X1_RAN	(24)						// ベースになるX開始座標	よこ用
#define WEATHER_STORM_START_Y1_MIN	( -64 )						//  Y開始座標最小
#define	WEATHER_STORM_START_Y1_MAX	(192)						// Y開始座標最大
#define	WEATHER_STORM_SPEED_NUM		(8)							// 風向きの数
#define	WEATHER_STORM_SPEED_CNG_NUM	(40)						// 変えるタイミング
#define WEATHER_STORM_SPEED_ADD_TMG (5)						// 風の勢いを変えるタイミング

#define WEATHER_STORM_STRONG_CHG	(6)						// 風がこの値以上になった時勢いを強くする


/*== すなあらしグラフィック構成データ ==*/
#define WEATHER_STORM_GRAPHIC_CELL	( 2 )
#define WEATHER_STORM_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

#define WEATHER_STORMBG_GRAPHIC_CELL	( 2 )
#define WEATHER_STORMBG_GRAPHIC_BG	( 1 )


//-------------------------------------
//	霧管理関数定数
//=====================================
/*== フォグ ==*/
#define	WEATHER_FOG_TIMING		(2)							// に１回フォグテーブルを操作
#define	WEATHER_FOG_TIMING_END	(2)							// に１回フォグテーブルを操作
#define WEATHER_FOG_START		(16)						// このカウント動いてからフォグテーブルを操作
#define WEATHER_FOG_START_END	(16)						// このカウント動いてからフォグテーブルを操作

#define WEATHER_FOG0_OFS	( 0x200 )
#define WEATHER_FOG1_OFS	( -0x9E0 )	
#define WEATHER_FOG1_SLOPE	( 3 )
#define WEATHER_FOG2_OFS	( 0xAA0 )
#define WEATHER_FOG2_SLOPE	( 5 )


/*== FOG2 BG設定 ==*/
#define WEATHER_FOG2_GRAPHIC_BG	( 6 )
#define WEATHER_FOG2_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )
#define WEATHER_FOG2_FADE_COUNT_MAX	( 30 )
#define WEATHER_FOG2_FADE_END_ALPHA	( 16 )


//-------------------------------------
//	スノーダスト関係
//====================================
#define	WEATHER_SNOW_D_TIMING_MIN		(2)							// 出すタイミング最小
#define WEATHER_SNOW_D_TIMING_MAX		(16)						// 出すタイミング最大
#define WEATHER_SNOW_D_TIMING_ADD		(2)							// タイミングを減らす数
#define WEATHER_SNOW_D_TIMING_ADD_END	(6)							// タイミングを減らす数
#define WEATHER_SNOW_D_ADD_START		(2)							// 最初の同時に登録する数
#define WEATHER_SNOW_D_ADD_TIMING		(4)							// タイミングをこれ回変更したら１回増やす
#define WEATHER_SNOW_D_ADD				(2)							// 登録する数を増やす数
#define WEATHER_SNOW_D_ADD_END			(10)							// 登録する数を増やす数
#define	WEATHER_SNOW_D_ADD_MAIN			(20)						// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_SNOW_D_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_NUM	( 10 )		// 何個ずつ動作数をかえるか
#define	WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ずらして動作させる値


/*== フォグ ==*/
#define	WEATHER_SNOW_D_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_SNOW_D_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_SNOW_D_FOG_START		(0)							// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_D_FOG_START_END	(0)							// このカウント動いてからフォグテーブルを操作
#define WEATHER_SNOW_D_FOG_OFS			(0x200)

// オブジェクト
#define WEATHER_SNOW_D_START_X_MIN		(-64)					// 開始座標
#define	WEATHER_SNOW_D_START_X_DIS		(384)					// 乱数で求める開始座標の値
#define WEATHER_SNOW_D_START_Y			(-8)					// ここから出す
#define WEATHER_SNOW_D_START_Y_MAX		(256)					// ここから出す
#define WEATHER_SNOW_D_SPARK_NUM_MIN	(7)						// これだけ出てる最小
#define WEATHER_SNOW_D_SPARK_NUM_RAN	(5)						// 乱数で求める値
#define WEATHER_SNOW_D_SPARK_NO			(0x14)					// 光の数

#define WEATHER_SNOW_D_SP_ADD_TMG_X_MIN	(3)						//　オブジェクトのスピードを足すタイミング
#define WEATHER_SNOW_D_SP_ADD_TMG_X_MAX	(6)					//　オブジェクトのスピードを足すタイミング
#define WEATHER_SNOW_D_SP_ADD_TMG_Y_MIN	(4)						// オブジェクトのスピードを足すタイミング
#define WEATHER_SNOW_D_SP_ADD_TMG_Y_MAX	(5)					// オブジェクトのスピードを足すタイミング	

/*== スノーダストグラフィック構成データ ==*/
#define WEATHER_SNOW_D_GRAPHIC_CELL	( 4 )
#define WEATHER_SNOW_D_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )


//-------------------------------------
//	虹
//=====================================
/*== 虹グラフィック構成データ ==*/
#define WEATHER_RAINBOW_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE  )
#define WEATHER_RAINBOW_GRAPHIC_BG		( 2 )

/*== ワークサイズ ==*/
#define WEATHER_RAINBOW_WORK_SIZE		(sizeof(int)*10)


//-------------------------------------
//	大雨
//=====================================
#define	WEATHER_STRAIN_TIMING_MIN		(1)					// 雨を出すタイミング最小
#define WEATHER_STRAIN_TIMING_MAX		(15)				// 雨を出すタイミング最大
#define WEATHER_STRAIN_TIMING_ADD		(3)					// タイミングを減らす数
#define WEATHER_STRAIN_ADD_START		(1)					// 最初の同時に雨を登録する数
#define WEATHER_STRAIN_ADD_TIMING		(2)					// 雨のタイミングをこれ回変更したら１回増やす
#define WEATHER_STRAIN_ADD			(4)						// 登録する数を増やす数
#define WEATHER_STRAIN_ADD_END			(-10)				// 登録する数を増やす数
#define	WEATHER_STRAIN_ADD_MAIN		(24)					// メインシーケンスでの登録する数

/*== フェード無し開始の時 ==*/
#define WEATHER_STRAIN_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_STRAIN_NOFADE_OBJ_START_DUST_NUM	( 5 )		// 何個ずつ動作数を変更するか
#define	WEATHER_STRAIN_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ずらす動作数の値

/*== フォグ ==*/
#define	WEATHER_STRAIN_FOG_TIMING		(1)						// に１回フォグテーブルを操作
#define	WEATHER_STRAIN_FOG_TIMING_END	(1)						// に１回フォグテーブルを操作
#define WEATHER_STRAIN_FOG_START		(0)					// このカウント動いてからフォグテーブルを操作
#define WEATHER_STRAIN_FOG_START_END	(0)					// このカウント動いてからフォグテーブルを操作


/*== 雨オブジェクト ==*/
#define WEATHER_STRAIN_SPEED_X		(-24)						// 横に進むスピード
#define WEATHER_STRAIN_SPEED_Y		(24)							// たてに進むスピードベース
#define	WEATHER_STRAIN_END_MIN		(0)							// 終了カウンタ最小
#define WEATHER_STRAIN_END_MAX		(4)							// 終了カウンタ最大
#define	WEATHER_STRAIN_START_X		(0)							// ベースになるX開始座標
#define	WEATHER_STRAIN_START_X_MAX	(512)						// X開始座標乱数値
#define	WEATHER_STRAIN_START_Y		(-80)						// Y開始座標
#define	WEATHER_STRAIN_START_Y_MAX	(48)						// Y開始座標乱数値

#define WEATHER_STRAIN_OBJ_MUL_NUM	(5)							// オブジェのスピードを変化させる値
#define WEATHER_STRAIN_OBJ_MUL_CHG	(60)						// 変更タイミング

/*== 大雨グラフィック構成データ ==*/
#define WEATHER_STRAIN_GRAPHIC_CELL	( 5 )
#define WEATHER_STRAIN_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE )

//-------------------------------------
//	火山灰管理関数定数
//=====================================
#define	WEATHER_VOLCANO_TIMING_MIN	(6)		// 火山灰を出すタイミング最小
#define WEATHER_VOLCANO_TIMING_MAX	(12)		// 火山灰を出すタイミング最大
#define WEATHER_VOLCANO_TIMING_ADD	(1)			// タイミングを減らす数
#define	WEATHER_VOLCANO_ADD_TIMING	(4)			// １度のオブジェ登録数を増やすタイミング
#define	WEATHER_VOLCANO_ADD			(0)			// オブジェ登録数を足す値
#define WEATHER_VOLCANO_MAIN		(1)			// メインではこれだけ登録

/*== フェード無し開始の時 ==*/
#define WEATHER_VOLCANO_NOFADE_OBJ_START_NUM	( 20 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_NUM	( 2 )		// 何オブジェずつ動作数をへんこうするか
#define	WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_MOVE	( 16 )		// ずらす動作数の値

/*== フォグ ==*/
#define	WEATHER_VOLCANO_FOG_TIMING		(1)		// に１回フォグテーブルを操作
#define	WEATHER_VOLCANO_FOG_TIMING_END	(1)		// に１回フォグテーブルを操作
#define WEATHER_VOLCANO_FOG_START		(0)	// このカウント動いてからフォグテーブルを操作
#define WEATHER_VOLCANO_FOG_START_END	(9)	// このカウント動いてからフォグテーブルを操作
#define WEATHER_VOLCANO_FOG_OFS			(-0x40)
#define WEATHER_VOLCANO_FOG_SLOPE		( 0 )

/*== BG ==*/
#define WEATHER_VOLCANO_BG_ALP_TIM_S	(6)		// アルファを１上げるタイミング
#define WEATHER_VOLCANO_BG_ALP_TIM_E	(8)		// アルファを１下げるタイミング
#define WEATHER_VOLCANO_BG_ALP_S_END	( 15 )
#define WEATHER_VOLCANO_BG_ALP_E_END	( 0 )
#define WEATHER_VOLCANO_BG_ALP_DEF		( 16 )

/*== 火山灰オブジェクト ==*/
#define	WEATHER_VOLCANO_ADD_TMG_Y_BASE	(1)			// 火山灰のスピードを足すタイミング
#define	WEATHER_VOLCANO_ADD_TMG_Y_RAN	(1)			// 火山灰のスピードを足すタイミング乱数値
#define	WEATHER_VOLCANO_START_X_BASE	(-32)		// ベースになるX開始座標
#define	WEATHER_VOLCANO_START_X_MAX		(414)		// X開始座標乱数の最大値
#define WEATHER_VOLCANO_OBJ_NUM			(4)			// オブジェ種類
#define WEATEHR_VOLCANO_DEL_COUNT_MIN	(10)			// 破棄するカウント値
#define WEATEHR_VOLCANO_DEL_COUNT_MAX	(20)			// 破棄カウント値

/*== 火山灰グラフィック構成データ ==*/
#define WEATHER_VOLCANO_GRAPHIC_CELL	( 6 )
#define WEATHER_VOLCANO_GRAPHIC_BG	( 3 )

//-------------------------------------
//	雷管理関数定数
//=====================================
#define WEATHER_SPARK_NUM		(2)	// ライト光カウント
#define WEATHER_SPARK_POWER_MIN	(200)	// 雷POWER最小	(小数点計算のため１００かけた値)
#define WEATHER_SPARK_POWER_RAN	(480)	// 雷POWER乱数	(小数点計算のため１００かけた値)

#define WEATHER_SPARK_SPARK_MUL	(50)	// 次の雷までの間隔はPOWER＊これを基本間隔として求め、
										//	したの値で乱数要素付加(１単位ー＞１００)
#define WEATHER_SPARK_SPARK_RAN	(120)	// 次の雷までの間隔乱数
#define WEATHER_SPARK_SPARK_RAN_HIGH	(15)	// 早く次を出すときの次の雷までの間隔乱数
#define	WEATHER_SPARK_FOG_TIMING		(1)		// に１回フォグテーブルを操作
#define	WEATHER_SPARK_FOG_TIMING_END	(1)		// に１回フォグテーブルを操作
#define WEATHER_SPARK_SUB_NUM			(36)	// α値を減らす値
#define WEATHER_SPARK_SUB_NUM_HIGH		(200)	// 早くアルファを減らす

/*== 雷グラフィック構成データ ==*/
#define WEATHER_SPARK_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )
#define WEATHER_SPARK_GRAPHIC_BG	( 4 )
/*== ワークサイズ ==*/
#define WEATHER_SPARK_WORK_SIZE		(sizeof(int)*10)

//-------------------------------------
//	気合管理関数定数
//=====================================
#define	WEATHER_SPIRIT_TIMING_MIN	(15)		// 雨を出すタイミング最小
#define WEATHER_SPIRIT_TIMING_MAX	(35)		// 雨を出すタイミング最大
#define WEATHER_SPIRIT_TIMING_ADD	(2)			// タイミングを減らす数
#define	WEATHER_SPIRIT_ADD_TIMING	(5)			// １度のオブジェ登録数を増やすタイミング
#define	WEATHER_SPIRIT_ADD			(1)			// オブジェ登録数を足す値
#define	WEATHER_SPIRIT_ADD_END		(-3)			// オブジェ登録数を足す値
#define WEATHER_SPIRIT_MAIN			(4)			// メインではこれだけ登録

#define WEATHER_SPIRIT_S_MOVE_NUM	(2)			// 小刻みに揺れる距離(横)
#define WEATHER_SPIRIT_S_MOVE_TMG	(1)			// 小刻みに揺れるタイミング

#define WEATHER_SPIRIT_OBJ_NUM		(0xe)		// オブジェクト数
#define WEATHER_SPIRIT_BIG_DIV		(4)			// これで割ると、大きさになる
#define	WEATHER_SPIRIT_SHIFT_UP		(8)			// これを大きさidxでかける
#define WEATHER_SPIRIT_SHIFT_UP_RAN	(25)		// 乱数値
#define	WEATHER_SPIRIT_ADD_SPEED	(16)		// 加速地（スピードは１００倍状態）

/*== フェード無し開始の時 ==*/
#define WEATHER_SPIRIT_NOFADE_OBJ_START_NUM	( 16 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_NUM	( 2 )		// 何オブジェずつ動作する数を変更するか
#define	WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_MOVE	( 1 )		// ずらして動作させる値

/*== オブジェクト ==*/
#define WEATHER_SPIRIT_MAT_X_MIN	(-128)		// X座標最小値
#define WEATHER_SPIRIT_MAT_X_RAN	(512)		// X座標乱数

#define WEATHER_SPIRIT_MAT_Y_S_MIN	(8)			// Y座標	小さいのがいていい場所(0,1)
#define WEATHER_SPIRIT_MAT_Y_S_RAN	(192)		// Y座標	小さいのがいていい場所
#define WEATHER_SPIRIT_MAT_Y_M_MIN	(64)		// Y座標	中くらいがいていい場所(2)
#define WEATHER_SPIRIT_MAT_Y_M_RAN	(128)		// Y座標	中くらいがいていい場所
#define WEATHER_SPIRIT_MAT_Y_L_MIN	(160)		// Y座標	大きいのがいていい場所(3)
#define WEATHER_SPIRIT_MAT_Y_L_RAN	(32)		// Y座標	大きいのがいていい場所


/*== 気合グラフィック構成データ ==*/
#define WEATHER_SPIRIT_GRAPHIC_CELL	( 7 )
#define WEATHER_SPIRIT_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE  )

//-------------------------------------
//	神秘
//=====================================
#define WEATHER_MYSTIC_GRAPHIC_BG	( 8 )
#define WEATHER_MYSTIC_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_MYSTIC_FADE_COUNT_MAX	( 8 )
#define WEATHER_MYSTIC_FADE_END_ALPHA	( 16 )

/*== フォグ ==*/
#define	WEATHER_MYSTIC_FOG_TIMING		(1)		// に１回フォグテーブルを操作
#define	WEATHER_MYSTIC_FOG_TIMING_END	(1)		// に１回フォグテーブルを操作
#define WEATHER_MYSTIC_FOG_START		(0)		// このカウント動いてからフォグテーブルを操作
#define WEATHER_MYSTIC_FOG_START_END	(48)	// このカウント動いてからフォグテーブルを操作
#define WEATHER_MYSTIC_FOG_OFS			(32175)
#define WEATHER_MYSTIC_FOG_SLOPE		(7)


#if 0
#define	WEATHER_MYSTIC_TIMING_MIN	(10)		// 出すタイミング最小
#define WEATHER_MYSTIC_TIMING_MAX	(40)		// 出すタイミング最大
#define WEATHER_MYSTIC_TIMING_ADD	(3)			// タイミングを減らす数
#define	WEATHER_MYSTIC_ADD_TIMING	(8)			// １度のオブジェ登録数を増やすタイミング
#define WEATHER_MYSTIC_ADD_START	(1)
#define	WEATHER_MYSTIC_ADD			(0)			// オブジェ登録数を足す値
#define	WEATHER_MYSTIC_ADD_END		(1)			// オブジェ登録数を足す値
#define WEATHER_MYSTIC_ADD_MAIN		(1)			// メインではこれだけ登録

/*== フェード無し開始の時 ==*/
#define WEATHER_MYSTIC_NOFADE_OBJ_START_NUM	( 4 )				// 開始時の散布するオブジェクトの数
#define	WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_NUM	( 1 )		// 何オブジェずつ動作数を変更するか
#define	WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_MOVE	( 10 )		// ずらして動作させる値


// オブジェクト
#define WEATHER_MYSTIC_M_Y			(60)		// 移動値
#define WEATHER_MYSTIC_M_Y_MUL		(20)		// 大きさにより増やす値
#define WEATHER_MYSTIC_M_X			(0)			// 移動値横

#define WEATHER_MYSTIC_MH_X			(50)		// 浮遊しているように見せる、補助動作移動値
#define WEATHER_MYSTIC_MH_Y			(50)		// 浮遊しているように見せる、補助動作移動値
#define WEATHER_MYSTIC_MH_COUNT		(2)			// カウント値
#define WEATHER_MYSTIC_MH_COUNT_RAN	(6)			// カウント値乱数


#define WEATHER_MYSTIC_DES_TM		(32)		// 死亡カウント
#define WEATHER_MYSTIC_DES_RAN		(16)		// 死亡カウントランダム

#define WEATHER_MYSTIC_NUM			(4)			// オブジェクト数
#define WEATHER_MYSTIC_RAN			(100)		// どの大きさにするかを求める時の値
#define WEATHER_MYSTIC_RAN_0		(40)		// 小オブジェの割合
#define WEATHER_MYSTIC_RAN_1		(30)		// 中オブジェの割合
#define WEATHER_MYSTIC_RAN_2		(20)		// 中大オブジェの割合
#define WEATHER_MYSTIC_RAN_3		(10)		// 大オブジェの割合

#define WEATHER_MYSTIC_MAT_X		(0)			// 開始座標
#define WEAHTER_MYSTIC_MAT_X_RAN	(512)		// 開始座標ラン数値
#define WEAHTER_MYSTIC_MAT_Y		(0)			// 開始座標
#define WEATHER_MYSTIC_MAT_Y_MUL	(48)		// 開始座標を大きさにより変える値
#define WEAHTER_MYSTIC_MAT_Y_RAN	(64)		// 開始座標ラン数値

/*== 神秘グラフィック構成データ ==*/
#define WEATHER_MYSTIC_GRAPHIC_CELL	( 8 )
#define WEATHER_MYSTIC_GRAPHIC_BG	( WEATHER_GRAPHIC_NONE  )
#endif


//-------------------------------------
//	曇り
//=====================================
#define WEATHER_CLOUDINESS_GRAPHIC_BG	( 5 )
#define WEATHER_CLOUDINESS_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_CLOUDINESS_FADE_COUNT_MAX	( 8 )
#define WEATHER_CLOUDINESS_FADE_END_ALPHA	( 4 )

//-------------------------------------
//	きりはらい
//=====================================
#define WEATHER_KIRI_HARAI_GRAPHIC_BG	( 6 )
#define WEATHER_KIRI_HARAI_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_KIRI_HARAI_FADE_COUNT_MAX	( 30 )
#define WEATHER_KIRI_HARAI_FADE_END_ALPHA	( 9 )

/*== フォグ ==*/
#define	WEATHER_KIRI_HARAI_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_KIRI_HARAI_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_KIRI_HARAI_FOG_COLOR		(GX_RGB(0,0,0))
#define WEATHER_KIRI_HARAI_FOG_OFS			( 30287 )
#define WEATHER_KIRI_HARAI_FOG_SLOPE		( 7 )

//-------------------------------------
//	きりはらい	しろ
//=====================================
#define WEATHER_KIRI_HARAI_WHITE_GRAPHIC_BG	( 6 )
#define WEATHER_KIRI_HARAI_WHITE_GRAPHIC_CELL	( WEATHER_GRAPHIC_NONE )

#define WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX	( 30 )
#define WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA	( 9 )

/*== フォグ ==*/
#define	WEATHER_KIRI_HARAI_WHITE_FOG_TIMING		(1)							// に１回フォグテーブルを操作
#define	WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END	(1)							// に１回フォグテーブルを操作
#define WEATHER_KIRI_HARAI_WHITE_FOG_COLOR		(GX_RGB(31,31,31))
#define WEATHER_KIRI_HARAI_WHITE_FOG_OFS			( 30037 )
#define WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE		( 6 )

//-------------------------------------
//	フラッシュ
//=====================================
#define WEATHER_FLASH_START_R	( FX32_CONST( 32 ) )
#define WEATHER_FLASH_END_R		( FX32_CONST( 256 ) )
#define WEATHER_FLASH_SYNC		( 30 )
#define WEATHER_FLASH_CX		( 128 )
#define WEATHER_FLASH_CY		( 84 )

#define WEATHER_FLASH_GRAPHIC_BG	( 7 )		// 使用するBG

#define WEATHER_FLASH_WND_MSK			( GX_BLEND_ALL )
#define WEATHER_FLASH_OUTSIDE_WND_MSK	( GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	天気グラフィックファイルパスデータ
//
//	読み込む天気のグラフィックファイルを
//	まとめる構造体
//=====================================

// BG
typedef struct{
	int pltt_arc;
	int char_arc;
	int screen_arc;
	/*char	pltt_path[50];	// パレットパス
	char	char_path[50];	// キャラクタパス
	char	screen_path[50];// スクリーンパス//*/
} WEATHER_BG_DATA;

//-------------------------------------
//	天気グラフィックデータ構造体
//-------------------------------------
// セル
typedef struct{
	CLACT_U_RES_OBJ_PTR res_obj[ WEATHER_RES_NUM ];
	CLACT_ADD add;				// セルアクター登録データ
	CLACT_HEADER head;			// セルアクターヘッダーデータ
} WATHER_GRAPHIC_FILE_DATA;

// BG
typedef struct{
	char*			pPlttBuff;		// パレットデータ
	char*			pCharBuff;		// キャラクタデータ
	char*			pScreenBuff;	// スクリーンデータ
	NNSG2dScreenData*		pScreen;// スクリーンデータ
	NNSG2dCharacterData*	pChar;	// BGのキャラクタデータ
	NNSG2dPaletteData*		pPltt;	// BGのパレットデータ

} WATHER_BG_FILE_DATA;

#define WEATHER_OBJ_DATA_WORK_NUM	( 10 )
#define WEATHER_OBJ_DATA_WORK_SIZE	( sizeof(s32)*WEATHER_OBJ_DATA_WORK_NUM )
//-------------------------------------
//
//		個々のオブジェクトの構造体
//	
//	雨や、雪のオブジェクト
//=====================================
typedef struct WAETHER_OBJ_DATA_tag{
	WEATHER_CONT_PTR	pWSysCont;	// 天気データ
	CLACT_WORK_PTR	clact_w;	// セルアクターワーク
	void*	work;					// 作業領域		AllocObjWork() FreeObjWork()で作成、破棄すること
	s32	work_buff[WEATHER_OBJ_DATA_WORK_NUM];					// 作業領域		AllocObjWork() FreeObjWork()で作成、破棄すること

	struct WAETHER_OBJ_DATA_tag* pNext;	// 次へ
	struct WAETHER_OBJ_DATA_tag* pPrev;	// 前へ
} WAETHER_OBJ_DATA;

//------------------------------------
//		天気管理データ構造体
//	
//	天気を管理する関数内でのワーク領域構造体
//=====================================
typedef struct{
	WEATHER_CONT_PTR	pWSysCont;			// 天気システムコントローラのポインタ
	void*			pWSD;				// 自分の親のWEATHER_SYS_DATAデータ
	const WATHER_GRAPHIC_FILE_DATA*	pCell;		// 使用するセルデータ
	WAETHER_OBJ_DATA	Dummy;				// オブジェリストのダミーデータ
	WAETHER_OBJ_DATA	ObjArray[WEATEHR_OBJDATA_MAX];// オブジェリスト配列
	TCB_PTR tcb;							// 自分のタスクポインタ
	
	VecFx32		CameraTarget;				// １つ前のカメラターゲットスクロール用
	void*		work;						// ワーク領域 各自作成	


	// 音を鳴らしているか?
	BOOL snd_play;
	u16 snd_no;
	u16		Sequence;						// 処理シーケンス

	// フォグ動作のONOFFF
	u16 fog_use;

	u16		ContFlag;						// 外部コントロールフラグ		

} WEATHER_SYS_WORK;

//-------------------------------------
//		天気データ構造体
//
//	使用するファイルや関数のデータ郡
//=====================================
typedef struct{
	int		GraphicNo;					// グラフィックデータ配列ナンバー
	int		BGNo;						// BGデータ配列ナンバー
	int		WorkByte;					// ワーク領域のバイトサイズ
	WEATHER_SYS_WORK* pWork;			// 実行中:天気管理関数のワーク領域	初期化していないとき:NULL
	WATHER_GRAPHIC_FILE_DATA*	pCell;	// 使用するセルデータ	初期化していないとき:NULL
	int		MoveFlag;					// 動作状態
			  /*WEATHER_SYS_MOVE_NONE,	// 動いていない
				WEATHER_SYS_MOVE_INIT,	// 初期化中
				WEATHER_SYS_MOVE_READY,	// 開始待ち
				WEATHER_SYS_MOVE_DO,*/	// 実行中
	
	int		DivInitSeq;					// 分割読み込みシーケンス
	TCB_PTR	DivInitTcb;					// 分割読み込みTCB
	
	void	(*cont)(TCB_PTR tcb, void* data);		// 天気を管理する関数
} WEATHER_SYS_DATA;

typedef void (*objFunc)(WAETHER_OBJ_DATA*);		// オブジェクト動作関数型

//-------------------------------------
//	
//	２D描画システム構造体
//	
//=====================================
typedef struct {
	
	CLACT_U_RES_MANAGER_PTR	resMan[ WEATHER_RES_NUM ];	// リソースマネージャ
	CLACT_U_RES_HEADER_PTR	resHeader;					// リソースヘッダ

	// メイン画面用レンダラーデータ
	NNSG2dRendererInstance	Render;		// レンダラ
	NNSG2dRenderSurface		Surface;	// サーフェース
	CLACT_SET_PTR	clactSet;			// セルアクタセット
	TCB_PTR	clactDrawTcb;				// アクター描画TCB
	
} WEATHER_SYS_DRAWSYS;


//---------------------------------------------------------
//
//		お天気システム制御オブジェ
//			天気システムのオブジェクト
//
//=========================================================
typedef struct _WEATHER_SYS_CONTROL{
	WEATHER_SYS_DATA*		pWSD;		// 天気システムデータ
	const WEATHER_BG_DATA*	pWSBG;		// 天気システムBGデータ

	WEATHER_SYS_DRAWSYS		Draw;		// 描画システム
		
	FIELDSYS_WORK* fsys;					// フィールドシステムポインタ

	ARCHANDLE*	ArcHandle;		// アーカイブファイルハンドル
} WEATHER_SYS_CONTROL;

//-----------------------------------------------
//	その他作業用構造体
//==============================================
//-------------------------------------
//	オブジェクトフェードデータ
//-------------------------------------
typedef struct{
	// ワーク
	WEATHER_SYS_WORK* pWork;	// ワーク

	// カウンタ
	s16 objAddNum;		// オブジェクト登録数
	s16 objAddTmg;		// 登録タイミングカウンタ
	s16 objAddTmgMax;	// 登録タイミング
	s16 objAddNumSum;	// オブジェクト登録数加減カウンタ
	
	// 定数
	s16	OBJ_ADD_NUM_END;		// オブジェクト１回の登録数　終了値
	s16	OBJ_ADD_TMG_END;		// 登録タイミングカウンタ　終了値
	s16	OBJ_ADD_TMG_SUM;		// 登録タイミングカウンタ変更値
	s16 OBJ_ADD_NUM_SUM_TMG;	// オブジェクト１回の登録数を変更するタイミング
	s32 OBJ_ADD_NUM_SUM;		// 変更する値

	// 関数
	void	(*add)(WEATHER_SYS_WORK* pWork, int num);		// OBJ登録
} WEATHER_SYS_OBJ_FADE;
typedef void (*OBJADD_FUNC)(WEATHER_SYS_WORK* pWork, int num);// OBJ登録


//-------------------------------------
//	動作ワーク
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} WEATHER_SYS_MOVE_WORK;

//-------------------------------------
//	ｆｘ３２動作ワーク
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	s16 count;
	s16 count_max;
} WEATHER_SYS_MOVE_WORK_FX;

//-------------------------------------
//	フォグデプス　カラー　スロープ変更
//=====================================
typedef struct {
	FOG_DATA_PTR	Fog;		// フェードするフォグデータ
	WEATHER_SYS_MOVE_WORK fog_depth;
	WEATHER_SYS_MOVE_WORK r;
	WEATHER_SYS_MOVE_WORK g;
	WEATHER_SYS_MOVE_WORK b;
	WEATHER_SYS_MOVE_WORK slope;
} WEATHER_SYS_CHG_FOG_DATA;

//-------------------------------------
//	フォグフェードデータ
//-------------------------------------
typedef struct{
	FOG_DATA_PTR	Fog;		// フェードするフォグデータ
	char			fog_tbl[32];// フォグテーブル

	// カウンタ
	s32	fogDepth;		// フォグ深度
	s32	fogCount;		// フォグカウンタ

	// 定数
	s16	FOG_CHG_TMG;		// フォグテーブル変更タイミング
	s16	FOG_TBL_SUM;		// 変更値
} WEATHER_SYS_FOG_FADE;

//-------------------------------------
//	システムワークデータ
//-------------------------------------

// Normal
typedef struct{
	WEATHER_SYS_OBJ_FADE	objFade;
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
	s32	work[10];
} WEATHER_SYSW_NORMAL;

// オブジェフェードのみ
typedef struct{
	WEATHER_SYS_OBJ_FADE	objFade;
	s32	work[10];
} WEATHER_SYSW_OBJFADE;

// フォグフェードのみ
typedef struct{
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
	s32	work[10];
} WEATHER_STSW_FOGFADE;

// 曇りようワーク
typedef struct{
	WEATHER_SYS_MOVE_WORK alpha;
} WEATHER_CLOUDINESS_WORK;

// 霧はらい
typedef struct{
	WEATHER_SYS_MOVE_WORK alpha;
	WEATHER_SYS_FOG_FADE	fogFade;
	WEATHER_SYS_CHG_FOG_DATA fogWithFade;
} WEATHER_KIRI_HARAI_WORK;

// サークル
typedef struct {
	s16 x;						// 中心ｘ座標
	s16 y;						// 中心ｙ座標
	WEATHER_SYS_MOVE_WORK_FX r;	// 半径
	FIELD_HBLANK_SYS* p_fldhblksys;	// hblankシステム
	FIELD_HBLANK_OBJ* p_hblank;	// hblankワーク
	LASTER_SYS_PTR p_laster[2];	// ラスターシステム
	TCB_PTR vblank_tcb;
	u32 status;				// ステータス
	u16	wnd_data[4][192];	// wndデータ
} WEATHER_CIRCLE_WORK;
enum{	// status
	WEATHER_CIRCLE_STATUS_INIT,
	WEATHER_CIRCLE_STATUS_DO,
};
#define WEATHER_CIRCLE_VBLANKTCB_PRI	( 1024 )


// フラッシュ
typedef struct {
	WEATHER_CIRCLE_WORK circle;
} WEATHER_FLASH_WORK;


//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	その他プライベート関数
//=====================================
static void WeatherLoopSndPlay( WEATHER_SYS_WORK* p_work, int snd_no );
static void WeatherLoopSndStop( WEATHER_SYS_WORK* p_work );
static void WeatherBGAlphaDef( int alpha1, int alpha2 );
static void WeatherMoveReq( WEATHER_SYS_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
static BOOL	WeatherMoveMain( WEATHER_SYS_MOVE_WORK* p_work );
static void WeatherMoveReqFx( WEATHER_SYS_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max );
static BOOL	WeatherMoveMainFx( WEATHER_SYS_MOVE_WORK_FX* p_work );
static void load2DGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell);	// 絵のデータの読み込み
static void setUpBG( WEATHER_SYS_CONTROL* cont, int BGNo );
static void destGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell);	// 絵のデータの破棄

static CLACT_U_RES_OBJ_PTR	loadRes(CLACT_U_RES_HEADER_PTR res_head, int res_type, int head_no, CLACT_U_RES_MANAGER_PTR resMan, ARCHANDLE* arcHandle, u32 alloc_type);

static void init2DDrawSys(WEATHER_SYS_DRAWSYS* draw);
static void loadResHeader(CLACT_U_RES_HEADER_PTR head, int no, int arc_data);
static void delete2DDrawSys(WEATHER_SYS_DRAWSYS* draw);
static void clactSetDrawTcb( TCB_PTR tcb, void* p_work );

//	天気データ代入関数
static void setSysData(WEATHER_SYS_DATA* pData, int CellNo, int BGNo, int WorkSize, TCB_FUNC func);
static void setBGData(WEATHER_BG_DATA* pData, int pltt_arc, int char_arc, int screen_arc );

// 座標設定専用関数
static void setClactMatrix( CLACT_WORK_PTR act, VecFx32* matrix );

//-------------------------------------
//	天気管理関数用関数
//=====================================
static void destObj(WAETHER_OBJ_DATA* pData);							// オブジェの破棄
static void destObjAll(WAETHER_OBJ_DATA* pDummy);						// 全オブジェの破棄
static WAETHER_OBJ_DATA* addObj(WEATHER_SYS_WORK* pWork, int w_byte);	// オブジェをアッド
static void getHeader(CLACT_HEADER_PTR head, WEATHER_SYS_CONTROL* cont, WATHER_GRAPHIC_FILE_DATA* pcell,int vram_trans, int priority );
static BOOL setUpCell( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );
static void moveFuncObj(WAETHER_OBJ_DATA* pDummy, objFunc pFunc);		// 全オブジェクトを動かす
static void drawObj(WEATHER_SYS_WORK* pData);							// オブジェの描画
static VecFx32 getObjMat( WAETHER_OBJ_DATA* obj );
static int getMaxOamNum(NNSG2dCellDataBank* pCell);						// セルデータバンク内のセルのOAMの最大数取得
static void getScrollNum(fx32* x, fx32* y, WEATHER_SYS_WORK* pWork);		// スクロール座標取得
static void scrollObj(WEATHER_SYS_WORK* pWork, int* x, int* y);			// 全オブジェクトの座標をscrollにあわせる
static void allocObjWork(WAETHER_OBJ_DATA* pData, int byte);			// ワーク領域を作成
static void freeObjWork(WAETHER_OBJ_DATA* pData);						// ワーク領域を破棄
static void weatherSysObjFadeInit( WEATHER_SYS_OBJ_FADE* data, WEATHER_SYS_WORK* pWork, s32 objAddTmgMax, s32 objAddNum, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM_TMG, s32 OBJ_ADD_NUM_SUM, OBJADD_FUNC add );
static void weatherSysObjFadeOutSet( WEATHER_SYS_OBJ_FADE* data, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM );
static int weatherSysObjFade(WEATHER_SYS_OBJ_FADE* data);				// オブジェクトフェード
static void weatherSysFogFadeInInitPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color, int timing, u32 fog_use_flg );
static int weatherSysFogFadeInMainPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, u32 fog_use_flg );
static void weatherSysFogParamSet( FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color );
static void weatherSysFogParamFadeInit( WEATHER_SYS_CHG_FOG_DATA* data, FOG_DATA_PTR fog, int fogslope, int offs, GXRgb color, int count_max );
static BOOL weatherSysFogParamFadeMain( WEATHER_SYS_CHG_FOG_DATA* data );
static void weatherSysFogTblInit( WEATHER_SYS_FOG_FADE* data );
static void weatherSysFogFadeInit( WEATHER_SYS_FOG_FADE* data, int timing, BOOL fade_inout );
static int weatherSysFogFade(WEATHER_SYS_FOG_FADE* data);				// フォグフェード
static int weatherSysFogFadeNoReflect(WEATHER_SYS_FOG_FADE* data);		// フォグフェード　フォグテーブルの反映を行わないバージョン
static void weatherSysFogSet(WEATHER_SYS_FOG_FADE* data);				// フォグフェードイン後のテーブルを作成する
static void calcWeatherFogTbl( WEATHER_SYS_FOG_FADE* data );			// フォグテーブル作成計算を行う
//static BOOL weatherBGFade( s32* now_alpha, const int end_alpha, const int add_alpha, s32* timing_count, const int add_timing );
static void weatherDustObj( WEATHER_SYS_WORK* pWork, OBJADD_FUNC add_func, int num, int dust_div_num, int dust_div_move, objFunc move_func );	// 天気のオブジェクトを散布させる
static WAETHER_OBJ_DATA* getCleanObjData( WEATHER_SYS_WORK* pWork );


//-------------------------------------
//	天気管理関数操作関数
//=====================================
static BOOL initWeatherSys(WEATHER_SYS_CONTROL* cont,int no);				// 管理関数初期化
static BOOL divInitWeatherSysCall(WEATHER_SYS_CONTROL* cont,int no);
static BOOL startWeatherSys(WEATHER_SYS_CONTROL* cont,int no, int init_seq, u32 fog_use);// 管理関数スタート
static void stopReqWeatherSys(WEATHER_SYS_CONTROL* cont,int no, u32 fog_use);				// 管理関数終了
static void stopWeatherSys( WEATHER_SYS_CONTROL* cont,int no );				// 強制終了
static void destWeatherSys(WEATHER_SYS_CONTROL* cont,int no);				// 管理関数完全破棄
static void stopWeatherWork(WEATHER_SYS_CONTROL* cont,int no);				// 管理データ破棄
static void stopWeatherWork_local(WEATHER_SYS_DATA* w_sys);				// 管理データ破棄

// 初期化処理分割関数
static void divInitWeatherSysTcb( TCB_PTR tcb, void* work );
static BOOL initWeatherSysWork( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );

static void initClactSet( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );
static BOOL initCellDataMemory( WEATHER_SYS_DATA* w_sys );
static void loadCell_CellData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_CellAnmData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_CharData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void loadCell_PlttData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell );
static void initClactAddData( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys );

static void initBgPltt( WEATHER_SYS_CONTROL* cont, int BGNo );
static void initBgChar( WEATHER_SYS_CONTROL* cont, int BGNo );
static void initBgScr( WEATHER_SYS_CONTROL* cont, int BGNo );

//-------------------------------------
//	天気管理関数
//=====================================
static void contWeatherDummy(TCB_PTR tcb, void* work);		// ダミー
static void contWeatherRain(TCB_PTR tcb, void* work);		// 雨
static void contWeatherSnow(TCB_PTR tcb, void* work);		// 雪
static void contWeatherSnowStorm(TCB_PTR tcb, void* work);	// 吹雪
static void contWeatherSnowStormBG(TCB_PTR tcb, void* work);// BG使用吹雪
static void contWeatherFog00(TCB_PTR tcb, void* work);		// 霧小
static void contWeatherFog01(TCB_PTR tcb, void* work);		// 霧中
static void contWeatherFog02(TCB_PTR tcb, void* work);		// 霧強
static void contWeatherStorm(TCB_PTR tcb, void* work);		// 砂嵐
static void contWeatherStormBG(TCB_PTR tcb, void* work);	// BG使用砂嵐
static void contWeatherSnowSML(TCB_PTR tcb, void* work);	// 北海道雪
static void contWeatherSnowD(TCB_PTR tcb, void* work);		// スノーダスト
static void contWeatherRainbow(TCB_PTR tcb, void* work);	// 虹
static void contWeatherSTRain(TCB_PTR tcb, void* work);		// 大雨
static void contWeatherSTRainSpark(TCB_PTR tcb, void* work);// 大雨＋雷
static void contWeatherVolcano(TCB_PTR tcb, void* work);	// 火山灰
static void contWeatherSpark(TCB_PTR tcb, void* work);		// 雷
static void contWeatherSpirit(TCB_PTR tcb, void* work);		// 気合
static void contWeatherMystic(TCB_PTR tcb, void* work);		// 神秘
static void contWeatherCloudiness(TCB_PTR tcb, void* work);	// 曇り
static void contWeatherKiriHarai(TCB_PTR tcb, void* work);	// きりはらい
static void contWeatherKiriHarai_White(TCB_PTR tcb, void* work);	// きりはらい
static void contWeatherFlash(TCB_PTR tcb, void* work);		// フラッシュ




//-------------------------------------
//	天気オブジェクト登録関数
//=====================================
static void addWeatherRain(WEATHER_SYS_WORK* pWork, int num);		// 雨
static void addWeatherSnow(WEATHER_SYS_WORK* pWork, int num);		// 雪
static void addWeatherSnowStorm(WEATHER_SYS_WORK* pWork, int num);	// 吹雪
static void addWeatherStorm(WEATHER_SYS_WORK* pWork, int num);		// 砂嵐
static void addWeatherSnowSML(WEATHER_SYS_WORK* pWork, int num);	// 北海道雪
static void addWeatherSnowD(WEATHER_SYS_WORK* pWork, int num);		// スノーダスト
static void addWeatherSTRain(WEATHER_SYS_WORK* pWork, int num);		// 大雨
static void addWeatherVolcano(WEATHER_SYS_WORK* pWork, int num);	// 火山灰
static void addWeatherSpirit(WEATHER_SYS_WORK* pWork, int num);		// 気合
static void addWeatherMystic(WEATHER_SYS_WORK* pWork, int num);		// 神秘

//-------------------------------------
//	天気のオブジェ関数
//=====================================
static void objWeatherRain(WAETHER_OBJ_DATA* work);			// 雨の粒
static void objWeatherSnow(WAETHER_OBJ_DATA* work);			// 雪の粒
static void objWeatherSnowStorm(WAETHER_OBJ_DATA* work);	// 吹雪の粒
static void objWeatherStorm(WAETHER_OBJ_DATA* work);		// 砂嵐
static void objWeatherSnowSML(WAETHER_OBJ_DATA* work);		// 北海道雪
static void objWeatherSnowD(WAETHER_OBJ_DATA* work);		// スノーダスト
static void objWeatherSTRain(WAETHER_OBJ_DATA* work);		// 大雨
static void objWeatherVolcano(WAETHER_OBJ_DATA* work);		// 火山灰
static void objWeatherSpirit(WAETHER_OBJ_DATA* work);		// 気合
static void objWeatherMystic(WAETHER_OBJ_DATA* work);		// 神秘


//-------------------------------------
//	天気の各処理を細かくパックした関数郡
//=====================================
static void contWeatherSTRain_Init( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static BOOL contWeatherSTRain_FadeIn( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_NoFade( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Main( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_FadeOutInit( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static BOOL contWeatherSTRain_FadeOut( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Dest( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );
static void contWeatherSTRain_Draw( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w );

//-------------------------------------
//	HBlank使用円描画システム
//=====================================
static void drawWeatherCircleInit( WEATHER_CIRCLE_WORK* p_circle, FIELD_HBLANK_SYS* p_fldhblksys );
static void drawWeatherCircleEnd( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleStart( WEATHER_CIRCLE_WORK* p_circle, fx32 s_r, fx32 e_r, int c_x, int c_y, int sync );
static BOOL drawWeatherCircleMain( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleHblankCall( FIELD_HBLANK_OBJ* p_hbw, void* p_work );
static void drawWeatherCircleVblankCall( TCB_PTR tcb, void* p_work );
static void drawWeatherCircleEndReq( WEATHER_CIRCLE_WORK* p_circle );
static void drawWeatherCircleEndVblank( TCB_PTR tcb, void* p_work );
static void drawWeatherCircleInitHblankTcb( TCB_PTR tcb, void* p_work );


static void CalcWeatherCircle( WEATHER_CIRCLE_WORK* p_circle );
static void CalcWeatherCircleCopyBuff( WEATHER_CIRCLE_WORK* p_circle );
static void CalcWeatherCircleSub( fx32 c_r, int c_x, int c_y, int n_h, int* st, int* ed );




//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	BGテーブル
//=====================================
static const WEATHER_BG_DATA WSBG[ WEATHER_BG_CONTROL_NUM ] = {
	{ NARC_WEATHER_SYS_SNOW_NCLR,		NARC_WEATHER_SYS_STORM_BG_NCGR,		NARC_WEATHER_SYS_STORM_SC_NSCR },
	{ NARC_WEATHER_SYS_STORM_BG_NCLR,	NARC_WEATHER_SYS_STORM_BG_NCGR,		NARC_WEATHER_SYS_STORM_SC_NSCR },
	{ NARC_WEATHER_SYS_RAINBOW_NCLR,	NARC_WEATHER_SYS_RAINBOW_NCGR,		NARC_WEATHER_SYS_RAINBOW_SC_NSCR },
	{ NARC_WEATHER_SYS_VOLCANO_NCLR,	NARC_WEATHER_SYS_VOLCANO_BG_NCGR,	NARC_WEATHER_SYS_VOLCANO_NSCR },
	{ NARC_WEATHER_SYS_SPARK_NCLR,		NARC_WEATHER_SYS_SPARK_NCGR,		NARC_WEATHER_SYS_SPARK_NSCR },
	{ NARC_WEATHER_SYS_CLOUDINESS_NCLR, NARC_WEATHER_SYS_CLOUDINESS_NCGR,	NARC_WEATHER_SYS_CLOUDINESS_NSCR },
	{ NARC_WEATHER_SYS_FOG_BG_NCLR,		NARC_WEATHER_SYS_CLOUDINESS_NCGR,	NARC_WEATHER_SYS_CLOUDINESS_NSCR },
	{ NARC_WEATHER_SYS_FLASH_NCLR,		NARC_WEATHER_SYS_FLASH_NCGR,		NARC_WEATHER_SYS_FLASH_NSCR },
	{ NARC_WEATHER_SYS_MYSTIC_NCLR,		NARC_WEATHER_SYS_MYSTIC_NCGR,		NARC_WEATHER_SYS_MYSTIC_NSCR },
};

//-------------------------------------
//	天気オブジェクトテーブル
//=====================================
static WEATHER_SYS_DATA WSD[ WEATHER_SYS_NUM ] = {
	{	// SUNNY
		WEATHER_GRAPHIC_NONE, 
		WEATHER_GRAPHIC_NONE,
		sizeof(u32),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherDummy
	},
	{	// CLOUDINESS
		WEATHER_CLOUDINESS_GRAPHIC_CELL,
		WEATHER_CLOUDINESS_GRAPHIC_BG,
		sizeof(WEATHER_CLOUDINESS_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherCloudiness
	},
	{	// RAIN
		WEATHER_RAIN_GRAPHIC_CELL,
		WEATHER_RAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherRain
	},
	{	// STRAIN 
		WEATHER_STRAIN_GRAPHIC_CELL,
		WEATHER_STRAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSTRain
	},
	{	// SPARK 
		WEATHER_STRAIN_GRAPHIC_CELL,
		WEATHER_STRAIN_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSTRainSpark
	},
	{	// SNOW
		WEATHER_SNOW_GRAPHIC_CELL,
		WEATHER_SNOW_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnow
	},
	{	// SNOW_STORM
		WEATHER_SSNOW_GRAPHIC_CELL, 
		WEATHER_SSNOW_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowStorm
	},
	{	// SNOW_SML
		WEATHER_SNOW_S_GRAPHIC_CELL, 
		WEATHER_SNOW_S_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowSML
	},
	{	// FOGL
		WEATHER_FOG2_GRAPHIC_CELL,
		WEATHER_FOG2_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog02
	},
	{	// VOLCANO
		WEATHER_VOLCANO_GRAPHIC_CELL,
		WEATHER_VOLCANO_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherVolcano
	},
	{	// STORM_BG
		WEATHER_STORMBG_GRAPHIC_CELL,
		WEATHER_STORMBG_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherStormBG
	},
	{	// SNOW_D
		WEATHER_SNOW_D_GRAPHIC_CELL,
		WEATHER_SNOW_D_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowD
	},
	{	// SPIRIT
		WEATHER_SPIRIT_GRAPHIC_CELL,
		WEATHER_SPIRIT_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_OBJFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSpirit
	},
	{	// MYSTIC
		WEATHER_MYSTIC_GRAPHIC_CELL,
		WEATHER_MYSTIC_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherMystic
	},
#if 0
	{	// MYSTIC
		WEATHER_MYSTIC_GRAPHIC_CELL,
		WEATHER_MYSTIC_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherMystic
	},
#endif
	{	// MIST1
		WEATHER_KIRI_HARAI_GRAPHIC_CELL,
		WEATHER_KIRI_HARAI_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherKiriHarai_White
	},
	{	// MIST2
		WEATHER_KIRI_HARAI_GRAPHIC_CELL,
		WEATHER_KIRI_HARAI_GRAPHIC_BG,
		sizeof(WEATHER_KIRI_HARAI_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherKiriHarai
	},
	{	// FLASH
		WEATHER_GRAPHIC_NONE,
		WEATHER_FLASH_GRAPHIC_BG,
		sizeof(WEATHER_FLASH_WORK),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFlash
	},
	{	// SPARK_EFF
		WEATHER_SPARK_GRAPHIC_CELL,
		WEATHER_SPARK_GRAPHIC_BG,
		WEATHER_SPARK_WORK_SIZE,
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSpark
	},
	{	// FOGS
		WEATHER_GRAPHIC_NONE,
		WEATHER_GRAPHIC_NONE,
		sizeof(WEATHER_STSW_FOGFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog00
	},
	{	// FOGM
		WEATHER_GRAPHIC_NONE, 
		WEATHER_GRAPHIC_NONE,
		sizeof(WEATHER_STSW_FOGFADE),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherFog01
	},
	{	// RAINBOW
		WEATHER_RAINBOW_GRAPHIC_CELL,
		WEATHER_RAINBOW_GRAPHIC_BG,
		WEATHER_RAINBOW_WORK_SIZE,
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherRainbow
	},
	{	// SNOW_STORM_BG
		WEATHER_SSNOW_BG_GRAPHIC_CELL,
		WEATHER_SSNOW_BG_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherSnowStormBG
	},
	{	// STORM
		WEATHER_STORM_GRAPHIC_CELL, 
		WEATHER_STORM_GRAPHIC_BG,
		sizeof(WEATHER_SYSW_NORMAL),
		NULL,
		NULL,
		WEATHER_SYS_MOVE_NONE,
		0,
		NULL,
		contWeatherStorm
	},
};



//----------------------------------------------------------------------------
/**
 *
 *@brief	描画システムの初期化
 *
 *@param	draw	描画システム
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void init2DDrawSys(WEATHER_SYS_DRAWSYS* draw)
{
	NNSG2dViewRect rect;		// サーフェース矩形
	int i;						// ループ用
	int size;					// ヘッダサイズ取得用
	
	// レンダラ初期化
	RNDP_InitRenderer(&draw->Render, -FX32_ONE);

	// サーフェース初期化
	rect.posTopLeft.x	= WEATHER_RENDER_X;
	rect.posTopLeft.y	= WEATHER_RENDER_Y;
	rect.sizeView.x		= WEATHER_RENDER_WIDTH;
	rect.sizeView.y		= WEATHER_RENDER_HEIGHT;
	REND_OAM_SetSurface(&draw->Surface, &rect, NNS_G2D_SURFACETYPE_MAIN2D, &draw->Render);

	// リソースマネージャ作成
	for(i=0;i<WEATHER_RES_NUM;i++){
		draw->resMan[i] = CLACT_U_ResManagerInit(WEATHER_SYS_NUM, i, USE_HEAPID);
	}

	// リソースマネージャヘッダ作成
	size = CLACT_U_ResManagerGetHeaderSize();
	draw->resHeader = sys_AllocMemory(USE_HEAPID, size * WEATHER_RES_NUM);
	
	// リソースヘッダー読み込み
	loadResHeader(draw->resHeader, CLACT_U_CHAR_RES, NARC_WEATHER_SYS_WEATHER_CHAR_RESDAT );
	loadResHeader(draw->resHeader, CLACT_U_PLTT_RES, NARC_WEATHER_SYS_WEATHER_PLTT_RESDAT);
	loadResHeader(draw->resHeader, CLACT_U_CELL_RES, NARC_WEATHER_SYS_WEATHER_CELL_RESDAT);
	loadResHeader(draw->resHeader, CLACT_U_CELLANM_RES, NARC_WEATHER_SYS_WEATHER_CELLANM_RESDAT);

	// セルアクターセット作成
	{
		CLACT_SETDATA	set;	// セルアクターセット作成データ
		// セルアクターセット作成
		set.WorkNum = WEATEHR_OBJ_MAX;
		set.pRender	= &draw->Render;
		set.heap	= USE_HEAPID;
		draw->clactSet = CLACT_InitSet( &set );

		// 描画タスク生成
		draw->clactDrawTcb = TCB_Add( clactSetDrawTcb, draw, WEATHER_CLACT_DRAW_TCB_PRI );
	} 
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクター描画タスク
 */
//-----------------------------------------------------------------------------
static void clactSetDrawTcb( TCB_PTR tcb, void* p_work )
{
	WEATHER_SYS_DRAWSYS* p_draw = p_work;
	CLACT_Draw( p_draw->clactSet );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースヘッダを１つ読み込む
 *
 *@param	head		ヘッダデータ配列
 *@param	no			読み込むヘッダ配列要素
 *@param	arc_data	アーカイブファイルデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadResHeader(CLACT_U_RES_HEADER_PTR head, int no, int arc_data)
{
	CLACT_U_RES_HEADER_PTR	w_head;		// 作業用ヘッダ
	void* file;

	w_head = CLACT_U_ResManagerGetHeaderNoData(head, no);
//	CLACT_U_ResManagerHeaderLoad(path, w_head, USE_HEAPID);
	file = ArcUtil_Load( ARC_WEATHER_SYS_GRA, arc_data, FALSE, USE_HEAPID, ALLOC_BOTTOM );
	CLACT_U_ResManagerHeaderLoadBinary( file, w_head, USE_HEAPID );
	sys_FreeMemoryEz( file );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	描画システムデータ破棄
 *
 *@param	draw	描画システムデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delete2DDrawSys(WEATHER_SYS_DRAWSYS* draw)
{
	int i;
	CLACT_U_RES_HEADER_PTR	res_head;
	

	// リソースヘッダ破棄
	// リソースマネージャ破棄
	for(i=0;i < WEATHER_RES_NUM;i++){
		res_head = CLACT_U_ResManagerGetHeaderNoData(draw->resHeader, i);
		CLACT_U_ResManagerHeaderFree(res_head);		// ヘッダ破棄

		CLACT_U_ResManagerDelete(draw->resMan[i]);	// マネージャ破棄
	}

	sys_FreeMemoryEz(draw->resHeader);
	draw->resHeader = NULL;

	// セルアクターセット破棄
	CLACT_DestSet(draw->clactSet);
	draw->clactSet = NULL;

	TCB_Delete( draw->clactDrawTcb );
	draw->clactDrawTcb = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気データ代入関数
 *
 *	@param	pData		設定先
 *	@param	CellNo		セルデータの配列要素数
 *	@param	BGNo		BGデータの配列要素数
 *	@param	WorkSize	ワークサイズ
 *	@param	func		コントロール関数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setSysData(WEATHER_SYS_DATA* pData, int CellNo, int BGNo, int WorkSize, TCB_FUNC func)
{
	pData->GraphicNo	= CellNo;		// セルNo
	pData->BGNo			= BGNo;			// BGNo
	pData->WorkByte		= WorkSize;		// 天気システムワークサイズ
	pData->pWork		= NULL;			// システムワーク実態
	pData->pCell		= NULL;			// 読み込んだセルデータ
	pData->cont			= func;			// CONTROL関数
	pData->MoveFlag		= WEATHER_SYS_MOVE_NONE;	// 動作状態
	pData->DivInitSeq	= 0;			// 分割初期化シーケンス
	pData->DivInitTcb	= NULL;			// 分割読み込みTCB
}
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGデータ設定関数
 *
 *	@param	pData			データ格納先
 *	@param	PlttPath		パレットパス
 *	@param	CharPath		キャラクタパス
 *	@param	ScreenPath		スクリーンデータパス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setBGData(WEATHER_BG_DATA* pData, int pltt_arc, int char_arc, int screen_arc )
{
	pData->pltt_arc = pltt_arc;
	pData->char_arc = char_arc;
	pData->screen_arc = screen_arc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターに座標を設定
 *
 *	@param	act			アクター
 *	@param	matrix		座標
 *
 *	@return	none
 *
 * サーフェース内の座標で折り返すように補正を行ってから
 * 登録しています。
 *
 */
//-----------------------------------------------------------------------------
static void setClactMatrix( CLACT_WORK_PTR act, VecFx32* matrix )
{
	// 折り返し処理
	if(matrix->x > WEATHER_OBJ_MAXTURN_X){
		matrix->x %= WEATHER_OBJ_MAXTURN_X;
	}else{

		if( matrix->x < WEATHER_OBJ_MINTURN_X ){	
			matrix->x += WEATHER_OBJ_MAXTURN_X;
		}
	}

	if(matrix->y > WEATHER_OBJ_MAXTURN_Y){
		matrix->y %= WEATHER_OBJ_MAXTURN_Y;
	}else{

		if( matrix->y < WEATHER_OBJ_MINTURN_Y ){	
			matrix->y += WEATHER_OBJ_MAXTURN_Y;
		}
	}

	
	CLACT_SetMatrix( act, matrix );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気システムを初期化
 *
 *@param	fsys		フィールドシステムワーク
 *
 *@return	WEATHER_CONT_PTR	天気システム制御データ
 *
 *	内容
 *		天気システムの制御データを作成
 *		fast_cellシステムのOAMバッファ作成
 *		キャラクタ、パレットのENTRYデータ読み込み
 *
 */
//-----------------------------------------------------------------------------
WEATHER_CONT_PTR InitWeatherSys(FIELDSYS_WORK* fsys)
{
	WEATHER_CONT_PTR pWSYSCONT;

	pWSYSCONT = sys_AllocMemory( USE_HEAPID, sizeof(WEATHER_SYS_CONTROL) );
	// フォグデータ格納先を保存
	pWSYSCONT->fsys = fsys;

	// 描画システム初期化
	init2DDrawSys(&pWSYSCONT->Draw);

	// 天気システムデータ作成
	pWSYSCONT->pWSD = WSD;
	pWSYSCONT->pWSBG = WSBG;

	// アーカイブファイルハンドルオープン
	 pWSYSCONT->ArcHandle = ArchiveDataHandleOpen( ARC_WEATHER_SYS_GRA, USE_HEAPID );
	
	return pWSYSCONT;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気システムを破棄
 *
 *@param	pWes		天気制御データポインタ
 *
 *@return	none
 *
 *	内容
 *		動作している天気管理関数タスクの強制終了---動いているオブジェクトタスクも強制終了
 *		キャラクタ、パレットのENTRYデータ破棄
 *
 */
//-----------------------------------------------------------------------------
void DestWeatherSys(WEATHER_CONT_PTR* pWes)
{
	int i;		// ループ用
	
	if(*pWes != NULL){
		
		// 動作している天気管理タスクの強制終了
		for(i=0;i<WEATHER_SYS_NUM;i++){
			destWeatherSys(*pWes, i);
		}
		
		SetFogData((*pWes)->fsys->fog_data, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		
		G2_SetBG0Priority(1);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );

		// グラフィック描画システム破棄
		delete2DDrawSys(&(*pWes)->Draw);

		// アーカイブファイルハンドル破棄
		ArchiveDataHandleClose( (*pWes)->ArcHandle );
		
		// 管理データ破棄
		sys_FreeMemory(USE_HEAPID,*pWes);
		*pWes = NULL;
	}
} 

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気システムコントロール関数
 *
 *@param	Wes			お天気制御データ
 *@param	cont		コントロールナンバー
 *@param	no			お天気ナンバー
 *
 *@return	BOOL	成功:TRUE	失敗:FALSE
 *
 *	説明
 *		cont
 *			WEATHER_SYS_START=0				// 正常開始
 *			WEATHER_SYS_END=1				// 正常終了(フェードして終わる)
 *			WEATHER_SYS_COMPULSION_END=2	// 強制終了
 *		
 *		contのナンバーによりお天気管理タスクを操作する
 * 
 */
//-----------------------------------------------------------------------------
BOOL ControlWeatherSys(WEATHER_CONT_PTR Wes, int cont, int no)
{
	BOOL ret = TRUE;

	// 天気ナンバーチェック
	if( no > WEATHER_SYS_NUM ){
		return FALSE;
	}
	
	
	switch(cont){
	case WEATHER_SYS_INIT:		// お天気管理タスク初期化
		ret = initWeatherSys(Wes, no);
		break;
	case WEATHER_SYS_INIT_DIV:	// お天気分割初期化タスク登録
		ret = divInitWeatherSysCall( Wes, no );
		break;
	case WEATHER_SYS_START:		// お天気管理タスク登録
		ret = startWeatherSys(Wes, no, WEATHER_SEQ_INIT, WEATEHR_FOG_NEW);
		break;

	case WEATHER_SYS_START_NOFADE:	// フェードインを飛ばす
		ret = startWeatherSys( Wes, no, WEATHER_SEQ_NO_FADE, WEATEHR_FOG_NEW );
		break;

	case WEATHER_SYS_START_WITHFOG:	// フェードインを飛ばす
		// もし現在FOG設定されていなければ、通常のフォグフェードにする
		if( GetFogFlag( Wes->fsys->fog_data ) == TRUE ){
			ret = startWeatherSys( Wes, no, WEATHER_SEQ_INIT, WEATHER_FOG_WITH );
		}else{
			ret = startWeatherSys(Wes, no, WEATHER_SEQ_INIT, WEATEHR_FOG_NEW);
		}
		break;

	case WEATHER_SYS_END:		// お天気管理タスク正常終了
		stopReqWeatherSys(Wes, no, WEATEHR_FOG_NEW);
		break;

	case WEATHER_SYS_END_NOFADE:// フェードアウトなし終了
		stopWeatherSys(Wes, no);
		break;

	case WEATHER_SYS_END_NOFOG:
		stopReqWeatherSys(Wes, no, WEATHER_FOG_NONE);
		break;

	case WEATHER_SYS_DEST:		// お天気管理タスク破棄
		destWeatherSys(Wes, no);
		break;

	default:
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気が終了している常態かチェックする
 *
 *	@param	Wes			天気
 *	@param	no			天気ナンバー
 *
 *	@retval	WEATHER_SYS_MOVE_NONE   	何も無し
 *	@retval	WEATHER_SYS_MOVE_INIT		初期化中
 *  @retval WEATHER_SYS_MOVE_READY		開始待機中
 *  @retval WEATHER_SYS_MOVE_DO			動作中
 */
//-----------------------------------------------------------------------------
int CheckMoveWeatherSys(WEATHER_CONT_PTR Wes, int no)
{
	WEATHER_SYS_DATA* w_sys;

	// 天気ナンバーチェック
	if(no >= WEATHER_SYS_NUM){
		return WEATHER_SYS_MOVE_NONE;
	}
	
	w_sys = Wes->pWSD+no;

	// 天気実体があるかチェック
	return w_sys->MoveFlag;
}


//-----------------------------------------------------------------------------
//	プライベート関数
//		その他
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	BGデフォルトα設定
 *
 *	@param	alpha1		α係数１
 *	@param	alpha2		α係数２
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherBGAlphaDef( int alpha1, int alpha2 )
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BD, alpha1, alpha2);
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作初期化
 *
 *	@param	p_work			動作ワーク
 *	@param	s_x				開始x座標
 *	@param	e_x				終了x座標
 *	@param	count_max		カウント最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherMoveReq( WEATHER_SYS_MOVE_WORK* p_work, int s_x, int e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}
//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL	WeatherMoveMain( WEATHER_SYS_MOVE_WORK* p_work )
{
	int w_x;

	// 現在座標取得
	w_x = p_work->dis_x * p_work->count;
	w_x = w_x / p_work->count_max;

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気　汎用動作ワークリクエスト
 *
 *	@param	p_work		ワーク
 *	@param	s_x			開始値
 *	@param	e_x			終了値
 *	@param	count_max	カウント最大数
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherMoveReqFx( WEATHER_SYS_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max )
{
	p_work->x = s_x;

	p_work->s_x = s_x;
	p_work->dis_x = e_x - s_x;
	p_work->count_max = count_max;
	p_work->count = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気　汎用計算　メイン処理
 *
 *	@param	p_work ワーク
 *
 *	@retval	TRUE		終了
 *	@retval	FALSE		途中
 */
//-----------------------------------------------------------------------------
static BOOL	WeatherMoveMainFx( WEATHER_SYS_MOVE_WORK_FX* p_work )
{
	fx32 w_x;

	// 現在座標取得
	w_x = FX_Mul( p_work->dis_x, p_work->count );
	w_x = FX_Div( w_x, p_work->count_max );

	
	p_work->x = w_x + p_work->s_x;

	if( (p_work->count + 1) <= p_work->count_max ){
		p_work->count++;
		return FALSE;
	}

	p_work->count = p_work->count_max;
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	グラフィックデータ読み込み
 *
 *@param	cont			天気コントローラ
 *@param	GraphicNo		セルパスデータ
 *@param	pCell			格納先
 *
 *@return	none
 *
 *	内容
 *		GraphicNoの絵のデータを読み込み
 *		pCellのメンバに格納する
 *
 */
//-----------------------------------------------------------------------------
static void load2DGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell)
{
	// セル読み込み
	loadCell_CellData( cont, GraphicNo, pCell );

	// セルアニメ読み込み
	loadCell_CellAnmData( cont, GraphicNo, pCell );

	// キャラクタ読み込み
	loadCell_CharData( cont, GraphicNo, pCell );

	// パレット読み込み
	loadCell_PlttData( cont, GraphicNo, pCell );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャに登録
 *	
 *@param	res_head	リソースヘッダ
 *@param	res_type	リソースタイプ
 *@param	head_no		ヘッダナンバー
 *@param	resMan		リソースマネージャ
 *@param	arcHandle	アーカイブファイルハンドル
 *
 *@return	CLACT_U_RES_OBJ_PTR		読み込まれたリソース情報
 *
 *
 */
//-----------------------------------------------------------------------------
static CLACT_U_RES_OBJ_PTR	loadRes(CLACT_U_RES_HEADER_PTR res_head, int res_type, int head_no, CLACT_U_RES_MANAGER_PTR resMan, ARCHANDLE* arcHandle, u32 alloc_type)
{
	CLACT_U_RES_HEADER_PTR	w_head;	// 作業用ヘッダ
	CLACT_U_RES_OBJ_PTR		res_obj;
	int data_idx;
	BOOL comp_flg;
	int vram_type;
	int pltt_num;
	int data_id;

	// リソースのヘッダ取得
	w_head = CLACT_U_ResManagerGetHeaderNoData(res_head, res_type);

	// ヘッダーデータ取得
	data_idx	= CLACT_U_ResManagerHeaderDataIdxGet( w_head, head_no );
	comp_flg	= CLACT_U_ResManagerHeaderCompFlagGet( w_head, head_no );
	vram_type	= CLACT_U_ResManagerHeaderVramTypeGet( w_head, head_no );
	pltt_num	= CLACT_U_ResManagerHeaderPlttNumGet( w_head, head_no );
	data_id		= CLACT_U_ResManagerHeaderDataIDGet( w_head, head_no );

	switch( res_type ){
	case CLACT_U_CHAR_RES:		// キャラクタリソースを管理
		res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType( resMan, arcHandle, data_idx, comp_flg, data_id, vram_type, USE_HEAPID, alloc_type );
		break;
		
	case CLACT_U_PLTT_RES:		// パレットリソースを管理
		res_obj = CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType( resMan, arcHandle, data_idx, comp_flg, data_id, vram_type, pltt_num, USE_HEAPID, alloc_type );
		break;
		
	case CLACT_U_CELL_RES:		// セルリソースを管理
		res_obj = CLACT_U_ResManagerResAddArcKindCell_ArcHandle( resMan, arcHandle, data_idx, comp_flg, data_id, CLACT_U_CELL_RES, USE_HEAPID );
		break;
		
	case CLACT_U_CELLANM_RES:	// セルアニメリソースを管理
		res_obj = CLACT_U_ResManagerResAddArcKindCell_ArcHandle( resMan, arcHandle, data_idx, comp_flg, data_id, CLACT_U_CELLANM_RES, USE_HEAPID );
		break;
	}
	
	// リソース読み込み
	return res_obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	グラフィックデータ破棄
 *
 *@param	cont			天気コントローラ
 *@param	GraphicNo		グラフィックナンバー
 *@param	pCell			グラフィックデータ格納位置
 *
 *@return	none
 *
 *	内容
 *		GraphicNoの絵のデータを破棄する
 *
 */
//-----------------------------------------------------------------------------
static void destGraphicFile(WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell)
{
	int i;	

	if(GraphicNo != WEATHER_GRAPHIC_NONE){
		// キャラクタデータ破棄
		if( pCell->res_obj[ CLACT_U_CHAR_RES ] ){
			CLACT_U_CharManagerDelete(pCell->res_obj[ CLACT_U_CHAR_RES ]);
		}

		// パレットデータ破棄
		if( pCell->res_obj[ CLACT_U_PLTT_RES ] ){
			CLACT_U_PlttManagerDelete(pCell->res_obj[ CLACT_U_PLTT_RES ]);
		}

		// リソース破棄
		for(i=0;i<WEATHER_RES_NUM;i++){
			if( pCell->res_obj[ i ] ){
				CLACT_U_ResManagerResDelete(cont->Draw.resMan[ i ], pCell->res_obj[ i ]);
			}
		}
	}
}


//-----------------------------------------------------------------------------
//	プライベート関数
//		お天気管理タスクを外部から操作する関数郡
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気管理タスク初期化
 *
 *
 *@param	cont	天気コントローラ
 *@param	no		天気ナンバー
 *
 *@return	BOOL	成功:TRUE	失敗:FALSE
 *
 *	内容
 *		グラフィックファイルの読み込み処理
 *
 */
//-----------------------------------------------------------------------------
static BOOL initWeatherSys(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	BOOL ret;
	
	
	// 作成されているかチェック
	if(w_sys->pWork == NULL){
		// ワークの作成
		ret = initWeatherSysWork( cont, w_sys );
		if( ret == FALSE ){
			return FALSE;
		}
	
		// セルアクターを使用できる状態にする
		ret = setUpCell( cont, w_sys );
		if( ret == FALSE ){
			sys_FreeMemoryEz( w_sys->pWork );
			w_sys->pWork = NULL;
			return FALSE;
		}
		w_sys->pWork->pCell = w_sys->pCell;		// セルデータコピー

		// BGセットアップ
		setUpBG( cont, w_sys->BGNo );

		w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;	// 開始待機中
	}


	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気管理タスク”分割”初期化タスクコール
 *
 *
 *@param	cont	天気コントローラ
 *@param	no		天気ナンバー
 *
 *@return	BOOL	成功:TRUE	失敗:FALSE
 *
 *	内容
 *		グラフィックファイルの読み込み処理
 *
 */
//-----------------------------------------------------------------------------
static BOOL divInitWeatherSysCall(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// 作成済みかチェック
	if( w_sys->pWork ){
		return TRUE;
	}

	// ワークを作成する
	if( initWeatherSysWork( cont, w_sys ) == FALSE ){
		return FALSE;
	}

	// タスク登録
	w_sys->DivInitTcb = TCB_Add( divInitWeatherSysTcb, w_sys, WEATHER_TCB_DIV_LOAD_PRI );

	// 初期化中にする
	w_sys->MoveFlag		= WEATHER_SYS_MOVE_INIT;

	// 初期化シーケンス初期化
	w_sys->DivInitSeq	= 0;
	

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気管理タスク開始
 *
 *@param	cont		天気コントローラ
 *@param	no			天気ナンバー
 *@param	init_seq	シーケンス初期化値
 *@param	fog_use		フォグ使用フラグ
 *
 *@return	BOOL	成功:TRUE	失敗:FALSE
 *
 *	内容
 *		ナンバーのお天気管理タスクを開始します。
 *
 */
//-----------------------------------------------------------------------------
static BOOL startWeatherSys(WEATHER_SYS_CONTROL* cont,int no, int init_seq, u32 fog_use)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// 絵が読み込まれているかチェック
	if(w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		if(w_sys->pCell == NULL){
			return FALSE;
		}
	}

	// タスクワークが作成されているかチェック
	if(w_sys->pWork == NULL){
		return FALSE;
	}

	// 開始待ち状態かチェック
	if(w_sys->MoveFlag != WEATHER_SYS_MOVE_READY){
		return FALSE;
	}

	// タスク登録
	w_sys->pWork->tcb = TCB_Add(w_sys->cont, w_sys->pWork, WEATHER_CONTROL_PRI);

	// タスク登録に成功したかチェック
	if(w_sys->pWork->tcb == NULL){
		return FALSE;
	}

	// 実行
	w_sys->MoveFlag = WEATHER_SYS_MOVE_DO;
	
	// データ設定
	w_sys->pWork->Sequence = init_seq;		// 作業シーケンス初期化
	w_sys->pWork->ContFlag = 0;				// 外部コントロールフラグ
	w_sys->pWork->Dummy.pNext = &w_sys->pWork->Dummy;
	w_sys->pWork->Dummy.pPrev = &w_sys->pWork->Dummy;
	w_sys->pWork->fog_use	= fog_use;		// フォグ使用フラグ
	w_sys->pWork->snd_play		= FALSE;

	w_sys->pWork->CameraTarget = *(NNS_G3dGlbGetCameraTarget());
	if(w_sys->WorkByte > 0){
		w_sys->pWork->work = sys_AllocMemory(USE_HEAPID, w_sys->WorkByte);	// ワーク領域
		memset( w_sys->pWork->work, 0, w_sys->WorkByte );
	}else{
		w_sys->pWork->work = NULL;
	}

	// BGセットアップ
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(1);
		G2_SetBG0Priority(2);
//		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気管理タスク終了	フェードアウトしてから終了
 *
 *@param	cont	天気コントローラ
 *@param	no		天気ナンバー
 *@param	fog_use	フォグ使用フラグ
 *
 *@return	none
 *
 *	内容
 *		ナンバーのお天気管理タスクをフェードアウト終了させます
 *		*例：だんだん雨が止んで終わるなど
 *
 */
//-----------------------------------------------------------------------------
static void stopReqWeatherSys(WEATHER_SYS_CONTROL* cont,int no, u32 fog_use)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;

	// お天気管理タスクが動いているかチェック
	if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
		w_sys->pWork->ContFlag = WEATHER_SYS_END;	// 終了フラグを立てる
		w_sys->pWork->fog_use = fog_use;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気終了	フェードアウトなし
 *
 *	@param	cont	天気コントローラ
 *	@param	no		天気ナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void stopWeatherSys( WEATHER_SYS_CONTROL* cont,int no )
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	if( CheckMoveWeatherSys( cont, no ) == WEATHER_SYS_MOVE_DO ){
		// 天気のシーケンスをWEATHER_SEQ_DESTにしてコントロール関数をコール
		w_sys->pWork->Sequence = WEATHER_SEQ_DEST;
	
		w_sys->cont( NULL, w_sys->pWork );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	お天気管理タスク強制終了
 *
 *@param	cont	天気コントローラ
 *@param	no		天気ナンバー
 *
 *@return	none
 *
 *	内容
 *		管理しているオブジェを全て破棄
 *		絵のデータを破棄
 *		自分を破棄
 *
 */
//-----------------------------------------------------------------------------
static void destWeatherSys(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	
	// BG面の表示をOFF
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE ){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(3);
		G2_SetBG0Priority(1);

		//　αブレンド破棄
		G2_BlendNone();
	}
	
	// 絵のデータ破棄
	if(w_sys->pCell != NULL){
		// 絵のデータ破棄
		destGraphicFile(cont, w_sys->GraphicNo, w_sys->pCell);
		sys_FreeMemory(USE_HEAPID, w_sys->pCell);
		w_sys->pCell = NULL;

		// 分割読み込みタスク破棄
		if( w_sys->DivInitTcb != NULL ){
			TCB_Delete( w_sys->DivInitTcb );
			w_sys->DivInitTcb = NULL;
		}
	}
	
	// お天気管理タスクが動いているかチェック
	if(w_sys->pWork != NULL){
		// 管理しているオブジェを破棄
		destObjAll(&w_sys->pWork->Dummy);

		// 音が鳴っているなら破棄
		if( w_sys->pWork->snd_play == TRUE ){
			WeatherLoopSndStop( w_sys->pWork );
		}

		// ワーク領域
		if(w_sys->pWork->work != NULL){
			sys_FreeMemory(USE_HEAPID, w_sys->pWork->work);
			w_sys->pWork->work = NULL;
		}
/*	CLACT_SET_DELETE
		// アクターセット破棄
		if( w_sys->pWork->clactSet ){
			CLACT_DestSet(w_sys->pWork->clactSet);
		}
//*/
		// 初期化タスクを破棄
		if( w_sys->MoveFlag == WEATHER_SYS_MOVE_INIT ){
			
			if( w_sys->DivInitTcb ){
				TCB_Delete(w_sys->DivInitTcb);					// TCB破棄
			}
		}else{
			
			// 動作タスクを破棄
			if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
				
				TCB_Delete(w_sys->pWork->tcb);					// TCB破棄
			}
		}
		sys_FreeMemory(USE_HEAPID, w_sys->pWork);	// ワーク破棄
		w_sys->pWork = NULL;
	}
}


// システム操作サブ関数
//----------------------------------------------------------------------------
/**
 *
 *	@brief	noの天気の天気システムデータを破棄
 *
 *	@param	cont		天気制御システム
 *	@param	no			天気no
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void stopWeatherWork(WEATHER_SYS_CONTROL* cont,int no)
{
	WEATHER_SYS_DATA* w_sys = cont->pWSD+no;
	stopWeatherWork_local( w_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気システムデータを破棄
 *	@param	w_sys
 *	@return
 */
//-----------------------------------------------------------------------------
static void stopWeatherWork_local(WEATHER_SYS_DATA* w_sys)
{
	// BG面の表示をOFF
	if(w_sys->BGNo != WEATHER_GRAPHIC_NONE ){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		G2_SetBG2Priority(3);
		G2_SetBG0Priority(1);
		//　αブレンド破棄
		G2_BlendNone();
	}

	// お天気管理タスクが動いているかチェック
	if(w_sys->pWork != NULL){
		// 管理しているオブジェを破棄
		destObjAll(&w_sys->pWork->Dummy);

		// 音が鳴っているなら破棄
		if( w_sys->pWork->snd_play == TRUE ){
			WeatherLoopSndStop( w_sys->pWork );
		}
		
		// タスクを破棄
		if(w_sys->MoveFlag == WEATHER_SYS_MOVE_DO){
			
			TCB_Delete(w_sys->pWork->tcb);					// TCB破棄
			w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGデータセットアップ
 *
 *	@param	cont	天気コントロールデータ
 *	@param	BGNo	BGナンバー
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setUpBG( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	// パレット読み込み
	initBgPltt( cont, BGNo );
	
	// キャラクタ読み込み
	initBgChar( cont, BGNo );

	// スクリーンデータ
	initBgScr( cont, BGNo );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターを使用できる状態にする
 *
 *	@param	cont		コントロールデータ
 *	@param	w_sys		データ郡
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL setUpCell( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	BOOL ret;

	// セルデータが必要かチェック
	if( w_sys->GraphicNo  != WEATHER_GRAPHIC_NONE ){
		
/*	CLACT_SET_DELETE
		// セルアクターセット初期化
		initClactSet( cont, w_sys );
//*/

		// セルデータ作成済みかチェック
		if( w_sys->pCell == NULL ){

			// セルデータ格納メモリ確保
			ret = initCellDataMemory( w_sys );
			if( ret == FALSE ){
/*	CLACT_SET_DELETE
				// アクターセット破棄
				CLACT_DestSet(w_sys->pWork->clactSet);
//*/
				return FALSE;
			}

			// セルアクター登録データ作成
			// 読み込み
			load2DGraphicFile(cont, w_sys->GraphicNo, w_sys->pCell);

			// セルアクター登録データ作成
			initClactAddData( cont, w_sys );
		}
	}

	return TRUE;
}


// 初期化処理分割関数
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分割処理TCB
 *
 *	@param	tcb		タスクポインタ
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void divInitWeatherSysTcb( TCB_PTR tcb, void* work )
{
	WEATHER_SYS_DATA* w_sys = work;
	WEATHER_SYS_CONTROL* cont = w_sys->pWork->pWSysCont;
	BOOL check;

	switch( w_sys->DivInitSeq ){
	case 0:

/*	CLACT_SET_DELETE
		// セルアクターセット初期化
		initClactSet( cont, w_sys );
//*/

		// セルデータ格納先メモリ確保
		check = initCellDataMemory( w_sys );
		GF_ASSERT( check );
		w_sys->DivInitSeq++;
		break;

	case 1:
		// セルデータ読み込み
		loadCell_CellData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;

	case 2:
		// パレット読み込み
		initBgPltt( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 3:
		// セルアニメデータ読み込み
		loadCell_CellAnmData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;

	case 4:
		// キャラクタ読み込み
		initBgChar( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 5:
		// キャラクタデータ読み込み
		loadCell_CharData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;
		
	case 6:
		// スクリーン読み込み
		initBgScr( cont, w_sys->BGNo );
		w_sys->DivInitSeq++;
		break;

	case 7:
		// パレットデータ読み込み
		loadCell_PlttData( cont, w_sys->GraphicNo, w_sys->pCell );
		w_sys->DivInitSeq++;
		break;
	
	case 8:
		// セルアクター追加データ作成
		initClactAddData( cont, w_sys );
		w_sys->pWork->pCell = w_sys->pCell;		// セルデータコピー

		w_sys->MoveFlag = WEATHER_SYS_MOVE_READY;	// 開始待機中
		w_sys->DivInitSeq = 0;
		w_sys->DivInitTcb = NULL;
		TCB_Delete( tcb );
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ワークのメモリ確保
 *
 *	@param	cont	コントローラ
 *	@param	w_sys	ワークの格納先
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL initWeatherSysWork( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->pWork ){
		// 確保済み
		return TRUE;
	}
	
	// ワークの作成
	w_sys->pWork = sys_AllocMemory(USE_HEAPID, sizeof(WEATHER_SYS_WORK));
	if(w_sys->pWork == NULL){
		return FALSE;
	}
	memset( w_sys->pWork, 0, sizeof(WEATHER_SYS_WORK) );

	// データ設定
	w_sys->pWork->pWSysCont= cont;	// コントローラポイント
	w_sys->pWork->Sequence = 0;		// 作業シーケンス初期化
	w_sys->pWork->ContFlag = 0;		// 外部コントロールフラグ
	w_sys->pWork->Dummy.pNext = &w_sys->pWork->Dummy;
	w_sys->pWork->Dummy.pPrev = &w_sys->pWork->Dummy;
	w_sys->pWork->work	= NULL;		// ワーク領域
	w_sys->pWork->pWSD	= w_sys;	// 自分を子供にも教えておく

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターセットの作成
 *
 *	@param	cont		コントローラ
 *	@param	w_sys		天気データ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initClactSet( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{

/*	CLACT_SET_DELETE
	CLACT_SETDATA	set;	// セルアクターセット作成データ


	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		
		if( w_sys->pWork->clactSet ){
			// 確保済み
			return;
		}

		// セルアクターセット作成
		set.WorkNum = WEATEHR_OBJ_MAX;
		set.pRender	= &cont->Draw.Render;
		set.heap	= USE_HEAPID;
		w_sys->pWork->clactSet = CLACT_InitSet( &set );
	}
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルデータ格納先メモリ領域確保
 *
 *	@param	w_sys	天気データ格納先
 *
 *	@retval TRUE	成功
 *	@retval FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL initCellDataMemory( WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		if( w_sys->pCell ){

			return TRUE;	// 確保済み
		}
		
		// グラフィックフィックファイルを読み込む領域を作成
		w_sys->pCell = sys_AllocMemory(USE_HEAPID, sizeof(WATHER_GRAPHIC_FILE_DATA));
		if(w_sys->pCell == NULL){
			return FALSE;
		}
		memset( w_sys->pCell, 0, sizeof(WATHER_GRAPHIC_FILE_DATA) );
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターデータ　　セル読み込み
 *
 *	@param	cont			コントローラ
 *	@param	GraphicNo		グラフィックナンバー
 *	@param	pCell			セルデータ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CellData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// セルデータ読み込み
		pCell->res_obj[ CLACT_U_CELL_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CELL_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CELL_RES ],
				cont->ArcHandle, ALLOC_TOP );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターデータ	セルアニメ読み込み
 *
 *	@param	cont			コントローラ
 *	@param	GraphicNo		グラフィックファイルナンバー
 *	@param	pCell			セルデータ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CellAnmData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// セルアニメデータ読み込み
		pCell->res_obj[ CLACT_U_CELLANM_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CELLANM_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CELLANM_RES ],
				cont->ArcHandle, ALLOC_TOP );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターデータ読み込み	キャラクタデータ
 *
 *	@param	cont			コントローラ
 *	@param	GraphicNo		グラフィックデータナンバー
 *	@param	pCell			セルデータ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_CharData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// キャラクタデータ読み込み
		pCell->res_obj[ CLACT_U_CHAR_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_CHAR_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_CHAR_RES ],
				cont->ArcHandle, ALLOC_BOTTOM );
		
		// Vram転送
		CLACT_U_CharManagerSetAreaCont( pCell->res_obj[ CLACT_U_CHAR_RES ] );
		// キャラクタの読み込んできたデータのみ破棄
		CLACT_U_ResManagerResOnlyDelete( pCell->res_obj[ CLACT_U_CHAR_RES ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクターデータ	パレット読み込み
 *
 *	@param	cont			コントローラ
 *	@param	GraphicNo		グラフィックファイルナンバー
 *	@param	pCell			セルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void loadCell_PlttData( WEATHER_SYS_CONTROL* cont, int GraphicNo, WATHER_GRAPHIC_FILE_DATA* pCell )
{
	if(GraphicNo != WEATHER_GRAPHIC_NONE){
	
		// パレットデータ読み込み
		pCell->res_obj[ CLACT_U_PLTT_RES ] = loadRes(
				cont->Draw.resHeader, CLACT_U_PLTT_RES, 
				GraphicNo,
				cont->Draw.resMan[ CLACT_U_PLTT_RES ],
				cont->ArcHandle, ALLOC_BOTTOM );
		
		// Vram転送
		CLACT_U_PlttManagerSetCleanArea( pCell->res_obj[ CLACT_U_PLTT_RES ] );
		// パレットの読み込んできたデータのみ破棄
		CLACT_U_ResManagerResOnlyDelete( pCell->res_obj[ CLACT_U_PLTT_RES ] );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター登録データ作成
 *
 *	@param	cont		コントローラ
 *	@param	w_sys		天気データ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initClactAddData( WEATHER_SYS_CONTROL* cont, WEATHER_SYS_DATA* w_sys )
{
	if( w_sys->GraphicNo != WEATHER_GRAPHIC_NONE){
		// セルアクター登録データ作成
		getHeader(&w_sys->pCell->head, cont, w_sys->pCell, 0, WEATHER_SYS_BG_2_DRAW_PRI);
		memset(&w_sys->pCell->add, 0, sizeof(CLACT_ADD));
		w_sys->pCell->add.ClActSet		= cont->Draw.clactSet;
		w_sys->pCell->add.ClActHeader	= &w_sys->pCell->head;
		w_sys->pCell->add.sca.x			= FX32_ONE;
		w_sys->pCell->add.sca.y			= FX32_ONE;
		w_sys->pCell->add.sca.z			= FX32_ONE;
		w_sys->pCell->add.DrawArea		= 1;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG	パレット読み込み
 *
 *	@param	cont		コントローラ
 *	@param	BGNo		読み込むBGデータナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgPltt( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BGファイルデータ読み込み領域

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// パレット読み込み
		BG.pPlttBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].pltt_arc, USE_HEAPID );
		// アンパック
		NNS_G2dGetUnpackedPaletteData( BG.pPlttBuff, &BG.pPltt );
		// BGの読み込み			
		GF_BGL_PaletteSet(FLD_MBGFRM_EFFECT2,
				BG.pPltt->pRawData,
				32,
				32 * (WEATHER_PLTT_OFS));
		sys_FreeMemoryEz( BG.pPlttBuff );
		BG.pPlttBuff = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG		キャラクタデータ読み込み
 *
 *	@param	cont		コントローラ
 *	@param	BGNo		BGデータナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgChar( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BGファイルデータ読み込み領域

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// ファイル読み込み
		BG.pCharBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].char_arc, USE_HEAPID );
		// アンパック
		NNS_G2dGetUnpackedCharacterData( BG.pCharBuff, &BG.pChar );

		GF_BGL_LoadCharacter( cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				BG.pChar->pRawData,
				BG.pChar->szByte,
				0 );
		sys_FreeMemoryEz( BG.pCharBuff );
		BG.pCharBuff = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG		スクリーンデータ読み込み
 *
 *	@param	cont		コントローラ
 *	@param	BGNo		BGデータナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBgScr( WEATHER_SYS_CONTROL* cont, int BGNo )
{
	WATHER_BG_FILE_DATA	BG;		// BGファイルデータ読み込み領域

	if(BGNo != WEATHER_GRAPHIC_NONE){
		// BGOFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		
		// スクリーンデータ
		BG.pScreenBuff = ArchiveDataLoadAllocByHandle( cont->ArcHandle, cont->pWSBG[BGNo].screen_arc, USE_HEAPID );
		GF_ASSERT(BG.pScreenBuff);
		// アンパック
		NNS_G2dGetUnpackedScreenData( BG.pScreenBuff, &BG.pScreen );
		GF_BGL_LoadScreen(cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				(void*)BG.pScreen->rawData,
				BG.pScreen->szByte,
				0 );

		GF_BGL_ScreenBufSet(cont->fsys->bgl, FLD_MBGFRM_EFFECT2, (void*)BG.pScreen->rawData,
				BG.pScreen->szByte );
		
		GF_BGL_ScrPalChange(
				cont->fsys->bgl, FLD_MBGFRM_EFFECT2,
				0, 0,
				32, 32,
				WEATHER_PLTT_OFS
				);
		GF_BGL_LoadScreenReq( cont->fsys->bgl, FLD_MBGFRM_EFFECT2 );

		sys_FreeMemoryEz( BG.pScreenBuff );
		BG.pScreenBuff = NULL;
	}
}


//-----------------------------------------------------------------------------
//	プライベート関数
//		お天気管理タスク内処理用関数郡	
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェのワーク領域を確保
 *
 *@param	pData		確保するオブジェデータ
 *@param	Byte		確保するバイトサイズ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void allocObjWork(WAETHER_OBJ_DATA* pData, int byte)
{
	GF_ASSERT( pData->work == NULL );
	GF_ASSERT( byte > 0 );
	GF_ASSERT( byte <= WEATHER_OBJ_DATA_WORK_SIZE );
	
//	pData->work = sys_AllocMemory(USE_HEAPID, byte);
	pData->work = pData->work_buff;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェのワーク領域を破棄
 *
 *@param	pData		破棄するオブジェデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void freeObjWork(WAETHER_OBJ_DATA* pData)
{
	pData->work = NULL;
	memset( pData->work_buff, 0, WEATHER_OBJ_DATA_WORK_SIZE );
/*	if(pData->work != NULL){
		sys_FreeMemory(USE_HEAPID, pData->work);
		pData->work = NULL;
	}//*/
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェタスクを登録
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	w_byte		ワークバイトサイズ
 *
 *@return	WAETHER_OBJ_DATA*	成功:オブジェクトのポインタ	失敗:NULL
 *
 *	内容
 *		管理関数ワークからオブジェを作成してリスト登録
 *
 */
//-----------------------------------------------------------------------------
static WAETHER_OBJ_DATA* addObj(WEATHER_SYS_WORK* pWork, int w_byte)
{
	WAETHER_OBJ_DATA* p_obj;		// オブジェデータ
	WEATHER_SYS_CONTROL* cont = (WEATHER_SYS_CONTROL*)pWork->pWSysCont;	// コントローラ
	
	// オブジェクトデータ作成
	p_obj = getCleanObjData( pWork );
	if(p_obj == NULL){
		return NULL;
	}

	// データセット
	p_obj->pWSysCont				= cont;			// 親の天気管理データ
	
	// リストに登録
	p_obj->pNext				= &pWork->Dummy;
	p_obj->pPrev				= pWork->Dummy.pPrev;
	pWork->Dummy.pPrev->pNext	= p_obj;
	pWork->Dummy.pPrev			= p_obj;

	p_obj->clact_w = CLACT_Add(&pWork->pCell->add);
	if(p_obj->clact_w == NULL){
		destObj(p_obj);
		return NULL;
	}

	// ワーク作成
	allocObjWork(p_obj, w_byte);
	if(p_obj->work == NULL){
		destObj(p_obj);
		return NULL;
	}
	
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダ作成
 *	
 *@param	head	ヘッダ
 *@param	cont	天気管理データ
 *@param	pcell	セルデータ
 *@param	vram_trans	Vram転送か
 *@param	priority	優先順位
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void getHeader(CLACT_HEADER_PTR head, WEATHER_SYS_CONTROL* cont, WATHER_GRAPHIC_FILE_DATA* pcell,int vram_trans, int priority )
{
	int id[ WEATHER_RES_NUM ];		// リソース分のID格納バッファ
	int i;							// ループ用

	// IDを取得
	for(i=0;i<WEATHER_RES_NUM;i++){
		id[ i ] = CLACT_U_ResManagerGetResObjID( pcell->res_obj[ i ] );
	}

	// ヘッダ作成
	CLACT_U_MakeHeader( 
			head,
			id[ CLACT_U_CHAR_RES ], id[ CLACT_U_PLTT_RES ], 
			id[ CLACT_U_CELL_RES ], id[ CLACT_U_CELLANM_RES ],
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			vram_trans, priority,
			cont->Draw.resMan[ CLACT_U_CHAR_RES ], cont->Draw.resMan[ CLACT_U_PLTT_RES ],
			cont->Draw.resMan[ CLACT_U_CELL_RES ], cont->Draw.resMan[ CLACT_U_CELLANM_RES ],
			NULL, NULL);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録オブジェタスク破棄
 *
 *@param	pData		破棄するオブジェクトデータ
 *
 *@return	none
 *
 *	内容
 *		オブジェクトデータを破棄する
 *
 */
//-----------------------------------------------------------------------------
static void destObj(WAETHER_OBJ_DATA* pData)
{
//	WEATHER_SYS_CONTROL* cont = (WEATHER_SYS_CONTROL*)pData->pWSysCont;	// コントローラ

	// リストから破棄
	pData->pPrev->pNext	= pData->pNext;
	pData->pNext->pPrev	= pData->pPrev;

	// セルアクターから破棄
	if(pData->clact_w){
		CLACT_Delete(pData->clact_w);
		pData->clact_w = NULL;
	}

	// ワーク破棄
	freeObjWork(pData);	
		
	// 破棄
	memset( pData, 0, sizeof(WAETHER_OBJ_DATA) );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録オブジェタスク全破棄
 *
 *@param	pDummy		破棄するオブジェクトリストの先頭データ
 *
 *@return	none
 *
 *	内容
 *		オブジェクトデータを全て破棄する
 *
 */
//-----------------------------------------------------------------------------
static void destObjAll(WAETHER_OBJ_DATA* pDummy)
{
	WAETHER_OBJ_DATA* p_work;		// 破棄作業用
	WAETHER_OBJ_DATA* p_next;		// 次のオブジェクト
	
	// 全破棄
	p_work = pDummy->pNext;
	while(p_work != pDummy){
		p_next = p_work->pNext;
		destObj(p_work);		// 破棄
		p_work = p_next;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録された全オブジェクトを動かす
 *
 *@param	pDummy		動かすオブジェクトリスト
 *@param	pFunc		動かす関数
 *
 *@return	none
 *
 *	内容
 *		オブジェクトデータを動かす
 *
 */
//-----------------------------------------------------------------------------
static void moveFuncObj(WAETHER_OBJ_DATA* pDummy, objFunc pFunc)
{
	WAETHER_OBJ_DATA* p_work;		// 作業用
	WAETHER_OBJ_DATA* p_work_next;	// 作業用

	// 全部動かす
	p_work = pDummy->pNext;
	p_work_next = p_work->pNext;
	while(p_work != pDummy){
		pFunc(p_work);		// 動かす
		
		p_work = p_work_next;
		p_work_next = p_work->pNext;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクトの描画
 *
 *@param	pData		天気１つのデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void drawObj(WEATHER_SYS_WORK* pData)
{
/*	CLACT_SET_DELETE
	CLACT_Draw(pData->clactSet);
//*/
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクト座標を取得
 *
 *@param	obj		取得するオブジェ
 *
 *@return	座標
 *
 *
 */
//-----------------------------------------------------------------------------
static VecFx32 getObjMat( WAETHER_OBJ_DATA* obj )
{
	const VecFx32* mat = CLACT_GetMatrix(obj->clact_w);

	return *mat;
}

// スクロール座標取得
static void getScrollNum(fx32* x, fx32* y, WEATHER_SYS_WORK* pWork)
{
	
	VecFx32	now_mat;				// 今の座標
	fx32 scl_x, scl_y;				// Scroll座標
	fx32 d_x, d_y;					// 2dで１の３ｄの値
	fx32 dist_x, dist_y;			// 移動した値
	int	mark;						// 符号
	fx32 aspect;					// アスペクト比
	
	
	// 今のカメラの2dで1の３ｄの値を求める
	aspect = FX_Div(4*FX32_ONE, 3*FX32_ONE);
	GetPerspectiveScreenSize( 
			GFC_GetCameraPerspWay( pWork->pWSysCont->fsys->camera_ptr ),
			GFC_GetCameraDistance(pWork->pWSysCont->fsys->camera_ptr),
			aspect,
			&d_x, &d_y);
	d_x = FX_Div(d_x, 256*FX32_ONE);
	d_y = FX_Div(d_y, 192*FX32_ONE);
	


	// 動いたら動いた方向に０．５足す（小数点の誤差で値が変わらないため）
	now_mat = *(NNS_G3dGlbGetCameraTarget());
	
	dist_x = (now_mat.x - pWork->CameraTarget.x);
	dist_y = (now_mat.z - pWork->CameraTarget.z);

	// プラスで計算する
	mark = FX32_ONE;
	if(dist_x < 0){		// ーの時は＋の値にする
		mark = -FX32_ONE;
		dist_x = FX_Mul( dist_x, -FX32_ONE );
	}
	scl_x = FX_Div(dist_x, d_x);	// スクロール座標を計算
	if( mark < 0 ){		// 元の符号に戻す
		scl_x = FX_Mul( scl_x, mark );	// 元の符号に戻す
	}

	mark = FX32_ONE;
	if(dist_y < 0){		// ーの時は＋の値にする
		mark = -FX32_ONE;
		dist_y = FX_Mul( dist_y, -FX32_ONE );
	}	
	scl_y = FX_Div(dist_y, d_y);	// スクロール座標を求める
	if( mark < 0 ){
		scl_y = FX_Mul( scl_y, mark );	// 元の符号に戻す
	}
		
	// 今の座標を取得
	if((scl_x + scl_y) != 0){
		pWork->CameraTarget = now_mat;
	}

	*x = scl_x;
	*y = scl_y;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	登録された全オブジェクトの座標をscrollにあわせる
 *
 *@param	pWork		Scrollさせる天気コントローラの本体
 *@param	x, y		スクロール座標(いらないときはNULL)
 *
 *@return	none
 *
 *	内容
 *		オブジェクトの座標をこのターンでのカメラのターゲットの移動地に合わせる
 *
 */
//-----------------------------------------------------------------------------
static void scrollObj(WEATHER_SYS_WORK* pWork,int* x, int* y)
{
	WAETHER_OBJ_DATA* p_work;		// 作業用
	fx32 scl_x, scl_y;		// スクロール座標	
	VecFx32 mat;			// 座標
	

	getScrollNum(&scl_x,&scl_y, pWork);
	
	
	// 全部オブジェクトに反映
	p_work = pWork->Dummy.pNext;
	while(p_work != &pWork->Dummy){
		// 今の座標取得
		mat = getObjMat(p_work);
		
		mat.x -= scl_x;
		mat.y -= scl_y;

		// 座標設定
		setClactMatrix(p_work->clact_w, &mat);
		
		p_work = p_work->pNext;
	}

	if(x != NULL){
		*x = scl_x >> FX32_SHIFT;
		if( *x < 0 ){
			*x += 1;	// マイナスのとき-1分の誤差が出るため
		}
	}
	if(y != NULL){
		*y = scl_y >> FX32_SHIFT;
		if( *y < 0 ){
			*y += 1;	// マイナスのとき-1分の誤差が出るため
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトフェードパラメータの初期化
 *
 *	@param	data					オブジェフェードワーク
 *	@param	pWork					天気システムワーク
 *	@param	objAddNum				オブジェクト登録数
 *	@param	objAddTmgMax			登録タイミング
 *	@param	OBJ_ADD_NUM_END			オブジェクト登録数　終了値
 *	@param	OBJ_ADD_TMG_END			オブジェクト１回の登録数　終了値
 *	@param	OBJ_ADD_TMG_SUM         登録タイミングカウンタ　終了値
 *	@param	OBJ_ADD_NUM_SUM_TMG     登録タイミングカウンタ変更値
 *	@param	OBJ_ADD_NUM_SUM         オブジェクト１回の登録数を変更するタイミング
 *	@param	add						登録関数
 */
//-----------------------------------------------------------------------------
static void weatherSysObjFadeInit( WEATHER_SYS_OBJ_FADE* data, WEATHER_SYS_WORK* pWork, s32 objAddNum, s32 objAddTmgMax, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM_TMG, s32 OBJ_ADD_NUM_SUM, OBJADD_FUNC add )
{
	data->pWork				= pWork;
	data->objAddNum			= objAddNum;	
	data->objAddTmg			= 0;						
	data->objAddTmgMax		= objAddTmgMax;	
	data->objAddNumSum		= 0;						
	data->OBJ_ADD_NUM_END	= OBJ_ADD_NUM_END;
	data->OBJ_ADD_TMG_END	= OBJ_ADD_TMG_END;
	data->OBJ_ADD_TMG_SUM	= OBJ_ADD_TMG_SUM;
	data->OBJ_ADD_NUM_SUM_TMG = OBJ_ADD_NUM_SUM_TMG;
	data->OBJ_ADD_NUM_SUM	= OBJ_ADD_NUM_SUM;
	data->add				= add;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードアウトのための設定
 *
 *	@param	data				ワーク
 *	@param	OBJ_ADD_NUM_END			オブジェクト登録数　終了値
 *	@param	OBJ_ADD_TMG_END			オブジェクト１回の登録数　終了値
 *	@param	OBJ_ADD_TMG_SUM         登録タイミングカウンタ　終了値
 *	@param	OBJ_ADD_NUM_SUM         オブジェクト１回の登録数を変更するタイミング
 */
//-----------------------------------------------------------------------------
static void weatherSysObjFadeOutSet( WEATHER_SYS_OBJ_FADE* data, s32 OBJ_ADD_NUM_END, s32 OBJ_ADD_TMG_END, s32 OBJ_ADD_TMG_SUM, s32 OBJ_ADD_NUM_SUM )
{
	data->OBJ_ADD_NUM_END	= OBJ_ADD_NUM_END;
	data->OBJ_ADD_TMG_END	= OBJ_ADD_TMG_END;
	data->OBJ_ADD_TMG_SUM	= OBJ_ADD_TMG_SUM;
	data->OBJ_ADD_NUM_SUM	= OBJ_ADD_NUM_SUM;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オブジェクトフェード
 *
 *@param	data		オブジェクトのフェードデータ
 *
 *@retval	0			フェード未終了
 *@retval	1			登録タイミングカウンタフェード終了
 *@retval	2			登録数フェード終了
 *@retval	3			完全終了
 *
 * 各カウンタの初期化を事前にしておく必要があります。
 * カウンタはポインタ参照なので、書き換えないようにしておく必要があります。
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysObjFade(WEATHER_SYS_OBJ_FADE* data)
{
	int fade_flag;
	int ret = 0;
	

	// フェード終了チェック
	// タイミング-------------------------------------------
	// 足す値が０ならタイミングフェード終了
	if(data->OBJ_ADD_TMG_SUM == 0){
		ret |= 1;
	}else{
		// フェードイン、アウトチェック
		if(data->OBJ_ADD_TMG_SUM > 0){
			fade_flag = 0;		// 変更値がプラスなのでフェードイン
		}else{
			fade_flag = 1;		// 変更値がマイナスなのでフェードアウト
		}
		// 登録タイミング終了点にきていないかチェック
		if(((data->objAddTmgMax >= data->OBJ_ADD_TMG_END)&&(fade_flag == 0)) ||
			((data->objAddTmgMax <= data->OBJ_ADD_TMG_END)&&(fade_flag == 1))){
			ret |= 1;

			data->objAddTmgMax = data->OBJ_ADD_TMG_END;
		}
	}

	// 登録数---------------------------------------------------
	// 足す値が０なら登録数フェード終了
	if(data->OBJ_ADD_NUM_SUM == 0){
		ret |= 2;
	}else{
		
		// フェードイン、アウトチェック
		if(data->OBJ_ADD_NUM_SUM > 0){
			fade_flag = 0;		// 変更値がプラスなのでフェードイン
		}else{
			fade_flag = 1;		// 変更値がマイナスなのでフェードアウト
		}
		// オブジェクト登録終了点にきていないかチェック
		if(((data->objAddNum >= data->OBJ_ADD_NUM_END)&&(fade_flag == 0)) ||
			((data->objAddNum <= data->OBJ_ADD_NUM_END)&&(fade_flag == 1))){
		
			ret |= 2;
			data->objAddNum = data->OBJ_ADD_NUM_END;
		}
	}
	

	// タイミングカウンタが最小になるまでカウント作業
	(data->objAddTmg)--;
	if(data->objAddTmg <= 0){

		// 登録
		data->add(data->pWork, data->objAddNum);

		data->objAddTmg = data->objAddTmgMax;			// 登録タイミングセット
		
		// タイミング-------------------------------------------
		if((ret & 1) == 0){
			data->objAddTmgMax += data->OBJ_ADD_TMG_SUM;	// 雨タイミング計算
		}
		
	
		// 登録数---------------------------------------------------
		if((ret & 2) == 0){
			(data->objAddNumSum)++;
			if(data->objAddNumSum >= data->OBJ_ADD_NUM_SUM_TMG){
				data->objAddNumSum = 0;
				data->objAddNum += data->OBJ_ADD_NUM_SUM;	// 登録数アッド
			}
		}
	}

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォグフェードイン　初期化処理　パック
 *
 *	@param	fogParam		フォグパラメータワーク
 *	@param	fogData			フォグテーブルワーク
 *	@param	Fog				フォグデータ
 *	@param	fog_slope		フォグスロープ
 *	@param	fog_offs		フォグオフセット
 *	@param	color			カラー
 *	@param	timing			タイミング
 *	@param	fog_use_flg		フォグ動作フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogFadeInInitPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color, int timing, u32 fog_use_flg )
{
	fogData->Fog = Fog;
	
	if( fog_use_flg != WEATHER_FOG_NONE ){

		if( fog_use_flg == WEATEHR_FOG_NEW ){
			weatherSysFogParamSet( Fog, fog_slope, fog_offs, color );
			weatherSysFogTblInit( fogData );
			weatherSysFogFadeInit( fogData, timing, TRUE );
		}else if( fog_use_flg == WEATHER_FOG_WITH ){
			weatherSysFogParamFadeInit( fogParam, 
					Fog,
					fog_slope, 
					fog_offs,
					color, timing * FOG_DEPTH_COUNT_MAX );
					// ↑ｶｳﾝﾀ　フォグはtimingに１回デプス値を変更する
					// のでそれにあわせてこのカウント値にする
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォグフェードメイン
 *
 *	@param	fogParam	フォグパラメータフェードデータ
 *	@param	fogData		フォグテーブルフェードデータ
 *
 *	@retval	1	終了
 *	@retval	0	途中
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFadeInMainPack( WEATHER_SYS_CHG_FOG_DATA* fogParam, WEATHER_SYS_FOG_FADE* fogData, u32 fog_use_flg )
{
	BOOL result_bool;
	int result_int = 1;
	
	if( fog_use_flg != WEATHER_FOG_NONE ){

		if( fog_use_flg == WEATEHR_FOG_NEW ){
			result_int = weatherSysFogFade(fogData);	
		}else if( fog_use_flg == WEATHER_FOG_WITH ){
			result_bool = weatherSysFogParamFadeMain( fogParam );
			if( result_bool == FALSE ){
				result_int = 0;
			}
		}
	}
	return result_int;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォグの値設定
 *
 *	@param	Fog			フォグデータ
 *	@param	fog_slope	フォグスロープ
 *	@param	fog_offs	フォグオフセット
 *	@param	color		カラー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogParamSet( FOG_DATA_PTR Fog, int fog_slope, int fog_offs, GXRgb color )
{
	SetFogData(Fog, FOG_SYS_ALL, TRUE, GX_FOGBLEND_COLOR_ALPHA, fog_slope, fog_offs);		// フォグデータ
	SetFogColor(Fog, FOG_SYS_ALL, color, 31);	// フォグカラー
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォグ　パラメータ値フェード
 *
 *	@param	data		格納先ワーク
 *	@param	fog			フォグ値バッファ
 *	@param	fogslope	変更後のフォグの係り具合
 *	@param	offs		オフセット値
 *	@param	color		カラー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogParamFadeInit( WEATHER_SYS_CHG_FOG_DATA* data, FOG_DATA_PTR fog, int fogslope, int offs, GXRgb color, int count_max )
{
	int fog_slope;
	int fog_offs;
	GXRgb fog_color;

	// 現在のパラメータ取得
	fog_slope = GetFogSlope( fog );
	fog_offs = GetFogOffset( fog );
	fog_color = GetFogColor( fog );
	
	data->Fog = fog;

	WeatherMoveReq( &data->fog_depth, fog_offs, offs, count_max );
	WeatherMoveReq( &data->r, WH_COLOR_R(fog_color), WH_COLOR_R(color), count_max );
	WeatherMoveReq( &data->g, WH_COLOR_G(fog_color), WH_COLOR_G(color), count_max );
	WeatherMoveReq( &data->b, WH_COLOR_B(fog_color), WH_COLOR_B(color), count_max );
	WeatherMoveReq( &data->slope, fog_slope, fogslope, count_max );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理メイン
 *
 *	@param	data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL weatherSysFogParamFadeMain( WEATHER_SYS_CHG_FOG_DATA* data )
{
	BOOL check;
	
	// 計算
	check = WeatherMoveMain( &data->fog_depth );
	WeatherMoveMain( &data->r );
	WeatherMoveMain( &data->g );
	WeatherMoveMain( &data->b );
	WeatherMoveMain( &data->slope );

	// 値設定
	weatherSysFogParamSet( data->Fog,
		data->slope.x, data->fog_depth.x, GX_RGB(data->r.x,data->g.x,data->b.x)	);
	
	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォグテーブル初期化
 *
 *	@param	data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogTblInit( WEATHER_SYS_FOG_FADE* data )
{
	int i;
	for(i=0;i<32;i++){						// フォグテーブル
		data->fog_tbl[i] = 0;
	}
	SetFogTbl(data->Fog, data->fog_tbl);				// フォグテーブル
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォグフェードテーブルパラメータ設定
 *
 *	@param	data			データ格納先
 *	@param	timing			変更タイミング
 *	@param	fade_inout		フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void weatherSysFogFadeInit( WEATHER_SYS_FOG_FADE* data, int timing, BOOL fade_inout )
{
	data->fogDepth		= FOG_DEPTH_COUNT_MAX;
	data->fogCount		= 0;
	data->FOG_CHG_TMG	= timing;

	if( fade_inout == TRUE ){
		data->FOG_TBL_SUM	= FOG_TBL_SUB_FADEIN;
	}else{
		data->FOG_TBL_SUM	= FOG_TBL_SUB_FADEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	フォグフェード
 *
 *@param	data		オブジェクトのフェードデータ
 *
 *@retval	0			フェード未終了
 *@retval	1			フェード終了
 *
 * 各カウンタの初期化を事前にしておく必要があります。
 * カウンタはポインタ参照なので、書き換えないようにしておく必要があります。
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFade(WEATHER_SYS_FOG_FADE* data)
{
	int ret;		// 戻り値
	
	ret = weatherSysFogFadeNoReflect( data );

	// fogCountが0＝テーブルデータを変更したタイミング
	// なので反映
	if( data->fogCount == 0 ){
		SetFogTbl(data->Fog, data->fog_tbl);	// フォグテーブルセット
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フェードイン後に作成されているフォグデータを作成する
 *
 *	@param	data		フォグフェードデータ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void weatherSysFogSet(WEATHER_SYS_FOG_FADE* data)
{
	int i;
	int result;
	
	data->fogDepth		= 1;
	data->fogCount		= 0;
	data->FOG_CHG_TMG	= 0;
	data->FOG_TBL_SUM	= 1;

	// テーブル計算
	calcWeatherFogTbl( data );
/*	do{
		result = weatherSysFogFadeNoReflect( data );	// フォグテーブル作成
	}while( result != TRUE );//*/
	SetFogTbl(data->Fog, data->fog_tbl);	// フォグテーブルセット
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	フォグフェード		フォグデータの反映を行わないバージョン
 *
 *@param	data		オブジェクトのフェードデータ
 *
 *@retval	0			フェード未終了
 *@retval	1			フェード終了
 *
 * 各カウンタの初期化を事前にしておく必要があります。
 * カウンタはポインタ参照なので、書き換えないようにしておく必要があります。
 * 
 * 
 */
//-----------------------------------------------------------------------------
static int weatherSysFogFadeNoReflect(WEATHER_SYS_FOG_FADE* data)
{
	int ret = 0;		// 戻り値
	
	if(data->FOG_TBL_SUM == 0){
		ret = 1;
	}else{
	
		// 終了しているかチェック
		if(data->fogDepth <= 0){
			ret = 1;
		}else{
			
			data->fogCount++;
			if(data->fogCount >= data->FOG_CHG_TMG){
				data->fogCount = 0;

				// テーブル計算
				calcWeatherFogTbl( data );
				
				data->fogDepth--;
				if(data->fogDepth <= 0){		// 終了チェック
					ret = 1;
				}
//				SetFogTbl(data->Fog, data->fog_tbl);	// フォグテーブルセット
			}
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フォグテーブル作成計算
 *
 *	@param	data	フォグフェードデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void calcWeatherFogTbl( WEATHER_SYS_FOG_FADE* data )
{
	int i;
	int fog_num;		// フォグテーブル計算用
	int fog_calc;

	if( data->FOG_TBL_SUM < 0 ){
		fog_calc = FOG_DEPTH_COUNT_MAX - data->fogDepth;
	}else{
		fog_calc = data->fogDepth;
	}

	// フォグを動かす		(y=(x*x)/(4*x))
	fog_num = fog_calc/4;
	for(i=31;i>fog_num;i--){
		data->fog_tbl[i] = ((i-fog_num)*4);

		// 127以上にしない
		if( data->fog_tbl[i] > 127 ){
			data->fog_tbl[i] = 127;
		}
	}
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGαフェード計算関数
 *
 *	@param	now_alpha		現在のα値
 *	@param	end_alpha		フェード終了α値
 *	@param	add_alpha		足すα値
 *	@param	timing_count	タイミングカウンタ
 *	@param	add_timing		足すタイミング
 *
 *	@retval	TRUE		正常
 *	@retval	FALSE		フェード終了
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL weatherBGFade( s32* now_alpha, const int end_alpha, const int add_alpha, s32* timing_count, const int add_timing )
{
	BOOL ret = TRUE;
	
	// BG
	(*timing_count)++;
	if((*timing_count) > add_timing){
		(*timing_count) = 0;

		if( add_alpha > 0 ){
			if(((*now_alpha) + add_alpha) <= end_alpha){
				(*now_alpha) += add_alpha;
			}else{
				(*now_alpha) = end_alpha;
				ret = FALSE;
			}
		}else{
			if(((*now_alpha) + add_alpha) >= end_alpha){
				(*now_alpha) += add_alpha;
			}else{
				(*now_alpha) = end_alpha;
				ret = FALSE;
			}
		}
	}

	return ret;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	天気のオブジェクトを分布させる
 *
 *	@param	pWork			ワーク
 *	@param	add_func		オブジェクト登録関数ポインタ
 *	@param	num				登録数
 *	@param	dust_div_num	何オブジェクトごとに動作数を変更するか
 *	@param	dust_div_move	各オブジェクトの動作数をどのくらい離すか
 *	@param	move_func		動作関数
 *
 *	@return	none
 *
 * num分のオブジェクトを登録し、0番目のオブジェクトからdust_div_move回数分
 * 多くオブジェクトを動作させる
 * 0番目のオブジェクト　0
 * 1番目のオブジェクト	dust_div_move
 * 2番目のオブジェクト	dust_div_move * 2
 * ....
 *
 */
//-----------------------------------------------------------------------------
static void weatherDustObj( WEATHER_SYS_WORK* pWork, OBJADD_FUNC add_func, int num, int dust_div_num, int dust_div_move, objFunc move_func )

{
	int i, j;
	int move_num;
	WAETHER_OBJ_DATA* obj;
	WAETHER_OBJ_DATA* obj_next;
	
	// オブジェクト登録
	add_func( pWork, num );


	// オブジェクトを進める
	move_num = 0;
	obj = pWork->Dummy.pNext;
	obj_next = obj->pNext;
	for( i=0; i<num; i++ ){	
		
		// 登録失敗しているときはnum分のオブジェクトが登録されていない
		if( obj == &pWork->Dummy ){
			break;
		}
		
		for( j=0; j<move_num; j++ ){
			move_func( obj );

			// 破棄されたら終わり
			if( obj->work == NULL ){
				break;
			}
		}

		// 次へ
		obj = obj_next;
		obj_next = obj->pNext;	// move_func内でオブジェクトが破棄されることもあるため、次のオブジェクトポインタを保存しておく

		// 動作数変更計算
		if( i >= dust_div_num ){
			if( (i % dust_div_num) == 0 ){
				move_num += dust_div_move;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	カラのオブジェクトデータ配列要素を取得
 *
 *	@param	pWork	天気システムワーク
 *
 *	@return	WAETHER_OBJ_DATA	オブジェデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static WAETHER_OBJ_DATA* getCleanObjData( WEATHER_SYS_WORK* pWork )
{
	int i;

	for( i=0; i<WEATEHR_OBJDATA_MAX; i++ ){

		if( pWork->ObjArray[ i ].pWSysCont == NULL ){	//(NULLチェックはどのメンバでもOK)
			return &pWork->ObjArray[ i ];
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
//	プライベート関数
//		お天気管理タスク郡	
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ダミー天気
 *	@param	tcb
 *	@param	work
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherDummy(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;

	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		sys_work->Sequence = WEATHER_SEQ_DEST;
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雨管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherRain(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL*	sys_w;	// システムワーク
	int		result;		// 関数結果
	int	fog_result;	// フォグ結果

	// ワークポインタセット
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		// 作業領域の初期化
		// オブジェクトフェード用
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_RAIN_ADD_START,
			WEATHER_RAIN_TIMING_MAX,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			-WEATHER_RAIN_TIMING_ADD,
			WEATHER_RAIN_ADD_TIMING,
			WEATHER_RAIN_ADD,
			addWeatherRain );

		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_RAIN_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_RAIN_FOG_TIMING,
				sys_work->fog_use );

		sys_w->work[0] = WEATHER_RAIN_FOG_START;	// 同じくフォグ用

		// 音
		WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_AME );	
		
		// アルファブレンド
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 4,16);
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
	
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		// 作業領域の初期化
		// オブジェクトフェード用
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			WEATHER_RAIN_ADD_MAIN,
			WEATHER_RAIN_TIMING_MIN,
			-WEATHER_RAIN_TIMING_ADD,
			WEATHER_RAIN_ADD_TIMING,
			WEATHER_RAIN_ADD,
			addWeatherRain );

		// フォグデータ設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_RAIN_FOG_OFS, GX_RGB(26,26,26) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// アルファブレンド
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 4,16);

		// 雨オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherRain, WEATHER_RAIN_NOFADE_OBJ_START_NUM, WEATHER_RAIN_NOFADE_OBJ_START_DUST_NUM, WEATHER_RAIN_NOFADE_OBJ_START_DUST_MOVE, objWeatherRain );

		// 音
		WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_AME );	
		
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 雨登録
			addWeatherRain(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}

		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_RAIN_TIMING_MAX,
					WEATHER_RAIN_TIMING_ADD,
					-WEATHER_RAIN_ADD );
			
			// フォグ
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_RAIN_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_RAIN_FOG_START_END;	// 同じくフォグ用

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了

			// 音
			WeatherLoopSndStop( sys_work );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
	
		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;


	default:
		break;
	}

	// 初期化、破棄以外のときはオブジェクトを動作させる
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherRain);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雨オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherRain(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int	err;	// 補正値
	s32* obj_w;	// オブジェクトワーク
	int frame;	// 描画フレーム
	VecFx32	mat;	// 設定座標
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}
		obj_w = (s32*)add_obj->work;		// オブジェワーク作成
		
		// 領域を初期化
		obj_w[0] = 0;			// カウンタ
		frame = gf_mtRand()%3;	// 雨の種類
		CLACT_AnmFrameSet(add_obj->clact_w, frame);

		err = (gf_mtRand() % WEATHER_RAIN_SPEED_ERR);
		obj_w[2] = WEATHER_RAIN_SPEED_Y * (frame+1) + err;
		if(frame == 2){		// 一番前の雨はスピードを１段階上げる
			obj_w[2] += WEATHER_RAIN_SPEED_Y;
		}
		
		err /= WEATHER_RAIN_SPEED_X;
		obj_w[4] = WEATHER_RAIN_SPEED_X * (frame+1) + err;
		if(frame == 2){		// 一番前の雨はスピードを１段階上げる
			obj_w[4] += WEATHER_RAIN_SPEED_X;
		}
		obj_w[3] = 0;			// 破棄アニメフラグ
		
		// 破棄タイミング	全部共通の範囲の値
		obj_w[1] = WEATHER_RAIN_END_MIN  + (gf_mtRand() % WEATHER_RAIN_END_MAX);
		
		// 座標を設定
		mat.x = ( WEATHER_RAIN_START_X_BASE + (frame * WEATHER_RAIN_MUL_X) + (gf_mtRand() % WEATHER_RAIN_START_X_MAX) ) << FX32_SHIFT;
		mat.y = WEATHER_RAIN_START_Y << FX32_SHIFT;
		mat.z = 0;	
		setClactMatrix(add_obj->clact_w, &mat);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雨オブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherRain(WAETHER_OBJ_DATA* work)
{
	int i;
	WAETHER_OBJ_DATA* p_obj = work;
	s32*	obj_w = (s32*)p_obj->work;
	VecFx32 mat;	// 座標

	mat = getObjMat(p_obj);
	
	// 動作フラグをチェック
	switch(obj_w[3]){
	case 0:		// 動作
		// 動きが早いため間を補正する　方法として１フレームに２回動かし、１．５の描画を行う
		for(i=0;i<2;i++){
			// 動かす
			mat.x += obj_w[4] << FX32_SHIFT;
			mat.y += obj_w[2] << FX32_SHIFT;
		
			// 破棄するかチェック
			if(obj_w[0]++ > obj_w[1]){
				// アニメーションさせるかチェック
				if((gf_mtRand() % 10) < 7){		// 7/10は破棄
					// 破棄
					obj_w[3] = 2;
				}else{
				
					// 破棄アニメ
					obj_w[3] = 1;		
					obj_w[0] = 4;			// 破棄アニメカウンタ
					CLACT_AnmFrameSet(p_obj->clact_w, 3);
				}
			}
		}
		// 座標設定
		setClactMatrix(p_obj->clact_w, &mat);

		break;
	case 1:		// 破棄アニメ
		if(obj_w[0]-- <= 0){
			obj_w[3] = 2;		// 破棄
		}
		break;

	case 2:		// 破棄
		destObj(p_obj);
		break;
	}		
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雪管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnow(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	int		tmp_y;		// y座標保存用
	WEATHER_SYSW_NORMAL*	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	

	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,
			WEATHER_SNOW_TIMING_MAX,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			-WEATHER_SNOW_TIMING_ADD,
			WEATHER_SNOW_ADD_TIMING,
			WEATHER_SNOW_ADD,
			addWeatherSnow );
		
		sys_w->work[1] = 0;							// 雪が１回下まで行ったかのフラグ
		
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_SNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_FOG_START;	// 同じくフォグ用
	
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 8, 16);
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			WEATHER_SNOW_MAIN,
			WEATHER_SNOW_TIMING_MIN,
			-WEATHER_SNOW_TIMING_ADD,
			WEATHER_SNOW_ADD_TIMING,
			WEATHER_SNOW_ADD,
			addWeatherSnow );
		
		sys_w->work[1] = 0;							// 雪が１回下まで行ったかのフラグ
		sys_w->work[2] = 0;							// 自動破棄フラグ
		
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_FOG_OFS, GX_RGB(26,26,26) );

			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_OBJ, GX_BLEND_PLANEMASK_BG0, 8, 16);
		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSnow, WEATHER_SNOW_NOFADE_OBJ_START_NUM, WEATHER_SNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnow );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 雪登録
			addWeatherSnow(sys_work, sys_w->objFade.objAddNum);
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_TIMING_MAX,
					WEATHER_SNOW_TIMING_ADD,
					-1 );
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワークが０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){

				// オブジェ破棄フラグON
				sys_w->work[2] = 1;
				
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){//*/
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnow);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	雪オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雪用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnow(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	int rand;	// 乱数
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	WEATHER_SYSW_NORMAL*	sys_w;	// システムワーク
	s32*	obj_w;		// オブジェクトワーク
	int	frame;		// フレーム
	VecFx32	mat;	// 座標

	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	if(sys_w->work[1] == 1){
		num *= 2;
	}
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*10);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}
		obj_w = (s32*)add_obj->work;
		
		frame = gf_mtRand() % WEATHER_SNOW_OBJ_NUM;
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		obj_w[4] = 10;	// 横の動く方向変更カウンタ	
		obj_w[5] = 0;
		obj_w[6] = 0;	// 輝きカウンタ
		obj_w[8] = 0;							// シーケンス
		
		rand = gf_mtRand();

		obj_w[9] = WEATHER_SNOW_OBJ_AUTODEST_TIMING_MIN + (rand % WEATHER_SNOW_OBJ_AUTODEST_TIMING_MAX);		// 自滅ｶｳﾝﾀ
	
		// スピード
		if((rand % 2) == 0){
			obj_w[1] = 1;
		}else{
			obj_w[1] = -1;
		}
		obj_w[2] = WEATHER_SNOW_ADD_TMG_X_BASE + (gf_mtRand() % WEATHER_SNOW_ADD_TMG_X_RAN);
		obj_w[3] = WEATHER_SNOW_ADD_TMG_Y_BASE + (gf_mtRand() % WEATHER_SNOW_ADD_TMG_Y_RAN);

		obj_w[0] = (s32)&sys_w->work[1];		// 下まで行ったらフラグを立てるポインタを保存
		obj_w[7] = (s32)&sys_w->work[2];		// 破棄フラグポインタON
		
		// 座標を設定
		mat.x = ( WEATHER_SNOW_START_X_BASE + (gf_mtRand() % WEATHER_SNOW_START_X_MAX) ) << FX32_SHIFT;
		
		if((sys_w->work[1] == 1) &&
			(i >= (num /2)) ){	// 半分出す
			mat.y = ( -40 - (gf_mtRand() % 20)) << FX32_SHIFT;
		}else{
			mat.y = ( -8 - (gf_mtRand() % 20) ) <<FX32_SHIFT;
		}
		setClactMatrix(add_obj->clact_w, &mat);
	}
}

static void objWeatherSnowObjNormal( WAETHER_OBJ_DATA* p_obj, s32* obj_w )
{
	VecFx32 mat;	// 座標
	s32*	p_flg;	// 雪が画面外へ行ったかのフラグ

	mat = getObjMat(p_obj);

	// 動かす
	// X座標移動
	if(((obj_w[5] & 0xffff) >= obj_w[2])){
		mat.x	+= obj_w[1] << FX32_SHIFT;
		obj_w[4]++;
		obj_w[5] &= 0xffff0000;
		// スピードチェンジャー
		if(obj_w[4] < 10){
			obj_w[2]--;
		}else{
			obj_w[2]++;
		}
		if(obj_w[4] >= 20){	// これで左右にゆらゆら
			obj_w[4] = 0;
			obj_w[1]*=-1;
		}//*/
	}
	// Y座標移動
	if(((obj_w[5] >> 16) >= obj_w[3])){
		mat.y += FX32_ONE;
		obj_w[5] &= 0x0000ffff;
	} 

	// 座標設定
	setClactMatrix( p_obj->clact_w, &mat );

	mat.x >>= FX32_SHIFT;
	mat.y >>= FX32_SHIFT;
	
	// カウント設定
	obj_w[6] = (obj_w[6] + 1) % 100;
	obj_w[5]++;
	obj_w[5]+=0x10000;

	// 破棄ゾーンにいたら破棄  
	if(((mat.y < -284) && (mat.y > -296)) ||
		((mat.y > 212) && (mat.y < 232))){
		p_flg = (s32*)(obj_w[0]);
		*p_flg = 1;
		destObj(p_obj);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雪動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnow(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32*	obj_w = (s32*)p_obj->work;
	s32* p_flg = (s32*)obj_w[7];	// 中身はポインタ

	switch( obj_w[8] ){
	case 0:
		// もし　破棄フラグが立っていたら自動破棄動さへ
		if( *p_flg == 1 ){
			obj_w[8] ++;
		}
		break;

	case 1:	// ｶｳﾝﾀが0になったら破棄
		obj_w[9] --;
		if( obj_w[9] < 0 ){
			destObj(p_obj);
			return ;
		}
		break;
	}
	
	// 通常動さ
	objWeatherSnowObjNormal( p_obj, obj_w );
}


//-------------------------------------
//	吹雪
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	吹雪管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowStorm(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL*	sys_w;		// システムワーク領域
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果	
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;
	

	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,
			WEATHER_SSNOW_TIMING_MAX,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		// フォグの設定		
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SSNOW_FOG_OFS, 
				GX_RGB(24,24,24),
				WEATHER_SSNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SSNOW_FOG_START;	// 同じくフォグ用
	
		
		sys_w->work[1] = 0;					// オブジェ数カウンタ
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行	
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワークが０になったらフォグを動かす
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}	
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_MAIN,  
			WEATHER_SSNOW_TIMING_MIN,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		// フォグの設定		
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SSNOW_FOG_OFS, GX_RGB(24,24,24) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		sys_w->work[1] = 0;					// オブジェ数カウンタ

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSnowStorm, WEATHER_SSNOW_NOFADE_OBJ_START_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowStorm );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 吹雪登録
			addWeatherSnowStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SSNOW_TIMING_MAX,
					WEATHER_SSNOW_TIMING_ADD,
					WEATHER_SSNOW_ADD_END );
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SSNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SSNOW_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワークが０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	吹雪オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowStorm(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int tbl_num;
	WEATHER_SYSW_NORMAL* sys_w;		// システムワーク
	s32* obj_w;			// オブジェクトワーク
	int WEATHER_SSNOW_ADD_SP_TMG[WEATHER_SSNOW_ADD_SP_TMG_NUM] = {16,32,16,10};
	int WEATHER_SSNOW_SPEED_Y[WEATHER_SSNOW_ADD_SP_TMG_NUM] = {2,2,2,2};	// たてに進むスピード
	int frame;	// フレーム数
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	

	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;

		// 風の値を求める
		sys_w->work[1]++;
		if(sys_w->work[1] >= (WEATHER_SSNOW_ADD_SP_TMG_TMG * WEATHER_SSNOW_ADD_SP_TMG_NUM)){
			sys_w->work[1] = 0;
		}
		tbl_num = (sys_w->work[1] / WEATHER_SSNOW_ADD_SP_TMG_TMG);
		obj_w[5] = WEATHER_SSNOW_ADD_SP_TMG[ tbl_num ];
		
	
		
		// 領域を初期化
		obj_w[0] = 0;			// カウンタ
		obj_w[1] = WEATHER_SSNOW_END_MIN + (gf_mtRand() % (WEATHER_SSNOW_END_MAX - WEATHER_SSNOW_END_MIN));	// 終了カウンタ
		frame = (obj_w[1] - WEATHER_SSNOW_END_MIN) / WEATHER_SSNOW_END_DIV;	// 吹雪の種類
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		obj_w[4] = WEATHER_SSNOW_SPEED_X * (frame+1);
		obj_w[2] = WEATHER_SSNOW_SPEED_Y[tbl_num] * (frame+1);	// たてスピード
		obj_w[3] = 0;			// 破棄アニメフラグ
		
		// 座標を設定
		{
			VecFx32	mat = getObjMat( add_obj );
			mat.x = WEATHER_SSNOW_START_X_BASE + (frame * WEATHER_SSNOW_MUL_X) + (gf_mtRand() % WEATHER_SSNOW_START_X_MAX);
			mat.y = WEATHER_SSNOW_START_Y;
			mat.z = 0;
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			
			setClactMatrix(add_obj->clact_w, &mat);	
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	吹雪オブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowStorm(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// 動作フラグをチェック
	switch(obj_w[3]){
	case 0:		// 動作

		// 動かす
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		// 破棄するかチェック
		if(obj_w[0]++ > obj_w[1]){
			// 破棄
			obj_w[3] = 1;
		}
		// カウンタで動かす値を変化
		if((obj_w[0] % obj_w[5]) == 0){
			obj_w[4]--;
			
			
			if(obj_w[2] > 1){
				obj_w[2]--;
			}//*/
		}

		setClactMatrix(p_obj->clact_w, &mat);
	
		break;
	case 1:		// 破棄
		destObj(p_obj);
		break;
	}		
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	BG使用吹雪管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowStormBG(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL* sys_w;			// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	
		
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 0, 16);
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,
			WEATHER_SSNOW_TIMING_MAX,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );

		

		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT, 
				GX_RGB(24,24,24),
				WEATHER_SSNOW_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SSNOW_FOG_START;	// 同じくフォグ用
	
		
		sys_w->work[1] = 0;					// オブジェ数カウンタ
		sys_w->work[2] = 0;					// BGカウンタ
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
			if(sys_w->work[0] == 0){
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 1, 16);
			}
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 2, 16);
			}
		}
		break;

	case WEATHER_SEQ_NO_FADE:
//		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 2, 16);
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_MAIN,  
			WEATHER_SSNOW_TIMING_MIN,
			WEATHER_SSNOW_ADD_MAIN,
			WEATHER_SSNOW_TIMING_MIN,
			-WEATHER_SSNOW_TIMING_ADD,
			WEATHER_SSNOW_ADD_TIMING,
			WEATHER_SSNOW_ADD,
			addWeatherSnowStorm );
		

		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT, GX_RGB(24,24,24) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
	
		
		sys_w->work[1] = 0;					// オブジェ数カウンタ
		sys_w->work[2] = 0;					// BGカウンタ

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSnowStorm, WEATHER_SSNOW_NOFADE_OBJ_START_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_NUM, WEATHER_SSNOW_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowStorm );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
		
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 吹雪登録
			addWeatherSnowStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SSNOW_TIMING_MAX,
					WEATHER_SSNOW_TIMING_ADD,
					WEATHER_SSNOW_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SSNOW_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SSNOW_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
			if(sys_w->work[0] == 0){
//				G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 1, 16);
			}
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
//					G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG0, 0, 16);
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);

		// BG面を斜め上に動かす
		sys_w->work[2] = (sys_w->work[2] + 6) % 256;
		G2_SetBG2Offset(sys_w->work[2],-sys_w->work[2]);

	}
}



//---------------------------------------------------------
//		霧
//=========================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	霧管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog00(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_STSW_FOGFADE* sys_w;	// システムワーク
	int		fog_result;	// フォグ結果
	sys_w = (WEATHER_STSW_FOGFADE*)sys_work->work;	// ワークポインタセット
	

	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG0_OFS, 
				GX_RGB(26,26,26),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_FOG_START;	// 同じくフォグ用
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}	
		break;
	case WEATHER_SEQ_NO_FADE:
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG0_OFS, GX_RGB(26,26,26) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1)){		// フェードリザルトが完了ならば終了へ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	霧管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog01(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_STSW_FOGFADE* sys_w;	// システムワーク
	int		fog_result;	// フォグ結果
	sys_w = (WEATHER_STSW_FOGFADE*)sys_work->work;	// ワークポインタセット
	
		
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG1_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG1_OFS, 
				GX_RGB(26,26,26),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_FOG_START;	// 同じくフォグ用
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG1_SLOPE, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_FOG1_OFS, GX_RGB(26,26,26) );

			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);	
			}else{
				fog_result = 1;
			}
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1)){		// フェードリザルトが完了ならば終了へ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	霧管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherFog02(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// システムワーク
	int		fog_result;	// フォグ結果
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG2_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT+WEATHER_FOG2_OFS, 
				GX_RGB(31,31,31),
				WEATHER_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_FOG2_FADE_END_ALPHA, WEATHER_FOG2_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		G2_SetBG2Priority(3);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならばメインへ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG2_SLOPE, WEATHER_FOG_DEPTH_DEFAULT+WEATHER_FOG2_OFS, GX_RGB(31,31,31) );

			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_FOG2_FADE_END_ALPHA, 16 - WEATHER_FOG2_FADE_END_ALPHA);
		G2_SetBG2Priority(3);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_FOG2_FADE_END_ALPHA, 0, WEATHER_FOG2_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならば終了へ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	砂嵐管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherStorm(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL* sys_w;			// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
		

	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_START,	// obj登録数
			WEATHER_STORM_TIMING_MAX,	// 登録タイミング
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
		
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_STORM_FOG_SLOPE, 
				WEATHER_STORM_FOG_OFS, 
				GX_RGB(26,20,5),
				WEATHER_STORM_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_STORM_FOG_START;	// 同じくフォグ用
		sys_w->work[1] = 0;			// オブジェクト追加数カウンタ
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_MAIN,	// obj登録数
			WEATHER_STORM_TIMING_MIN,	// 登録タイミング
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
		
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_STORM_FOG_SLOPE, WEATHER_STORM_FOG_OFS, GX_RGB(26,20,5) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		sys_w->work[1] = 0;			// オブジェクト追加数カウンタ

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherStorm, WEATHER_STORM_NOFADE_OBJ_START_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE, objWeatherStorm );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 砂嵐登録
			addWeatherStorm(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_STORM_TIMING_MAX,
					WEATHER_STORM_TIMING_ADD,
					WEATHER_STORM_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STORM_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_STORM_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherStorm);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	砂嵐オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherStorm(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int	wind;	// 風向き
	int	rand;
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	s32* obj_w;	// オブジェワーク
	int frame;	// フレーム数
	
	static const int	STORM_SPEED_X_TBL[WEATHER_STORM_SPEED_NUM] = {-3,-5,-5,-4,-5,-6,-10,-6};
	static const int	STORM_SPEED_Y_TBL[WEATHER_STORM_SPEED_NUM] = { 2, 2, 2, 4, 4, 2, 2, 2};
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;

	
	
	// 風変更カウント
	sys_w->work[1] = (sys_w->work[1]+1) % (WEATHER_STORM_SPEED_CNG_NUM*WEATHER_STORM_SPEED_NUM);
		
	// 風向きを求める
	wind = sys_w->work[1] / WEATHER_STORM_SPEED_CNG_NUM;
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		// オブジェワーク
		obj_w = add_obj->work;
		
		
		// 領域を初期化
		obj_w[0] = 0;			// カウンタ
		obj_w[1] = WEATHER_STORM_END_MIN + (gf_mtRand() % (WEATHER_STORM_END_MAX - WEATHER_STORM_END_MIN));	// 終了カウンタ
		
		frame = 3 - ((obj_w[1] - WEATHER_STORM_END_MIN) / WEATHER_STORM_END_DIV);	// 吹雪の種類
		
		obj_w[2] = (STORM_SPEED_Y_TBL[wind]) * (frame+1);
		obj_w[4] = (STORM_SPEED_X_TBL[wind]) * (frame+1);
		obj_w[3] = 0;			// 破棄アニメフラグ
		obj_w[5] = STORM_SPEED_X_TBL[wind];	// スピードを上げていく値

		// ほんとにたまにサボテン
		rand = gf_mtRand() % 1000;
		if(rand == 777){
			frame = 4;
			obj_w[2] += obj_w[2] / 2;
		}
		
		CLACT_AnmFrameSet(add_obj->clact_w, frame);
		
		{
			VecFx32 mat;
			mat = getObjMat( add_obj );
			mat.x = WEATHER_STORM_START_X1 + (gf_mtRand() % WEATHER_STORM_START_X1_RAN);
			mat.x <<= FX32_SHIFT;
			mat.y = WEATHER_STORM_START_Y1_MIN + (gf_mtRand() % WEATHER_STORM_START_Y1_MAX);
			mat.y <<= FX32_SHIFT;
			setClactMatrix(add_obj->clact_w, &mat);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	砂嵐オブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherStorm(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;		// オブジェワーク
	VecFx32 mat = getObjMat( p_obj );
	
	// 動作フラグをチェック
	switch(obj_w[3]){
	case 0:		// 動作

		// 動かす
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		if((obj_w[0] % WEATHER_STORM_SPEED_ADD_TMG) == 0){
			obj_w[4] += obj_w[5];
		}

		// 破棄するかチェック
		if(obj_w[0]++ > obj_w[1]){
			// 破棄
			obj_w[3] = 1;
		}

		setClactMatrix(p_obj->clact_w, &mat);
			
		break;
	case 1:		// 破棄
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	砂嵐管理タスク		BG使用
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherStormBG(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	int		wind;		// 風テーブルの値
	int		scl_x, scl_y;// スクロール座標
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	static const int STORM_SPEED_X_TBL[WEATHER_STORM_SPEED_NUM] = {-3,-5,-5,-3,-5,-6,-10,-6};
	static const int STORM_SPEED_Y_TBL[WEATHER_STORM_SPEED_NUM] = { 2, 2, 2, 4, 4, 2, 2, 2};	
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット


	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		

		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_START,	// obj登録数
			WEATHER_STORM_TIMING_MAX,	// 登録タイミング
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
	
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_STORM_FOG_SLOPE, 
				WEATHER_STORM_FOG_OFS, 
				GX_RGB(26,20,5),
				WEATHER_STORM_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_STORM_FOG_START;	// 同じくフォグ用
		sys_w->work[1] = 0;		// オブジェクト追加数カウンタ
		sys_w->work[2] = 0;		// BGカウンタ
		sys_w->work[3] = 0;		// 風のスピード
		

		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			
			// fog
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;

				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		

		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_STORM_ADD_MAIN,	// obj登録数
			WEATHER_STORM_TIMING_MIN,	// 登録タイミング
			WEATHER_STORM_ADD_MAIN,
			WEATHER_STORM_TIMING_MIN,
			-WEATHER_STORM_TIMING_ADD,
			WEATHER_STORM_ADD_TIMING,
			WEATHER_STORM_ADD,
			addWeatherStorm );
	
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_STORM_FOG_SLOPE, WEATHER_STORM_FOG_OFS, GX_RGB(26,20,5) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		
		sys_w->work[1] = 0;		// オブジェクト追加数カウンタ
		sys_w->work[2] = 0;		// BGカウンタ
		sys_w->work[3] = 0;		// 風のスピード
		
		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherStorm, WEATHER_STORM_NOFADE_OBJ_START_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_NUM, WEATHER_STORM_NOFADE_OBJ_START_DUST_MOVE, objWeatherStorm );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 風テーブルを取得
			wind = sys_w->work[1] / WEATHER_STORM_SPEED_CNG_NUM;
			// 風を設定する
			sys_w->work[3] = STORM_SPEED_X_TBL[wind];
			
			// α値とオブジェの出す量を風の強さで変える
			if(sys_w->work[3] <= -WEATHER_STORM_STRONG_CHG){
				// 砂嵐登録
				addWeatherStorm(sys_work, sys_w->objFade.objAddNum*2);
			
			}else{
				// 砂嵐登録
				addWeatherStorm(sys_work, sys_w->objFade.objAddNum);
			}
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_STORM_TIMING_MAX,
					WEATHER_STORM_TIMING_ADD,
					WEATHER_STORM_ADD_END );

			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STORM_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_STORM_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherStorm);
		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);

		// BG面を斜め上に動かす
		sys_w->work[2] = (sys_w->work[2] + 6) % 256;
		G2_SetBG2Offset(sys_w->work[2]*2 - scl_x,-sys_w->work[2] + scl_y);
	}
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	北海道雪管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowSML(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	int		wind;		// 風
	int		scl_x, scl_y;// スクロール座標
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	
		

	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SSNOW_ADD_START,	// obj登録数
			WEATHER_SSNOW_TIMING_MAX,	// 登録タイミング
			WEATHER_SNOW_S_ADD_MAIN,
			WEATHER_SNOW_S_TIMING_MIN,
			-WEATHER_SNOW_S_TIMING_ADD,
			WEATHER_SNOW_S_ADD_TIMING,
			WEATHER_SNOW_S_ADD,
			addWeatherSnowSML );
		
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_S_FOG_OFS, 
				GX_RGB(24,24,24),
				WEATHER_SNOW_S_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_S_FOG_START;	// 同じくフォグ用
		
		sys_w->work[1] = 0;				// オブジェ数カウンタ
		sys_w->work[2] = 0;				// BGカウンタ

		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行	
	
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{

			// fog
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_S_ADD_MAIN,	// obj登録数
			WEATHER_SNOW_S_TIMING_MIN,	// 登録タイミング
			WEATHER_SNOW_S_ADD_MAIN,
			WEATHER_SNOW_S_TIMING_MIN,
			-WEATHER_SNOW_S_TIMING_ADD,
			WEATHER_SNOW_S_ADD_TIMING,
			WEATHER_SNOW_S_ADD,
			addWeatherSnowSML );
		
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_S_FOG_OFS, GX_RGB(24,24,24) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		sys_w->work[1] = 0;				// オブジェ数カウンタ
		sys_w->work[2] = 0;				// BGカウンタ


		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSnowSML, WEATHER_SNOW_S_NOFADE_OBJ_START_NUM, WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_S_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowSML );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		
		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			wind = sys_w->work[1] / WEATHER_SNOW_S_ADD_SP_CHG_TMG;
			wind = WEATHER_SSNOW_SPEED_X_SML[wind];
			
			if(wind <= -WEATHER_SNOW_S_SP_UP){
				// 吹雪登録
				addWeatherSnowSML(sys_work, sys_w->objFade.objAddNum*2);
			}else{
				// 吹雪登録
				addWeatherSnowSML(sys_work, sys_w->objFade.objAddNum);
			}
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_S_TIMING_MAX,
					WEATHER_SNOW_S_TIMING_ADD,
					WEATHER_SNOW_S_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_S_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_S_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
			
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理する雪が全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}		
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowSML);
//		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);

		// BG面を斜め上に動かす
		sys_w->work[2] = (sys_w->work[2] + 12) % 256;
		G2_SetBG2Offset(sys_w->work[2]*2,-sys_w->work[2]);

	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	北海道雪オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowSML(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int tbl_num;
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	s32* obj_w;	// オブジェクトワーク
	int		frame;		// フレーム数
	
	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;

		
	// 風の値を求める
	sys_w->work[1]++;
	if(sys_w->work[1] >= (WEATHER_SNOW_S_ADD_SP_CHG_TMG  * WEATHER_SNOW_S_ADD_SP_TMG_NUM)){
		sys_w->work[1] = 0;
	}
	tbl_num = (sys_w->work[1] / WEATHER_SNOW_S_ADD_SP_CHG_TMG );

	
	// num分オブジェクトを登録
	for(i=0;i<num*4;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		// 領域を初期化
		obj_w[0] = 0;			// カウンタ
		obj_w[1] = WEATHER_SNOW_S_END_MIN + (gf_mtRand() % (WEATHER_SNOW_S_END_MAX - WEATHER_SNOW_S_END_MIN));	// 終了カウンタ
		frame = gf_mtRand()%4;	// 吹雪の種類
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
		
		obj_w[4] = WEATHER_SSNOW_SPEED_X_SML[tbl_num] * ((frame)+1);
		obj_w[2] = WEATHER_SSNOW_SPEED_Y_SML[tbl_num] * ((frame)+1);	// たてスピード
		obj_w[3] = 0;			// 破棄アニメフラグ
		if(frame == 3){
			obj_w[4] += WEATHER_SSNOW_SPEED_X_SML[tbl_num];
			obj_w[2] += WEATHER_SSNOW_SPEED_Y_SML[tbl_num];
		}
		obj_w[5] = WEATHER_SSNOW_SPEED_X_SML[tbl_num];
		
		// 座標を設定
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_SNOW_S_START_X + (gf_mtRand() % WEATHER_SNOW_S_START_X_RAN);
			mat.y = WEATHER_SNOW_S_START_Y_BASE + (gf_mtRand() % WEATHER_SNOW_S_START_Y_MAX);
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;

			setClactMatrix(add_obj->clact_w, &mat);
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	吹雪オブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowSML(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// 動作フラグをチェック
	switch(obj_w[3]){
	case 0:		// 動作

		// 動かす
		mat.x += obj_w[4] << FX32_SHIFT;
		mat.y += obj_w[2] << FX32_SHIFT;

		// 破棄するかチェック
		if(obj_w[0]++ > obj_w[1]){
			// 破棄
			obj_w[3] = 1;
		}
		// カウンタで動かす値を変化
		if((obj_w[0] % WEATHER_SNOW_S_ADD_SP_TMG) == 0){
			obj_w[4] += obj_w[5];
			
			if(obj_w[2] > 1){
				obj_w[2]--;
			}
		}
	
		setClactMatrix( p_obj->clact_w, &mat );
		break;
	case 1:		// 破棄
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	スノーダスト管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSnowD(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL* sys_w;		// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	

		
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理

	
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_D_ADD_START,	// obj登録数
			WEATHER_SNOW_D_TIMING_MAX,// 登録タイミング
			WEATHER_SNOW_D_ADD_MAIN,
			WEATHER_SNOW_D_TIMING_MIN,
			-WEATHER_SNOW_D_TIMING_ADD,
			WEATHER_SNOW_D_ADD_TIMING,
			WEATHER_SNOW_D_ADD,
			addWeatherSnowD );
		
		// フォグ設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_D_FOG_OFS, 
				GX_RGB(26,26,26),
				WEATHER_SNOW_D_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_SNOW_D_FOG_START;	// 同じくフォグ用
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行	
		

		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化

	
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_SNOW_D_ADD_MAIN,	// obj登録数
			WEATHER_SNOW_D_TIMING_MIN,// 登録タイミング
			WEATHER_SNOW_D_ADD_MAIN,
			WEATHER_SNOW_D_TIMING_MIN,
			-WEATHER_SNOW_D_TIMING_ADD,
			WEATHER_SNOW_D_ADD_TIMING,
			WEATHER_SNOW_D_ADD,
			addWeatherSnowD );
		
		// フォグ設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_SNOW_D_FOG_OFS, GX_RGB(26,26,26) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSnowD, WEATHER_SNOW_D_NOFADE_OBJ_START_NUM, WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_NUM, WEATHER_SNOW_D_NOFADE_OBJ_START_DUST_MOVE, objWeatherSnowD );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){
			
			
			// ダイヤモンドダスト登録
			addWeatherSnowD(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){

			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SNOW_D_TIMING_MAX,
					WEATHER_SNOW_D_TIMING_ADD_END,
					-WEATHER_SNOW_D_ADD_END );
			
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_SNOW_D_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_SNOW_S_FOG_START_END;	// 同じくフォグ用	
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSnowD);
		
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);

	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スノーダストオブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSnowD(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int	rand;
	int sum_y;	// y座標計算
	int	big_d;	// 大きいダイヤモンドダストにするかチェック
	int frame;	// フレーム数
	VecFx32 mat;	// 座標
	s32* obj_w;	// オブジェクトワーク
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		obj_w[0] = 0;		// カウンタ
		obj_w[1] = WEATHER_SNOW_D_SPARK_NUM_MIN + (gf_mtRand() % WEATHER_SNOW_D_SPARK_NUM_RAN);
		rand = gf_mtRand() % 1000;

		
		if((rand % 2) == 0){			// 横の移動のプラスマイナス
			obj_w[2] = 1;
		}else{
			obj_w[2] = -1;
		}
		obj_w[3] = 1;
		

		obj_w[4] = WEATHER_SNOW_D_SP_ADD_TMG_X_MIN + (gf_mtRand() % WEATHER_SNOW_D_SP_ADD_TMG_X_MAX);
		obj_w[5] = WEATHER_SNOW_D_SP_ADD_TMG_Y_MIN + (gf_mtRand() % WEATHER_SNOW_D_SP_ADD_TMG_Y_MAX);
		
	
		// 小さい光を出す
		frame = gf_mtRand() % WEATHER_SNOW_D_SPARK_NO;
		
		// 座標
		{
			mat = getObjMat( add_obj );
			mat.x = WEATHER_SNOW_D_START_X_MIN + (gf_mtRand() % WEATHER_SNOW_D_START_X_DIS);
			mat.y = WEATHER_SNOW_D_START_Y + (gf_mtRand() % WEATHER_SNOW_D_START_Y_MAX);
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;
			setClactMatrix( add_obj->clact_w, &mat );
			mat.x >>= FX32_SHIFT;
			mat.y >>= FX32_SHIFT;
		}
		
		
		// Xの値から方程式で求める
		sum_y = 50 - (mat.x/3);
		rand = 206 - (mat.x/3);
		if(rand < 0){
			rand*=-1;
			big_d = sum_y - (gf_mtRand()%rand);		
		}else{
			big_d = sum_y + (gf_mtRand()%rand);		
		}
		if((sum_y <= mat.y) &&
			(big_d >= mat.y)){
			
			obj_w[1] *= 2;
//			obj_w[6] = 4;		// おそ点滅
		}else{
			// 小さい光にする
			frame = gf_mtRand() % 4;
//			obj_w[6] = 1;		// 半透明
		}
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スノーダストオブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSnowD(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	int		rand;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );


	// ぶれる
	obj_w[0]++;
	
	if((obj_w[0] % obj_w[4]) == 0){
		mat.x += obj_w[2] << FX32_SHIFT;
	}
	
	if((obj_w[0] % obj_w[5]) == 0){
		mat.y += obj_w[3] << FX32_SHIFT;
	}
	
	// 破棄するかチェック
	if(obj_w[0] >= obj_w[1]){
		destObj(p_obj);
		return ;
	}
		
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	虹管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherRainbow(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	s32* sys_w;			// システムワーク

	sys_w = (s32*)sys_work->work;	// ワークポインタセット
	

		
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理

		sys_w[0] = 0;	// アルファカウンタ
		sys_w[1] = 0;	// アルファ値
		
		WeatherBGAlphaDef(0, 16);
		G2_SetBG2Offset(0,32);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// フェードイン

		sys_w[0]++;
		
		if(sys_w[0] >= 10){
			sys_w[0] = 0;
			sys_w[1]++;
		
			WeatherBGAlphaDef(sys_w[1], 16);
			if(sys_w[1] >= 10){
				sys_w[2] = 10 + (gf_mtRand() % 20);	// 値を変更するタイミング
				sys_w[3] = 5 + (gf_mtRand() % 3);		// アルファを落とす限度
				sys_w[4] = 1;							// アルファを減らすか
				
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
			
		}
		
		
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化

		sys_w[0] = 0;	// アルファカウンタ
		sys_w[1] = 10;	// アルファ値
		G2_SetBG2Offset(0,32);
		
		WeatherBGAlphaDef(sys_w[1], 16);
		
		sys_w[2] = 10 + (gf_mtRand() % 20);	// 値を変更するタイミング
		sys_w[3] = 5 + (gf_mtRand() % 3);		// アルファを落とす限度
		sys_w[4] = 1;							// アルファを減らすか
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// メイン
		sys_w[0]++;
		

		if(sys_w[0] >= sys_w[2]){
			sys_w[0] = 0;

			if(sys_w[4] == 1){
				sys_w[1]--;
				if(sys_w[1] <= sys_w[3]){
					sys_w[2] = 10 + (gf_mtRand() % 15);		// 値を変更するタイミング
					sys_w[3] = 7 + (gf_mtRand() % 3);		// アルファを落とす限度
					sys_w[4] = 0;							// アルファを減らすか
				}
			}else{
				sys_w[1]++;
				if(sys_w[1] >= sys_w[3]){
					sys_w[2] = 10 + (gf_mtRand() % 20);	// 値を変更するタイミング
					sys_w[3] = 5 + (gf_mtRand() % 3);		// アルファを落とす限度
					sys_w[4] = 1;							// アルファを減らすか
				}
			}
		}
		WeatherBGAlphaDef(sys_w[1], 16);
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		sys_w[0]++;
		
		if(sys_w[0] >= 10){
			sys_w[0] = 0;
			sys_w[1]--;
		
			WeatherBGAlphaDef(sys_w[1], 16);
			if(sys_w[1] <= 0){
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_DEST;
			}
			
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	大雨初期化処理
 *	@param	sys_work
 *	@param	sys_w 
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Init( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// 作業領域の初期化
	weatherSysObjFadeInit( &sys_w->objFade, sys_work,
		WEATHER_STRAIN_ADD_START,	// obj登録数
		WEATHER_STRAIN_TIMING_MAX,// 登録タイミング
		WEATHER_STRAIN_ADD_MAIN,
		WEATHER_STRAIN_TIMING_MIN,
		-WEATHER_STRAIN_TIMING_ADD,
		WEATHER_STRAIN_ADD_TIMING,
		WEATHER_STRAIN_ADD,
		addWeatherSTRain );
	

	// フォグの設定
	weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
			sys_work->pWSysCont->fsys->fog_data,
			WEATHER_FOG_SLOPE_DEFAULT, 
			WEATHER_FOG_DEPTH_DEFAULT, 
			GX_RGB(26,26,26),
			WEATHER_STRAIN_FOG_TIMING,
			sys_work->fog_use );
	sys_w->work[0] = WEATHER_STRAIN_FOG_START;	// 同じくフォグ用
	sys_w->work[1] = 0;
	sys_w->work[2] = 0;							// 風カウンタ

	// 音
	WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_OOAME );	

//*/
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨フェードイン処理
 *	@param	sys_work
 *	@param	sys_w 
 *
 *	@retval	TRUE	フェード完了
 *	@retval	FALSE	フェード途中
 */
//-----------------------------------------------------------------------------
static BOOL contWeatherSTRain_FadeIn( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果

	// オブジェクトフェード
	result = weatherSysObjFade(&sys_w->objFade);	// 実行	

	if(sys_w->work[0] > 0){
		sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		
	}else{
		fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		

		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨　フェードなし初期化
 *
 *	@param	sys_work	
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_NoFade( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// 作業領域の初期化
	weatherSysObjFadeInit( &sys_w->objFade, sys_work,
		WEATHER_STRAIN_ADD_MAIN,	// obj登録数
		WEATHER_STRAIN_TIMING_MIN,// 登録タイミング
		WEATHER_STRAIN_ADD_MAIN,
		WEATHER_STRAIN_TIMING_MIN,
		-WEATHER_STRAIN_TIMING_ADD,
		WEATHER_STRAIN_ADD_TIMING,
		WEATHER_STRAIN_ADD,
		addWeatherSTRain );
	

	// フォグの設定
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		// データを設定
		sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
		weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT, GX_RGB(26,26,26) );
		// テーブルデータを作成して反映
		weatherSysFogSet( &sys_w->fogFade );
	}

	sys_w->work[1] = 0;
	sys_w->work[2] = 0;							// 風カウンタ

	// オブジェクトを散らばす
	weatherDustObj( sys_work, addWeatherSTRain, WEATHER_STRAIN_NOFADE_OBJ_START_NUM, WEATHER_STRAIN_NOFADE_OBJ_START_DUST_NUM, WEATHER_STRAIN_NOFADE_OBJ_START_DUST_MOVE, objWeatherSTRain );


	// 音
	WeatherLoopSndPlay( sys_work, SEQ_SE_DP_T_OOAME );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨メイン処理
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Main( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	sys_w->work[2] = (sys_w->work[2] + 1) % (WEATHER_STRAIN_OBJ_MUL_CHG*WEATHER_STRAIN_OBJ_MUL_NUM);		// 雨登録料変更カウンタ
	// カウンタが0いかになったら雨登録
	if(sys_w->objFade.objAddTmg-- <= 0){
						
		// 雨登録
		addWeatherSTRain(sys_work, sys_w->objFade.objAddNum);

		sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	大雨フェードアウト初期化処理
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_FadeOutInit( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// obj
	// フェードアウト設定
	weatherSysObjFadeOutSet( &sys_w->objFade,
			0,
			WEATHER_STRAIN_TIMING_MAX,
			WEATHER_STRAIN_TIMING_ADD,
			WEATHER_STRAIN_ADD_END );
	
	// fog
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_STRAIN_FOG_TIMING_END, FALSE );
	}
	sys_w->work[0] = WEATHER_STRAIN_FOG_START_END;	// 同じくフォグ用

	// 音
	WeatherLoopSndStop( sys_work );	
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨フェードアウト処理
 *
 *	@param	sys_work
 *	@param	sys_w 
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL contWeatherSTRain_FadeOut( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果

	// オブジェクトフェード
	result = weatherSysObjFade(&sys_w->objFade);	// 実行
	
	// フォグ操作
	if(sys_w->work[0] > 0){
		sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		
	}else{
	
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		if((fog_result == 1) && (result == 3)){
			// 登録数が０になったら終了するかチェック
			// 自分の管理するあめが全て破棄されたら終了
			if(sys_work->Dummy.pNext == &sys_work->Dummy){
				
				return TRUE;
			}
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨　破棄処理
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Dest( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	if(sys_work->fog_use != WEATHER_FOG_NONE){
		SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
	}
	{
		WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
		stopWeatherWork_local(p_wsd);

	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨　描画処理
 *
 *	@param	sys_work
 *	@param	sys_w 
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain_Draw( WEATHER_SYS_WORK* sys_work, WEATHER_SYSW_NORMAL* sys_w )
{
	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSTRain);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	大雨＋雷
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRainSpark(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// 初期化処理
		contWeatherSTRain_Init( sys_work, sys_w );
		// 雷を発動
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_INIT, WEATHER_SYS_SPARK_EFF );
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_START_NOFADE, WEATHER_SYS_SPARK_EFF );
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		if( contWeatherSTRain_FadeIn( sys_work, sys_w ) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		contWeatherSTRain_NoFade( sys_work, sys_w );
		// 雷を発動
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_INIT, WEATHER_SYS_SPARK_EFF );
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_START_NOFADE, WEATHER_SYS_SPARK_EFF );//*/
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		break;
	case WEATHER_SEQ_MAIN:		// メイン
		contWeatherSTRain_Main( sys_work, sys_w );
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			contWeatherSTRain_FadeOutInit( sys_work, sys_w );
			// 雷終了
			ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_END, WEATHER_SYS_SPARK_EFF );//*/

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		if( contWeatherSTRain_FadeOut( sys_work, sys_w ) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		contWeatherSTRain_Dest( sys_work, sys_w );
		// 雷強制終了
		ControlWeatherSys( sys_work->pWSysCont, WEATHER_SYS_DEST, WEATHER_SYS_SPARK_EFF );//*/

		break;

	default:
		break;
	}
	// 描画処理
	contWeatherSTRain_Draw( sys_work, sys_w );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	雨管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSTRain(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// 初期化処理
		contWeatherSTRain_Init( sys_work, sys_w );
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;

		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		if( contWeatherSTRain_FadeIn( sys_work, sys_w ) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		contWeatherSTRain_NoFade( sys_work, sys_w );
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		contWeatherSTRain_Main( sys_work, sys_w );
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			contWeatherSTRain_FadeOutInit( sys_work, sys_w );

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		if( contWeatherSTRain_FadeOut( sys_work, sys_w ) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		contWeatherSTRain_Dest( sys_work, sys_w );
		break;

	default:
		break;
	}
	// 描画処理
	contWeatherSTRain_Draw( sys_work, sys_w );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	雨オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		雨用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSTRain(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	int	err;	// 補正値
	s32* obj_w;	// オブジェクトワーク
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	int speed_m;	// スピードにかける値テーブルの要素数
	int frame;		// フレーム数
	static const int WEATHER_STRAIN_OBJ_MUL[ WEATHER_STRAIN_OBJ_MUL_NUM ] = {100, 100, 200, 100, 300};

	sys_w = (WEATHER_SYSW_NORMAL*)pWork->work;
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}
		obj_w = (s32*)add_obj->work;
		
		// 領域を初期化
		obj_w[0] = 0;			// カウンタ
		frame = gf_mtRand()%3;	// 雨の種類
		CLACT_AnmFrameSet( add_obj->clact_w, frame );

		obj_w[4] = WEATHER_STRAIN_SPEED_X * (frame+1);
		obj_w[2] = WEATHER_STRAIN_SPEED_Y * (frame+1);
		obj_w[4] *= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		obj_w[2] *= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		obj_w[4] /= 100;
		obj_w[2] /= 100;
		
		obj_w[3] = 0;			// 破棄アニメフラグ
		
		// 破棄タイミング	全部共通の範囲の値
		obj_w[1] = WEATHER_STRAIN_END_MIN  + (gf_mtRand() % WEATHER_STRAIN_END_MAX);
		obj_w[1] *= 100;
		obj_w[1] /= WEATHER_STRAIN_OBJ_MUL[sys_w->work[2]/WEATHER_STRAIN_OBJ_MUL_CHG];
		
		// 座標を設定
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_STRAIN_START_X + (gf_mtRand() % WEATHER_STRAIN_START_X_MAX);
			mat.y = WEATHER_STRAIN_START_Y + (gf_mtRand() % WEATHER_STRAIN_START_Y_MAX);
			mat.z = 0;

			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			setClactMatrix(add_obj->clact_w, &mat);
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雨オブジェクト動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSTRain(WAETHER_OBJ_DATA* work)
{
	int i;
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	
	// 動作フラグをチェック
	switch(obj_w[3]){
	case 0:		// 動作
		// 雨のとった後を見せるため1フレームに2回の描画を行い、１．５の位置も見せる
		for(i=0;i<2;i++){
			// 動かす
			mat.x += obj_w[4] << FX32_SHIFT;
			mat.y += obj_w[2] << FX32_SHIFT;
		
			// 破棄するかチェック
			if(obj_w[0]++ > obj_w[1]){
				// アニメーションさせるかチェック
				if((gf_mtRand() % 10) < 5){		// 7/10は破棄
					// 破棄
					obj_w[3] = 2;
				}else{
				
					// 破棄アニメ
					obj_w[3] = 1;		
					obj_w[0] = 4;			// 破棄アニメカウンタ
					CLACT_AnmFrameSet(p_obj->clact_w, 3);// 破棄アニメの絵
				}
			}
			setClactMatrix(p_obj->clact_w, &mat);
		}
		break;
	case 1:		// 破棄アニメ
		if(obj_w[0]-- <= 0){
			obj_w[3] = 2;		// 破棄
		}
		break;

	case 2:		// 破棄
		destObj(p_obj);
		break;
	}		
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	火山灰管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherVolcano(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	int		tmp_y;		// y座標保存用
	int		scl_x, scl_y;	// スクロール座標
	short		sc_w_x, sc_w_y;	// スクロールワーク
	WEATHER_SYSW_NORMAL* sys_w;			// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
	


	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj登録数
			WEATHER_VOLCANO_TIMING_MAX,	// 登録タイミング
			WEATHER_VOLCANO_MAIN,
			WEATHER_VOLCANO_TIMING_MIN,
			-WEATHER_VOLCANO_TIMING_ADD,
			WEATHER_VOLCANO_ADD_TIMING,
			WEATHER_VOLCANO_ADD,
			addWeatherVolcano );
		
		sys_w->work[1] = 0;						// 火山灰が１回下まで行ったかのフラグ
		sys_w->work[2] = 0;						// BG座標	上16bit X	下16bit Y
		sys_w->work[4] = 0;						// BG横カウンタ

		sys_w->work[5] = 0;						// オブジェクト破棄フラグ
		
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT + WEATHER_VOLCANO_FOG_SLOPE, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_VOLCANO_FOG_OFS, 
				GX_RGB(20,20,14),
				WEATHER_VOLCANO_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_VOLCANO_FOG_START;	// 同じくフォグ用
		
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			// FOG
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
				// BGON
				GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_VOLCANO_MAIN,	// obj登録数
			WEATHER_VOLCANO_TIMING_MIN,	// 登録タイミング
			WEATHER_VOLCANO_MAIN,
			WEATHER_VOLCANO_TIMING_MIN,
			-WEATHER_VOLCANO_TIMING_ADD,
			WEATHER_VOLCANO_ADD_TIMING,
			WEATHER_VOLCANO_ADD,
			addWeatherVolcano );
		
		sys_w->work[1] = 0;						// 火山灰が１回下まで行ったかのフラグ
		sys_w->work[2] = 0;						// BG座標	上16bit X	下16bit Y
		sys_w->work[4] = 0;						// BG横カウンタ
		sys_w->work[5] = 0;						// オブジェクト破棄フラグ
		
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_VOLCANO_FOG_OFS, GX_RGB(20,20,14) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherVolcano, WEATHER_VOLCANO_NOFADE_OBJ_START_NUM, WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_NUM, WEATHER_VOLCANO_NOFADE_OBJ_START_DUST_MOVE, objWeatherVolcano );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;

		// BGON
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 火山灰登録
			addWeatherVolcano(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_VOLCANO_TIMING_MAX,
					WEATHER_VOLCANO_TIMING_ADD,
					-1 );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_VOLCANO_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_VOLCANO_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了

			sys_w->work[5] = 1;						// オブジェクト破棄フラグ
			
			// BGOFF
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			// フォグ
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherVolcano);
		scrollObj(sys_work, &scl_x, &scl_y);
		drawObj(sys_work);


		// BGスクロール
		sc_w_x = sys_w->work[2] >> 16;	// スクロール座標取り出し
		sc_w_y = sys_w->work[2] & 0xffff;
		sc_w_x += scl_x;
		sc_w_y -= scl_y*5;
		if(sc_w_x < 0){
			sc_w_x += 256;
		}else{
			if(sc_w_x >= 256){
				sc_w_x -= 256;
			}
		}
		if(sc_w_y < 0){
			sc_w_y += 2048;
		}

		// BG面の横は一定間隔でずらす（ちらちらを表現）
		sys_w->work[4]+=2;
		if(sys_w->work[4] > 60){
			sys_w->work[4] = 0;

			sc_w_x = (sc_w_x + 32) % 256;
		}
		
		// BG面を斜め上に動かす
		sc_w_y = (sc_w_y + 2) % 2048;
		G2_SetBG2Offset(sc_w_x, -sc_w_y/5);
		sys_w->work[2] = sc_w_x << 16;	// スクロール座標格納
		sys_w->work[2] |= sc_w_y & 0xffff;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	火山灰オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 *	内容
 *		num分オブジェクトを登録
 *		火山灰用にワーク領域を初期化
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherVolcano(WEATHER_SYS_WORK* pWork, int num)
{
	int i;		// ループ用
	int rand;	// 乱数
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	WEATHER_SYSW_NORMAL* sys_w;	// システムワーク
	int frame;	// フレーム数
	s32* obj_w;	// オブジェクトワーク
	sys_w = pWork->work;


	if(sys_w->work[1] == 1){
		num *= 2;
	}
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;
		
		frame = gf_mtRand() % WEATHER_VOLCANO_OBJ_NUM;
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
		
		obj_w[4] = 10;	// 横の動く方向変更カウンタ	
		obj_w[5] = 0;
		
		rand = gf_mtRand();
	
		// スピード
		if((rand % 2) == 0){
			obj_w[1] = 1;
		}else{
			obj_w[1] = -1;
		}
		obj_w[3] = WEATHER_VOLCANO_ADD_TMG_Y_BASE + (gf_mtRand() % WEATHER_VOLCANO_ADD_TMG_Y_RAN);

		obj_w[0] = (s32)&sys_w->work[1];		// 下まで行ったらフラグを立てるポインタを保存
		obj_w[6] = (s32)&sys_w->work[5];		// 破棄フラグ
		obj_w[7] = WEATEHR_VOLCANO_DEL_COUNT_MIN + (gf_mtRand() % WEATEHR_VOLCANO_DEL_COUNT_MAX);					// 破棄ｶｳﾝﾀ
		
		// 座標を設定
		{
			VecFx32 mat = getObjMat( add_obj );
			mat.x = WEATHER_VOLCANO_START_X_BASE + (gf_mtRand() % WEATHER_VOLCANO_START_X_MAX);
		
			if((sys_w->work[1] == 1) &&
				(i >= (num /2)) ){	// 半分出す
				mat.y = -40 - (gf_mtRand() % 20);
			}else{
				mat.y = -8 - (gf_mtRand() % 20);
			}
			mat.x <<= FX32_SHIFT;
			mat.y <<= FX32_SHIFT;
			mat.z = 0;

			setClactMatrix( add_obj->clact_w, &mat );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	火山灰動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherVolcano(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );
	BOOL del_flg = FALSE;

	// 動かす
	if((obj_w[5] >= obj_w[3])){
		mat.y += FX32_ONE;
		obj_w[5] = 0;

		setClactMatrix( p_obj->clact_w, &mat );
	} 
	
	obj_w[5]++;

	mat.y >>= FX32_SHIFT;

	// 破棄フラグが立っていたら、破棄
	if( *((s32*)obj_w[6]) == 1 ){

		// 破棄ｶｳﾝﾀが無くなったら破棄
		obj_w[7] --;
		if( obj_w[7] <= 0 ){
			del_flg = TRUE;
		}
	}
	
	// 破棄ゾーンにいたら破棄  
	if(((mat.y < -284) && (mat.y > -296)) ||
		((mat.y > 212) && (mat.y < 232))){
		del_flg = TRUE;
	}

	if( del_flg == TRUE ){
		*((s32*)obj_w[0]) = 1;
		destObj(p_obj);
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	雷管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSpark(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	s32* sys_w;			// システムワーク
	int	num;
	int rand;
	
	sys_w = (s32*)sys_work->work;	// ワークポインタセット
	

	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
	case WEATHER_SEQ_FADEIN:	// フェードイン
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		
		// 作業領域の初期化
		sys_w[0] = 0;		// ライトフェードカウンタ
		sys_w[4] = 0;
		sys_w[1] = 0;
		WeatherBGAlphaDef(0,31);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		

		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		if(sys_w[4] >= 0){
			sys_w[4]--;
		}else{
			switch(sys_w[1]){
			case 0:
				sys_w[1] = 1;		// ライトフェード中
				sys_w[5] = 0;
				sys_w[6] = WEATHER_SPARK_POWER_MIN+(gf_mtRand() % WEATHER_SPARK_POWER_RAN);	// 光の増やす値を求める
				sys_w[7] = 0;		// 今のアルファ

				// 点滅の雷にするか　落ちた雷にするかチェック
				if((gf_mtRand()%3) != 0){
					sys_w[2] = WEATHER_SPARK_SUB_NUM;

					// ごろ雷
					Snd_SePlay( SEQ_SE_DP_T_KAMI2 );
				}else{
					sys_w[2] = WEATHER_SPARK_SUB_NUM_HIGH;

					// ピカ雷
					Snd_SePlay( SEQ_SE_DP_T_KAMI );
				}
				break;
			case 1:
				sys_w[5]++;
				sys_w[7] += sys_w[6];	
				if(sys_w[5] >= WEATHER_SPARK_NUM){	// 終了チェック
					sys_w[1] = 2;		// 暗くする
				}
				WeatherBGAlphaDef(sys_w[7]/100,31);
				break;
			case 2:
				sys_w[7] -= sys_w[2];	
				if(sys_w[7] <= 0){	// 終了チェック
					sys_w[1] = 0;
					sys_w[7] = 0;

					// 次の雷までのカウンタを設定
					// 消えるのが早いときはもう一度出す
					if(sys_w[2] == WEATHER_SPARK_SUB_NUM_HIGH){
						sys_w[4] = (gf_mtRand() % WEATHER_SPARK_SPARK_RAN_HIGH);
					}else{
						sys_w[4] = ((sys_w[6] * WEATHER_SPARK_SPARK_MUL)/100) + (gf_mtRand()%WEATHER_SPARK_SPARK_RAN);
					}
				}
				WeatherBGAlphaDef(sys_w[7]/100,31);
				break;
			}
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
				
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		
		sys_work->Sequence = WEATHER_SEQ_DEST;
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	気合管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherSpirit(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_OBJFADE* sys_w;			// システムワーク
	int		result;		// 関数結果
	
	sys_w = (WEATHER_SYSW_OBJFADE*)sys_work->work;	// ワークポインタセット
	

			
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj登録数
			WEATHER_SPIRIT_TIMING_MAX,	// 登録タイミング
			WEATHER_SPIRIT_MAIN,
			WEATHER_SPIRIT_TIMING_MIN,
			-WEATHER_SPIRIT_TIMING_ADD,
			WEATHER_SPIRIT_ADD_TIMING,
			WEATHER_SPIRIT_ADD,
			addWeatherSpirit );
		
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		// タイミングが最小になったらメインへ
		if(result == 3){		// フェードリザルトが完了ならばメインへ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			1,	// obj登録数
			WEATHER_SPIRIT_MAIN,	// obj登録数
			WEATHER_SPIRIT_TIMING_MIN,	// 登録タイミング
			WEATHER_SPIRIT_TIMING_MIN,
			-WEATHER_SPIRIT_TIMING_ADD,
			WEATHER_SPIRIT_ADD_TIMING,
			WEATHER_SPIRIT_ADD,
			addWeatherSpirit );

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherSpirit, WEATHER_SPIRIT_NOFADE_OBJ_START_NUM, WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_NUM, WEATHER_SPIRIT_NOFADE_OBJ_START_DUST_MOVE, objWeatherSpirit );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 岩登録
			addWeatherSpirit(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_SPIRIT_TIMING_MAX,
					WEATHER_SPIRIT_TIMING_ADD,
					WEATHER_SPIRIT_ADD_END );
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}

		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行

		if(result == 3){
			// 登録数が０になったら終了するかチェック
			// 自分の管理するあめが全て破棄されたら終了
			if(sys_work->Dummy.pNext == &sys_work->Dummy){
				
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_DEST;
			
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherSpirit);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	気合オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherSpirit(WEATHER_SYS_WORK* pWork, int num)
{
	int i;			// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	s32* obj_w;		// オブジェクトワーク
	int obj_num;	// オブジェクト数
	int frame;		// フレーム数
	VecFx32 mat;	// 座標

		
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*8);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;

		// 種類を求める
		frame = gf_mtRand() % WEATHER_SPIRIT_OBJ_NUM;
		CLACT_AnmFrameSet( add_obj->clact_w, frame );

		// 種類から解放カウンタ、加速値を求める
		obj_num = frame / WEATHER_SPIRIT_BIG_DIV;	// オブジェの大きさidx
		obj_num++;	// 0->1にする
		obj_w[0] = WEATHER_SPIRIT_SHIFT_UP+(gf_mtRand()%WEATHER_SPIRIT_SHIFT_UP_RAN);	// 力解放カウンタ
		obj_w[0] *= obj_num;
		obj_w[1] = WEATHER_SPIRIT_ADD_SPEED / obj_num;	// 加速値//*/
		obj_w[2] = 0;									// 今の速度

		// 小刻みに横に動く
		obj_w[3] = gf_mtRand() % 2;		// 0:右	1:左
		obj_w[4] = WEATHER_SPIRIT_S_MOVE_TMG;	// ゆれるタイミング

		
		// 座標
		switch(obj_num){
		case 1:
		case 2:
				
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_S_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_S_RAN);
			break;
		case 3:
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_M_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_M_RAN);
			break;
		case 4:
			mat.x = WEATHER_SPIRIT_MAT_X_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_X_RAN);
			mat.y = WEATHER_SPIRIT_MAT_Y_L_MIN + (gf_mtRand() % WEATHER_SPIRIT_MAT_Y_L_RAN);
			break;
		}
		mat.z = 0;
		mat.x <<= FX32_SHIFT;
		mat.y <<= FX32_SHIFT;
		setClactMatrix( add_obj->clact_w, &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	気合動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherSpirit(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	VecFx32 mat = getObjMat( p_obj );

	// 加速しながら移動
	obj_w[2] += obj_w[1];
	if(obj_w[0] > 0){
		obj_w[0]--;		// 力解放カウント	0になったら速度＊２

		mat.y -= (obj_w[2]/100) << FX32_SHIFT;
	}else{
		mat.y -= (obj_w[2]/50) << FX32_SHIFT;
	}

	// 小刻みに揺れる
	obj_w[4]--;
	if(obj_w[4] <= 0){
		obj_w[4] = WEATHER_SPIRIT_S_MOVE_TMG;

		if(obj_w[3] == 0){
			mat.x += WEATHER_SPIRIT_S_MOVE_NUM << FX32_SHIFT;
			obj_w[3] = 1;
		}else{
			mat.x -= WEATHER_SPIRIT_S_MOVE_NUM << FX32_SHIFT;
			obj_w[3] = 0;
		}
	}

	setClactMatrix( p_obj->clact_w, &mat );
	

	//　上まで行ったら終わり
	if( (mat.y >> FX32_SHIFT) <= -16){
		destObj(p_obj);
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	神秘管理タスク
 *
 *@param	tcb		自分のタスク
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void contWeatherMystic(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;			// システムワーク
	BOOL result;
	BOOL fog_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_MYSTIC_FADE_END_ALPHA, WEATHER_MYSTIC_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);

		// 表示優先順位変更
		G2_SetBG2Priority(3);
		
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

/*
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_MYSTIC_FOG_SLOPE, 
				WEATHER_MYSTIC_FOG_OFS, 
				GX_RGB(0,0,0),
				WEATHER_MYSTIC_FOG_TIMING,
				sys_work->fog_use );
//*/		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// フェードイン

//		fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
		fog_result = TRUE;

		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( (result == TRUE) && (fog_result == TRUE) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化

		WeatherBGAlphaDef(WEATHER_MYSTIC_FADE_END_ALPHA, 16 - WEATHER_MYSTIC_FADE_END_ALPHA);

		// 表示優先順位変更
		G2_SetBG2Priority(3);
		
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );


		// フォグの設定
/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_MYSTIC_FOG_SLOPE, WEATHER_MYSTIC_FOG_OFS, GX_RGB(0,0,0) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}//*/
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			WeatherMoveReq( &sys_w->alpha, WEATHER_MYSTIC_FADE_END_ALPHA, 0, WEATHER_MYSTIC_FADE_COUNT_MAX );

			// fog
/*			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_MYSTIC_FOG_TIMING_END, FALSE );
			}//*/
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}//*/
		fog_result = TRUE;

		if( (result == TRUE) && (fog_result == TRUE) ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
/*		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}//*/
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}

#if 0
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	int		i;			// ループ用
	WEATHER_SYSW_NORMAL* sys_w;			// システムワーク
	int		result;		// 関数結果
	int		fog_result;	// フォグ結果
	sys_w = (WEATHER_SYSW_NORMAL*)sys_work->work;	// ワークポインタセット
		

		
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_MYSTIC_ADD_START,	// obj登録数
			WEATHER_MYSTIC_TIMING_MAX,	// 登録タイミング
			WEATHER_MYSTIC_ADD_MAIN,
			WEATHER_MYSTIC_TIMING_MIN,
			-WEATHER_MYSTIC_TIMING_ADD,
			WEATHER_MYSTIC_ADD_TIMING,
			WEATHER_MYSTIC_ADD,
			addWeatherMystic );
		
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_FOG_SLOPE_DEFAULT, 
				WEATHER_FOG_DEPTH_DEFAULT + WEATHER_MYSTIC_FOG_OFS, 
				GX_RGB(31,31,31),
				WEATHER_MYSTIC_FOG_TIMING,
				sys_work->fog_use );
		sys_w->work[0] = WEATHER_MYSTIC_FOG_START;	// 同じくフォグ用
		
		sys_w->work[1] = 0;			// オブジェクト追加数カウンタ
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
			fog_result = weatherSysFogFadeInMainPack(&sys_w->fogWithFade, &sys_w->fogFade, sys_work->fog_use);
			
			// タイミングが最小になったらメインへ
			if((fog_result == 1) && (result == 3)){		// フェードリザルトが完了ならばメインへ
				// シーケンス変更
				sys_work->Sequence = WEATHER_SEQ_MAIN;
			}
		}
		break;
	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化
		
		
		// 作業領域の初期化
		weatherSysObjFadeInit( &sys_w->objFade, sys_work,
			WEATHER_MYSTIC_ADD_MAIN,	// obj登録数
			WEATHER_MYSTIC_TIMING_MIN,	// 登録タイミング
			WEATHER_MYSTIC_ADD_MAIN,
			WEATHER_MYSTIC_TIMING_MIN,
			-WEATHER_MYSTIC_TIMING_ADD,
			WEATHER_MYSTIC_ADD_TIMING,
			WEATHER_MYSTIC_ADD,
			addWeatherMystic );
		
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_FOG_SLOPE_DEFAULT, WEATHER_FOG_DEPTH_DEFAULT + WEATHER_MYSTIC_FOG_OFS, GX_RGB(31,31,31) );
			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}
		
		sys_w->work[1] = 0;			// オブジェクト追加数カウンタ

		// オブジェクトを散らばす
		weatherDustObj( sys_work, addWeatherMystic, WEATHER_MYSTIC_NOFADE_OBJ_START_NUM, WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_NUM, WEATHER_MYSTIC_NOFADE_OBJ_START_DUST_MOVE, objWeatherMystic );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		
		// カウンタが0いかになったら雨登録
		if(sys_w->objFade.objAddTmg-- <= 0){

			// 神秘登録
			addWeatherMystic(sys_work, sys_w->objFade.objAddNum);
	
			sys_w->objFade.objAddTmg = sys_w->objFade.objAddTmgMax;	// 登録タイミングセット	
		}
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			// obj
			// フェードアウト設定
			weatherSysObjFadeOutSet( &sys_w->objFade,
					0,
					WEATHER_MYSTIC_TIMING_MAX,
					WEATHER_MYSTIC_TIMING_ADD,
					-WEATHER_MYSTIC_ADD_END );
			
			// fog
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_MYSTIC_FOG_TIMING_END, FALSE );
			}
			sys_w->work[0] = WEATHER_MYSTIC_FOG_START_END;	// 同じくフォグ用
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// オブジェクトフェード
		result = weatherSysObjFade(&sys_w->objFade);	// 実行
		
		// フォグ操作
		if(sys_w->work[0] > 0){
			sys_w->work[0]--;			// ワーク6が０になったらフォグを動かす
		}else{
		
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				fog_result = weatherSysFogFade(&sys_w->fogFade);
			}else{
				fog_result = 1;
			}
		
			if((fog_result == 1) && (result == 3)){
				// 登録数が０になったら終了するかチェック
				// 自分の管理するあめが全て破棄されたら終了
				if(sys_work->Dummy.pNext == &sys_work->Dummy){
					
					// シーケンス変更
					sys_work->Sequence = WEATHER_SEQ_DEST;
				}
			}
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}

	// 初期化、破棄以外のときは動作関数を動かす
	if((sys_work->Sequence != WEATHER_SEQ_DEST) &&
		(sys_work->Sequence != WEATHER_SEQ_INIT) ){

		moveFuncObj(&sys_work->Dummy, objWeatherMystic);
		scrollObj(sys_work, NULL, NULL);
		drawObj(sys_work);
	}
#endif
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	神秘オブジェクト登録関数
 *
 *@param	pWork		登録するオブジェの管理関数ワーク
 *@param	num			登録する数
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void addWeatherMystic(WEATHER_SYS_WORK* pWork, int num)
{
	int i;			// ループ用
	WAETHER_OBJ_DATA* add_obj;		// 登録オブジェ
	s32* obj_w;		// オブジェクトワーク
	int obj_num;	// オブジェクトの大きさけっていよう
	int ch_num;		// オブジェクトの大きさけっていよう
	int frame;		// フレーム数
	VecFx32 mat;	// 座標
	
	
	// num分オブジェクトを登録
	for(i=0;i<num;i++){

		add_obj = addObj(pWork, sizeof(s32)*10);		// 登録
		if(add_obj == NULL){			// 失敗したら終了
			break;
		}

		obj_w = (s32*)add_obj->work;
		// 大きさを決める
		obj_num = gf_mtRand()%WEATHER_MYSTIC_RAN;
		ch_num = 0;
		for(i=0;i<WEATHER_MYSTIC_NUM;i++){
			switch(i){
			case 0:
				ch_num += WEATHER_MYSTIC_RAN_0;
				break;
			case 1:
				ch_num += WEATHER_MYSTIC_RAN_1;
				break;
			case 2:
				ch_num += WEATHER_MYSTIC_RAN_2;
				break;
			case 3:
				ch_num += WEATHER_MYSTIC_RAN_3;
				break;
			}
			
			if(obj_num < ch_num){
				frame = i;
				break;
			}	
		}
		CLACT_AnmFrameSet( add_obj->clact_w, frame );
	 	
		// 破棄カウンタ初期化
		obj_w[0] = WEATHER_MYSTIC_DES_TM+(gf_mtRand()%WEATHER_MYSTIC_DES_RAN);
		
		// スピードを求める
		obj_w[2] = WEATHER_MYSTIC_M_Y + (WEATHER_MYSTIC_M_Y_MUL*frame);

		// 付加移動（浮遊物が自由に飛んでいるように見せるため、sin.cosで動かす）
		obj_w[4] = gf_mtRand() % 360;
		obj_w[5] = gf_mtRand() % 360;
		obj_w[6] = gf_mtRand() % WEATHER_MYSTIC_MH_X;
		obj_w[7] = gf_mtRand() % WEATHER_MYSTIC_MH_Y;
		obj_w[8] = WEATHER_MYSTIC_MH_COUNT + (gf_mtRand() % WEATHER_MYSTIC_MH_COUNT_RAN);
		
		// 座標を求める
		obj_w[1] = 0;
		obj_w[3] = 0;
		mat.x = WEATHER_MYSTIC_MAT_X+(gf_mtRand()%WEAHTER_MYSTIC_MAT_X_RAN);	// X座標
		mat.y = WEAHTER_MYSTIC_MAT_Y+(WEATHER_MYSTIC_MAT_Y_MUL*frame);
		mat.y += (gf_mtRand()%WEAHTER_MYSTIC_MAT_Y_RAN);
		mat.z = 0;
		mat.x <<= FX32_SHIFT;
		mat.y <<= FX32_SHIFT;

		setClactMatrix( add_obj->clact_w, &mat );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	神秘動作関数
 *
 *@param	work	ワーク領域
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void objWeatherMystic(WAETHER_OBJ_DATA* work)
{
	WAETHER_OBJ_DATA* p_obj = (WAETHER_OBJ_DATA*)work;
	s32* obj_w = (s32*)p_obj->work;
	int hm_num;		// 補助移動値
	fx32 hm_par;	// 移動補正値の値にかける値
	int sc_ch;		// スクロールﾁｪｯｸ用
	VecFx32 mat = getObjMat( p_obj );

	mat.x >>= FX32_SHIFT;
	mat.y >>= FX32_SHIFT;

	// スクロールチェック	スクロール処理で動いた座標を各内部座標にする
	sc_ch = obj_w[1] % 100;
	obj_w[1] = mat.y * 100;
	obj_w[1] += sc_ch;
	sc_ch = obj_w[3] % 100;
	obj_w[3] = mat.x * 100;
	obj_w[3] += sc_ch;
	
	// 移動
	obj_w[1] -= obj_w[2];
	
	// 補助移動
	hm_par = FX_SinIdx(obj_w[4]*182);
	hm_num = FX_Mul(hm_par, obj_w[6]<<FX32_SHIFT) >> FX32_SHIFT;
	obj_w[3] += hm_num;		// X座標補正
	hm_par = FX_SinIdx(obj_w[5]*182);
	hm_num = FX_Mul(hm_par, obj_w[7]<<FX32_SHIFT) >> FX32_SHIFT;
	obj_w[1] += hm_num;		// Y座標補正
	obj_w[4] = (obj_w[4]+obj_w[8]) % 360;	// 角度変更
	obj_w[5] = (obj_w[5]+obj_w[8]) % 360;	// 角度変更
	
	// 座標を設定
	mat.y = obj_w[1]/100;
	mat.x = obj_w[3]/100;


	mat.x <<= FX32_SHIFT;
	mat.y <<= FX32_SHIFT;
	setClactMatrix( p_obj->clact_w, &mat );
	
	// 破棄
	if(obj_w[0] <= 0){
		destObj(p_obj);
	}else{
		obj_w[0]--;
	}

}
#endif

//----------------------------------------------------------------------------
/**
 *	@brief	曇り　コントロール関数
 *
 *	@param	tcb		TCBワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherCloudiness(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_CLOUDINESS_WORK* sys_w;			// システムワーク
	BOOL result;
	sys_w = (WEATHER_CLOUDINESS_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_CLOUDINESS_FADE_END_ALPHA, WEATHER_CLOUDINESS_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	
	case WEATHER_SEQ_FADEIN:	// フェードイン

		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( result ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;

	case WEATHER_SEQ_NO_FADE:	// フェードインなし初期化

		WeatherBGAlphaDef(WEATHER_CLOUDINESS_FADE_END_ALPHA, 16 - WEATHER_CLOUDINESS_FADE_END_ALPHA);

		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			WeatherMoveReq( &sys_w->alpha, WEATHER_CLOUDINESS_FADE_END_ALPHA, 0, WEATHER_CLOUDINESS_FADE_COUNT_MAX );
			
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
	
	case WEATHER_SEQ_FADEOUT:	// フェードアウト
		result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);

		if( result ){
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}	
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	霧払い
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherKiriHarai(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// システムワーク
	int		fog_result;	// フォグ結果
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_KIRI_HARAI_FOG_SLOPE, 
				WEATHER_KIRI_HARAI_FOG_OFS, 
				WEATHER_KIRI_HARAI_FOG_COLOR,
				WEATHER_KIRI_HARAI_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_KIRI_HARAI_FADE_END_ALPHA, WEATHER_KIRI_HARAI_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならばメインへ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_KIRI_HARAI_FOG_SLOPE, WEATHER_KIRI_HARAI_FOG_OFS, WEATHER_KIRI_HARAI_FOG_COLOR );

			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_KIRI_HARAI_FADE_END_ALPHA, 16 - WEATHER_KIRI_HARAI_FADE_END_ALPHA);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_KIRI_HARAI_FADE_END_ALPHA, 0, WEATHER_KIRI_HARAI_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならば終了へ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	霧払い	しろ
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void contWeatherKiriHarai_White(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_KIRI_HARAI_WORK* sys_w;	// システムワーク
	int		fog_result;	// フォグ結果
	BOOL	alpha_result;
	sys_w = (WEATHER_KIRI_HARAI_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フォグの設定
		weatherSysFogFadeInInitPack( &sys_w->fogWithFade, &sys_w->fogFade,
				sys_work->pWSysCont->fsys->fog_data,
				WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE, 
				WEATHER_KIRI_HARAI_WHITE_FOG_OFS, 
				WEATHER_KIRI_HARAI_WHITE_FOG_COLOR,
				WEATHER_KIRI_HARAI_WHITE_FOG_TIMING,
				sys_work->fog_use );

		WeatherMoveReq( &sys_w->alpha, 0, WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX );
		WeatherBGAlphaDef(0, 16);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );

		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		
		fog_result = weatherSysFogFade(&sys_w->fogFade);

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならばメインへ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;
		}
		break;
	case WEATHER_SEQ_NO_FADE:
		// フォグの設定
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			// データを設定
			sys_w->fogFade.Fog = sys_work->pWSysCont->fsys->fog_data;		// フォグ保存先代入
			weatherSysFogParamSet( sys_w->fogFade.Fog, WEATHER_KIRI_HARAI_WHITE_FOG_SLOPE, WEATHER_KIRI_HARAI_WHITE_FOG_OFS, WEATHER_KIRI_HARAI_WHITE_FOG_COLOR );

			// テーブルデータを作成して反映
			weatherSysFogSet( &sys_w->fogFade );
		}

		WeatherBGAlphaDef(WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, 16 - WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;
	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			if(sys_work->fog_use != WEATHER_FOG_NONE){
				weatherSysFogFadeInit( &sys_w->fogFade, WEATHER_KIRI_HARAI_WHITE_FOG_TIMING_END, FALSE );
			}

			WeatherMoveReq( &sys_w->alpha, WEATHER_KIRI_HARAI_WHITE_FADE_END_ALPHA, 0, WEATHER_KIRI_HARAI_WHITE_FADE_COUNT_MAX );
			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		if(sys_work->fog_use != WEATHER_FOG_NONE){
			fog_result = weatherSysFogFade(&sys_w->fogFade);
		}else{
			fog_result = 1;
		}

		alpha_result = WeatherMoveMain( &sys_w->alpha );
		WeatherBGAlphaDef(sys_w->alpha.x, 16 - sys_w->alpha.x);
		
		// タイミングが最小になったらメインへ
		if((fog_result == 1) && (alpha_result == TRUE)){		// フェードリザルトが完了ならば終了へ
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		if(sys_work->fog_use != WEATHER_FOG_NONE){
			SetFogData(sys_w->fogFade.Fog, FOG_SYS_FLAG, FALSE, 0,0,0);	// フォグをオフ
		}
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気フラッシュ
 *
 *	@param	tcb		タスクワーク
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void contWeatherFlash(TCB_PTR tcb, void* work)
{
	WEATHER_SYS_WORK* sys_work = (WEATHER_SYS_WORK*)work;
	WEATHER_FLASH_WORK* sys_w;	// システムワーク
	WEATHER_SYS_CONTROL* sys_cont = sys_work->pWSysCont;
	FIELDSYS_WORK* fsys = sys_cont->fsys;
	sys_w = (WEATHER_FLASH_WORK*)sys_work->work;	// ワークポインタセット
	
	// シーケンスチェック
	switch(sys_work->Sequence){
	case WEATHER_SEQ_INIT:		// 初期化処理
		// フラッシュ
		drawWeatherCircleInit( &sys_w->circle, fsys->fldmap->hblanksys );
		drawWeatherCircleStart( &sys_w->circle, WEATHER_FLASH_END_R, WEATHER_FLASH_START_R, WEATHER_FLASH_CX, WEATHER_FLASH_CY, WEATHER_FLASH_SYNC );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_FADEIN;
		break;
	case WEATHER_SEQ_FADEIN:	// フェードイン
		if( drawWeatherCircleMain( &sys_w->circle ) == TRUE ){	

			// BG表示
			GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );


			// Hブランク処理破棄
			drawWeatherCircleEndReq( &sys_w->circle );
			
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_MAIN;	
		}
		break;

	case WEATHER_SEQ_NO_FADE:
		// BG表示
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
		
		// シーケンス変更
		sys_work->Sequence = WEATHER_SEQ_MAIN;
		break;

	case WEATHER_SEQ_MAIN:		// メイン
		// 終了チェック
		if(sys_work->ContFlag == WEATHER_SYS_END){
			drawWeatherCircleInit( &sys_w->circle, fsys->fldmap->hblanksys );
			drawWeatherCircleStart( &sys_w->circle, WEATHER_FLASH_START_R, WEATHER_FLASH_END_R, WEATHER_FLASH_CX, WEATHER_FLASH_CY, WEATHER_FLASH_SYNC );

			sys_work->Sequence = WEATHER_SEQ_FADEOUT;		// 正常終了
		}
		break;
		
	case WEATHER_SEQ_FADEOUT:	// フェードアウト

		// 毎フレームOFFしていることになるが、
		// こうしないと上の関数でHブランク設定する瞬間変なものが出てしまう
		// BGOFF
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
		

		if( drawWeatherCircleMain( &sys_w->circle ) == TRUE ){	
			// シーケンス変更
			sys_work->Sequence = WEATHER_SEQ_DEST;
		}
		break;

	case WEATHER_SEQ_DEST:		// タスク破棄
		drawWeatherCircleEnd( &sys_w->circle );
		{
			WEATHER_SYS_DATA* p_wsd = sys_work->pWSD;
			stopWeatherWork_local(p_wsd);
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループするサウンド再生
 *
 *	@param	p_work
 *	@param	snd_no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void WeatherLoopSndPlay( WEATHER_SYS_WORK* p_work, int snd_no )
{
	// もうなってるよ！
	GF_ASSERT( p_work->snd_play == FALSE );
	p_work->snd_play = TRUE;
	p_work->snd_no = snd_no;

	Snd_SePlay( snd_no );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生SE停止処理
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void WeatherLoopSndStop( WEATHER_SYS_WORK* p_work )
{
	Snd_SeStopBySeqNo( p_work->snd_no, WEATHER_SND_FADE_OUT_SYNC );
	p_work->snd_play = FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	circle計算
 *
 *	@param	p_circle	circleワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircle( WEATHER_CIRCLE_WORK* p_circle )
{
	int i;			// ループ用
	int st;			// ウィンドウ開始点
	int ed;			// ウィンドウ終了点
	u16* p_start_buff;
	u16* p_end_buff;

	// 開始位置格納先
	p_start_buff = LASTER_GetWriteBuff( p_circle->p_laster[0] );
	p_end_buff = LASTER_GetWriteBuff( p_circle->p_laster[1] );

	// 半径が画面内にあるときは
	// 中心まで幅を求めたら下半分はコピーするようにする
	for(i=0;i < 192;i++){
		if(i <= p_circle->y){		// 半径までは普通の求める
			CalcWeatherCircleSub(p_circle->r.x, p_circle->x, p_circle->y, i, &st, &ed);
		}else{
			if(i <= (p_circle->y*2)){		// 半径から半径の２倍までは,コピー
				st = p_start_buff[(p_circle->y*2)-i];
				ed = p_end_buff[(p_circle->y*2)-i];
			}else{				// その他は普通に求める
				CalcWeatherCircleSub(p_circle->r.x, p_circle->x, p_circle->y, i, &st, &ed);
			}
		}
		
		p_start_buff[i] = st;
		p_end_buff[i] = ed;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	円の幅計算
 *
 *	@param	c_r		半径
 *	@param	c_x		中心ｘ座標
 *	@param	c_y		中心ｙ座標
 *	@param	n_h		現在の高さ
 *	@param	st		横開始点格納先
 *	@param	ed		横終了点格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircleSub( fx32 c_r, int c_x, int c_y, int n_h, int* st, int* ed )
{
	fx32 r;			// 半径
	fx32 height;	// 高さ
	fx32 width;		// 幅

	r = c_r;

	height = n_h - c_y;
	if(height < 0){
		height = -height;
	}
	
	if(height >= r){
		*st = 0;
		*ed = 0;
	}else{
		// 半径から幅を求める
		height <<= FX32_SHIFT;
		width = FX_Sqrt(FX_Mul(r,r) - FX_Mul(height,height));
		width >>= FX32_SHIFT;

		// ウィンドウの開始点を設定
		*st = c_x - width;
		if(*st < 0){
			*st = 0;
		}
		*ed = *st + (width*2);
		if(*ed > 255){
			*ed = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	天気　円描画システム
 *	
 *	@param	p_circle		ワーク
 *	@param	p_fldhblksys	Hブランクシステム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleInit( WEATHER_CIRCLE_WORK* p_circle, FIELD_HBLANK_SYS* p_fldhblksys )
{
	int i;
	
	// ワーク初期化
	// Hブランクタスク
	// Vブランクタスク登録
	memset( p_circle, 0, sizeof(WEATHER_CIRCLE_WORK) );	

	p_circle->p_laster[0] = LASTER_Init( USE_HEAPID, p_circle->wnd_data[0], p_circle->wnd_data[1] );
	p_circle->p_laster[1] = LASTER_Init( USE_HEAPID, p_circle->wnd_data[2], p_circle->wnd_data[3] );
	for( i=0; i<192; i++ ){
		p_circle->wnd_data[2][i] = 255;
		p_circle->wnd_data[3][i] = 255;
	}

/*	
	// 背景黒
	{
		u16 color = 0;
		GX_LoadBGPltt( &color, 0, 32 );
	}
//*/	

	// 画面に何も出ないようにVBlank期間中にHブランク関数を登録する
	p_circle->p_fldhblksys = p_fldhblksys;
	VWaitTCB_Add( drawWeatherCircleInitHblankTcb, p_circle, WEATHER_TCB_CIRCLEINIT_PRI );
	
	p_circle->vblank_tcb = VWaitTCB_Add( drawWeatherCircleVblankCall, p_circle, WEATHER_CIRCLE_VBLANKTCB_PRI );
	
	p_circle->status = WEATHER_CIRCLE_STATUS_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	円枠終了
 *
 *	@param	p_circle	円ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEnd( WEATHER_CIRCLE_WORK* p_circle )
{
	int visi = GX_GetVisibleWnd();
	// ウィンドウ破棄
	GX_SetVisibleWnd( visi & (~GX_WNDMASK_W1) );
	
	// hブランク破棄
	FLDHBLANK_OBJ_Delete( p_circle->p_hblank );
	// Vブランク
	TCB_Delete( p_circle->vblank_tcb );

	LASTER_Delete( p_circle->p_laster[0] );
	LASTER_Delete( p_circle->p_laster[1] );

	memset( p_circle, 0, sizeof(WEATHER_CIRCLE_WORK) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｴﾌｪｸﾄ開始
 *
 *	@param	p_circle	円ワーク
 *	@param	s_r			開始半径
 *	@param	e_r			終了半径
 *	@param	c_x			中心ｘ座標
 *	@param	c_y			中心ｙ座標
 *	@param	sync		シンク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleStart( WEATHER_CIRCLE_WORK* p_circle, fx32 s_r, fx32 e_r, int c_x, int c_y, int sync )
{
	WeatherMoveReqFx( &p_circle->r, s_r, e_r, sync );
	p_circle->x = c_x;
	p_circle->y = c_y;
	p_circle->status = WEATHER_CIRCLE_STATUS_DO;

	CalcWeatherCircle( p_circle );
}

//----------------------------------------------------------------------------
/**
 *	@brief	円ワークメイン
 *
 *	@param	p_circle	円ワーク
 *
 *	@retval	TRUE	終了	
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL drawWeatherCircleMain( WEATHER_CIRCLE_WORK* p_circle )
{
	BOOL result;

	if( p_circle->status == WEATHER_CIRCLE_STATUS_INIT ){

		// 終わっているので、参照先を書き込み先に
		// コピーを繰り返す
		CalcWeatherCircleCopyBuff( p_circle );

		return TRUE;
	}
	
	result = WeatherMoveMainFx( &p_circle->r );
	CalcWeatherCircle( p_circle );

	if( result == TRUE ){
		p_circle->status = WEATHER_CIRCLE_STATUS_INIT;
	}

	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク期間コールバック関数
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleHblankCall( FIELD_HBLANK_OBJ* p_hbw, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	const u16* cp_buff[2];
	int count;
	int i;
	
	count = GX_GetVCount();
	
	for( i=0; i<2; i++ ){
		cp_buff[i] = LASTER_GetReadBuff( p_circle->p_laster[i] );
	}
	
	if( count < 192 ){
		count++;	// 次の高さのデータを設定
		if( count >= 192 ){
			count -= 192;
		}
		// BG1面のH方向スクロール設定
		if( GX_IsHBlank() ){
			G2_SetWnd1Position( cp_buff[ 0 ][ count ], 0, cp_buff[ 1 ][ count ], 192 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Vブランクコールバック関数
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleVblankCall( TCB_PTR tcb, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	int i;
	
	for( i=0; i<2; i++ ){
		LASTER_VBlank( p_circle->p_laster[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlank期間中にウィンドウでの円描画処理を破棄する
 *
 *	@param	p_circle	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEndReq( WEATHER_CIRCLE_WORK* p_circle )
{
	VWaitTCB_Add( drawWeatherCircleEndVblank, p_circle, WEATHER_TCB_CIRCLEEND_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	VBlank期間中にウィンドウでの円描画処理を破棄する
 *
 *	@param	tcb		TCBワーク
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleEndVblank( TCB_PTR tcb, void* p_work )
{
	drawWeatherCircleEnd( p_work );

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	circleが閉じたり開くアニメ終了後は、ダブルバッファの書き込み先に
 *	　参照先のデータをコピーするための関数
 *
 *	@param	p_circle	円ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void CalcWeatherCircleCopyBuff( WEATHER_CIRCLE_WORK* p_circle )
{
	const u16* cp_read;
	u16* p_write;
	int i;
	
	for( i=0; i<2; i++ ){

		cp_read = LASTER_GetReadBuff( p_circle->p_laster[i] );
		p_write = LASTER_GetWriteBuff( p_circle->p_laster[i] );
		memcpy( p_write, cp_read, sizeof(u16) * 192 );
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク割り込みコールバック関数を登録
 *
 *	@param	tcb			TCBワーク
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void drawWeatherCircleInitHblankTcb( TCB_PTR tcb, void* p_work )
{
	WEATHER_CIRCLE_WORK* p_circle = p_work;
	GXWndPlane outside = G2_GetWndOutsidePlane();
	int visi = GX_GetVisibleWnd();

	// ウィンドウ設定
	G2_SetWnd1InsidePlane( WEATHER_FLASH_WND_MSK, TRUE );
//	G2_SetWndOutsidePlane( outside.planeMask | WEATHER_FLASH_OUTSIDE_WND_MSK, outside.effect );
	G2_SetWndOutsidePlane( WEATHER_FLASH_OUTSIDE_WND_MSK, outside.effect );
	G2_SetWnd1Position( 0,0,255,192 );
	GX_SetVisibleWnd( visi | GX_WNDMASK_W1 );

	p_circle->p_hblank = FLDHBLANK_OBJ_Add( p_circle->p_fldhblksys, drawWeatherCircleHblankCall, p_circle );

	TCB_Delete( tcb );
}

