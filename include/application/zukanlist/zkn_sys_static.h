//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys_static.h
 *	@brief		図鑑システムの内部公開データ	(図鑑のシステム限定でinclude出来る)
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SYS_STATIC_H__
#define __ZKN_SYS_STATIC_H__

#include "include/gflib/touchpanel.h"

// データ関係
#include "include/application/zukanlist/zkn_glbdata.h"


// 描画関係
#include "include/application/zukanlist/zkn_drawglb.h"


// 処理分岐関係
#include "include/application/zukanlist/zkn_proc_sys.h"
#include "include/application/zukanlist/zkn_event.h"

#undef GLOBAL
#ifdef	__ZKN_SYS_STATIC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	アプリケーション種類
//=====================================
//メイン
enum {
	ZKN_SYS_APLMAIN_POKELIST,		// ポケモンリスト
	ZKN_SYS_APLMAIN_SORTSEARCH,		// 検索ソート
	ZKN_SYS_APLMAIN_ZUKAN,			// 図鑑画面
	ZKN_SYS_APLMAIN_ZUKAN_GRA,		// 図鑑画面グラフィックバージョン
	ZKN_SYS_APLMAIN_ZUKAN_TEXT,		// 図鑑画面言語バージョン
	ZKN_SYS_APLMAIN_ZUKAN_COMMON,	// 図鑑画面共通
	ZKN_SYS_APLMAIN_RANGE,			// 分布図
	ZKN_SYS_APLMAIN_SOUND,			// 泣き声
	ZKN_SYS_APLMAIN_BIG,			// 大きさ比べ	 高さ
	ZKN_SYS_APLMAIN_BIG_WEIGHT,		// 大きさ比べ    重さ
	ZKN_SYS_APLMAIN_NUM,			// アプリケーション数又はアプリケーション無し
} ;
// サブ
enum {
	ZKN_SYS_APLSUB_POKELIST,				// ポケモンリスト
	ZKN_SYS_APLSUB_SORTSEARCH,				// 検索ソート
	ZKN_SYS_APLSUB_ZUKAN,					// 図鑑画面
	ZKN_SYS_APLSUB_ZUKAN_COMMON,			// 図鑑画面共通
	ZKN_SYS_APLSUB_RANGE,					// 分布図
	ZKN_SYS_APLSUB_SOUND,					// 泣き声
	ZKN_SYS_APLSUB_BIG,						// 大きさ比べ    
	ZKN_SYS_APLSUB_ZUKAN_GRA,				// 図鑑画面グラフィックバージョン


#ifdef PM_DEBUG
	ZKN_SYS_APLSUB_HEIGHT_DEBUG,			// 高さ比べDEBUGアプリ
#endif 
	
	ZKN_SYS_APLSUB_NUM,						// アプリケーション数又はアプリケーション無し
} ;



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	各アプリケーションデータ構造体
//=====================================
typedef struct {
	void* p_glb_data;								// グローバルデータ
	void* p_glb_draw;								// グローバルデータ
	ZKN_PROC_DO_FUNC	do_func[ZKN_PROC_FUNC_NUM];// 各処理関数
	ZKN_PROC_DRAW_FUNC	draw_func[ZKN_PROC_FUNC_NUM];// 各処理関数
	ZKN_EVENT_DATA*		p_event_data;			// イベントデータ
	int	event_num;									// イベント数
} ZKN_APL_DATA;

