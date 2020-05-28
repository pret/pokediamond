//=============================================================================
/**
 * @file	comm_state.h
 * @brief	通信状態を管理するサービス  通信の上位にある
 *          スレッドのひとつとして働き、自分の通信状態や他の機器の
 *          開始や終了を管理する
 *          communication部分のみを再移動
 * @author	k.ohno
 * @date    2006.01.12
 */
//=============================================================================

#ifndef __COMM_STATE_H__
#define __COMM_STATE_H__

#include "savedata/savedata.h"
#include "savedata/regulation.h"


//==============================================================================
// extern宣言
//==============================================================================
#ifdef PM_DEBUG
extern void DebugOhnoCommDebugUnderNo(int no);
extern void DebugOhnoCommDebugUnderParentOnly(int no);
extern void DebugOhnoCommDebugUnderChildOnly(int no);
#endif


extern BOOL CommStateIsInitialize(void);
// 地下に入る場合の処理 ステートが地下用に変更される
extern void CommStateEnterUnderGround(SAVEDATA* pSaveData);
// 地下をでる場合の処理 ステートが何もなしに変更される
extern void CommStateExitUnderGround(void);
// 地下において接続中STATEなのかどうか返す
extern BOOL CommIsUnderGroundConnectingState(void);
// 地下においてRESETステートなのかどうか
extern BOOL CommIsUnderResetState(void);
// 地下において秘密基地に入る為に切断を行う
extern void CommStateUnderGroundOfflineSecretBase(void);
// 秘密基地から出てきたら接続処理を行う
extern void CommStateUnderGroundOnlineSecretBase(void);
// 地下のビーコン収集を再開
extern void CommStateUnderRestart(void);
// 地下のビーコン収集を再開
extern void CommStateUnderParentRestart(void);
// 地下検索停止状態にする
extern void CommStaetUnderPause(BOOL bFlg);
// かせき掘りスタート
extern void CommStateUnderGroundDigFossilStart(void);
extern void CommStateUnderGroundDigFossilEnd(void);


// バトル時に親になる場合の処理開始
#ifdef PM_DEBUG
extern void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi, int soloDebugNo);
#else
extern void CommStateEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi);
#endif
// バトル時に子になる場合の処理開始
#ifdef PM_DEBUG
extern void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi, int soloDebugNo);
#else
extern void CommStateEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, const REGULATION* pReg, BOOL bWifi);
#endif
// バトル時に親を決めた際の子機の処理
extern void CommStateConnectBattleChild(int connectIndex);
// バトル時に子機を再起動する時の処理
extern void CommStateRebootBattleChild(void);
// 終了処理手続き
extern void CommStateExitBattle(void);
// バトル接続中STATEなのかどうか返す
extern BOOL CommIsBattleConnectingState(void);

/// ユニオンルームでビーコンの収集
extern void CommStateUnionBconCollection(SAVEDATA* pSaveData);
/// ユニオン子機になる予定なので誰もつながらない
extern void CommStateChildReserve(void);
/// ユニオンルームで会話開始
extern void CommStateUnionTalkStart(void);
/// ユニオンルームで接続開始 
extern void CommStateUnionConnectStart(int index);
/// 接続したかどうか
extern int CommStateIsUnionConnectSuccess(void);
/// 親機として接続しているかどうか
extern BOOL CommStateIsUnionParentConnectSuccess(void);
/// ビーコン収集再開
extern void CommStateUnionBconCollectionRestart(void);
/// ビーコン収集再開の流れに戻ったかどうか
extern BOOL CommStateUnionIsRestartSuccess(void);
// 終了処理手続き
extern void CommStateExitUnion(void);
/// 一時停止
extern void CommStateUnionPause(void);
/// ユニオンルーム内の接続モードに戻す
extern void CommStateUnionAppEnd(void);
/// 「ユニオンルームアプリケーション」という接続モードに変える
extern void CommStateUnionAppStart(void);






extern void CommStateSetPokemon(u8* sel);
// コピー
extern void CommStateGetPokemon(u8* sel);

// 不思議通信親機の接続
extern void CommStateEnterMysteryParent(SAVEDATA* pSaveData, int serviceNo);
// 不思議通信子機の接続
extern void CommStateEnterMysteryChild(SAVEDATA* pSaveData, int serviceNo);


#ifdef PM_DEBUG
// タイトルから通信デバッグを行う時の関数
extern void CommStateDBattleConnect(BOOL bParent, int gameMode ,SAVEDATA* pSaveData);
// WIFIステート処理
extern void CommStateWifiCheckFunc(void);

// デバッグスタートをそろえる関数
extern void CommStateRecvDebugStart(int netID, int size, void* pData, void* pWork);
// 戦闘シーケンスに進んでいいかどうか
extern BOOL CommStateDBattleIsReady(void);


#endif

// お絵かき掲示板よう接続に変更
extern void CommStateUnionPictureBoardChange(void);
//お絵かきstateに移行した場合TRUE
extern BOOL CommStateIsUnionPictureBoardState(void);
// お絵かき子機として繋ぐ
extern void CommStateUnionPictureBoardChild(int index);

// レコードコーナーの状態に切り替える
extern void CommStateUnionRecordCornerChange(void);
// レコードコーナー子機として繋ぐ
extern void CommStateUnionRecordCornerChild(int index);


