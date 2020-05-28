//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_demo.h
 *	@brief		木の実ミキサー　小さいエフェクト動さなどの処理
 *	@author		tomoya takahashi
 *	@data		2006.05.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_DEMO_H__
#define __NMIX_GAME_DEMO_H__

#include "nmix_game_comm.h"
#include "system/clact_util.h"
#include "nmix_stdata.h"
#include "include/system/swsprite.h"
#include "nutmix_comm_pack.h"
#include "src/system/clact_tool.h"
#include "src/application/poruto/poru_oam.h"
#include "include/system/touch_subwindow.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_DEMO_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

// デフォルトOAMリソース数
enum{
	NMIX_GAME_DEF_OAM_RES_START,
	NMIX_GAME_DEF_OAM_RES_COMMON,
	NMIX_GAME_DEF_OAM_RES_SOUP,
	NMIX_GAME_DEF_OAM_RES_CREAM,
	NMIX_GAME_DEF_OAM_RES_SOBORO,
	NMIX_GAME_DEF_OAM_RES_END,
	NMIX_GAME_DEF_OAM_RES_NUM,
};
#define NMIX_GAME_DEF_OAM_CL		( 2 )	// それぞれの使用カラーパレット数
#define NMIX_GAME_DEF_OAM_CONTID	( 2000 )	// 管理ID



//-------------------------------------
//	セルアクターパック
//=====================================
typedef struct {
	CLACT_SET_PTR	cas;
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ
	CLACT_U_RES_MANAGER_PTR	resMan[4];	// リソースマネージャ
} NMIXGAME_CLACT_SYS;
//-------------------------------------
//	セルアクターリソースオブジェパック
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR resobj[4];
	BOOL pltt_copy;
	CLACT_HEADER head;
} NMIXGAME_CLACT_RES_WORK;

// システム初期化
GLOBAL void NMIXGAME_CLACT_Init( NMIXGAME_CLACT_SYS* p_sys, int work_num, int res_num, int heapID );
GLOBAL void NMIXGAME_CLACT_Delete( NMIXGAME_CLACT_SYS* p_sys );

// 簡単リソース読み込み
GLOBAL void NMIXGAME_CLACT_ResLoadEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, u32 pltt_idx, u32 pltt_num, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap );
GLOBAL void NMIXGAME_CLACT_ResLoadEasy_PlttCopy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, u32 arc_file, CLACT_U_RES_OBJ_PTR pltt_obj, u32 char_idx, u32 cel_idx, u32 anm_idx, u32 cont_id, u32 heap );
GLOBAL void NMIXGAME_CLACT_ResDeleteEasy( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work );

// アクター登録
GLOBAL CLACT_WORK_PTR NMIXGAME_CLACT_Add( NMIXGAME_CLACT_SYS* p_sys, NMIXGAME_CLACT_RES_WORK* p_work, fx32 x, fx32 y, fx32 z, int pri, int heap );


