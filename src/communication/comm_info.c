//=============================================================================
/**
 * @file	comm_info.c
 * @brief	通信で得た各カセットの基本情報を蓄えておくクラス
 * @author	Katsumi Ohno
 * @date    2005.08.22
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/gamedata.h"
#include "system/pm_str.h"

#include "communication/comm_info.h"
#include "system/savedata.h"
#include "savedata/randomgroup.h"
#include "savedata/undergrounddata.h"
#include "savedata/wifihistory.h"
#include "wifi/dwc_rapfriend.h"

//==============================================================================
// ワーク
//==============================================================================

enum _info_e {
    _INFO_EMPTY,      // 空
    _INFO_NEW_ENTRY,  // 受信して何も対応していないユーザー
    _INFO_ENTRY,      // 受付完了 メンバーになった
    _INFO_ENTRY_MSGSENDED,      // メッセージも送り終わった状態
    _INFO_MAX
};


// MYSTATUSにない要素を持った構造体
typedef struct{
    u8 myRegulation[COMM_SEND_REGULATION_SIZE]; //
    u8 myStatusBuff[COMM_SEND_MYSTATUS_SIZE];  	// 実際のmystatusの大きさは実行時でないとわからないので上に切ってある
    DWCFriendData friendData;   //通信で渡す用のフレンドコード
    STRCODE groupName[PERSON_NAME_SIZE + EOM_SIZE];     //ランダムグループの MYUSE名
    u8 mac[WM_SIZE_BSSID];  ///mac
    u8 netID;     /// ID
    u8 my_nation;			///<自分の国
    u8 my_area;				///<自分の地域
    u8 myPenalty;
} PlayerInfo;


#define _RESULT_TYPE_WIN  (0)  //自分が勝った
#define _RESULT_TYPE_LOSE  (1) // 負けた
#define _RESULT_TYPE_TRADE  (2) //交換

typedef struct{
    u16 win;
    u16 lose;
    u16 trade;
} PlayerResult;

typedef struct{
    const REGULATION* pReg;
    SAVEDATA* pSaveData;
    PlayerInfo sPlayerData[COMM_MACHINE_MAX];  // 通信用 info
    MYSTATUS* pMyStatus[COMM_MACHINE_MAX];     // myStatus
    PlayerResult sPlayerResult[COMM_MACHINE_MAX];
    u8 info[COMM_MACHINE_MAX];    /// 状態
    u8 _infoEnd;
    u8 bNewInfoData;
    u8 nowNetID;
} _COMM_INFO_WORK;

static _COMM_INFO_WORK* _pCommInfo;

#define _INVALID_POKEID (-1)  /// 無効なポケモンID
#define _ID_STR_LENGTH  (5)  /// IDの桁数＝文字数

//--------------------------------------------------------------
/**
 * @brief   通信情報管理の初期化
 * @param   pWork       内部で使用するワークエリア
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoInitialize(SAVEDATA* pSaveData, const REGULATION* pReg)
{
    int i;
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);

    if(_pCommInfo){
        return;
    }
    _pCommInfo = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_INFO_WORK));
    MI_CpuClear8(_pCommInfo, sizeof(_COMM_INFO_WORK));
    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        _pCommInfo->pMyStatus[i] = (MYSTATUS*)&_pCommInfo->sPlayerData[i].myStatusBuff[0]; //MyStatus_AllocWork(HEAPID_COMMUNICATION);
        CommInfoDeletePlayer( i );
    }
    _pCommInfo->_infoEnd = FALSE;
    _pCommInfo->bNewInfoData = FALSE;
    _pCommInfo->nowNetID = 0;
    _pCommInfo->pSaveData = pSaveData;
    _pCommInfo->pReg = pReg;

    // 自分のMYSTATUSをコピー
    MyStatus_Copy( pMyStatus, _pCommInfo->pMyStatus[0]);
}

//--------------------------------------------------------------
/**
 * @brief   通信情報管理の開放
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoFinalize(void)
{
    int i;

    if(_pCommInfo){
        for(i = 0; i < COMM_MACHINE_MAX ; i++){
            //            sys_FreeMemoryEz(_pCommInfo->pMyStatus[i]);
            _pCommInfo->pMyStatus[i] = NULL;
        }
        if(_pCommInfo){
            sys_FreeMemoryEz(_pCommInfo);
        }
        _pCommInfo = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   初期化がすんでいるかどうかを返す
 * @param   none
 * @retval  初期化完了の場合TRUE
 */
