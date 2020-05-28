//=============================================================================
/**
 * @file	comm_command.c
 * @brief	データを送るためのコマンドをテーブル化しています
 *          送信したい内容がある場合、ここに追加していくことになります
 *          comm_command.h の enum と同じ並びである必要があります
 * @author	Katsumi Ohno
 * @date    2005.07.26
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/mystatus.h"

//==============================================================================
//  static定義
//==============================================================================
static void _commCommandRecvThrowOut(int netID, int size, void* pData, void* pWork);
static void _commCommandRecvThrowOutReq(int netID, int size, void* pData, void* pWork);
static void _commCommandRecvThrowOutEnd(int netID, int size, void* pData, void* pWork);
static int _getTwo(void);

// field/d_ohno.hにあるデバッグ用
extern void CommDebugRecvHugeData(int netID, int size, void* pData, void* pWork);


//==============================================================================
//	テーブル宣言
//  comm_shar.h の enum と同じならびにしてください
//  CALLBACKを呼ばれたくない場合はNULLを書いてください
//  コマンドのサイズを返す関数を書いてもらえると通信が軽くなります
//  _getZeroはサイズなしを返します。_getVariableは可変データ使用時に使います
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
    {NULL, _getZero, NULL},
    {NULL, _getZero, NULL},
    {CommRecvAutoExit, _getZero, NULL},
    {CommInfoRecvPlayerData, CommInfoGetPlayerDataSize, NULL},
    {CommInfoRecvArrayPlayerData, CommInfoGetPlayerDataSize, NULL},
    {CommInfoRecvEnd, _getZero, NULL},
    {CommRecvNegotiation, CommRecvGetNegotiationSize, NULL},
    {CommRecvNegotiationReturn, CommRecvGetNegotiationSize, NULL},
#ifdef PM_DEBUG
    {CommDebugRecvHugeData, _getVariable, NULL},
    {CommStateRecvDebugStart, _getZero, NULL},
#else
    {NULL, NULL, NULL},
    {NULL, NULL, NULL},
#endif
    {CommRecvDSMPChange, _getOne, NULL},
    {CommRecvDSMPChangeReq, _getOne, NULL},
    {CommRecvDSMPChangeEnd, _getOne, NULL},
    {_commCommandRecvThrowOut, _getZero, NULL},
    {_commCommandRecvThrowOutReq, _getZero, NULL},
    {_commCommandRecvThrowOutEnd, _getZero, NULL},
    {CommRecvTimingSync, _getOne, NULL},
    {CommRecvTimingSyncEnd, _getOne, NULL},
    {CommRecvTimingSyncInfo, _getTwo, NULL},
    {CommRecvListNo, CommGetListNoSize, NULL},
    {CommToolRecvTempData, CommToolGetTempDataSize, NULL},
    {CommRecvExit, _getZero, NULL},
};

typedef struct{
    const CommPacketTbl* pCommPacket;  ///< fieldやbattleのコマンドのテーブル
    int listNum;                       ///< _pCommPacketのlist数
    void* pWork;                       ///< fieldやbattleのメインになるワーク
    u8 bThrowOutReq[COMM_MACHINE_MAX];        ///< コマンドを交換したいフラグ
    u8 bThrowOuted;    ///< コマンド入れ替えが終了したらTRUE
} _COMM_COMMAND_WORK;

static _COMM_COMMAND_WORK* _pCommandWork = NULL;


//--------------------------------------------------------------
/**
 * @brief   コマンドテーブルの初期化
 * @param   pCommPacketLocal 呼び出しモジュール専用のコマンド体系
 * @param   listNum          コマンド数
 * @param   pWork            呼び出しモジュール専用のワークエリア
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandInitialize(const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork)
{
    int i;
    
    if(!_pCommandWork){
        _pCommandWork = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_COMMAND_WORK));
    }
    _pCommandWork->pCommPacket = pCommPacketLocal;
    _pCommandWork->listNum = listNum;
    _pCommandWork->pWork = pWork;


    for(i = 0 ; i < COMM_MACHINE_MAX; i++){
        _pCommandWork->bThrowOutReq[i] = FALSE;
    }
    _pCommandWork->bThrowOuted = FALSE;


}

//--------------------------------------------------------------
/**
 * @brief   コマンドテーブルの終了処理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandFinalize( void )
{
    if(_pCommandWork){
        sys_FreeMemoryEz(_pCommandWork);
        _pCommandWork = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   テーブルに従い 受信コールバックを呼び出します
 * @param   command         受信コマンド
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandCallBack(int netID, int command, int size, void* pData)
{
    PTRCommRecvFunc func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].callbackFunc;
    }
    else{
        GF_ASSERT_RETURN(_pCommandWork,);
        if(command > (_pCommandWork->listNum + CS_COMMAND_MAX)){
#ifdef DEBUG_ONLY_FOR_ohno
            OHNO_PRINT("command %d \n", command);
            GF_ASSERT(0 && "存在しない通信コマンド");
#endif
            CommSetError();
            return;  // 本番ではコマンドなし扱い
        }
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].callbackFunc;
    }
    if(func != NULL){
        if(_pCommandWork){
            func(netID, size, pData, _pCommandWork->pWork);
        }
        else{
            func(netID, size, pData, NULL);
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   定義があったコマンドのサイズを返します
 * @param   command         コマンド
 * @retval  データのサイズ   可変なら COMM_VARIABLE_SIZEを返します
 */
