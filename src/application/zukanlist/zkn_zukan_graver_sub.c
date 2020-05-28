//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_zukan_graver_sub.c
 *	@brief		すがた画面
 *	@author		tomoya takahashi
 *	@data		2006.03.07
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/gflib/vram_transfer_manager.h"
#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_cursor.h"
#include "include/application/zukanlist/zkn_zukan_graver.h"

#define	__ZKN_ZUKAN_GRAVER_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_zukan_graver_sub.h"

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
#define ZKN_GRAPHIC_SUB_EVENT_NUM ( 0 )	// イベント数

#define ZKN_GRAPHIC_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_GRAPHICSUB_SEQINIT_ALLOC,
	ZKN_GRAPHICSUB_SEQINIT_LOAD,
	ZKN_GRAPHICSUB_SEQINIT_FADEIN,
	ZKN_GRAPHICSUB_SEQINIT_END,
};
enum{
	ZKN_GRAPHICSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_GRAPHICSUB_SEQDELETE_FADEOUT,
	ZKN_GRAPHICSUB_SEQDELETE_RELEASE,
	ZKN_GRAPHICSUB_SEQDELETE_FREE,
	ZKN_GRAPHICSUB_SEQDELETE_END,
};





//-------------------------------------
//	ボタン種類
//=====================================
enum{
	ZKN_GRAPHICSUB_BUTTON_GRAPHIC,
	ZKN_GRAPHICSUB_BUTTON_NUM,
};
#define ZKN_GRAPHICSUB_BUTTON_DEF_Y		( 144 )
#define ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X	( 128 )
#define ZKN_GRAPHICSUB_BUTTON_SIZE_X	( 240 )
#define ZKN_GRAPHICSUB_BUTTON_SIZE_Y	( 80 )
#define ZKN_GRAPHICSUB_BUTTON_ANM_SEQ	( 2 )
#define ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO	(4)

#define ZKN_GRAPHICSUB_CURSOR_SIZE_X	( 228 )
#define ZKN_GRAPHICSUB_CURSOR_SIZE_Y	( 64 )

// FONTOAM
#define ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CX ( 16 )
#define ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_GRAPHICSUB_BUTTON_PAL_OFS			( 4 )
#define ZKN_GRAPHICSUB_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_GRAPHICSUB_BUTTON_FONT_OFS_X		( -60 )
#define ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y		( -8 )

#define ZKN_GRAPHICSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	おおきさくらべサブ画面　グローバル変数
//=====================================
typedef struct {
	int* p_event_key;

	ZKN_GLB_DATA* p_glb;
	
	// 図鑑コモンサブアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;

	// 図鑑すがた画面メイン
	ZKN_APL_DATA* p_zukan_sugata_apl;
} ZKN_GRAPHIC_SUB_GLB;

//-------------------------------------
//	大きさぐらべサブ画面画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_GRAPHIC_SUB_DRAWGLB;

//-------------------------------------
//	ボタンコールバックへのワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_GRAPHIC_BUTTON_CALLBACK;

//-------------------------------------
//	おおきさくらべサブ画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_GRAPHIC_BUTTON_CALLBACK callcack;

	// アプリデータ
	int button_event[ ZKN_GRAPHICSUB_BUTTON_NUM ];	// ボタンイベントデータ

	// メイン画面を変更するリクエストフラグ
	BOOL change_apl_req;
} ZKN_GRAPHIC_SUB_WORK;

//-------------------------------------
//	おおきさくらべサブ画面画面　内部ワーク
//=====================================
typedef struct {
	// ボタングラフィック
	CLACT_WORK_PTR button[ ZKN_GRAPHICSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_GRAPHICSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// カーソル
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];

	int	bgpltt_no[ ZKN_GRAPHICSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_GRAPHICSUB_BUTTON_NUM ];
} ZKN_GRAPHIC_SUB_DRAW;


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
static ZKN_GRAPHIC_SUB_GLB* MakeGraphicSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_GRAPHIC_SUB_DRAWGLB* MakeGraphicSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeGraphicSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGraphicSubGlb( ZKN_GRAPHIC_SUB_GLB* p_glb );
static void DeleteGraphicSubDrawGlb( ZKN_GRAPHIC_SUB_DRAWGLB* p_glb );
static void DeleteGraphicSubEvent( ZKN_EVENT_DATA* p_event );


