//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_sub.c
 *@brief	画面きりかえワイプ処理
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "string.h"
#include "calctool.h"
#include "system/wipe_def.h"
#include "system/wipe.h"
#include "include/gflib/sdkdef.h"
#include "include/system/brightness.h"

#define __WIPE_SUB_H_GLOBAL
#include "system/wipe_sub.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define SUM_NUM_MINI	(128)
#define ROTA_NUM(x)		((0xffff*(x))/360)

// ドア用
// この値で,今の開いている値を割ると角度が出てくる
#define	WIPE_DOOR_ROTA_NUM	(21)
//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	マスターブライトネスフェードワーク
//	
//=====================================
typedef struct {
	int a_count;	// 変化数（段階数）
	int piece_sync;	// １片のシンク数
	int sync_c;		// シンクカウント

	int set_num;
	int end_num;
	int add_num;
	int disp;
	
} WIPE_BRIGHTNESS_FADE;


//-------------------------------------
//	
//	ウィンドウ座標をパック
//	
//=====================================
typedef struct {
	int x1;
	int y1;
	int x2;
	int y2;
} WIPE_WND_POSITION;


//-------------------------------------
//	
//	ウィンドウ変形構造体
//
//	シャッター・イン/アウト
//	スライド・イン/アウト
//	シャッター・イン/アウト
//	ボックス・イン/アウト
//	処理用構造体です。
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// 開始座標
	WIPE_WND_POSITION add;	// 加算座標
	WIPE_WND_POSITION ed;	// 終了座標

	int disp;		// 面
	int wnd_no;		// ウィンドウナンバー
	
	int a_count;	// 変化数（段階数）
	int piece_sync;	// １片のシンク数
	int sync_c;		// シンクカウント
	int fade_flg;	// フェードフラグ

	WNDP_SYS_PTR wnd_sys;
} WIPE_TYPE_WND_MOVE;

//-------------------------------------
//	
//	ウィンドウ変形初期化用
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// 開始座標
	WIPE_WND_POSITION ed;	// 終了座標

	u8 wnd_no;		// ウィンドウナンバー

	u8 in_wnd;		// ウィンドウの中
	u8 out_wnd;	// ウィンドウの外

	u8 fade_flg;	// フェードフラグ

} WIPE_TYPE_WND_MOVE_FP;


//-------------------------------------
//	
//	ウィンドウ変形構造体
//	ウィンドウを２つ使うときよう
//
//	スプリット・イン/アウト
//	
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE wnd0;
	WIPE_TYPE_WND_MOVE wnd1;
} WIPE_TYPE_WND_DMOVE;

//-------------------------------------
//	
//	HBlank中のwndデータ
//	構造体
//	
//=====================================
typedef struct {
	short	wnd_data[2][192];	// wndデータ
	short	wnd_tmp[2][192];		// メインループ計算用
	
	int wnd_no;		// ウィンドウナンバー
} WIPE_TYPE_HB_WND_ONE;

//-------------------------------------
//	
//	Hblank中のwndデータを
//	束ねた構造体
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND_ONE* data;
	int wnd_data_num;
	int disp;		// 面
} WIPE_TYPE_HB_WND;


//-------------------------------------
//	
//	HBlankを使用し円をwndで描くシステムの
//	構造体
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_circle;	// HblankCIRCLEデータ
	int	r;		// 半径
	int x;		// 中心座標
	int y;
	int add_r;		// 半径変化値
	int a_count;	// 変化数（段階数）
	int piece_sync;	// １片のシンク数
	int sync_c;		// シンクカウント
	int heap;		// 使用するヒープ
	int fade_flg;	// フェードフラグ

	WNDP_SYS_PTR wnd_sys;	// ウィンドウ設定データ保存領域
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
} WIPE_TYPE_WND_CIRCLE;

//-------------------------------------
//	
//	HBlankを使用し円をwndで描くシステム
//	パック関数の引数
//	
//=====================================
typedef struct {
	int r;
	int e_r;
	short x;
	short y;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_CIRCLE_FP;

//-------------------------------------
//	
//	HBlankを使用しカーテンをwndで描くシステムの
//	構造体
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_c;	// Hblankデータ
	int rota;		// 開き角度
	int rota_add;	// １回で開く角度
	int a_count;	// 変化数（段階数）
	int piece_sync;	// １片のシンク数
	int sync_c;		// シンクカウント
	int fade_flg;	// フェードフラグ

	WNDP_SYS_PTR wnd_sys;
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク

	int heap;		// 使用するヒープ
} WIPE_TYPE_WND_CURTAIN;

//-------------------------------------
//	
//	HBlankを使用しカーテンを表示するシステム
//	パック関数の引数
//	
//=====================================
typedef struct {
	int rota;
	int e_rota;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_CURTAIN_FP;


//-------------------------------------
//	
//	HBlankを使用しドアをwndで描くシステムの
//	構造体
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND hb_d;	// Hblankデータ
	int open_max;	// 最大の開く距離
	int open_r;		// 開く回転値
	int open_r_a;	// 足す値
	int a_count;	// 変化数（段階数）
	int piece_sync;	// １片のシンク数
	int sync_c;		// シンクカウント
	int fade_flg;	// フェードフラグ

	WNDP_SYS_PTR wnd_sys;
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
	int heap;		// 使用するヒープ
} WIPE_TYPE_WND_DOOR;

//-------------------------------------
//	
//	HBlankを使用しドアを表示するシステム
//	パック関数の引数
//	
//=====================================
typedef struct {
	int s_d;
	int e_d;
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_DOOR_FP;

//-------------------------------------
//	
//	分割されたウィンドウの各々の設定
//	
//=====================================
typedef struct {
	WIPE_WND_POSITION st;	// 開始座標
	WIPE_WND_POSITION add;	// 加算座標
	WIPE_WND_POSITION ed;	// 終了座標
} WIPE_TYPE_WND_D_PIECE;

//-------------------------------------
//	
//	１つのウィンドウを複数のウィンドウ
//	使用しているかのように使用する
//	
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb_divi;		// Hblank設定データ
	
	WIPE_TYPE_WND_D_PIECE* piece_tbl;		// 分割したデータ
	int						piece_num;		// ウィンドウ分割数

	int a_count;		// 変化数（段階数）
	int piece_sync;		// １片のシンク数
	int sync_c;			// シンクカウント
	int fade_flg;	// フェードフラグ

	WNDP_SYS_PTR wnd_sys;	// ウィンドウVblank変更システムのワーク
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
	int heap;			// 使用するヒープ
} WIPE_TYPE_WND_DIVI;

//-------------------------------------
//	
//	１つのウィンドウを複数のウィンドウ
//	使用しているかのように使用する	
//	引数用
//=====================================
typedef struct {
	const WIPE_WND_POSITION* p_st;	// 分割した各々の開始座標	優先順位（０＞ｎ）
	const WIPE_WND_POSITION* p_ed;	// 分割した各々の終了座標
	u8 divi_num;				// 分割数
	u8 wnd_no;
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_DIVI_FP;


//-------------------------------------
//	
//	スクリュー１つのデータ
//	
//=====================================
typedef struct {
	int	rota;		// 現在の回転角
	int s_rota;		// 回転角度初期値
	int add_num_rota;	// 回転角度の最大変化値
} WIPE_TYPE_WND_SCREW_ONE;

//-------------------------------------
//	
//	スクリューデータ構造体
//
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb;		// Hblank設定データ
	
	WIPE_TYPE_WND_SCREW_ONE screw;	// スクリューデータ

	int a_count_max;	// 変化数（段階数）最大数
	int a_count;		// 変化数（段階数）カウント値
	int piece_sync;		// １片のシンク数
	int sync_c;			// シンクカウント
	int fade_flg;		// フェードフラグ
	int heap;			// ヒープ

	WNDP_SYS_PTR wnd_sys;	// ウィンドウVblank変更システムのワーク
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
} WIPE_TYPE_WND_SCREW;

//-------------------------------------
//	
//	スクリュー動作関数引数
//	
//=====================================
typedef struct {
	int	s_rota;		// 開始回転角
	int	e_rota;		// 終了回転角
	
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_SCREW_FP;

//-------------------------------------
//	
//	フラッシュ４方向データ
//	
//=====================================
typedef struct {
	int	rota;		// 現在の回転角
	int s_rota;		// 回転角度初期値
	int add_num_rota;	// 回転角度の最大変化値
} WIPE_TYPE_WND_FLASH_FOUR_ONE;

//-------------------------------------
//	
//	フラッシュ４方向データ構造体
//
//=====================================
typedef struct {
	WIPE_TYPE_HB_WND		hb;		// Hblank設定データ
	
	WIPE_TYPE_WND_FLASH_FOUR_ONE screw;	// スクリューデータ

	int a_count_max;	// 変化数（段階数）最大数
	int a_count;		// 変化数（段階数）カウント値
	int piece_sync;		// １片のシンク数
	int sync_c;			// シンクカウント
	int fade_flg;		// フェードフラグ
	int heap;			// ヒープ

	WNDP_SYS_PTR wnd_sys;	// ウィンドウVblank変更システムのワーク
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
} WIPE_TYPE_WND_FLASH_FOUR;

//-------------------------------------
//	
//	フラッシュ４方向動作関数引数
//	
//=====================================
typedef struct {
	int	s_rota;		// 開始回転角
	int	e_rota;		// 終了回転角
	
	u8 in_wnd;
	u8 out_wnd;
	u8 fade_flg;
} WIPE_TYPE_WND_FLASH_FOUR_FP;

//-------------------------------------
//	V方向WND動作　Hブランクワーク
//=====================================
typedef struct {
	u8 in_out_write[ 192 ];	// in_wnd out_wndフラグ
	u8 in_out_read[ 192 ];	// in_wnd out_wndフラグ
	
	int wnd_no;
} WIPE_TYPE_WND_VMOVE_HDATA;

//-------------------------------------
//	V方向WND動作　束ねたデータ
//=====================================
typedef struct {
	WIPE_TYPE_WND_VMOVE_HDATA data[2];
	u8 wnd_data_num;	// ウィンドウ使用数(最大2)
	u8 disp;		// 面
} WIPE_TYPE_WND_VMOVE;
enum{
	WIPE_WND_VMOVE_INWND,
	WIPE_WND_VMOVE_OUTWND
};

//-------------------------------------
//	
//	縦方向Hブランク使用ウィンドウ動作
//	システム
//	
//=====================================
//-------------------------------------
//	動作データ
//
//	in_outの領域がs_yからe_yへと広がっていきます
//=====================================
typedef struct {
	u8 s_y;		
	u8 e_y;
	u8 in_out;		// WIPE_WND_VMOVE_INWND, WIPE_WND_VMOVE_OUTWND
} WIPE_TYPE_WND_VMOVE_DATA;

//-------------------------------------
//	管理データ
//=====================================
typedef struct {
	WIPE_TYPE_WND_VMOVE HblankData;	// Hブランクデータ

	const WIPE_TYPE_WND_VMOVE_DATA* p_param;
	int param_num;

	int a_count_max;	// 変化数（段階数）最大数
	int a_count;		// 変化数（段階数）カウント値
	int piece_sync;		// １片のシンク数
	int sync_c;			// シンクカウント
	int fade_flg;		// フェードフラグ
	int heap;			// ヒープ

	WNDP_SYS_PTR wnd_sys;	// ウィンドウVblank変更システムのワーク
	WIPE_HBLANK* p_wipehb;	// ワイプHBlankワーク
} WIPE_TYPE_WND_VMOVE_CONT;

//-------------------------------------
//	パラメータ
//=====================================
typedef struct {
	const WIPE_TYPE_WND_VMOVE_DATA* cp_data;
	u8 data_num;
	u8 fade_flg;
} WIPE_TYPE_WND_VMOVE_PARAM;


//-------------------------------------
//
//	
//		ポケモンワイプ
//
//	
//=====================================
//-------------------------------------
//	パラメータ
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE_FP wnd_move;
	WIPE_TYPE_WND_VMOVE_PARAM wnd_split;
	fx32 sync_div_par;	// シンク数の割合（wnd_moveの割合）
} WIPE_TYPE_WND_PESOCOM_PARAM;

//-------------------------------------
//	ワーク
//=====================================
typedef struct {
	WIPE_TYPE_WND_MOVE wnd_move;
	WIPE_TYPE_WND_VMOVE_CONT wnd_split;
	WIPE_TYPE_WND_PESOCOM_PARAM* p_param;
	u8 sub_divi;
	u8 seq;	// シーケンス
	u8 fade_flg;
	u8 dummy;
} WIPE_TYPE_WND_PESOCOM;