//--------------------------------------------------------------

BOOL CommInfoIsInitialize(void)
{
    return (_pCommInfo != NULL);
}



//--------------------------------------------------------------
/**
 * @brief   自分のID,nameなどを送信します
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------


void CommInfoSendPokeData(void)
{
    u16 netID = CommGetCurrentID();
    MYSTATUS* pMyStatus;
    const STRCODE *pStr;
    RANDOM_GROUP* pRG = SaveData_GetRandomGroup(_pCommInfo->pSaveData);
    WIFI_LIST* pList = SaveData_GetWifiListData(_pCommInfo->pSaveData);
    WIFI_HISTORY* pHistry = SaveData_GetWifiHistory(_pCommInfo->pSaveData);

    pMyStatus = SaveData_GetMyStatus(_pCommInfo->pSaveData);
    MyStatus_Copy( pMyStatus, _pCommInfo->pMyStatus[netID]);
    OS_GetMacAddress(&_pCommInfo->sPlayerData[netID].mac[0]);

    pStr = RandomGroup_GetNamePtr( pRG, RANDOMGROUP_MYUSE, RANDOMGROUP_NAME_GROUP );

    OHNO_PRINT("コピーサイズ  %d \n",sizeof(_pCommInfo->sPlayerData[netID].groupName));
    MI_CpuCopy8(pStr,_pCommInfo->sPlayerData[netID].groupName,
                sizeof(_pCommInfo->sPlayerData[netID].groupName));

    _pCommInfo->sPlayerData[netID].my_nation = WIFIHISTORY_GetMyNation(pHistry);
    _pCommInfo->sPlayerData[netID].my_area = WIFIHISTORY_GetMyArea(pHistry);
    _pCommInfo->sPlayerData[netID].myPenalty = UnderGroundDataIsGoodsSend(_pCommInfo->pSaveData);
    _pCommInfo->sPlayerData[netID].myPenalty = 1 - _pCommInfo->sPlayerData[netID].myPenalty;
    
    DWC_CreateExchangeToken(WifiList_GetMyUserInfo(pList), &_pCommInfo->sPlayerData[netID].friendData);

    MI_CpuClear8(_pCommInfo->sPlayerData[netID].myRegulation, COMM_SEND_REGULATION_SIZE);
    if(_pCommInfo->pReg){
        Regulation_Copy(_pCommInfo->pReg, (REGULATION*)_pCommInfo->sPlayerData[netID].myRegulation);
    }
    CommSendData(CS_COMM_INFO, &_pCommInfo->sPlayerData[netID], sizeof(PlayerInfo));
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤー情報のサイズを返します
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------
int CommInfoGetPlayerDataSize(void)
{
    return sizeof(PlayerInfo);
}

//--------------------------------------------------------------
/**
 * @brief   infoデータがすべてきたことを示すコマンドの受信
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvEnd( int netID, int size, void* pData, void* pWork)
{
    if(_pCommInfo){
        _pCommInfo->_infoEnd = TRUE;
    }
    else{
        OHNO_PRINT("comminfoが初期化されていない\n");
    }
}


//--------------------------------------------------------------
/**
 * @brief   サーバーからみんなの情報が送られてきたかどうか確認
 * @param   none
 * @retval  送られてきたらTRUE
 */
//--------------------------------------------------------------
BOOL CommInfoIsInfoCollected(void)
{
    return _pCommInfo->_infoEnd;
}