//-----------------------------------------------------------------------------
/**
 *			汎用計算システム
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	汎用動作
//=====================================
typedef struct {
	int x;
	int s_x;
	int dis_x;
	int count;
	int count_max;
} NMIX_DEMO_MOVE_WORK;
GLOBAL void NMIX_DEMO_MoveReq( NMIX_DEMO_MOVE_WORK* p_work, int s_x, int e_x, int count_max );
GLOBAL BOOL	NMIX_DEMO_MoveMain( NMIX_DEMO_MOVE_WORK* p_work );

//-------------------------------------
//	汎用動作
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 dis_x;
	int count;
	int count_max;
} NMIX_DEMO_MOVE_WORK_FX;
GLOBAL void NMIX_DEMO_MoveReqFx( NMIX_DEMO_MOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, int count_max );
GLOBAL BOOL	NMIX_DEMO_MoveMainFx( NMIX_DEMO_MOVE_WORK_FX* p_work );

//-------------------------------------
//	汎用加速動作
//=====================================
typedef struct {
	fx32 x;
	fx32 s_x;
	fx32 s_s;	// 初速度
	fx32 s_a;	// 加速度
	int count;
	int count_max;
} NMIX_DEMO_ADDMOVE_WORK_FX;
GLOBAL void NMIX_DEMO_AddMoveReqFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work, fx32 s_x, fx32 e_x, fx32 s_s, int count_max );
GLOBAL BOOL	NMIX_DEMO_AddMoveMainFx( NMIX_DEMO_ADDMOVE_WORK_FX* p_work );


//-------------------------------------
//　ベクトル作成
//=====================================
VecFx32 NMIX_DEMO_MakeVec( fx32 x, fx32 y, fx32 z );





//-----------------------------------------------------------------------------
/**
 *				木の実なべに投げ込み
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	木の実なべに投げ込み
//=====================================
typedef struct _NMIX_DEMO_NUTS_IN{
	BOOL					res_load;		// リソース読み込みフラグ
	BOOL					move_flg;		// 動さフラグ
	CLACT_WORK_PTR			clact[ NUTMIXER_MEMBER_MAX ];
	CLACT_WORK_PTR			pochan[ NUTMIXER_MEMBER_MAX ];
	NMIXGAME_CLACT_RES_WORK res_work[ NUTMIXER_MEMBER_MAX ];
	int						nuts_num;
	NMIX_DEMO_ADDMOVE_WORK_FX move_x[ NUTMIXER_MEMBER_MAX ];
	NMIX_DEMO_ADDMOVE_WORK_FX move_y[ NUTMIXER_MEMBER_MAX ];
	int						obj_seq[ NUTMIXER_MEMBER_MAX ];
	int						obj_wait[ NUTMIXER_MEMBER_MAX ];
	int						start_count;	// 今発射した総数
} NMIX_DEMO_NUTS_IN;

enum{
	NMIX_DEMO_NUTS_RET_FALSE,	// 途中
	NMIX_DEMO_NUTS_RET_TRUE,	// 終了
	NMIX_DEMO_NUTS_RET_NUTS_00,	// 0投入
	NMIX_DEMO_NUTS_RET_NUTS_01,	// 1投入
	NMIX_DEMO_NUTS_RET_NUTS_02,	// 2投入
	NMIX_DEMO_NUTS_RET_NUTS_03,	// 3投入
};

GLOBAL void NMixGameDemo_NutsIn_Init( NMIX_DEMO_NUTS_IN* p_work, int nuts_num );
GLOBAL void NMixGameDemo_NutsIn_Delete( NMIX_DEMO_NUTS_IN* p_work );
GLOBAL void NMixGameDemo_NutsIn_GraphicLoad( NMIX_DEMO_NUTS_IN* p_work, NUTMIX_COMM_BEFORE_KO* p_get_ko_before_data, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID );
GLOBAL void NMixGameDemo_NutsIn_GraphicRelease( NMIX_DEMO_NUTS_IN* p_work, NMIXGAME_CLACT_SYS* p_clact );
GLOBAL void NMixGameDemo_NutsIn_Start( NMIX_DEMO_NUTS_IN* p_work );
GLOBAL u32 NMixGameDemo_NutsIn_Main( NMIX_DEMO_NUTS_IN* p_work );


//-----------------------------------------------------------------------------
/**
 *		上画面描画制御
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	上画面描画制御ワーク
//=====================================
typedef struct {
	int heapID;
	GF_BGL_INI* p_bgl;
	GF_BGL_BMPWIN* p_bmp;
	GF_BGL_BMPWIN* p_bmp_plname;// トレーナー名用BMP
	int			wnd_type;			// ウィンドウタイプ
	int			comm_count;			// 通信相手数
	NMIXER_MSG* p_msg_data;			// 文字列データ
	NUTMIX_GAME_COMM_PACK* p_comm_data;	// 通信データ
	
	// スクリーンデータはいつでも張り替えられるように取っておく
	void* p_bg_scrn_buf;		// 背景グラフィックバッファ
	NNSG2dScreenData* p_bg_scrn;// 背景グラフィック
	void* p_playername_scrn_buf;// プレイヤー名バッファ
	NNSG2dScreenData* p_playername_scrn;// プレイヤー名グラフィック
	
	// 状態フラグ
	BOOL	res_load;		// リソース読み込み
} NMIX_DEMO_SUB_WIN;
GLOBAL void NMixGameDemo_SubWin_Init( NMIX_DEMO_SUB_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID );
GLOBAL void NMixGameDemo_SubWin_Delete( NMIX_DEMO_SUB_WIN* p_work );
GLOBAL void NMixGameDemo_SubWin_GraphicLoad( NMIX_DEMO_SUB_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID );
GLOBAL void NMixGameDemo_SubWin_GraphicRelease( NMIX_DEMO_SUB_WIN* p_work );

GLOBAL void NMixGameDemo_SubWin_WinNutsOn( NMIX_DEMO_SUB_WIN* p_work, int nuts_id );
GLOBAL void NMixGameDemo_SubWin_WinNutsOff( NMIX_DEMO_SUB_WIN* p_work );
GLOBAL void NMixGameDemo_SubWin_WinWaitMsgOn( NMIX_DEMO_SUB_WIN* p_work );

GLOBAL void NMixGameDemo_SubWin_PlayerNameOn( NMIX_DEMO_SUB_WIN* p_work );


//-----------------------------------------------------------------------------
/**
 *		カウントダウン
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	カウントダウン
//	終了エフェクトにも使用
//=====================================
typedef struct {
	BOOL					res_load;		// リソース読み込みフラグ
	BOOL					move_flg;		// 動さフラグ
	CLACT_WORK_PTR			clact;
} NMIX_DEMO_COUNTDOWN;

GLOBAL void NMixGameDemo_CountDown_Init( NMIX_DEMO_COUNTDOWN* p_work );
GLOBAL void NMixGameDemo_CountDown_Delete( NMIX_DEMO_COUNTDOWN* p_work );
GLOBAL void NMixGameDemo_CountDown_GraphicLoad( NMIX_DEMO_COUNTDOWN* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID, u32 res_no, u32 anm_idx );
GLOBAL void NMixGameDemo_CountDown_GraphicRelease( NMIX_DEMO_COUNTDOWN* p_work );
GLOBAL void NMixGameDemo_CountDown_Start( NMIX_DEMO_COUNTDOWN* p_work );
GLOBAL void NMixGameDemo_CountDown_Start_Pen( NMIX_DEMO_COUNTDOWN* p_work );
GLOBAL BOOL NMixGameDemo_CountDown_Main( NMIX_DEMO_COUNTDOWN* p_work );



//-----------------------------------------------------------------------------
/**
 *		鍋グラフィック描画管理システム
 */
