//=============================================================================
/**
 * @file	comm_queue.c
 * @bfief	（送信）キューの仕組みを管理する関数
 * @author	katsumi ohno
 * @date	06/01/29
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"
#include "comm_queue.h"

//==============================================================================
/**
 * 開いているキューを返す
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param   queueMax  キュー数
 * @retval  none
 */
//==============================================================================

static SEND_QUEUE* _freeQueue(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command == CS_FREE){
            return pFree;
        }
        pFree++;
    }
    return NULL;   // コマンドが無い
}

//==============================================================================
/**
 * キューに何か入っているかどうかを確認する
 * @param   pQueueMgr キューマネージャーのポインタ
 * @retval  空ならばTRUE
 */
//==============================================================================

BOOL CommQueueIsEmpty(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command != CS_FREE){
            return FALSE;
        }
        pFree++;
    }
    return TRUE;   // コマンドが無い
}

//==============================================================================
/**
 * キューの数を得る
 * @param   pQueueMgr キューマネージャーのポインタ
 * @retval  空ならばTRUE
 */
//==============================================================================

int CommQueueGetNowNum(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_QUEUE* pFree = pQueueMgr->heapTop;
    int i,j = 0;

    for(i = 0;i < pQueueMgr->max; i++){
        if(pFree->command != CS_FREE){
            j++;
        }
        pFree++;
    }
    return j;
}

//==============================================================================
/**
 * キューを消す
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param   queueMax  キュー数
 * @retval  none
 */
//==============================================================================

