#ifndef ___MPDATA_H___
#define ___MPDATA_H___
/**
 * @version "$Id: mpdata.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpdata.h
 * @brief 無線通信ライブラリ 内部データ参照関数
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "mpconnect.h"

/**
 * ライブラリ内で保持されるWMParentParamを返す
 *
 * @return WMParentParam
 */
extern WMParentParam *MpGetParentParameter(void);

extern u32 MpGetConnectChildMax(void);
extern void MpSetConnectChildMax(u32 num);
  
/**
 * 内部で使用するデータを返す
 *
 * @return TWL_InternalData
 */
extern MpInternalData *MpGetInternalData(void);
  

/**
 * 内部ステータスを返す
 *
 * @return MP_STATUS
 */
extern MP_STATUS MpGetStatus(void);


/**
 * 内部ステータスを設定する
 *
 * @param status MP_STATUS 
 */
extern void MpSetStatus(MP_STATUS status);
  

/**
 * 要求ステータスを返す
 *
 * @return MP_STATUS
 */
extern MP_STATUS MpGetRequestStatus(void);

  
/**
 * 要求ステータスを設定する
 *
 * @param status TWL_STATUS 
 */
extern void MpSetRequestStatus(MP_STATUS status);

  
/**
 * 通信モードを返す
 *
 * @return MP_MODE
 */
extern MP_MODE MpGetMode(void);


/**
 * 通信モードを設定する
 *
 * @param status MP_MODE
 */
extern void MpSetMode(MP_MODE mode);


/**
 * 通信ポートを返す
 *
 * @param port 
 */
extern u32 MpGetPort(void);


/**
 * 通信ポートを設定する
 *
 * @param port 
 */
extern void MpSetPort(u32 port);
  

/**
 * 通信チャンネルを返す
 *
 * @return channel 
 */
extern u32 MpGetChannel(void);


/**
 * 通信チャンネルを設定する
 *
 * @param channel 
 */
extern void MpSetChannel(u32 channel);

  
/**
 * WMScanParamを取得する
 *
 * @return WMScanParam
 */
extern WMScanParam *MpGetScanParameter(void);
  

/**
 * 送信バッファサイズを返す
 *
 * @return バッファサイズ
 */
extern u32 MpGetSendBuffSize(void);


/**
 * 受信バッファサイズを返す
 *
 * @return バッファサイズ
 */
extern u32 MpGetRecvBuffSize(void);


/**
 * 送信バッファのアドレスを返す
 *
 * @return バッファのアドレス
 */
extern void *MpGetSendBuff(void);


/**
 * 受信バッファのアドレスを返す
 *
 * @return バッファのアドレス
 */
extern void *MpGetRecvBuff(void);


/**
 * WMBssDescのアドレスを返す
 *
 * @return アドレス
 */
extern WMBssDesc *MpGetBssDesc(void);


/**
 * AIDを記録
 *
 * @param aid AID
 */
extern void MpSetAid(u16 aid);


/**
 * AIDを返す
 *
 * @return AID
 */
extern u16 MpGetAid(void);


  extern BOOL MpIsConnectFlag(void);
extern void MpSetIsConnectFlag(BOOL flag);
extern void MpSetDisconnectTrigger(BOOL flag);
extern BOOL MpGetDisconnectTrigger(void);
  
extern BOOL MpGetEndRequest(void);
extern void MpSetEndRequest(BOOL flag);
extern void MpSetIsEnd(BOOL flag);  

  
/**
 * モード別データのアドレスを返す
 */
extern MpModeData *MpGetModeData(void);


/**
 * 子機状態用データのアドレスを返す
 */
extern MpDataChildMP *MpGetDataChildMP(void);


/**
 * 親機状態用データのアドレスを返す
 */
extern MpDataParentMP *MpGetDataParentMP(void);
  

/**
 * MpDataChildMPを初期化
 */
extern void MpInitDataChildMP(void);

  
/**
 * MpDataParentMPを初期化
 */
extern void MpInitDataParentMP(void);
  

/**
 * MpTransDataを返す
 */
extern MpTransData *MpGetTransData(void);


/**
 * MpTransDataを初期化
 */
extern void MpInitTransData(void);
  

/**
 * GGIDを返す
 */
extern u32 MpGetGameID(void);


/**
 *
 */
extern u16 MpGetFramePeriod(void);


/**
 * プロトコルIDを返す
 */
extern u32 MpGetProtocolID(void);

  
/**
 * プロトコルバージョンを返す
 */
extern u32 MpGetProtocolVersion(void);

       
/**
 * 接続IDを返す
 */
extern u32 MpGetConnectID(void);


/**
 * UserGameInfoのサイズを返す
 *
 * @return UserGameInfoのサイズ
 */
extern u32 MpGetUserGameInfoSize(void);

  
/**
 * MpUserGameInfoを返す
 *
 * @return MpUserGameInfoのアドレス
 */
extern MpUserGameInfo *MpGetUserGameInfo(void);


/**
 * MpSsidDataを返す
 *
 * @return MpSsidDataのアドレス
 */
extern MpSsidData *MpGetSsidData(void);
  

/**
 * MACアドレスを格納した配列からMpMACAddDataを生成
 *
 * @param mac_arry MACアドレス配列
 * @return　MpMACAddData
 */
extern MpMACAddData MpMACAddArrayToMACAddData(u8 *mac_arry);


/**
 * MACアドレスを格納した配列からMpMACVendorDataを生成
 *
 * @param mac_arry MACアドレス配列
 * @return　MpMACVendorData
 */
extern MpMACVendorData MpMACAddArrayToMACVendorData(u8 *mac_arry);
  

/**
 * u32のMACアドレスから接続IDを生成
 *
 * @param mac_addr MACアドレス
 * @param high_code ユーザーコード上位が格納される
 * @param low_code ユーザーコード下位が格納される
 */
extern void MpMACAddressToConnectCode(u32 mac_addr, u32 *high_code, u32* low_code);


/**
 * u32のMACアドレスから接続IDを文字列として生成
 *
 * @param mac_addr MACアドレス
 * @return 文字列バッファのポインタ
 */
extern const u16* MpConnectCodeToString(u32 mac_addr);
  
  
#if 0       
/**
 * 上位下位それぞれのユーザーコードからu32のMACアドレスを生成
 *
 * @param high_code ユーザーコード上位
 * @param low_code ユーザーコード下位
 * @return MACアドレス
 */
extern u32 MpUserCodeToMACAddress(u32 high_code, u32 low_code);
#endif
  

/**
 * 送信データのヘッダサイズを取得 （現在固定）
 *
 * @return バイト数
 */
extern u32 MpGetSendHeaderSize(void);

       
/**
 * 送信用データを生成する
 *
 * @param buff データを生成するアドレス
 * @param data 送信用データ
 * @param data_size 送信用データのサイズ
 * @param control_code 通信制御コード
 * @param seq_num 通信番号
 */
extern void MpSetupSendData(void *buff, void *data, u32 data_size, MP_CONTROL_CODE control_code, u32 seq_num);


/**
 * 受信したデータを復号する
 *
 * @param buff 受信したデータ
 */
extern void MpDecodeRecvData(void *buff);


/**
 * 受信したデータのCRCをチェックする
 *
 * @return buff 受信したデータ
 */
extern BOOL MpCheckRecvData(void *buff);

       
#ifdef  __cplusplus
}       /* extern "C" */
#endif


#endif // ___MPDATA_H___
  
