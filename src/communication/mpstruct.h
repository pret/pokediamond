#ifndef ___MPSTRUCT_H___
#define ___MPSTRUCT_H___
/**
 * @version "$Id: mpstruct.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpstruct.h
 * @brief MP無線通信ライブラリ データ定義
 * 
 */
#include "mpconfig.h"
 

#ifdef __cplusplus
extern "C" {
#endif

/* プロトコルID */
#define		MP_PROTOCOL_ID			(0x0F)

/* プロトコルバージョン */  
#define		MP_PROTOCOL_VERSION		(0x01)
  

#define		MP_RECV_READY_SEND_NUM		(3)
#define		MP_RECV_ACKNOWLEDGE_SEND_NUM	(4)

  
/* 符号化方式 */  
typedef enum {
  MP_ENCODE_TYPE_NONE = 0,
  MP_ENCODE_TYPE_TYCHO,  
  MP_ENCODE_TYPE_NINTENDO_CRYPT,  
  MP_ENCODE_TYPE_END  
} MP_ENCODE_TYPE;

/* 通信制御コード */ 
typedef enum {
  MP_CONTROL_CODE_ACKNOWLEDGE,		/* 受信成功 */
  MP_CONTROL_CODE_RETRY,		/* 再送要求 */
  MP_CONTROL_CODE_DATA_CONTINUALLY,	/* データ継続 */
  MP_CONTROL_CODE_DATA_END,		/* データ終了 */
  MP_CONTROL_CODE_END
} MP_CONTROL_CODE;  

/* 転送データヘッダ0 符号化されない */  
typedef struct {
  u32 protocol_id	: 8;	/* プロトコル番号 */
  u32 protocol_version	: 4;	/* プロトコルバージョン */
  u32 encode_type	: 4;	/* 符号化方式 MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* 復号用データ */    
} MpSendHeader0;		/* 4byte */

/* 転送データヘッダ1 符号化される */    
typedef struct {
  u32 game_id		: 8;	/* ゲームタイトルID */
  u32 game_version	: 4;	/* ゲームバージョン */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 game_etc		: 16;	/* ゲーム補足情報 */
} MpSendHeader1;		/* 4byte */
  
/* 転送データヘッダ2 符号化される */    
typedef struct {
  u32 sequence_num	: 8;	/* 通信シーケンス番号 */
  u32 control_code	: 8;	/* 通信制御コード MP_CONTROL_CODE  */
  u32 crc		: 16;	/* データCRC */
} MpSendHeader2;		/* 4byte */  

/* 転送データヘッダ3 符号化される */    
typedef struct {
  u32 header_size	: 8;	/* ヘッダーサイズ */
  u32 data_size		: 24;	/* データサイズ */
} MpSendHeader3;		/* 4byte */

/* 転送データヘッダ4 拡張用（未使用）*/    
typedef struct {
  u32 extend;
} MpSendHeader4;		/* 4byte */

/* 転送データヘッダ */  
typedef struct {
  MpSendHeader0 data0;
  MpSendHeader1 data1;
  MpSendHeader2 data2;
  MpSendHeader3 data3;
} MpSendHeader;			/* 16byte */

/* ビーコンデータヘッダ0 符号化されない */  
typedef struct {
  u32 protocol_id	: 8;	/* プロトコル番号 */
  u32 protocol_version	: 4;	/* プロトコルバージョン */
  u32 encode_type	: 4;	/* 符号化方式 MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* 復号用データ */    
} MpBeaconHeader0;		/* 4byte */
  
/* ビーコンデータヘッダ1 符号化されない */  
typedef struct {
  u32 game_id		: 8;	/* ゲームタイトルID */
  u32 game_version	: 4;	/* ゲームバージョン */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 connect_id	: 16;	/* 接続ID */
} MpBeaconHeader1;		/* 4byte */

/* ビーコンデータヘッダ */  
typedef struct {
  MpBeaconHeader0 data0;
  MpBeaconHeader1 data1;
} MpBeaconHeader;  
  

/* SSIDデータヘッダ0 符号化されない */  
typedef struct {
  u32 protocol_id	: 8;	/* プロトコル番号 */
  u32 protocol_version	: 4;	/* プロトコルバージョン */
  u32 encode_type	: 4;	/* 符号化方式 MP_ENCODE_TYPE */
  u32 encode_data	: 16;	/* 復号用データ */    
} MpSsidHeader0;		/* 4byte */
  
/* SSIDデータヘッダ1 符号化されない */  
typedef struct {
  u32 game_id		: 8;	/* ゲームタイトルID */
  u32 game_version	: 4;	/* ゲームバージョン */
  u32 language		: 4;	/* OS_LANGUAGE */
  u32 connect_id	: 16;	/* 接続ID */
} MpSsidHeader1;		/* 4byte */

/* SSIDデータヘッダ */  
typedef struct {
  MpSsidHeader0 data0;
  MpSsidHeader1 data1;
} MpSsidHeader;			/* 8byte */

  
/* SSIDデータ */   
typedef struct {
  MpSsidHeader header;
  u8 dummy[24-8];
} MpSsidData;			/* 24byte */
  

/* ユーザー名格納用バッファ */  
#define MP_USERGAMEINFO_NAME_LENGTH	(12)
typedef struct {
  u16 data[MP_USERGAMEINFO_NAME_LENGTH];
} MpUserName;			/* 24byte */

/* WMbssDescに含まれる接続データ */  
typedef struct {
  MpUserName name;		/* レンジャー／トレーナ名 */
  MpUserName user_id;		/* レンジャー番号／トレーナ番号 */
} MpUserGameInfoData;		/* 48byte */

/* WMbssDescデータ */  
typedef struct {
  MpBeaconHeader	header;
  MpUserGameInfoData	data;
} MpUserGameInfo;  
  

#define	MP_SIZE_MAC_DATA	(4)	/* 識別用MACアドレスサイズ */
typedef struct {
  union {
    u8 data[MP_SIZE_MAC_DATA];
    u32 data32;
  } u;
} MpMACAddData;

#define	MP_SIZE_MAC_VENDOR_DATA	(2)	/* MACアドレスベンダIDサイズ */
typedef struct {
  union {
    u8 data[MP_SIZE_MAC_VENDOR_DATA];
    u16 data16;
  } u;
} MpMACVendorData;

  
typedef enum {
  MP_TRANS_MODE_NONE,
  MP_TRANS_MODE_SEND,
  MP_TRANS_MODE_RECV,
  MP_TRANS_MODE_END
} MP_TRANS_MODE;

/* データ転送ステータス */
typedef enum {
  MP_TRANS_STATUS_ENABLE,	/*  */
  MP_TRANS_STATUS_WAIT,
  MP_TRANS_STATUS_SUCCESS,
  MP_TRANS_STATUS_READY,
  MP_TRANS_STATUS_END
} MP_TRANS_STATUS;
typedef struct {
  void *org_data;
  void *data;
  void *send_buff;
  void *recv_buff;
  u32 org_size;
  u32 size;
  vu8 mode;
  vu8 state;
  u8 time_out;
  u8 resend_count;
  u8 seq_num;
} MpTransData;

/* 子機ステータス定義 */  
typedef enum {
  MP_CHILD_MP_STATUS_READY = 0,
  MP_CHILD_MP_STATUS_SCAN_1,		/* 最初に親機探索するためのステート */
  MP_CHILD_MP_STATUS_SCAN_2,		/* 選択した親機と接続するためのステート */
  MP_CHILD_MP_STATUS_MAX
} MP_CHILD_MP_STATUS;
  
/* 子機が保持する親機情報 */ 
typedef struct {
  MpMACAddData	mac_addr;		/* 4byte */
  MpUserName	name;			/* 24byte */
  MpUserName	user_id;		/* 24byte */
  MpMACVendorData mac_vendor;		/* 2byte */
  u8		link_level;		/* 1byte */
  u8		data_trans_ready;	/* 1byte */
} MpDataConnectionUser;			/* 56byte */
  
/* MP通信（子機）用データ定義 */  
typedef struct {
  MpDataConnectionUser user_list[MP_SIZE_RECEIVE_MP_PARENT_LIST]; /* 56*8byte */
  u16		time_count; 
  u8		scan_retry_count;
  u8		select : 4;	/* 任意に選択した親機番号 （MP_CHILD_MP_STATUS_SCAN_2でのスキャン対象） */
  u8		status : 4;
} MpDataChildMP;		/* 452byte */

/* 親機ステータス定義 */  
typedef enum {
  MP_PARENT_MP_STATUS_READY = 0,
  MP_PARENT_MP_STATUS_SEARCH_CHANNEL,	/* 通信に使用するチャンネル設定ステート */  
  MP_PARENT_MP_STATUS_WAIT_CONNECT,	/* 接続してくる子機待ちステート */
  MP_PARENT_MP_STATUS_MAX
} MP_PARENT_MP_STATUS;

  
/* 親機が保持する子機情報 */ 
typedef struct {
  MpMACAddData	mac_addr;		/* 4byte */
  MpMACVendorData mac_vendor;		/* 2byte */
  u16		aid;			/* 2byte */
  u8		data_trans_ready;	/* 1byte */
  u8		data_trans_count;	/* 1byte */
  u8		connect_flag;		/* 1byte */
  u8		dummy;			/* 1byte */
} MpDataParentConnectionUser;		/* 12byte */
  
/* MP通信（親機）用データ定義 */  
typedef struct {
  MpDataParentConnectionUser user_list[MP_SIZE_RECEIVE_MP_CHILD_LIST]; /* 8*12byte */
  u8 status;
  u8 busy_ratio;
  u16 channel_bitmap;
  u8 channel;
  u8 dummy[3];
} MpDataParentMP;		/* 104byte */

typedef union {
  MpDataParentMP	parent_mp;
  MpDataChildMP		child_mp;
} MpModeData;

/* 電波使用率の最大（初期）値 */  
#define MP_MEASURE_BUSYRATIO_MAX	(102)
  

/**
 * 内部ステータス定義
 */  
typedef enum {
  MP_STATUS_INIT = 0,	/* 初期化状態 */
  MP_STATUS_READY,	/* 待機状態 */
  MP_STATUS_STOP,	/* 電源未投入状態 */  
  MP_STATUS_IDLE,	/* アイドル状態 */  
  MP_STATUS_ERROR,	/* どうにもならないエラー状態 */
  MP_STATUS_BUSY,	/* 状態遷移中につきビジー状態 */
  MP_STATUS_SCAN,	/* 親機のスキャン中状態 （子機専用ステータス）*/
  MP_STATUS_ENDSCAN,	/* スキャン終了状態 （子機専用ステータス）*/
  MP_STATUS_PARENT,	/* 親機として接続済み状態 */
  MP_STATUS_CHILD,	/* 子機として接続済み状態 */
  MP_STATUS_PARENT_MP,	/* 親機としてMP通信状態 */
  MP_STATUS_CHILD_MP,	/* 子機としてMP通信状態 */
  MP_STATUS_END,	/* ライブラリ終了状態 */
  MP_STATUS_MAX
} MP_STATUS;
  

/**
 * 通信シーケンス番号定義
 */  
typedef enum {
  MP_SEQUENCE_APP = 0,		/* アプリケーションが自由に使用できる値 */
  MP_SEQUENCE_APP_END	= 0xF0,	/* アプリケーションが自由に使用できる値の最後 */  
  MP_SEQUENCE_READY	= 0xFD,	/* データ送信準備シーケンス */
  MP_SEQUENCE_USER_DATA	= 0xFE,	/* ユーザ－データ送信シーケンス */
  MP_SEQUENCE_END
} MP_SEQUENCE;

  
typedef struct {

  /* 現在のステータス */
  u8 status;

  /* 変更要求ステータス */
  u8 request_status;
  
  /* 通信モード */
  u8 mode;

  /* 通信ポート */
  u8 port;
  
  /* GameID */
  u32 ggid;
  
  /* 目標ステータス */
  MP_STATUS target;

  /* AID */
  u16 aid;
  
  /* ゲームフレーム間隔 */
  u16 frame_period;

  /* Indication通知用コールバック設定済みフラグ */
  BOOL indication_callback_flag;     

  BOOL connect_flag;
  BOOL disconnect_trigger;
  
  BOOL request_end_flag;
  BOOL is_end_flag;
    
  
  WMScanParam* scan_parameter;
  WMBssDesc* bss_desc;
  
  u32 send_buff_size;
  u32 recv_buff_size;

  void *lib_buff;
  void *send_buff;
  void *recv_buff;

  MpUserGameInfo user_game_info;
  MpSsidData ssid_data;
  
  MpModeData mode_data;
  MpTransData trans_data;
  
} MpInternalData; 
  

  
  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPSTRUCT_H___
