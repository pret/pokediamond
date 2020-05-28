/**
 * @version "$Id: mpdata.c,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file twl_data.c
 * @brief 無線通信ライブラリ 内部データ参照関数
 * 
 */
#include "mpconfig.h"
#include "mpdata.h"
#include "mpdebug.h"

#if 0
#include "../data/message/message_def.h"
#include "../data/message/wordtbl_def.h"
#endif

static MpInternalData MpData;

#define     DEFAULT_CHAN            1


__attribute__ ((aligned (32))) static WMParentParam MpDefaultParameter = {
  NULL, 0, 0,
  MP_GGID,			/* ゲームグループID */
  0x0000,                       /* temporary ID */
  1,				/* エントリー許可フラグ */
  MP_CONNECT_CHILD_MAX,		/* 最大接続子機数 */
  0,                            /* マルチブートフラグ */
  0,                            /* キーシェアリング */
  0,                            /* 連続送信フラグ */
  MP_DEFAULT_BEACON_PERIOD,	/* beacon 間隔 */
  {0, 0, 0, 0},			/* rdv1 */
  {0, 0, 0, 0, 0, 0, 0, 0},	/* rsv2 */
  0,				/* 接続チャンネル */
  MP_PARENT_DATA_SIZE,		/* 親機送信データサイズ */
  MP_CHILD_DATA_SIZE		/* 子機送信データサイズ */
};


/**
 * ライブラリ内で保持されるWMParentParamを返す
 *
 * @return WMParentParam
 */
WMParentParam *MpGetParentParameter(void) { return &MpDefaultParameter; }


u32 MpGetConnectChildMax(void) { return (u32)MpDefaultParameter.maxEntry; }
void MpSetConnectChildMax(u32 num) { MpDefaultParameter.maxEntry = (u16)num; }



/**
 * 内部で使用するデータを返す
 *
 * @return TWL_InternalData
 */
MpInternalData *MpGetInternalData(void)
{
  return &MpData;
}


/**
 * 内部ステータスを返す
 *
 * @return MP_STATUS
 */
MP_STATUS MpGetStatus(void) { return (MP_STATUS)MpGetInternalData()->status; }


/**
 * 内部ステータスを設定する
 *
 * @param status TWL_STATUS 
 */
void MpSetStatus(MP_STATUS status) { MpGetInternalData()->status = (u8)status; }


/**
 * 要求ステータスを返す
 *
 * @return MP_STATUS
 */
MP_STATUS MpGetRequestStatus(void) { return (MP_STATUS)MpGetInternalData()->request_status; }


/**
 * 要求ステータスを設定する
 *
 * @param status TWL_STATUS 
 */
void MpSetRequestStatus(MP_STATUS status) { MpGetInternalData()->request_status = (u8)status; }


/**
 * 通信モードを返す
 *
 * @return MP_MODE
 */
MP_MODE MpGetMode(void) { return (MP_MODE)MpGetInternalData()->mode; }


/**
 * 通信モードを設定する
 *
 * @param mode MP_MODE
 */
void MpSetMode(MP_MODE mode) { MpGetInternalData()->mode = (u8)mode; }


/**
 * 通信ポートを返す
 *
 * @return port 
 */
u32 MpGetPort(void) { return (u32)MpGetInternalData()->port; }


/**
 * 通信ポートを設定する
 *
 * @param port 
 */
void MpSetPort(u32 port) { MpGetInternalData()->port = (u8)port; }


/**
 * 通信チャンネルを返す
 *
 * @return channel 
 */
u32 MpGetChannel(void) { return (u32)MpGetParentParameter()->channel; }


/**
 * 通信チャンネルを設定する
 *
 * @param channel 
 */
void MpSetChannel(u32 channel) { MpGetParentParameter()->channel= (u16)channel; }


/**
 * WMScanParamを取得する
 *
 * @return WMScanParam
 */
WMScanParam *MpGetScanParameter(void)
{
  return MpGetInternalData()->scan_parameter;
}


/**
 * 送信バッファサイズを返す
 *
 * @return バッファサイズ
 */
