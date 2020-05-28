//==============================================================================
/**
 * @file	battle_tcb_pri.h
 * @brief	戦闘画面で動作するTCBのプライオリティ定義
 * @author	matsuda
 * @date	2005.09.29(木)
 */
//==============================================================================
#ifndef __BATTLE_TCB_PRI_H__
#define __BATTLE_TCB_PRI_H__


///FightUpdate(アクターUpdate等実行している)	メインループの最後で実行
#define TCBPRI_FIGHT_UPDATE		(60000)

//ピンチSEのチェック
#define TCBPRI_PINCH_SE_CHECK	(50000)

///HPゲージIN 実動作タスク
#define TCBPRI_HP_GAUGE_IN_TASK	(990)
///HPゲージIN
#define TCBPRI_HP_GAUGE_IN		(1000)
///HPゲージ計算
#define TCBPRI_HP_GAUGE_CALC	(1000)
///HPゲージSinカーブエフェクト実行タスク
#define TCBPRI_HP_GAUGE_SIN_CURVE	(1010)
///選択中のポケモン揺れSinカーブエフェクト実行タスク
#define TCBPRI_HP_POKEYURE_SIN_CURVE	(1010)

///ボールエフェクト
#define TCBPRI_BALL_EFFECT		(1000)

///背景切り替えTCB
#define TCBPRI_HAIKEI_CHANGE	(1100)

///サウンドコントロールTCB
#define TCBPRI_SE_CONTROL		(1100)

///エフェクトサポート関数用TCB
#define TCBPRI_WE_SUPPORT		(1100)

///ゲージレベルアップエフェクト
#define TCBPRI_GAUGE_LEVELUP_EFF	(1000)

///手持ちゲージ：矢印動作
#define TCBPRI_TEMOTIGAUGE_ARROW	(500)
///手持ちゲージ：ボール動作
#define TCBPRI_TEMOTIGAUGE_BALL		(TCBPRI_TEMOTIGAUGE_ARROW + 1)

#define TCBPRI_MSG_WIN_MOVE			( 1200 )

//--------------------------------------------------------------
//	戦闘入力画面
//--------------------------------------------------------------
///戦闘入力画面プレイヤー背景スクロールエフェクトTCB
#define TCBPRI_BINPUT_PLAYER_SCROLL_EFFECT	(1200)
///戦闘入力画面：コマンド選択スクロールエフェクトTCB
#define TCBPRI_BINPUT_COMMAND_IN_EFFECT		(1210)

///戦闘入力画面エフェクトTCB
#define TCBPRI_BINPUT_EFFECT	(1300)
///戦闘入力画面常駐カラーエフェクトTCB
#define TCBPRI_BINPUT_DEF_COLOR_EFFECT	(1310)
///戦闘入力画面カラーエフェクトTCB
#define TCBPRI_BINPUT_COLOR_EFFECT	(1320)

///戦闘入力画面：黒枠拡大エフェクトTCB
#define TCBPRI_BINPUT_BLACK_WAKU_EFFECT	(1200)
///戦闘入力画面：背景フェードTCB
#define TCBPRI_BINPUT_BACKFADE			(3000)

///戦闘入力画面：カーソルOBJUpdate
#define TCBPRI_BCURSOR					(40000)

///戦闘入力画面：背景パレット切り替え
#define TCBPRI_BACKGROUND_PAL			(55000)

///戦闘入力画面：捕獲デモ用指カーソル
#define TCBPRI_FINGER					(999)


#endif	//__BATTLE_TCB_PRI_H__

