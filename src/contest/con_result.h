//==============================================================================
/**
 * @file	con_result.h
 * @brief	コンテスト結果発表画面のヘッダ
 * @author	matsuda
 * @date	2006.03.17(金)
 */
//==============================================================================
#ifndef __CON_RESULT_H__
#define __CON_RESULT_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "contest_order.h"
#include "system/fontoam.h"

#include "adv_tool.h"
#include "res_snd_def.h"



//==============================================================================
//	定数定義
//==============================================================================
//--------------------------------------------------------------
//	結果発表画面の画面モード
//--------------------------------------------------------------
///現在の画面モード
enum{
	RESDISP_MODE_ANNOUNCE,		///<アナウンス画面
	RESDISP_MODE_RESULT,		///<結果発表画面
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ポケモン定位置Z(メインダンサー)
#define CONRES_POKEPOS_Z_MAIN		(APPEAR_Z_TYPE_AA)
///ポケモン定位置Z(バックダンサー)
#define CONRES_POKEPOS_Z_SUB			(CONRES_POKEPOS_Z_MAIN - 0x80)

///メインダンサーのポケモン拡縮率(XY共通)
#define CONRES_POKEAFF_MAIN		(0x0100)
///バックダンサーのポケモン拡縮率(XY共通)
#define CONRES_POKEAFF_BACK		(0x00c0)	//(0x0080)

///ダンス部門メイン画面で使用するフォントOAMの最大数
#define CONRES_FONTOAM_MAX_MAIN	(10)	// 10 = とりあえず適当

//--------------------------------------------------------------
//	バッファ
//--------------------------------------------------------------
///文字列バッファのサイズ
#define CONRES_MESSAGE_BUF_SIZE	(2*160)		///<暫定で１６０文字分

//--------------------------------------------------------------
//	フレーム番号
//--------------------------------------------------------------
///ウィンドウ・メッセージ面のフレーム
#define CONRES_FRAME_WIN				(GF_BGL_FRAME1_M)
///エフェクト面のフレーム
#define CONRES_FRAME_EFF				(GF_BGL_FRAME2_M)
///背景面のフレーム
#define CONRES_FRAME_BACKGROUND			(GF_BGL_FRAME3_M)

///サブ画面：観客面のフレーム
#define CONRES_FRAME_SUB_AUDIENCE		(GF_BGL_FRAME0_S)

///BG番号：ウィンドウ
#define CONRES_BGNO_WIN			(1)
///BG番号：エフェクト
#define CONRES_BGNO_EFF			(2)
///BG番号：背景
#define CONRES_BGNO_BACKGROUND	(3)

///GX_WND番号：エフェクト
#define CONRES_GX_WND_EFF			(GX_WND_PLANEMASK_BG2)

///<3D面のBGプライオリティ
#define CONRES_3DBG_PRIORITY		(1)
///ウィンドウ面のBGプライオリティ
#define CONRES_BGPRI_WIN			(2)
///エフェクト面のBGプライオリティ
#define CONRES_BGPRI_EFF			(1)
///背景面のBGプライオリティ
#define CONRES_BGPRI_BACKGROUND		(3)

///<サブ画面：背景面のBGプライオリティ
///観客面のBGプライオリティ
#define CONRES_BGPRI_SUB_AUDIENCE	(3)

//--------------------------------------------------------------
//	会話ウィンドウ
//--------------------------------------------------------------
///会話ウィンドウのキャラクタ転送オフセット(キャラクタ単位)
#define CONRES_TALKWIN_CGX_OFFSET	(1)
///会話ウィンドウ背景色
#define CONRES_TALKWIN_BACK_COLOR	(15)
///会話ウィンドウのパレット番号
#define CONRES_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
///BMPウィンドウCGXエリア開始位置(オフセット)
#define RES_BMPWIN_CGX_START			(TALK_WIN_CGX_SIZ + CONRES_TALKWIN_CGX_OFFSET)

#define RES_BMPWIN_TALK_COLOR			(13)
#define RES_BMPWIN_TALK_CGX_OFFSET		(RES_BMPWIN_CGX_START)
#define RES_BMPWIN_TALK_POS_X			(0x2)
#define RES_BMPWIN_TALK_POS_Y			(0x13)
#define RES_BMPWIN_TALK_SIZE_X			(27)
#define RES_BMPWIN_TALK_SIZE_Y			(4)
#define RES_BMPWIN_TALK_CGX_SIZE		(RES_BMPWIN_TALK_SIZE_X * RES_BMPWIN_TALK_SIZE_Y)

#define RES_BMPWIN_NAME_COLOR			(RES_BMPWIN_TALK_COLOR)
#define RES_BMPWIN_NAME_GF_COLOR		(GF_PRINTCOLOR_MAKE(1, 2, 0))
#define RES_BMPWIN_NAME_DOT_OFFSET		(3)

#define RES_BMPWIN_NICK_SIZE_X			(8)
#define RES_BMPWIN_NICK_SIZE_Y			(3)		//表示位置を数ドット下にずらすので3キャラにまたぐ
#define RES_BMPWIN_NICK_CGX_SIZE		(RES_BMPWIN_NICK_SIZE_X * RES_BMPWIN_NICK_SIZE_Y)
#define RES_BMPWIN_POS_X_NICK			(6)
#define RES_BMPWIN_POS_Y_NICK			(1)
#define RES_BMPWIN_POS_Y_SPACE_NICK		(4)

#define RES_BMPWIN_OYA_SIZE_X			(8)
#define RES_BMPWIN_OYA_SIZE_Y			(3)		//表示位置を数ドット下にずらすので3キャラにまたぐ
#define RES_BMPWIN_OYA_CGX_SIZE			(RES_BMPWIN_OYA_SIZE_X * RES_BMPWIN_OYA_SIZE_Y)
#define RES_BMPWIN_POS_X_OYA			(0x10)
#define RES_BMPWIN_POS_Y_OYA			(RES_BMPWIN_POS_Y_NICK)
#define RES_BMPWIN_POS_Y_SPACE_OYA		(RES_BMPWIN_POS_Y_SPACE_NICK)

#define RES_BMPWIN_NICK_CGX_OFFSET_0	(RES_BMPWIN_TALK_CGX_OFFSET + RES_BMPWIN_TALK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_1	(RES_BMPWIN_NICK_CGX_OFFSET_0 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_2	(RES_BMPWIN_NICK_CGX_OFFSET_1 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_NICK_CGX_OFFSET_3	(RES_BMPWIN_NICK_CGX_OFFSET_2 + RES_BMPWIN_NICK_CGX_SIZE)

#define RES_BMPWIN_OYA_CGX_OFFSET_0	(RES_BMPWIN_NICK_CGX_OFFSET_3 + RES_BMPWIN_NICK_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_1	(RES_BMPWIN_OYA_CGX_OFFSET_0 + RES_BMPWIN_OYA_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_2	(RES_BMPWIN_OYA_CGX_OFFSET_1 + RES_BMPWIN_OYA_CGX_SIZE)
#define RES_BMPWIN_OYA_CGX_OFFSET_3	(RES_BMPWIN_OYA_CGX_OFFSET_2 + RES_BMPWIN_OYA_CGX_SIZE)

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
enum{
	CONRES_BMPWIN_TALK,		///<会話ウィンドウ
	
