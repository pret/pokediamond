//==============================================================================
/**
 * @file	actin_tcb_pri.h
 * @brief	演技部門のTCBプライオリティ定義
 * @author	matsuda
 * @date	2005.11.16(水)
 */
//==============================================================================
#ifndef __ACTIN_TCB_PRI_H__
#define __ACTIN_TCB_PRI_H__


///FightUpdate(アクターUpdate等実行している)	メインループの最後で実行
#define TCBPRI_ACTIN_UPDATE		(60000)

///技エフェクト実行タスク
#define TCBPRI_ACTIN_WAZAEFF	(5)

///命令実行サブタスクの汎用プライオリティ
#define TCBPRI_ACTIN_ORDERSUB	(30000)
///各種エフェクトの汎用プライオリティ
#define TCBPRI_ACTIN_EFFECT		(40000)

///技選択実行タスク
#define TCBPRI_ACTIN_WAZASELECT	(100)

///会話ウィンドウスクロールタスク
#define TCBPRI_ACTIN_TALKWIN_SLIDE	(1000)
///ブリーダーパネルαエフェクトタスク
#define TCBPRI_ACTIN_BRDPANEL_ALPHA	(1000)
///ブリーダーパネルαエフェクト：Vブランク転送タスク
#define TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK	(10)

///観客BGアニメタスク
#define TCBPRI_ACTIN_AUDIENCE_ANIME		(3000)

///ブリーダーパネルフラッシュエフェクト
#define TCBPRI_ACTIN_BRDPANEL_FLASH		(TCBPRI_ACTIN_EFFECT + 100)


//--------------------------------------------------------------
//	サブ画面
//--------------------------------------------------------------
///入力画面エフェクトTCB
#define TCBPRI_AINPUT_EFFECT	(1300)
///入力画面カラーエフェクトTCB
#define TCBPRI_AINPUT_COLOR_EFFECT	(1320)



#endif	//__ACTIN_TCB_PRI_H__