static int GraphicSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknGraphicSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknGraphicSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknGraphicSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknGraphicSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknGraphicSubOamFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubOamFadeDelete( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknGraphicSubFadeMain( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out );

// ボタン制御
static void ZknGraphicSubButtonMake( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb, int heap );
static void ZknGraphicSubButtonEventBuffInit( ZKN_GRAPHIC_SUB_WORK* p_work );
static void ZknGraphicSubButtonMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb );
static void ZknGraphicSubButtonDelete( ZKN_GRAPHIC_SUB_WORK* p_work );
static void ZknGraphicSubButtonCallBack( u32 button_no, u32 event, void* p_work );


// ボタン描画制御
static void ZknGraphicSubButtonControl( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );
static void ZknGraphicSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );
static void ZknGraphicSubButtonDrawMain( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, ZKN_GRAPHIC_SUB_DRAW* p_draw, const ZKN_GRAPHIC_SUB_WORK* cp_work, int heap );


// 次のグラフィックに変更する
static void ZknGraphicSubNextGraphicChange( const ZKN_GRAPHIC_SUB_GLB* cp_glb );

// カーソル制御
static void ZknGraphicSubCursorMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb );
static void ZknGraphicSubCursorDraw( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb );
static void ZknGraphicSubCursorMatSet( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y );



// 読み込み
static void ZknGraphicSubLoadResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubReleaseResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubSetUpBg( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubLoadOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubReleaseOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb );
static void ZknGraphicSubAddClact( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubDeleteClact( ZKN_GRAPHIC_SUB_DRAW* p_draw );
static void ZknGraphicSubAddFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknGraphicSubDeleteFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　アプリ作成
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
void ZKN_GraphicSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_GRAPHIC_SUB_GLB*	p_glb;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeGraphicSubGlb( heap, zkn_sys );
	p_drawglb = MakeGraphicSubDrawGlb( heap, zkn_sys );
	p_event = MakeGraphicSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= GraphicSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknGraphicSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknGraphicSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknGraphicSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknGraphicSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknGraphicSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknGraphicSubProcDrawFuncDelete;
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
void ZKN_GraphicSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteGraphicSubGlb( p_data->p_glb_data ); 
	DeleteGraphicSubDrawGlb( p_data->p_glb_draw ); 
	DeleteGraphicSubEvent( p_data->p_event_data );
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_GRAPHIC_SUB_GLB* MakeGraphicSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_GRAPHIC_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_GRAPHIC_SUB_GLB) );

	// 変数初期化
	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// 図鑑コモンアプリグローバルデータ
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	// 図鑑姿画面メイン　アプリデータ
	p_glb->p_zukan_sugata_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_GRAPHIC_SUB_DRAWGLB* MakeGraphicSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_GRAPHIC_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_GRAPHIC_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_GRAPHIC_SUB_DRAWGLB) );


	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeGraphicSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
