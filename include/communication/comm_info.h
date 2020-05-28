//=============================================================================
/**
 * @file	comm_info.h
 * @brief	通信で得た情報を蓄えておくクラス
 * @author	Katsumi Ohno
 * @date    2005.08.22
 */
//=============================================================================

#ifndef __COMM_INFO_H__
#define __COMM_INFO_H__

#include "savedata/mystatus.h"
#include "savedata/regulation.h"
#include "wifi/dwc_rap.h"

/// 初期化
extern void CommInfoInitialize(SAVEDATA* pSaveData, const REGULATION* pReg);
/// 開放
extern void CommInfoFinalize(void);
/// ワークサイズを得る
extern int CommInfoGetWorkSize(void);
/// 初期化がすんでいるかどうか返す
extern BOOL CommInfoIsInitialize(void);
/// ポケモンデータの送信
extern void CommInfoSendPokeData(void);
/// プレーヤーデータのサイズを得る
extern int CommInfoGetPlayerDataSize(void);
/// プレーヤーデータの受信が終了した
extern void CommInfoRecvEnd(int netID, int size, void* pData, void* pWork);
/// プレーヤー情報を集め終わった
extern BOOL CommInfoIsInfoCollected(void);
/// MyStatusデータを受信する
extern void CommInfoRecvMyStatusData( int netID, int size, void* pData, void* pWork);
/// MyStatusArrayデータを受信する
extern void CommInfoRecvMyStatusArrayData( int netID, int size, void* pData, void* pWork);

/// プレーヤーデータを受信する
extern void CommInfoRecvArrayPlayerData( int netID, int size, void* pData, void* pWork);
/// プレーヤーデータを受信する
extern void CommInfoRecvPlayerData(int netID, int size, void* pData, void* pWork);

extern BOOL CommInfoSendArray_ServerSide(void);
extern BOOL CommInfoIsNewInfoData(void);


/// 名前データを得る
extern BOOL CommInfoGetName(int index, u16* name);
extern BOOL CommInfoIsBattleNewName(int netID);
/// IDを文字列で得る
extern BOOL CommInfoGetIDString(int index, u16* idStr);
/// IDのパケットサイズを返す
extern int CommInfoGetRecvPokeIDSize();
///   情報を消す
extern void CommInfoDeletePlayer(int netID);
///  新着データかどうかを得る
extern BOOL CommInfoIsNewName(int netID);
///  遊ぶ仲間として認証する
extern void CommInfoSetEntry(int netID);
/// 新しく登録されたことを外部に伝えた
extern void CommInfoSetMessageEnd(int netID);
/// 新しい名前が入っている番号を返す
extern int CommInfoGetNewNameID(void);
/// 正式にエントリーした人数を帰す
extern int CommInfoGetEntryNum(void);

extern void CommInfoFunc(void);
// 地下に入ってきた状況メッセージを返す
extern BOOL CommInfoGetActionMessage(u16* message);
// myStatusを返す
extern MYSTATUS* CommInfoGetMyStatus(int netID);
// DWCフレンドデータを返す
extern DWCFriendData* CommInfoGetDWCFriendCode(int netID);
// グループ名を返す
extern STRCODE* CommInfoGetGroupName(int netID);
/// myNationを返す
extern int CommInfoGetMyNation(int netID);
/// myAreaを返す
extern int CommInfoGetMyArea(int netID);
/// myPenaltyを返す
extern int CommInfoGetMyPenalty(int netID);
// レギュレーションを返す
extern const REGULATION* CommInfoGetRegulation(int netID);
// 接続している人のレギュレーションが同じかどうか検査する
extern BOOL CommInfoRegulationCheck(void);

// 通信たいせん＆こうかん結果を一時記録
extern void CommInfoWriteResult(SAVEDATA* pSaveData);
extern void CommInfoSetBattleResult(SAVEDATA* pSaveData, int bWin );
extern void CommInfoSetTradeResult(SAVEDATA* pSaveData, int num);


#define INVALID_NETID (0xff) ///< 無効なNetID

#endif  // __COMM_INFO_H__
