//=============================================================================
/**
 * @file	comm_system.c
 * @brief	通信システム
 * @author	Katsumi Ohno
 * @date    2005.09.08
 */
//=============================================================================


#include "common.h"
#include "wh_config.h"
#include "wh.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/pm_str.h"
#include "system/gamedata.h"  //PERSON_NAME_SIZE

#include "comm_ring_buff.h"
#include "comm_queue.h"
#include "system/savedata.h"
#include "savedata/regulation.h"
#include "system/pm_rtc.h"  //GF_RTC

#include "wifi/dwc_rap.h"   //WIFI

#define FREEZE_SORCE (0)
#define _SENDRECV_LIMIT  (3)  // 送信と受信の数がずれた場合送信を抑制する

//==============================================================================
// extern宣言
//==============================================================================

// コンパイル時にワーニングが出るので定義してある
#include "communication/comm_system.h"



//==============================================================================
// 定義
//==============================================================================

// クライアント送信用キューのバッファサイズ    現状、クライアントの罠の数より多く切っている
#define _SENDQUEUE_NUM_MAX  (100)
#define _SENDQUEUE_NUM_NORMAL  (20)
// サーバー送信用キューのバッファサイズ    現状、罠の数より多く切っている
#define _SENDQUEUE_SERVER_NUM_MAX      (800)
#define _SENDQUEUE_SERVER_NUM_NORMAL      (280)

//子機送信バッファのサイズ    １６台つなぐ場合の任天堂の推奨バイト数
#define _SEND_BUFF_SIZE_CHILD  WH_MP_CHILD_DATA_SIZE
//子機送信バッファのサイズ    ４台以下接続時の送信バイト数
#define _SEND_BUFF_SIZE_4CHILD  WH_MP_4CHILD_DATA_SIZE
// 子機RING送信バッファサイズ
#define _SEND_RINGBUFF_SIZE_CHILD  (_SEND_BUFF_SIZE_CHILD * 22)
//親機送信バッファのサイズ
#define _SEND_BUFF_SIZE_PARENT  WH_MP_PARENT_DATA_SIZE
// 親機RING送信バッファサイズ
#define _SEND_RINGBUFF_SIZE_PARENT  (_SEND_BUFF_SIZE_PARENT * 2)

// 子機受信バッファのサイズ
#define _RECV_BUFF_SIZE_CHILD  (_SEND_BUFF_SIZE_PARENT-1)
// 親機受信バッファサイズ
#define _RECV_BUFF_SIZE_PARENT (_SEND_BUFF_SIZE_CHILD-1)



// 初期化されていないイテレーターの数
#define _NULL_ITERATE (-1)
// ありえないID
#define _INVALID_ID  (COMM_INVALID_ID)
// ありえないHEADER
#define _INVALID_HEADER  (0xff)
// 送信データがまだもらえていなかった
#define _NODATA_SEND  (0x0e)

//VBlank処理のタスクのプライオリティー
#define _PRIORITY_VBLANKFUNC (0)

// 通信先頭バイトのBITの意味
#define _SEND_NONE  (0x00)  // 一回で送れる場合
#define _SEND_NEXT  (0x01)  // 一回で送れない場合
#define _SEND_NO_DATA  (0x02)  // キーデーター以外は無い場合 MP子機
#define _MP_DATA_HEADER (0x0b)  // 親機MPデータの場合の番号  DSの場合は 0x00 or 0x01 or 0xfe or 0xff

#define _ACTION_COUNT_MOVE  (8)  // 移動キーを送らない期間

#define _PORT_DATA_RETRANSMISSION   (14)    // 切断するまで無限再送を行う  こちらを使用している
#define _PORT_DATA_PARENT         _PORT_DATA_RETRANSMISSION
#define _PORT_DATA_CHILD              _PORT_DATA_RETRANSMISSION

typedef enum{   // 送信状態
    _SEND_CB_NONE,           // なにもしていない
    _SEND_CB_FIRST_SEND,     // 流れの中での最初の送信
    _SEND_CB_FIRST_SENDEND,  // 最初の送信のコールバックが来た
    _SEND_CB_SECOND_SEND,    // 割り込みでの送信
    _SEND_CB_SECOND_SENDEND  // 割り込みでの送信コールバックが来た

};

typedef enum{   // 送信形態
    _MP_MODE,    // 親子型
    _DS_MODE,    // 並列型
    _CHANGE_MODE_DSMP,  // DSからMPに切り替え中
    _CHANGE_MODE_MPDS,  // MPからDSに切り替え中
};

typedef enum TrapKeyMode_e{
    _NONE_KEY,
    _RANDOM_KEY,
    _REVERSE_KEY,
};



//==============================================================================
// ワーク
//==============================================================================

typedef struct{
    u8* pData;     ///< データポインタ
    u16 size;       ///< サイズ
    u8 command;    ///< コマンド
    u8 priority;   ///< 優先順位  もしくは送信中かどうか
} _SEND_QUEUE;

typedef struct{
    int dataPoint; // 受信バッファ予約があるコマンドのスタート位置
    u8* pRecvBuff; // 受信バッファ予約があるコマンドのスタート位置
    u16 valSize;
    u8 valCommand;
} _RECV_COMMAND_PACK;


typedef struct{
    /// ----------------------------子機用＆親機用BUFF
    u8 sSendBuf[2][_SEND_BUFF_SIZE_4CHILD];          ///<  子機の送信用バッファ
    u8 sSendBufRing[_SEND_RINGBUFF_SIZE_CHILD];  ///<  子機の送信リングバッファ
    u8 sSendServerBuf[2][_SEND_BUFF_SIZE_PARENT];          ///<  親機の送信用バッファ
    u8 sSendServerBufRing[_SEND_RINGBUFF_SIZE_PARENT];
    u8* pMidRecvBufRing;          ///< 受け取るバッファをバックアップする DS専用
    u8* pServerRecvBufRing;       ///< 親機側受信バッファ
    u8* pRecvBufRing;             ///< 子機が受け取るバッファ
    u8* pTmpBuff;                 ///< 受信受け渡しのための一時バッファポインタ
    //----ring
    RingBuffWork sendRing;
    RingBuffWork recvRing;                      ///< 子機の受信リングバッファ
//    RingBuffWork recvRingUndo;                      ///< 子機の受信リングバッファ
    RingBuffWork recvMidRing[COMM_MACHINE_MAX];
    RingBuffWork sendServerRing;
    RingBuffWork recvServerRing[COMM_MACHINE_MAX];
//    RingBuffWork recvServerRingUndo[COMM_MACHINE_MAX];
    TCB_PTR pVBlankTCB;
    ///---que関連
    SEND_QUEUE_MANAGER sendQueueMgr;
    SEND_QUEUE_MANAGER sendQueueMgrServer;
    ///---受信関連
    _RECV_COMMAND_PACK recvCommServer[COMM_MACHINE_MAX];
    _RECV_COMMAND_PACK recvCommClient;
    
    ///------  pad関連
    MATHRandContext32 sRand;                    ///< キー用乱数キー
    u16 cont[COMM_MACHINE_MAX];            ///< 独自キーシェアリング
    u8 speed[COMM_MACHINE_MAX];             ///< 速度を毎回送る
    u16 sendCont;
    u8 sendKeyStop;
    u8 sendSpeed;
    u8 randPadType;   ///< 乱数移動に使用
    s8 randPadStep;   ///< 乱数移動に使用
    u16 oldPad;        ///< 乱数移動に使用
    //---------  同期関連
    BOOL bWifiSendRecv;   // WIFIの場合同期を取る時ととらないときが必要なので 切り分ける
    volatile int countSendRecv;   // 送ったら＋受け取ったら－ 回数
    volatile int countSendRecvServer[COMM_MACHINE_MAX];   // 送ったら＋受け取ったら－ 回数

#ifdef PM_DEBUG

    volatile int countSendNum;   // 送ったら＋
    volatile int countRecvNum;   // 受け取ったら＋ 回数
    volatile int countSendNumServer[COMM_MACHINE_MAX];   // 送ったら＋ 回数
    volatile int countRecvNumServer[COMM_MACHINE_MAX];   // 受け取ったら＋ 回数
#endif
    
    //-------
    int packetSizeMax;
    u16 bitmap;   // 接続している機器をBIT管理
    
    //-------------------
//    u8 DSCountRecv[COMM_MACHINE_MAX];  // 順番確認用
    u8 DSCount; // 順番確認用
    u8 recvDSCatchFlg[COMM_MACHINE_MAX];  // 通信をもらったことを記憶 DS同期用
    u8 bFirstCatch[COMM_MACHINE_MAX];  // コマンドをはじめてもらった時用

    u8 bPSendNoneRecv[COMM_MACHINE_MAX];        // 最初のコールバックを無条件無視

#ifdef PM_DEBUG
    u8 DebugAutoMove;
#endif
    u8 standNo[4];     // 戦闘のときの立った位置
   // u8 actionCount;
    u8 transmissionNum;
    u8 transmissionSend;
    u8 transmissionType;  // 通信形態 DSかMPかの管理
    u8 changeService;    // 通信形態の変更
    u8 sendSwitch;   // 送信バッファのスイッチフラグ
    u8 sendServerSwitch;   // 送信バッファのスイッチフラグ（サーバ用）
    u8 timSendCond; // キーを送信し場合 対戦部屋でMENUを動かなくする為につかう
    u8 bFirstCatchP2C;
    u8 bSendNoneSend;        // 無効コマンドを送る
    u8 bNextSendData;  ///
    u8 bNextSendDataServer;  ///
    u8 bAlone;    // 一人で通信できるようにするモードの時TRUE
    u8 bWifiConnect; //WIFI通信可能になったらTRUE
    u8 bResetState;
    u8 bError;  // 復旧不可能な時はTRUE
    u8 bShutDown;
    u8 bNotRecvCheck;
} _COMM_WORK_SYSTEM;

static _COMM_WORK_SYSTEM* _pComm = NULL;  ///<　ワーク構造体のポインタ
// 親機になる場合のTGID 構造体に入れていないのは
// 通信ライブラリーを切ったとしてもインクリメントしたいため
static u16 _sTgid = 0;
// 割り込みでデータを処理するかどうかのフラグ
static volatile u8 _bVSAccess = FALSE;

// 送信したことを確認するためのフラグ
static volatile u8 _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
// 同上
static volatile u8 _sendCallBack = _SEND_CB_SECOND_SENDEND;


//==============================================================================
// static宣言
//==============================================================================

static void _commCommandInit(void);
static void _commMpVBlankIntr(TCB_PTR pTCB, void* pWork);
static void _dataMpStep(void);
static void _updateMpDataServer(void);
static void _dataMpServerStep(void);
static void _sendCallbackFunc(BOOL result);
static void _sendServerCallback(BOOL result);
static void _commRecvCallback(u16 aid, u16 *data, u16 size);
static void _commRecvParentCallback(u16 aid, u16 *data, u16 size);

static void _keyRand(void);
static void _updateMpData(void);

static void _recvDataFunc(void);
static void _recvDataServerFunc(void);
static BOOL _setSendData(u8* pSendBuff);
static void _setSendDataServer(u8* pSendBuff);

static BOOL _padDataRecv(u8* pRecvBuff, int netID);
static BOOL _padDataSend(u8* pSendBuff);

static BOOL _setSendQueue(_SEND_QUEUE* pSendQueue,
                          int command, const void* data, int size);
static int _getNowQueueDataSize(_SEND_QUEUE* pSendQueue);
static BOOL _sendQueueSet(void);
static BOOL _sendServerQueueSet(void);
static void _queueSet(int restSize);
static void _queueSetServer(int restSize);
static void _spritDataSendFunc(void);

static void _transmission(void);

#ifdef PM_DEBUG
static void _debugAutoMove(void);
#endif



#ifdef PM_DEBUG

extern int DebugCommGetNum(int id);
int DebugCommGetNum(int id)
{
    if(_pComm==NULL){
        return 0;
    }
    switch(id){
      case 0:
        return _pComm->countSendRecv;
      case 1:
        return _pComm->countSendRecvServer[0];
      case 2:
        return _pComm->countSendRecvServer[1];
      case 3:
        return _pComm->countSendRecvServer[2];
      case 4:
        return _pComm->countSendRecvServer[3];
      case 5:
        return _pComm->countSendNum;   // 送ったら＋
      case 6:
        return _pComm->countRecvNum;   // 受け取ったら＋ 回数
      case 7:
        return _pComm->countSendNumServer[0];   // 送ったら＋ 回数
      case 8:
        return _pComm->countSendNumServer[1];   // 送ったら＋ 回数
      case 9:
        return _pComm->countRecvNumServer[0];   // 送ったら＋ 回数
      case 10:
        return _pComm->countRecvNumServer[1];   // 送ったら＋ 回数
    }
    return 0;
}

#endif

