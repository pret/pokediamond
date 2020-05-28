/**
 * @version "$Id: mprequest.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mprequest.c
 * @brief 無線通信ライブラリ 状態遷移関数
 * 
 */
#include "mpconnect.h"
#include "mprequest.h"
#include "mpcallback.h"
#include "mpdata.h"
#include "mpdebug.h"

/**
 * PORT通信を行う
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestSetMPData(const void *buf, u32 size, u16 aid_bitmap)
{
  WMErrCode result;

  MpPrintf("MpSetMPData start. data: %08x (%x) size %d\n", *(u32 *)buf, buf, size);

  result = WM_SetMPDataToPort(MpCallbackSetMPDataToPort,
			      buf, (u16)size, aid_bitmap, (u16)MpGetPort(), MP_DEFAULT_PORT_PRIO);
  
  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSetMPData() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
  return TRUE;
}



/**
 * 無線デバイスを使用可能な状態にする
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestEnable(void)
{
  WMErrCode result;

  MpPrintf("MpRequestEnable() start.\n");

  result = WM_Enable(MpCallbackEnable);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEnable() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else 
    return TRUE;
}


/**
 * 無線デバイスを使用不可の状態にする
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestDisable(void)
{
  WMErrCode result;

  MpPrintf("MpRequestDisable() start.\n");

  result = WM_Disable(MpCallbackDisable);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("WL_Disable() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestDisable() error");    
    
    return FALSE;
  } else
    return TRUE;
}


/**
 * 指定チャンネルの電波使用率を測定
 *
 * @param チャンネル番号（1,7,13） 
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestSearchChannel(u32 channel)
{
  WMErrCode result;

  MpPrintf("MpRequestSearchChannel() channel %d.\n", channel);

  result = WM_MeasureChannel(MpCallbackSearchChannel, MP_MEASURE_MODE, MP_MEASURE_ED_THRESHOLD, (u16)channel, MP_MEASURE_TIME);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSearchChannel() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;  
}

  
/**
 * 親機として必要なパラメータを設定
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestSetParentParameter(void)
{
  WMErrCode result;

  WMParentParam *param = MpGetParentParameter();
  MpUserGameInfo *info = MpGetUserGameInfo();
  MpDataParentMP *parent_data = MpGetDataParentMP();

  /* MpRequestSearchChannelで探索されたチャンネル番号を指定 */
  param->channel = parent_data->channel;
  
  param->userGameInfo = (u16*)info;
  param->userGameInfoLength = (u16)MpGetUserGameInfoSize();

  MpPrintf("MpRequestSetParentParameter() channel %d start.\n", param->channel);

  result = WM_SetParentParameter(MpCallbackSetParentParameter, param);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpSetParentParameter() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 親機として活動開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestStartParent(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartParent() start.\n");

  result = WM_StartParent(MpCallbackStartParent);

  if (result != WM_ERRCODE_OPERATING) {

    MpPrintf("MpRequestStartParent() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 子機として親機のスキャン開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestStartScan(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartScan() start.\n");

  result = WM_StartScan(MpCallbackStartScan, MpGetScanParameter());

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartScan() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
   return FALSE;
  } else
    return TRUE;
}


/**
 * 子機として特定の親機のスキャン開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestStartScan2(void)
{
  WMErrCode result;

  MpPrintf("MpRequestStartScan2() start.\n");

  {
    WMScanParam *scan_param = MpGetScanParameter();
    MpDataChildMP *dcmp = MpGetDataChildMP();

    /* 接続先のMACアドレスを指定する */
    scan_param->bssid[0] = dcmp->user_list[dcmp->select].mac_vendor.u.data[0];
    scan_param->bssid[1] = dcmp->user_list[dcmp->select].mac_vendor.u.data[1];
    scan_param->bssid[2] = dcmp->user_list[dcmp->select].mac_addr.u.data[0];
    scan_param->bssid[3] = dcmp->user_list[dcmp->select].mac_addr.u.data[1];
    scan_param->bssid[4] = dcmp->user_list[dcmp->select].mac_addr.u.data[2];
    scan_param->bssid[5] = dcmp->user_list[dcmp->select].mac_addr.u.data[3];
  }
  
  result = WM_StartScan(MpCallbackStartScan2, MpGetScanParameter());

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartScan2() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
   return FALSE;
  } else
    return TRUE;
}


