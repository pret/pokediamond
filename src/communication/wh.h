/*
  Project:  NitroSDK - wireless_shared - demos - wh
  File:     wh.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  Revision 1.19  2005/04/26 02:35:02  terui
  Fix comment

  Revision 1.18  2005/03/25 03:05:28  seiki_masashi
  WEPKey 設定関数を設定する WH_Set{Parent,Child}WEPKeyGenerator を追加

  Revision 1.17  2005/03/04 09:18:56  takano_makoto
  WH_SetUserGameInfoを追加

  Revision 1.16  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.15  2004/12/22 02:49:08  terui
  ピクトチャットサーチに対応

  Revision 1.14  2004/12/20 08:31:27  takano_makoto
  WH_Initializeを使用して初期化処理を短縮するように変更。

  Revision 1.13  2004/12/20 07:17:20  takano_makoto
  WHReceiverをWHReceiverFuncに変更、内部でOS_Allocを使用するのを排除、アプリ毎に設定するパラメータをwh_config.hとして分離

  Revision 1.12  2004/11/16 03:01:11  takano_makoto
  WH_GetCurrentAid関数を追加

  Revision 1.11  2004/11/08 02:46:17  takano_makoto
  WM_EndScanの多重呼び防止

  Revision 1.10  2004/11/05 04:27:40  sasakis
  ロビー画面、親機選択画面の追加と、それに必要な改造（scan関連など）。

  Revision 1.9  2004/11/02 19:36:19  takano_makoto
  WH_StartMeasureChannel, WH_EndScanの返り値をBOOLに変更

  Revision 1.8  2004/11/01 09:38:14  seiki_masashi
  WH_DS_DATA_SIZE を 14 から 12 に変更
  コメントの修正

  Revision 1.7  2004/11/01 09:16:47  takano_makoto
  WH関数の返り値の型変更、WH_SYSSTATE_FATAL状態を追加

  Revision 1.6  2004/10/29 02:16:34  takano_makoto
  WH_StartScanの引数変更

  Revision 1.4  2004/10/28 07:11:20  takano_makoto
  WH_Connectの関数名を変更

  Revision 1.3  2004/10/27 02:31:31  takano_makoto
  複数あったMeasureChannel系関数の統合
  WM_ERRCODE_OPERATINGで待つべき部分をWM_ERRCODE_SUCCESSで判定していた不具合修正
  その他不具合の修正

  Revision 1.2  2004/10/25 02:29:54  seiki_masashi
  親子最大送信サイズに WH_CHILD_MAX を反映
  親子最大送信サイズを WH_{PARENT,CHILD}_MAX_SIZE に統一
  コメントの訂正

  Revision 1.1  2004/10/21 00:41:50  yosizaki
  Initial upload.

 */

/*
  Log : (from multiboot-model)
  Revision 1.6  2004/09/30 08:28:14  yosizaki
  add SDK_MAKEGGID_SYSTEM macro.

  Revision 1.5  2004/09/30 03:58:40  takano_makoto
  WH_SYSSTATE_CONNECT_FAILを追加

  Revision 1.4  2004/09/27 08:34:38  takano_makoto
  WH_ChildConnect, WH_Initializeのインターフェイス変更

  Revision 1.3  2004/09/17 14:12:45  takano_makoto
  接続子機の判定ルーチンを追加.

  Revision 1.2  2004/09/17 10:29:47  takano_makoto
  WH_PARENT_MAX_SIZE, WH_CHILD_MAX_SIZEを定義

  Revision 1.1  2004/09/16 14:07:11  takano_makoto
  Initial Update
*/