//==============================================================================
/**
 * 親子共通、通信の初期化をまとめた
 * @param   bAlloc          メモリー確保するかどうか
 * @param   packetSizeMax   確保したいパケットサイズ
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================

static BOOL _commInit(BOOL bAlloc, int packetSizeMax)
{
    void* pWork;
    int i;
    // イクニューモン等ネットワークライブラリの再初期化が必要な場合TRUE
    BOOL bReInit = FALSE;

    _bVSAccess = FALSE;  // 割り込み内での処理を禁止

    if(bAlloc){
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
        if(_pComm!=NULL){  // すでに初期化している場合はreturn
            return TRUE;
        }
        CommToolInitialize(HEAPID_COMMUNICATION);
        OHNO_PRINT("_COMM_WORK_SYSTEM size %d \n", sizeof(_COMM_WORK_SYSTEM));
        _pComm = (_COMM_WORK_SYSTEM*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_WORK_SYSTEM));
        MI_CpuClear8(_pComm, sizeof(_COMM_WORK_SYSTEM));
        
        _pComm->packetSizeMax = packetSizeMax + 64;
        _pComm->transmissionType = _MP_MODE;
        _pComm->changeService = COMM_MODE_NONE;
//        _pComm->bAlone = FALSE;
        
        _pComm->pRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, _pComm->packetSizeMax*2); ///< 子機が受け取るバッファ
        _pComm->pTmpBuff = sys_AllocMemory(HEAPID_COMMUNICATION, _pComm->packetSizeMax);  ///< 受信受け渡しのための一時バッファ
        _pComm->pServerRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, machineMax * _pComm->packetSizeMax);   ///< 受け取るバッファをバックアップする
        _pComm->pMidRecvBufRing = sys_AllocMemory(HEAPID_COMMUNICATION, machineMax * _pComm->packetSizeMax);   ///< 受け取るバッファをバックアップする DS専用
        // キューの初期化
        if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
            CommQueueManagerInitialize(&_pComm->sendQueueMgr, _SENDQUEUE_NUM_MAX, &_pComm->sendRing);
            CommQueueManagerInitialize(&_pComm->sendQueueMgrServer, _SENDQUEUE_SERVER_NUM_MAX, &_pComm->sendServerRing);
        }
        else{
            CommQueueManagerInitialize(&_pComm->sendQueueMgr, _SENDQUEUE_NUM_NORMAL, &_pComm->sendRing);
            CommQueueManagerInitialize(&_pComm->sendQueueMgrServer, _SENDQUEUE_SERVER_NUM_NORMAL, &_pComm->sendServerRing);
        }

#ifdef PM_DEBUG
//        CommQueueDebugTest();  // キューのプログラムテスト
#endif
    }
    else{
        bReInit = TRUE;
        GF_ASSERT((_pComm) && "切り替えの時はすでに初期化済み\n");
    }
    
#ifdef PM_DEBUG
    _pComm->DebugAutoMove = 0;
#endif
    _pComm->bitmap = 0;
    for(i =0; i < 4;i++){
        _pComm->standNo[i] = 0xff;
    }

    if(!bReInit){   // コマンドの初期化
        _commCommandInit();
    }
    CommRandSeedInitialize(&_pComm->sRand);

    //************************************

    if(!bReInit){   // プロセスタスクの作成
        // VBLANK
        _pComm->pVBlankTCB = VIntrTCB_Add(_commMpVBlankIntr, NULL, _PRIORITY_VBLANKFUNC);

    }
    _pComm->bWifiConnect = FALSE;
    return TRUE;
}


#ifdef PM_DEBUG
static u8 _sendDataNext=FALSE;
#endif


//==============================================================================
/**
 * 親子共通、通信のコマンド管理の初期化をまとめた
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandInit(void)
{
    void* pWork;
    int i;

    // ワークの初期化
//    OHNO_PRINT("コマンド再初期化\n");
    
    _pComm->randPadType = 0;
    _pComm->randPadStep = 0;
    _pComm->sendSwitch = 0;
    _pComm->sendServerSwitch = 0;
    
    // 親機のみの送受信
    {
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        OHNO_PRINT("packet %d %d\n",_pComm->packetSizeMax,machineMax);
        MI_CpuFill8(_pComm->pServerRecvBufRing, 0, _pComm->packetSizeMax * machineMax);
        for(i = 0; i< machineMax;i++){
            CommRingInitialize(&_pComm->recvServerRing[i],
                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
                               _pComm->packetSizeMax);
//            CommRingInitialize(&_pComm->recvServerRingUndo[i],
//                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
//                               _pComm->packetSizeMax);
        }

        MI_CpuFill8(_pComm->pMidRecvBufRing, 0, _pComm->packetSizeMax * machineMax );
        for(i = 0; i < machineMax; i++){
            CommRingInitialize(&_pComm->recvMidRing[i],
                               &_pComm->pMidRecvBufRing[i * _pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }
    }
    MI_CpuFill8(_pComm->sSendServerBufRing, 0, _SEND_RINGBUFF_SIZE_PARENT);
    CommRingInitialize(&_pComm->sendServerRing, _pComm->sSendServerBufRing,
                       _SEND_RINGBUFF_SIZE_PARENT);
    for(i = 0; i < _SEND_BUFF_SIZE_PARENT; i++){
        _pComm->sSendServerBuf[0][i] = CS_NONE;
        _pComm->sSendServerBuf[1][i] = CS_NONE;
    }
    // 子機の送受信
    MI_CpuFill8(_pComm->sSendBufRing, 0, _SEND_RINGBUFF_SIZE_CHILD);
    CommRingInitialize(&_pComm->sendRing, _pComm->sSendBufRing, _SEND_RINGBUFF_SIZE_CHILD);

    _pComm->sSendBuf[0][0] = _INVALID_HEADER;
    _pComm->sSendBuf[1][0] = _INVALID_HEADER;
    for(i = 1;i < _SEND_BUFF_SIZE_4CHILD;i++){
        _pComm->sSendBuf[0][i] = CS_NONE;
        _pComm->sSendBuf[1][i] = CS_NONE;
    }
    MI_CpuFill8(_pComm->pRecvBufRing, 0, _pComm->packetSizeMax*2);
    CommRingInitialize(&_pComm->recvRing, _pComm->pRecvBufRing, _pComm->packetSizeMax*2);

    _pComm->bNextSendData = FALSE;
    _pComm->bNextSendDataServer = FALSE;
#ifdef PM_DEBUG
    _sendDataNext=FALSE;
#endif
    for(i = 0; i< COMM_MACHINE_MAX;i++){
  //      _pComm->DSCountRecv[i] = 0xff;
        _pComm->recvDSCatchFlg[i] = 0;  // 通信をもらったことを記憶
        _pComm->bFirstCatch[i] = TRUE;
        _pComm->bPSendNoneRecv[i] = TRUE;
        _pComm->cont[i]=0;  ///< 独自キーシェアリング
        //_pComm->contOld[i]=0;  ///< 独自キーシェアリング
        //_pComm->trg[i]=0;   ///< 独自キーシェアリング
        _pComm->recvCommServer[i].valCommand = CS_NONE;
        _pComm->recvCommServer[i].valSize = 0xffff;
        _pComm->recvCommServer[i].pRecvBuff = NULL;
        _pComm->recvCommServer[i].dataPoint = 0;
        _pComm->countSendRecvServer[i] = 0;
#ifdef PM_DEBUG
        _pComm->countSendNumServer[i] = 0;
        _pComm->countRecvNumServer[i] = 0;
#endif
    }
    _pComm->countSendRecv = 0;
#ifdef PM_DEBUG
    _pComm->countSendNum = 0;
    _pComm->countRecvNum = 0;
#endif
    _pComm->bWifiSendRecv = TRUE;
    _pComm->recvCommClient.valCommand = CS_NONE;
    _pComm->recvCommClient.valSize = 0xffff;
    _pComm->recvCommClient.pRecvBuff = NULL;
    _pComm->recvCommClient.dataPoint = 0;

    _pComm->bFirstCatchP2C = TRUE;
    _pComm->bSendNoneSend = TRUE;
    
    _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
    _sendCallBack = _SEND_CB_SECOND_SENDEND;

        // キューのリセット
    CommQueueManagerReset(&_pComm->sendQueueMgr);
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
    _pComm->bResetState = FALSE;
}

//==============================================================================
/**
 * 親子共通、DSMPを交換する場合に呼ばれる
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandInitChange2(void)
{
    void* pWork;
    int i;

    _pComm->randPadType = 0;
    _pComm->randPadStep = 0;
//    _pComm->sendSwitch = 0;
//    _pComm->sendServerSwitch = 0;
    
    // 親機のみの送受信
    {
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        OHNO_PRINT("packet %d %d\n",_pComm->packetSizeMax,machineMax);
        MI_CpuFill8(_pComm->pServerRecvBufRing, 0, _pComm->packetSizeMax * machineMax);
        for(i = 0; i< machineMax;i++){
            CommRingInitialize(&_pComm->recvServerRing[i],
                               &_pComm->pServerRecvBufRing[i*_pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }

        MI_CpuFill8(_pComm->pMidRecvBufRing, 0, _pComm->packetSizeMax * machineMax );
        for(i = 0; i < machineMax; i++){
            CommRingInitialize(&_pComm->recvMidRing[i],
                               &_pComm->pMidRecvBufRing[i * _pComm->packetSizeMax],
                               _pComm->packetSizeMax);
        }
    }
    MI_CpuFill8(_pComm->sSendServerBufRing, 0, _SEND_RINGBUFF_SIZE_PARENT);
    CommRingInitialize(&_pComm->sendServerRing, _pComm->sSendServerBufRing,
                       _SEND_RINGBUFF_SIZE_PARENT);
    for(i = 0; i < _SEND_BUFF_SIZE_PARENT; i++){
        _pComm->sSendServerBuf[0][i] = CS_NONE;
        _pComm->sSendServerBuf[1][i] = CS_NONE;
    }
    // 子機の送受信
    MI_CpuFill8(_pComm->sSendBufRing, 0, _SEND_RINGBUFF_SIZE_CHILD);
    CommRingInitialize(&_pComm->sendRing, _pComm->sSendBufRing, _SEND_RINGBUFF_SIZE_CHILD);

    _pComm->sSendBuf[0][0] = _INVALID_HEADER;
    _pComm->sSendBuf[1][0] = _INVALID_HEADER;
    for(i = 1;i < _SEND_BUFF_SIZE_4CHILD;i++){
        _pComm->sSendBuf[0][i] = CS_NONE;
        _pComm->sSendBuf[1][i] = CS_NONE;
    }
    MI_CpuFill8(_pComm->pRecvBufRing, 0, _pComm->packetSizeMax*2);
    CommRingInitialize(&_pComm->recvRing, _pComm->pRecvBufRing, _pComm->packetSizeMax*2);

    _pComm->bNextSendData = FALSE;
    _pComm->bNextSendDataServer = FALSE;
#ifdef PM_DEBUG
    _sendDataNext = FALSE;
#endif
    for(i = 0; i< COMM_MACHINE_MAX;i++){
        _pComm->recvDSCatchFlg[i] = 0;  // 通信をもらったことを記憶
        _pComm->bFirstCatch[i] = TRUE;
        _pComm->bPSendNoneRecv[i] = TRUE;
        _pComm->cont[i]=0;  ///< 独自キーシェアリング
        _pComm->recvCommServer[i].valCommand = CS_NONE;
        _pComm->recvCommServer[i].valSize = 0xffff;
        _pComm->recvCommServer[i].pRecvBuff = NULL;
        _pComm->recvCommServer[i].dataPoint = 0;
    }
    _pComm->bWifiSendRecv = TRUE;
    _pComm->recvCommClient.valCommand = CS_NONE;
    _pComm->recvCommClient.valSize = 0xffff;
    _pComm->recvCommClient.pRecvBuff = NULL;
    _pComm->recvCommClient.dataPoint = 0;

    _pComm->bFirstCatchP2C = TRUE;
    _pComm->bSendNoneSend = TRUE;
    
//    _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
//    _sendCallBack = _SEND_CB_SECOND_SENDEND;

        // キューのリセット
    CommQueueManagerReset(&_pComm->sendQueueMgr);
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
    _pComm->bResetState = FALSE;
}

//==============================================================================
/**
 * 指定された子機の領域をクリアーする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _clearChildBuffers(int netID)
{
//    _pComm->DSCountRecv[netID] = 0xff;
    _pComm->recvDSCatchFlg[netID] = 0;  // 通信をもらったことを記憶 DS同期用
    _pComm->bFirstCatch[netID] = TRUE;  // コマンドをはじめてもらった時用
    _pComm->countSendRecvServer[netID]=0;  //SERVER受信
    _pComm->bPSendNoneRecv[netID] = TRUE;  // 一個無視

    CommRingInitialize(&_pComm->recvMidRing[netID],
                       &_pComm->pMidRecvBufRing[netID * _pComm->packetSizeMax],
                       _pComm->packetSizeMax);

    CommRingInitialize(&_pComm->recvServerRing[netID],
                       &_pComm->pServerRecvBufRing[netID * _pComm->packetSizeMax],
                       _pComm->packetSizeMax);

    _pComm->recvCommServer[netID].valCommand = CS_NONE;
    _pComm->recvCommServer[netID].valSize = 0xffff;
    _pComm->recvCommServer[netID].pRecvBuff = NULL;
    _pComm->recvCommServer[netID].dataPoint = 0;
}

//==============================================================================
/**
 * 指定された子機の領域をクリアーする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _connectFunc(void)
{
    int i;

    for(i = 1 ; i < COMM_MACHINE_MAX ; i++){
        if((!CommIsConnect(i)) && !_pComm->bFirstCatch[i]){
            if(!CommGetAloneMode()){
                OHNO_PRINT("非接続になった時に %d\n",i);
                _clearChildBuffers(i);  // 非接続になった時に
            }
        }
    }

}


//==============================================================================
/**
 * 親機の初期化を行う
 * @param   work_area 　システムで使うメモリー領域
 *                      NULLの場合すでに初期化済みとして動作
 * @param   regulationNo  ゲームの種類
 * @param   bTGIDChange  新規のゲームの初期化の場合TRUE 古いビーコンでの誤動作を防ぐため用
 * @param   bEntry  子機を受け入れるかどうか
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================
BOOL CommParentModeInit(BOOL bAlloc, BOOL bTGIDChange, int packetSizeMax, BOOL bEntry)
{
    BOOL ret = TRUE;
    if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
        ret = CommMPParentInit(bAlloc, bTGIDChange, bEntry);
    }
    _commInit(bAlloc, packetSizeMax);
    return ret;
}

//==============================================================================
/**
 * 子機の初期化を行う
 * @param   work_area 　システムで使うメモリー領域
 *                      NULLの場合はすでに初期化済みとして扱う
 * @param   regulationNo  ゲームの種類
 * @param   bBconInit  ビーコンデータを初期化するのかどうか
 * @retval  初期化に成功したらTRUE
 */
