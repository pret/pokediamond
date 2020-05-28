//=============================================================================
/**
 * @file	ug_dig_stone.c
 * @brief	玉を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.10.26
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"

#include "../fieldsys.h"
#include "communication/communication.h"
#include "../comm_field_state.h"
#include "ug_manager.h"

#include "../worldmap.h"
#include "../fieldobj.h"
#include "../fld_bmp.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/window.h"
#include "system/wordset.h"
#include "msgdata/msg_underworld.h"

#include "system/snd_tool.h"
#include "field/eventflag.h"
#include "../sysflag.h"

#include "../d_ohno.h"  // デバッグ用



//==============================================================================
// 定義
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ

#define _RESULT_CMD_SIZE (2) // データ送受信の結果を返す時のデータバイト数
#define _TOUCH_OBJ_MAX (3)  //Touchした時に表示する罠の限界数
#define _STONE_NUM_SINGLE_MAX (UG_STONE_PLACE_NUM_MAX)   // 一人分の石
#define _STONE_NUM_MAX (_STONE_NUM_SINGLE_MAX)      // 石 100

#define _INTERVAL_STONE_DISP (20)

// ありえないID
#define _INVALID_ID  (0xff)

enum _result_e {
    _RESULT_NONE,
    _RESULT_OK,
    _RESULT_NG
};

//==============================================================================
//	型宣言
//==============================================================================

typedef struct{
    u16 xpos;   // 石の位置
    u16 zpos;
    u8 carat;   // 大きさ=カラット 1-99
    u8 addCarat;   // 成長=カラット 1-99
    u8 type;     // 種類
//    u8 order;   // 埋めた順番  (たくさん埋めると古いものが消えていってしまう為)
} _Stone;

typedef struct{
    _Stone stone;
    u8 netID;
    u8 result;
} _StoneResult;


typedef struct{
    u8 pcRadarIndex;  //パソコンレーダー受信用
    u16 pcRadarTimer;  //パソコンレーダー表示用
} _EVENT_PCRADAR_WORK;

typedef struct{
    _Stone myStone[_STONE_NUM_SINGLE_MAX];    // 埋めている自分の石（セーブ可能）
    _Stone* pStoneTbl[_STONE_NUM_SINGLE_MAX]; // 検索用テーブル
    u8 recvCounter[COMM_MACHINE_MAX];
    u8 recvCounterBackup[COMM_MACHINE_MAX];
    TCB_PTR pPcRadar;
    _EVENT_PCRADAR_WORK* pPcRadarWork;
    FIELDSYS_WORK* pFSys;
    u8 logMsgGetStone[COMM_MACHINE_MAX];
    int intervalTimer;
    u8 sendNum;
    u8 result;
    u8 bStopDisp;
} CommDigWork;

// シングルトン
static CommDigWork* _pCommWork = NULL;

//==============================================================================
//	static宣言
//==============================================================================

static _Stone* _getOldOrderData(_Stone* pStoneTbl);
static Grid* _getStoneTblPos(Grid* pGrid, int index);
static void _delStone(_Stone* pStone);
static void _resetOrderNo(_Stone* pStoneTbl);
static void _myStoneDel(_Stone* pStone);
static void _myStoneAdd(_Stone* pStone);
static void _insertStoneTbl(_Stone* pStone);

//--------------------------------------------------------------
/**
 * @brief   メッセージを自動表示した場合の終了時コールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static void _msgEndCallBack(int num)
{
    CommPlayerHoldEnd();
}

//==============================================================================
/**
 * 石名つきメッセージの表示
 * @param   type   石タイプ
 * @param   message   GMMメッセージID
 * @retval  none
 */
//==============================================================================

static void _digAddCaratMessage(int num)
{
    if(num > 0){
        CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 0, num);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_75, TRUE, _msgEndCallBack);
    }
    else{
        _msgEndCallBack(num);
    }
}

//==============================================================================
/**
 * 石掘り管理の初期化
 * @param   pWork   作業メモリー
 * @retval  none
 */
//==============================================================================

void CommDigStoneInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i;
    UNDERGROUNDDATA* pUGData;

    if(_pCommWork){
        return;
    }
    _pCommWork = pWork;
    MI_CpuFill8(_pCommWork, 0, sizeof(CommDigWork));
    _pCommWork->pFSys = pFSys;
    pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pFSys));

    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        _pCommWork->myStone[i].type = UnderGroundGetStoneGroundItemType(pUGData,i);
        _pCommWork->myStone[i].xpos = UnderGroundGetStoneGroundItemX(pUGData,i);
        _pCommWork->myStone[i].zpos = UnderGroundGetStoneGroundItemZ(pUGData,i);
        _pCommWork->myStone[i].carat = UnderGroundGetStoneGroundItemCaratOrg(pUGData,i);
     //   _pCommWork->myStone[i].order = UnderGroundGetStoneGroundItemOrder(pUGData,i);
        _pCommWork->myStone[i].addCarat = UnderGroundGetStoneGroundItemCaratMul(pUGData,i);
        if(_pCommWork->myStone[i].type != STONE_TYPE_NONE){
            _insertStoneTbl(&_pCommWork->myStone[i]);
        }
    }
}


//==============================================================================
/**
 * 自分の石をバックアップする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _myStoneBackup(void)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommWork->pFSys));
    int i;
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        UnderGroundAddStoneGroundItem( pUGData, _pCommWork->myStone[i].type,i,
                                      _pCommWork->myStone[i].xpos,
                                      _pCommWork->myStone[i].zpos,
                                    // _pCommWork->myStone[i].order,
                                      _pCommWork->myStone[i].carat,
                                       _pCommWork->myStone[i].addCarat
                                       );
    }
}

//==============================================================================
/**
 * 石掘りのワークサイズを得る
 * @param   none
 * @retval  サイズ
 */
//==============================================================================

int CommDigStoneManagerGetWorkSize(void)
{
    return sizeof(CommDigWork);
}

//==============================================================================
/**
 * 石掘りのリセット
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneManagerReset(void)
{
    _pCommWork->bStopDisp = TRUE;
}

//==============================================================================
/**
 * 石掘りの復帰処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneManagerReboot(void)
{
    _pCommWork->bStopDisp = FALSE;
}

//==============================================================================
/**
 * 石掘りの終了
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneFinalize(void)
{
    if(_pCommWork){
        sys_FreeMemoryEz(_pCommWork);
        _pCommWork = NULL;
    }
}

//==============================================================================
/**
 * 石掘りの毎フレーム処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneStep(void)
{
    if(_pCommWork->bStopDisp)
        return;
    
    _pCommWork->intervalTimer++;
    if(_pCommWork->intervalTimer >= (_STONE_NUM_MAX * _INTERVAL_STONE_DISP)){
        _pCommWork->intervalTimer = 0;
    }
    if((_pCommWork->intervalTimer % _INTERVAL_STONE_DISP) == 10){
        int stoneID = _pCommWork->intervalTimer / _INTERVAL_STONE_DISP;
        int x = UgStoneGetMyStoneX(stoneID);
        int z = UgStoneGetMyStoneZ(stoneID);
        if((x != 0) && (z != 0)){
            FE_FldOBJGFlashSet(_pCommWork->pFSys, x, z);
        }
    }
}



//==============================================================================
/**
 * テーブル上にある石の位置を返す
 * @param   pGrid  返す位置
 * @param   index  検索するindex
 * @retval  noneサイズ
 */
//==============================================================================

static Grid* _getStoneTblPos(Grid* pGrid, int index)
{
    if(_pCommWork->pStoneTbl[index]==NULL){
        return NULL;
    }
    pGrid->xpos = _pCommWork->pStoneTbl[index]->xpos;
    pGrid->zpos = _pCommWork->pStoneTbl[index]->zpos;
    return pGrid;
}

//==============================================================================
/**
 * テーブルに石を挿入する
 * @param   pGrid  返す位置
 * @param   index  検索するindex
 * @retval  noneサイズ
 */
//==============================================================================

static void _insertStoneTbl(_Stone* pStone)
{
    int ins,i;
    Grid grid;

    grid.xpos = pStone->xpos;
    grid.zpos = pStone->zpos;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    ins = CommUnderSearchItemTbl(&grid);

    OHNO_PRINT("テーブルに入れる %d\n",ins);
    GF_ASSERT_RETURN(ins < (_STONE_NUM_MAX),);

    for(i = (_STONE_NUM_MAX - 1); i > ins  ; i--){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i - 1 ];
    }
    