/**
 * 子機の親機スキャン終了
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestEndScan(void)
{
  WMErrCode result;

  MpPrintf("MpRequestEndScan() start.\n");
  
  result = WM_EndScan(MpCallbackEndScan);
  
  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEndScan() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;

  } else
    
    return TRUE;
}


/**
 * 親機への接続開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestStartConnect(void)
{
  WMErrCode result;

  MpSsidData *ssid_data = MpGetSsidData();  
  
  MpPrintf("MpRequestStartConnect() start.\n");

  result = WM_StartConnect(MpCallbackStartConnect, MpGetBssDesc(), (const u8*)ssid_data);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 接続解除
 *
 * @param 対象AID
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestDisConnect(u16 aid)
{
  WMErrCode result;

  MpPrintf("MpRequestDisConnect() start. target AID %d\n", aid);

  result = WM_Disconnect(MpCallbackDisConnect, aid);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestDisConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 複数の子機との接続解除 （親機専用）
 *
 * @param 対象AIDビットマップ
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestDisConnectChildren(u16 aid_bit)
{
  WMErrCode result;

  MpPrintf("MpRequestDisConnectChildren() start. target AID bitmap %x\n", aid_bit);

  result = WM_DisconnectChildren(MpCallbackDisConnectChildren, aid_bit);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestDisConnect() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * MP通信モード開始
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestStartMP(void)
{
  WMErrCode result;
  
  MpPrintf("MpRequestStartMP() start.\n");

  MpPrintf("MpRequestStartMP() SetPortCallback start.\n");
  result = WM_SetPortCallback(MP_DEFAULT_PORT, MpCallbackReceiveData, NULL);

  if (result == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpRequestStartMP() SetPortCallback success.\n");

  } else {

    MpPrintf("WL_RequestStartMP() SetPortCallback failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  }


  result = WM_StartMP(MpCallbackStartMP,
		      MpGetRecvBuff(),
		      (u16)MpGetRecvBuffSize(),
		      MpGetSendBuff(),
		      (u16)MpGetSendBuffSize(),
		      (u16)(MpGetParentParameter()->CS_Flag ? 0 : 1));

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestStartMP() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 無線デバイスに電源投入
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestPowerOn(void)
{
  WMErrCode result;

  MpPrintf("MpRequestPowerOn() start.\n");
  result = WM_PowerOn(MpCallbackPowerOn);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestPowerOn() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);
    return FALSE;
  } else
    return TRUE;
}


/**
 * 無線デバイスの電源OFF
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestPowerOff(void)
{
  WMErrCode result;

  MpPrintf("MpRequestPowerOff() start.\n");
  result = WM_PowerOff(MpCallbackPowerOff);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestPowerOff failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestPowerOff() error");

    return FALSE;
  } else
    return TRUE;
}



/**
 * WMをリセット WMのREADY、IDLEステート以外全てのステートからIDLEステートに移行
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestReset(void)
{
  WMErrCode result;

  MpPrintf("MpRequestReset() start.\n");
  result = WM_Reset(MpCallbackReset);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestReset() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestReset() error");
    
    return FALSE;
  } else
    return TRUE;
}


/**
 * WMを終了 WMのIDLEステートから無線機能全停止に移行
 *
 * @return エラーが発生した場合FALSEが返る
 */
BOOL MpRequestEnd(void)
{
  WMErrCode result;

  MpPrintf("MpRequestReset() start.\n");
  result = WM_End(MpCallbackEnd);

  if (result != WM_ERRCODE_OPERATING) {
    MpPrintf("MpRequestEnd() failed. ERRCODE: %x\n", result);
    MpPrintErrorCode(result);

    OS_Panic("MpRequestEnd() error");
    
    return FALSE;
  } else
    return TRUE;
}

//