static BOOL _deleteQueue(SEND_TERMINATOR* pTerm)
{
    if(pTerm->pTop != NULL){
        if(pTerm->pTop->next!= NULL){
            pTerm->pTop = pTerm->pTop->next;
            pTerm->pTop->prev = NULL;
        }
        else{
            pTerm->pTop = NULL;
            pTerm->pLast = NULL;
        }
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 送信データのヘッダー部分をバッファに入れる
 * @param   pSendBuff   送信バッファ管理構造体ポインタ
 * @param   byte        セットするデータ
 * @retval  0になったらTRUE
 */
//==============================================================================

static BOOL _setSendData(SEND_BUFF_DATA* pSendBuff ,u8 byte)
{
    *pSendBuff->pData = byte;
    pSendBuff->pData++;
    pSendBuff->size--;
    if(pSendBuff->size==0){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 送信データのヘッダー部分をバッファに入れる
 * @param   pQueue  キューのポインタ
 * @param   pSendBuff   送信バッファ管理構造体ポインタ
 * @retval  蓄えたらFALSE
 */
//==============================================================================

static BOOL _dataHeadSet(SEND_QUEUE* pQueue, SEND_BUFF_DATA* pSendBuff)
{
    int cs = CommCommandGetPacketSize(pQueue->command);

    if( cs == COMM_VARIABLE_SIZE){
        if(pSendBuff->size < 3){
            pQueue->bHeadSet = FALSE;
            return TRUE;
        }
    }
    else{
        if(pSendBuff->size < 1){
            pQueue->bHeadSet = FALSE;
            return TRUE;
        }
    }
    _setSendData(pSendBuff,pQueue->command);
    if(cs == COMM_VARIABLE_SIZE){
        _setSendData(pSendBuff,(pQueue->size >> 8)  & 0xff);
        _setSendData(pSendBuff,pQueue->size & 0xff);
    }
    else{
        pQueue->size = cs;
    }
    pQueue->bHeadSet = TRUE;
    return FALSE;
}

//==============================================================================
/**
 * キューから送信バッファに移す
 * @param   pQueue  キュー
 * @param   pSendBuff   送信バッファ
 * @retval  ヘッダーが入らなかった場合TRUE
 */
//==============================================================================

static BOOL _dataCopyQueue(SEND_QUEUE* pQueue, SEND_BUFF_DATA* pSendBuff, RingBuffWork* pSendRing, BOOL bNextPlus)
{
    int i;
    int size;
    int cs = CommCommandGetPacketSize(pQueue->command);
    if( cs == COMM_VARIABLE_SIZE){
        size = 3;
    }
    else{
        size = 1;
    }
    if((pSendBuff->size < (pQueue->size + size)) && (!bNextPlus)){  // キューのほうがでかい場合
        return FALSE;
    }
    if(pQueue->bHeadSet != TRUE){
        if(_dataHeadSet(pQueue, pSendBuff)){
            return FALSE;
        }
    }
//    if((pSendBuff->size < pQueue->size) && (!bNextPlus)){  // キューのほうがでかい場合
//        return FALSE;  // 前に移動
//    }
    if(pSendBuff->size < pQueue->size){  // キューのほうがでかい場合
        if(pQueue->bRing){
            CommRingGets(pSendRing, pSendBuff->pData, pSendBuff->size);
        }
        else{
          //  OHNO_PRINT("-----%x-%x--%d\n",(int)pQueue->pData, (int)pSendBuff->pData , pSendBuff->size);
//            MI_CpuCopy8( pQueue->pData, pSendBuff->pData, pSendBuff->size);
            
            for(i = 0;i < pSendBuff->size;i++){
                pSendBuff->pData[i] = pQueue->pData[i];
            }
        }
//        OHNO_PRINT("-----%d-%d--\n",pQueue->command, pQueue->size);
        
        pQueue->pData += pSendBuff->size;  // アドレスを進める
        pQueue->size -= pSendBuff->size;  // 送信サイズ減らす
        pSendBuff->size = -1;  // 残りを-1にする
        return TRUE;
    }
    // 同じもしくは小さい場合
    if(pQueue->bRing){
        CommRingGets(pSendRing, pSendBuff->pData, pQueue->size);
    }
    else{
        MI_CpuCopy8( pQueue->pData, pSendBuff->pData, pQueue->size);
    }
    pSendBuff->pData += pQueue->size;  // アドレスを進める
    pSendBuff->size -= pQueue->size; // サイズは減らす
    return TRUE;
}


//==============================================================================
/**
 * キューを蓄える
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param   command   送信コマンド
 * @param   pDataArea  送信データ
 * @param   size    サイズ
 * @param   bFast  優先度が高いデータ?
 * @param   bSave  保存するかどうか
 * @retval  蓄えたらTRUE
 */
//==============================================================================

BOOL CommQueuePut(SEND_QUEUE_MANAGER* pQueueMgr,int command, u8* pDataArea, int size, BOOL bFast, BOOL bSave)
{
    SEND_QUEUE* pLast;
    SEND_QUEUE* pFree = _freeQueue(pQueueMgr);
    SEND_TERMINATOR* pTerm;
    int cSize;

    bFast = TRUE;
    if(pFree== NULL){
        OHNO_SP_PRINT("---キューが無い\n");
        return FALSE;
    }
    
    GF_ASSERT(size < 65534 && "65534以上は分割");
    cSize = CommCommandGetPacketSize(command);

    if(COMM_VARIABLE_SIZE == cSize){
        cSize = size;
    }
    if(bSave){
        int rest = CommRingDataRestSize(pQueueMgr->pSendRing);
        if((cSize+3) >= rest){  // 送信バッファをオーバーしてしまう
            OHNO_PRINT("送信バッファオーバー com = %d size = %d / %d\n", command, cSize, rest);
            return FALSE;
        }
        CommRingPuts(pQueueMgr->pSendRing, pDataArea, cSize, __LINE__);
        CommRingEndChange(pQueueMgr->pSendRing);
        pFree->bRing = TRUE;
    }
    pFree->size = cSize;
    pFree->command = command;
    pFree->pData = pDataArea;
    if(bFast == TRUE){
        pTerm = &pQueueMgr->fast;
    }
    else{
        pTerm = &pQueueMgr->stock;
    }
    if(pTerm->pLast==NULL){
        pTerm->pLast = pFree;
        pTerm->pTop = pFree;
    }
    else{
        pTerm->pLast->next = pFree;
        pFree->prev = pTerm->pLast;
        pTerm->pLast = pFree;
    }
    return TRUE;
}

//==============================================================================
/**
 * キューを出す
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param
 * @retval  none
 */
//==============================================================================

static SEND_QUEUE* _queueGet(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_TERMINATOR* pTerm;

    if(pQueueMgr->pNow != NULL){
        return pQueueMgr->pNow;
    }
    if(pQueueMgr->fast.pTop != NULL){
        return pQueueMgr->fast.pTop;
    }
    if(pQueueMgr->stock.pTop != NULL){
        return pQueueMgr->stock.pTop;
    }
    return NULL;
}


//==============================================================================
/**
 * キューを一個削り次に進める
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param
 * @retval  none
 */
//==============================================================================

static void _queueNext(SEND_QUEUE_MANAGER* pQueueMgr)
{
    SEND_TERMINATOR* pTerm;

    if(pQueueMgr->pNow != NULL){
        pQueueMgr->pNow = NULL;
    }
    else{
        if(!_deleteQueue( &pQueueMgr->fast )){
            _deleteQueue( &pQueueMgr->stock );
        }
    }
}

//==============================================================================
/**
 * 指定バイト分バッファに入れる
 * @param   pQueueMgr  キューマネージャーのポインタ
 * @param   pSendBuff  送信バッファ構造体のポインタ
 * @retval  続きデータがない場合TRUE データが連続している場合FALSE
 */
//==============================================================================

BOOL CommQueueGetData(SEND_QUEUE_MANAGER* pQueueMgr, SEND_BUFF_DATA *pSendBuff, BOOL bNextPlus)
{
    int ret;
    int i;
    int bNextPlusFirst = TRUE;

    while(pSendBuff->size > 0){
        SEND_QUEUE* pQueue = _queueGet(pQueueMgr);
        if(NULL == pQueue){
            break;
        }
        _queueNext(pQueueMgr);
        // ヘッダー送信できない
        if(!_dataCopyQueue(pQueue, pSendBuff, pQueueMgr->pSendRing, bNextPlusFirst)){
            pQueueMgr->pNow = pQueue;  // 次の最初で送信できるようにセット
            break;
        }
        if( -1 == pSendBuff->size ){  // データが詰まっている場合
            pQueueMgr->pNow = pQueue;  // 次の最初で送信できるようにセット
            return FALSE;
        }
        else{
            MI_CpuFill8(pQueue, 0, sizeof(SEND_QUEUE));  // キューを消す
        }
        bNextPlusFirst = bNextPlus;
    }
    for(i = 0 ; i < pSendBuff->size; i++){
        *pSendBuff->pData = CS_NONE;
        pSendBuff->pData++;
    }
    return TRUE;
}



//==============================================================================
/**
 * キューMANAGERの初期化
 * @param   pQueueMgr キューマネージャーのポインタ
 * @param   queueMax  キュー数
 * @param   RingBuffWork 実データを保存する場合のリングバッファワーク
 * @retval  none
 */
//==============================================================================

void CommQueueManagerInitialize(SEND_QUEUE_MANAGER* pQueueMgr, int queueMax, RingBuffWork* pSendRing)
{
    MI_CpuFill8(pQueueMgr, 0 ,sizeof(SEND_QUEUE_MANAGER));
    pQueueMgr->heapTop = sys_AllocMemory(HEAPID_COMMUNICATION,
                                         sizeof(SEND_QUEUE)*queueMax);
    MI_CpuFill8(pQueueMgr->heapTop, 0 ,sizeof(SEND_QUEUE)*queueMax);
    pQueueMgr->max = queueMax;
    pQueueMgr->pSendRing = pSendRing;
}


//==============================================================================
/**
 * キューMANAGERのリセット
 * @param   pQueueMgr キューマネージャーのポインタ
 * @retval  none
 */
//==============================================================================

void CommQueueManagerReset(SEND_QUEUE_MANAGER* pQueueMgr)
{
    MI_CpuFill8(pQueueMgr->heapTop, 0 ,sizeof(SEND_QUEUE) * pQueueMgr->max);
    pQueueMgr->fast.pTop = NULL;     // すぐ送る送信キュー
    pQueueMgr->fast.pLast = NULL;     // すぐ送る送信キュー
    pQueueMgr->stock.pTop = NULL;    // 後で送ればいいキュー
    pQueueMgr->stock.pLast = NULL;    // 後で送ればいいキュー
    pQueueMgr->pNow = NULL;   // 今送っている最中のキュー
}

//==============================================================================
/**
 * キューMANAGERの終了
 * @param   pQueueMgr キューマネージャーのポインタ
 * @retval  none
 */
//==============================================================================

void CommQueueManagerFinalize(SEND_QUEUE_MANAGER* pQueueMgr)
{
    sys_FreeMemoryEz( pQueueMgr->heapTop );
}


//==============================================================================
/**
 * キューが存在するかどうか
 * @param   pQueueMgr  キューマネージャーのポインタ
 * @param   command    調べるコマンド
 * @retval  あったらTRUE
 */
//==============================================================================

BOOL CommQueueIsCommand(SEND_QUEUE_MANAGER* pQueueMgr, int command)
{
    int i;
    SEND_QUEUE* pNext = pQueueMgr->heapTop;

    for(i = 0; i < pQueueMgr->max; i++){
        if(pNext->command == command){
            return TRUE;
        }
        pNext++;
    }
    return FALSE;
}


//==============================================================================
/**
 * キューMANAGERのテスト
 * @param   none
 * @retval  none
 */
//==============================================================================
#ifdef PM_DEBUG

void CommQueueDebugTest(void)
{
    SEND_QUEUE_MANAGER mgr;
    u8 data1[30];
    u8 data2[22];
    SEND_BUFF_DATA buffData;
    u8 dummy[100];
    u8 ringbuff[50];
    int i;
    RingBuffWork sendRing;

    MI_CpuFill8(data1,2,30);
    MI_CpuFill8(data2,4,22);
    MI_CpuFill8(ringbuff,3,50);
    CommRingInitialize(&sendRing, ringbuff, 50);

    // ３本キュー作成
    CommQueueManagerInitialize(&mgr,3,&sendRing);

    // ----- テスト１
    CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 30, TRUE, TRUE);

    for(i = 0; i < 50; i++){
        if(i < 30){
            GF_ASSERT(ringbuff[i] == 2);
        }
        else{
            GF_ASSERT(ringbuff[i] == 3);
        }
    }

    
    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size==-1);
    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0 && "i=1");
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 30 && "i=2");
        }
        else if(i < 25){
            GF_ASSERT(dummy[i] == 2 && "i<25");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i>=25");
        }
    }
    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == (25-8));

    GF_ASSERT(mgr.pNow == NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 8){
            GF_ASSERT(dummy[i] == 2 && "i < 5");
        }
        else if(i < 25){
            GF_ASSERT(dummy[i] == CS_NONE && "CS_NONE");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i >= 5");
        }
    }
    buffData.size = 25;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == (25));

    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 25){
            GF_ASSERT(dummy[i] == CS_NONE && "i<25 CS_NONE");
        }
        else{
            GF_ASSERT(dummy[i] == 0xff && "i  all");
        }
    }

    // テスト２
    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);
    GF_ASSERT(mgr.fast.pLast == mgr.fast.pTop);

    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data2, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pTop->next != NULL);
    GF_ASSERT(mgr.fast.pTop->next->next == NULL);


    GF_ASSERT(CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, FALSE));

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pTop->next != NULL);
    GF_ASSERT(mgr.fast.pTop->next->next != NULL);

    // これはキューに入らない