/*    memmove(&_pCommWork->pStoneTbl[ins+1],
            &_pCommWork->pStoneTbl[ins],
            (_STONE_NUM_MAX - ins - 1)*sizeof(u32));*/
    _pCommWork->pStoneTbl[ins] = pStone;

}

//==============================================================================
/**
 * 検索テーブルつくりなおし
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static void _delStoneTbl(_Stone* pStone)
{
    int match = -1;
    Grid grid;
    int i;

    MI_CpuClear8(_pCommWork->pStoneTbl,sizeof(u32)*_STONE_NUM_MAX);

    for(i = 0; i < _STONE_NUM_MAX; i++){
        if(_pCommWork->myStone[i].type != STONE_TYPE_NONE){
            _insertStoneTbl(&_pCommWork->myStone[i]); //再構築
        }
    }
    
#if 0
    for(i = 0; i < _STONE_NUM_MAX; i++){
        OHNO_PRINT("石テーブル %d %d %d\n",i, _pCommWork->pStoneTbl[ i ]->xpos,_pCommWork->pStoneTbl[ i ]->zpos);
        if(_pCommWork->pStoneTbl[ i ] == pStone){
            match = i;
            break;
        }
    }
    GF_ASSERT_RETURN(match != -1,);
    for(i = match; i < (_STONE_NUM_MAX-1); i++){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i+1 ];
    }
    _pCommWork->pStoneTbl[_STONE_NUM_MAX-1] = NULL;
#endif
    
#if 0
    
    
    grid.xpos = pStone->xpos;
    grid.zpos = pStone->zpos;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    match = CommUnderMatchItemTbl(&grid);
    OHNO_PRINT("テーブルから消去 %d\n",match);
    

    GF_ASSERT_RETURN(match != -1,);

    for(i = match; i < (_STONE_NUM_MAX-1); i++){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i+1 ];
    }

//    memmove(&_pCommWork->pStoneTbl[match],
//            &_pCommWork->pStoneTbl[match+1],
//            (_STONE_NUM_MAX - match - 1)*sizeof(u32));
    _pCommWork->pStoneTbl[_STONE_NUM_MAX-1] = NULL;
#endif
}

//==============================================================================
/**
 * あいてる石バッファを返す
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static _Stone* _getFreeStone( _Stone* pStoneTbl )
{
    int i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(pStoneTbl->type == STONE_TYPE_NONE){
            return pStoneTbl;
        }
        pStoneTbl++;
    }
    return NULL;
}

//==============================================================================
/**
 * あいてる石のindexを返す
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static int _getFreeStoneIndex( _Stone* pStoneTbl )
{
    int i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(pStoneTbl->type == STONE_TYPE_NONE){
            return i;
        }
        pStoneTbl++;
    }
    return 0;
}



//==============================================================================
/**
 * 石の消去
 * @param   TrapInfo* pTrap 罠
 * @retval  none
 */
//==============================================================================
#if 0
static void _delStone(_Stone* pStone)
{
    u32 baseAddr = (u32)&_pCommWork->myStone[0];
    u32 nowStone = (u32)pStone;
    u32 stoneNo = (nowStone-baseAddr)/sizeof(_Stone);
    u32 id = stoneNo;
    
    pStone->type = STONE_TYPE_NONE;
    pStone->order = 0;
    _delStoneTbl(pStone);
}
#endif
//--------------------------------------------------------------
/**
 * 最初に生成した石を得る
 * @param    netID  機器番号
 * @retval   生成番号
 */
//--------------------------------------------------------------
static _Stone* _getOldOrderData(_Stone* pStoneTbl)
{
    return pStoneTbl;
}

//==============================================================================
/**
 *  石があったかどうかを返す
 * @param   調べたい座標のX座標
   @param   調べたい座標のZ座標
 * @retval  引っかかった罠
 */
//==============================================================================

static _Stone* _checkStone(int x, int z)
{
    Grid grid;
    int ret;

    grid.xpos = x;
    grid.zpos = z;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    ret = CommUnderMatchItemTbl(&grid);

    if(-1 == ret){
        return NULL;
    }
    return _pCommWork->pStoneTbl[ret];
}

//==============================================================================
/**
 *  石を拾ったことを拾ったクライアントに表示 CF_DIG_STONE_PICKUP
 * @param   netID    送信してきたID
 * @param   x,y      位置情報
 * @retval  発見した場合TRUE 
 */
