//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range_sub.c
 *	@brief		分布図サブ画面
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "calctool.h"
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
#include "include/application/zukanlist/zkn_range.h"

#define	__ZKN_RANGE_SUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_range_sub.h"

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
#define ZKN_RANGE_SUB_EVENT_NUM ( 0 )	// イベント数

#define ZKN_RANGE_SUB_OAM_BG_PRI	( 1 )
#define ZKN_RANGE_SUB_OAM_SOFT_PRI	( 31 )

enum{
	ZKN_RANGESUB_SEQINIT_ALLOC,
	ZKN_RANGESUB_SEQINIT_LOAD,
	ZKN_RANGESUB_SEQINIT_FADEIN,
	ZKN_RANGESUB_SEQINIT_END,
};
enum{
	ZKN_RANGESUB_SEQDELETE_FADEOUT_INIT,
	ZKN_RANGESUB_SEQDELETE_FADEOUT,
	ZKN_RANGESUB_SEQDELETE_RELEASE,
	ZKN_RANGESUB_SEQDELETE_FREE,
	ZKN_RANGESUB_SEQDELETE_END,
};

// ボタン
enum{
	ZKN_RANGESUB_BUTTON_CURSOR,
	ZKN_RANGESUB_BUTTON_NUM,
};


// 時間テーブル
#define ZKN_RANGE_SUB_TIME_LIMIT	( 85 )

//BGパレットフェード
#define ZKN_RANGE_SUB_TIMEPLTT_LIMIT	( 51 )
#define ZKN_RANGE_SUB_PLTT_NUM			( 5 )
#define ZKN_RANGE_SUB_PLTT_NO			( 2 )

// パレットアニメ
#define ZKN_RANGE_SUB_PLTT_ANM_WAIT	( 0 )
enum{
	ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0,
//	ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0WAIT,
	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0,
//	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0WAIT,
	ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_1,
};
	

// カーソル位置
#define ZKN_RANGE_SUB_CURSOR_MORNING_X	( 32 )
#define ZKN_RANGE_SUB_CURSOR_MORNING_Y	( 128 )
#define ZKN_RANGE_SUB_CURSOR_NOON_X		( 128 )
#define ZKN_RANGE_SUB_CURSOR_NOON_Y		( 96 )
#define ZKN_RANGE_SUB_CURSOR_NIGHT_X	( 224 )
#define ZKN_RANGE_SUB_CURSOR_NIGHT_Y	( 128 )
#define ZKN_RANGE_SUB_CURSOR_SEQ		( 0 )
#define ZKN_RANGE_SUB_CURSOR_SIZE_R		( 32 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_X	( 24 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX	( 246 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y	( 64 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX	( 132 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS	( 48 )
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X	( 40 )	// 両端から減らすX座標値
#define ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X_CALC_DIS	( 256 - (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X * 2) )	// 両端から減らすX座標値をへらした横size
#define ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X		( 32 )
#define ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y		( 32 )


// フェード
#define ZKN_RANGESUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	分布図サブ画面画面　グローバル変数
//=====================================
typedef struct {
	// 分布図サブアプリデータ
	ZKN_APL_DATA* p_range_apl;
	
	// 図鑑コモンサブアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;
} ZKN_RANGE_SUB_GLB;

//-------------------------------------
//	分布図サブ画面画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_RANGE_SUB_DRAWGLB;

//-------------------------------------
//	ボタンコールバック用ワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_RANGE_SUB_CALLBACK_WORK;


//-------------------------------------
//	分布図サブ画面画面　内部ワーク
//=====================================
typedef struct {
	// タッチ座標
	int x;
	int y;
	int ofs_x;	// 抑えられたときの中心からの離れた座標
	int ofs_y;

	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_RANGE_SUB_CALLBACK_WORK button_work;
	int touch;

	BOOL key_set;
	
} ZKN_RANGE_SUB_WORK;

