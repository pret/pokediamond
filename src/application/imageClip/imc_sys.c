//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_sys.c
 *	@brief		イメージクリップメインシステム
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include <string.h>
#include "touchpanel_system.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"
#include "include/contest/contest.h"
#include "src/contest/comm_command_contest.h"
#include "include/communication/comm_tool.h"

#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_left_box.h"
#include "include/application/imageClip/imc_hand.h"
#include "include/application/imageClip/imc_acce_hand.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_obj_list_func.h"
#include "include/application/imageClip/imc_button.h"
#include "include/system/wipe.h"
#include "include/application/imageClip/imc_subwin.h"
#include "include/application/imageClip/imc_rbox_player.h"
#include "include/application/imageClip/imc_snd_def.h"
#include "include/application/imageClip/imc_item_buff.h"

#include "include/system/pmfprint.h"

#include "include/communication/wm_icon.h"

#include "imc_calc.h"


#define __IMC_SYS_H_GLOBAL
#include "include/application/imageClip/imc_sys.h"


#ifdef PM_DEBUG

#define IMC_DEBUG

#endif


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	メインプロック
//	シーケンス設定
//	
//=====================================
enum{
	IMC_SYS_SEQ_START_TIMING_WAIT,
	IMC_SYS_SEQ_FADE_IN,
	IMC_SYS_SEQ_FADE_IN_WAIT,
	IMC_SYS_SEQ_REFERENCE_ON,
	IMC_SYS_SEQ_REFARENCE_WAIT,
	IMC_SYS_SEQ_KET_WAIT,
	IMC_SYS_SEQ_MAIN,			// イメージクリップ作成メイン
	IMC_SYS_SEQ_END_CHECK_WAIT,
	IMC_SYS_SEQ_END_CHECK,		// 終了チェック
	IMC_SYS_SEQ_SAVE_CHECK,		// セーブチェック
	IMC_SYS_SEQ_MAIN_WAIT,
	IMC_SYS_SEQ_FADE_OUT,
	IMC_SYS_SEQ_FADE_OUT_WAIT,
};

//-------------------------------------
//	
//	メインプロック
//	シーケンス設定
//	コンテスト
//	
//=====================================
enum{
	IMC_SYS_CON_SEQ_CON_SND_FADE,
	IMC_SYS_CON_SEQ_CON_SND_FADE_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_THEME_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_THEME_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_ON,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_LAST_DOUKI,
	IMC_SYS_CON_SEQ_START_TIMING_WAIT,
	IMC_SYS_CON_SEQ_CON_TEXT_END,
	IMC_SYS_CON_SEQ_FADE_IN,
	IMC_SYS_CON_SEQ_FADE_IN_WAIT,
	IMC_SYS_CON_SEQ_MAIN,			// イメージクリップ作成メイン
	IMC_SYS_CON_SEQ_EX_END_WAIT,	// 強制終了待ち
	IMC_SYS_CON_SEQ_END_CHECK_WAIT,
	IMC_SYS_CON_SEQ_END_CHECK,		// 終了チェック
	IMC_SYS_CON_SEQ_SAVE_CHECK,		// セーブチェック
	IMC_SYS_CON_SEQ_MAIN_WAIT,
	IMC_SYS_CON_SEQ_FADE_OUT,
	IMC_SYS_CON_SEQ_FADE_OUT_WAIT,
};

//-------------------------------------
//	
//	実行状態
//	
//=====================================
enum{
	IMC_SYS_ACCE,		// アクセサリ変更
	IMC_SYS_BG,			// BG変更
	IMC_SYS_SND,		// サウンド変更
	IMC_SYS_END_CHECK_REQ,// 終了チェックリクエスト
	IMC_SYS_END_CHECK,	// 終了チェック
	IMC_SYS_SAVE_CHECK_REQ,	// セーブチェック
	IMC_SYS_SAVE,		// セーブチェック
	IMC_SYS_SAVE_CAN,	// セーブCANCEL
	IMC_SYS_END_REQ,	// 終了リクエスト
	IMC_SYS_END_CANCEL_REQ,	// 終了キャンセルリクエスト
	IMC_SYS_END,		// 終了
};

//-------------------------------------
//	
//	終了確認画面へのフェード
//	
//=====================================
enum
{
	IMC_SEENFADEIN_ACCE_FADEOUT,
	IMC_SEENFADEIN_ACCE_FADEWAIT,
	IMC_SEENFADEIN_BRIGHTNESS_OUT,
	IMC_SEENFADEIN_BRIGHTNESS_WAIT,
	IMC_SEENFADEIN_BUTTON_OLDOUT,
//	IMC_SEENFADEIN_BUTTON_CHG,
	IMC_SEENFADEIN_MOVE_BG,
	IMC_SEENFADEIN_MOVE_BGINIT,
//	IMC_SEENFADEIN_BUTTON_NEWIN,
	IMC_SEENFADEIN_BRIGHTNESS_IN,
	IMC_SEENFADEIN_BRIGHTNESS_INWAIT,
	IMC_SEENFADEIN_END
};
enum
{
	IMC_SEENFADEOUT_BRIGHTNESS_OUT,
	IMC_SEENFADEOUT_BRIGHTNESS_OUTWAIT,
//	IMC_SEENFADEOUT_BUTTON_OLDOUT,
//	IMC_SEENFADEOUT_BUTTON_CHG,
	IMC_SEENFADEOUT_MOVE_BG_SET,
	IMC_SEENFADEOUT_MOVE_BG,
	IMC_SEENFADEOUT_BUTTON_NEWIN,
	IMC_SEENFADEOUT_BRIGHTNESS_IN,
	IMC_SEENFADEOUT_BRIGHTNESS_WAIT,
	IMC_SEENFADEOUT_ACCE_FADEIN,
	IMC_SEENFADEOUT_ACCE_FADEWAIT,
	IMC_SEENFADEOUT_END
};

//-------------------------------------
//	アクセサリがつながってポケモンとくっついているか
//	チェックするシステムのオブジェクト数
//=====================================
#define IMC_POKEON_ACCE_CHECK_OBJNUM	( IMC_RBOX_OBJ_CONTEST_MAX )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	イメージクリップデータ構造体
//	
//=====================================
typedef struct {
	// 描画関係
	IMC_DRAW_DATA drawSys;

	// アイテムバッファ
	IMC_ITEM_BUFF item_buff;

	// オブジェクトリストデータ
	IMC_OBJLIST_TBL	objListTbl;

	// アクセサリデータ
	IMC_ACCESSORIE_OBJ_TBL* acce;

	// 左画面データ
	IMC_LEFT_BOX lbox;
	
	// 右画面データ
	IMC_RIGHT_BOX rbox;
	IMC_RBOX_PLAYER rbox_player;		// 右ボックスプレイヤー
	
	// ハンドデータ
	IMC_HAND hand;

	// フレームBG
	IMC_BG	frame_bg;
	
	// ボタンデータ
	IMC_BUTTON_DATA bttn;				// 作成時
		
	// サブウィンドウ
	IMC_SUBWIN	subwin;

	int state;		// 今の実行状態

	int effect;		// エフェクト処理用

	// ハイイイエ　ウィンドウ
	TOUCH_SW_SYS* p_tsw;
	GF_BGL_BMPWIN* p_tsw_bmp;	// 終了確認ウィンドウ

	// セーブフラグ
	BOOL save_flag;

	// アクセサリ最大数
	int acce_max;

	//　コンテスト用
	int rank;			// ランク
	int mode;			// モード
	int type;			// ﾀｲﾌﾟ
	int theme;			// てーま
	CON_IMC_LOCAL* p_comm_data;	// 通信データ	

	const CONFIG* cp_config;	// コンフィグデータ
	u32 msg_idx;
	STRBUF* p_glb_str;		// グローバル文字列バッファ
	WORDSET* p_wordset;		// ワードセット
	
} IMC_SYS_WORK;

//-------------------------------------
//	
//	フェード処理用ワーク
//	
//=====================================
typedef struct {
	IMC_SYS_WORK* sys_w;	// システムワーク
	BOOL*	end;			// 終了検知フラグ
	int		work;			// ワークフラグ
	int		seq;			// シーケンス
} IMC_SYS_FADE_WORK;


//-------------------------------------
//	アクセサリがつながってポケモンとくっついているか
//	チェックする１オブジェクトデータ
//=====================================
typedef struct {
	IMC_OBJLIST* obj;
	u32 pokemon_data;	// ポケモンにくっついていない:0  ポケモンにくっついている:それ以外
} IMC_POKE_ON_ACCEOBJ;

//-------------------------------------
//	アクセサリがつながってポケモンとくっついているか
//	チェックするシステム
//=====================================
typedef struct {
	IMC_POKE_ON_ACCEOBJ	obj[ IMC_RBOX_OBJ_CONTEST_MAX ];
	int set_num;
} IMC_POKE_ON_ACCESYS;
//-------------------------------------
//	アクセサリがつながってポケモンとくっついているか
//	チェック定数
//=====================================
enum{
	IMC_POKEON_ACCE_NONE,		// つながっていない
	IMC_POKEON_ACCE_ON,			// つながっている
	IMC_POKEON_ACCE_SEARCHEND	// つながっている＆SEARCH済み
};



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void imageClipVBlankFunc( void* work );

static void initDrawSys( IMC_SYS_WORK* imc_w );
static void mainDrawSys( IMC_SYS_WORK* imc_w );
static void deleteDrawSys( IMC_SYS_WORK* imc_w );

static void initRightBox( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max );
static void initRightBox_Contest( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max );
static void deleteRightBox( IMC_SYS_WORK* imc_w );

static void initLeftBox( IMC_SYS_WORK* imc_w );
static void deleteLeftBox( IMC_SYS_WORK* imc_w );
static void setLeftBoxBg( IMC_SYS_WORK* imc_w );

static void setFrameBG( IMC_SYS_WORK* imc_w, int no );
static void delFrameBG( IMC_SYS_WORK* imc_w );

static void initBttn( IMC_SYS_WORK* imc_w );
static void initBttn_Contest( IMC_SYS_WORK* imc_w );
static void deleteBttn( IMC_SYS_WORK* imc_w );
static void mainBttn( IMC_SYS_WORK* imc_w );
static void resetBttn( IMC_SYS_WORK* imc_w );

static void endBttn( IMC_BUTTON* bttn, void* work );
static void retBttn( IMC_BUTTON* bttn, void* work );
static void retbBttn( IMC_BUTTON* bttn, void* work );
static void	acceBttn( IMC_BUTTON* bttn, void* work );
static void	bgBttn( IMC_BUTTON* bttn, void* work );

static void endCkEndBttn( IMC_BUTTON* bttn, void* work );
static void endCkCancelBttn( IMC_BUTTON* bttn, void* work );

static void initSubWin( IMC_SYS_WORK* imc_w, const CONFIG* cp_config );
static void initSubWin_Contest( IMC_SYS_WORK* imc_w, int acce_num, int thema, CON_IMC_LOCAL* p_comm_data, const CONFIG* cp_config );
static void deleteSubWin( IMC_SYS_WORK* imc_w );

static void endSeenFadeIn( IMC_SYS_WORK* imc_w, BOOL* end );
static void endSeenFadeInTask( TCB_PTR tcb, void* work );
static void endSeenFadeOut( IMC_SYS_WORK* imc_w, BOOL* end );
static void endSeenFadeOutTask( TCB_PTR tcb, void* work );
static BOOL endSeenFadeMoveBg( IMC_SYS_FADE_WORK* fade_w, int move_x, int move_y, int move_count_num );

static void dataSave( IMC_TELEVISION_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, const MYSTATUS* cp_tr );
static void dataSave_Contest( IMC_CONTEST_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, int rank, const MYSTATUS* cp_tr );

static void initConTextSys( IMC_SYS_WORK* imc_w );
static void deleteConTextSys( IMC_SYS_WORK* imc_w );