	CONRES_BMPWIN_NICK_0,	///<ニックネーム
	CONRES_BMPWIN_NICK_1,	///<ニックネーム
	CONRES_BMPWIN_NICK_2,	///<ニックネーム
	CONRES_BMPWIN_NICK_3,	///<ニックネーム

	CONRES_BMPWIN_OYA_0,	///<親名
	CONRES_BMPWIN_OYA_1,	///<親名
	CONRES_BMPWIN_OYA_2,	///<親名
	CONRES_BMPWIN_OYA_3,	///<親名
	
	CONRES_BMPWIN_MAX,
};

//--------------------------------------------------------------
//	メッセージ
//--------------------------------------------------------------
///メッセージタグ
enum{
	CRTAG_NONE,		///<タグなし
	
	CRTAG_RANK,		///<コンテストランク
	CRTAG_OYA_NICK,	///<親名、ニックネーム
	CRTAG_NUM_OYA_NICK,	///<数値、親名、ニックネーム
	
	CRTAG_MAX,
};

//--------------------------------------------------------------
//	アクタープライオリティ
//--------------------------------------------------------------
///花柄模様のBGプライオリティ
#define R_FLOWER_BGPRI				(CONRES_BGPRI_BACKGROUND)
///花柄模様のソフトプライオリティ
#define R_FLOWER_SOFTPRI			(200)

///ポケモンアイコンのBGプライオリティ
#define R_POKEICON_BGPRI			(CONRES_BGPRI_BACKGROUND)
///ポケモンアイコンのソフトプライオリティ
#define R_POKEICON_SOFTPRI			(100)

///紙ふぶきのBGプライオリティ
#define R_CONFETTI_BGPRI			(CONRES_BGPRI_EFF)
///紙ふぶきのソフトプライオリティ
#define R_CONFETTI_SOFTPRI			(20)

///順位アイコンのBGプライオリティ
#define R_RANKING_BGPRI				(CONRES_BGPRI_BACKGROUND)
///順位アイコンのソフトプライオリティ
#define R_RANKING_SOFTPRI			(100)

///メーターのBGプライオリティ
#define R_METER_BGPRI				(CONRES_BGPRI_BACKGROUND)
///メーターのソフトプライオリティ
#define R_METER_SOFTPRI				(110)

//--------------------------------------------------------------
//	得点取得関連
//--------------------------------------------------------------
///1位の得点を基準に各ブリーダーが持つメーターのパーセンテージを取得する際のMAXパーセンテージ
#define RES_METER_PERCENT_MAX		(100)
///得点メーター最大キャラ数
#define RES_METER_CHAR_MAX			(24)
///得点メーター最大ドット数
#define RES_METER_DOT_MAX			(RES_METER_CHAR_MAX * 8)

///メーターのアクター１つの横幅ドット数
#define RES_METER_ACT_SIZE_X		(16)
///メーターアクター数
#define RES_METER_CAP_MAX			(RES_METER_DOT_MAX / RES_METER_ACT_SIZE_X)


//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
//	メッセージ
//--------------------------------------------------------------
///演技部門メッセージデータ
typedef struct{
	u16 msg_id;				///<メッセージID
	u8 msg_tag;				///<タグコード
}CONRES_MESSAGE_PARAM;

///メッセージタグ展開する場合、参照されるパラメータ類
typedef struct{
	u8 mine_brd;		///<MINEが指定されていた時に参照するブリーダーの番号
	u8 enemy_brd;		///<ENEMYが指定されていた時に参照するブリーダーの番号
	u16 wazano;			///<WAZAが指定されていた時に参照する技番号
	u8 num;				///<NUMが指定されていた時に表示する数値
	u8 judge_no;		///<JUDGEが指定されていた時に参照する審判の番号
}CRTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------

///メインシーケンス内で使用するローカルワーク
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}CONRES_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門進行パラメータ(現在技を出しているポケモンの進行パラメータ)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<現在場に出ているブリーダーの番号
	u8 now_pos;						///<現在場に出ているブリーダーが何番目にアピールしているか
	
	u8 victory_breeder;				///<優勝したブリーダーの番号
	u8 ranking[BREEDER_MAX];		///<順位(1位から順にブリーダー番号が入ります)
	
	u8 meter_type;					///<伸ばすメータータイプ(CONGAME_???)
	
	CRTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_CONRES_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
	u8 a_talk_bmpwin_not_open;		///<TRUE:ウィンドウ描画を行わない
}CONRES_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門ゲーム進行パラメータ
 *
 * このパラメータがあれば全画面を再構築出来るだけの情報が入っています。
 * 通信時はサーバーから子機はデータを受け取る事になります。
 * 基本的にメニュー画面からの画面復帰のような事がない限り、
 * 個々の子機側で値を参照する事はないはずです。
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_SCORE score[BREEDER_MAX];	///<得点
	
	u8 breeder_sort[BREEDER_MAX];	///<技を出す順番(出る順にブリーダー番号が入ってます)
	u8 breeder_end_count;			///<行動が終了したブリーダーの数をカウント

	u8 ranking[BREEDER_MAX];		///<順位(1位から順にブリーダー番号が入ります)
	s16 visual_revise[BREEDER_MAX];	///<ビジュアルゲーム：修正値
	s16 dance_revise[BREEDER_MAX];	///<ダンスゲーム：修正値
	s16 actin_revise[BREEDER_MAX];	///<演技ゲーム：修正値
	s16 total_revise[BREEDER_MAX];	///<総合修正値
	s16 visual_percent[BREEDER_MAX];	///<ビジュアルゲーム：修正値
	s16 dance_percent[BREEDER_MAX];	///<ダンスゲーム：修正値
	s16 actin_percent[BREEDER_MAX];	///<演技ゲーム：修正値
	s16 total_percent[BREEDER_MAX];	///<総合修正値を1位を100%した場合の変換したもの
	s16 gauge_dot[BREEDER_MAX];		///<total_percentをドット数に変換したもの
	s16 visual_dot[BREEDER_MAX];	///<ビジュアルが持つゲージドット数
	s16 dance_dot[BREEDER_MAX];		///<ダンスが持つゲージドット数
	s16 actin_dot[BREEDER_MAX];		///<演技が持つゲージドット数
}CONRES_GAME_PARAM;

