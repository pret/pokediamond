//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_textver.c
 *	@brief		図鑑言語バージョン
 *	@author		tomoya takahashi
 *	@data		2006.02.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"
#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/msgdata/msg_zkn_height.h"
#include "include/msgdata/msg_zkn_gram.h"
#include "include/msgdata/msg_zkn_comment_00.h"
#include "include/msgdata/msg_zkn_type.h"
#include "include/poketool/pokefoot.h"

#include "include/battle/battle_common.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_world_text_sys.h"

// エフェクトで座標をLinkさせるため、仕方なくインクルード
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_ZUKAN_TEXTVER_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_textver.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_ZUKANTEXTVER_EVENT_NUM ( 0 )	// イベント数
#define ZKN_ZUKANTEXTVER_OAM_BG_PRI	( 0 )
#define ZKN_ZUKANTEXTVER_OAM_SOFT_PRI	( 32 )

// BGブライトネスフェード面
#define ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )
#define ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

// 背景座標
#define ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_ZUKANTEXTVER_TEXT_FRAME_CX			( 0 )
#define ZKN_ZUKANTEXTVER_TEXT_FRAME_CY			( 16 )
#define ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CX		( 14 )
#define ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CY		( 8 )


// 文字列面
#define ZKN_ZUKANTEXTVER_NUM_STR		( 64 )	// バッファサイズ
#define ZKN_ZUKANTEXTVER_NUM_STRTEXT	( 256 )	// バッファサイズ

#define ZKN_ZUKANTEXTVER_FONT_COMMENT_X	( 8 )
#define ZKN_ZUKANTEXTVER_FONT_COMMENT_Y	( 136 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X ( 16 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_OFS_X ( 8 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_Y ( 116 )
#define ZKN_ZUKANTEXTVER_FONT_PAGE_PLACE ( 1 )	// 桁
#define ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_C_X	( 184 )
#define ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_Y	( 72 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNO_X	( 128 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNO_Y	( 96 )
#define ZKN_ZUKANTEXTVER_FONT_MONSNO_PLACE ( 3 )	// 桁
#define ZKN_ZUKNATEXTVER_FONT_MONSNAME_X	( 160 )
#define ZKN_ZUKNATEXTVER_FONT_MONSNAME_Y	( 96 )
#define ZKN_ZUKNATEXTVER_FONT_MONSTYPE_X_OFS ( 8 )
#define ZKN_ZUKNATEXTVER_FONT_MONSTYPE_Y	( 112 )
#define ZKN_ZUKNATEXTVER_FONT_POKEMON_X	( 200 )
#define ZKN_ZUKNATEXTVER_FONT_POKEMON_Y	( 112 )

//-------------------------------------
//	描画初期化シーケンス
//=====================================
enum
{
	ZKN_ZUKANTEXTVER_SEQINIT_ALLOC,
	ZKN_ZUKANTEXTVER_SEQINIT_LOAD,
	ZKN_ZUKANTEXTVER_SEQINIT_FADEIN,
	ZKN_ZUKANTEXTVER_SEQINIT_END,
};

//-------------------------------------
//	図鑑破棄シーケンス
//=====================================
enum{
	ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT,
	ZKN_ZUKANTEXTVER_SEQDELETE_RELEASE,
	ZKN_ZUKANTEXTVER_SEQDELETE_FREE,
	ZKN_ZUKANTEXTVER_SEQDELETE_END,
};