//-----------------------------------------------------------------------------
// グラフィックリソース定義
enum{
	// キャラクタデータ
	NMIX_DEMO_NABE_CHAR_FIRE = 0,
	NMIX_DEMO_NABE_CHAR_NABE_UP,
	NMIX_DEMO_NABE_CHAR_NABE_DOWN,
	NMIX_DEMO_NABE_CHAR_SOOP_0,
	NMIX_DEMO_NABE_CHAR_SOOP_1,
	NMIX_DEMO_NABE_CHAR_SOOP_2,
	NMIX_DEMO_NABE_CHAR_NUM,

	// パレットデータ
	NMIX_DEMO_NABE_PLTT_FIRE_0 = 0,
	NMIX_DEMO_NABE_PLTT_FIRE_1,
	NMIX_DEMO_NABE_PLTT_FIRE_2,
	NMIX_DEMO_NABE_PLTT_NABE_UP,
	NMIX_DEMO_NABE_PLTT_NABE_DOWN,
	NMIX_DEMO_NABE_PLTT_SOOP_0,
	NMIX_DEMO_NABE_PLTT_SOOP_1,
	NMIX_DEMO_NABE_PLTT_SOOP_2,
	NMIX_DEMO_NABE_PLTT_NUM,

	// オブジェクト数
	NMIX_DEMO_NABE_OBJ_FIRE_0 = 0,
	NMIX_DEMO_NABE_OBJ_FIRE_1,
	NMIX_DEMO_NABE_OBJ_FIRE_2,
	NMIX_DEMO_NABE_OBJ_NABE_UP,
	NMIX_DEMO_NABE_OBJ_NABE_DOWN,
	NMIX_DEMO_NABE_OBJ_SOOP_0,
	NMIX_DEMO_NABE_OBJ_SOOP_1,
	NMIX_DEMO_NABE_OBJ_SOOP_2,
	NMIX_DEMO_NABE_OBJ_NUM,
};


