//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_big_sub.c
 *	@brief		おおきさくらべサブ画面
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
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

#define	__ZKN_BIG_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_big_sub.h"

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
#define ZKN_BIG_SUB_EVENT_NUM ( 2 )	// イベント数
#define ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT	(1<<0)
#define ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT	(1<<1)

#define ZKN_BIG_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_BIGSUB_SEQINIT_ALLOC,
	ZKN_BIGSUB_SEQINIT_LOAD,
	ZKN_BIGSUB_SEQINIT_FADEIN,
	ZKN_BIGSUB_SEQINIT_END,
};
enum{
	ZKN_BIGSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_BIGSUB_SEQDELETE_FADEOUT,
	ZKN_BIGSUB_SEQDELETE_RELEASE,
	ZKN_BIGSUB_SEQDELETE_FREE,
	ZKN_BIGSUB_SEQDELETE_END,
};





//-------------------------------------
//	ボタン種類
//=====================================
enum{
	ZKN_BIGSUB_BUTTON_HEIGHT,
	ZKN_BIGSUB_BUTTON_GRAM,
	ZKN_BIGSUB_BUTTON_NUM,
};
#define ZKN_BIGSUB_BUTTON_DEF_Y		( 120 )
#define ZKN_BIGSUB_BUTTON_HEIGHT_X	( 68 )
#define ZKN_BIGSUB_BUTTON_GRAM_X	( 188 )
#define ZKN_BIGSUB_BUTTON_SIZE_X	( 120 )
#define ZKN_BIGSUB_BUTTON_SIZE_Y	( 112 )
#define ZKN_BIGSUB_BUTTON_ANM_SEQ	( 1 )
#define ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO	(4)
#define ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO	(5)

#define ZKN_BIGSUB_CURSOR_SIZE_X	( 104 )
#define ZKN_BIGSUB_CURSOR_SIZE_Y	( 96 )

// FONTOAM
#define ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX ( 12 )
#define ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY ( 2 )
#define ZKN_BIGSUB_BUTTON_PAL_OFS			( 4 )
#define ZKN_BIGSUB_BUTTON_PAL_OFS_ON		( 1 )
#define ZKN_BIGSUB_BUTTON_FONT_OFS_X		( -40 )
#define ZKN_BIGSUB_BUTTON_FONT_OFS_Y		( -8 )

#define ZKN_BIGSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

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

	int now_apply;

	ZKN_GLB_DATA* p_glb;
	
	// 図鑑コモンサブアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_BIG_SUB_GLB;

//-------------------------------------
//	大きさぐらべサブ画面画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_BIG_SUB_DRAWGLB;

//-------------------------------------
//	ボタンコールバックへのワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_BIG_BUTTON_CALLBACK;

//-------------------------------------
//	おおきさくらべサブ画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_BIG_BUTTON_CALLBACK callcack;

	// アプリデータ
	int button_event[ ZKN_BIGSUB_BUTTON_NUM ];	// ボタンイベントデータ

} ZKN_BIG_SUB_WORK;

//-------------------------------------
//	おおきさくらべサブ画面画面　内部ワーク
//=====================================
typedef struct {
	// ボタングラフィック
	CLACT_WORK_PTR button[ ZKN_BIGSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_button_font[ ZKN_BIGSUB_BUTTON_NUM ];
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// カーソル
	CLACT_WORK_PTR cursor[ ZKN_CURROS_MAT_RECT_NUM ];

	int	bgpltt_no[ ZKN_BIGSUB_BUTTON_NUM ];

	void* pltt_buff[ ZKN_BIGSUB_BUTTON_NUM ];
} ZKN_BIG_SUB_DRAW;


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
static ZKN_BIG_SUB_GLB* MakeBigSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_BIG_SUB_DRAWGLB* MakeBigSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeBigSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteBigSubGlb( ZKN_BIG_SUB_GLB* p_glb );
static void DeleteBigSubDrawGlb( ZKN_BIG_SUB_DRAWGLB* p_glb );
static void DeleteBigSubEvent( ZKN_EVENT_DATA* p_event );


static int BigSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknBigSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknBigSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknBigSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknBigSubOamFadeInit( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubOamFadeDelete( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubFadeInit( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknBigSubFadeMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out );

// ボタン制御
static void ZknBigSubButtonMake( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb, int heap );
static void ZknBugSubButtonEventBuffInit( ZKN_BIG_SUB_WORK* p_work );
static void ZknBigSubButtonMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb );
static void ZknBigSubButtonDelete( ZKN_BIG_SUB_WORK* p_work );
static void ZknBigSubButtonCallBack( u32 button_no, u32 event, void* p_work );


// ボタン描画制御
static void ZknBigSubButtonControl( ZKN_BIG_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff );
static void ZknBigSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );
static void ZknBigSubButtonDrawMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_WORK* cp_work, int heap );