/// 接続確認検査
extern void CommRecvNegotiation(int netID, int size, void* pData, void* pWork);
/// 接続確認検査 親機からの返事
extern void CommRecvNegotiationReturn(int netID, int size, void* pData, void* pWork);
/// 接続確認コマンドのサイズ
extern int CommRecvGetNegotiationSize(void);

/// 入ってくる人の数を制限
extern void CommStateSetLimitNum(int num);
/// ぽけっち接続開始
extern void CommStateEnterPockchChild(SAVEDATA* pSaveData);
/// ぽけっち処理手続き
extern void CommStateExitPoketch(void);
/// ぽけっちにおいて情報収集STATEなのかどうか返す
extern BOOL CommIsPoketchSearchingState(void);

// パーティーゲーム種類
#define PARTYGAME_MYSTERY_BCON (0x01)
#define PARTYGAME_RANGER_BCON  (0x02)
#define PARTYGAME_WII_BCON     (0x04)
#define PARTYGAME_DOWNLOAD_BCON (0x08)

// * パーティーゲーム検索の通信処理開始（子機状態のみ）
extern void CommStateEnterPartyGameScanChild(SAVEDATA* pSaveData);
// パーティーゲームサーチの終了処理
extern void CommStateExitPartyGameScan(void);
// 拾ったビーコンのBITを返す
extern u8 CommStateGetPartyGameBit(void);

/// リセット用の通信切断
extern BOOL CommStateExitReset(void);

extern void CommStateCheckFunc(void);

// WIFIバトル接続用関数
#ifdef PM_DEBUG
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo);
#else
void CommStateWifiEnterBattleChild(SAVEDATA* pSaveData, int serviceNo, int regulationNo);
#endif
#ifdef PM_DEBUG
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo, int soloDebugNo);
#else
void CommStateWifiEnterBattleParent(SAVEDATA* pSaveData, int serviceNo, int regulationNo);
#endif
//

extern void CommStateSetEntryChildEnable(BOOL bEntry);

//extern void CommStateSetDisconnectFlg(BOOL bFlg);
extern void CommStateSetErrorCheck(BOOL bFlg,BOOL bAuto);
//extern void CommStateSetErrorCheck(BOOL bFlg);
extern BOOL CommStateGetErrorCheck(void);

extern BOOL CommStateGetWifiDPWError(void);


extern void* CommStateWifiEnterLogin(SAVEDATA* pSaveData, int wifiFriendStatusSize);
extern void* CommStateGetMatchWork(void);
extern BOOL CommStateIsWifiLoginState(void);
extern BOOL CommStateIsWifiLoginMatchState(void);
extern void CommStateWifiMatchEnd(void);
extern void CommStateWifiTradeMatchEnd(void);
extern void CommStateWifiBattleMatchEnd(void);
extern BOOL CommStateIsWifiDisconnect(void);

extern int CommWifiWaitingCancel( void );

extern int CommStateGetServiceNo(void);
extern int CommStateGetRegulationNo(void);
#ifdef PM_DEBUG
extern int CommStateGetSoloDebugNo(void);
#endif

extern void CommStateWifiLogout(void);
extern int CommStateGetWifiErrorNo(void);
extern BOOL CommStateIsWifiError(void);

//ゲームを開始する。// 2006.4.13 吉原追加
extern int CommWifiBattleStart( int target );

//マッチングが完了したかどうかを判定 // 2006.4.13 吉原追加
extern int CommWifiIsMatched();

// 通信がWIFI接続しているかどうかを返す
extern BOOL CommStateIsWifiConnect(void);


extern void CommStateWifiDPWStart(SAVEDATA* pSaveData);
extern void CommStateWifiDPWEnd(void);

extern void CommStateWifiFusigiStart(SAVEDATA* pSaveData);
extern void CommStateWifiFusigiEnd(void);


#define COMM_ERROR_RESET_SAVEPOINT  (1)
#define COMM_ERROR_RESET_TITLE  (2)
#define COMM_ERROR_RESET_GTS  (3)
#define COMM_ERROR_RESET_OTHER (4)


// リセットするエラーが発生した場合に呼ぶ
extern void CommSetErrorReset(u8 type);
// リセットするエラーが発生したかどうか
extern u8 CommIsResetError(void);

// fatalエラー関数
extern void CommFatalErrorFunc(int no);
extern void CommFatalErrorFunc_NoNumber( void );


// 地下はじめのイベントを行う場合設定
extern void CommStateSetFirstEvent(void);

// WIFIから切断要求
extern void CommRecvExit(int netID, int size, void* pData, void* pWork);

extern BOOL CommStateIsResetEnd(void);

extern void CommStateSetParentOnlyFlg(BOOL bFlg);


#define COMM_ERRORTYPE_ARESET (0)     // Aボタンでリセット
#define COMM_ERRORTYPE_POWEROFF (1)   // 電源を切らないといけない
#define COMM_ERRORTYPE_TITLE (2)     // Aボタンでリセット タイトル戻し
#define COMM_ERRORTYPE_GTS (3)     // Aボタンでリセット セーブポイントへ戻す

// エラー表示関数
extern void ComErrorWarningResetCall( int heapID, int type, int code );
extern void DWClibWarningCall( int heapID, int error_msg_id );


// エラーにする関数   以下の番号を使用してください
//#define COMM_ERROR_RESET_SAVEPOINT  (1)
//#define COMM_ERROR_RESET_TITLE  (2)
//#define COMM_ERROR_RESET_GTS  (3)
//#define COMM_ERROR_RESET_OTHER (4)
extern BOOL CommStateSetError(int no);


#endif //__COMM_STATE_H__

