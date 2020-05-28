//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sortsearch.c
 *	@brief		検索ソートアプリケーション
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/calctool.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"

#include "include/application/zukanlist/zkn_pokelist_sub.h"
#include "include/application/zukanlist/zkn_pokelist.h"

#define	__ZKN_SORTSEARCH_H_GLOBAL
#include "include/application/zukanlist/zkn_sortsearch.h"


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
#define ZKN_SORTSEARCH_EVENT_NUM ( 1 )	// イベント数
#define ZKN_SORTSEARCH_CHANGE_POKELIST	( 0x1 << 1 )	// ポケリストへ移動

#define ZKN_SORTSEARCH_OAM_BG_PRI	( 2 )
#define ZKN_SORTSEARCH_OAM_PRI		( 31 )

//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_SORTSEARCH_SEQINIT_ALLOC,
	ZKN_SORTSEARCH_SEQINIT_LOAD,
	ZKN_SORTSEARCH_SEQINIT_FADEIN,
	ZKN_SORTSEARCH_SEQINIT_END,
};
enum{
	ZKN_SORTSEARCH_SEQDELETE_FADEOUT_INIT,
	ZKN_SORTSEARCH_SEQDELETE_FADEOUT,
	ZKN_SORTSEARCH_SEQDELETE_RELEASE,
	ZKN_SORTSEARCH_SEQDELETE_FREE,
	ZKN_SORTSEARCH_SEQDELETE_END,
};

// BG
#define ZKN_SORTSEARCH_BG_X			( 6 )
#define ZKN_SORTSEARCH_BG_SORT_Y	( 6 )
#define ZKN_SORTSEARCH_BG_NAME_Y	( 9 )
#define ZKN_SORTSEARCH_BG_TYPE_Y	( 12 )
#define ZKN_SORTSEARCH_BG_FORM_Y	( 17 )


// FONT BG
#define ZKN_SORTSEARCH_PLTT				( 7 )
#define ZKN_SORTSEARCH_STR_NUM			( 64 )
#define ZKN_SORTSEARCH_FONT_BG_X		( 104 )
#define ZKN_SORTSEARCH_FONT_BG_SORT_Y	( 52 )
#define ZKN_SORTSEARCH_FONT_BG_NAME_Y	( 76 )
#define ZKN_SORTSEARCH_FONT_BG_TYPE1_Y	( 102 )
#define ZKN_SORTSEARCH_FONT_BG_TYPE2_Y	( 120 )
#define ZKN_SORTSEARCH_FONT_BG_AREA_X	( 80 )
#define ZKN_SORTSEARCH_FONT_BG_AREA_Y	( 16 )

#define ZKN_SORTSEARCH_FONT_BG_SELECT_X	( 32 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_Y	( 8 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X	( 208 )
#define ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y	( 32 )

#define ZKN_SORTSEARCH_FONT_BG_NAME_BOU_NUM	( 5 ) 
#define ZKN_SORTSEARCH_FONT_BG_TYPE_BOU_NUM	( 4 ) 
#define ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X	( 16 )

// FORM　OAM
#define ZKN_SORTSEARCH_FORM_OAM_X	( 128 )
#define ZKN_SORTSEARCH_FORM_OAM_Y	( 164 )
#define ZKN_SORTSEARCH_FORM_OAM_ANM	( 3 )
enum{
	ZKN_SORTSEARCH_FORM_OAM_FOUR_LEGS = ZKN_SORTSEARCH_FORM_OAM_ANM,
	ZKN_SORTSEARCH_FORM_OAM_TWO_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_TAIL,
	ZKN_SORTSEARCH_FORM_OAM_HARABAI,
	ZKN_SORTSEARCH_FORM_OAM_FOUR_WING,
	ZKN_SORTSEARCH_FORM_OAM_TWO_WING,
	ZKN_SORTSEARCH_FORM_OAM_HAITSUKUBARI,
	ZKN_SORTSEARCH_FORM_OAM_STRAIGHT,
	ZKN_SORTSEARCH_FORM_OAM_ARM,
	ZKN_SORTSEARCH_FORM_OAM_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_MANY_LEGS,
	ZKN_SORTSEARCH_FORM_OAM_WATER,
	ZKN_SORTSEARCH_FORM_OAM_CIRCLE,
	ZKN_SORTSEARCH_FORM_OAM_COMP,
};

// ｿｰﾄ失敗テキスト描画カウント
#define ZKN_SORTSEARCH_ERR_DRAW_COUNT	( 64 )


// ｿｰﾄｴﾌｪｸﾄ
#define ZKN_SORTSEARCH_EFECT_ACT_X		( 128 )
#define ZKN_SORTSEARCH_EFECT_ACT_Y		( 96 )
#define ZKN_SORTSEARCH_EFECT_ACT_ANM	( 17 )
#define ZKN_SORTSEARCH_EFECT_FONT_X		( 96 )
#define ZKN_SORTSEARCH_EFECT_FONT_Y		( 128 )

#define ZKN_SORTSEARCH_EFECT_OAM_ROTA	( FX_GET_ROTA_NUM(180) )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	検索ソート画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ
	ZKN_POKELIST_GLB_DATA* p_pokelist;		// ポケリスト

	int					now_select;			// 現在のセレクトﾀｲﾌﾟ
	int					sort_type;			// ｿｰﾄﾀｲﾌﾟ
	int					search_name;		// なまえサーチﾀｲﾌﾟ
	int					search_type1;		// ﾀｲﾌﾟサーチﾀｲﾌﾟ
	int					search_type2;		// ﾀｲﾌﾟサーチﾀｲﾌﾟ
	int					search_form;		// かたちサーチﾀｲﾌﾟ
	BOOL				list_chg_flag;// リスト画面へ
	BOOL				sort_flag;		// ｿｰﾄ実行フラグ
	BOOL				sort_err;		// ｿｰﾄ実行失敗

	// モード
	int		fade_mode;			// フェードモード
	int		fade_count;			// フェード動作カウント	
								// このｶｳﾝﾀで全動作する
} ZKN_SORTSEARCH_GLB;

