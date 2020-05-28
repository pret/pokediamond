//==============================================================================
/**
 * @file	res_tcb_pri.h
 * @brief	コンテスト結果発表画面のTCBプライオリティ定義
 * @author	matsuda
 * @date	2006.03.17(金)
 */
//==============================================================================
#ifndef __RES_TCB_PRI_H__
#define __RES_TCB_PRI_H__


///FightUpdate(アクターUpdate等実行している)	メインループの最後で実行
#define TCBPRI_CONRES_UPDATE		(80000)

///命令実行サブタスクの汎用プライオリティ
#define TCBPRI_CONRES_ORDERSUB	(30000)

///結果発表画面切り替え時のプライオリティ
#define TCBPRI_CONRES_RESULT_CHANGE		(1000)


///エフェクト用の基本プライオリティ(これより上は基本的にシステム系)
#define TCBPRI_CONRES_EFFECT_BASE_PRI	(TCBPRI_CONRES_ORDERSUB + 10000)

///ウィンドウ機能の開く閉じる実行タスク
#define TCBPRI_CONRES_WNDOPEN		(TCBPRI_CONRES_EFFECT_BASE_PRI + 1000)

///各種エフェクト用の汎用プライオリティ
#define TCBPRI_CONRES_EFFECT		(50000)

///紙ふぶき生成タスクのプライオリティ
#define TCBPRI_CONRES_CONFETTI_SYS	(TCBPRI_CONRES_EFFECT + 10)
///紙ふぶきアクター動作タスクのプライオリティ
#define TCBPRI_CONRES_CONFETTI_ACTOR	(TCBPRI_CONRES_CONFETTI_SYS + 1)

///ポケモンアイコンアニメ更新処理
#define TCBPRI_POKEICON_UPDATE		(TCBPRI_CONRES_EFFECT + 1000)

///フラッシュエフェクト
#define TCBPRI_CONRES_FLASH_EFF		(TCBPRI_CONRES_EFFECT + 5000)


//--------------------------------------------------------------
//	サブ画面
//--------------------------------------------------------------



#endif	//__RES_TCB_PRI_H__

