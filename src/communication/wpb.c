#pragma showmessagenumber on
#pragma warning off (10370)
#pragma warning off (10317)

/*---------------------------------------------------------------------------*
  Project:  Wireless PassBy Library
  File:     wpb.c

  2005 Ambrella
 *---------------------------------------------------------------------------*/
#include    "communication/wpb.h"

// これをdefine すると、無線エラーの場合でもResetして続行する
#define FORCE_CONTINUE 1

/*---------------------------------------------------------------------------*
    定数定義
 *---------------------------------------------------------------------------*/
#define     WC_DEFAULT_PORT             4       // ポート番号( 4～7 )
#define     WC_DEFAULT_PORT_PRIO        2       // ポートの優先度( 0～3 )

/*---------------------------------------------------------------------------*
    構造体定義
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
    内部関数定義
 *---------------------------------------------------------------------------*/
static void WcCreateParentParameter(void);      // 親機情報編集
static void WcCreateScanParameter(void);        // スキャン設定編集
static void WcSetNextScanChannel(void);

static void WcInit(WPBBuf *buf);
static void WcStartParent(void);              // 親機としての接続開始
static void WcStartChild(void);               // 子機としての接続開始
static void WcEnd(void);                      // 初期化状態への移行開始
static WCStatus WcGetStatus(void);            // WCStatus型の内部状態取得

// 親機としての送信データセット
static void WcSetParentData(const void *buf, u16 size);
// 子機としての送信データセット
static void WcSetChildData(const void *buf, u16 size);

static const WMBssDesc *WcBssid_GetParentBssdesc(void);

// WM呼び出し単機能関数
static BOOL Wc_Enable(void);
static BOOL Wc_Disable(void);
static BOOL Wc_PowerOn(void);
static BOOL Wc_PowerOff(void);
static BOOL Wc_SetIndCallback(void);
static BOOL Wc_Reset(void);
static BOOL Wc_SetParentParameter(void);
static BOOL Wc_StartParent(void);
static BOOL Wc_StartScan(void);
static BOOL Wc_EndScan(void);
static BOOL Wc_StartConnect(void);
static BOOL Wc_StartMP(void);
static BOOL Wc_SetMPData(const void *buf, u16 size);

static WMBssDesc *WcBssid_GetScanBuffer();
static u16  WcBssid_GetScanBufferSize();
static void WcBssid_AddFoundChild(const WMStartScanExCallback *arg); /* NEW */
static void WcBssid_ResetScanBuffer(); /* NEW */

// プリント出力抑制ダミー関数
#define WC_DEBUG_PRINT

#ifdef  WC_DEBUG_PRINT
#define     WcDebugPrintf       OS_TPrintf
#else
#define     WcDebugPrintf(...)  ((void) 0)
#endif
//#define DEBUG

/*---------------------------------------------------------------------------*
    内部変数定義
 *---------------------------------------------------------------------------*/

static WPBBuf *wpbBuf;
static int finished = 0;
/************ すれ違い通信関連 ******************/

#define WPBC_SCAN_TIME_MAX               150    // ms
#define WPBC_BEACON_PERIOD               90     // ms

#define WPBC_NUM_OF_CHILD         1

#define MAX_RATIO 100                  // チャンネル使用率は0～100の範囲

typedef enum {
	WPBC_RETURN_NONE = 0,
	WPBC_RETURN_CONTINUE,
	WPBC_RETURN_DONE,
	WPBC_RETURN_DISCONNECT,
	WPBC_RETURN_MAX
}
WpbcReturnCode;

/*---------------------------------------------------------------------------*
    関数定義
 *---------------------------------------------------------------------------*/
// wcから呼び出される関数
static void WPBC_MeasureEnd(void);
static void WPBC_BeaconSent(void);
static BOOL WPBC_GetMode(void);

static void WPBC_StartMpParent(void);
static int  WPBC_Connected(u16 aid, const u8 macAddress[], const u8 ssid[]);
static void WPBC_SetMPDataParent(void);
static void WPBC_Disconnect(u16 aid_bitmap);

static void WPBC_StartMpChild(void);
static void WPBC_SetMPDataChild(void);
static BOOL WPBC_IsActiveWPBC(void);
static int  WPBC_ParentReceiveCallback(u16 *data, u16 length);
static int  WPBC_ChildReceiveCallback(u16 *data, u16 length);

// WMからのコールバック関数
static void WcCb_Disconnect(void *arg);
static BOOL Wc_Disconnect(u16 aid);

static BOOL Wc_MeasureChannel(u16 channel);
static int NumOfAllowedChannels(void);
static int GetNextAllowedChannel(int current_channel);

/* 子機パラメータ */
static int child_scan_channel_count = 0;
static int child_scan_channel = 0;


static BOOL pass_active_flag = FALSE;


static WMStatus _wmstatus ATTRIBUTE_ALIGN(32);

static u16
wm_getstatus()
{
	(void)WM_ReadStatus(&_wmstatus);

	switch (_wmstatus.state) {
	case WM_STATE_READY:		OS_TPrintf("current state = WM_STATE_READY\n");		break;
	case WM_STATE_STOP:			OS_TPrintf("current state = WM_STATE_STOP\n");		break;
	case WM_STATE_IDLE:			OS_TPrintf("current state = WM_STATE_IDLE\n");		break;
	case WM_STATE_CLASS1:		OS_TPrintf("current state = WM_STATE_CLASS1\n");	break;
	case WM_STATE_TESTMODE:		OS_TPrintf("current state = WM_STATE_TESTMODE\n");	break;
	case WM_STATE_SCAN:			OS_TPrintf("current state = WM_STATE_SCAN\n");		break;
	case WM_STATE_CONNECT:		OS_TPrintf("current state = WM_STATE_CONNECT\n");	break;
	case WM_STATE_PARENT:		OS_TPrintf("current state = WM_STATE_PARENT\n");	break;
	case WM_STATE_CHILD:		OS_TPrintf("current state = WM_STATE_CHILD\n");		break;
	case WM_STATE_MP_PARENT:	OS_TPrintf("current state = WM_STATE_MP_PARENT\n");	break;
	case WM_STATE_MP_CHILD:		OS_TPrintf("current state = WM_STATE_MP_CHILD\n");	break;
	case WM_STATE_DCF_CHILD:	OS_TPrintf("current state = WM_STATE_DCF_CHILD\n");	break;
	default:					OS_TPrintf("current state = WM_STATE_MAX\n");		break;
	}

	return _wmstatus.state;
}

/*---------------------------------------------------------------------------*
    内部変数定義
 *---------------------------------------------------------------------------*/
static u16 ChannelListToChannel(u16 channelList)
{
	u16 i;
	for (i = 0; i < 16; i++) {
		if (channelList & (0x0001 << i)) {
			return (u16)(i + 1);
		}
	}
	return (u16)0;
}