//-------------------------------------
//	鍋グラフィック描画管理ワーク
//=====================================
typedef struct {
	SWSP_CHAR_PTR swsp_char[ NMIX_DEMO_NABE_CHAR_NUM ];
	SWSP_PLTT_PTR swsp_pltt[ NMIX_DEMO_NABE_PLTT_NUM ];
	SWSP_OBJ_PTR  swsp_obj[ NMIX_DEMO_NABE_OBJ_NUM ];


	NMIX_DEMO_MOVE_WORK_FX fire_anm;
	int fire_anm_seq;
	int way_switch;

	int res_load;
} NMIX_DEMO_NABE_GRA;

GLOBAL void NMixGameDemo_NabeGra_Init( NMIX_DEMO_NABE_GRA* p_work );
GLOBAL void NMixGameDemo_NabeGra_Delete( NMIX_DEMO_NABE_GRA* p_work );
GLOBAL void NMixGameDemo_NabeGra_GraphicLoad( NMIX_DEMO_NABE_GRA* p_work, SWSP_SYS_PTR	swsp_sys, u32 heapID );
GLOBAL void NMixGameDemo_NabeGra_GraphicRelease( NMIX_DEMO_NABE_GRA* p_work );

GLOBAL void NMixGameDemo_NabeGra_GraphicSetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, BOOL flg );
GLOBAL BOOL NMixGameDemo_NabeGra_GraphicGetDrawFlg( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id );

GLOBAL void NMixGameDemo_NabeGra_GraphicSetSoopRota( NMIX_DEMO_NABE_GRA* p_work, u16 rota );
GLOBAL void NMixGameDemo_NabeGra_GraphicSetSoopScale( NMIX_DEMO_NABE_GRA* p_work, fx32 scale );

GLOBAL void NMixGameDemo_NabeGra_GraphicSetAlpha( NMIX_DEMO_NABE_GRA* p_work, u32 obj_id, u32 alpha );

GLOBAL void NMixGameDemo_NabeGra_FireAnmStart( NMIX_DEMO_NABE_GRA* p_work );
GLOBAL void NMixGameDemo_NabeGra_FireAnm( NMIX_DEMO_NABE_GRA* p_work, int soop_type );


//-----------------------------------------------------------------------------
/**
 *		他の人の位置　描画　管理システム
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	他の人　位置描画
//=====================================
typedef struct {
	BOOL					res_load;		// リソース読み込みフラグ
	CLACT_WORK_PTR			clact[ NUTMIXER_MEMBER_MAX ];
	const NUTMIX_GAME_COMM_PACK* cp_commdata;
	u32 comm_count;
	NUTMIX_COMMPACK_WORK* p_comm_work;
} NMIX_DEMO_OTHER_MARK;
GLOBAL void NMixGameDemo_OtherMark_Init( NMIX_DEMO_OTHER_MARK* p_work, const NUTMIX_GAME_COMM_PACK* cp_commdata, u32 comm_count, NUTMIX_COMMPACK_WORK* p_comm_work );
GLOBAL void NMixGameDemo_OtherMark_Delete( NMIX_DEMO_OTHER_MARK* p_work );
GLOBAL void NMixGameDemo_OtherMark_GraphicLoad( NMIX_DEMO_OTHER_MARK* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID );
GLOBAL void NMixGameDemo_OtherMark_GraphicRelease( NMIX_DEMO_OTHER_MARK* p_work );
GLOBAL void NMixGameDemo_OtherMark_Main( NMIX_DEMO_OTHER_MARK* p_work );
GLOBAL void NMixGameDemo_OtherMark_DrawFlag( NMIX_DEMO_OTHER_MARK* p_work, BOOL flg );


//-----------------------------------------------------------------------------
/**
 *		メイン画面　ビットマップウィンドウ
 */
//-----------------------------------------------------------------------------
enum{
	// ビットマップウィンドウ定数
	NMIX_DEMO_MAINWIN_COMME = 0,
	NMIX_DEMO_MAINWIN_RESULT_MAIN,
	NMIX_DEMO_MAINWIN_RESULT_SUB,
	NMIX_DEMO_MAINWIN_TEXT,			// テキスト描画面
	NMIX_DEMO_MAINWIN_NUM,
};


