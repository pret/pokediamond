//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_pokelist.c
 *	@brief		ポケモンリスト
 *	@author		tomoya takahashi
 *	@data		2006.01.18
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
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"

#define __ZKN_POKELIST_H_GLOBAL
#include "include/application/zukanlist/zkn_pokelist.h"

// エフェクトで座標をLinkさせるため、仕方なくインクルード
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
//-------------------------------------
// ポケモンリスト描画処理初期化シーケンス
//=====================================
enum{
	ZKN_POKELIST_DRAWINIT_SEQ_GRA_LOAD,
	ZKN_POKELIST_DRAWINIT_SEQ_FADEIN,
	ZKN_POKELIST_DRAWINIT_SEQ_FADEIN_WAIT,
	ZKN_POKELIST_DRAWINIT_SEQ_END,
};

//-------------------------------------
// ポケモンリスト描画処理メインシーケンス
//=====================================
enum{
	ZKN_POKELIST_DRAWMAIN_SEQ_END,
};

//-------------------------------------
// ポケモンリスト描画処理破棄シーケンス
//=====================================
enum{
	ZKN_POKELIST_DRAWEND_SEQ_FADEOUT,
	ZKN_POKELIST_DRAWEND_SEQ_FADEOUT_WAIT,
	ZKN_POKELIST_DRAWEND_SEQ_GRA_RELEASE,
	ZKN_POKELIST_DRAWEND_SEQ_END,
};


#define EVENT_DATA_NUM		( 5 )

// イベント定数
#define EVENT_MSK_POKELIST_CHENGE_SORTSEARCH	( 1 << 0 )
#define EVENT_MSK_POKELIST_CHENGE_ZUKAN			( 1 << 1 )
#define EVENT_MSK_POKELIST_ZUKAN_END			( 1 << 2 )
#define EVENT_MSK_POKELIST_MAIN_CHANGE			( 1 << 3 )
#define EVENT_MSK_POKELIST_CHANGE				( 1 << 4 )

// 動作定数
#define ZKN_POKE_LIST_MOVE_CHENGE_NUM		( 4 )	// スピードを変更する回数
#define ZKN_POKE_LIST_MOVE_CHENGE_TIMING	( 4 )	// この回数ポケモンデータナンバーを変更したらスピードを変更
#define ZKN_POKE_LIST_MOVE_COUNT_S		( 60 )	// 1=10の単位
#define ZKN_POKE_LIST_MOVE_COUNT_MUL	( 1.60f )	// カウントアップ数加算値

#define ZKN_POKE_LIST_MOVE_SKIP_NUM	( 5 )		// スキップ数


// フェードイン定数
#define ZKN_POKELIST_FADEIN_SYNC	( ZKN_FADE_SYNC_LONG_COMMON)		// フェードインシンク数
// フェードアウト定数
#define ZKN_POKELIST_FADEOUT_SYNC	( ZKN_FADE_SYNC_LONG_COMMON)		// フェードインシンク数

// BGブライトネスフェード面
#define ZKN_POKELSIT_BRIGHTNESS_MSK	( GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD )	// 通常
#define ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK	( GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )	// 図鑑フェード用
#define ZKN_POKELIST_BRIGHTNESS_ZUKAN_END_MSK	( GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )



// 背景
#define ZKN_POKELIST_BACK_POKEFRAME_CX	( 1 )
#define ZKN_POKELIST_BACK_POKEFRAME_CY	( 4 )


// 文字面
#define ZKN_POKELIST_STR_Y			( 152 )
#define ZKN_POKELIST_SEE_STR_X		( 8 )
#define ZKN_POKELIST_GET_STR_X		( 128 )
#define ZKN_POKELIST_SEE_NUM_X		( 48 )
#define ZKN_POKELIST_SEE_NUM_Y		( 170 )
#define ZKN_POKELIST_GET_NUM_X		( 180 )
#define ZKN_POKELIST_GET_NUM_Y		( 170 )
#define ZKN_POKELIST_NUM_STR		( 32 )	// バッファサイズ
#define ZKN_POKELIST_PLACE			( 3 )	// 桁




// セルアクターリソース数
#define ZKN_POKELIST_CELL_CG_NUM	( 2 )
#define ZKN_POKELIST_CELL_CL_NUM	( 2 )
#define ZKN_POKELIST_CELL_CE_NUM	( 2 )
#define ZKN_POKELIST_CELL_AN_NUM	( 2 )


// ポケモンテーブル定数
#define ZKN_POKELIST_POKETBL_NUM	(9)		// 表示用ポケモンテーブル数
#define ZKN_POKELIST_POKETBL_CHECK	(4)		// 選択ポケモンの位置
#define ZKN_POKELIST_POKETBL_TBL_DEFX	( 180 * FX32_ONE )
#define ZKN_POKELIST_POKETBL_TBL_CHECKX	( ZKN_POKELIST_TBL_MAT_X * FX32_ONE )
const static ZknPokeListPokeTblMoveX[] = {		// 動作テーブル
	ZKN_POKELIST_POKETBL_TBL_DEFX + 9*FX32_ONE,		// 控え
	ZKN_POKELIST_POKETBL_TBL_DEFX + 5*FX32_ONE,		// 描画 
	ZKN_POKELIST_POKETBL_TBL_DEFX + 1*FX32_ONE,		// 描画 
	ZKN_POKELIST_POKETBL_TBL_DEFX - 3*FX32_ONE,		// 描画 
	ZKN_POKELIST_POKETBL_TBL_DEFX - 5*FX32_ONE,		// 描画
	ZKN_POKELIST_POKETBL_TBL_CHECKX,	// 選択
	ZKN_POKELIST_POKETBL_TBL_DEFX - 5*FX32_ONE,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX - 3*FX32_ONE,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX + 1*FX32_ONE,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX + 5*FX32_ONE,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX + 9,		// 控え
};
const static ZknPokeListPokeTblMoveY[] = {		// 動作テーブル
	12 * FX32_ONE,
	22 * FX32_ONE,		// ここから描画
	26 * FX32_ONE,
	42 * FX32_ONE, 
	58 * FX32_ONE,
	82 * FX32_ONE,		// 選択
	106 * FX32_ONE,
	122 * FX32_ONE,
	138 * FX32_ONE,
	142 * FX32_ONE,		// ここまで
	152 * FX32_ONE,
};
#if 0
const static ZknPokeListPokeTblMoveX[] = {		// 動作テーブル
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 予備
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 控え
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 描画 
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 描画
	ZKN_POKELIST_POKETBL_TBL_CHECKX,	// 選択
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 描画
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 控え
	ZKN_POKELIST_POKETBL_TBL_DEFX,		// 予備
};
const static ZknPokeListPokeTblMoveY[] = {		// 動作テーブル
	7 * FX32_ONE,	// 5
	12 * FX32_ONE,	// 10
	22 * FX32_ONE,	// 26
	48 * FX32_ONE,  // 34
	82 * FX32_ONE,
	116 * FX32_ONE,
	142 * FX32_ONE,
	152 * FX32_ONE,
	157 * FX32_ONE,
};
#endif
#define ZKN_POKELIST_PLTT_SELECT	(0)		// 中央のリストのカラー
#define ZKN_POKELIST_PLTT_OTHER0	(7)		// その他のリストのカラー
#define ZKN_POKELIST_PLTT_OTHER1	(8)		// その他のリストのカラー
#define ZKN_POKELIST_PLTT_OTHER2	(9)		// その他のリストのカラー

#define ZKN_POKELIST_OAM_BG_PRI	( 2 )


// Cursor定数
#define ZKN_POKELIST_CURSOR_X		( 248 * FX32_ONE )	// X座標
#define ZKN_POKELIST_CURSOR_YMIN	( 58 * FX32_ONE )	// 最小Y座標
#define ZKN_POKELIST_CURSOR_YDIS	( 54 * FX32_ONE )	// Y移動距離


// ポケモンOAM定数
#define ZKN_POKELIST_ICON_ANMSEQ	( 1 )
#define ZKN_POKELIST_ICON_PRI		( 0 )
#define ZKN_POKELIST_POKETBL_ANMSEQ	( 0 )
#define ZKN_POKELIST_POKETBL_PRI	( 32 )
#define ZKN_POKELIST_CURSOR_ANMSEQ	( 2 )
#define ZKN_POKELIST_CURSOR_PRI		( 0 )





//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ポケモンリスト描画グローバルデータ
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ
} ZKN_POKELIST_GLB_DRAW;


//-------------------------------------
//	ポケモンリストワーク
//=====================================
typedef struct {
	int move_way;			// 動作方向保存
	int move_count_add_num;	// グローバルデータのmove_count加算数
	int move_speed_chg_timing;	// スピードを変更するタイミング
	int move_speed_chg_num;	// スピードを変更した数

	int sub_seq;		// サブで動く処理用のシーケンス
	
	BOOL skip_flag;		// スキップフラグ
	int skip_count;		// スキップカウンタ
	int skip_add;		// 1回の足し算値
	int skip_way;		// スキップ方向

} ZKN_POKELIST_WORK;

//-------------------------------------
//	ポケモンリストグラフィックワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR	poke_tbl[ ZKN_POKELIST_POKETBL_NUM ];// ポケモン名テーブル
	int poke_tbl_start;				// ポケモン名テーブルの座標０の要素数
	ZKN_FONTOAM_DATA* poke_name[ ZKN_POKELIST_POKETBL_NUM ];// ポケモン名OAM
	int poke_name_char_size;		// ポケモン名のキャラクタデータを転送する領域のサイズ

	CLACT_WORK_PTR	icon[ ZKN_POKELIST_POKETBL_NUM ];// ポケモン名テーブル指定アイコン
	CLACT_WORK_PTR	cursor;			// 全体の現在の位置カーソル
	fx32	onepoke_move_dis;		// 1つのポケモンが動いた時のCursorの移動値

	CLACT_WORK_PTR dummy_poke;	// ポケモングラフィックダミー
	
	// リソースマネージャ
	CLACT_U_RES_MANAGER_PTR	res_manager[ ZKN_CLACT_RES_MANAGER_NUM ];	
	
	// セルアクター登録ヘッダ
	CLACT_HEADER		clheader;
	CLACT_HEADER		clheader_dummy_poke;

	void*			p_util_scrn_buff;
	NNSG2dScreenData* p_util_scrn;	// ユーティリティ面のスクリーンデータ
	ZKN_UTIL_BGSHTTER_DADE bg_fade;	// BG面フェードデータ

	// 図鑑フェード用動作ワーク
	ZKN_UTIL_MOVE_WORK pokegra_move;
	ZKN_UTIL_MOVE_WORK pokelist_move;


	// 今中央に表示されているポケモンのテーブル要素数（ZKN_GLBDATA.ZKN_POKELIST_TBLの配列の要素数 ）
	int draw_poke_name;				
} ZKN_POKELIST_GRAWORK;


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
static ZKN_POKELIST_GLB_DATA* MakeGlbData( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGlbData( ZKN_POKELIST_GLB_DATA* p_glb );

static ZKN_POKELIST_GLB_DRAW* MakeGlbDraw( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteGlbDraw( ZKN_POKELIST_GLB_DRAW* p_glb );

// イベントデータ関係
static ZKN_EVENT_DATA* MakeEventData( int heap, ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys );
static void DeleteEventData( ZKN_EVENT_DATA* p_event_data );
static int EventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		アプリケーションプロセス関係
 */
//-----------------------------------------------------------------------------
// プロセス関数
static int ZknPokeListProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknPokeListProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknPokeListProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// FadeInOut
static void ZknPokeListDefaultFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL ZknPokeListDefaultFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static void ZknPokeListChZukanFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL ZknPokeListChZukanFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );

static void PokeListBgFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );
static BOOL PokeListBgFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static void PokeListBgFadeDel( ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out );

