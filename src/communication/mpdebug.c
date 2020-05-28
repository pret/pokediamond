/**
 * @version "$Id: mpdebug.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpdebug.c
 * @brief MP無線通信デナッグ用関数
 * 
 */
#include "mpdebug.h"

#if DEBUG_MP 


/**
 * 指定ステータスを文字列で返す
 */
const char* MpGetStatusString(MP_STATUS status)
{
  static const char* string_tbl[MP_STATUS_MAX] = {
    "Init",
    "Ready",
    "Stop",
    "Idle",
    "FatalError",
    "Busy",
    "Scan(Child)",
    "EndScan(Child)",
    "Connected(Parent)",
    "Connected(Child)",
    "MP(Parent)",
    "MP(Child)",
    "End",
  };

  return string_tbl[status];
}


/**
 * エラーコードを表示する
 *
 * @param WMが返すエラーコード
 */
void MpPrintErrorCode(WMErrCode code)
{
  switch (code) {
  case WM_ERRCODE_SUCCESS :
    MpPrintf("[SUCCES] \n"); break;   

  case WM_ERRCODE_FAILED :
    MpPrintf("[FAILD] \n"); break;   

  case WM_ERRCODE_OPERATING :
    MpPrintf("[OPERATING] \n"); break;   

  case WM_ERRCODE_ILLEGAL_STATE :
    MpPrintf("[ILLEGAL_STATE] \n"); break;   

  case WM_ERRCODE_WM_DISABLE :
    MpPrintf("[WM_DISABLE] \n"); break;   
#if 0  /* WM_ERRCODE_NO_KEYSET == WM_ERRCODE_NO_DATASET */
  case WM_ERRCODE_NO_KEYSET :
    MpPrintf("[NO_KEYSET] \n"); break;   
#endif
  case WM_ERRCODE_NO_DATASET :
    MpPrintf("[NO_KEYSET/NO_DATASET] \n"); break;   

  case WM_ERRCODE_INVALID_PARAM :
    MpPrintf("[INVALID_PARAM] \n"); break;   
    
  case WM_ERRCODE_NO_CHILD :
    MpPrintf("[NO_CHILD] \n"); break;   

  case WM_ERRCODE_FIFO_ERROR :
    MpPrintf("[FIFO_ERROR] \n"); break;   

  case WM_ERRCODE_TIMEOUT :
    MpPrintf("[TIMEOUT] \n"); break;   

  case WM_ERRCODE_SEND_QUEUE_FULL :
    MpPrintf("[SEND_QUEUE_FULL] \n"); break;   

  case WM_ERRCODE_NO_ENTRY :
    MpPrintf("[NO_ENTRY] \n"); break;   

  case WM_ERRCODE_OVER_MAX_ENTRY :
    MpPrintf("[OVER_MAX_ENTRY] \n"); break;   

  case WM_ERRCODE_INVALID_POLLBITMAP :
    MpPrintf("[INVALID_POLLBITMAP] \n"); break;   

  case WM_ERRCODE_NO_DATA :
    MpPrintf("[NO_DATA] \n"); break;   

  case WM_ERRCODE_SEND_FAILED :
    MpPrintf("[SEND_FAILED] \n"); break;   

  default :
    MpPrintf("[UNKNOWN (%d)] \n", code); break;   
  }
}


/**
 * ステータスコードを表示する
 *
 * @param WMが返すステータスコード
 */
void MpPrintStateCode(WMStateCode code)
{
  switch (code) {
  case WM_STATECODE_PARENT_START :
    MpPrintf("[PARENT_START] \n"); break;   

  case WM_STATECODE_BEACON_SENT :
    MpPrintf("[BEACON_SENT] \n"); break;   

  case WM_STATECODE_SCAN_START :
    MpPrintf("[SCAN_START] \n"); break;   

  case WM_STATECODE_PARENT_NOT_FOUND :
    MpPrintf("[PARENT_NOT_FOUND] \n"); break;   

  case WM_STATECODE_PARENT_FOUND :
    MpPrintf("[PARENT_FOUND] \n"); break;   

  case WM_STATECODE_CONNECT_START :
    MpPrintf("[CONNECT_START] \n"); break;   

  case WM_STATECODE_CHILD_CONNECTED :
    MpPrintf("[BEACON_SENT] \n"); break;   

  case WM_STATECODE_DISCONNECTED :
    MpPrintf("[DISCONNECTED] \n"); break;   

  case WM_STATECODE_MP_START :
    MpPrintf("[MP_START] \n"); break;   

  case WM_STATECODE_MPEND_IND :
    MpPrintf("[MPEND_IND] \n"); break;   

  case WM_STATECODE_MP_IND :
    MpPrintf("[MP_IND] \n"); break;   

  case WM_STATECODE_MPACK_IND :
    MpPrintf("[MPACK_IND] \n"); break;   

  case WM_STATECODE_DCF_START :
    MpPrintf("[DCF_START] \n"); break;   

  case WM_STATECODE_DCF_IND :
    MpPrintf("[DCF_IND] \n"); break;   

  case WM_STATECODE_BEACON_RECV :
    MpPrintf("[BEACON_RECV] \n"); break;   

  case WM_STATECODE_DISASSOCIATE :
    MpPrintf("[DISASSOCIATE] \n"); break;   

  case WM_STATECODE_REASSOCIATE :
    MpPrintf("[REASSOCIATE] \n"); break;   

  case WM_STATECODE_AUTHENTICATE :
    MpPrintf("[AUTHENTICATE] \n"); break;   

  case WM_STATECODE_PORT_SEND :
    MpPrintf("[PORT_SEND] \n"); break;   

  case WM_STATECODE_PORT_RECV :
    MpPrintf("[PORT_RECV] \n"); break;   

  case WM_STATECODE_FIFO_ERROR :
    MpPrintf("[FIFO_ERROR] \n"); break;   

  default :
    MpPrintf("[UNKNOWN (%d)] \n", code); break;   
    
  }
}

