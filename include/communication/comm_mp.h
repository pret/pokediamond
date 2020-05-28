//=============================================================================
/**
 * @file	comm_mp.h
 * @brief	通信の接続を管理しているクラス  comm_system.c から分離
 * @author	Katsumi Ohno
 * @date    2006.01.25
 */
//=============================================================================

#ifndef _COMM_MP_H_
#define _COMM_MP_H_


#include "gflib/tcb.h" //TCB_PTRのため
#include "savedata/mystatus.h" //MYSTATUSのため

//==============================================================================
// extern宣言
//==============================================================================

/// 初期化
extern void CommMPInitialize(MYSTATUS* pMyStatus);
/// 通信しているかどうか
extern BOOL CommMPIsConnect(void);

//親機の初期化をします。つなぎにくる子機を待ちます
extern BOOL CommMPParentInit(BOOL bAlloc, BOOL bTGIDChange, BOOL bEntry);
// 子機の初期化をします。同時に親機を探しに行きます
extern BOOL CommMPChildInit(BOOL bAlloc, BOOL bBconInit);
/// 通信終了処理
extern BOOL CommMPFinalize(void);
/// 通信していないがそのまま潜む処理
extern void CommMPStealth(BOOL bStalth);
// 発見した親機の数を返します
extern int CommMPGetParentCount(void);
// 親機のスキャンリストに更新があった場合TRUE
extern BOOL CommMPIsScanListChange(void);
// 親機を拾うフラグをリセット
extern void CommMPResetScanChangeFlag(void);
// 親機が現在つながっている台数を返す
extern int CommMPGetParentConnectionNum(int index);
// すぐに繋いでいい人がいたらそのindexを返します
extern int CommMPGetFastConnectIndex(void);
// 次の段階で繋いでいい人がいたらそのindexを返します
extern int CommMPGetNextConnectIndex(void);
// 親機の名前をMYSTATUSで返します。
extern void CommMPGetParentName(int index, MYSTATUS* pMyStatus);
// 親機のIDを返します
extern u32 CommMPGetPokeID(int index);
// 子機　MP状態で接続-- CC_CONNECT_STARTINGが帰ってきたら成功です
extern int CommMPChildNameAndIDConnect(STRBUF* pStrBuff, u32 pokeID);
// 子機　データシェアリング状態で接続-- TRUEが帰ってきたら成功です
extern BOOL CommMPChildIndexConnect(u16 index);
// 子機 親機のBCONのタイムアウトを監視します
extern void CommMPParentBconCheck(void);

/// 通信切り替えを行う（親子反転に必要な処理）
extern BOOL CommMPSwitchParentChild(void);
/// 通信切断モードに入ったかどうか
extern BOOL CommMPIsConnectStalth(void);
/// 子機がつながったかどうかを確認
extern BOOL CommMPIsChildsConnecting(void);
/// 親機が回線切断した場合TRUE
extern BOOL CommMPParentDisconnect(void);
/// VRAMDのイクニューモンを捨てる
extern void CommVRAMDFinalize(void);
/// VRAMDのイクニューモンを設定開始していた
extern BOOL CommIsVRAMDStart(void);
/// 通信エラーかどうか
extern BOOL CommMPIsError(void);
/// 初期化がすんでいるかどうか
extern BOOL CommMPIsInitialize(void);
/// 子機がいない事をエラーにしたい場合セットする
extern void CommMPSetNoChildError(BOOL bOn);
/// 誰かが落ちた時にエラーにしたい場合セットする
extern void CommMPSetDisconnectOtherError(BOOL bOn);

/// ビーコンデータを得る  削除予定
extern WMBssDesc* CommMPGetWMBssDesc(int index);
/// ビーコンのデータをクリアする
extern void ChildBconDataInit(void);
/// GFビーコンデータを得る
extern _GF_BSS_DATA_INFO* CommMPGetGFBss(int index);
/// ビーコンデータを消す  削除予定
extern void CommMPResetWMBssDesc(int index);
/// ビーコンデータを消す
extern void CommMPResetGFBss(int index);


///自分のBCONのPMSデータを書き換える この関数はCommMPFlashMyBssを呼ぶことで反映される
extern void CommMPSetMyPMS(PMS_DATA* pPMS);
///自分のBCONのレギュレーションデータを書き換える この関数はCommMPFlashMyBssを呼ぶことで反映される
extern void CommMPSetMyRegulation(void* pRegulation);
///ビーコンデータに現在の状況を反映させる
extern void CommMPFlashMyBss(void);

/// MYSTATUSを得る
extern MYSTATUS* CommMPGetMyStatus(void);
/// BCON内に含まれるMYSTATUSを返す
extern MYSTATUS* CommMPGetBconMyStatus(int index);

/// 自動切断モードに入ったかどうかを返す
extern BOOL CommMPIsAutoExit(void);
/// 自動切断モードON
extern void CommMPSetAutoExit(void);
/// WM通信がアイドル状態にあるかどうか
extern BOOL CommMPIsStateIdle(void);

extern void CommMPSetBackupMacAddress(u8* pMac, int netID);
/// サービス番号を取得する
extern int CommMPGetServiceNo(void);
/// ライフタイムを小さくする または元に戻す
extern void CommMPSetLifeTime(BOOL bMinimum);

/// 任意のサービスの利用者数を返します
extern int CommMPGetServiceNumber(int serviceNo);
// プロセス処理
extern void CommMpProcess(u16 bitmap);
// ビーコンを送ったかどうか検査
extern BOOL CommMPIsParentBeaconSent(void);

extern BOOL CommMPIsChildStateScan(void);

//   ビーコンデータに自由にデータを載せます
extern void CommMPSetBeaconTempData(void* pData);
//   ビーコンデータからデータを引き出します
extern const void* CommMPGetBeaconTempData(int index);

// 関連ゲームのビーコン収集
extern BOOL CommMPPartyGameScanChildInit(void);

// 接続しようとしているチャンネル、接続したチャンネルを得る
extern int CommMPGetChannel(void);

extern void * CommMPGetMyGFBss(void);
extern int CommMPGetBConUncacheTime(int index);

extern int CommBmpListPosBconIndexGet(int index);

#endif // _COMM_MP_H_

