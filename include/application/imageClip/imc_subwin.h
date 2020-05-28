//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_subwin.h
 *	@brief		サブウィンドウ
 *	@author		tomoya takahashi
 *	@data		2005.10.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_SUBWIN_H__
#define __IMC_SUBWIN_H__
#include "bg_system.h"
#include "include/application/imageClip/imc_bg.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/contest/contest.h"
#include "include/savedata/config.h"

#undef GLOBAL
#ifdef	__IMC_SUBWIN_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	初期化マスク
//	
//=====================================
enum{
	IMC_SUBWIN_INITMASK_CLEAN	= 1 << 0,	// 最初の初期化
	IMC_SUBWIN_INITMASK_BG		= 1 << 1,	// BG面の初期化
	IMC_SUBWIN_INITMASK_BMP		= 1 << 2,	// bmpウィンドウ面の初期化 
	IMC_SUBWIN_INITMASK_ACCE_COUNT = 1 << 3,// アクセサリカウント画面の初期化 
	IMC_SUBWIN_INITMASK_TIME_COUNT = 1 << 4,// タイムカウント画面の初期化 
	IMC_SUBWIN_INITMASK_RANKBMP = 1 << 5,	// ランクのBMPウィンドウ
};

#define IMC_SUBWIN_DEFAULT_INIT	(IMC_SUBWIN_INITMASK_CLEAN | IMC_SUBWIN_INITMASK_BG | IMC_SUBWIN_INITMASK_BMP | IMC_SUBWIN_INITMASK_ACCE_COUNT)
#define IMC_SUBWIN_CONTEST_INIT	(IMC_SUBWIN_INITMASK_CLEAN | IMC_SUBWIN_INITMASK_BG | IMC_SUBWIN_INITMASK_BMP | IMC_SUBWIN_INITMASK_ACCE_COUNT | IMC_SUBWIN_INITMASK_TIME_COUNT | IMC_SUBWIN_INITMASK_RANKBMP)

//---------------------------------------------------------
//	アクセサリｶｳﾝﾀ関係
//---------------------------------------------------------
// アクセサリアイコンｶｳﾝﾀワークの最大数
#define IMC_SUBWIN_ACCECOUNT_ICON_MAX	( IMC_RBOX_ACCE_CONTEST_MAX )


//---------------------------------------------------------
//	タイムｶｳﾝﾀ関係		ｶｳﾝﾀ転送モード
//---------------------------------------------------------
#define IMC_SUBWIN_NUM_KETA	(2)		// 桁数
enum{
	IMC_SUBWIN_NUM_TRANS_OYA,		// 親
	IMC_SUBWIN_NUM_TRANS_CHILD,		// 子
	IMC_SUBWIN_NUM_TRANS_NONE,		// なんでもない
};
#define IMC_SUBWIN_NUM_POP_TCB_PRI	( 128 )
#define IMC_SUBWIN_NUM_PUSH_TCB_PRI	( 64 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	アイコンデータ
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[IMC_DRAW_USE_RES_NUM];
	CLACT_WORK_PTR	icon[IMC_SUBWIN_ACCECOUNT_ICON_MAX];
	int acce_num;
	int acce_max;
} IMC_SUBWIN_ACCEICON;

//-------------------------------------
//	動作ワーク
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	int count;
	int count_max;
} IMC_SUBWIN_MOVE_WORK;


//-------------------------------------
//	タイムカウントグラフィック用
//	ｴﾌｪｸﾄワーク
//=====================================
typedef struct {
	BOOL init_flg;	// TRUE	動作中 FALSE	非動作中
	CLACT_WORK_PTR	num[IMC_SUBWIN_NUM_KETA];
	VecFx32 mat[IMC_SUBWIN_NUM_KETA];
	IMC_SUBWIN_MOVE_WORK	scale;
	IMC_SUBWIN_MOVE_WORK	x;
	IMC_SUBWIN_MOVE_WORK	y;
} IMC_SUBWIN_TIME_EFFECT;