//-------------------------------------
//	検索ソート画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_SORTSEARCH_DRAWGLB;

//-------------------------------------
//	検索ソート画面　内部ワーク
//=====================================
typedef struct {
	int dummy;
} ZKN_SORTSEARCH_WORK;

//-------------------------------------
//	検索ソート画面　描画ワーク
//=====================================
typedef struct {
	int		now_select;			// 現在のセレクトﾀｲﾌﾟ
	int		sort_type;			// ｿｰﾄﾀｲﾌﾟ
	int		search_name;		// なまえサーチﾀｲﾌﾟ
	int		search_type1;		// ﾀｲﾌﾟサーチﾀｲﾌﾟ
	int		search_type2;		// ﾀｲﾌﾟサーチﾀｲﾌﾟ
	int		search_form;		// かたちサーチﾀｲﾌﾟ

	BOOL				sort_err;		// ｿｰﾄ実行失敗
	int					sort_err_draw_count;	// ｿｰﾄ実行失敗描画ｶｳﾝﾀ

	// フォームOAM
	CLACT_WORK_PTR search_form_act;
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	// シャッターフェード
	ZKN_UTIL_BGSHTTER_DADE shutter;

	// 検索中アニメ用
	CLACT_WORK_PTR sort_act;

	void* p_scrn_buff;
	NNSG2dScreenData* p_scrn;	// スクリーンデータ
} ZKN_SORTSEARCH_DRAW;

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
static ZKN_SORTSEARCH_GLB* MakeSortSearchGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SORTSEARCH_DRAWGLB* MakeSortSearchDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSortSearchEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSortSearchGlb( ZKN_SORTSEARCH_GLB* p_glb );
static void DeleteSortSearchDrawGlb( ZKN_SORTSEARCH_DRAWGLB* p_glb );
static void DeleteSortSearchEvent( ZKN_EVENT_DATA* p_event );


static int SortSearchEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// フェード処理
static void ZknSortSearchFadeSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );

// 検索中エフェクト処理
static void ZknSortSearchSortEffSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchSortEffFontSet( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSortEffFontReset( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, ZKN_SORTSEARCH_DRAW* p_draw, int heap );

// Resource読み込み
static void ZknSortSearchLoadRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, const ZKN_SORTSEARCH_WORK* cp_datawork, int heap );
static void ZknSortSearchDeleteRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );
static void ZknSortSearchSetUpBg( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchOamResLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchOamResDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );
static void ZknSortSearchOamInit( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap );
static void ZknSortSearchOamDelete( ZKN_SORTSEARCH_DRAW* p_draw );
static void ZknSortSearchUtilBgLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap, int zkn_mode );
static void ZknSortSearchUtilBgDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb );



// 描画処理
static void ZknSortSearchSelectDraw( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb,  int heap );

