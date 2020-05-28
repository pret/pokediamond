//==============================================================================
/**
 * @file	dance_snd_def.h
 * @brief	コンテスト：ダンス部門　SE定義ファイル
 * @author	matsuda
 * @date	2006.03.01(水)
 */
//==============================================================================
#ifndef __DANCE_SND_DEF_H__
#define __DANCE_SND_DEF_H__

#include "system/snd_tool.h"


//--------------------------------------------------------------
/**
 * デバッグ用SE非再生定義
 *
 * この定義があると、仮当てしているSEは再生されません
 * ※check
 */
//--------------------------------------------------------------
//#define DEBUG_DANCE_SE_PLAY

//--------------------------------------------------------------
//
//--------------------------------------------------------------
///カーソル決定
#define DSE_DECIDE			(SEQ_SE_DP_DECIDE)

///オープニング時のライトがつく時のSE
#define DSE_LIGHT_ON		(SEQ_SE_DP_CON_019)	// SE-DP-POKETCH-006

//--------------------------------------------------------------
//	PLAYER3
//--------------------------------------------------------------
///ダンス部門が開始した時の歓声
#define DSE_START_SHOUT		(SEQ_SE_DP_CON_007)
///Finishパーティクルが出たときの歓声
#define DSE_FINISH_DANCE	(SEQ_SE_DP_CON_007)
///ダンス部門が終了した時の歓声
#define DSE_END_SHOUT		(SEQ_SE_DP_CON_007)

//--------------------------------------------------------------
//	PLAYER4
//--------------------------------------------------------------
//定義有効で、ポケモンの動きで音が鳴る
#define DEBUG_DANCE_SE_PLAY_POKE_MOVE

///ポケモンダンスアニメ：通常
//#define DSE_STEP_NORMAL	(SEQ_SE_DP_CON_027)	//SE-DP-POKELIST-001
//#define DSE_STEP_NORMAL		(SEQ_SE_DP_CON_027_2)	//SE-DP-POKELIST-001
#define DSE_STEP_NORMAL		(SEQ_SE_DP_CON_027_3)	//SE-DP-POKELIST-001

///ポケモンダンスアニメ：決め
#define DSE_STEP_FINISH		(SEQ_SE_DP_CON_028)	//SE-DP-W030

//--------------------------------------------------------------
//	PLAYER1
//--------------------------------------------------------------
///ダンスボタン：ジャンプ
#define DSE_BUTTON_JUMP		(SEQ_SE_DP_CON_009)

///ダンスボタン：前進
#define DSE_BUTTON_ADVANCE	(SEQ_SE_DP_CON_010)

///ダンスボタン：左
#define DSE_BUTTON_LEFT		(SEQ_SE_DP_CON_011)

///ダンスボタン：右
#define DSE_BUTTON_RIGHT	(SEQ_SE_DP_CON_012)

//--------------------------------------------------------------
//	PLAYER2
//--------------------------------------------------------------
///Excellent1回目
#define DSE_EXCELLENT_1		(SEQ_SE_DP_CON_021)	//SE-DP-KIRAKIRA3

///Excellent2回目
#define DSE_EXCELLENT_2		(SEQ_SE_DP_CON_022)	//SE-DP-KIRAKIRA

///Excellent3回目
#define DSE_EXCELLENT_3		(SEQ_SE_DP_CON_023)	//SE-DP-KIRAKIRA4

///Good
#define DSE_GOOD			(SEQ_SE_DP_CON_024)	//SE-DP-UG-004

///Failed
//#define DSE_FAILED		(SEQ_SE_DP_CON_025)	//SE-DP-CARD10
#define DSE_FAILED			(SEQ_SE_DP_CARD10)	//SE-DP-CARD10

///違うボタンを押していた
#define DSE_FAILED_BUTTON	(SEQ_SE_DP_CON_026)	//SE-DP-UG-003

//--------------------------------------------------------------
//
//--------------------------------------------------------------
///自分のターンになった
#define DSE_MY_TURN			(SEQ_SE_DP_CON_031)
///ローテーションに合わせて
#define DSE_ROTATION		(SEQ_SE_DP_CON_030)


#endif	//__DANCE_SND_DEF_H__
