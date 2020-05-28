//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big.c
 *	@brief		大きさ比べアプリケーション	高さ比べ
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
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"


#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"

#define	__ZKN_BIG_H_GLOBAL
#include "include/application/zukanlist/zkn_big.h"


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
#ifdef PM_DEBUG
#define ZKN_BIG_EVENT_NUM ( 1 )	// イベント数
#define ZKN_BIG_EVENT_CHANGE_DEBUG	(0x1 << 1)	// DEBUGがめんへ
#else
#define ZKN_BIG_EVENT_NUM ( 0 )	// イベント数
//#define ZKN_BIG_EVENT_CHANGE_ZUKAN	(0x1 << 1)	// 図鑑へ
#endif

#define ZKN_BIG_OAM_BG_PRI	( 1 )
#define ZKN_BIG_OAM_PRI	( 31 )

// フェード用
#define ZKN_BIG_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_BIG_SEQINIT_ALLOC,
	ZKN_BIG_SEQINIT_LOAD,
	ZKN_BIG_SEQINIT_FADEIN,
	ZKN_BIG_SEQINIT_END,
};
enum{
	ZKN_BIG_SEQDELETE_FADEOUT_INIT,
	ZKN_BIG_SEQDELETE_FADEOUT,
	ZKN_BIG_SEQDELETE_RELEASE,
	ZKN_BIG_SEQDELETE_FREE,
	ZKN_BIG_SEQDELETE_END,
};

// 確保文字列バッファサイズ
#define ZKN_BIG_HEIGHT_NUM_STR	( 32 )

// 文字列描画位置
#define ZKN_BIG_HEIGHT_TITLE_X	( 96 )		// タイトル
#define ZKN_BIG_HEIGHT_TITLE_Y	( 24 )
#define ZKN_BIG_HEIGHT_TAKASA_Y	( 168 )		// "高さ"
#define ZKN_BIG_HEIGHT_TAKASA1_X	( 32 )
#define ZKN_BIG_HEIGHT_TAKASA2_X	( 152 )
#define ZKN_BIG_HEIGHT_NUM_OFS_X	( 32 )	// 実際の値を表示する高さからの位置
#define ZKN_BIG_HEIGHT__M__OFS_X	( 30 )	// Mを表示する値からの位置
#define ZKN_BIG_HEIGHT_NAME_Y		( 152 )
#define ZKN_BIG_HEIGHT_MONSNAME_X	( 24 )
#define ZKN_BIG_HEIGHT_HERO_X		( 146 )

// 主人公基本表示位置
#define ZKN_BIG_HEIGHT_HERO_DEF_X	( 168 )
#define ZKN_BIG_HEIGHT_HERO_DEF_Y	( 88 )
#define ZKN_BIG_HEIGHT_HERO_ANM_SEQ_MAN		( 5 )
#define ZKN_BIG_HEIGHT_HERO_ANM_SEQ_GIRL	( 6 )

// ポケモングラフィック
#define ZKN_BIG_HEIGHT_POKEGRA_DEF_X	( 88 )
#define ZKN_BIG_HEIGHT_POKEGRA_DEF_Y	( ZKN_BIG_HEIGHT_HERO_DEF_Y )


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	大きさ比べ画面　グローバル変数
//=====================================
typedef struct {
	int* p_event_key;		// イベントキー
	
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ

	// メインコモングローバル
	ZKN_APL_DATA*	p_main_common;	// アプリデータ
} ZKN_BIG_GLB;

//-------------------------------------
//	大きさ比べ画面	描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ

#ifdef PM_DEBUG
	short hero_scale;
	BOOL reflect_scale;
	short hero_yofs;
	BOOL reflect_yofs;
#endif
} ZKN_BIG_DRAWGLB;

//-------------------------------------
//	大きさ比べ画面　内部ワーク
//=====================================
typedef struct {
	int dummy;
} ZKN_BIG_WORK;

//-------------------------------------
//	大きさ比べ画面　内部ワーク
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	CLACT_WORK_PTR hero;
} ZKN_BIG_DRAW;

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
static ZKN_BIG_GLB* MakeBigGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_DRAWGLB* MakeBigDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigGlb( ZKN_BIG_GLB* p_glb );
static void DeleteBigDrawGlb( ZKN_BIG_DRAWGLB* p_glb );
static void DeleteBigEvent( ZKN_EVENT_DATA* p_event );


