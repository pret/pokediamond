//=============================================================================
/**
 * @file	comm_field_state.h
 * @brief	通信状態を管理するサービス  通信の上位にある
 *          スレッドのひとつとして働き、自分の通信状態や他の機器の
 *          開始や終了を管理する
 *          フィールド上で直接管理したいのでcommunicationからfieldに移動 2005.09.28
 * @author	Katsumi Ohno
 * @date    2005.08.08
 */
//=============================================================================

#ifndef __COMM_FIELD_STATE_H__
#define __COMM_FIELD_STATE_H__

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "savedata/undergrounddata.h"  //SECRETBASEDATA

#define COMM_HEAPSIZE_BATTLE_CHILD    (0x9000)  // バトル子機領域
#define COMM_HEAPSIZE_BATTLE_PARENT   (0x9000)  // バトル親機領域
#define COMM_HEAPSIZE_UNDERGROUND     (0xB000)  // 地下領域


//==============================================================================
// extern宣言
//==============================================================================


// 地下に入る場合の処理 ステートが地下用に変更される
extern void CommFieldStateEnterUnderGround(FIELDSYS_WORK* pFSys);

extern void CommFieldStateArrivalUnderGround(void);

// 地下をでる場合の処理 ステートが何もなしに変更される
extern void CommFieldStateExitUnderGround(void);
// 地下をJUMPする場合の処理 ステートがHold状態になる
extern BOOL CommStateJumpUnderGround(void);
// 地下を通信切断してJUMPする場合の処理 ステートがHold状態になる
extern void CommStateExitAndJumpUnderGround(void);
// 地下を通信切断するが、サービスは残したまま
extern void CommFieldStateStalthUnderGround(void);
// 地下通信を再開
extern void CommFieldStateUnderGroundReConnect(void);

// 地下をJUMPし終わった場合の処理 ステートがActive状態になる
extern BOOL CommStateJumpEndUnderGround(void);

// バトル時に親になる場合の処理開始
extern void CommFieldStateEnterBattleParent(FIELDSYS_WORK* pFSys,int serviceNo, int regulationNo);
// バトル時に子になる場合の処理開始
extern void CommFieldStateEnterBattleChild(FIELDSYS_WORK* pFSys,int serviceNo, int regulationNo);
// バトル時に親を決めた際の子機の処理
extern void CommFieldStateConnectBattleChild(int connectIndex);
// バトル時に子機を再起動する時の処理
extern void CommFieldStateRebootBattleChild(void);
// バトル時に移動できる部屋に入る時の処理
extern void CommFieldStateEnterBattleRoom(FIELDSYS_WORK* pFSys);
// 移動位置に来たことの受信
extern void CommDirectRecvStartPos(int netID, int size, void* pData, void* pWork);
// 移動位置にいるかどうか
extern BOOL CommDirectIsMoveState(void);
// データコピーが終わったかどうか
extern BOOL CommFieldStateIsCopyEnd(void);

// トレーナーカード閲覧
extern void CommDCRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork );
// トレーナーカード閲覧
extern u8* CommDCGetTrainerCardRecvBuff( int netID, void* pWork, int size);

// 終了処理手続き
extern void CommFieldStateExitBattle(void);
// 終了処理手続き タイミング同期版
extern void CommFieldStateExitBattleTiming(void);

// 移動可能ステートなのかどうか返す
extern BOOL CommIsUnderGroundMoveState(void);

#ifdef PM_DEBUG
//
extern void CommFieldStateConnectBattleChild_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo, int connectIndex);
//
extern void CommFieldStateEnterBattleParent_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo);

#endif

extern SECRETBASEDATA* CommUgSetupSecretBaseData(SAVEDATA * sv);
extern BOOL CommFieldStateIsUnder(void);
extern void CommStateFieldUnderOptionReset(void);
extern void CommStateFieldUnderOptionReboot(void);

#endif //__COMM_FIELD_STATE_H__

