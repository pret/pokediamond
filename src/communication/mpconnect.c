/**
 * @version "$Id: mpconnect.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpconnect.c
 * @brief MP無線通信ライブラリ
 * 
 */
#include "mpconnect.h"
#include "mpdata.h"
#include "mprequest.h"
#include "mpcallback.h"
#include "mpdebug.h"


/**
 * Indicationコールバック関数を設定する
 *
 * @return 処理が成功した場合はTRUEを返す、エラーの場合はFALSEを返す
 */
static BOOL MpSetIndicationCallback(void)
{
  WMErrCode result;

  MpPrintf("MpSetIndicationCallback() start.\n");

  result = WM_SetIndCallback(MpCallbackIndicate);

  if (result != WM_ERRCODE_SUCCESS) {
    MpPrintf("MpSetIndicationCallback() failed. ERRCODE: %x\n", result);
    MpSetStatus(MP_STATUS_ERROR);
    return FALSE;
  }
  
  MpPrintf("MpSetIndicationCallback() success.\n");

  return TRUE;
}


/**
 * MP通信を開始する 
 */
static void MpStartMp(void)
{
  switch (MpGetStatus()) {
  case MP_STATUS_INIT:
  case MP_STATUS_STOP:
  case MP_STATUS_READY:
    (void)MpRequestEnable();
    break;
    
  default :
    MpPrintf("MpStartMp() fail state %d\n", MpGetStatus());
    //OS_Panic("MpStartMp() state %d error\n", MpGetStatus());
    break;
  }
}


static void MpSetMpData(const void *buf, u32 size, u16 aid_bitmap)
{
  const WMParentParam *parent_param = MpGetParentParameter();

  MpPrintf("MpSetParentData() start.\n");
  
  // 送信データサイズ確認
  if (size > parent_param->parentMaxSize) {
    MpPrintf("MpSetParentData() size over (%d/%d)\n", size, parent_param->parentMaxSize);
    return;
  }
  
  MpPrintf("MpSetParentData() call MpRequestSetMPData()\n");

  DC_FlushRange((void*)buf, size);

  (void)MpRequestSetMPData(buf, size, aid_bitmap);
}


/**   
 * 送信に必要なバッファサイズを求める
 *
 * @return バッファのバイト数
 */