static u16 ChannelToChannelList(int channel)
{
	u16 channelList;
	channelList = (u16)(1 << (channel - 1));
	return channelList;
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcInit

  Description:  無線通信を初期化する

  Returns:      None.
 *---------------------------------------------------------------------------*/
static WMParentParam wpbcDefaultParameter = {
	NULL, 0, 0,
	0,                                 // ゲームグループID
	0x0000,                            // temporary ID (毎回+1される)
	1,                                 // エントリー許可フラグ
	WPBC_NUM_OF_CHILD,                 // 最大接続子機数
	0,                                 // マルチブートフラグ
	0,                                 // キーシェアリング
	0,                                 // 連続送信フラグ
	WPBC_BEACON_PERIOD,                // beacon 間隔
	{0, 0, 0, 0},                      // ユーザー名
	{0, 0, 0, 0, 0, 0, 0, 0},          // ゲーム名
	1,                                 // 接続チャンネル
	WPBC_PARENT_DATA_SIZE_MAX,         // 親機送信データサイズ
	WPBC_CHILD_DATA_SIZE_MAX           // 子機送信データサイズ
		// Reserves
};

static void WcInit(WPBBuf *buf)
{
	// WPB用メモリポインタ
	wpbBuf = buf;
	// ステート初期化
	wpbBuf->wcStatus = WC_STATUS_READY;
	// 送信フラグ初期化
	wpbBuf->wcSendFlag = FALSE;

	// 親機情報をキャッシュStoreしても問題ないバッファにコピー
	MI_CpuCopy32(&wpbcDefaultParameter, &wpbBuf->pparaBuf,
				 sizeof(WMParentParam));
	wpbBuf->pparaBuf.userGameInfo = wpbBuf->gameInfo;
}

/*---------------------------------------------------------------------------*
  Name:         WcStartParent

  Description:  親機として無線通信を開始する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcStartParent(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		// 親機として初期化開始
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // 目標状態を"親機接続状態"に
		Wc_Enable();
		break ;
	case WC_STATUS_BUSY:
		// 目標状態を更新
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // 目標状態を"親機接続状態"に
		break ;
	case WC_STATUS_PARENT:
		// 既に親機なので処理なし
		break ;
	case WC_STATUS_CHILD:
		// 一旦リセットする
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_PARENT;   // 目標状態を"親機接続状態"に
		Wc_Reset();
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcStartChild

  Description:  子機として無線通信を開始する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcStartChild(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		// 子機として初期化開始
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // 目標状態を"子機接続状態"に
		Wc_Enable();
		break ;
	case WC_STATUS_BUSY:
		// 目標状態を更新
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // 目標状態を"子機接続状態"に
		break ;
	case WC_STATUS_PARENT:
		// 一旦リセットする
		wpbBuf->wcStatus = WC_STATUS_BUSY;
		wpbBuf->wcTarget = WC_STATUS_CHILD;    // 目標状態を"子機接続状態"に
		Wc_Reset();
		break ;
	case WC_STATUS_CHILD:
		// 既に子機なので処理なし
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcEnd

  Description:  通信前の状態に戻す

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcEnd(void)
{
	switch (wpbBuf->wcStatus) {
	case WC_STATUS_READY:
		WcDebugPrintf("WcEnd: status ready\n");
		// 目標状態を更新
		wpbBuf->wcTarget = WC_STATUS_END;      // 目標状態を"END"に
		break ;
	case WC_STATUS_BUSY:
		WcDebugPrintf("WcEnd: status busy\n");
		// 目標状態を更新
//		wpbBuf->wcTarget = WC_STATUS_READY;    // 目標状態を"READY"に
		wpbBuf->wcTarget = WC_STATUS_END;      // 目標状態を"END"に
		break ;
	case WC_STATUS_PARENT:
		WcDebugPrintf("WcEnd: status parent\n");
	case WC_STATUS_CHILD:
		WcDebugPrintf("WcEnd: status parent or child\n");

		// リセットすることで接続を切断する
		wpbBuf->wcStatus = WC_STATUS_BUSY;
//		wpbBuf->wcTarget = WC_STATUS_READY;    // 目標状態を"READY"に
		wpbBuf->wcTarget = WC_STATUS_END;      // 目標状態を"END"に
		Wc_Reset();
		break ;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcGetStatus

  Description:  無線通信の現在のステートを取得する。

  Arguments:    None.

  Returns:      現在のステートを返す。
 *---------------------------------------------------------------------------*/
static WCStatus WcGetStatus(void)
{
	return wpbBuf->wcStatus;
}

/*---------------------------------------------------------------------------*
  Name:         WcSetParentData

  Description:  親機として送信するデータを設定する。

  Arguments:    buf  - 送信するデータへのポインタ。
                       (32-Byte Align されている必要がある)
                size - 送信するデータのサイズ。

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetParentData(const void *buf, u16 size)
{
	// 送信データサイズ確認
	if (size > wpbBuf->pparaBuf.parentMaxSize) {
		return ;
	}
	// 前の送信の完了を確認
	if (wpbBuf->wcSendFlag) {
		wpbBuf->wcSendFlag = FALSE;
		Wc_SetMPData(buf, size);
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcSetChildData

  Description:  子機として送信するデータを設定する。

  Arguments:    buf  - 送信するデータへのポインタ。
                       (32-Byte Align されている必要がある)
                size - 送信するデータのサイズ。

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetChildData(const void *buf, u16 size)
{
	// 送信データサイズ確認
	if (size > wpbcDefaultParameter.childMaxSize) {
		return ;
	}
	// 前の送信の完了を確認
	if (wpbBuf->wcSendFlag) {
		wpbBuf->wcSendFlag = FALSE;
		Wc_SetMPData(buf, size);
	}
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcCreateParentParameter

  Description:  親機情報を編集する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcCreateParentParameter(void)
{
	static u16 tempID;

	wpbBuf->pparaBuf.channel = wpbBuf->sChannel;
	WcDebugPrintf("  parent channel = %d.\n", wpbBuf->sChannel);
	// tempIDをインクリメント
	wpbBuf->pparaBuf.tgid = ++tempID;
}

/*---------------------------------------------------------------------------*
  Name:         WcCreateScanParameter

  Description:  スキャン設定情報を編集する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcCreateScanParameter(void)
{
	WMScanExParam *p = &wpbBuf->wmScanExParam.param;

	p->maxChannelTime = WPBC_SCAN_TIME_MAX;
	child_scan_channel = GetNextAllowedChannel(child_scan_channel);
	p->channelList = ChannelToChannelList(child_scan_channel);
	p->scanBuf = WcBssid_GetScanBuffer();
	p->scanBufSize = WcBssid_GetScanBufferSize();
	p->scanType = WM_SCANTYPE_PASSIVE;
	p->ssidLength = 0;
	MI_CpuFill8(p->ssid, 0xff, sizeof p->ssid);

	// ブロードキャストアドレスを指定し、全親機を探索するよう設定
	MI_CpuFill8(p->bssid, 0xff, sizeof p->bssid);
}

/*---------------------------------------------------------------------------*
  Name:         WcSetNextScanChannel

  Description:  スキャン設定内のチャンネル指定を次のチャンネルに更新する。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcSetNextScanChannel(void)
{
	WMScanExParam *p = &wpbBuf->wmScanExParam.param;
	u16           allowedChannel = WM_GetAllowedChannel();
	s32           i;
	u16           channel;

	if (allowedChannel == 0) return ;

	channel = ChannelListToChannel(p->channelList);
	for (i = 0; i < 16; i++) {
		if (allowedChannel & 1 << (channel + i) % 16) {
			p->channelList = ChannelToChannelList(((channel + i) % 16) + 1);
			break ;
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Enable

  Description:  WM_Enable関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_Enableにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_Enable(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Enable failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Enable success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Disable();
		break ;
	case WC_STATUS_PARENT:
	case WC_STATUS_CHILD:
		Wc_PowerOn();
		break ;
	}
}

static BOOL Wc_Enable(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_Enable start.\n");
	wmResult = WM_Enable(WcCb_Enable);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Enable failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Disable

  Description:  WM_Disable関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_Disableにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_Disable(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Disable failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Disable success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
	default:
		wpbBuf->wcStatus = WC_STATUS_READY; // 正常にREADY状態に遷移完了
		if (wpbBuf->wcTarget == WC_STATUS_END) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			if (wpbBuf->wpbCallback) {
				WPBCallback arg;

				MI_CpuClear32(&arg, sizeof arg);
				arg.state = WPB_STATECODE_END;
				arg.errcode = WM_ERRCODE_SUCCESS;
				wpbBuf->wpbCallback(&arg);
			}
		}
		OS_TPrintf("WM_Finish!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		WM_Finish();
		finished = 1;
		break ;
	case WC_STATUS_PARENT:
		OS_TPrintf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!REALLY? DISCONNECT AND PARENT\n");
		wpbBuf->wcStatus = WC_STATUS_READY;
		WcStartParent();
		break ;
	case WC_STATUS_CHILD:
		OS_TPrintf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!REALLY? DISCONNECT AND CHILD\n");
		wpbBuf->wcStatus = WC_STATUS_READY;
		WcStartChild();
		break ;
	}
}

static BOOL Wc_Disable(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_Disable start.\n");
	wmResult = WM_Disable(WcCb_Disable);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Disable failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_PowerOn

  Description:  WM_PowerOn関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_PowerOnにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_PowerOn(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_PowerOn failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_PowerOn success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		if (Wc_SetIndCallback()) {
			if (wpbBuf->measure_channel_flag == TRUE) {
				wpbBuf->measure_channel_flag = FALSE;
				wpbBuf->sChannel = 0;
				wpbBuf->sChannelBusyRatio = MAX_RATIO + 1;

				Wc_MeasureChannel((u16)GetNextAllowedChannel(0));
				return ;
			}

			WcCreateParentParameter();
			if (!Wc_SetParentParameter()) {
				wpbBuf->wcTarget = WC_STATUS_READY; // 目標状態を"READY"に
				Wc_Reset();
			}
		}
		break ;
	case WC_STATUS_CHILD:
		if (TRUE == Wc_SetIndCallback()) {
			WcCreateScanParameter();
			if (!Wc_StartScan()) {
				wpbBuf->wcTarget = WC_STATUS_READY; // 目標状態を"READY"に
				Wc_Reset();
			}
		}
		break ;
	}
}

static BOOL Wc_PowerOn(void)
{
	WMErrCode wmResult;

	wpbBuf->measure_channel_flag = TRUE;

	WcDebugPrintf("> WM_PowerOn start.\n");
	wmResult = WM_PowerOn(WcCb_PowerOn);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_PowerOn failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_PowerOff

  Description:  WM_PowerOff関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_PowerOffにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_PowerOff(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_PowerOff failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_PowerOff success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Disable();
		break ;
	case WC_STATUS_PARENT:
	case WC_STATUS_CHILD:
		Wc_PowerOn();
		break ;
	}
}

static BOOL Wc_PowerOff(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_PowerOff start.\n");
	wmResult = WM_PowerOff(WcCb_PowerOff);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_PowerOff failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetIndCallback

  Description:  WM_SetIndCallback関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_SetIndCallback関数が成功した場合にTRUEを返す。
                       失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_Indicate(void *arg)
{
	WMindCallback *cb = (WMindCallback *)arg;
	if (cb->state != 16 && cb->state != 19 /* beacon recv */ ) {
		WcDebugPrintf("- Indication. STATE: %x ERR %d reason %d\n",
					  cb->state, cb->errcode, cb->reason);
	}
}