//==============================================================================

void CommDigStoneRecvPickUp(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int id = CommGetCurrentID();
    int x,z,ca;
    _Stone* pStone;

    if(pBuff[0] == id){
        x = CommPlayerGetPosXDirAdd(id);
        z = CommPlayerGetPosZDirAdd(id);
        pStone = _checkStone(x, z);
        if(pStone){       // 石を拾う
            CommPlayerHold();
            if(CommUnderBagAddStone(pStone->type, pStone->carat + pStone->addCarat)){  // ボールをバッグに追加
                _pCommWork->logMsgGetStone[id] = pStone->type;
                Snd_SePlay(UG_SE_FIND);
                ca = UG_STONE_CARAT_MAX;
                if(pStone->carat+ pStone->addCarat < UG_STONE_CARAT_MAX){
                    ca = pStone->carat+ pStone->addCarat;
                }
                CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 1, ca);
                CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, pStone->type);
                ca = pStone->addCarat;
                if((ca + pStone->carat) > UG_STONE_CARAT_MAX){
                    ca = UG_STONE_CARAT_MAX - pStone->carat;
                }
                CommMsgTalkWindowStartSendNum(CommUnderGetMsgUnderWorld(),
                                              msg_underworld_69, TRUE, _digAddCaratMessage, ca);
                CommMsgTalkWindowMeWait(CommUnderGetMsgUnderWorld());  //MEの終了待ちON
                _myStoneDel(pStone);  // 古いのを消す
                _myStoneBackup();
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                       msg_underworld_83, TRUE, _msgEndCallBack);
            }
        }
    }
}

//==============================================================================
/**
 * 自分に近います座標を教えてくれる
 * @param   none
 * @retval  none
 */
//==============================================================================

void NearHexInitialize(NearHexWork* pWork, int maxDist)
{
    pWork->maxDist = maxDist;
    pWork->iterater = 0;
}

//==============================================================================
/**
 * 自分に近います座標を教えてくれる
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL NearHexGetHex(NearHexWork* pWork, NearHex* pHex)
{
    int i, ite, x, y;

    ite = pWork->iterater;

    for(i = 0 ; i <= pWork->maxDist; i++){
        if((ite - (i*4)) > 0){
            ite = ite - (i*4);
        }
        else{
            if(ite!=0){
                ite--;
            }
            if(ite < (i*2)){
                y = i - ite;
            }
            else{
                y = ite - i*3;
            }
            if(ite < (i)){
                x = ite;
            }
            else if(ite < (i*3)){
                x = i*3 - (ite + i);
            }
            else{
                x = -i + (ite - i*3);
            }
            pHex->xpos = x;
            pHex->zpos = y;
//            OHNO_PRINT("%d x=%d y=%d\n",pWork->iterater,x,y);
            pWork->iterater++;
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 *  玉を埋める
 * @param   type      タマ
 * @param   carat     カラット
 * @retval  メッセージがある場合TRUE
 */
//==============================================================================

void CommDigStoneAddStone( int type, int carat ,int x,int z)
{
    _Stone stone;
    _Stone* pStone;
    BOOL bDig = FALSE;
    
    stone.xpos = x;   // 石の位置
    stone.zpos = z;
    stone.carat = carat;   // 大きさ=カラット 1-99
    stone.type = type;     // 種類
    stone.addCarat = 0;

    if(UgSecretBaseIsSecretBasePlace(x,z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_84, FALSE, NULL);
        return;
    }
    if(CommPlayerNPCHitCheck(x, z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_55, FALSE, NULL);
        return;
    }    
    if(GetHitAttr(_pCommWork->pFSys,x,z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_60, FALSE, NULL);
        return;
    }
    pStone = _checkStone(x, z);
    if(pStone){  // 先約がいた
        if(pStone->type == stone.type){ // 同じ石の場合
            if(pStone->carat > carat){
                pStone->carat = pStone->carat + (carat / 5) + 1;
            }
            else{
                pStone->carat = carat + (pStone->carat / 5) + 1;
            }
            if(pStone->carat > UG_STONE_CARAT_MAX){
                pStone->carat = UG_STONE_CARAT_MAX;
            }
            bDig = TRUE;
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_59, FALSE, NULL);
        }
    }
    else{
        _myStoneAdd(&stone);
        bDig = TRUE;
    }
    if(bDig){
        CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 0, type);
        CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 1, carat);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_58, FALSE, NULL);
        CommUnderBagDeleteStone(type);
        Snd_SePlay(UG_SE_BURY);  // 埋めた
        //Snd_SePlay(UG_SE_SMOKE);
        SysFlag_UgTamaSet(SaveData_GetEventWork(_pCommWork->pFSys->savedata));
        FE_FldOBJGFlashSet(_pCommWork->pFSys, x, z);
    }
}