static u32 MpGetSendBufferSize(void)
{
  u32 parent_size;
  u32 child_size;
  u32 size;
  
  parent_size = (u32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(MP_CHILD_DATA_SIZE, MP_CONNECT_CHILD_MAX, FALSE);
  child_size = (u32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(MP_PARENT_DATA_SIZE, FALSE);
  size = (parent_size > child_size) ? parent_size : child_size;

  return size;
}


/**
 * 受信に必要なバッファサイズを求める
 *
 * @return バッファのバイト数
 */
static u32 MpGetRecvBufferSize(void)
{
  u32 parent_size;
  u32 child_size;
  u32 size;
  
  parent_size = (s32)WM_SIZE_MP_PARENT_RECEIVE_BUFFER(MP_CHILD_DATA_SIZE, MP_CONNECT_CHILD_MAX, FALSE);
  child_size = (s32)WM_SIZE_MP_CHILD_RECEIVE_BUFFER(MP_PARENT_DATA_SIZE, FALSE);
  size =(parent_size > child_size) ? parent_size : child_size;

  return size;
}


/**
 * 無線ライブラリが使用するバッファサイズを返す
 *
 * @return バイト数
 */
u32 MpGetBufferSize(void)
{
  u32 total_size = WM_SYSTEM_BUF_SIZE;
  MpPrintf("MpGetBufferSize() \n\tsystem buffer size \t%d\n", WM_SYSTEM_BUF_SIZE);
  
  total_size += MpGetSendBufferSize() << 1;
  MpPrintf("\tsend buffer size \t%d\n", MpGetSendBufferSize());
  MpPrintf("\ttrans (send) buffer size \t%d\n", MpGetSendBufferSize());

  total_size += MpGetRecvBufferSize() << 1;
  MpPrintf("\trecv buffer size \t%d\n", MpGetRecvBufferSize());
  MpPrintf("\ttrans (recv) buffer size \t%d\n", MpGetSendBufferSize());
  
  total_size += sizeof(WMBssDesc);
  MpPrintf("\tWMBssDesc size \t%d\n", sizeof(WMBssDesc));  

  total_size += sizeof(WMScanParam);
  MpPrintf("\tWMScanParam size \t%d\n", sizeof(WMScanParam));  

  total_size += 0x20;
  MpPrintf("\tfor align  size \t%d\n", 0x20);

  MpPrintf("\ttotal size \t%d\n", total_size);
  return total_size;
}


/**
 * ライブラリ初期化
 *
 * @param init_desc 初期化データ
 * @param buff ライブラリの使用するバッファのアドレスを指定 MpGetBufferSize()で取得するサイズ領域が確保されている必要がある
 */
void MpInit(MpInitDesc* init_desc, void* buff)
{
  WMParentParam *pp = MpGetParentParameter();
  MpInternalData *id = MpGetInternalData();

  /* バッファは32byteアライメントされている必要がある */
  void* org_buff = buff;
  u32 md = (u32)buff & 0x01F;
  MpPrintf("MpInit() buffer address %x ", buff);
  if (md) {
    md = 0x20 - ((u32)buff & 0x01F);
    buff = (void*)((u32)buff + md);
  }
  MpPrintf("(%x)\n", buff);

  
#if DEBUG_MP
  {
    u8 mac_addr[6];
    u32 i;
    
    OS_GetMacAddress(mac_addr);

    MpPrintf("MpInit() MAC address : ");
    for (i=0; i<sizeof(mac_addr); i++) MpPrintf("%02x ", mac_addr[i]);      
    MpPrintf("\n");

    MpPrintf("MpInit() send buffer size %d  recv buffer size %d\n",
	       MpGetSendBufferSize(),
	       MpGetRecvBufferSize());
  }
#endif
    

  /* ステータス初期化 */
  id->status = (u8)MP_STATUS_INIT;
  id->request_status = (u8)MP_STATUS_INIT;
  
  /* 通信モード初期化 */
  id->mode = (u8)MP_MODE_NONE;

  /* 通信ポート番号設定 */
  id->port = MP_DEFAULT_PORT;
  
  /* GemID設定 */
  id->ggid = MP_GGID;

  /* AID初期化 */
  id->aid = 0;
  
  /* WMライブラリ用バッファ設定 */
  id->lib_buff = buff;
  (u8*)buff += WM_SYSTEM_BUF_SIZE;
  
  /* 送信バッファ用メモリ設定 */
  id->send_buff = buff;
  (u8*)buff += id->send_buff_size = MpGetSendBufferSize();
  
  /* 受信バッファ用メモリ設定 */
  id->recv_buff = buff;
  (u8*)buff += id->recv_buff_size = MpGetRecvBufferSize();

  /* BssDesc設定 */  
  id->bss_desc = buff;
  (u8*)buff += sizeof(WMBssDesc);

  /* WMScanParam設定 */
  id->scan_parameter = buff;
  (u8*)buff += sizeof(WMScanParam);
  
  /* WM ライブラリ初期化 */
  (void)WM_Init(id->lib_buff, MP_DMA_NO);

  /* Indicationコールバック関数設定 */
  id->indication_callback_flag = MpSetIndicationCallback();

  id->connect_flag = FALSE;
  id->disconnect_trigger = FALSE;
  
  id->request_end_flag = FALSE;
  id->is_end_flag = FALSE;
  
  /* プロコトルID設定 */
  id->user_game_info.header.data0.protocol_id = MP_PROTOCOL_ID;
  
  /* プロコトルバージョン設定 */
  id->user_game_info.header.data0.protocol_version = MP_PROTOCOL_VERSION;

  /* 符号化種別設定 */
  id->user_game_info.header.data0.encode_type = MP_ENCODE_TYPE_TYCHO;
  
  id->user_game_info.header.data1.game_id = init_desc->game_id;
  id->user_game_info.header.data1.game_version = init_desc->game_version;
  id->user_game_info.header.data1.language = init_desc->language;
  id->user_game_info.header.data1.connect_id = init_desc->connect_id;
  {
    const u16* name = init_desc->name;
    const u16* user_id = init_desc->user_id;
    u32 count = 0;
    while ((name) && (count < MP_USERGAMEINFO_NAME_LENGTH)) {
      id->user_game_info.data.name.data[count] = *name;
      id->user_game_info.data.user_id.data[count] = *user_id;
      count++;
      name++;
      user_id++;
    }
  }

  /* SSIDデータ初期化 */
  id->ssid_data.header = *(MpSsidHeader*)&id->user_game_info.header;
  
  /* データ転送用構造体を初期化 */
  MpInitTransData();
  MpGetTransData()->send_buff = buff;
  (u8*)buff += id->send_buff_size;
  MpGetTransData()->recv_buff = buff;
  (u8*)buff += id->recv_buff_size;

  MpPrintf("MpInit() use buff %x \n", (u32)buff - (u32)org_buff);
  
  /* TGID設定のため最初カラ読み（初回はRTCを使用するため） */
  (void)WM_GetNextTgid();
}


/**
 * MP通信送信側プロセス
 */
static void MpProcStatusMpSend(void)
{
  MpTransData *td = MpGetTransData();

  /* 返事待ちか？ */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    if (--td->time_out > 0) return;

    /* 一定時間経過後に再送信する */ 
    MpPrintf("MpProcStatusMp() MODE_SEND TimeOut to ReSend\n");
    td->state = MP_TRANS_STATUS_ENABLE;
  }
    
  /* 送信可能か？ */
  if (td->state == MP_TRANS_STATUS_ENABLE) {
    
    u32 send_size = MP_SEND_DATA_SIZE - MpGetSendHeaderSize();
    u32 size = send_size;
    
    MP_CONTROL_CODE cc = MP_CONTROL_CODE_DATA_END;
    
    MpPrintf("MpProcStatusMp() MODE_SEND : SendData data %x size %d CC %d \n",
	     td->data, size, cc);

    /* 送信データ生成 */
    MpSetupSendData(td->send_buff, td->data, size, cc, td->seq_num);
    
    /* 送信要求 */
    MpSetMpData(td->send_buff, size + MpGetSendHeaderSize(), 0xFFFF);

    /* ステータスを返事待ちに設定 */
    td->state = MP_TRANS_STATUS_WAIT;	

    /* 返事待ちでいるフレーム数設定 */
    td->time_out = 60;
  }
}




/**
 * MP通信受信側プロセス
 */
static void MpProcStatusMpRecv(void)
{
  MpTransData *td = MpGetTransData();

#if 0  
  /* 送信可能か？ */
  if (td->state == MP_TRANS_STATUS_WAIT) {

    /* 返事待ち */ 
    if (--td->time_out > 0) return;

    MpPrintf("MpProcStatusMp() MODE_RECV TimeOut to ReSend\n");
    td->state = MP_TRANS_STATUS_ENABLE;
  }
#endif

  /* 送信可能か？ */
  if (td->state == MP_TRANS_STATUS_ENABLE) {
  
    /* データ送信シーケンスの場合の処理 */
    if (td->seq_num == (u8)MP_SEQUENCE_READY) {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      int i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	if (parent_data->user_list[i].data_trans_count) {
	  MP_CONTROL_CODE cc = MP_CONTROL_CODE_ACKNOWLEDGE;

	  u16 send_bitmap = (u16)(1 << parent_data->user_list[i].aid);
	  
	  MpPrintf("MpProcStatusMp() MODE_RECV : DequenceReady SendData data %x size 0 aid %d, ControlCode %s \n",
		   td->data, parent_data->user_list[i].aid, MpPrintControlCode(cc));      
	  
	  /* 送信データ生成 */
	  MpSetupSendData(td->send_buff, td->data, 0, cc, MP_SEQUENCE_READY);
	
	  /* 送信要求 */
	  MpSetMpData(td->send_buff, MpGetSendHeaderSize(), send_bitmap);
	  
	  parent_data->user_list[i].data_trans_count--;
	  return;
	}
      }

      if (--td->time_out == 0)
	/* 全ての返信に応答終了 */
	td->state = MP_TRANS_STATUS_SUCCESS;
      
    } else {

      /* 通常の受信処理 */
      u32 send_size = MpGetSendBufferSize() - MpGetSendHeaderSize();
      MP_CONTROL_CODE cc;
      
      MpSendHeader *header = (MpSendHeader *)td->recv_buff;
      
      /* MpCallbackReceiveDataRecvMp()で設定された通信の制御コード取得 */
      cc = (MP_CONTROL_CODE)header->data2.control_code;
      
      // 通信成功の場合
      if (cc == MP_CONTROL_CODE_ACKNOWLEDGE) {
	
	// 成功の連絡が全て終了した時点でMP_TRANS_STATUS_SUCCESSにする
	if (td->resend_count == 0) {
	  td->state = MP_TRANS_STATUS_SUCCESS;
	  return;
	} else {
	  td->resend_count--;
	}
      }
      
      MpPrintf("MpProcStatusMp() MODE_RECV : SendData data %x size 0 ControlCode %s \n",
	       td->data, MpPrintControlCode(cc));      
      
      /* 送信データ生成 */
      MpSetupSendData(td->send_buff, td->data, 0, cc, td->seq_num);
      
      /* 送信要求 */
      MpSetMpData(td->send_buff, MpGetSendHeaderSize(), 0xFFFF);
    }
  }
  
}