//==============================================================================
BOOL CommChildModeInit(BOOL bAlloc, BOOL bBconInit, int packetSizeMax)
{
    BOOL ret = TRUE;

    if(COMM_MODE_BATTLE_SINGLE_WIFI > CommStateGetServiceNo()){
        ret = CommMPChildInit(bAlloc, bBconInit);
    }
    else{
    }
    _commInit(bAlloc, packetSizeMax);
    _sendCallBack = _SEND_CB_SECOND_SENDEND;

    return ret;
}

//==============================================================================
/**
 * 通信モード切替
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _transmissonTypeChange(void)
{
    int i;
    BOOL bChange = FALSE;

    // 遅延してる時に変更しないようにした
    if(CommGetCurrentID() == COMM_PARENT_ID){
        if(_sendCallBackServer != _SEND_CB_SECOND_SENDEND){
            return;
        }
    }
    else{
        if(_sendCallBack != _SEND_CB_SECOND_SENDEND){
            return;
        }
    }
    
    if(_pComm->transmissionType == _CHANGE_MODE_DSMP){
        _pComm->transmissionType = _MP_MODE;
        bChange=TRUE;
        OHNO_PRINT("MPモードになりました\n");
    }
    if(_pComm->transmissionType == _CHANGE_MODE_MPDS){
        _pComm->transmissionType = _DS_MODE;
        bChange=TRUE;
        OHNO_PRINT("DSモードになりました\n");
    }
    if(bChange){
        _commCommandInitChange2(); // コマンド全部消し
        OHNO_PRINT("send Recv %d %d %d \n",_pComm->countSendRecv,_pComm->countSendRecvServer[0],_pComm->countSendRecvServer[1]);
    }

    _transmission();

}

//==============================================================================
/**
 * DSモードに切り替える
 * @param   DSモードで動く場合_DS_MODE MPで動く場合_MP_MODE
 * @retval  none
 */
//==============================================================================


static void _commSetTransmissonType(int type)
{
    if((_pComm->transmissionType == _MP_MODE) && (type == _DS_MODE)){
        _pComm->transmissionType = _CHANGE_MODE_MPDS;
        return;
    }
    if((_pComm->transmissionType == _DS_MODE) && (type == _MP_MODE)){
        _pComm->transmissionType = _CHANGE_MODE_DSMP;
        return;
    }
}

void CommSetTransmissonTypeDS(void)
{
    _commSetTransmissonType(_DS_MODE);
}

void CommSetTransmissonTypeMP(void)
{
    _commSetTransmissonType(_MP_MODE);
}

//==============================================================================
/**
 * 現在のモードの取得
 * @param   none
 * @retval  _DS_MODEか_MP_MODE
 */
//==============================================================================

static int _transmissonType(void)
{
    if(_pComm->transmissionType == _CHANGE_MODE_DSMP){
        return _DS_MODE;
    }
    if(_pComm->transmissionType == _CHANGE_MODE_MPDS){
        return _MP_MODE;
    }
    return _pComm->transmissionType;
}

//==============================================================================
/**
 * 現在 DSモードかどうか
 * @param   none
 * @retval  TRUEならDS
 */
//==============================================================================

BOOL CommIsTransmissonDSType(void)
{
    if(_DS_MODE == _transmissonType()){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信切断を行う
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommFinalize(void)
{
    BOOL bEnd = FALSE;

    if(_pComm){
        if(COMM_MODE_BATTLE_SINGLE_WIFI <= CommStateGetServiceNo()){
            OHNO_PRINT("切断------\n");
            mydwc_Logout();  // 切断
            bEnd = TRUE;
        }
        else{
            if(CommMPFinalize()){
                bEnd = TRUE;
            }
        }
    }
    if(bEnd){
        OHNO_PRINT("切断----開放処理--\n");
        CommToolFinalize();
        CommInfoFinalize();
        // VBLANKタスクを切る
        _bVSAccess = FALSE;  // 割り込み内での処理を禁止
        OHNO_PRINT("VBLANKタスクを切る\n");
        TCB_Delete(_pComm->pVBlankTCB);
        _pComm->pVBlankTCB = NULL;
        sys_FreeMemoryEz(_pComm->pRecvBufRing);
        sys_FreeMemoryEz(_pComm->pTmpBuff);
        sys_FreeMemoryEz(_pComm->pServerRecvBufRing);
        sys_FreeMemoryEz(_pComm->pMidRecvBufRing);
        CommQueueManagerFinalize(&_pComm->sendQueueMgrServer);
        CommQueueManagerFinalize(&_pComm->sendQueueMgr);
        sys_FreeMemoryEz(_pComm);
        _pComm = NULL;
    }
}

//==============================================================================
/**
 * 子機 名前とIDで接続
 * @param   pNameBuf   つなぎに行きたいユーザー名 
 * @param   pokeID     つなぎに行きたいID
 * @retval  親機情報がない場合  CC_NOT_FOUND_PARENT_INFO
 * @retval  通信の内部状態が遷移中で、接続にいけない場合  CC_BUSY_STATE
 * @retval  接続関数を呼び出したら CC_CONNECT_STARTING
 */
//==============================================================================
//int CommChildNameAndIDConnect(STRBUF* pNameBuf,u32 pokeID)
//{
  //  return CommMPChildNameAndIDConnect(pNameBuf, pokeID);
//}

//==============================================================================
/**
 * 子機 index接続
 * @param   index   親のリストのindex
 * @retval  子機接続を親機に送ったらTRUE
 */
//==============================================================================
BOOL CommChildIndexConnect(u16 index)
{
    return CommMPChildIndexConnect(index);
}

//==============================================================================
/**
 * 通信処理を含めたVBLANK割り込み処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commMpVBlankIntr(TCB_PTR pTCB, void* pWork)
{
    if(_bVSAccess){
        _updateMpData();     // データ送受信
        if(((CommGetCurrentID() == COMM_PARENT_ID) && (CommIsConnect(COMM_PARENT_ID))) || CommGetAloneMode()){
            _updateMpDataServer();   // MP通信サーバー側STEP処理
        }
        _bVSAccess = FALSE;  // 割り込み内での処理を禁止
    }
}


//==============================================================================
/**
 * 終了コマンドを受信したらモードに応じて処理を行い自動切断する
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _autoExitSystemFunc(void)
{
    if(!CommMPIsAutoExit()){
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){   // 自分が親の場合みんなに逆返信する
        if(CommMPIsChildsConnecting()){
            return;
        }
        CommFinalize();  // 終了処理に入る
    }
    else{   //子機の場合
        CommFinalize();  // 終了処理に入る
    }
}

//==============================================================================
/**
 * 通信データの更新処理  データを収集
 *    main.c   から  vblank後にすぐに呼ばれる
 * @param   none
 * @retval  データシェアリング同期が取れなかった場合FALSE
 */
//==============================================================================


BOOL CommUpdateData(void)
{
    int j;

    CommStateCheckFunc(); //commstateをタスク処理しないことにしたのでここに
    if(_pComm != NULL){
        
#if 0
        if(CommGetCurrentID() != -1){
            OHNO_PRINT("  RecvSend %d \n",_pComm->countSendRecv);
            if((CommGetCurrentID() == 0) || CommGetAloneMode()){
                for(j = 0;j < COMM_MACHINE_MAX;j++){
                    if(CommIsConnect(j) || (j == 0)){
                        OHNO_PRINT("  RecvSend %d  %d \n",j,_pComm->countSendRecvServer[j]);
                    }
                }
            }
        }
#endif
        if(!_pComm->bShutDown){

            _bVSAccess = FALSE;   // 安全のためVBlank割り込みでのアクセス禁止宣言
            _transmissonTypeChange();  //通信切り替え
            _pComm->sendCont |= (sys.cont & 0x7fff);  // キーデータの取得
#ifdef PM_DEBUG
            _debugAutoMove();
#endif
            _keyRand();

            _dataMpStep();
            _pComm->sendCont &= 0x8000;
            if(_transmissonType() == _MP_MODE){
                _recvDataFunc();    // 子機としての受け取り処理
            }
            if((CommGetCurrentID() == COMM_PARENT_ID) && (CommIsConnect(COMM_PARENT_ID)) || CommGetAloneMode() ){
                // サーバーとしての処理
                _dataMpServerStep();
            }
            if((CommGetCurrentID() == COMM_PARENT_ID) || (_transmissonType() == _DS_MODE) || CommGetAloneMode() ){
                _recvDataServerFunc();  // サーバー側の受信処理
            }
            _bVSAccess = TRUE;  // 次の割り込み時での処理を許可
        }
        CommMpProcess(_pComm->bitmap);
        if(CommGetCurrentID() == COMM_PARENT_ID){
            _connectFunc();
        }
        _autoExitSystemFunc();  // 自動切断 _pComm=NULLになるので注意
    }
    else{
        CommMpProcess(0);
    }
    CommErrorDispCheck(HEAPID_BASE_SYSTEM);
    CommTimingSyncSend();
    return TRUE;
}


//==============================================================================
/**
 * 通信バッファをクリアーする
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemReset(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // 割り込み内での処理を禁止
    if(_pComm){
        _commCommandInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * DSモードで通信バッファをクリアーする
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemResetDS(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // 割り込み内での処理を禁止
    if(_pComm){
        _pComm->transmissionType = _DS_MODE;
        _commCommandInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * 通信バッファをクリアーする+ビーコンの初期化を行う
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemResetBattleChild(void)
{
    BOOL bAcc = _bVSAccess;

    OHNO_PRINT("CommSystemReset\n");
    _bVSAccess = FALSE;  // 割り込み内での処理を禁止
    if(_pComm){
        _commCommandInit();
        ChildBconDataInit();
    }
    _bVSAccess = bAcc;
}

//==============================================================================
/**
 * データ送信処理
 * @param   none
 * @retval  none
 */
//==============================================================================


static void _dataMpStep(void)
{
    if(_pComm->bSendNoneSend){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            if( _pComm->bWifiConnect ){
                if( mydwc_sendToServer( _pComm->sSendBuf[0], _SEND_BUFF_SIZE_4CHILD )){
                    _pComm->bSendNoneSend = FALSE;
                }
            }
        }
        else if(((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) &&
                 (CommIsConnect(CommGetCurrentID()))) || CommGetAloneMode()){
            _sendCallBack = _SEND_CB_NONE;
            _updateMpData();     // データ送受信
            if(_sendCallBack != _SEND_CB_NONE){
                _pComm->bSendNoneSend = FALSE;
            }
        }
        return;
    }


    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if( _pComm->bWifiConnect ){
            if( _pComm->bWifiSendRecv ){  // 同期を取っている場合
                if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //送りすぎ
                    return;
                }
                if(_sendCallBack == _SEND_CB_SECOND_SENDEND){
                    _setSendData(_pComm->sSendBuf[0]);   // 送るデータをリングバッファから差し替える
                    _sendCallBack = _SEND_CB_FIRST_SENDEND;
                }
            }
            else{
                if(_sendCallBack == _SEND_CB_SECOND_SENDEND){
                    if(!_setSendData(_pComm->sSendBuf[0])){  // 送るデータをリングバッファから差し替える
                        return;  // 本当に送るものが何も無い場合
                    }
                    _sendCallBack = _SEND_CB_FIRST_SENDEND;
                }
            }
            if( mydwc_sendToServer( _pComm->sSendBuf[0], _SEND_BUFF_SIZE_4CHILD )){
//                if( !_pComm->bWifiSendRecv ){  // 同期を取ってない場合
//                    DEBUG_DUMP(&_pComm->sSendBuf[0][0], 16,"sp0");
//                }
                _sendCallBack = _SEND_CB_SECOND_SENDEND;
                _pComm->countSendRecv++;  //wifi client
#ifdef PM_DEBUG
                _pComm->countSendNum++;
#endif
            }
            else{
            }
        }
    }
    else if(((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) &&
        (CommIsConnect(CommGetCurrentID()))) || CommGetAloneMode()){
        if(_sendCallBack != _SEND_CB_SECOND_SENDEND){  // 2個送ったが送信完了していない
//            OHNO_PRINT("にかいうけとってない _sendCallBack\n");
            return;
        }
        if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //送りすぎ
//            OHNO_PRINT("子機がデータ送信をしない\n");
            return;
        }
        _setSendData(_pComm->sSendBuf[_pComm->sendSwitch]);  // 送るデータをリングバッファから差し替える
        _setSendData(_pComm->sSendBuf[ 1 - _pComm->sendSwitch]);  // 送るデータをリングバッファから差し替える
        _sendCallBack = _SEND_CB_NONE;
        _updateMpData();     // データ送受信
    }
}