/*	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = GraphicSubEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeGraphicMain( heap, &p_event_tbl[0], zkn_sys, ZKN_GRAPHIC_SUB_EVENT_CHANGE_GRAPHIC );
	ZKN_EVENT_MakeChangeGraphicWeightMain( heap, &p_event_tbl[1], zkn_sys, ZKN_GRAPHIC_SUB_EVENT_CHANGE_WEIGHT );

	return p_event_tbl;//*/
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubGlb( ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubDrawGlb( ZKN_GRAPHIC_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGraphicSubEvent( ZKN_EVENT_DATA* p_event )
{
/*	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );

	sys_FreeMemoryEz( p_event );//*/
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	おおきさくらべサブ画面アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	おおきさくらべサブ画面アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int GraphicSubEventDataNumGet( void )
{
	return ZKN_GRAPHIC_SUB_EVENT_NUM;
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
static int ZknGraphicSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_GRAPHIC_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_GRAPHIC_SUB_WORK) );

	// ボタンイベントデータ
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// ボタンイベントデータ
	}

	// ボタンを作成
	ZknGraphicSubButtonMake( p_work, p_glb, p_dodata->heap );

	// ボタンの状態を１回設定
	// ボタン動作
	ZknGraphicSubButtonMove( p_work, p_glb );


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
static int ZknGraphicSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( p_glb->cp_zukan_common_apl ) ){

		// ボタンイベントバッファ初期化
		ZknGraphicSubButtonEventBuffInit( p_work );
		
		// カーソル動作
		// カーソル動作有効で、サブアプリにカーソル動作が許されているときのみ
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknGraphicSubCursorMove( p_work, p_glb );
		}
		
		// ボタン動作
		ZknGraphicSubButtonMove( p_work, p_glb );

		// 次のアプリへのフラグがたったら移行する
		if( p_work->change_apl_req ){
			ZknGraphicSubNextGraphicChange( p_glb );
			p_work->change_apl_req = FALSE;
		}
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
static int ZknGraphicSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_glbdata;
	ZKN_GRAPHIC_SUB_WORK* p_work = p_dodata->p_work;

	// ボタン破棄
	ZknGraphicSubButtonDelete( p_work );

	// ワーク破棄
	sys_FreeMemoryEz( p_work );

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
static int ZknGraphicSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_GRAPHICSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_GRAPHIC_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_GRAPHIC_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_LOAD:
		// Resource読み込み
		ZknGraphicSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// フェード処理
		ZknGraphicSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_FADEIN:
		
		if( ZknGraphicSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_GRAPHICSUB_SEQINIT_END:
		// カーソルアニメ開始
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, FALSE );
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
static int ZknGraphicSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){
		
		// ボタン描画メイン
		ZknGraphicSubButtonDrawMain( p_drawglb, p_drawwork, cp_datawork, p_drawdata->heap );

		// カーソル描画メイン
		ZknGraphicSubCursorDraw( p_drawglb, cp_dataglb );
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
static int ZknGraphicSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_GRAPHIC_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_GRAPHIC_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_GRAPHIC_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_GRAPHIC_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_GRAPHICSUB_SEQDELETE_FADEOUT_INIT:
		// カーソルアニメ停止
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// フェード処理
		ZknGraphicSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQDELETE_FADEOUT:
		if( ZknGraphicSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_GRAPHICSUB_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknGraphicSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_GRAPHICSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_GRAPHICSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理	初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubOamFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEを半透明にする
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_XLU );
		FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_XLU );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理　後処理
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubOamFadeDelete( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEをノーマルにする
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_ObjModeSet( p_draw->button[ i ], GX_OAM_MODE_NORMAL );
		FONTOAM_ObjModeSet( p_draw->p_button_font[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面フェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト FALSE	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubFadeInit( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknGraphicSubOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_GRAPHICSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_GRAPHICSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理　メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト　FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknGraphicSubFadeMain( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// ブライトネスしよう許可でてるかチェック
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );
	}else{
//		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade_sub );
		check = IsFinishedBrightnessChg( MASK_SUB_DISPLAY );
	}

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknGraphicSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	ボタン作成関数
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonMake( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_GRAPHICSUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ],
			ZKN_GRAPHICSUB_BUTTON_DEF_Y - (ZKN_GRAPHICSUB_BUTTON_SIZE_Y/2),
			ZKN_GRAPHICSUB_BUTTON_DEF_Y + (ZKN_GRAPHICSUB_BUTTON_SIZE_Y/2),
			ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X - (ZKN_GRAPHICSUB_BUTTON_SIZE_X/2),
			ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X + (ZKN_GRAPHICSUB_BUTTON_SIZE_X/2) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_GRAPHICSUB_BUTTON_NUM,
			ZknGraphicSubButtonCallBack,
			&p_work->callcack,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンイベントバッファ初期化
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonEventBuffInit( ZKN_GRAPHIC_SUB_WORK* p_work )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタン動作処理
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	BMN_Main( p_work->p_button_man );

	if( p_work->change_apl_req ){
		p_work->button_event[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = BMN_EVENT_HOLD;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonDelete( ZKN_GRAPHIC_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンコールバック関数
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		ボタンイベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_GRAPHIC_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_GRAPHIC_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_GRAPHIC_SUB_WORK* p_subwork = p_work_data->p_work;

	// ボタンイベント格納
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_TOUCH:
		switch( button_no ){
		case ZKN_GRAPHICSUB_BUTTON_GRAPHIC:
			// 次の絵へ
			p_subwork->change_apl_req = TRUE;
			break;
			
		default:
			break;
		}
		break;

	case BMN_EVENT_HOLD:		///< おしっぱ
		switch( button_no ){
		case ZKN_GRAPHICSUB_BUTTON_GRAPHIC:
			// 次の絵へ
			p_subwork->change_apl_req = TRUE;
			break;
			
		default:
			break;
		}
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック初期化処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubLoadResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	// 背景
	ZknGraphicSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknGraphicSubLoadOamData( p_draw, p_drawglb, heap );

	// セルアクター登録
	ZknGraphicSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM登録
	ZknGraphicSubAddFontOam( p_draw, p_drawglb, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック破棄処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubReleaseResource( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// パレットをリセット
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO*32, 32, heap );
	
	// セルアクター破棄
	ZknGraphicSubDeleteClact( p_draw );

	// FONTOAM破棄
	ZknGraphicSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknGraphicSubReleaseOamData( p_draw, p_drawglb );

	// パレットバッファ破棄
	for( i=0;i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		if( p_draw->pltt_buff[i] ){
			sys_FreeMemoryEz( p_draw->pltt_buff[i] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面セットアップ
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubSetUpBg( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub0_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubLoadOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_draw_glb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_GRAPHIC_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース破棄
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubReleaseOamData( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubAddClact( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_GRAPHIC_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_GRAPHIC_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_GRAPHIC_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_GRAPHIC_SUB_OAM_BG_PTR,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 31;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// 別の姿
	add.mat.x = ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X << FX32_SHIFT;
	add.mat.y = ZKN_GRAPHICSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ], ZKN_GRAPHICSUB_BUTTON_ANM_SEQ );	

}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubDeleteClact( ZKN_GRAPHIC_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->button[ i ] );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubAddFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] );

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_GRAPHICSUB_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_GRAPHIC_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_GRAPHICSUB_BUTTONFONT_BMP_SIZE_CY );

	// すがた
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SHAPE_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ];
	p_draw->p_button_font[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_GRAPHICSUB_BUTTON_GRAPHIC ]->p_fontoam, pltt_ofs + ZKN_GRAPHICSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubDeleteFontOam( ZKN_GRAPHIC_SUB_DRAW* p_draw, ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_button_font[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン描画制御
 *
 *	@param	button		ボタンアクター
 *	@param	event		イベント
 *	@param	p_fontoam	フォントOAM
 *	@param	def_y		Y距離
 *	@param	bgpltt_no	BGパレットNO
 *	@param	heap		ヒープ
 *	@param	off_fontoam_pl	フォントOAMオフ時
 *	@param	on_fontoam_pl	フォントOAMオン時
 *	@param	パレットバッファ	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonControl( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	
	// ボタン動作
	ZKN_UTIL_ButtonMove( button,
			event );

	ZknGraphicSubFontButtonMove( 
			button,
			p_fontoam,
			def_y,
			off_fontoam_pl,
			on_fontoam_pl );

	// 現在フレーム取得
	now_frm = CLACT_AnmFrameGet( button );


	// カラーパレット設定
	switch( now_frm ){
	case ZKN_UTIL_BUTTON_FRAME_NONE:
	case ZKN_UTIL_BUTTON_FRAME_PUSH1:
		if( *p_nowbgpltt_no != 0 ){
			// off_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_4_NCLR;
			*p_nowbgpltt_no = 0;
		}
		break;
	case ZKN_UTIL_BUTTON_FRAME_PUSH2:
		if( *p_nowbgpltt_no != 1 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_5_NCLR;
			*p_nowbgpltt_no = 1;
		}
		break;

	case ZKN_UTIL_BUTTON_FRAME_SELECT:
		if( *p_nowbgpltt_no != 2 ){
			// on_pltt
			chenge = TRUE;
			arc_data_idx = NARC_zukan_zkn_data_3_NCLR;
			*p_nowbgpltt_no = 2;
		}
		break;
	}
	if( chenge ){
		// 今までのを破棄
		if( *buff ){
			sys_FreeMemoryEz( *buff );
		}
		*buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, arc_data_idx, &p_plt, heap );
		// TransferManagerに登録
		check = AddVramTransferManager(
				NNS_GFD_DST_2D_BG_PLTT_SUB,
				bgpltt_no*32,
				p_plt->pRawData,
				32);
		// 転送タスク生成失敗
		GF_ASSERT( check );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォント動作
 *
 *	@param	act				アクター
 *	@param	p_fontoam		フォントOAM
 *	@param	def_y			デフォルトY位置
 *	@param	off_pltt		ボタンOFF時のカラーパレット
 *	@param	on_pltt			ボタンON時のカラーパレット
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	int now_frm;
	
	ZKN_UTIL_ButtonFontMove( 
			act,
			p_fontoam,
			def_y );

	// 現在フレーム取得
	now_frm = CLACT_AnmFrameGet( act );

	// カラーパレット設定
	if( now_frm < ZKN_UTIL_BUTTON_FRAME_PUSH2 ){
		// off_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, off_pltt );
	}else{
		// on_pltt
		FONTOAM_SetPaletteOffsetAddTransPlttNo( p_fontoam->p_fontoam, on_pltt );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン描画処理メイン
 *
 *	@param	p_draw	描画ワーク
 *	@param	cp_work	ワーク
 *	@parma	heap	ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubButtonDrawMain( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, ZKN_GRAPHIC_SUB_DRAW* p_draw, const ZKN_GRAPHIC_SUB_WORK* cp_work, int heap )
{
	int i;	// ループ用
	int bgpltt_no;

	// ボタン表示動作
	for( i=0; i<ZKN_GRAPHICSUB_BUTTON_NUM; i++ ){

		bgpltt_no = ZKN_GRAPHICSUB_BUTTON_GRAPHICBG_PLTT_NO;
		
		ZknGraphicSubButtonControl( p_drawglb,
				p_draw->button[i],
				p_draw->p_button_font[i], cp_work->button_event[i],
				ZKN_GRAPHICSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
				&p_draw->bgpltt_no[i], heap,
				ZKN_GRAPHICSUB_BUTTON_PAL_OFS, 
				ZKN_GRAPHICSUB_BUTTON_PAL_OFS_ON,
				&p_draw->pltt_buff[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	大きさ比べカーソル制御
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorMove( ZKN_GRAPHIC_SUB_WORK* p_work, ZKN_GRAPHIC_SUB_GLB* p_glb )
{
	// Aボタンでアプリケーションを分岐
	if( sys.cont & PAD_BUTTON_A ){
		// 次の絵へ
		p_work->change_apl_req = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	大きさ比べカーソル描画制御
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		データグローバル 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorDraw( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, const ZKN_GRAPHIC_SUB_GLB* cp_glb )
{
	
	// 自分の座標を設定してよいかチェック
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		ZknGraphicSubCursorMatSet( p_drawglb, ZKN_GRAPHICSUB_BUTTON_GRAPHIC_X, ZKN_GRAPHICSUB_BUTTON_DEF_Y, ZKN_GRAPHICSUB_CURSOR_SIZE_X, ZKN_GRAPHICSUB_CURSOR_SIZE_Y );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル座標設定
 *
 *	@param	p_drawglb
 *	@param	x
 *	@param	y
 *	@param	size_x
 *	@param	size_y 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubCursorMatSet( ZKN_GRAPHIC_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}


//----------------------------------------------------------------------------
/**
 *	@brief	次の絵へ変更
 *
 *	@param	cp_glb	グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknGraphicSubNextGraphicChange( const ZKN_GRAPHIC_SUB_GLB* cp_glb )
{
	// 次の絵へ
	ZKN_ZukanGraverDrawTypeAdd( cp_glb->p_zukan_sugata_apl, 1 );
}