static int BigEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknBigProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknBigOamFadeInit( ZKN_BIG_DRAW* p_draw );
static void ZknBigOamFadeDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigFadeInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigFadeMain( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out );

// 読み込み処理
static void ZknBigLoadRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, const ZKN_BIG_WORK* cp_datawork, int heap );
static void ZknBigDeleteRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb );
static void ZknBigSetUpBg( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigOamResLoad( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, int heap );
static void ZknBigOamResDelete( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb );
static void ZknBigOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigOamDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigFontOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );
static void ZknBigFontOamDelete( ZKN_BIG_DRAW* p_draw );
static void ZknBigSetUpFontBgNormal( ZKN_BIG_DRAWGLB* p_drawglb, int heap );
static void ZknBigSetUpFontBgHeroPokeData( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap );

static void ZknBigPokeGraOn( ZKN_BIG_DRAWGLB* p_draw, const ZKN_BIG_GLB* cp_glb );
static void ZknBigPokeGraOff( ZKN_BIG_DRAWGLB* p_draw );

// 拡縮値設定用関数郡
static void ZknBigHeroYOfsSet( CLACT_WORK_PTR p_act, short yofs );
static void ZknBigPokeGraYOfsSet( SOFT_SPRITE* p_pokegra, short yofs );
static void ZknBigHeroScaleSet( CLACT_WORK_PTR p_act, short scale );
static void ZknBigPokeGraScaleSet( SOFT_SPRITE* p_pokegra, short scale );


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
void ZKN_BigAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_GLB*	p_glb;
	ZKN_BIG_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigGlb( heap, zkn_sys );
	p_drawglb = MakeBigDrawGlb( heap, zkn_sys );
	p_event = MakeBigEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigProcDrawFuncDelete;
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
void ZKN_BigAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigGlb( p_data->p_glb_data ); 
	DeleteBigDrawGlb( p_data->p_glb_draw ); 
	DeleteBigEvent( p_data->p_event_data );
}



#ifdef PM_DEBUG
//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹｸﾞﾗ拡縮値を設定
 *
 *	@param	p_data
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplPokeGraScaleSet( ZKN_APL_DATA* p_data, short scale )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	SOFT_SPRITE* pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	ZknBigPokeGraScaleSet( pokegra, scale );
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公拡縮値を設定
 *
 *	@param	p_data	
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplHeroGraScaleSet( ZKN_APL_DATA* p_data, short scale )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;

	p_drawglb->hero_scale = scale;
	p_drawglb->reflect_scale = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹｸﾞﾗYオフセット設定
 *
 *	@param	p_data
 *	@param	yofs 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplPokeGraYofsSet( ZKN_APL_DATA* p_data, short yofs )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;
	SOFT_SPRITE* pokegra = ZKN_GlbPokemonGraphicGet( p_drawglb->p_drawglb );
	ZknBigPokeGraYOfsSet( pokegra, yofs );
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公Yオフセット設定
 *
 *	@param	p_data
 *	@param	yofs 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_BigAplHeroGraYofsSet( ZKN_APL_DATA* p_data, short yofs )
{
	ZKN_BIG_DRAWGLB* p_drawglb = p_data->p_glb_draw;

	p_drawglb->hero_yofs = yofs;
	p_drawglb->reflect_yofs = TRUE;
}
#endif


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
static ZKN_BIG_GLB* MakeBigGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_GLB) );

	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys );

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// めいんグローバルアプリデータ取得
	p_glb->p_main_common = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバル作成
 *
 *	@param	heap	ヒープ
 *	@param	zkn_sys	図鑑システム
 *
 *	@return	作成データ
 */
//-----------------------------------------------------------------------------
ZKN_BIG_DRAWGLB* MakeBigDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_DRAWGLB) );

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
static ZKN_EVENT_DATA* MakeBigEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
#ifdef PM_DEBUG
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_BigHeightDebugApl( &p_event_tbl[0], zkn_sys, heap, ZKN_BIG_EVENT_CHANGE_DEBUG );

	return p_event_tbl;
#else
	return NULL;