static void ZknSortSearchBgSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZknSortSearchFontSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSortType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchName( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType1( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType2( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap );
static void ZKnSortSearchFontSearchType_Core( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap, int y );
static void ZKnSortSearchOamSearchForm( ZKN_SORTSEARCH_DRAW* p_draw, int type );
static void ZknSortSearchFontNotHitPokemon( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap );


static void ZknSortSearchPokeGraDrawOff( ZKN_SORTSEARCH_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　アプリ作成
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
void ZKN_SortSearchAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SORTSEARCH_GLB*	p_glb;
	ZKN_SORTSEARCH_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSortSearchGlb( heap, zkn_sys );
	p_drawglb = MakeSortSearchDrawGlb( heap, zkn_sys );
	p_event = MakeSortSearchEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SortSearchEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchProcDrawFuncDelete;
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
void ZKN_SortSearchAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSortSearchGlb( p_data->p_glb_data ); 
	DeleteSortSearchDrawGlb( p_data->p_glb_draw ); 
	DeleteSortSearchEvent( p_data->p_event_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在選択しているﾀｲﾌﾟを設定
 *
 *	@param	p_data	アプリﾃﾞｰﾀ
 *	@param	type	ﾀｲﾌﾟ
 *
 *	@return	none
 *	typoe
	ZKN_SORTSEARCH_SELECT_SORT,
	ZKN_SORTSEARCH_SELECT_NEME,
	ZKN_SORTSEARCH_SELECT_TYPE,
	ZKN_SORTSEARCH_SELECT_FORM,
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplSelectTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_SORTSEARCH_SELECT_NUM );
	p_glb->now_select = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	現在選択しているﾀｲﾌﾟを取得
 *
 *	@param	cp_data		アプリケーションﾃﾞｰﾀ
 *
 *	@return	選択ﾀｲﾌﾟ
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplSelectTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->now_select;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄﾀｲﾌﾟ設定
 *
 *	@param	p_data	アプリﾃﾞｰﾀ
 *	@param	type	ﾀｲﾌﾟ
 *
 *	@return	none
 *
 *	type
	ZKN_POKELIST_SORT_NORMAL,		// ポケモンナンバー
	ZKN_POKELIST_SORT_GOZYUUON,		// 五十音
	ZKN_POKELIST_SORT_GRAM_L,		// 重い
	ZKN_POKELIST_SORT_GRAM_S,		// 軽い
	ZKN_POKELIST_SORT_HIGH_L,		// 高い
	ZKN_POKELSIT_SOTT_HIGH_S,		// 低い
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplSortTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SORT_NUM );
	p_glb->sort_type = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄﾀｲﾌﾟを取得
 *
 *	@param	cp_data		アプリﾃﾞｰﾀ
 *
 *	@return	ｿｰﾄﾀｲﾌﾟ
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplSortTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->sort_type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	なまえﾀｲﾌﾟ設定
 *
 *	@param	p_data	アプリﾃﾞｰﾀ
 *	@param	type	名前ﾀｲﾌﾟ
 *
 * type
	ZKN_POKELIST_SEARCH_NAME_NONE,
	ZKN_POKELIST_SEARCH_NAME_A,
	ZKN_POKELIST_SEARCH_NAME_KA,
	ZKN_POKELIST_SEARCH_NAME_SA,
	ZKN_POKELIST_SEARCH_NAME_TA,
	ZKN_POKELIST_SEARCH_NAME_NA,
	ZKN_POKELIST_SEARCH_NAME_HA,
	ZKN_POKELIST_SEARCH_NAME_MA,
	ZKN_POKELIST_SEARCH_NAME_RA,
	ZKN_POKELIST_SEARCH_NAME_YAWA,
 * 
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplNameTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_NAME_NUM );
	p_glb->search_name = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾅﾏｴﾀｲﾌﾟ取得
 *
 *	@param	cp_data		アプリﾃﾞｰﾀ
 *
 *	@return	ﾅﾏｴﾀｲﾌﾟ
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplNameTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->search_name;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟﾀｲﾌﾟ設定
 *	
 *	@param	p_data		アプリデータ
 *	@param	type		ﾀｲﾌﾟ
 *	@param	no			ﾀｲﾌﾟﾅﾝﾊﾞｰ 0or1
 *
 * type
	ZKN_POKELIST_SEARCH_TYPE_NONE,
	ZKN_POKELIST_SEARCH_TYPE_NORMAL,
	ZKN_POKELIST_SEARCH_TYPE_BATTLE,	
	ZKN_POKELIST_SEARCH_TYPE_HIKOU,	
	ZKN_POKELIST_SEARCH_TYPE_POISON,	
	ZKN_POKELIST_SEARCH_TYPE_JIMEN,	
	ZKN_POKELIST_SEARCH_TYPE_IWA,		
	ZKN_POKELIST_SEARCH_TYPE_MUSHI,	
	ZKN_POKELIST_SEARCH_TYPE_GHOST,	
	ZKN_POKELIST_SEARCH_TYPE_METAL,	
	ZKN_POKELIST_SEARCH_TYPE_FIRE,	
	ZKN_POKELIST_SEARCH_TYPE_WATER,	
	ZKN_POKELIST_SEARCH_TYPE_KUSA,	
	ZKN_POKELIST_SEARCH_TYPE_ELECTRIC,
	ZKN_POKELIST_SEARCH_TYPE_SP,		
	ZKN_POKELIST_SEARCH_TYPE_KOORI,	
	ZKN_POKELIST_SEARCH_TYPE_DRAGON,	
	ZKN_POKELIST_SEARCH_TYPE_AKU,	
 * 
 * no
	ZKN_SORTSEARCH_TYPE1,
	ZKN_SORTSEARCH_TYPE2

 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplTypeTypeSet( ZKN_APL_DATA* p_data, int type, int no )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_TYPE_NUM );

	if( no == ZKN_SORTSEARCH_TYPE1 ){
		p_glb->search_type1 = type;
	}else{
		p_glb->search_type2 = type;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟﾀｲﾌﾟの取得
 *
 *	@param	cp_data		アプリﾃﾞｰﾀ
 *	@param	no			ﾀｲﾌﾟﾅﾝﾊﾞｰ
 *
 *	@return	ﾀｲﾌﾟﾀｲﾌﾟ
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplTypeTypeGet( const ZKN_APL_DATA* cp_data, int no )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	if( no == ZKN_SORTSEARCH_TYPE1 ){
		return cp_glb->search_type1;
	}

	return cp_glb->search_type2;
}

//----------------------------------------------------------------------------
/**
 *	@brief	形態ﾀｲﾌﾟの設定
 *
 *	@param	p_data		アプリﾃﾞｰﾀ
 *	@param	type		ﾀｲﾌﾟ
 *
 *	@return	none
 *	type
	ZKN_POKELIST_SEARCH_FORM_NONE,
	ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TWO_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TAIL,
	ZKN_POKELIST_SEARCH_FORM_HARABAI,
	ZKN_POKELIST_SEARCH_FORM_FOUR_WING,
	ZKN_POKELIST_SEARCH_FORM_TWO_WING,
	ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI,
	ZKN_POKELIST_SEARCH_FORM_STRAIGHT,
	ZKN_POKELIST_SEARCH_FORM_ARM,
	ZKN_POKELIST_SEARCH_FORM_LEGS,
	ZKN_POKELIST_SEARCH_FORM_MANY_LEGS,
	ZKN_POKELIST_SEARCH_FORM_WATER,
	ZKN_POKELIST_SEARCH_FORM_CIRCLE,
	ZKN_POKELIST_SEARCH_FORM_COMP,
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplFormTypeSet( ZKN_APL_DATA* p_data, int type )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	GF_ASSERT( type < ZKN_POKELIST_SEARCH_FORM_NUM );
	p_glb->search_form = type;
}

//----------------------------------------------------------------------------
/**
 *	@brief	形態ﾀｲﾌﾟの取得
 *	
 *	@param	cp_data		アプリﾃﾞｰﾀ
 *
 *	@return	形態ﾀｲﾌﾟ
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFormTypeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->search_form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リスト画面へ行く
 *
 *	@param	p_data
 *	@param	do_sort	TRUE	ｿｰﾄを行う
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchAplReqListFade( ZKN_APL_DATA* p_data, BOOL do_sort )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_data->p_glb_data;

	p_glb->list_chg_flag = TRUE;
	p_glb->sort_flag = do_sort;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄ処理を行うかのフラグ
 *
 *	@param	p_data	アプリﾃﾞｰﾀ
 *
 *	@retval	TRUE	行う
 *	@retval	FALSE	行わない
 */
