//=============================================================================
/**
 * @file	comm_direct_counter.h
 * @bfief	通信ダイレクトコーナーのカウンター
 * @author	katsumi ohno
 * @date	05/08/04
 */
//=============================================================================

#ifndef __COMM_VSROOM_H__
#define __COMM_VSROOM_H__

#include "poketool\pokeparty.h"

typedef void (StartLineCallBack)(BOOL bStart, const POKEPARTY* party);

/// 定位置についた時のイベント
extern void EventCmd_StartLine(FIELDSYS_WORK* pFSys,StartLineCallBack* pCallBack);
/// トレーナーとの会話
extern void EventCmd_VSRoomTrainer(FIELDSYS_WORK* pFSys);



// ミックスバトル用データ通信関数群
extern void CommMixBattleRecv(int netID, int size, void* pBuff, void* pWork);
extern int  CommMixBattleGetDataSize( void );
extern u8* CommMixBattleGetBuffer( int netID, void* pWork, int size );
extern void CommMixBattleTradeRecv( int netID, int size, void* pBuff, void* pWork );

#endif  // __COMM_VSROOM_H__
