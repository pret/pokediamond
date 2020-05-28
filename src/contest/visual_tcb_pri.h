//==============================================================================
/**
 * @file	visual_tcb_pri.h
 * @brief	ビジュアル部門のTCBプライオリティ定義
 * @author	matsuda
 * @date	2005.12.10(土)
 */
//==============================================================================
#ifndef __VISUAL_TCB_PRI_H__
#define __VISUAL_TCB_PRI_H__


///FightUpdate(アクターUpdate等実行している)	メインループの最後で実行
#define TCBPRI_VISUAL_UPDATE		(60000)

///命令実行サブタスクの汎用プライオリティ
#define TCBPRI_VISUAL_ORDERSUB		(30000)
///命令実行サブタスクの中で生成されるタスクの汎用プライオリティ
#define TCBPRI_VISUAL_ORDERSUB_SUB	(TCBPRI_VISUAL_ORDERSUB + 10)

///各種エフェクト用の汎用プライオリティ
#define TCBPRI_VISUAL_EFFECT		(50000)


//--------------------------------------------------------------
//	サブ画面
//--------------------------------------------------------------



#endif	//__VISUAL_TCB_PRI_H__