static void MpProcStatusMp(void)
{
  MpTransData *td = MpGetTransData();

  switch (td->mode) {
  case MP_TRANS_MODE_SEND :
    MpProcStatusMpSend(); break;

  case MP_TRANS_MODE_RECV :
    MpProcStatusMpRecv(); break;
  }
}


static void MpProcChildMP(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  /* 内部ステータスによって処理を分岐 */
  switch (MpGetStatus()) {    
    
  case MP_STATUS_SCAN :
    // タイムアウト用カウンタ更新
    if (dcmp->time_count) dcmp->time_count--;
    break;

  case MP_STATUS_CHILD_MP :
    MpProcStatusMp();
    break;
  default :
    break;
    
  }  
}

static void MpProcParentMP(void)
{
  /* 内部ステータスによって処理を分岐 */
  switch (MpGetStatus()) {

  case MP_STATUS_PARENT_MP :
    MpProcStatusMp();
    break;

  default :
    break;
  }  
}



void MpProc(void)
{ 
  if (MpGetStatus() == MP_STATUS_END) return;

  //MpPrintf("Proc() Link %d\n", (u32)WM_GetLinkLevel());
  MpPrintf("AID %d Connect %d / %d \n", MpGetAid(), MpGetDataTransListNum(), MpGetConnectListNum());

  
  if (MpGetRequestStatus() == MP_STATUS_END) {
    if (MpGetStatus() == MP_STATUS_ENDSCAN) MpRequestReset();
    return;
  }
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
    MpProcChildMP(); break;

  case MP_MODE_PARENT_MP :
    MpProcParentMP(); break;
    
  default :
    {
      MpInternalData *id = MpGetInternalData();  

      /* 内部ステータスによって処理を分岐 */
      switch (MpGetStatus()) {
	
      case MP_STATUS_INIT :	/* 初期化後の状態 何もしない */
	//MpPrintf("MpProc() status INIT\n");
	break;
      
      case MP_STATUS_READY :	/*  */
	//MpPrintf("MpProc() status READY\n");
	break;
	
      case MP_STATUS_BUSY:
	//MpPrintf("MpProc() status BUSY\n");    
	break;
	
      case MP_STATUS_SCAN :
      case MP_STATUS_ENDSCAN :
      
      break;
      
      case MP_STATUS_PARENT:
	break;
	
      case MP_STATUS_CHILD:
	//MpPrintf("MpProc() status CHILD\n");    
	break;
	
      default :
	//OS_Printf("MpProc() unknown status %d\n", MpGetStatus());
	;
      }
    }
  }
}