//==============================================================================
/**
 * 中間RINGBUFFから子機全員に逆送信するためbuffにコピー
 * @param   none
 * @retval  none
 */
//==============================================================================

static BOOL _copyDSData(int switchNo)
{
    int mcSize;
    int machineMax;
    int i,num,nosend = 0;

    mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
/*
    // 初期化
    for(i = 0; i < machineMax; i++){
        if(CommIsConnect(i) && (_pComm->recvDSCatchFlg[i] > 1) ){
            // OHNO_PRINT("--------------追い越しが発生 %d\n",i);
            //                        _pComm->sSendServerBuf[_pComm->sendServerSwitch][i*mcSize] = _NODATA_SEND;
        }
        if(CommIsConnect(i) && (_pComm->recvDSCatchFlg[i] == 0) ){
            OHNO_PRINT("--------------追いぬきが発生 %d\n",i);
            _pComm->sSendServerBuf[switchNo][i * mcSize] = _NODATA_SEND;
            if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
                _sendCallBackServer--;
                return FALSE;
            }
        }
        _pComm->recvDSCatchFlg[i] = 0;
    }
   */
    /// 中間RINGBUFFから子機全員に逆送信するためbuffにコピー
    for(i = 0; i < machineMax; i++){
        CommRingEndChange(&_pComm->recvMidRing[i]);
        if(CommIsConnect(i)){
            _pComm->sSendServerBuf[switchNo][i * mcSize] = _NODATA_SEND;
        }
        num = CommRingGets(&_pComm->recvMidRing[i] ,
                     &_pComm->sSendServerBuf[switchNo][i*mcSize],
                     mcSize);
        if(_pComm->sSendServerBuf[switchNo][i * mcSize] == _NODATA_SEND){
            nosend++;
        }
    }
    if(nosend == machineMax){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * データ送信処理  サーバー側
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _updateMpDataServer(void)
{
    int i;
    int debug=0;
    int mcSize ,machineMax;

    if(!_pComm){
        return;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        return;
    }
    
    mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
    if((_sendCallBackServer == _SEND_CB_FIRST_SENDEND) ||
       (_sendCallBackServer == _SEND_CB_NONE)){
        _sendCallBackServer++;
        
        if(_transmissonType() == _DS_MODE){
            _copyDSData(_pComm->sendServerSwitch);
        }
        if( (WH_GetSystemState() == WH_SYSSTATE_CONNECTED)  && !CommGetAloneMode()){
            if(!WH_SendData(_pComm->sSendServerBuf[_pComm->sendServerSwitch],
                            _SEND_BUFF_SIZE_PARENT,
                            _PORT_DATA_PARENT, _sendServerCallback)){
                _sendCallBackServer--;
            }
        }
        // 送信完了
        if((_sendCallBackServer == _SEND_CB_FIRST_SEND) || (_sendCallBackServer == _SEND_CB_SECOND_SEND) ){

            for(i = 0; i < machineMax; i++){
                if(CommIsConnect(i)){
                    _pComm->countSendRecvServer[i]++; // 親MP送信
#ifdef PM_DEBUG
                    _pComm->countSendNumServer[i]++;
#endif
                }
                else if(CommGetAloneMode() && (i == 0)){
                    _pComm->countSendRecvServer[i]++; // 親MP送信
#ifdef PM_DEBUG
                    _pComm->countSendNumServer[i]++;
#endif
                }
            }

            // 親機自身に子機の動きをさせるためここでコールバックを呼ぶ
            _commRecvCallback(COMM_PARENT_ID,
                              (u16*)_pComm->sSendServerBuf[ _pComm->sendServerSwitch ],
                              _SEND_BUFF_SIZE_PARENT);
            _pComm->sendServerSwitch = 1 - _pComm->sendServerSwitch;
        }
        for(i = 0; i < machineMax; i++){
            if(!CommIsConnect(i)){
                if(_transmissonType() == _DS_MODE){             // 初期化
                    _pComm->sSendServerBuf[_pComm->sendServerSwitch][i*mcSize] = _INVALID_HEADER;
                }
                else{
  //                        _clearChildBuffers(i);
                }
            }
        }
        if( (WH_GetSystemState() != WH_SYSSTATE_CONNECTED)  || CommGetAloneMode() ){
            // 割り込みが無い状況でも動かす為ここでカウント
            _sendCallBackServer++;
        }
    }
}

//==============================================================================
/**
 * データ送信処理  サーバー側
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _dataMpServerStep(void)
{
    int i;

    if(_pComm->bSendNoneSend){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            if( CommIsConnect(COMM_PARENT_ID) ){
                if( mydwc_sendToClient( _pComm->sSendServerBuf[0], WH_MP_4CHILD_DATA_SIZE*2 )){
                    _pComm->bSendNoneSend = FALSE;
                    return;
                }
            }
        }
        else if((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) || (CommGetAloneMode()) ){
            _updateMpDataServer();
            if(_sendCallBackServer == _SEND_CB_FIRST_SENDEND){
                _pComm->bSendNoneSend = FALSE;
                return;
            }
        }
    }

    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if( CommIsConnect(COMM_PARENT_ID) ){
            if( _pComm->bWifiSendRecv ){  // 同期を取っている場合
                if(_pComm->countSendRecvServer[1] > _SENDRECV_LIMIT){ // 送信しすぎの場合
                    return;
                }
                if(_pComm->countSendRecvServer[0] > _SENDRECV_LIMIT){ // 送信しすぎの場合
                    return;
                }
                if(_sendCallBackServer == _SEND_CB_SECOND_SENDEND){
                    if(_transmissonType() == _DS_MODE){
                        _copyDSData(0);  //DS通信ならコピー
                    }
                    _sendCallBackServer = _SEND_CB_FIRST_SENDEND;
                }
            }
            else{
                if(_sendCallBackServer == _SEND_CB_SECOND_SENDEND){
                    if(_transmissonType() == _DS_MODE){
                        if(!_copyDSData(0)){  //DS通信ならコピー
                            return;
                        }
                    }
                }
                _sendCallBackServer = _SEND_CB_FIRST_SENDEND;
            }

            if( mydwc_sendToClient( _pComm->sSendServerBuf[0], WH_MP_4CHILD_DATA_SIZE*2 )){
                OHNO_SP_PRINT("send %d \n",_pComm->sSendServerBuf[0][0]);
                _sendCallBackServer = _SEND_CB_SECOND_SENDEND;
                _pComm->countSendRecvServer[0]++; // wifi server
                _pComm->countSendRecvServer[1]++; // wifi server
#ifdef PM_DEBUG
                _pComm->countSendNumServer[0]++;
                _pComm->countSendNumServer[1]++;
#endif
            }
            else{
                OHNO_PRINT("mydwc_sendToClientに失敗\n");
            }
        }
    }
    else if((WH_GetSystemState() == WH_SYSSTATE_CONNECTED) || (CommGetAloneMode()) ){
        if(_sendCallBackServer != _SEND_CB_SECOND_SENDEND){
//            OHNO_PRINT("二回うけとってない_sendCallBackServer\n");
            return;
        }
        for(i = 1; i < COMM_MACHINE_MAX; i++){
            if(CommIsConnect(i)){
                if(_pComm->countSendRecvServer[i] > _SENDRECV_LIMIT){ // 送信しすぎの場合
                    //OHNO_PRINT("送信しすぎ%d \n",i);
                    return;
                }
            }
            else if((i == 0) && CommGetAloneMode()){
                if(_pComm->countSendRecvServer[0] > _SENDRECV_LIMIT){ // 送信しすぎの場合
                    return;
                }
            }
        }
//        if( _pComm->countSendRecv > _SENDRECV_LIMIT ){  //送りすぎ
  //          return;
    //    }
        if(_transmissonType() == _MP_MODE){  // DS時にはすでにsSendServerBufにデータがある
            _setSendDataServer(_pComm->sSendServerBuf[ _pComm->sendServerSwitch ]);  // 送るデータをリングバッファから差し替える
            _setSendDataServer(_pComm->sSendServerBuf[ 1 - _pComm->sendServerSwitch ]);  // 送るデータをリングバッファから差し替える
        }
        _sendCallBackServer = _SEND_CB_NONE;
        // 最初の送信処理
        _updateMpDataServer();
    }
}

//==============================================================================
/**
 * 通信を受信した時に呼ばれるコールバック
 * @param   result  成功か失敗
 * @retval  none
 */
//==============================================================================

#ifdef PM_DEBUG
static u8 debugHeadData[COMM_MACHINE_MAX][100];
static int debugCnt[COMM_MACHINE_MAX]={0,0,0,0,0,0,0,0};
static u8 debugHeadDataC[5][100];
static int debugCntC = 0;
#endif



//#define WIFI_DUMP_TEST

// 受信コールバック型 子機側の受信は 親機の192byteのみの受信となる
void CommRecvCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;

#ifdef WIFI_DUMP_TEST
//    if((adr[0] & 0xf) != 0xe){
 //       DEBUG_DUMP(&adr[0], 38,"cr0");
//    }
//    if((adr[38] & 0xf) != 0xe){
  //DEBUG_DUMP(&adr[38], 38,"cr1");
//    }
#endif

    if(_pComm->bPSendNoneRecv[COMM_PARENT_ID]){
        _pComm->countSendRecv--;  //受信
#ifdef PM_DEBUG
        _pComm->countRecvNum++;
#endif
        _pComm->bPSendNoneRecv[COMM_PARENT_ID] = FALSE;
        return;
    }
    _commRecvCallback(aid, data, size);
}
// こちらが本体 上のはrapper
static void _commRecvCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
    int i;
    int recvSize = size;

    _pComm->countSendRecv--;  //受信
#ifdef PM_DEBUG
    _pComm->countRecvNum++;
#endif
    if(adr==NULL){
        return;
    }

#ifdef PM_DEBUG
    debugHeadDataC[0][debugCntC] = adr[0];
    debugHeadDataC[1][debugCntC] = adr[1];
    debugHeadDataC[2][debugCntC] = adr[2];
    debugHeadDataC[3][debugCntC] = adr[3];
    debugHeadDataC[4][debugCntC] = adr[4];
    debugCntC++;
    if(debugCntC == 100){
        debugCntC = 0;
    }
#endif

    
//    if( !_pComm->bWifiSendRecv ){  // 同期を取ってない
    //DEBUG_DUMP(&adr[0], 16,"cr0");
    //DEBUG_DUMP(&adr[38], 16,"cr1");
//    }
    if(adr[0] == _MP_DATA_HEADER){   ///MPデータの場合
        if(_transmissonType() == _DS_MODE){
            OHNO_PRINT("DSなのにMPデータが来た \n");
            return;
        }
        adr++;
        recvSize--;
    }
    else if(_transmissonType() == _MP_MODE){  //DSデータの場合
        OHNO_PRINT("MPなのにDEPデータが来た \n");
        return;
    }
    if((_pComm->bFirstCatchP2C) && (adr[0] & _SEND_NEXT)){
        // まだ一回もデータをもらったことがない状態なのに連続データだった
        OHNO_PRINT("連続データ child %d \n",aid);
        DEBUG_DUMP((u8*)data,24,"cr");
        return;
    }
#if 0
    DEBUG_DUMP(adr,24,"cr");
#endif
    _pComm->bFirstCatchP2C = FALSE;

    if(_transmissonType() == _DS_MODE){
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

        for(i = 0; i < machineMax; i++){
            if(adr[0] == _INVALID_HEADER){
                _pComm->bitmap = _pComm->bitmap & ~(1<<i);
//                _pComm->DSCountRecv[i] = 0xff;
            }
            else{
                _pComm->bitmap = _pComm->bitmap | (1<<i);
            }
            if(adr[0] == _INVALID_HEADER){
                adr += mcSize;
            }
            else if(adr[0] == _NODATA_SEND){
                adr += mcSize;
//                OHNO_PRINT("--------------今回データなし %d\n",i);
            }
            else if((_pComm->bFirstCatch[i]) && (adr[0] & _SEND_NEXT)){ // まだ一回もデータをもらったことがない状態なのに連続データだった
                OHNO_PRINT("連続データ parent %d \n",aid);
                adr += mcSize;
            }
            else{
#if 0
                u8 cnt = ((adr[0] >> 4)  & 0xf);
                if(_pComm->DSCountRecv[i] != 0xff){
                    if(cnt > _pComm->DSCountRecv[i]){
                        if((cnt-1)!=_pComm->DSCountRecv[i]){
                            OHNO_PRINT("コマンドずれ  %d %d %d\n",i,cnt-1,_pComm->DSCountRecv[i]);
                            DEBUG_DUMP((u8*)data,size,"コマンドずれ");
                            GF_ASSERT((cnt-1)==_pComm->DSCountRecv[i]);
                        }
                    }
                    else{
                        if((cnt!=0) || (_pComm->DSCountRecv[i]!=0xf)){
                            OHNO_PRINT("コマンドずれ  %d %d %d\n",i,cnt-1,_pComm->DSCountRecv[i]);
                            DEBUG_DUMP((u8*)data,size,"コマンドずれ");
                        }
                        GF_ASSERT((cnt==0) && (_pComm->DSCountRecv[i]==0xf));
                    }
                }
                _pComm->DSCountRecv[i] = cnt;
#endif
                adr++;
                CommRingPuts(&_pComm->recvServerRing[i], adr, mcSize-1, __LINE__);
                adr += (mcSize-1);
                _pComm->bFirstCatch[i]=FALSE;
            }
        }
    }
    else{   //MPデータ
#if _COMMAND_TEST
        DEBUG_DUMP(adr,recvSize,"子機データ受信");
#endif
//        DEBUG_DUMP(adr,recvSize,"子機データ受信");
        
        adr++;      // ヘッダー１バイト読み飛ばす
        _pComm->bitmap = adr[0];
        _pComm->bitmap *= 256;
        adr++;   // Bitmapでーた
        _pComm->bitmap += adr[0];
        adr++;   // Bitmapでーた
        recvSize -= 3;
        //    OHNO_PRINT("bitmap %x\n",_pComm->bitmap);
        recvSize = adr[0]; 
        adr++;
        //if(recvSize > CommRingDataRestSize(&_pComm->recvRing)){
          //  GF_ASSERT_RETURN("Error:受信オーバー\n",);
        //}
        CommRingPuts(&_pComm->recvRing , adr, recvSize, __LINE__);
    }
}