/*
  Revision 1.15  2004/10/06 05:11:35  sasakis
  グラフ表示の追加など。

  Revision 1.14  2004/10/05 09:21:57  seiki_masashi
  WH_SendData に callback を指定するよう変更
  定数の文字列変換関数にエラーチェックを追加

  Revision 1.13  2004/10/01 01:58:54  seiki_masashi
  通常の MP 通信関係の関数を戻しました

  Revision 1.12  2004/09/30 08:46:48  seiki_masashi
  GGID に割り振られた正式な値を設定

  Revision 1.11  2004/09/30 06:26:49  seiki_masashi
  一時的に通常の MP 通信関係の関数を削除

  Revision 1.10  2004/09/30 06:20:03  seiki_masashi
  インデントを変更

  Revision 1.9  2004/09/30 06:16:38  seiki_masashi
  最新の SDK の仕様に準拠するよう変更

  Revision 1.8  2004/09/24 09:43:35  sasakis
  細かいバグフィックスをいくつか。

  Revision 1.7  2004/09/24 06:12:35  sasakis
  チャンネル手動選択機能を追加。

  Revision 1.6  2004/09/22 09:39:33  sasakis
  デバグ画面を追加。

  Revision 1.5  2004/09/15 10:23:40  sasakis
  電波受信強度アイコンの追加と、データサイズ可変化のための改造など。

  Revision 1.4  2004/09/10 08:44:52  sasakis
  ガイドライン準拠処理の追加、エラー関係の見直しなど。

  Revision 1.3  2004/09/08 08:55:35  sasakis
  切断処理を少々強化した。

  Revision 1.2  2004/09/08 01:52:52  sasakis
  エラー・切断関係改良。

  Revision 1.1  2004/09/07 04:59:42  sasakis
  初版登録。
*/


#ifndef __WMHIGH_H__
#define __WMHIGH_H__

#include "wh_config.h"

// 使用する GGID
#define _DP_GGID       (0x333)   // メインのGGID
#define _MYSTERY_GGID  (0x333)
#define	_RANGER_GGID   (0x00000178)
#define	_WII_GGID      (0x346)   //
#define _BCON_DOWNLOAD_GGID (0x345)


// WM_Initializeを使用して初期化する場合はOFF
// WM_Init, WM_Enable, WM_PowerOnを個別に使用して細かく制御する必要がある場合にはONに設定する。
// #define WH_USE_DETAILED_INITIALIZE

enum
{
    WH_SYSSTATE_STOP,                  // 初期状態
    WH_SYSSTATE_IDLE,                  // 待機中
    WH_SYSSTATE_SCANNING,              // スキャン中
    WH_SYSSTATE_BUSY,                  // 接続作業中
    WH_SYSSTATE_CONNECTED,             // 接続完了（この状態で通信可能）
    WH_SYSSTATE_DATASHARING,           // data-sharing有効で接続完了
    WH_SYSSTATE_KEYSHARING,            // key-sharing有効で接続完了
    WH_SYSSTATE_MEASURECHANNEL,        // チャンネルの電波使用率をチェック
    WH_SYSSTATE_CONNECT_FAIL,          // 親機への接続失敗
    WH_SYSSTATE_ERROR,                 // エラー発生
    WH_SYSSTATE_FATAL,                 // FATALエラー発生
    WH_SYSSTATE_NUM
};

enum
{
    WH_CONNECTMODE_MP_PARENT,          // 親機 MP 接続モード
    WH_CONNECTMODE_MP_CHILD,           // 子機 MP 接続モード
    WH_CONNECTMODE_KS_PARENT,          // 親機 key-sharing 接続モード
    WH_CONNECTMODE_KS_CHILD,           // 子機 key-sharing 接続モード
    WH_CONNECTMODE_DS_PARENT,          // 親機 data-sharing 接続モード
    WH_CONNECTMODE_DS_CHILD,           // 子機 data-sharing 接続モード
    WH_CONNECTMODE_NUM
};

enum
{
    // 自前のエラーコード
    WH_ERRCODE_DISCONNECTED = WM_ERRCODE_MAX,   // 親から切断された
    WH_ERRCODE_PARENT_NOT_FOUND,       // 親がいない
    WH_ERRCODE_NO_RADIO,               // 無線使用不可
    WH_ERRCODE_LOST_PARENT,            // 親を見失った
    WH_ERRCODE_NOMORE_CHANNEL,         // すべてのチャンネルの調査を終えた
    WH_ERRCODE_FATAL,
    WH_ERRCODE_MAX
};

