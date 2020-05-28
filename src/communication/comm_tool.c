//=============================================================================
/**
 * @file	comm_tool.c
 * @brief	通信を使った汎用関数
 * @author	Katsumi Ohno
 * @date    2006.03.14
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "system/snd_tool.h"


//汎用データの１パケット
#define _TEMPDATA_SIZE (70)

//==============================================================================
// static宣言
//==============================================================================

typedef struct _COMM_TOOL_WORK_t COMM_TOOL_WORK;


typedef struct{
    u8 no;
    u8 listNo;
}_ListResult;

typedef struct _COMM_TOOL_WORK_t{
    // リスト
    _ListResult listNo[COMM_MACHINE_MAX];     // 同期コマンド用
    u8 timingSync[COMM_MACHINE_MAX];     // 同期コマンド用
    //------------------  tempデータ用バッファ
    u8 tempWork[COMM_MACHINE_MAX][_TEMPDATA_SIZE];
    u8 tempRecv[COMM_MACHINE_MAX];
    //-------------------
    u8 timingSyncEnd;     // 同期コマンド用
    u8 timingSyncMy;  // 自分が送ったNO
    u8 timingSend;
};

static COMM_TOOL_WORK* _pCT = NULL;  ///<　ワーク構造体のポインタ


//==============================================================================
/**
 * 初期化
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommToolInitialize(int heapID)
{
    int i;
    
    if(!_pCT){
        _pCT = sys_AllocMemory(heapID,sizeof(COMM_TOOL_WORK));
        MI_CpuFill8(_pCT,0,sizeof(COMM_TOOL_WORK));
    }


    for(i = 0; i< COMM_MACHINE_MAX;i++){
        _pCT->timingSync[i]=0xff;     // 同期コマンド用
    }
    _pCT->timingSyncEnd = 0xff;     // 同期コマンド用
    _pCT->timingSyncMy = 0xff;
    _pCT->timingSend = FALSE;

}

//==============================================================================
/**
 * 開放
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommToolFinalize(void)
{
    sys_FreeMemoryEz(_pCT);
    _pCT = NULL;
}

//==============================================================================
/**
 * 確認
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

BOOL CommToolIsInitialize(void)
{
    if(_pCT){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 * タイミングコマンドを受信した   CS_TIMING_SYNC
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSync(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 syncNo = pBuff[0];
    u8 sendBuff[2];
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        sendBuff[0] = netID;
        sendBuff[1] = syncNo;
        CommSendFixSizeData_ServerSide(CS_TIMING_SYNC_INFO, &sendBuff);
        OHNO_PRINT("同期受信 %d %d\n",netID,syncNo);
        _pCT->timingSync[netID] = syncNo;     // 同期コマンド用
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            if(CommIsConnect(i)){
                if(syncNo != _pCT->timingSync[i]){
                    // 同期していない
                    return;
                }
            }
        }
        CommSendFixSizeData_ServerSide(CS_TIMING_SYNC_END, &syncNo);
    }
}


//==============================================================================
/**
 * タイミングコマンドINFOを受信した   CS_TIMING_SYNC_INFO
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSyncInfo(int netID, int size, void* pData, void* pWork)
{
    // 子機が状況を把握できるようにコマンドが送られてくる
    u8* pBuff = pData;
    
    _pCT->timingSync[pBuff[0]] = pBuff[1];     // 同期コマンド用
}

//==============================================================================
/**
 * タイミングコマンドENDを受信した   CS_TIMING_SYNC_END
 * @param   callback用引数
 * @retval  none
 */
//==============================================================================

void CommRecvTimingSyncEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    u8 syncNo = pBuff[0];

    OHNO_PRINT("全員同期コマンド受信 %d %d\n", syncNo);
    _pCT->timingSyncEnd = syncNo;     // 同期コマンド用
}

//==============================================================================
/**
 * タイミングコマンドを発行する
 * @param   no   タイミング取りたい番号
 * @retval  none
 */
//==============================================================================

void CommTimingSyncStart(u8 no)
{
    OHNO_PRINT("コマンド発行 %d \n",no);
    _pCT->timingSyncMy = no;
    _pCT->timingSend = TRUE;
}

//==============================================================================
/**
 * タイミングコマンドを送信
 * @param   no   タイミング取りたい番号
 * @retval  none
 */
//==============================================================================


#ifdef PM_DEBUG
extern int DebugCommGetNum(int id);
static u8 _keytrg = 0;
#endif

void CommTimingSyncSend(void)
{
    if(_pCT){
        if(_pCT->timingSend){
            if(CommSendFixSizeData(CS_TIMING_SYNC, &_pCT->timingSyncMy)){
                OHNO_PRINT("コマンド送信 %d \n",_pCT->timingSyncMy);
                _pCT->timingSend = FALSE;
            }
        }

#if 0
//#if (defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_tomoya_takahashi) | defined(DEBUG_ONLY_FOR_mituhara))
//#ifdef PM_DEBUG
        {
            if((sys.trg == PAD_BUTTON_B) && (_keytrg==3)){
                _keytrg = 4;
                Snd_SePlay(SEQ_SE_DP_DECIDE);
            }
            else if((sys.trg == PAD_BUTTON_B) && (_keytrg==2)){
                _keytrg = 3;
            }
            else if((sys.trg == PAD_BUTTON_R) && (_keytrg==1)){
                _keytrg = 2;
            }
            else if((sys.trg == PAD_BUTTON_L) && (_keytrg==0)){
                _keytrg = 1;
            }
            else if((sys.trg == PAD_BUTTON_START) && (_keytrg < 4)){
                _keytrg = 0;
            }

            if((sys.trg == PAD_BUTTON_L) && (_keytrg==4)){
                GF_ASSERT_MSG(0, "tim %d %d %d %d %d \n %d %d %d %d %d \n %d %d %d %d %d\n",_pCT->timingSyncMy,
                              _pCT->timingSync[0],_pCT->timingSync[1],
                              _pCT->timingSync[2],_pCT->timingSync[3],
                              DebugCommGetNum(0),DebugCommGetNum(1),DebugCommGetNum(2),
                              DebugCommGetNum(3),DebugCommGetNum(4),DebugCommGetNum(5),
                              DebugCommGetNum(6),DebugCommGetNum(7),
                              DebugCommGetNum(8),DebugCommGetNum(9),DebugCommGetNum(10));
                _keytrg = 0;
            }
        }
#endif
    }

}