//==============================================================================
/**
 * 通信を受信した時に呼ばれるコールバック
 * @param   result  成功か失敗
 * @retval  none
 */
//==============================================================================

// 受信コールバック型  親機用
void CommRecvParentCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
#ifdef WIFI_DUMP_TEST
//   if((adr[0] & 0xf) != 0xe){
    if(aid == 1){
        DEBUG_DUMP(&adr[0], 38,"pr1");
        OHNO_PRINT("adr %x size %d\n",(u32)data, size);
    }
    else{
        DEBUG_DUMP(&adr[0], 38,"pr0");
    }
//   }
#endif

    if(_pComm->bPSendNoneRecv[aid]){
        _pComm->countSendRecvServer[aid]--;  //SERVER受信
#ifdef PM_DEBUG
        _pComm->countRecvNumServer[aid]++;
#endif
        _pComm->bPSendNoneRecv[aid] = FALSE;
        return;
    }


    _commRecvParentCallback(aid, data, size);
}


static void _commRecvParentCallback(u16 aid, u16 *data, u16 size)
{
    u8* adr = (u8*)data;
    int i;

    _pComm->countSendRecvServer[aid]--;  //SERVER受信
#ifdef PM_DEBUG
    _pComm->countRecvNumServer[aid]++;
#endif
    if(adr==NULL){
        return;
    }

#ifdef PM_DEBUG
    debugHeadData[aid][debugCnt[aid]] = adr[0];
    debugCnt[aid]++;
    if(debugCnt[aid]==100){
        debugCnt[aid] = 0;
    }
#endif
    
    if((_pComm->bFirstCatch[aid]) && (adr[0] & _SEND_NEXT)){
        // まだ一回もデータをもらったことがない状態なのに連続データだった
        OHNO_PRINT("連続データ parent %d \n",aid);
        i = 0;
        DEBUG_DUMP(adr,12,"連続データ");
        return;
    }
    _pComm->bFirstCatch[aid] = FALSE;

    if(_transmissonType() == _DS_MODE){
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
#if 0
        if((aid == 1) && ((adr[0] & 0x0f)== _SEND_NEXT)){
           DEBUG_DUMP(&adr[1],mcSize-1,"poke");
        }
   //     if(aid == 0){
   //         DEBUG_DUMP(adr,mcSize,"親機のDS");
  //      }
#endif
#if 0
        for(i = 1;i < mcSize; i++){
            if(adr[i] != CS_NONE){  //何かが送られてきてたら
                CommRingPuts(&_pComm->recvMidRing[aid] , adr, mcSize, __LINE__);
                //OHNO_SP_PRINT("middle %d %d\n",CommRingDataSize(&_pComm->recvMidRing[aid]),aid);
//                OHNO_PRINT(" まるまま中間リングに入れる %d %d \n", aid, CommRingDataSize(&_pComm->recvMidRing[aid]));
                break;
            }
        }
#endif
        if(!(adr[0] & _SEND_NO_DATA)){
            CommRingPuts(&_pComm->recvMidRing[aid] , adr, mcSize, __LINE__);
//            OHNO_PRINT("MidRingのこり%d\n",CommRingDataRestSize(&_pComm->recvMidRing[aid]));
        }
        _pComm->recvDSCatchFlg[aid]++;  // 通信をもらったことを記憶
    }else{   // MPモード
        _padDataRecv(adr, aid);
        if(adr[0] & _SEND_NO_DATA){   // データが空っぽの場合受け取らない
            return;
        }
        adr++;
        if(_RECV_BUFF_SIZE_PARENT > CommRingDataRestSize(&_pComm->recvServerRing[aid])){
            OHNO_PRINT("Error Throw:受信オーバー\n");
            return;
        }
//        if(aid==0)
//            DEBUG_DUMP(adr,_RECV_BUFF_SIZE_PARENT,"MP 受け取った");
        CommRingPuts(&_pComm->recvServerRing[aid] , adr, _RECV_BUFF_SIZE_PARENT, __LINE__);
    }
}

//==============================================================================
/**
 * 通信を送信したときに呼ばれるコールバック
 * @param   result  成功か失敗
 * @retval  none
 */
//==============================================================================

static void _sendCallbackFunc(BOOL result)
{
    if(result){
        _sendCallBack++;
    }
    else{
        GF_ASSERT_MSG(0,"send failed");
    }
}

//==============================================================================
/**
 * 通信を送信したときに呼ばれるコールバック 
 * @param   result  成功か失敗
 * @retval  none
 */
//==============================================================================

static void _sendServerCallback(BOOL result)
{
    if(result){
        _sendCallBackServer++;
    }
    else{
        GF_ASSERT_MSG(0,"send failed");
    }
}

//==============================================================================
/**
 * データの収集
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _updateMpData(void)
{
    u16 i;
    u8 *adr;
    int size;

    if(!_pComm){
        return;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        return;
    }
    {
        int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
        int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
        if(CommGetAloneMode()){   // aloneモードの場合
            if((_sendCallBack == _SEND_CB_FIRST_SENDEND) || (_sendCallBack == _SEND_CB_NONE)){
                _sendCallBack++;
                _sendCallbackFunc(TRUE);
                // 子機のふりをする部分          // 親機は自分でコールバックを呼ぶ
                _commRecvParentCallback(COMM_PARENT_ID, (u16*)_pComm->sSendBuf[_pComm->sendSwitch],
                                    mcSize);
                _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                _pComm->countSendRecv++; // MP送信親
#ifdef PM_DEBUG
                _pComm->countSendNum++;
#endif
                return;
            }
        }
        if(WH_GetSystemState() == WH_SYSSTATE_CONNECTED ){
            if(!CommIsConnect(CommGetCurrentID())){
                if(CommGetCurrentID()==1){
                    OHNO_PRINT("自分自身の接続がまだ\n");
                }
                return;
            }
            if((_sendCallBack == _SEND_CB_FIRST_SENDEND) || (_sendCallBack == _SEND_CB_NONE)){
                // 子機データ送信
                if(CommGetCurrentID() != COMM_PARENT_ID){
                    _sendCallBack++;
                    if(!WH_SendData(_pComm->sSendBuf[_pComm->sendSwitch],
                                    mcSize, _PORT_DATA_CHILD, _sendCallbackFunc)){
                        _sendCallBack--;
                        OHNO_PRINT("failed WH_SendData\n");
                    }
                    else{
                        _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                        _pComm->countSendRecv++; // MP送信
#ifdef PM_DEBUG
                        _pComm->countSendNum++;
#endif
                    }
                }
                else if(WH_GetBitmap() & 0xfffe){         // サーバーとしての処理 自分以外の誰かにつながっている時
                    _sendCallBack++;
                    _sendCallbackFunc(TRUE);
                    // 子機のふりをする部分          // 親機は自分でコールバックを呼ぶ
                    _commRecvParentCallback(COMM_PARENT_ID, (u16*)_pComm->sSendBuf[_pComm->sendSwitch],
                                        mcSize);
                    _pComm->sendSwitch = 1 - _pComm->sendSwitch;
                    _pComm->countSendRecv++; // MP送信
#ifdef PM_DEBUG
                    _pComm->countSendNum++;
#endif
                }
            }
            else{
//                OHNO_PRINT("sendCallBack != _SEND_CB_FIRST_SENDE\n");
            }
        }
    }
}

//==============================================================================
/**
 * キーの乱数を発生する キーが入力された時だけ動く
 * @param   none
 * @retval  エラーの時TRUE
 */
//==============================================================================

static void _keyRand(void)
{
    u16 pad = 0;

    if(_pComm->randPadType == _NONE_KEY){
        return;
    }
    if(!(_pComm->sendCont &
         (PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_KEY_UP|PAD_KEY_DOWN))){
        return;  // キー押されてない場合はここも使用しない
    }
    if(_pComm->randPadType == _REVERSE_KEY){   // リバースモード
        if(_pComm->sendCont & PAD_KEY_LEFT){
            pad |= PAD_KEY_RIGHT;
        }
        if(_pComm->sendCont & PAD_KEY_RIGHT){
            pad |= PAD_KEY_LEFT;
        }
        if(_pComm->sendCont & PAD_KEY_UP){
            pad |= PAD_KEY_DOWN;
        }
        if(_pComm->sendCont & PAD_KEY_DOWN){
            pad |= PAD_KEY_UP;
        }
    }
    else{
        if(_pComm->oldPad){   // ランダムモード
            pad = _pComm->oldPad;
            _pComm->randPadStep--;
            if(_pComm->randPadStep < 0){
                _pComm->oldPad = 0;
            }
        }
        else{
            switch(MATH_Rand32(&_pComm->sRand, 4)){
              case 0:
                pad = PAD_KEY_LEFT;
                break;
              case 1:
                pad = PAD_KEY_RIGHT;
                break;
              case 2:
                pad = PAD_KEY_UP;
                break;
              case 3:
                pad = PAD_KEY_DOWN;
                break;
            }
            _pComm->randPadStep = MATH_Rand32(&_pComm->sRand, 16);
            _pComm->oldPad = pad;
        }
    }
    _pComm->sendCont &= ~(PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_KEY_UP|PAD_KEY_DOWN);
    _pComm->sendCont += pad;
}

//==============================================================================
/**
 * キーをランダムモードにする
 * @param   none
 * @retval  エラーの時TRUE
 */
//==============================================================================

void CommSetKeyRandMode(void)
{
    _pComm->randPadType = _RANDOM_KEY;
}

void CommSetKeyReverseMode(void)
{
    _pComm->randPadType = _REVERSE_KEY;
}

void CommResetKeyRandMode(void)
{
    _pComm->randPadType = _NONE_KEY;
}


#define _COMM_DIR_UP  (0x00)
#define _COMM_DIR_DOWN  (0x04)
#define _COMM_DIR_LEFT  (0x08)
#define _COMM_DIR_RIGHT  (0x0C)
#define _COMM_SEND_KEY   (0x10)


//==============================================================================
/**
 * @brief   sendBuff ０のあまりBITを使用して キーデータを受信する
 *
 * @param   pRecvBuff  受け取りバッファ
 * @param   netID      netID
 * @retval  現在FALSEのみ
 */
//==============================================================================