//--------------------------------------------------------------
/**
 * @brief   受信コールバックを呼び出します   CS_COMM_INFO_ARRAY
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvArrayPlayerData( int netID, int size, void* pData, void* pWork)
{
    PlayerInfo* pPlayer = (PlayerInfo*)pData;
    if(!_pCommInfo){
        OHNO_PRINT("comminfoが初期化されていない\n");
        return;
    }
    MI_CpuCopy8( pData, &_pCommInfo->sPlayerData[pPlayer->netID], sizeof(PlayerInfo));
    _pCommInfo->nowNetID = pPlayer->netID;

    if(_pCommInfo->info[_pCommInfo->nowNetID] < _INFO_ENTRY){
        OHNO_PRINT("CommInfo 新たなエントリー %d\n", _pCommInfo->nowNetID);
        _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_NEW_ENTRY;  // 新たなエントリー
        if(CommGetCurrentID() == _pCommInfo->nowNetID){  // 自分自身はすでに受付完了状態にする
            _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_ENTRY_MSGSENDED;
        }
    }

}

//--------------------------------------------------------------
/**
 * @brief   受信コールバックを呼び出します CS_COMM_INFO
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvPlayerData( int netID, int size, void* pData, void* pWork)
{
    int i;

    if(!_pCommInfo){
        OHNO_SP_PRINT("comminfoが初期化されていない\n");
        return;
    }
    OHNO_SP_PRINT("CommInfo %d\n", netID);

    MI_CpuCopy8( pData, &_pCommInfo->sPlayerData[netID], sizeof(PlayerInfo));
    CommMPSetBackupMacAddress(&_pCommInfo->sPlayerData[netID].mac[0], netID);

    _pCommInfo->info[netID] = _INFO_NEW_ENTRY;  // 新たなエントリー
    if(CommGetCurrentID() == netID){  // 自分自身はすでに受付完了状態にする
        _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
    }
    else{
        _pCommInfo->bNewInfoData = TRUE;
    }

}

//--------------------------------------------------------------
/**
 * @brief   Myステータスを受信  CS_COMM_MYSTATUS
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

#if 0
void CommInfoRecvMyStatusData( int netID, int size, void* pData, void* pWork)
{
    if(!_pCommInfo){
        OHNO_PRINT("comminfoが初期化されていない\n");
        return;
    }
    OHNO_SP_PRINT("CommInfoServer受信 %d \n",netID);

    OHNO_PRINT("CommInfoServer 新たなエントリー %d\n", netID);
    OHNO_PRINT("CommInfo mystatusGET %d\n", netID);
    MI_CpuCopy8( pData, _pCommInfo->pMyStatus[netID], MyStatus_GetWorkSize());
    _pCommInfo->info[netID] = _INFO_NEW_ENTRY;  // 新たなエントリー
    if(CommGetCurrentID() == netID){  // 自分自身はすでに受付完了状態にする
        _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
    }
    else{
        _pCommInfo->bNewInfoData = TRUE;
    }
}
#endif

//--------------------------------------------------------------
/**
 * @brief   Myステータスを受信  CS_COMM_MYSTATUS_ARRAY
 * @param   netID           ネットワークID
 * @param   size            受信データサイズ
 * @param   pData           受信データ
 * @retval  none
 */
//--------------------------------------------------------------

#if 0
void CommInfoRecvMyStatusArrayData( int netID, int size, void* pData, void* pWork)
{
    if(!_pCommInfo){
        OHNO_PRINT("comminfoが初期化されていない\n");
        return;
    }
    OHNO_SP_PRINT("CommInfoClient受信 %d \n",_pCommInfo->nowNetID);
    OHNO_PRINT("CommInfo mystatusArrayGET %d\n", _pCommInfo->nowNetID);
    MI_CpuCopy8(pData, _pCommInfo->pMyStatus[_pCommInfo->nowNetID],
                MyStatus_GetWorkSize());
#ifdef PM_DEBUG
    {
        const STRCODE* pN = MyStatus_GetMyName(_pCommInfo->pMyStatus[_pCommInfo->nowNetID]);
        OHNO_PRINT("%d %d %d %d\n",pN[0],pN[1],pN[2],pN[3]);
    }
#endif
    if(_pCommInfo->info[_pCommInfo->nowNetID] < _INFO_ENTRY){
        OHNO_PRINT("CommInfo 新たなエントリー %d\n", _pCommInfo->nowNetID);
        _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_NEW_ENTRY;  // 新たなエントリー
        if(CommGetCurrentID() == _pCommInfo->nowNetID){  // 自分自身はすでに受付完了状態にする
            _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_ENTRY_MSGSENDED;
        }
    }

}
#endif