//--------------------------------------------------------------

int CommCommandGetPacketSize(int command)
{
    int size = 0;
    PTRCommRecvSizeFunc func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].getSizeFunc;
    }
    else{
        GF_ASSERT(_pCommandWork);
        if(_pCommandWork==NULL){
            CommSetError();
            return size;  // 本番ではエラー
        }
        if(command > (_pCommandWork->listNum + CS_COMMAND_MAX)){
#ifdef DEBUG_ONLY_FOR_ohno
            GF_ASSERT_MSG(0,"command %d ",command);
#endif
            CommSetError();
            return size;  // 本番ではエラー
        }
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getSizeFunc;
    }
    if(func != NULL){
        size = func();
    }
    return size;
}

//--------------------------------------------------------------
/**
 * @brief   受信バッファを持っているかどうかの検査
 * @param   command         コマンド
 * @retval  持ってるならTRUE
 */
//--------------------------------------------------------------

BOOL CommCommandCreateBuffCheck(int command)
{
    if( command < CS_COMMAND_MAX ){
        return ( _CommPacketTbl[command].getAddrFunc != NULL);
    }
    return (_pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getAddrFunc != NULL);
}

//--------------------------------------------------------------
/**
 * @brief   
 * @param   command         コマンド
 * @retval  持ってるならTRUE
 */
//--------------------------------------------------------------

void* CommCommandCreateBuffStart(int command,int netID, int size)
{
    PTRCommRecvBuffAddr func;

    if( command < CS_COMMAND_MAX ){
        func = _CommPacketTbl[command].getAddrFunc;
        return func(netID, NULL, size);
    }
    else{
        func = _pCommandWork->pCommPacket[command - CS_COMMAND_MAX].getAddrFunc;
        return func(netID, _pCommandWork->pWork, size);
    }
    return NULL;
}


//--------------------------------------------------------------
/**
 * @brief   ３つともサイズを返します
 * @param   command         コマンド
 * @retval  サイズ   可変なら COMM_VARIABLE_SIZE Zeroは０を返す
 */
//--------------------------------------------------------------
int _getVariable(void)
{
    return COMM_VARIABLE_SIZE;
}

int _getZero(void)
{
    return 0;
}

int _getOne(void)
{
    return 1;
}

static int _getTwo(void)
{
    return 2;
}


//--------------------------------------------------------------
/**
 * @brief   コマンドテーブルの廃棄
 * @param   none
 * @retval  受付完了したらTRUE
 */
//--------------------------------------------------------------

BOOL CommCommandThrowOut(void)
{
    GF_ASSERT_RETURN(_pCommandWork, TRUE);

    _pCommandWork->bThrowOuted = FALSE;
    return CommSendFixData(CS_COMMAND_THROWOUT);
}


//==============================================================================
/**
 * コマンド廃棄コールバック
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOut(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
//    OHNO_PRINT("CommRecvDSMPChange 受信\n");
    // 全員に切り替え信号を送る
    _pCommandWork->bThrowOutReq[netID] = TRUE;
    for(i = 0 ; i < COMM_MACHINE_MAX; i++){
        if(!CommIsConnect(i)){
            continue;
        }
        if(!_pCommandWork->bThrowOutReq[i]){
            return;
        }
    }
    CommSendData_ServerSide(CS_COMMAND_THROWOUT_REQ, NULL, 0);
}

//==============================================================================
/**
 * コマンド廃棄実行コールバック
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOutReq(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    _pCommandWork->pCommPacket = NULL;
    _pCommandWork->listNum = 0;
    _pCommandWork->pWork = NULL;
    _pCommandWork->bThrowOuted = TRUE;

    CommSendFixSizeData(CS_COMMAND_THROWOUT_END,pData);
}

//==============================================================================
/**
 * コマンド廃棄完了コールバック
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commCommandRecvThrowOutEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int i;

    if(CommGetCurrentID() != COMM_PARENT_ID){
        return;
    }
    _pCommandWork->bThrowOutReq[netID] = FALSE;
}

//==============================================================================
/**
 * コマンド交換できたかどうかを確認する
 * @param   none
 * @retval  交換完了したらTRUE
 */
//==============================================================================

BOOL CommCommandIsThrowOuted(void)
{
    if(_pCommandWork){
        return _pCommandWork->bThrowOuted;
    }
    return FALSE;
}