static BOOL _padDataRecv(u8* pRecvBuff, int netID)
{
    int i;
    u8 keyBuff[2];

    _pComm->cont[netID] = 0;
    if(_COMM_SEND_KEY == (*pRecvBuff & _COMM_SEND_KEY)){
        keyBuff[ 0 ] = *pRecvBuff & 0x0c;
        if(keyBuff[ 0 ] == _COMM_DIR_UP){
            _pComm->cont[netID] |= PAD_KEY_UP;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_DOWN){
            _pComm->cont[netID] |= PAD_KEY_DOWN;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_LEFT){
            _pComm->cont[netID] |= PAD_KEY_LEFT;
        }
        else if(keyBuff[ 0 ] == _COMM_DIR_RIGHT){
            _pComm->cont[netID] |= PAD_KEY_RIGHT;
        }
        _pComm->speed[netID] = (*pRecvBuff >> 5) & 0x7;
    }
//    _pComm->trg[netID] = _pComm->contOld[netID] ^ _pComm->cont[netID];
  //  _pComm->contOld[netID] = _pComm->cont[netID];
    return TRUE;

    
#if 0
    // 1/60の通信から padは1/30しか必要ないので間引く処理
    _pComm->padGetSwitch[netID] = _pComm->padGetSwitch[netID] ? FALSE : TRUE;
    if(_pComm->padGetSwitch[netID]){
        return FALSE;
    }
    
    _pComm->cont[netID] = 0;
    keyBuff[0] = *pRecvBuff;

    // BIT格納
    for( i = 0; i < sizeof(_sendPadBit)/sizeof(u16); i++ ){
        if(keyBuff[ _sendPattern[i][0] ] & _sendPattern[i][1]){
            _pComm->cont[netID] |= _sendPadBit[i];
        }
    }
//    _pComm->trg[netID] = _pComm->contOld[netID] ^ _pComm->cont[netID];
//    _pComm->contOld[netID] = _pComm->cont[netID];
    return FALSE;
#endif
}

//==============================================================================
/**
 * @brief   子機側のアクションが行われたことを設定
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommActionCommandSet(void)
{
//    _pComm->actionCount = _ACTION_COUNT_MOVE;
}

//==============================================================================
/**
 * @brief   sendBuff ０のあまりBIT+1byteを使用して キーデータを送信する
 *          移動に必要な方向キー + Y のみ送っている  trg contを送信するので
 *          キーが押されている場合に送信量が1byte変化する
 * @param   sendSwitch  送るバッファのスイッチ
 * @retval  1バイト多く送信する場合1
 */
//==============================================================================

static BOOL _padDataSend(u8* pSendBuff)
{
    int i,k;
/*
    if(_pComm->actionCount != 0 ){
        _pComm->actionCount--;
        return FALSE;
    }
   */
#ifdef DEBUG_ONLY_FOR_ohno
    if(sys.cont & PAD_BUTTON_START){
        if(CommIsSendMoveData()==FALSE){
            OHNO_PRINT("CommIsSendMoveData()==FALSE\n");
        }
        else{
            OHNO_PRINT("CommIsSendMoveData()==TRUE\n");
        }
    }
#endif
    if(_pComm->sendKeyStop){
        return FALSE;
    }
    
    if(CommIsSendMoveData()==FALSE){
        return FALSE;  // 今回はパッドデータは送信しない
    }
#if 0
    // BIT格納
    for( i = 0; i < sizeof(_sendPadBit)/sizeof(u16); i++ ){
        if(_pComm->sendCont & _sendPadBit[i]){
            pSendBuff[ _sendPattern[i][0] ] |= _sendPattern[i][1];
        }
    }
#endif
    if(_pComm->timSendCond){
        _pComm->timSendCond--;
    }
    if(_pComm->sendCont & PAD_KEY_UP){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_UP | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_DOWN){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_DOWN | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_LEFT){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_LEFT | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    else if(_pComm->sendCont & PAD_KEY_RIGHT){
        pSendBuff[ 0 ] = pSendBuff[ 0 ] | _COMM_DIR_RIGHT | _COMM_SEND_KEY;
        _pComm->timSendCond = 8;
    }
    pSendBuff[ 0 ] |= (_pComm->sendSpeed << 5);
    return FALSE;
}

//==============================================================================
/**
 * 送信キューにあったものを送信バッファに入れる
 * @param   none
 * @retval  none
 */
//==============================================================================

static BOOL _setSendData(u8* pSendBuff)
{
    int i;
    int mcSize = CommGetServiceMaxChildSendByte(CommStateGetServiceNo());
    int machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;
    if(_pComm->bNextSendData == FALSE){  // 一回で送れる場合
        pSendBuff[0] = _SEND_NONE;
    }
    else{
        pSendBuff[0] = _SEND_NEXT;  // 一回で送れない場合
    }
    if(_transmissonType() == _MP_MODE){  // DS時はパットを送るBITが無いので送らない
        _padDataSend(pSendBuff);  // パッドデータを送信する
    }
    _pComm->bNextSendData = FALSE;
#if 0
    if(CommQueueIsEmpty(&_pComm->sendQueueMgr) && (_transmissonType() == _MP_MODE)){
        pSendBuff[0] |= _SEND_NO_DATA;  // 空っぽなら何も送らない
    }
#endif
    if(CommQueueIsEmpty(&_pComm->sendQueueMgr)){
        pSendBuff[0] |= _SEND_NO_DATA;  // 空っぽなら何も送らない
        if(pSendBuff[0] == _SEND_NO_DATA){
            return FALSE;  // 送るものが何も無い
        }
    }
    else{
        SEND_BUFF_DATA buffData;
        buffData.size = mcSize - 1;
        buffData.pData = &pSendBuff[1];
        if(!CommQueueGetData(&_pComm->sendQueueMgr, &buffData, TRUE)){
            _pComm->bNextSendData = TRUE;
        }
        if(_transmissonType() == _DS_MODE){
            _pComm->DSCount++;
//            OHNO_PRINT("DSデータセット %d\n",_pComm->DSCount);
            pSendBuff[0] |= ((_pComm->DSCount << 4) & 0xf0);  //DS通信順番カウンタ
        }
    }
#if 0
    if(CommGetCurrentID()==0){
        DEBUG_DUMP(pSendBuff,mcSize,"_setSendData");
    }
#endif
    return TRUE;
}

//==============================================================================
/**
 * 送信キューにあったものを送信バッファに入れる サーバーMP通信用
 * @param   pSendBuff 入れる送信バッファ
 * @retval  none
 */
//==============================================================================



static void _setSendDataServer(u8* pSendBuff)
{
    int i;

    pSendBuff[0] = _MP_DATA_HEADER;

#ifdef PM_DEBUG
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        if(_sendDataNext != _pComm->bNextSendDataServer){
            GF_ASSERT(0);
        }
    }
#endif

    if(_pComm->bNextSendDataServer == FALSE){  // 一回で送れる場合
        pSendBuff[1] = _SEND_NONE;
    }
    else{
        pSendBuff[1] = _SEND_NEXT;  // 一回で送れない場合
    }

    {
        u16 bitmap = WH_GetBitmap();
        pSendBuff[2] = bitmap >> 8;
        pSendBuff[3] = bitmap & 0xff;

        {
            SEND_BUFF_DATA buffData;
            buffData.size = _SEND_BUFF_SIZE_PARENT - 5;
            buffData.pData = &pSendBuff[5];
            if(CommQueueGetData(&_pComm->sendQueueMgrServer, &buffData, FALSE)){
                _pComm->bNextSendDataServer = FALSE;
                pSendBuff[4] = (_SEND_BUFF_SIZE_PARENT - 5) - buffData.size;
            }
            else{
                _pComm->bNextSendDataServer = TRUE;
                pSendBuff[4] = _SEND_BUFF_SIZE_PARENT - 5;
            }
#ifdef PM_DEBUG
            _sendDataNext = _pComm->bNextSendDataServer;
#endif

        }
    }
#if 0
    DEBUG_DUMP(pSendBuff, _SEND_BUFF_SIZE_PARENT, "MP SERVER SEND");
#endif
}


//==============================================================================
/**
 * 子機送信メソッド  大きいサイズのデータを送信する
 *     バックアップしないので dataの中身を書き換えると、
 *     書き換えたものを送ってしまう可能性がある
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendHugeData(int command, const void* data, int size)
{
    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
        //        OHNO_PRINT("接続してなくて送れなかった\n");
        return FALSE;   // 通信状態が悪い場合送らない
    }
    if(CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, FALSE)){
//        if(25 == command){
            //OHNO_SP_PRINT("%d ",CommGetCurrentID());
            //DEBUG_DUMP((u8*)data,size,"poke");
  //      }
#if _COMMAND_TEST
        OHNO_PRINT("<<<送信 NetId=%d -- size%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-キュ- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgr));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * 子機送信メソッド
 * 親機がデータを子機全員に送信するのは別関数
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendData(int command, const void* data, int size)
{
    OHNO_PRINT("< 送信 %d %d\n", command,CommQueueGetNowNum(&_pComm->sendQueueMgr));
//    GF_ASSERT_RETURN(size < 256 && "CommSendHugeDataを使ってください",FALSE);
    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
        OHNO_PRINT("接続してなくて送れなかった\n");
        return FALSE;   // 通信状態が悪い場合送らない
    }
    if(CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, TRUE)){
#if _COMMAND_TEST
        OHNO_PRINT("<<<送信 NetId=%d -- size%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-キュー無い- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgr));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}


//==============================================================================
/**
 * 親機専用サーバー送信メソッド
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

static BOOL _data_ServerSide(int command, const void* data, int size, BOOL bCopy)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // 親機以外は使えない
        GF_ASSERT(0 && "親以外は使用不可");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
//        OHNO_PRINT("接続してなくて送れなかった\n");
        return FALSE;   // 通信状態が悪い場合送らない
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS通信状態なのにサーバー送信が使われた\n");
        return CommSendData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, bCopy)){
#if _COMMAND_TEST
        OHNO_PRINT("<<S送信 id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S送信");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * 親機送信メソッド  大きいサイズのデータを送信する  サイズ固定
 *     バックアップしないので dataの中身を書き換えると、
 *     書き換えたものを送ってしまう可能性がある
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendFixHugeSizeData_ServerSide(int command, const void* data)
{
    return CommSendHugeData_ServerSide(command, data, 0);
}

//==============================================================================
/**
 * 親機送信メソッド  大きいサイズのデータを送信する
 *     バックアップしないので dataの中身を書き換えると、
 *     書き換えたものを送ってしまう可能性がある
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendHugeData_ServerSide(int command, const void* data, int size)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // 親機以外は使えない
        GF_ASSERT(0 && "親以外は使用不可");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
//        OHNO_PRINT("接続してなくて送れなかった\n");
        return FALSE;   // 通信状態が悪い場合送らない
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS通信状態なのにサーバー送信が使われた\n");
        return CommSendHugeData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, FALSE)){
#if 0
        OHNO_PRINT("<<S送信 id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S送信");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("-キュ無い- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgrServer));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * 親機専用サーバー送信メソッド
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendData_ServerSide(int command, const void* data, int size)
{
    if(CommGetCurrentID() != COMM_PARENT_ID){  // 親機以外は使えない
        CommSetError();
//        GF_ASSERT(0 && "親以外は使用不可");
        return FALSE;
    }
    if(!CommIsConnect(COMM_PARENT_ID)  && !CommGetAloneMode()){
        OHNO_PRINT("接続してなくて送れなかった\n");
        return FALSE;   // 通信状態が悪い場合送らない
    }
    if(_transmissonType() == _DS_MODE){
        OHNO_PRINT("WARRNING: DS通信状態なのにサーバー送信が使われた\n");
        return CommSendData(command, data, size);
    }

    if(CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, TRUE)){

//        OHNO_PRINT("qnum %d %d\n",command,CommQueueGetNowNum(&_pComm->sendQueueMgrServer));

#if _COMMAND_TEST
        OHNO_PRINT("<<S送信 id=%d size=%d ",CommGetCurrentID(), size);
        CommCommandDebugPrint(command);
//        DEBUG_DUMP(pSend, size, "S送信");
#endif
        return TRUE;
    }
#ifdef DEBUG_ONLY_FOR_ohno
    OHNO_PRINT("キュー無い- %d %d\n",CommGetCurrentID(),
               CommQueueGetNowNum(&_pComm->sendQueueMgrServer));
    GF_ASSERT(0);
#endif
    if(CommStateGetServiceNo() == COMM_MODE_UNDERGROUND){
        CommSetError();
    }
    return FALSE;
}

//==============================================================================
/**
 * 親機専用サーバー送信メソッド サイズ固定版
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendFixSizeData_ServerSide(int command, const void* data)
{
    return CommSendData_ServerSide(command, data, 0);
}

//==============================================================================
/**
 * 送信バッファ残り容量
 * @retval  サイズ
 */
//==============================================================================

int CommGetSendRestSize(void)
{
    return CommRingDataRestSize(&_pComm->sendRing);
}

//==============================================================================
/**
 * サーバ側の送信バッファ残り容量
 * @retval  サイズ
 */
//==============================================================================