/**
 * WMBssDescの内容を表示する
 */
void MpPrintBssDesc(WMBssDesc *desc)
{
  u32 i;

  DC_InvalidateRange(desc, sizeof(WMbssDesc));
  
  MpPrintf("MpPrintBssDesc(desc %x) \n", desc);
  MpPrintf("\t length %d (%d byte)\n", desc->length, desc->length*2);
  MpPrintf("\t bssid ");
  for (i=0; i<WM_SIZE_BSSID; i++) MpPrintf("%02x ", desc->bssid[i]);
  MpPrintf("\n");
  MpPrintf("\t game info length %d\n", desc->gameInfoLength);
  MpPrintf("\t ggid %08x\n", desc->gameInfo.ggid);
  MpPrintf("\t tgid %08x\n", desc->gameInfo.tgid);
  MpPrintf("\t user game info length %d \n", desc->gameInfo.userGameInfoLength);
  MpPrintf("\t attribute %02x \n", desc->gameInfo.gameNameCount_attribute);
  MpPrintf("\t parent max size %d \n", desc->gameInfo.parentMaxSize);
  MpPrintf("\t child  max size %d \n", desc->gameInfo.childMaxSize);
}


/**
 * MpDataChildMPの内容を表示する
 */
void MpPrintDataChildMP(MpDataChildMP *dcmp)
{
  u32 i;
  
  MpPrintf("MpPrintDataChildMP(data %x) \n", dcmp);

  MpPrintf("\t RetryCount %d\n", dcmp->scan_retry_count);

  for (i=0; i<MP_SIZE_RECEIVE_MP_PARENT_LIST; i++) {
    u32 j;
    MpPrintf("\t No%d : ", i);
    for (j=0; j<MP_SIZE_MAC_DATA; j++) MpPrintf("%02x ", dcmp->user_list[i].mac_addr.u.data[j]);
    MpPrintf("  Link %d\n", dcmp->user_list[i].link_level);
  }
}


/**
 * MpDataParentMPの内容を表示する
 */
void MpPrintDataParentMP(MpDataParentMP *dpmp)
{
  u32 i;
  
  MpPrintf("MpPrintDataParentMP(data %x) \n", dpmp);

  for (i=0; i<MP_SIZE_RECEIVE_MP_CHILD_LIST; i++) {
    u32 j;
    MpPrintf("\t No%d : ", i);
    for (j=0; j<MP_SIZE_MAC_DATA; j++) MpPrintf("%02x ", dpmp->user_list[i].mac_addr.u.data[j]);
    MpPrintf("  Aid %d\n", dpmp->user_list[i].aid);
  }
}


/**
 * MP_CONTROL_CODEを文字列返す
 */
const char* MpPrintControlCode(MP_CONTROL_CODE code)
{
  switch (code) {
  case MP_CONTROL_CODE_ACKNOWLEDGE :
    return "Success";
    break;

  case MP_CONTROL_CODE_RETRY :
    return "Retry";
    break;

  case MP_CONTROL_CODE_DATA_CONTINUALLY :
    return "Continue";
    break;
    
  case MP_CONTROL_CODE_DATA_END:
    return "End";
    break;

  default :
    return "Unknown";
    break;
  }
}


/**
 * MpSendHeaderの内容を表示する
 */
void MpPrintSendHeader(MpSendHeader *header)
{
  MpPrintf("MpPrintSendHeader(header %x) \n", header);

  MpPrintf("\t ProtocolID      %d\n", header->data0.protocol_id);
  MpPrintf("\t ProtocolVersion %d\n", header->data0.protocol_version);
  MpPrintf("\t EncodeType      %d\n", header->data0.encode_type);
  MpPrintf("\t EncodeData      %x\n", header->data0.encode_data);
  
  MpPrintf("\t GameTitleID     %d\n", header->data1.game_id);
  MpPrintf("\t GameVersion     %d\n", header->data1.game_version);
  MpPrintf("\t Language        %d\n", header->data1.language);
  MpPrintf("\t GameEtc         %d\n", header->data1.game_etc);

  MpPrintf("\t SequenceNo      %d\n", header->data2.sequence_num);
  MpPrintf("\t ControlCode     %s\n", MpPrintControlCode((MP_CONTROL_CODE)header->data2.control_code));
  MpPrintf("\t CRC             %d\n", header->data2.crc);

  MpPrintf("\t HeaderSize      %d\n", header->data3.header_size);
  MpPrintf("\t DataSize        %d\n", header->data3.data_size);
}

#else

const char* MpGetStatusString(MP_STATUS status)
{
#pragma unused(status)
  return "\0";
}
void MpPrintErrorCode(WMErrCode code) {
#pragma unused(code)
}
void MpPrintStateCode(WMStateCode code) {
#pragma unused(code)
}
void MpPrintBssDesc(WMBssDesc *desc) {
#pragma unused(desc)
} 
void MpPrintDataChildMP(MpDataChildMP *drmp) {
#pragma unused(drmp)
}
void MpPrintDataParentMP(MpDataParentMP *dpmp) {
#pragma unused(dpmp)
}
const char* MpPrintControlCode(MP_CONTROL_CODE code) {
#pragma unused(code)
  return "\0";
}
void MpPrintSendHeader(MpSendHeader *header) {
#pragma unused(header)
}

#endif // DEBUG_MP 


//
