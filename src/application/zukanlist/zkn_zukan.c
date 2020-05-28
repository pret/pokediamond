//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan.c
 *	@brief		図鑑アプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
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
#include "include/application/zukanlist/zkn_world_text_sys.h"

// エフェクトで座標をLinkさせるため、仕方なくインクルード
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_ZUKAN_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan.h"


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
#define ZKN_ZUKAN_EVENT_NUM ( 0 )	// イベント数
#define ZKN_ZUKAN_OAM_BG_PRI	( 0 )
#define ZKN_ZUKAN_OAM_SOFT_PRI	( 32 )

// BGブライトネスフェード面
#define ZKN_ZUKAN_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )
#define ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-------------------------------------
//	図鑑セルアクター数
//=====================================
enum{
	ZKN_ZUKAN_CLACT_FOOT,
	ZKN_ZUKAN_CLACT_TYPE1,
	ZKN_ZUKAN_CLACT_TYPE2,
	ZKN_ZUKAN_CLACT_NUM,
};

// 背景座標
#define ZKN_ZUKAN_POKE_DRAW_FRAME_CX	( 0 )
#define ZKN_ZUKAN_POKE_DRAW_FRAME_CY	( 3 )
#define ZKN_ZUKAN_FOOT_FRAME_CX			( 12 )
#define ZKN_ZUKAN_FOOT_FRAME_CY			( 8 )
#define ZKN_ZUKAN_TEXT_FRAME_CX			( 0 )
#define ZKN_ZUKAN_TEXT_FRAME_CY			( 16 )


// 文字列面
#define ZKN_ZUKAN_NUM_STR		( 64 )	// バッファサイズ
#define ZKN_ZUKAN_NUM_STRTEXT	( 256 )	// バッファサイズ
#define ZKN_ZUKAN_FONT_HEIGHTGRAM_X	( 152 )
#define ZKN_ZUKAN_FONT_HEIGHT_Y	( 88 )
#define ZKN_ZUKAN_FONT_GRAM_Y	( 104 )
#define ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X	( 192 )

#define ZKN_ZUKAN_FONT_COMMENT_X	( 44 )
#define ZKN_ZUKAN_FONT_COMMENT_Y	( 136 )

//-------------------------------------
//	描画初期化シーケンス
//=====================================
enum
{
	ZKN_ZUKAN_SEQINIT_ALLOC,
	ZKN_ZUKAN_SEQINIT_LOAD,
	ZKN_ZUKAN_SEQINIT_FADEIN,
	ZKN_ZUKAN_SEQINIT_END,
};

//-------------------------------------
//	図鑑破棄シーケンス
//=====================================
enum{
	ZKN_ZUKAN_SEQDELETE_FADEOUT_INIT,
	ZKN_ZUKAN_SEQDELETE_FADEOUT,
	ZKN_ZUKAN_SEQDELETE_RELEASE,
	ZKN_ZUKAN_SEQDELETE_FREE,
	ZKN_ZUKAN_SEQDELETE_END,
};

// ポケモンリスト座標
#define ZKN_ZUKAN_POKELIST_MAT_X	( ZKN_ZUKAN_POKELIST_MAT_IX*FX32_ONE )
#define ZKN_ZUKAN_POKELIST_MAT_Y	( ZKN_ZUKAN_POKELIST_MAT_IY*FX32_ONE )

// 足跡
#define ZKN_ZUKAN_FOOT_MAT_X	( 120 * FX32_ONE )
#define ZKN_ZUKAN_FOOT_MAT_Y	( 88 * FX32_ONE )

// タイプ座標
#define ZKN_ZUKAN_POKETYPE1_MAT_X	( 170 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE2_MAT_X	( 220 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE_MAT_Y	( 72 * FX32_ONE )

// ～ポケモン座標
#define ZKN_ZUKAN_POKETYPE_TEXT_MAT_X	( 192 * FX32_ONE )
#define ZKN_ZUKAN_POKETYPE_TEXT_MAT_Y	( 52 * FX32_ONE )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	図鑑画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_ZUKAN_DRAWGLB;

#if 0
//-------------------------------------
//	図鑑画面　内部ワーク
//=====================================
typedef struct {
	int dummy;
} ZKN_ZUKAN_WORK;
#endif