int CommGetSendRestSize_ServerSide(void)
{
    return CommRingDataRestSize(&_pComm->sendServerRing);
}


static void _endCallBack(int netID,int command,int size,void* pTemp, _RECV_COMMAND_PACK* pRecvComm)
{
    CommCommandCallBack(netID, command, size, pTemp);
    pRecvComm->valCommand = CS_NONE;
    pRecvComm->valSize = 0xffff;
    pRecvComm->pRecvBuff = NULL;
    pRecvComm->dataPoint = 0;
}


//==============================================================================
/**
 * 受信したデータをプロセス中に処理する
 * @param   pRing  リングバッファのポインタ
 * @param   netID     処理しているnetID
 * @param   pTemp    コマンドを結合するためのtempバッファ
 * @retval  none
 */
//==============================================================================

static void _recvDataFuncSingle(RingBuffWork* pRing, int netID, u8* pTemp, BOOL bDebug, _RECV_COMMAND_PACK* pRecvComm)
{
    int size;
    u8 command;
    int bkPos;
    int realbyte;

    
    while( CommRingDataSize(pRing) != 0 ){
        bkPos = pRing->startPos;
        if(pRecvComm->valCommand != CS_NONE){
            command = pRecvComm->valCommand;
        }
        else{
            command = CommRingGetByte(pRing);
            if(command == CS_NONE){
                continue;
            }
        }
        bkPos = pRing->startPos;
        pRecvComm->valCommand = command;
//        OHNO_PRINT("c %d\n",command);
        if(bDebug){
            OHNO_PRINT(">>>cR %d %d %d\n", bkPos, CommRingDataSize(pRing), command);
        }
        if(pRecvComm->valSize != 0xffff){
            size = pRecvComm->valSize;
        }
        else{
            size = CommCommandGetPacketSize(command);
            if(_pComm->bError){
                return;
            }
            if(COMM_VARIABLE_SIZE == size){
                if( CommRingDataSize(pRing) < 1 ){  // 残りデータが1以下だった
                    pRing->startPos = bkPos;
                    break;
                }
                // サイズがない通信データはここにサイズが入っている
                size = CommRingGetByte(pRing)*0x100;
                size += CommRingGetByte(pRing);
                OHNO_PRINT("受信サイズ  %d\n",size);
                bkPos = pRing->startPos; // ２個進める
            }
            pRecvComm->valSize = size;
        }
        if(CommCommandCreateBuffCheck(command)){  // 受信バッファがある場合
            if(pRecvComm->pRecvBuff==NULL){
                pRecvComm->pRecvBuff = CommCommandCreateBuffStart(command, netID, pRecvComm->valSize);
            }
            realbyte = CommRingGets(pRing, pTemp, size - pRecvComm->dataPoint);
//            OHNO_SP_PRINT("id %d -- rest %d\n",netID, size - pRecvComm->dataPoint);
            if(pRecvComm->pRecvBuff){
                MI_CpuCopy8(pTemp, &pRecvComm->pRecvBuff[pRecvComm->dataPoint], realbyte);
            }
            pRecvComm->dataPoint += realbyte;
            if(pRecvComm->dataPoint >= size ){

//                if(25 == command){
  //                  OHNO_SP_PRINT("%d ",netID);
    //                DEBUG_DUMP(pRecvComm->pRecvBuff,size,"recv");
      //          }
                
                _endCallBack(netID, command, size, pRecvComm->pRecvBuff, pRecvComm);
            }
        }
        else{
            if( CommRingDataSize(pRing) >= size ){
                if(bDebug){
                    OHNO_PRINT(">>>受信 comm=%d id=%d -- size%d \n",command, netID, size);
                }
                CommRingGets(pRing, pTemp, size);
                _endCallBack(netID, command, size, (void*)pTemp, pRecvComm);
            }
            else{   // まだ届いていない大きいデータの場合ぬける
                //            OHNO_PRINT("結合待ち command %d size %d\n",command,size);
                pRing->startPos = bkPos;
                break;
            }
        }
    }
}

//==============================================================================
/**
 * 受信したデータをプロセス中に処理する
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _recvDataFunc(void)
{
    int id = COMM_PARENT_ID;
    int size;
    u8 command;
    int bkPos;

    if(!_pComm){
        return;
    }
    if(_pComm->bNotRecvCheck){
        return;
    }

    CommRingEndChange(&_pComm->recvRing);
    if(CommRingDataSize(&_pComm->recvRing) > 0){
        // 一個前の位置を変数に保存しておく
//        MI_CpuCopy8( &_pComm->recvRing,&_pComm->recvRingUndo, sizeof(RingBuffWork));
//        CommRingStartPush(&_pComm->recvRingUndo); //start位置を保存
#if 0
        OHNO_PRINT("-解析開始 %d %d-%d\n",id,
                   _pComm->recvRing.startPos,_pComm->recvRing.endPos);
#endif
//        OHNO_PRINT("子機解析 %d \n",id);
        _recvDataFuncSingle(&_pComm->recvRing, id, _pComm->pTmpBuff, TRUE, &_pComm->recvCommClient);
#if 0
        OHNO_PRINT("解析 %d %d-%d\n",id,
                   _pComm->recvRing.startPos,_pComm->recvRing.endPos);
#endif
    }
}

//==============================================================================
/**
 * 受信したデータをプロセス中に処理する
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _recvDataServerFunc(void)
{
    int id;
    int size;
    u8 command;
    int machineMax;

    if(!_pComm){
        return;
    }
    if(_pComm->bNotRecvCheck){
        return;
    }

    machineMax = CommLocalGetServiceMaxEntry(CommStateGetServiceNo())+1;

    for(id = 0; id < machineMax; id++){
        CommRingEndChange(&_pComm->recvServerRing[id]);
        
        if(CommRingDataSize(&_pComm->recvServerRing[id]) > 0){
#if 0
            OHNO_PRINT("解析開始 %d %d-%d\n",id,
                       _pComm->recvServerRing[id].startPos,_pComm->recvServerRing[id].endPos);
#endif
#if 0
            OHNO_PRINT("親機が子機%dを解析\n",id);
#endif
#if _COMMAND_TEST
    //        OHNO_PRINT("DS解析 %d\n",id);
#endif
            // 一個前の位置を変数に保存しておく
//            MI_CpuCopy8(&_pComm->recvServerRing[id],
  //                      &_pComm->recvServerRingUndo[id],
    //                    sizeof(RingBuffWork));
      //      CommRingStartPush(&_pComm->recvServerRingUndo[id]); //start位置を保存
//            OHNO_PRINT("親機が子機%dを解析\n",id);
            _recvDataFuncSingle(&_pComm->recvServerRing[id], id, _pComm->pTmpBuff, FALSE, &_pComm->recvCommServer[id]);
        }
    }
}

//==============================================================================
/**
 * データが送られてきたか確認する。
 * @param   netID       親機は_PARENT_INDEX　他は子機
 * @param   command     このデータが送られてきたのかどうか調べ利う
 * @param   retSsize    送られてきたデータのサイズを入れる
 * @param   data        送られてきたデータ
 * @retval  コマンドのデータをみつけたらTRUE
 */
//==============================================================================
#if 0
BOOL CommRecvData(int netID,int chkCommand, int* retSize, u8* data)
{
    if(FALSE == CommIsConnect(netID)){
        return FALSE;
    }
    if(_transmissonType() == _DS_MODE){
        return CommGetRecvData_ServerSide(netID,chkCommand,retSize,data);
    }
    return _getRecvDataSingle(&_pComm->recvRingUndo,
                              chkCommand, retSize, data, _pComm->pTmpBuff);
}
#endif

//==============================================================================
/**
 * データが送られてきたか確認する。サーバー専用
 * @param   netID       machine index
 * @param   command     このデータが送られてきたのかどうか調べ利う
 * @param   retSsize    送られてきたデータのサイズを入れる
 * @param   data        送られてきたデータ
 * @retval  コマンドのデータをみつけたらTRUE
 */
//==============================================================================
#if 0
BOOL CommGetRecvData_ServerSide(int netID,int chkCommand, int* retSize, u8* data)
{
    if(FALSE == CommIsConnect(netID)){
        return FALSE;
    }
    return _getRecvDataSingle(&_pComm->recvServerRingUndo[netID],
                              chkCommand, retSize, data, _pComm->pTmpBuff);
}
#endif
//==============================================================================
/**
 * 通信可能状態なのかどうかを返す ただしコマンドによるネゴシエーションがまだの状態
 * @param   親子機のnetID
 * @retval  TRUE  通信可能    FALSE 通信切断
 */
//==============================================================================
BOOL CommIsConnect(u16 netID)
{
    if(!_pComm){
        return FALSE;
    }
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        if(_pComm->bWifiConnect){
            int id = mydwc_getaid();
            if(-1 != id){
                if(netID == 0){
                    return TRUE;
                }
                else if(netID == 1){
                    return TRUE;
                }
            }
        }
        return FALSE;
    }
    if(!CommIsInitialize()){
        return FALSE;
    }
    if (WH_GetSystemState() != WH_SYSSTATE_CONNECTED) {
        return FALSE;
    }
    if(CommGetCurrentID()==netID){// 自分はONLINE
        return TRUE;
    }
    else if(CommGetCurrentID()==COMM_PARENT_ID){  // 親機のみ子機情報をLIBで得られる
        u16 bitmap = WH_GetBitmap();
        if( bitmap & (1<<netID)){
            return TRUE;
        }
    }
    else if(_pComm->bitmap & (1<<netID)){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 通信可能状態の人数を返す
 * @param   none
 * @retval  接続人数
 */
//==============================================================================
int CommGetConnectNum(void)
{
    int num = 0,i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(CommIsConnect(i)){
            num++;
        }
    }
    return num;
}

//==============================================================================
/**
 * 初期化しているかどうかを返す
 * @param   none
 * @retval  初期が終わっていたらTRUE
 */
//==============================================================================
BOOL CommIsInitialize(void)
{
    if(_pComm){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            return TRUE;
        }
    }
    return CommMPIsInitialize();
}

//==============================================================================
/**
 * 移動速度を入れる
 * @param   speed
 * @retval  
 */
//==============================================================================

void CommSetSpeed(u8 speed)
{
    _pComm->sendSpeed = speed;
}

//==============================================================================
/**
 * 移動速度を返す
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
u8 CommGetSpeed(int netID)
{
    return _pComm->speed[netID];
}

//==============================================================================
/**
 * パッドコントロールを返す
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
u16 CommGetPadCont(int netID)
{
    int cnt;

    if(!_pComm){
        return 0;
    }
    cnt = _pComm->cont[netID];
    _pComm->cont[netID] = 0;
    return cnt;
}

//==============================================================================
/**
 * パッドを送信可能にする
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
void CommEnableSendMoveData(void)
{
    if(_pComm){
        _pComm->sendCont |= 0x8000;
    }
}

//==============================================================================
/**
 * パッドを送信不可にする
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
void CommDisableSendMoveData(void)
{
    if(_pComm){
        _pComm->sendCont = 0;
    }
}

//==============================================================================
/**
 * パッドを送信不可にする
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
void CommStopSendMoveData(BOOL bStop)
{
    if(_pComm){
        _pComm->sendKeyStop = bStop;
    }
}

//==============================================================================
/**
 * パッドを送信不可にしているかどうかを得る
 * @param   netID     ネットID
 * @retval  key cond
 */
//==============================================================================
BOOL CommIsSendMoveData(void)
{
    if(_pComm){
        return (_pComm->sendCont & 0x8000);
    }
    return TRUE;
}

//==============================================================================
/**
 * サーバー側から子機に送る場合 送信キューへの追加
 * @param   command    comm_sharing.hに定義したラベル
 * @param   sendNetID
 * @param   data       送信したいデータ ない時はNULL
 *                     このデータは静的でなければならない  バッファに溜めないため
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSetSendQueue_ServerSide(int command, const void* data, int size)
{
    if(_transmissonType() == _DS_MODE){
        return CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, TRUE, FALSE);
    }
    else{
        return CommQueuePut(&_pComm->sendQueueMgrServer, command, (u8*)data, size, TRUE, FALSE);
    }
}

//==============================================================================
/**
 * クライアント側から親機に送る場合 送信キューへの追加
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 *                     このデータは静的でなければならない  バッファに溜めないため
 * @param   byte       送信量    コマンドだけの場合0
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSetSendQueue(int command, const void* data, int size)
{
    return CommQueuePut(&_pComm->sendQueueMgr, command, (u8*)data, size, FALSE, FALSE);
}

enum{
    _TRANS_NONE,
    _TRANS_LOAD,
    _TRANS_LOAD_END,
    _TRANS_SEND,
    _TRANS_SEND_END,
};


static void _transmission(void)
{
    BOOL bCatch=FALSE;

    if(!_pComm){
        return;
    }
    
    switch(_pComm->transmissionNum){
      case _TRANS_LOAD:
        if(_transmissonType() == _DS_MODE){
            bCatch = CommSendFixSizeData(CS_DSMP_CHANGE_REQ,&_pComm->transmissionSend);
        }
        else{
            bCatch = CommSendData_ServerSide(CS_DSMP_CHANGE_REQ, &_pComm->transmissionSend, 1);
        }
        if(bCatch){
            _pComm->transmissionNum = _TRANS_LOAD_END;
        }
        break;
      case _TRANS_SEND:
        if(CommSendFixSizeData(CS_DSMP_CHANGE_END,&_pComm->transmissionSend)){
            _commSetTransmissonType(_pComm->transmissionSend);  // 切り替える  親機はここで切り替えない
            _pComm->transmissionNum = _TRANS_NONE;
        }
        break;
    }

}

//==============================================================================
/**
 * DS通信MP通信の切り替え  CS_DSMP_CHANGE
 * @param   none
 * @retval  残り数
 */