//-------------------------------------
//	メイン画面　BG面管理
//=====================================
typedef struct {
	int heapID;
	GF_BGL_INI* p_bgl;
	GF_BGL_BMPWIN* p_bmp[NMIX_DEMO_MAINWIN_NUM];
	int			wnd_type;			// ウィンドウタイプ
	NMIXER_MSG* p_msg_data;			// 文字列データ
	int comm_count;
	NUTMIX_GAME_COMM_PACK* p_comm_data;	// 通信データ
	// 状態フラグ
	BOOL	res_load;		// リソース読み込み

	// コメントエフェクトワーク
	TCB_PTR move_tcb;
	int		move_count;
} NMIX_DEMO_MAIN_WIN;
GLOBAL void NMixGameDemo_MainWin_Init( NMIX_DEMO_MAIN_WIN* p_work, int comm_count, NMIXER_MSG* p_msg_data, NUTMIX_GAME_COMM_PACK* p_comm_data, int wnd_type, u32 heapID );
GLOBAL void NMixGameDemo_MainWin_Delete( NMIX_DEMO_MAIN_WIN* p_work );
GLOBAL void NMixGameDemo_MainWin_GraphicLoad( NMIX_DEMO_MAIN_WIN* p_work, GF_BGL_INI* p_bgl, u32 heapID );
GLOBAL void NMixGameDemo_MainWin_GraphicRelease( NMIX_DEMO_MAIN_WIN* p_work );

GLOBAL void NMixGameDemo_EndMsgPirntOn( NMIX_DEMO_MAIN_WIN* p_work );
GLOBAL void NMixGameDemo_EndMsgPrintOff( NMIX_DEMO_MAIN_WIN* p_work );

GLOBAL void NMixGameDemo_StartComment( NMIX_DEMO_MAIN_WIN* p_work, u32 comm_type );
GLOBAL BOOL NMixGameDemo_EndCheckComment( const NMIX_DEMO_MAIN_WIN* cp_work );
GLOBAL void NMixGameDemo_StopComment( NMIX_DEMO_MAIN_WIN* p_work );

enum{
	NMIX_DEMO_MINWIN_RESULT_SEEN0,
	NMIX_DEMO_MINWIN_RESULT_SEEN1,
	NMIX_DEMO_MINWIN_RESULT_SEEN2,
};
GLOBAL void NMixGameDemo_ResultOn( NMIX_DEMO_MAIN_WIN* p_work, u32 seen );
GLOBAL void NMixGameDemo_ResultOff( NMIX_DEMO_MAIN_WIN* p_work );

//-------------------------------------
//	テキストナンバー
//=====================================
enum{
	NMIX_DEMO_MAINWIN_TEXT_SAVE_PORUTO,
	NMIX_DEMO_MAINWIN_TEXT_HIKITUDUKI,
	NMIX_DEMO_MAINWIN_TEXT_PORUTO_IPPAI,
	NMIX_DEMO_MAINWIN_TEXT_BAG,
	NMIX_DEMO_MAINWIN_TEXT_TUGOUWARU,
	NMIX_DEMO_MAINWIN_TEXT_NUTS_NONE,
	NMIX_DEMO_MAINWIN_TEXT_TUUSHIN_TAIKI,
};
GLOBAL void NMixGameDemo_TextOn( NMIX_DEMO_MAIN_WIN* p_work, u32 text_no );


//-----------------------------------------------------------------------------
/**
 *		スープエフェクト管理
 */
//-----------------------------------------------------------------------------
#define NMIX_DEMO_SOOP_EFF_NUM	( 8 )
// エフェクトタイプ
enum{
	NMIX_DMEO_SOOP_EFF_TYPE_KEMURI,
	NMIX_DEMO_SOOP_EFF_TYPE_KOGE,
	NMIX_DMEO_SOOP_EFF_TYPE_KOBORE,
};