static BOOL Wc_SetIndCallback(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetIndCallback start.\n");
	wmResult = WM_SetIndCallback(WcCb_Indicate);
	if (wmResult != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetIndCallback failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	WcDebugPrintf("< WM_SetIndCallback success.\n");
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_Reset

  Description:  WM_Reset関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_Resetにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_Reset(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Reset failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return ;
	}
	WcDebugPrintf("< WM_Reset success. target=%d\n",wpbBuf->wcTarget);
	if (wpbBuf->wcTarget == WC_STATUS_READY) {
		WcDebugPrintf("WcCb_Reset: target is STATUS_READY\n");
		if (WPBC_IsActiveWPBC() == TRUE) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
		}
	} else if (wpbBuf->wcTarget == WC_STATUS_CHILD) {
		WcDebugPrintf("WcCb_Reset: target is STATUS_CHILD\n");

		child_scan_channel_count = 0;
//		WcBssid_ClearChildFoundChannel();
		WcBssid_ResetScanBuffer();
	}

	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		WcCreateParentParameter();
		if (!Wc_SetParentParameter()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		WcCreateScanParameter();
		if (!Wc_StartScan()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static void
WcCb_EndMP(void *arg)
{
	(void)&arg;
	Wc_Reset();
}

static void
WcCb_EndParent(void *arg)
{
	(void)&arg;
	Wc_Reset();
}

static BOOL Wc_Reset(void)
{
	WMErrCode wmResult;

	if (wpbBuf->wcStatus != WC_STATUS_BUSY &&
		wpbBuf->wcStatus != WC_STATUS_ERROR) {
		wpbBuf->wcStatus = WC_STATUS_BUSY;
	}
	WcDebugPrintf("Wc_Reset: start\n");

	switch (wm_getstatus()) {
	case WM_STATE_MP_PARENT:
		WcDebugPrintf("Wc_Reset: WM_EndMP\n");
		WM_EndMP(WcCb_EndMP);
		break;
	case WM_STATE_PARENT:
		OS_TPrintf("==================== BE CAREFUL! now in PARENT STATE\n");
		WM_EndParent(WcCb_EndParent);
		break;
	case WM_STATE_IDLE:
		if (wpbBuf->wcStatus == WC_STATUS_END) {
			Wc_PowerOff();
			break;
		}
	default:
		OS_TPrintf("exec WM_Reset: current wm status = %d\n",wm_getstatus());

		wmResult = WM_Reset(WcCb_Reset);
		if (wmResult != WM_ERRCODE_OPERATING) {
			WcDebugPrintf("< WM_Reset failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
			wpbBuf->wcStatus = WC_STATUS_ERROR;
			return FALSE;
		}
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetParentParameter

  Description:  WM_SetParentParameter関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_SetParentParameterにより非同期処理が正常に開始できた
                       場合にTRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_SetParentParameter(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetParentParameter failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_SetParentParameter success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
		Wc_Reset();
		break ;
	case WC_STATUS_PARENT:
		if (!Wc_StartParent()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		wpbBuf->wcTarget = WC_STATUS_CHILD;
		// 子機モードに移行する為に一旦リセットする
		Wc_Reset();
		break ;
	}
}

static BOOL Wc_SetParentParameter(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetParentParameter start.\n");
	wmResult = WM_SetParentParameter(WcCb_SetParentParameter,
									 &wpbBuf->pparaBuf);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_SetParentParameter failed. ERRCODE: %x !!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartParent

  Description:  WM_StartParent関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_StartParentにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void disconnect_callback();

static void WcCb_StartParent(void *arg)
{
	WMstartParentCallback *cb = (WMstartParentCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartParent failed. ERRCODE: %x %x %x !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_PARENT_START:
		WcDebugPrintf("< WM_StartParent success.\n");

		switch (wpbBuf->wcTarget) {
		case WC_STATUS_END:
		case WC_STATUS_READY:
			Wc_Reset();
			break ;
		case WC_STATUS_PARENT:
			if (!Wc_StartMP()) {
				wpbBuf->wcTarget = WC_STATUS_READY;
				Wc_Reset();
			}
			break ;
		case WC_STATUS_CHILD:
			wpbBuf->wcTarget = WC_STATUS_CHILD;
			// 子機モードに移行する為に一旦リセットする
			Wc_Reset();
			break ;
		}
		break ;
	case WM_STATECODE_CONNECTED:
		WcDebugPrintf("- Child Connected.\n");
#ifdef MY_TEXT
		mfprintf(tc[2], "connected from aid = %d\n", cb->aid);
#endif
		if (WPBC_Connected(cb->aid, cb->macAddress, cb->ssid)
			== WPBC_RETURN_DISCONNECT) {
			Wc_Disconnect(cb->aid);
		}
		break ;
	case WM_STATECODE_BEACON_SENT:
	  //  WcDebugPrintf("- Beacon sent.\n");
		WPBC_BeaconSent();

		break ;
	case WM_STATECODE_DISCONNECTED:
		WcDebugPrintf("- Child disconnected.\n");
#ifdef MY_TEXT
		mfprintf(tc[2], "- Child disconnected. %d\n", cb->aid);
#endif
		disconnect_callback();
		WPBC_Disconnect((u16)(1 << cb->aid));
		// コールバックのチェーン中の場合はここではWc_Resetを呼ばない。
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			//親機になる？オリジナルとちがうところ
			wpbBuf->wcTarget = WC_STATUS_PARENT;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartParent(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartParent start.\n");
	wmResult = WM_StartParent(WcCb_StartParent);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartParent failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartScan

  Description:  WM_StartScan関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_StartScanにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_StartScan(void *arg)
{
	WMstartScanExCallback *cb = (WMstartScanExCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartScan failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_StartScan success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_READY:
	case WC_STATUS_END:
//		Wc_Reset();
//		break ;
	case WC_STATUS_PARENT:
		// 親機モードに移行する為に一旦IDLEに戻す
		if (!Wc_EndScan()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		switch (cb->state) {
		case WM_STATECODE_PARENT_FOUND:
			// 親機情報格納バッファのキャッシュを破棄
			DC_InvalidateRange(WcBssid_GetScanBuffer(),
							   WcBssid_GetScanBufferSize());
			WcBssid_AddFoundChild(cb);

			// Don't break here.
			// 続けてもう一回スキャンを実行
		case WM_STATECODE_PARENT_NOT_FOUND:
			// もう一回スキャンを実行する
			WcSetNextScanChannel();
			child_scan_channel_count++;

			if (child_scan_channel_count >= NumOfAllowedChannels()) {
				if (!Wc_EndScan()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
				break ;
			}
			WcCreateScanParameter();
			if (!Wc_StartScan()) {
				wpbBuf->wcTarget = WC_STATUS_READY;
				Wc_Reset();
			}
			break ;
		default:
			WcDebugPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartScan(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartScan start.\n");
	wmResult = WM_StartScanEx(WcCb_StartScan, &wpbBuf->wmScanExParam.param);
	WcDebugPrintf("   channelList %04x\n",
				  &wpbBuf->wmScanExParam.param.channelList);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartScan failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_EndScan

  Description:  WM_EndScan関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_EndScanにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void set_buf(const WPBCallback *arg);
static void reset_buf();

static void WcCb_EndScan(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_EndScan failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	WcDebugPrintf("< WM_EndScan success.\n");
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_PowerOff();
		break ;
	case WC_STATUS_PARENT:
		WcCreateParentParameter();
		if (!Wc_SetParentParameter()) {
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		if (wpbBuf->wpbCallback) {
			WPBCallback arg;

			MI_CpuClear32(&arg, sizeof arg);
			arg.state = WPB_STATECODE_PARENT_FOUND;
			arg.errcode = WM_ERRCODE_SUCCESS;
			arg.bssDesc = (const WMBssDesc *)wpbBuf->scanBuf;
			arg.bssDescCount = wpbBuf->child_found_num;
			wpbBuf->wpbCallback(&arg);
			if (arg.bssDesc && arg.send_ptr && arg.recv_ptr) {
				wpbBuf->parent_bssdesc_ptr = arg.bssDesc;
				set_buf(&arg);
				// 子機としてコネクト開始
				if (!Wc_StartConnect()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
				break ;
			} else {
				reset_buf();
			}
		}
		/* 親機になる */
		// wcTarget = WC_STATUS_READY;
		// WcStartParent();
		if (WPBC_GetMode() == TRUE) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
		}
		Wc_Reset();
		break ;
	}
}

static BOOL Wc_EndScan(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_EndScan start.\n");
	wmResult = WM_EndScan(WcCb_EndScan);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_EndScan failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_StartConnect

  Description:  WM_StartConnect関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_StartConnectにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_StartConnect(void *arg)
{
	WMstartConnectCallback *cb = (WMstartConnectCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_StartConnect failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
		if (cb->errcode == WM_ERRCODE_NO_ENTRY) {
			WcDebugPrintf(" ! Parent doesn't accept entry now.\n");
		}
		if (cb->errcode == WM_ERRCODE_OVER_MAX_ENTRY) {
			WcDebugPrintf(" ! Over max entry of BSS group.\n");
		}
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
		Wc_Reset();
		break;
	case WC_STATUS_READY:
	case WC_STATUS_PARENT:
		WcDebugPrintf("< WM_StartConnect success.\n");
		// 目標状態が"子機"でなくなったので、一旦リセットする
		// コールバックのチェーン中の場合はここではWc_Resetを呼ばない。
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			Wc_Reset();
		}
		break ;
	case WC_STATUS_CHILD:
		switch (cb->state) {
		case WM_STATECODE_CONNECT_START:
			// CONNECTEDになるのを待つので、処理なし
			break ;
		case WM_STATECODE_CONNECTED:
			// 既に子機の場合は何もしない
			if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
				WcDebugPrintf("- Connected , but already child mode.\n");
			} else {
				// MPを開始
				WcDebugPrintf("< WM_StartConnect success. to CHILD\n");
				if (!Wc_StartMP()) {
					wpbBuf->wcTarget = WC_STATUS_READY;
					Wc_Reset();
				}
			}
			break ;
		case WM_STATECODE_BEACON_LOST:
			WcDebugPrintf("- Beacon from parent lost.\n");
			// ビーコンを失っただけではリセットしない
			break ;
		case WM_STATECODE_DISCONNECTED:
			WcDebugPrintf("- DisConnected from parent.\n");
#ifdef MY_TEXT
			mfprintf(tc[2], "1 disconnected by parent\n");
#endif
			disconnect_callback();
			wpbBuf->wcTarget = WC_STATUS_READY;
			// コールバックのチェーン中の場合はここではWc_Resetを呼ばない。
			if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
				//親機になる？オリジナルとちがうところ
				wpbBuf->wcTarget = WC_STATUS_PARENT;
				Wc_Reset();
			}
			break ;
		default:
			WcDebugPrintf("< WM_StartConnect failed. Invalid state code. STATECODE: %x!!!!!!!!!!!!!!!!\n",
						  cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_StartConnect(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_StartConnect start.\n");
	wmResult = WM_StartConnect(WcCb_StartConnect,
							   WcBssid_GetParentBssdesc(),
							   NULL);
	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartConnect failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:Wc_StartMP

  Description:  WM_StartMP関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_StartMPにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_StartMP(void *arg)
{
	WMstartMPCallback *cb = (WMstartMPCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		switch (cb->errcode) {
		case WM_ERRCODE_SEND_FAILED:
		case WM_ERRCODE_TIMEOUT:
			// 送受信が完了しなかった場合のindicate
			// なにもせずに再送されるのを待つ
			break ;
		case WM_ERRCODE_INVALID_POLLBITMAP:
			// 自分宛ではない MP 通信を受け取った場合の indicate
			break ;
		default:
			WcDebugPrintf("< WM_StartMP failed. ERRCODE: %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
						  cb->errcode, cb->state);
			wpbBuf->wcStatus = WC_STATUS_BUSY;
			wpbBuf->wcTarget = WC_STATUS_READY;
			Wc_Reset();
		}
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_MP_START:
		WcDebugPrintf("< WM_StartMP success.\n");
		switch (wpbBuf->wcTarget) {
		case WC_STATUS_END:
		case WC_STATUS_READY:
OS_TPrintf("================================================================\n");
			WM_EndMP(WcCb_EndMP);
			break ;
		case WC_STATUS_PARENT:
		case WC_STATUS_CHILD:
			wpbBuf->wcSendFlag = TRUE;
			// 親(子)機としての接続が正常に完了
			wpbBuf->wcStatus = wpbBuf->wcTarget;
			if (wpbBuf->wcStatus == WC_STATUS_PARENT) {
				WPBC_StartMpParent();
			} else if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
				WPBC_StartMpChild();
			}
			break ;
		}
		break ;
	case WM_STATECODE_MPEND_IND:
		// 親機としての送受信完了時のindicate
		break ;
	case WM_STATECODE_MP_IND:
		// 子機としての受信完了時のindicate
		break ;
	}
}

static void WcCb_ReceiveData(void *arg)
{
	WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< Receive Data failedl. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", cb->errcode);
		return ;
	}
	switch (cb->state) {
	case WM_STATECODE_PORT_RECV:
		// データ受信
		switch (wpbBuf->wcStatus) {
		case WC_STATUS_PARENT:
			if (WPBC_ParentReceiveCallback(cb->data, cb->length)
				== WPBC_RETURN_DISCONNECT) {
				Wc_Disconnect(cb->aid);
				/* 接続＆データ交換完了したら登録 */
			}
			break ;
		case WC_STATUS_CHILD:
			if (WPBC_ChildReceiveCallback(cb->data, cb->length)
				== WPBC_RETURN_DISCONNECT) {
				Wc_Disconnect(0);
			}
			break ;
		default:
			break ;
		}
		break ;
	case WM_STATECODE_CONNECTED:
		// 接続通知
		break ;
	case WM_STATECODE_DISCONNECTED:
		// 切断通知
		switch (wpbBuf->wcStatus) {
		case WC_STATUS_PARENT:
#ifdef MY_TEXT
			mfprintf(tc[2], "disconnected by child %d\n", cb->aid);
#endif
			/* StartParentのほうで通知 */
//			WPBC_Disconnect((u16)(1 << cb->aid));
//			WPBC_ParentReceiveCallback(NULL, 0);
			break ;
		case WC_STATUS_CHILD:
#ifdef MY_TEXT
			mfprintf(tc[2], "disconnected by parent\n");
#endif
			WPBC_ChildReceiveCallback(NULL, 0);
			break ;
		}
		break ;
	default:
		WcDebugPrintf("< Receive Data success. STATE %d API %d ERR %d\n",
					  cb->state, cb->apiid, cb->errcode);
		break ;
	}
}

// static BOOL
BOOL Wc_StartMP(void)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetPortCallback start.\n");
	wmResult = WM_SetPortCallback(WC_DEFAULT_PORT, WcCb_ReceiveData, NULL);
	if (wmResult == WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetPortCallback success.\n");
	} else {
		WcDebugPrintf("< WM_SetPortCallback failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}

	wpbBuf->wcSendFlag = TRUE;

	WcDebugPrintf("> WM_StartMP start.\n");

	wmResult = WM_StartMP(WcCb_StartMP,
						  wpbBuf->recvBuf, (u16)WPB_RECEIVE_BUFFER,
						  wpbBuf->sendBuf, (u16)WPB_SEND_BUFFER,
						  0);

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_StartMP failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         Wc_SetMPData

  Description:  WM_SetMPData関数を呼び出す。

  Arguments:    None.

  Returns:      BOOL - WM_SetMPDataにより非同期処理が正常に開始できた場合に
                       TRUEを返す。失敗した場合はFALSEを返す。
 *---------------------------------------------------------------------------*/
static void WcCb_SetMPData(void *arg)
{
	WMCallback *cb = (WMCallback *)arg;

	// force End
	if (!pass_active_flag) {
		WcDebugPrintf("WcCb_SetMPData: -----------------------------------------------pass_active_flag=0; force end\n");
		wpbBuf->wcTarget = WC_STATUS_END;
		Wc_Reset();
		return;
	}


	wpbBuf->wcSendFlag = TRUE;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_SetMPData failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
	} else {
		WcDebugPrintf("< WM_SetMPData success.\n");
	}

	if (wpbBuf->wcTarget == WC_STATUS_END) {
		WcDebugPrintf("!!!!!!!!!!!!!!!!!WcCb_SetMPData: wcTarget is END. dont continue this process\n");
		Wc_Reset();
		return;
	}

	/* WM_ERRCODE_SEND_FAILEDのときも呼び出す */
	if (wpbBuf->wcStatus == WC_STATUS_CHILD) {
		WPBC_SetMPDataChild();
	} else if (wpbBuf->wcStatus == WC_STATUS_PARENT) {
		WPBC_SetMPDataParent();
	}
}

static BOOL Wc_SetMPData(const void *buf, u16 size)
{
	WMErrCode wmResult;

	WcDebugPrintf("> WM_SetMPData start. data: %08x\n", *(u32 *)buf);

	wmResult = WM_SetMPDataToPort(WcCb_SetMPData, buf, size, 0xffff,
								  WC_DEFAULT_PORT, WC_DEFAULT_PORT_PRIO);
	if (wmResult != WM_ERRCODE_OPERATING) {
		wpbBuf->wcSendFlag = TRUE;
		WcDebugPrintf("< WM_SetMPData failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/*********** org-wc.c ***************/

static int NumOfAllowedChannels(void)
{
	int i, j;

	u16 allowedChannel = WM_GetAllowedChannel();
	for (i = 0, j = 0; i < 16; i++) {
		if ((allowedChannel >> i) & 0x01) {
			j++;
		}
	}
	return j;
}

static u16 next_channel(u16 chan)
{
	int ac = WM_GetAllowedChannel();

	while (++chan <= 14) {
		if (ac & 1 << chan - 1) return chan;
	}
	return 0;
}

static int GetNextAllowedChannel(int current_channel)
{
	int chan;

	chan = next_channel((u16)current_channel);
	if (chan) return chan;
	return next_channel(0);
}


static void WcCb_Disconnect(void *arg)
{
	WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< WM_Disconnect failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  cb->errcode, cb->wlCmdID, cb->wlResult);
#ifdef FORCE_CONTINUE
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			Wc_Reset();
		}
#else
		wpbBuf->wcStatus = WC_STATUS_ERROR;
#endif
		return ;
	}
	WcDebugPrintf("< WM_Disconnect success.\n");

	// force End
	if (!pass_active_flag) {
		WcDebugPrintf("WcCb_DISCONNECT: -----------------------------------------------pass_active_flag=0; force end\n");
		wpbBuf->wcTarget = WC_STATUS_END;
		Wc_Reset();
		return;
	}

	switch (wpbBuf->wcTarget) {
	case WC_STATUS_END:
	case WC_STATUS_READY:
		Wc_Reset();
		break ;
	case WC_STATUS_PARENT:
#ifdef MY_TEXT
		mfprintf(tc[2], "diconnectedBitmap = %04X\n", cb->disconnectedBitmap);
#endif
		WPBC_Disconnect(cb->disconnectedBitmap);
		break ;
	case WC_STATUS_CHILD:
#ifdef MY_TEXT
		mfprintf(tc[2], "< WM_Disconnect success\n");
#endif
//		wpbBuf->wcTarget = WC_STATUS_PARENT;    // 目標状態を"親機接続状態"に
//		Wc_Reset();
		if (wpbBuf->wcStatus != WC_STATUS_BUSY) {
			wpbBuf->wcTarget = WC_STATUS_PARENT;
			Wc_Reset();
		}
		break ;
	}
}

static BOOL Wc_Disconnect(u16 aid)
{
	int wmResult;

	WcDebugPrintf("> WM_Disconnect start.\n");
#ifdef DEBUG
	OS_TPrintf("WM_Disconnect call\n");
#endif
	wmResult = WM_Disconnect(WcCb_Disconnect, aid);

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_Disconnect failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
#ifdef MY_TEXT
		mfprintf(tc[2], "< WM_Disconnect failed. ERRCODE: %x\n", wmResult);
#endif
		wpbBuf->wcStatus = WC_STATUS_ERROR;
		return FALSE;
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
    電波使用率測定部分
 *---------------------------------------------------------------------------*/

static void WcCb_MeasureChannel(void *arg);

/* Wc_MeasureChannel */
static BOOL Wc_MeasureChannel(u16 channel)
{
#define WH_MEASURE_TIME         30     // 1フレームに一回通信している電波を拾えるだけの間隔(ms)
#define WH_MEASURE_CS_OR_ED     3      // キャリアセンスとED値の論理和
#define WH_MEASURE_ED_THRESHOLD 17     // 実験データによる経験的に有効と思われるお勧めED閾値

	int wmResult;

	WcDebugPrintf("> WM_MeasureChannel start.\n");

#ifdef DEBUG
	OS_TPrintf("Channel = %d\n", channel);
#endif
	wmResult = WM_MeasureChannel(WcCb_MeasureChannel,   /* コールバック設定 */
								 WH_MEASURE_CS_OR_ED,   /* CS or ED */
								 WH_MEASURE_ED_THRESHOLD,       /* 第2引数がキャリアセンスのみの場合は無効 */
								 channel,       /* 今回の検索チャンネル */
								 WH_MEASURE_TIME);      /*１チャンネルあたりの調査時間[ms] */

	if (wmResult != WM_ERRCODE_OPERATING) {
		WcDebugPrintf("< WM_MeasureChannel failed. ERRCODE: %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", wmResult);
		return FALSE;
	}
	return TRUE;
}

/* WcCb_MeasureChannel */
static void WcCb_MeasureChannel(void *arg)
{
	WMMeasureChannelCallback *cb = (WMMeasureChannelCallback *)arg;
	u16 channel;

	if (cb->errcode != WM_ERRCODE_SUCCESS) {
		WcDebugPrintf("< %s failed. ERRCODE: %x %x %x!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",
					  __FUNCTION__, cb->errcode, cb->wlCmdID, cb->wlResult);
		wpbBuf->wcTarget = WC_STATUS_READY;
		Wc_Reset();
		return ;
	}
	/* より使用率の低いチャンネルを取得 (初期値 101% なので先頭は必ず選択) */
	if (wpbBuf->sChannelBusyRatio > cb->ccaBusyRatio) {
		wpbBuf->sChannelBusyRatio = cb->ccaBusyRatio;
		wpbBuf->sChannel = cb->channel;
	}

	channel = next_channel(cb->channel);
	if (channel) {
		Wc_MeasureChannel(channel);
		return ;
	}
	WPBC_MeasureEnd();
	wpbBuf->wcTarget = WC_STATUS_PARENT;        // 目標状態を"親機接続状態"に
	Wc_Reset();
}

/*===========================================================================*/

/*---------------------------------------------------------------------------*
  Name:         WcBssid_GetScanBuffer

  Description:  スキャンバッファを得る

  Arguments:    None.

  Returns:      WMBssDesc* - スキャンバッファのポインタ
 *---------------------------------------------------------------------------*/
static WMBssDesc *WcBssid_GetScanBuffer()
{
	return (WMBssDesc *)wpbBuf->current_bssdesc_ptr;
}

static u16 WcBssid_GetScanBufferSize()
{
	int n = (u8 *)wpbBuf->scanBuf + sizeof wpbBuf->scanBuf
		- (u8 *)wpbBuf->current_bssdesc_ptr;

	if (n > WM_SIZE_SCAN_EX_BUF) {
		return WM_SIZE_SCAN_EX_BUF;
	} else {
		return (u16)n;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_AddFoundChild

  Description:  スキャンして見つけた親機の数をセットする

  Arguments:    arg     - スキャン結果

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcBssid_AddFoundChild(const WMStartScanExCallback *arg)
{
	if (arg->bssDescCount) {
		WMBssDesc *bssdesc = arg->bssDesc[arg->bssDescCount - 1];
		/* BssDescのワード数 */
		int w = (u16 *)bssdesc - wpbBuf->current_bssdesc_ptr;
		int n = MATH_ROUNDUP(w + bssdesc->length, 16);

		bssdesc->length = (u16)(n - w);
		wpbBuf->current_bssdesc_ptr += n;
		wpbBuf->child_found_num += arg->bssDescCount;
	}
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_ResetScanBuffer

  Description:  見つけた親機の数をクリアする。

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void WcBssid_ResetScanBuffer()
{
	wpbBuf->child_found_num = 0;
	wpbBuf->current_bssdesc_ptr = wpbBuf->scanBuf;
}

/*---------------------------------------------------------------------------*
  Name:         WcBssid_GetParentBssdesc

  Description:  接続する親機のWMBssDescポインタを返す

  Arguments:    None.

  Returns:      WMBssDesc* - 親機のWMBssDescポインタ
 *---------------------------------------------------------------------------*/
static const WMBssDesc *WcBssid_GetParentBssdesc(void)
{
	return wpbBuf->parent_bssdesc_ptr;
}

/*---------------------------------------------------------------------------*
    定数定義
 *---------------------------------------------------------------------------*/

#define REQUEST_DONE                          0xffff
#define REQUEST_NONE                          0xfffe
#define REQUEST_BYE                           0xfffd

#define HARDWARE_BUFFER_DUMMY_COUNT           3

#define MAX_PATTERN                           4
#define MAX_SEQ                               4

#define     PARENT_BEACON_SEND_COUNT_OUT  (900/WPBC_BEACON_PERIOD)


/*---------------------------------------------------------------------------*
    構造体定義
 *---------------------------------------------------------------------------*/
typedef struct {
	int      size;
	int      total_count;
	const u8 *user_send_data;
} PassData;

typedef struct {
	u16 req_count;
	u16 res_count;
	u8  buf[PASS_BUFFER_SIZE];
} PassBuffer;

typedef struct {
	u8 *user_recv_buffer;
	BOOL reset_done;
	BOOL send_done;
	BOOL recv_done;
	int hardware_buffer_count;
	PassBuffer send_buf;
	PassBuffer recv_buf;
	int pre_send_count;
	u32 recv_bitmap; /* mod32でループ */
	int recv_bitmap_index;
} PassCtrl;


/********** 内部データ ***********************************/

static u8 gSendBuf[512] ATTRIBUTE_ALIGN(32);    //送信バッファ

static PassData my_pass_data;
static PassCtrl pass_ctrl;

/* 親機パラメータ */
static u16 connected_bitmap = 0;
static int parent_beacon_sent_count;

static int start_pattern = 0;
static int current_pattern = 0;
static int current_seq = 0;


static BOOL pass_comm_pattern[MAX_PATTERN][MAX_SEQ] = {
	{TRUE, FALSE, TRUE, TRUE},         // FALSE -> 子機
	{FALSE, TRUE, TRUE, TRUE},         // TRUE ->  親機
	{FALSE, TRUE, TRUE, TRUE},
	{TRUE, FALSE, TRUE, TRUE},
};

/*---------------------------------------------------------------------------*
    マクロ定義
 *---------------------------------------------------------------------------*/
static inline int div32(int a)
{
	return (a >> 5);
}

static inline int mod32(int a)
{
	return (a & 0x1f);
}

static inline int get_data_total_count(void)
{
	return my_pass_data.total_count;
}

/********** 内部関数 *************************************/

/*---------------------------------------------------------------------------*
  Name:         pass_copy_to_structure

  Description:  WM受信バッファからPassBuffer構造体にコピーする

  Arguments:    buf - WM受信バッファ
                pb  - PassBuffer構造体

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_copy_to_structure(u8 *buf, PassBuffer * pb)
{
	int i;

	pb->req_count = (u16)(((u32)(*buf++)) << 8);        /* HI */
	pb->req_count += (u16)(*buf++);    /* LO */

	pb->res_count = (u16)(((u32)(*buf++)) << 8);        /* HI */
	pb->res_count += (u16)(*buf++);    /* LO */

	for (i = 0; i < PASS_BUFFER_SIZE; i++) {
		pb->buf[i] = *buf++;
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_copy_to_buffer

  Description:  PassBuffer構造体からWM送信バッファにコピーする

  Arguments:    pb  - PassBuffer構造体
                buf - WM送信バッファ

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_copy_to_buffer(PassBuffer * pb, u8 *buf)
{
	int i;

	*buf++ = (u8)(((pb->req_count) >> 8) & 0xff);       /* HI */
	*buf++ = (u8)(pb->req_count & 0xff);        /* LO */

	*buf++ = (u8)(((pb->res_count) >> 8) & 0xff);       /* HI */
	*buf++ = (u8)(pb->res_count & 0xff);        /* LO */

	for (i = 0; i < PASS_BUFFER_SIZE; i++) {
		*buf++ = pb->buf[i];
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_BufToData

  Description:  PassBuffer構造体からユーザー受信バッファにコピーする

  Arguments:    pb  - PassBuffer構造体
                buf - ユーザー受信バッファ

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_BufToData(PassBuffer * pb, PassCtrl * pctrl)
{
	int res_count;
	u8  *src, *dest;

	res_count = (int)pb->res_count;
	src = pb->buf;

	if (pctrl->user_recv_buffer == NULL) {
		return ;
	}

	dest = pctrl->user_recv_buffer + (res_count * PASS_BUFFER_SIZE);
	if (res_count == get_data_total_count() - 1) {
		int mod = my_pass_data.size % PASS_BUFFER_SIZE;
		if (mod) {
			MI_CpuCopy8(src, dest, mod);
		} else {
			MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
		}
	} else {
		MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_DataToBuf

  Description:  ユーザー送信バッファからPassBuffer構造体にコピーする

  Arguments:    seq_no - シーケンス番号
                pb     - PassBuffer構造体
                buf    - ユーザー送信バッファ

  Returns:      None.    {TRUE, TRUE, FALSE, TRUE},

 *---------------------------------------------------------------------------*/
static void pass_DataToBuf(int seq_no, PassBuffer * pb, PassData * pd)
{
	const u8 *src;
	u8       *dest;

	pb->res_count = (u16)seq_no;

	if (seq_no != REQUEST_DONE && seq_no != REQUEST_NONE &&
		seq_no != REQUEST_BYE) {
		src = pd->user_send_data + (seq_no * PASS_BUFFER_SIZE);
		dest = pb->buf;
		if (seq_no == get_data_total_count() - 1) {
			int mod = my_pass_data.size % PASS_BUFFER_SIZE;
			if (mod) {
				MI_CpuCopy8(src, dest, mod);
			} else {
				MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
			}
		} else {
			MI_CpuCopy8(src, dest, PASS_BUFFER_SIZE);
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_init_recv_bitmap

  Description:  受信履歴ビットマップの初期化

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_data_init_recv_bitmap()
{
	pass_ctrl.recv_bitmap = 0;
	pass_ctrl.recv_bitmap_index = 0;
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_set_recv_bitmap

  Description:  受信履歴ビットマップをセットする

  Arguments:    aid    - AID(AIDごとに受信バッファを管理しているため)
                seq_no - シーケンス番号

  Returns:      BOOL   - FALSE/すでにチェック済み
 *---------------------------------------------------------------------------*/
static BOOL pass_data_set_recv_bitmap(int seq_no)
{
	if (seq_no < pass_ctrl.recv_bitmap_index) return FALSE;
	if (seq_no >= pass_ctrl.recv_bitmap_index + 32) return FALSE;
	if (pass_ctrl.recv_bitmap & 1 << seq_no % 32) return FALSE;
	pass_ctrl.recv_bitmap |= 1 << seq_no % 32;
	while (pass_ctrl.recv_bitmap & 1 << pass_ctrl.recv_bitmap_index % 32) {
		pass_ctrl.recv_bitmap &= ~(1 << pass_ctrl.recv_bitmap_index++ % 32);
	}
	return TRUE;
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_get_recv_bitmap

  Description:  受信履歴ビットマップをチェックする

  Arguments:    seq_no - シーケンス番号

  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL pass_data_get_recv_bitmap(int seq_no)
{
	if (seq_no < pass_ctrl.recv_bitmap_index) return TRUE;
	if (seq_no >= pass_ctrl.recv_bitmap_index + 32) return FALSE;
	if (pass_ctrl.recv_bitmap & 1 << seq_no % 32) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_data_get_next_count

  Description:  次に相手に要求するシーケンス番号を得る

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static u16 pass_data_get_next_count()
{
	PassCtrl *pc = &pass_ctrl;
	int count;

	if (pc->recv_bitmap_index >= get_data_total_count()) {
		return REQUEST_DONE;          /* すべて受信済み */
	}
	count = pc->pre_send_count;
	for (;;) {
		count++;
		if (count >= get_data_total_count() ||
			count >= pc->recv_bitmap_index + 32) {
			count = pc->recv_bitmap_index;
		}
		if (!pass_data_get_recv_bitmap(count)) {
			pc->pre_send_count = count;
			return (u16)count;
		}
		if (count == pc->pre_send_count) {
			/* ここに来ることはないはず */
			OS_TPrintf("Error ! %d %d %d %08X\n", pc->pre_send_count, pc->recv_bitmap_index, get_data_total_count(), pc->recv_bitmap);
			return REQUEST_DONE;          /* すべて受信済み */
		}
	}
}

/*---------------------------------------------------------------------------*
  Name:         pass_InitBuf

  Description:  PassBuffer構造体の初期化

  Arguments:    pb - PassBuffer構造体

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void pass_InitBuf(PassBuffer * pb)
{
	pb->res_count = REQUEST_NONE;
	//  pb->req_count = REQUEST_NONE;
	pb->req_count = 0;
	MI_CpuClear8(pb->buf, PASS_BUFFER_SIZE);
}


/*---------------------------------------------------------------------------*
  Name:         pass_ResetData

  Description:  に呼び出される関数。

  Arguments:    None.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void pass_ResetData()
{
	PassCtrl *pc;
	pc = &pass_ctrl;

	pass_InitBuf(&(pc->send_buf));
	pass_InitBuf(&(pc->recv_buf));
	pass_data_init_recv_bitmap();
	pc->pre_send_count = REQUEST_NONE;
	pc->reset_done = TRUE;
	pc->send_done = FALSE;
	pc->recv_done = FALSE;
	pc->hardware_buffer_count = 0;
}


/*---------------------------------------------------------------------------*
    外部関数
 *---------------------------------------------------------------------------*/

static void WPBC_MeasureEnd(void)
{
	if (wpbBuf->wpbCallback) {
		WPBCallback arg;

		MI_CpuClear32(&arg, sizeof arg);
		arg.state = WPB_STATECODE_START;
		arg.errcode = WM_ERRCODE_SUCCESS;
		wpbBuf->wpbCallback(&arg);
	}
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_BeaconSent

  Description:  すれちがい通信関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_BeaconSent(void)
{
	parent_beacon_sent_count++;

	if (parent_beacon_sent_count > PARENT_BEACON_SEND_COUNT_OUT) {
		if (connected_bitmap == 0) {
			parent_beacon_sent_count = 0;

			if (WPBC_GetMode() == TRUE) {
				/* 親機のまま */
			} else {
				/* 子機になる */
				WcStartChild();
			}
		}
	}
}


static BOOL WPBC_GetMode(void)
{
	current_seq++;
	if (current_seq > MAX_SEQ - 1) {
		current_seq = 0;
		current_pattern++;
		if (current_pattern > MAX_PATTERN - 1) {
			current_pattern = 0;
		}
		if (current_pattern == start_pattern) {
			start_pattern = (int)(OS_GetTick() % MAX_PATTERN);  /* 乱数のつもり */
			current_pattern = start_pattern;
		}
	}

	if (pass_comm_pattern[current_pattern][current_seq] == TRUE) {
#if 0
		OS_TPrintf("pat %d seq %d",current_pattern, current_seq );
		OS_TPrintf("P\n");
#endif
		return TRUE;
	} else {
#if 0
		OS_TPrintf("pat %d seq %d",current_pattern, current_seq );
		OS_TPrintf("C\n");
#endif
		return FALSE;
	}
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_StartMpParent

  Description:  すれちがい通信関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_StartMpParent(void)
{
	connected_bitmap = 0;
	parent_beacon_sent_count = 0;
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ParentSendStep

  Description:  親機として子機へのデータ送信時に呼び出される関数。

  Arguments:    connected_bitmp - 現在接続中のAIDビットマップ
                buf  - 送信バッファへのポインタ
                size - 送信バッファサイズ

  Returns:      送信データサイズ
 *---------------------------------------------------------------------------*/
static int WPBC_ParentSendStep(int size)
{
#pragma unused(size)
	int send_size = 0;
	int send_buf_count;
	u8 *send_buf = gSendBuf;

	if (connected_bitmap == 0) {
		return 0;
	}

	/* 自局のリクエスト番号のセット */
	if (pass_ctrl.recv_done == TRUE) {
		if (pass_ctrl.reset_done) {
			pass_ctrl.send_buf.req_count = REQUEST_DONE;
		} else {
			pass_ctrl.send_buf.req_count = REQUEST_BYE;
		}
	} else {
		pass_ctrl.send_buf.req_count = pass_data_get_next_count();
		if (pass_ctrl.send_buf.req_count == REQUEST_DONE) {
			pass_ctrl.recv_done = TRUE;
		}
	}

	/* 相手のリクエストに対するデータのセット */
	if (pass_ctrl.send_done) {
		send_buf_count = REQUEST_NONE;
	} else {
		send_buf_count = pass_ctrl.recv_buf.req_count;
	}
	pass_DataToBuf(send_buf_count, &(pass_ctrl.send_buf), &my_pass_data);

	/* send_bufから送信バッファにコピー */
	pass_copy_to_buffer(&(pass_ctrl.send_buf), send_buf);

#ifdef DEBUG
	OS_TPrintf("parent send->%x req->%x\n", send_buf_count,
			   pass_ctrl.send_buf.req_count);
#endif
	send_size = PASS_PACKET_SIZE;

	if (send_size > 0) {
		if (send_size & 1) {
			WcSetParentData((void *)gSendBuf, (u16)(send_size + 1));
		} else {
			WcSetParentData((void *)gSendBuf, (u16)send_size);
		}
	}

	return send_size;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Connected

  Description:  すれちがい通信関数。親として待機中に子から接続された

  Arguments:    aid.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void set_buf(const WPBCallback *arg)
{
	my_pass_data.total_count = (arg->recv_size / PASS_BUFFER_SIZE) + ((arg->recv_size % PASS_BUFFER_SIZE) ? 1 : 0);
	my_pass_data.size = arg->send_size;
	my_pass_data.user_send_data = arg->send_ptr;

	pass_ctrl.user_recv_buffer = arg->recv_ptr;

//        pass_ctrl[i].user_recv_buffer = &(((u8 *)recv_ptr)[i * send_size]);
//	pass_ctrl.keepalive = keepalive;
}

static void reset_buf()
{
	my_pass_data.total_count = 0;
	my_pass_data.size = 0;
	my_pass_data.user_send_data = NULL;

	pass_ctrl.user_recv_buffer = NULL;
}

static int WPBC_Connected(u16 aid, const u8 macAddress[], const u8 ssid[])
{
	int send_size;

	if (connected_bitmap != 0) {
		/* 別の子機と通信しているときは送信しない */
		connected_bitmap |= (1 << aid);
	} else {
		connected_bitmap |= (1 << aid);
		pass_ctrl.reset_done = FALSE;
		pass_ctrl.recv_done = FALSE;
		if (wpbBuf->wpbCallback) {
			WPBCallback arg;
			int         i;

			MI_CpuClear32(&arg, sizeof arg);
			arg.state = WPB_STATECODE_CONNECTED;
			arg.errcode = WM_ERRCODE_SUCCESS;
			/* arg.bssDesc = NULL; */
			/* arg.recv_ptr = NULL; */
			for (i = 0; ; i++) {
				if (i == WM_SIZE_CHILD_SSID / sizeof(u32)) {
					/* arg.extinfo = NULL; */
					break ;
				}
				if (((const u32 *)ssid)[i] != 0) {
					arg.extinfo = ssid;
					break ;
				}
			}
			MI_CpuCopy8(macAddress, arg.macAddress, sizeof arg.macAddress);
			wpbBuf->wpbCallback(&arg);
			if (arg.send_ptr && arg.recv_ptr) {
				set_buf(&arg);
				pass_ResetData();
				send_size = WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX);
				return WPBC_RETURN_CONTINUE;
			} else {
				reset_buf();
			}
		}
	}
	return WPBC_RETURN_DISCONNECT;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_SetMPDataParent

  Description:  すれちがい通信関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_SetMPDataParent(void)
{
	WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX);
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ParentReceiveCallback

  Description:  親機として子機からのデータ受信時に呼び出される関数。

  Arguments:    buf    - 受信データへのポインタ (NULL で切断通知)
                length  - 受信データのサイズ

  Returns:      TRUE/FALSE - データ交換完了(TRUE)
 *---------------------------------------------------------------------------*/
static void disconnect_callback()
{
	if (!(pass_ctrl.reset_done == FALSE && pass_ctrl.recv_done)) {
		WPBCallback arg;

		pass_ctrl.reset_done = FALSE;
		pass_ctrl.recv_done = TRUE;
		MI_CpuClear32(&arg, sizeof arg);
		arg.state = WPB_STATECODE_DISCONNECTED;
		arg.errcode = WM_ERRCODE_SUCCESS;
		wpbBuf->wpbCallback(&arg);
	}
}

static int WPBC_ParentReceiveCallback(u16 *buf, u16 length)
{
	if (buf == NULL || length == 0) {
		return WPBC_RETURN_CONTINUE;   /* 通信を継続する */
	}

	/* まず受信バッファからpass_recv_bufにコピー */
	pass_copy_to_structure(((u8 *)buf), &(pass_ctrl.recv_buf));
	if (pass_ctrl.recv_buf.req_count == REQUEST_BYE) {
#ifdef DEBUG
		OS_TPrintf("parent : get REQUEST_BYE\n");
#endif
		disconnect_callback();
		return WPBC_RETURN_DISCONNECT;  /* 通信を切断する */
	}
	if (pass_ctrl.reset_done == FALSE) {
		//    pass_ctrl[aid].recv_buf.req_count = REQUEST_NONE;
	} else {
		if (pass_ctrl.recv_done == FALSE) {
#ifdef DEBUG
			OS_TPrintf("parent recv->%x\n", pass_ctrl.recv_buf.res_count);
#endif
			if (pass_ctrl.recv_buf.res_count < get_data_total_count()) {
				/* 受信履歴にチェックを入れる */
				if (TRUE == pass_data_set_recv_bitmap(pass_ctrl.recv_buf.res_count)) {
					/* 受信データをセーブ */
					pass_BufToData(&(pass_ctrl.recv_buf), &pass_ctrl);
				}
			}
		} else {
			if (pass_ctrl.recv_buf.req_count == REQUEST_DONE) {
				pass_ctrl.send_done = TRUE;
			}
			if (pass_ctrl.send_done == TRUE) {
				/* こちらも送信データ終了の場合 */
				if (pass_ctrl.hardware_buffer_count < (HARDWARE_BUFFER_DUMMY_COUNT * 2)) {
					// ４回くるまで保留
					/* 相手のとりこぼしを防ぐ */
					pass_ctrl.hardware_buffer_count++;
					return WPBC_RETURN_CONTINUE;        /* 通信を継続する */
				}
				pass_ctrl.reset_done = FALSE;
				if (wpbBuf->wpbCallback) {
					WPBCallback arg;

					MI_CpuClear32(&arg, sizeof arg);
					arg.state = WPB_STATECODE_EXCHANGED;
					arg.errcode = WM_ERRCODE_SUCCESS;
					arg.bssDesc = NULL;
					wpbBuf->wpbCallback(&arg);
					if (arg.send_ptr && arg.recv_ptr) {
#ifdef DEBUG
						OS_TPrintf("Parent SetNext\n");
#endif
						set_buf(&arg);
						pass_ResetData();
						/* WPBC_ParentSendStep(WPBC_PARENT_DATA_SIZE_MAX); */
						return WPBC_RETURN_DONE;
					}
				}
				return WPBC_RETURN_CONTINUE;        /* 通信を継続する */
//				return WPBC_RETURN_DISCONNECT;  /* 通信を切断する */
			}
		}
	}
	return WPBC_RETURN_CONTINUE;       /* 通信を継続する */
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Disconnect

  Description:  すれちがい通信関数

  Arguments:    aid_bitmap.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_Disconnect(u16 aid_bitmap)
{
	connected_bitmap &= ~aid_bitmap;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_ChildSendStep

  Description:  子機として親機からのデータ受信時に呼び出される関数。

  Arguments:    None.

  Returns:      送信データサイズ
 *---------------------------------------------------------------------------*/
static int WPBC_ChildSendStep(int size)
{
#pragma unused(size)
	int peer_request;

	/* 自局のリクエスト番号をセット */
	if (pass_ctrl.recv_done == TRUE) {
		if (pass_ctrl.reset_done) {
			pass_ctrl.send_buf.req_count = REQUEST_DONE;
		} else {
			pass_ctrl.send_buf.req_count = REQUEST_BYE;
		}
	} else {
		pass_ctrl.send_buf.req_count = pass_data_get_next_count();
		if (pass_ctrl.send_buf.req_count == REQUEST_DONE) {
			pass_ctrl.recv_done = TRUE;
		}
	}

	/* 相手局のリクエスト番号に対してデータをセット */
	peer_request = (int)(pass_ctrl.recv_buf.req_count);
	pass_DataToBuf(peer_request, &(pass_ctrl.send_buf), &my_pass_data);

	/* send_bufから送信バッファにコピー */
	pass_copy_to_buffer(&(pass_ctrl.send_buf), gSendBuf);

#ifdef DEBUG
	OS_TPrintf("child send->%x req->%x\n", peer_request, pass_ctrl.send_buf.req_count);
#endif

	WcSetChildData((void *)gSendBuf, PASS_PACKET_SIZE);

	return PASS_PACKET_SIZE;           /* send size */
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_StartMpChild

  Description:  すれちがい通信関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_StartMpChild(void)
{
	pass_ResetData();

	WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX);
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_SetMPDataChild

  Description:  すれちがい通信関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static void WPBC_SetMPDataChild(void)
{
	int send_size;

	send_size = WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX);
}


/*---------------------------------------------------------------------------*
  Name:         WPBC_ChildReceiveCallback

  Description:  子機として親機からのデータ受信時に呼び出される関数。

  Arguments:    buf     - 受信データへのポインタ (NULL で切断通知)
                length  - 受信データのサイズ

  Returns:      TRUE/FALSE - データ交換完了(TRUE)
 *---------------------------------------------------------------------------*/
static int WPBC_ChildReceiveCallback(u16 *buf, u16 length)
{
	if (buf == NULL || length == 0) {
		return WPBC_RETURN_CONTINUE;   /* 通信を継続する */
	}

#ifdef DEBUG
	OS_TPrintf("child recv->%x\n", pass_ctrl.recv_buf.res_count);
#endif

	/* まず受信バッファからpass_recv_bufにコピー */
	pass_copy_to_structure(((u8 *)buf), &(pass_ctrl.recv_buf));
	if (pass_ctrl.recv_buf.req_count == REQUEST_BYE) {
#ifdef DEBUG
		OS_TPrintf("child: get REQUEST_BYE\n");
#endif
		disconnect_callback();
		return WPBC_RETURN_DISCONNECT;  /* 通信を切断する */
	}
	if (pass_ctrl.reset_done == FALSE) {
		//    pass_ctrl[MY_AID].recv_buf.req_count = REQUEST_NONE;
	} else {
		if (length < PASS_PACKET_SIZE) {
			// OS_TPrintf("length shortage aid %d = %d logical = %d\n",aid, length, PASS_PACKET_SIZE * aid );
			return WPBC_RETURN_CONTINUE;        /* 通信を継続する */
		}
		if (pass_ctrl.recv_done == FALSE) {
			if (pass_ctrl.recv_buf.res_count < get_data_total_count()) {
				/* 受信履歴にチェックを入れる */
				if (TRUE == pass_data_set_recv_bitmap(pass_ctrl.recv_buf.res_count)) {
					pass_BufToData(&(pass_ctrl.recv_buf), &(pass_ctrl));
				}
			}
		} else {
			if (pass_ctrl.recv_buf.req_count == REQUEST_DONE) {
				pass_ctrl.send_done = TRUE;
			}
			if (pass_ctrl.send_done == TRUE) {
				/* 自局も送信データ終了の場合 */
				if (pass_ctrl.hardware_buffer_count < HARDWARE_BUFFER_DUMMY_COUNT) {
					// ２回くるまで保留
					/* 相手のとりこぼしを防ぐ */
					pass_ctrl.hardware_buffer_count++;
					return WPBC_RETURN_CONTINUE;        /* 通信を継続する */
				}
				pass_ctrl.reset_done = FALSE;
				if (wpbBuf->wpbCallback) {
					WPBCallback arg;

					MI_CpuClear32(&arg, sizeof arg);
					arg.state = WPB_STATECODE_EXCHANGED;
					arg.errcode = WM_ERRCODE_SUCCESS;
					arg.bssDesc = WcBssid_GetParentBssdesc();
					wpbBuf->wpbCallback(&arg);
					if (arg.send_ptr && arg.recv_ptr) {
#ifdef DEBUG
						OS_TPrintf("Child SetNext\n");
#endif
						set_buf(&arg);
						pass_ResetData();
						/* WPBC_ChildSendStep(WPBC_CHILD_DATA_SIZE_MAX); */
						return WPBC_RETURN_DONE;
					}
				}
				return WPBC_RETURN_CONTINUE;        /* 通信を継続する */
//				return WPBC_RETURN_DISCONNECT;
			}
		}
	}
	return WPBC_RETURN_CONTINUE;       /* 通信を継続する */
}

/*===========================================================================*/
WMErrCode WPB_SetBuffer(WPBBuf *wpbBuf)
{
	if (!wpbBuf || ((u32)wpbBuf & 0x01f)) return WM_ERRCODE_INVALID_PARAM;

	WcInit(wpbBuf);
	return WM_ERRCODE_SUCCESS;
}

WMErrCode WPB_SetCallback(WPBCallbackFunc callback)
{
	if (!wpbBuf) return WM_ERRCODE_FAILED;

	wpbBuf->wpbCallback = callback;
	return WM_ERRCODE_SUCCESS;
}

WMErrCode WPB_SetGameInfo(const u16 *gameInfo,
						  u16       gameInfoLength,
						  u32       ggid)
{
	if (gameInfoLength > WM_SIZE_USER_GAMEINFO) {
		return WM_ERRCODE_INVALID_PARAM;
	}
	if (!wpbBuf) return WM_ERRCODE_FAILED;

	if (gameInfoLength) {
		MI_CpuCopy8(gameInfo, wpbBuf->pparaBuf.userGameInfo, gameInfoLength);
	}
	wpbBuf->pparaBuf.userGameInfoLength = gameInfoLength;
	wpbBuf->pparaBuf.ggid = ggid;

	return WM_ERRCODE_SUCCESS;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_Start

  Description:  すれちがい通信開始関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
WMErrCode WPB_Start()
{
	finished = 0;
	pass_active_flag = TRUE;
	WcStartParent();

	return WM_ERRCODE_SUCCESS;
}

/*---------------------------------------------------------------------------*
  Name:         WPBC_IsActiveWPBC

  Description:  すれちがい通信開始関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
static BOOL WPBC_IsActiveWPBC(void)
{
	return pass_active_flag;
}

/*---------------------------------------------------------------------------*
  Name:         WPB_End

  Description:  すれちがい通信終了関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
WMErrCode WPB_End(void)
{
	pass_active_flag = FALSE;
	WcEnd();                           /* PowerOff状態になる */
	return WM_ERRCODE_SUCCESS;
}


void WPB_ForceFinish(void)
{
	wpbBuf->wcTarget = WC_STATUS_END;
	Wc_PowerOff();
}

int
WPB_Finished(void)
{
	return finished;
}

/*---------------------------------------------------------------------------*
  Name:         WPB_TestParent

  Description:  すれちがい親機テスト関数

  Arguments:    none.

  Returns:      none.
 *---------------------------------------------------------------------------*/
const WMBssDesc *WPB_TestParent(const WMBssDesc *bssDesc,
								int bssDescCount, u32 ggid)
{
	int i;
	int n = 0;
	const WMBssDesc *p = bssDesc;

	/* GGID が一致する親機を数える */
	for (i = 0; i < bssDescCount; i++) {
		/* GameGroupIDが一致するかを確認 */
		/* userGameInfo が 4 バイト以上あり、最初の 4 バイトを u32 として */
		/* 最上位ビットが 0 なら共通すれ違いに対応 */
		if (p->gameInfoLength >=
			(char *)&p->gameInfo.ggid - (char *)&p->gameInfo
			+ sizeof p->gameInfo.ggid &&
			p->gameInfo.ggid == ggid &&
			p->gameInfo.userGameInfoLength >= 4 &&
			(*(u32 *)p->gameInfo.userGameInfo & 1 << 31) == 0) {
			n++;
		}
		p = (const WMBssDesc *)((const u16 *)p + p->length);
	}
	if (!n) return NULL;
	n = OS_GetTickLo() % 263 % n; /* 擬似乱数 */
	p = bssDesc;
	for (i = 0; i < bssDescCount; i++) {
		/* GameGroupIDが一致するかを確認 */
		/* userGameInfo が 4 バイト以上あり、最初の 4 バイトを u32 として */
		/* 最上位ビットが 0 なら共通すれ違いに対応 */
		if (p->gameInfoLength >=
			(char *)&p->gameInfo.ggid - (char *)&p->gameInfo
			+ sizeof p->gameInfo.ggid &&
			p->gameInfo.ggid == ggid &&
			p->gameInfo.userGameInfoLength >= 4 &&
			(*(u32 *)p->gameInfo.userGameInfo & 1 << 31) == 0) {
			if (!n) return p;
			n--;
		}
		p = (const WMBssDesc *)((const u16 *)p + p->length);
	}
	return NULL; /* ここには来ないはず */
}
/*---------------------------------------------------------------------------*
  End of file
 *---------------------------------------------------------------------------*/