/**
 * 親機として通信開始
 */
void MpRequestParent()
{
  // 親機専用データ初期化
  MpInitDataParentMP();

  // MP通信開始（親機）  
  MpSetMode(MP_MODE_PARENT_MP);
  MpStartMp();  
}


/**
 * 子機として親機のスキャン開始
 */
void MpRequestScan()
{
  // 子機専用データ初期化
  MpInitDataChildMP();

  // MP通信開始（子機）
  MpSetMode(MP_MODE_CHILD_MP);
  MpStartMp();  
}


/**
 * 親機リストの最大数を取得
 *
 * @return 最大数
 */
static u32 MpGetParentListMax()
{
  return MP_SIZE_RECEIVE_MP_PARENT_LIST;
}


/**
 * 発見された親機の数を返す
 *
 * @return 親機の数
 */
static u32 MpGetParentListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_CHILD_MP)
    OS_Panic("MpGetParentListNum() illegal mode (%d)\n", mode);
#endif

  /* MP通信（子機）モードの場合 */
  if (mode == MP_MODE_CHILD_MP) {
    MpDataChildMP *dcmp = MpGetDataChildMP();

    /* スキャン中／スキャン終了のステータスの場合のみ有効 */
    if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) {

      /* MACアドレスが記録されている数を計数 */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

	if (dcmp->user_list[i].mac_addr.u.data32 != 0) list_count++;
      }
    }  
  }

  MpPrintf("MpGetParentListNum() find parent %d\n", list_count);
  
  return list_count;
}


/**
 * 指定番号の親機と接続可能か調べる
 *
 * @param 親機番号
 * @return 可能な場合TRUEが返る
 */