//-------------------------------------
//	スープエフェクトオブジェクト
//=====================================
typedef struct {
	BOOL move_type;
	BOOL move_end;
	BOOL anm_end;
	BOOL scale_use;
	BOOL soop_move;	// スープと一緒に移動するか
	VecFx32 matrix;
	VecFx32 scale;
	s32	obj_rota;

	NMIX_DEMO_ADDMOVE_WORK_FX move_x;
	NMIX_DEMO_ADDMOVE_WORK_FX move_y;
	NMIX_DEMO_ADDMOVE_WORK_FX move_scale;
	
	CLACT_WORK_PTR	clact;

	int add_time;
} NMIX_DEMO_SOOP_EFF_OBJ;

//-------------------------------------
//	スープエフェクト
//=====================================
typedef struct {
	int res_load;	
	NMIXGAME_CLACT_SYS* p_clact;
	NMIXGAME_CLACT_RES_WORK* p_def_oam_res;
	u32 heapID;
	NMIX_DEMO_SOOP_EFF_OBJ eff_obj[ NMIX_DEMO_SOOP_EFF_NUM ];
	int add_count;
} NMIX_DEMO_SOOP_EFFECT;

GLOBAL void NMixGameDemo_SoopEffect_Init( NMIX_DEMO_SOOP_EFFECT* p_work );
GLOBAL void NMixGameDemo_SoopEffect_Delete( NMIX_DEMO_SOOP_EFFECT* p_work );
GLOBAL void NMixGameDemo_SoopEffect_GraphicLoad( NMIX_DEMO_SOOP_EFFECT* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID );
GLOBAL void NMixGameDemo_SoopEffect_GraphicRelease( NMIX_DEMO_SOOP_EFFECT* p_work );
GLOBAL void NMixGameDemo_SoopEffect_Main( NMIX_DEMO_SOOP_EFFECT* p_work, NUTMIX_GAME_COMM_PACK* p_comm_pack );
GLOBAL void NMixGameDemo_SoopEffect_Add( NMIX_DEMO_SOOP_EFFECT* p_work, int soop_type, int eff_type );
GLOBAL void NMixGameDemo_SoopEffect_DelReq( NMIX_DEMO_SOOP_EFFECT* p_work );