//==============================================================================
/**
 * 自分の石を消す
 * @param   pStone    石データ
 * @retval  none
 */
//==============================================================================

static void _myStoneDel(_Stone* pStone)
{
    _Stone* pFreeStone;
    int index = -1,i;

    
    for(i = 0; i< _STONE_NUM_SINGLE_MAX; i++){
        pFreeStone = &_pCommWork->myStone[i];
        if(pStone == pFreeStone){
            index = i;
            break;
        }
    }
    GF_ASSERT_RETURN(index != -1,);

    for( ; i < (_STONE_NUM_SINGLE_MAX-1); i++){
        MI_CpuCopy8(&_pCommWork->myStone[i+1],&_pCommWork->myStone[i],sizeof(_Stone));
    }
    _pCommWork->myStone[_STONE_NUM_SINGLE_MAX-1].type = STONE_TYPE_NONE;

    _delStoneTbl(pStone);

}

//==============================================================================
/**
 * 自分の石を追加する
 * @param   pStone
 * @retval  none
 */
//==============================================================================

static void _myStoneAdd(_Stone* pStone)
{
    _Stone* pFreeStone = _getFreeStone(_pCommWork->myStone);
    int index;

    if(pFreeStone==NULL){
        pFreeStone = _getOldOrderData(_pCommWork->myStone);
        _myStoneDel(pFreeStone);  // 古いのを消す
        pFreeStone = _getFreeStone(_pCommWork->myStone);
        GF_ASSERT_RETURN(pFreeStone,);
    }
//    index = _getFreeStoneIndex(_pCommWork->myStone);
    MI_CpuCopy8( pStone, pFreeStone, sizeof(_Stone));
    _insertStoneTbl(pFreeStone);
    _myStoneBackup();
}

//==============================================================================
/**
 *  タマかどうかを返す
 * @param   message   メッセージ
 * @retval  メッセージがある場合TRUE
 */
//==============================================================================
BOOL CommDigIsStone(int type)
{
    if((type != STONE_TYPE_NONE) && (type < DIG_PARTS_TREASURE_MIN)){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 *  石があったかどうかを返す
 * @param   調べたい座標のX座標
   @param   調べたい座標のZ座標
 * @retval  あったかどうか
 */
//==============================================================================

BOOL UgStoneCheck(int x, int z)
{
    if(_checkStone(x,z)){
        return TRUE;
    }
    return FALSE;
}



//--------------------------------------------------------------
/**
 * 石の位置X座標を得る
 * @param    index
 * @retval   X座標
 */
//--------------------------------------------------------------

int UgStoneGetMyStoneX(int index)
{
    if(_pCommWork  &&
       (_pCommWork->myStone[index].type != STONE_TYPE_NONE) ){
        return _pCommWork->myStone[index].xpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * 石の位置Z座標を得る
 * @param    index
 * @retval   Z座標
 */
//--------------------------------------------------------------

int UgStoneGetMyStoneZ(int index)
{
    if(_pCommWork  &&
       (_pCommWork->myStone[index].type != STONE_TYPE_NONE) ){
        return _pCommWork->myStone[index].zpos;
    }
    return 0;
}

//==============================================================================
/**
 * 石logメッセージを返す
 * @param   message   メッセージ
 * @retval  メッセージがある場合TRUE
 */
//==============================================================================

BOOL UgDigStoneGetActionMessage(STRBUF* pStrBuf)
{
    int i;
    WORDSET* pWordSetMain=NULL;  //ワードセット構造体
    STRBUF* tmp_buf1=NULL;
    BOOL bRet = FALSE;

    if(!_pCommWork){
        return bRet;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCommWork->logMsgGetStone[i] != STONE_TYPE_NONE){
            pWordSetMain = WORDSET_Create(HEAPID_FIELD);
            tmp_buf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
            WORDSET_RegisterUGItemName(pWordSetMain, 2, _pCommWork->logMsgGetStone[i]);
            MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), UGBallGet, tmp_buf1 );
            WORDSET_ExpandStr( pWordSetMain, pStrBuf, tmp_buf1 );
            _pCommWork->logMsgGetStone[i] = STONE_TYPE_NONE;
            bRet = TRUE;
            break;
        }
    }
    if(tmp_buf1)
        STRBUF_Delete( tmp_buf1 );
    if(pWordSetMain)
        WORDSET_Delete(pWordSetMain);
    return bRet;
}

//==============================================================================
/**
 * 石一個の近くに化石一個を埋める
 * @param   乱数ポインタ
 * @retval  うめたかず
 */
//==============================================================================

int UgDigStoneSetOneFossil(MATHRandContext16* pRand)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommWork->pFSys));
    int x,z,i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(STONE_TYPE_NONE != UnderGroundGetStoneGroundItemType(pUGData,i)){
            x = UnderGroundGetStoneGroundItemX(pUGData,i);
            z = UnderGroundGetStoneGroundItemZ(pUGData,i);
            UgFossilOneSetup(x,z, pRand);
        }
    }
    return i;
}

