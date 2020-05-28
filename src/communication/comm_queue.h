//=============================================================================
/**
 * @file	comm_queue.h
 * @bfief	（送信）キューの仕組みを管理する関数
 * @author	katsumi ohno
 * @date	06/01/29
 */
//=============================================================================

#ifndef __COMM_QUEUE_H__
#define __COMM_QUEUE_H__

#include "comm_ring_buff.h"

typedef struct _SEND_QUEUE SEND_QUEUE;

// キュー構造体
struct _SEND_QUEUE{
    u8* pData;     ///< データアドレス
    SEND_QUEUE* prev;      //
    SEND_QUEUE* next;
    u16 size;       ///< サイズ
    u8 command;    ///< コマンド
    u8 bHeadSet:1;  ///< ヘッダーを送信した場合１ まだの場合０
    u8 bRing:1;     ///< リングバッファ使用の場合１
} ;

typedef struct{
    u8* pData;
    int size;
} SEND_BUFF_DATA;



typedef struct{
    SEND_QUEUE* pTop;     // 送信キューの初め
    SEND_QUEUE* pLast;    // 送信キューの最後
} SEND_TERMINATOR;



typedef struct{
    SEND_TERMINATOR fast;     // すぐ送る送信キュー
    SEND_TERMINATOR stock;    // 後で送ればいいキュー
    SEND_QUEUE* pNow;   // 今送っている最中のキュー
    RingBuffWork* pSendRing;  // リングバッファワークポインタ
    void* heapTop;   // キューHEAP
    int max;         // キューの数
} SEND_QUEUE_MANAGER;


// キューに何か入っているかどうかを確認する
extern BOOL CommQueueIsEmpty(SEND_QUEUE_MANAGER* pQueueMgr);
// キューMANAGERの初期化
extern void CommQueueManagerInitialize(SEND_QUEUE_MANAGER* pQueueMgr, int queueMax, RingBuffWork* pSendRing);
// キューの中身をリセット
extern void CommQueueManagerReset(SEND_QUEUE_MANAGER* pQueueMgr);
// キューMANAGERの終了
extern void CommQueueManagerFinalize(SEND_QUEUE_MANAGER* pQueueMgr);
// キューにデータを入れる
extern BOOL CommQueuePut(SEND_QUEUE_MANAGER* pQueueMgr,int command, u8* pDataArea, int size, BOOL bFast, BOOL bSave);
// キューからデータを吸い上げる
extern BOOL CommQueueGetData(SEND_QUEUE_MANAGER* pQueueMgr, SEND_BUFF_DATA *pSendBuff, BOOL bNextPlus);
// コマンドがあるかどうか調べる
extern BOOL CommQueueIsCommand(SEND_QUEUE_MANAGER* pQueueMgr, int command);

extern int CommQueueGetNowNum(SEND_QUEUE_MANAGER* pQueueMgr);

#ifdef PM_DEBUG
extern void CommQueueDebugTest(void);
#endif

#endif// __COMM_QUEUE_H__