BOOL MpGetConnectParentEnable(u32 num)
{
  if ((MpGetMode() == MP_MODE_CHILD_MP) && (MpGetStatus() == MP_STATUS_ENDSCAN)) {
    MpDataChildMP *dcmp = MpGetDataChildMP();
    if ((dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) && (dcmp->user_list[num].mac_addr.u.data32))
      return TRUE;
  }

  return FALSE;
}


/**
 * 指定番号の親機と接続する 接続不可能の場合は何もしない
 *
 * @param 親機番号
 */
void MpConnectParent(u32 num)
{
  /* MP通信（子機）モードの場合 */
  if ((MpGetMode() == MP_MODE_CHILD_MP) && (MpGetStatus() == MP_STATUS_ENDSCAN)) {
    
    MpDataChildMP *dcmp = MpGetDataChildMP();

    if ((dcmp->status == MP_CHILD_MP_STATUS_SCAN_1) && (dcmp->user_list[num].mac_addr.u.data32)) {
    
      dcmp->select = (u8)num;
      dcmp->time_count = 120;

      //if (MpRequestStartScan2() == FALSE) MpErrorToReset();
      MpRequestStartScan2();
      
    }
  }  
}


/**
 * 親機との接続を切る 接続していない場合は何もしない
 */
void MpDisConnectParent(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {
    if (MpIsConnectFlag()) MpRequestDisConnect(0);
  }
}


/**
 * 全ての子機との接続を切る 接続していない場合は何もしない
 */
void MpDisConnectChild(void)
{
  MpRequestDisConnectChildren(0xFFFF);
}



/**
 * 接続済みの親機番号を返す 接続状態にない場合はMP_ERROR_CODEが返る
 *
 * @return 親機番号
 */
u32 MpGetConnectParentNum(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  if (dcmp->status == MP_CHILD_MP_STATUS_SCAN_2) {
    return dcmp->select;
  }

  return MP_ERROR_CODE;
}


/**
 * 指定接続番号の親機の名前を取得
 *
 * @param num 親機番号
 * @return 名前（u16*）
 */
u16* MpGetParentListName(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return (u16*)&dcmp->user_list[num].name;
}


/**
 * 指定接続番号の親機のユーザーIDを取得
 *
 * @param num 親機番号
 * @return 名前（u16*）
 */
u16* MpGetParentListUserID(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return (u16*)&dcmp->user_list[num].user_id;
}


/**
 * 指定接続番号の親機のMACアドレスを取得
 *
 * @param num 親機番号
 * @return MACアドレス
 */
static u32 MpGetParentListMacAddr(u32 num)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();
  return dcmp->user_list[num].mac_addr.u.data32;
}


/**
 * 子機リストの最大数を取得
 *
 * @return 最大数
 */
static u32 MpGetChildListMax()
{
  return MP_SIZE_RECEIVE_MP_CHILD_LIST;
}


/**
 * 接続された子機の数を返す
 *
 * @return 子機の数
 */
static u32 MpGetChildListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_PARENT_MP) OS_Panic("MpGetChildListNum() illegal mode (%d)\n", mode);
#endif

  /* MP通信（親機）モードの場合 */
  if (mode == MP_MODE_PARENT_MP) {
    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* 接続待ち中ステータスの場合のみ有効 */
    if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

      /* MACアドレスが記録されている数を計数 */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

	if ((parent_data->user_list[i].mac_addr.u.data32 != 0) && 
	    (parent_data->user_list[i].connect_flag))
	  list_count++;
      }
    }  
  }

  MpPrintf("MpGetChildListNum() find child %d\n", list_count);
  
  return list_count;
}


/**
 * データ通信可能な子機の数を返す
 *
 * @return 子機の数
 */
static u32 MpGetEnableChildListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 list_count = 0;
  
#if DEBUG_MP
  if (mode != MP_MODE_PARENT_MP) OS_Panic("MpGetEnableChildListNum() illegal mode (%d)\n", mode);
#endif

  /* MP通信（親機）モードの場合 */
  if (mode == MP_MODE_PARENT_MP) {
    MpDataParentMP *parent_data = MpGetDataParentMP();

    /* 接続待ち中ステータスの場合のみ有効 */
    if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

      /* MACアドレスが記録されている数を計数 */ 
      u32 i;
      for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
	if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	    (parent_data->user_list[i].data_trans_ready != 0) && 
	    (parent_data->user_list[i].connect_flag))
	  list_count++;
      }
    }  
  }
  
  MpPrintf("MpGetEnableChildListNum() find child %d\n", list_count);
  
  return list_count;
}


