/**
 * @version "$Id: mpcallback.c,v 1.2 2006/07/19 04:48:04 mitsuhara Exp $"
 *
 * @file mpcallback.c
 * @brief 無線通信ライブラリ 状態遷移コールバック関数
 * 
 */
#include "mpconnect.h"
#include "mpcallback.h"
#include "mprequest.h"
#include "mpdata.h"
#include "mpdebug.h"


/**
 * エラー発生のためResetを行いIDLEステータスへ移行
 */
static void MpErrorToReset(void)
{
#ifdef MP_DEBUG
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_INIT,  "MpErrorToReset() bad status %d\n", MpGetStatus());
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_READY, "MpErrorToReset() bad status %d\n", MpGetStatus());
  SDK_ASSERTMSG(MpGetStatus() != MP_STATUS_STOP,  "MpErrorToReset() bad status %d\n", MpGetStatus());
#endif  
  
  MpSetStatus(MP_STATUS_ERROR);
  (void)MpRequestReset();
}


static MpMACAddData MpBssIDToMACAddData(u8 *bssid)
{
  return MpMACAddArrayToMACAddData(bssid);
}
static MpMACVendorData MpBssIDToMACVendorData(u8 *bssid)
{
  return MpMACAddArrayToMACVendorData(bssid);
}


/**
 * 終了要求のためResetを行いIDLEステータスへ移行
 */
static BOOL MpResetForEnd(void)
{
  if (MpGetRequestStatus() == MP_STATUS_END) {

    MpInternalData *id = MpGetInternalData();

    if (id->request_end_flag == FALSE) {

      MpPrintf("MpResetForEnd() request [END] to Reset\n");
      (void)MpRequestReset();
      id->request_end_flag = TRUE;
    }

    return TRUE;
  } else
    return FALSE;
}


// 指定AIDの子機を未接続状態にする
static void MpSetupDisconnectChid(u32 aid)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();
  int i;
  
  for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
    if ((parent_data->user_list[i].mac_addr.u.data32) && 
	(parent_data->user_list[i].aid == aid)) {
      parent_data->user_list[i].data_trans_ready = 0;
      parent_data->user_list[i].connect_flag = 0;
    }
  }
}  


static u32 MpGetNextChannel(void)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  MpPrintf("MpGetNextChannel() channel bitmap %x\n", parent_data->channel_bitmap);
  
  if (parent_data->channel_bitmap & 1) {
    parent_data->channel_bitmap &= ~1;
    return 1;
  } else if (parent_data->channel_bitmap & (1<<6)) {
    parent_data->channel_bitmap &= ~(1<<6);
    return 7;
  } else if (parent_data->channel_bitmap & (1<<12)) {
    parent_data->channel_bitmap &= ~(1<<12);
    return 13;
  } else
    return 0;
}


/**
 * 通信チャンネル検索初期化
 */
static BOOL MpSetupSearchChannel(void)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  parent_data->status = MP_PARENT_MP_STATUS_SEARCH_CHANNEL;

  parent_data->channel_bitmap = WM_GetAllowedChannel();

  MpPrintf("MpSetupSearchChannel() allowd channel bitmap %x\n", parent_data->channel_bitmap);
  
  if ((parent_data->channel_bitmap == 0) || (parent_data->channel_bitmap == 0x8000)) 
    return FALSE;
  else {
    parent_data->busy_ratio = MP_MEASURE_BUSYRATIO_MAX;
    parent_data->channel = 0;
    return TRUE;
  }
}


/**
 * 親機情報を設定
 */
static void MpSetupParentParameter(void)
{
  WMParentParam *param = MpGetParentParameter();
  
  MpPrintf("MpSetupParentParameter()\n");
  
  // ビーコン間隔を適度な値に設定
  param->beaconPeriod = WM_GetDispersionBeaconPeriod();

  // tempIDを設定
  param->tgid = WM_GetNextTgid();
}


/**
 * 子機のスキャン情報を設定 MpRequestStartScanの前に呼ばれる
 */
static void MpSetupScanParameter(void)
{  
  WMScanParam *scan_param = MpGetScanParameter();

  MpPrintf("MpSetupScanParameter()\n");
  
  scan_param->scanBuf = MpGetBssDesc();
  scan_param->channel = MpGetParentParameter()->channel;

  // 探索限度時間を適度な値に設定
  scan_param->maxChannelTime = WM_GetDispersionScanPeriod();

  /* ブロードキャストアドレスを指定し、NINTENDOの全機を探索するよう設定 */
  scan_param->bssid[0] = 0xff;
  scan_param->bssid[1] = 0xff;
  scan_param->bssid[2] = 0xff;
  scan_param->bssid[3] = 0xff;
  scan_param->bssid[4] = 0xff;
  scan_param->bssid[5] = 0xff;
}


static void MpSetupNextScanCannel(void)
{
  WMScanParam *scan_param = MpGetScanParameter();  
  u16 allowed_channel;
  s32 i;

  allowed_channel = WM_GetAllowedChannel();
  
  if (allowed_channel == 0) return;
  
  for (i=0; i<16; i++) {
    if (allowed_channel & (0x0001 << ((scan_param->channel + i) % 16))) {
      scan_param->channel = (u16)(((scan_param->channel + i) % 16) + 1);

      MpPrintf("MpSetupNextScanChannel() NextChannle %d \n", scan_param->channel);

      break;
    }
  }
}



/**
 * Indicationコールバック関数
 */