// ポケモンリスト座標
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_X	( ZKN_ZUKANTEXTVER_POKELIST_MAT_IX*FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKELIST_MAT_Y	( ZKN_ZUKANTEXTVER_POKELIST_MAT_IY*FX32_ONE )


// タイプ座標
#define ZKN_ZUKANTEXTVER_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_MAT_Y	( 72 * FX32_ONE )
// タイプアニメシーケンス
enum{
	ZKN_ZUKANTEXTVER_POKETYPE_NORMAL = 0,
};

// ～ポケモン座標
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_X	( -58 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_Y	( -8 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCX	( 16 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCY	( 2 )
#define ZKN_ZUKANTEXTVER_POKETYPE_TEXT_TBL_SEQ	( 0x11 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	int poke_gra_move_x;					// ポケグラ動作先
	int poke_gra_move_y;					// ポケグラ動作先

	// 図鑑コモンアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;
	int					fade_mode;			// フェードモード

	// 表示データ
	int zukan_type;		// 表示タイプ
	int zukan_page;		// ページ数
} ZKN_ZUKANTEXTVER_GLB;

//-------------------------------------
//	図鑑画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_ZUKANTEXTVER_DRAWGLB;

//-------------------------------------
//	図鑑画面　描画ワーク
//=====================================
typedef struct {
	// ～ポケモン
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	
	// ポケリストフェード用動作ワーク
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;
} ZKN_ZUKANTEXTVER_DRAW;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		アプリケーションデータ作成関係
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_GLB* MakeZukanTextverGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKANTEXTVER_DRAWGLB* MakeZukanTextverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanTextverEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanTextverGlb( ZKN_ZUKANTEXTVER_GLB* p_glb );
static void DeleteZukanTextverDrawGlb( ZKN_ZUKANTEXTVER_DRAWGLB* p_glb );
//static void DeleteZukanTextverEvent( ZKN_EVENT_DATA* p_event );


static int ZukanTextverEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanTextverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanTextverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanTextverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// フェードインアウト
static void ZknZukanTextverDefaultFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverDefaultFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out );
static void ZknZukanTextverChPokeListFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverChPokeListFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static void ZknZukanTextverChOtherFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanTextverChOtherFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanTextverSpritePokeGraPalFade( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

static void ZknZukanTextverOamFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static void ZknZukanTextverOamFadeDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw );

static void ZknZukanTextverPokeGraFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw, int move_x, int move_y, int sync );
static BOOL ZknZukanTextverPokeGraFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );
static void ZknZukanTextverPokeListFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static BOOL ZknZukanTextverPokeListFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );


// BG設定
static void ZknZukanTextverLoadResource( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverReleaseResource( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );
static void ZknZukanTextverSetUpBackGround( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanTextverSetUpFontBg( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverFontSetUpText( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang, int page );
static int ZknZukanTextverZukanNameGmmIDGet( int lang );
static void ZknZukanTextvereFontPokeName( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang );
static void ZknZukanTextvereFontPokeType( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang );

// ～ポケモン
static void ZknZukanTextverPokeTypeTextAdd( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverPokeTypeTextDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw );
static GF_BGL_BMPWIN* ZknZukanTextverPokeTypeTextBmpMake( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int mons_no, int heap );
static void ZknZukanTextverClactResLoad( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap );
static void ZknZukanTextverClactResDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

// ポケモンリスト
static void ZknZukanTextverPokeListDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap );
static void ZknZukanTextverPokeListDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

// ポケモングラフィック
static void ZknZukanTextverPokeGraDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb );
static void ZknZukanTextverPokeGraDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　アプリ作成
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	heap		使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKANTEXTVER_GLB*	p_glb;
	ZKN_ZUKANTEXTVER_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanTextverGlb( heap, zkn_sys );
	p_drawglb = MakeZukanTextverDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanTextverEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanTextverEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanTextverProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanTextverProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanTextverProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanTextverProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanTextverProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanTextverProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト	サブ画面　メニューアプリ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanTextverGlb( p_data->p_glb_data ); 
	DeleteZukanTextverDrawGlb( p_data->p_glb_draw );
//	DeleteZukanTextverEvent( p_data->p_event_data );
}

// アプリデータ外部変更関数
//----------------------------------------------------------------------------
/**
 *	@brief	フェードインアウトグラフィック座標設定
 *
 *	@param	p_data		グラフィックデータ
 *	@param	x			ｘ座標	
 *	@param	y			ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverPokeGraFadeOutSet( ZKN_APL_DATA* p_data, int x, int y )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

	p_glb->poke_gra_move_x = x;
	p_glb->poke_gra_move_y = y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑フェードモード設定
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	fade_mode	フェードモード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTextverFadeModeSet( ZKN_APL_DATA* p_data, int fade_mode )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

	p_glb->fade_mode = fade_mode;
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑言語ページ変更
 *
 *	@param	p_data	図鑑アプリ
 *
 *	@retval TRUE	変更した
 *	@retval	FALSE	変更しなかった
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanTexverPageAdd( ZKN_APL_DATA* p_data )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;

/*	
	p_glb->zukan_page = (p_glb->zukan_page + 1) % ZKN_WT_WORLD_TEXT_PAGE_NUM;

	return TRUE;
//*/