static u32 MpConnectNumToTransNum(u32 num)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();
  u32 list_count = 0;
  u32 i;

  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
    if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	(parent_data->user_list[i].data_trans_ready != 0) &&
	(parent_data->user_list[i].connect_flag)) {
      
      if (list_count == num) return i;
      list_count++;
    }
  }
  return 0;
}


/**
 * 指定接続番号の子機のMACアドレスを取得
 *
 * @param num 子機番号
 * @return MACアドレス
 */
static u32 MpGetChildListMacAddr(u32 num)
{
  MpDataParentMP *dpmp = MpGetDataParentMP();
  return dpmp->user_list[num].mac_addr.u.data32;
}


/**
 * 指定番号以外の子機との接続を切る 接続していない場合は何もしない
 *
 * @param num 子機番号
 */
void MpConnectOnlyChild(u32 num)
{
  MpDataParentMP *parent_data = MpGetDataParentMP();

  MpPrintf("MpConnectOnlyChild() child num %d AID %d\n", num, parent_data->user_list[num].aid);
  
  if (parent_data->status == MP_PARENT_MP_STATUS_WAIT_CONNECT) {

    u32 aid_bit = 0xFFFFFFFF;

    u32 mask = 1 << (parent_data->user_list[num].aid);

    aid_bit ^= mask;

    MpRequestDisConnectChildren((u16)aid_bit);
  }
}


/**
 * 指定MACアドレスの子機以外との接続を切る 接続していない場合は何もしない
 *
 * @param num 子機のMACアドレス
 */
void MpDataTransOnlyChild(u32 only_addr)
{
#if 1
  MpDataParentMP *parent_data = MpGetDataParentMP();
  u32 list_count = 0;
  u32 i;

  u32 aid_bit = 0;

  MpPrintf("MpDataTransOnlyChild() addr %x\n");
  
  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {

    MpPrintf("No %02d addr %x trans ready %d connect flag %d aid %d\n",
	     i,
	     parent_data->user_list[i].mac_addr.u.data32,
	     parent_data->user_list[i].data_trans_ready,
	     parent_data->user_list[i].connect_flag,
	     parent_data->user_list[i].aid);

    if ((parent_data->user_list[i].mac_addr.u.data32 != 0) &&
	(parent_data->user_list[i].mac_addr.u.data32 != only_addr) && 
	//(parent_data->user_list[i].data_trans_ready != 0) &&
	(parent_data->user_list[i].connect_flag)) {

      u32 mask = 1 << (parent_data->user_list[i].aid);
      aid_bit |= mask;
    }
  }

  MpPrintf("MpDataTransOnlyChild() disconnect aid bitmap %x\n", aid_bit);

  if (aid_bit) MpRequestDisConnectChildren((u16)aid_bit);

#else  
  MpConnectOnlyChild(MpConnectNumToTransNum(num));
#endif
}


/**
 * リンク強度を取得
 *
 * @return リンク強度
 */
u32 MpGetConnectLinkLevel(void)
{
  MpInternalData *id = MpGetInternalData();
  
  if (!id->is_end_flag)
    return (u32)WM_GetLinkLevel();
  else
    return 0;
}


/**
 * 接続可能な最大数を取得
 *
 * @return 最大数
 */
u32 MpGetConnectListMax(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = MpGetParentListMax();
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetChildListMax();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * 接続された数を返す
 *
 * @return 接続数
 */
u32 MpGetConnectListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = MpGetParentListNum();
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetChildListNum();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * データ通信可能な数を返す
 *
 * @return 接続数
 */
u32 MpGetDataTransListNum(void)
{
  MP_MODE mode = MpGetMode();
  u32 num;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    num = 0;
    break;
  case MP_MODE_PARENT_MP :
    num = MpGetEnableChildListNum();
    break;
  default :
    num = 0;
    break;
  }
  return num;
}


/**
 * 指定接続番号のMACアドレスを取得
 *
 * @param num 接続番号
 * @return MACアドレス
 */
u32 MpGetListMacAddr(u32 num)
{
  MP_MODE mode = MpGetMode();
  u32 mac;
  
  switch (mode) {
  case MP_MODE_CHILD_MP :
    mac = MpGetParentListMacAddr(num);
    break;
  case MP_MODE_PARENT_MP :
    mac = MpGetChildListMacAddr(num);
    break;
  default :
    mac = 0;
    break;
  }
  return mac;
}


/**
 * 指定データ通信番号のMACアドレスを取得
 *
 * @param num データ通信番号
 * @return MACアドレス
 */
u32 MpGetTransMacAddr(u32 num)
{
  return MpGetListMacAddr(MpConnectNumToTransNum(num));
}