//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
// 各種計算用
static fx32 sum_tan(int rota);
static int sub_rota_height_width_one( int rota, int height );
static void sum_rota_height_width(int rota, int* depth, int work_num, int s_h);
static int sum_triangle_height(int rota, int undefground);
static int sum_add_num(int st, int ed, int divi);
static int sum_add_wnd_width(int num1, int num2);
static void sum_add_wnd(WIPE_WND_POSITION* num, WIPE_WND_POSITION* add);
static void sum_set_wnd_position(WIPE_WND_POSITION* st, WIPE_WND_POSITION* ed, WIPE_WND_POSITION* add, const WIPE_WND_POSITION* set_st, const WIPE_WND_POSITION* set_ed, int division );

// ウィンドウ処理用
static void scchg_WndEnd(int flag, WNDP_SYS_PTR wnd_sys, int disp);
static void scchg_h_Wnd(void* work);
static void scchg_h_WndMake(WIPE_TYPE_HB_WND* data, int flag, int disp, int heap);
static void scchg_h_WndDel(WIPE_TYPE_HB_WND* data);
static void scchg_v_h_WndDel( TCB_PTR tcb, void* work );
static void scchg_main_h_WndDel( WIPE_TYPE_HB_WND* data );
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndNoDataGet(WIPE_TYPE_HB_WND* data, int wnd_no);
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndIdxDataGet(WIPE_TYPE_HB_WND* data, int idx);
static void scchg_WndSwap(TCB_PTR tcb, void* work);
static void scchg_WndSetUp(WNDP_SYS_PTR wnd_sys, int in_wnd, int out_wnd, int wnd_no, int disp, int x1, int y1, int x2, int y2, int fade_flg);
static void scchg_WndVisible(WNDP_SYS_PTR wnd_sys, int plane, int disp, int fade_flg);

// ウィンドウY動作処理用
static void scchg_h_VMoveWndInit( WIPE_TYPE_WND_VMOVE* p_wnddata, int disp, int data_num, int wnd_no0, int wnd_no1 );

static void scchg_h_VMoveWnd_SwapReq( WIPE_TYPE_WND_VMOVE* p_wnddata );
static void scchg_h_VMoveWnd_Start( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap );
static void scchg_h_VMoveWnd_End( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap );

static void scchg_h_VMoveWnd_Swap( TCB_PTR tcb, void* p_work );
static void scchg_h_VMoveWnd_Main( void* p_work );


// ブライトネスフェード処理用
static void scchg_FadeInit(WIPE_SYS_WIPE_WORK* wipe, int fade_flag);
static BOOL scchg_FadePack(WIPE_SYS_WIPE_WORK* wipe);
static BOOL scchg_FadeCalcMain( WIPE_BRIGHTNESS_FADE* data );

// 四角表示ウィンドウ処理用
static void scchg_WndMovePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram );
static BOOL scchg_WndMovePack(WIPE_SYS_WIPE_WORK* wipe);

static void scchg_WndMoveDoublePackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram1, const WIPE_TYPE_WND_MOVE_FP* pram2);
static BOOL scchg_WndMoveDoublePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndMoveInit(WIPE_TYPE_WND_MOVE* data, const WIPE_TYPE_WND_MOVE_FP* pram, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys);
static BOOL scchg_WndMoveMain(WIPE_TYPE_WND_MOVE* data);

// 円表示ウィンドウ処理用
static void scchg_WndCirclePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CIRCLE_FP* param );
static BOOL scchg_WndCirclePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndCircleInit(WIPE_TYPE_WND_CIRCLE* data, const WIPE_TYPE_WND_CIRCLE_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap);
static BOOL scchg_WndCircleMain(WIPE_TYPE_WND_CIRCLE* data);
static void scchg_WndCircleSum(WIPE_TYPE_WND_CIRCLE* work);

// カーテン型ウィンドウ表示用
static void scchg_WndCurtainPackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CURTAIN_FP* param);
static BOOL scchg_WndCurtainPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndCurtainInit(WIPE_TYPE_WND_CURTAIN* data, const WIPE_TYPE_WND_CURTAIN_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndCurtainMain(WIPE_TYPE_WND_CURTAIN* data);
static void scchg_WndCurtainSum(WIPE_TYPE_WND_CURTAIN* work);

// ドア型ウィンドウ表示用

static void scchg_WndDoorPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DOOR_FP* param);
static BOOL scchg_WndDoorPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndDoorInit(WIPE_TYPE_WND_DOOR* data, const WIPE_TYPE_WND_DOOR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndDoorMain(WIPE_TYPE_WND_DOOR* data);
static void scchg_WndDoorSum(WIPE_TYPE_WND_DOOR* work);

// 1ウィンドウ分割処理システム
static void scchg_WndDivisionPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DIVI_FP* param);
static BOOL scchg_WndDivisionPack(WIPE_SYS_WIPE_WORK* wipe);
static BOOL scchg_WndDivisionMain(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionInit(WIPE_TYPE_WND_DIVI* data, const WIPE_TYPE_WND_DIVI_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static void scchg_WndDivisionEnd(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionSum(WIPE_TYPE_WND_DIVI* work);
static void scchg_WndDivisionMainSub(WIPE_TYPE_WND_DIVI* data);
static void scchg_WndDivisionSumSub(WIPE_TYPE_HB_WND* hb_divi, WIPE_WND_POSITION* set);

// スクリュー
static void scchg_WndScrewPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_SCREW_FP* param);
static BOOL scchg_WndScrewPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndScrewInit(WIPE_TYPE_WND_SCREW* data, WIPE_TYPE_WND_SCREW_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndScrewMain(WIPE_TYPE_WND_SCREW* data);
static void scchg_WndScrewEnd(WIPE_TYPE_WND_SCREW* data);
static void scchg_WndScrewSum(WIPE_TYPE_WND_SCREW* work);
static void scchg_WndScrewOneAdd( WIPE_TYPE_WND_SCREW_ONE* p_data, int count, int count_max );

// フラッシュ　４
static void scchg_WndFlashFourPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_FLASH_FOUR_FP* param);
static BOOL scchg_WndFlashFourPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndFlashFourInit(WIPE_TYPE_WND_FLASH_FOUR* data, WIPE_TYPE_WND_FLASH_FOUR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndFlashFourMain(WIPE_TYPE_WND_FLASH_FOUR* data);
static void scchg_WndFlashFourEnd(WIPE_TYPE_WND_FLASH_FOUR* data);
static void scchg_WndFlashFourSum(WIPE_TYPE_WND_FLASH_FOUR* work);
static void scchg_WndFlashFourOneAdd( WIPE_TYPE_WND_FLASH_FOUR_ONE* p_data, int count, int count_max );


// Hブランク使用	ウィンドウY方向移動システム
static void scchg_WndWndVMovePackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_VMOVE_PARAM* param);
static BOOL scchg_WndWndVMovePack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndWndVMoveInit(WIPE_TYPE_WND_VMOVE_CONT* data, WIPE_TYPE_WND_VMOVE_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndVMoveMain(WIPE_TYPE_WND_VMOVE_CONT* data);
static void scchg_WndWndVMoveEnd(WIPE_TYPE_WND_VMOVE_CONT* data);
static void scchg_WndWndVMoveSum(WIPE_TYPE_WND_VMOVE_CONT* work);
static void scchg_WndWndVMoveSub_Core( const WIPE_TYPE_WND_VMOVE_DATA* p_one, WIPE_TYPE_WND_VMOVE_HDATA* p_buff, int count, int count_max );


// パソコンワイプ
static void scchg_WndWndPesocomPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_PESOCOM_PARAM* param);
static BOOL scchg_WndWndPesocomPack(WIPE_SYS_WIPE_WORK* wipe);
static void scchg_WndWndPesocomInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndPesocomMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe );
static void scchg_WndWndPesocomOutInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap );
static BOOL scchg_WndWndPesocomOutMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe );



//----------------------------------------------------------------------------
/**
 *
 *@brief	フェードアウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	BOOL	TRUE：終了　FALSE：続行
 *
 * フェードアウト
 *	画面が徐々に暗くなっていく
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc00(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_BRI;
		
		scchg_FadeInit(wipe, WIPE_FADE_OUT);
		return FALSE;
	}
	return scchg_FadePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	フェードイン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	BOOL	TRUE：終了　FALSE：続行
 *
 *  フェードイン
 *		画面が徐々に明るくなり、画面が表示される
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc01(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_BRI;
		
		scchg_FadeInit(wipe, WIPE_FADE_IN);
		return FALSE;
	}
	return scchg_FadePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	シャッターアウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	noen
 *
 * 上から下へのシャッターアウト
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc02(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			0, 192, WIPE_WND_VMOVE_OUTWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_OUT
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	シャッターイン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 上から下へのシャッターイン
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc03(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			0, 192, WIPE_WND_VMOVE_INWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_IN
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	シャッターアウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	noen
 *
 * 下から上へのシャッターアウト
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc04(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			192, 0, WIPE_WND_VMOVE_OUTWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_OUT
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	シャッターイン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 下から上へのシャッターイン
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc05(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data = {
			192, 0, WIPE_WND_VMOVE_INWND
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			1,
			WIPE_FADE_IN
		};
		param.cp_data = &move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スライドアウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc06(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{0,0,0,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スライドイン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc07(WIPE_SYS_WIPE_WORK* wipe)
{

	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,0,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN	
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 縦　画面上下から
 * 
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc08(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 0, 96, WIPE_WND_VMOVE_OUTWND },
			{ 192, 96, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 縦　画面中央から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc09(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 96, 0, WIPE_WND_VMOVE_INWND },
			{ 96, 192, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 縦　画面中央から
 * 
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc10(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 96, 0, WIPE_WND_VMOVE_OUTWND },
			{ 96, 192, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 縦　画面上下から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc11(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[2] = {
			{ 0, 96, WIPE_WND_VMOVE_INWND },
			{ 192, 96, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			2,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 横　画面左右から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc12(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,0,128,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 横　画面中央から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc13(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,0,128,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 横　画面中央から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc14(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_MOVE_FP param1 = {
			{128,0,128,192},
			{0,0,128,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};
		static const WIPE_TYPE_WND_MOVE_FP param2 = {
			{128,0,128,192},
			{128,0,255,192},
			WNDP_WND_1,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};
	
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMoveDoublePackInit(wipe, &param1, &param2);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMoveDoublePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スプリット・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 * 横　画面左右から
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc15(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_MOVE_FP param1 = {
			{0,0,128,192},
			{128,0,128,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};
		static const WIPE_TYPE_WND_MOVE_FP param2 = {
			{128,0,255,192},
			{128,0,128,192},
			WNDP_WND_1,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};
	
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMoveDoublePackInit(wipe, &param1, &param2);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMoveDoublePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ホール・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードアウト
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc16(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			256,0,
			128,96,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ホール・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードイン
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc17(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,256,
			128,96,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	トンネル・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードアウト
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc18(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			512,0,
			128,288,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	トンネル・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードイン
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc19(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,512,
			128,288,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );
		
		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カーテン・アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc20(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CURTAIN_FP param = {
			ROTA_NUM(90),
			0,
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCurtainPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndCurtainPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	カーテン・イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc21(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CURTAIN_FP param = {
			0,
			ROTA_NUM(90),// tan90は値不定になるので、安定を求め90にしています。
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCurtainPackInit(wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndCurtainPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ボックスアウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none	
 *
 * 外から中
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc22(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,96,128,96},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ボックスイン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 * 中から外
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc23(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,96,128,96},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ボックスアウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none	
 *
 *	中から外
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc24(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{128,96,128,96},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);
		
		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ボックスイン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 * 外から中
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc25(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{128,96,128,96},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドアアウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc26(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_DOOR_FP param = {
			ROTA_NUM(90),
			ROTA_NUM(0),
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDoorPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
		
	return scchg_WndDoorPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドアイン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc27(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_DOOR_FP param = {
			ROTA_NUM(0),
			ROTA_NUM(90),
			WNDP_WND_0,
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDoorPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndDoorPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オルタネートアウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc28(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_WND_POSITION st[] = {
			{0,0,255,48},
			{0,47,255,96},
			{0,96,255,144},
			{0,144,255,192}
		};
		static const WIPE_WND_POSITION ed[] = {
			{0,0,0,48},
			{255,47,255,96},
			{0,96,0,144},
			{255,144,255,192}
		};
		WIPE_TYPE_WND_DIVI_FP param;
		
		param.p_st			= st;
		param.p_ed			= ed;
		param.divi_num		= 4;
		param.wnd_no		= WNDP_WND_0;
		param.in_wnd		= GX_BLEND_ALL;
		param.out_wnd		= GX_BLEND_PLANEMASK_BD;
		param.fade_flg		= WIPE_FADE_OUT;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDivisionPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndDivisionPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	オルタネート・イン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc29(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_WND_POSITION st[] = {
			{255,0,255,48},
			{0,47,0,96},
			{255,96,255,144},
			{0,144,0,192}
		};
		static const WIPE_WND_POSITION ed[] = {
			{0,0,255,48},
			{0,47,255,96},
			{0,96,255,144},
			{0,144,255,192}
		};
		WIPE_TYPE_WND_DIVI_FP param;
		
		param.p_st			= st;
		param.p_ed			= ed;
		param.divi_num		= 4;
		param.wnd_no		= WNDP_WND_0;
		param.in_wnd		= GX_BLEND_ALL;
		param.out_wnd		= GX_BLEND_PLANEMASK_BD;
		param.fade_flg		= WIPE_FADE_IN;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndDivisionPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	
	return scchg_WndDivisionPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ブラインドアウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none	
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc30(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[3] = {
			{ 0, 64, WIPE_WND_VMOVE_OUTWND },
			{ 64, 128, WIPE_WND_VMOVE_OUTWND },
			{ 128, 192, WIPE_WND_VMOVE_OUTWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			3,
			WIPE_FADE_OUT
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ブラインド・イン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc31(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		static const WIPE_TYPE_WND_VMOVE_DATA move_data[3] = {
			{ 64, 0, WIPE_WND_VMOVE_INWND },
			{ 128, 64, WIPE_WND_VMOVE_INWND },
			{ 192, 128, WIPE_WND_VMOVE_INWND },
		};
		static WIPE_TYPE_WND_VMOVE_PARAM param = {
			NULL,
			3,
			WIPE_FADE_IN
		};
		param.cp_data = move_data;
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndVMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;

		return FALSE;
	}
	return scchg_WndWndVMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スクリュー・アウト
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc32(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_SCREW_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(179),	
			GX_BLEND_PLANEMASK_BD,
			GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndScrewPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndScrewPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スクリュー・イン
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc33(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_SCREW_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(179),	
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndScrewPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndScrewPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	フラッシュ・アウト　４
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc34(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_FLASH_FOUR_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(45), 
			GX_BLEND_ALL,
			GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndFlashFourPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndFlashFourPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	フラッシュ・イン	４
 *
 *@param	wipe	ワイプワーク
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc35(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		WIPE_TYPE_WND_FLASH_FOUR_FP param = {
			FX_GET_ROTA_NUM(0), FX_GET_ROTA_NUM(45),	// 45にうしないと隙間があいてしまった。
			GX_BLEND_PLANEMASK_BD,
			GX_BLEND_ALL,
			WIPE_FADE_IN
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndFlashFourPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndFlashFourPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	トンネル・アウト	上から
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードアウト
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc36(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			512,0,
			128,-80,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_OUT
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	トンネル・イン		上から
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *	円形フェードイン
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc37(WIPE_SYS_WIPE_WORK* wipe)
{
	if(wipe->sequence == WIPE_INIT){
		static const WIPE_TYPE_WND_CIRCLE_FP param = {
			0,512,
			128,-80,
			WNDP_WND_0,
			GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
			WIPE_FADE_IN
		};
		WIPE_SetBackDropColor( wipe->color );
		scchg_WndCirclePackInit( wipe, &param );

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndCirclePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スライドアウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	noen
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc38(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,0,192},
			{0,0,255,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_OUT
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	スライドイン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc39(WIPE_SYS_WIPE_WORK* wipe)
{

	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_MOVE_FP param = {
			{0,0,255,192},
			{0,0,0,192},
			WNDP_WND_0,
			GX_BLEND_PLANEMASK_BD,GX_BLEND_ALL,
			WIPE_FADE_IN	
		};

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndMovePackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}
	return scchg_WndMovePack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パソコン　アウト
 *
 *@param	wipe	ワイプデータ
 *
 *@return	noen
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc40(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_VMOVE_DATA split_data[2] = {
			{0, 94, WIPE_WND_VMOVE_OUTWND},
			{192, 98, WIPE_WND_VMOVE_OUTWND},
		};
		static WIPE_TYPE_WND_PESOCOM_PARAM param ={
			{
				{0,94,255,98},
				{128,96,128,96},
				WNDP_WND_0,
				GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
				WIPE_FADE_OUT
			},
			{
				NULL,
				2,
				WIPE_FADE_OUT
			},
			FX32_CONST( 0.70f )
		};
		param.wnd_split.cp_data = split_data;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndPesocomPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_OUT;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndWndPesocomPack(wipe);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パソコン　イン
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
BOOL WipeFunc41(WIPE_SYS_WIPE_WORK* wipe)
{
	if( wipe->sequence == WIPE_INIT ){
		
		static const WIPE_TYPE_WND_VMOVE_DATA split_data[2] = {
			{94, 0, WIPE_WND_VMOVE_INWND},
			{98, 192, WIPE_WND_VMOVE_INWND},
		};
		static WIPE_TYPE_WND_PESOCOM_PARAM param ={
			{
				{128,96,128,96},
				{0,94,255,98},
				WNDP_WND_0,
				GX_BLEND_ALL,GX_BLEND_PLANEMASK_BD,
				WIPE_FADE_IN
			},
			{
				NULL,
				2,
				WIPE_FADE_IN
			},
			FX32_CONST( 0.70f )
		};
		param.wnd_split.cp_data = split_data;

		WIPE_SetBackDropColor( wipe->color );
		scchg_WndWndPesocomPackInit(wipe, &param);

		wipe->fade_inout	= WIPE_FADE_IN;
		wipe->wnd_br		= WIPE_USE_WND;
		return FALSE;
	}

	return scchg_WndWndPesocomPack(wipe);
}



//-----------------------------------------------------------------------------
//
//	各ワイプで使用する関数郡
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	タンジェント計算
 *
 *@param	rota		回転角
 *
 *@return	fx32		tan(rota)の値
 *
 *	タンジェントは角度９０のときは、不定値になるので注意してください
 *
 *
 */
//-----------------------------------------------------------------------------
static fx32 sum_tan(int rota)
{
	return FX_Div(FX_SinIdx(rota), FX_CosIdx(rota));
}
//----------------------------------------------------------------------------
/**
 *	@brief	回転角と高さから幅を求める
 *
 *	@param	rota		回転角度
 *	@param	height		高さ
 *
 *	@return	幅
 */