static void PokeListPokeGraFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static BOOL PokeListPokeGraFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static void PokeListPokeListFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );
static BOOL PokeListPokeListFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb );


// 動作部分
static void PokeListMoveMain( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap );
static BOOL PokeListMoveIf( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap );
static void PokeListMoveIfFlagReset( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListMoveIfKey( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );
static void PokeListMoveUp( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );
static void PokeListMoveReq( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int way );
static BOOL PokeListMoveAdd( ZKN_POKELIST_GLB_DATA* p_glb, int num );

static BOOL PokeListListReset( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListListStart( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListListEnd( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );

static void PokeListSkipMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work );

static void PokeListZukanDel( ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListZukanChg( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListSortChg( ZKN_POKELIST_GLB_DATA* p_glb );
static BOOL PokeListZukanModeChg( ZKN_POKELIST_GLB_DATA* p_glb, int heap );
static void PokeListZukanReset( ZKN_POKELIST_GLB_DATA* p_glb, int heap );
static void PokeListSkipMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );
static void PokeListKeyMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb );

// 内部ワーク作成
static void PokeListDrawWorkInit( ZKN_POKELIST_GRAWORK*	p_work, const ZKN_POKELIST_GLB_DATA* cp_dataglb );

// ファイル読み込み＆画面作成
static void PokeListLoadGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListReleaseGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb );
static void PokeListLoadGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListReleaseGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb );

