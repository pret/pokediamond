//=============================================================================
/**
 * @file	comm_player.c
 * @bfief	通信で相手側のプレーヤーを表示する
 * @author	katsumi ohno
 * @date	05/07/14
 */
//=============================================================================

#ifndef __COMM_PLAYER_H__
#define	__COMM_PLAYER_H__

// ありえない座標の場合の戻り値
#define COMM_PLAYER_INVALID_GRID (0xffff)

/// コミュニケーションプレーヤー管理マネージャー初期化
extern BOOL CommPlayerManagerInitialize(void* work_area, FIELDSYS_WORK* pFSys,BOOL bUnder);
/// コミュニケーションプレーヤー管理マネージャー終了
extern void CommPlayerManagerFinalize(BOOL bDel);

/// 通信プレーヤーを消す
extern void CommPlayerManagerReset(void);
/// 通信プレーヤーを復帰する
extern void CommPlayerManagerReboot(void);
/// 自分をCOMM_PARENT_IDにもどす
extern void CommPlayerManagerReInit(void);
/// 緊急停止
extern void CommPlayerManagerStop(void);
// 秘密基地へ入り口を閉じていくのでプレーヤーを消す
extern void CommPlayerManagerDeletePlayers(void);

/// 自分のデータの初期化
extern void CommPlayerMyDataInitialize(void);
// 自動接続した際のデータ引継ぎ
extern void CommPlayerMyDataCopy(int netID);
// 引継ぎデータを子機に送信
extern void CommPlayerSendPosServer(BOOL bLiveMessage);


/// このクラスが初期化されたかどうかを返す
extern BOOL CommPlayerManagerIsInitialize(void);
/// 自分の位置を送信
extern void CommPlayerSendPosXZ(BOOL bLiveMessage,int xpos,int zpos);
/// 自分の位置を送信
extern void CommPlayerSendPos(BOOL bLiveMessage);
/// コミュニケーションプレーヤーワーク管理ワークサイズ
extern u32 CommPlayerGetWorkSize(void);
/// カード情報の要求コマンドを受信
extern void CommPlayerRecvReqCardInfo(int netID, void* pData);
/// カード情報の受信
extern void CommPlayerRecvCardInfo(int netID, int size, void* pData, void* pWork);
/// カード情報のサイズを返す
extern int CommPlayerGetRecvCardInfoSize(void);
/// 場所情報の受信
extern void CommPlayerRecvPlace(int netID, int size, void* pData, void* pWork);
/// プレーヤーを消す情報を受信
extern void CommPlayerRecvDelete(int netID, int size, void* pBuff, void* pWork);
/// 場所情報のサイズを返す
extern int CommPlayerGetRecvPlaceSize(void);
/// 会話を送信する
// 使う必要はないはずなので封印
//extern void CommPlayerSendTalk(int targetID, int msgSize, u16* pMsg);
/// 会話データを受信する
extern void CommPlayerRecvTalk(int netID, int size, void* pData, void* pWork);
/// 会話データを受信する（サーバー側）
extern void CommPlayerRecvTalk_ServerSide(int netID, int size, void* pData, void* pWork);
/// 停止状態解除
extern void CommPlayerRecvFreezeEnd(int netID, int size, void* pData, void* pWork);