//    GF_ASSERT(!CommQueuePut(&mgr, CS_DEBUG_VARIABLE, data1, 10, TRUE, TRUE));


    buffData.size = 12;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 12){
            GF_ASSERT(dummy[i] == 2);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }
    buffData.size = 12;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop != NULL);
    GF_ASSERT(mgr.fast.pLast != NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == 2);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 3){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 12){
            GF_ASSERT(dummy[i] == 4);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }

    // わざと小さく読み込むと、続きだけが入っている
    buffData.size = 4;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == 2);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i < 2){
            GF_ASSERT(dummy[i] == 4);
        }
        else if(i < 4){
            GF_ASSERT(dummy[i] == CS_NONE);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }

    /// 最後は３番目のコマンドが頭から入っている
    buffData.size = 4;
    buffData.pData = dummy;
    MI_CpuFill8(dummy, 0xff, 100);
    GF_ASSERT(!CommQueueGetData(&mgr, &buffData, TRUE));
    GF_ASSERT(buffData.size == -1);

    GF_ASSERT(mgr.pNow != NULL);
    GF_ASSERT(mgr.fast.pTop == NULL);
    GF_ASSERT(mgr.fast.pLast == NULL);

    for(i = 0; i < 100; i++){
        if(i == 0){
            GF_ASSERT(dummy[i] == CS_DEBUG_VARIABLE);
        }
        else if(i == 1){
            GF_ASSERT(dummy[i] == 0);
        }
        else if(i == 2){
            GF_ASSERT(dummy[i] == 10);
        }
        else if(i < 4){
            GF_ASSERT(dummy[i] == 2);
        }
        else{
            GF_ASSERT(dummy[i] == 0xff);
        }
    }
    CommQueueManagerFinalize(&mgr);

//   GF_ASSERT(0 && "ok");  //テスト完了
}

#endif