void MpCallbackIndicate(void *arg)
{
  WMindCallback *cb = (WMindCallback *)arg;

  MpPrintf("MpCallbackIndicate() Indication. STATECODE: %x ", cb->state);

  MpPrintStateCode((WMStateCode)cb->state);
  
  if (cb->errcode == WM_ERRCODE_FIFO_ERROR) {
    // 復旧不能なエラー
    MpPrintf("MpCallbackIndicate() error\n");
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestSetMPDataToPortのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackSetMPDataToPort(void *arg)
 {
   //WMCallback *cb = (WMCallback *)arg;
   WMPortSendCallback *cb = (WMPortSendCallback *)arg;
   
   MpPrintf("MpCallbackSetMPDataToPort() ");
   MpPrintStateCode((WMStateCode)cb->state);
   
   if (cb->errcode == WM_ERRCODE_SUCCESS) {     
     MpPrintf("MpCallbackSetMPData() MpRequestSetMPData success.\n");
  } else {

    WMPortSendCallback *cb_PortSend = (WMPortSendCallback *)cb;
    MpPrintf("MpCallbackSetMPData() MpSetMPData failed. ERRCODE: %x %x %x restBitmap: %x\n", cb->errcode,
	       cb->wlCmdID, cb->wlResult, cb_PortSend->restBitmap);
    MpPrintErrorCode((WMErrCode)cb->errcode);
  }
  //if (wcBtCallback != NULL) (*wcBtCallback) (arg);
}


/**
 * MpRequestEnableのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackEnable(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEnable() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackEnable() MpRequestEnable success.\n");

    // ステータス設定
    MpSetStatus(MP_STATUS_STOP);

    // 無線終了リクエストがあった場合はDisableに移行
    if (MpGetRequestStatus() == MP_STATUS_END) {
      MpPrintf("MpCallbackEnable() request [END] to Disable\n");
      MpRequestDisable();
      MpSetStatus(MP_STATUS_STOP);
      return;
    }
    
    // 無線デバイスに電源投入
    if (MpRequestPowerOn() == FALSE) {
      MpRequestDisable();
      MpSetStatus(MP_STATUS_STOP);
      return;
    }

  } else {

    MpPrintf("MpCallbackEnable() MpRequestEnable failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpRequestDisable();

  }
}


/**
 * MpRequestDisableのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackDisable(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackDisable() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackDisable() MpRequestDisable success.\n");

    // 無線終了リクエストがあった場合は無線ライブラリを終了
    if (MpGetRequestStatus() == MP_STATUS_END) {
      MpPrintf("MpCallbackDisable() request [END] to Finish\n");
      WM_Finish();
      MpSetStatus(MP_STATUS_END);

      // 無線ライブラリの終了を記録
      MpSetIsEnd(TRUE);
      return;
    }

    MpSetStatus(MP_STATUS_READY);

  } else {
    
    MpPrintf("MpCallbackDisable() MpRequestDisable failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackDisable() MpRequestDisable callback error\n");
  }
}


/**
 * MpRequestSearchChannelのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
void MpCallbackSearchChannel(void *arg)
{
  WMMeasureChannelCallback *cb = (WMMeasureChannelCallback *)arg;

  MpPrintf("MpCallbackSearchChannel() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpDataParentMP *parent_data = MpGetDataParentMP();

    MpPrintf("MpCallbackSearchChannel() busy ratio %d (%d ch) / %d (%d ch)\n",
	     cb->ccaBusyRatio, cb->channel, parent_data->busy_ratio, parent_data->channel);
    
    if (parent_data->busy_ratio > cb->ccaBusyRatio) {
      parent_data->busy_ratio = (u8)cb->ccaBusyRatio;
      parent_data->channel = (u8)cb->channel;
    }

    {
      /* 次のチャンネル取得 */
      u32 next_channel = MpGetNextChannel();

      MpPrintf("MpCallbackSearchChannel() next channel %d\n", next_channel);
      
      /* 次のチャンネルの電波使用率測定 */
      if (next_channel) {	
	if (MpRequestSearchChannel(next_channel) == FALSE) MpErrorToReset();
      } else {

	/* 電波使用率の低いチャンネルが見つかった場合、親機に移行 */
	if (parent_data->busy_ratio < MP_MEASURE_BUSYRATIO_MAX) {
	
	  /* 親機用のパラメータ設定 */
	  MpSetupParentParameter();

	  /* 親機パラメータ設定に移行 */ 
	  if (MpRequestSetParentParameter() == FALSE) MpErrorToReset();
	} else
	  MpErrorToReset();
      }
    }
  } else {

    MpPrintf("MpCallbackSearchChannel() MpRequestSearchChannel failed. ERRCODE: %x %x %x\n",
	     cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestSetParentParameterのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
void MpCallbackSetParentParameter(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackSetParentParameter() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackSetParentParameter() MpRequestSetParentParameter() success.\n");

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
    
    if (MpRequestStartParent() == FALSE) MpErrorToReset();
    
  } else {
    
    MpPrintf("MpCallbackSetParentParameter() MpRequestSetParentParameter failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}



/**
 * MpRequestStartParentのコールバック関数
 *
 *
 * @param arg WM非同期処理関数用構造体 
 */
void MpCallbackStartParent(void *arg)
{
  WMstartParentCallback *cb = (WMstartParentCallback *)arg;

  MpPrintf("MpCallbackStartParent() ");
  MpPrintStateCode((WMStateCode)cb->state);
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* ステータスを親機接続済みに設定 */
    MpSetStatus(MP_STATUS_PARENT);

    /* 無線終了リクエストがあった場合はResetに移行 */
    if (MpResetForEnd()) return;

    if (parent_data->status == MP_PARENT_MP_STATUS_SEARCH_CHANNEL)
      /* 親機ステータスを接続待ちに */
      parent_data->status = MP_PARENT_MP_STATUS_WAIT_CONNECT;
    
    switch (cb->state) {

    case WM_STATECODE_PARENT_START:
      MpPrintf("MpCallbackStartParent() MpRequestStartParent success.\n");
      
      if (MpRequestStartMP() == FALSE) MpErrorToReset();
      else MpSetAid(0);
      break;

    case WM_STATECODE_CONNECTED:
      MpPrintf("MpCallbackStartParent() Child Connected.\n");
      MpPrintDataParentMP(MpGetDataParentMP());
      
      if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

	MpSsidData *ssid = (MpSsidData *)cb->ssid;

	MpPrintf("MpCallbackStartParent() ParentState WAIT_CONNECT .\n");
	MpPrintf("MpCallbackStartParent() protcol %d(%d) ver %d(%d) connect id %d (%d)\n",
		 ssid->header.data0.protocol_id,
		 MpGetProtocolID(),
		 ssid->header.data0.protocol_version,
		 MpGetProtocolVersion(),
		 ssid->header.data1.connect_id,
		 MpGetConnectID());
	
	if (
	    /* プロトコルIDが一致するか */
	    (ssid->header.data0.protocol_id == MpGetProtocolID()) &&
	    /* 対応可能なバージョンか */
	    (ssid->header.data0.protocol_version <= MpGetProtocolVersion()) &&
	    /* 接続IDが一致するかを確認 */
	    (ssid->header.data1.connect_id == MpGetConnectID())) {

	  int i;
	  MpDataParentMP *parent_data = MpGetDataParentMP();	  
	  MpMACAddData mac_connect = MpBssIDToMACAddData(cb->macAddress);
	  MpMACVendorData vnd_connect = MpBssIDToMACVendorData(cb->macAddress);

	  for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	    MpMACAddData *mac_data = &parent_data->user_list[i].mac_addr;

	    /* 既出のMACアドレスの場合パス */
	    if (mac_data->u.data32 == mac_connect.u.data32) {
	      /* AIDとConnectFlagを再設定 */
	      parent_data->user_list[i].aid = cb->aid;
	      parent_data->user_list[i].connect_flag = 1;
	      break;
	    }
	    
	    /* 未記録のバッファがあれば、そこにMACアドレスとAIDを記録 */
	    if (mac_data->u.data32 == 0) {
	      parent_data->user_list[i].mac_addr.u.data32 = mac_connect.u.data32;
	      parent_data->user_list[i].mac_vendor.u.data16 = vnd_connect.u.data16;
	      parent_data->user_list[i].aid = cb->aid;
	      parent_data->user_list[i].connect_flag = 1;
	      break;			
	    }
	  }
	}
      }
      break;

    case WM_STATECODE_BEACON_SENT:
      MpPrintf("MpCallbackStartParent() Beacon sent.\n");
      break;

    case WM_STATECODE_DISCONNECTED:
      MpPrintf("MpCallbackStartParent() Child disconnected.\n");
      MpSetupDisconnectChid((u32)cb->aid);
      break;
    }
  } else {
    
    MpPrintf("MpCallbackStartParent() MpRequestStartParent failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * 指定されたbssidをMpMACAddDataに追加
 */
static BOOL MpReceiveMPAddParentAddr(WMstartScanCallback *cb, WMBssDesc *bss_desc)
{
  int i;
  MpDataChildMP *dcmp = MpGetDataChildMP();
  MpMACAddData mac_bss = MpBssIDToMACAddData(bss_desc->bssid);
  MpMACVendorData vnd_bss = MpBssIDToMACVendorData(bss_desc->bssid);

  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
    MpMACAddData *mac_data = &dcmp->user_list[i].mac_addr;
    MpMACVendorData *vnd_data = &dcmp->user_list[i].mac_vendor;
    
    /* 既出のMACアドレスの場合パス */
    if ((mac_data->u.data32 == mac_bss.u.data32) && (vnd_data->u.data16 == vnd_bss.u.data16))
      return TRUE;

    /* 未記録のバッファがあれば、そこにMACアドレスとUserNameを記録 */
    if (mac_data->u.data32 == 0) {
      dcmp->user_list[i].mac_addr.u.data32 = mac_bss.u.data32;
      dcmp->user_list[i].name = ((MpUserGameInfo*)bss_desc->gameInfo.userGameInfo)->data.name;
      dcmp->user_list[i].user_id = ((MpUserGameInfo*)bss_desc->gameInfo.userGameInfo)->data.user_id;
      dcmp->user_list[i].mac_vendor.u.data16 = vnd_bss.u.data16;
      dcmp->user_list[i].link_level = (u8)cb->linkLevel;
      return TRUE;
    }
  }

  /* 親機リストが一杯になった場合 */
  return FALSE;
}


static void MpCallbackStartScanParentNotFound(void)
{
  /* スキャンのパラメータを変更 */
  MpSetupNextScanCannel();

  /* もう一回スキャンを実行する */
  if (MpRequestStartScan() == FALSE) MpErrorToReset();
}


/**
 * MpCallbackStartScanで親機が発見された場合の処理
 *
 * @param cb WM_StartScanのコールバックの引数
 * @return 再スキャンを行う場合FALSEを返す
 */
static BOOL MpCallbackStartScanParentFound(WMstartScanCallback *cb)
{
  WMBssDesc *bss_desc = MpGetBssDesc();
  MpDataChildMP *child_data = MpGetDataChildMP();

  MpPrintf("MpCallbackStartScanParentFound() TimeCount %d\n", child_data->time_count);

  /* リセット要求のチェック */
  if (MpResetForEnd()) return TRUE;

#if 1
  {
    int find_flag = 0;
    int i;
    for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
      MpMACAddData *mac_data = &child_data->user_list[i].mac_addr;
      if (mac_data->u.data32) {
	find_flag = 1;
	break;
      }
    }
  
    /* タイムアウトのチェック */
    if ((find_flag != 0) && (child_data->time_count == 0)) {
      
      /* EndScanステータスに移行 */
      if (MpRequestEndScan() == FALSE) MpErrorToReset();
      return TRUE;
    }
  }
#endif
  
  /* 親機情報格納バッファのキャッシュを破棄 */
  DC_InvalidateRange(bss_desc, sizeof(WMbssDesc));
  
  MpPrintDataChildMP(MpGetDataChildMP());	    
  MpPrintf("MpCallbackStartScanParentFound() InfoLength %d ScanGameID %x GameID %x\n",
	   bss_desc->gameInfoLength,
	   bss_desc->gameInfo.ggid,
	   MpGetGameID());
  
  /* GameGroupIDが一致するかを確認 */
  if ((cb->gameInfoLength >= 8) && (bss_desc->gameInfo.ggid == MpGetGameID())) {
      
    MpUserGameInfo *info = (MpUserGameInfo*)bss_desc->gameInfo.userGameInfo;

    MpPrintf("MpCallbackStartScanParentFound() protcol %d(%d) ver %d(%d) connect id %d (%d)\n",
	     info->header.data0.protocol_id,
	     MpGetProtocolID(),
	     info->header.data0.protocol_version,
	     MpGetProtocolVersion(),
	     info->header.data1.connect_id,
	     MpGetConnectID());

    if (
	/* プロトコルIDが一致するか */
	(info->header.data0.protocol_id == MpGetProtocolID()) &&
	/* 対応可能なバージョンか */
	(info->header.data0.protocol_version <= MpGetProtocolVersion()) &&
    	/* 接続IDが一致するかを確認 */
	(info->header.data1.connect_id == MpGetConnectID())) {

      /* 接続対象を記憶 */
      if (MpReceiveMPAddParentAddr(cb, bss_desc)) {
	
	/* 親機検索回数の上限に達したか確認 */
	MpDataChildMP *child_data = MpGetDataChildMP();
	if (++child_data->scan_retry_count > MP_NUM_RECEIVE_MP_RETRY) {
	    
	  MpPrintf("MpCallbackStartScanParentFound() over retry count (%d/%d)\n", child_data->scan_retry_count, MP_NUM_RECEIVE_MP_RETRY);

	  /* EndScanステータスに移行 */
	  if (MpRequestEndScan() == FALSE) {
	    MpErrorToReset();
	    return TRUE;
	  }
	}
      } else {
	
	MpPrintf("MpCallbackStartScanParentFound() over parent list buff\n");
	
	/* 接続対象がいっぱいになったのでEndScanステータスに移行 */
	if (MpRequestEndScan() == FALSE) MpErrorToReset();
	return TRUE;
      }
    }
  }
  return FALSE;
}


/**
 * MpRequestStartScanのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
void MpCallbackStartScan(void *arg)
{
  WMstartScanCallback *cb = (WMstartScanCallback *)arg;
 
  MpPrintf("MpCallbackStartScan() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackStartScan() MpRequestStartScan success.\n");
    
    {
      WMBssDesc *bss_desc = MpGetBssDesc();
      MpPrintBssDesc(bss_desc);
    }
    
    /* ステータスをスキャン中に設定 */
    MpSetStatus(MP_STATUS_SCAN);    

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
    
    /* モード毎のステータス設定 */
    switch (MpGetMode()) {
    case MP_MODE_CHILD_MP :
      {
	MpDataChildMP *dcmp = MpGetDataChildMP();
	dcmp->status = MP_CHILD_MP_STATUS_SCAN_1;
      }
      break;
    }
    
    switch (cb->state) {
      
    case WM_STATECODE_PARENT_FOUND :

      MpPrintf("MpCallbackStartScan() Callback MACAddr %02x %02x %02x %02x %02x %02x \n",
		 cb->macAddress[0],
		 cb->macAddress[1],
		 cb->macAddress[2],
		 cb->macAddress[3],
		 cb->macAddress[4],
		 cb->macAddress[5]);

      
      MpPrintf("MpCallbackStartScan() Callback GGID %x \n", cb->gameInfo.ggid);      
      
      if (MpCallbackStartScanParentFound(cb) != FALSE) break;

      // Don't break here.
      // 続けてもう一回スキャンを実行
      
    case WM_STATECODE_PARENT_NOT_FOUND :
      MpCallbackStartScanParentNotFound();
      break;
	
    default :
      MpPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
      break;
    }
  } else {
    MpPrintf("WM_CallbackStartScan() WM_RequestStartScan() failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpCallbackStartScan2で親機が発見された場合の処理
 *
 * @param cb WM_StartScanのコールバックの引数
 * @return 再スキャンを行う場合FALSEを返す
 */
static BOOL MpCallbackStartScan2ParentFound(void)
{
  WMBssDesc *bss_desc = MpGetBssDesc();
  MpDataChildMP *child_data = MpGetDataChildMP();
  WMParentParam *parent_param = MpGetParentParameter();

  MpPrintf("MpCallbackStartScan2ParentFound()\n");

  /* リセット要求のチェック */
  if (MpResetForEnd()) return TRUE;

#if 0
  /* タイムアウトのチェック */
  if (child_data->time_count == 0) {

    /* EndScanステータスに移行 */
    if (MpRequestEndScan() == FALSE) {
      MpErrorToReset();
    }
    return TRUE;
  }    
#endif
  
  /* 親機情報格納バッファのキャッシュを破棄 */
  DC_InvalidateRange(bss_desc, sizeof(WMbssDesc));
  
  MpPrintDataChildMP(MpGetDataChildMP());
  
  /* GameGroupIDが一致するかを確認 */
  if ((bss_desc->gameInfoLength >= 8) && (bss_desc->gameInfo.ggid == MpGetGameID())) {
      
    MpUserGameInfo *info = (MpUserGameInfo*)bss_desc->gameInfo.userGameInfo;

    if (
	/* プロトコルIDが一致するか */
	(info->header.data0.protocol_id == MpGetProtocolID()) &&
	/* 対応可能なバージョンか */
	(info->header.data0.protocol_version <= MpGetProtocolVersion()) &&
    	/* 接続IDが一致するかを確認 */
	(info->header.data1.connect_id == MpGetConnectID())) {
    
      /*  */
      MpMACAddData mac_bss = MpBssIDToMACAddData(bss_desc->bssid);
      MpMACAddData *mac_data = &child_data->user_list[child_data->select].mac_addr;
      
      if (mac_data->u.data32 == mac_bss.u.data32) {
	
	/* EndScanステータスに移行 */
	if (MpRequestEndScan() == FALSE) MpErrorToReset();
	return TRUE;
      }
    }
  }
  return FALSE;
}
	

/**
 * MpRequestStartScan2のコールバック関数
 *
 * @param arg WM非同期処理関数用構造体 
 */
void MpCallbackStartScan2(void *arg)
{
  WMstartScanCallback *cb = (WMstartScanCallback *)arg;
 
  MpPrintf("MpCallbackStartScan2() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpDataChildMP *dcmp = MpGetDataChildMP();
    MpPrintf("MpCallbackStartScan2() MpRequestStartScan2 success.\n");

    /* モード毎のステータス設定 */
    dcmp->status = MP_CHILD_MP_STATUS_SCAN_2;

     /* ステータスをスキャン中に設定 */
    MpSetStatus(MP_STATUS_SCAN);    

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
    
    switch (cb->state) {
      
    case WM_STATECODE_PARENT_FOUND :

      if (MpCallbackStartScan2ParentFound() != FALSE) break;

      // Don't break here.
      // 続けてもう一回スキャンを実行
      MpPrintf("MpCallbackStartScan2() ReScan start.\n");

      
    case WM_STATECODE_PARENT_NOT_FOUND :
      /* スキャンのパラメータを変更 */
      MpSetupNextScanCannel();

      /* もう一回スキャンを実行する */
      if (MpRequestStartScan2() == FALSE) MpErrorToReset();
      break;
	
    default :
      MpPrintf("- Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
      break;
    }
  } else {
    MpPrintf("WM_CallbackStartScan2() WM_RequestStartScan2() failed. ERRCODE: %x %x %x\n",
	       cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestEndScanのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackEndScan(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEndScan() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("WM_CallbackEndScan() MpRequestEndScan success.\n");
    MpSetStatus(MP_STATUS_ENDSCAN);

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
    
    if (MpGetMode() == MP_MODE_CHILD_MP) {
      MpDataChildMP *dcmp = MpGetDataChildMP();

      /* 接続開始のためのスキャン後の場合 */
      if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {

	/* 子機としてコネクト開始 */
	if (MpRequestStartConnect() == FALSE) MpErrorToReset();
	else MpSetStatus(MP_STATUS_IDLE);
      }
    }    
  } else {

    MpPrintf("MpCallbackEndScan() MpCallbackEndScan failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestStartConnectのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackStartConnect(void *arg)
{
  WMstartConnectCallback *cb = (WMstartConnectCallback *)arg;

  MpPrintf("MpCallbackStartConnect() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");    
    
    /* ステータスを子機接続中に設定 */
    MpSetStatus(MP_STATUS_CHILD);    

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
    
    switch (cb->state) {
    case WM_STATECODE_CONNECT_START:
      // CONNECTEDになるのを待つので、処理なし
      break;

    case WM_STATECODE_CONNECTED:
      // 割り当てられたAIDを退避
      MpSetAid(cb->aid);

      // 接続通知
      MpSetIsConnectFlag(TRUE);
      MpSetDisconnectTrigger(FALSE);
      
#if 0      
      // 既に子機の場合は何もしない
      if (MpGetStatus() == MP_STATUS_CHILD) {
	MpPrintf("MpCallbackStartConnect() - Connected , but already child mode.\n");

      } else {

	/* MP通信を開始 */
	MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");
	if (MpRequestStartMP() == FALSE) MpErrorToReset();

      }
#else
      /* MP通信を開始 */
      MpPrintf("MpCallbackStartConnect() MpRequestStartConnect success.\n");
      if (MpRequestStartMP() == FALSE) MpErrorToReset();
#endif      
      break;

    case WM_STATECODE_BEACON_LOST:
      MpPrintf("MpCallbackStartConnect() - Beacon from parent lost.\n");
      // ビーコンを失っただけではリセットしない
      break;

    case WM_STATECODE_DISCONNECTED:
      MpPrintf("MpCallbackStartConnect() - DisConnected from parent.\n");

      if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
      MpSetIsConnectFlag(FALSE);            
#if 0      
      if (MpGetStatus() != MP_STATUS_BUSY) {
	(void)MpRequestReset();
      }
#endif      
      break;

    default:
      MpPrintf("MpCallbackStartConnect() MpRequestStartConnect failed. Invalid state code. STATECODE: %x\n", cb->state);
      MpPrintErrorCode((WMErrCode)cb->errcode);
      MpErrorToReset();
    }
    
  } else {
    
    MpPrintf("MpCallbackStartConnect() MpRequestStartConnect failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    
    if (cb->errcode == WM_ERRCODE_NO_ENTRY) MpPrintf(" ! Parent doesn't accept entry now.\n");
    if (cb->errcode == WM_ERRCODE_OVER_MAX_ENTRY) MpPrintf(" ! Over max entry of BSS group.\n");

    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


static void MpCallbackNextStateFromIdele(void)
{
  switch (MpGetMode()) {
  case MP_MODE_PARENT_MP :

#if 0    
    /* 親機用のパラメータ設定 */
    MpSetupParentParameter();

    /* 親機パラメータ設定に移行 */ 
    if (MpRequestSetParentParameter() == FALSE) MpErrorToReset();
    else MpSetStatus(MP_STATUS_IDLE);

#else
    
    /* 通信チャンネル検索初期化 */
    if ((MpSetupSearchChannel() != FALSE) &&
	(MpRequestSearchChannel(MpGetNextChannel()) != FALSE)) {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      parent_data->status = MP_PARENT_MP_STATUS_SEARCH_CHANNEL;
      MpSetStatus(MP_STATUS_IDLE);
    } else
      MpErrorToReset();
#endif    
    break;

  case MP_MODE_CHILD_MP :

    /* 子機のスキャン開始用パラメータ設定 */
    MpSetupScanParameter();

    /* 子機スキャンに移行 */
    if (MpRequestStartScan() == FALSE) MpErrorToReset();
    else MpSetStatus(MP_STATUS_IDLE);
    break;
  }
}


/**
 * MpRequestDisConnectのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackDisConnect(void *arg)
{
  WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

  MpPrintf("MpCallbackDisConnect()\n");

  /* ステータスはIDLE状態 */
  MpSetStatus(MP_STATUS_IDLE);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackDisConnect() MpRequestDisConnect success.\n");    

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;

    MpCallbackNextStateFromIdele();
    
    if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
    MpSetIsConnectFlag(FALSE);            
    
  } else {
    MpPrintf("MpCallbacDisConnect() MpRequestDisConnect failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestDisConnectChildrenのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackDisConnectChildren(void *arg)
{
  WMDisconnectCallback *cb = (WMDisconnectCallback *)arg;

  MpPrintf("MpCallbackDisConnectChildren()\n");

  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    u16 cb_bitmap = cb->disconnectedBitmap;
    int i;
    
    MpPrintf("MpCallbackDisConnectChildren() MpRequestDisConnectChildren success.\n");    
    MpPrintf("MpCallbackDisConnectChildren() disconnect bitmap %x.\n", cb_bitmap);

    for (i=1; i<16; i++) {
      u32 aid_bitmap = 1 << i;
      if (cb_bitmap & aid_bitmap)
	MpSetupDisconnectChid(i);
    }
    
    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;
  } else {
    MpPrintf("MpCallbacDisConnectChildren() MpRequestDisConnectChildren failed. ERRCODE: %x %x %x\n",
	     cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}



/**
 * MpRequestStatMPのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackStartMP(void *arg)
{
  WMstartMPCallback *cb = (WMstartMPCallback *)arg;

  MpPrintf("MpCallbackStartMP() ");
  MpPrintStateCode((WMStateCode)cb->state);

  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    if (cb->apiid == WM_APIID_START_MP) {
      if (MpResetForEnd()) return;
    }
    
    switch (MpGetMode()) {
    case MP_MODE_PARENT_MP :
      MpSetStatus(MP_STATUS_PARENT_MP); break;
    case MP_MODE_CHILD_MP :
      MpSetStatus(MP_STATUS_CHILD_MP); break;
    }
    
    switch (cb->state) {
    case WM_STATECODE_MP_START:
      MpPrintf("MpCallbackStartMP() MpRequestStartMP success.\n");
      //if (wcBtCallback != NULL) (*wcBtCallback) (arg);
      break;

    case WM_STATECODE_MPEND_IND:
      // 親機としての送受信完了時のindicate
      break;

    case WM_STATECODE_MP_IND:
      // 子機としての受信完了時のindicate
      break;
    }
  } else {

    switch (cb->errcode) {

    case WM_ERRCODE_SEND_FAILED:
    case WM_ERRCODE_TIMEOUT:
      // 送受信が完了しなかった場合のindicate
      // なにもせずに再送されるのを待つ
      break;      

    case WM_ERRCODE_INVALID_POLLBITMAP:
      // 自分宛ではない MP 通信を受け取った場合の indicate
      break;

    default:
      MpPrintf("WM_CallbackStartMP() MpRequestStartMP failed. ERRCODE: %x %x\n", cb->errcode, cb->state);
      MpErrorToReset();
    }
  }
}


static void MpUpdateSendData(void)
{
  MpTransData *td = MpGetTransData();  
  u32 send_size = MpGetSendBuffSize() - MpGetSendHeaderSize();

  /* シーケンス番号更新 */
  //td->sequence_num++;
  
  if (td->size > send_size) {
    td->size -= send_size;
    (u8*)td->data += send_size;
  } else {
    td->size = 0;
  }
}



static void MpCallbackReceiveDataSendMp(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();

  MpPrintf("MpCallbackReceiveDataSendMp() TRANS MODE SEND trans status %d\n", td->state);  
  
  /* 応答待ちか？ */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
    
    /* 受信データを復号 */
    DC_FlushRange(cb->data, cb->length);	      
    MI_CpuCopy8(cb->data, td->recv_buff, cb->length);

    if (
	/* プロトコルIDが一致するか */
	(header->data0.protocol_id == MpGetProtocolID()) &&
	/* 対応可能なバージョンか */
	(header->data0.protocol_version <= MpGetProtocolVersion())) {
      
      /* 受信データを復号 */
      MpDecodeRecvData(td->recv_buff);

      /* 通信番号が一致しているか */
      if (header->data2.sequence_num != td->seq_num) return;
      
      MpPrintSendHeader((MpSendHeader *)td->recv_buff);
      
      /* データのCRCチェック */
      if ((MpCheckRecvData(td->recv_buff)) && 

	  /* 再送要求ではない*/
	  (header->data2.control_code != MP_CONTROL_CODE_RETRY)) {

	// 受信を確認 通信成功
	MpPrintf("MpCallbackReceiveData() TRANS MODE SEND recv success !!!\n");
	td->state = MP_TRANS_STATUS_SUCCESS;
      } else {

	/* 受信失敗 （再送要求orCRCエラー）もう一度送信する*/
	td->state = MP_TRANS_STATUS_ENABLE;
      }
    }
  }
}



static void MppCallbackReceiveDataRecvMpReady(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();

  MpPrintf("MppCallbackReceiveDataRecvMpReady() MP_MODE_PARENT_MP only\n");

  if ((MpGetMode() == MP_MODE_PARENT_MP) && (td->state != MP_TRANS_STATUS_SUCCESS)) {
    
    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
    
    DC_FlushRange(cb->data, cb->length);	      
    MI_CpuCopy8(cb->data, td->recv_buff, cb->length);

    if (
	/* プロトコルIDが一致するか */
	(header->data0.protocol_id == MpGetProtocolID()) &&
	/* 対応可能なバージョンか */
	(header->data0.protocol_version <= MpGetProtocolVersion())) {
      
      /* 受信データを復号 */
      MpDecodeRecvData(td->recv_buff);
      
      /* 通信番号が一致しているか */
      if (header->data2.sequence_num != MP_SEQUENCE_READY) return;
      else {
	MpDataParentMP *parent_data = MpGetDataParentMP();
	int i;

	for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	  if (parent_data->user_list[i].aid == cb->aid) {
	    
	    MpPrintf("MppCallbackReceiveDataRecvMpReady() find child AID %d\n", cb->aid);
	    
	    parent_data->user_list[i].data_trans_ready = 1;
	    parent_data->user_list[i].data_trans_count = MP_RECV_READY_SEND_NUM;
	    
	    td->time_out = 180;

	    td->state = MP_TRANS_STATUS_ENABLE;

	    break;
	  }
	}
      }
    }
  }
}


static void MpCallbackReceiveDataRecvMp(WMPortRecvCallback *cb)
{
  MpTransData *td = MpGetTransData();
  
  MpPrintf("MpCallbackReceiveDataRecvMp() PrintHeader TRANS MODE RECV\n");
    
  /* データ転送準備状態か？ */
  if (td->seq_num == MP_SEQUENCE_READY) {

    MppCallbackReceiveDataRecvMpReady(cb);

  } else {
     
    /* 応答待ちか？ */
    if (((td->state == MP_TRANS_STATUS_WAIT) || (td->state == MP_TRANS_STATUS_READY)) && (td->resend_count == 0)) {
      
      MpSendHeader *header = (MpSendHeader *)td->recv_buff;
      
      DC_FlushRange(cb->data, cb->length);	      
      MI_CpuCopy8(cb->data, td->recv_buff, cb->length);
      
      if (
	  /* プロトコルIDが一致するか */
	  (header->data0.protocol_id == MpGetProtocolID()) &&
	  /* 対応可能なバージョンか */
	  (header->data0.protocol_version <= MpGetProtocolVersion())) {
	
	/* 受信データを復号 */
	MpDecodeRecvData(td->recv_buff);
      
	/* 通信番号が一致しているか */
	if (header->data2.sequence_num != td->seq_num) return;
	
	MpPrintSendHeader((MpSendHeader *)td->recv_buff);
	
	/* 送信可能にする */
	td->state = MP_TRANS_STATUS_ENABLE;
	
	/* データのCRCチェック */
	if (MpCheckRecvData(td->recv_buff)) {
	  
	  MpPrintf("MpCallbackReceiveData() TRANS MODE RECV recv success\n");
	  
	  /* データ送信準備 */
	  if (header->data2.sequence_num == MP_SEQUENCE_READY) {
	    MppCallbackReceiveDataRecvMpReady(cb);
	    
	  } else {
	    
	    /* 受信バッファにデータを転送 */
	    MI_CpuCopy8((u8*)td->recv_buff + header->data3.header_size, td->data, header->data3.data_size);
	  }
	  
	  /* 受信成功 成功した旨を送信する */
	  header->data2.control_code = MP_CONTROL_CODE_ACKNOWLEDGE;
	  
	  /* 成功の送信を行う回数指定 */
	  td->resend_count = MP_RECV_ACKNOWLEDGE_SEND_NUM;
	} else {
	  
	  /* CRCエラーがあったので再送要求 */
	  header->data2.control_code = MP_CONTROL_CODE_RETRY;
	}
      }
    }
  }
}


/**
 * WM_SetPortCallbackのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackReceiveData(void *arg)
{
  WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;
  
  MpPrintf("MpCallbackReceiveData() ");
  MpPrintStateCode((WMStateCode)cb->state);

#if 0  
  // 無線終了リクエストがあった場合はResetに移行
  if (MpGetRequestStatus() == MP_STATUS_END) {
    MpPrintf("MpCallbackReceiveData() request [END] to Reset\n");
    (void)MpRequestReset();
    return;
  }
#endif  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {

    MpPrintf("MpCallbackReceiveData() MpRequestStartMP Receive Data success.\n");

    switch (cb->state) {

    case WM_STATECODE_PORT_RECV:

      // データ受信
      switch (MpGetStatus()) {

      case MP_STATUS_PARENT_MP:
      case MP_STATUS_CHILD_MP:
	{
	  MpTransData *td = MpGetTransData();

	  switch (td->mode) {
	  case MP_TRANS_MODE_SEND :
	    /* データ送信モードか？ */
	    MpCallbackReceiveDataSendMp(cb); break;

	    /* データ受信モードか？ */
	  case MP_TRANS_MODE_RECV :
	    MpCallbackReceiveDataRecvMp(cb); break;
	  }
	}
	break;
      }
      break;

    case WM_STATECODE_CONNECTED:


      // 接続通知
      MpSetIsConnectFlag(TRUE);
      MpSetDisconnectTrigger(FALSE);
      break;

    case WM_STATECODE_DISCONNECTED:

      MpPrintf("MpCallbackReceiveData() Disconnect.\n");

      if (MpIsConnectFlag()) MpSetDisconnectTrigger(TRUE);
      
      // 切断通知
      switch (MpGetStatus()) {
      case MP_STATUS_PARENT_MP:       
	// main側に切断を通知
	//if (wcMpRecvCallback != NULL) wcMpRecvCallback(cb->aid, NULL, 0);
	MpSetupDisconnectChid((u32)cb->aid);
	break;

      case MP_STATUS_CHILD_MP:
	// main側に切断を通知
	MpSetIsConnectFlag(FALSE);      
	break;
      }
      break;
    }
  } else {
    MpPrintf("MpCallbackReceiveData() MpRequestStartMP Receive Data failed. ERRCODE: %x\n", cb->errcode);
  }
}


/**
 * MpRequestPowerOnのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackPowerOn(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackPowerOn() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackPowerOn() MpRequestPowerOn success.\n");

    // 無線終了リクエストがあった場合はResetに移行
    if (MpResetForEnd()) return;

    MpCallbackNextStateFromIdele();

  } else {
    MpPrintf("MpCallbackPowerOn() MpRequestPowerOn failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackPowerOn() callback error\n");

  }
}


/**
 * MpRequestPowerOffのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackPowerOff(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackPowerOff() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackPowerOff() MpRequestPowerOff success.\n");

    if (MpRequestDisable() == FALSE) {
      //OS_Panic("MpCallbackPowerOff() MpRequestDisable == FALSE\n");
      ;
    } else {

      /* ステータスを停止状態に */
      MpSetStatus(MP_STATUS_STOP);
    }
      } else {

    MpPrintf("MpCallbacPoweOff() MpRequestPowerOff failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpErrorToReset();
  }
}


/**
 * MpRequestResetのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackReset(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackReset() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackReset() MpRequestReset success.\n");

    /* AIDリセット */
    MpSetAid(0);

    //if (wcBtCallback != NULL) (*wcBtCallback)(arg);

    if (MpGetRequestStatus() == MP_STATUS_END) {
      if (MpRequestEnd() == FALSE) {
	//OS_Panic("MpCallbackReset() MpRequestReset == FALSE\n");
	;
      } else
	MpSetStatus(MP_STATUS_IDLE);
    } else {
    
      if (MpRequestPowerOff() == FALSE) {
	//OS_Panic("MpCallbackReset() MpRequestReset == FALSE\n");
	;
      } else
	MpSetStatus(MP_STATUS_IDLE);
    }
  } else {
    MpPrintf("MpCallbackReset() MpRequestReset() failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackReset() callback error\n");
  }
}


/**
 * MpRequestEndのコールバック関数
 *
 * @param arg WM非同期処理関数用構造体
 */
void MpCallbackEnd(void *arg)
{
  WMCallback *cb = (WMCallback *)arg;

  MpPrintf("MpCallbackEnd() \n");
  
  if (cb->errcode == WM_ERRCODE_SUCCESS) {
    MpPrintf("MpCallbackEnd() MpRequestEnd success.\n");
    MpSetStatus(MP_STATUS_END);

    // 無線ライブラリの終了を記録
    MpSetIsEnd(TRUE);

  } else {
    MpPrintf("MpCallbackEnd() MpRequestEnd() failed. ERRCODE: %x %x %x\n", cb->errcode, cb->wlCmdID, cb->wlResult);
    MpPrintErrorCode((WMErrCode)cb->errcode);
    MpSetStatus(MP_STATUS_ERROR);

    //OS_Panic("MpCallbackEnd() callback error\n");
  }
}


//
