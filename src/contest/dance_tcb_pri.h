//==============================================================================
/**
 * @file	dance_tcb_pri.h
 * @brief	ビジュアル部門のTCBプライオリティ定義
 * @author	matsuda
 * @date	2005.12.10(土)
 */
//==============================================================================
#ifndef __DANCE_TCB_PRI_H__
#define __DANCE_TCB_PRI_H__


///FightUpdate(アクターUpdate等実行している)	メインループの最後で実行
#define TCBPRI_DANCE_UPDATE		(80000)

///命令実行サブタスクの汎用プライオリティ
#define TCBPRI_DANCE_ORDERSUB	(30000)

///AI実行のプライオリティ(一応プレイヤー操作よりも後に実行させる)
#define TCBPRI_DANCE_AI_CALC	(TCBPRI_DANCE_ORDERSUB + 10)
///ダンスした時のパラメータ送信タスクのプライオリティ
#define TCBPRI_DANCE_DANCING_PARAM_SEND		(TCBPRI_DANCE_ORDERSUB + 100)

///ポケモン常駐アニメーション実行タスクのプライオリティ
#define TCBPRI_DANCE_DEFANM				(TCBPRI_DANCE_ORDERSUB + 9000)
///ポケモンダンスアニメーション実行タスクのプライオリティ
#define TCBPRI_DANCE_MOVE				(TCBPRI_DANCE_DEFANM + 10)

///エフェクト用の基本プライオリティ(これより上は基本的にシステム系)
#define TCBPRI_DANCE_EFFECT_BASE_PRI	(TCBPRI_DANCE_ORDERSUB + 10000)

///ローテーション時の各ブリーダー動作タスクのプライオリティ
#define TCBPRI_DANCE_ROTATION	(TCBPRI_DANCE_EFFECT_BASE_PRI + 100)
///自分を指すカーソルの動作タスクプライオリティ
#define TCBPRI_DANCE_MY_CURSOR	(TCBPRI_DANCE_ROTATION + 10)

///影の動作プライオリティ(ポケモンの常駐アニメ、ローテーションよりも後に設定)
#define TCBPRI_DANCE_SHADOW		(TCBPRI_DANCE_ROTATION + 1000)

///評価パネルエフェクトプライオリティ
#define TCBPRI_DANCE_REVIEWPANEL	(TCBPRI_DANCE_EFFECT_BASE_PRI + 200)

///プリン動作タスク
#define TCBPRI_PRIN_MAIN			(TCBPRI_DANCE_EFFECT_BASE_PRI + 15)


//--------------------------------------------------------------
//	サブ画面
//--------------------------------------------------------------
///入力画面エフェクトTCB
#define TCBPRI_DINPUT_EFFECT	(1300)



#endif	//__DANCE_TCB_PRI_H__