/**
 * データの送信準備を行う
 */
void MpSetSendRedy(void)
{
  MpTransData *trans_data = MpGetTransData();
  MpUserGameInfo *user_game_info = MpGetUserGameInfo();

  MpPrintf("MpSetSendReady() state %d \n", MpGetStatus());

  if (MpGetMode() == MP_MODE_CHILD_MP) {
  
    trans_data->mode     = MP_TRANS_MODE_SEND;
    trans_data->state    = MP_TRANS_STATUS_ENABLE;
    trans_data->org_data = (void*)&user_game_info->data;
    trans_data->data     = (void*)&user_game_info->data;
    trans_data->org_size = 0;
    trans_data->size     = 0;
    trans_data->time_out = 120;  
    trans_data->resend_count = 0;  
    trans_data->seq_num  = (u8)MP_SEQUENCE_READY;  
  }
}


/**
 * ユーザーデータの送信を行う
 */
void MpSetSendUserData(void)
{
  MpTransData *trans_data = MpGetTransData();
  MpUserGameInfo *user_game_info = MpGetUserGameInfo();
  
  trans_data->mode     = MP_TRANS_MODE_SEND;
  trans_data->state    = MP_TRANS_STATUS_ENABLE;
  trans_data->org_data = (void*)&user_game_info->data;
  trans_data->data     = (void*)&user_game_info->data;
  trans_data->org_size = sizeof(MpUserGameInfoData);
  trans_data->size     = sizeof(MpUserGameInfoData);
  trans_data->time_out = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num  = (u8)MP_SEQUENCE_USER_DATA;  
}


/**
 * データを送信を行う
 *
 * @param data データ送信バッファ
 * @param size 送信サイズ
 * @param seq_num 通信番号
 */
void MpSetSendData(void *data, u32 size, u32 seq_num)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetSendData() state %d data %x size %d sequence %d\n", MpGetStatus(), data, size, seq_num);

  if ((MP_SEQUENCE)seq_num > MP_SEQUENCE_APP_END) {
    MpPrintf("MpSetSendData() sequence %d over\n", seq_num);
    return;
  }
  
  trans_data->mode     = MP_TRANS_MODE_SEND;
  trans_data->state    = MP_TRANS_STATUS_ENABLE;
  trans_data->org_data = data;
  trans_data->data     = data;
  trans_data->org_size = size;
  trans_data->size     = size;
  trans_data->time_out = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num  = (u8)seq_num;  
}


/**
 * ユーザーデータの受信バッファサイズを返す
 *
 * @return バイト数
 */
u32 MpGetUserDataSize(void)
{
  return sizeof(MpUserGameInfoData);
}


/**
 * データの受信準備を行う
 */
void MpSetRecvReady(void)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvReady() state %d \n", MpGetStatus());

  if (MpGetMode() == MP_MODE_PARENT_MP) {
  
    trans_data->mode         = MP_TRANS_MODE_RECV;
    trans_data->state        = MP_TRANS_STATUS_READY;
    trans_data->org_data     = NULL;
    trans_data->data         = NULL;
    trans_data->org_size     = 0;
    trans_data->size         = 0;
    trans_data->time_out     = 120;  
    trans_data->resend_count = 0;  
    trans_data->seq_num  = (u8)MP_SEQUENCE_READY;  
  }
}


/**
 * ユーザーデータの受信を行う 受信バッファサイズはsizeof(MpUserGameInfoData)
 *
 * @param data データ受信バッファ
 */
void MpSetRecvUserData(void *data)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvUserData() state %d data %x size %d \n", MpGetStatus(), data, sizeof(MpUserGameInfoData));
  
  trans_data->mode         = MP_TRANS_MODE_RECV;
  trans_data->state        = MP_TRANS_STATUS_READY;
  trans_data->org_data     = data;
  trans_data->data         = data;
  trans_data->org_size     = sizeof(MpUserGameInfoData);
  trans_data->size         = 0;
  trans_data->time_out     = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num      = (u8)MP_SEQUENCE_USER_DATA;  
}


/**
 * データを受信を行う
 *
 * @param data データ受信バッファ
 * @param size 受信サイズ
 * @param seq_num 通信番号
 */
