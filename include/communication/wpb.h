/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library - include
  File:     wpb.h

  2005 Ambrella
 *---------------------------------------------------------------------------*/

#ifndef WPB_H_
#define WPB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================*/

#include <nitro/types.h>
#include <nitro/math.h>
#include <nitro/wm.h>

/*---------------------------------------------------------------------------*
    構造体定義
 *---------------------------------------------------------------------------*/

typedef enum WCStatus {
	WC_STATUS_READY = 0,               // 初期化状態
	WC_STATUS_ERROR,                   // どうにもならないエラー状態
	WC_STATUS_BUSY,                    // 状態遷移中につきビジー状態
	WC_STATUS_PARENT,                  // 親機として接続済み状態
	WC_STATUS_CHILD,                   // 子機として接続済み状態
	WC_STATUS_END,                     // 終了状態 (Targetのみ)
	WC_STATUS_MAX
} WCStatus;

// APIのコールバックで返すステートコード
typedef enum WPBStateCode {
	WPB_STATECODE_START,        /* すれ違い待機開始 */
	WPB_STATECODE_PARENT_FOUND, /* 親機を発見した */
	WPB_STATECODE_CONNECTED,    /* 接続完了 */
	WPB_STATECODE_EXCHANGED,    /* データ交換完了 */
	WPB_STATECODE_DISCONNECTED, /* 切断通知 */
	WPB_STATECODE_END,          /* すれ違い待機終了 */
	WPB_STATECODE_MAX
} WPBStateCode;

// コールバックの引数
typedef struct WPBCallback {
	u16             state;               // コールバックの発生した要因種別
	u16             errcode;             // 非同期処理の結果
	u16             wlCmdID;             // エラーとなったコマンドのID
	u16             wlResult;            // エラーとなった要因コード
	const WMBssDesc *bssDesc;            // 発見した親機情報
	u16             bssDescCount;        // 発見した親機数
	u8              macAddress[WM_SIZE_BSSID]; // すれ違い相手のMACアドレス
	const void      *extinfo;
	const void      *send_ptr;
	int             send_size;
	void            *recv_ptr;
	int             recv_size;
} WPBCallback;

// WPB APIのコールバックの型
typedef void (*WPBCallbackFunc)(WPBCallback *arg);

// ワークエリア
#define PASS_PACKET_SIZE                 512
#define PASS_BUFFER_SIZE                 (PASS_PACKET_SIZE - 4)
#define WPBC_PARENT_DATA_SIZE_MAX        PASS_PACKET_SIZE
#define WPBC_CHILD_DATA_SIZE_MAX         PASS_PACKET_SIZE

#define WPB_RECEIVE_BUFFER \
	(MATH_MAX(WM_SIZE_MP_PARENT_RECEIVE_BUFFER(WPBC_PARENT_DATA_SIZE_MAX, \
											   1, FALSE), \
			  WM_SIZE_MP_CHILD_RECEIVE_BUFFER(WPBC_CHILD_DATA_SIZE_MAX, \
											  FALSE)))
#define WPB_SEND_BUFFER \
	(MATH_MAX(WM_SIZE_MP_PARENT_SEND_BUFFER(WPBC_PARENT_DATA_SIZE_MAX, \
											FALSE), \
			  WM_SIZE_MP_CHILD_SEND_BUFFER(WPBC_CHILD_DATA_SIZE_MAX, FALSE)))

typedef struct WPBBuf {
	WMParentParam pparaBuf;
	union {
		WMScanExParam param;
		u32           dummy[96 / sizeof(u32)]; /* fixme */
	} wmScanExParam;
	/* スキャンバッファ */
	u16           scanBuf[WM_SIZE_SCAN_EX_BUF / sizeof(u16) * 3];
	u16           recvBuf[WPB_RECEIVE_BUFFER / sizeof(u16)];
	u16           sendBuf[WPB_SEND_BUFFER / sizeof(u16)];
	u16           gameInfo[WM_SIZE_USER_GAMEINFO / sizeof(u16)];

	WPBCallbackFunc wpbCallback;
	WCStatus wcStatus;              // 現在の状態を管理
	WCStatus wcTarget;              // 状態変更の目標を管理
	BOOL     wcSendFlag;            // 送信完了フラグ(通常MPモード時)
	u16      sChannel;
	u16      sChannelBusyRatio;
	BOOL     measure_channel_flag;
	/* 親機発見数 */
	u16             child_found_num;
	u16             pad_1; /* padding */
	u16             *current_bssdesc_ptr;
	/* 接続中の親機BssDescポインタ(子機用データ) */
	const WMBssDesc *parent_bssdesc_ptr;
} WPBBuf;