static void initTouchSWSys( IMC_SYS_WORK* imc_w );
static void deleteTouchSWSys( IMC_SYS_WORK* imc_w );
static u32 mainTouchSWSys( IMC_SYS_WORK* imc_w );
static void initTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w );
static u32 mainTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w );

static void initTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void setTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void deleteTouchSWBmpWin( IMC_SYS_WORK* imc_w );

static void initContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static u32 setContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static void setContestWordSet( IMC_SYS_WORK* imc_w, int buff_id, int no );
static void endContestTextBmpWin( IMC_SYS_WORK* imc_w );
static void deleteContestTextBmpWin( IMC_SYS_WORK* imc_w );

static void initMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx, u8 cx, u8 cy, u8 csx, u8 csy );
static void setMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx );
static u32 setMsgBmpWin_okuri( IMC_SYS_WORK* imc_w, u32 str_idx );
static void endMsgBmpWin_okuri( IMC_SYS_WORK* imc_w );
static void deleteMsgBmpWin( IMC_SYS_WORK* imc_w );

static void setAcceNumSubWin( IMC_SYS_WORK* imc_w );

static int getRightAcceMax_contest( int rank );

static void initPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys );
static void setPokeOnAcceCheckObj( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* obj, u32 init_data );
static void mainPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys );
static IMC_OBJLIST* getPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, u32 no );
static BOOL getPokeOnAcceCheckObjOnPoke( IMC_POKE_ON_ACCESYS* p_sys, u32 no );
static BOOL checkPokeOnAcceCalc( IMC_POKE_ON_ACCEOBJ* p_obj, IMC_POKE_ON_ACCEOBJ* p_check_obj );

static void setPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* dummy, u32 init_data );

static void Imc_OyaExEndCheck( IMC_SYS_WORK* imc_w );

