//==============================================================================
/**
 * @file	visual.h
 * @brief	ビジュアル部門のヘッダ
 * @author	matsuda
 * @date	2005.12.10(土)
 */
//==============================================================================
#ifndef __VISUAL_H__
#define __VISUAL_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/clact_tool.h"
#include "system/wordset.h"
#include "contest_order.h"
#include "visual_snd_def.h"
#include "contest/visual_ex.h"
#include "contest_type.h"



//==============================================================================
//	定数定義
//==============================================================================
///観客が同時に出せるハートの数
#define VISUAL_AUDIENCE_HEART_MAX		(8)

///サブ画面のサーフェース位置
#define VISUAL_SUB_ACTOR_DISTANCE		(256 * FX32_ONE)

//--------------------------------------------------------------
//	バッファ
//--------------------------------------------------------------
///文字列バッファのサイズ
#define VISUAL_MESSAGE_BUF_SIZE	(2*160)		///<暫定で１６０文字分

//--------------------------------------------------------------
//	フレーム番号：メイン
//--------------------------------------------------------------
///ウィンドウ・パネル面のフレーム
#define VISUAL_FRAME_WIN				(GF_BGL_FRAME1_M)
///エフェクト面のフレーム
#define VISUAL_FRAME_EFF				(GF_BGL_FRAME2_M)
///観客(背景)面のフレーム
#define VISUAL_FRAME_BACKGROUND			(GF_BGL_FRAME3_M)

///<BG番号：ウィンドウ
#define VISUAL_BGNO_WIN			(1)
///<BG番号：エフェクト
#define VISUAL_BGNO_EFF			(2)
///<BG番号：背景
#define VISUAL_BGNO_AUDIENCE	(3)

///<3D面のBGプライオリティ
#define VISUAL_3DBG_PRIORITY		(1)
///ウィンドウ面のBGプライオリティ
#define VISUAL_BGPRI_WIN			(0)
///エフェクト面のBGプライオリティ
#define VISUAL_BGPRI_EFF			(2)
///背景面のBGプライオリティ
#define VISUAL_BGPRI_AUDIENCE		(3)

//--------------------------------------------------------------
//	フレーム番号：サブ
//--------------------------------------------------------------
///観客面のフレーム
#define VISUAL_FRAME_SUB_AUDIENCE				(GF_BGL_FRAME0_S)

///<BG番号：観客
#define VISUAL_BGNO_SUB_AUDIENCE			(0)

///観客面のBGプライオリティ
#define VISUAL_BGPRI_SUB_AUDIENCE			(3)


//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
enum{
	VISUAL_BMPWIN_TALK,		///<会話ウィンドウ
	
	VISUAL_BMPWIN_MAX,
};


//--------------------------------------------------------------
//	会話ウィンドウ
//--------------------------------------------------------------
///会話ウィンドウのキャラクタ転送オフセット(キャラクタ単位)
#define VISUAL_TALKWIN_CGX_OFFSET	(1)
///会話ウィンドウ背景色
#define VISUAL_TALKWIN_BACK_COLOR	(15)
///会話ウィンドウのパレット番号
#define VISUAL_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	アクタープライオリティ
//--------------------------------------------------------------
///花柄模様のBGプライオリティ
#define V_FLOWER_BGPRI				(VISUAL_BGPRI_AUDIENCE)
///花柄模様のソフトプライオリティ
#define V_FLOWER_SOFTPRI			(200)
///観客ハートのBGプライオリティ
#define V_AUDIENCE_HEART_BGPRI		(1)
///観客ハートのソフトプライオリティ
#define V_AUDIENCE_HEART_SOFTPRI	(10)


//--------------------------------------------------------------
//	メッセージタグ
//--------------------------------------------------------------
///メッセージタグ
enum{
	VTAG_NONE,		///<タグなし
	
	VTAG_OYA_NICK,
	
	VTAG_MAX,
};


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
}VISUAL_MESSAGE_PARAM;