//-------------------------------------
//	図鑑画面　描画ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR	clact[ ZKN_ZUKAN_CLACT_NUM ];

	// ～ポケモン
	CLACT_WORK_PTR  poketype_text_tbl;
	ZKN_FONTOAM_DATA*  p_poketype_text;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	
	// 足跡用
	CLACT_U_RES_OBJ_PTR foot_resobj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// ポケリストフェード用動作ワーク
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;
} ZKN_ZUKAN_DRAW;


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
static ZKN_ZUKAN_GLB* MakeZukanGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_ZUKAN_DRAWGLB* MakeZukanDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
//static ZKN_EVENT_DATA* MakeZukanEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteZukanGlb( ZKN_ZUKAN_GLB* p_glb );
static void DeleteZukanDrawGlb( ZKN_ZUKAN_DRAWGLB* p_glb );
//static void DeleteZukanEvent( ZKN_EVENT_DATA* p_event );


static int ZukanEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknZukanProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknZukanProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknZukanProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// フェードインアウト
static void ZknZukanDefaultFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanDefaultFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out );
static void ZknZukanChPokeListFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanChPokeListFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static void ZknZukanChOtherFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknZukanChOtherFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out );

static void ZknZukanSpritePokeGraPalFade( ZKN_ZUKAN_DRAWGLB* p_drawglb );

static void ZknZukanOamFadeInit( ZKN_ZUKAN_DRAW* p_draw );
static void ZknZukanOamFadeDelete( ZKN_ZUKAN_DRAW* p_draw );

static void ZknZukanPokeGraFadeInit( ZKN_ZUKAN_DRAW* p_draw, int move_x, int move_y, int sync_num );
static BOOL ZknZukanPokeGraFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanPokeListFadeInit( ZKN_ZUKAN_DRAW* p_draw );
static BOOL ZknZukanPokeListFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );


// BG設定
static void ZknZukanLoadResource( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanReleaseResource( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanSetUpBackGround( ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanSetUpFontBg( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanFontSetUpHeight( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk );
static void ZknZukanFontSetUpGram( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk );
static void ZknZukanFontSetUpText( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, int page, u32 color_msk );

// 足跡
static void ZknZukanFootSetUp( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanFootDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanFootResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap, int mons_no );
static void ZknZukanFootResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanFootActAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanFootActDelete( ZKN_ZUKAN_DRAW* p_draw );

// 足跡以外のアクター
static void ZknZukanClactResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap );
static void ZknZukanClactResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb );
static void ZknZukanClactAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanClactDelete( ZKN_ZUKAN_DRAW* p_draw );

// ～ポケモン
static void ZknZukanPokeTypeTextAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanPokeTypeTextDelete( ZKN_ZUKAN_DRAW* p_draw );

// ポケモンリスト
static void ZknZukanPokeListDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap );
static void ZknZukanPokeListDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb );

// ポケモングラフィック
static void ZknZukanPokeGraDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb );
static void ZknZukanPokeGraDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb );

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
void ZKN_ZukanAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_ZUKAN_GLB*	p_glb;
	ZKN_ZUKAN_DRAWGLB*	p_drawglb;
//	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeZukanGlb( heap, zkn_sys );
	p_drawglb = MakeZukanDrawGlb( heap, zkn_sys );
//	p_event = MakeZukanEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= NULL;
//	p_data->p_event_data	= p_event;
	p_data->event_num		= ZukanEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknZukanProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknZukanProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknZukanProcDrawFuncDelete;
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
void ZKN_ZukanAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteZukanGlb( p_data->p_glb_data ); 
	DeleteZukanDrawGlb( p_data->p_glb_draw );