//-----------------------------------------------------------------------------
BOOL ZKN_SortSearchAplSortDoFlagGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->sort_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作モード取得
 *	
 *	@param	cp_data 
 *
 *	@return	動作モード
	ZKN_SORTSEARCH_MOVE_MODE_SELECT,	パラメータ設定中
	ZKN_SORTSEARCH_MOVE_MODE_DO_SORT,	検索中
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFadeModeGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->fade_mode;
}
//----------------------------------------------------------------------------
/**
 *	@brief	フェードカウント値取得
 *
 *	@param	cp_data		アプリﾃﾞｰﾀ
 *
 *	@return	フェードカウント値
 */
//-----------------------------------------------------------------------------
int ZKN_SortSearchAplFadeModeCountGet( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SORTSEARCH_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->fade_count;
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCH_GLB* MakeSortSearchGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCH_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCH_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCH_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// ポケリスト
	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist = p_apl->p_glb_data;

	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCH_DRAWGLB* MakeSortSearchDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCH_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCH_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCH_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSortSearchEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = SortSearchEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_tbl[0], zkn_sys, ZKN_SORTSEARCH_CHANGE_POKELIST );

	return p_event_tbl;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchGlb( ZKN_SORTSEARCH_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchDrawGlb( ZKN_SORTSEARCH_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソートアプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	検索ソートアプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int SortSearchEventDataNumGet( void )
{
	return ZKN_SORTSEARCH_EVENT_NUM;
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
static int ZknSortSearchProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCH_WORK* p_work;

	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SORTSEARCH_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SORTSEARCH_WORK) );
	p_dodata->p_work = p_work;


	//　グローバルﾃﾞｰﾀ初期化
	p_glb->now_select = ZKN_SORTSEARCH_SELECT_SORT;
	p_glb->sort_type  = ZKN_POKELIST_SORT_NORMAL;
	p_glb->search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
	p_glb->search_type1 = ZKN_POKELIST_SEARCH_TYPE_NONE;
	p_glb->search_type2 = ZKN_POKELIST_SEARCH_TYPE_NONE;
	p_glb->search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	
	p_glb->list_chg_flag = FALSE;
	p_glb->sort_flag = FALSE;

	p_glb->fade_mode = ZKN_SORTSEARCH_FADENONE;
	
	
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
static int ZknSortSearchProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCH_WORK*	p_work = p_dodata->p_work;
	BOOL check;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	switch( p_dodata->seq ){
	case 0:
		// ｿｰﾄ失敗解除
		if( p_glb->sort_err ){
			p_glb->sort_err = FALSE;
		}

		if( p_glb->list_chg_flag == TRUE ){

			// ｿｰﾄ検索実行チェック
			if( p_glb->sort_flag == FALSE ){
				// Bボタンでポケモンリストへ
				*p_glb->p_event_key |= ZKN_SORTSEARCH_CHANGE_POKELIST;
				p_glb->fade_mode = ZKN_SORTSEARCH_END_FADE;	
			}else{
				p_glb->fade_mode = ZKN_SORTSEARCH_FADEOUT;
				p_glb->fade_count = ZKN_SORTSEARCH_FADECOUNT_MAX;
				p_dodata->seq++;
			}
		}
		break;

	case 1:
		// フェードカウント
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_dodata->seq++;
			
			p_glb->fade_mode = ZKN_SORTSEARCH_DO_MAIN;
			p_glb->fade_count = ZKN_SORTSEARCH_DO_MAIN_EFF_COUNT_MAX;

			
			Snd_SePlay( ZKN_SND_SEARCH );
		}
		break;

	case 2:
		// 検索エフェクトカウント
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_dodata->seq++;
		}
		break;
		
	case 3:			// ｿｰﾄｻｰﾁ処理
		check = TRUE;
	
		// ｿｰﾄ実行するならする
		// ﾎﾟｹﾓﾝﾘｽﾄ変更
		check = ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( p_glb->p_glb, p_glb->sort_type,
				p_glb->search_name, p_glb->search_type1, 
				p_glb->search_type2, p_glb->search_form, 
				ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ), p_dodata->heap, TRUE );

		if( check == TRUE ){
			// Bボタンでポケモンリストへ
			*p_glb->p_event_key |= ZKN_SORTSEARCH_CHANGE_POKELIST;

			// リスト先頭位置を設定
			ZKN_GLBDATA_PokeListDrawTblNoSet( p_glb->p_glb, 0 );

			// ポケリストをｿｰﾄｻｰﾁモードで開く
			p_glb->p_glb->sort_search_flag = ZKN_SORTSEARCH_SORT;
			p_glb->p_pokelist->fade_sort_data = TRUE;
		}else{

			p_glb->sort_flag = FALSE;
			p_glb->list_chg_flag = FALSE;
			// ｿｰﾄ失敗
			p_glb->sort_err = TRUE;
			// 動作方法変更
			p_glb->fade_mode = ZKN_SORTSEARCH_FADEIN;
			p_glb->fade_count = ZKN_SORTSEARCH_FADECOUNT_MAX;

			p_dodata->seq ++;

		}
		break;
		
	// フェードイン
	case 4:
		// フェードカウント
		p_glb->fade_count --;
		if( p_glb->fade_count < 0 ){
			p_glb->fade_mode = ZKN_SORTSEARCH_FADENONE;
			p_glb->fade_count = 0;
			p_dodata->seq = 0;
		}
		break;

	default:
		GF_ASSERT( 0 );
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
static int ZknSortSearchProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCH_WORK* p_work = p_dodata->p_work;
	ZKN_SORTSEARCH_GLB* p_glb = p_glbdata;



	sys_FreeMemoryEz( p_work );
	p_dodata->p_work = NULL;
	
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
static int ZknSortSearchProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCH_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SORTSEARCH_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SORTSEARCH_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_LOAD:
		ZknSortSearchLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		
		// フェード初期化
		ChangeBrightnessRequest( ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_FADEIN:
		// フェード
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCH_SEQINIT_END:
		return ZKN_PROC_TRUE;
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
static int ZknSortSearchProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;


	if( cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADENONE ){
		
		// 選択処理時の動き　
		ZknSortSearchSelectDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
		
	}else if( (cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADEOUT) || 
			(cp_dataglb->fade_mode == ZKN_SORTSEARCH_FADEIN) ){

		// フェード処理
		ZknSortSearchFadeSys( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
	}else if( cp_dataglb->fade_mode != ZKN_SORTSEARCH_END_FADE ){
  
		// 検索中エフェクト
		ZknSortSearchSortEffSys( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );
	}


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
static int ZknSortSearchProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCH_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCH_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCH_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCH_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCH_SEQDELETE_FADEOUT_INIT:
		if( cp_dataglb->sort_flag == FALSE ){
			ChangeBrightnessRequest( COMM_BRIGHTNESS_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
			p_drawdata->seq++;
		}else{
			p_drawdata->seq = ZKN_SORTSEARCH_SEQDELETE_RELEASE;
		}
		break;
		
	case ZKN_SORTSEARCH_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_MAIN_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SORTSEARCH_SEQDELETE_RELEASE:
		
		ZknSortSearchDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCH_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SORTSEARCH_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource読み込み＆画面構築
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	cp_datawork	データワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchLoadRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, const ZKN_SORTSEARCH_WORK* cp_datawork, int heap )
{
	// ユーティリティ面スクリーン破棄
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M );
	// フォント面スクリーン破棄
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// この画面ではFONTカラーを7にする
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_SORTSEARCH_PLTT );

	// ポケグラ表示OFF
	ZknSortSearchPokeGraDrawOff( p_drawglb );
	
	// BG設定
	ZknSortSearchSetUpBg( p_drawglb, cp_glb, heap );

	// ユーティリティ面
	ZknSortSearchUtilBgLoad( p_draw, p_drawglb, cp_glb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	//OAM読み込み
	ZknSortSearchOamResLoad( p_draw, p_drawglb, heap );

	// OAM登録
	ZknSortSearchOamInit( p_draw, p_drawglb, cp_glb, heap );

	// 表示の初期設定
	ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
	ZknSortSearchBgSelectType( p_drawglb, cp_glb->now_select, heap );
	ZKnSortSearchFontSortType( p_drawglb, cp_glb->sort_type, heap );
	ZKnSortSearchFontSearchName( p_drawglb, cp_glb->search_name, heap );
	ZKnSortSearchFontSearchType1( p_drawglb, cp_glb->search_type1, heap );
	ZKnSortSearchFontSearchType2( p_drawglb, cp_glb->search_type2, heap );
	ZKnSortSearchOamSearchForm( p_draw, cp_glb->search_form );


	// 表示優先順位を変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 1 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchDeleteRes( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	// OAM破棄
	ZknSortSearchOamDelete( p_draw );

	// OAMリソース破棄
	ZknSortSearchOamResDelete( p_draw, p_drawglb );

	// ユーティティ面破棄
	ZknSortSearchUtilBgDelete( p_draw, p_drawglb );


	// フォント面スクリーン破棄
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );

	// この画面ではFONTカラーをもどす
	GF_BGL_BmpWinSet_Pal( &p_drawglb->p_drawglb->bmp_mfont, ZKN_BG_FONT_COLOR );

	// 表示優先順位を変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 0 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景面セット	
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 * [イベントで出てくる島のスクリーンデータ書き換えもこの中]
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSetUpBg( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	void* p_buff;

	
	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );


	// カラーパレットを転送
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort2_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ユーティリティ面描画設定
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	heap		ヒープ
 *	@param	zkn_mode	図鑑モード
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchUtilBgLoad( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap, int zkn_mode )
{
	int dataidx;
	
	// キャラクタデータ転送
//	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// 全国とシンオウでデータidxを変更
	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		dataidx = NARC_zukan_zkn_list_bg_zen_lzh_NSCR;
	}else{
		dataidx = NARC_zukan_zkn_list_bg_sin_lzh_NSCR;
	}
	
	// スクリーンデータ読み込み
	p_draw->p_scrn_buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, dataidx, TRUE, &p_draw->p_scrn, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ユーティティBG面はき
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchUtilBgDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	sys_FreeMemoryEz( p_draw->p_scrn_buff );
	p_draw->p_scrn_buff = NULL;
	p_draw->p_scrn = NULL;
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
static void ZknSortSearchPokeGraDrawOff( ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );

	// 表示OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// ソフトパレットフェードがかかっている可能性があるのでOFF
	SoftSpritePalFadeOff( p_pokegra );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchOamResLoad(  ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR + ZKN_SORTSEARCH_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCH_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_POKELIST_TBL_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_list_oam_main_lzh_NCER, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NCER + ZKN_SORTSEARCH_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_list_oam_main_lzh_NANR, TRUE,
			NARC_zukan_zkn_list_oam_main_lzh_NANR + ZKN_SORTSEARCH_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMResource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchOamResDelete( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb )
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
 *	@brief	OAMアクターバッファ作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchOamInit( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR + ZKN_SORTSEARCH_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCH_RES_ID, 
			NARC_zukan_zkn_list_oam_main_lzh_NCER + ZKN_SORTSEARCH_RES_ID,
			NARC_zukan_zkn_list_oam_main_lzh_NANR + ZKN_SORTSEARCH_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SORTSEARCH_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_SORTSEARCH_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	
	//form
	add.mat.x = ZKN_SORTSEARCH_FORM_OAM_X << FX32_SHIFT;
	add.mat.y = ZKN_SORTSEARCH_FORM_OAM_Y << FX32_SHIFT;
	p_draw->search_form_act = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_ANM );


	// ｿｰﾄｴﾌｪｸﾄ用アクター
	add.mat.x = ZKN_SORTSEARCH_EFECT_ACT_X << FX32_SHIFT;
	add.mat.y = ZKN_SORTSEARCH_EFECT_ACT_Y << FX32_SHIFT;
	p_draw->sort_act = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->sort_act, ZKN_SORTSEARCH_EFECT_ACT_ANM );
	CLACT_SetDrawFlag( p_draw->sort_act, FALSE );
	CLACT_SetAffineParam( p_draw->sort_act, CLACT_AFFINE_NORMAL );
	CLACT_BGPriorityChg( p_draw->sort_act, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMアクターバッファ破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchOamDelete( ZKN_SORTSEARCH_DRAW* p_draw )
{
	CLACT_Delete( p_draw->search_form_act );

	CLACT_Delete( p_draw->sort_act );
}


//----------------------------------------------------------------------------
/**
 *	@brief	今選択中の画面の説明
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	type			ﾀｲﾌﾟ
 *	@param	heap			ﾋｰﾌﾟ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFontSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	// 書き込む領域クリーン
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X, ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y );

	// 文字列
	switch( type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		msg_idx = ZNK_SORTSEARCH_TEXT_03;
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		msg_idx = ZNK_SORTSEARCH_TEXT_00;
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		msg_idx = ZNK_SORTSEARCH_TEXT_01;
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		msg_idx = ZNK_SORTSEARCH_TEXT_02;
		break;
	default:
		break;
	}


	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	設定にヒットしたポケモンがいなかった
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFontNotHitPokemon( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	
	// 書き込む領域クリーン
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_X, ZKN_SORTSEARCH_FONT_BG_SELECT_AREA_Y );


	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( ZNK_SORTSEARCH_TEXT_06, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_SELECT_X, ZKN_SORTSEARCH_FONT_BG_SELECT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択時の描画メイン関数
 *
 *	@param	p_draw
 *	@param	p_drawglb
 *	@param	cp_glb
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSelectDraw( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb,  int heap )
{
	// 検索ｿｰﾄエラー描画
	if( cp_glb->sort_err != p_draw->sort_err ){

		p_draw->sort_err = cp_glb->sort_err;
		if( p_draw->sort_err == TRUE ){
			p_draw->sort_err_draw_count = ZKN_SORTSEARCH_ERR_DRAW_COUNT;
			ZknSortSearchFontNotHitPokemon( p_drawglb, heap );
		}
	}
	if( p_draw->sort_err_draw_count > 0 ){		// 一定間隔だしたら消す処理
		p_draw->sort_err_draw_count--;
	}else if( p_draw->sort_err_draw_count == 0 ){
		ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
		p_draw->sort_err_draw_count--;
	}

	if( p_draw->now_select != cp_glb->now_select ){
		ZknSortSearchBgSelectType( p_drawglb, cp_glb->now_select, heap );
		ZknSortSearchFontSelectType( p_drawglb, cp_glb->now_select, heap );
		p_draw->now_select =  cp_glb->now_select;
	}

	if( p_draw->sort_type != cp_glb->sort_type ){
		ZKnSortSearchFontSortType( p_drawglb, cp_glb->sort_type, heap );
		p_draw->sort_type =  cp_glb->sort_type;
	}

	if( p_draw->search_name != cp_glb->search_name ){
		ZKnSortSearchFontSearchName( p_drawglb, cp_glb->search_name, heap );
		p_draw->search_name =  cp_glb->search_name;
	}

	if( p_draw->search_type1 != cp_glb->search_type1 ){
		ZKnSortSearchFontSearchType1( p_drawglb, cp_glb->search_type1, heap );
		p_draw->search_type1 =  cp_glb->search_type1;
	}

	if( p_draw->search_type2 != cp_glb->search_type2 ){
		ZKnSortSearchFontSearchType2( p_drawglb, cp_glb->search_type2, heap );
		p_draw->search_type2 =  cp_glb->search_type2;
	}

	if( p_draw->search_form != cp_glb->search_form ){
		ZKnSortSearchOamSearchForm( p_draw, cp_glb->search_form );
		p_draw->search_form =  cp_glb->search_form;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	選択中の項目のBGを設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	type		ﾀｲﾌﾟ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchBgSelectType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	int x, y;
	int data_idx;

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	x = ZKN_SORTSEARCH_BG_X;
	switch( type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		y = ZKN_SORTSEARCH_BG_SORT_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_a_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		y = ZKN_SORTSEARCH_BG_NAME_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_b_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		y = ZKN_SORTSEARCH_BG_TYPE_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_c_lzh_NSCR;
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		y = ZKN_SORTSEARCH_BG_FORM_Y;
		data_idx = NARC_zukan_zkn_sort_bg_main1_d_lzh_NSCR;
		break;
	default:
		break;
	}

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, data_idx, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, x, y,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );


	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄﾀｲﾌﾟの文字ﾃﾞｰﾀ書き込み
 *
 *	@param	p_drawglb	描画
 *	@param	type		ﾀｲﾌﾟ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSortType( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	// 書き込む領域クリーン
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_SORT_Y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// 文字列
	msg_idx = ZNK_SORTSEARCH_SORT_00 + type;


	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_SORT_Y,
			0, ZKN_BG_FONT_COLOR2_MSK, NULL );

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	なまえサーチﾀｲﾌﾟ描画
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	type			サーチﾀｲﾌﾟ
 *	@param	heap			ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchName( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	int i;
	
	// 書き込む領域クリーン
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_NAME_Y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// 文字列
	switch( type ){
	case ZKN_POKELIST_SEARCH_NAME_NONE:
		msg_idx = ZNK_SORTSEARCH_NAME_00;
		break;
	case ZKN_POKELIST_SEARCH_NAME_A:
		msg_idx = ZNK_SORTSEARCH_NAME_01;
		break;
	case ZKN_POKELIST_SEARCH_NAME_KA:
		msg_idx = ZNK_SORTSEARCH_NAME_02;
		break;
	case ZKN_POKELIST_SEARCH_NAME_SA:
		msg_idx = ZNK_SORTSEARCH_NAME_03;
		break;
	case ZKN_POKELIST_SEARCH_NAME_TA:
		msg_idx = ZNK_SORTSEARCH_NAME_04;
		break;
	case ZKN_POKELIST_SEARCH_NAME_NA:
		msg_idx = ZNK_SORTSEARCH_NAME_05;
		break;
	case ZKN_POKELIST_SEARCH_NAME_HA:
		msg_idx = ZNK_SORTSEARCH_NAME_06;
		break;
	case ZKN_POKELIST_SEARCH_NAME_MA:
		msg_idx = ZNK_SORTSEARCH_NAME_07;
		break;
	case ZKN_POKELIST_SEARCH_NAME_RA:
		msg_idx = ZNK_SORTSEARCH_NAME_09;
		break;
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		msg_idx = ZNK_SORTSEARCH_NAME_08;
		break;
	}


	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );


	if( type == 0 ){
		for( i=0; i<ZKN_SORTSEARCH_FONT_BG_NAME_BOU_NUM; i++ ){
			GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
					ZKN_SORTSEARCH_FONT_BG_X + (ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X * i),
					ZKN_SORTSEARCH_FONT_BG_NAME_Y,
					0, ZKN_BG_FONT_COLOR2_MSK, NULL );
		}
	}else{
		GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
				ZKN_SORTSEARCH_FONT_BG_X, ZKN_SORTSEARCH_FONT_BG_NAME_Y,
				0, ZKN_BG_FONT_COLOR2_MSK, NULL );
	}

	STRBUF_Delete(str);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ　検索ﾀｲﾌﾟ描画		共通部分
 *
 *	@param	p_drawglb
 *	@param	type
 *	@param	heap
 *	@param	y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType_Core( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap, int y )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	int i;
	
	// 書き込む領域クリーン
	GF_BGL_BmpWinFill( &p_draw_glb->bmp_mfont, 0, 
			ZKN_SORTSEARCH_FONT_BG_X, y,
			ZKN_SORTSEARCH_FONT_BG_AREA_X, ZKN_SORTSEARCH_FONT_BG_AREA_Y );

	// 文字列
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_NONE:
		msg_idx = ZNK_SORTSEARCH_NAME_00;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		msg_idx = ZNK_SORTSEARCH_TYPE_00;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		msg_idx = ZNK_SORTSEARCH_TYPE_06;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		msg_idx = ZNK_SORTSEARCH_TYPE_09;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		msg_idx = ZNK_SORTSEARCH_TYPE_07;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		msg_idx = ZNK_SORTSEARCH_TYPE_08;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		msg_idx = ZNK_SORTSEARCH_TYPE_12;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		msg_idx = ZNK_SORTSEARCH_TYPE_11;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		msg_idx = ZNK_SORTSEARCH_TYPE_13;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		msg_idx = ZNK_SORTSEARCH_TYPE_16;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		msg_idx = ZNK_SORTSEARCH_TYPE_01;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		msg_idx = ZNK_SORTSEARCH_TYPE_02;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		msg_idx = ZNK_SORTSEARCH_TYPE_04;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		msg_idx = ZNK_SORTSEARCH_TYPE_03;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		msg_idx = ZNK_SORTSEARCH_TYPE_10;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		msg_idx = ZNK_SORTSEARCH_TYPE_05;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		msg_idx = ZNK_SORTSEARCH_TYPE_14;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		msg_idx = ZNK_SORTSEARCH_TYPE_15;
		break;
	}

	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( msg_idx, heap );


	if( type == 0 ){
		for( i=0; i<ZKN_SORTSEARCH_FONT_BG_TYPE_BOU_NUM; i++ ){
			GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
					ZKN_SORTSEARCH_FONT_BG_X + (ZKN_SORTSEARCH_FONT_BG_BOU_SIZE_X * i),
					y,
					0, ZKN_BG_FONT_COLOR2_MSK, NULL );
		}
	}else{
		GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
				ZKN_SORTSEARCH_FONT_BG_X, y,
				0, ZKN_BG_FONT_COLOR2_MSK, NULL );
	}

	STRBUF_Delete(str);
}


//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1　検索ﾀｲﾌﾟを表示
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	type		ﾀｲﾌﾟ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType1( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKnSortSearchFontSearchType_Core( p_drawglb, type, heap, ZKN_SORTSEARCH_FONT_BG_TYPE1_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1　検索ﾀｲﾌﾟを表示
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	type		ﾀｲﾌﾟ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchFontSearchType2( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int type, int heap )
{
	ZKnSortSearchFontSearchType_Core( p_drawglb, type, heap, ZKN_SORTSEARCH_FONT_BG_TYPE2_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	けいじょう　検索ﾀｲﾌﾟを表示
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	type		ﾀｲﾌﾟ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZKnSortSearchOamSearchForm( ZKN_SORTSEARCH_DRAW* p_draw, int type )
{
	if( type == 0 ){
		CLACT_SetDrawFlag( p_draw->search_form_act, FALSE );
	}else{
		CLACT_SetDrawFlag( p_draw->search_form_act, TRUE );

		switch( type ){
		case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_FOUR_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TWO_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TAIL:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TAIL );
			break;
		case ZKN_POKELIST_SEARCH_FORM_HARABAI:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_HARABAI );
			break;
		case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_FOUR_WING );
			break;
		case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_TWO_WING );
			break;
		case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_HAITSUKUBARI );
			break;
		case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_STRAIGHT );
			break;
		case ZKN_POKELIST_SEARCH_FORM_ARM:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_ARM );
			break;
		case ZKN_POKELIST_SEARCH_FORM_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_MANY_LEGS );
			break;
		case ZKN_POKELIST_SEARCH_FORM_WATER:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_WATER );
			break;
		case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_CIRCLE );
			break;
		case ZKN_POKELIST_SEARCH_FORM_COMP:
			CLACT_AnmChg( p_draw->search_form_act, ZKN_SORTSEARCH_FORM_OAM_COMP );
			break;
		default:
			break;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄｻｰﾁフェードシステム
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルﾃﾞｰﾀ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchFadeSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	// フェード処理初期化
	if( cp_glb->fade_count == ZKN_SORTSEARCH_FADECOUNT_MAX ){

		if( cp_glb->fade_mode == ZKN_SORTSEARCH_FADEOUT ){
			ZKN_UTIL_BgShutterFadeInit( &p_draw->shutter,
					p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
					p_draw->p_scrn, 
					ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S, ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S, 
					ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S, ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S, ZKN_SORTSEARCH_FADECOUNT_MAX );
		}else{
			
			// フェードインのときはFONTBG設定を変更
			ZknSortSearchSortEffFontReset( p_drawglb, p_draw, heap );
			
			ZKN_UTIL_BgShutterFadeInit( &p_draw->shutter,
					p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
					p_draw->p_scrn, 
					ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S, ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S, 
					ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S, ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S, ZKN_SORTSEARCH_FADECOUNT_MAX );
		}
		
	}

	// 動作
	ZKN_UTIL_BgShutterFade( &p_draw->shutter );
}

//----------------------------------------------------------------------------
/**
 *	@brief	検索中エフェクト動作
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		ﾃﾞｰﾀグローバル 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffSys( ZKN_SORTSEARCH_DRAW* p_draw, ZKN_SORTSEARCH_DRAWGLB* p_drawglb, const ZKN_SORTSEARCH_GLB* cp_glb, int heap )
{
	int set_rota;
	int  count;
	
	// 動作処理初期化
	if( cp_glb->fade_count == ZKN_SORTSEARCH_DO_MAIN_EFF_COUNT_MAX ){
		
		CLACT_SetDrawFlag( p_draw->sort_act, TRUE );
		// フォントBG設定
		ZknSortSearchSortEffFontSet( p_drawglb, heap );
		
	}else if( cp_glb->fade_count == 0 ){		// 破棄処理
		
		CLACT_SetDrawFlag( p_draw->sort_act, FALSE );
		// フォントBG破棄
		GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	}

	// OAMを回転させる
	count = ZKN_SORTSEARCH_FADECOUNT_MAX - cp_glb->fade_count;
	set_rota = ZKN_SORTSEARCH_EFECT_OAM_ROTA * count;
	set_rota = set_rota / ZKN_SORTSEARCH_FADECOUNT_MAX;

	CLACT_SetRotation( p_draw->sort_act, (u16)set_rota );
}

//----------------------------------------------------------------------------
/**
 *	@brief	検索中文字を表示
 *	
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffFontSet( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	STRBUF* str;
	int msg_idx;
	
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );


	// 文字列を書き込む
	str = ZKN_UTIL_ZknGmmGet( ZNK_SORTSEARCH_MSG_00, heap );
	GF_STR_PrintColor( &p_draw_glb->bmp_mfont, FONT_SYSTEM, str, 
			ZKN_SORTSEARCH_EFECT_FONT_X, ZKN_SORTSEARCH_EFECT_FONT_Y,
			0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);

	// 表示優先順位を変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 0 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントBGを元に戻す
 *
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSortEffFontReset( ZKN_SORTSEARCH_DRAWGLB* p_drawglb, ZKN_SORTSEARCH_DRAW* p_draw, int heap )
{
	// 表示優先順位を変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_FONT_M, 1 );
	GF_BGL_PrioritySet( ZKN_BG_FRM_UTIL_M, 0 );

	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	ZknSortSearchBgSelectType( p_drawglb, p_draw->now_select, heap );
	ZknSortSearchFontSelectType( p_drawglb, p_draw->now_select, heap );
	ZKnSortSearchFontSortType( p_drawglb, p_draw->sort_type, heap );
	ZKnSortSearchFontSearchName( p_drawglb, p_draw->search_name, heap );
	ZKnSortSearchFontSearchType1( p_drawglb, p_draw->search_type1, heap );
	ZKnSortSearchFontSearchType2( p_drawglb, p_draw->search_type2, heap );
	ZKnSortSearchOamSearchForm( p_draw, p_draw->search_form );
}