//-------------------------------------
//	分布図サブ画面画面　内部ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor;	// カーソル
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	void* pltt_buff;
	int pltt_no;
	int next_pltt_no;
	NNSG2dPaletteData* p_plt;
	int pltt_anm_seq;
	int pltt_anm_count;
} ZKN_RANGE_SUB_DRAW;

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
static ZKN_RANGE_SUB_GLB* MakeRangeSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_RANGE_SUB_DRAWGLB* MakeRangeSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeRangeSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteRangeSubGlb( ZKN_RANGE_SUB_GLB* p_glb );
static void DeleteRangeSubDrawGlb( ZKN_RANGE_SUB_DRAWGLB* p_glb );
static void DeleteRangeSubEvent( ZKN_EVENT_DATA* p_event );


static int RangeSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknRangeSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknRangeSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknRangeSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknRangeSubOamFadeInit( ZKN_RANGE_SUB_DRAW* p_draw );
static void ZknRangeSubOamFadeDelete( ZKN_RANGE_SUB_DRAW* p_draw );
static void ZknRangeSubFadeInit( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknRangeSubFadeMain( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out );

// ボタン制御
static void ZknRangeSubCursorInit( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb, int heap );

static void ZknRangeSubCursorMain( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );
static void ZknRangeSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknRangeSubCursorDelete( ZKN_RANGE_SUB_WORK* p_work );
static void ZknRangeSubCursorMove( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );
static void ZknRangeSubCursorDefMatSet( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );

// キーによるカーソル操作
static void ZknRangeSubCursorMoveKey( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb );

static void ZknRangeSubCursorMoveKey_CorsorDrawSet( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_WORK* cp_work, const ZKN_RANGE_SUB_GLB* cp_glb );


// 読み込み処理
static void ZknRangeSubLoadResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubReleaseResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubSetUpBg( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubLoadOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubReleaseOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb );
static void ZknRangeSubAddClact( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknRangeSubDeleteClact( ZKN_RANGE_SUB_DRAW* p_draw );

// CURSOR描画制御
static void ZknRangeSubCursorDraw( ZKN_RANGE_SUB_DRAW* p_draw, const ZKN_RANGE_SUB_GLB* cp_glb, const ZKN_RANGE_SUB_WORK* cp_work );

static int ZknRangeSubCursorMoveMaxDisGet( int x );

// BGパレット制御
static void ZknRangeSubBgPlttDraw( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　アプリ作成
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
void ZKN_RangeSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_RANGE_SUB_GLB*	p_glb;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeRangeSubGlb( heap, zkn_sys );
	p_drawglb = MakeRangeSubDrawGlb( heap, zkn_sys );
	p_event = MakeRangeSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= RangeSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknRangeSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknRangeSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknRangeSubProcDrawFuncDelete;
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
void ZKN_RangeSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteRangeSubGlb( p_data->p_glb_data ); 
	DeleteRangeSubDrawGlb( p_data->p_glb_draw ); 
	DeleteRangeSubEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_SUB_GLB* MakeRangeSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_SUB_GLB) );

	// 分布図アプリデータ
	p_glb->p_range_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );

	// 図鑑サブコモンデータ
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画グローバル
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static ZKN_RANGE_SUB_DRAWGLB* MakeRangeSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_RANGE_SUB_DRAWGLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_RANGE_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_RANGE_SUB_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );


	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeRangeSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;	// 今はなし
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubGlb( ZKN_RANGE_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubDrawGlb( ZKN_RANGE_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteRangeSubEvent( ZKN_EVENT_DATA* p_event )
{
	// 今はなし
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	分布図サブ画面アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	分布図サブ画面アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int RangeSubEventDataNumGet( void )
{
	return ZKN_RANGE_SUB_EVENT_NUM;
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
static int ZknRangeSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work;

	// メモリ確保
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_RANGE_SUB_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_RANGE_SUB_WORK) );
	p_dodata->p_work = p_work;

	// CURSORデフォ位置設定
	ZknRangeSubCursorDefMatSet( p_work, p_glb );

	// ボタン作成
	// CURSORデフォ位置設定の後の必要あり
	ZknRangeSubCursorInit( p_work, p_glb, p_dodata->heap );
	
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
static int ZknRangeSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work = p_dodata->p_work;

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
		// CURSOR動作
		ZknRangeSubCursorMain( p_work, p_glb );	
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
static int ZknRangeSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_RANGE_SUB_GLB* p_glb = p_glbdata;
	ZKN_RANGE_SUB_WORK* p_work = p_dodata->p_work;


	// ボタン破棄
	ZknRangeSubCursorDelete( p_work );
	
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
static int ZknRangeSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	
	switch( p_drawdata->seq ){
	case ZKN_RANGESUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_RANGE_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_RANGE_SUB_DRAW) );

		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQINIT_LOAD:
		// Resource読み込み
		ZknRangeSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );
		// 座標設定
		ZknRangeSubCursorDraw( p_drawwork, cp_dataglb, cp_datawork );
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

		// フェード処理
		ZknRangeSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQINIT_FADEIN:
		// アニメするのでずっと呼ぶ
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );


		if( ZknRangeSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_RANGESUB_SEQINIT_END:
		// アニメするのでずっと呼ぶ
		ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

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
static int ZknRangeSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// CURSOR動作
	ZknRangeSubCursorDraw( p_drawwork, cp_dataglb, cp_datawork );

	// カーソルMARK描画
	ZknRangeSubCursorMoveKey_CorsorDrawSet( p_drawglb, cp_datawork, cp_dataglb );

	// パレットフェード
	ZknRangeSubBgPlttDraw( p_drawwork, p_drawglb, cp_dataglb, p_drawdata->heap );

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
static int ZknRangeSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_RANGE_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_RANGE_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_RANGE_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_RANGE_SUB_DRAW*		p_drawwork = p_drawdata->p_work;
	
	switch( p_drawdata->seq ){
	case ZKN_RANGESUB_SEQDELETE_FADEOUT_INIT:

		// カーソルアニメ停止
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );
		
		// フェード処理
		ZknRangeSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQDELETE_FADEOUT:
		if( ZknRangeSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_RANGESUB_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknRangeSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_RANGESUB_SEQDELETE_FREE:

		sys_FreeMemoryEz( p_drawwork->pltt_buff );
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_RANGESUB_SEQDELETE_END:
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
static void ZknRangeSubOamFadeInit( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->cursor, GX_OAM_MODE_XLU );
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
static void ZknRangeSubOamFadeDelete( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->cursor, GX_OAM_MODE_NORMAL );
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
static void ZknRangeSubFadeInit( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknRangeSubOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_RANGESUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_FADE_SYNC_COMMON,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_RANGESUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
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
static BOOL ZknRangeSubFadeMain( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, BOOL fadein_out )
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
			ZknRangeSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
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
static void ZknRangeSubLoadResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	// 背景
	ZknRangeSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknRangeSubLoadOamData( p_draw, p_drawglb, heap );

	// セルアクター登録
	ZknRangeSubAddClact( p_draw, p_drawglb, heap );


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
static void ZknRangeSubReleaseResource( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	// セルアクター破棄
	ZknRangeSubDeleteClact( p_draw );

	// OAM
	ZknRangeSubReleaseOamData( p_draw, p_drawglb );
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
static void ZknRangeSubSetUpBg( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_bg_sub_lzh_NSCR, TRUE, &p_scrn, heap );
	
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
static void ZknRangeSubLoadOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR + ZKN_RANGE_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER + ZKN_RANGE_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR, TRUE,
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR + ZKN_RANGE_RES_ID,
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
static void ZknRangeSubReleaseOamData( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb )
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
static void ZknRangeSubAddClact( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_data_oam_sub4_lzh_NCGR + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_sub_NCLR + ZKN_ZUKAN_COMMON_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_data_oam_sub4_lzh_NCER + ZKN_RANGE_RES_ID,
			NARC_zukan_zkn_data_oam_sub4_lzh_NANR + ZKN_RANGE_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_RANGE_SUB_OAM_BG_PRI,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= ZKN_RANGE_SUB_OAM_SOFT_PRI;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// CURSOR
	add.mat.x = 0;
	add.mat.y = 0;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->cursor = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->cursor, ZKN_RANGE_SUB_CURSOR_SEQ );	

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
static void ZknRangeSubDeleteClact( ZKN_RANGE_SUB_DRAW* p_draw )
{
	CLACT_Delete( p_draw->cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR用ボタンマネージャ作成
 *
 *	@param	p_work		ワーク
 *	@param	p_glb		グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorInit( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_RANGESUB_BUTTON_NUM );

	// テーブルデータ設定
	p_work->hit_tbl[ 0 ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ 0 ].circle.x	 = p_work->x;
	p_work->hit_tbl[ 0 ].circle.y	 = p_work->y;
	p_work->hit_tbl[ 0 ].circle.r	 = ZKN_RANGE_SUB_CURSOR_SIZE_R;

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_RANGESUB_BUTTON_NUM,
			ZknRangeSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR動作メイン関数
 *
 *	@param	p_work		ワーク
 *	@param	p_glb		グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMain( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	
	// ボタン範囲内に入ったか
	BMN_Main( p_work->p_button_man );

	ZknRangeSubCursorMove( p_work, p_glb );

	// 当たり判定領域に設定
	p_work->hit_tbl[ 0 ].circle.x = p_work->x;
	p_work->hit_tbl[ 0 ].circle.y = p_work->y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	キー入力動さ
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルワーク
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMoveKey( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	s32 type;

	if( sys.tp_cont ){
		return ;
	}
	
	if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) == TRUE ){
		type = ZKN_RangeTypeGet( p_glb->p_range_apl );
		if( sys.trg & PAD_KEY_LEFT ){
			type --;
			if( type < 0 ){
				type = 0;
			}
			// その座標のじかん代入
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );

			// その時間の座標をカーソルに設定
			ZknRangeSubCursorDefMatSet( p_work, p_glb );
			p_work->key_set = TRUE;
			
		}else if( sys.trg & PAD_KEY_RIGHT ){

			type ++;
			if( type >= ZKN_RANGE_TYPE_NUM ){
				type = ZKN_RANGE_TYPE_NUM - 1;
			}
			// その座標のじかん代入
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );
			// その時間の座標をカーソルに設定
			ZknRangeSubCursorDefMatSet( p_work, p_glb );
			p_work->key_set = TRUE;
		}
	
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR制御
 *
 *	@param	p_work	ワークデータ
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMove( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	int type;
	int y_max_dis;
	
	p_work->key_set = FALSE;
	
	if( p_work->touch ){

		// タッチしていたらその座標を保存し
		// その座標位置の時間を設定b
		if( sys.tp_cont ){
			p_work->x = sys.tp_x - p_work->ofs_x;
			p_work->y = sys.tp_y - p_work->ofs_y;

			if( p_work->x < ZKN_RANGE_SUB_CURSOR_LIMIT_X ){
				p_work->x = ZKN_RANGE_SUB_CURSOR_LIMIT_X;
			}
			if( p_work->x > ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX ){
				p_work->x = ZKN_RANGE_SUB_CURSOR_LIMIT_X_MAX;
			}

			if( p_work->y < ZKN_RANGE_SUB_CURSOR_LIMIT_Y ){
				p_work->y = ZKN_RANGE_SUB_CURSOR_LIMIT_Y;
			}

			// Y方向最大値を求める
			y_max_dis = ZknRangeSubCursorMoveMaxDisGet( p_work->x );
			if( p_work->y > (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX + y_max_dis) ){
				p_work->y = (ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX + y_max_dis);
			}


			type = p_work->x / ZKN_RANGE_SUB_TIME_LIMIT;

			if( type > ZKN_RANGE_TYPE_NIGHT ){
				type = ZKN_RANGE_TYPE_NIGHT;
			}
			
			// その座標のじかん代入
			ZKN_RangeTypeSet( p_glb->p_range_apl, type );
		}else{
			p_work->touch = 0;
		}
	}else{
		ZknRangeSubCursorMoveKey( p_work, p_glb );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	図鑑ボタンコールばっく関数
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		イベントナンバー
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_RANGE_SUB_CALLBACK_WORK* p_work_data = p_work;
	ZKN_RANGE_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_RANGE_SUB_WORK* p_subwork = p_work_data->p_work;

	switch( event ){
	case BMN_EVENT_TOUCH:
		// ボタンにタッチ
		Snd_SePlay( ZKN_SND_BUTTON );
		p_subwork->touch = 1;	// タッチ

		// 中心からの座標を取得
		p_subwork->ofs_x = sys.tp_x - p_subwork->x;
		p_subwork->ofs_y = sys.tp_y - p_subwork->y;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSORデータ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDelete( ZKN_RANGE_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSOR描画制御
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_glb		グローバルデータ
 *	@param	cp_work		データワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDraw( ZKN_RANGE_SUB_DRAW* p_draw, const ZKN_RANGE_SUB_GLB* cp_glb, const ZKN_RANGE_SUB_WORK* cp_work )
{
	VecFx32 mat;
	
	// CURSOR座標を設定
	mat.x = cp_work->x << FX32_SHIFT;
	mat.y = cp_work->y << FX32_SHIFT;
	mat.y += SUB_SURFACE_Y;

	CLACT_SetMatrix( p_draw->cursor, &mat );

	// 時間によって絵を変更
	CLACT_AnmChg( p_draw->cursor, ZKN_RangeTypeGet( cp_glb->p_range_apl ) );
}

// BGパレット制御
//----------------------------------------------------------------------------
/**
 *	@brief	BGパレット制御
 *
 *	@param	p_draw	描画ワーク
 *	@param	cp_glb	グローバルデータ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubBgPlttDraw( ZKN_RANGE_SUB_DRAW* p_draw, ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_GLB* cp_glb, int heap )
{
	int pltt_no;
	int pltt_anm = 0;
	BOOL check;
	
	// パレットタイプナンバー
	pltt_no = ZKN_RangeTypeGet( cp_glb->p_range_apl );

	// パレットナンバーが違うかバッファがNULLのとき設定
	if( (p_draw->pltt_no != pltt_no) || ( p_draw->pltt_buff == NULL ) ||
		(p_draw->next_pltt_no != p_draw->pltt_no) ){

		// 今設定中のパレットナンバーが違うものになってしまったら
		// 再設定
		if( p_draw->next_pltt_no != pltt_no ){
			p_draw->pltt_no = p_draw->next_pltt_no;
			p_draw->pltt_anm_seq = 0;
		}
		
		// パレットアニメさせる
		switch( p_draw->pltt_anm_seq ){
		case ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0:
			// 次のパレットナンバー設定
			p_draw->next_pltt_no = pltt_no;
			
			// 今までのを破棄
			if( p_draw->pltt_buff ){
				sys_FreeMemoryEz( p_draw->pltt_buff );
			}
			// パレット読み込み
			p_draw->pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_00_NCLR + p_draw->pltt_no, &p_draw->p_plt, heap );
			p_draw->pltt_anm_count = ZKN_RANGE_SUB_PLTT_ANM_WAIT;

			// パレットアニメセット
			if( p_draw->pltt_no > pltt_no ){
				pltt_anm = 1;	// 朝ー＞昼　昼ー＞夜
			}else{
				pltt_anm = 2;	// 夜ー＞昼　昼ー＞朝
			}
			p_draw->pltt_anm_seq ++;
			break;

/*		case ZKN_RANGESUB_PLTTANM_SEQ_NOW_PLTT_0WAIT:
			p_draw->pltt_anm_count--;
			if( p_draw->pltt_anm_count <= 0 ){
				p_draw->pltt_anm_seq ++;
			}
			return ;//*/

		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0:
			// 今までのを破棄
			if( p_draw->pltt_buff ){
				sys_FreeMemoryEz( p_draw->pltt_buff );
			}
			// パレット読み込み
			p_draw->pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_map_00_NCLR + p_draw->next_pltt_no, &p_draw->p_plt, heap );
			p_draw->pltt_anm_count = ZKN_RANGE_SUB_PLTT_ANM_WAIT;

			// パレットアニメセット
			if( p_draw->pltt_no < p_draw->next_pltt_no ){
				pltt_anm = 1;	// 朝ー＞昼　昼ー＞夜
			}else{
				pltt_anm = 2;	// 夜ー＞昼　昼ー＞朝
			}
			p_draw->pltt_anm_seq ++;
			break;

/*		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_0WAIT:
			p_draw->pltt_anm_count--;
			if( p_draw->pltt_anm_count <= 0 ){
				p_draw->pltt_anm_seq ++;
			}
			return ;//*/
			
		case ZKN_RANGESUB_PLTTANM_SEQ_NEXT_PLTT_1:
			pltt_anm = 0;		// 通常
			p_draw->pltt_anm_seq = 0;
			p_draw->pltt_no = p_draw->next_pltt_no;
			break;

		}

		// TransferManagerに登録
		check = AddVramTransferManager(
				NNS_GFD_DST_2D_BG_PLTT_SUB,
				ZKN_RANGE_SUB_PLTT_NO*32,
				&((u8*)(p_draw->p_plt->pRawData))[(pltt_anm*32)],
				32 );
		// 転送タスク生成失敗
		GF_ASSERT( check );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	CURSORデフォルト位置設定
 *
 *	@param	p_work	動作ワーク
 *	@param	p_glb	グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorDefMatSet( ZKN_RANGE_SUB_WORK* p_work, ZKN_RANGE_SUB_GLB* p_glb )
{
	int type = ZKN_RangeTypeGet( p_glb->p_range_apl );
	
	// 最初のカーソル位置設定
	switch( type ){
	case ZKN_RANGE_TYPE_MORNING:	// 朝
		p_work->x = ZKN_RANGE_SUB_CURSOR_MORNING_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_MORNING_Y;
		break;
		
	case ZKN_RANGE_TYPE_NOON:	// 昼
		p_work->x = ZKN_RANGE_SUB_CURSOR_NOON_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_NOON_Y;
		break;
		
	case ZKN_RANGE_TYPE_NIGHT:	// 夜
		p_work->x = ZKN_RANGE_SUB_CURSOR_NIGHT_X;
		p_work->y = ZKN_RANGE_SUB_CURSOR_NIGHT_Y;
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	Y軸に移動する最大値のX座標による変動値を求める
 *
 *	@param	x 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static int ZknRangeSubCursorMoveMaxDisGet( int x )
{
	int rota_num;
	int ret_num;
	
	// 最大の部分は計算しなくてもわかる
	if( (x < ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X) ||
		( (256 - ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X) < x ) ){

		return ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS;
	}
	
	// やっていることはｘ座標から今の座標のsinカーブ回転角
	// を取得して、その値でY座標リミット変更値
	// からいくつ減らすと今のリミット変更値になるかを求めている
	x -= ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X;

	rota_num = FX_GET_ROTA_NUM( 180 ) * x;
	rota_num = rota_num / ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_SUB_X_CALC_DIS;
	// 今のリミット座標のから減らす値を求める
	ret_num = FX_Mul( FX_SinIdx( (u16)rota_num ), ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS << FX32_SHIFT );
	ret_num >>= FX32_SHIFT;

	// 引く
	ret_num = ZKN_RANGE_SUB_CURSOR_LIMIT_Y_MAX_DIS - ret_num;

	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル　座標を設定
 *
 *	@param	p_drawglb
 *	@param	p_drawwork
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknRangeSubCursorMoveKey_CorsorDrawSet( ZKN_RANGE_SUB_DRAWGLB* p_drawglb, const ZKN_RANGE_SUB_WORK* cp_work, const ZKN_RANGE_SUB_GLB* cp_glb )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;

	// 自分の座標を設定してよいかチェック
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){

		if( cp_work->key_set == FALSE ){
			ZKN_UTIL_CursorSetMatrix( p_draw, 
					cp_work->x, cp_work->y,
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X, 
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y);
		}else{
			ZKN_UTIL_CursorSetMatrixNotAnm(  p_draw, 
					cp_work->x, cp_work->y,
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_X, 
					ZKN_RANGE_SUB_CURSOR_MARK_SIZE_Y );
		}
	}
}