u32 MpGetSendBuffSize(void) { return MpGetInternalData()->send_buff_size; }


/**
 * 受信バッファサイズを返す
 *
 * @return バッファサイズ
 */
u32 MpGetRecvBuffSize(void) { return MpGetInternalData()->recv_buff_size; }


/**
 * 送信バッファのアドレスを返す
 *
 * @return バッファのアドレス
 */
void *MpGetSendBuff(void) { return MpGetInternalData()->send_buff; }


/**
 * 受信バッファのアドレスを返す
 *
 * @return バッファのアドレス
 */
void *MpGetRecvBuff(void) {  return MpGetInternalData()->recv_buff; }


/**
 * WMBssDescのアドレスを返す
 *
 * @return アドレス
 */
WMBssDesc *MpGetBssDesc(void) { return MpGetInternalData()->bss_desc; }


/**
 * AIDを記録
 *
 * @param aid AID
 */
void MpSetAid(u16 aid) { MpGetInternalData()->aid = aid; }


/**
 * AIDを返す
 *
 * @return AID
 */
u16 MpGetAid(void) { return MpGetInternalData()->aid; }



BOOL MpIsConnectFlag(void) { return MpGetInternalData()->connect_flag; }
void MpSetIsConnectFlag(BOOL flag) { MpGetInternalData()->connect_flag = flag; }
void MpSetDisconnectTrigger(BOOL flag) { MpGetInternalData()->disconnect_trigger = flag; }
BOOL MpGetDisconnectTrigger(void) { return MpGetInternalData()->disconnect_trigger; }


void MpSetIsEnd(BOOL flag) { MpGetInternalData()->is_end_flag = flag; }


/**
 * モード別データのアドレスを返す
 */
MpModeData *MpGetModeData(void) { return &MpGetInternalData()->mode_data; }


/**
 * 子機状態用データのアドレスを返す
 */
MpDataChildMP *MpGetDataChildMP(void) { return &MpGetModeData()->child_mp; }


/**
 * 親機状態用データのアドレスを返す
 */
MpDataParentMP *MpGetDataParentMP(void) { return &MpGetModeData()->parent_mp; }


/**
 * MpDataChildMPを初期化
 */
void MpInitDataChildMP(void)
{
  MpDataChildMP *dcmp = MpGetDataChildMP();

  /* 全て0クリア */
  MI_CpuClear8(dcmp, sizeof(MpDataChildMP));

  dcmp->time_count = 280;
}


/**
 * MpDataParentMPを初期化
 */
void MpInitDataParentMP(void)
{
  MpDataParentMP *dpmp = MpGetDataParentMP();

  /* 全て0クリア */
  MI_CpuClear8(dpmp, sizeof(MpDataParentMP));
}


/**
 * MpTransDataを返す
 */
MpTransData *MpGetTransData(void) { return &MpGetInternalData()->trans_data; }


/**
 * MpTransDataを初期化
 */
void MpInitTransData(void)
{
  MpTransData *trans_data = MpGetTransData();
  trans_data->mode = MP_TRANS_MODE_NONE;
}


/**
 * GGIDを返す
 */
u32 MpGetGameID(void) { return MpGetInternalData()->ggid; }


/**
 *
 */
u16 MpGetFramePeriod(void) { return MpGetInternalData()->frame_period; }


/**
 * プロトコルIDを返す
 */
u32 MpGetProtocolID(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data0.protocol_id;
}

/**
 * プロトコルバージョンを返す
 */
u32 MpGetProtocolVersion(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data0.protocol_version;
}


/**
 * 接続IDを返す
 */
u32 MpGetConnectID(void)
{
  return (u32)MpGetInternalData()->user_game_info.header.data1.connect_id;
}


/**
 * UserGameInfoのサイズを返す
 *
 * @return UserGameInfoのサイズ
 */
u32 MpGetUserGameInfoSize(void)
{
  return sizeof(MpUserGameInfo);
}


/**
 * MpUserGameInfoを返す
 *
 * @return MpUserGameInfoのアドレス
 */
