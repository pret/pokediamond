#ifndef ___MPCONNECT_H___
#define ___MPCONNECT_H___
/**
 * @version "$Id: mpconnect.h,v 1.3 2006/08/11 06:30:17 mitsuhara Exp $"
 *
 * @file mpconnect.h
 * @brief MP無線通信ライブラリ
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif
  
#include    <nitro/types.h>
#include    <nitro/wm.h>
#include    <nitro/cht.h>

#ifdef PM_DEBUG
#ifndef		DEBUG_MP   
#define		DEBUG_MP	1
#endif
#else
#ifndef		DEBUG_MP   
#define		DEBUG_MP	0
#endif
#endif

#include "mpstruct.h"

  

//#define		MP_DEBUG_PRINT			1
  
/* プリント出力抑制ダミー関数 */
#ifdef  MP_DEBUG_PRINT
#define     MpPrintf			OS_TPrintf
#else
#define     MpPrintf(...)		((void) 0)
#endif

//#define		MP_DEBUG_STATE_PRINT		1

#ifdef  MP_DEBUG_STATE_PRINT
#define     MpStatePrintf		OS_TPrintf
#else
#define     MpStatePrintf(...)		((void) 0)
#endif


#define		MP_ERROR_CODE		(0xFFFFFFFF)

#define		MP_PORT_MIN	(4)  
#define		MP_PORT_MAX	(7)  

/**
 * ライブラリ初期化用構造体
 *
 * 接続IDが一致しない相手とは通信を行わない
 */
typedef struct {
  u32 game_id		: 8;	/* ゲームタイトルID */
  u32 game_version	: 4;	/* ゲームバージョン */
  u32 language		: 4;	/* 言語（OS_LANGUAGE） */
  u32 connect_id	: 16;	/* 接続ID */
  const u16* user_id;		/* ゲーム中でのプレイヤーID (15文字以内) */
  const u16* name;		/* ゲーム中でのプレイヤー名 (15文字以内) */
} MpInitDesc;
  
    
/**
 * 通信モード定義
 */
typedef enum {
  MP_MODE_NONE = 0,
  MP_MODE_CHILD_MP,		/* MP通信でデータを送信（子機になる／接続先の選択権がある） */
  MP_MODE_PARENT_MP,		/* MP通信でデータを受信（親機になる） */
  MP_MODE_MAX
} MP_MODE;  




  
extern void MpProc(void);

  
extern BOOL MpIsConnect(void);


/**
 * データ転送可能な状態か調べる
 *
 * @return 接続があればTRUEを返す
 */
extern BOOL MpIsDataTrans(void);
  

/**
 * 無線ライブラリが使用するバッファサイズを返す
 *
 * @return バイト数
 */
extern u32 MpGetBufferSize(void);
  
  
/**
 * ライブラリ初期化
 *
 * @param init_desc 初期化データ
 * @param buff ライブラリの使用するバッファのアドレスを指定 MpGetBufferSize()で取得するサイズ領域が確保されている必要がある
 */
extern void MpInit(MpInitDesc* init_desc, void* buff);


/**
 * 親機として通信開始
 */
extern void MpRequestParent();


/**
 * 子機として親機のスキャン開始
 */
extern void MpRequestScan();


/**
 * 指定接続番号の親機のユーザーIDを取得
 *
 * @param num 親機番号
 * @return 名前（u16*）
 */
extern u16* MpGetParentListUserID(u32 num);

       
/**
 * 指定番号の親機と接続可能か調べる
 *
 * @param 親機番号
 * @return 可能な場合TRUEが返る
 */
extern BOOL MpGetConnectParentEnable(u32 num);


/**
 * 指定番号の親機と接続する 接続不可能の場合は何もしない
 *
 * @param num 親機番号
 */
extern void MpConnectParent(u32 num);


/**
 * 親機との接続を切る 接続していない場合は何もしない
 */
extern void MpDisConnectParent(void);


