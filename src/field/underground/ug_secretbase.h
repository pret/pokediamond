//=============================================================================
/**
 * @file	comm_secretbase_info.h
 * @brief	地下の秘密基地情報を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.10.04
 */
//=============================================================================

#ifndef __UG_SECRETBASE_H__
#define __UG_SECRETBASE_H__

#include "savedata/undergrounddata.h"

/// 秘密基地情報初期化
extern void CommSecretBaseInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys);
extern void CommSecretBaseInfoReset(void);
extern void CommSecretBaseInfoReboot(void);
/// 秘密基地情報処理終了
extern void CommSecretBaseInfoFinalize(void);
extern void CommSecretBaseInfoReInit(void);
extern void CommSecretBaseInfoParentDel(void);
/// ワーク全体のサイズを返す
extern int CommSecretBaseInfoGetWorkSize(void);
/// セーブデータから自分のあたりを作成
extern void UgSecretBaseMakeMyAttr(FIELDSYS_WORK* pFSys);
/// 子機側のプログラム  親機に秘密基地を送る
extern void CommSecretBaseInfoChildSendStart(void);
/// 秘密基地データ受信
extern void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork);
/// 秘密基地データサイズ
extern int CommSecretBaseInfoGetDataSize(void);
/// 親機から秘密基地データが届いたかどうか
extern BOOL CommSecretBaseInfoIsChildRecv(void);
/// 親機から秘密基地データが届いたので、フラグを消す
extern void CommSecretBaseResetChildRecv(void);

extern BOOL CommSecretBaseInfoIsPosRecv(void);

extern void CommSecretBaseResetPosRecv(void);

extern BOOL CommSecretBaseIsTraveling(int netID);

/// 秘密基地移動が終了したことを送信
extern void CommSecretBaseInfoJumpEnd(void);
/// 秘密基地移動が終了したことを受信
extern void CommSecretBaseInfoRecvJumpEnd(int netID, int size, void* pData, void* pWork);

extern void UgSecretBaseRecvJumpEvent(int netID, int size, void* pData, void* pWork);

extern void UgSecretBaseRecvMoveFailed(int netID, int size, void* pData, void* pWork);

extern int UgSecretBaseRecvJumpEventSize(void);

extern void UgSecretBaseRecvJumpEventRes(int netID, int size, void* pData, void* pWork);

extern int UgSecretBaseRecvJumpEventResSize(void);

extern void CommSecretBaseInfoParentSendStart(int netID);

extern void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseInfoRecvDataServer(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseInfoRecvPos(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseInfoGetDataSize(void);
extern int CommSecretBaseInfoGetPosSize(void);

extern void CommSecretBaseInfoStepFunc(void);
extern BOOL CommSecretBaseSingleStepFunc(int playerId, int moveX, int moveZ);

extern BOOL CommSecretBaseInfoGetActionMessage(STRBUF* pStrBuf);

extern void CommSecretBaseInfoRecvRetJump(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseInfoGetRetJumpSize(void);

extern void CommSecretBaseDrillStart(void);
extern void CommSecretBaseRecvDrillStart(int netID, int size, void* pData, void* pWork);
extern void CommSecretBaseRecvDrillStartResult(int netID, int size, void* pData, void* pWork);
extern int CommSecretBaseDrillStartResultSize(void);

/// 通信離脱した人の秘密基地を消す
extern void UgSecretBaseResetPlayer(int netID);
extern void UgSecretBaseDestroyPlayer(int netID);
extern void UgSecretBaseDestroyDoor(int netID);
extern void UgSecretBaseDestroyPlayerDontBaseIn(int netID);
/// 秘密基地の内容物を返す
extern SECRETBASEDATA* UgSetupSecretBaseData(SAVEDATA * sv);
///今からセットアップする秘密基地のブロックを返す
extern int UgSetupSecretBaseBlockX(void);
extern int UgSetupSecretBaseBlockZ(void);
/// 秘密基地グッズあたりデータをみて歩けるかどうかしらべる
extern BOOL UgSecretBaseMoveing(int x, int z);
/// もようがえの会話スタート
extern int UgSecretBaseTalkStart(int messageNo);
/// もようがえの会話終わり
extern void UgSecretBaseTalkEnd(void);
/// グッズの名前をメッセージに表示させる場合の関数
extern void UgSecretBaseTalkRegisterGoodsName(int type);
/// 数字２桁をメッセージに表示させる場合の関数
extern void UgSecretBaseTalkRegisterNum2(int number,int index);
/// Aボタンでグッズのチェックがあった
extern BOOL UgSecretBaseGoodsCheck(int netID, Grid* pTouch);
/// Aボタンでグッズのチェックがあった
extern void UgSecretBaseRecvGoodsCheck(int netID, int size, void* pData, void* pWork);
extern int UgSecretBaseGetRecvGoodsCheckSize(void);

extern void UgSecretBaseSetFlagGetLog(int netID, int targetPCNetID);
extern void UgSecretBaseSetFlagReverseLog(int myNetID);
extern void UgSecretBaseSetFlagConquerLog(int myNetID, int targetID);


extern int UgSBGetLVUPFlagRetSize(void);
extern void UgSBRecvLVUPFlagRet(int netID, int size, void* pData, void* pWork);
extern void UgSBRecvLVUPFlag(int netID, int size, void* pData, void* pWork);

// 検査
extern BOOL UgSecretBaseTrapGoodsCheck(int netID);
// リセット
extern BOOL UgSecretBaseTrapGoodsReset(int netID);

extern void UgSecretBaseRemovePlayer(int netID);
//
extern BOOL UgSecretBaseRemovePlayer_Client(int playerID, BOOL bRemove);

extern BOOL UgSecretBaseIsOtherEnter(void);

extern void UgSecretBaseErrorMoveTickets(void);
extern void UgSecretBaseErrorDisconnectTickets(void);
// 子機が秘密基地にいた場合、いったん外にでてもらう
extern void UgSecretBaseFirstConnectChild(int netID);




extern int UgSecretBaseEscapePosX(void);
extern int UgSecretBaseEscapePosZ(void);
extern int UgSecretBaseEscapeDir(void);
extern void UgSecretBaseEscapePosSXSet(int netID,int x);
extern void UgSecretBaseEscapePosSZSet(int netID,int z);
extern void UgSecretBaseEscapeDirSet(int netID,int dir);

extern void UgSecretBaseBootOn(BOOL bOn);


#endif //__UG_SECRETBASE_H__