/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	// 全部2ページ目なし
	return FALSE;
#endif
/* アメリカ */
#if( PM_LANG == LANG_ENGLISH )
	// 全部2ページ目なし
	return FALSE;
#endif
/* フランス */
#if( PM_LANG == LANG_FRANCE )
	// 全部2ページ目なし
	return FALSE;
#endif
/* イタリア */
#if( PM_LANG == LANG_ITALY )
	// 全部2ページ目なし
	return FALSE;
#endif
/* ドイツ */
#if( PM_LANG == LANG_GERMANY )
	// 全部2ページ目なし
	return FALSE;
#endif
/* スペイン */
#if( PM_LANG == LANG_SPAIN )
	// 全部2ページ目なし
	return FALSE;
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑言語ページ設定
 *
 *	@param	p_data	図鑑アプリデータ
 *	@param	page	ページ	(0～1)
 *
 *	@retval	TRUE	変更した
 *	@retval	FALSE	変更しなかった
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanTexverPageSet( ZKN_APL_DATA* p_data, int page )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;
	BOOL ret = TRUE;

/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* アメリカ */
#if( PM_LANG == LANG_ENGLISH )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* フランス */
#if( PM_LANG == LANG_FRANCE )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* イタリア */
#if( PM_LANG == LANG_ITALY )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* ドイツ */
#if( PM_LANG == LANG_GERMANY )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif
/* スペイン */
#if( PM_LANG == LANG_SPAIN )
	// 2ページ目なし
	if( page == 1 ){
		page = 0;
		ret = FALSE;
	}
#endif

	p_glb->zukan_page = page;

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑言語国コード設定
 *
 *	@param	p_data	図鑑アプリ
 *	@param	lang	国コード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ZukanTexverTypeSet( ZKN_APL_DATA* p_data, int lang )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_data->p_glb_data;
	p_glb->zukan_type = lang;

/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
/* アメリカ */
#if( PM_LANG == LANG_ENGLISH )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
/* フランス */
#if( PM_LANG == LANG_FRANCE )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
/* イタリア */
#if( PM_LANG == LANG_ITALY )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
/* ドイツ */
#if( PM_LANG == LANG_GERMANY )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
/* スペイン */
#if( PM_LANG == LANG_SPAIN )
	// 全部2ページ目なし
	p_glb->zukan_page = 0;
#endif
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_GLB* MakeZukanTextverGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANTEXTVER_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANTEXTVER_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// 図鑑コモンアプリグローバルデータ
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	p_glb->cp_zukan_common_apl = p_apl;
	

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑	描画グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	描画グローバルデータ
 */
