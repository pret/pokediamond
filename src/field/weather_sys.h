//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys.h
 *@brief	お天気システム
 *@author	tomoya takahashi
 *@data		2005.04.25
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#ifndef __WEATHER_SYS_H__
#define	__WEATHER_SYS_H__

#include "include/field/weather_no.h"
#include "field_common.h"
#include "weather_sys_def.h"

#undef	GLOBAL
#ifdef	__WEATHER_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



//-----------------------------------------------------------------------------
/**
 *
 *					天気管理システム
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	天気が使用するヒープの作成
//=====================================
GLOBAL void WEATHER_CreateHeap( u32 heapid );
GLOBAL void WEATHER_DeleteHeap( void );

//-------------------------------------
// 天気管理システム大本操作関数
//=====================================
GLOBAL WEATHER_MANAGER_PTR WEATHER_Init( FIELDSYS_WORK * fsys );	// 初期化(最初に１回)
GLOBAL void WEATHER_Delete( WEATHER_MANAGER_PTR pWes );				// 破棄（最後に１回）

//-------------------------------------
// 天気	変更
//=====================================
GLOBAL void WEATHER_Set( WEATHER_MANAGER_PTR pWes, int no );		// 天気設定　直ちに指定した天気になります。
GLOBAL BOOL WEATHER_ChengeReq( WEATHER_MANAGER_PTR pWes, int no );	// 天気変更リクエスト　今までの天気をフェードアウトさせ、徐々に指定した天気になります。
GLOBAL BOOL WEATHER_ChengeReqWithLast( WEATHER_MANAGER_PTR pWes, int no );	// 天気変更リクエスト　今までの天気をフェードアウトさせつつ、徐々に指定した天気になります。
GLOBAL u32 WEATHER_GetNow( WEATHER_MANAGER_PTR pWes );





//-----------------------------------------------------------------------------
/**
 *
 *				天気システム
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					定数宣言
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	天気管理関数外部コントロール	(cont)
//=====================================
enum{
	WEATHER_SYS_INIT=0,			// 初期化(キャラクタファイルなどの読み込みを行っています。)
	WEATHER_SYS_INIT_DIV,		// 分割初期化（キャラクタファイルなどの読み込みを複数シンクを使用して処理します。）
	WEATHER_SYS_START,			// 正常開始（フェードしながらはじまる）
	WEATHER_SYS_START_NOFADE,	// フェード無し開始
	WEATHER_SYS_START_WITHFOG,	// フォグを残したままフェード開始
	WEATHER_SYS_END,			// 正常終了(フェードして終わる)
	WEATHER_SYS_END_NOFADE,		// フェード無し終了
	WEATHER_SYS_END_NOFOG,		// フォグを残したままフェード終了
	WEATHER_SYS_DEST			// 破棄(管理タスクを終了させ、読み込んだファイルを破棄します。)
};

//-------------------------------------
//	MoveFlag用定数
//		今の天気コントロール状態
//=====================================
enum{
	WEATHER_SYS_MOVE_NONE,		// 動いていない
	WEATHER_SYS_MOVE_INIT,		// 初期化中
	WEATHER_SYS_MOVE_READY,		// 開始待ち
	WEATHER_SYS_MOVE_DO,		// 実行中
};


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
GLOBAL WEATHER_CONT_PTR InitWeatherSys(FIELDSYS_WORK * fsys);	// 初期化(最初に１回)
GLOBAL void DestWeatherSys(WEATHER_CONT_PTR* pWes);						// 破棄（最後に１回）
GLOBAL BOOL ControlWeatherSys(WEATHER_CONT_PTR Wes, int cont, int no);	// 天気コントロール関数
GLOBAL int CheckMoveWeatherSys(WEATHER_CONT_PTR Wes, int no);			// 天気がどんな常態かチェック


#undef	GLOBAL
#endif