//--------------------------------------------------------------
/**
 * @brief   命令送受信用パラメータ
 * 
 * サーバーとの命令の送受信に使用します
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_no;
	
	u8 buffer[255];					///<各命令で個別に渡すデータが変わる場合、ここを使用
}CONRES_ORDER_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ゲーム画面を構成するために必要なシステムデータ類を持つ構造体
 *
 * 通信時でも全てのマシンで個別に作成されます
 * 各スタッフが命令受信時、そのマシン個々で生成したこのワークバッファを渡す事になります
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_GAME_PARAM *c_game;		///<コンテスト進行パラメータ(受付で既に通信済みのデータへのポインタを持つだけ。参照用)
	
	SOFT_SPRITE_MANAGER	*soft_sprite;
	SOFT_SPRITE *ss[BREEDER_MAX];
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[CONRES_BMPWIN_MAX];
	MSGDATA_MANAGER *conres_msg;	///<ダンス部門メッセージ用メッセージマネージャのポインタ
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Allocした文字列バッファへのポインタ
	PALETTE_FADE_PTR pfd;			///<パレットフェードシステムへのポインタ
	FONTOAM_SYS_PTR fontoam_sys;	///<フォントOAMシステムへのポインタ
	
	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<技エフェクト用キャラ展開バッファ

	FLOWER_WORK flower;				///<花柄模様制御ワーク

	TCB_PTR pokeicon_tcb;							///<ポケモンアイコンアニメ更新処理タスク
	CATS_ACT_PTR pokeicon_cap[BREEDER_MAX];			///<ポケモンアイコンアクターへのポインタ
	CATS_ACT_PTR ranking_cap[BREEDER_MAX];			///<順位アクターへのポインタ
	CATS_ACT_PTR visual_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<ビジュアルメーター
	CATS_ACT_PTR dance_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<ダンスメーター
	CATS_ACT_PTR actin_meter_cap[BREEDER_MAX][RES_METER_CAP_MAX];	///<演技メーター
	
	u8 talk_msg_index;				///<文字描画ルーチンのインデックス
}CONRES_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門管理ワーク
 *
 * ダンス部門全体を管理する大元のワークになります。
 * 通信時でも全てのマシンで個別に作成されます
 */