//-----------------------------------------------------------------------------
static ZKN_ZUKANTEXTVER_DRAWGLB* MakeZukanTextverDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKANTEXTVER_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKANTEXTVER_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKANTEXTVER_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeZukanTextverEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanTextverEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeRange( heap, &p_event_tbl[0], zkn_sys, ZKN_ZUKNA_EVENT_CHANGE_RANGE );

	return p_event_tbl;
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverGlb( ZKN_ZUKANTEXTVER_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　描画グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverDrawGlb( ZKN_ZUKANTEXTVER_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteZukanTextverEvent( ZKN_EVENT_DATA* p_event )
{

	GF_ASSERT( p_event );
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );//*/
}
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	図鑑アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZukanTextverEventDataNumGet( void )
{
	return ZKN_ZUKANTEXTVER_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[初期化]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[メイン]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKANTEXTVER_GLB* p_glb = p_glbdata;
	
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[破棄]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [初期化]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANTEXTVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANTEXTVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKANTEXTVER_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKANTEXTVER_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKANTEXTVER_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_LOAD:
		ZknZukanTextverLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			ZknZukanTextverChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			ZknZukanTextverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			ZknZukanTextverChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_FADEIN:

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			check = ZknZukanTextverChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			check = ZknZukanTextverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			check = ZknZukanTextverChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKANTEXTVER_SEQINIT_END:
		G2_BlendNone();
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [メイン]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [破棄]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKANTEXTVER_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKANTEXTVER_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT_INIT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			ZknZukanTextverChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			ZknZukanTextverDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			ZknZukanTextverChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_FADEOUT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKANTEXTVER_FADE_MODE_CHPOKELIST:	
			check = ZknZukanTextverChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_NORMAL:
			check = ZknZukanTextverDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKANTEXTVER_FADE_MODE_OTHER:
			check = ZknZukanTextverChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKANTEXTVER_SEQDELETE_RELEASE:
		ZknZukanTextverReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKANTEXTVER_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKANTEXTVER_SEQDELETE_END:
		return ZKN_PROC_TRUE;

	default:
		break;
	}
	
	return ZKN_PROC_FALSE;
}