///メッセージタグ展開する場合、参照されるパラメータ類
typedef struct{
	u8 mine_brd;		///<MINEが指定されていた時に参照するブリーダーの番号
	u8 num;				///<NUMが指定されていた時に表示する数値
	u8 judge_no;		///<JUDGEが指定されていた時に参照する審判の番号
	
	u8 dummy;	//4バイト境界オフセット
}VTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///メインシーケンス内で使用するローカルワーク
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}VISUAL_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門進行パラメータ(現在技を出しているポケモンの進行パラメータ)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<現在場に出ているブリーダーの番号
	u8 evaluate_heart_num_bp;		///<観客が表示するハートの数(ブリーダーポイント分)
	u8 evaluate_heart_num_clip;		///<観客が表示するハートの数(クリップ分)

	VTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_VISUAL_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了

	s8 fade_start_evy;
	s8 fade_end_evy;
	s8 fade_wait;
	u16 fade_next_rgb;
	
	u16 se_id;
}VISUAL_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門ゲーム進行パラメータ
 *
 * このパラメータがあれば全画面を再構築出来るだけの情報が入っています。
 * 通信時はサーバーから子機はデータを受け取る事になります。
 * 基本的にメニュー画面からの画面復帰のような事がない限り、
 * 個々の子機側で値を参照する事はないはずです。
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_sort[BREEDER_MAX];	///<技を出す順番(出る順にブリーダー番号が入ってます)
	u8 breeder_end_count;			///<行動が終了したブリーダーの数をカウント
	
	s16 bp[BREEDER_MAX];			///<獲得したブリーダーポイント
}VISUAL_GAME_PARAM;

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
}VISUAL_ORDER_PARAM;

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
	SOFT_SPRITE *trainer_ss;
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[VISUAL_BMPWIN_MAX];
	MSGDATA_MANAGER *visual_msg;	///<ビジュアル部門メッセージ用メッセージマネージャのポインタ
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Allocした文字列バッファへのポインタ
	PALETTE_FADE_PTR pfd;			///<パレットフェードシステムへのポインタ

	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<技エフェクト用キャラ展開バッファ

	CATS_ACT_PTR heart_cap[VISUAL_AUDIENCE_HEART_MAX];	///<観客が出すハートアクターのポインタ
	
	FLOWER_WORK flower;				///<花柄模様制御ワーク
	
	u8 talk_msg_index;				///<文字描画ルーチンのインデックス
}VISUAL_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ビジュアル部門管理ワーク
 *
 * ビジュアル部門全体を管理する大元のワークになります。
 * 通信時でも全てのマシンで個別に作成されます
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_SYSTEM *consys;			///<コンテストシステムワークへのポインタ
	TCB_PTR update_tcb;
	GF_G3DMAN *g3Dman;
	
	VISUAL_SYSTEM_PARAM sys;			///<ビジュアル部門システムデータパラメータ
	VISUAL_GAME_PARAM v_game;			///<ゲーム進行パラメータ
	VISUAL_ADVANCE_PARAM advance;		///<進行パラメータ
	VISUAL_ORDER_PARAM order[BREEDER_MAX];	///<命令パラメータ
	
	u16 seq;
	u16 tbl_seq_no;					///<メインシーケンステーブルの番号
	u8 proc_mode;					///<現在の動作状況
	u8 heart_count;					///<場に出ているハートアクターの数をカウント
	
#if 0
	//-- 送受信バッファ --//
	u32 request_bit;				///<命令を出しているビット
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<送信用バッファ
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<受信用バッファ
	u8 transmit_flag;				///<TRUE：送信待ち。　FALSE:新たなデータセット可能
	u8 receive_flag;				///<TRUE：データ受信した
#endif
	CONTEST_ORDER_WORK cow;			///<送受信ワーク
	
	VISUAL_LOCAL_WORK local;			///<ローカルワーク
	u8 main_end;					///<TRUE:メイン処理終了
	
	//イメージクリップ
	CONTEST_IMC_WORK imcwork[BREEDER_MAX];	///<イメージクリップ関連ワーク

	u8 wnd0_x1;						///<ウィンドウ0のX1座標
	u8 wnd0_y1;
	u8 wnd0_x2;
	u8 wnd0_y2;

	u8 wnd1_x1;
	u8 wnd1_y1;
	u8 wnd1_x2;
	u8 wnd1_y2;
}VISUAL_PROC_WORK;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern PROC_RESULT VisualProc_Init( PROC * proc, int * seq );
extern PROC_RESULT VisualProc_Main( PROC * proc, int * seq );
extern PROC_RESULT VisualProc_End( PROC * proc, int * seq );

//==============================================================================
//	外部データ宣言
//==============================================================================
extern const PROC_DATA ContestVisualProcData;



#endif	//__VISUAL_H__