static void PokeListBackGroundSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListUtilSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int zkn_mode );
static void PokeListUtilDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int see_num, int get_num );
static void PokeListSortVerFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int list_num );
static void PokeListResManagerMake( ZKN_POKELIST_GRAWORK* p_work, int heap );
static void PokeListResManagerDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListClActResLoad( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListClActAdd( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListClActDelete( ZKN_POKELIST_GRAWORK* p_work );

static int PokeListPokeNameCharTransSizeGet( ZKN_GLB_DRAWDATA* p_drawglb, int heap );
static void PokeListPokeNameSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameDelete( ZKN_POKELIST_GRAWORK* p_work );
static void PokeGraphicSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );


static void PokeListOamFadeInit( ZKN_POKELIST_GRAWORK* p_work );
static void PokeListOamFadeDelete( ZKN_POKELIST_GRAWORK* p_work );

// CLACT_OBJパラメータ計算＆設定関数郡
static void PokeListPokeTblInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblDrawFlagSetUp( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeTblListStartNumChenge( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListIconMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListCursorInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListCursorMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb );

static void PokeListPokeNameMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameMoveNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );
static void PokeListPokeNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap, int pokename_tbl_no, int pokelist_tbl_no );
static void PokeListPokeNameDummySet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int pokename_tbl_no, int pokenum );
static void PokeListPokeNameMoveMatGet( CLACT_WORK_PTR target_act, int* x, int* y );
static fx32 PokeListPokeTblMoveCalc( fx32 s, fx32 e, int max_count, int count );
static void PokeListPokeGraMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListDummyPokeGraMove( const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListPokeGraAlphaInit( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb );
static void PokeListSelectPokeDataGlbSet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	アプリケーションデータ	作成
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
void ZKN_PokeListAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_POKELIST_GLB_DATA* p_glb;
	ZKN_POKELIST_GLB_DRAW* p_glb_draw;
	ZKN_EVENT_DATA*	p_event_data_tbl;

	p_glb = MakeGlbData( heap, zkn_sys );
	p_glb_draw = MakeGlbDraw( heap, zkn_sys );
	p_event_data_tbl = MakeEventData( heap, p_data, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_glb_draw;
	p_data->p_event_data	= p_event_data_tbl;
	p_data->event_num		= EventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknPokeListProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknPokeListProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknPokeListProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アプリケーションデータ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PokeListAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteGlbData( p_data->p_glb_data );
	DeleteGlbDraw( p_data->p_glb_draw );
	DeleteEventData( p_data->p_event_data );
}



//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹﾓﾝﾘｽﾄイベントを設定して大丈夫かチェック
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	TRUE	よい
 *	@retval	FALSE	だめ
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PokeList_SubEventSetOkCheck( const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	if( (cp_glb->zukan_sort_end == TRUE) ||		
		(cp_glb->zukan_end == TRUE) ||
		(cp_glb->zukan_see == TRUE) ||
		(cp_glb->zukan_chg == TRUE) ||
		(cp_glb->sort_chg  == TRUE) ){

		return FALSE;
	}
	return TRUE;
}




//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		アプリケーションデータ作成関係
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストのグローバルデータ作成
 *
 *	@param	heap		ヒープ	
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_GLB_DATA* MakeGlbData( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_GLB_DATA*	p_glb;

	// メモリ確保
	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_GLB_DATA) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_GLB_DATA) );
	
	// イベントキーポインタ取得
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys );

	// 図鑑の各アプリケーション共有データ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// フェードインモード変更
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;

	// 図鑑データ画面へのフェードチェックフラグ
	p_glb->fade_zukan_data = FALSE;

	// 描画更新フラグ
	p_glb->move_draw = TRUE;
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルデータ破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGlbData( ZKN_POKELIST_GLB_DATA* p_glb )
{
	GF_ASSERT( p_glb );
	
	sys_FreeMemoryEz(p_glb);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストのグローバルデータ作成
 *
 *	@param	heap		ヒープ	
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_POKELIST_GLB_DRAW* MakeGlbDraw( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_POKELIST_GLB_DRAW*	p_glb;

	// メモリ確保
	p_glb = sys_AllocMemory( heap, sizeof(ZKN_POKELIST_GLB_DRAW) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_POKELIST_GLB_DRAW) );
	

	// 図鑑の各アプリケーション共有グラフィックデータ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルデータ破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteGlbDraw( ZKN_POKELIST_GLB_DRAW* p_glb )
{
	GF_ASSERT( p_glb );
	
	sys_FreeMemoryEz(p_glb);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントデータテーブル作成
 *
 *	@param	heap		ヒープ
 *	@param	p_data		アプリケーションデータ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeEventData( int heap, ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys )
{
	ZKN_EVENT_DATA* p_event_data;

	p_event_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_DATA) *  EventDataNumGet() );
	ZKN_EVENT_MakeChangeSortSearch( heap, &p_event_data[0], zkn_sys, EVENT_MSK_POKELIST_CHENGE_SORTSEARCH );
	ZKN_EVENT_MakeChangeZukan( heap, &p_event_data[1], zkn_sys, EVENT_MSK_POKELIST_CHENGE_ZUKAN );
	ZKN_EVENT_MakeZukanEnd( heap, &p_event_data[2], zkn_sys, EVENT_MSK_POKELIST_ZUKAN_END );
	ZKN_EVENT_MakeStartMainPokeList( &p_event_data[3], zkn_sys, heap, EVENT_MSK_POKELIST_MAIN_CHANGE );
	ZKN_EVENT_MakeChangePokeList( heap, &p_event_data[4], zkn_sys, EVENT_MSK_POKELIST_CHANGE );

	return p_event_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベントデータ破棄
 *
 *	@param	p_event_data		イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteEventData( ZKN_EVENT_DATA* p_event_data )
{
	GF_ASSERT( p_event_data );
	
	ZKN_EVENT_DeleteData( &p_event_data[0] );
	ZKN_EVENT_DeleteData( &p_event_data[1] );
	ZKN_EVENT_DeleteData( &p_event_data[2] );
	ZKN_EVENT_DeleteData( &p_event_data[3] );
	ZKN_EVENT_DeleteData( &p_event_data[4] );

	sys_FreeMemoryEz( p_event_data );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	イベント数取得
 *
 *	@param	none
 *
 *	@return	イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int EventDataNumGet( void )
{
	return	EVENT_DATA_NUM;
}




//-----------------------------------------------------------------------------
/**
 *		アプリケーションプロセス関係
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
static int ZknPokeListProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_GLB_DATA* p_glb = p_glbdata;
	
	// 内部ワーク初期化
	p_dodata->p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_POKELIST_WORK) );
	GF_ASSERT( p_dodata->p_work );
	memset( p_dodata->p_work, 0, sizeof(ZKN_POKELIST_WORK) );

	// 動作データ設定
	PokeListMoveInit( p_glb, p_dodata->p_work );

	// 今のポケリスト位置に描画位置も合わせる
	ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( p_glb->p_glb );
	
	// 描画更新フラグ
	p_glb->move_draw = TRUE;

	// ホイールロックフラグ
	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;


	// ｿｰﾄﾓｰﾄﾞのときはフェードﾀｲﾌﾟをシャッターにする
	if( p_glb->fade_sort_data == TRUE ){
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_SHUTTER;
	}

	// 分岐フラグの初期化
	PokeListMoveIfFlagReset( p_glb );

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
static int ZknPokeListProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_POKELIST_GLB_DATA* p_glb = p_glbdata;
	ZKN_POKELIST_WORK*	p_work = p_dodata->p_work;


	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}

	if( p_dodata->seq == 0 ){		//　初期化
		p_glb->fade_sort_data = FALSE;
		p_dodata->seq = 1;
	}else{		// メイン

		// メインリスト動作
		PokeListMoveMain( p_glb, p_work, p_dodata->heap );
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
static int ZknPokeListProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	// 内部ワーク破棄
	sys_FreeMemoryEz( p_dodata->p_work );
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
static int ZknPokeListProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_dataglb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	BOOL check;

	// データファイル読み込み処理　フェード処理
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_DRAWINIT_SEQ_GRA_LOAD:
		// 内部ワーク作成
		p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_POKELIST_GRAWORK) );
		GF_ASSERT(p_work);
		p_drawdata->p_work = p_work;
		PokeListDrawWorkInit( p_work, cp_dataglb );

		// ポケモングラフィックセットアップ
		PokeGraphicSetUp( p_work, p_drawglb->p_drawglb, cp_dataglb );

		
		p_drawdata->seq++;
		break;

	case  ZKN_POKELIST_DRAWINIT_SEQ_FADEIN:
		// ポケモンのグラフィックが転送されるのをまつ
		// グラフィックデータ読み込み
		if( cp_dataglb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
			// 通常
			PokeListLoadGraphicFile( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );
		}else{
			// ｿｰﾄﾓｰﾄﾞ
			PokeListLoadGraphicFileSortMode( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );
		}

		// 図鑑用フェードか通常フェードかチェック
		if( cp_dataglb->fade_zukan_data ){

			ZknPokeListChZukanFadeReq( p_work, p_drawglb, cp_dataglb, TRUE );
		}else{
			ZknPokeListDefaultFadeReq( p_work, p_drawglb, cp_dataglb, TRUE );
		}

		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_DRAWINIT_SEQ_FADEIN_WAIT:
	
		// 図鑑用フェードか通常フェードかチェック
		if( cp_dataglb->fade_zukan_data ){
			check = ZknPokeListChZukanFadeEndCheck( p_work, p_drawglb, cp_dataglb, TRUE );
		}else{
			check = ZknPokeListDefaultFadeEndCheck( p_work, p_drawglb, cp_dataglb, TRUE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_POKELIST_DRAWINIT_SEQ_END:
		// α値の設定
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BG3, 0, 16 );
		return ZKN_PROC_TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT(0);
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
static int ZknPokeListProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_glb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	int tbl_no;

	// 描画更新ONOFF
	if( cp_glb->move_draw == FALSE ){
		return ZKN_PROC_FALSE;
	}

	// 現在表示中の選択ポケモンナンバーを更新
	tbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	if( p_work->draw_poke_name != tbl_no ){
		// センター表示テーブルナンバー設定
		p_work->draw_poke_name = tbl_no;

		// リスト変更処理
		// ポケモンリストテーブルの先頭を変更する処理
		// リストの表示非表示も管理
		PokeListPokeTblListStartNumChenge( p_work, cp_glb );
	
		// ポケモン名キャラクタデータ変更処理
		PokeListPokeNameMoveNameChange( p_work, p_drawglb->p_drawglb, cp_glb, p_drawdata->heap );

		// ポケモングラフィックの変更処理
		PokeGraphicSetUp( p_work, p_drawglb->p_drawglb, cp_glb );
	}
	
	// リスト描画座標設定
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );
	PokeListPokeNameMove( p_work, p_drawglb->p_drawglb, cp_glb, p_drawdata->heap );
	PokeListPokeGraMove( p_work, p_drawglb->p_drawglb, cp_glb );
	PokeListDummyPokeGraMove( cp_glb );

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
static int ZknPokeListProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	ZKN_POKELIST_GLB_DRAW* p_drawglb = p_glbdraw;
	const ZKN_POKELIST_GLB_DATA* cp_dataglb = cp_glbdata;
	const ZKN_POKELIST_WORK*	cp_datawork = cp_dodata->p_work;
	ZKN_POKELIST_GRAWORK*		p_work = p_drawdata->p_work;
	BOOL check;

	// データファイル読み込み処理　フェード処理
	switch( p_drawdata->seq ){
	case ZKN_POKELIST_DRAWEND_SEQ_FADEOUT:
		G2_BlendNone();

		// 図鑑用フェードか通常フェードかチェック
		if( cp_dataglb->fade_zukan_data ){
			// グローバルエリアにポケモンリスト作成
			PokeListSelectPokeDataGlbSet( p_work, p_drawglb->p_drawglb, cp_dataglb, p_drawdata->heap );

			// ポケモングラフィックα値リセット
			PokeListPokeGraAlphaInit( p_drawglb->p_drawglb, cp_dataglb );

			ZknPokeListChZukanFadeReq( p_work, p_drawglb, cp_dataglb, FALSE );
		}else{
			ZknPokeListDefaultFadeReq( p_work, p_drawglb, cp_dataglb, FALSE );
		}
		p_drawdata->seq++;
		break;
		
	case ZKN_POKELIST_DRAWEND_SEQ_FADEOUT_WAIT:
		// 図鑑用フェードか通常フェードかチェック
		if( cp_dataglb->fade_zukan_data ){
			check = ZknPokeListChZukanFadeEndCheck( p_work, p_drawglb, cp_dataglb, FALSE );
		}else{
			check = ZknPokeListDefaultFadeEndCheck( p_work, p_drawglb, cp_dataglb, FALSE );
		}
		if( check ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_POKELIST_DRAWEND_SEQ_GRA_RELEASE:
		PokeListReleaseGraphicFile( p_work, p_drawglb->p_drawglb );

		// 廃部ワーク破棄
		sys_FreeMemoryEz( p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_POKELIST_DRAWEND_SEQ_END:
		return ZKN_PROC_TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト動作初期化
 *
 *	@param	p_glb	グローバルデータ
 *	@param	p_work	内部ワーク
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	p_glb->move_way					= ZKN_POKE_LIST_NO_MOVE;
	p_work->move_way				= ZKN_POKE_LIST_NO_MOVE;
	p_work->move_count_add_num		= ZKN_POKE_LIST_MOVE_COUNT_S;
	p_work->move_speed_chg_timing	= ZKN_POKE_LIST_MOVE_CHENGE_TIMING;
	p_work->move_speed_chg_num		= ZKN_POKE_LIST_MOVE_CHENGE_NUM;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スキップ動作初期化
 *
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListSkipMoveInit( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	p_work->move_count_add_num		= ZKN_POKELIST_MOVE_END_COUNT;
	p_work->move_speed_chg_timing	= 0;
	p_work->move_speed_chg_num		= 0;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストメイン動作
 *
 *	@param	p_glb	グローバルデータ
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListMoveMain( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap )
{
	// 分岐処理
	if( PokeListMoveIf( p_glb, p_work, heap ) == TRUE ){
		return ;	// 画面切り替え処理が行われたので、そのまま抜ける
		// これをはずして、下のMoveIfFlagResetを実行すると
		// pokelist_subのリスト先頭、最終ジャンプが実行できるようになっちゃいます
	}

	// 分岐フラグの初期化
	PokeListMoveIfFlagReset( p_glb );


	// 動作停止していたら
	if( p_work->move_way == ZKN_POKE_LIST_NO_MOVE ){

		// スキップ処理
		if( p_work->skip_flag == TRUE ){

			// スキップ動作
			PokeListSkipMove( p_work, p_glb );
		}else{

			// スキップ中でないときの処理
			PokeListKeyMove( p_work, p_glb );
		}
	}


	// 動作
	if( p_glb->sub_wheel_lock != ZKN_POKELIST_WHEEL_LOCK_NONE ){
		PokeListMoveUp( p_glb, p_work );
	}

	// タッチパネルと分岐タイミングが同じになるように
	// この位置で分岐キー操作
	PokeListMoveIfKey( p_glb );
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	分岐フラグリセット
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListMoveIfFlagReset( ZKN_POKELIST_GLB_DATA* p_glb )
{
	p_glb->zukan_sort_end = FALSE;			// SORTモード終了
	p_glb->zukan_end = FALSE;				// 図鑑終了
	p_glb->zukan_see = FALSE;				// 図鑑データを見る
	p_glb->zukan_chg = FALSE;				// 図鑑モード変更
	p_glb->sort_chg = FALSE;				// SORT画面へ変更
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布キー操作
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListMoveIfKey( ZKN_POKELIST_GLB_DATA* p_glb )
{
	if( sys.trg & PAD_BUTTON_B ){
		if(  p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
			p_glb->zukan_end = TRUE;
		}else{
			p_glb->zukan_sort_end = TRUE;
		}
		return ;
	}

	if( sys.trg & PAD_BUTTON_A ){
		p_glb->zukan_see = TRUE;
		return ;
	}

//	if( sys.trg & PAD_BUTTON_START ){
	if( sys.trg & PAD_BUTTON_X ){
		p_glb->sort_chg = TRUE;
		return ;
	}

	if( sys.trg & PAD_BUTTON_SELECT ){
		p_glb->zukan_chg = TRUE;
		return ;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	分岐処理
 *
 *	@param	p_glb
 *	@param	p_work
 *	@param	heap 
 *
 *	@retval	TRUE	処理があった
 *	@retval	FALSE	処理がなかった
 */
//-----------------------------------------------------------------------------
static BOOL PokeListMoveIf( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int heap )
{
	// 図鑑破棄イベントへ
	if( p_glb->zukan_end ){

		PokeListZukanDel( p_glb );
		
		// キャンセル音
		Snd_SePlay( ZKN_SND_CANCEL );
		return TRUE;
	}

	// SORTモードリセット
	if( p_glb->zukan_sort_end ){

		PokeListZukanReset( p_glb, heap );
		// キャンセル音
		Snd_SePlay( ZKN_SND_CANCEL );
		return TRUE;
	}

	// 図鑑画面へ
	if( p_glb->zukan_see ){
		int draw_tbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( p_glb->p_glb );
		// いけるかチェック
		if( ZKN_GLBDATA_PokeListDrawTblDataGet( p_glb->p_glb, draw_tbl_no ) != POKEMON_LIST_DRAWTBL_DUMMY ){
			
			PokeListZukanChg( p_work, p_glb );

			// 選択音
			Snd_SePlay( ZKN_SND_SELECT );
			return TRUE;
		}

	}//*/

	// SORT画面へ
	if( p_glb->sort_chg ){
		return PokeListSortChg( p_glb );
	}

	// 図鑑を切り替える
	if( p_glb->zukan_chg ){
		return PokeListZukanModeChg( p_glb, heap );
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スピードアップ制御
 *
 *	@param	p_glb		グローバルデータ
 *	@param	p_work		内部ワーク
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveUp( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work )
{
	// 動いていないなら抜ける
	if( p_work->move_way == ZKN_POKE_LIST_NO_MOVE ){
		return;
	}

	// 動作シンク数変更
	if( (p_glb->move_count - p_work->move_count_add_num) > 0 ){
		// カウント
		p_glb->move_count -= p_work->move_count_add_num;
	}else{
		// カウント終了
		p_glb->move_count = 0;
		p_work->move_way = ZKN_POKE_LIST_NO_MOVE;

		if( p_work->move_speed_chg_num > 0 ){
			// カウントアップスピードを変更するかチェック
			if( (p_work->move_speed_chg_timing - 1) > 0 ){
				p_work->move_speed_chg_timing--;
			}else{
				p_work->move_count_add_num *= ZKN_POKE_LIST_MOVE_COUNT_MUL;
				p_work->move_speed_chg_num --;

				// 変更するたびにスピードアップ間隔を大きくする
				p_work->move_speed_chg_timing = ZKN_POKE_LIST_MOVE_CHENGE_TIMING * (ZKN_POKE_LIST_MOVE_CHENGE_NUM - p_work->move_speed_chg_num);
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	動作開始リクエストを出す
 *
 *	@param	p_glb	グローバルデータ
 *	@param	p_work	内部ワーク
 *	@param	way		動作方向
 *	
 *	@return	none
 *
	ZKN_POKE_LIST_UP,			// 上に移動
	ZKN_POKE_LIST_DOWN,			// 下に移動
 *
 */
//-----------------------------------------------------------------------------
static void PokeListMoveReq( ZKN_POKELIST_GLB_DATA* p_glb, ZKN_POKELIST_WORK* p_work, int way )
{
	p_glb->move_count			= ZKN_POKELIST_MOVE_END_COUNT;
	p_work->move_way			= way;
	p_glb->move_way				= way;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	指定ポケモンをポケモン引数分進める
 *
 *	@param	p_glb	グローバルデータ
 *	@param	num		進める値
 *
 *	@retval	TRUE	更新された
 *	@retval	FALSE	値は変わらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL PokeListMoveAdd( ZKN_POKELIST_GLB_DATA* p_glb, int num )
{
	return ZKN_GLBDATA_PokeListDrawTblNoAdd( p_glb->p_glb, num );
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画ファイル読み込み＆生成
 *
 *	@param	p_work			データ格納ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	heap			使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListLoadGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	// BG面
	// パレットデータ転送
	ZKN_GLBDATA_PalSet( p_drawglb, NARC_zukan_zkn_list_NCLR, PALTYPE_MAIN_BG, 0, 0, heap );

	// 背景面設定
	PokeListBackGroundSetUp( p_drawglb, heap );

	// ユーティリティ面
	PokeListUtilSetUp( p_work, p_drawglb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	// 文字列面
	PokeListFontSetUp( p_drawglb, heap, 
			ZKN_GLBDATA_PokeSeeNumGet( cp_glb->p_glb ),
			ZKN_GLBDATA_PokeGetNumGet( cp_glb->p_glb ) );


	// セルデータ読み込み
	// リソースマネージャ初期化
	PokeListResManagerMake( p_work, heap );

	// リソース読み込み
	PokeListClActResLoad( p_work, p_drawglb, heap );

	// アクター登録
	PokeListClActAdd( p_work, p_drawglb, heap );

	// 文字列OAM登録
	// ポケモンテーブルを転送する領域のキャラクタサイズを求める
	p_work->poke_name_char_size = PokeListPokeNameCharTransSizeGet( p_drawglb, heap );

	// 領域作成
	PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );


	// アクター座標のセットアップ
	PokeListPokeTblInit( p_work, cp_glb );
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorInit( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );

	// 文字列動作
	PokeListPokeNameMove(p_work, p_drawglb, cp_glb, heap);

	// ポケモンのα値セットアップ
	PokeListPokeGraMove( p_work, p_drawglb, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	読み込みデータ破棄処理
 *
 *	@param	p_work			ワークデータ
 *	@param	p_drawglb		描画グローバルデータ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListReleaseGraphicFile( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb )
{
	// セルデータ
	// 全セルアクターの破棄
	PokeListClActDelete( p_work );	
	
	// リソースマネージャのはき
	PokeListResManagerDelete( p_work );

	// 文字列OAM破棄
	PokeListPokeNameDelete( p_work );

	// ユーティリティ面データ破棄
	PokeListUtilDelete( p_work );

}

//----------------------------------------------------------------------------
/**
 *	@brief	リソースの読み込みｿｰﾄモード
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルﾃﾞｰﾀ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListLoadGraphicFileSortMode( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	void* p_palBuff;
	NNSG2dPaletteData* p_palData;
	u8* p_pal_data;
	
	// BG面
	// カラーパレットを転送
	ZKN_GLBDATA_PalSet( p_drawglb, NARC_zukan_zkn_sort1_NCLR, PALTYPE_MAIN_BG, 0, 32, heap );
	// パレットデータ転送
	p_palBuff = ZKN_GLBDATA_PalDataGet( p_drawglb, NARC_zukan_zkn_list_NCLR, &p_palData, heap );

	// 計算しやすいのでu8*にキャスト
	p_pal_data = (u8*)p_palData->pRawData;
	DC_FlushRange( p_pal_data, 16*32 );
	GX_LoadBGPltt( p_pal_data + 32, 32, 15*32 );
	sys_FreeMemoryEz( p_palBuff );

	// 背景面設定
	PokeListBackGroundSetUp( p_drawglb, heap );

	// ユーティリティ面
	PokeListUtilSetUp( p_work, p_drawglb, heap, ZKN_GLBDATA_PokeZknModeGet( cp_glb->p_glb ) );

	// セルデータ読み込み
	// リソースマネージャ初期化
	PokeListResManagerMake( p_work, heap );

	// リソース読み込み
	PokeListClActResLoad( p_work, p_drawglb, heap );

	// アクター登録
	PokeListClActAdd( p_work, p_drawglb, heap );

	// 文字列OAM登録
	// ポケモンテーブルを転送する領域のキャラクタサイズを求める
	p_work->poke_name_char_size = PokeListPokeNameCharTransSizeGet( p_drawglb, heap );

	// 領域作成
	PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );

	// 文字列面
	PokeListSortVerFontSetUp( p_drawglb, heap, 
			ZKN_GLBDATA_PokeSeeNumGet( cp_glb->p_glb ) );


	// アクター座標のセットアップ
	PokeListPokeTblInit( p_work, cp_glb );
	PokeListPokeTblMove( p_work, cp_glb );
	PokeListIconMove( p_work, cp_glb );
	PokeListCursorInit( p_work, cp_glb );
	PokeListCursorMove( p_work, cp_glb );

	// 文字列動作
	PokeListPokeNameMove(p_work, p_drawglb, cp_glb, heap);

	// ポケモンのα値セットアップ
	PokeListPokeGraMove( p_work, p_drawglb, cp_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面のセットアップ
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListBackGroundSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, NARC_zukan_zkn_list_bg_main1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_bg, ZKN_BG_FRM_BACK_M,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// ポケモンの表示枠を背景に貼り付け	
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, NARC_zukan_zkn_list_bg_main1a_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_bg, ZKN_BG_FRM_BACK_M, p_scrn->rawData,
			ZKN_POKELIST_BACK_POKEFRAME_CX, ZKN_POKELIST_BACK_POKEFRAME_CY,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );
	
	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_BACK_M );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストの図鑑名表示面設定
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	heap			ヒープ 
 *	@param	zkn_mode		図鑑モード
 *
 *	@return	none
 *
 * zkn_mode
	ZKN_MODE_SHINOH,	// シンオウ図鑑
	ZKN_MODE_ZENKOKU,	// 全国図鑑
 *
 */
//-----------------------------------------------------------------------------
static void PokeListUtilSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int zkn_mode )
{
	int dataidx;
	
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb, NARC_zukan_zkn_list_main_lzh_NCGR, p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M, 0, 0, TRUE, heap );

	// 全国とシンオウでデータidxを変更
	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		dataidx = NARC_zukan_zkn_list_bg_zen_lzh_NSCR;
	}else{
		dataidx = NARC_zukan_zkn_list_bg_sin_lzh_NSCR;
	}
	
	// スクリーンデータ読み込み
	p_work->p_util_scrn_buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb, dataidx, TRUE, &p_work->p_util_scrn, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ユーティリティ面データ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListUtilDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_util_scrn_buff );
	p_work->p_util_scrn_buff = NULL;
	p_work->p_util_scrn = NULL;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケリストフォント面設定
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープID
 *	@param	see_num		発見数
 *	@param	get_num		捕獲数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int see_num, int get_num )
{
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// みつけたかずという文字列
	MSGMAN_GetString( man, ZNK_POKELIST_00, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// つかまえたかずという文字列
	MSGMAN_GetString( man, ZNK_POKELIST_01, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_GET_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 発見数
	STRBUF_SetNumber( str, see_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_NUM_X, ZKN_POKELIST_SEE_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	// 捕獲数
	STRBUF_SetNumber( str, get_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_GET_NUM_X, ZKN_POKELIST_GET_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄの時はリスト数のみ出す
 *
 *	@param	p_drawglb		グローバルﾃﾞｰﾀ
 *	@param	heap			ヒープ
 *	@param	list_num		表示リスト数 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListSortVerFontSetUp( ZKN_GLB_DRAWDATA* p_drawglb, int heap, int list_num )
{
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);

	// みつけたかずという文字列
	MSGMAN_GetString( man, ZNK_SORT_NUM, str );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_STR_X, ZKN_POKELIST_STR_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );
	
	// 発見数
	STRBUF_SetNumber( str, list_num, ZKN_POKELIST_PLACE, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( &p_drawglb->bmp_mfont, FONT_SYSTEM, str, ZKN_POKELIST_SEE_NUM_X, ZKN_POKELIST_SEE_NUM_Y, 0, ZKN_BG_FONT_COLOR_MSK, NULL );

	STRBUF_Delete(str);

	MSGMAN_Delete(man);

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト用リソースマネージャの作成
 *
 *	@param	p_work	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListResManagerMake( ZKN_POKELIST_GRAWORK* p_work, int heap )
{
	// セルアクター用リソース管理システム
	p_work->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CG_NUM, CLACT_U_CHAR_RES, heap );
	p_work->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CL_NUM, CLACT_U_PLTT_RES, heap );
	p_work->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_CE_NUM, CLACT_U_CELL_RES, heap );
	p_work->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( ZKN_POKELIST_CELL_AN_NUM, CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト用リソースマネージャ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListResManagerDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	CLACT_U_RES_OBJ_PTR res_obj;
	// パレットとキャラクタの管理領域を破棄
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_CHAR_RES ], NARC_zukan_zkn_list_oam_main_lzh_NCGR );
	CLACT_U_CharManagerDelete( res_obj );
	
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR );
	CLACT_U_PlttManagerDelete( res_obj );


	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_work->res_manager[ CLACT_U_CHAR_RES ], NARC_zukan_zkn_hatena_oam_lzh_NCGR );
	CLACT_U_CharManagerDelete( res_obj );
	

	
	// セルアクター用リソース管理システム
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_work->res_manager[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター用リソース読み込み
 *
 *	@param	p_work	ワーク
 *	@param	heap	ヒープ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActResLoad( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	CLACT_U_RES_OBJ_PTR res_obj;
	ARCHANDLE* p_handle =ZKN_GLBDATA_ArcHandlGet( p_drawglb ); 
	
	// キャラクタデータ読み込み
	res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_work->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( res_obj );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( res_obj );

	// パレットデータ読み込み
	res_obj = CLACT_U_ResManagerResAddArcPltt_ArcHandle( p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_handle, NARC_zukan_zkn_list_oam_NCLR,
			FALSE, NARC_zukan_zkn_list_oam_NCLR, NNS_G2D_VRAM_TYPE_2DMAIN, 
			ZKN_POKELIST_TBL_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( res_obj );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( res_obj );



	// セルデータ読み込み
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NCER,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NCER,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_list_oam_main_lzh_NANR,
			TRUE, NARC_zukan_zkn_list_oam_main_lzh_NANR,
			CLACT_U_CELLANM_RES, heap );

	// セルアクターヘッダー作成
	CLACT_U_MakeHeader( &p_work->clheader,
			NARC_zukan_zkn_list_oam_main_lzh_NCGR,
			NARC_zukan_zkn_list_oam_NCLR,
			NARC_zukan_zkn_list_oam_main_lzh_NCER,
			NARC_zukan_zkn_list_oam_main_lzh_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, ZKN_POKELIST_OAM_BG_PRI,
			p_work->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );


	// キャラクタデータ読み込み
	res_obj = CLACT_U_ResManagerResAddArcChar_ArcHandle( p_work->res_manager[ CLACT_U_CHAR_RES ], 
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( res_obj );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( res_obj );

	// セルデータ読み込み
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NCER,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NCER,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			p_handle, NARC_zukan_zkn_hatena_oam_lzh_NANR,
			TRUE, NARC_zukan_zkn_hatena_oam_lzh_NANR,
			CLACT_U_CELLANM_RES, heap );

	// セルアクターヘッダー作成
	CLACT_U_MakeHeader( &p_work->clheader_dummy_poke,
			NARC_zukan_zkn_hatena_oam_lzh_NCGR,
			NARC_zukan_zkn_list_oam_NCLR,
			NARC_zukan_zkn_hatena_oam_lzh_NCER,
			NARC_zukan_zkn_hatena_oam_lzh_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE,
			0, ZKN_POKELIST_OAM_BG_PRI,
			p_work->res_manager[ CLACT_U_CHAR_RES ],
			p_work->res_manager[ CLACT_U_PLTT_RES ],
			p_work->res_manager[ CLACT_U_CELL_RES ],
			p_work->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター登録
 *
 *	@param	p_work		ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActAdd( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	CLACT_ADD_SIMPLE	add;
	int i;

	// 登録データテンプレート作成
	memset( &add, 0, sizeof(CLACT_ADD_SIMPLE) );
	add.ClActSet		= p_drawglb->clact_set;
	add.ClActHeader		= &p_work->clheader;
	add.DrawArea		= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap			= heap;

	
	// リストオブジェクト
	add.pri		= ZKN_POKELIST_POKETBL_PRI;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		p_work->poke_tbl[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_work->poke_tbl[ i ], ZKN_POKELIST_POKETBL_ANMSEQ );
	}
	
	// アイコン
	add.pri		= ZKN_POKELIST_ICON_PRI;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		p_work->icon[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_work->icon[ i ], ZKN_POKELIST_ICON_ANMSEQ );
	}

	// カーソル
	add.pri			= ZKN_POKELIST_CURSOR_PRI;
	p_work->cursor	= CLACT_AddSimple( &add );
	CLACT_AnmChg( p_work->cursor, ZKN_POKELIST_CURSOR_ANMSEQ );

	// ダミーポケモン
	add.pri			= 0;
	add.mat.x		= ZKN_POKELIST_POKEGRA_X << FX32_SHIFT;
	add.mat.y		= ZKN_POKELIST_POKEGRA_Y << FX32_SHIFT;
	add.ClActHeader		= &p_work->clheader_dummy_poke;
	p_work->dummy_poke = CLACT_AddSimple( &add );
	CLACT_SetDrawFlag( p_work->dummy_poke, FALSE );
	CLACT_ObjModeSet( p_work->dummy_poke, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン名前テーブル作成
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int i;	// ループ用
	int pokelist_s;	// ポケモンリストの表示要素の開始番号
	int poketbl_s;	// ポケモンテーブルの表示要素の開始番号
	int pokelist_tbl_num;	// ポケモンリストテーブル数
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	const ZKN_POKELIST_DATA* p_poke_data;	// ポケモンデータ
	int poke_listdraw_link_list_idx;

	// 共通データ代入
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;


	// ポケモン名テーブルをZKN_POKELIST_POKETBL_NUM分作成
	pokelist_s = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb ) - ZKN_POKELIST_POKETBL_CHECK;
	poketbl_s = p_work->poke_tbl_start;
	pokelist_tbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		// 破棄
		if( p_work->poke_name[ poketbl_s ] ){
			ZKN_FONTOAM_Delete( p_work->poke_name[ poketbl_s ] );
			p_work->poke_name[ poketbl_s ] = NULL;
		}
		
		// 値が有効かチェック
		if( (pokelist_s >= 0) && (pokelist_s < pokelist_tbl_num) ){
			
			// ポケモンリスト描画配列idxからポケモンリストデータ配列idxを取得
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, pokelist_s );
			// ダミーでなければポケモン名書き込み
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){

				p_poke_data = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, poke_listdraw_link_list_idx );

#if 0
				// 文字列書き込み領域作成
				p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );


				// ビットマップ領域に書き込み
				ZKN_UTIL_PokeListPokeNameBmpMake( p_bmp, p_poke_data->mons_no, heap );
#endif
				// ビットマップ領域に書き込み
				p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb->p_glb, heap, p_poke_data->mons_no );

				
				// FONTOAM登録
				fontoam_init.p_bmp = p_bmp;
				p_work->poke_name[ poketbl_s ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

				// BMP領域破棄
				ZKN_FONTOAM_DeleteBmp( p_bmp );
			}else{

				// ダミーの名前設定
				PokeListPokeNameDummySet( p_work, p_drawglb, heap, poketbl_s, pokelist_s + 1 );
			}
		}else{

			p_work->poke_name[ poketbl_s ] = NULL;
		}

		poketbl_s = (poketbl_s + 1) % ZKN_POKELIST_POKETBL_NUM;
		pokelist_s ++;
	}

}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックファイル設定
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	cp_glb		グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeGraphicSetUp( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int pokelist_no;
	int drawpokelist_no;
	const ZKN_POKELIST_DATA* cp_pokedata;

	drawpokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );

	pokelist_no = ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb );
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb , pokelist_no );

	// 表示するかチェック
	if( ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, drawpokelist_no ) == POKEMON_LIST_DRAWTBL_DUMMY ){
		// 描画OFF
		ZKN_GlbPokemonGraphicDrawFlagSet( p_drawglb,FALSE ); 
	
		// ダミー描画ON
		if( p_work->dummy_poke ){
			CLACT_SetDrawFlag( p_work->dummy_poke, TRUE );
		}
	}else{

		// ポケモングラフィックデータ設定
		ZKN_UTIL_PokemonGraphicSet( p_drawglb, cp_glb->p_glb, cp_pokedata->mons_no,
				PARA_FRONT, ZKN_POKELIST_POKEGRA_X, ZKN_POKELIST_POKEGRA_Y );

		// 描画ON
		ZKN_GlbPokemonGraphicDrawFlagSet( p_drawglb,TRUE ); 

		// ダミー描画OFF
		if( p_work->dummy_poke ){
			CLACT_SetDrawFlag( p_work->dummy_poke, FALSE );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン名前テーブル破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;

	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		if( p_work->poke_name[ i ] ){
			ZKN_FONTOAM_Delete( p_work->poke_name[ i ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアクター破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListClActDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;

	// ポケモンテーブル
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_Delete( p_work->poke_tbl[ i ] );
	}

	// アイコン
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_Delete( p_work->icon[ i ] );
	}

	// カーソル
	CLACT_Delete( p_work->cursor );

	//　ダミーぽけもん 
	CLACT_Delete( p_work->dummy_poke );
}

// CLACT_OBJパラメータ計算＆設定関数郡
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケリストテーブル動作前初期化
 *
 *	@param	p_work	描画ワーク
 *	@param	cp_glb	グローバルデータ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	p_work->poke_tbl_start = 0;

	// 表示非表示設定
	PokeListPokeTblDrawFlagSetUp( p_work, cp_glb );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン名前テーブル動作
 *
 *	@param	p_work	描画ワーク
 *	@param	cp_glb	グローバルデータ
 *
 *	@return none;
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int tbl_count;
	VecFx32 mat;
	int i;
	int tbl_s, tbl_e;
	int center_dis;		// 中央からの距離
	int pri;			// 表示プライオリティ
	int col;			// カラーパレット

	// move_countにより座標を設定
	tbl_count = p_work->poke_tbl_start;
	// 先頭から座標を設定する
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		// 開始テーブルと終了テーブルナンバーを動いている方向によって変化させる
		if( cp_glb->move_way == ZKN_POKE_LIST_UP ){
			tbl_s = i + 2;		// ひとつしたから自分の座標へ
			tbl_e = i + 1;
		}else{
			tbl_s = i;			// ひとつうえから自分の座標へ
			tbl_e = i + 1;
		}
		
		mat.x = PokeListPokeTblMoveCalc( ZknPokeListPokeTblMoveX[ tbl_s ], ZknPokeListPokeTblMoveX[ tbl_e ], ZKN_POKELIST_MOVE_END_COUNT, ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count );	// X座標計算
		mat.y = PokeListPokeTblMoveCalc( ZknPokeListPokeTblMoveY[ tbl_s ], ZknPokeListPokeTblMoveY[ tbl_e ], ZKN_POKELIST_MOVE_END_COUNT, ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count );	// Y座標計算

		
		// 座標設定
		CLACT_SetMatrix( p_work->poke_tbl[ tbl_count ], &mat );

		// 中心からの距離を求める
		center_dis = ZKN_POKELIST_POKETBL_CHECK - i;
		if( center_dis < 0 ){
			center_dis = -center_dis;
		}
		
		// 表示優先順位計算
		pri = center_dis * 2;
		if( pri < 0 ){
			pri = -pri;
		}
		pri += ZKN_POKELIST_POKETBL_PRI;
		CLACT_DrawPriorityChg( p_work->poke_tbl[ tbl_count ], pri );

		// カラーパレット
		// 中央がそれ以外でカラーパレット変更
		if( i == ZKN_POKELIST_POKETBL_CHECK ){
			CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_SELECT );
		}else{
			if( ZKN_POKELIST_PLTT_OTHER0 + (center_dis - 1) < ZKN_POKELIST_PLTT_OTHER2 ){
				CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_OTHER0 + (center_dis - 1) );
			}else{
				CLACT_PaletteOffsetChgAddTransPlttNo( p_work->poke_tbl[ tbl_count ], ZKN_POKELIST_PLTT_OTHER2 );
			}
		}
		
		// 次の配列へ
		tbl_count = (tbl_count + 1) % ZKN_POKELIST_POKETBL_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストテーブル開始ナンバー変更処理
 *
 *	@param	p_work		描画ワーク
 *	@param	cp_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblListStartNumChenge( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int poke_last;
	int pokelist_no;
	int pokelist_num;
	
	pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	// どの方向に動作しているかチェック
	if( cp_glb->move_way == ZKN_POKE_LIST_UP ){
		// 上に移動	
		// 変更
		if( (p_work->poke_tbl_start + 1) < ZKN_POKELIST_POKETBL_NUM ){
			p_work->poke_tbl_start ++;
		}else{
			p_work->poke_tbl_start = 0;
		}

		// 先頭から一番後方に行ったテーブルナンバー取得
		poke_last = p_work->poke_tbl_start + (ZKN_POKELIST_POKETBL_NUM - 1);
		poke_last %= ZKN_POKELIST_POKETBL_NUM;

		// 非表示テーブルチェック
		// 下にZKN_POKELIST_POKETBL_CHECK個ないかチェック
		if( (pokelist_no + ZKN_POKELIST_POKETBL_CHECK) >= pokelist_num ){
			// 一番下のテーブルを非表示にする
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], FALSE );
		}else{
			// 一番下のテーブルを表示にする
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], TRUE );
		}
	}else{
		
		// 下に移動
		if( cp_glb->move_way == ZKN_POKE_LIST_DOWN ){
			if( (p_work->poke_tbl_start - 1) >= 0 ){
				p_work->poke_tbl_start --;
			}else{
				p_work->poke_tbl_start = ZKN_POKELIST_POKETBL_NUM - 1;
			}
		
			// 後方から一番先頭に行ったテーブルナンバー取得
			poke_last = p_work->poke_tbl_start;

			// 上にZKN_POKELIST_POKETBL_CHECK個ないかチェック
			if( (pokelist_no - ZKN_POKELIST_POKETBL_CHECK) < 0 ){
				// 一番上のテーブルを非標示にする
				CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], FALSE );
			}else{
				// 一番上のテーブルを表示にする
				CLACT_SetDrawFlag( p_work->poke_tbl[ poke_last ], TRUE );
			}
		}else{
			// 上でも下でもなく値が変更されていたときは表示のONOFF設定のみ行う
			PokeListPokeTblDrawFlagSetUp( p_work, cp_glb );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アイコンの動作
 *
 *	@param	p_work		描画ワーク
 *	@param	cp_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListIconMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	const VecFx32* cp_mat;
	VecFx32 mat;
	int i;
	int tbl_no;
	BOOL draw_on_off;
	int pokelist_no_work;
	int pokelist_no;
	int pokelist_num;
	const ZKN_POKELIST_DATA* cp_poke_data;
	int pri;
	int pltt_no;
	int poke_listdraw_link_list_idx;

	pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		tbl_no = (p_work->poke_tbl_start + i) % ZKN_POKELIST_POKETBL_NUM;

		// 表示ONOFF設定
		draw_on_off = FALSE;
		pokelist_no_work = ((pokelist_no - ZKN_POKELIST_POKETBL_CHECK) + i);
		// そのポケモンは捕まえたポケモンか見つけたポケモンか
		if( (pokelist_no_work >= 0) && (pokelist_no_work < pokelist_num) ){
			// ポケモンリスト描画配列idxからポケモンリストデータ配列idxを取得
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, pokelist_no_work );
			
			// ダミーデータ出ないかチェック
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){
			
				cp_poke_data = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, poke_listdraw_link_list_idx );

				// 捕まえたポケモンかチェック
				if( cp_poke_data->type == ZKN_POKELIST_TYPE_GET ){
					draw_on_off = TRUE;
				}
			}
			
		}

		// 表示設定
		CLACT_SetDrawFlag( p_work->icon[ tbl_no ], draw_on_off );

		// 表示なら設定		
		if( draw_on_off ){
			
			// ポケモンテーブルのセンターテーブル座標に追従
			cp_mat = CLACT_GetMatrix( p_work->poke_tbl[ tbl_no ] );

			mat.x = cp_mat->x + ZKN_POKELIST_ICON_X_OFS;
			mat.y = cp_mat->y;

			CLACT_SetMatrix( p_work->icon[ tbl_no ], &mat );

			// 親テーブルと同じカラーパレット設定
			pltt_no = CLACT_PaletteOffsetGet( p_work->poke_tbl[ tbl_no ] );
			CLACT_PaletteOffsetChg( p_work->icon[ tbl_no ], pltt_no );

			// 表示優先順位を設定
			pri = CLACT_DrawPriorityGet( p_work->poke_tbl[ tbl_no ] );
			pri--;
			CLACT_DrawPriorityChg( p_work->icon[ tbl_no ], pri );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Cursor動作初期化
 *
 *	@param	p_work		描画ワーク
 *	@param	cp_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListCursorInit( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int pokelist_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );
	
	p_work->onepoke_move_dis = FX_Div( ZKN_POKELIST_CURSOR_YDIS, pokelist_num << FX32_SHIFT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Cursor動作
 *
 *	@param	p_work		描画ワーク
 *	@param	cp_glb		グローバルデータ
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListCursorMove( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	VecFx32	mat;
	int pokelist_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	
	// 全体のポケモンリストでの今の選択ポケモンの位置により座標を求める
	mat.y = FX_Mul( p_work->onepoke_move_dis, pokelist_no  << FX32_SHIFT );
	mat.y += ZKN_POKELIST_CURSOR_YMIN;
	mat.x = ZKN_POKELIST_CURSOR_X;

	CLACT_SetMatrix( p_work->cursor, &mat );
}



//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト座標計算
 *
 *	@param	s				開始座標
 *	@param	e				終点座標
 *	@param	max_count		最大カウント数
 *	@param	count			今のカウント値
 *
 *	@return	座標
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32 PokeListPokeTblMoveCalc( fx32 s, fx32 e, int max_count, int count )
{
	fx32 work;

	work = (e - s);

	work = FX_Mul( work, count << FX32_SHIFT );
	work = FX_Div( work, max_count << FX32_SHIFT );	// 座標

	return work + s;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	内部ワークの初期化
 *
 *	@param	p_work			ワーク
 *	@param	cp_dataglb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListDrawWorkInit( ZKN_POKELIST_GRAWORK*	p_work, const ZKN_POKELIST_GLB_DATA* cp_dataglb )
{
	memset( p_work, 0, sizeof(ZKN_POKELIST_GRAWORK) );
	p_work->draw_poke_name = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_dataglb->p_glb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名前テーブル動作
 *
 *	@param	p_work		ワーク
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *
 *	先にポケモンリストを動かしてください
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int i;
	int x, y;
	VecFx32 mat;
	int poke_tbl_no;
	int pri;
	int col;
	
	// ポケモンリストの各テーブル座標にあわせる
	poke_tbl_no = p_work->poke_tbl_start;
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		if( p_work->poke_name[ poke_tbl_no ] ){
			// 座標取得
			PokeListPokeNameMoveMatGet( p_work->poke_tbl[ poke_tbl_no ], &x, &y );
			// 座標設定
			FONTOAM_SetMat( p_work->poke_name[ poke_tbl_no ]->p_fontoam, 
					x, y );

			// 表示優先順位設定
			pri = CLACT_DrawPriorityGet( p_work->poke_tbl[ poke_tbl_no ] );
			pri--;
			FONTOAM_SetDrawPriority( p_work->poke_name[ poke_tbl_no ]->p_fontoam, pri );

			// カラーパレット
			col = CLACT_PaletteOffsetGet( p_work->poke_tbl[ poke_tbl_no ] );
			FONTOAM_SetPaletteOffset( p_work->poke_name[ poke_tbl_no ]->p_fontoam, col );
		}

		// 次のテーブルへ
		poke_tbl_no = (poke_tbl_no + 1) % ZKN_POKELIST_POKETBL_NUM;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター座標から上に乗るフォントOAMの座標を求める
 *
 *	@param	target_act	ターゲットアクター
 *	@param	x			X座標
 *	@param	y			Y座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMoveMatGet( CLACT_WORK_PTR target_act, int* x, int* y )
{
	const VecFx32* p_mat;

	// 座標取得
	p_mat = CLACT_GetMatrix( target_act );

	*x = p_mat->x >> FX32_SHIFT;
	*y = p_mat->y >> FX32_SHIFT;
	*x -= (ZKN_POKELIST_POKENAME_BMP_SIZE_X / 2);	// 左上座標にする
	*y -= (ZKN_POKELIST_POKENAME_BMP_SIZE_Y / 2);			
}

//----------------------------------------------------------------------------
/**
 *	@brief	名前変更データ変更チェック＆実行処理
 *
 *	@param	p_work			ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバル
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameMoveNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	int pokelisttbl_no;
	int pokelisttbl_num;
	int chg_name_no;	// 変更する名前テーブルナンバー
	int poke_list_no;	// 変更するポケモンリストナンバー
	int poke_listdraw_link_list_idx;

	pokelisttbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelisttbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );

	// どの方向に動作しているかチェック
	switch( cp_glb->move_way ){
	case ZKN_POKE_LIST_UP:
		// 一番したのテーブルのポケモン名を選択されたポケモン + ZKN_POKELIST_POKETBL_CHECKのテーブルポケモンで変更
		chg_name_no = p_work->poke_tbl_start + ZKN_POKELIST_POKETBL_NUM - 1;
		poke_list_no = pokelisttbl_no + ZKN_POKELIST_POKETBL_CHECK;
		break;
		
	case ZKN_POKE_LIST_DOWN:
		// 一番先頭のテーブルのポケモン名を選択されたポケモン - ZKN_POKELIST_POKETBL_CHECKのテーブルポケモンで変更
		chg_name_no = p_work->poke_tbl_start;
		poke_list_no = pokelisttbl_no - ZKN_POKELIST_POKETBL_CHECK;

		break;

	default:
		break;
	}
	
	// 上でも下でも無いときは全部変更(スキップがコールされた)
	if( (cp_glb->move_way == ZKN_POKE_LIST_NO_MOVE) ){
		// 全変更
		PokeListPokeNameSetUp( p_work, p_drawglb, cp_glb, heap );
	}else{
		// １つだけ変更
		chg_name_no %= ZKN_POKELIST_POKETBL_NUM;

		// 範囲内なら変更
		if( (poke_list_no < pokelisttbl_num) &&
			(poke_list_no >= 0) ){
			
			// ポケモンリスト描画配列idxからポケモンリストデータ配列idxを取得
			poke_listdraw_link_list_idx = ZKN_GLBDATA_PokeListDrawTblDataGet( cp_glb->p_glb, poke_list_no );
			
			// ダミーデータでないかチェック
			if( poke_listdraw_link_list_idx != POKEMON_LIST_DRAWTBL_DUMMY ){
			
				PokeListPokeNameChange( p_work, p_drawglb, cp_glb, heap, chg_name_no, poke_listdraw_link_list_idx );
			}else{

				// だみー名前設定
				PokeListPokeNameDummySet( p_work, p_drawglb, heap, chg_name_no, poke_list_no + 1 );
			}
		}else{
			// 範囲外なら破棄
			if( p_work->poke_name[ chg_name_no ] ){
				ZKN_FONTOAM_Delete( p_work->poke_name[ chg_name_no ] );
				p_work->poke_name[ chg_name_no ] = NULL;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン名キャラクタデータ変更
 *
 *	@param	p_work				描画ワーク
 *	@param	p_drawglb			描画グローバルデータ
 *	@param	cp_glb				グローバルデータ
 *	@param	heap				ヒープ
 *	@param	pokename_tbl_no		ポケモン名前テーブルの何番目を変更するのか
 *	@param	pokelist_tbl_no		変更するポケモンのデータテーブルナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeNameChange( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap, int pokename_tbl_no, int pokelist_tbl_no )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	const ZKN_POKELIST_DATA* cp_pokedata;

	//　ポケモンデータ
	cp_pokedata = ZKN_GLBDATA_PokeListTblGet( cp_glb->p_glb, pokelist_tbl_no );
	GF_ASSERT_MSG( cp_pokedata, " %d\n", pokelist_tbl_no );

	// 共通データ代入
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// 文字列書き込み領域作成
	p_bmp = ZKN_UTIL_PokeListPokeNameTblBmpMake( p_drawglb, cp_glb->p_glb, heap, cp_pokedata->mons_no );
	

	// 破棄
	if( p_work->poke_name[ pokename_tbl_no ] ){
		ZKN_FONTOAM_Delete( p_work->poke_name[ pokename_tbl_no ] );
	}
	
	// FONTOAM登録
	fontoam_init.p_bmp = p_bmp;
	p_work->poke_name[ pokename_tbl_no ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーデータ設定
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	heap			ヒープ
 *	@param	pokename_tbl_no	ネームテーブルナンバー
 *	@param	pokenum
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
static void PokeListPokeNameDummySet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, int heap, int pokename_tbl_no, int pokenum )
{
	ZKN_FONTOAM_INIT fontoam_init;
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	STRBUF* str = STRBUF_Create(ZKN_POKELIST_NUM_STR, heap);
	MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_zkn_dat, heap);


	// 共通データ代入
	fontoam_init.zkn_fontoam = p_drawglb->fontoam_sys;
	fontoam_init.pltt		 = p_work->clheader.pPaletteProxy;
	fontoam_init.parent		 = NULL;
	fontoam_init.x			 = 0;
	fontoam_init.y			 = 0;
	fontoam_init.bg_pri		 = ZKN_POKELIST_OAM_BG_PRI;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DMAIN;
	fontoam_init.heap		 = heap;

	// 文字列書き込み領域作成
	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );

	// 数字作成
	STRBUF_SetNumber( str, pokenum, ZKN_POKELIST_POKENAME_NO_KETA,
			NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, str, ZKN_POKELIST_POKENAME_NO_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );

	// なぞポケモン文字 
	MSGMAN_GetString( man, ZNK_UNKNOWN_00, str );
	GF_STR_PrintColor( p_bmp, FONT_BUTTON, str, ZKN_POKELIST_POKENAME_NAME_MAT_X, ZKN_POKELIST_POKENAME_MAT_Y, MSG_NO_PUT, ZKN_FOTNOAM_COLOR, NULL );
	
	// 破棄
	if( p_work->poke_name[ pokename_tbl_no ] ){
		ZKN_FONTOAM_Delete( p_work->poke_name[ pokename_tbl_no ] );
	}
	
	// FONTOAM登録
	fontoam_init.p_bmp = p_bmp;
	p_work->poke_name[ pokename_tbl_no ] = ZKN_FONTOAM_MakeCharOfs( &fontoam_init, p_work->poke_name_char_size );

	// BMP領域破棄
	ZKN_FONTOAM_DeleteBmp( p_bmp );


	STRBUF_Delete(str);

	MSGMAN_Delete(man);

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	テーブルの描画オンオフ設定	一気に全テーブルを設定します。
 *
 *	@param	p_work		描画ワーク
 *	@param	cp_glb		グローバルデータ	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void PokeListPokeTblDrawFlagSetUp( ZKN_POKELIST_GRAWORK* p_work, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	int poke_list_no;
	int poke_tbl_no;
	int i;		// ループ用
	int pokelisttbl_no;
	int pokelisttbl_num;

	pokelisttbl_no = ZKN_GLBDATA_PokeListDrawTblNoGet( cp_glb->p_glb );
	pokelisttbl_num = ZKN_GLBDATA_PokeListDrawTblNumGet( cp_glb->p_glb );

	poke_list_no = pokelisttbl_no - ZKN_POKELIST_POKETBL_CHECK;
	poke_tbl_no = p_work->poke_tbl_start;
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){

		if( (poke_list_no >= 0) &&
			(poke_list_no < pokelisttbl_num) ){
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_tbl_no ], TRUE );
		}else{
			CLACT_SetDrawFlag( p_work->poke_tbl[ poke_tbl_no ], FALSE );
		}

		poke_tbl_no = (poke_tbl_no + 1) % ZKN_POKELIST_POKETBL_NUM;
		poke_list_no++;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック動作
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraMove( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	fx32 calc;
	int alpha;
	SOFT_SPRITE* ssp;
	
	// カウント値からαを変更
	// 0～31に徐々に変わっていく
	calc = FX_Mul( 31 << FX32_SHIFT, (ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count) << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_POKELIST_MOVE_END_COUNT << FX32_SHIFT );
	alpha = calc >> FX32_SHIFT;

	// softsprite
	ssp = ZKN_GlbPokemonGraphicGet( p_drawglb );
	SoftSpriteParaSet( ssp, SS_PARA_ALPHA, alpha );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックのα値リセット
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraAlphaInit( ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	SOFT_SPRITE* ssp;
	
	// softsprite
	ssp = ZKN_GlbPokemonGraphicGet( p_drawglb );
	SoftSpriteParaSet( ssp, SS_PARA_ALPHA, 31 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーポケモングラフィックの動作
 *
 *	@param	cp_glb			グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListDummyPokeGraMove( const ZKN_POKELIST_GLB_DATA* cp_glb )
{
	fx32 calc;
	int alpha;
	
	// カウント値からαを変更
	// 0～16に徐々に変わっていく
	calc = FX_Mul( 16 << FX32_SHIFT, (ZKN_POKELIST_MOVE_END_COUNT - cp_glb->move_count) << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_POKELIST_MOVE_END_COUNT << FX32_SHIFT );
	alpha = calc >> FX32_SHIFT;

	// OAMα
	G2_ChangeBlendAlpha( alpha, 16 - alpha );
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG面フェード初期化
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	fadein_out		フェードインTRUE　アウトFALSEフラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListBgFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	int top_s, top_e;
	int bottom_s, bottom_e;
	int fade_sync;

	
	// シャッター音
	Snd_SePlay( ZKN_SND_SHUTTER );

	// font面マスク
/*	GX_SetVisibleWnd( GX_WNDMASK_W0 );
	G2_SetWnd0InsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );
	G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE );
	G2_SetWnd0Position( 0, 0, 255, 192 );//*/

	
	// フェードデータ初期化データ設定
	if( cp_glb->fade_mode == ZKN_POKELIST_BG_FADE_NORMAL ){
		
		if( fadein_out ){
			top_s = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E;
			fade_sync = ZKN_POKELIST_FADEIN_SYNC;

			// 文字面の表示オフセット設定
			GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, 192 );

		}else{
			top_s = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_E;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_E;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE00_TOP_S;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE00_BOTTOM_S;
			fade_sync = ZKN_POKELIST_FADEOUT_SYNC;
		}
		
	}else{
		
		if( fadein_out ){
			top_s = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E;
			fade_sync = ZKN_POKELIST_FADEIN_SYNC;
		}else{
			top_s = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_E;
			bottom_s = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_E;
			top_e = ZKN_POKELIST_BGSHUTTER_FADE01_TOP_S;
			bottom_e = ZKN_POKELIST_BGSHUTTER_FADE01_BOTTOM_S;
			fade_sync = ZKN_POKELIST_FADEOUT_SYNC;
		}
	}


	// フェードデータ初期化
	ZKN_UTIL_BgShutterFadeInit( &p_work->bg_fade,
			p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_UTIL_M,
			p_work->p_util_scrn, 
			top_s, top_e, bottom_s, bottom_e,
			fade_sync );

}

//----------------------------------------------------------------------------
/**
 *	@brief	BGフェード関数
 *
 *	@param	p_work 
 *	@param	p_drawglb
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL PokeListBgFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	int bottom_w_size;
	
	check = ZKN_UTIL_BgShutterFade( &p_work->bg_fade );

	// 文字列面スクロール
	if( check == FALSE ){
		bottom_w_size = (p_work->bg_fade.bottom_dis * (p_work->bg_fade.move_count - 1)) / p_work->bg_fade.move_count_max;
		bottom_w_size += p_work->bg_fade.bottom_start;
		bottom_w_size = bottom_w_size;			// 下からのキャラクタサイズ
		bottom_w_size *= 8;						// 下からのピクセルサイズ
		bottom_w_size = bottom_w_size - ZKN_POKELIST_SCR_START_DOWN_YSIZ; // 文字の表示位置

		// ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMITより大きい値にさせない
		if( bottom_w_size < ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT ){
			bottom_w_size = ZKN_POKELIST_BGSHUTTER_FADE_FONTBG_LIMIT;
		}
		
		// これがBGの移動値になる
		GF_BGL_ScrollReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, bottom_w_size );

	}

	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	SHUTTERフェード後処理
 *
 *	@param	p_drawglb		描画グローバルデータ
 *	@param	cp_glb			グローバルデータ
 *	@param	fadein_out		フェードインTRUE　アウトFALSE
 *	@param	set_blend_msk	設定ブライトネスマスク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListBgFadeDel( ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	if( cp_glb->fade_mode == ZKN_POKELIST_BG_FADE_NORMAL ){
		
		if( fadein_out == FALSE ){
			
			// 全部の面にブライトネスをかけ、スクロール座標をリセット
			GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M, GF_BGL_SCROLL_Y_SET, 0 );
		}
	}

	GX_SetVisibleWnd( GX_WNDMASK_NONE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストのポケモン名を書く転送サイズを求める
 *
 *	@param	p_drawglb	描画グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	転送サイズ
 */
//-----------------------------------------------------------------------------
static int PokeListPokeNameCharTransSizeGet( ZKN_GLB_DRAWDATA* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* p_bmp;	// 書き込み領域
	int char_size;

	p_bmp = ZKN_FONTOAM_GetBmp( p_drawglb->fontoam_sys, ZKN_POKELIST_POKENAME_BMP_SIZE_CX, ZKN_POKELIST_POKENAME_BMP_SIZE_CY );
	char_size = FONTOAM_NeedCharSize( p_bmp, NNS_G2D_VRAM_TYPE_2DMAIN, heap ); 
	ZKN_FONTOAM_DeleteBmp( p_bmp );

	return char_size;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード初期化
 *
 *	@param	p_work	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListOamFadeInit( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;


	CLACT_ObjModeSet( p_work->cursor, GX_OAM_MODE_XLU );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_ObjModeSet( p_work->poke_tbl[ i ], GX_OAM_MODE_XLU );
		CLACT_ObjModeSet( p_work->icon[ i ], GX_OAM_MODE_XLU );
		if(p_work->poke_name[ i ]){
			FONTOAM_ObjModeSet( p_work->poke_name[ i ]->p_fontoam, GX_OAM_MODE_XLU );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのフェード処理破棄
 *
 *	@param	p_work	描画ワーク
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListOamFadeDelete( ZKN_POKELIST_GRAWORK* p_work )
{
	int i;


	CLACT_ObjModeSet( p_work->cursor, GX_OAM_MODE_NORMAL );
	
	for( i=0; i<ZKN_POKELIST_POKETBL_NUM; i++ ){
		CLACT_ObjModeSet( p_work->poke_tbl[ i ], GX_OAM_MODE_NORMAL );
		CLACT_ObjModeSet( p_work->icon[ i ], GX_OAM_MODE_NORMAL );
		if(p_work->poke_name[ i ]){
			FONTOAM_ObjModeSet( p_work->poke_name[ i ]->p_fontoam, GX_OAM_MODE_NORMAL );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	セレクトポケモンのリストデータをグローバルのデータに反映
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListSelectPokeDataGlbSet( ZKN_POKELIST_GRAWORK* p_work, ZKN_GLB_DRAWDATA* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, int heap )
{
	const VecFx32* p_mat;
	int select_work_no;
	
	// 選択されているテーブルidx取得
	select_work_no = (p_work->poke_tbl_start + ZKN_POKELIST_POKETBL_CHECK) % ZKN_POKELIST_POKETBL_NUM;

	// ポケモンリストテーブルの座標を設定
	p_mat = CLACT_GetMatrix( p_work->poke_tbl[ select_work_no ] );

	// ポケモン名リストデータ作成
	ZKN_UTIL_PokeListPokeNameMakeGlb( p_drawglb, cp_glb->p_glb, heap, ZKN_GLBDATA_PokeListTblNoGet( cp_glb->p_glb ), p_mat->x, p_mat->y );
	ZKN_GlbPokeNameTblBGPriSet( p_drawglb, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ノーマルフェード処理	文字面とユーティリティ面をSLIDEイン　その他ブライトネス
 *
 *	@param	p_work			描画ワーク
 *	@param	cp_dataglb		描画グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDefaultFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	// BG面
	PokeListBgFadeInit( p_work, p_drawglb, cp_glb, fadein_out );

	// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
	
		if( fadein_out ){
			// フェードイン
			ChangeBrightnessRequest( ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, ZKN_POKELSIT_BRIGHTNESS_MSK, MASK_MAIN_DISPLAY );
		}else{
			// フェードアウト
			ChangeBrightnessRequest( ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, ZKN_POKELSIT_BRIGHTNESS_MSK, MASK_MAIN_DISPLAY );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード終了チェック
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb			グローバルデータ
 *	@param	fadein_out	フェードインアウト
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListDefaultFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	BOOL check[2];

	// BG面のSHUTTERフェード
	check[0] = PokeListBgFadeMain( p_work, p_drawglb );
	
	// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
		check[1] = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
	}else{
		check[1] = TRUE;
	}

	// ブライトネスフェード
	if( (check[0] == TRUE) &&
		(check[1] == TRUE) ){

		// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
		if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
			// 真っ暗にする
			if( fadein_out == FALSE ){
				SetBrightness( BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_MAIN_DISPLAY );
				// BG面の初期化
				GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
				// 文字列面初期化
				GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
			}
		}

		PokeListBgFadeDel( p_drawglb, cp_glb, fadein_out );

		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑画面とのフェード処理
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバルデータ
 *	@param	fadein_out		フェードイン TRUE アウト FALSE 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListChZukanFadeReq( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	// フェードするオブジェモードを半透明に
	PokeListOamFadeInit( p_work );

	// BG面
	PokeListBgFadeInit( p_work, p_drawglb, cp_glb, fadein_out );

	// フェードアウトのみの処理
	if( fadein_out == FALSE ){
		// ポケグラフェード
		PokeListPokeGraFadeInit( p_work, p_drawglb );

		// ポケリストフェード
		PokeListPokeListFadeInit( p_work, p_drawglb );
	}

	// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){


		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade, ZKN_POKELIST_FADEIN_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_POKELSIT_BRIGHTNESS_ZUKAN_MSK, PLANEMASK_BG3, ZKN_UTIL_FADE_MAIN );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑画面とのフェード処理終了チェック
 *
 *	@param	p_work			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバルデータ
 *	@param	fadein_out		フェードイン TRUE　アウト FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknPokeListChZukanFadeEndCheck( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb, const ZKN_POKELIST_GLB_DATA* cp_glb, BOOL fadein_out )
{
	BOOL check[4];
	int i;

	// BG面のSHUTTERフェード
	check[0] = PokeListBgFadeMain( p_work, p_drawglb );


	// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
	if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
		// ブライトネスフェード
		check[1] = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade );
	}

	// フェードアウトのみの処理
	if( fadein_out == FALSE ){

		// ポケグラ
		check[2] = PokeListPokeGraFadeMain( p_work, p_drawglb );

		// ポケリスト
		check[3] = PokeListPokeListFadeMain( p_work, p_drawglb );
	}else{
		check[2] = TRUE;
		check[3] = TRUE;
	}

	
	for( i=0; i<4; i++ ){
		if( check[i] == FALSE ){
			break;
		}
	}
	
	if( i == 4 ){
		// フェードアウトのとき
		if( fadein_out == FALSE ){
			// BGフェードモードがZKN_POKELIST_BG_FADE_SHUTTERの時はブライトネスを使用しない
			if( cp_glb->fade_mode != ZKN_POKELIST_BG_FADE_SHUTTER ){
				// 真っ暗にする
				G2_SetBlendBrightnessExt( ZKN_POKELIST_BRIGHTNESS_ZUKAN_END_MSK, PLANEMASK_BG3, 0, 0, BRIGHTNESS_BLACK );

				// BG面の初期化
				GF_BGL_BmpWinDataFill( &p_drawglb->p_drawglb->bmp_mfont, 0 );
				// 文字列面初期化
				GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_FONT_M );
			}
			
		}else{
			// フェードインのとき
			// OAMの半透明モード破棄
			PokeListOamFadeDelete( p_work );

			// グローバルポケリスト表示OFF
			ZKN_GlbPokeNameTblDrawFlagSet( p_drawglb->p_drawglb, FALSE );
			ZKN_GlbPokeNameTblObjModeSet( p_drawglb->p_drawglb, GX_OAM_MODE_NORMAL );
		}
		
		// BGフェードリセット
		PokeListBgFadeDel( p_drawglb, cp_glb, fadein_out );
		
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * [図鑑フェードエフェクト]
 *	@brief	ポケモングラフィック動作初期化
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeGraFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	ZKN_UTIL_MoveReq( &p_work->pokegra_move, ZKN_POKELIST_POKEGRA_X, ZKN_ZUKAN_POKEGRA_MAT_X, ZKN_POKELIST_POKEGRA_Y, ZKN_ZUKAN_POKEGRA_MAT_Y, ZKN_POKELIST_FADEIN_SYNC );

	// 座標設定
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_work->pokegra_move.x, p_work->pokegra_move.y );
}

//----------------------------------------------------------------------------
/**
 * [図鑑フェードエフェクト]
 *	@brief	ポケモングラフィック動作
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL PokeListPokeGraFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_work->pokegra_move );

	// 座標設定
	ZKN_GlbPokemonGraphicSetMatrix( p_drawglb->p_drawglb, p_work->pokegra_move.x, p_work->pokegra_move.y );

	return check;
}

//----------------------------------------------------------------------------
/**
 * [図鑑フェードエフェクト]
 *	@brief	ポケモンリスト動作初期化
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListPokeListFadeInit( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	ZKN_UTIL_MoveReq( &p_work->pokelist_move, ZKN_POKELIST_TBL_MAT_X, ZKN_ZUKAN_POKELIST_MAT_IX, ZKN_POKELIST_TBL_MAT_Y, ZKN_ZUKAN_POKELIST_MAT_IY, ZKN_POKELIST_FADEIN_SYNC );

	// 座標設定
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_work->pokelist_move.x, p_work->pokelist_move.y );
}

//----------------------------------------------------------------------------
/**
 * [図鑑フェードエフェクト]
 *	@brief	ポケモンリスト動作初期化
 *
 *	@param	p_work		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static BOOL PokeListPokeListFadeMain( ZKN_POKELIST_GRAWORK* p_work, ZKN_POKELIST_GLB_DRAW* p_drawglb )
{
	BOOL check;
	
	check = ZKN_UTIL_MoveMain( &p_work->pokelist_move );

	// 座標設定
	ZKN_UTIL_PokeListPokeNameGlbMatrixSet( p_drawglb->p_drawglb, p_work->pokelist_move.x, p_work->pokelist_move.y );

	return check;
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑破棄処理
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListZukanDel( ZKN_POKELIST_GLB_DATA* p_glb )
{
	*p_glb->p_event_key	|= EVENT_MSK_POKELIST_ZUKAN_END;
	// フェードインモード変更
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = FALSE;

	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑データ画面に移行
 *
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListZukanChg( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{
	*p_glb->p_event_key	|= EVENT_MSK_POKELIST_CHENGE_ZUKAN;
	// フェードインモード変更
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = TRUE;

	// グローバル変数初期化
	p_glb->move_count = 0;
//	PokeListMoveInit( p_glb, p_work );	
	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストからSORT画面に分岐
 *
 *	@param	p_glb 
 *
 *	@retval	TRUE	処理がされた
 *	@retval	FALSE	処理がなされなかった
 */
//-----------------------------------------------------------------------------
static BOOL PokeListSortChg( ZKN_POKELIST_GLB_DATA* p_glb )
{
	if( p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_NONE ){
		
		// ソート位置にカーソル移動して検索ソート画面開始
		*p_glb->p_event_key |= EVENT_MSK_POKELIST_CHENGE_SORTSEARCH;//*/

		// フェードモード
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
		p_glb->fade_zukan_data = FALSE;

		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

		// 選択音
		Snd_SePlay( ZKN_SND_SELECT );
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑モードを切り替える
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@retval	TRUE	処理がされた
 *	@retval	FALSE	処理がされなかった
 */
//-----------------------------------------------------------------------------
static BOOL PokeListZukanModeChg( ZKN_POKELIST_GLB_DATA* p_glb, int heap )
{
	int zkn_mode;

	// ｿｰﾄﾓｰﾄﾞの時はかえられない
	if( p_glb->p_glb->sort_search_flag == ZKN_SORTSEARCH_SORT ){
		return FALSE;
	}
		

	// 図鑑モードを変更する
	zkn_mode = ZKN_GLBDATA_PokeZknModeGet(p_glb->p_glb);
	if( zkn_mode == ZKN_MODE_SHINOH ){
		zkn_mode = ZKN_MODE_ZENKOKU;
	}else{
		zkn_mode = ZKN_MODE_SHINOH;
	}
	
	// 図鑑モードを変更できるかチェック
	if( ZKN_GLBDATA_PokeZknModeChengeCheck( p_glb->p_glb, zkn_mode ) ){
		// 変更
		ZKN_GLBDATA_PokeZknModeChenge( p_glb->p_glb, zkn_mode );

		// 選択音
		Snd_SePlay( ZKN_SND_SELECT );

		// リスト設定
		ZKN_GLBDATA_PokeListTblMake( p_glb->p_glb, 
				ZKN_POKELIST_SORT_NORMAL, 
				ZKN_POKELIST_SEARCH_NAME_NONE,
				ZKN_POKELIST_SEARCH_TYPE_NONE,
				ZKN_POKELIST_SEARCH_TYPE_NONE,
				ZKN_POKELIST_SEARCH_FORM_NONE,
				zkn_mode, heap );

		// リストナンバー初期化
		ZKN_GLBDATA_PokeListTblNoSet( p_glb->p_glb, 0 );

		// 動作カウンタも初期化
		p_glb->move_count = 0;	

		// ポケリスト画面再作成
		*p_glb->p_event_key |= EVENT_MSK_POKELIST_CHANGE;
		// フェードインモード変更
		p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
		p_glb->fade_zukan_data = FALSE;

		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

		// 描画行進OFF
		p_glb->move_draw = FALSE;

		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑のSORT設定リセット
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PokeListZukanReset( ZKN_POKELIST_GLB_DATA* p_glb, int heap )
{
	// モンスターナンバー保存
	u32 monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );
	
	// 図鑑リストリセット
	ZKN_GLBDATA_PokeListTblMake( p_glb->p_glb, 
			ZKN_POKELIST_SORT_NORMAL, 
			ZKN_POKELIST_SEARCH_NAME_NONE,
			ZKN_POKELIST_SEARCH_TYPE_NONE,
			ZKN_POKELIST_SEARCH_TYPE_NONE,
			ZKN_POKELIST_SEARCH_FORM_NONE,
			ZKN_GLBDATA_PokeZknModeGet( p_glb->p_glb ), heap );
	(*p_glb->p_event_key) |= EVENT_MSK_POKELIST_CHANGE;

	// リストナンバー初期化
	ZKN_GLBDATA_PokeListTblNoSet_Monsno( p_glb->p_glb, monsno );

	// 動作カウンタも初期化
	p_glb->move_count = 0;	

	// ｿｰﾄモードも変更
	p_glb->p_glb->sort_search_flag = ZKN_SORTSEARCH_NONE;

	// フェードインモード変更
	p_glb->fade_mode = ZKN_POKELIST_BG_FADE_NORMAL;
	p_glb->fade_zukan_data = FALSE;
	// 方向もなし
	p_glb->move_way = ZKN_POKE_LIST_NO_MOVE;

	p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_ALL;

	// 描画行進OFF
	p_glb->move_draw = FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	スキップ動作
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListSkipMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{
	p_work->skip_count--;
	
	if( p_work->skip_count >= 0 ){
		if( PokeListMoveAdd( p_glb, p_work->skip_add ) ){

			PokeListMoveReq( p_glb, p_work, p_work->skip_way );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// サブ画面ホイール動作停止
			// 選択移動音
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			p_work->skip_count = 0;		// 最終新項目までいった
		}
	}else{

		// スキップ終了
		PokeListMoveInit( p_glb, p_work );	
		p_work->skip_flag = FALSE;		// スキップ終了
		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// サブ面ホイールロック解除
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	キー動作
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeListKeyMove( ZKN_POKELIST_WORK* p_work, ZKN_POKELIST_GLB_DATA* p_glb )
{

	// カーソルアップ
	if( sys.cont & PAD_KEY_UP ){
		// 値が更新されたら動かす
		if( PokeListMoveAdd( p_glb, -1 ) ){
			PokeListMoveReq( p_glb, p_work, ZKN_POKE_LIST_DOWN );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// サブ画面ホイール動作停止
			
			// 選択移動音
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			PokeListMoveInit( p_glb, p_work );	
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// サブ画面ホイール動作停止解除
		}
		return ;
	}

	// カーソル
	if( sys.cont & PAD_KEY_DOWN ){
		// 値が更新されたら動かす
		if( PokeListMoveAdd( p_glb, 1 ) ){
			PokeListMoveReq( p_glb, p_work, ZKN_POKE_LIST_UP );
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NORMAL;	// サブ画面ホイール動作停止

			// 選択移動音
			Snd_SePlay( ZKN_SND_SELECT_MOVE_ONE );
		}else{
			PokeListMoveInit( p_glb, p_work );	
			p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// サブ画面ホイール動作停止解除
		}
		return ;
	}

	//スキップ処理
	if( sys.trg & PAD_KEY_LEFT ){
		p_work->skip_flag = TRUE;
		p_work->skip_count = ZKN_POKE_LIST_MOVE_SKIP_NUM;
		p_work->skip_add = -1;
		p_work->skip_way = ZKN_POKE_LIST_DOWN;
		// 速度調整
		PokeListSkipMoveInit( p_glb, p_work );
		return ;
	}
	if( sys.trg & PAD_KEY_RIGHT ){
		p_work->skip_flag = TRUE;
		p_work->skip_count = ZKN_POKE_LIST_MOVE_SKIP_NUM;
		p_work->skip_add = 1;
		p_work->skip_way = ZKN_POKE_LIST_UP;
		// 速度調整
		PokeListSkipMoveInit( p_glb, p_work );
		return ;
	}

	// 全てに引っかからないときは何もしない
	// 多重に初期化するとサブ画面でデータ更新中に
	// 初期化してしまう
	if( p_glb->sub_wheel_lock == ZKN_POKELIST_WHEEL_LOCK_NORMAL ){
		PokeListMoveInit( p_glb, p_work );	
		p_glb->sub_wheel_lock = ZKN_POKELIST_WHEEL_LOCK_NONE;	// サブ画面ホイール動作停止解除
	}
}