extern void CommPlayerRecvFixedTalk(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvFixedTalk_ServerSide(int netID, int size, void* pData, void* pWork);
extern int CommPlayerRecvFixedTalkSize(void);

extern BOOL CommPlayerIsMyMoveControl(void);
extern BOOL CommPlayerGetMoveControl(int netID);
extern void CommPlayerSetMoveControl(BOOL bMoveControl);
extern void CommPlayerSetMoveControl_Server(int netID, BOOL bMoveControl);
extern void CommPlayerRecvMoveControl(int netID, int size, void* pData, void* pWork);

// トラップにかかっているかどうか
extern BOOL CommPlayerIsTrapBind(int targetID);
extern void CommPlayerSetFEExclamationAdd(int netID);
extern void CommPlayerSetFEOkAdd(int netID);
extern void CommPlayerSetFENoneAdd(int netID);
/// ネットワークプレーヤーの移動処理
extern void CommPlayersMove(FIELDSYS_WORK * repw, BOOL bMoveControl);
/// ネットワークプレーヤーの移動処理になっているかどうか
extern BOOL CommPlayerIsControl(void);
// このプレーヤーがつながっているかどうか
extern BOOL CommPlayerIsActive(int netID);

extern void CommPlayerHold_Control(void);

extern void CommPlayerBlowStart( int netID, int dir , BOOL bHit);
extern void CommPlayerBlowExit(int victimNetID);
extern void CommPlayerBlowFirst(int victimNetID);
extern void CommPlayerBlowAnimStart( int netID, int dir , BOOL bHit );
extern void CommPlayerBlowAnimStop( int netID );

extern void CommPlayerRecvIDPlace(int netID, int size, void* pBuff, void* pWork);
extern void CommPlayerClientMoveControl(int netID, int moveX, int moveZ, FIELDSYS_WORK* pFSys);
extern int CommPlayerGetRecvIDPlaceSize(void);

// 各プレーヤーの座標を取得する Sがついたらサーバー

extern int CommPlayerGetPosDigFossilX(int netID);
extern int CommPlayerGetPosDigFossilZ(int netID);
extern int CommPlayerGetPosXDirAdd(int netID);
extern int CommPlayerGetPosZDirAdd(int netID);
extern int CommPlayerGetPosXOrg(int netID);
extern int CommPlayerGetPosZOrg(int netID);
extern int CommPlayerGetPosX(int netID);
extern int CommPlayerGetPosZ(int netID);
extern int CommPlayerGetDir(int netID);
extern int CommPlayerGetPosSXDirAdd(int netID);
extern int CommPlayerGetPosSZDirAdd(int netID);
extern int CommPlayerGetPosSX(int netID);
extern int CommPlayerGetPosSZ(int netID);
extern int CommPlayerGetPosSXOrg(int netID);
extern int CommPlayerGetPosSZOrg(int netID);
extern int CommPlayerGetSDir(int netID);
extern void CommPlayerSetLook_Server(int netID, int targetID);
extern void CommPlayerSetLook(int netID, int targetID);
// 状態セット
extern void CommPlayerSetCondition(int victimNetID, int condition);
extern void CommPlayerResetCondition(int victimNetID);
// 基地に直接移動
extern void CommPlayerBaseTeleportClient(int netID, int x, int z, int dir);
extern void CommPlayerBaseTeleportServer(int netID, int x, int z, int dir);

extern void CommPlayerRecvCheckFieldMenuOpen(int netID, int size, void* pData, void* pWork);
extern int CommPlayerIsAlive(int xpos, int zpos);
extern void CommPlayerRecvResultFieldMenuOpen(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvResultUGMenuOpen(int netID, int size, void* pData, void* pWork);

extern BOOL CommPlayerCheckBattleJump(void);
extern void CommPlayerBattleDirSet(void);
extern BOOL CommPlayerMoveBattlePos(void);

extern BOOL CommPlayerDeliveryFlagData(int netID);
extern BOOL CommPlayerDeleteFlagData(int netID);
extern BOOL CommPlayerIsFlagData(int netID);
extern BOOL CommPlayerGetFlag(int myNetID, int targetNetID);
extern BOOL CommPlayerFlagTalkCheck(int netID, int targetID, BOOL bNPCTalk);
extern BOOL CommPlayerFlagDigCheck(int netID);
extern int CommPlayerRecvFlagStateServerRetGetSize(void);
extern void CommPlayerRecvFlagState(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvFlagStateServerRet(int netID, int size, void* pData, void* pWork);
// 反対の方向を返す
extern int CommPlayerGetReverseDir(int dir);
// 混乱する歩数を設定する
extern void CommPlayerSetGiddyStep(int netID,int count);
extern void CommPlayerResetGiddyStep(int netID);

extern void CommPlayerSetHole(int netID,int count);
extern void CommPlayerResetHole(int netID);

extern int CommPlayerGetWalkCount(int netID);
extern void CommPlayerSetWalkCount(void);
extern int CommPlayerGetWalkCountServer(int netID);

extern void CommPlayerRecvOtherTalk(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvOtherTalk_ServerSide(int netID, int size, void* pData, void* pWork);

extern void CommPlayerDestroy(u8 netID, BOOL bExit,BOOL bDel);

extern void CommPlayerSetDir(int dir);
extern void CommPlayerSetClientDir(int netID, int dir);
extern int CommPlayerGetClientDir(int netID);

extern BOOL CommPlayerNPCHitCheck(int x,int z);

extern void CommPlayerHold(void);
extern void CommPlayerHoldEnd(void);

extern void CommPlayerHoldBit(int bit);
extern void CommPlayerHoldBitEnd(int bit);

extern void CommPlayerSetForcePos(void);
extern void CommPlayerFirstMoveEnable(void);
extern void CommPlayerFirstMoveDisable(void);

extern void CommPlayerRecvStartLineSet(int netID, int size, void* pData, void* pWork);

// 現状のハタデータを送る
extern int CommPlayerNowFlagSize(void);
extern u8* CommPlayerGetFlagRecvBuff( int netID, void* pWork, int size);
extern void CommPlayerNowFlagSend(void);
extern void CommPlayerRecvNowFlagDataReq(int netID, int size, void* pData, void* pWork);
extern void CommPlayerRecvNowFlagDataArray(int netID, int size, void* pData, void* pWork);
extern int CommPlayerNowFlagDataArraySize(void);
extern void CommPlayerRecvNowFlagDataEnd(int netID, int size, void* pData, void* pWork);
extern BOOL CommPlayerIsNowFlagDataEnd(void);
extern void CommPlayerParentFlagDataReset(void);

extern void CommPlayerFlagChange(void);

extern void CommSetForceDir(void);

extern void CommPlayerHoldBitOff(void);

#define _HOLD_ALL (0)
#define _HOLD_FLAG_RIP_OFF (0x01)
#define _HOLD_FLAG_NO_TALK (0x02)
#define _HOLD_FLAG_STOLEN (0x04)
#define _HOLD_FLAG_STOLEN_MY (0x08)
#define _HOLD_TRAP (0x10)
#define _HOLD_FLAG_NO_DIG (0x20)
#define _HOLD_FLAG_PC_GET (0x40)
#define _HOLD_TOUCH (0x80)
#define _HOLD_FLAG_DEL (0x100)




#endif //__COMM_PLAYER_H__
