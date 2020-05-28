//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist_sub.c
 *	@brief		ポケモンリストサブ画面
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 *
 *	2006.08.02	リストを動かすパラメータの値を全て角度からベクトルの動いた距離に変更　定数を調整しました。
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"


#include "include/application/zukanlist/zkn_pokelist.h"
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/system/brightness.h"
#include "include/system/arc_util.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zukan.naix"

#include "include/application/zukanlist/zkn_pokelist_sub.h"


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
#define ZKN_POKELIST_SUB_LIST_PAR_SET	// ﾎﾟｹﾓﾝﾘｽﾄに重さを持たせる


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

#define ZKN_POKELIST_SUB_EVENT_NUM	( 1 )


#define ZKN_POKELIST_SUB_FADEIN_COUNT	( ZKN_FADE_SYNC_LONG_COMMON)
#define ZKN_POKELIST_SUB_FADEOUT_COUNT	( ZKN_FADE_SYNC_LONG_COMMON)



#define ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX	( 10 )
#define ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY	( 4 )

//-------------------------------------
//	ホイール面用定数
//=====================================
#define ZKN_POKELIST_SUB_EVENT_POKELIST		( 0x1 << 0 )	// 図鑑種類変換

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X	( 48 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_X	( 124 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_X	( 124 )

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_Y	( 40 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y	( 88 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y	( 152 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y	( 64 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_Y	( 146 )

#define ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y		( 48 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y		( 48 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X		( 96 )
#define ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y		( 80 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X	( 16 )
#define ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y	( 16 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X	( 16 )
#define ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y	( 16 )

#define ZKN_POKELSIT_SUB_SEARCH_BUTTON_SEQ	( 2 )	// リストリセットボタンシーケンス
#define ZKN_POKELSIT_SUB_ZUKANCHG_BUTTON_SEQ	( 0 )	// リストの先頭へボタンシーケンス
#define ZKN_POKELSIT_SUB_ZUKANSEE_BUTTON_SEQ	( 1 )	// リストの最後へボタンシーケンス
#define ZKN_POKELSIT_SUB_LISTSTART_BUTTON_SEQ	( 3 )
#define ZKN_POKELSIT_SUB_LISTEND_BUTTON_SEQ	( 4 )

#define ZKN_POKELIST_SUB_BUTTON_FONT_COL		( 3 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN	( 2 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_COL_CLOSE	( 1 )
#define ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL	( 5 )

#define ZKN_POKELIST_SUB_FADE_DEF_X	( ZKN_POKELIST_SUB_BUTTON_X )

#define ZKN_POKELSIT_SUB_MAT_X	( -120 )
#define ZKN_POKELSIT_SUB_MAT_Y	( 0 )
#define ZKN_POKELIST_SUB_BGCX	( 128 )		// BGアフィン変換用中心
#define ZKN_POKELIST_SUB_BGCY	( 104 )		// BGアフィン変換用中心
#define ZKN_POKELIST_SUB_CX		( ZKN_POKELIST_SUB_BGCX + (-ZKN_POKELSIT_SUB_MAT_X) )	// 中心
#define ZKN_POKELIST_SUB_CY		( ZKN_POKELIST_SUB_BGCY + (-ZKN_POKELSIT_SUB_MAT_Y) )	// 中心
#define ZKN_POKELSIT_SUB_R		( 104 )		// 半径

// リスト動作制御パラ
#define ZKN_POKELIST_SUB_MOVE_CACL_R	( 524 )	// 距離を求める為の円半径基準値
#define ZKN_POKELIST_SUB_MOVE_CACL_MUL	( 10 )	// 距離に掛ける値
#define ZKN_POKELIST_SUB_LOCK_MOVE_MAX	( 1024 )	// キー操作のときの1個のリストが動く距離
#define ZKN_POKELIST_SUB_COUNT_R	( ZKN_POKELIST_SUB_LOCK_MOVE_MAX / ZKN_POKELIST_MOVE_END_COUNT )	// この値で、動作速度を割ってリストｶｳﾝﾀを動かす
#define ZKN_POKELIST_SUB_SUB_R	( 2 )	// 速度減らしていくあたい
#define ZKN_POKELIST_SUB_SUBLIMIT_R	( ZKN_POKELIST_SUB_COUNT_R + 32 )// 値を反映させないリミット
#define ZKN_POKELIST_SUB_SUBDRAWLIMIT_R	( 4 )// 値を反映させないリミット
#define ZKN_POKELIST_SUB_SUB_MIN_SP	( 16 )// これ以下のスピードのときは反応しない

// ホイール描画制御定数
#define ZKN_POKELIST_SUB_LOCK_MOVE_DRAW_MAX	( FX_GET_ROTA_NUM( 25 ) )	// キー操作のときの1個のリストが動くときに回るホイールの角度　描画反映角度

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
/////////////////////////////////////////////////////
#define ZKN_POKELIST_SUB_LIST_PAR_ADD_LIMIT	( 64 )
#define ZKN_POKELIST_SUB_LIST_PAR_MIN	( FX32_CONST( 0.30f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_MAX	( FX32_CONST( 1.0f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_ADD	( FX32_CONST( 0.20f ) )
#define ZKN_POKELIST_SUB_LIST_PAR_SUB	( FX32_CONST( 0.01f ) )
//////////////////////////////////////////////////////
#endif


#define ZKN_POKELIST_SUB_BGFADE_DEF_X	( ZKN_POKELSIT_SUB_MAT_X )

#define ZKN_POKELIST_SUB_FONTOAM_OFS_X	( -40 )
#define ZKN_POKELIST_SUB_FONTOAM_OFS_Y	( -14 )

#define ZKN_POKELIST_SUB_CLACT_NUM	( 3 )


// Bボタン
#define ZKN_POKELIST_SUB_BUTTON_B_X	( 124 )
#define ZKN_POKELIST_SUB_BUTTON_B_Y	( 8 )
#define ZKN_POKELIST_SUB_BUTTON_B_ANM	( 5 )
#define ZKN_POKELIST_SUB_FONT_B_OFS		( 10 )
#define ZKN_POKELIST_SUB_FONT_B_OFS_Y	( -8 )
#define ZKN_POKELIST_SUB_FONT_B_BMP_CX	( 14 )
#define ZKN_POKELIST_SUB_FONT_B_BMP_CY	( 2 )

#define ZKN_POKELIST_SUB_BUTTON_HIT_X	( ZKN_POKELIST_SUB_BUTTON_B_X - 8 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_Y	( ZKN_POKELIST_SUB_BUTTON_B_Y - 8 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_WIDHT	( 64 )
#define ZKN_POKELIST_SUB_BUTTON_HIT_HEIGHT	( 16 )

// サブ画面のパレット位置
#define ZKN_POKELIST_SUB_BACK_PL		( 3 )

// ボタン定数
enum{
	ZKN_POKELIST_SUB_BUTTON_SEARCH,
	ZKN_POKELIST_SUB_BUTTON_ZUKANCHG,
	ZKN_POKELIST_SUB_BUTTON_ZUKANSEE,
	ZKN_POKELIST_SUB_BUTTON_LISTSTART,
	ZKN_POKELIST_SUB_BUTTON_LISTEND,
	ZKN_POKELIST_SUB_BUTTON_WHEEL,		// ホイール
	ZKN_POKELIST_SUB_BUTTON_CANCEL,
	ZKN_POKELIST_SUB_BUTTON_NUM,
};

// 初期化シーケンス
enum{
	ZKN_POKELIST_SUB_SEQINIT_ALLOC,
	ZKN_POKELIST_SUB_SEQINIT_LOAD,
	ZKN_POKELIST_SUB_SEQINIT_FADEIN_INIT,
	ZKN_POKELIST_SUB_SEQINIT_FADEIN,
	ZKN_POKELIST_SUB_SEQINIT_END,
};

// 破棄シーケンス
enum{
	ZKN_POKELIST_SUB_SEQDELETE_FADEOUT_INIT,
	ZKN_POKELIST_SUB_SEQDELETE_FADEOUT,
	ZKN_POKELIST_SUB_SEQDELETE_RELEASE,
	ZKN_POKELIST_SUB_SEQDELETE_FREE,
	ZKN_POKELIST_SUB_SEQDELETE_END,
};



//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	ポケモンリスト　サブ画面
//	ホイールアプリ　グローバルデータ
//=====================================
typedef struct {
	int button_event[ ZKN_POKELIST_SUB_BUTTON_NUM ];	// ボタンイベントデータ
	ZKN_POKELIST_GLB_DATA* p_pokelist_glb;		// ポケモンリストmainデータ
	int* p_event_key;		// イベントキー
	int heap;
} ZKN_POKELIST_SUB_GLB;

//-------------------------------------
//	ポケモンリスト　サブ画面
//	ホイールアプリ　グラフィックグローバルデータ
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_glb_draw;
} ZKN_POKELIST_SUB_GLBDRAW;

//-------------------------------------
//	ポケモンリスト　サブ画面
//	ホイールアプリ　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	void* p_button_work;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ

	int move_dist;		// 移動した距離
	int move_dist_list;	// 移動した距離値反映用
	int tp_last_x;
	int tp_last_y;

	fx32 wheel_rota_par;// 回転角度反映率

	BOOL touch_hold;
} ZKN_POKELIST_SUB_WORK;

//-------------------------------------
//	ボタン用ワーク
//=====================================
typedef struct {
	ZKN_POKELIST_SUB_WORK* p_work;
	ZKN_POKELIST_SUB_GLB* p_glb;

} ZKN_POKELIST_SUB_BUTTON_WORK;


//-------------------------------------
//	ポケモンリスト　サブ画面
//	ホイールアプリ　描画内部ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_POKELIST_SUB_CLACT_NUM ];
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_POKELIST_SUB_CLACT_NUM ];

	CLACT_WORK_PTR list_start;
	CLACT_WORK_PTR list_end;

	CLACT_WORK_PTR act_B;
	ZKN_FONTOAM_DATA* p_fontoam_B;

	u16 wheel_rota;		// ホイールの現在回転角
	u16 save_wheel_rota;// ホイールの角度保存領域

	// リソースオブジェ
	CLACT_U_RES_OBJ_PTR		res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

} ZKN_POKELIST_SUB_DRAWWORK;





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

static ZKN_POKELIST_SUB_GLB* MakePokeListSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_POKELIST_SUB_GLBDRAW* MakePokeListSubGlbDraw( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakePokeListSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeletePokeListSubGlb( ZKN_POKELIST_SUB_GLB* p_glb );
static void DeletePokeListSubGlbDraw( ZKN_POKELIST_SUB_GLBDRAW* p_glb );
static void DeletePokeListSubEvent( ZKN_EVENT_DATA* p_event );

static int EventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------

static int ZknPokeListSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// ボタンの動作
static void ZknPokelistSubButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt );

static void ZknPokeListSubButtonMake( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb, int heap );
static void ZknPokeListSubButtonMove( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );
static void ZknPokeListSubButtonDelete( ZKN_POKELIST_SUB_WORK* p_work );
static void ZknPokeListSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknPokeListSubButton_KeyMove( ZKN_POKELIST_SUB_GLB* p_glb );

// リソース読み込み
static void ZknPokeListSubResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubResDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubBgLoad( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubOamResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubOamResRelease( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb );
static void ZknPokeListSubAddClact( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubDeleteClact( ZKN_POKELIST_SUB_DRAWWORK* p_work );
static void ZknPokeListSubFontMake( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap );
static void ZknPokeListSubFontDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work );

static void ZknPokeListSubBgSetUp( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );
static void ZknPokeListSubBgDelete( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap );

static void ZknPokeListSub_ListNoChange( ZKN_POKELIST_SUB_GLB* p_glb, int no );

// 動作
static void ZknPokeListSubListCount( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );
static void ZknPokeListSubMoveDistGet( ZKN_POKELIST_SUB_WORK* p_work );
static void ZknPokeListSubDrawMove( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int add_num, fx32 draw_ref_par );
static void ZknPokeListSubDrawMoveLockTime( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb );
static void ZknPokeListSubResist( ZKN_POKELIST_SUB_WORK* p_work, int move_count, int move_way );

static BOOL ZknPokeListSubListMoveOkCheck( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb );
static BOOL ZknPokeListSubListAdd( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb );
static void ZknPokeListSubListMoveStop( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb );

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
static fx32 ZknPokeListSubDrawRefParCalc( fx32 now_par, s32 now_rota );
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイールアプリケーション作成
 *	
 *	@param	p_data		アプリケーションデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_POKELIST_SUB_GLB*		p_glb;
	ZKN_POKELIST_SUB_GLBDRAW*	p_glbdraw;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakePokeListSubGlb( heap, zkn_sys );
	p_glbdraw = MakePokeListSubGlbDraw( heap, zkn_sys );
	p_event = MakePokeListSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_glbdraw;
	p_data->p_event_data	= p_event;
	p_data->event_num		= EventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイールアプリデータ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeletePokeListSubGlb( p_data->p_glb_data ); 
	DeletePokeListSubGlbDraw( p_data->p_glb_data ); 
	DeletePokeListSubEvent( p_data->p_event_data );
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　グローバルデータ作成　
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *	
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_SUB_GLB* MakePokeListSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_SUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;
	int i;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_SUB_GLB) );

	p_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_glb->p_pokelist_glb = p_apl->p_glb_data;

	// 初期化
	for( i=0; i<ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}

	// イベントキーポインタ
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );

	// ヒープ
	p_glb->heap = heap;

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　グローバルデータ作成　
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *	
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_SUB_GLBDRAW* MakePokeListSubGlbDraw( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_SUB_GLBDRAW* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_GLBDRAW) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_SUB_GLBDRAW) );

	p_glb->p_glb_draw = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　イベントデータ作成　
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakePokeListSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_tbl;	// イベントテーブル作成先
	int event_num = EventDataNumGet();

	// イベントテーブルメモリ確保
	p_event_tbl = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) * event_num );
	GF_ASSERT( p_event_tbl );
	memset( p_event_tbl, 0, sizeof(ZKN_EVENT_DATA) * event_num );

	
	// イベントデータ作成
	ZKN_EVENT_MakeStartMainPokeList( &p_event_tbl[0], zkn_sys, heap, ZKN_POKELIST_SUB_EVENT_POKELIST );

	return p_event_tbl;
}	

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　	グローバルデータ破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubGlb( ZKN_POKELIST_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );

	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　	グローバルデータ破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubGlbDraw( ZKN_POKELIST_SUB_GLBDRAW* p_glb )
{
	GF_ASSERT( p_glb );

	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト　サブ画面　ホイール　	イベントデータ破棄
 *
 *	@param	p_event		イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeletePokeListSubEvent( ZKN_EVENT_DATA* p_event )
{
	GF_ASSERT( p_event );
	
	// イベントデータ破棄
	ZKN_EVENT_DeleteData( &p_event[0] );

	sys_FreeMemoryEz( p_event );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ホイールアプリイベント数取得
 *
 *	@param	none
 *
 *	@return	ホイールアプリイベントデータ数
 *
 *
 */
//-----------------------------------------------------------------------------
static int EventDataNumGet( void )
{
	return ZKN_POKELIST_SUB_EVENT_NUM;
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
static int ZknPokeListSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_SUB_GLB*  p_glb = p_glbdata;
	ZKN_POKELIST_SUB_WORK* p_work;
	int i;

	p_dodata->p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_POKELIST_SUB_WORK) );
	GF_ASSERT(p_dodata->p_work);
	memset( p_dodata->p_work, 0, sizeof(ZKN_POKELIST_SUB_WORK) );

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
		p_work = p_dodata->p_work;
		p_work->wheel_rota_par = ZKN_POKELIST_SUB_LIST_PAR_MIN;
#endif

	// ボタンイベントワーク初期化
	for( i=0; i<ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}
		
	// ボタンデータ作成
	ZknPokeListSubButtonMake( p_dodata->p_work, p_glb, p_dodata->heap );
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
static int ZknPokeListSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_SUB_GLB*  p_glb = p_glbdata;
	ZKN_POKELIST_SUB_WORK* p_work = p_dodata->p_work;
	

	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// 動作スピードを減らしてく
	ZknPokeListSubResist( p_work, p_glb->p_pokelist_glb->move_count, p_glb->p_pokelist_glb->move_way );


	// ボタンイベント制御
	ZknPokeListSubButtonMove( p_work, p_glb );


	// リストカウント
	if( p_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){		
		// メイン画面がサブホイールをlockしていなければ動作
		ZknPokeListSubListCount( p_work, p_glb );
	}else{
		p_work->move_dist = 0;	// lockされたらとめる
		p_work->move_dist_list = 0;
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
static int ZknPokeListSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	// ボタンデータ破棄
	ZknPokeListSubButtonDelete( p_dodata->p_work );
	
	// メモリ破棄
	sys_FreeMemoryEz( p_dodata->p_work );
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
static int ZknPokeListSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_POKELIST_SUB_SEQINIT_ALLOC:
		// メモリ確保
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_POKELIST_SUB_DRAWWORK) );
		GF_ASSERT( p_drawdata->p_work );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_POKELIST_SUB_DRAWWORK) );


		p_drawdata->seq++;
		break;

	case ZKN_POKELIST_SUB_SEQINIT_LOAD:
		ZknPokeListSubResLoad( p_drawwork, p_drawglb, cp_glb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQINIT_FADEIN_INIT:
		ChangeBrightnessRequest( ZKN_POKELIST_SUB_FADEIN_COUNT, 
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQINIT_FADEIN:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_SUB_SEQINIT_END:
		p_drawdata->seq++;
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
static int ZknPokeListSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;

	
	// ボタン動作
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	ZKN_UTIL_ButtonMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	ZKN_UTIL_ButtonMove( p_drawwork->list_start, cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_LISTSTART ] );
	ZKN_UTIL_ButtonMove( p_drawwork->list_end, cp_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_LISTEND ] );

	// 文字列ボタン動作
	ZknPokelistSubButtonFontMove( 
			p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );
	ZknPokelistSubButtonFontMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );
	ZknPokelistSubButtonFontMove( p_drawwork->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], p_drawwork->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ],
			ZKN_POKELIST_SUB_FONTOAM_OFS_Y,
			ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN,
			ZKN_POKELIST_SUB_BUTTON_FONT_PUSH_COL );

	// ホイール動作
	if( cp_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){
		ZknPokeListSubDrawMove( p_drawwork, p_drawglb,
				CalcTool_CircleVectroDistRotaGet( ZKN_POKELIST_SUB_MOVE_CACL_R, cp_datawork->move_dist ), // 移動距離を回転角度に変更
				cp_datawork->wheel_rota_par );		
	}else if( cp_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NORMAL ){
		// lockされているときの動き
		ZknPokeListSubDrawMoveLockTime( p_drawwork, p_drawglb, cp_glb );
	}else{
		// 完全lock何もしません
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
static int ZknPokeListSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_POKELIST_SUB_GLB* cp_glb = cp_glbdata;
	const ZKN_POKELIST_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_SUB_GLBDRAW* p_drawglb = p_glbdraw;
	ZKN_POKELIST_SUB_DRAWWORK* p_drawwork = p_drawdata->p_work;
	BOOL check;

	
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_SUB_SEQDELETE_FADEOUT_INIT:
		ChangeBrightnessRequest( ZKN_POKELIST_SUB_FADEIN_COUNT, 
				BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_SUB_SEQDELETE_RELEASE:
		ZknPokeListSubResDelete( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_SUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}
	
	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ホイール面ボタン作成
 *
 *	@param	p_work	ホイールワーク
 *	@param	p_glb	グローバルデータ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonMake( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb, int heap )
{
	ZKN_POKELIST_SUB_BUTTON_WORK* p_button_work;
	
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_POKELIST_SUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELIST_SUB_SEARCH_BUTTON_Y - (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_Y + (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_X - (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_SEARCH_BUTTON_X + (ZKN_POKELIST_SUB_SEARCH_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ],
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y - (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y + (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X - (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X + (ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ],
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y - (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y + (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X - (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X + (ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_LISTSTART ],
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y - (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y + (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_X - (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_LISTSTART_BUTTON_X + (ZKN_POKELIST_SUB_LISTSTART_BUTTON_SIZE_X/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_LISTEND ],
			ZKN_POKELIST_SUB_LISTEND_BUTTON_Y - (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_Y + (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_Y/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_X - (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X/2),
			ZKN_POKELIST_SUB_LISTEND_BUTTON_X + (ZKN_POKELIST_SUB_LISTEND_BUTTON_SIZE_X/2) );

	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.x	 = ZKN_POKELIST_SUB_CX;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.y	 = ZKN_POKELIST_SUB_CY;
	p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_WHEEL ].circle.r	 = ZKN_POKELSIT_SUB_R;


	// CANCELボタン用
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_POKELIST_SUB_BUTTON_CANCEL ],
			ZKN_POKELIST_SUB_BUTTON_HIT_Y,
			ZKN_POKELIST_SUB_BUTTON_HIT_Y + ZKN_POKELIST_SUB_BUTTON_HIT_HEIGHT,
			ZKN_POKELIST_SUB_BUTTON_HIT_X,
			ZKN_POKELIST_SUB_BUTTON_HIT_X + ZKN_POKELIST_SUB_BUTTON_HIT_WIDHT);

	// ボタン用ワーク作成
	p_button_work = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_SUB_BUTTON_WORK) );	
	p_button_work->p_work = p_work;
	p_button_work->p_glb  = p_glb;
	p_work->p_button_work = p_button_work;


	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_POKELIST_SUB_BUTTON_NUM,
			ZknPokeListSubButtonCallBack,
			p_button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイールボタン動作
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonMove( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_POKELIST_SUB_BUTTON_NUM; i++ ){
		p_glb->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;
	}

	// キーによるボタン動作
	ZknPokeListSubButton_KeyMove( p_glb );
	
	// タッチパネルによるボタン操作
	BMN_Main( p_work->p_button_man );

	// 次のリストに進めるかチェックする
	if( ZknPokeListSubListMoveOkCheck( p_work, p_glb->p_pokelist_glb->p_glb ) == FALSE ){
		p_work->move_dist = 0;
	}

	// ホイール描画反映パーセント計算
#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
	if( p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_WHEEL ] != ZKN_UTIL_BUTTON_PUSH_NONE ){
		// タッチパネルに触ったときは、動かした角度で反映数を変更させる
		p_work->wheel_rota_par = ZknPokeListSubDrawRefParCalc( p_work->wheel_rota_par, p_work->move_dist );
	}else{
		// タッチパネルに触っていないときは、動かしていないとして
		// ０で計算する
		p_work->wheel_rota_par = ZknPokeListSubDrawRefParCalc( p_work->wheel_rota_par, 0 );
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイールボタン破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonDelete( ZKN_POKELIST_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	sys_FreeMemoryEz( p_work->p_button_work );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイールボタンコールバック
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		イベントナンバー
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_POKELIST_SUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_POKELIST_SUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_POKELIST_SUB_WORK* p_datawork = p_button_work->p_work;
	ZKN_GLB_DATA* p_zkn_glb = p_glb->p_pokelist_glb->p_glb;
	int poketbl_num;
	int zkn_mode;


	// ボタンイベントデータ設定
	p_glb->button_event[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_TOUCH:
		p_datawork->tp_last_x = sys.tp_x;
		p_datawork->tp_last_y = sys.tp_y;
		break;

	case BMN_EVENT_HOLD:
		switch( button_no ){
		case ZKN_POKELIST_SUB_BUTTON_SEARCH:
			p_glb->p_pokelist_glb->sort_chg = TRUE;
			break;

		case ZKN_POKELIST_SUB_BUTTON_ZUKANCHG:
			p_glb->p_pokelist_glb->zukan_chg = TRUE;
			break;
				
		case ZKN_POKELIST_SUB_BUTTON_ZUKANSEE:
			p_glb->p_pokelist_glb->zukan_see = TRUE;
			break;
			
		case ZKN_POKELIST_SUB_BUTTON_LISTSTART:
			if( p_datawork->touch_hold == FALSE ){
				ZknPokeListSub_ListNoChange( p_glb, 0 );
			}
			break;
			
		case ZKN_POKELIST_SUB_BUTTON_LISTEND:
			if( p_datawork->touch_hold == FALSE ){
				poketbl_num = ZKN_GLBDATA_PokeListTblNumGet( p_zkn_glb );
				ZknPokeListSub_ListNoChange( p_glb, poketbl_num - 1 );
			}
			break;

		case ZKN_POKELIST_SUB_BUTTON_CANCEL:
			// CANCELまたは、分布図OFF
			if(  p_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
				p_glb->p_pokelist_glb->zukan_end = TRUE;
			}else{
				p_glb->p_pokelist_glb->zukan_sort_end = TRUE;
			}
			break;

		default:
			break;
		}

		if( button_no == ZKN_POKELIST_SUB_BUTTON_WHEEL ){
 
			// メイン画面側でタッチパネル動作をホールドしていないかチェック
			if( p_glb->p_pokelist_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NONE ){
				// 移動した距離を求める
				ZknPokeListSubMoveDistGet( p_datawork );	

				// 距離がZKN_POKELIST_SUB_SUB_MIN_SP未満なら０にする
				if( (p_datawork->move_dist <= ZKN_POKELIST_SUB_SUB_MIN_SP) &&
					(p_datawork->move_dist >= -ZKN_POKELIST_SUB_SUB_MIN_SP) ){
					p_datawork->move_dist = 0;
				}

			}

			p_datawork->tp_last_x = sys.tp_x;
			p_datawork->tp_last_y = sys.tp_y;
		}
		p_datawork->touch_hold = TRUE;
		break;

	default:
		p_datawork->touch_hold = FALSE;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストサブ画面　リソース読み込み
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	// 背景
	ZknPokeListSubBgLoad( p_drawglb, cp_glb, heap );

	// ホイール
	ZknPokeListSubBgSetUp( p_drawglb, heap );

	// OAM
	ZknPokeListSubOamResLoad( p_work, p_drawglb, heap );

	// セルアクター登録
	ZknPokeListSubAddClact( p_work, p_drawglb, cp_glb, heap );

	// FONTOAM登録
	ZknPokeListSubFontMake( p_work, p_drawglb, cp_glb, heap );

	// BG優先順位変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 3 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストサブ画面　リソース破棄
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	// FONTOAM
	ZknPokeListSubFontDelete( p_work );

	// CLACT
	ZknPokeListSubDeleteClact( p_work );

	// OAM
	ZknPokeListSubOamResRelease( p_work, p_drawglb );

	// BG
	ZknPokeListSubBgDelete( p_drawglb, heap );

	// BG優先順位変更
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストサブ画面　BG面の設定
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgLoad( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;

	
	
	// パレットデータ転送
	ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_NCLR, PALTYPE_SUB_BG, 0, 0, heap );

	// ｿｰﾄﾓｰﾄﾞの時は色変更
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){

		ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list2_NCLR, PALTYPE_SUB_BG, ZKN_POKELIST_SUB_BACK_PL * 32, 32, heap );
	}else{

		// 全国図鑑のときは色を変える
		if( ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_pokelist_glb->p_glb ) == ZKN_MODE_ZENKOKU ){
			ZKN_GLBDATA_PalSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list4_NCLR, PALTYPE_SUB_BG, ZKN_POKELIST_SUB_BACK_PL * 32, 32, heap );
		}
	}

	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_sub_lzh_NCGR, p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_BACK_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストサブ画面　OAMリソース読み込み
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubOamResLoad( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_glb_draw;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_glb_draw );
	
	// キャラクタデータ読み込み
	p_work->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR + ZKN_POKELIST_SUB_RES_ID_OFS,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_work->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_work->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_work->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_POKELIST_SUB_TBL_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_work->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_work->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_work->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_list_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NCER + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_work->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_list_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_list_oam_sub_lzh_NANR + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_CELLANM_RES, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストサブ画面　OAMリソース破棄
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubOamResRelease( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_glb_draw;


	CLACT_U_CharManagerDelete( p_work->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_work->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_work->res_obj[ CLACT_U_CELLANM_RES ] );

}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイールセルアクター登録
 *
 *	@param	p_work		ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubAddClact( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_glb_draw;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_list_oam_sub_lzh_NCGR + ZKN_POKELIST_SUB_RES_ID_OFS,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS, 
			NARC_zukan_zkn_list_oam_sub_lzh_NCER + ZKN_POKELIST_SUB_RES_ID_OFS,
			NARC_zukan_zkn_list_oam_sub_lzh_NANR + ZKN_POKELIST_SUB_RES_ID_OFS,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 8;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// ポケモンを探す
	add.mat.x = ZKN_POKELIST_SUB_SEARCH_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_SEARCH_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ],
			ZKN_POKELSIT_SUB_SEARCH_BUTTON_SEQ );
	// ｿｰﾄﾓｰﾄﾞの時は非表示
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		CLACT_SetDrawFlag( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ], FALSE );
	}

	// 図鑑を切り替える
	add.mat.x = ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_ZUKANCHG_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], ZKN_POKELSIT_SUB_ZUKANCHG_BUTTON_SEQ );

	// 図鑑を切り替えられないときは非表示にする
	// ｿｰﾄﾓｰﾄﾞの時は非表示
	if( (ZKN_GLBDATA_PokeZknModeChengeCheck( cp_glb->p_pokelist_glb->p_glb, ZKN_MODE_ZENKOKU ) == FALSE) ||
		(cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT) ){
		CLACT_SetDrawFlag( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ], FALSE );
	}

	// 図鑑を見る
	add.mat.x = ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_ZUKANSEE_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ], ZKN_POKELSIT_SUB_ZUKANSEE_BUTTON_SEQ );

	// リストの先頭へ
	add.mat.x = ZKN_POKELIST_SUB_LISTSTART_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_LISTSTART_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->list_start = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->list_start, ZKN_POKELSIT_SUB_LISTSTART_BUTTON_SEQ );

	// リストの最後尾へ
	add.mat.x = ZKN_POKELIST_SUB_LISTEND_BUTTON_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_LISTEND_BUTTON_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->list_end = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->list_end, ZKN_POKELSIT_SUB_LISTEND_BUTTON_SEQ );


	// Bというボタン
	add.mat.x = ZKN_POKELIST_SUB_BUTTON_B_X << FX32_SHIFT;
	add.mat.y = ZKN_POKELIST_SUB_BUTTON_B_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_work->act_B = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->act_B, ZKN_POKELIST_SUB_BUTTON_B_ANM );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDeleteClact( ZKN_POKELIST_SUB_DRAWWORK* p_work )
{
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	CLACT_Delete( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	CLACT_Delete( p_work->list_start );
	CLACT_Delete( p_work->list_end );
	CLACT_Delete( p_work->act_B );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_work		ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubFontMake( ZKN_POKELIST_SUB_DRAWWORK* p_work, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_glb_draw;
	int pltt_ofs;	// パレットアドレス

	// 先にCLACTを登録してある必要がある
	GF_ASSERT( p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_POKELIST_SUB_RES_ID_OFS );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.x			 = ZKN_POKELIST_SUB_FONTOAM_OFS_X;
	fontoam_init.y			 = ZKN_POKELIST_SUB_FONTOAM_OFS_Y;
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );

	// SORT画面へ
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_POKELIST_BUTTON_05, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_SEARCH ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL );
	// ｿｰﾄﾓｰﾄﾞの時は非表示
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		FONTOAM_SetDrawFlag( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ]->p_fontoam, FALSE );
	}

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );

	// 図鑑切り替え
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_POKELIST_BUTTON_03, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL );

	// 図鑑を切り替えられないときは非表示にする
	if( (ZKN_GLBDATA_PokeZknModeChengeCheck( cp_glb->p_pokelist_glb->p_glb, ZKN_MODE_ZENKOKU ) == FALSE) ||
		(cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT) ){
		FONTOAM_SetDrawFlag( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ]->p_fontoam, FALSE );
	}
	
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CX,
			ZKN_POKELSIT_SUB_FONT_BMP_SIZE_CY );
	
	// 図鑑を見る
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->clact[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ];
	p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ]->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL_ZUKAN );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_POKELIST_SUB_FONT_B_BMP_CX,
			ZKN_POKELIST_SUB_FONT_B_BMP_CY );

	// Bボタンの横のフォントOAM
	if( cp_glb->p_pokelist_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_BACK_00, 0, 0 );
	}else{
		ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
				NARC_msg_zkn_dat, ZNK_BACK_01, 0, 0 );
	}
	fontoam_init.p_bmp		 = win;
	fontoam_init.parent = p_work->act_B;
	fontoam_init.x			 = ZKN_POKELIST_SUB_FONT_B_OFS;
	fontoam_init.y			 = ZKN_POKELIST_SUB_FONT_B_OFS_Y;
	p_work->p_fontoam_B = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_work->p_fontoam_B->p_fontoam, pltt_ofs + ZKN_POKELIST_SUB_BUTTON_FONT_COL_CLOSE );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubFontDelete( ZKN_POKELIST_SUB_DRAWWORK* p_work )
{
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] );
	ZKN_FONTOAM_Delete( p_work->p_fontoam_B );
}