typedef void (*WHStartScanCallbackFunc) (WMBssDesc *bssDesc);

/* 未接続, または親機しかいない状態を示すビットマップ値 */
#define WH_BITMAP_EMPTY           1

// 送信コールバック型 (for data-sharing model)
typedef void (*WHSendCallbackFunc) (BOOL result);

// 接続許可判定関数型 (for multiboot model)
typedef BOOL (*WHJudgeAcceptFunc) (WMStartParentCallback *);

// ggidスキャンコールバック
typedef void (*fGGIDCallBack) (u32 ggid, int serviceNo);

// 受信コールバック型
typedef void (*WHReceiverFunc) (u16 aid, u16 *data, u16 size);

// WEP Key 生成関数
typedef u16 (*WHParentWEPKeyGeneratorFunc) (u16* wepkey, const WMParentParam* parentParam);
typedef u16 (*WHChildWEPKeyGeneratorFunc) (u16* wepkey, const WMBssDesc* bssDesc);


typedef void (*WHdisconnectCallBack) (int aid);

extern void HWSetDisconnectCallBack(WHdisconnectCallBack callBack);

/**************************************************************************
 * 以下は、WH の各種設定値を変更する関数です。
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         WH_SetGgid

  Description:  ゲームグループIDを設定します。
                親機の接続前に呼び出します。

  Arguments:    ggid    設定するゲームグループID.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetGgid(u32 ggid);

/*---------------------------------------------------------------------------*
  Name:         WH_SetUserGameInfo

  Description:  ユーザ定義の親機情報を設定します。
                親機の接続前に呼び出します。

  Arguments:    userGameInfo  ユーザ定義の親機情報へのポインタ
                length        ユーザ定義の親機情報のサイズ

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetUserGameInfo( u16* userGameInfo, u16 length );

/*---------------------------------------------------------------------------*
  Name:         WH_SetDebugOutput

  Description:  デバッグ文字列出力用の関数を設定します。

  Arguments:    func    設定するデバッグ文字列出力用の関数.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WH_SetDebugOutput(void (*func) (const char *, ...));

/*---------------------------------------------------------------------------*
  Name:         WH_SetParentWEPKeyGenerator

  Description:  WEP Key を生成する関数を設定します。
                この関数を呼び出すと、接続時の認証に WEP が使われます。
                ゲームアプリケーションごとのアルゴリズムで
                接続前に親子で同一の値を設定します。
                この関数は親機用です。

  Arguments:    func    WEP Key を生成する関数へのポインタ
                        NULL を指定すると WEP Key を使用しない

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetParentWEPKeyGenerator(WHParentWEPKeyGeneratorFunc func);

/*---------------------------------------------------------------------------*
  Name:         WH_SetChildWEPKeyGenerator

  Description:  WEP Key を生成する関数を設定します。
                この関数を呼び出すと、接続時の認証に WEP が使われます。
                ゲームアプリケーションごとのアルゴリズムで
                接続前に親子で同一の値を設定します。
                この関数は子機用です。

  Arguments:    func    WEP Key を生成する関数へのポインタ
                        NULL を指定すると WEP Key を使用しない

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetChildWEPKeyGenerator(WHChildWEPKeyGeneratorFunc func);


/**************************************************************************
 * 以下は、低レイヤ WM ライブラリの状態を取得するラッパー関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
  Name:        WH_GetLinkLevel
  Description: 電波の受信強度を取得します。
  Arguments:   none.
  Returns:     WMLinkLevel の数値を返します。
  ---------------------------------------------------------------------- */