//==============================================================================
/**
 * タイミングコマンドが届いたかどうかを確認する
 * @param   no   届く番号
 * @retval  届いていたらTRUE
 */
//==============================================================================

BOOL CommIsTimingSync(u8 no)
{
    if(_pCT==NULL){
        return TRUE;  // 通信してない場合同期しているとみなす
    }
    if(_pCT->timingSyncEnd == no){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * タイミングコマンドが届いたかどうかを確認する
 * @param   no   届く番号
 * @retval  届いていたらTRUE
 */
//==============================================================================

int CommGetTimingSyncNo(int netID)
{
    return _pCT->timingSync[netID];
}

//------------------------------------------------------
/**
 * @brief   選択結果を受信する関数
 * @param   コールバック引数
 * @retval  none
 */
//------------------------------------------------------

void CommRecvListNo(int netID, int size, void* pData, void* pWork)
{
    _ListResult* pRet = pData;

    _pCT->listNo[netID].no = pRet->no;
    _pCT->listNo[netID].listNo = pRet->listNo;
}

//------------------------------------------------------
/**
 * @brief   選択結果を通信するコマンドサイズ
 * @param   no        選択ユニーク番号
 * @param   listNo    選択結果  0-255
 * @retval  none
 */
//------------------------------------------------------

int CommGetListNoSize(void)
{
    return sizeof(_ListResult);
}

//------------------------------------------------------
/**
 * @brief   選択結果を通信する
 * @param   no        選択ユニーク番号
 * @param   listNo    選択結果  0-255
 * @retval  none
 */
//------------------------------------------------------

void CommListSet(u8 no,u8 listNo)
{
    _ListResult ret;

    ret.no = no;
    ret.listNo = listNo;
    CommSendFixSizeData(CS_LIST_NO,&ret);
}

//------------------------------------------------------
/**
 * @brief   選択結果を受け取る
 * @param   recvNetID   どの人のデータを待ち受けるのか
 * @param   pBuff       受信バッファ
 * @retval  選択結果 もしくは -1
 */
//------------------------------------------------------

int CommListGet(int netID, u8 no)
{
    if(!_pCT){
        return INVALID_LIST_NO;
    }
    if(_pCT->listNo[netID].no == no){
        return _pCT->listNo[netID].listNo;
    }
    return INVALID_LIST_NO;
}


//------------------------------------------------------
/**
 * @brief   選択結果を消す
 * @param   none
 * @retval  none
 */
//------------------------------------------------------

void CommListReset(void)
{
    int i;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        MI_CpuFill8(&_pCT->listNo[i], 0, sizeof(_ListResult));
    }
}

//==============================================================================
/**
 * 接続時に相手に送りたいデータを入れる  10byte
 * @param   netID   id   自分の予定のID
 * @param   pData   送りたいデータ
 * @retval  失敗した場合は０
 */
//==============================================================================

void CommToolTempDataReset(void)
{
    int i;
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCT->tempRecv[i] = FALSE;
    }

}

//==============================================================================
/**
 * 接続時に相手に送りたいデータを入れる  10byte
 * @param   netID   id   自分の予定のID
 * @param   pData   送りたいデータ
 * @retval  失敗した場合は０
 */
//==============================================================================

BOOL CommToolSetTempData(int netID,const void* pData)
{
    if(_pCT){
        MI_CpuCopy8(pData, _pCT->tempWork[netID], _TEMPDATA_SIZE);
        CommSendFixSizeData(CS_TOOL_TEMP, _pCT->tempWork[netID]);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 接続時に相手に送ったデータを得る  10byte
 * @param   netID   id   相手の予定のID
 * @retval  失敗した場合は０
 */
//==============================================================================

const void* CommToolGetTempData(int netID)
{
    if(_pCT->tempRecv[netID]){
        return &_pCT->tempWork[netID];
    }
    return NULL;
}

//==============================================================================
/**
 * テンポラリーデータを受信する
 * @param   netID   id   相手の予定のID
 * @retval  失敗した場合は０
 */
//==============================================================================

void CommToolRecvTempData(int netID, int size, void* pData, void* pWork)
{
    _pCT->tempRecv[netID] = TRUE;
    MI_CpuCopy8(pData, _pCT->tempWork[netID], _TEMPDATA_SIZE);
}

//==============================================================================
/**
 * テンポラリーデータサイズを返す
 * @param   netID   id   相手の予定のID
 * @retval  失敗した場合は０
 */
//==============================================================================

int CommToolGetTempDataSize(void)
{
    return _TEMPDATA_SIZE;
}