typedef struct _ZKN_SYS* ZKN_SYS_PTR;
typedef const struct _ZKN_SYS* CONST_ZKN_SYS_PTR;
//-------------------------------------
//	アプリケーションデータ作成関数
//=====================================
typedef void (*ZKN_APL_DATA_MAKE_FUNC)( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap );
typedef void (*ZKN_APL_DATA_DELETE_FUNC)( ZKN_APL_DATA* p_data );



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// グローバルデータアクセス関数
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysMain( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysSub( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysMainCommon( ZKN_SYS_PTR zkn );
GLOBAL ZKN_PROC_SYS_PTR	ZKN_SYS_GetProcSysSubCommon( ZKN_SYS_PTR zkn );

GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMain( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSub( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysMainCommon( ZKN_SYS_PTR zkn );
GLOBAL ZKN_EVENT_SYS_PTR ZKN_SYS_GetEventSysSubCommon( ZKN_SYS_PTR zkn );

GLOBAL int* ZKN_SYS_GetEventKeyPtrMain( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrSub( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrMainCommon( ZKN_SYS_PTR zkn );
GLOBAL int* ZKN_SYS_GetEventKeyPtrSubCommon( ZKN_SYS_PTR zkn );

GLOBAL BOOL* ZKN_SYS_GetZknDeleteFlag( ZKN_SYS_PTR zkn );

GLOBAL ZKN_GLB_DATA* ZKN_SYS_GetGlbData( ZKN_SYS_PTR zkn );
GLOBAL ZKN_GLB_DRAWDATA* ZKN_SYS_GetGlbDrawData( ZKN_SYS_PTR zkn );

GLOBAL ZKN_APL_DATA* ZKN_GetAplDataMain( ZKN_SYS_PTR zkn, int apl_no );
GLOBAL ZKN_APL_DATA* ZKN_GetAplDataSub( ZKN_SYS_PTR zkn, int apl_no );


//-----------------------------------------------------------------------------
//
/**
 *		いろんなアプリケーションが共通して使用できるもの
 */
//-----------------------------------------------------------------------------
#define ZKN_UTIL_BUTTON_PUSH_NONE	(BMN_EVENT_SLIDEOUT + 1)
enum{
	ZKN_UTIL_BUTTON_FRAME_NONE,		// 無し
	ZKN_UTIL_BUTTON_FRAME_PUSH1,	// プッシュアニメ１フレーム目
	ZKN_UTIL_BUTTON_FRAME_PUSH2,	// プッシュアニメ２フレーム目
	ZKN_UTIL_BUTTON_FRAME_SELECT,	// 選択
};
GLOBAL void ZKN_UTIL_ButtonMove( CLACT_WORK_PTR act, int button_event );
GLOBAL void ZKN_UTIL_ButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y );
GLOBAL void ZKN_UTIL_ButtonFontMove_Col( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

GLOBAL void ZKN_UTIL_HitTblDataSet( TP_HIT_TBL* p_tbl, int top, int bottom, int left, int right );

//-------------------------------------
//	BGスクリーンShutterフェード構造体
//=====================================
typedef struct {
	GF_BGL_INI* p_bg;			// BGデータ
	NNSG2dScreenData* p_scrn;	// スクリーンデータ
	int frm;					// フレーム面

	int top_start;			// 上の開始Yキャラクタ位置
	int bottom_start;		// 下の開始Yキャラクタ位置
	int top_dis;			// 上の動作距離
	int bottom_dis;			// 下の動作距離
	
	int move_count;			// カウンタ
	int move_count_max;		// 最大数
} ZKN_UTIL_BGSHTTER_DADE;
GLOBAL void ZKN_UTIL_BgShutterFadeInit( ZKN_UTIL_BGSHTTER_DADE* p_data, GF_BGL_INI* p_bg, int frm, NNSG2dScreenData* p_scrn, int top_cs, int top_ce, int bottom_cs, int bottom_ce, int count_max );
GLOBAL BOOL ZKN_UTIL_BgShutterFade( ZKN_UTIL_BGSHTTER_DADE* p_data );


//-------------------------------------
//	ポケモン名リスト作成関数郡
//=====================================
// 文字列OAM
#define ZKN_POKELIST_POKENAME_BMP_SIZE_CX	( 15 )	// 書き込み領域のビットマップサイズ
#define ZKN_POKELIST_POKENAME_BMP_SIZE_CY	( 2 )	// 書き込み領域のビットマップサイズ
#define ZKN_POKELIST_POKENAME_BMP_SIZE_X	( 128 )	// 書き込み領域のビットマップサイズ
#define ZKN_POKELIST_POKENAME_BMP_SIZE_Y	( 16 )	// 書き込み領域のビットマップサイズ
#define ZKN_POKELIST_POKENAME_NO_NUM		( 4 )	// STRBUFの領域取得数
#define ZKN_POKELIST_POKENAME_NO_KETA		( 3 )	// 数字の桁
#define ZKN_POKELIST_POKENAME_MAT_Y			( 0 )
#define ZKN_POKELIST_POKENAME_NO_MAT_X		( 18 )
#define ZKN_POKELIST_POKENAME_NAME_MAT_X	( 52 )

// アイコン定数
#define ZKN_POKELIST_ICON_X_OFS		( -54 * FX32_ONE )	// 今選択されているポケモンテーブルのX座標からの距離

GLOBAL void ZKN_UTIL_PokeListPokeNameBmpMake( GF_BGL_BMPWIN* p_bmp, int num, int monsno, int heap );
GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int mons_no );
GLOBAL void ZKN_UTIL_PokeListPokeNameMakeGlb( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_GLB_DATA* cp_glb, int heap, int poke_tbl_no, fx32 x, fx32 y );
GLOBAL void ZKN_UTIL_PokeListPokeNameGlbMatrixSet(  ZKN_GLB_DRAWDATA* p_drawglb, int x, int y );

GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Zenkoku( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no );
GLOBAL GF_BGL_BMPWIN* ZKN_UTIL_PokeListPokeNameTblBmpMake_Shinou( ZKN_FONTOAM_SYS_PTR fontoam_sys, int heap, int mons_no );
GLOBAL void ZKN_UTIL_PokeListPokeNameGlbMatrixSet_Minute(  ZKN_POKELIST_DATA_OAM_DATA* p_data, int x, int y );

//-------------------------------------
//	ポケモングラフィック設定関数
//=====================================
GLOBAL void  ZKN_UTIL_PokemonGraphicSet( ZKN_GLB_DRAWDATA* p_draw, ZKN_GLB_DATA* p_glb, int mons_no, int dir, int x, int y );

GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_FS_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int mons_no, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Anoon_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Siiusi_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Siidorugo_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Minomutti_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Minomesu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );
GLOBAL u32 ZKN_UTIL_PokemonGraphicSet_Deokisisu_Idx( ZKN_GLB_DRAWDATA* p_draw, const ZKN_GLB_DATA* cp_glb, int dir, int x, int y, int count, int idx );



//-------------------------------------
//	ポケモン図鑑メッセージﾃﾞｰﾀSTRBUF取得
//=====================================
GLOBAL STRBUF* ZKN_UTIL_ZknGmmGet( int data_idx, int heap );


#undef	GLOBAL
#endif		// __ZKN_SYS_STATIC_H__

