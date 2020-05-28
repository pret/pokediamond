//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_demo.h
 *	@brief		フィールド上での簡単なデモ処理
 *	@author		tomoya takahashi	
 *	@data		2006.04.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_DEMO_H__
#define __FIELD_DEMO_H__

#include "fieldmap_func.h"

#undef GLOBAL
#ifdef	__FIELD_DEMO_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *		フィールドマップタスク動作
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	伝説ポケモン出現
//	Start		開始
//	EndCheck	終了待ち[TRUE] 
//	End			終了（破棄）
//=====================================
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_LegendPokeApp_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_LegendPokeApp_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLDMAP_DEMO_LegendPokeApp_EndCheck( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	黒いワッカの放出
//	Start		開始
//	End			終了（破棄）
//=====================================
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_BlackRing_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_BlackRing_End( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	ありの卵
//	Start		開始
//	End			終了（破棄）
//=====================================
enum{
	FLDMAP_DEMO_ANTEGG_CUT00,
	FLDMAP_DEMO_ANTEGG_CUT01,
	FLDMAP_DEMO_ANTEGG_CUT02,
};
GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_AntEgg_Start( FIELDSYS_WORK* fsys, u32 cut );
GLOBAL void FLDMAP_DEMO_AntEgg_End( FLDMAPFUNC_WORK* p_demo );

//-------------------------------------
//	銀河放出
//	Start		開始
//	GetState	拡大終了チェック[FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT]
//	EndReq		終了リクエスト
//	GetState	終了チェック[FLDMAP_DEMO_GINGA_SEQ_END]
//	End			終了（破棄）
//=====================================
enum{
	FLDMAP_DEMO_GINGA_SEQ_START,		// エフェクト開始
	FLDMAP_DEMO_GINGA_SEQ_SCALEUP,		// 銀河拡大
	FLDMAP_DEMO_GINGA_SEQ_ENDREQ_WAIT,	// 終了リクエスト待ち
	FLDMAP_DEMO_GINGA_SEQ_ENDREQ,		// 終了エフェクト開始
	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF_WAIT,	// 銀河縮小
	FLDMAP_DEMO_GINGA_SEQ_SCALEDOWN_DARKOFF,	// 銀河縮小＋明るく
	FLDMAP_DEMO_GINGA_SEQ_END			// 終了
};

GLOBAL FLDMAPFUNC_WORK* FLDMAP_DEMO_Ginga_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_DEMO_Ginga_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL void FLDMAP_DEMO_Ginga_EndReq( FLDMAPFUNC_WORK* p_demo );
GLOBAL u32 FLDMAP_DEMO_Ginga_GetState( FLDMAPFUNC_WORK* p_demo );


//-----------------------------------------------------------------------------
/**
 *
 *	画面揺らしイベント
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FLD_MAP_DEMO_ZishinEventCall(GMEVENT_CONTROL *event);
GLOBAL void FLD_MAP_DEMO_MioZishinEventCall(GMEVENT_CONTROL *event);


//-----------------------------------------------------------------------------
/**
 *
 *			下は、個々のｴﾌｪｸﾄ単体
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		画面揺らし
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	画面揺らしワーク
//=====================================
typedef struct _FLD_DEMO_SHAKE_SCRN FLD_DEMO_SHAKE_SCRN;

GLOBAL FLD_DEMO_SHAKE_SCRN* FLD_DEMO_ShakeScrn_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_ShakeScrn_Free( FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_Start( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width, fx32 height, u32 one_sync, u32 count, GF_CAMERA_PTR copy_camera );
GLOBAL BOOL FLD_DEMO_ShakeScrn_EndCheck( FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_Main( FLD_DEMO_SHAKE_SCRN* p_data );

GLOBAL u32 FLD_DEMO_ShakeScrn_GetNowCount( const FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL fx32 FLD_DEMO_ShakeScrn_GetNowShakeWidth( const FLD_DEMO_SHAKE_SCRN* p_data );
GLOBAL void FLD_DEMO_ShakeScrn_SetNowShakeWidth( FLD_DEMO_SHAKE_SCRN* p_data, fx32 width );


//-----------------------------------------------------------------------------
/**
 *		フラッシュ		
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	フラッシュワーク
//=====================================
typedef struct _FLD_DEMO_FLASH FLD_DEMO_FLASH;

GLOBAL FLD_DEMO_FLASH* FLD_DEMO_Flash_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_Flash_Free( FLD_DEMO_FLASH* p_data );
GLOBAL void FLD_DEMO_Flash_Start( FLD_DEMO_FLASH* p_data, u32 alphamax, u32 out_sync, u32 in_sync );
GLOBAL BOOL FLD_DEMO_Flash_EndCheck( FLD_DEMO_FLASH* p_data );
GLOBAL void FLD_DEMO_Flash_Main( FLD_DEMO_FLASH* p_data );
GLOBAL int FLD_DEMO_Flash_GetAlpha( const FLD_DEMO_FLASH* cp_data );



//-----------------------------------------------------------------------------
/**
 *		デモ銀河		コンテ⑥
 *
 *		銀河デモを呼ぶ前にサブ面の破棄が行われている必要があります
*/
//-----------------------------------------------------------------------------
// システム全体の初期化破棄タスク
#define FLD_DEMO_GINGA_DRAWSYSTEM_INIT_TCB_PRI	( 1024 )

// 描画システムのセットアップ用TCB　優先順位	
#define FLD_DEMO_GINGA_MOTIONBL_SETUP_TCB_PRI	( 1023 )	// モーションブラー
#define FLD_DEMO_GINGA_DRAWDATA_SETUP_TCB_PRI	( 1024 )	// BG

// 現在の状態
enum{
	FLD_DEMO_GINGA_MOTIONBL_INIT,	// 初期化中
	FLD_DEMO_GINGA_MOTIONBL_SCALEUP,	// 拡大中
	FLD_DEMO_GINGA_MOTIONBL_REQWAIT,	// 縮小リクエスト待ち
	FLD_DEMO_GINGA_MOTIONBL_SCALEDOWN,	// 縮小中
	FLD_DEMO_GINGA_MOTIONBL_DELETE,	// 破棄処理中
	FLD_DEMO_GINGA_MOTIONBL_END		// 全作業終了 or 初期化前
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
typedef struct _FLD_DEMO_GINGA FLD_DEMO_GINGA;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL FLD_DEMO_GINGA* FLD_DEMO_GINGA_Alloc( FIELDSYS_WORK * fsys );
GLOBAL void FLD_DEMO_GINGA_Free( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_Init( FLD_DEMO_GINGA* p_data, fx32 x, fx32 y, fx32 z );
GLOBAL void FLD_DEMO_GINGA_Main( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_EndReq( FLD_DEMO_GINGA* p_data );
GLOBAL u32 FLD_DEMO_GINGA_GetState( const FLD_DEMO_GINGA* cp_data );
GLOBAL void FLD_DEMO_GINGA_Draw( FLD_DEMO_GINGA* p_data );
GLOBAL void FLD_DEMO_GINGA_SetMotionBlNum( FLD_DEMO_GINGA* p_data, int a, int b );



//-----------------------------------------------------------------------------
/**
 *
 *		イア・エア登場		コンテ①
 *
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	イアエア登場　ワーク
//=====================================
typedef struct _FLD_DEMO_LEGENDPOKE_APP FLD_DEMO_LEGENDPOKE_APP;

GLOBAL FLD_DEMO_LEGENDPOKE_APP* FLD_DEMO_LegendPokeApp_Alloc( u32 heapID, FIELDSYS_WORK * fsys );
GLOBAL void FLD_DEMO_LegendPokeApp_Free( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Start( FLD_DEMO_LEGENDPOKE_APP* p_data, u32 legendpoke_id );
GLOBAL BOOL FLD_DEMO_LegendPokeApp_EndCheck( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Main( FLD_DEMO_LEGENDPOKE_APP* p_data );
GLOBAL void FLD_DEMO_LegendPokeApp_Draw( FLD_DEMO_LEGENDPOKE_APP* p_data );


//-----------------------------------------------------------------------------
/**
 *
 *		イア・エアを中心からわっか出現		コンテ③
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イア・エアを中心にわっか出現　ワーク
//=====================================
typedef struct _FLD_DEMO_BLACK_RING FLD_DEMO_BLACK_RING;

GLOBAL FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_BlackRing_Free( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_Start( FLD_DEMO_BLACK_RING* p_data, u16 grid_x, u16 grid_y, u16 grid_z );
GLOBAL void FLD_DEMO_BlackRing_Main( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_Draw( FLD_DEMO_BLACK_RING* p_data );


//-----------------------------------------------------------------------------
/**
 *
 *		ありの卵を出す		コンテ③
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	ありの卵　ワーク
//=====================================
typedef struct _FLD_DEMO_ANTEGG FLD_DEMO_ANTEGG;

// 以下の４つの関数は、共通で使用する
GLOBAL FLD_DEMO_ANTEGG* FLD_DEMO_AntEgg_Cut_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_AntEgg_Cut_Free( FLD_DEMO_ANTEGG* p_data );
GLOBAL void FLD_DEMO_AntEgg_Cut_Main( FLD_DEMO_ANTEGG* p_data );
GLOBAL void FLD_DEMO_AntEgg_Cut_Draw( FLD_DEMO_ANTEGG* p_data );

// 開始関数だけ分けて使用する
//-------------------------------------
//	カット００
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut00_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	カット０１
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut01_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	カット０２
//=====================================
GLOBAL void FLD_DEMO_AntEgg_Cut02_Start( FLD_DEMO_ANTEGG* p_data, fx32 x, fx32 y, fx32 z );


//-----------------------------------------------------------------------------
/**
 *
 *		ありの卵の時の黒リング	コンテ③
 * 
 */
//-----------------------------------------------------------------------------
// 以下の４つの関数は、共通で使用する
GLOBAL FLD_DEMO_BLACK_RING* FLD_DEMO_BlackRing_AntEggCat_Alloc( u32 heapID );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Free( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Main( FLD_DEMO_BLACK_RING* p_data );
GLOBAL void FLD_DEMO_BlackRing_AntEggCat_Draw( FLD_DEMO_BLACK_RING* p_data );

// 開始関数だけ分けて使用する
//-------------------------------------
//	カット００
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat00_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	カット０１
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat01_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );

//-------------------------------------
//	カット０２
//=====================================
GLOBAL void FLD_DEMO_BlackRing_AntEggCat02_Start( FLD_DEMO_BLACK_RING* p_data, fx32 x, fx32 y, fx32 z );


//-----------------------------------------------------------------------------
/**
 * 
 *		フィールド全体を暗くする
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	状態定数	
//=====================================
enum{
	FLD_DEMO_DARKLIGHT_INIT,	// 初期化
	FLD_DEMO_DARKLIGHT_FADEOUT,	// 暗くなっています。
	FLD_DEMO_DARKLIGHT_ENDWAIT,	// 終了リクエスト待ち。
	FLD_DEMO_DARKLIGHT_FADEIN,	// 明るくなっています。
	FLD_DEMO_DARKLIGHT_END,		// 全工程終了
};

//-------------------------------------
//	明度の低いLIGHTをフィールド全体にかける
//=====================================
typedef struct _FLD_DEMO_DARKLIGHT FLD_DEMO_DARKLIGHT;

GLOBAL FLD_DEMO_DARKLIGHT* FLD_DEMO_DarkLight_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys );
GLOBAL void FLD_DEMO_DarkLight_Free( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL void FLD_DEMO_DarkLight_Start( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL void FLD_DEMO_DarkLight_Main( FLD_DEMO_DARKLIGHT* p_data );
GLOBAL u32 FLD_DEMO_DarkLight_GetState( const FLD_DEMO_DARKLIGHT* cp_data );
GLOBAL void FLD_DEMO_DarkLight_EndReq( FLD_DEMO_DARKLIGHT* p_data );

//-----------------------------------------------------------------------------
/**
 *
 *
 *		アリのタマゴ放出開始デモ
 *
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	アリの卵放出開始デモ
//=====================================
typedef struct _FLD_DEMO_ARITAMA_START FLD_DEMO_ARITAMA_START;

GLOBAL FLD_DEMO_ARITAMA_START* FLD_DEMO_AriTamaStart_Alloc( u32 heapID, FIELDSYS_WORK* p_fsys );
GLOBAL void FLD_DEMO_AriTamaStart_Free( FLD_DEMO_ARITAMA_START* p_data );
GLOBAL void FLD_DEMO_AriTamaStart_Start( FLD_DEMO_ARITAMA_START* p_data, u32 legendpoke_id );
GLOBAL BOOL FLD_DEMO_AriTamaStart_Main( FLD_DEMO_ARITAMA_START* p_data );
GLOBAL void FLD_DEMO_AriTamaStart_Draw( FLD_DEMO_ARITAMA_START* p_data );

#undef	GLOBAL
#endif		// __FIELD_DEMO_H__