/**
 * 全ての子機との接続を切る 接続していない場合は何もしない
 */
extern void MpDisConnectChild(void);

       
/**
 * 接続済みの親機番号を返す 接続状態にない場合はMP_ERROR_CODEが返る
 *
 * @return 親機番号
 */
extern u32 MpGetConnectParentNum(void);

  
/**
 * 指定接続番号の親機の名前を取得
 *
 * @param num 親機番号
 * @return 名前（u16*）
 */
extern u16* MpGetParentListName(u32 num);


/**
 * 指定MACアドレスの子機以外との接続を切る 接続していない場合は何もしない
 *
 * @param num 子機のMACアドレス
 */
extern void MpConnectOnlyChild(u32 num);


/**
 * 指定番号以外の子機との接続を切る 接続していない場合は何もしない
 *
 * @param num 子機番号
 */
extern void MpDataTransOnlyChild(u32 num);
  
  
/**
 * リンク強度を取得
 *
 * @return リンク強度
 */
extern u32 MpGetConnectLinkLevel(void);


/**
 * 接続可能な最大数を取得
 *
 * @return 最大数
 */
extern u32 MpGetConnectListMax(void);

  
/**
 * 接続された数を返す
 *
 * @return 接続数
 */
extern u32 MpGetConnectListNum(void);


/**
 * データ通信可能な数を返す
 *
 * @return 接続数
 */
extern u32 MpGetDataTransListNum(void);
  
  
/**
 * 指定接続番号のMACアドレスを取得
 *
 * @param num 接続番号
 * @return MACアドレス
 */
extern u32 MpGetListMacAddr(u32 num);
extern u32 MpGetTransMacAddr(u32 num);


/**
 * データの送信準備を行う
 */
extern void MpSetSendRedy(void);
  
  
/**
 * ユーザーデータの送信を行う
 */
extern void MpSetSendUserData(void);

  
/**
 * データを送信を行う
 *
 * @param data データ送信バッファ
 * @param size 送信サイズ
 * @param seq_num 通信番号
 */
extern void MpSetSendData(void *data, u32 size, u32 seq_num);


/**
 * データを受信を行う
 *
 * @param data データ受信バッファ
 * @param size 受信サイズ
 * @param seq_num 通信番号
 */
extern void MpSetRecvData(void *data, u32 size, u32 seq_num);

  
/**
 * ユーザーデータの受信バッファサイズを返す
 *
 * @return バイト数
 */
extern u32 MpGetUserDataSize(void);

  
/**
 * データの受信準備を行う
 */
extern void MpSetRecvReady(void);


/**
 * ユーザーデータの受信を行う 受信バッファサイズはsizeof(MpUserGameInfoData)
 *
 * @param data データ受信バッファ
 */
extern void MpSetRecvUserData(void *data);

  
/**
 * 送信したデータのサイズを取得する
 *
 * @return 送信バイト数
 */
extern u32 MpGetSendDataSize(void);

       
/**
 * 受信したデータのサイズを取得する
 *
 * @return 送信バイト数
 */
extern u32 MpGetRecvDataSize(void);

  
/**
 * データ送信が終了したか調べる
 *
 * @return 終了している場合TRUEが返る
 */
extern BOOL MpIsSendDataEnd(void);


/**
 * データ受信が終了したか調べる
 *
 * @return 終了している場合TRUEが返る
 */
extern BOOL MpIsRecvDataEnd(void);
extern BOOL MpIsRecvDataAcknowledge(void);


/**
 * 接続されている状態か調べる
 *
 * @return 接続があればTRUEを返す
 */
extern BOOL MpIsConnect(void);


/**
 * 無線ライブラリ停止要求
 */
extern void MpRequestClose(void);


/**
 * 無線ライブラリが停止したか調べる
 *
 * @return 停止状態になった場合TRUEが返る
 */
extern BOOL MpIsEnd(void);
  
  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___TWL_H___