#endif
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
static void DeleteBigGlb( ZKN_BIG_GLB* p_glb )
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
static void DeleteBigDrawGlb( ZKN_BIG_DRAWGLB* p_glb )
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
static void DeleteBigEvent( ZKN_EVENT_DATA* p_event )
{
#ifdef PM_DEBUG
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
#endif
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
static int BigEventDataNumGet( void )
{
	return ZKN_BIG_EVENT_NUM;
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
static int ZknBigProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK* p_work;
	
	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_BIG_WORK) );
	p_dodata->p_work = p_work;

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
static int ZknBigProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK*	p_work = p_dodata->p_work;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

#ifdef PM_DEBUG
	// LR同時押しでDEBUGがめんへ
	if( ((sys.cont & PAD_BUTTON_L) != 0) &&
		((sys.cont & PAD_BUTTON_R) != 0) ){
		*p_glb->p_event_key |= ZKN_BIG_EVENT_CHANGE_DEBUG;
	}
#endif

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
static int ZknBigProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_GLB* p_glb = p_glbdata;
	ZKN_BIG_WORK*	p_work = p_dodata->p_work;

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
static int ZknBigProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIG_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_DRAW) );

		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQINIT_LOAD:
		ZknBigLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );

		// フェード初期化
		ZknBigFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQINIT_FADEIN:
		if( ZknBigFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIG_SEQINIT_END:
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
static int ZknBigProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;


#ifdef PM_DEBUG
	if( p_drawglb->reflect_scale ){
		ZknBigHeroScaleSet( p_drawwork->hero, p_drawglb->hero_scale );
		p_drawglb->reflect_scale = FALSE;
	}
	if( p_drawglb->reflect_yofs ){
		ZknBigHeroYOfsSet( p_drawwork->hero, p_drawglb->hero_yofs );
		p_drawglb->reflect_yofs = FALSE;
	}
#endif
	
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
static int ZknBigProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_BIG_DRAW* p_drawwork = p_drawdata->p_work;


	switch( p_drawdata->seq ){
	case ZKN_BIG_SEQDELETE_FADEOUT_INIT:
		ZknBigFadeInit( p_drawwork, p_drawglb, cp_glbdata, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQDELETE_FADEOUT:
		if( ZknBigFadeMain( p_drawwork, p_drawglb, cp_glbdata, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIG_SEQDELETE_RELEASE:
		ZknBigDeleteRes( p_drawwork, p_drawglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIG_SEQDELETE_FREE:
		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIG_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigOamFadeInit( ZKN_BIG_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェードリセット
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigOamFadeDelete( ZKN_BIG_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->hero, GX_OAM_MODE_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理初期化
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigFadeInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknBigOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIG_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_MAIN );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@retval	TRUE	フェード終了
 *	@retval	FALSE	フェード途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknBigFadeMain( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// ブライトネスしよう許可でてるかチェック
	if( ZKN_ZukanCommonBrightnessOnFlagGet( cp_glb->p_main_common ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}else{
		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade );
	}

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknBigOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
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
static void ZknBigLoadRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, const ZKN_BIG_WORK* cp_datawork, int heap )
{
	// BG設定
	ZknBigSetUpBg( p_drawglb, cp_glb, heap );

	// フォントBG設定
	ZknBigSetUpFontBgNormal( p_drawglb, heap );	// 共通の文字列
	ZknBigSetUpFontBgHeroPokeData( p_drawglb, cp_glb, heap );	// データ

	// OAMリソース読み込み
	ZknBigOamResLoad( p_draw, p_drawglb, heap );

	// アクター登録
	ZknBigOamInit( p_draw, p_drawglb, cp_glb, heap );

	// FONTOAM
	ZknBigFontOamInit( p_draw, p_drawglb, cp_glb, heap );

	// ポケグラ表示
	ZknBigPokeGraOn( p_drawglb, cp_glb );
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
static void ZknBigDeleteRes( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb )
{

	// FONTOAM
	ZknBigFontOamDelete( p_draw );
	
	// アクター破棄
	ZknBigOamDelete( p_draw );

	// OAMリソース破棄
	ZknBigOamResDelete( p_draw, p_drawglb );

	// bmp破棄
	GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

	// ポケグラ非表示
	ZknBigPokeGraOff( p_drawglb );
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
static void ZknBigSetUpBg( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_main_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );
	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_height_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );

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
static void ZknBigOamResLoad(  ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_data_oam3_NCLR, FALSE, 
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_BIG_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_main3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
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
static void ZknBigOamResDelete( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb )
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
static void ZknBigOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	VecFx32				scale;
	short				ofs_y;
	short				scale_num;	
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );

	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_main3_lzh_NCGR + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam3_NCLR + ZKN_BIG_WEIGHT_RES_ID, 
			NARC_zukan_zkn_data_oam_main3_lzh_NCER + ZKN_BIG_WEIGHT_RES_ID,
			NARC_zukan_zkn_data_oam_main3_lzh_NANR + ZKN_BIG_WEIGHT_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_BIG_OAM_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;
	

	// 主人公データ取得
	ofs_y = ZKN_HEIGHTGRAM_GetHeightY_hero( cp_glb->p_glb->height_gram, monsno );
	scale_num = ZKN_HEIGHTGRAM_GetHeightScale_hero( cp_glb->p_glb->height_gram, monsno );	

	// 主人公
	add.mat.x = ZKN_BIG_HEIGHT_HERO_DEF_X << FX32_SHIFT;
	add.mat.y = (ZKN_BIG_HEIGHT_HERO_DEF_Y + ofs_y) << FX32_SHIFT;
	p_draw->hero = CLACT_AddSimple( &add );

	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_HEIGHT_HERO_ANM_SEQ_MAN );
	}else{
		CLACT_AnmChg( p_draw->hero, ZKN_BIG_HEIGHT_HERO_ANM_SEQ_GIRL );
	}

	// 拡縮値と座標を設定
	ZknBigHeroYOfsSet( p_draw->hero, ofs_y );
	ZknBigHeroScaleSet( p_draw->hero, scale_num );
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
static void ZknBigOamDelete( ZKN_BIG_DRAW* p_draw )
{
	CLACT_Delete( p_draw->hero );
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	p_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigFontOamInit( ZKN_BIG_DRAW* p_draw, ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_draw 描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigFontOamDelete( ZKN_BIG_DRAW* p_draw )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	FONTBGのセットアップ
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigSetUpFontBgNormal( ZKN_BIG_DRAWGLB* p_drawglb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_HEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// たかさくらべ
	MSGMAN_GetString( man, ZNK_BIG_00, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TITLE_X, ZKN_BIG_HEIGHT_TITLE_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// たかさ
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA1_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// たかさ
	MSGMAN_GetString( man, ZNK_ZUKAN_01, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名　主人公名　高さデータ　表示
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigSetUpFontBgHeroPokeData( ZKN_BIG_DRAWGLB* p_drawglb, const ZKN_BIG_GLB* cp_glb, int heap )
{
	STRBUF* str = STRBUF_Create(ZKN_BIG_HEIGHT_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_height_dat, heap);
	int mons_no =  ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );
	STRBUF* monsname_str = MSGDAT_UTIL_GetMonsName( mons_no, heap );
	
	// ポケモン名
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, monsname_str, ZKN_BIG_HEIGHT_MONSNAME_X, ZKN_BIG_HEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	//	ポケモンの高さ
	MSGMAN_GetString( man, mons_no, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA1_X + ZKN_BIG_HEIGHT_NUM_OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(monsname_str);

	MSGMAN_Delete(man);

	// 違うメッセージマネージャオープン
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// 主人公名
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, 
			ZKN_GLBDATA_HeroNameGet( cp_glb->p_glb ),
			ZKN_BIG_HEIGHT_HERO_X, ZKN_BIG_HEIGHT_NAME_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	
	// 主人公の高さ
	if( ZKN_GLBDATA_HeroSexGet( cp_glb->p_glb ) == 0 ){
		MSGMAN_GetString( man, ZNK_HEIGHT_00, str );
	}else{
		MSGMAN_GetString( man, ZNK_HEIGHT_01, str );
	}
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X + ZKN_BIG_HEIGHT_NUM_OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// M
	MSGMAN_GetString( man, ZNK_ZUKAN_03, str );
	GF_STR_PrintColor( &p_drawglb->p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_BIG_HEIGHT_TAKASA2_X + ZKN_BIG_HEIGHT_NUM_OFS_X + ZKN_BIG_HEIGHT__M__OFS_X, ZKN_BIG_HEIGHT_TAKASA_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示
 *
 *	@param	p_draw	描画グローバル
 *	@param	cp_glb	グローバルデータ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraOn( ZKN_BIG_DRAWGLB* p_draw, const ZKN_BIG_GLB* cp_glb )
{
	// 真っ黒いポケグラ表示
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_draw->p_drawglb );
	short ofs_y;
	short scale_num;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb->p_glb );


	// ポケモン表示データ取得
	ofs_y = ZKN_HEIGHTGRAM_GetHeightY_poke( cp_glb->p_glb->height_gram, monsno );
	scale_num = ZKN_HEIGHTGRAM_GetHeightScale_poke( cp_glb->p_glb->height_gram, monsno );
	
	
	// ポケモン設定
	ZKN_UTIL_PokemonGraphicSet( p_draw->p_drawglb, cp_glb->p_glb, monsno,
			PARA_FRONT, ZKN_BIG_HEIGHT_POKEGRA_DEF_X, ZKN_BIG_HEIGHT_POKEGRA_DEF_Y + ofs_y );
	
	// 表示
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, FALSE );

	// パレット変換で真っ黒に
	SoftSpritePalFadeSet( p_pokegra, 15, 15, 0, 0 );

	// Yオフセットと拡大縮小値設定
	ZknBigPokeGraYOfsSet( p_pokegra, ofs_y );
	ZknBigPokeGraScaleSet( p_pokegra, scale_num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック非表示
 *
 *	@param	p_draw	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraOff( ZKN_BIG_DRAWGLB* p_draw )
{
	SOFT_SPRITE* p_pokegra = ZKN_GlbPokemonGraphicGet( p_draw->p_drawglb );

	// 表示OFF
	SoftSpriteParaSet( p_pokegra, SS_PARA_VANISH, TRUE );

	// ソフトパレットフェードがかかっている可能性があるのでOFF
	SoftSpritePalFadeOff( p_pokegra );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Yオフセットとスケールを設定
 *
 *	@param	p_act		アクター
 *	@param	yofs		Yオフセット
 *	@param	scale		拡縮値パラメータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigHeroYOfsSet( CLACT_WORK_PTR p_act, short yofs )
{
	VecFx32				matrix;

	// 座標
	matrix.x = ZKN_BIG_HEIGHT_HERO_DEF_X << FX32_SHIFT;
	matrix.y = (ZKN_BIG_HEIGHT_HERO_DEF_Y + yofs) << FX32_SHIFT;
	CLACT_SetMatrix( p_act, &matrix );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Yオフセットとスケールを設定
 *
 *	@param	p_pokegra	ポケモングラフィック
 *	@param	yofs		Yオフセット
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraYOfsSet( SOFT_SPRITE* p_pokegra, short yofs )
{
	// Y座標
	SoftSpriteParaSet( p_pokegra, SS_PARA_POS_Y, ZKN_BIG_HEIGHT_POKEGRA_DEF_Y + yofs );
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公に拡縮値を設定
 *
 *	@param	p_act
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigHeroScaleSet( CLACT_WORK_PTR p_act, short scale )
{
	VecFx32				vec_scale;

	// 拡縮値を設定
	vec_scale.x = FX_Div( ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT, scale << FX32_SHIFT );
	vec_scale.y = vec_scale.x;
	CLACT_SetScaleAffine( p_act, &vec_scale, CLACT_AFFINE_DOUBLE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹｸﾞﾗに拡縮値を設定
 *
 *	@param	p_pokegra
 *	@param	scale 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBigPokeGraScaleSet( SOFT_SPRITE* p_pokegra, short scale )
{
	fx32 fx_scale;

	// scale_numは0x100を割る数になっている（OAM用の拡縮）
	// それを0x100で割る数に変更
	fx_scale = FX_Div( ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT, scale << FX32_SHIFT );
	scale = FX_Mul( fx_scale, ZKN_HEIGHT_SCALDE_DEF << FX32_SHIFT ) >> FX32_SHIFT;
	
	// 拡縮設定
	SoftSpriteParaSet( p_pokegra, SS_PARA_AFF_X, scale );
	SoftSpriteParaSet( p_pokegra, SS_PARA_AFF_Y, scale );
}