//--------------------------------------------------------------
/**
 * パソコンレーダークライアントタスク
 * @param    tcb   tcb
 * @param    work   _EVENT_PCRADAR_WORK
 * @retval   none
 */
//--------------------------------------------------------------

static void _GMEVENT_PcRadar(TCB_PTR tcb, void *work)
{
    _EVENT_PCRADAR_WORK* pWork = work;

    pWork->pcRadarTimer++;
    if(_STONE_NUM_SINGLE_MAX < pWork->pcRadarTimer){
        Snd_SePlay(UG_SE_RADAR_ECHO);
        pWork->pcRadarTimer = 0;
    }
}


//--------------------------------------------------------------
/**
 * パソコンレーダースタート
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgStonePcRadarStart(void)
{
    _EVENT_PCRADAR_WORK* mdw;
    GF_ASSERT_RETURN(!_pCommWork->pPcRadarWork,);  // 二重起動禁止
    GF_ASSERT_RETURN(!_pCommWork->pPcRadar,);

    mdw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EVENT_PCRADAR_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_PCRADAR_WORK));
    mdw->pcRadarTimer = _STONE_NUM_SINGLE_MAX;
    _pCommWork->pPcRadarWork = mdw;
    _pCommWork->pPcRadar = TCB_Add(_GMEVENT_PcRadar , mdw,TCB_PRIORITY_NORMAL);
}

//--------------------------------------------------------------
/**
 * パソコンレーダーエンド
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgStonePcRadarEnd(void)
{
    if(_pCommWork->pPcRadar){
        TCB_Delete(_pCommWork->pPcRadar);
        sys_FreeMemoryEz(_pCommWork->pPcRadarWork);
        _pCommWork->pPcRadar = NULL;
        _pCommWork->pPcRadarWork = NULL;
    }
}

#define _DTIME  (2)  // レーダーをゆっくり見せる為の間隔

//--------------------------------------------------------------
/**
 * 自分の石の位置X座標を得る
 * @param    index
 * @retval   X座標
 */
//--------------------------------------------------------------

int UgStoneGetRadarStoneX(int index)
{
    if(_pCommWork && _pCommWork->pPcRadarWork){
        int a = _pCommWork->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_STONE_NUM_SINGLE_MAX);
        return UgStoneGetMyStoneX(a);
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * 自分の石のTRAPの位置Z座標を得る
 * @param    index
 * @retval   Z座標
 */
//--------------------------------------------------------------

int UgStoneGetRadarStoneZ(int index)
{
    if(_pCommWork && _pCommWork->pPcRadarWork){
        int a = _pCommWork->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_STONE_NUM_SINGLE_MAX);
        return UgStoneGetMyStoneZ(a);
    }
    return 0;
}



#ifdef PM_DEBUG

void Debug_UgDigStoneAdd( int type, int carat ,int x,int z)
{
    _Stone stone;
    stone.xpos = x;   // 石の位置
    stone.zpos = z;
    stone.carat = carat;   // 大きさ=カラット 1-99
    stone.type = type;     // 種類
    stone.addCarat = 0;

    _myStoneAdd(&stone);
}

#endif