//-------------------------------------
//	タイムｶｳﾝﾀワーク
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR res_obj[IMC_DRAW_USE_RES_NUM];
	CLACT_WORK_PTR	num[IMC_SUBWIN_NUM_KETA];
	GF_BGL_BMPWIN*	bmp;
	int count;
	int master_count;		// 通信の親用ｶｳﾝﾀ
	TCB_PTR	CountTCB;		// countの値を書き換えるTCB
	TCB_PTR MstTransTCB;	// ﾏｽﾀｰｶｳﾝﾀの値を転送するTCB
	CON_IMC_LOCAL* p_comm_data;	// 通信データ
	IMC_SUBWIN_TIME_EFFECT counter_eff;	// カウンターｴﾌｪｸﾄ

	BOOL pal_chg;	// パレット変更済みチェック
} IMC_SUBWIN_TIMECOUNT;


//-------------------------------------
//	
//	サブ画面構造体
//	
//=====================================
typedef struct {
	IMC_BG			bg;			// BG面
	GF_BGL_BMPWIN*	bmp;		// ビットマップウィンドウ
	CLACT_SET_PTR		clactSet;			// セルアクターセット
	CLACT_U_RES_MANAGER_PTR* p_resMan;	// リソースマネージャ

	IMC_SUBWIN_ACCEICON	acce_icon;	// アクセサリアイコンワーク
	IMC_SUBWIN_TIMECOUNT counter;	// カウンター
	GF_BGL_BMPWIN*	rankbmp;		// ランク文字列ビットマップウィンドウ
	
	int init_flg;				// 初期化済みチェックフラグ

	// コンフィグデータ
	int wnd_no;
	u32 wait;

	STRBUF* p_glb_str;	// グローバル文字列バッファ
} IMC_SUBWIN;

typedef struct {
	GF_BGL_INI* bg_ini;
	CLACT_SET_PTR		clactSet;			// セルアクターセット
	CLACT_U_RES_MANAGER_PTR* p_resMan;	// リソースマネージャ

	// コンフィグ
	const CONFIG* cp_config;

	// アクセサリｶｳﾝﾀ用
	int acce_max;		// アイコン数

	// テーマ用
	int rank_msgid;		// ランクメッセージID
	int rank_strid;		// ランク文字列ID

	// タイマー用
	int count_max;		// 最大カウント値
	CON_IMC_LOCAL* p_comm_data;	// 通信データ
} IMC_SUBWIN_INIT;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウの初期化
 *
 *	@param	subwin		サブウィンドウ構造体
 *	@param	init		初期化データ
 *	@param	init_mask	初期化マスク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Init( IMC_SUBWIN* subwin, IMC_SUBWIN_INIT* init, int init_mask );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウ破棄
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Delete( IMC_SUBWIN* subwin );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン関数
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_Main( IMC_SUBWIN* subwin );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップに文字列を表示
 *
 *	@param	subwin	サブウィンドウオブジェ
 *	@param	arcID	アーカイブID
 *	@param	dataID	データID
 *	@param	msgID	表示するメッセージID
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_SetBmpWin( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID );
GLOBAL s32 IMC_SUBWIN_SetBmpWinWait( IMC_SUBWIN* subwin, int arcID, int dataID, int msgID );
GLOBAL void IMC_SUBWIN_EndBmpWinWait( IMC_SUBWIN* subwin );	// 確保していたワークをはき

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリカウントアイコン描画設定
 *
 *	@param	subwin		ワーク
 *	@param	acce_num	現在のアクセサリ数
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
GLOBAL void IMC_SUBWIN_SetAcceIcon( IMC_SUBWIN* subwin, int acce_num );

//----------------------------------------------------------------------------
/**
 *	@brief	今のカウンター値取得関数
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@return	カウンターの値
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_SUBWIN_GetCounterNowNum( const IMC_SUBWIN* subwin );
GLOBAL void IMC_SUBWIN_SetCounterNowNum( IMC_SUBWIN* subwin, int count );

//----------------------------------------------------------------------------
/**
 *	@brief	カウンターｴﾌｪｸﾄの終了チェック
 *
 *	@param	subwin	サブウィンドウ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_SUBWIN_GetCounterEffectEnd( const IMC_SUBWIN* subwin );

#ifdef PM_DEBUG
GLOBAL void IMC_SUBWIN_DEBUG_SetBmpWin( IMC_SUBWIN* p_data, int msgID_1, int msgID_2 );
GLOBAL void IMC_SUBWIN_DEBUG_CountTimeSet( IMC_SUBWIN* p_data, int num );
#endif

#undef	GLOBAL
#endif		// __IMC_SUBWIN_H__