//--------------------------------------------------------------
/**
 * @brief   サーバーから子機に全員のリソースを送信します
 * @param   none
 * @retval  返し終わったタイミングでTRUE
 */
//--------------------------------------------------------------

BOOL CommInfoSendArray_ServerSide(void)
{
    int i;
    if(!_pCommInfo->bNewInfoData){
        return FALSE;
    }

    if(!CommIsSendCommand_ServerSize(CS_COMM_INFO_END)){
        OHNO_PRINT("comminfoarray-------子機に送信\n");
        for(i=0;i<COMM_MACHINE_MAX;i++){
            if(_pCommInfo->info[i] != _INFO_EMPTY){
                OHNO_PRINT("%d を送信\n", i);
                _pCommInfo->sPlayerData[i].netID = i;
                MI_CpuCopy8(_pCommInfo->pMyStatus[i], _pCommInfo->sPlayerData[i].myStatusBuff,MyStatus_GetWorkSize());
                CommSetSendQueue_ServerSide(CS_COMM_INFO_ARRAY,
                                            &_pCommInfo->sPlayerData[i],
                                            sizeof(PlayerInfo));
                //                CommSetSendQueue_ServerSide(CS_COMM_MYSTATUS_ARRAY,
                //                                          _pCommInfo->pMyStatus[i],
                //                                        MyStatus_GetWorkSize());
            }
        }
        // INFOデータを全て送り終わった事を送信 このIDのリクエストで終わった
        CommSetSendQueue_ServerSide(CS_COMM_INFO_END, NULL,0);
        _pCommInfo->bNewInfoData = FALSE;
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   新しいinfoデータが来たかどうか
 * @param   none
 * @retval  新しいinfoデータが来た場合TRUE
 */
//--------------------------------------------------------------

BOOL CommInfoIsNewInfoData(void)
{
    return _pCommInfo->bNewInfoData;
}

//--------------------------------------------------------------
/**
 * @brief   ワークにある名前を得ます
 * @param   index       人物のindex番号
 * @param   name        人物の名前を入れるバッファのポインタ
 * @retval  名前があったらTRUE
 */
//--------------------------------------------------------------

BOOL CommInfoGetName(int index,u16* name)
{
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ワークにある人物のIDを文字列で得ます
 * @param   index       人物のindex番号
 * @param   idStr       人物のIDを入れるバッファのポインタ
 * @retval  IDがあったらTRUE
 */
//--------------------------------------------------------------

BOOL CommInfoGetIDString(int netID, u16* idStr)
{
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   情報を消す
 * @param   netID           ネットワークID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoDeletePlayer(int netID)
{
    //    _pCommInfo->sPlayerData[netID].pokeNickName[0] = 0;
    //    _pCommInfo->sPlayerData[netID].pokeID = _INVALID_POKEID;
    MyStatus_Init(_pCommInfo->pMyStatus[ netID ]);
    _pCommInfo->info[ netID ] = _INFO_EMPTY;

}

//--------------------------------------------------------------
/**
 * @brief   新しい名前が入ったかどうか調べる
 * @param   netID           ネットワークID
 * @retval  新しい名前の場合TRUEを返す
 */
//--------------------------------------------------------------

BOOL CommInfoIsBattleNewName(int netID)
{
    return (_pCommInfo->info[netID] == _INFO_NEW_ENTRY);
}

//--------------------------------------------------------------
/**
 * @brief   新しい名前が入ったかどうか調べる
 * @param   netID           ネットワークID
 * @retval  新しい名前の場合TRUEを返す
 */
//--------------------------------------------------------------

BOOL CommInfoIsNewName(int netID)
{
    return (_pCommInfo->info[netID] == _INFO_ENTRY) || (_pCommInfo->info[netID] == _INFO_NEW_ENTRY);
}

//--------------------------------------------------------------
/**
 * @brief   遊ぶ仲間として認証する
 * @param   netID           ネットワークID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoSetEntry(int netID)
{
    _pCommInfo->info[netID] = _INFO_ENTRY;
}

//--------------------------------------------------------------
/**
 * @brief   受け取ったというメッセージ表示が終わったことを格納する
 * @param   netID           ネットワークID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoSetMessageEnd(int netID)
{
    _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
}


//--------------------------------------------------------------
/**
 * @brief   新しい名前が入ったかどうか調べる
 * @param   netID           ネットワークID
 * @retval  新しい名前の場合0以上を返す
 */
//--------------------------------------------------------------

int CommInfoGetNewNameID(void)
{
    int i;

    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        if(_pCommInfo->info[i] == _INFO_NEW_ENTRY){
            return i;
        }
    }
    return INVALID_NETID;
}

//--------------------------------------------------------------
/**
 * @brief   正式エントリーした人数を帰す
 * @param   none
 * @retval  num
 */
//--------------------------------------------------------------

int CommInfoGetEntryNum(void)
{
    int i;
    int j = 0;

    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        switch(_pCommInfo->info[i]){
          case _INFO_ENTRY:
          case _INFO_ENTRY_MSGSENDED:
            j++;
            break;
        }
    }
    return j;
}

//--------------------------------------------------------------
/**
 * @brief   接続に応じてデータを消す
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoFunc(void)
{
    int i;

    if(_pCommInfo){
        if(CommGetConnectNum()==0){
            return;
        }
        for(i = 0; i < COMM_MACHINE_MAX ; i++){
            if( !CommIsConnect(i) && !( (i == COMM_PARENT_ID) && CommGetAloneMode())  ){
                if(_pCommInfo->info[i] != _INFO_EMPTY){
                    CommInfoDeletePlayer(i);
                }
            }
        }
    }
}


//==============================================================================
/**
 *  MyStatusを返す
 * @param   netID   id
 * @retval  MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommInfoGetMyStatus(int netID)
{
    if(!_pCommInfo){
        return NULL;
    }
    switch(_pCommInfo->info[netID]){
      case _INFO_NEW_ENTRY:
      case _INFO_ENTRY:
      case _INFO_ENTRY_MSGSENDED:
        return _pCommInfo->pMyStatus[netID];
    }
    return NULL;
}

//==============================================================================
/**
 * REGULATIONを返す
 * @param   netID   id
 * @retval  REGULATION*
 */
//==============================================================================

const REGULATION* CommInfoGetRegulation(int netID)
{
    if(!_pCommInfo){
        return NULL;
    }
    switch(_pCommInfo->info[netID]){
      case _INFO_NEW_ENTRY:
      case _INFO_ENTRY:
      case _INFO_ENTRY_MSGSENDED:
        return (const REGULATION*)_pCommInfo->sPlayerData[netID].myRegulation;
    }
    return NULL;
}

//==============================================================================
/**
 *  DWCFriendDataを返す
 * @param   netID   id
 * @retval  DWCFriendData*
 */
//==============================================================================

DWCFriendData* CommInfoGetDWCFriendCode(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return &_pCommInfo->sPlayerData[netID].friendData;   //通信で渡す用のフレンドコード
    }
    return NULL;
}

//==============================================================================
/**
 *  GroupNameを返す
 * @param   netID   id
 * @retval  STRCODE*
 */
//==============================================================================

STRCODE* CommInfoGetGroupName(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].groupName;
    }
    return NULL;
}