//--------------------------------------------------------------
typedef struct _CONRES_PROC_WORK{
	CONTEST_SYSTEM *consys;			///<コンテストシステムワークへのポインタ
	TCB_PTR update_tcb;				///<システム更新処理
	TCB_PTR vintr_tcb;				///<Vブランク割り込みタスク
	GF_G3DMAN *g3Dman;
	
	CONRES_SYSTEM_PARAM sys;			///<ダンス部門システムデータパラメータ
	CONRES_GAME_PARAM r_game;			///<ゲーム進行パラメータ
	CONRES_ADVANCE_PARAM advance;		///<進行パラメータ
	CONRES_ORDER_PARAM order[BREEDER_MAX];	///<命令パラメータ
	
	void *flash_eff;				///<カメラのフラッシュエフェクトワーク
	
	u16 seq;
	u16 tbl_seq_no;					///<メインシーケンステーブルの番号
	u8 proc_mode;					///<現在の動作状況

	u8 wnd0_x1;						///<ウィンドウ0のX1座標
	u8 wnd0_y1;
	u8 wnd0_x2;
	u8 wnd0_y2;

	u8 wnd1_x1;
	u8 wnd1_y1;
	u8 wnd1_x2;
	u8 wnd1_y2;
	
	CONTEST_ORDER_WORK cow;			///<送受信ワーク

	CONRES_LOCAL_WORK local;			///<ローカルワーク
	u8 main_end;					///<TRUE:メイン処理終了
	
	u8 confetti_end;				///<TRUE:紙ふぶきアクター削除リクエスト
	u8 confetti_count;				///<紙ふぶきが生成されている数をカウント
	
	u8 disp_mode;					///<RESDISP_MODE_???
}CONRES_PROC_WORK;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern PROC_RESULT ConresProc_Init( PROC * proc, int * seq );
extern PROC_RESULT ConresProc_Main( PROC * proc, int * seq );
extern PROC_RESULT ConresProc_End( PROC * proc, int * seq );

//==============================================================================
//	外部データ宣言
//==============================================================================
extern const PROC_DATA ContestResultProcData;



#endif	//__CON_RESULT_H__