//-----------------------------------------------------------------------------
/**
 *		矢印エフェクト管理
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	矢印タイプ
//=====================================
enum{
	// オブジェ
	NMIX_DEMO_YAZIRUSI_RIGHT = 0,
	NMIX_DEMO_YAZIRUSI_RIGHT_R,
	NMIX_DEMO_YAZIRUSI_LEFT,
	NMIX_DEMO_YAZIRUSI_LEFT_R,
	NMIX_DEMO_YAZIRUSI_OBJ_NUM
};


//-------------------------------------
//	矢印オブジェ
//=====================================
typedef struct {
	CLACT_WORK_PTR clact;
	int count;
	int count_num;
	BOOL move;
} NMIX_DEMO_YAZIRUSI_OBJ;

//-------------------------------------
//	回転方向　矢印操作
//=====================================
typedef struct {
	NMIXGAME_CLACT_SYS* p_clact;
	NMIXGAME_CLACT_RES_WORK oam_res;
	NMIX_DEMO_YAZIRUSI_OBJ yazirusi[ NMIX_DEMO_YAZIRUSI_OBJ_NUM ];

	int res_load;
} NMIX_DEMO_YAZIRUSI;

GLOBAL void NMixGameDemo_Yazirusi_Init( NMIX_DEMO_YAZIRUSI* p_work );
GLOBAL void NMixGameDemo_Yazirusi_Delete( NMIX_DEMO_YAZIRUSI* p_work );
GLOBAL void NMixGameDemo_Yazirusi_GraphicLoad( NMIX_DEMO_YAZIRUSI* p_work, NMIXGAME_CLACT_SYS* p_clact, u32 heapID );
GLOBAL void NMixGameDemo_Yazirusi_GraphicRelease( NMIX_DEMO_YAZIRUSI* p_work );
GLOBAL void NMixGameDemo_Yazirusi_Main( NMIX_DEMO_YAZIRUSI* p_work );
GLOBAL void NMixGameDemo_Yazirusi_Add( NMIX_DEMO_YAZIRUSI* p_work, int eff_type );
GLOBAL void NMixGameDemo_Yazirusi_Stop( NMIX_DEMO_YAZIRUSI* p_work, int eff_type );
GLOBAL BOOL NMixGameDemo_Yazirusi_EndCheck( const NMIX_DEMO_YAZIRUSI* cp_work, int eff_type );


//-----------------------------------------------------------------------------
/**
 *		星キラキラ　
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	キラキラオブジェ最大数
//=====================================
#define KIRAKIRA_OBJ_MAX	( 32 )

//-------------------------------------
//	星キラキラオブジェ
//=====================================
typedef struct {
	BOOL move_flg;
	BOOL move_end;
	VecFx32 matrix;
	NMIX_DEMO_ADDMOVE_WORK_FX move_x;
	NMIX_DEMO_ADDMOVE_WORK_FX move_y;
	CLACT_WORK_PTR	clact;
} NMIX_DEMO_HOSI_KIRAKIRA_OBJ;

//-------------------------------------
//	星キラキラ
//=====================================
typedef struct {
	int res_load;	
	int comm_count;
	int eff_count;
	NMIX_DEMO_HOSI_KIRAKIRA_OBJ eff_obj[ KIRAKIRA_OBJ_MAX ];
} NMIX_DEMO_HOSI_KIRAKIRA;

GLOBAL void NMixGameDemo_HosiKiraKira_Init( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int comm_count );
GLOBAL void NMixGameDemo_HosiKiraKira_Delete( NMIX_DEMO_HOSI_KIRAKIRA* p_work );
GLOBAL void NMixGameDemo_HosiKiraKira_GraphicLoad( NMIX_DEMO_HOSI_KIRAKIRA* p_work, NMIXGAME_CLACT_SYS* p_clact, NMIXGAME_CLACT_RES_WORK* p_def_oam_res, u32 heapID );
GLOBAL void NMixGameDemo_HosiKiraKira_GraphicRelease( NMIX_DEMO_HOSI_KIRAKIRA* p_work );
GLOBAL void NMixGameDemo_HosiKiraKira_Main( NMIX_DEMO_HOSI_KIRAKIRA* p_work );
GLOBAL void NMixGameDemo_HosiKiraKira_Add( NMIX_DEMO_HOSI_KIRAKIRA* p_work, int x, int y );



//-----------------------------------------------------------------------------
/**
 *			ポルト表示
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	ポルト表示ワーク
//=====================================
typedef struct {
	PORUOAM_MAN* poruto_man;
	PORUTO_OAM* p_obj;
} NMIX_DEMO_PORUTO_DRAW;
GLOBAL void NMixGameDemo_PorutoDraw_Init( NMIX_DEMO_PORUTO_DRAW* p_work, int x, int y, int poruto_type, int heapID );
GLOBAL void NMixGameDemo_PorutoDraw_Delete( NMIX_DEMO_PORUTO_DRAW* p_work );
GLOBAL void NMixGameDemo_PorutoDraw_Draw( NMIX_DEMO_PORUTO_DRAW* p_work );
#define NMIX_DEMO_RESULT_PORUTO_DRAW_X	( 128 )
#define NMIX_DEMO_RESULT_PORUTO_DRAW_Y	( 144 )



//-----------------------------------------------------------------------------
/**
 *			YES　NO　ウィンドウ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	YES NO　ウィンドウ
//=====================================
typedef struct {
	TOUCH_SW_SYS* yes_no;
	GF_BGL_INI* p_bgl;
} NMIX_DEMO_YESNO_WND;

GLOBAL void NMixGameDemo_YesNoWnd_Init( NMIX_DEMO_YESNO_WND* p_work, int heap, GF_BGL_INI* p_bgl );
GLOBAL void NMixGameDemo_YesNoWnd_Delete( NMIX_DEMO_YESNO_WND* p_work );
GLOBAL void NMixGameDemo_YesNoWnd_Start( NMIX_DEMO_YESNO_WND* p_work );
GLOBAL u32 NMixGameDemo_YesNoWnd_Main( NMIX_DEMO_YESNO_WND* p_work );





#undef	GLOBAL
#endif		// __NMIX_GAME_DEMO_H__