// カーソル制御
static void ZknBigSubCursorMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb );
static void ZknBigSubCursorDraw( ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb );
static void ZknBigSubCursorMatSet( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y );



// 読み込み
static void ZknBigSubLoadResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubReleaseResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubSetUpBg( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubLoadOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubReleaseOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb );
static void ZknBigSubAddClact( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubDeleteClact( ZKN_BIG_SUB_DRAW* p_draw );
static void ZknBigSubAddFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknBigSubDeleteFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb );

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
void ZKN_BigSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_BIG_SUB_GLB*	p_glb;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeBigSubGlb( heap, zkn_sys );
	p_drawglb = MakeBigSubDrawGlb( heap, zkn_sys );
	p_event = MakeBigSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= BigSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknBigSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknBigSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknBigSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknBigSubProcDrawFuncDelete;
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
void ZKN_BigSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteBigSubGlb( p_data->p_glb_data ); 
	DeleteBigSubDrawGlb( p_data->p_glb_draw ); 
	DeleteBigSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	現在のアプリケーションデータ取得
 *
 *	@param	p_data	アプリデータ
 *
 *	@retval	ZKN_BIGSUB_CONTROL_HEIGHT	高さ比べ
 *	@retval	ZKN_BIGSUB_CONTROL_GRAM		重さ比べ
 */