//-----------------------------------------------------------------------------
static int sub_rota_height_width_one( int rota, int height )
{
	fx32	tan;			// タンジェント計算用
	fx32	width;			// 幅計算用

	// タンジェント計算
	tan = sum_tan(rota);
	
	// タンジェントを使用し、今の角度で、高さの時の幅を求める
	width = FX_Mul(tan, height << FX32_SHIFT);
	width >>= FX32_SHIFT;
	
	return width;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	回転角からバッファにその角度で、高さのときの幅を求める
 *
 *@param	rota		回転角
 *@param	depth		幅格納ワーク
 *@param	work_num	ワークの配列要素数
 *@param	s_h			高さ開始地点（要素数分ループでまわす）
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_rota_height_width(int rota, int* depth, int work_num, int s_h)
{
	int i;
	fx32	tan;			// タンジェント計算用
	fx32	width, height;	// 幅計算用
	int st,ed;

	// タンジェント計算
	tan = sum_tan(rota);
	
	// 各Y座標での幅を代入する
	for(i=s_h;i<work_num;i++){
		// タンジェントを使用し、今の角度で、高さの時の幅を求める
		height = i<<FX32_SHIFT;
		width = FX_Mul(tan, height);
		width >>= FX32_SHIFT;
		*(depth+i) = width;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	三角形の角度と底辺から高さを求める
 *
 *@param	rota			角度
 *@param	underground		底辺の長さ
 *
 *@return	int		高さ
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_triangle_height(int rota, int underground)
{
	fx32 tan;
	fx32 ug;
	int h;

	tan = sum_tan(rota);
	ug = (underground/2) << FX32_SHIFT;
	h = FX_Div(ug ,tan);
	return h;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	分割数から１回に足す値を求める
 *
 *@param	st		開始点
 *@param	ed		終了点
 *@param	divi	分割数
 *
 *@return	int		"SUM_NUM_MINI倍にされた1回に足す値"
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_add_num(int st, int ed, int divi)
{
	int add;

	add = ed - st;
	add *= SUM_NUM_MINI;
	add /= divi;
	return add;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ座標を幅が０～２５５を超えないように足す
 *
 *@param	num1		足す値１
 *@param	num2		足す値２
 *
 *@return	int		足した値
 *
 *
 */
//-----------------------------------------------------------------------------
static int sum_add_wnd_width(int num1, int num2)
{
	int num;

	num = num1+num2;
	if(num < 0){
		num = 0;
	}
	if(num > 255){
		num = 255;
	}

	return num;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ポジションデータを足しこむ
 *
 *@param	num		足しこむ値へのポインタ	
 *@param	add		足す値へのポインタ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_add_wnd(WIPE_WND_POSITION* num, WIPE_WND_POSITION* add)
{
	num->x1 += add->x1;
	num->y1 += add->y1;
	num->x2 += add->x2;
	num->y2 += add->y2;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	データを設定する
 *
 *@param	st			開始
 *@param	ed			終了
 *@param	add			足す値
 *@param	set_st		開始座標設定データ
 *@param	set_ed		終了座標設定データ
 *@param	division	分割数
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void sum_set_wnd_position(WIPE_WND_POSITION* st, WIPE_WND_POSITION* ed, WIPE_WND_POSITION* add, const WIPE_WND_POSITION* set_st, const WIPE_WND_POSITION* set_ed, int division )
{
	// 座標を設定
	st->x1 = set_st->x1*SUM_NUM_MINI;
	st->y1 = set_st->y1*SUM_NUM_MINI;
	st->x2 = set_st->x2*SUM_NUM_MINI;
	st->y2 = set_st->y2*SUM_NUM_MINI;

	*ed = *set_ed;

	// 移動値を計算
	add->x1 = sum_add_num(set_st->x1, set_ed->x1, division);
	add->y1 = sum_add_num(set_st->y1, set_ed->y1, division);
	add->x2 = sum_add_num(set_st->x2, set_ed->x2, division);
	add->y2 = sum_add_num(set_st->y2, set_ed->y2, division);
}


//----------------------------------------------------------------------------
/**
 *@brief	フェード処理をパックした関数	初期化
 *
 *@param	wipe		ワイプワーク
 *@param	fade_flag	フェード・イン
						フェード・アウト	フラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_FadeInit(WIPE_SYS_WIPE_WORK* wipe, int fade_flag)
{
	int start, end;					// 開始、終了ブライトネス値
	WIPE_BRIGHTNESS_FADE* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof( WIPE_BRIGHTNESS_FADE ) );
	memset( wipe->wipe_work, 0, sizeof( WIPE_BRIGHTNESS_FADE ) );
	data = wipe->wipe_work;

	// ブライトネス設定
	// 開始ブライトネス値
	if( fade_flag == WIPE_FADE_IN ){
		if(wipe->color == WIPE_FADE_WHITE){
			start	= BRIGHTNESS_WHITE;
			end		= BRIGHTNESS_NORMAL;
		}else if(wipe->color == WIPE_FADE_BLACK){
			start	= BRIGHTNESS_BLACK;
			end		= BRIGHTNESS_NORMAL;
		}else{

			// 一応動くようにしておく
			start	= BRIGHTNESS_BLACK;
			end		= BRIGHTNESS_NORMAL;
			// 白黒以外の設定
			GF_ASSERT_MSG( 0, "color %x", wipe->color );
		}
	}else{
		if(wipe->color == WIPE_FADE_WHITE){
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_WHITE;
		}else if(wipe->color == WIPE_FADE_BLACK){
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_BLACK;
		}else{

			// 一応動くようにしておく
			start	= BRIGHTNESS_NORMAL;
			end		= BRIGHTNESS_BLACK;
			// 白黒以外の設定
			GF_ASSERT_MSG( 0, "color %x", wipe->color );
		}
	}
	WIPE_SetMstBrightness( wipe->disp, start );
	

	// ブライトネス変化値パラメータ設定
	data->a_count		= wipe->division;
	data->piece_sync	= wipe->piece_sync;
	data->sync_c		= 0;
	data->set_num		= start * SUM_NUM_MINI;
	data->end_num		= end * SUM_NUM_MINI;
	data->add_num		= sum_add_num( start, end, wipe->division );
	data->disp			= wipe->disp;

	wipe->sequence++;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	フェード処理をパックした関数
 *
 *@param	wipe		ワイプワーク
 *
 *@return	BOOL	終了：TRUE	続行：FALSE
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_FadePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_BRIGHTNESS_FADE* data = wipe->wipe_work;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値

	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_FadeCalcMain(data);
		if(ret == TRUE){
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;

	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ブライトネスフェード計算メイン
 *
 *	@param	data	ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_FadeCalcMain( WIPE_BRIGHTNESS_FADE* data )
{
	BOOL ret = FALSE;
	
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;
	
			data->set_num += data->add_num;
		}else{
			data->set_num = data->end_num;
			ret = TRUE;
		}
		WIPE_SetMstBrightness( data->disp, data->set_num / SUM_NUM_MINI );
	}

	return ret;
}

// Hブランク専用
static inline void wndp_setWndPosition_HBlank(int x1, int y1, int x2, int y2, int wnd_no, int disp)
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd0Position(x1,y1,x2,y2);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd0Position(x1,y1,x2,y2);
			}
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd1Position(x1,y1,x2,y2);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd1Position(x1,y1,x2,y2);
			}
		}
	}
}

static inline void set_H_WndData( WIPE_TYPE_HB_WND* shb, int v_c, int i )
{
	WIPE_TYPE_HB_WND_ONE* one;

	one = scchg_h_WndIdxDataGet(shb, i);	// インデックスのデータ取得
	wndp_setWndPosition_HBlank(one->wnd_data[0][v_c], 0, one->wnd_data[1][v_c], 192, one->wnd_no, shb->disp);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウを描くHblank関数
 *
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_Wnd(void* work)
{
	WIPE_TYPE_HB_WND* shb = (WIPE_TYPE_HB_WND*)work;
	int v_c;
	int i;

	GF_ASSERT(work);

	v_c = GX_GetVCount();

	if(v_c < 192){
		v_c ++;
		if( v_c > 191 ){
			v_c -= 192;
		}

		if( shb->wnd_data_num == 1 ){
			set_H_WndData( shb, v_c, 0 );
		}else{
			set_H_WndData( shb, v_c, 0 );
			set_H_WndData( shb, v_c, 1 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Hブランクウィンドウデータ作成
 *
 *@param	data	データ格納先
 *@param	flag	ウィンドウデータフラグ
 *@param	disp	表示面
 *@param	heap	使用するヒープ
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_WndMake(WIPE_TYPE_HB_WND* data, int flag, int disp, int heap)
{
	switch(flag){
	case WNDP_WND_0:	// どちらか片方のとき
	case WNDP_WND_1:
		data->data = sys_AllocMemory(heap, sizeof(WIPE_TYPE_HB_WND_ONE));
		data->wnd_data_num	= 1;
		data->disp			= disp;
		data->data->wnd_no	= flag;		// flag = WNDナンバー
		break;
	case 2:
		{
			int i;
			data->data = sys_AllocMemory(heap, sizeof(WIPE_TYPE_HB_WND_ONE)*2);
			data->wnd_data_num	= 2;
			data->disp			= disp;
			for(i=0;i<2;i++){			// ウィンドウデータ設定
				data->data[i].wnd_no	= i;
			}
		}
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウデータ破棄
 *
 *@param	data	破棄するウィンドウデータ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_h_WndDel(WIPE_TYPE_HB_WND* data)
{
//	VWaitTCB_Add( scchg_v_h_WndDel, data, WIPE_VBLANK_WND_DELETE_TCB );
	scchg_main_h_WndDel( data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	実際にVブランク中にワークを破棄する関数
 *
 *	@param	tcb		タスクワーク
 *	@param	work	データ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_h_WndDel( TCB_PTR tcb, void* work )
{
	WIPE_TYPE_HB_WND* data = work;

	scchg_main_h_WndDel( data );

	TCB_Delete(tcb);
}

//----------------------------------------------------------------------------
/**
 *	@brief	実際にワークを破棄する関数
 *
 *	@param	data 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_main_h_WndDel( WIPE_TYPE_HB_WND* data )
{
	sys_FreeMemoryEz(data->data);	
	data->data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウナンバーのウィンドウデータを取得
 *
 *@param	wnd_no	取得するウィンドウナンバー	
 *
 *@return	ウィンドウデータ	無いときNULL
 *
 *
 */
//-----------------------------------------------------------------------------
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndNoDataGet(WIPE_TYPE_HB_WND* data, int wnd_no)
{
	int i;

	for(i=0;i<data->wnd_data_num;i++){
		if(data->data[i].wnd_no == wnd_no){
			return (data->data + i);
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	インデックスのウィンドウデータ取得
 *
 *@param	data	取得先
 *@param	idx		インデックス
 *
 *@return	ウィンドウデータ	無いときNULL
 *
 *
 */
//-----------------------------------------------------------------------------
static WIPE_TYPE_HB_WND_ONE* scchg_h_WndIdxDataGet(WIPE_TYPE_HB_WND* data, int idx)
{
	GF_ASSERT(data->wnd_data_num > idx);

	return (data->data + idx);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	メインループで計算したウィンドウの形のバッファを
 *			反映テーブルに代入
 *
 *@param	tcb		タスクポインタ
 *@param	work	データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndSwap(TCB_PTR tcb, void* work)
{
	WIPE_TYPE_HB_WND*	swc = (WIPE_TYPE_HB_WND*)work;
	WIPE_TYPE_HB_WND_ONE* one;
	int i;

	for(i=0;i<swc->wnd_data_num;i++){
		one = scchg_h_WndIdxDataGet(swc, i);		// インデックスのデータ取得
		memcpy(one->wnd_data, one->wnd_tmp, sizeof(short)*2*192);	// sizeof(short)*2*192
	}
	TCB_Delete( tcb );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ動作の後処理
 *
 *@param	flag		WIPE_FADE_IN:フェードイン	WIPE_FADE_OUT:フェードアウト
 *@param	wnd_sys		ウィンドウVblank処理ワーク
 *@param	disp		表示面
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndEnd(int flag, WNDP_SYS_PTR wnd_sys, int disp)
{
	if(flag == WIPE_FADE_IN){
		// フェード・インが終了したら使用したウィンドウの表示をオフ
		WNDP_V_SetVisibleWnd(wnd_sys, GX_WNDMASK_NONE, disp);

	}else{

		// ウィンドウ0を画面いっぱいに広げる
		WNDP_V_SetVisibleWnd(wnd_sys, GX_WNDMASK_W0, disp);
		WNDP_V_SetWndInsidePlane(wnd_sys, GX_BLEND_ALL, FALSE, 0, disp);
		WNDP_V_SetWndPosition(wnd_sys, 0,0,0,0,0, disp);	
		WNDP_V_SetWndOutsidePlane(wnd_sys, GX_BLEND_PLANEMASK_BD, FALSE, disp);	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウを使用できる状態にする
 *
 *@param	wnd_sys		ウィンドウVblank設定システム用ワーク
 *@param	in_wnd		ウィンドウ内設定
 *@param	out_wnd		ウィンドウ外設定
 *@param	wnd_no		ウィンドウナンバー
 *@param	disp		ウィンドウ表示面
 *@param	x1			ウィンドウ座標
 *@param	y1
 *@param	x2
 *@param	y2
 *@param	fade_flg	フェードフラグ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndSetUp(WNDP_SYS_PTR wnd_sys, int in_wnd, int out_wnd, int wnd_no, int disp, int x1, int y1, int x2, int y2, int fade_flg)
{
	// ウィンドウの内外を設定
	if( fade_flg == WIPE_FADE_IN ){
		// フェードイン
		WNDP_SetWndInsidePlane(in_wnd, FALSE, wnd_no, disp);
		WNDP_SetWndOutsidePlane(out_wnd, FALSE, disp);
		WNDP_SetWndPosition(x1,y1,x2,y2, wnd_no, disp);
	}else{
		// フェードアウト
		WNDP_V_SetWndInsidePlane(wnd_sys, in_wnd, FALSE, wnd_no, disp);
		WNDP_V_SetWndOutsidePlane(wnd_sys, out_wnd, FALSE, disp);
		WNDP_V_SetWndPosition(wnd_sys, x1,y1,x2,y2, wnd_no, disp);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief		ウィンドウ表示非表示設定
 *
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	plane		表示ウィンドウ面
 *	@param	disp		表示画面
 *	@param	fade_flg	フェードイン・アウトフラグ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndVisible(WNDP_SYS_PTR wnd_sys, int plane, int disp, int fade_flg)
{
	if(fade_flg == WIPE_FADE_IN){

		WNDP_SetVisibleWnd( plane, disp );
	}else{

		WNDP_V_SetVisibleWnd(wnd_sys, plane, disp);
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	縦方向　Hブランク使用　ウィンドウ動作
 *
 *	@param	p_wnddata	ワーク
 *	@param	disp		面
 *	@param	data_num	ウィンドウ使用数	(1 or 2)
 *	@param	wnd_no0		ワーク０のウィンドウナンバー
 *	@param	wnd_no1		ワーク１のウィンドウナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWndInit( WIPE_TYPE_WND_VMOVE* p_wnddata, int disp, int data_num, int wnd_no0, int wnd_no1 )
{
	memset( p_wnddata, 0, sizeof(WIPE_TYPE_WND_VMOVE) );

	if( data_num == 1 ){
		p_wnddata->data[0].wnd_no	= wnd_no0;
		p_wnddata->wnd_data_num		= data_num;
		p_wnddata->disp				= disp;
	}else{
		p_wnddata->data[0].wnd_no = wnd_no0;
		p_wnddata->data[1].wnd_no = wnd_no1;
		p_wnddata->wnd_data_num		= data_num;
		p_wnddata->disp				= disp;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	スワップバッファリクエスト
 *
 *	@param	p_wnddata	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_SwapReq( WIPE_TYPE_WND_VMOVE* p_wnddata )
{
	VWaitTCB_Add(scchg_h_VMoveWnd_Swap, p_wnddata, WIPE_VBLANK_WND_SWAP_TCB );
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作開始　Vブランクがきたら開始します。
 *
 *	@param	p_wnddata ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Start( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap )
{
	// Hblank関数を設定
	WIPE_V_HBlankInit(p_wipehb, p_wnddata, scchg_h_VMoveWnd_Main, p_wnddata->disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作終了
 *
 *	@param	p_wnddata	Vブランクがきたら終了します。
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_End( WIPE_HBLANK* p_wipehb, WIPE_TYPE_WND_VMOVE* p_wnddata, u32 heap )
{
	WIPE_V_HBlankDelete(p_wipehb, p_wnddata->disp, heap);
}


//----------------------------------------------------------------------------
/**
 *	@brief	スワップバッファ
 *
 *	@param	tcb			タスクポインタ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Swap( TCB_PTR tcb, void* p_work )
{
	WIPE_TYPE_WND_VMOVE* p_wnddata = p_work;
	int i;
	
	for( i=0; i<2; i++ ){
		memcpy( p_wnddata->data[i].in_out_read, p_wnddata->data[i].in_out_write, sizeof(u8)*192 );
	}

	TCB_Delete( tcb );
}

static inline void wndp_SetWndOutsidePlane_HBlank( int wnd, BOOL effect, int disp )
{
	if(disp == WNDP_DISP_MAIN){
		if( GX_IsHBlank() ){
			G2_SetWndOutsidePlane(wnd, effect);
		}
	}else{
		if( GX_IsHBlank() ){
			G2S_SetWndOutsidePlane(wnd, effect);
		}
	}
}
static inline void wndp_SetWndInsidePlane_HBlank( int wnd, BOOL effect, int wnd_no, int disp )
{
	if(wnd_no == WNDP_WND_0){
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd0InsidePlane(wnd, effect);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd0InsidePlane(wnd, effect);
			}
		}
	}else{
		if(disp == WNDP_DISP_MAIN){
			if( GX_IsHBlank() ){
				G2_SetWnd1InsidePlane(wnd, effect);
			}
		}else{
			if( GX_IsHBlank() ){
				G2S_SetWnd1InsidePlane(wnd, effect);
			}
		}
	}
}

static inline void set_H_VMoveWndData( WIPE_TYPE_WND_VMOVE* shb, int v_c, int i )
{
	WIPE_TYPE_WND_VMOVE_HDATA* one;

	one = &shb->data[ i ];
	if( one->in_out_read[ v_c ] == WIPE_WND_VMOVE_INWND ){
		wndp_SetWndOutsidePlane_HBlank( GX_BLEND_ALL, TRUE,  shb->disp );
		wndp_SetWndInsidePlane_HBlank( GX_BLEND_PLANEMASK_BD, TRUE, one->wnd_no, shb->disp );
	}else{
		wndp_SetWndOutsidePlane_HBlank( GX_BLEND_PLANEMASK_BD, TRUE,  shb->disp );
		wndp_SetWndInsidePlane_HBlank( GX_BLEND_ALL, TRUE, one->wnd_no, shb->disp );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	Hブランクデータ設定
 *
 *	@param	p_work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_h_VMoveWnd_Main( void* p_work )
{
	WIPE_TYPE_WND_VMOVE* shb = (WIPE_TYPE_WND_VMOVE*)p_work;
	int v_c;
	int i;

	GF_ASSERT(p_work);

	v_c = GX_GetVCount();

	if(v_c < 192){
		
		v_c ++;
		if( v_c > 191 ){
			v_c -= 192;
		}
		
		if( shb->wnd_data_num == 1 ){
			set_H_VMoveWndData( shb, v_c, 0 );
		}else{
			set_H_VMoveWndData( shb, v_c, 0 );
			set_H_VMoveWndData( shb, v_c, 1 );
		}
	}
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	ウィンドウ動作パック初期化関数
 *
 *	@param	wipe	ワイプデータ
 *	@param	param	ウィンドウ動作データ
 *
 * @return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMovePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram )
{
	WIPE_TYPE_WND_MOVE* wwm;

	// フェード開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_MOVE));
	
	wwm = (WIPE_TYPE_WND_MOVE*)wipe->wipe_work;
	
	scchg_WndMoveInit(wwm, pram, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
	
	// ウィンドウオン
	if(pram->wnd_no == 0){
		scchg_WndVisible(wipe->wnd_sys, GX_WNDMASK_W0, wwm->disp, wwm->fade_flg);
	}else{
		scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W1, wwm->disp, wwm->fade_flg);
	}
	
	wipe->sequence++;		// メイン動作へ
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ動作パック
 *
 *@param	wipe	ワイプデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMovePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_MOVE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_MOVE*)wipe->wipe_work;
	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_WndMoveMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;

	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	２つのウィンドウを同時に動かす関数の初期化
 *
 *@param	wipe		ワイプ構造体
 *@param	pram1		ウィンドウ０の引数データ
 *@param	pram2		ウィンドウ１の引数データ
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMoveDoublePackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_MOVE_FP* pram1, const WIPE_TYPE_WND_MOVE_FP* pram2)
{
	WIPE_TYPE_WND_DMOVE* wwm;

	// フェード開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DMOVE));
	wwm = (WIPE_TYPE_WND_DMOVE*)wipe->wipe_work;
	scchg_WndMoveInit(&wwm->wnd0, pram1, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
	scchg_WndMoveInit(&wwm->wnd1, pram2, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys);

	scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W0|GX_WNDMASK_W1, wipe->disp, wwm->wnd0.fade_flg);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	２つのウィンドウを同時に動かす関数の初期化
 *
 *@param	wipe		ワイプ構造体
 *	
 *@retval	TRUE		終了
 *@retval	FALSE		続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMoveDoublePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DMOVE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_DMOVE*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndMoveMain(&wwm->wnd0);
		ret += scchg_WndMoveMain(&wwm->wnd1);
		if(ret == 2){
			scchg_WndEnd(wwm->wnd0.fade_flg, wipe->wnd_sys, wipe->disp);
//			scchg_WndEnd(wwm->wnd1.fade_flg, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ変形処理の初期化
 *
 *@param	data		データ格納先
 *@param	param		ウィンドウ変形データ
 *@param	division	処理分割数
 *@param	piece_sync	１片のシンク数
 *@param	disp		表示面
 *@param	wnd_sys		ウィンドウシステムポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndMoveInit(WIPE_TYPE_WND_MOVE* data, const WIPE_TYPE_WND_MOVE_FP* pram, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys)
{
	// 座標を設定
	sum_set_wnd_position(&data->st, &data->ed, &data->add, &pram->st, &pram->ed, division);

	// データ設定
	data->disp			= disp;
	data->wnd_no		= pram->wnd_no;
	data->a_count		= division;
	data->piece_sync	= piece_sync;
	data->sync_c		= 0;
	data->wnd_sys		= wnd_sys;
	data->fade_flg		= pram->fade_flg;

	// ウィンドウの内外を設定
	scchg_WndSetUp(wnd_sys, pram->in_wnd, pram->out_wnd, pram->wnd_no, disp,
			pram->st.x1,pram->st.y1,
			pram->st.x2,pram->st.y2,
			data->fade_flg);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウの形を変形させる
 *
 *@param	data	ウィンドウ変形データ
 *
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndMoveMain(WIPE_TYPE_WND_MOVE* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;
	
			// 足し算
			sum_add_wnd(&data->st, &data->add);
		}else{
			WNDP_V_SetWndPosition(data->wnd_sys, data->ed.x1,data->ed.y1,data->ed.x2,data->ed.y2, data->wnd_no, data->disp);

			return TRUE;
		}

		WNDP_V_SetWndPosition(data->wnd_sys, data->st.x1/SUM_NUM_MINI,data->st.y1/SUM_NUM_MINI,data->st.x2/SUM_NUM_MINI,data->st.y2/SUM_NUM_MINI, data->wnd_no, data->disp);//*/
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ウィンドウで円を描くシステム
 *
 *	@param	wipe	ワイプワーク
 *	@param	param	初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCirclePackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CIRCLE_FP* param )
{
	WIPE_TYPE_WND_CIRCLE* wwm;
	
	// ワイプ開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_CIRCLE));
	wwm = (WIPE_TYPE_WND_CIRCLE*)wipe->wipe_work;
	scchg_WndCircleInit(wwm, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);

	// メイン動作へ
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウで円を描くシステム
 *
 *@param	wipe		ワイプワーク
 *
 *@return	BOOL		TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCirclePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_CIRCLE* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_CIRCLE*)wipe->wipe_work;
	
	switch(wipe->sequence){
	case WIPE_MAIN:
		ret = scchg_WndCircleMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_circle);	// ウィンドウ設定データ破棄
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
		
	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	円描画システムを初期化
 *
 *@param	data			データ格納先
 *@param	param			ワイプデータ
 *@param	division		処理分割数
 *@param	piece_sync		１片のシンク数
 *@param	disp			表示面
 *@param	wnd_sys			ウィンドウシステムポインタ
 *@param	heap			使用するヒープID
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleInit(WIPE_TYPE_WND_CIRCLE* data, const WIPE_TYPE_WND_CIRCLE_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap)
{
	int add_r;
	WIPE_TYPE_HB_WND_ONE* one;

	// 変化値を求める
	add_r = sum_add_num(param->r, param->e_r, division);

	// データを設定
	scchg_h_WndMake(&data->hb_circle, param->wnd_no, disp, heap);
	data->r					= param->r*SUM_NUM_MINI;
	data->x					= param->x;
	data->y					= param->y;
	data->add_r				= add_r;
	data->a_count			= division;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndCircleSum(data);	// 1回計算する
	VWaitTCB_Add(scchg_WndSwap,&data->hb_circle, WIPE_VBLANK_WND_SWAP_TCB );

	// ウィンドウ設定
	one = scchg_h_WndIdxDataGet(&data->hb_circle, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, param->wnd_no, disp,
			one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);

	// ウィンドウオン
	if(param->wnd_no == 0){
		scchg_WndVisible( wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg );
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}
	
	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_circle, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	円描画メイン処理
 *
 *@param	data	ウィンドウ変形データ
 *
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCircleMain(WIPE_TYPE_WND_CIRCLE* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->r += data->add_r;	
			scchg_WndCircleSum(data);
			VWaitTCB_Add(scchg_WndSwap,&data->hb_circle, WIPE_VBLANK_WND_SWAP_TCB );
		}else{

			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_circle.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	円データ計算サブ関数
 *
 *@param	c_r		半径（SUM_NUM_MINIでかけた値）
 *@param	c_x		中心座標
 *@param	c_y		中心座標
 *@param	n_h		今の高さ
 *@param	st		ウィンドウ横の開始点
 *@param	ed		ウィンドウ横の終了点
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleSumSub(int c_r, int c_x, int c_y, int n_h, int* st, int* ed)
{
	fx32 r;			// 半径
	fx32 height;	// 高さ
	fx32 width;		// 幅

	// ３平方の定理で今の高さから円の幅を求める
	
	r = c_r / SUM_NUM_MINI;

	height = n_h - c_y;
	if(height < 0){
		height = -height;
	}
	
	if(height >= r){
		*st = 0;
		*ed = 0;
	}else{
		// 半径から幅を求める
		height <<= FX32_SHIFT;
		r <<= FX32_SHIFT;
		width = FX_Sqrt(FX_Mul(r,r) - FX_Mul(height,height));
		width >>= FX32_SHIFT;

		// ウィンドウの開始点を設定
		*st = c_x - width;
		if(*st < 0){
			*st = 0;
		}
		*ed = *st + (width*2);
		if(*ed > 255){
			*ed = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	円データの計算を行う
 *
 *@param	work		円描画システムのデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCircleSum(WIPE_TYPE_WND_CIRCLE* work)
{
	WIPE_TYPE_HB_WND* shb = &work->hb_circle;
	int i;			// ループ用
	int st;			// ウィンドウ開始点
	int ed;			// ウィンドウ終了点
	int roop_end;
	WIPE_TYPE_HB_WND_ONE* one;

	// インデックス０のウィンドウデータを取得
	one = scchg_h_WndIdxDataGet(shb, 0);

	// 半径が画面内にあるときは
	// 中心まで幅を求めたら下半分はコピーするようにする
	for(i=0;i < 192;i++){
		if(i <= work->y){		// 半径までは普通の求める
			scchg_WndCircleSumSub(work->r, work->x, work->y, i, &st, &ed);
		}else{
			if(i <= (work->y*2)){		// 半径から半径の２倍までは,コピー
				st = one->wnd_tmp[0][(work->y*2)-i];
				ed = one->wnd_tmp[1][(work->y*2)-i];
			}else{				// その他は普通に求める
				scchg_WndCircleSumSub(work->r, work->x, work->y, i, &st, &ed);
			}
		}
		
		one->wnd_tmp[0][i] = st;
		one->wnd_tmp[1][i] = ed;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウをカーテンのように表示する初期化関数
 *
 *@param	wipe		ワイプワーク
 *@param	param		関数引数
 *
 *	rota		開始角度		角度は０～８９でお願いします
 *	e_rota		終了角度		またラジアン値である必要があります。
 *	wnd_no		ウィンドウナンバー
 *	in_wnd		ウィンドウ内の面
 *	out_wnd		ウィンドウ外の面
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainPackInit( WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_CURTAIN_FP* param)
{
	WIPE_TYPE_WND_CURTAIN* wwm;

	// フェード開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_CURTAIN));
	wwm = (WIPE_TYPE_WND_CURTAIN*)wipe->wipe_work;
	scchg_WndCurtainInit(wwm, param,wipe->division, wipe->piece_sync,  wipe->disp,  wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウをカーテンのように表示する
 *
 *@param	wipe		ワイプワーク
 *
 *@return	BOOL	TRUE：終了	FALSE：続行
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCurtainPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_CURTAIN* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_CURTAIN*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndCurtainMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_c);
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウでのカーテン描画開始
 *
 *@param	data		カーテン描画データ
 *@param	param		カーテン動作データ
 *@param	division	処理の分割数
 *@param	piece_sync	１片のシンク数
 *@param	disp		ウィンドウ表示面
 *@param	wnd_sys		ウィンドウVblank処理システムのワーク
 *@param	p_wipehb	ワイプHブランクワーク
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainInit(WIPE_TYPE_WND_CURTAIN* data, const WIPE_TYPE_WND_CURTAIN_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one;
	
	data->rota_add = sum_add_num(param->rota, param->e_rota, division);

	// データ設定
	scchg_h_WndMake(&data->hb_c, param->wnd_no, disp, heap);
	data->rota		= param->rota*SUM_NUM_MINI;
	data->a_count	= division;
	data->piece_sync = piece_sync;
	data->sync_c	= 0;
	data->wnd_sys	= wnd_sys;	
	data->p_wipehb	= p_wipehb;
	data->heap		= heap;
	data->fade_flg	= param->fade_flg;
	
	scchg_WndCurtainSum(data);	// 1回計算する
	VWaitTCB_Add(scchg_WndSwap,&data->hb_c, WIPE_VBLANK_WND_SWAP_TCB );

	// ウィンドウ表示設定
	// ウィンドウ設定
	one = scchg_h_WndIdxDataGet(&data->hb_c, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd,
			param->wnd_no, disp, one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);

	// ウィンドウオン
	if(param->wnd_no == 0){
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}
	

	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_c, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウカーテン表示のメイン処理
 *
 *@param	data	ウィンドウ動作データ
 *	
 *@return	BOOL	TRUE：終了	FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndCurtainMain(WIPE_TYPE_WND_CURTAIN* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->rota += data->rota_add;
			scchg_WndCurtainSum(data);		// 計算
			VWaitTCB_Add(scchg_WndSwap,&data->hb_c, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// 処理終了
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_c.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウをカーテンのように表示するデータを計算
 *
 *@param	work		ウィンドウ動作データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndCurtainSum(WIPE_TYPE_WND_CURTAIN* work)
{
	int i;
	int st, ed;
	int width[192];
	WIPE_TYPE_HB_WND_ONE* one;

	// インデックス０のウィンドウデータを取得
	one = scchg_h_WndIdxDataGet(&work->hb_c, 0);

	// 角度から各高さでの幅を求める
	sum_rota_height_width(work->rota/SUM_NUM_MINI, width, 192, 0);

	// 各Y座標での幅を代入する
	for(i=0;i<192;i++){
		one->wnd_tmp[0][i] = sum_add_wnd_width(128, -width[i]);
		one->wnd_tmp[1][i] = sum_add_wnd_width(128, width[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドアフェードパック関数	初期化関数
 *
 *@param	wipe		ワイプワーク
 *@param	param		ドアデータ
 *	s_d			開始開き角度	（ROTA_NUM(0)～ROTA_NUM(90)）
 *	e_d			終了開き角度	（ROTA_NUM(0)～ROTA_NUM(90)）
 *	wnd_no		使用ウィンドウナンバー
 *	in_wnd		ウィンドウ内面設定
 *	out_wnd		ウィンドウ外面設定
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DOOR_FP* param)
{
	WIPE_TYPE_WND_DOOR* wwm;
	// フェード開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DOOR));
	wwm = (WIPE_TYPE_WND_DOOR*)wipe->wipe_work;
	scchg_WndDoorInit(wwm, param, wipe->division, wipe->piece_sync,  wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドアフェードパック関数
 *
 *@param	wipe		ワイプワーク
 *
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDoorPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DOOR* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_DOOR*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndDoorMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_h_WndDel(&wwm->hb_d);
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウでドアフェード初期化
 *
 *@param	data		データ格納先
 *@param	param		ドア動作データ
 *@param	division	処理分割数
 *@param	piece_sync	１片のシンク数
 *@param	disp		ウィンドウ表示面
 *@param	wnd_no		使用ウィンドウナンバー
 *@param	wnd_sys		ウィンドウVblank設定ワーク
 *@param	wipe_hb		ワイプHブランクワーク
 *@param	heap		使用するヒープ
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorInit(WIPE_TYPE_WND_DOOR* data, const WIPE_TYPE_WND_DOOR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int add_num;
	WIPE_TYPE_HB_WND_ONE* one;

	// １回で開くドアの距離を計算
	add_num	= (param->e_d - param->s_d);
	add_num	/= division;

	// データ設定
	scchg_h_WndMake(&data->hb_d, param->wnd_no, disp, heap);
	data->open_max		= 128*FX32_ONE;	// 横幅の半分の値で考える
	data->open_r		= param->s_d;
	data->open_r_a		= add_num;
	data->a_count	= division;
	data->piece_sync= piece_sync;
	data->sync_c	= 0;
	data->wnd_sys	= wnd_sys;
	data->p_wipehb	= p_wipehb;
	data->heap		= heap;
	data->fade_flg	= param->fade_flg;

	// ドア計算
	scchg_WndDoorSum(data);
	VWaitTCB_Add(scchg_WndSwap,&data->hb_d, WIPE_VBLANK_WND_SWAP_TCB );
	
	// ウィンドウ設定
	one = scchg_h_WndIdxDataGet(&data->hb_d, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 
			param->wnd_no, disp,
			one->wnd_tmp[0][96], 0, one->wnd_tmp[1][96], 192,
			data->fade_flg);	// ９６からにするべし

	// ウィンドウオン
	if(param->wnd_no == 0){
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W1, disp, data->fade_flg);
	}

	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_d, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドアフェードメイン
 *
 *@param	data		ドアデータ
 *
 *@return	BOOL		TRUE：終了		FALSE：失敗
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDoorMain(WIPE_TYPE_WND_DOOR* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;
			data->open_r += data->open_r_a;
			scchg_WndDoorSum(data);		// 計算
			VWaitTCB_Add(scchg_WndSwap, &data->hb_d, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// 処理終了
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_d.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ドア型のウィンドウ計算
 *
 *@param	work		ドアデータ
 *
 *@return	noen
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDoorSum(WIPE_TYPE_WND_DOOR* work)
{
	int i;
	int tri_h;		// 奥行き表現の２等辺三角形の高さ
	int rota;		// 奥行き表現の２等辺三角形の頂点の角度
	int tri_data[192];	// 奥行き表現の２等辺三角形の形データ
	int tri_n;		// tri_dataテーブルの要素数
	int h_open;		// 今の開いている値の半分
	int set_w;		// ウィンドウに設定する幅
	int st, ed;		// 開始点、終了点
	WIPE_TYPE_HB_WND_ONE* one;	// ウィンドウ設定データ

	// インデックス０のウィンドウを取得
	one = scchg_h_WndIdxDataGet(&work->hb_d, 0);

	// 今の開く値を求める
	h_open = FX_Mul(FX_SinIdx(work->open_r), work->open_max);
	h_open >>= FX32_SHIFT;
	
	rota = h_open*2;						// 今の開く値を求める
	rota = rota / WIPE_DOOR_ROTA_NUM;		// ２等辺三角形の再度の角度を求める
	rota += 1;								// 90度回避
	rota = 180 - (rota*2);					// 三角形の頂点の角度を求める
	rota = ROTA_NUM(rota);					// FXの計算で使用する角度の単位にする
	rota /= 2;								// 幅を求めるため半分の角度にする
	tri_h = sum_triangle_height(rota, 256);	// 三角形の高さを取得
	tri_h >>= FX32_SHIFT;					// fx32からintへ
	GF_ASSERT(tri_h < 192);

	sum_rota_height_width(rota, tri_data, tri_h, 0);	// 三角形の形データを求める
	
	// ドア型のウィンドウデータを作成
	for(i=0;i<96;i++){

		// ウィンドウに設定する幅を求める
		tri_n = tri_h - (i+1);
		set_w = h_open;
		if(tri_n > 0){
			if(tri_data[tri_n] > set_w){
				set_w = tri_data[tri_n];
			}
		}

		// 開始点終了点を求める
		st = sum_add_wnd_width(128, -set_w);
		ed = sum_add_wnd_width(128, set_w);

		// ウィンドウに設定する
		one->wnd_tmp[0][i] = st;
		one->wnd_tmp[1][i] = ed;
		one->wnd_tmp[0][191 - i] = st;
		one->wnd_tmp[1][191 - i] = ed;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	１ウィンドウ分割処理フェードパック
 *
 *	@param	wipe		ワイプワーク
 *	@param	param		分割フェードデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionPackInit(WIPE_SYS_WIPE_WORK* wipe, const WIPE_TYPE_WND_DIVI_FP* param)
{
	WIPE_TYPE_WND_DIVI* wwm;
	// フェード開始
	wipe->wipe_work = sys_AllocMemory(wipe->heap, sizeof(WIPE_TYPE_WND_DIVI));
	wwm = (WIPE_TYPE_WND_DIVI*)wipe->wipe_work;
	scchg_WndDivisionInit(wwm, param, wipe->division, wipe->piece_sync,  wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap);
	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１ウィンドウ分割処理フェードパック
 *
 *@param	wipe		ワイプワーク
 *	
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDivisionPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_DIVI* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_DIVI*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndDivisionMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndDivisionEnd(wwm);	// 分割ウィンドウデータ破棄
		scchg_h_WndDel(&wwm->hb_divi);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	１ウィンドウ分割フェード初期化
 *
 *@param	data		データ格納先
 *@param	param		１ウィンドウ分割データ
 *@param	division	処理分割数
 *@param	piece_sync	分割した１片のシンク数
 *@param	disp		ウィンドウ表示面
 *@param	wnd_sys		ウィンドウVblank設定システムワーク
 *@param	p_wipehb	ワイプ用Hブランクワーク
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionInit(WIPE_TYPE_WND_DIVI* data, const WIPE_TYPE_WND_DIVI_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int i;
	WIPE_TYPE_HB_WND_ONE* one;
	
	// 分割データ作成
	// メモリアロック
	data->piece_tbl = sys_AllocMemory(heap, sizeof(WIPE_TYPE_WND_D_PIECE)*param->divi_num);
	GF_ASSERT(data->piece_tbl != NULL);
	data->piece_num = param->divi_num;

	// データ格納
	for(i=0;i<param->divi_num;i++){

		sum_set_wnd_position(&data->piece_tbl[i].st, &data->piece_tbl[i].ed, &data->piece_tbl[i].add, (param->p_st+i), (param->p_ed+i), division);
	}

	// データ設定
	scchg_h_WndMake(&data->hb_divi, param->wnd_no, disp, heap);
	data->a_count		= division;
	data->piece_sync	= piece_sync;
	data->sync_c		= 0;
	data->wnd_sys		= wnd_sys;
	data->p_wipehb		= p_wipehb;
	data->heap			= heap;
	data->fade_flg		= param->fade_flg;

	// 分割計算
	scchg_WndDivisionSum(data);
	VWaitTCB_Add(scchg_WndSwap,&data->hb_divi, WIPE_VBLANK_WND_SWAP_TCB );
	
	// ウィンドウ設定
	one = scchg_h_WndIdxDataGet(&data->hb_divi, 0);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, param->wnd_no, disp,
			one->wnd_tmp[0][0], 0, one->wnd_tmp[1][0], 192,
			data->fade_flg);	// ９６からにするべし

	// ウィンドウオン
	if(param->wnd_no == 0){
		scchg_WndVisible(data->wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg);
	}else{
		scchg_WndVisible(data->wnd_sys,GX_WNDMASK_W1, disp, data->fade_flg);
	}

	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb_divi, scchg_h_Wnd, disp, heap);
}
	

//----------------------------------------------------------------------------
/**
 *
 *@brief	1ウィンドウを分割してそれぞれで動かす
 *
 *@param	data		分割したウィンドウデータ
 *
 *@return	BOOL		TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndDivisionMain(WIPE_TYPE_WND_DIVI* data)
{
	
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count - 1) > 0){
			data->a_count--;

			// 動かす
			scchg_WndDivisionMainSub(data);			
			
			scchg_WndDivisionSum(data);		// 計算
			VWaitTCB_Add(scchg_WndSwap,&data->hb_divi, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// 処理終了
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb_divi.disp, data->heap);
			return TRUE;
		}
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	各々の分割データを破棄する
 *
 *@param	data	ウィンドウ分割データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionEnd(WIPE_TYPE_WND_DIVI* data)
{
	// 確保したメモリを解放
	sys_FreeMemoryEz( data->piece_tbl);
	data->piece_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	各々のデータをウィンドウの設定データに変換
 *
 *@param	work		１ウィンドウ分割データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionSum(WIPE_TYPE_WND_DIVI* work)
{
	int i;		// ループ用
	WIPE_TYPE_HB_WND_ONE* one;
	
	one = scchg_h_WndIdxDataGet(&work->hb_divi, 0);
	memset(one->wnd_tmp, 0, 768);	// クリア

	// 要素０が一番優先順位が高くなるように最後の要素からデータを設定していく
	for(i = (work->piece_num-1); i >= 0; i--){
		scchg_WndDivisionSumSub(&work->hb_divi, &work->piece_tbl[i].st);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ウィンドウ分割データ計算サブ関数
 *
 *@param	hb_divi		Hブランク設定データ
 *@param	set			設定データ
 *
 *@return	none
 *
 * 設定する
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionSumSub(WIPE_TYPE_HB_WND* hb_divi, WIPE_WND_POSITION* set)
{
	int i;		// ループ用
	WIPE_TYPE_HB_WND_ONE* one;
	WIPE_WND_POSITION set_data;
	
	one = scchg_h_WndIdxDataGet(hb_divi, 0);

	set_data.x1 = set->x1 / SUM_NUM_MINI;
	set_data.y1 = set->y1 / SUM_NUM_MINI;
	set_data.x2 = set->x2 / SUM_NUM_MINI;
	set_data.y2 = set->y2 / SUM_NUM_MINI;

	for( i = set_data.y1; i < set_data.y2; i++ ){
		one->wnd_tmp[0][i] = set_data.x1;
		one->wnd_tmp[1][i] = set_data.x2;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	メイン関数の内部関数
 *
 *@param	data		データ
 *
 *@return	none
 *
 * 実際に分割されたそれぞれのウィンドウを動かす
 *
 */
//-----------------------------------------------------------------------------
static void scchg_WndDivisionMainSub(WIPE_TYPE_WND_DIVI* data)
{
	int i;		// ループ用

	// それぞれ動かす
	for(i=0;i<data->piece_num;i++){
		sum_add_wnd(&data->piece_tbl[i].st, &data->piece_tbl[i].add);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリュー関数初期化
 *
 *	@param	wipe		ワイプ
 *	@param	param		パラメータ
 *	@param	flag		フェードインアウトフラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_SCREW_FP* param)
{
	WIPE_TYPE_WND_SCREW* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_SCREW) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_SCREW) );
	data = wipe->wipe_work;
	scchg_WndScrewInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリューワイプメイン処理
 *
 *	@param	wipe		ワイプ
 *	
 *	@retval	TRUE		終了
 *	@retval	FALSE		続行
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndScrewPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_SCREW* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_SCREW*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndScrewMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndScrewEnd(wwm);	// ウィンドウデータ破棄
		scchg_h_WndDel(&wwm->hb);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリュー初期化関数
 *
 *	@param	data		ワーク
 *	@param	param		パラメータ
 *	@param	division	分割数
 *	@param	piece_sync	シンク数
 *	@param	disp		画面
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	p_wipehb	Hブランク関数システム
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewInit(WIPE_TYPE_WND_SCREW* data, WIPE_TYPE_WND_SCREW_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;

	// 変化値を求める
	data->screw.rota		= 0;
	data->screw.s_rota		= param->s_rota;
	data->screw.add_num_rota = param->e_rota - param->s_rota;

	// データを設定
	scchg_h_WndMake(&data->hb, 2, disp, heap);
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndScrewOneAdd(&data->screw, data->a_count, data->a_count_max);
	scchg_WndScrewSum(data);	// 1回計算する
	VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );

	// ウィンドウ設定
	one0 = scchg_h_WndIdxDataGet(&data->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&data->hb, 1);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 0, disp,
			one0->wnd_tmp[0][0], 0, one0->wnd_tmp[1][0], 192,
			data->fade_flg);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 1, disp,
			one1->wnd_tmp[0][0], 0, one1->wnd_tmp[1][0], 192,
			data->fade_flg);

	// ウィンドウオン
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0|GX_WNDMASK_W1, disp, data->fade_flg );

	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリューメイン関数
 *
 *	@param	data	ワーク
 *
 *	@retval	TRUE		終了
 *	@retval	FALSE		続行
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndScrewMain(WIPE_TYPE_WND_SCREW* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// 動かす
			scchg_WndScrewOneAdd(&data->screw, data->a_count, data->a_count_max);
			scchg_WndScrewSum(data);		// 計算
			VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// 処理終了
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb.disp, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリューワーク破棄関数
 *
 *	@param	data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewEnd(WIPE_TYPE_WND_SCREW* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	スクリューデータ計算関数
 *
 *	@param	work	ワーク
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewSum(WIPE_TYPE_WND_SCREW* work)
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	u16 rota_num;
	int x1, x2;
	int i;


	// ウィンドウ0左側	ウィンドウ1 右側で計算します
	// ウィンドウテーブルに値を設定
	// ウィンドウ0は 終点128  始点128-(y*tan(rota))
	// ウィンドウ1は 始点128  終点128+(y*tan(rota))
	// 角度90以上になったら
	// ウィンドウ0は 終点128-(y*tan(rota))  始点0
	// ウィンドウ1は 始点128+(y*tan(rota))  終点255
	
	rota_num = work->screw.rota % FX_GET_ROTA_NUM( 90 );
	
	one0 = scchg_h_WndIdxDataGet(&work->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&work->hb, 1);
	// 考えやすいので、ウィンドウ1の方で計算して
	// 計算結果をサブにXY反転して設定する
	for( i=0; i<96; i++ ){
		if( work->screw.rota < FX_GET_ROTA_NUM( 90 ) ){
			x1 = 128;

			// 回転角と高さから作られる３角形の幅を求める
			x2 = sub_rota_height_width_one( rota_num, (96 - i) );

			if( x2 > 127 ){
				x2 = 127;
			}
			
			one0->wnd_tmp[0][191 - i] = x1 - x2;
			one0->wnd_tmp[1][191 - i] = x1;

			one1->wnd_tmp[0][i] = x1;
			one1->wnd_tmp[1][i] = x1 + x2;
		}else{
			one0->wnd_tmp[0][191 - i] = 0;
			one0->wnd_tmp[1][191 - i] = 128;

			one1->wnd_tmp[0][i] = 128;
			one1->wnd_tmp[1][i] = 255;
		}
	}

	for( i=96; i<192; i++ ){
		if( work->screw.rota < FX_GET_ROTA_NUM( 90 ) ){
			one0->wnd_tmp[0][191 - i] = 128;
			one0->wnd_tmp[1][191 - i] = 128;

			one1->wnd_tmp[0][i] = 128;
			one1->wnd_tmp[1][i] = 128;
		}else{
			// 回転角と高さから作られる３角形の幅を求める
			x1 = sub_rota_height_width_one( FX_GET_ROTA_NUM( 90 ) - rota_num, (i - 96) );

			if( x1 > 127 ){
				x1 = 127;
			}
			
			one0->wnd_tmp[0][191 - i] = 0;
			one0->wnd_tmp[1][191 - i] = 128 - x1;
			
			one1->wnd_tmp[0][i] = 128 + x1;
			one1->wnd_tmp[1][i] = 255;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	１データの計算
 *
 *	@param	p_data		ワーク
 *	@param	count		現在ｶｳﾝﾀ
 *	@param	count_max	ｶｳﾝﾀ最大数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndScrewOneAdd( WIPE_TYPE_WND_SCREW_ONE* p_data, int count, int count_max )
{
	int rota_w;
	
	rota_w = p_data->add_num_rota * count;
	rota_w = rota_w / count_max;
	p_data->rota = rota_w + p_data->s_rota;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュワイプ　４方向
 *
 *	@param	wipe		ワイプワーク
 *	@param	param		パラメータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_FLASH_FOUR_FP* param)
{
	WIPE_TYPE_WND_FLASH_FOUR* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_FLASH_FOUR) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_FLASH_FOUR) );
	data = wipe->wipe_work;
	scchg_WndFlashFourInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュ　４方向
 *
 *	@param	wipe	ワイプワーク
 *
 *	@retval	TRUE		終了
 *	@retval	FALSE		続行
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndFlashFourPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_FLASH_FOUR* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_FLASH_FOUR*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndFlashFourMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndFlashFourEnd(wwm);	// ウィンドウデータ破棄
		scchg_h_WndDel(&wwm->hb);
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュ　４方向　初期化処理
 *
 *	@param	data		ワーク
 *	@param	param		パラメータ
 *	@param	division	分割数
 *	@param	piece_sync	シンク数
 *	@param	disp		画面
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	p_wipehb	Hブランク関数システム
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourInit(WIPE_TYPE_WND_FLASH_FOUR* data, WIPE_TYPE_WND_FLASH_FOUR_FP* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	
	// 変化値を求める
	data->screw.rota		= param->s_rota;
	data->screw.s_rota		= param->s_rota;
	data->screw.add_num_rota = param->e_rota - param->s_rota;

	// データを設定
	scchg_h_WndMake(&data->hb, 2, disp, heap);
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb			= p_wipehb;
	data->heap				= heap;
	data->fade_flg			= param->fade_flg;
	
	scchg_WndFlashFourSum(data);	// 1回計算する
	VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );

	// ウィンドウ設定
	one0 = scchg_h_WndIdxDataGet(&data->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&data->hb, 1);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 0, disp,
			0, 0, 255, 192,
			data->fade_flg);
	scchg_WndSetUp(wnd_sys, param->in_wnd, param->out_wnd, 1, disp,
			0, 0, 255, 192,
			data->fade_flg);

	// ウィンドウオン
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0|GX_WNDMASK_W1, disp, data->fade_flg );

	// Hblank関数を設定
	WIPE_V_HBlankInit(data->p_wipehb, &data->hb, scchg_h_Wnd, disp, heap);
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュ　４方向メイン関数
 *
 *	@param	data	ワーク
 *
 *	@retval	TRUE		終了
 *	@retval	FALSE		続行
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndFlashFourMain(WIPE_TYPE_WND_FLASH_FOUR* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// 動かす
			scchg_WndFlashFourOneAdd(&data->screw, data->a_count, data->a_count_max);
			scchg_WndFlashFourSum(data);		// 計算
			VWaitTCB_Add(scchg_WndSwap,&data->hb, WIPE_VBLANK_WND_SWAP_TCB );
		}else{
			// 処理終了
			WIPE_V_HBlankDelete(data->p_wipehb, data->hb.disp, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュ４方向破棄関数
 *
 *	@param	data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourEnd(WIPE_TYPE_WND_FLASH_FOUR* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	フラッシュ４方向関数	計算
 *
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourSum(WIPE_TYPE_WND_FLASH_FOUR* work)
{
	WIPE_TYPE_HB_WND_ONE* one0;
	WIPE_TYPE_HB_WND_ONE* one1;
	u16 rota_num;
	int x1, x2;
	int i;

	rota_num = work->screw.rota;
	
	one0 = scchg_h_WndIdxDataGet(&work->hb, 0);
	one1 = scchg_h_WndIdxDataGet(&work->hb, 1);

	// 右上の部分を基準に４つのブロックの値を設定していく
	// ０～４５ﾄﾞで完全に閉じる
	for( i=0; i<96; i++ ){
		// 回転角と高さから作られる３角形の幅を求める
		x1 = sub_rota_height_width_one( rota_num, (96 - i) );
		x2 = sub_rota_height_width_one( FX_GET_ROTA_NUM(90) - rota_num, (96 - i) );
		if( x1 > 127 ){
			x1 = 127;
		}
		if( x2 > 127 ){
			x2 = 127;
		}

		// 左上
		one0->wnd_tmp[0][i] = 128 - x2;
		one0->wnd_tmp[1][i] = 128 - x1;
		
		// 左下
		one0->wnd_tmp[0][191 - i] = 128 - x2;
		one0->wnd_tmp[1][191 - i] = 128 - x1;
		
		// 右上
		one1->wnd_tmp[0][i] = 128 + x1;
		one1->wnd_tmp[1][i] = 128 + x2;
		
		// 右下
		one1->wnd_tmp[0][191 - i] = 128 + x1;
		one1->wnd_tmp[1][191 - i] = 128 + x2;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	角度計算処理
 *
 *	@param	p_data		ワーク
 *	@param	count		現在ｶｳﾝﾀ
 *	@param	count_max	ｶｳﾝﾀ最大数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndFlashFourOneAdd( WIPE_TYPE_WND_FLASH_FOUR_ONE* p_data, int count, int count_max )
{
	int rota_w;
	
	rota_w = p_data->add_num_rota * count;
	rota_w = rota_w / count_max;
	
	p_data->rota = rota_w + p_data->s_rota;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウHブランク使用　縦動作　初期化
 *
 *	@param	wipe		ワイプワーク
 *	@param	param		パラメータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMovePackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_VMOVE_PARAM* param)
{
	WIPE_TYPE_WND_VMOVE_CONT* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_VMOVE_CONT) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_VMOVE_CONT) );
	data = wipe->wipe_work;
	scchg_WndWndVMoveInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウHブランク使用　縦動作	動作
 *
 *	@param	wipe		ワイプワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndVMovePack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_VMOVE_CONT* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_VMOVE_CONT*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		ret = scchg_WndWndVMoveMain(wwm);
		if(ret == TRUE){
			scchg_WndEnd(wwm->fade_flg, wwm->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		scchg_WndWndVMoveEnd(wwm);	// ウィンドウデータ破棄
		
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウHブランク使用　縦動作	初期化
 *
 *	@param	data		ワーク
 *	@param	param		パラメータ
 *	@param	division	分割数
 *	@param	piece_sync	シンク数
 *	@param	disp		画面
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	p_wipehb	Hブランク関数システム
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveInit(WIPE_TYPE_WND_VMOVE_CONT* data, WIPE_TYPE_WND_VMOVE_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	// Hブランクワーク初期化
	scchg_h_VMoveWndInit( &data->HblankData, disp, 1, WNDP_WND_0, 0 );
	// 初期ワーク値を設定
	if( param->fade_flg == WIPE_FADE_IN ){
		memset( data->HblankData.data[0].in_out_write, WIPE_WND_VMOVE_OUTWND, sizeof( u8 ) * 192 );
		memset( data->HblankData.data[0].in_out_read, WIPE_WND_VMOVE_OUTWND, sizeof( u8 ) * 192 );
	}else{
		memset( data->HblankData.data[0].in_out_write, WIPE_WND_VMOVE_INWND, sizeof( u8 ) * 192 );
		memset( data->HblankData.data[0].in_out_read, WIPE_WND_VMOVE_INWND, sizeof( u8 ) * 192 );
	}


	// データテーブル設定
	data->p_param = param->cp_data;
	data->param_num = param->data_num;
	data->fade_flg = param->fade_flg;
	data->heap	= heap;

	// 変化数とシンク数設定
	data->a_count_max		= division;
	data->a_count			= 0;
	data->piece_sync		= piece_sync;
	data->sync_c			= 0;
	data->wnd_sys			= wnd_sys;
	data->p_wipehb		= p_wipehb;

	// Hブランク関数設定
	scchg_h_VMoveWnd_Start( p_wipehb, &data->HblankData, heap );


	// ウィンドウ設定
	if( param->fade_flg == WIPE_FADE_OUT ){
		scchg_WndSetUp(wnd_sys, GX_BLEND_PLANEMASK_BD, GX_BLEND_ALL, WNDP_WND_0, disp, 0, 0, 0, 0, param->fade_flg);
	}else{
		scchg_WndSetUp(wnd_sys, GX_BLEND_ALL, GX_BLEND_PLANEMASK_BD, WNDP_WND_0, disp, 0, 0, 0, 0, param->fade_flg);
	}

	// ウィンドウオン
	scchg_WndVisible( wnd_sys, GX_WNDMASK_W0, disp, data->fade_flg );

}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン動作
 *
 *	@param	data	ワーク
 *
 *	@retval	 TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndVMoveMain(WIPE_TYPE_WND_VMOVE_CONT* data)
{
	data->sync_c++;
	if(data->sync_c >= data->piece_sync){
		data->sync_c = 0;
		
		// 動かす
		if((data->a_count + 1) <= data->a_count_max){
			data->a_count++;

			// 動かす
			scchg_WndWndVMoveSum(data);		// 計算
			scchg_h_VMoveWnd_SwapReq( &data->HblankData );
		}else{
			// 処理終了
			scchg_h_VMoveWnd_End(data->p_wipehb, &data->HblankData, data->heap);
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	破棄関数
 *	
 *	@param	data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveEnd(WIPE_TYPE_WND_VMOVE_CONT* data)
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワークにデータ設定関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveSum(WIPE_TYPE_WND_VMOVE_CONT* work)
{
	int i;
	WIPE_TYPE_WND_VMOVE_HDATA* p_buff;
	const WIPE_TYPE_WND_VMOVE_DATA* cp_one;

	// 書き込み先バッファ
	p_buff = &work->HblankData.data[0];

	for( i=0; i<work->param_num; i++ ){
		cp_one = &work->p_param[i];
		scchg_WndWndVMoveSub_Core( cp_one, p_buff, work->a_count, work->a_count_max );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	計算Core
 *
 *	@param	p_one		１つの動作データ
 *	@param	p_buff		書き込み先バッファデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndVMoveSub_Core( const WIPE_TYPE_WND_VMOVE_DATA* p_one, WIPE_TYPE_WND_VMOVE_HDATA* p_buff, int count, int count_max )
{
	int i;
	int sum_work;	// 計算ワーク
	int e_y_sum;	// 終了Y座標の計算結果
	int min_y;
	int max_y;
	int set_wndmsk;

	sum_work = (p_one->e_y - p_one->s_y) * count;
	e_y_sum = sum_work / count_max;
	e_y_sum += p_one->s_y;

	// for分でまわすため最小Yと最大Yを求める
	if( p_one->s_y <= p_one->e_y ){
		min_y = p_one->s_y;
		max_y = p_one->e_y;

		set_wndmsk = p_one->in_out;
	}else{
		min_y = p_one->e_y;
		max_y = p_one->s_y;
		if( p_one->in_out == WIPE_WND_VMOVE_INWND ){
			set_wndmsk = WIPE_WND_VMOVE_OUTWND;
		}else{
			set_wndmsk = WIPE_WND_VMOVE_INWND;
		}
	}

	for( i=min_y; i<max_y; i++ ){
		// マスク切り替え
		if( i==e_y_sum ){
			if( set_wndmsk == WIPE_WND_VMOVE_INWND ){
				set_wndmsk = WIPE_WND_VMOVE_OUTWND;
			}else{
				set_wndmsk = WIPE_WND_VMOVE_INWND;
			}
		}
		p_buff->in_out_write[ i ] = set_wndmsk;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコン　ワイプ　初期化　パック
 *
 *	@param	wipe		ワイプワーク
 *	@param	param		パラメータ
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomPackInit(WIPE_SYS_WIPE_WORK* wipe, WIPE_TYPE_WND_PESOCOM_PARAM* param)
{
	WIPE_TYPE_WND_PESOCOM* data;

	wipe->wipe_work = sys_AllocMemory( wipe->heap, sizeof(WIPE_TYPE_WND_PESOCOM) );
	memset( wipe->wipe_work, 0, sizeof(WIPE_TYPE_WND_PESOCOM) );
	data = wipe->wipe_work;


	if( param->wnd_move.fade_flg == WIPE_FADE_IN ){
		scchg_WndWndPesocomInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
	}else{
		scchg_WndWndPesocomOutInit( data, param, wipe->division, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
	}

	wipe->sequence++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコンワイプ　メイン　パック
 *
 *	@param	wipe	ワイプワーク
 *
 *	@retval	TRUE	終了
 *	@ratval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomPack(WIPE_SYS_WIPE_WORK* wipe)
{
	WIPE_TYPE_WND_PESOCOM* wwm;
	BOOL	ret;
	BOOL	ret_num = FALSE;		// この関数の戻り値
	
	wwm = (WIPE_TYPE_WND_PESOCOM*)wipe->wipe_work;
	
	switch(wipe->sequence){
		
	case WIPE_MAIN:
		if( wwm->fade_flg == WIPE_FADE_IN ){
			ret = scchg_WndWndPesocomMain(wwm, wipe);
		}else{
			ret = scchg_WndWndPesocomOutMain(wwm, wipe);
		}
		if(ret == TRUE){
			scchg_WndEnd(wipe->fade_inout, wipe->wnd_sys, wipe->disp);
			wipe->sequence++;
		}
		break;

	case WIPE_END:
		sys_FreeMemoryEz(wipe->wipe_work);
		wipe->wipe_work = NULL;
		wipe->sequence++;
		ret_num = TRUE;
		break;
	case WIPE_END_WAIT:
		ret_num = TRUE;
		break;

	default:
		GF_ASSERT(0);
		break;
	}
	
	return ret_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコンワイプ　初期化
 *
 *	@param	data		ワーク
 *	@param	param		パラメータ
 *	@param	division	分割数
 *	@param	piece_sync	シンク数
 *	@param	disp		画面
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	p_wipehb	Hブランク関数システム
 *	@param	heap		ヒープ
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int move_divi;

	move_divi = FX_Mul( division * FX32_ONE, param->sync_div_par ) >> FX32_SHIFT;
	data->sub_divi = division - move_divi;

	// パラメータ保存
	data->p_param = param;
	data->fade_flg = param->wnd_move.fade_flg;

	// wnd_move
	scchg_WndMoveInit(&data->wnd_move, &param->wnd_move, move_divi, piece_sync, disp, wnd_sys);
	if(param->wnd_move.wnd_no == 0){	// ウィンドウオン
		scchg_WndVisible(wnd_sys, GX_WNDMASK_W0,disp, param->wnd_move.fade_flg);
	}else{
		scchg_WndVisible(wnd_sys,GX_WNDMASK_W1, disp, param->wnd_move.fade_flg);
	}

	data->seq = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコン　ワイプ　メイン処理
 *
 *	@param	data
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe )
{
	BOOL result;
	BOOL ret = FALSE;
	
	switch( data->seq ){
	case 0:
		result = scchg_WndMoveMain( &data->wnd_move );
		if( result == TRUE ){
			data->seq ++;

			// split_divi
			scchg_WndWndVMoveInit(&data->wnd_split, &data->p_param->wnd_split, data->sub_divi, wipe->piece_sync, wipe->disp, wipe->wnd_sys, wipe->p_wipehb, wipe->heap );
		}
		break;

	case 1:
		result = scchg_WndWndVMoveMain( &data->wnd_split );
		if( result == TRUE ){
			ret = TRUE;
			data->seq ++;
		}
		break;

	case 2:
		ret = TRUE;
		break;
	}

	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコン　ワイプアウト　初期化
 *
 *	@param	data		ワーク
 *	@param	param		パラメータ
 *	@param	division	分割数
 *	@param	piece_sync	シンク数
 *	@param	disp		画面
 *	@param	wnd_sys		ウィンドウシステム
 *	@param	p_wipehb	Hブランク関数システム
 *	@param	heap		ヒープ
 */
//-----------------------------------------------------------------------------
static void scchg_WndWndPesocomOutInit(WIPE_TYPE_WND_PESOCOM* data, WIPE_TYPE_WND_PESOCOM_PARAM* param, int division, int piece_sync, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb, int heap )
{
	int split_divi;

	data->sub_divi = FX_Mul( division * FX32_ONE, param->sync_div_par ) >> FX32_SHIFT;
	split_divi = division - data->sub_divi;

	// パラメータ保存
	data->p_param = param;
	data->fade_flg = param->wnd_move.fade_flg;

	// split_divi
	scchg_WndWndVMoveInit(&data->wnd_split, &data->p_param->wnd_split, split_divi,piece_sync, disp, wnd_sys, p_wipehb, heap );

	data->seq = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パソコン　ワイプアウト　メイン処理
 *
 *	@param	data
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL scchg_WndWndPesocomOutMain(WIPE_TYPE_WND_PESOCOM* data, WIPE_SYS_WIPE_WORK* wipe )
{
	BOOL result;
	BOOL ret = FALSE;
	
	switch( data->seq ){
	case 0:
		result = scchg_WndWndVMoveMain( &data->wnd_split );
		if( result == TRUE ){
			data->seq ++;

			// wnd_move
			scchg_WndMoveInit(&data->wnd_move, &data->p_param->wnd_move, data->sub_divi, wipe->piece_sync, wipe->disp, wipe->wnd_sys);
			if(data->p_param->wnd_move.wnd_no == 0){	// ウィンドウオン
				scchg_WndVisible(wipe->wnd_sys, GX_WNDMASK_W0, wipe->disp, data->p_param->wnd_move.fade_flg);
			}else{
				scchg_WndVisible(wipe->wnd_sys,GX_WNDMASK_W1, wipe->disp, data->p_param->wnd_move.fade_flg);
			}
		}
		break;

	case 1:
		result = scchg_WndMoveMain( &data->wnd_move );
		if( result == TRUE ){
			ret = TRUE;
			data->seq ++;
		}
		break;

	case 2:
		ret = TRUE;
		break;
	}

	return ret;
}