//==============================================================================
/**
 * myNationを返す
 * @param   netID   id
 * @retval  失敗した場合は０
 */
//==============================================================================

int CommInfoGetMyNation(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].my_nation;
    }
    return 0;
}

//==============================================================================
/**
 * myAreaを返す
 * @param   netID   id
 * @retval  失敗した場合は０
 */
//==============================================================================

int CommInfoGetMyArea(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].my_area;
    }
    return 0;
}

//==============================================================================
/**
 * myPenaltyを返す
 * @param   netID   id
 * @retval  失敗した場合は０
 */
//==============================================================================

int CommInfoGetMyPenalty(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].myPenalty;
    }
    return 0;
}




//==============================================================================
/**
 * 接続している人のレギュレーションが同じかどうか検査する
 * @param   void
 * @retval  失敗した場合は０
 */
//==============================================================================

BOOL CommInfoRegulationCheck(void)
{
    int i,j;

    for(i = 0; i < COMM_MACHINE_MAX-1 ; i++){
        if( CommIsConnect(i) && (_pCommInfo->info[i] != _INFO_EMPTY)){
            if( CommIsConnect(i+1) && (_pCommInfo->info[i+1] != _INFO_EMPTY)){
                DEBUG_DUMP(_pCommInfo->sPlayerData[i].myRegulation, COMM_SEND_REGULATION_SIZE,"");
                DEBUG_DUMP(_pCommInfo->sPlayerData[i+1].myRegulation, COMM_SEND_REGULATION_SIZE,"");
                for(j = 0;j < COMM_SEND_REGULATION_SIZE ; j++){
                    if(_pCommInfo->sPlayerData[i].myRegulation[j] != _pCommInfo->sPlayerData[i+1].myRegulation[j]){
                        return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
}

//==============================================================================
/**
 * 勝ち負け交換の記録をつける
 * @param   type カウント種類
 * @param   num  回数
 * @retval  none
 */
//==============================================================================

static void _commInfoSetResult(int type,int num)
{
    int i;
    int myStandBit,targetBit;

    if(_pCommInfo==NULL){
        return;
    }
    if(type != _RESULT_TYPE_TRADE){
        myStandBit = CommGetStandNo(CommGetCurrentID()) & 0x1;  // 自分の立場
    }

    
    for(i = 0; i < CommGetConnectNum(); i++){
        if( CommIsConnect(i) && (_pCommInfo->info[i] != _INFO_EMPTY)){
            if(type == _RESULT_TYPE_WIN){
                targetBit = CommGetStandNo(i) & 0x1;
                if(myStandBit != targetBit){
                    _pCommInfo->sPlayerResult[i].win += num;
                    OHNO_PRINT("かった %d %d %d\n",i,type,num);
                }
            }
            else if(type == _RESULT_TYPE_LOSE){
                targetBit = CommGetStandNo(i) & 0x1;
                if(myStandBit != targetBit){
                    _pCommInfo->sPlayerResult[i].lose += num;
                    OHNO_PRINT("まけた %d %d %d\n",i,type,num);
                }
            }
            else{
                _pCommInfo->sPlayerResult[i].trade += num;
            }
        }
    }
}

//------------------------------------------------------------------
/**
 * $brief   勝ち負けや交換回数を登録する
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

void CommInfoWriteResult(SAVEDATA* pSaveData)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(pSaveData);
    int i,ret,pos;

    for(i = 0; i < CommGetConnectNum(); i++){
        DWCFriendData* pFriend = CommInfoGetDWCFriendCode(i);
        if(pFriend == NULL){
            continue;
        }
        ret = dwc_checkfriendByToken(pSaveData, pFriend, &pos);
        switch(ret){
          case DWCFRIEND_INLIST:// … すでに、同じデータがリスト上にある。この場合は何もする必要なし。
          case DWCFRIEND_OVERWRITE:// … すでに、同じデータがリスト上にあるが、上書きすることが望ましい場合。
            GF_ASSERT(pos >= 0);

            OHNO_PRINT("勝ち負け記録  %d %d  %d %d %d \n",i,pos,
                       _pCommInfo->sPlayerResult[i].win,
                       _pCommInfo->sPlayerResult[i].lose,
                       _pCommInfo->sPlayerResult[i].trade);
            WifiList_SetResult(pList, pos,
                               _pCommInfo->sPlayerResult[i].win,
                               _pCommInfo->sPlayerResult[i].lose,
                               _pCommInfo->sPlayerResult[i].trade);
            break;
        }
    }
    // けします
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCommInfo->sPlayerResult[i].win = 0;
        _pCommInfo->sPlayerResult[i].lose = 0;
        _pCommInfo->sPlayerResult[i].trade = 0;
    }

}

//------------------------------------------------------------------
/**
 * $brief   勝ち負けの登録
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

void CommInfoSetBattleResult(SAVEDATA* pSaveData, int bWin )
{
    if(bWin==1){
        _commInfoSetResult(_RESULT_TYPE_WIN, 1);
    }
    else if(bWin == -1){
        _commInfoSetResult(_RESULT_TYPE_LOSE, 1);
    }
    CommInfoWriteResult(pSaveData);
}

void CommInfoSetTradeResult(SAVEDATA* pSaveData, int num)
{
    _commInfoSetResult(_RESULT_TYPE_TRADE, num);
    CommInfoWriteResult(pSaveData);
}