//-----------------------------------------------------------------------------
int ZKN_BigSubNowAplTypeGet( ZKN_APL_DATA* p_data )
{
	ZKN_BIG_SUB_GLB* p_glb = p_data->p_glb_data;

	return p_glb->now_apply;
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
static ZKN_BIG_SUB_GLB* MakeBigSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_SUB_GLB) );

	// 変数初期化
	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// 図鑑コモンアプリグローバルデータ
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	// 今のアプリケーション
	p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;

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
static ZKN_BIG_SUB_DRAWGLB* MakeBigSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_BIG_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_BIG_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_BIG_SUB_DRAWGLB) );


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
static ZKN_EVENT_DATA* MakeBigSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;
	int event_num = BigSubEventDataNumGet();

	// イベントデータテーブル作成
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );
	
	ZKN_EVENT_MakeChangeBigMain( heap, &p_event_tbl[0], zkn_sys, ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT );
	ZKN_EVENT_MakeChangeBigWeightMain( heap, &p_event_tbl[1], zkn_sys, ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT );

	return p_event_tbl;
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
static void DeleteBigSubGlb( ZKN_BIG_SUB_GLB* p_glb )
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
static void DeleteBigSubDrawGlb( ZKN_BIG_SUB_DRAWGLB* p_glb )
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
static void DeleteBigSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	ZKN_EVENT_DeleteData( &p_event[0] );
	ZKN_EVENT_DeleteData( &p_event[1] );

	sys_FreeMemoryEz( p_event );
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
static int BigSubEventDataNumGet( void )
{
	return ZKN_BIG_SUB_EVENT_NUM;
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
static int ZknBigSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;
	int i;

	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_BIG_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_BIG_SUB_WORK) );

	// ボタンイベントデータ
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// ボタンイベントデータ
	}

	// 今のアプリケーション
	p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;


	// ボタンを作成
	ZknBigSubButtonMake( p_work, p_glb, p_dodata->heap );

	// ボタンの状態を１回設定
	// ボタン動作
	ZknBigSubButtonMove( p_work, p_glb );

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
static int ZknBigSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;
	
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
		ZknBugSubButtonEventBuffInit( p_work );
		
		// カーソル動作
		// カーソル動作有効で、サブアプリにカーソル動作が許されているときのみ
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknBigSubCursorMove( p_work, p_glb );
		}

		// ボタン動作
		ZknBigSubButtonMove( p_work, p_glb );

		
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
static int ZknBigSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_BIG_SUB_GLB* p_glb = p_glbdata;
	ZKN_BIG_SUB_WORK* p_work = p_dodata->p_work;

	// ボタン破棄
	ZknBigSubButtonDelete( p_work );

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
static int ZknBigSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_BIG_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_BIG_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQINIT_LOAD:
		// Resource読み込み
		ZknBigSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );

		// フェード処理
		ZknBigSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQINIT_FADEIN:
		
		if( ZknBigSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_BIGSUB_SEQINIT_END:
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
static int ZknBigSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){
		
		// ボタン描画メイン
		ZknBigSubButtonDrawMain( p_drawwork, p_drawglb, cp_datawork, p_drawdata->heap );

		// カーソル描画メイン
		ZknBigSubCursorDraw( p_drawglb, cp_dataglb );
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
static int ZknBigSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_BIG_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_BIG_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_BIG_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_BIG_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_BIGSUB_SEQDELETE_FADEOUT_INIT:
		// カーソルアニメ停止
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// フェード処理
		ZknBigSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQDELETE_FADEOUT:
		if( ZknBigSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_BIGSUB_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknBigSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_BIGSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_BIGSUB_SEQDELETE_END:
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
static void ZknBigSubOamFadeInit( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEを半透明にする
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubOamFadeDelete( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;
	// OBJMODEをノーマルにする
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubFadeInit( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknBigSubOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_BIGSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_BIGSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknBigSubFadeMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb, BOOL fadein_out )
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
			ZknBigSubOamFadeDelete( p_draw );
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
static void ZknBigSubButtonMake( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_BIGSUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_BIGSUB_BUTTON_HEIGHT ],
			ZKN_BIGSUB_BUTTON_DEF_Y - (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_DEF_Y + (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_HEIGHT_X - (ZKN_BIGSUB_BUTTON_SIZE_X/2),
			ZKN_BIGSUB_BUTTON_HEIGHT_X + (ZKN_BIGSUB_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_BIGSUB_BUTTON_GRAM ],
			ZKN_BIGSUB_BUTTON_DEF_Y - (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_DEF_Y + (ZKN_BIGSUB_BUTTON_SIZE_Y/2),
			ZKN_BIGSUB_BUTTON_GRAM_X - (ZKN_BIGSUB_BUTTON_SIZE_X/2),
			ZKN_BIGSUB_BUTTON_GRAM_X + (ZKN_BIGSUB_BUTTON_SIZE_X/2) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_BIGSUB_BUTTON_NUM,
			ZknBigSubButtonCallBack,
			&p_work->callcack,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brieuf	ボタンバッファ初期化
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknBugSubButtonEventBuffInit( ZKN_BIG_SUB_WORK* p_work )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubButtonMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb )
{

	BMN_Main( p_work->p_button_man );

	// 今選択中のアプリケーションのボタンは押しっぱなしにする
	switch( p_glb->now_apply ){
	case ZKN_BIGSUB_BUTTON_HEIGHT:	//高さ比べ 
		if( p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_BIGSUB_BUTTON_GRAM:	//重さ比べ
		if( p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] = BMN_EVENT_RELEASE;
		}
		break;
		
	default:
		break;
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
static void ZknBigSubButtonDelete( ZKN_BIG_SUB_WORK* p_work )
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
static void ZknBigSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_BIG_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_BIG_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_BIG_SUB_WORK* p_subwork = p_work_data->p_work;

	// ボタンイベント格納
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_BIGSUB_BUTTON_HEIGHT:
			if( p_glb->now_apply != ZKN_BIGSUB_CONTROL_HEIGHT ){
				// ボタンにタッチ
				Snd_SePlay( ZKN_SND_BUTTON );
				p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;
				*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT;
			}
			break;
			
		case ZKN_BIGSUB_BUTTON_GRAM:
			if( p_glb->now_apply != ZKN_BIGSUB_CONTROL_GRAM ){
				// ボタンにタッチ
				Snd_SePlay( ZKN_SND_BUTTON );
				p_glb->now_apply = ZKN_BIGSUB_CONTROL_GRAM;
				*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT;
			}
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
static void ZknBigSubLoadResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	// 背景
	ZknBigSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknBigSubLoadOamData( p_draw, p_drawglb, heap );

	// セルアクター登録
	ZknBigSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM登録
	ZknBigSubAddFontOam( p_draw, p_drawglb, heap );
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
static void ZknBigSubReleaseResource( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// パレットをリセット
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO*32, 32, heap );
	ZKN_GLBDATA_PalSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_4_NCLR, PALTYPE_SUB_BG, ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO*32, 32, heap );
	
	// セルアクター破棄
	ZknBigSubDeleteClact( p_draw );

	// FONTOAM破棄
	ZknBigSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknBigSubReleaseOamData( p_draw, p_drawglb );

	// パレットバッファ破棄
	for( i=0;i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubSetUpBg( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_bg_sub2_b_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
static void ZknBigSubLoadOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_BIG_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_BIG_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_BIG_SUB_RES_ID,
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
static void ZknBigSubReleaseOamData( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb )
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
static void ZknBigSubAddClact( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub3_lzh_NCGR + ZKN_BIG_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub3_lzh_NCER + ZKN_BIG_SUB_RES_ID,
			NARC_zukan_zkn_data_oam_sub3_lzh_NANR + ZKN_BIG_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_BIG_SUB_OAM_BG_PTR,
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
	
	// 高さ
	add.mat.x = ZKN_BIGSUB_BUTTON_HEIGHT_X << FX32_SHIFT;
	add.mat.y = ZKN_BIGSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ], ZKN_BIGSUB_BUTTON_ANM_SEQ );	

	// 重さ
	add.mat.x = ZKN_BIGSUB_BUTTON_GRAM_X << FX32_SHIFT;
	add.mat.y = ZKN_BIGSUB_BUTTON_DEF_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ], ZKN_BIGSUB_BUTTON_ANM_SEQ );	
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
static void ZknBigSubDeleteClact( ZKN_BIG_SUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubAddFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ] );

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_BIGSUB_BUTTON_FONT_OFS_X;
	fontoam_init.y			 = ZKN_BIGSUB_BUTTON_FONT_OFS_Y;
	fontoam_init.bg_pri		 = ZKN_BIG_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY );

	// すがた
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BIG_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_BIGSUB_BUTTON_HEIGHT ];
	p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_HEIGHT ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_HEIGHT ]->p_fontoam, pltt_ofs + ZKN_BIGSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_BIGSUB_BUTTONFONT_BMP_SIZE_CY );


	// せつめい
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BIG_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_draw->button[ ZKN_BIGSUB_BUTTON_GRAM ];
	p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_GRAM ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_button_font[ ZKN_BIGSUB_BUTTON_GRAM ]->p_fontoam, pltt_ofs + ZKN_BIGSUB_BUTTON_PAL_OFS );


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
static void ZknBigSubDeleteFontOam( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb )
{
	int i;

	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){
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
static void ZknBigSubButtonControl( ZKN_BIG_SUB_DRAWGLB* p_drawglb, CLACT_WORK_PTR button, ZKN_FONTOAM_DATA* p_fontoam, int event, int def_y, int bgpltt_no, int* p_nowbgpltt_no, int heap, int off_fontoam_pl, int on_fontoam_pl, void** buff )
{
	int now_frm;
	NNSG2dPaletteData* p_plt;
	BOOL check;
	BOOL chenge = FALSE;
	int arc_data_idx;

	
	// ボタン動作
	ZKN_UTIL_ButtonMove( button,
			event );

	ZknBigSubFontButtonMove( 
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
static void ZknBigSubFontButtonMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
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
static void ZknBigSubButtonDrawMain( ZKN_BIG_SUB_DRAW* p_draw, ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_WORK* cp_work, int heap )
{
	int i;	// ループ用
	int bgpltt_no;

	// ボタン表示動作
	for( i=0; i<ZKN_BIGSUB_BUTTON_NUM; i++ ){

		if( i == ZKN_BIGSUB_BUTTON_HEIGHT ){
			bgpltt_no = ZKN_BIGSUB_BUTTON_HEIGHTBG_PLTT_NO;
		}else{
			bgpltt_no = ZKN_BIGSUB_BUTTON_GRAMBG_PLTT_NO;
		}
		
		ZknBigSubButtonControl( p_drawglb,
				p_draw->button[i],
				p_draw->p_button_font[i], cp_work->button_event[i],
				ZKN_BIGSUB_BUTTON_FONT_OFS_Y, bgpltt_no,
				&p_draw->bgpltt_no[i], heap,
				ZKN_BIGSUB_BUTTON_PAL_OFS, 
				ZKN_BIGSUB_BUTTON_PAL_OFS_ON,
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
static void ZknBigSubCursorMove( ZKN_BIG_SUB_WORK* p_work, ZKN_BIG_SUB_GLB* p_glb )
{
	// Aボタンでアプリケーションを分岐
	if( sys.trg & PAD_BUTTON_A ){

		// アプリにより分岐
		if( p_glb->now_apply == ZKN_BIGSUB_CONTROL_GRAM ){	
			p_glb->now_apply = ZKN_BIGSUB_CONTROL_HEIGHT;
			*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_HEIGHT;

			p_work->button_event[ ZKN_BIGSUB_BUTTON_HEIGHT ] = BMN_EVENT_HOLD;
		}else{
			p_glb->now_apply = ZKN_BIGSUB_CONTROL_GRAM;
			*p_glb->p_event_key |= ZKN_BIG_SUB_EVENT_CHANGE_WEIGHT;

			p_work->button_event[ ZKN_BIGSUB_BUTTON_GRAM ] = BMN_EVENT_HOLD;
		}
		// ボタンにタッチ
		Snd_SePlay( ZKN_SND_BUTTON );
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
static void ZknBigSubCursorDraw( ZKN_BIG_SUB_DRAWGLB* p_drawglb, const ZKN_BIG_SUB_GLB* cp_glb )
{
	
	// 自分の座標を設定してよいかチェック
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		// アプリにより分岐
		if( cp_glb->now_apply == ZKN_BIGSUB_CONTROL_HEIGHT ){
			ZknBigSubCursorMatSet( p_drawglb, ZKN_BIGSUB_BUTTON_GRAM_X, ZKN_BIGSUB_BUTTON_DEF_Y, ZKN_BIGSUB_CURSOR_SIZE_X, ZKN_BIGSUB_CURSOR_SIZE_Y );
		}else{
			ZknBigSubCursorMatSet( p_drawglb, ZKN_BIGSUB_BUTTON_HEIGHT_X, ZKN_BIGSUB_BUTTON_DEF_Y, ZKN_BIGSUB_CURSOR_SIZE_X, ZKN_BIGSUB_CURSOR_SIZE_Y );
		}
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
static void ZknBigSubCursorMatSet( ZKN_BIG_SUB_DRAWGLB* p_drawglb, int x, int y, int size_x, int size_y )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrix( p_draw, x, y, size_x, size_y );
}

