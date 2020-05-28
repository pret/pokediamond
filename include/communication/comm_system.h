//=============================================================================
/**
 * @file	comm_system.h
 * @brief	通信システム
 * @author	Katsumi Ohno
 * @date    2005.07.08
 */
//=============================================================================

#ifndef _COMM_SYSTEM_H_
#define _COMM_SYSTEM_H_


#include "gflib/tcb.h" //TCB_PTRのため
#include "savedata/mystatus.h"

//==============================================================================
// extern宣言
//==============================================================================

// 必要なワークサイズを返します Allocして渡してください
extern u32 CommGetWorkSize(void);
//親機の初期化をします。つなぎにくる子機を待ちます
extern BOOL CommParentModeInit(BOOL bAlloc, BOOL bTGIDChange, int packetSizeMax, BOOL bEntry);
// 子機の初期化をします。同時に親機を探しに行きます
extern BOOL CommChildModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax);
// パーティーゲームを探す子機の初期化
extern BOOL CommChildPartyScanModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax);


/// こまんどバッファをクリアする
extern void CommSystemReset(void);
extern void CommSystemResetDS(void);
/// リセットする
extern void CommSystemResetBattleChild(void);

extern void CommStopSendMoveData(BOOL bStop);

/// 通信終了処理
extern void CommFinalize(void);
// 発見した親機の数を返します
extern int CommGetParentCount(void);
// 親機が現在つながっている台数を返す
extern int CommGetParentConnectionNum(int index);
// 親機のスキャンリストに更新があった場合TRUE
extern BOOL CommIsScanListChange(void);
// 子機　データシェアリング状態で接続-- CC_CONNECT_STARTINGが帰ってきたら成功です
extern int CommChildNameAndIDConnect(STRBUF* pStrBuff, u32 pokeID);
// 子機　データシェアリング状態で接続-- TRUEが帰ってきたら成功です
extern BOOL CommChildIndexConnect(u16 index);
// 子機 親機のBCONのタイムアウトを監視します
extern void CommParentBconCheck(void);
// 送信受信の処理を行います。VBlankに入ってすぐ呼びましょう
extern BOOL CommUpdateData(void);
// 受信コールバック子機用
extern void CommRecvCallback(u16 aid, u16 *data, u16 size);
/// 受信コールバック親機用
extern void CommRecvParentCallback(u16 aid, u16 *data, u16 size);

// 内部状態によって通信に必要な処理をする
extern void CommStateProcess(TCB_PTR tcb, void* work);
// 通信中かどうかを返す
extern BOOL CommIsConnect(u16 netID);
// 送信バッファの残量を調べます
extern int CommGetSendRestSize(void);
// アクションが行われたことを設定します
extern void CommActionCommandSet(void);
// サーバ側の送信バッファの残量を調べます
extern int CommGetSendRestSize_ServerSide(void);
// 受信データに目的のコマンドがあるかどうか検査する
extern BOOL CommGetRecvData_ServerSide(int netID,int chkCommand, int* retSize, u8* data);
// 接続人数を調べます
extern int CommGetConnectNum(void);
/// 初期化しているかどうかを調べます
extern BOOL CommIsInitialize(void);
/// 通信切り替えを行う（親子反転に必要な処理）
extern BOOL CommSwitchParentChild(void);

/// パッドコントロールを返す
extern u16 CommGetPadCont(int netID);

/// 移動速度を入れる
extern void CommSetSpeed(u8 speed);
/// 移動速度を返す
extern u8 CommGetSpeed(int netID);

// 親機を拾うフラグをリセット
extern void CommResetScanChangeFlag(void);
// 移動データを送信することを許可する
extern void CommEnableSendMoveData(void);
// 移動データを送信することを禁止する
extern void CommDisableSendMoveData(void);
// 移動データを送信することを許可しているかどうかを得る
extern BOOL CommIsSendMoveData(void);


// データを送る
extern BOOL CommSendData(int command, const void* data, int size);
// 大容量データを送る
extern BOOL CommSendHugeData(int command, const void* data, int size);
// 大容量でサイズ固定のデータを送る
extern BOOL CommSendFixHugeSizeData(int command, const void* data);
/// サイズが固定のデータを送る
extern BOOL CommSendFixSizeData(int command, const void* data);
/// コマンドのみのデータを送る
extern BOOL CommSendFixData(int command);
/// サーバ側のデータを全子機に送る
extern BOOL CommSendData_ServerSide(int command, const void* data, int size);
// サーバー側へ固定サイズのデータを送る
extern BOOL CommSendFixSizeData_ServerSide(int command, const void* data);
// サーバーから大容量データを送る
extern BOOL CommSendHugeData_ServerSide(int command, const void* data, int size);
// サーバーからサイズ固定の大容量データを送る
extern BOOL CommSendFixHugeSizeData_ServerSide(int command, const void* data);