//==============================================================================

void CommRecvDSMPChange(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    OHNO_PRINT("CommRecvDSMPChange 受信\n");
    _pComm->transmissionNum = _TRANS_LOAD;
    _pComm->transmissionSend = pBuff[0];
}

//==============================================================================
/**
 * DS通信MP通信の切り替え
 * @param   none
 * @retval  残り数
 */
//==============================================================================

void CommRecvDSMPChangeReq(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        return;
    }
    _pComm->transmissionSend = pBuff[0];
    _pComm->transmissionNum = _TRANS_SEND;
    OHNO_PRINT("CommRecvDSMPChangeReq 受信\n");
}

//==============================================================================
/**
 * DS通信MP通信の切り替え 終了処理 CS_DSMP_CHANGE_END
 * @param   none
 * @retval  残り数
 */
//==============================================================================

void CommRecvDSMPChangeEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    OHNO_PRINT("CommRecvDSMPChangeEND 受信\n");

    if(_pComm->transmissionNum == _TRANS_LOAD_END){
        _commSetTransmissonType(pBuff[0]);  // 切り替える
        _pComm->transmissionNum = _TRANS_NONE;
    }
}

//==============================================================================
/**
 * 自分の機のIDを返す
 * @param   
 * @retval  自分の機のID  つながっていない場合COMM_PARENT_ID
 */
//==============================================================================

u16 CommGetCurrentID(void)
{
    if(_pComm){
        if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
            int id = mydwc_getaid();
            if(id != -1){
                return id;
            }
        }
        else if(CommGetAloneMode()){
            return COMM_PARENT_ID;
        }
        else{
            return WH_GetCurrentAid();
        }
    }
    return COMM_PARENT_ID;
}

//==============================================================================
/**
 * 汎用送信メソッド  送信サイズ固定でしかも大きい場合
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendFixHugeSizeData(int command, const void* data)
{
    return CommSendHugeData(command, data, 0);
}

//==============================================================================
/**
 * 汎用送信メソッド  送信サイズ固定の場合
 * @param   command    comm_sharing.hに定義したラベル
 * @param   data       送信したいデータ ない時はNULL
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendFixSizeData(int command, const void* data)
{
    return CommSendData(command, data, 0);
}

//==============================================================================
/**
 * 汎用送信メソッド  コマンド以外存在しない場合
 * @param   command    comm_sharing.hに定義したラベル
 * @retval  送信キューに入ったかどうか
 */
//==============================================================================

BOOL CommSendFixData(int command)
{
    return CommSendData(command, NULL, 0);
}

//==============================================================================
/**
 * WHライブラリで　通信状態のBITを確認
 * @param   none
 * @retval  接続がわかるBIT配列
 */
//==============================================================================

BOOL CommIsChildsConnecting(void)
{
    return CommMPIsChildsConnecting();
}

//==============================================================================
/**
 * エラー状態かどうか
 * @param   none
 * @retval  エラーの時TRUE
 */
//==============================================================================

BOOL CommIsError(void)
{
    if(CommGetAloneMode()){  // 一人モードの場合ここはエラーにしない
        return FALSE;
    }
    if(_pComm){
        if(_pComm->bError){
            CommStateSetErrorCheck(TRUE,TRUE);
            return TRUE;
        }
    }
    return CommMPIsError();
}

//==============================================================================
/**
 * サービス番号に対応した子機送信byte数を得ます
 * サービス番号は include/communication/comm_def.hにあります
 * @param   serviceNo サービス番号
 * @retval  子機台数
 */
//==============================================================================

u16 CommGetServiceMaxChildSendByte(u16 serviceNo)
{
    if(CommLocalGetServiceMaxEntry(serviceNo) >= COMM_WIDE_BYTE_SEND_CHILDNUM){
        return _SEND_BUFF_SIZE_CHILD;
    }
    if(_transmissonType() == _MP_MODE){
        return _SEND_BUFF_SIZE_CHILD;
    }
    return _SEND_BUFF_SIZE_4CHILD;
}

//==============================================================================
/**
 * 最大接続人数を得る
 * @param   none
 * @retval  最大接続人数
 */
//==============================================================================

int CommGetMaxEntry(int service)
{
    return CommLocalGetServiceMaxEntry(service)+1;
}

//==============================================================================
/**
 * 最小接続人数を得る
 * @param   none
 * @retval  最小接続人数
 */
//==============================================================================

int CommGetMinEntry(int service)
{
    return CommLocalGetServiceMinEntry(service)+1;
}

//==============================================================================
/**
 * 一人通信モードを設定
 * @param   bAlone    一人通信モード
 * @retval  none
 */
//==============================================================================

void CommSetAloneMode(BOOL bAlone)
{
    if(_pComm){
        _pComm->bAlone = bAlone;
    }
}

//==============================================================================
/**
 * 一人通信モードかどうかを取得
 * @param   none
 * @retval  一人通信モードの場合TRUE
 */
//==============================================================================

BOOL CommGetAloneMode(void)
{
    if(_pComm){
        return _pComm->bAlone;
    }
    return FALSE;
}

//==============================================================================
/**
 * 自動終了コマンド受信
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommRecvAutoExit(int netID, int size, void* pData, void* pWork)
{
    u8 dummy;

    OHNO_PRINT("CommRecvAutoExit 受信 \n");
    if(!CommMPIsAutoExit()){
        if(CommGetCurrentID() == COMM_PARENT_ID){   // 自分が親の場合みんなに逆返信する
            CommSendFixSizeData_ServerSide(CS_AUTO_EXIT, &dummy);
        }
    }
    CommMPSetAutoExit();
}

#ifdef PM_DEBUG

//==============================================================================
/**
 * デバッグ用にダンプを表示する
 * @param   adr           表示したいアドレス
 * @param   length        長さ
 * @param   pInfoStr      表示したいメッセージ
 * @retval  サービス番号
 */
//==============================================================================

void CommDump_Debug(u8* adr, int length, char* pInfoStr)
{
    int i,j = 0;

    OHNO_PRINT("%s \n",pInfoStr);
    while(length){
        OHNO_PRINT(">> ");
        for(i = 0 ; i < 8 ; i++){
            OHNO_PRINT("%2x ",adr[j]);
            j++;
            if(j == length){
                break;
            }
        }
        OHNO_PRINT("\n");
        if(j == length){
            break;
        }
    }
    OHNO_PRINT(" --end\n");
}

//==============================================================================
/**
 * デバッグオート移動切り替え
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSwitchAutoMove_Debug(void)
{
    _pComm->DebugAutoMove =
        (_pComm->DebugAutoMove) ? 0 : 1;
}

//==============================================================================
/**
 * デバッグオート移動切
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _debugAutoMove(void)
{
    if(_pComm->DebugAutoMove){
        _pComm->DebugAutoMove++;
        if(_pComm->DebugAutoMove==0){
            _pComm->DebugAutoMove++;
        }
        if(_pComm->DebugAutoMove & 0x08){
            _pComm->sendCont |= (PAD_KEY_LEFT | PAD_BUTTON_Y); //ダッシュ移動
        }
        else{
            _pComm->sendCont |= (PAD_KEY_RIGHT | PAD_BUTTON_Y); //ダッシュ移動
        }
    }
}
#endif

//==============================================================================
/**
 * WEP Key の種用の乱数生成機の初期化
 * @param   pRand  乱数管理構造体
 * @retval  none
 */
//==============================================================================

void CommRandSeedInitialize(MATHRandContext32* pRand)
{
    u64 randSeed = 0;
    RTCDate date;
    RTCTime time;
    
    GF_RTC_GetDateTime(&date, &time);
    randSeed = (((((((u64)date.year * 16ULL + date.month) * 32ULL)
                   + date.day) * 32ULL + time.hour) * 64ULL + time.minute)
                * 64ULL + (time.second + sys.vsync_counter));
    MATH_InitRand32(pRand, randSeed);
}


//==============================================================================
/**
 * 特定のコマンドを送信し終えたかどうかを調べる サーバ側
 * @param   command 調べるコマンド
 * @retval  コマンドが在ったらTRUE
 */
//==============================================================================


BOOL CommIsSendCommand_ServerSize(int command)
{
    return CommQueueIsCommand(&_pComm->sendQueueMgrServer, command);

}


//==============================================================================
/**
 * 特定のコマンドを送信し終えたかどうかを調べる クライアント側
 * @param   command 調べるコマンド
 * @retval  コマンドが在ったらTRUE
 */
//==============================================================================


BOOL CommIsSendCommand(int command)
{
    return CommQueueIsCommand(&_pComm->sendQueueMgr, command);

}


//==============================================================================
/**
 * キューが空っぽかどうか サーバー側
 * @param   none
 * @retval  コマンドが在ったらFALSE
 */
//==============================================================================

BOOL CommIsEmptyQueue_ServerSize(void)
{
    return CommQueueIsEmpty(&_pComm->sendQueueMgrServer);

}

//==============================================================================
/**
 * キューが空っぽかどうか
 * @param   none
 * @retval  コマンドが在ったらFALSE
 */
//==============================================================================

BOOL CommIsEmptyQueue(void)
{
    return CommQueueIsEmpty(&_pComm->sendQueueMgr);

}

//==============================================================================
/**
 * wifi接続したかどうかを設定する
 * @param   none
 * @retval  コマンドが在ったらFALSE
 */
//==============================================================================

void CommSetWifiConnect(BOOL bConnect)
{
    // 通信待機状態にあるかどうかを伝える
    _pComm->bWifiConnect = bConnect;
}

//==============================================================================
/**
 * 戦闘に入る前の敵味方の立ち位置を設定
 * @param   no   立っていた位置の番号に直したもの
 * @param   netID   通信のID
 * @retval  none
 */
//==============================================================================
void CommSetStandNo(int no,int netID)
{
    if(_pComm){
        _pComm->standNo[netID] = no;
        OHNO_PRINT("id = %d  がたってるところは %d\n",netID,no);
    }
}

//==============================================================================
/**
 * 戦闘に入る前の敵味方の立ち位置を得る
 * @param   netID 通信のID
 * @retval  立っていた位置の番号に直したもの  0-3  0,2 vs 1,3
 */
//==============================================================================
int CommGetStandNo(int netID)
{
    if(_pComm){
        if(_pComm->standNo[netID] != 0xff){
            OHNO_PRINT("立ち位置 %d ばん id%d\n",_pComm->standNo[netID], netID);
            return _pComm->standNo[netID];
        }
    }
    return netID;
}

//==============================================================================
/**
 * VCHAT状態かどうか
 * @param   none
 * @retval  VCHAT状態ならTRUE
 */
//==============================================================================

BOOL CommIsVChat(void)
{
    if(CommStateGetServiceNo() < COMM_MODE_BATTLE_SINGLE_WIFI){
        return FALSE;
    }
    return mydwc_IsVChat();

}

//==============================================================================
/**
 * WIFI通信を同期通信するか、非同期通信するかの切り替えを行う
 * @param   TRUE 同期 FALSE 非同期
 * @retval  none
 */
//==============================================================================

void CommSetWifiBothNet(BOOL bFlg)
{
    if(CommStateGetServiceNo() >= COMM_MODE_BATTLE_SINGLE_WIFI){
        _pComm->bWifiSendRecv = bFlg;
        if(bFlg){
            _pComm->countSendRecv = 0;
            _pComm->countSendRecvServer[0] = 0;
            _pComm->countSendRecvServer[1] = 0;
        }
        OHNO_PRINT("oo同期切り替え %d\n",bFlg);
    }
}

//==============================================================================
/**
 * キーを送ったのかどうか得る
 * @param   TRUE 同期 FALSE 非同期
 * @retval  none
 */
//==============================================================================

BOOL CommSysIsMoveKey(void)
{
    if(_pComm->timSendCond){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * エラーにする場合TRUE
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSetError(void)
{
    _pComm->bError=TRUE;
}

//==============================================================================
/**
 * 通信を止める
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSystemShutdown(void)
{
    if(_pComm){
        _pComm->bShutDown = TRUE;
    }
}


void CommSystemResetQueue_Server(void)
{
    CommQueueManagerReset(&_pComm->sendQueueMgrServer);
}

void CommSystemRecvStop(BOOL bFlg)
{
    if(_pComm){
        _pComm->bNotRecvCheck = bFlg;
    }
}