MpUserGameInfo *MpGetUserGameInfo(void)
{
  return &MpGetInternalData()->user_game_info;
}


/**
 * MpSsidDataを返す
 *
 * @return MpSsidDataのアドレス
 */
MpSsidData *MpGetSsidData(void)
{
  return &MpGetInternalData()->ssid_data;
}


/**
 * MACアドレスを格納した配列からMpMACAddDataを生成
 *
 * @param mac_arry MACアドレス配列
 * @return　MpMACAddData
 */
MpMACAddData MpMACAddArrayToMACAddData(u8 *mac_arry)
{
  u32 i;
  MpMACAddData mac_bss;
  
  mac_bss.u.data32 = 0;
  for (i=0; i<MP_SIZE_MAC_DATA; i++) mac_bss.u.data[i] = mac_arry[i + 2];    

  return mac_bss;
}


/**
 * MACアドレスを格納した配列からMpMACVendorDataを生成
 *
 * @param mac_arry MACアドレス配列
 * @return　MpMACVendorData
 */
MpMACVendorData MpMACAddArrayToMACVendorData(u8 *mac_arry)
{
  u32 i;
  MpMACVendorData mac_bss;
  
  mac_bss.u.data16 = 0;
  for (i=0; i<MP_SIZE_MAC_VENDOR_DATA; i++) mac_bss.u.data[i] = mac_arry[i];    

  return mac_bss;
}


/**
 * u32のMACアドレスから接続IDを生成
 *
 * @param mac_addr MACアドレス
 * @param high_code ユーザーコード上位が格納される
 * @param low_code ユーザーコード下位が格納される
 */
void MpMACAddressToConnectCode(u32 mac_addr, u32 *high_code, u32* low_code)
{
  *high_code = mac_addr % 10000;
  *low_code = (mac_addr / 10000) % 10000;
}


/**
 * u32のMACアドレスから接続IDを文字列として生成
 *
 * @param mac_addr MACアドレス
 * @return 文字列バッファのポインタ
 */
const u16* MpConnectCodeToString(u32 mac_addr)
{
#if 0
  static u16 string_buff[4+4+2];
  const int num0 = n0_;
  const int hyphen = bou_;
  const int endcode = EOM_;
  int code_count = 0;
  u32 hc,lc;

  MpMACAddressToConnectCode(mac_addr, &hc, &lc);

  //OS_Printf("HightCode %d LowCode %d\n", hc, lc);
  
  string_buff[code_count++] = (u16)((hc / 1000) + num0);
  hc %= 1000;
  string_buff[code_count++] = (u16)((hc / 100) + num0);
  hc %= 100;
  string_buff[code_count++] = (u16)((hc / 10) + num0);
  hc %= 10;
  string_buff[code_count++] = (u16)(hc + num0);

  string_buff[code_count++] = (u16)hyphen;

  string_buff[code_count++] = (u16)((lc / 1000) + num0);
  lc %= 1000;
  string_buff[code_count++] = (u16)((lc / 100) + num0);
  lc %= 100;
  string_buff[code_count++] = (u16)((lc / 10) + num0);
  lc %= 10;
  string_buff[code_count++] = (u16)(lc + num0);

  string_buff[code_count] = (u16)endcode;
  
  return string_buff;
#else
  return (u16 *)NULL;
#endif
}


#if 0
/**
 * 上位下位それぞれのユーザーコードからu32のMACアドレスを生成
 *
 * @param high_code ユーザーコード上位
 * @param low_code ユーザーコード下位
 * @return MACアドレス
 */
u32 MpUserCodeToMACAddress(u32 high_code, u32 low_code)
{
  return high_code + low_code * 10000;
}
#endif

/**
 * 送信データのヘッダサイズを取得 （現在固定）
 *
 * @return バイト数
 */
u32 MpGetSendHeaderSize(void)
{
  return sizeof(MpSendHeader);
}


/**
 * 符号化用乱数seed値を取得する
 *
 * @return seed値
 */