//----------------------------------------------------------------------------
/**
 *	@brief	ホイール面の表示	
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgSetUp( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_disk_lzh_NCGR, p_bg, ZKN_BG_FRM_AFFINE_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_glb_draw, NARC_zukan_zkn_list_bg_disk_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_bg, ZKN_BG_FRM_AFFINE_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_bg, ZKN_BG_FRM_AFFINE_S );

	// スクリーン座標を設定
	GF_BGL_ScrollSet( p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_X_SET, ZKN_POKELIST_SUB_BGFADE_DEF_X );
	GF_BGL_ScrollSet( p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_Y_SET, ZKN_POKELSIT_SUB_MAT_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリーンを初期化
 *
 *	@param	p_drawglb	描画グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubBgDelete( ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int heap )
{
	GF_BGL_INI* p_bg = p_drawglb->p_glb_draw->p_bg;
	GF_BGL_ClearCharSet( ZKN_BG_FRM_AFFINE_S, 64, 0, heap );
	GF_BGL_ScrClear( p_bg, ZKN_BG_FRM_AFFINE_S );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストカウント処理
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubListCount( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	int rota;
	ZKN_GLB_DATA* p_zkn_glb = p_glb->p_pokelist_glb->p_glb;

	// 今カウント中でないなら足す
	if( p_glb->p_pokelist_glb->move_count <= 0 ){
		
		// カウント値がある
		if( p_work->move_dist_list != 0 ){
			
			// 登録
			// 失敗したら動作停止
			if( ZknPokeListSubListAdd( p_work, p_zkn_glb ) == FALSE ){

				ZknPokeListSubListMoveStop( p_work, p_glb );
			}else{
				p_glb->p_pokelist_glb->move_count = ZKN_POKELIST_MOVE_END_COUNT;
			
				// 選択移動音
				Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
			}

		}else{

			// 動かず動作カウントも０なら終わり
			p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
		}
	}

	// 方向設定
	if( p_work->move_dist_list < 0 ){
		p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_UP;
	}else{
		if( p_work->move_dist_list > 0 ){
			p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_DOWN;
		}
	}

	// リスト動作
	if( p_glb->p_pokelist_glb->move_way != ZKN_POKE_LIST_NO_MOVE ){
		
		// 絶対値にする
		if( p_work->move_dist_list < 0 ){
			rota = -p_work->move_dist_list;
		}else{
			rota = p_work->move_dist_list;
		}

		// カウント値を取得
		rota /= ZKN_POKELIST_SUB_COUNT_R;

		// カウント処理
		p_glb->p_pokelist_glb->move_count -= rota;
		// カウンタが最後まで行ったかチェック
		if( p_glb->p_pokelist_glb->move_count < 0 ){	
			p_glb->p_pokelist_glb->move_count = 0;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転した距離を取得		06.08.02移動距離に変更
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubMoveDistGet( ZKN_POKELIST_SUB_WORK* p_work )
{
	int last_y, last_x;
	int now_y, now_x;

	// ホイールの中心座標からの値にする
	last_x = p_work->tp_last_x - ZKN_POKELIST_SUB_CX;
	last_y = p_work->tp_last_y - ZKN_POKELIST_SUB_CY;
	now_x = sys.tp_x - ZKN_POKELIST_SUB_CX;
	now_y = sys.tp_y - ZKN_POKELIST_SUB_CY;

	// 動さ値を求める
//	p_work->move_dist = CalcTool_CircleVectorMove( last_x, last_y, now_x, now_y );
	p_work->move_dist = CalcTool_CircleVectorDistance( last_x, last_y, now_x, now_y, ZKN_POKELIST_SUB_MOVE_CACL_R );
	p_work->move_dist *= ZKN_POKELIST_SUB_MOVE_CACL_MUL;

#if 0
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( now_y, now_x );

	p_work->move_dist = now_rota - last_rota;

	// 絶対値を求める
	if( p_work->move_dist < 0 ){
		zettai = -p_work->move_dist;
	}else{
		zettai = p_work->move_dist;
	}

	// 180以上になることは考えにくいその場合は,０を３６０として考える
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360という考えになるからベクトルを変える必要がある
	}

	// 設定
	if( p_work->move_dist < 0 ){
		p_work->move_dist = -zettai;
	}else{
		p_work->move_dist = zettai;
	}
#endif
}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイールの描画動作
 *
 *	@param	p_drawwork	描画ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	add_num		回転角を動かす値
 *	@param	draw_ref_par	描画回転角反映パーセント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDrawMove( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, int add_num, fx32 draw_ref_par )
{
#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
	int add_rot_num;
	add_rot_num = FX_Mul( add_num*FX32_ONE, draw_ref_par ) >> FX32_SHIFT;
	
	// 回転角度を求める
	p_drawwork->wheel_rota += add_rot_num;
	p_drawwork->wheel_rota &= 0xffff;
#else

	// 回転角度を求める
	p_drawwork->wheel_rota += add_num;
	p_drawwork->wheel_rota &= 0xffff;
#endif

	// 回転角度の設定
	GF_BGL_RadianSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_drawwork->wheel_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_POKELIST_SUB_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_POKELIST_SUB_BGCY );

	// lockされたと起用に角度を保存
	p_drawwork->save_wheel_rota = p_drawwork->wheel_rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	lockされているときにホイールの絵を動かす
 *
 *	@param	p_drawwork		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubDrawMoveLockTime( ZKN_POKELIST_SUB_DRAWWORK* p_drawwork, ZKN_POKELIST_SUB_GLBDRAW* p_drawglb, const ZKN_POKELIST_SUB_GLB* cp_glb )
{
	int rota_num;
	int calc;
	int count = ZKN_POKELIST_MOVE_END_COUNT - cp_glb->p_pokelist_glb->move_count;
	
	//　今の角度計算
	calc = ZKN_POKELIST_SUB_LOCK_MOVE_DRAW_MAX * count;
	rota_num = calc / ZKN_POKELIST_MOVE_END_COUNT;
	
	// -方向設定
	if( cp_glb->p_pokelist_glb->move_way == ZKN_POKE_LIST_UP ){
		rota_num = -rota_num;
	}

	// 回転角度を求める
	p_drawwork->wheel_rota = p_drawwork->save_wheel_rota + rota_num;
	p_drawwork->wheel_rota &= 0xffff;

	// 回転角度の設定
	GF_BGL_RadianSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_drawwork->wheel_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_POKELIST_SUB_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_glb_draw->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_POKELIST_SUB_BGCY );


	// 動作カウンタが0の時回転角をセーブする
	if( cp_glb->p_pokelist_glb->move_count == 0 ){
		p_drawwork->save_wheel_rota = p_drawwork->wheel_rota;
	} 
}


//----------------------------------------------------------------------------
/**
 *	@brief	ホイールのスピードを落とす
 *
 *	@param	p_work	ワーク
 *	@param	move_count 動作カウンタ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubResist( ZKN_POKELIST_SUB_WORK* p_work, int move_count, int move_way )
{
	// 描画用回転角計算
	if( p_work->move_dist > 0 ){
		if( p_work->move_dist - ZKN_POKELIST_SUB_SUB_R >= ZKN_POKELIST_SUB_SUBDRAWLIMIT_R ){

			p_work->move_dist -= ZKN_POKELIST_SUB_SUB_R;
		}else{
			p_work->move_dist = ZKN_POKELIST_SUB_SUBDRAWLIMIT_R;
		}
	}else{

		if( p_work->move_dist + ZKN_POKELIST_SUB_SUB_R <= -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R ){
			p_work->move_dist += ZKN_POKELIST_SUB_SUB_R;
		}else{
			p_work->move_dist = -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R;
		}
	}

	// 距離を値反映用距離に設定
	p_work->move_dist_list = p_work->move_dist;


	// 動作距離が　ZKN_POKELIST_SUB_COUNT_Rのときで
	// move_countが0なら回転を止める
	if( (p_work->move_dist <= ZKN_POKELIST_SUB_SUBLIMIT_R) && 
		(p_work->move_dist >= -ZKN_POKELIST_SUB_SUBLIMIT_R)){
		if( move_count == 0 ){
			p_work->move_dist_list = 0;

			// さらにZKN_POKELIST_SUB_SUBDRAWLIMIT_R以下なら描画用
			// ｶｳﾝﾀもとめる
			if( (p_work->move_dist <= ZKN_POKELIST_SUB_SUBDRAWLIMIT_R) && 
				(p_work->move_dist >= -ZKN_POKELIST_SUB_SUBDRAWLIMIT_R)){
				p_work->move_dist = 0;

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
				p_work->wheel_rota_par = ZKN_POKELIST_SUB_LIST_PAR_MIN;
#endif
			}
		}else{

			// カウントがとまらないように
			// ZKN_POKELIST_SUB_COUNT_Rいかにしない
			if( move_way == ZKN_POKE_LIST_UP ){
				p_work->move_dist_list = -ZKN_POKELIST_SUB_SUBLIMIT_R;
				p_work->move_dist = -ZKN_POKELIST_SUB_SUBLIMIT_R;
			}else{
				p_work->move_dist_list = ZKN_POKELIST_SUB_SUBLIMIT_R;
				p_work->move_dist = ZKN_POKELIST_SUB_SUBLIMIT_R;
			}
		}
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
static void ZknPokelistSubButtonFontMove( CLACT_WORK_PTR act, ZKN_FONTOAM_DATA* p_fontoam, int def_y, int off_pltt, int on_pltt )
{
	ZKN_UTIL_ButtonFontMove_Col( act, p_fontoam, def_y, off_pltt, on_pltt );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面の管理しているキー操作によるボタンの動作
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubButton_KeyMove( ZKN_POKELIST_SUB_GLB* p_glb )
{
	ZKN_POKELIST_GLB_DATA* p_main_glb = p_glb->p_pokelist_glb;
	
	// 図鑑画面へ
	if( p_main_glb->zukan_see ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANSEE ] = BMN_EVENT_HOLD;
		return;
	}//*/

	// SORT画面へ
	if( p_main_glb->sort_chg ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_SEARCH ] = BMN_EVENT_HOLD;
		return;
	}

	// 図鑑を切り替える
	if( p_main_glb->zukan_chg ){
		p_glb->button_event[ ZKN_POKELIST_SUB_BUTTON_ZUKANCHG ] = BMN_EVENT_HOLD;
		return;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ホイールの進んでいる方向を見て、その方向に進めるかチェック
 *
 *	@param  p_work		ワーク
 *	@param	p_glb		図鑑グローバルデータ
 *
 *	@retval	TRUE	まだ回ってOK
 *	@retval	FALSE	回っちゃだめ
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListSubListMoveOkCheck( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb )
{
	int add_count;

	if( p_work->move_dist != 0 ){

		// リストを足すことができるのかチェック
		// 足す値を代入
		if( p_work->move_dist < 0 ){
			add_count = 1;
		}else{
			add_count = -1;
		}
		// 失敗したら動作停止
		if( ZKN_GLBDATA_PokeListDrawTblNoAddCheck( p_glb, add_count ) == FALSE ){
			return FALSE;
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リスト足し算
 *
 *	@param  p_work		ワーク
 *	@param	p_glb		図鑑グローバルデータ
 *
 *	@retval	TRUE	まだ回ってOK
 *	@retval	FALSE	回っちゃだめ
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListSubListAdd( ZKN_POKELIST_SUB_WORK* p_work, ZKN_GLB_DATA* p_glb )
{
	int add_count;

	if( p_work->move_dist_list != 0 ){

		// リストを足すことができるのかチェック
		// 足す値を代入
		if( p_work->move_dist_list < 0 ){
			add_count = 1;
		}else{
			add_count = -1;
		}
		// 失敗したら動作停止
		if( ZKN_GLBDATA_PokeListDrawTblNoAdd( p_glb, add_count ) == FALSE ){
			return FALSE;
		}
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ホイール強制終了
 *
 *	@param	p_work
 *	@param	p_glb 
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSubListMoveStop( ZKN_POKELIST_SUB_WORK* p_work, ZKN_POKELIST_SUB_GLB* p_glb )
{
	p_work->move_dist_list = 0;
	p_work->move_dist = 0;
	p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストナンバー設定
 *
 *	@param	p_glb	グローバルデータ
 *	@param	no		リストナンバー
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSub_ListNoChange( ZKN_POKELIST_SUB_GLB* p_glb, int no )
{
	// その他画面切り替えリクエストが来ていたら処理しない
	if( ZKN_PokeList_SubEventSetOkCheck( p_glb->p_pokelist_glb ) == FALSE ){
		return ;
	}
	
	ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_pokelist_glb->p_glb, no );

	(*p_glb->p_event_key) |= ZKN_POKELIST_SUB_EVENT_POKELIST;
	// 動作カウンタも初期化
	 p_glb->p_pokelist_glb->move_count = 0;	
	// ホイールの動きを止める
	 p_glb->p_pokelist_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;	
	// フェードインモード変更
	p_glb->p_pokelist_glb->fade_mode = ZKN_POKELIST_BG_FADE_SHUTTER;
	p_glb->p_pokelist_glb->fade_zukan_data = FALSE;
	// 方向もなし
	p_glb->p_pokelist_glb->move_way = ZKN_POKE_LIST_NO_MOVE;
	// 表示の変更はフェード終了してから
	p_glb->p_pokelist_glb->move_draw = FALSE;
}

#ifdef ZKN_POKELIST_SUB_LIST_PAR_SET
//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹﾓﾝﾘｽﾄ描画　ホイール回転角反映パーセント計算関数
 *
 *	@param	now_par		現在の反映パーセント
 *	@param	now_rota	今プレイヤーが入力した回転角
 *
 *	@return	計算後の反映パーセント
 */
//-----------------------------------------------------------------------------
static fx32 ZknPokeListSubDrawRefParCalc( fx32 now_par, s32 now_rota )
{
	int abs_add;
	
	abs_add = MATH_ABS( now_rota );

	// 足す値の反映率を変更
	if( abs_add < ZKN_POKELIST_SUB_LIST_PAR_ADD_LIMIT ){
		if( (now_par - ZKN_POKELIST_SUB_LIST_PAR_SUB) >= ZKN_POKELIST_SUB_LIST_PAR_MIN){
			now_par -= ZKN_POKELIST_SUB_LIST_PAR_SUB;
		}
	}else{
		if( (now_par + ZKN_POKELIST_SUB_LIST_PAR_ADD) <= ZKN_POKELIST_SUB_LIST_PAR_MAX ){
			now_par += ZKN_POKELIST_SUB_LIST_PAR_ADD;
		}
	}

	return now_par;
}
#endif