extern int WH_GetLinkLevel(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetAllowedChannel
   Description: 接続に使用出来るチャンネルのビットパターンを取得します。
   Arguments:   none.
   Returns:     channel pattern
   ---------------------------------------------------------------------- */
extern u16 WH_GetAllowedChannel(void);


/**************************************************************************
 * 以下は、WH の状態を取得する関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_GetBitmap
   Description: 接続状態を示すビットパターンを取得します。
   Arguments:   none.
   Returns:     bitmap pattern
   ---------------------------------------------------------------------- */
extern u16 WH_GetBitmap(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetSystemState
   Description: WH の内部状態を取得します。
   Arguments:   none.
   Returns:     内部状態（WH_SYSSTATE_XXXX）。
   ---------------------------------------------------------------------- */
extern int WH_GetSystemState(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetConnectMode
   Description: 接続情報を取得します。
   Arguments:   none.
   Returns:     接続情報（WH_CONNECTMODE_XX_XXXX）。
   ---------------------------------------------------------------------- */
extern int WH_GetConnectMode(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetLastError
   Description: 最も最近に起きたエラーのコードを取得します。
   Arguments:   none.
   Returns:     エラーコード。
   ---------------------------------------------------------------------- */
extern int WH_GetLastError(void);

/*---------------------------------------------------------------------------*
  Name:         WH_PrintBssDesc

  Description:  WMBssDesc 構造体のメンバをデバッグ出力する。

  Arguments:    info    デバッグ出力したいBssDescへのポインタ.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_PrintBssDesc(WMBssDesc *info);


/**************************************************************************
 * 以下は、チャンネルに関する処理を行う関数です。
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         WH_StartMeasureChannel

  Description:  使用可能な全チャンネルで電波使用率の調査を開始します。
                調査が完了すると、使用率が最低のチャンネルを内部で計算し
                状態を WH_SYSSTATE_MEASURECHANNEL に移行します。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_StartMeasureChannel(void);

/*---------------------------------------------------------------------------*
  Name:         WH_GetMeasureChannel

  Description:  利用可能な中から一番使用率の低いチャンネルを返します。
                WH_MeasureChannelの動作が完了しWH_SYSSTATE_MEASURECHANNEL状態
                になっている必要があります。
                この関数がコールされると一番使用率の低いチャンネルを返し
                WH_SYSSTATE_IDLE状態に遷移します。
                
  Arguments:    None.

  Returns:      もっとも使用率の低い利用可能なチャンネル番号.
 *---------------------------------------------------------------------------*/
extern u16 WH_GetMeasureChannel(void);


/**************************************************************************
 * 以下は、無線を初期化して通信可能状態まで遷移する関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_Initialize
   Description: 初期化作業を行い、初期化シーケンスを開始します。
   Arguments:   None.
   Returns:     シーケンス開始に成功すれば真。
   ---------------------------------------------------------------------- */
extern BOOL WH_Initialize(void* pHeap);
/* ----------------------------------------------------------------------
   ヒープ領域サイズを返す
   ---------------------------------------------------------------------- */
extern int WH_GetHeapSize(void);

/*---------------------------------------------------------------------------*
  Name:         WH_TurnOnPictoCatch

  Description:  ピクトチャットサーチ機能を有効にする。
                WH_StartScanにてスキャン中に、ピクトチャットを発見した場合にも
                コールバック関数が呼ばれるようになる。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_TurnOnPictoCatch(void);

/*---------------------------------------------------------------------------*
  Name:         WH_TurnOffPictoCatch

  Description:  ピクトチャットサーチ機能を無効にする。
                WH_StartScanにてスキャン中に、ピクトチャットを発見した場合でも
                無視されるようになる。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_TurnOffPictoCatch(void);

/*---------------------------------------------------------------------------*
  Name:         WH_StartScan

  Description:  親機のビーコンを取得する関数

  Arguments:    callback - 親機発見時に返すコールバックを設定する。
                
                macAddr  - 接続する親機のMACアドレスを指定
                           0xFFFFFFならばすべての親機を検索する。
                           
                channel  - 親を検索するチャンネルを指定
                           0ならばすべてのチャンネルを検索する。

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_StartScan(WHStartScanCallbackFunc callback, const u8 *macAddr, u16 channel);


/*---------------------------------------------------------------------------*
  Name:         WH_EndScan

  Description:  親機のビーコンを取得する関数

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_EndScan(void);

/* ----------------------------------------------------------------------
  Name:        WH_ParentConnect
  Description: 接続シーケンスを開始します。
  Arguments:   mode    - WH_CONNECTMODE_MP_PARENT ならば親機としてMP開始。
                         WH_CONNECTMODE_DS_PARENT ならば親機としてDataSharing開始。
                         WH_CONNECTMODE_KS_PARENT ならば親機としてKeySharing開始。
               tgid    - 親機通信tgid
               channel - 親機通信channel
               maxEntry - 最大受付子機数
               beaconPeriod - ビーコン間隔 サービスによって指定する
  Returns:     接続シーケンス開始に成功すれば真。
  ---------------------------------------------------------------------- */
extern BOOL WH_ParentConnect(int mode, u16 tgid, u16 channel,u16 maxEntry, u16 beaconPeriod,BOOL bEntry);

/* ----------------------------------------------------------------------
  Name:        WH_ChildConnect
  Description: 接続シーケンスを開始します。
  Arguments:   mode -    WH_CONNECTMODE_MP_CHILD ならば子機としてMP開始。
                         WH_CONNECTMODE_DS_CHILD ならば子機としてDataSharing開始。
                         WH_CONNECTMODE_KS_CHILD ならば子機としてKeySharing開始。
               bssDesc - 接続する親機のbssDesc
               
  Returns:     接続シーケンス開始に成功すれば真。
  ---------------------------------------------------------------------- */
extern BOOL WH_ChildConnect(int mode, WMBssDesc *bssDesc);

/* ----------------------------------------------------------------------
   Name:        WH_ChildConnectAuto
   Description: 子機接続シーケンスを開始します。
                ただし、WH_ParentConnect や WH_ChildConnect で指定する
                各種設定を内部の自動処理に任せます。
   Arguments:   mode    - WH_CONNECTMODE_MP_CHILD ならば子機としてMP開始。
                          WH_CONNECTMODE_DS_CHILD ならば子機としてDataSharing開始。
                          WH_CONNECTMODE_KS_CHILD ならば子機としてKeySharing開始。

                macAddr - 接続する親機のMACアドレスを指定
                          0xFFFFFFならばすべての親機を検索する。
                          
                channel - 親を検索するチャンネルを指定
                          0ならばすべてのチャンネルを検索する。

  Returns:     接続シーケンス開始に成功すれば真。
   ---------------------------------------------------------------------- */
extern BOOL WH_ChildConnectAuto(int mode, const u8 *macAddr, u16 channel);

/*---------------------------------------------------------------------------*
  Name:         WH_SetJudgeAcceptFunc

  Description:  子機の接続受け入れを判定するための関数をセットします。

  Arguments:    子機の接続判定関数を設定.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetJudgeAcceptFunc(WHJudgeAcceptFunc func);


/**************************************************************************
 * 以下は、WH_DATA_PORT ポートを使用する直接的な MP 通信の関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_SetReceiver
   Description: WH_DATA_PORT ポートにデータ受信コールバックを設定します。
   Arguments:   proc - データ受信コールバック
                port   データ送信ポート
   Returns:     none.
   ---------------------------------------------------------------------- */
extern void WH_SetReceiver(WHReceiverFunc proc, int port);

/* ----------------------------------------------------------------------
   Name:        WH_SendData
   Description: WH_DATA_PORT ポートにデータ送信を開始します。
               （MP通信用。データシェアリング中などに呼ぶ必要はありません）
   Arguments:   size - データサイズ
   Returns:     送信開始に成功すれば真。
   ---------------------------------------------------------------------- */
extern BOOL WH_SendData(void *data, u16 datasize, int port, WHSendCallbackFunc callback);


/**************************************************************************
 * 以下は、データシェアリング通信を制御する関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_GetKeySet
   Description: 共有キーデータを読み出します。
   Arguments:   keyset - データ格納先指定
   Returns:     成功すれば真。
   ---------------------------------------------------------------------- */
extern BOOL WH_GetKeySet(WMKeySet *keyset);

/* ----------------------------------------------------------------------
   Name:        WH_GetSharedDataAdr
  Description: 指定の aid を持つマシンから得たデータのアドレスを
                共有データのアドレスから計算し取得します。
   Arguments:   aid - マシンの指定
   Returns:     失敗時は NULL 。
   ---------------------------------------------------------------------- */
extern u16 *WH_GetSharedDataAdr(u16 aid);

/* ----------------------------------------------------------------------
   Name:        WH_StepDS
   Description: データシェアリングの同期を1つ進めます。
                毎フレーム通信するなら、この関数も毎フレーム呼ぶ必要が
                あります。
   Arguments:   data - 送信するデータ
   Returns:     成功すれば真。
   ---------------------------------------------------------------------- */
extern BOOL WH_StepDS(void *data);


/**************************************************************************
 * 以下は、通信を終了して初期化状態まで遷移させる関数です。
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_Reset
   Description: リセットシーケンスを開始します。
                この関数を呼ぶと、今の状態に構わずリセットします。
        エラーからの強制復帰用です。
   Arguments:   none.
   Returns:     処理開始に成功すれば真。
   ---------------------------------------------------------------------- */
extern void WH_Reset(void);

/* ----------------------------------------------------------------------
   Name:        WH_Finalize
   Description: 後処理・終了シーケンスを開始します。
                この関数を呼ぶと、今の状態を見て適切な終了シーケンスを
                実行します。
                通常の終了処理には（WH_Resetではなく）この関数を使用します。
   Arguments:   None.
   Returns:     None.
   ---------------------------------------------------------------------- */
extern void WH_Finalize(void);

/*---------------------------------------------------------------------------*
  Name:         WH_End

  Description:  無線通信を終了する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_End(void);

/*---------------------------------------------------------------------------*
  Name:         WH_GetCurrentAid

  Description:  現在の自分のAIDを取得します。
                子機は接続・切断時に変化する可能性があります。

  Arguments:    None.

  Returns:      AIDの値
 *---------------------------------------------------------------------------*/
extern u16 WH_GetCurrentAid(void);

/*---------------------------------------------------------------------------*
  Name:         WH_IsSysStateIdle
  Description:  アイドル状態になったのを確認して
                次の状態に進むので、その確認のために必要  k.ohno追加
  Arguments:    none
  Returns:      WH_SYSSTATE_IDLEならTRUE
 *---------------------------------------------------------------------------*/
extern BOOL WH_IsSysStateIdle(void);
extern BOOL WH_IsSysStateBusy(void);
extern BOOL WH_IsSysStateScan(void);

extern void WHSetGameInfo(void* pBuff, int size, int ggid, int tgid);

extern BOOL WHSetEntry(BOOL bEnable);

extern BOOL WHIsSetEntryEnd(void);

extern void WHSetLifeTime(BOOL bMinimum);

extern BOOL HWIsParentBeaconSent(void);

extern void WH_ParentDataInit(void);

extern void WH_SetMaxEntry(int maxEntry);

extern BOOL WH_IsSysStateError(void);

/*---------------------------------------------------------------------------*
  Name:         WHSetGGIDScanCallback
  Description:  GGIDを検索する為のコールバックセット
  Arguments:    コールバック
  Returns:      none
 *---------------------------------------------------------------------------*/

extern void WHSetGGIDScanCallback(fGGIDCallBack callback);

extern void WHParentConnectPause(BOOL bPause);

/*---------------------------------------------------------------------------*
  Name:         WHChildConnectPause
  Description:  親機に入ってくるものを切断する
  Arguments:    コールバック
  Returns:      none
 *---------------------------------------------------------------------------*/
extern void WHChildConnectPause(BOOL bPause);
extern BOOL WHGetParentConnectPause(void);

/*---------------------------------------------------------------------------*
  Name:         WHParentConnectPauseSystem  システム専用
  Description:  親機にくる接続を止める もしくは解除
  Arguments:    止める もしくは解除
  Returns:      none
 *---------------------------------------------------------------------------*/

extern void WHParentConnectPauseSystem(BOOL bPause);

#endif