//-----------------------------------------------------------------------------
/**
 *					通常
 * [JAMP_NORMAL]
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロック生成
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcInit( PROC* proc, int* seq )
{
	IMC_SYS_WORK*	imc_w;			// イメージクリップワーク
	u32				check;			// ﾁｪｯｸ用
	IMC_PROC_WORK*  p_imc_pr_w;		// 外部から受け取るデータ


	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// イメージクリップワーク作成
	imc_w = PROC_AllocWork( proc, sizeof( IMC_SYS_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( imc_w, 0, sizeof( IMC_SYS_WORK ) );

	// VブランクHブランク関数設定
	sys_VBlankFuncChange( imageClipVBlankFunc, imc_w );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止


	// 外部からのデータを取得
	p_imc_pr_w = PROC_GetParentWork( proc );

	// 外部からのデータ設定
	imc_w->cp_config = p_imc_pr_w->cp_config;

	// タッチパネルオートサンプリング開始
	InitTPSystem();
	check = InitTPNoBuff( 4 );
//	GF_ASSERT( check == TP_OK );
	if( check != TP_OK ){
		OS_Printf( "check != TP_OK\n" );
	}
//	while( InitTPNoBuff( 4 ) != TP_OK ){};

	// アイテムバッファ作成
	IMC_ITEM_BUFF_Make( p_imc_pr_w->cp_imc_item, &imc_w->item_buff );

	// 表示設定
	initDrawSys( imc_w );

	// オブジェクトリストテーブル作成
	IMC_OBJLIST_TblInit( &imc_w->objListTbl, IMC_OBJLIST_MAX, HEAPID_IMAGECLIP_DATA );
	
	// アクセサリ格納データ作成
	imc_w->acce = IMC_ACCE_ObjTblInit( IMC_SYS_ACCESSORIE_MAX, HEAPID_IMAGECLIP_DATA );

	// 右ボックスデータ作成
	initRightBox( imc_w, p_imc_pr_w->p_poke_para, IMC_RBOX_ACCE_TELEVISION_MAX );
	
	// 左ボックスデータ作成
	initLeftBox( imc_w );

	// フレームBGを表示
	setFrameBG( imc_w, IMC_BG_FRAME_00 );
	
	// ボタンデータ作成
	initBttn( imc_w );

	// サブウィンドウ初期化
	initSubWin( imc_w, p_imc_pr_w->cp_config );

	// ハンドデータ初期化
	IMC_ACCE_HAND_Init( &imc_w->hand, &imc_w->rbox, &imc_w->lbox, &imc_w->drawSys, &imc_w->subwin, TRUE );

	// はい　いいえ　ウィンドウメモリ確保
	imc_w->p_tsw = TOUCH_SW_AllocWork( HEAPID_IMAGECLIP_DATA );
	imc_w->p_tsw_bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DATA, 1 );

	// 状態設定
	// 状態	普通
	imc_w->state = IMC_SYS_ACCE;

	// サウンドデータロード(イメージクリップ)(BGM引継ぎ)
	Snd_DataSetByScene( SND_SCENE_SUB_IMAGE, 0, 0 );
	
	return PROC_RES_FINISH;
}

#ifdef IMC_DEBUG
extern void IMC_POKE_DEBUG_ChangePoke( IMC_POKE* poke, int heap, IMC_DRAW_DATA* drawData );
#endif

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロックメイン
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcMain( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	PROC_RESULT	ret = PROC_RES_CONTINUE;
	IMC_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// データセーブ

	switch( (*seq) ){
	case IMC_SYS_SEQ_START_TIMING_WAIT:
	case IMC_SYS_SEQ_FADE_IN:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_TYPE_SHUTTERIN_UP,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq)  = IMC_SYS_SEQ_FADE_IN_WAIT;
		break;
		
	case IMC_SYS_SEQ_FADE_IN_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) ++;
		}
		break;

	case IMC_SYS_SEQ_REFERENCE_ON:
		if( p_pr_w->reference == TRUE ){

			MsgPrintTouchPanelFlagSet(MSG_TP_ON);

			imc_w->msg_idx = IMC_SUBWIN_SetBmpWinWait( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_manual_01 );
			(*seq) ++;
		}else{
			(*seq) = IMC_SYS_SEQ_MAIN;
		}
		break;
		
	case IMC_SYS_SEQ_REFARENCE_WAIT:
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			IMC_SUBWIN_EndBmpWinWait( &imc_w->subwin );
			(*seq) ++;
		}
		break;

	case IMC_SYS_SEQ_KET_WAIT:
		if( (sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) | (sys.tp_trg) ){
			IMC_SUBWIN_SetBmpWin( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, imgclip_manual_02 );

			MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
			(*seq) ++;
		}
		break;

	//-------------------------------------
	//	
	//	メイン処理
	//	
	//=====================================
	case IMC_SYS_SEQ_MAIN:

		if(imc_w->state == IMC_SYS_END_CHECK_REQ){
			// フェード開始
			endSeenFadeIn( imc_w, &imc_w->effect );
			// フェードアウト
			(*seq) = IMC_SYS_SEQ_END_CHECK_WAIT;
		}

		// ハンド処理
		IMC_HAND_Main( &imc_w->hand );

		// 右ボックスのアクセサリ数を設定
		setAcceNumSubWin( imc_w );

#ifdef IMC_DEBUG
		IMC_POKE_DEBUG_ChangePoke( &imc_w->rbox.boxDraw.poke, HEAPID_IMAGECLIP_DRAW, &imc_w->drawSys );
#endif

		// サブウィンドウメイン
		IMC_SUBWIN_Main( &imc_w->subwin );
		
		// ボタン処理
		mainBttn( imc_w );
		break;

	case IMC_SYS_SEQ_END_CHECK_WAIT:	// 終了チェックフェード待ち
		if( imc_w->effect ){
			imc_w->effect = FALSE;
			(*seq) = IMC_SYS_SEQ_END_CHECK;
			imc_w->state = IMC_SYS_END_CHECK;

			// 右ボックスプレイヤー作成
			IMC_RBOX_PLAYER_Init( &imc_w->rbox_player, &imc_w->rbox, HEAPID_IMAGECLIP_DRAW );
		}
		break;

	case IMC_SYS_SEQ_END_CHECK:			// 終了チェック動作
		
		// キャンセルチェック
		if( imc_w->state == IMC_SYS_END_CANCEL_REQ ){
			// フェード開始
			endSeenFadeOut( imc_w, &imc_w->effect );
			(*seq) = IMC_SYS_SEQ_MAIN_WAIT;
			break;
		}

		// 終了チェック
		if( imc_w->state == IMC_SYS_END_REQ ){
			(*seq) = IMC_SYS_SEQ_SAVE_CHECK;
			imc_w->state = IMC_SYS_SAVE_CHECK_REQ;
			
			initTouchSaveCheckSWSys( imc_w );	// セーブチェックボタン作成
			break;
		}
		
		// ボタン処理
		imc_w->state = mainTouchSWSys( imc_w );

		// 右ボックスプレイヤー
		IMC_RBOX_PLAYER_Main( &imc_w->rbox_player );
		break;

	case IMC_SYS_SEQ_SAVE_CHECK:	// セーブチェック
		if( imc_w->state == IMC_SYS_SAVE ){
			imc_w->save_flag = TRUE;
			(*seq) = IMC_SYS_SEQ_FADE_OUT;
			break;
		}
		if( imc_w->state == IMC_SYS_SAVE_CAN ){
			imc_w->save_flag = FALSE;
			(*seq) = IMC_SYS_SEQ_FADE_OUT;
			break;
		}

		// ボタン処理
		imc_w->state = mainTouchSaveCheckSWSys( imc_w );

		// 右ボックスプレイヤー
		IMC_RBOX_PLAYER_Main( &imc_w->rbox_player );
		break;

	case IMC_SYS_SEQ_MAIN_WAIT:			// メイン画面フェード待ち
		if( imc_w->effect ){
			imc_w->effect = FALSE;
			(*seq) = IMC_SYS_SEQ_MAIN;
			imc_w->state = IMC_SYS_ACCE;		// アクセサリ変更ではじめる

			// 右ボックスプレイヤー終了
			IMC_RBOX_PLAYER_Delete( &imc_w->rbox_player );
		}
		break;
		
	case IMC_SYS_SEQ_FADE_OUT:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_FADEOUT,
				WIPE_TYPE_FADEOUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );
		(*seq) ++;
		break;

	case IMC_SYS_SEQ_FADE_OUT_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) = 0;
			imc_w->state = IMC_SYS_END;
			ret = PROC_RES_FINISH;

			// 右ボックスプレイヤー終了
			IMC_RBOX_PLAYER_Delete( &imc_w->rbox_player );
		}
		break;
	}

	///////////////////////////////////////////////
	//
	//	ここは共通処理
	//
	//////////////////////////////////////////////
	// 描画処理
	mainDrawSys( imc_w );
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロック終了
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcEnd( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	u32	check;	// ﾁｪｯｸ用
	IMC_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// データセーブ

	// データをセーブ
	if( imc_w->save_flag == TRUE ){
		// レコードデータ　スコア足し算処理
		RECORD_Score_Add( p_pr_w->p_record, SCORE_ID_MAKE_CLIP );
		
		dataSave( p_pr_w->p_imc_one_data, &imc_w->rbox, p_pr_w->cp_tr );	
	}

	// セーブ有無設定
	if( p_pr_w->p_save_flg != NULL ){
		if( imc_w->save_flag == TRUE ){
			*p_pr_w->p_save_flg = TRUE;
		}else{
			*p_pr_w->p_save_flg = FALSE;
		}
	}

	// ハイイイエウィンドウメモリ破棄
	TOUCH_SW_FreeWork( imc_w->p_tsw );	
	GF_BGL_BmpWinFree( imc_w->p_tsw_bmp, 1 );
	
	// サブウィンドウ破棄
	deleteSubWin( imc_w );
	
	// ハンド情報破棄
	IMC_ACCE_HAND_Delete( &imc_w->hand );

	// ボタン破棄
	deleteBttn( imc_w );
	
	// フレームBGを破棄
	delFrameBG( imc_w );
	
	// 右ボックス破棄
	deleteRightBox( imc_w );
	
	// 左ボックス破棄
	deleteLeftBox( imc_w );
	
	// アクセサリ格納データ破棄
	IMC_ACCE_ObjTblDelete( imc_w->acce );
	imc_w->acce = NULL;
	
	// オブジェクトリストテーブル破棄
	IMC_OBJLIST_TblDelete( &imc_w->objListTbl );
	
	deleteDrawSys( imc_w );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// タッチパネルサンプリング終了
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// ワーク破棄
	PROC_FreeWork( proc );

	// ヒープ破棄
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );
	
	return PROC_RES_FINISH;
}





//-----------------------------------------------------------------------------
/**
 *					コンテスト用
 * [JAMP_CONTEST]
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロック生成
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestInit( PROC* proc, int* seq )
{
	IMC_SYS_WORK*	imc_w;			// イメージクリップワーク
	u32				check;			// ﾁｪｯｸ用
	IMC_CONTEST_PROC_WORK*  p_imc_pr_w;		// 外部から受け取るデータ


	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DATA, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_IMAGECLIP_DRAW, 0x40000 );

	// イメージクリップワーク作成
	imc_w = PROC_AllocWork( proc, sizeof( IMC_SYS_WORK ), HEAPID_IMAGECLIP_DATA );
	memset( imc_w, 0, sizeof( IMC_SYS_WORK ) );

	// VブランクHブランク関数設定
	sys_VBlankFuncChange( imageClipVBlankFunc, imc_w );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止


	// 外部からのデータを取得
	p_imc_pr_w = PROC_GetParentWork( proc );

	// コンテスト情報取得
	imc_w->rank = p_imc_pr_w->rank;
	imc_w->mode = p_imc_pr_w->mode;
	imc_w->type = p_imc_pr_w->type;
	imc_w->theme = p_imc_pr_w->theme;
	imc_w->p_comm_data = p_imc_pr_w->p_comm_data;

	OS_Printf( "コンテストテーマ　%d ランク %d \n", p_imc_pr_w->theme, p_imc_pr_w->rank );

	// タッチパネルオートサンプリング開始
	InitTPSystem();
	check = InitTPNoBuff( 4 );
//	GF_ASSERT( check == TP_OK );
	if( check != TP_OK ){
		OS_Printf( "check != TP_OK\n" );
	}
//	while( InitTPNoBuff( 4 ) != TP_OK ){};


	// アイテムバッファ作成
	IMC_ITEM_BUFF_Make( p_imc_pr_w->cp_imc_item, &imc_w->item_buff );

	
	// 表示設定
	initDrawSys( imc_w );

	// 最初アクターセット非表示
	CLACT_DrawFlagSet( imc_w->drawSys.clactSet, 0 );

	// COMM_ICON設定
	WirelessIconEasy();	

	// キャラクタマネージャにキャラクタ領域を予約
	CLACT_U_WmIcon_SetReserveAreaCharManager( NNS_G2D_VRAM_TYPE_2DMAIN, GX_OBJVRAMMODE_CHAR_1D_32K );
	CLACT_U_WmIcon_SetReserveAreaPlttManager( NNS_G2D_VRAM_TYPE_2DMAIN );

	// オブジェクトリストテーブル作成
	IMC_OBJLIST_TblInit( &imc_w->objListTbl, IMC_OBJLIST_MAX, HEAPID_IMAGECLIP_DATA );
	
	// アクセサリ格納データ作成
	imc_w->acce = IMC_ACCE_ObjTblInit( IMC_SYS_ACCESSORIE_MAX, HEAPID_IMAGECLIP_DATA );

	// 外部からのデータ設定
	imc_w->cp_config = p_imc_pr_w->cp_config;


	// 右ボックスデータ作成
	if( imc_w->p_comm_data->sio_flag == 0 ){
		imc_w->acce_max = getRightAcceMax_contest( p_imc_pr_w->rank );	
	}else{
		imc_w->acce_max = CON_IMAGE_ACCE_MAX_SIO;
	}
	initRightBox_Contest( imc_w, p_imc_pr_w->p_poke_para, imc_w->acce_max );
		
	
	// 左ボックスデータ作成
	initLeftBox( imc_w );

	// フレームBGを表示
	setFrameBG( imc_w, IMC_BG_FRAME_00 );
	
	// ボタンデータ作成
	initBttn_Contest( imc_w );

	// サブウィンドウ初期化
	initSubWin_Contest( imc_w, imc_w->acce_max, p_imc_pr_w->theme, p_imc_pr_w->p_comm_data, p_imc_pr_w->cp_config );

	// ハンドデータ初期化
	IMC_ACCE_HAND_Init( &imc_w->hand, &imc_w->rbox, &imc_w->lbox, &imc_w->drawSys, &imc_w->subwin, FALSE );

	// はい　いいえ　ウィンドウメモリ確保
	imc_w->p_tsw = TOUCH_SW_AllocWork( HEAPID_IMAGECLIP_DATA );
	imc_w->p_tsw_bmp = GF_BGL_BmpWinAllocGet( HEAPID_IMAGECLIP_DATA, 1 );

	// 状態設定
	// 状態	普通
	imc_w->state = IMC_SYS_ACCE;

	// メッセージ設定
	ConTool_MsgPrintFlagSet( imc_w->p_comm_data->sio_flag );
	
	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロックメイン
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestMain( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	PROC_RESULT	ret = PROC_RES_CONTINUE;
	int count;

	switch( (*seq) ){
	case IMC_SYS_CON_SEQ_CON_SND_FADE:
		Snd_BgmFadeOut( BGM_VOL_CLIP, BGM_FADE_CLIP_TIME );
		(*seq) ++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_SND_FADE_WAIT:
		if( Snd_FadeCheck() == 0 ){
			(*seq) ++;
		}
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_ON:
		initConTextSys( imc_w );

		// 各ランクのアクセサリ数をワードセットに設定
		setContestWordSet( imc_w, 0, imc_w->acce_max );
		
		if( imc_w->mode != CONMODE_VISUAL_PRACTICE ){
			// 本番テキスト
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_du_b_01 );
		}else{
			// 練習テキスト
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_prac_01 );
		}
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_WAIT:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;


	case IMC_SYS_CON_SEQ_CON_TEXT_THEME_ON:
		// THEME発表
		imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_theme_01 + imc_w->theme );
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_THEME_WAIT:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;

	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_ON:
		// 最後の開始！！という言葉
		if( imc_w->mode != CONMODE_VISUAL_PRACTICE ){
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_after_theme_02 );
		}else{
			imc_w->msg_idx = setContestTextBmpWin( imc_w, msg_con_v_after_theme_01 );
		}
		(*seq)++;
		break;
		
	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_WAIT:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( imc_w->msg_idx ) == 0 ){
			endContestTextBmpWin( imc_w );
			(*seq)++;
		}
		break;


	case IMC_SYS_CON_SEQ_CON_TEXT_LAST_DOUKI:
		// 同期コマンドを転送
		if( imc_w->p_comm_data->sio_flag ){
			CommTimingSyncStart( CONSIO_TIMING_CALL_IN_IMCPROC );
		}
		(*seq)++;
		break;

	case IMC_SYS_CON_SEQ_START_TIMING_WAIT:	// 同期待ち
		// 通信しているときは
		// 同期待ち
		if( imc_w->p_comm_data->sio_flag ){
			if( CommIsTimingSync( CONSIO_TIMING_CALL_IN_IMCPROC ) ){
				(*seq)++;
			}
		}else{
			(*seq)++;
		}
		break;

		
	case IMC_SYS_CON_SEQ_CON_TEXT_END:
		deleteConTextSys( imc_w );
		// 音を鳴らす
		Snd_SePlay( IMC_SE_CON_START );
		(*seq)++;
		break;
	
	
	case IMC_SYS_CON_SEQ_FADE_IN:
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_HOLEIN,
				WIPE_TYPE_TUNNELIN,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );

//		WirelessIconEasyXY( 0, 176, FALSE );	
		(*seq) ++;
		break;
		
	case IMC_SYS_CON_SEQ_FADE_IN_WAIT:
		if( WIPE_SYS_EndCheck() ){

			// サウンドデータロード(コンテストイメージクリップ)(BGM切り替え)
			//Snd_DataSetByScene( SND_SCENE_SUB_IMAGE, 0, 0 );
			Snd_DataSetByScene( SND_SCENE_CON_IMAGE, SEQ_CO_DRESS, 0 );

			(*seq) ++;
		}
		break;

	//-------------------------------------
	//	
	//	メイン処理
	//	
	//=====================================
	case IMC_SYS_CON_SEQ_MAIN:

		// 終了ボタンが押されたときの処理
		if(imc_w->state == IMC_SYS_END_CHECK_REQ){
			// 親に終了をコール
			CommContestSendImcForceEnd( imc_w->p_comm_data, TRUE );

			// 通信しているときは上に待っての文字を出す
			if( imc_w->p_comm_data->sio_flag ){
				IMC_SUBWIN_SetBmpWin( &imc_w->subwin, ARC_MSG, NARC_msg_imageclip_dat, msg_con_caution_01 );
			}
			
			(*seq)  = IMC_SYS_CON_SEQ_EX_END_WAIT;
			break;
		}

#ifdef IMC_DEBUG
		{
			static BOOL COUNTER_END_FLG = TRUE;
			if( sys.trg & PAD_BUTTON_L ){
				COUNTER_END_FLG ^= 1;
			}
			
			// カウンターが０になったら終わり
			count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
			if(0 == count){
				(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
				// 音を鳴らす
				Snd_SePlay( IMC_SE_CON_FINISH );
			}

			// ハンド処理
			IMC_HAND_Main( &imc_w->hand );

			// 右ボックスのアクセサリ数を設定
			setAcceNumSubWin( imc_w );

			// FALSEなら終わらない
			if( COUNTER_END_FLG == TRUE ){
				// サブウィンドウメイン
				IMC_SUBWIN_Main( &imc_w->subwin );
			}
			
			// ボタン処理
			mainBttn( imc_w );

		}
#else
		// カウンターが０になったら終わり
		count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
		if(0 == count){
			(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
			// 音を鳴らす
			Snd_SePlay( IMC_SE_CON_FINISH );
		}

		// ハンド処理
		IMC_HAND_Main( &imc_w->hand );

		// 右ボックスのアクセサリ数を設定
		setAcceNumSubWin( imc_w );

		// サブウィンドウメイン
		IMC_SUBWIN_Main( &imc_w->subwin );
		
		// ボタン処理
		mainBttn( imc_w );
#endif
		break;

	case IMC_SYS_CON_SEQ_EX_END_WAIT:	// 終わるを押しての強制終了待ち
		// カウンターが０になったら終わり
		count = IMC_SUBWIN_GetCounterNowNum( &imc_w->subwin );
		if(0 == count){
			(*seq)  = IMC_SYS_CON_SEQ_END_CHECK_WAIT;
			// 音を鳴らす
			Snd_SePlay( IMC_SE_CON_FINISH );
		}

		// 右ボックスのアクセサリ数を設定
		setAcceNumSubWin( imc_w );

		// サブウィンドウメイン
		IMC_SUBWIN_Main( &imc_w->subwin );

		// 強制終了チェック
		Imc_OyaExEndCheck( imc_w );
		
		break;

	case IMC_SYS_CON_SEQ_END_CHECK_WAIT:
		// サブウィンドウメイン
		IMC_SUBWIN_Main( &imc_w->subwin );
		// ちゃんとカウンターのｴﾌｪｸﾄが終わったら終了
		if( IMC_SUBWIN_GetCounterEffectEnd( &imc_w->subwin ) ){
			(*seq) = IMC_SYS_CON_SEQ_FADE_OUT;
		}
		break;
		
	case IMC_SYS_CON_SEQ_FADE_OUT:

		// 音が終わるのを待つ
		if( Snd_SePlayCheck( IMC_SE_CON_FINISH ) == TRUE ){
			break;
		}
		
		WIPE_SYS_Start( 
				WIPE_PATTERN_FMAS,
				WIPE_TYPE_DOOROUT,
				WIPE_TYPE_DOOROUT,
				WIPE_FADE_BLACK,
				WIPE_DEF_DIV,WIPE_DEF_SYNC,
				HEAPID_IMAGECLIP_DATA );

		Snd_SePlay( IMC_SE_CON_DOOR_CLOSE );
		(*seq) ++;
		break;

	case IMC_SYS_CON_SEQ_FADE_OUT_WAIT:
		if( WIPE_SYS_EndCheck() ){
			(*seq) = 0;
			imc_w->state = IMC_SYS_END;
			ret = PROC_RES_FINISH;

			// ウィンドウの初期化
			GX_SetVisibleWnd( GX_WNDMASK_NONE );
			
			// 右ボックスのデータを終了座標まで動かしておく
			IMC_RBOX_ListMove( &imc_w->rbox, -(IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT), (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT) );
		}
		break;
	}

	///////////////////////////////////////////////
	//
	//	ここは共通処理
	//
	//////////////////////////////////////////////
	// 描画処理
	mainDrawSys( imc_w );
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリッププロック終了
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT IMC_ProcContestEnd( PROC* proc, int* seq )
{
	IMC_SYS_WORK* imc_w = PROC_GetWork( proc );
	u32	check;	// ﾁｪｯｸ用
	IMC_CONTEST_PROC_WORK* p_pr_w = PROC_GetParentWork( proc );	// データセーブ

	OS_Printf( "コンテストテーマ　%d ランク %d \n", imc_w->theme, imc_w->rank );

	// データをセーブ
	dataSave_Contest( p_pr_w->p_imc_one_data, &imc_w->rbox, imc_w->rank, p_pr_w->cp_tr );	

	// ハイイイエウィンドウメモリ破棄
	TOUCH_SW_FreeWork( imc_w->p_tsw );	
	GF_BGL_BmpWinFree( imc_w->p_tsw_bmp, 1 );
	
	// サブウィンドウ破棄
	deleteSubWin( imc_w );
	
	// ハンド情報破棄
	IMC_ACCE_HAND_Delete( &imc_w->hand );

	// ボタン破棄
	deleteBttn( imc_w );
	
	// フレームBGを破棄
	delFrameBG( imc_w );
	
	// 右ボックス破棄
	deleteRightBox( imc_w );
	
	// 左ボックス破棄
	deleteLeftBox( imc_w );
	
	// アクセサリ格納データ破棄
	IMC_ACCE_ObjTblDelete( imc_w->acce );
	imc_w->acce = NULL;
	
	// オブジェクトリストテーブル破棄
	IMC_OBJLIST_TblDelete( &imc_w->objListTbl );
	
	deleteDrawSys( imc_w );
	
	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// タッチパネルサンプリング終了
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// ワーク破棄
	PROC_FreeWork( proc );

	// ヒープ破棄
	sys_DeleteHeap( HEAPID_IMAGECLIP_DATA );
	sys_DeleteHeap( HEAPID_IMAGECLIP_DRAW );

	// メッセージ設定
	ConTool_MsgPrintFlagReset();

	WirelessIconEasyEnd();

	
	return PROC_RES_FINISH;
}




//-----------------------------------------------------------------------------
/**
*		プライベート関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム初期化
 *
 *	@param	imc_w	システムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initDrawSys( IMC_SYS_WORK* imc_w )
{
	IMC_DRAW_LOADRES_DATA loadData;	// 画像データ読み込みデータ

	// 画面データ設定
	IMC_DRAW_SetUp();

	// 描画システム作成
	IMC_DRAW_InitSys( &imc_w->drawSys );
	
	// 描画データ作成
	IMC_DRAW_MakeLoadSWSP_samp( &imc_w->drawSys, &loadData );

	// 描画データVram転送
	IMC_DRAW_LoadResource( &imc_w->drawSys, &loadData );

	// 描画データ破棄
	IMC_DRAW_DestLoadSWSP( &loadData );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムメイン
 *
 *	@param	imc_w	システムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainDrawSys( IMC_SYS_WORK* imc_w )
{
	IMC_DRAW_DrawSys( &imc_w->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム破棄
 *
 *	@param	imc_w	システムワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteDrawSys( IMC_SYS_WORK* imc_w )
{
	// 描画データ破棄
	IMC_DRAW_DeleteResource( &imc_w->drawSys );

	// 描画システム破棄
	IMC_DRAW_DeleteSys( &imc_w->drawSys );

	// 描画面設定破棄
	IMC_DRAW_PutBack();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスデータ作成
 *
 *	@param	imc_w	イメージクリップシステムデータ
 *	@param	pp		ポケモンパラメータ
 *	@param	acce_max	アクセサリ登録数最大数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initRightBox( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max )
{
	IMC_RIGHT_BOX_INIT	rbox_init;	// 右ボックス初期化データ

	// 右ボックスデータ作成
	// 描画データ
	rbox_init.SWSP_drawSys		= imc_w->drawSys.SWSP_drawSys;
	rbox_init.SWSP_charData		= imc_w->drawSys.SWSP_charData;
	rbox_init.SWSP_plttData		= imc_w->drawSys.SWSP_plttData;
	rbox_init.accePlttOfsTbl	= imc_w->drawSys.accePlttOfsTbl;
	rbox_init.SSM_drawSys		= imc_w->drawSys.SSM_drawSys;
	rbox_init.BG_Ini			= imc_w->drawSys.BG_Ini;
	rbox_init.acce_count_max	= acce_max;

	rbox_init.acce		= imc_w->acce;			// アクセサリデータ
	rbox_init.objListTbl= &imc_w->objListTbl;	// オブジェクトリストテーブル
	IMC_RBOX_InitSys( &imc_w->rbox, &rbox_init );
	
	// ポケモンを登録
	{
		SOFT_SPRITE_ARC	arc;
		IMC_RBOX_AddPoke( &imc_w->rbox, pp, &arc, HEAPID_IMAGECLIP_DRAW );

		// ポケモンキャラクタデータ登録
		IMC_POKE_CharSet( &imc_w->drawSys, &arc );
	}
/*
	// 右ボックスに配置するデータを作成
	{
		int i;
		for(i=0;i<IMC_ACCE_MAX; i++){
			int x,y;
			x = IMC_RBOX_AREA_X;
			y = IMC_RBOX_AREA_Y;
			
			IMC_RBOX_AddAccessorie( &imc_w->rbox, i, 
					x + (gf_mtRand() % (IMC_RBOX_AREA_WIDTH / 2)),
					y + (gf_mtRand() % (IMC_RBOX_AREA_HEIGHT / 2)) );
		}
	}//*/
	IMC_RBOX_SetObjPriority( &imc_w->rbox );

	// BGを表示
	IMC_RBOX_BGSet( &imc_w->rbox, IMC_BG_RIGHT_00, HEAPID_IMAGECLIP_DRAW );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　右ボックス初期化
 *
 *	@param	imc_w
 *	@param	pp
 *	@param	acce_max 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void initRightBox_Contest( IMC_SYS_WORK* imc_w, POKEMON_PARAM* pp, int acce_max )
{
	int size_x, size_y;
	int in_size_x, in_size_y;
	
	initRightBox( imc_w, pp, acce_max );

	// ポケモンサイズ取得
	IMC_POKE_SizeGet( &imc_w->rbox.boxDraw.poke, &size_x, &size_y );
	IMC_POKE_InSizeGet( &imc_w->rbox.boxDraw.poke, &in_size_x, &in_size_y );

	// コンテスト用座標設定
	IMC_POKE_MatrixSet( &imc_w->rbox.boxDraw.poke, IMC_POKE_INIT_X, (IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT) - ((size_y/2) - in_size_y) + IMC_POKE_MAT_CONTEST_Y_OFS );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスデータ破棄
 *
 *	@param	imc_w	イメージクリップシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteRightBox( IMC_SYS_WORK* imc_w )
{
	// BGをクリーン
	IMC_RBOX_BGClean( &imc_w->rbox );
	
	// 右ボックス配置データ破棄
	IMC_RBOX_DeleteAccessorieAll( &imc_w->rbox );
	
	// 右ボックスデータ破棄
	IMC_RBOX_DeleteSys( &imc_w->rbox );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスデータ作成
 *
 *	@param	imc_w	イメージクリップシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initLeftBox( IMC_SYS_WORK* imc_w )
{
	IMC_LEFT_BOX_INIT	lbox_init;	// 右ボックス初期化データ

	// 左ボックスデータ作成
	// 描画データ
	lbox_init.SWSP_drawSys		= imc_w->drawSys.SWSP_drawSys;
	lbox_init.SWSP_charData		= imc_w->drawSys.SWSP_charData;
	lbox_init.SWSP_plttData		= imc_w->drawSys.SWSP_plttData;
	lbox_init.accePlttOfsTbl	= imc_w->drawSys.accePlttOfsTbl;
	lbox_init.BG_Ini			= imc_w->drawSys.BG_Ini;
	lbox_init.p_item_buff		= &imc_w->item_buff;
	lbox_init.acce			= imc_w->acce;			// アクセサリデータ
	lbox_init.objListTbl	= &imc_w->objListTbl;	// オブジェクトリストテーブル
	lbox_init.accelist_num	= IMC_LBOX_ACCE_NEAD_LIST_NUM;	// リスト数
	lbox_init.bglist_num	= IMC_LBOX_BG_NEAD_LIST_NUM;	// リスト数
	lbox_init.sndlist_num	= IMC_LBOX_SND_NEAD_LIST_NUM;	// リスト数
	IMC_LBOX_InitSys( &imc_w->lbox, &lbox_init );

	// カレント先頭ダミーデータ作成
	IMC_LBOX_SetCurrentAccessorie( 
			&imc_w->lbox, 
			IMC_OBJLIST_ACCE,
			0 );


	// 左ボックスに配置するデータを作成
	{
		int i, j;
		int add_num;

		for(i=0;i<IMC_ACCE_MAX; i++){
			add_num = IMC_ITEM_BUFF_AcceGetNum( &imc_w->item_buff, i );
			for( j=0; j<add_num; j++ ){
				// 左ボックスアクセサリ配置
				IMC_LBOX_AddAccessorie( &imc_w->lbox, IMC_OBJLIST_ACCE, i );
			}
		}
		// BGサムネイルを作成
		for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

			add_num = IMC_ITEM_BUFF_TurnBgNoGet( &imc_w->item_buff, i );
			if( add_num < IMC_BG_RIGHT_MAX ){
				// 左ボックスアクセサリ配置
				IMC_LBOX_AddAccessorie( &imc_w->lbox, IMC_OBJLIST_BG, add_num );
			}
		}

		// 表示優先順位設定
		IMC_LBOX_SetAccessoriePriority( &imc_w->lbox );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスデータ作成
 *
 *	@param	imc_w	イメージクリップシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteLeftBox( IMC_SYS_WORK* imc_w )
{
	// BGをクリーン
	IMC_LBOX_BGClean( &imc_w->lbox );
	
	// 右ボックス配置データ破棄
	IMC_LBOX_DeleteAccessorieAll( &imc_w->lbox );
	
	// 右ボックスデータ破棄
	IMC_LBOX_DeleteSys( &imc_w->lbox );
}

//----------------------------------------------------------------------------
/**
 *	@brief	左ボックスBGのセットアップ
 *
 *	@param	imc_w	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setLeftBoxBg( IMC_SYS_WORK* imc_w )
{
	// 表示優先順位設定
	G2_SetBG0Priority( 1 );
	G2_SetBG1Priority( 0 );//*/
	G2_SetBG2Priority( 2 );
	G2_SetBG3Priority( 3 );

	// スクロール座標を設定
	// なぜかこれでうまくいく　何でだ？？
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, -16 );
	
	// 背景ナンバ
	IMC_LBOX_BGSet( &imc_w->lbox, 0 );
	IMC_LBOX_BGChange( &imc_w->lbox, 0, IMC_LBOX_FADE_Y, 0, NULL );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	Vブランク関数
 *
 *	@param	void* work 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void imageClipVBlankFunc( void* work )
{
	IMC_SYS_WORK* sys = work;

	// 描画関係Vブランク関数
	IMC_DRAW_VBlank( &sys->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フレームBGを表示
 *
 *	@param	imc_w	イメージクリップワーク
 *	@param	no		BGno
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setFrameBG( IMC_SYS_WORK* imc_w, int no )
{
	IMC_BG_ADD add;
	
	// 登録データ設定
	add.bg_ini		= imc_w->drawSys.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_FRAME_CG_ARC_GET(no);
	add.pltt_arc	= IMC_BG_LEFT_FRAME_CL;
	add.scrn_arc	= IMC_BG_FRAME_SC_ARC_GET(no);
	add.x			= 0;
	add.y			= 0;
	add.frame		= GF_BGL_FRAME1_M;
	add.pltt_num	= 1;
	add.pltt_offs	= 2;
	add.char_offs	= 0;
	add.heap		= HEAPID_IMAGECLIP_DRAW;

	IMC_BG_MakaObj( &imc_w->frame_bg, &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	フレームBG非表示
 *
 *	@param	imc_w	イメージクリップワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void delFrameBG( IMC_SYS_WORK* imc_w )
{
	IMC_BG_DeleteObj( &imc_w->frame_bg );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンデータ作成
 *
 *	@param	imc_w	イメージクリップワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Init( &imc_w->bttn, &imc_w->drawSys );

	// 左パレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RET, retBttn, imc_w, IMC_BTTN_PUSH_F );

	// 左パレット変更戻る関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RETB, retbBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// アクセサリパレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_ACE, acceBttn, imc_w, IMC_BTTN_PUSH_F );
	// アクセサリパレット変更ボタンをオン状態にする
	
	
	// BGパレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_BG, bgBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// 終了ボタン関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_END, endBttn, imc_w, IMC_BTTN_PUSH_F );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンデータ作成		コンテスト用
 *
 *	@param	imc_w	イメージクリップワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initBttn_Contest( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Init( &imc_w->bttn, &imc_w->drawSys );

	// 左パレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RET, retBttn, imc_w, IMC_BTTN_PUSH_F );

	// 左パレット変更戻る関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_RETB, retbBttn, imc_w, IMC_BTTN_PUSH_F );
	
	// アクセサリパレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_ACE, acceBttn, imc_w, IMC_BTTN_PUSH_F );
	// アクセサリパレット変更ボタンをオン状態にする
	
	
	// BGパレット変更関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_BG, bgBttn, imc_w, IMC_BTTN_PUSH_F );

	// 終了ボタン関数を設定
	IMC_IMCBTTN_FuncSet( &imc_w->bttn, IMC_BTTN_END, endBttn, imc_w, IMC_BTTN_PUSH_F );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンデータ破棄
 *
 *	@param	imc_w	イメージクリップワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Delete( &imc_w->bttn, &imc_w->drawSys );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ボタンメイン関数
 *
 *	@param	imc_w	イメージクリップワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void mainBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Main( &imc_w->bttn );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ状況のリセット
 *
 *	@param	imc_w 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void resetBttn( IMC_SYS_WORK* imc_w )
{
	IMC_IMCBTTN_Reset( &imc_w->bttn );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップを終了させる関数
 *
 *	@param	bttn	ボタン構造体
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// 終了して良い常態化チェック
	if( IMC_LBOX_ENDCheck( &imc_w->lbox ) == FALSE ){
		return ;
	}
	
	// 状態設定
	// 状態	終了リクエスト
	imc_w->state = IMC_SYS_END_CHECK_REQ;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左パレットを変更
 *
 *	@param	bttn	ボタン構造体
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void retBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int mode;
/*	int list_num;
	int list_max;

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, mode );
	list_max	= IMC_LBOX_GetDummyTblNum( &imc_w->lbox, mode );
	
	list_num = (list_num + 1) % list_max;

	// 左パレットの中身を変更
	IMC_LBOX_ChangeCurrentAccessorie( 
			&imc_w->lbox, mode, list_num );//*/
	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	IMC_LBOX_AddCurrentAccessorie(
			&imc_w->lbox, mode, IMC_LBOX_ADD_ONE );
	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左パレットを戻す
 *
 *	@param	bttn	ボタン構造体
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void retbBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int mode;
/*	int list_num;
	int list_max;

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, mode );
	list_max	= IMC_LBOX_GetDummyTblNum( &imc_w->lbox, mode );
	
	list_num--;
	if( list_num < 0 ){
		list_num += list_max;
	}

	// 左パレットの中身を変更
	IMC_LBOX_ChangeCurrentAccessorie( 
			&imc_w->lbox, mode, list_num );
//*/

	mode		= IMC_LBOX_GetMode( &imc_w->lbox );
	IMC_LBOX_AddCurrentAccessorie(
			&imc_w->lbox, mode, IMC_LBOX_SUB_ONE );

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリパレットに変更
 *
 *	@param	bttn	ボタン構造体
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	acceBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int list_num;
	int mode;

	if( imc_w->state != IMC_SYS_ACCE ){
		list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, IMC_OBJLIST_ACCE );
		

		// 左パレットの中身を変更
		IMC_LBOX_SetCurrentAccessorie( 
				&imc_w->lbox, IMC_OBJLIST_ACCE, list_num );

		// 状態設定
		imc_w->state = IMC_SYS_ACCE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGパレットに変更
 *
 *	@param	bttn	ボタン構造体
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void	bgBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;
	int list_num;
	int mode;

	if( imc_w->state != IMC_SYS_BG ){

		list_num	= IMC_LBOX_GetCurrentNo( &imc_w->lbox, IMC_OBJLIST_BG );
		
		// 左パレットの中身を変更
		IMC_LBOX_SetCurrentAccessorie( 
				&imc_w->lbox, IMC_OBJLIST_BG, list_num );

		// 状態設定
		imc_w->state = IMC_SYS_BG;

	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウ初期化
 *
 *	@param	imc_w		サブウィンドウ
 *	@param	cp_config	コンフィグデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void initSubWin( IMC_SYS_WORK* imc_w, const CONFIG* cp_config )
{
	IMC_SUBWIN_INIT	init;

	memset( &init, 0, sizeof(IMC_SUBWIN_INIT) );
	init.bg_ini		= imc_w->drawSys.BG_Ini;
	init.clactSet	= imc_w->drawSys.clactSet;
	init.p_resMan	= imc_w->drawSys.resMan;
	init.acce_max	= IMC_RBOX_ACCE_TELEVISION_MAX;	
	init.cp_config	= cp_config;

	
	IMC_SUBWIN_Init( &imc_w->subwin, &init, IMC_SUBWIN_DEFAULT_INIT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用サブウィンドウ初期化
 *
 *	@param	imc_w		ワーク
 *	@param	acce_num	アクセサリ最大数
 *	@param	thema		テーマ
 *	@param	p_comm_data	通信データ
 *	@param	cp_config	コンフィグデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initSubWin_Contest( IMC_SYS_WORK* imc_w, int acce_num, int thema, CON_IMC_LOCAL* p_comm_data, const CONFIG* cp_config )
{
	IMC_SUBWIN_INIT	init;
	BOOL oya;
	
	init.bg_ini		= imc_w->drawSys.BG_Ini;
	init.clactSet	= imc_w->drawSys.clactSet;
	init.p_resMan	= imc_w->drawSys.resMan;
	init.acce_max	= acce_num;	
	init.rank_msgid = NARC_msg_imageclip_dat;
	init.rank_strid = imgclip_theme_01 + thema;
	init.count_max	= IMC_COUNT_MAX;
	init.p_comm_data = p_comm_data;
	init.cp_config	= cp_config;

	IMC_SUBWIN_Init( &imc_w->subwin, &init, IMC_SUBWIN_CONTEST_INIT );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サブウィンドウ破棄
 *
 *	@param	imc_w	サブウィンドウ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void deleteSubWin( IMC_SYS_WORK* imc_w )
{
	IMC_SUBWIN_Delete( &imc_w->subwin );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了画面へフェードイン開始
 *
 *	@param	imc_w	システムワーク	
 *	@param	end		終了検知フラグ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeIn( IMC_SYS_WORK* imc_w, BOOL* end )
{
	TCB_PTR tcb;
	IMC_SYS_FADE_WORK* fade_w;

	// タスク登録
	tcb = PMDS_taskAdd( endSeenFadeInTask, sizeof( IMC_SYS_FADE_WORK ), 10, HEAPID_IMAGECLIP_DATA );

	// ワークにデータ設定
	fade_w = TCB_GetWork( tcb );
	fade_w->sys_w	= imc_w;
	fade_w->end		= end;
	fade_w->work	= 0;
	fade_w->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了画面フェードタスク
 *
 *	@param	tcb		タスクオブジェ
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeInTask( TCB_PTR tcb, void* work )
{
	IMC_SYS_FADE_WORK* fade_w = work;
	BOOL	check;
	
	switch( fade_w->seq ){
	case IMC_SEENFADEIN_ACCE_FADEOUT:
		check = IMC_LBOX_ChangeCurrentAccessorie( 
				&fade_w->sys_w->lbox,
				IMC_LBOX_FADELIST_MODE,
				0);
		GF_ASSERT( check );	// おかしい

		
		fade_w->seq++;
		break;
		
	case IMC_SEENFADEIN_ACCE_FADEWAIT:
		check = IMC_LBOX_ENDCheck( &fade_w->sys_w->lbox );
		if( check ){

			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_BRIGHTNESS_OUT:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_BLACK,
				BRIGHTNESS_NORMAL,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;


	case IMC_SEENFADEIN_BRIGHTNESS_WAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_BUTTON_OLDOUT:
		IMC_IMCBTTN_Move( &fade_w->sys_w->bttn, 0, IMC_SEENFADE_BTTNMOVE_ADD_Y );
		fade_w->work ++;
		if( fade_w->work >= IMC_SEENFADE_BTTNMOVE_COUNT ){
			fade_w->work = 0;
			fade_w->seq ++;
		}
		break;

	
	case IMC_SEENFADEIN_MOVE_BG:
		if( endSeenFadeMoveBg( fade_w, -IMC_SEENFADE_MOVE_ADD_X, IMC_SEENFADE_MOVE_ADD_Y, IMC_SEENFADE_MOVE_COUNT ) ){
			fade_w->work = 0;
			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEIN_MOVE_BGINIT:
		// BG 1面のBG変更
		setFrameBG( fade_w->sys_w, IMC_BG_FRAME_01 );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, 0 );

		// ハイイイエウィンドウセットアップ
		initTouchSWSys( fade_w->sys_w );
		fade_w->seq++;
		break;

		
	
	case IMC_SEENFADEIN_BRIGHTNESS_IN:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_NORMAL,
				BRIGHTNESS_BLACK,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;


	case IMC_SEENFADEIN_BRIGHTNESS_INWAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;
		
	case IMC_SEENFADEIN_END:
		*fade_w->end = TRUE;
		PMDS_taskDel( tcb );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ作成画面フェード開始
 *
 *	@param	imc_w	システムワーク
 *	@param	end		終了検知フラグ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeOut( IMC_SYS_WORK* imc_w, BOOL* end )
{
	TCB_PTR tcb;
	IMC_SYS_FADE_WORK* fade_w;

	// タスク登録
	tcb = PMDS_taskAdd( endSeenFadeOutTask, sizeof( IMC_SYS_FADE_WORK ), 10, HEAPID_IMAGECLIP_DATA );

	// ワークにデータ設定
	fade_w = TCB_GetWork( tcb );
	fade_w->sys_w	= imc_w;
	fade_w->end		= end;
	fade_w->work	= 0;
	fade_w->seq		= 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	イメージクリップ作成画面フェードタスク
 *
 *	@param	tcb		タスクオブジェ
 *	@param	work	ワーク
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void endSeenFadeOutTask( TCB_PTR tcb, void* work )
{
	IMC_SYS_FADE_WORK* fade_w = work;
	BOOL	check;
	
	switch( fade_w->seq ){

	case IMC_SEENFADEOUT_BRIGHTNESS_OUT:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_BLACK,
				BRIGHTNESS_NORMAL,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;
			
	case IMC_SEENFADEOUT_BRIGHTNESS_OUTWAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;


	case IMC_SEENFADEOUT_MOVE_BG_SET:
		// ハイイイエウィンドウ破棄
		deleteTouchSWSys( fade_w->sys_w );
		// 左ボックスウィンドウ設定
		setLeftBoxBg( fade_w->sys_w );
		// ボタンのアニメリセット
		resetBttn( fade_w->sys_w );
		
		setFrameBG( fade_w->sys_w, IMC_BG_FRAME_00 );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_SET, -IMC_SEENFADE_BG_MOVE_Y );
		fade_w->seq++;
		break;


	case IMC_SEENFADEOUT_MOVE_BG:
		if( endSeenFadeMoveBg( fade_w, IMC_SEENFADE_MOVE_ADD_X, -IMC_SEENFADE_MOVE_ADD_Y, IMC_SEENFADE_MOVE_COUNT ) ){
			fade_w->work = 0;
			fade_w->seq++;
		}
		break;


	case IMC_SEENFADEOUT_BUTTON_NEWIN:
		IMC_IMCBTTN_Move( &fade_w->sys_w->bttn, 0, -IMC_SEENFADE_BTTNMOVE_ADD_Y );
		fade_w->work ++;
		if( fade_w->work >= IMC_SEENFADE_BTTNMOVE_COUNT ){
			fade_w->work = 0;
			fade_w->seq ++;
		}
		break;

	case IMC_SEENFADEOUT_BRIGHTNESS_IN:
		ChangeBrightnessRequest(
				IMC_SEENFADE_BRIGHTNESS_FADE_SYNC,
				BRIGHTNESS_NORMAL,
				BRIGHTNESS_BLACK,
//				PLANEMASK_BG1 | PLANEMASK_BG3 | PLANEMASK_OBJ,
				PLANEMASK_BG1 | PLANEMASK_BG3,
				MASK_MAIN_DISPLAY );
		fade_w->seq++;
		break;

	case IMC_SEENFADEOUT_BRIGHTNESS_WAIT:
		check = IsFinishedBrightnessChg( MASK_MAIN_DISPLAY );
		if( check ){
			fade_w->seq++;
		}
		break;
		
	case IMC_SEENFADEOUT_ACCE_FADEIN:
		check = IMC_LBOX_ChangeCurrentAccessorie( 
				&fade_w->sys_w->lbox,
				IMC_OBJLIST_ACCE,
				0);
		GF_ASSERT( check );	// おかしい

		fade_w->seq++;
		break;
		
	case IMC_SEENFADEOUT_ACCE_FADEWAIT:
		check = IMC_LBOX_ENDCheck( &fade_w->sys_w->lbox );
		if( check ){

			fade_w->seq++;
		}
		break;

	case IMC_SEENFADEOUT_END:
		*fade_w->end = TRUE;
		PMDS_taskDel( tcb );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェックシーケンス　終了ボタン
 *
 *	@param	bttn		ボタン構造体
 *	@param	work		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endCkEndBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// 状態設定
	// 状態	終了リクエスト
	imc_w->state = IMC_SYS_END_REQ;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェックシーケンス　CANCELボタン
 *
 *	@param	bttn		ボタン構造体
 *	@param	work		ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void endCkCancelBttn( IMC_BUTTON* bttn, void* work )
{
	IMC_SYS_WORK* imc_w = work;

	// 状態設定
	// 状態	終了リクエスト
	imc_w->state = IMC_SYS_END_CANCEL_REQ;
}

//----------------------------------------------------------------------------
/**
 *	@brief	データセーブ
 *
 *	@param	save_data	セーブデータ
 *	@param	rbox		右ボックスデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void dataSave( IMC_TELEVISION_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, const MYSTATUS* cp_tr )
{
	IMC_OBJLIST* p_work;
	int count;
	STRBUF* p_str;
	int sex;

	ImcSaveData_ClaenTelevisionData( save_data );		// 編集するワークを初期化
	
	// ポケモンデータ保存
	ImcSaveData_SetTelevisionPokeData( save_data, 
			rbox->boxDraw.poke.poke_para,
			&rbox->boxDraw.poke );

	// トレーナーデータ設定
	if( cp_tr ){
		p_str = MyStatus_CreateNameString( cp_tr, HEAPID_IMAGECLIP_DATA );
		sex = MyStatus_GetMySex( cp_tr );
		ImcSaveData_SetTelevisionTrData( save_data, p_str, sex );
		STRBUF_Delete( p_str );
	}

	// アクセサリデータ保存
	count = 0;
	p_work = rbox->boxData.dummy_poke.next;
	while( p_work != &rbox->boxData.dummy_poke ){
		// アクセサリデータなら保存する	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			ImcSaveData_SetTelevisionAcceData( save_data, p_work->obj_data, count );
			count ++;
		}
		p_work = p_work->next;
	}
	p_work = rbox->boxData.dummy.next;
	while( p_work != &rbox->boxData.dummy ){
		// アクセサリデータなら保存する	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			ImcSaveData_SetTelevisionAcceData( save_data, p_work->obj_data, count );
			count ++;
		}
		p_work = p_work->next;
	}

	// BGID
	ImcSaveData_SetTelevisionBgId( save_data, rbox->boxDraw.bg_no );	

	// セーブ完了
	ImcSaveData_SetComplateFlagTelevisionData( save_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用セーブデータ保存
 *
 *	@param	save_data	コンテストセーブデータ保存先
 *	@param	rbox		右ボックスデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void dataSave_Contest( IMC_CONTEST_SAVEDATA* save_data, IMC_RIGHT_BOX* rbox, int rank, const MYSTATUS* cp_tr )
{
	int count;
	int i;
	IMC_POKE_ON_ACCESYS* p_sys;
	IMC_OBJLIST* p_obj;
	STRBUF* p_str;
	int sex;

	// システム
	p_sys = sys_AllocMemory( HEAPID_IMAGECLIP_DATA, sizeof(IMC_POKE_ON_ACCESYS) );
	initPokeOnAcceCheckSys( p_sys );
	
	// ポケモンデータ保存
	ImcSaveData_SetContestPokeData( save_data, 
			rbox->boxDraw.poke.poke_para,
			&rbox->boxDraw.poke );


	// トレーナーデータ設定
	if( cp_tr ){
		p_str = MyStatus_CreateNameString( cp_tr, HEAPID_IMAGECLIP_DATA );
		sex = MyStatus_GetMySex( cp_tr );
		ImcSaveData_SetContestTrData( save_data, p_str, sex );
		STRBUF_Delete( p_str );
	}

	// まず全アクセサリデータをワークに設定する
	setPokeOnAcceCheckObjList( p_sys, &rbox->boxData.dummy_poke, IMC_POKEON_ACCE_ON );
	setPokeOnAcceCheckObjList( p_sys, &rbox->boxData.dummy, IMC_POKEON_ACCE_NONE );

	// ポケモンについているアクセサリチェック
	mainPokeOnAcceCheckSys( p_sys );

	// アクセサリデータ保存
	count = 0;
	for( i=0; i<IMC_POKEON_ACCE_CHECK_OBJNUM; i++ ){

		if( getPokeOnAcceCheckObjOnPoke( p_sys, i ) == TRUE ){
			p_obj = getPokeOnAcceCheckObjList( p_sys, i );
			ImcSaveData_SetContestAcceData( save_data, p_obj->obj_data, count );
			count ++;
		}
	}

	// BGID
	ImcSaveData_SetContestBgId( save_data, rbox->boxDraw.bg_no );	
	// ランクの保存
	ImcSaveData_SetContestRank( save_data, rank );

	// セーブ完了
	ImcSaveData_SetComplateFlagContestData( save_data );


	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シーンフェード　BGとポケモンアクセサリ同時移動関数
 *
 *	@param	fade_w				フェードワーク
 *	@param	move_x				X変更値			(ポケモンオブジェクトにあわせる)
 *	@param	move_y				Y変更値			(ポケモンオブジェクトにあわせる)
 *	@param	move_count_num		ｶｳﾝﾀ最大値
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	続行
 */
//-----------------------------------------------------------------------------
static BOOL endSeenFadeMoveBg( IMC_SYS_FADE_WORK* fade_w, int move_x, int move_y, int move_count_num )
{
	// 3Dのオブジェクトは描画タイミングの影響で、反映が1シンク遅くなってしまうので、１回先に変更する
	if( fade_w->work < IMC_SEENFADE_MOVE_COUNT ){
		IMC_RBOX_ListMove( &fade_w->sys_w->rbox, move_x, move_y );
	}

	// ２Dオブジェクトは１回遅いタイミングで変更する
	if( fade_w->work >= 1 ){
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_X_DEC, move_x );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_X_DEC, move_x );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME2_M, GF_BGL_SCROLL_Y_DEC, move_y );
		GF_BGL_ScrollReq( fade_w->sys_w->drawSys.BG_Ini, GF_BGL_FRAME1_M, GF_BGL_SCROLL_Y_DEC, move_y );
	}
	
	fade_w->work++;
	if( fade_w->work > move_count_num ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト　説明開始
 *
 *	@param	imc_w	ワーク
 */
//-----------------------------------------------------------------------------
static void initConTextSys( IMC_SYS_WORK* imc_w )
{
	// スクリーンクリーン
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
	
	// ビットマップウィンドウ描画
	initContestTextBmpWin( imc_w, 0 );

	// 表示優先順位設定
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );

	//FRAME3だけ表示させる
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_OFF );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG3, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	// WIPE破棄
	WIPE_ResetBrightness( WIPE_DISP_MAIN );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト　説明終了
 *
 *	@param	imc_w	ワーク
 */
//-----------------------------------------------------------------------------
static void deleteConTextSys( IMC_SYS_WORK* imc_w )
{
	// ビットマップ破棄
	deleteContestTextBmpWin( imc_w );

	// スクリーンを初期化
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );

	// 左ボックスグラフィック再設定
	setLeftBoxBg( imc_w );

	// WIPE設定
	WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );

	// 最初アクターセット表示
	CLACT_DrawFlagSet( imc_w->drawSys.clactSet, 1 );

	//全て表示させる
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG2, VISIBLE_ON );
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}


//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面　触れるウィンドウ　初期化
 *
 *	@param	imc_w	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initTouchSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_PARAM touch_prm;

	// スクリーンクリーン
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_X_SET, 0 );
	GF_BGL_ScrollSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, GF_BGL_SCROLL_Y_SET, 0 );
	
	// YES NO ウィンドウボタンの表示
	touch_prm.p_bgl		= imc_w->drawSys.BG_Ini;
	touch_prm.bg_frame	= GF_BGL_FRAME3_M;
	touch_prm.char_offs	= IMC_ENDCHECK_YESNO_CHAR_OFFS;
	touch_prm.pltt_offs = IMC_ENDCHECK_YESNO_PLTT_OFFS;
	touch_prm.x			= IMC_ENDCHECK_YESNO_X;
	touch_prm.y			= IMC_ENDCHECK_YESNO_Y;
	TOUCH_SW_Init( imc_w->p_tsw, &touch_prm );

	// ビットマップウィンドウ描画
	initTouchSWBmpWin( imc_w, imgclip_ok );

	// 表示優先順位設定
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面　触れるウィンドウ　破棄
 *
 *	@param	imc_w	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void deleteTouchSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_Reset( imc_w->p_tsw );

	// ビットマップ破棄
	deleteTouchSWBmpWin( imc_w );

	// スクリーンを初期化
	GF_BGL_ScrClear( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面　触れるウィンドウ　メイン動作
 *
 *	@param	imc_w	ワーク
 *
 *	@retval	IMC_SYS_END_CHECK			// 何もなし
 *	@retval	IMC_SYS_END_REQ				// はい
 *	@retval	IMC_SYS_END_CANCEL_REQ		// いいえ
 */
//-----------------------------------------------------------------------------
static u32 mainTouchSWSys( IMC_SYS_WORK* imc_w )
{
	u32 ret;
	ret = TOUCH_SW_Main( imc_w->p_tsw );

	switch( ret ){
	case TOUCH_SW_RET_NORMAL:	// 何もなし
		ret = IMC_SYS_END_CHECK;
		break;
		
	case TOUCH_SW_RET_YES:	// はい
		ret = IMC_SYS_END_REQ;
		break;
		
	case TOUCH_SW_RET_NO:		// いいえ
		ret = IMC_SYS_END_CANCEL_REQ;
		break;
	}
	
	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウの初期化
 *
 *	@param	imc_w 
 *	@param	str_idx		文字列ID
 *	@param	cx			ｘキャラクタ位置
 *	@param	cy			ｙキャラクタ位置
 *	@param	csx			ｘキャラクタサイズ
 *	@param	csy			ｙキャラクタサイズ
 */
//-----------------------------------------------------------------------------
static void initMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx, u8 cx, u8 cy, u8 csx, u8 csy )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	WINTYPE wnd_no = CONFIG_GetWindowType( imc_w->cp_config );
	
	
	// 文字フォントカラーパレット転送
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, IMC_ENDCHECK_WND_PAL*32, HEAPID_IMAGECLIP_DRAW );
	
	// ビットマップウィンドウ作成
	GF_BGL_BmpWinAdd( imc_w->drawSys.BG_Ini,
			imc_w->p_tsw_bmp, GF_BGL_FRAME3_M,
			cx, cy,
			csx, csy,
			IMC_ENDCHECK_WND_PAL, IMC_ENDCHECK_WND_CHROFS );
	// クリーン
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// 枠描画
	TalkWinGraphicSet( imc_w->drawSys.BG_Ini, GF_BGL_FRAME3_M, IMC_ENDCHECK_WNDWAKU_CHROFS, IMC_ENDCHECK_WNDWAKU_PAL, wnd_no, HEAPID_IMAGECLIP_DRAW );
	BmpTalkWinWrite( imc_w->p_tsw_bmp, WINDOW_TRANS_ON, IMC_ENDCHECK_WNDWAKU_CHROFS, IMC_ENDCHECK_WNDWAKU_PAL );

	// 文字描画
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	str = MSGMAN_AllocString( msg_data, str_idx );
	GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, str, 0, 0, 0, IMC_ENDCHECK_WND_PRICOLOR, NULL );
	// メモリ破棄
	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	// 転送
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウに文字列を描画
 *
 *	@param	imc_w		ワーク
 *	@param	str_idx		文字列ID
 */
//-----------------------------------------------------------------------------
static void setMsgBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	STRBUF* p_exstr;
	
	// クリーン
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// 文字描画
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	p_exstr = MSGMAN_AllocString( msg_data, str_idx );
	str = STRBUF_Create( 256, HEAPID_IMAGECLIP_DATA );

	WORDSET_ExpandStr( imc_w->p_wordset, str, p_exstr );
	
	GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, str, 0, 0, 0, IMC_ENDCHECK_WND_PRICOLOR, NULL );

	// メモリ破棄
	STRBUF_Delete( str );
	STRBUF_Delete( p_exstr );
	MSGMAN_Delete( msg_data );

	// 転送
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メッセージ送り描画
 *
 *	@param	imc_w		ワーク
 *	@param	str_idx		文字列ID
 *
 *	@return	メッセージIDX
 */
//-----------------------------------------------------------------------------
static u32 setMsgBmpWin_okuri( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	u32 msg_index;
	MSGDATA_MANAGER* msg_data;
	u32 speed;
	STRBUF* p_exstr;

	GF_ASSERT( imc_w->p_glb_str == NULL );
	
	// クリーン
	GF_BGL_BmpWinDataFill( imc_w->p_tsw_bmp, 15 );

	// 文字描画
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_imageclip_dat, HEAPID_IMAGECLIP_DATA );
	p_exstr = MSGMAN_AllocString( msg_data, str_idx );
	imc_w->p_glb_str = STRBUF_Create( 256, HEAPID_IMAGECLIP_DATA );

	WORDSET_ExpandStr( imc_w->p_wordset, imc_w->p_glb_str, p_exstr );
	
	if( imc_w->p_comm_data->sio_flag == 0 ){
		speed = CONFIG_GetMsgPrintSpeed( imc_w->cp_config );
	}else{
		speed = CONTEST_SIO_MSG_SPEED;
	}
	
	msg_index = GF_STR_PrintColor( imc_w->p_tsw_bmp, FONT_TALK, imc_w->p_glb_str, 0, 0, speed, IMC_ENDCHECK_WND_PRICOLOR, NULL );

	STRBUF_Delete( p_exstr );
	// メモリ破棄
	MSGMAN_Delete( msg_data );

	// 転送
	GF_BGL_BmpWinOn( imc_w->p_tsw_bmp );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	送りようワーク破棄
 *
 *	@param	imc_w 
 */
//-----------------------------------------------------------------------------
static void endMsgBmpWin_okuri( IMC_SYS_WORK* imc_w )
{
	STRBUF_Delete( imc_w->p_glb_str );
	imc_w->p_glb_str = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウの破棄
 *
 *	@param	imc_w	ワーク
 */
//-----------------------------------------------------------------------------
static void deleteMsgBmpWin( IMC_SYS_WORK* imc_w )
{
	// 転送
	GF_BGL_BmpWinOff( imc_w->p_tsw_bmp );
	GF_BGL_BmpWinDel( imc_w->p_tsw_bmp );
}


//----------------------------------------------------------------------------
/**
 *	@brief	終了チェックビットマップウィンドウ作成
 *
 *	@param	imc_w 
 *	@param	str_idx		文字列ID
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void initTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	initMsgBmpWin( imc_w, str_idx, 
			IMC_ENDCHECK_WND_X, IMC_ENDCHECK_WND_Y,
			IMC_ENDCHECK_WND_SIZX, IMC_ENDCHECK_WND_SIZY );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了チェックビットマップウィンドウ文字列設定
 *
 *	@param	imc_w 
 *	@param	str_idx		文字列ID
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void setTouchSWBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	setMsgBmpWin( imc_w, str_idx );
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了ﾁｪｯｸ用ビットマップウィンドウ破棄
 *
 *	@param	imc_w	
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void deleteTouchSWBmpWin( IMC_SYS_WORK* imc_w )
{
	deleteMsgBmpWin( imc_w );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストテキスト	説明BMP作成
 *
 *	@param	imc_w	ワーク
 *	@param	str_idx メッセージ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	initMsgBmpWin( imc_w, str_idx, 
			IMC_CONTESTTEXT_WND_X, IMC_CONTESTTEXT_WND_Y,
			IMC_CONTESTTEXT_WND_SIZX, IMC_CONTESTTEXT_WND_SIZY );

	// ワードセット作成
	imc_w->p_wordset = WORDSET_Create( HEAPID_IMAGECLIP_DATA );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストテキスト　
 *
 *	@param	imc_w		ワーク
 *	@param	str_idx		文字列ID
 *
 *	@return	メッセージIDX
 */
//-----------------------------------------------------------------------------
static u32 setContestTextBmpWin( IMC_SYS_WORK* imc_w, u32 str_idx )
{
	return setMsgBmpWin_okuri( imc_w, str_idx );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワードセットに設定
 *
 *	@param	imc_w	ワーク
 *	@param	buff_id	バッファID
 *	@param	no		数字
 */
//-----------------------------------------------------------------------------
static void setContestWordSet( IMC_SYS_WORK* imc_w, int buff_id, int no )
{
	WORDSET_RegisterNumber( imc_w->p_wordset, buff_id, no, 2, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	文字列破棄
 */
//-----------------------------------------------------------------------------
static void endContestTextBmpWin( IMC_SYS_WORK* imc_w )
{
	endMsgBmpWin_okuri( imc_w );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストテキストBMP破棄
 *
 *	@param	imc_w	ワーク
 */
//-----------------------------------------------------------------------------
static void deleteContestTextBmpWin( IMC_SYS_WORK* imc_w )
{
	deleteMsgBmpWin( imc_w );

	// ワードセット破棄
	WORDSET_Delete( imc_w->p_wordset );
	imc_w->p_wordset = NULL;
}



//----------------------------------------------------------------------------
/**
 *	@brief	右ボックスのアクセサリ登録数を設定
 *
 *	@param	imc_w	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setAcceNumSubWin( IMC_SYS_WORK* imc_w )
{
	int acce_num;

	acce_num = IMC_RBOX_GetNowHaveAcceNum( &imc_w->rbox );
	
	// 右ボックスの配置アクセサリデータを設定
	IMC_SUBWIN_SetAcceIcon( &imc_w->subwin, acce_num );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストのランクにより、アクセサリ最大数を取得
 *
 *	@param	rank	ランク数
 *
 *	@return	アクセサリ数
 */
//-----------------------------------------------------------------------------
static int getRightAcceMax_contest( int rank )
{
	int acce_max;
	
	switch( rank ){
	case CONRANK_NORMAL:
		acce_max = CON_IMAGE_ACCE_MAX_NORMAL;
		break;

	case CONRANK_SUPER:
		acce_max = CON_IMAGE_ACCE_MAX_SUPER;
		break;

	case CONRANK_HYPER:
		acce_max = CON_IMAGE_ACCE_MAX_HYPER;
		break;

	case CONRANK_MASTER:
		acce_max = CON_IMAGE_ACCE_MAX_MASTER;
		break;

	default:
		// ランク不正
		GF_ASSERT(0);
		break;
	}

	return acce_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブするかﾁｪｯｸ用イエスノーボタン初期化
 *
 *	@param	imc_w	ワーク
 *
 *	@return	none
 *
 *	終了チェックのハイイイエを引き継ぎます
 */
//-----------------------------------------------------------------------------
static void initTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w )
{
	TOUCH_SW_PARAM touch_prm;

	// YES NO ウィンドウボタンの表示
	touch_prm.p_bgl		= imc_w->drawSys.BG_Ini;
	touch_prm.bg_frame	= GF_BGL_FRAME3_M;
	touch_prm.char_offs	= IMC_ENDCHECK_YESNO_CHAR_OFFS;
	touch_prm.pltt_offs = IMC_ENDCHECK_YESNO_PLTT_OFFS;
	touch_prm.x			= IMC_ENDCHECK_YESNO_X;
	touch_prm.y			= IMC_ENDCHECK_YESNO_Y;
	TOUCH_SW_Reset( imc_w->p_tsw );
	TOUCH_SW_Init( imc_w->p_tsw, &touch_prm );

	// ビットマップウィンドウ描画
	setTouchSWBmpWin( imc_w, imgclip_ng );

	// 表示優先順位設定
	G2_SetBG0Priority( 2 );
	G2_SetBG1Priority( 1 );
	G2_SetBG2Priority( 3 );
	G2_SetBG3Priority( 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータチェック YESNO メイン処理
 *
 *	@param	imc_w	ワーク
 *
 *	@retval	
 */
//-----------------------------------------------------------------------------
static u32 mainTouchSaveCheckSWSys( IMC_SYS_WORK* imc_w )
{
	u32 ret;
	ret = TOUCH_SW_Main( imc_w->p_tsw );

	switch( ret ){
	case TOUCH_SW_RET_NORMAL:	// 何もなし
		ret = IMC_SYS_SAVE_CHECK_REQ;
		break;
		
	case TOUCH_SW_RET_YES:	// はい
		ret = IMC_SYS_SAVE;
		break;
		
	case TOUCH_SW_RET_NO:		// いいえ
		ret = IMC_SYS_SAVE_CAN;
		break;
	}
	
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンにアクセサリ伝いでつながっているかチェックするシステム　初期化	（ワークを０クリア）
 *
 *	@param	p_sys	システムワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void initPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys )
{
	memset( p_sys, 0, sizeof(IMC_POKE_ON_ACCESYS) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンにアクセサリ伝いでつながっているかチェックするシステム　オブジェクトリスト設定
 *
 *	@param	p_sys		システムワーク
 *	@param	obj			オブジェクト
 *	@param	init_data	ポケモンにくっついているかの初期値
 *
 *	@return	none
 *
 *	init_data	
 *		最初からポケモンにくっついているとわかっているものには1を渡しておく
 *		IMC_POKEON_ACCE_NONE	ポケモンにくっついていない
 *		IMC_POKEON_ACCE_ON		ポケモンにくっついている
 */
//-----------------------------------------------------------------------------
static void setPokeOnAcceCheckObj( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* obj, u32 init_data )
{
	//　NULLはだめ
	GF_ASSERT( obj );
	p_sys->obj[ p_sys->set_num ].obj			= obj;
	p_sys->obj[ p_sys->set_num ].pokemon_data	= init_data;
	p_sys->set_num++;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンにアクセサリ伝いでつながっているかチェックするシステム　チェック関数
 *
 *	@param	p_sys	システムワーク
 *
 *	@return	none
 *
 *	この関数を行った後　getPokeOnAcceCheckObjOnPokeで
 *	ちぇっくするとアクセサリ伝いでつながっているかがわかる
 */
//-----------------------------------------------------------------------------
static void mainPokeOnAcceCheckSys( IMC_POKE_ON_ACCESYS* p_sys )
{
	int i, j;
	BOOL result;

	// ポケモンにくっついているアクセサリから
	// 判定していく、範囲内のアクセサリがあったら、
	// 自分の値を入れる、全部判定したら自分に２を入れる
	// 次の[IMC_POKEON_ACCE_ON]のアクセサリを今度は、
	// はんていする
	// これを繰り返す
	i=0;
	while( i<p_sys->set_num ){

		if( p_sys->obj[ i ].pokemon_data == IMC_POKEON_ACCE_ON ){

			// 当たり判定ないならチェック対象のアクセサリもポケモンとつながっている
			for( j=0; j<p_sys->set_num; j++ ){

				if( p_sys->obj[ j ].pokemon_data == IMC_POKEON_ACCE_NONE ){
					result = checkPokeOnAcceCalc( 
							&p_sys->obj[ i ], &p_sys->obj[ j ] );
					if( result == TRUE ){
						p_sys->obj[ j ].pokemon_data = IMC_POKEON_ACCE_ON;
					}
				}
			}
			// SEARCH完了
			p_sys->obj[ i ].pokemon_data = IMC_POKEON_ACCE_SEARCHEND;
			// もう一度先頭からチェック
			i = 0;
		}else{
			i++;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ナンバーのオブジェクトリストを取得する
 *
 *	@param	p_sys		システムワーク
 *	@param	no			配列インデックス
 *
 *	@return	オブジェクトリスト
 */
//-----------------------------------------------------------------------------
static IMC_OBJLIST* getPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, u32 no )
{
	GF_ASSERT(no < IMC_POKEON_ACCE_CHECK_OBJNUM);

	return p_sys->obj[ no ].obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンにアクセサリ伝いでつながっているかチェックするシステム　そのアクセサリがつながっているかを返す
 *
 *	@param	p_sys		システムワーク
 *	@param	no			配列インデックス
 *	
 *	@retval	TRUE	つながっている
 *	@retval	FALSE	つながっていない
 */
//-----------------------------------------------------------------------------
static BOOL getPokeOnAcceCheckObjOnPoke( IMC_POKE_ON_ACCESYS* p_sys, u32 no )
{
	GF_ASSERT(no < IMC_POKEON_ACCE_CHECK_OBJNUM);
	
	if( p_sys->obj[ no ].pokemon_data ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	当たり判定
 *
 *	@param	p_obj		今何かとつながっているかチェックしているオブジェクト
 *	@param	p_check_obj	チェックされるオブジェクト
 *
 *	@retval	TRUE	あたっている
 *	@retval	FLASE	あたっていない
 */
//-----------------------------------------------------------------------------
enum{
	IMC_POKEON_ACCE_TOP,
	IMC_POKEON_ACCE_BOTTOM,
	IMC_POKEON_ACCE_LEFT,
	IMC_POKEON_ACCE_RIGHT,
	IMC_POKEON_ACCE_YHALF,
	IMC_POKEON_ACCE_XHALF,
	IMC_POKEON_ACCE_POS_NUM
};
static BOOL checkPokeOnAcceCalc( IMC_POKE_ON_ACCEOBJ* p_obj, IMC_POKE_ON_ACCEOBJ* p_check_obj )
{
	int pos[IMC_POKEON_ACCE_POS_NUM];
	BOOL result;
	int i;
	int x, y;
	
	// 16点チェックする
	// 上下左右　真ん中
	// 真ん中
	IMC_OBJLIST_GetObjCenterMat( p_obj->obj, &pos[IMC_POKEON_ACCE_XHALF], &pos[IMC_POKEON_ACCE_YHALF] );
	IMC_OBJLIST_GetObjRectSubInSize( p_obj->obj,
			&pos[IMC_POKEON_ACCE_TOP], &pos[IMC_POKEON_ACCE_BOTTOM], 
			&pos[IMC_POKEON_ACCE_LEFT], &pos[IMC_POKEON_ACCE_RIGHT] );

	for( i=0; i<16; i++ ){
		IMC_CALC_HitPoint16Get( pos[IMC_POKEON_ACCE_TOP], pos[IMC_POKEON_ACCE_BOTTOM],
				pos[IMC_POKEON_ACCE_LEFT], pos[IMC_POKEON_ACCE_RIGHT], i,
				&x, &y );	
/*		switch( i ){
		case 0:	// 左上
			x = pos[IMC_POKEON_ACCE_LEFT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 1:	// 右上
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 2:	// 左下
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 3:	// 右下
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 4:	// 左真ん中
			x = pos[IMC_POKEON_ACCE_LEFT];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		case 5:	// 右真ん中
			x = pos[IMC_POKEON_ACCE_RIGHT];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		case 6:	// 真ん中上
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_TOP];
			break;
		case 7:	// 真ん中下
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_BOTTOM];
			break;
		case 8:	// 真ん中
			x = pos[IMC_POKEON_ACCE_XHALF];
			y = pos[IMC_POKEON_ACCE_YHALF];
			break;
		default:
			GF_ASSERT(0);
			break;
		}//*/

		result = IMC_OBJLIST_ACCEPOKE_Hit( p_check_obj->obj, x, y );
		if( result == TRUE ){	// あたったら抜ける
			return TRUE;
		}
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトリスト内のアクセサリを全部　チェック用テーブルに入れる
 *
 *	@param	p_sys		ワーク
 *	@param	dummy		ダミーデータ
 *	@param	init_data	初期化データ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void setPokeOnAcceCheckObjList( IMC_POKE_ON_ACCESYS* p_sys, IMC_OBJLIST* dummy, u32 init_data )
{
	IMC_OBJLIST* p_work;

	p_work = dummy->next;	// ポケモンの上のアクセサリ
	while( p_work != dummy ){
		// アクセサリデータなら保存する	
		if( p_work->flag == IMC_OBJLIST_ACCE ){
			setPokeOnAcceCheckObj( p_sys, p_work, init_data );
		}
		p_work = p_work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	強制終了チェック
 *
 *	@param	imc_w 
 */
//-----------------------------------------------------------------------------
static void Imc_OyaExEndCheck( IMC_SYS_WORK* imc_w )
{
	int i;
	int count = 0;
	
	// もし通信していないときは無条件で0にする
	if( imc_w->p_comm_data->sio_flag == 0 ){
		IMC_SUBWIN_SetCounterNowNum( &imc_w->subwin, 0 );
		return ;
	}

	// もし親なら皆から終了フラグを調べる
	if( imc_w->p_comm_data->server_no == imc_w->p_comm_data->my_net_id ){
		for( i=0; i<BREEDER_MAX; i++ ){
			if( imc_w->p_comm_data->recieve_force_end[i] == TRUE ){
				count ++;
			}
		}
		
		// 全員から終了がきたのでカウント値を０にする
		if( imc_w->p_comm_data->player_num  <= count ){
			IMC_SUBWIN_SetCounterNowNum( &imc_w->subwin, 0 );
		}
	}

}



//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップあたり判定ポイント取得関数
 *
 *	@param	top			トップ
 *	@param	bottom		ボトム
 *	@param	left		レフト
 *	@param	right		ライト
 *	@param	no			当たり判定ポイントナンバー(０～１５)
 *	@param	p_x			X座標格納先
 *	@param	p_y			Y座標格納先
 */
//-----------------------------------------------------------------------------
void IMC_CALC_HitPoint16Get( u32 top, u32 bottom, u32 left, u32 right, u32 no, int* p_x, int* p_y )
{
	u32 halfx_0, halfx_1;
	u32 halfy_0, halfy_1;
	
	halfx_0 = left + ((right - left) / 3);
	halfx_1 = left + ((right - left) / 3)*2;

	halfy_0 = top + ((bottom - top) / 3);
	halfy_1 = top + ((bottom - top) / 3)*2;
	
	switch( no ){
	case 0:	// 左上
		*p_x = left;
		*p_y = top;
		break;

	case 1:	// 左　中間０
		*p_x = left;
		*p_y = halfy_0;
		break;

	case 2:	// 左　中間１
		*p_x = left;
		*p_y = halfy_1;
		break;

	case 3:	// 左下
		*p_x = left;
		*p_y = bottom;
		break;

	case 4:	// 中間０　上
		*p_x = halfx_0;
		*p_y = top;
		break;

	case 5:	// 中間０　中間０
		*p_x = halfx_0;
		*p_y = halfy_0;
		break;

	case 6:	// 中間０　中間１
		*p_x = halfx_0;
		*p_y = halfy_1;
		break;

	case 7:	// 中間０　下
		*p_x = halfx_0;
		*p_y = bottom;
		break;

	case 8:	// 中間１　上
		*p_x = halfx_1;
		*p_y = top;
		break;

	case 9:	// 中間１　中間０
		*p_x = halfx_1;
		*p_y = halfy_0;
		break;

	case 10:	// 中間１　中間１
		*p_x = halfx_1;
		*p_y = halfy_1;
		break;

	case 11:	// 中間１　下
		*p_x = halfx_1;
		*p_y = bottom;
		break;

	case 12:	// 右　上
		*p_x = right;
		*p_y = top;
		break;

	case 13:	// 右　中間０
		*p_x = right;
		*p_y = halfy_0;
		break;

	case 14:	// 右　中間１
		*p_x = right;
		*p_y = halfy_1;
		break;

	case 15:	// 右　下
		*p_x = right;
		*p_y = bottom;
		break;
	}
}