// キューに送る予定のデータをためる
extern BOOL CommSetSendQueue_ServerSide(int command, const void* data, int size);
// キューに送る予定のデータをためる
extern BOOL CommSetSendQueue(int command, const void* data, int size);

/// ランダムにキーを発生させる
extern void CommSetKeyRandMode(void);
extern void CommSetKeyReverseMode(void);
extern void CommResetKeyRandMode(void);

/// DSモードMPモードの切り替え
extern void CommSetTransmissonTypeDS(void);
extern void CommSetTransmissonTypeMP(void);
extern int CommGetTransmissonType(void);
// 通信モード切替のコールバック
extern void CommRecvDSMPChange(int netID, int size, void* pData, void* pWork);
extern void CommRecvDSMPChangeReq(int netID, int size, void* pData, void* pWork);
extern void CommRecvDSMPChangeEnd(int netID, int size, void* pData, void* pWork);
// 自分の機のnetIDを返す
extern u16 CommGetCurrentID(void);

/// データが受信バッファにあるかどうか確認する
extern BOOL CommRecvData(int netID,int chkCommand, int* retSize, u8* data);
/// WHライブラリで　状態がIDLEになっているか確認する
extern BOOL CommIsWHStateIdle(void);
/// 子機がつながったかどうかを確認
extern BOOL CommIsChildsConnecting(void);
/// 親機が回線切断した場合TRUE
extern BOOL CommParentDisconnect(void);
/// VRAMDにイクニューモンを入れる
extern void CommVRAMDInitialize(void);
/// VRAMDのイクニューモンが入るのを待つ
extern BOOL CommIsVRAMDInitialize(void);
/// エラーが起こるとTRUEを返す
extern BOOL CommIsError(void);
/// 子機がいない事をエラーにしたい場合セットする
extern void CommSetNoChildError(BOOL bOn);
/// サービスに対応した送信バイト数を得る
extern u16 CommGetServiceMaxChildSendByte(u16 serviceNo);
/// 最大接続人数を得る
extern int CommGetMaxEntry(int service);
/// 最小接続人数を得る
extern int CommGetMinEntry(int service);

/// DS用受信データ解析イテレーター 初期化
extern void CommRecvDSIteratorInitialize(int netID);
/// DS用受信データ解析イテレーター データがあるかどうか
extern BOOL CommRecvDSIteratorHasNext(int netID);
/// DS用受信データ解析イテレーター データを取り出し次に進む
extern BOOL CommRecvDSIteratorNext(int netID,int *pCommand, int* pSize, u8* pData);
/// ビーコンデータを得る
extern WMBssDesc* CommGetWMBssDesc(int index);
/// ビーコンデータを消す
extern void CommResetWMBssDesc(int index);
/// MYSTATUSを得る
extern MYSTATUS* CommGetMyStatus(void);
/// BCON内に含まれるMYSTATUSを返す
extern MYSTATUS* CommGetBconMyStatus(int index);
/// 自動切断モードに入ったかどうかを返す
extern BOOL CommIsAutoExit(void);
/// 自動切断モードON
extern void CommSetAutoExit(void);

/// 一人で通信するモードの設定
extern void CommSetAloneMode(BOOL bAlone);
/// 一人で通信するモードかどうかの取得
extern BOOL CommGetAloneMode(void);

extern void CommSetBackupMacAddress(u8* pMac, int netID);
/// サービス番号を取得する
extern int CommGetServiceNo(void);

/// 乱数の種を初期化
extern void CommRandSeedInitialize(MATHRandContext32* pRand);

/// コマンドが送信されたかどうか確認
extern BOOL CommIsSendCommand_ServerSize(int command);
extern BOOL CommIsSendCommand(int command);


/// キューが空っぽかどうか
BOOL CommIsEmptyQueue_ServerSize(void);
/// キューが空っぽかどうか
BOOL CommIsEmptyQueue(void);
// DSモードかどうか
BOOL CommIsTransmissonDSType(void);


// 戦闘に入る前の敵味方の立ち位置を設定
extern void CommSetStandNo(int no, int netID);
// 戦闘に入る前の敵味方の立ち位置を得る
extern int CommGetStandNo(int netID);
//
extern void CommSetWifiBothNet(BOOL bFlg);


#ifdef PM_DEBUG
extern void CommSwitchAutoMove_Debug(void);
#endif

extern void CommSetWifiConnect(BOOL bConnect);

extern BOOL CommIsVChat(void);

extern BOOL CommSysIsMoveKey(void);

extern void CommSetError(void);

extern void CommSystemShutdown(void);

// 
extern BOOL CommLocalIsUnionGroup(int serviceNo);

// キューを消す
extern void CommSystemResetQueue_Server(void);

extern void CommSystemRecvStop(BOOL bFlg);

#endif // _COMM_SYSTEM_H_