//	DeleteZukanEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	自国テキスト描画　ページ設定
 *
 *	@param	p_data	データ
 *	@param	add		足し算値
 *
 *	@retval	TRUE	設定しました
 *	@retval	FALSE	設定しませんでした
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanAplPageAdd( ZKN_ZUKAN_GLB* p_data, int add )
{
/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	// 全部2ページ目なし
	return FALSE;//*/

	// 2ページがあるばあい
/*	p_data->zukan_page = (p_data->zukan_page + add) % ZKN_WT_HOME_TEXT_PAGE_NUM;
	return TRUE;//*/
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
 *	@brief	自国テキストページ数設定
 *
 *	@param	p_data	データ
 *	@param	set		セットページ数
 *
 *	@retval	TRUE	設定しました
 *	@retval	FALSE	設定しませんでした
 */
//-----------------------------------------------------------------------------
BOOL ZKN_ZukanAplPageSet( ZKN_ZUKAN_GLB* p_data, int set )
{
	BOOL ret = TRUE;
	
/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* アメリカ */
#if( PM_LANG == LANG_ENGLISH )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* フランス */
#if( PM_LANG == LANG_FRANCE )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* イタリア */
#if( PM_LANG == LANG_ITALY )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* ドイツ */
#if( PM_LANG == LANG_GERMANY )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif
/* スペイン */
#if( PM_LANG == LANG_SPAIN )
	// 全部2ページ目なし
	if( set == 1 ){
		set = 0;
		ret = FALSE;
	}
#endif

	p_data->zukan_page = set;
	return ret;
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
static ZKN_ZUKAN_GLB* MakeZukanGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_GLB) );

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
static ZKN_ZUKAN_DRAWGLB* MakeZukanDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_ZUKAN_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_ZUKAN_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_ZUKAN_DRAWGLB) );

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
static ZKN_EVENT_DATA* MakeZukanEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = ZukanEventDataNumGet();

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
static void DeleteZukanGlb( ZKN_ZUKAN_GLB* p_glb )
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
static void DeleteZukanDrawGlb( ZKN_ZUKAN_DRAWGLB* p_glb )
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
static void DeleteZukanEvent( ZKN_EVENT_DATA* p_event )
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
static int ZukanEventDataNumGet( void )
{
	return ZKN_ZUKAN_EVENT_NUM;
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
static int ZknZukanProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_GLB* p_glb = p_glbdata;
	// 図鑑見たフラグ設定
	ZKN_GLBDATA_PokeTextSeeSetMonsno( p_glb->p_glb, ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb ) );	
	ZKN_GLBDATA_PokeTextSeeSetZknMode( p_glb->p_glb, ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ) );	
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
static int ZknZukanProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_ZUKAN_GLB* p_glb = p_glbdata;
	
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	switch( p_dodata->seq ){
	case 0:	// 鳴き声チェック
		if( p_glb->mons_snd_req == TRUE ){
			Snd_PMVoicePlayEx( PV_ZUKAN_NORMAL, ZKN_GLBDATA_PokeMonsNoGet(p_glb->p_glb), 
					PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE, PV_PTN_PARAM_NONE );	//ぺラップ(default)

			p_glb->mons_snd_req = FALSE;
		}
		p_dodata->seq ++;
		break;

	default:
		break;
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
static int ZknZukanProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	Snd_PMVoiceStop(0);
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
static int ZknZukanProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKAN_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_ZUKAN_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_ZUKAN_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_ZUKAN_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQINIT_LOAD:
		ZknZukanLoadResource( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			ZknZukanChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			ZknZukanDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			ZknZukanChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQINIT_FADEIN:

		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			check = ZknZukanChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			check = ZknZukanDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			check = ZknZukanChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, TRUE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_ZUKAN_SEQINIT_END:
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
static int ZknZukanProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
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
static int ZknZukanProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_ZUKAN_GLB* cp_glb = cp_glbdata;
	ZKN_ZUKAN_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_ZUKAN_DRAW*	p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
		
	case ZKN_ZUKAN_SEQDELETE_FADEOUT_INIT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			ZknZukanChPokeListFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			ZknZukanDefaultFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			ZknZukanChOtherFadeReq( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQDELETE_FADEOUT:
		switch( cp_glb->fade_mode ){
		case ZKN_ZUKAN_FADE_MODE_CHPOKELIST:	
			check = ZknZukanChPokeListFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_NORMAL:
			check = ZknZukanDefaultFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		case ZKK_ZUKAN_FADE_MODE_OTHER:
			check = ZknZukanChOtherFadeEndCheck( p_drawwork, p_drawglb, cp_glb, FALSE );
			break;
		}

		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_ZUKAN_SEQDELETE_RELEASE:
		ZknZukanReleaseResource( p_drawwork, p_drawglb );
		p_drawdata->seq++;
		break;

	case ZKN_ZUKAN_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
	case ZKN_ZUKAN_SEQDELETE_END:
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
static void ZknZukanLoadResource(  ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap  )
{

	// グローバル領域にあるポケモンリストの座標を設定
	// 表示ON
	ZknZukanPokeListDrawOn( p_drawglb, cp_glb, heap );

	// ポケモングラフィック表示ON
	ZknZukanPokeGraDrawOn( p_drawglb, cp_glb );

	// アクターリソース読み込み
	ZknZukanClactResLoad( p_draw, p_drawglb, heap );

	// ～ポケモン表示
	ZknZukanPokeTypeTextAdd( p_draw, p_drawglb, cp_glb, heap );
	// 背景設定
	ZknZukanSetUpBackGround( p_drawglb, heap );

	// 文字面設定
	ZknZukanSetUpFontBg( p_drawglb, cp_glb, heap );

	// 捕まえてあるかチェック
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) == ZKN_POKELIST_TYPE_GET ){
		// 足跡
		ZknZukanFootSetUp( p_draw, p_drawglb, cp_glb, heap );

		
		// アクター登録
		ZknZukanClactAdd( p_draw, p_drawglb, cp_glb, heap );
	}


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
static void ZknZukanReleaseResource(  ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{

	// ～ポケモン表示
	ZknZukanPokeTypeTextDelete( p_draw );
	
	// bmp破棄
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// 足跡
	ZknZukanFootDelete( p_draw, p_drawglb );

	// アクター破棄
	ZknZukanClactDelete( p_draw );	

	// アクターリソース破棄
	ZknZukanClactResDelete( p_draw, p_drawglb );

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
static void ZknZukanSetUpBackGround( ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
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
			ZKN_ZUKAN_POKE_DRAW_FRAME_CX, ZKN_ZUKAN_POKE_DRAW_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモン足跡の表示枠を背景に貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKAN_FOOT_FRAME_CX, ZKN_ZUKAN_FOOT_FRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモン説明text枠を貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_main1_d_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_ZUKAN_TEXT_FRAME_CX, ZKN_ZUKAN_TEXT_FRAME_CY,
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
static void ZknZukanSetUpFontBg( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// 捕獲しているかチェック
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// 捕獲していないのでダミー
	}
	ZknZukanSetUpFontBg_Minute( &p_drawglb->p_drawglb->bmp_mfont,  mons_no, heap, cp_glb->zukan_page, ZKN_BG_FONT_COLOR_MSK );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑文字列データ書き込み関数
 *
 *	@param	p_bmp		ビットマップ
 *	@param	monsno		モンスターナンバー
 *	@param	heap		ヒープ
 *	@param	page		ページ
 *	@param	color_msk	カラーマスク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZknZukanSetUpFontBg_Minute( GF_BGL_BMPWIN* p_bmp, int monsno, int heap, int page, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);


	// 高さ
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_X, ZKN_ZUKAN_FONT_HEIGHT_Y, 0, color_msk, NULL );

	// 重さ
	MSGMAN_GetString( man, ZNK_ZUKAN_02, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_X, ZKN_ZUKAN_FONT_GRAM_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);


	// 高さ表示
	ZknZukanFontSetUpHeight( p_bmp, heap, monsno, color_msk );

	// 重さ表示
	ZknZukanFontSetUpGram( p_bmp, heap, monsno, color_msk );

	// text表示
	ZknZukanFontSetUpText( p_bmp, heap, monsno, page, color_msk );
}


//----------------------------------------------------------------------------
/**
 *	@brief	高さフォントセット
 *
 *	@param	p_bmp		ビットマップ	
 *	@param	heap		ヒープ
 *	@param	mons_no		設定モンスターナンバー
 *	@param	color_msk	カラーマスク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpHeight( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_height_dat, heap);

	// 高さ
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X, ZKN_ZUKAN_FONT_HEIGHT_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	重さフォントセット
 *
 *	@param	p_bmp		ビットマップ	
 *	@param	heap		ヒープ
 *	@param	mons_no		設定モンスターナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpGram( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, u32 color_msk )
{
	STRBUF* str = STRBUF_Create(ZKN_ZUKAN_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_gram_dat, heap);

	// 重さ
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_HEIGHTGRAM_TEXT_X, ZKN_ZUKAN_FONT_GRAM_Y, 0, color_msk, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン説明textセット
 *	
 *	@param	p_bmp		ビットマップ
 *	@param	heap		ヒープ
 *	@param	mons_no		設定モンスターナンバー
 *	@param	page		ページ
 *	@param	color_msk	カラーマスク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFontSetUpText( GF_BGL_BMPWIN* p_bmp, int heap, int mons_no, int page, u32 color_msk )
{
	STRBUF* str = ZKN_WT_GetText( mons_no, PM_LANG, page, heap);
	// ポケモンのメッセージ
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, ZKN_ZUKAN_FONT_COMMENT_X, ZKN_ZUKAN_FONT_COMMENT_Y, 0, color_msk, NULL );

	// 破棄
	ZKN_WT_DeleteStrBuf( str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	p_glb		グローバルデータ
 *	@param	heap		ヒープ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootSetUp( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	int mons_no = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	
	// リソース読み込み
	ZknZukanFootResLoad( p_draw, p_drawglb, heap, mons_no );

	// 登録
	ZknZukanFootActAdd( p_draw, p_drawglb, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{

	// 破棄
	ZknZukanFootActDelete( p_draw );
	
	// リソース破棄
	ZknZukanFootResDelete( p_draw, p_drawglb );

}

//----------------------------------------------------------------------------
/**
 *	@brief	リソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	グローバルデータ
 *	@param	heap		ヒープ
 *	@param	mons_no		モンスターナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap, int mons_no )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	int arc_file = PokeFootArcFileGet();
	int char_idx = PokeFootCharDataIdxGet( mons_no );
	int pltt_idx = PokeFootPlttDataIdxGet();
	int cell_idx = PokeFootCellDataIdxGet();
	int cellanm_idx = PokeFootCellAnmDataIdxGet();

	// キャラクタデータ読み込み
	p_draw->foot_resobj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], arc_file,
			char_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->foot_resobj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], arc_file,
			pltt_idx, FALSE, 
			ZKN_ZUKAN_FOOT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_ZUKAN_FOOT_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->foot_resobj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], arc_file,
			cell_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID, 
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->foot_resobj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], arc_file, 
			cellanm_idx, TRUE,
			ZKN_ZUKAN_FOOT_RES_ID, 
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑足跡リソース破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;

	if( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] == NULL ){
		return;
	}

	CLACT_U_CharManagerDelete( p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->foot_resobj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->foot_resobj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->foot_resobj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->foot_resobj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡アクター追加
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootActAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	add.mat.y		= ZKN_ZUKAN_FOOT_MAT_Y;
	add.mat.x		= ZKN_ZUKAN_FOOT_MAT_X;
	
	// 登録　アニメーション設定
	p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ] = CLACT_AddSimple( &add );
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡アクター破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanFootActDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	if(p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ]){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_FOOT ] );
	}
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
static void ZknZukanPokeListDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	// リスト作成
	ZKN_UTIL_PokeListPokeNameMakeGlb( 
			p_drawglb->p_drawglb, cp_glb->p_glb, heap,
			ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), 
			ZKN_ZUKAN_POKELIST_MAT_X, ZKN_ZUKAN_POKELIST_MAT_Y );

	ZKN_GlbPokeNameTblBGPriSet( p_drawglb->p_drawglb, ZKN_ZUKAN_OAM_BG_PRI );
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
static void ZknZukanPokeListDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeGraDrawOn( ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// ポケモン設定
	ZKN_UTIL_PokemonGraphicSet( p_drawglb->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_ZUKAN_POKEGRA_MAT_X, ZKN_ZUKAN_POKEGRA_MAT_Y );
	
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
static void ZknZukanPokeGraDrawOff( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanClactResLoad( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, int heap )
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
static void ZknZukanClactResDelete( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
 *	@brief	足跡以外のアクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanClactAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int mons_no			= ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	int type1, type2;
	int form = ZKN_GLBDATA_SaveData_FirstFormGet( cp_glb->p_glb, mons_no );


	type1 = PokeFormNoPersonalParaGet( mons_no, form, ID_PER_type1 );
	type2 = PokeFormNoPersonalParaGet( mons_no, form, ID_PER_type2 );

	// typeをニトロキャラクタのアニメシーケンスナンバーに変更
	type1 =	ZknZukanClactTypeNoChg( type1 );
	type2 =	ZknZukanClactTypeNoChg( type2 );

	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main2_lzh_NCGR + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam2_NCLR + ZKN_ZUKAN_FOOT_RES_ID, 
			NARC_zukan_zkn_data_oam_main2_lzh_NCER + ZKN_ZUKAN_FOOT_RES_ID,
			NARC_zukan_zkn_data_oam_main2_lzh_NANR + ZKN_ZUKAN_FOOT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// タイプ1
	add.mat.x = ZKN_ZUKAN_POKETYPE1_MAT_X;
	add.mat.y = ZKN_ZUKAN_POKETYPE_MAT_Y;
	p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ], ZKN_ZUKAN_POKETYPE_NORMAL + type1 );

	// タイプ2
	if( type1 != type2 ){
		add.mat.x = ZKN_ZUKAN_POKETYPE2_MAT_X;
		add.mat.y = ZKN_ZUKAN_POKETYPE_MAT_Y;
		p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ], ZKN_ZUKAN_POKETYPE_NORMAL + type2 );
	}else{
		p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] = NULL;
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンタイプをニトロキャラクタのアニメシーケンスにあわせる
 *
 *	@param	type	タイプ
 *
 *	@return	タイプ
 */
//-----------------------------------------------------------------------------
int ZknZukanClactTypeNoChg( int type )
{
	int num;
	
	switch( type ){
	case NORMAL_TYPE:		
		num = 0x0;
		break;
		
	case BATTLE_TYPE:		
		num = 0x6; 
		break;
		
	case HIKOU_TYPE:		
		num = 0xe;
		break;
		
	case POISON_TYPE:		
		num = 0xa;
		break;
		
	case JIMEN_TYPE:		
		num = 0x8;
		break;
		
	case IWA_TYPE:		
		num = 0x5;
		break;
		
	case MUSHI_TYPE:		
		num = 0xb;
		break;
		
	case GHOST_TYPE:		
	case HATE_TYPE:		
		num = 0x7;
		break;
		
	case METAL_TYPE:		
		num = 0x9;
		break;
		
	case FIRE_TYPE:		
		num = 0x1;
		break;
		
	case WATER_TYPE:		
		num = 0x3;
		break;
		
	case KUSA_TYPE:		
		num = 0x2;
		break;
		
	case ELECTRIC_TYPE:	
		num = 0x4;
		break;
		
	case SP_TYPE:			
		num = 0xf;
		break;
		
	case KOORI_TYPE:		
		num = 0xd;
		break;
		
	case DRAGON_TYPE:				
		num = 0x10;
		break;
		
	case AKU_TYPE:
		num = 0x0c;
		break;
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足跡以外のアクターを破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknZukanClactDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	if( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] ){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE1 ] );
	}
	if(p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ]){
		CLACT_Delete( p_draw->clact[ ZKN_ZUKAN_CLACT_TYPE2 ] );
	}
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
static void ZknZukanPokeTypeTextAdd( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, int heap )
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
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_ZUKAN_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_ZUKAN_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	// テーブル部分
	add.mat.x = ZKN_ZUKAN_POKETYPE_TEXT_MAT_X;
	add.mat.y = ZKN_ZUKAN_POKETYPE_TEXT_MAT_Y;
	p_draw->poketype_text_tbl = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->poketype_text_tbl, ZKN_ZUKAN_POKETYPE_TEXT_TBL_SEQ );

	// 捕まえているかチェック
	if( ZKN_GLBDATA_PokeMonsTypeGet( cp_glb->p_glb ) != ZKN_POKELIST_TYPE_GET ){
		mons_no = 0;	// ダミーデータ表示
	}

	// 文字列作成
	p_bmp = ZknZukanPokeTypeTextBmpMake( p_drawglb->p_drawglb->fontoam_sys, mons_no, heap );

	// パレットResource取得
	pltt_res = ZKN_GlbPokeNameTblResObjGet( p_drawglb->p_drawglb, CLACT_U_PLTT_RES );
	
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_drawglb->p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( pltt_res, NULL );
	fontoam_init.parent		 = p_draw->poketype_text_tbl;
	fontoam_init.x			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_X;
	fontoam_init.y			 = ZKN_ZUKAN_POKETYPE_TEXT_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_ZUKAN_OAM_BG_PRI;
	fontoam_init.soft_pri	 = ZKN_ZUKAN_OAM_SOFT_PRI - 1;
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
GF_BGL_BMPWIN* ZknZukanPokeTypeTextBmpMake( ZKN_FONTOAM_SYS_PTR p_fontoamsys, int mons_no, int heap )
{
	GF_BGL_BMPWIN* p_bmp;
	STRBUF* str;

	p_bmp = ZKN_FONTOAM_GetBmp( p_fontoamsys, ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCX, ZKN_ZUKAN_POKETYPE_TEXT_BMP_SCY );

	// ～ポケモン文字列取得
	str = ZKN_WT_GetPokeType( mons_no, PM_LANG, heap );
	ZKN_FONTOAM_PrintBmpStrBuf( p_fontoamsys,
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
static void ZknZukanPokeTypeTextDelete( ZKN_ZUKAN_DRAW* p_draw )
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
static void ZknZukanDefaultFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	
	// 半透明OAM設定
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );
	ZknZukanOamFadeInit( p_draw );

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESS_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );

		}
	}

	// ポケグラパレットフェード設定
	ZknZukanSpritePokeGraPalFade( p_drawglb );
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
static BOOL ZknZukanDefaultFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
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
			ZknZukanOamFadeDelete( p_draw );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// ポケモングラフィック表示OFF
			ZknZukanPokeGraDrawOff( p_drawglb );

			// グローバル領域にあるポケモンリスト表示OFF
			ZknZukanPokeListDrawOff( p_drawglb );
		}
	}else{
		// ポケグラパレットフェード設定
		ZknZukanSpritePokeGraPalFade( p_drawglb );
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
static void ZknZukanChPokeListFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanOamFadeInit( p_draw );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZknZukanPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_LONG_COMMON );

		// ポケモングラフィックフェード
		ZknZukanPokeListFadeInit( p_draw );
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_LONG_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

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
static BOOL ZknZukanChPokeListFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check[ 3 ];
	int i;
	

	// フェードアウトのときのみの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィック
		check[0] = ZknZukanPokeGraFadeMain( p_draw, p_drawglb );

		// ポケモンリスト
		check[1] = ZknZukanPokeListFadeMain( p_draw, p_drawglb );
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
			ZknZukanOamFadeDelete( p_draw );
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
static void ZknZukanChOtherFadeReq( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknZukanOamFadeInit( p_draw );

	// ポケモンリストテーブルも半透明
	ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_XLU );


	// フェードアウトの時だけの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィックフェード
		ZknZukanPokeGraFadeInit( p_draw, cp_glb->poke_gra_move_x, cp_glb->poke_gra_move_y, ZKN_FADE_SYNC_COMMON );
	}

	// ブライトネスを使って良いかﾁｪｯｸ
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					 BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_ZUKAN_BRIGHTNESSCH_POKELIST_MSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );

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
static BOOL ZknZukanChOtherFadeEndCheck( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb, const ZKN_ZUKAN_GLB* cp_glb , BOOL fadein_out )
{
	BOOL check[ 2 ];
	int i;
	

	// フェードアウトのときのみの処理
	if( fadein_out == FALSE ){
		// ポケモングラフィック
		check[0] = ZknZukanPokeGraFadeMain( p_draw, p_drawglb );

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
			ZknZukanOamFadeDelete( p_draw );

			// ポケテーブル
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}else{
			// グローバル領域にあるポケモンリスト表示OFF
			ZknZukanPokeListDrawOff( p_drawglb );
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
static void ZknZukanOamFadeInit( ZKN_ZUKAN_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_CLACT_NUM; i++ ){
		if( p_draw->clact[ i ] ){
			CLACT_ObjModeSet( p_draw->clact[ i ], GX_OAM_MODE_XLU );
		}
	}

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
static void ZknZukanOamFadeDelete( ZKN_ZUKAN_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_ZUKAN_CLACT_NUM; i++ ){
		if( p_draw->clact[ i ] ){
			CLACT_ObjModeSet( p_draw->clact[ i ], GX_OAM_MODE_NORMAL );
		}
	}

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
static void ZknZukanSpritePokeGraPalFade( ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeGraFadeInit( ZKN_ZUKAN_DRAW* p_draw, int move_x, int move_y, int sync_num )
{
	ZKN_UTIL_MoveReq( &p_draw->pokegra_move, ZKN_ZUKAN_POKEGRA_MAT_X, move_x, ZKN_ZUKAN_POKEGRA_MAT_Y, move_y, sync_num);
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
static BOOL ZknZukanPokeGraFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
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
static void ZknZukanPokeListFadeInit( ZKN_ZUKAN_DRAW* p_draw )
{
	ZKN_UTIL_MoveReq( &p_draw->pokelist_move, ZKN_ZUKAN_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKAN_POKELIST_MAT_IY, ZKN_POKELIST_TBL_MAT_Y, ZKN_FADE_SYNC_LONG_COMMON);
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
static BOOL ZknZukanPokeListFadeMain( ZKN_ZUKAN_DRAW* p_draw, ZKN_ZUKAN_DRAWGLB* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_draw->pokelist_move );

	// 座標設定
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_draw->pokelist_move.x, p_draw->pokelist_move.y );

	return check;
}