static u32 MpGetSeed()
{
  return  ((u32)(OS_GetTick() + GX_GetVCount()) & 0xFFFFFFFE) + 1;
}


/**
 * 符号／復号化を行う
 *
 * @param seed シード
 * @param size コード化する領域のサイズ
 * @param data コード化する領域のアドレス
 */
static u32 MpEncodeData(u32 seed, u32 size, void* data)
{
  u32 i;
  u32 *target = (u32*)data;
  MATHRandContext16 cont;
  
  MATH_InitRand16(&cont, seed);
  
  for (i=0; i<size/sizeof(u32); i++) {
    (*target) ^= ((MATH_Rand16(&cont, 0) << 16) | MATH_Rand16(&cont, 0));
    target++;
  }

  return cont.x;
}


/**
 * 送信用データを生成する
 *
 * @param buff データを生成するアドレス
 * @param data 送信用データ
 * @param data_size 送信用データのサイズ
 * @param control_code 通信制御コード
 */
void MpSetupSendData(void *buff, void *data, u32 data_size, MP_CONTROL_CODE control_code, u32 seq_num)
{
  MpSendHeader *header = (MpSendHeader *)buff;
  MpUserGameInfo *info = MpGetUserGameInfo();

  header->data0.protocol_id      = info->header.data0.protocol_id;
  header->data0.protocol_version = info->header.data0.protocol_version;
  header->data0.encode_type      = info->header.data0.encode_type;
  header->data0.encode_data      = (u16)MpGetSeed();

  header->data1.game_id          = info->header.data1.game_id;
  header->data1.game_version     = info->header.data1.game_version;
  header->data1.language         = info->header.data1.language;
  header->data1.game_etc         = 0;

  header->data2.sequence_num     = (u8)seq_num;
  header->data2.control_code     = control_code;
  header->data2.crc              = SVC_GetCRC16(0, data, data_size);

  header->data3.header_size      = (u8)MpGetSendHeaderSize();
  header->data3.data_size        = data_size;

  if (data_size)
    MI_CpuCopy8(data, ((u8*)buff) + header->data3.header_size, data_size);

  MpPrintSendHeader(header);	
  
  if ((MP_ENCODE_TYPE)info->header.data0.encode_type == MP_ENCODE_TYPE_TYCHO)
    MpEncodeData(header->data0.encode_data,
		 data_size + header->data3.header_size - sizeof(MpSendHeader0),
		 &header->data1);
  
}


/**
 * 受信したデータを復号する
 *
 * @param buff 受信したデータ
 */
void MpDecodeRecvData(void *buff)
{
  MpSendHeader *header = (MpSendHeader *)buff;
  MpUserGameInfo *info = MpGetUserGameInfo();

  if ((MP_ENCODE_TYPE)header->data0.encode_type == MP_ENCODE_TYPE_TYCHO) {
    u32 seed;

    MpPrintf("MpDecodeRecvData() buff %x  encode seed %d\n", buff, header->data0.encode_data);
    
    /* ヘッダ／データサイズを取得するためにMpSendHeader1からMpSendHeader3までを復号する */
    seed = MpEncodeData(header->data0.encode_data,
			sizeof(MpSendHeader1) + sizeof(MpSendHeader2) + sizeof(MpSendHeader3),
			&header->data1);

    MpPrintf("\t header size %d  data size %d\n", header->data3.header_size, header->data3.data_size);

    /* 残りのデータを復号 */
    MpEncodeData(seed,
		 header->data3.header_size + header->data3.data_size - sizeof(MpSendHeader),
		 (void*)((u32)buff + sizeof(MpSendHeader)));
    
  }
}


/**
 * 受信したデータのCRCをチェックする
 *
 * @return buff 受信したデータ
 */
BOOL MpCheckRecvData(void *buff)
{
  MpSendHeader *header = (MpSendHeader *)buff;

  u16 crc_val = SVC_GetCRC16(0, ((u8*)buff) + header->data3.header_size, header->data3.data_size);

  if (header->data2.crc == crc_val) return TRUE;
  else return FALSE;
    
}



//