//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverLoadResource(  ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap  )
{

	// グローバル領域にあるポケモンリストの座標を設定
	// 表示ON
	ZknZukanTextverPokeListDrawOn( p_drawglb, cp_glb, heap );

	// ポケモングラフィック表示ON
	ZknZukanTextverPokeGraDrawOn( p_drawglb, cp_glb );

	// アクターリソース読み込み
	ZknZukanTextverClactResLoad( p_draw, p_drawglb, heap );

	// ～ポケモン表示
	ZknZukanTextverPokeTypeTextAdd( p_draw, p_drawglb, cp_glb, heap );
	// 背景設定
	ZknZukanTextverSetUpBackGround( p_drawglb, heap );

	// 文字面設定
	ZknZukanTextverSetUpFontBg( p_drawglb, cp_glb, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リソースの破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverReleaseResource(  ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{

	// ～ポケモン表示
	ZknZukanTextverPokeTypeTextDelete( p_draw );
	
	// bmp破棄
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// アクターリソース破棄
	ZknZukanTextverClactResDelete( p_draw, p_drawglb );

	// 文字列面初期化
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSetUpBackGround( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモンの表示枠を背景に貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CX, ZKN_ZUKANTEXTVER_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// テキスト表示枠を背景に貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_e_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_TEXT_FRAME_CX, ZKN_ZUKANTEXTVER_TEXT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// テキスト詳細データ表示枠を背景に貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_f_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CX, ZKN_ZUKANTEXTVER_TEXTEX_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	文字列面設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSetUpFontBg( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKANTEXTVER_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int gmm_id;
	int str_width;

	// 捕獲しているかチェック
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// 捕獲していないのでダミー
		GF_ASSERT(0);
	}

/*	// ページ
	MSGMAN_GetString( man, ZNK_ZUKAN_TEXT_06, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X + ZKN_ZUKANTEXTVER_FONT_PAGE_OFS_X, ZKN_ZUKANTEXTVER_FONT_PAGE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// ページ数
	STRBUF_SetNumber( str, cp_glb->zukan_page + 1, ZKN_ZUKANTEXTVER_FONT_PAGE_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_PAGE_NUM_X, ZKN_ZUKANTEXTVER_FONT_PAGE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );//*/

	// 図鑑名
	gmm_id = ZknZukanTextverZukanNameGmmIDGet( cp_glb->zukan_type );
	MSGMAN_GetString( man, gmm_id, str );
	str_width = FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 );
	str_width /= 2;	// センターからの幅にする
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_C_X - str_width, ZKN_ZUKNATEXTVER_FONT_ZUKAN_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	

	// ポケモンナンバー描画
	STRBUF_SetNumber( str, mons_no, ZKN_ZUKANTEXTVER_FONT_MONSNO_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_MONSNO_X, ZKN_ZUKNATEXTVER_FONT_MONSNO_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// Poke'mon
	MSGMAN_GetString( man, ZNK_ZUKAN_TEXT_05, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_POKEMON_X, ZKN_ZUKNATEXTVER_FONT_POKEMON_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// text表示
	ZknZukanTextverFontSetUpText( p_drawglb, heap, mons_no, cp_glb->zukan_type, cp_glb->zukan_page );

	// ポケモン名
	ZknZukanTextvereFontPokeName( p_drawglb, heap, mons_no, cp_glb->zukan_type );
	
	// ポケモンタイプ
	ZknZukanTextvereFontPokeType( p_drawglb, heap, mons_no, cp_glb->zukan_type );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン説明textセット
 *	
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *	@param	mons_no		設定モンスターナンバー
 *	@param	lang		国コード
 *	@param	page		ページ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverFontSetUpText( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang, int page )
{
	STRBUF* str = ZKN_WT_GetText( mons_no, lang, page, heap);
	// ポケモンのメッセージ
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKANTEXTVER_FONT_COMMENT_X, ZKN_ZUKANTEXTVER_FONT_COMMENT_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 破棄
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリスト描画オン
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	// リスト作成
	ZKN_UTIL_PokeListPokeNameMakeGlb( 
			p_drawglb->p_drawglb, cp_glb->p_glb, heap,
			ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), 
			ZKN_ZUKANTEXTVER_POKELIST_MAT_X, ZKN_ZUKANTEXTVER_POKELIST_MAT_Y );

	ZKN_GlbPokeNameTblBGPriSet( p_drawglb->p_drawglb, ZKN_ZUKANTEXTVER_OAM_BG_PRI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリスト描画オフ
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	ZKN_GlbPokeNameTblDrawFlagSet( p_drawglb->p_drawglb, FALSE );
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示ON
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraDrawOn( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// ポケモン設定
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_ZUKANTEXTVER_POKEGRA_MAT_X, ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y );
	
	// 表示
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示OFF
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraDrawOff( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// 表示OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// ソフトパレットフェードがかかっている可能性があるのでOFF
	SoftSpritePalFadeOff( p_pokegra );
}


//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターのリソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverClactResLoad( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam2_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main2_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクターリソース破棄
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverClactResDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}	

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンタイプ（～ポケモン）の表示アクター作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeTypeTextAdd( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int mons_no			= ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	GF_BGL_BMPWIN* p_bmp;
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR pltt_res;

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKANTEXTVER_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKANTEXTVER_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// テーブル部分
	add.mat.x = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_X;
	add.mat.y = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_MAT_Y;
	p_draw->poketype_text_tbl = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->poketype_text_tbl, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_TBL_SEQ );

	// 捕まえているかチェック
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// ダミーデータ表示
	}

	// 文字列作成
	p_bmp = ZknZukanTextverPokeTypeTextBmpMake( p_drawglb, mons_no, heap );

	// パレットResource取得
	pltt_res = ZKN_GlbPokeNameTblResObjGet( p_drawglb->p_drawglb, CLACT_U_PLTT_RES );
	
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_drawglb->p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = p_draw->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKANTEXTVER_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKANTEXTVER_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_ZUKANTEXTVER_OAM_SOFT_PRI - 1;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;
	fontoam_init.p_bmp		 = p_bmp;
	p_draw->p_poketype_text = ZKN_FONTOAM_Make( &fontoam_init );
	

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );

}


//----------------------------------------------------------------------------
/**
 *	@brief	～ポケモン文字列BMP作成
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	mons_no		モンスターナンバー
 *	@param	heap		ヒープ
 *
 *	@return	作成ビットマップ
 *
 *	破棄が必要
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN* ZknZukanTextverPokeTypeTextBmpMake( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int mons_no, int heap )
{
	GF_BGL_BMPWIN* p_bmp;
	STRBUF* str;

	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->p_drawglb->fontoam_sys, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCX, ZKN_ZUKANTEXTVER_POKETYPE_TEXT_BMP_SCY );

	// ～ポケモン文字列取得
	str = ZKN_WT_GetPokeType( mons_no, PM_LANG, heap );
	ZKN_FONTOAM_PrintBmpStrBuf( p_drawglb->p_drawglb->fontoam_sys,
			p_bmp, str, 0, 0 );
	ZKN_WT_DeleteStrBuf( str );

	return p_bmp;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンタイプtextアクター破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeTypeTextDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	CLACT_Delete( p_draw->poketype_text_tbl );
	p_draw->poketype_text_tbl = NULL;
	ZKN_FONTOAM_Delete( p_draw->p_poketype_text );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑デフォルトフェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverDefaultFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	
	// 半透明OAM設定
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );
	ZknZukanTextverOamFadeInit( p_draw );

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// ポケグラパレットフェード設定
	ZknZukanTextverSpritePokeGraPalFade( p_drawglb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑デフォルトフェード処理　終了チェック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードイン TRUE アウト FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverDefaultFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;
	
	// フェードワークを図鑑データが動かしてよいかチェック
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}
	

	if( check == TRUE ){

		// フェードインのときは半透明破棄
		if( fadein_out == TRUE ){
			// OAM半透明設定破棄
			ZknZukanTextverOamFadeDelete( p_draw );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// ポケモングラフィック表示OFF
			ZknZukanTextverPokeGraDrawOff( p_drawglb );

			// グローバル領域にあるポケモンリスト表示OFF
			ZknZukanTextverPokeListDrawOff( p_drawglb );
		}
	}else{
		// ポケグラパレットフェード設定
		ZknZukanTextverSpritePokeGraPalFade( p_drawglb );
	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケリストとのフェード処理リクエスト
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverChPokeListFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanTextverOamFadeInit( p_draw );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZknZukanTextverPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_LONG_COMMON );

		// ポケモングラフィックフェード
		ZknZukanTextverPokeListFadeInit( p_draw );
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケリストとのフェード処理	終了チェック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverChPokeListFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 3 ];
	int i;
	

	// フェードアウトのときのみの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィック
		check[0] = ZknZukanTextverPokeGraFadeMain( p_draw, p_drawglb );

		// ポケモンリスト
		check[1] = ZknZukanTextverPokeListFadeMain( p_draw, p_drawglb );
	}else{
		check[0] = TRUE;
		check[1] = TRUE;
	}
	
	// ブライトネスを使用してよいときは自分でfadeを動かす
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check[2] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[2] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<3; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==3 ){

		// フェードインのときは半透明破棄
		if( fadein_out == TRUE ){
			// OAM半透明設定破棄
			ZknZukanTextverOamFadeDelete( p_draw );
		}
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	その他画面への移動
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverChOtherFadeReq( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanTextverOamFadeInit( p_draw );

	// ポケモンリストテーブルも半透明
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZknZukanTextverPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_COMMON );
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKANTEXTVER_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	その他画面とのフェード処理	終了チェック
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverChOtherFadeEndCheck( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, const ZKN_ZUKANTEXTVER_GLB* cp_glb , BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// フェードアウトのときのみの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィック
		check[0] = ZknZukanTextverPokeGraFadeMain( p_draw, p_drawglb );

	}else{
		check[0] = TRUE;
	}
	
	// ブライトネスを使用してよいときは自分でfadeを動かす
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check[1] = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	for( i=0; i<2; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}

	if( i==2 ){

		// フェードインのときは半透明破棄
		if( fadein_out == TRUE ){
			// OAM半透明設定破棄
			ZknZukanTextverOamFadeDelete( p_draw );

			// ポケテーブル
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// グローバル領域にあるポケモンリスト表示OFF
			ZknZukanTextverPokeListDrawOff( p_drawglb );
		}
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード処理初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverOamFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	// ～ポケモン
	CLACT_ObjModeSet( p_draw->poketype_text_tbl, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->p_poketype_text->p_fontoam, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード処理リセット
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverOamFadeDelete( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	// ～ポケモン
	CLACT_ObjModeSet( p_draw->poketype_text_tbl, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->p_poketype_text->p_fontoam, GX_OAM_MODE_NORMAL );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックパレットフェード値設定
 *
 *	@param	p_drawglb	描画グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverSpritePokeGraPalFade( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	// ブライトネス値設定
	ZKN_GLB_SpritePokeGraPalFade( p_drawglb->p_drawglb, &p_drawglb->p_drawglb->fade );
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモングラフィックフェード初期化
 *
 *	@param	p_draw	描画ワーク
 *	@param	move_x	動作ｘ座標
 *	@param	move_y	動作ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeGraFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw, int move_x, int move_y, int sync )
{
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_ZUKANTEXTVER_POKEGRA_MAT_X, move_x, ZKN_ZUKANTEXTVER_POKEGRA_MAT_Y, move_y, sync);
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモングラフィックフェード
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverPokeGraFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokegra_move );

	// 座標設定
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_draw->pokegra_move.x, p_draw->pokegra_move.y );

	return check;
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモンリストフェード
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextverPokeListFadeInit( ZKN_ZUKANTEXTVER_DRAW* p_draw )
{
	ZKN_UTIL_MoveReq( &p_draw->pokelist_move, ZKN_ZUKANTEXTVER_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKANTEXTVER_POKELIST_MAT_IY, ZKN_POKELIST_TBL_MAT_Y, ZKN_FADE_SYNC_LONG_COMMON);
}

//----------------------------------------------------------------------------
/**
 * [ポケモンリスト画面フェード]
 *	@brief	ポケモンリストフェード
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknZukanTextverPokeListFadeMain( ZKN_ZUKANTEXTVER_DRAW* p_draw, ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokelist_move );

	// 座標設定
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_draw->pokelist_move.x, p_draw->pokelist_move.y );

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	国コードに対応するGMMデータID取得
 *
 *	@param	lang	国コード
 *
 *	@return	GMMデータ
 */
//-----------------------------------------------------------------------------
static int ZknZukanTextverZukanNameGmmIDGet( int lang )
{
	int gmm_id;
	
	switch( lang ){
	case LANG_JAPAN:		///<	言語コード：日本
		gmm_id = ZNK_ZUKAN_TEXT_00;
		break;
		
	case LANG_ENGLISH:		///<	言語コード：英語
		gmm_id = ZNK_ZUKAN_TEXT_00;
		break;
		
	case LANG_FRANCE:		///<	言語コード：フランス語
		gmm_id = ZNK_ZUKAN_TEXT_01;
		break;
		
	case LANG_ITALY:		///<	言語コード：イタリア語
		gmm_id = ZNK_ZUKAN_TEXT_03;
		break;
		
	case LANG_GERMANY:		///<	言語コード：ドイツ語
		gmm_id = ZNK_ZUKAN_TEXT_02;
		break;
		
	case LANG_SPAIN:		///<	言語コード：スペイン語
		gmm_id = ZNK_ZUKAN_TEXT_04;
		break;
	default:
		//　おかしい
		GF_ASSERT( 0 );
		break;
	}

	return gmm_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名を描画
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *	@param	mons_no			モンスターナンバー
 *	@param	lang			国コード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextvereFontPokeName( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang )
{
	STRBUF* str = ZKN_WT_GetPokeName( mons_no, lang, heap);
	// ポケモンのメッセージ
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_ZUKNATEXTVER_FONT_MONSNAME_X, ZKN_ZUKNATEXTVER_FONT_MONSNAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 破棄
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンタイプの描画
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *	@param	mons_no			モンスターナンバー
 *	@param	lang			国コード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanTextvereFontPokeType( ZKN_ZUKANTEXTVER_DRAWGLB* p_drawglb, int heap, int mons_no, int lang )
{
	STRBUF* str = ZKN_WT_GetPokeType( mons_no, lang, heap);
	u32 x_mat;

	// X座標計算
	x_mat = ZKN_ZUKNATEXTVER_FONT_POKEMON_X - (FontProc_GetPrintStrWidth( FONT_SYSTEM, str, 0 ) + ZKN_ZUKNATEXTVER_FONT_MONSTYPE_X_OFS);
	
	// ポケモンのメッセージ
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, x_mat, ZKN_ZUKNATEXTVER_FONT_MONSTYPE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 破棄
	ZKN_WT_DeleteStrBuf( str );
}
