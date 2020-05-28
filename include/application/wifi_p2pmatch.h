//============================================================================================
/**
 * @file	wifi_p2pmatch.h
 * @bfief	WIFI P2P接続のマッチング
 * @author	k.ohno
 * @date	06.04.07
 */
//============================================================================================
#ifndef __WIFI_P2PMATCH_H__
#define __WIFI_P2PMATCH_H__

#include "application/wifi_p2pmatch_def.h"

//============================================================================================
//	定義
//============================================================================================

//------------------------------------------------------
/**
 * WIFIともだちリストPROCパラメータ
 */
//------------------------------------------------------
typedef struct {
	SAVEDATA*  pSaveData;
    int seq;                // どこに分岐してほしいかが入っている
    int targetID;   //対戦 交換する人が誰なのかが入っている
}WIFIP2PMATCH_PROC_PARAM;

// プロセス定義データ
extern PROC_RESULT WifiP2PMatchProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WifiP2PMatchProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WifiP2PMatchProc_End( PROC * proc, int * seq );

// ポインタ参照だけできるレコードコーナーワーク構造体
typedef struct _WIFIP2PMATCH_WORK WIFIP2PMATCH_WORK;	

// 呼び出すためのイベント
extern void EventCmd_P2PMatchProc(GMEVENT_CONTROL * event);
// 世界交換前に呼び出すためのイベント
extern void EventCmd_DPWInitProc(GMEVENT_CONTROL * event);
//
extern void EventCmd_DPWInitProc2(GMEVENT_CONTROL * event, u16* ret);


#endif //__WIFI_P2PMATCH_H__