/*---------------------------------------------------------------------------*
    関数定義
 *---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*
  Name:         WPB_SetBuffer

  Description:  ライブラリで使用するバッファを指定する。
                WPB_SetGameInfoの前に呼び出す必要がある。

  Arguments:    wpbBuf       - 呼び出し元によって確保されたバッファへのポインタを指定する。
                               32バイトアラインされている必要がある。

  Returns:      WMErrCode    -   処理結果を返す。
                WM_ERRCODE_SUCCESS       : 処理が正常に完了
                WM_ERRCODE_INVALID_PARAM : 関数に指定したパラメータが不正
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetBuffer(WPBBuf *wpbBuf);

/*---------------------------------------------------------------------------*
  Name:         WPB_SetCallback

  Description:  コールバック関数を設定する。
                WPB_Startの前に呼び出す必要がある。
                この関数の実行前に、WPB_SetBufferを呼び出す必要がある。

  Arguments:    callback  -   ユーザーへのコールバック関数（イベント発生時にコールバックされる）

  Returns:      WMErrCode    -   処理結果を返す。
                WM_ERRCODE_SUCCESS       : 処理が正常に完了
                WM_ERRCODE_FAILED : 処理に失敗 (WPB_SetBufferが呼び出されていない)
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetCallback(WPBCallbackFunc callback);

/*---------------------------------------------------------------------------*
  Name:         WPB_SetGameInfo

  Description:  親機として必要なパラメータを設定する。
                WPB_Start発行前に、必ず1度呼び出す必要がある。
                すれ違い待機中にも呼び出せる。
                この関数の実行前に、WPB_SetBufferを呼び出す必要がある。

  Arguments:    gameInfo       -   ユーザーゲーム情報へのポインタを指定する。
                gameInfoLength -   ユーザーゲーム情報のサイズを指定する。
                                   最大で 112 バイトまで指定することができる。
                ggid           -   ゲームグループIDを指定する。

  Returns:      WMErrCode    -   処理結果を返す。
                WM_ERRCODE_SUCCESS       : 処理が正常に完了
                WM_ERRCODE_FAILED : 処理に失敗 (WPB_SetBufferが呼び出されていない)
                WM_ERRCODE_ILLEGAL_STATE : すでにすれ違い接続が確立し、通信中
                WM_ERRCODE_INVALID_PARAM : 関数に指定したパラメータが不正
 *---------------------------------------------------------------------------*/
WMErrCode WPB_SetGameInfo(const u16 *gameInfo,
						  u16       gameInfoLength,
						  u32       ggid);
/*---------------------------------------------------------------------------*
  Name:         WPB_Start

  Description:  すれ違い通信待機状態にする。WM状態がWM_READYのときに使用可能。
                この関数の実行前に、WPB_SetGameInfoを呼び出す必要がある。

  Arguments:    None.

  Returns:      WMErrCode    -   処理結果を返す。
                WM_ERRCODE_SUCCESS       : 処理が正常に完了
                WM_ERRCODE_ILLEGAL_STATE : すでにすれ違い接続が確立し、通信中
                WM_ERRCODE_INVALID_PARAM : 関数に指定したパラメータが不正
 *---------------------------------------------------------------------------*/
WMErrCode WPB_Start();

/*---------------------------------------------------------------------------*
  Name:         WPB_End

  Description:  すれ違い通信待機状態を終了する。
                無線ユニットへの電源供給を止め、WM_READY ステートに移行する。

  Arguments:    None.

  Returns:      WMErrCode    -   処理結果を返す。
                WM_ERRCODE_SUCCESS       : 処理が正常に完了
                WM_ERRCODE_ILLEGAL_STATE : すれ違い通信待機中でない
 *---------------------------------------------------------------------------*/
WMErrCode WPB_End(void);

int WPB_Finished(void);
void WPB_ForceFinish(void);


/*---------------------------------------------------------------------------*
  Name:         WPB_CheckParent

  Description:  親機情報のリストから、GGID が一致するものを返す。
                複数存在した場合は、ランダムに選択する。

  Arguments:    bssDesc       -  発見した親機情報の集合
                bssDescCount  -  発見した親機の数
                ggid          -  GGID

  Returns:      const WMBssDesc *  -  GGID が一致した親機情報を返す。一致するものがない場合は NULL を返す。
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_TestParent(const WMBssDesc *bssDesc,
								int bssDescCount, u32 ggid);

#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif /* WPB_H_ */

/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