void MpSetRecvData(void *data, u32 size, u32 seq_num)
{
  MpTransData *trans_data = MpGetTransData();

  MpPrintf("MpSetRecvData() state %d data %x size %d sequence %d\n", MpGetStatus(), data, size, seq_num);

  if ((MP_SEQUENCE)seq_num > MP_SEQUENCE_APP_END) {
    MpPrintf("MpSetRecvData() sequence %d over\n", seq_num);
    return;
  }
  
  trans_data->mode         = MP_TRANS_MODE_RECV;
  trans_data->state        = MP_TRANS_STATUS_READY;
  trans_data->org_data     = data;
  trans_data->data         = data;
  trans_data->org_size     = size;
  trans_data->size         = 0;
  trans_data->time_out     = 120;  
  trans_data->resend_count = 0;  
  trans_data->seq_num      = (u8)seq_num;  
}


/**
 * 送信したデータのサイズを取得する
 *
 * @return 送信バイト数
 */
u32 MpGetSendDataSize(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->mode == MP_TRANS_MODE_SEND) size = td->org_size - td->size;
	}
	break;
      }
      
    }
    break;
  }
    
  return size;
}


/**
 * 受信したデータのサイズを取得する
 *
 * @return 送信バイト数
 */
u32 MpGetRecvDataSize(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->mode == MP_TRANS_MODE_RECV) size = td->size;
	}
	break;
      }
      
    }
    break;
  }
    
  return size;
}


/**
 * データ送信が終了したか調べる
 *
 * @return 終了している場合TRUEが返る
 */
BOOL MpIsSendDataEnd(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();
	  if (td->state == MP_TRANS_STATUS_SUCCESS) return TRUE;
	}
	break;
      }
      
    }
    break;
  }
    
  return FALSE;
}


/**
 * データ受信が終了したか調べる
 *
 * @return 終了している場合TRUEが返る
 */
BOOL MpIsRecvDataEnd(void)
{
  u32 size = 0;
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();

	  MpPrintf("MpIsRecvDataEnd() trans_state %d \n", td->state);

	  if (td->state == MP_TRANS_STATUS_SUCCESS) return TRUE;
	}
	break;
      }
      
    }
    break;
  }
    
  return FALSE;
}


BOOL MpIsRecvDataAcknowledge(void)
{
  
  switch (MpGetMode()) {
  case MP_MODE_CHILD_MP :
  case MP_MODE_PARENT_MP :
    {
      switch (MpGetStatus()) {
      case MP_STATUS_CHILD_MP :
      case MP_STATUS_PARENT_MP :
	{
	  MpTransData *td = MpGetTransData();

	  if (td->state == MP_TRANS_STATUS_ENABLE) {
	    MpSendHeader *header = (MpSendHeader *)td->recv_buff;
	    if ((header->data2.control_code == MP_CONTROL_CODE_ACKNOWLEDGE) &&
		(td->resend_count < MP_RECV_ACKNOWLEDGE_SEND_NUM))
	      return TRUE;
	  }
	}
	break;
      }
    }
    break;
  }
  return FALSE;
}
	      

/**
 * 接続されている状態か調べる
 *
 * @return 接続があればTRUEを返す
 */
BOOL MpIsConnect(void)
{
  switch (MpGetMode()) {
  case MP_MODE_PARENT_MP :
    {
      MpDataParentMP *parent_data = MpGetDataParentMP();
      int i;
      
      for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
	if (parent_data->user_list[i].mac_addr.u.data32) { 
	  if (parent_data->user_list[i].connect_flag) return TRUE;
	}
      }
      return FALSE;
    }
    break;
  default :
    return MpIsConnectFlag();
    break;
  }
}


/**
 * データ転送可能な状態か調べる
 *
 * @return 接続があればTRUEを返す
 */
BOOL MpIsDataTrans(void)
{
  if (MpGetDataTransListNum()) return TRUE;
  else return FALSE;
}


/**
 * 無線ライブラリ停止要求
 */
void MpRequestClose(void)
{
  MpPrintf("MpRequestClose state %d\n", MpGetStatus());

  //MpSetEndRequest(TRUE);  
  MpSetRequestStatus(MP_STATUS_END);
  
  switch (MpGetStatus()) {
  case MP_STATUS_INIT :
  case MP_STATUS_READY :
    WM_Finish();
    MpSetIsEnd(TRUE);
    break;
  case MP_STATUS_CHILD :
    if (!MpIsConnectFlag()) {
      MpInternalData *id = MpGetInternalData();
      MpRequestReset();
      id->request_end_flag = TRUE;
    }
    break;
  }
}


/**
 * 無線ライブラリが停止したか調べる
 *
 * @return 停止状態になった場合TRUEが返る
 */
BOOL MpIsEnd(void)
{
  MpInternalData *id = MpGetInternalData();
  return id->is_end_flag;
}


//


