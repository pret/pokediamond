//=============================================================================
/**
 * @file	ug_secretbase.c
 * @brief	地下の秘密基地情報を管理するクラス
            自分の秘密基地と
            サーバー用全員の秘密基地
            自分の秘密基地
            16+1=17こ
 * @author	Katsumi Ohno
 * @date    2005.10.03
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"

#include "communication/communication.h"
#include "../fieldsys.h"

#include "../field_event.h"
#include "../fld_bmp.h"
#include "system/bmp_menu.h"
#include "../ev_mapchange.h"
#include "../mapdefine.h"
#include "../comm_field_state.h"
#include "../map3d_object.h"
#include "../../fielddata/build_model/build_model_id.h"

#include "ug_manager.h"
#include "system/pm_str.h"
#include "system/gamedata.h"
#include "system/wordset.h"
#include "../field_effect.h"
#include "msgdata/msg_underworld.h"
#include "msgdata/msg_uwflag.h"
#include "system/fontproc.h"
#include "gflib/bg_system.h"
#include "system/window.h"
#include "ug_snd_def.h"
#include "system/wipe.h"
#include "system/brightness.h"

#include "field/goods_data.h"
#include "savedata/undergrounddata.h"
#include "system/arc_util.h"
#include "field/eventflag.h"
#include "../sysflag.h"
#include "../../fielddata/base_goods/goods_id_def.h"
#include "ug_trap.naix"

#include "../../communication/wh.h"


//==============================================================================
// 定義
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ
#define _SECRETBASE_NUM_MAX (17)  ///< 秘密基地バッファの最大
#define _SECRETBASE_MY_ID (16)  ///< 自分の秘密基地のデータが入っているID
#define _SECRETBASE_SPLIT_NUM (4)  ///< 送信をしやすくするための分割数

#define _SECRETBASE_ATTR_MAX (32)

#define _SECLET_INNER_BASE_X  (15)
#define _SECLET_INNER_BASE_Z  (24)
#define _SECLET_INNER_BASE_Z_PLUS (32)

#define _INVALID_BASE (0xff)
#define _PLAYER_INVALID_GRID  (0xfff)   // 座標は１２BIT送信を行うため変な数字になっている


#define _MOVE_TICKETS  (1)  //秘密基地データ移動開始
#define _ERROR_TICKETS (2)  //秘密基地受信中にエラー
#define _NONE_TICKETS (0)   // 何も無い
#define _DISCONECT_TICKETS (4) // 秘密基地移動中にエラー
#define _TRANS_TICKETS  (5)  //子機移動開始
#define _RETURN_TICKETS  (6) // 帰りの切符

typedef enum {
    _SB_INCOMPLETION,  // 未完成
    _SB_COMPLETION, // 完成

} SecretBaseState;

#define _GOODS_NUM_MAX  (15)   // 置けるグッズの数   パソコン別

#define DEBUG_BLACT_NEW_HOOK //ビルボード仕様変更による修正箇所

#define _M3DO_NONE (0xff)

//==============================================================================
//	型宣言
//==============================================================================

#define _SECLET_BASE_DATA_SIZE  (148)

// 秘密基地構造体データ
typedef struct{
    u8 netID;
    u8 moveID;       //移動する人
    u8 secretBaseDataBuff[_SECLET_BASE_DATA_SIZE];
} SecretBaseInfo;


typedef struct{
    u16 xpos;    // ドアの位置
    u16 zpos;
    u8 dir;  // どっち向きに入り口があるのか
} _Pos;

typedef struct{
    u16 xpos;    // ドアの位置
    u16 zpos;
    u8 netID;    // 誰が移動するか
    u8 dir;  // どっち向きに入り口があるのか
    u8 bRemove;
} _SendPos;


// 秘密基地全体
typedef struct{
    FIELDSYS_WORK* pFSys;
    TCB_PTR pDoorTCB;
    SecretBaseInfo secretBaseData[_SECRETBASE_NUM_MAX];  // 秘密基地構造体
    SecretBaseInfo* pNowMoveingBase;
    u32 aAttr[_SECRETBASE_NUM_MAX][32];  // 秘密基地あたりデータ３２ｘ３２
    _Pos secretHeaderData[COMM_MACHINE_MAX]; // ドアを表示するためのデータ
    _Pos secretHDataServer[COMM_MACHINE_MAX]; // ドアを表示するためのデータサーバ用
    u8 moveTickets;
    u8 doorAct[ _SECRETBASE_NUM_MAX ];
    u16 doorActX[ _SECRETBASE_NUM_MAX ];
    u16 doorActZ[ _SECRETBASE_NUM_MAX ];
    u8 doorActDir[ _SECRETBASE_NUM_MAX ];
    u8 flagGetLog[COMM_MACHINE_MAX]; // LOG
    u8 flagConqureLog[COMM_MACHINE_MAX];
    u8 flagReverseLog[COMM_MACHINE_MAX];
    u8 travelBase[COMM_MACHINE_MAX]; // 入っている秘密基地 CLIENTデータ
    u8 travelingBase[COMM_MACHINE_MAX]; //いこうとしている秘密基地
    u8 travelingBaseSend[COMM_MACHINE_MAX]; //送信している秘密基地
    u8 travelingBaseMessage[COMM_MACHINE_MAX]; //いこうとしている秘密基地
    u8 bGoodsTrap[COMM_MACHINE_MAX]; //
    u8 sendBuff[COMM_MACHINE_MAX*4];    // 移動位置を送る為のバッファ

    u16 resquePosSX[COMM_MACHINE_MAX];  // 入る時に出る時の位置を記憶
    u16 resquePosSZ[COMM_MACHINE_MAX];
    u16 resqueSDir[COMM_MACHINE_MAX];
    u16 resquePosX;  // 入る時に出る時の位置を記憶
    u16 resquePosZ;
    u8 resqueDir;
    u8 sbNum;       // 親機から受け取った秘密基地の数
    u8 bChildRecv;    // 子機のデータを受信したらTRUE
    u8 bPosRecv;    // 子機の位置を受信したらTRUE
    u8 bHalt;      // サービス停止中の場合TRUE
    u8 bDoorON;
    u8 bClientBaseIn;  // クライアント側、
} CommSecretBaseWork;


typedef struct {
    FIELDSYS_WORK* pFSys;
    BMPMENU_WORK*  pYesNoWork;
    TCB_PTR pTCB;
    int seq;
    int subseq;
    int next_zone_id;
    int next_door_id;
    int next_x;
    int next_z;
    int nextDir;
   // int index;
    u8 connectNum;
    u8 timer;
    u8 brightness;
    u8 netID;
    u8 moveID;
    u8 bRemove;
    u8 bMessage;
} EVENT_UGCHG_WORK;


typedef struct{
    FIELDSYS_WORK* pFSys;
    TCB_PTR pTCB;
    BMPMENU_WORK*  pYesNoWork;
    int seq;
   // int index;
    u8 netID;
    u8 timer;
    u8 bBaseDoor;
} _EVENT_DRILL_WORK;


// シングルトン
static CommSecretBaseWork* _pCommSecretBaseWork = NULL;

//==============================================================================
// static宣言
//==============================================================================

static void _makeAttr(SECRETBASEDATA* pSecret, u32* attr);
static void _sendSecretBasePosition(void);
static void _doorPictFinalize(void);
static void _doorPictAdd(int x, int z, int dir, int index);
static void _jumpMapForUG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID,BOOL bRemove);
static void _returnUGMapEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID);
static void _enterSecretBaseEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID);
static BOOL _enterSecretBaseStart(int secretBaseNo, int playerID);
static void _returnUnderGroundStart(int secretBaseNo, int playerID, BOOL bRemove);
static void _createSecretBase(void);
static void _disconnectEVENT(TCB_PTR tcb, void *work);
static void _doorPictDelete(int netID);
static void _taskDoor(TCB_PTR tcb , void* work);
static void _connectDisable(void);
static void _connectEnable(void);

static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };

static const BMPWIN_DAT _connectBmpDat = {
    GF_BGL_FRAME3_M, (FLD_YESNO_WIN_PX-9), FLD_YESNO_WIN_PY,
    (FLD_YESNO_WIN_SX+9), FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, (FLD_YESNO_WIN_CGX-((FLD_YESNO_WIN_SX+13)*2))
    };


// IDによる部屋のBLOCK位置  最後がOFFLINE
static u8 _blockToRoomX[]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,0};
static u8 _blockToRoomZ[]={0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0};


#define _DRILL_START_CHECK  (0)
#define _DRILL_START_REFORM  (1)
#define _DRILL_START_NEW  (2)
#define _DRILL_START_RENEW  (3)

#define _RESQUE_POSX (72)
#define _RESQUE_POSZ (437)


//==============================================================================
// 関数
//==============================================================================

static int _getSecretIndex(int x,int z)
{
    int i;
    int bx = x / _SECRETBASE_ATTR_MAX;
    int bz = z / _SECRETBASE_ATTR_MAX;

    for(i = 0;i < _SECRETBASE_NUM_MAX;i++){
        if((bx == _blockToRoomX[i]) && (bz == _blockToRoomZ[i])){
            return i;
        }
    }
    return _SECRETBASE_MY_ID;  // オフライン自分の部屋
}

//==============================================================================
/**
 * 秘密基地出口の座標を求める
 * @param   netID
 * @retval  none
 */
//==============================================================================

static BOOL _checkSecretBaseOutPos(int x,int z)
{
    const _Pos base = {_SECLET_INNER_BASE_X, _SECLET_INNER_BASE_Z, DIR_UP};
    const int plus = _SECLET_INNER_BASE_Z_PLUS;
    int id;
    int i;

    for(i = 0; i< COMM_MACHINE_MAX;i++){
        if(x == (base.xpos + i * plus + plus) && 
           (z == base.zpos)){
            return TRUE;
        }
    }
    return FALSE;
}


//==============================================================================
/**
 * 秘密基地出口の座標を求める
 * @param   netID
 * @retval  none
 */
//==============================================================================

static void _getSecretBaseOutPos_local(int netID, _Pos* pPos)
{
    const _Pos base = {_SECLET_INNER_BASE_X, _SECLET_INNER_BASE_Z, DIR_UP};
    const int plus = _SECLET_INNER_BASE_Z_PLUS;
    int id;

    if(CommMPIsConnectStalth()){   // 通信切断状態の場合
        pPos->xpos = base.xpos;
        pPos->zpos = base.zpos;
        return;
    }
    id = netID;
    if(netID == _SECRETBASE_MY_ID){
        id = 0;
    }
//    pPos->xpos = base.xpos + (id % 8) * plus + plus;
//    pPos->zpos = base.zpos + (id / 8) * plus;
    pPos->xpos = base.xpos + id * plus + plus;
    pPos->zpos = base.zpos;
}

static void _getSecretBaseOutPos(int netID, _Pos* pPos)
{
    int id = netID;

    if(CommGetAloneMode()){
        id = _SECRETBASE_MY_ID;
    }
    _getSecretBaseOutPos_local(id, pPos);
}

//==============================================================================
/**
 * 秘密基地情報初期化
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;


    if(_pCommSecretBaseWork){  // 今のところ何度も初期化されるので
        return;
    }

    OHNO_PRINT("_SECLET_BASE_DATA_SIZE 大きさ表示 %d\n",SecretBaseData_GetWorkSize());
    GF_ASSERT(_SECLET_BASE_DATA_SIZE == SecretBaseData_GetWorkSize());

    _pCommSecretBaseWork = (CommSecretBaseWork*)pWork;
    MI_CpuFill8(pWork, 0, sizeof(CommSecretBaseWork));
    _pCommSecretBaseWork->pFSys = pFSys;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCommSecretBaseWork->secretHeaderData[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[i].zpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].zpos = _PLAYER_INVALID_GRID;
        
        _pCommSecretBaseWork->travelingBase[i] = _INVALID_BASE;
        _pCommSecretBaseWork->travelingBaseSend[i]  = _INVALID_BASE;
        _pCommSecretBaseWork->travelBase[i] = _INVALID_BASE;
        // メッセージ表示
        _pCommSecretBaseWork->travelingBaseMessage[i] = _INVALID_BASE;
        _pCommSecretBaseWork->flagGetLog[i] = INVALID_NETID;
        _pCommSecretBaseWork->flagConqureLog[i] = INVALID_NETID;
        _pCommSecretBaseWork->flagReverseLog[i] = INVALID_NETID;

        _pCommSecretBaseWork->resquePosSX[i] = _RESQUE_POSX;
        _pCommSecretBaseWork->resquePosSZ[i] = _RESQUE_POSZ;
        _pCommSecretBaseWork->resqueSDir[i] = DIR_DOWN;
    }

    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        pBase = &_pCommSecretBaseWork->secretBaseData[i];
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_Init(pSecret);
        _pCommSecretBaseWork->doorAct[i] = _M3DO_NONE;
        _pCommSecretBaseWork->doorActDir[i] = DIR_NOT;
    }
    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );

    UgSecretBaseMakeMyAttr(pFSys);

    _pCommSecretBaseWork->resquePosX = _RESQUE_POSX;
    _pCommSecretBaseWork->resquePosZ = _RESQUE_POSZ;
    _pCommSecretBaseWork->resqueDir = DIR_DOWN;

    _pCommSecretBaseWork->pDoorTCB = TCB_Add(_taskDoor, NULL, TCB_PRIORITY_NORMAL);
    
    
    HWSetDisconnectCallBack(UgSecretBaseResetPlayer);
    
}

//==============================================================================
/**
 * セーブデータから自分のあたりデータを作る
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

void UgSecretBaseMakeMyAttr(FIELDSYS_WORK* pFSys)
{
    SECRETBASEDATA* pSecret;
    SB_RECORD_DATA* pRecord;

    pSecret = SaveData_GetSecretBaseData(GameSystem_GetSaveData(pFSys));
    pRecord = SecretBaseGetSecretBaseRecord(pSecret);
    SecretBaseRecordSetPoint(pRecord,
                             RECORD_Score_Get(SaveData_GetRecord(pFSys->savedata)));

    MI_CpuCopy8(pSecret,_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[_SECRETBASE_MY_ID]);
    MI_CpuCopy8(pSecret,_pCommSecretBaseWork->secretBaseData[COMM_PARENT_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[COMM_PARENT_ID]);
}

//==============================================================================
/**
 * あたりデータをぬく
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================
static void _attrBitOff(int xinit, int zinit,const u8* pBuff, u32* attr)
{
    int x,z;

    for(z = 0;z < 3; z++){
        if((zinit+z) < 32){
            for(x = 0;x < 3; x++){
                if(pBuff[z*3 + x]){
                    if((xinit+x) < 32){
                        attr[z+zinit] &= ~(0x1 << (xinit+x));
                    }
                }
            }
        }
    }
}


//==============================================================================
/**
 * あたりデータを作成する
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

static void _makeAttr(SECRETBASEDATA* pSecret, u32* attr)
{
    int i,x,z;
    const u8* pBuff;
    u8 pcBuff[]={1,1,0,0,0,0,0,0,0};
    u8 blockBuff[]={1,1,0,1,1,0,0,0,0};


    MI_CpuFill8(attr, 0xff,  _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        if(i == 0){
            pBuff = pcBuff;
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            pBuff = blockBuff;
        }
        _attrBitOff(x, z, pBuff, attr);
    }
#if 0
    for(i = 0; i < _SECRETBASE_ATTR_MAX; i++){
        OHNO_PRINT("ATTR>> %x \n",attr[i]);
    }
#endif
}

//==============================================================================
/**
 * 一時的に画面を消去する際に呼ぶリセット関数
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReset(void)
{
    _doorPictFinalize();
    if(_pCommSecretBaseWork->pDoorTCB){
        TCB_Delete(_pCommSecretBaseWork->pDoorTCB);
        _pCommSecretBaseWork->pDoorTCB=NULL;
    }
    _pCommSecretBaseWork->bHalt = TRUE;
}

//==============================================================================
/**
 * 画面を復帰する際に呼ぶ関数
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReboot(void)
{
    int i;

    _pCommSecretBaseWork->bHalt = FALSE;

    if(_pCommSecretBaseWork->bClientBaseIn == FALSE){
        OHNO_PRINT("秘密基地出る際に表示\n");
        for(i = 0;i < COMM_MACHINE_MAX;i++){
            _doorPictDelete( i );
        }
        for(i = 0; i < COMM_MACHINE_MAX;i++){
            _Pos* pHead = &_pCommSecretBaseWork->secretHeaderData[i];
            if((_PLAYER_INVALID_GRID != pHead->xpos) && (_PLAYER_INVALID_GRID != pHead->zpos)){
                _doorPictAdd(pHead->xpos, pHead->zpos, pHead->dir, i);
            }
        }
    }
    if(_pCommSecretBaseWork->pDoorTCB==NULL){
        _pCommSecretBaseWork->pDoorTCB = TCB_Add(_taskDoor, NULL, TCB_PRIORITY_NORMAL);
    }

}

//==============================================================================
/**
 * 秘密基地情報処理終了
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoFinalize(void)
{

    HWSetDisconnectCallBack(NULL);


    if(_pCommSecretBaseWork->pDoorTCB){
        TCB_Delete(_pCommSecretBaseWork->pDoorTCB);
        _pCommSecretBaseWork->pDoorTCB=NULL;
    }
    _doorPictFinalize();
    if(_pCommSecretBaseWork){
        sys_FreeMemoryEz(_pCommSecretBaseWork);
    }
    _pCommSecretBaseWork = NULL;
}

//==============================================================================
/**
 * 秘密基地情報処理再度初期化
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReInit(void)
{
    int i;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_SetMakeDown(pSecret);
        _pCommSecretBaseWork->secretHeaderData[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[i].zpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].zpos = _PLAYER_INVALID_GRID;
        // 穴を消す
//        OHNO_PRINT("穴を消す  \n");
    }
    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );
    UgSecretBaseMakeMyAttr(_pCommSecretBaseWork->pFSys);
}





void CommSecretBaseInfoParentDel(void)
{
    int i;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;

    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        pBase = &_pCommSecretBaseWork->secretBaseData[i];
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_Init(pSecret);
    }
    UgSecretBaseMakeMyAttr(_pCommSecretBaseWork->pFSys);
}


//==============================================================================
/**
 * ワーク全体のサイズを返す
 * @param   none
 * @retval  空いているCommSecretBaseWorkのポインタ
 */
//==============================================================================

int CommSecretBaseInfoGetWorkSize(void)
{
    return sizeof(CommSecretBaseWork);
}

//==============================================================================
/**
 * 通信で抜けていった人の削除を行う
 * @param   netID
 * @retval  none
 */
//==============================================================================
/*
void UgSecretBaseDestroyPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // 入っている秘密基地 CLIENTデータ
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //いこうとしている秘密基地
        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
        if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
            M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID], _pCommSecretBaseWork->pFSys->Map3DObjExp);
            _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        }
    }
}
*/
//==============================================================================
/**
 * 自分がこの秘密基地にいない場合、通信で抜けていった人の秘密基地削除を行う
 * @param   netID
 * @retval  none
 */
//==============================================================================
/*
void UgSecretBaseDestroyPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        OHNO_PRINT("自分は%d - %d基地\n",CommGetCurrentID(),_pCommSecretBaseWork->travelBase[CommGetCurrentID()]);
        if(_pCommSecretBaseWork->travelBase[CommGetCurrentID()] == netID){
            _Pos* pHead = &_pCommSecretBaseWork->secretHeaderData[netID];
            _pCommSecretBaseWork->resquePosX = pHead->xpos;
            _pCommSecretBaseWork->resquePosZ = pHead->zpos;
            _pCommSecretBaseWork->resqueDir = pHead->dir;
        }
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // 入っている秘密基地 CLIENTデータ
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //いこうとしている秘密基地
        _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
        if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
            M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID], _pCommSecretBaseWork->pFSys->Map3DObjExp);
            _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        }
    }
}
*/
//==============================================================================
/**
 * 切断した子機の移動情報は消す
 * @param   netID
 * @retval  none
 */
//==============================================================================

void UgSecretBaseResetPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // 入っている秘密基地 CLIENTデータ
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //いこうとしている秘密基地
        _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
        _pCommSecretBaseWork->secretHDataServer[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[netID].zpos = _PLAYER_INVALID_GRID;
    }
}

//==============================================================================
/**
 * 秘密基地の削除（クライアント側情報も一緒に消す）を行う
 * @param   netID
 * @retval  none
 */
//==============================================================================

void UgSecretBaseDestroyDoor(int netID)
{
    if(_pCommSecretBaseWork){
        _doorPictDelete(netID);
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
//        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
    }
}

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
 * 秘密基地の入り口がある場合持ち主を返す
 * @param   none
 * @retval  あったらIDを返す 無かったらINVALID_NETID
 */
//==============================================================================

static int _getSecretBaseEnter(int x, int z)
{
    int i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[i];
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        if(!SecretBaseIsSecretBaseMake(pSecret)){
            continue;
        }
        if(!CommPlayerIsActive(i)){
            continue;
        }
        if((x == SecretBaseGetSecretBasePositionX(pSecret)) &&
           (z == SecretBaseGetSecretBasePositionZ(pSecret)) ){   // 位置ヒット
            return i;
        }
    }
    return INVALID_NETID;
}

//==============================================================================
/**
 * @brief   通路<>秘密基地の移動イベント開始 CF_SECRETBASE_EVENT_START
 * @param   コールバック引数
 * @retval  none
 */
//==============================================================================

typedef struct{
    u16 x;
    u16 z;
    u8 netID;   // 移動する人
    u8 baseID;  // 移動する場所のID
    u8 dir;
    u8 bEnterBase;
} _JumpEventPacket;


void UgSecretBaseRecvJumpEvent(int netID, int size, void* pData, void* pWork)
{
    _JumpEventPacket* pJump = pData;

    if(pJump->netID != CommGetCurrentID()){
        return;
    }
    if(_pCommSecretBaseWork->bHalt){
        return;
    }
    
    if(pJump->bEnterBase){
        _enterSecretBaseEvent(_pCommSecretBaseWork->pFSys,
                              pJump->x, pJump->z, DIR_UP,
                              pJump->netID, pJump->baseID);
    }
    else{
        _returnUGMapEvent(_pCommSecretBaseWork->pFSys,
                          pJump->x, pJump->z, pJump->dir,
                          pJump->netID, pJump->baseID);
    }
}

//==============================================================================
/**
 * @brief   通路 > 秘密基地の移動に失敗した場合
 * @param   none
 * @retval  パケットサイズ
 */
//==============================================================================

void UgSecretBaseRecvMoveFailed(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(CommGetCurrentID() == pBuff[0]){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_88, TRUE, _msgEndCallBack);
    }
}

//==============================================================================
/**
 * @brief   通路<>秘密基地の移動イベント開始のパケットサイズ
 * @param   none
 * @retval  パケットサイズ
 */
//==============================================================================

int UgSecretBaseRecvJumpEventSize(void)
{
    return sizeof(_JumpEventPacket);
}

//==============================================================================
/**
 * @brief   通路<>秘密基地の移動イベントの結果を返す CF_SECRETBASE_EVENT_RES
 * @param   コールバック引数
 * @retval  none
 */
//==============================================================================

typedef struct {
    u8 baseNo;
    u8 bResult;
    u8 bBaseIn;
} _UgJumpEventResult;

void UgSecretBaseRecvJumpEventRes(int netID, int size, void* pData, void* pWork)
{
    _UgJumpEventResult* pRes = pData;
    u8 id = netID;

    if(CommGetCurrentID()!=COMM_PARENT_ID){
        GF_ASSERT(0);
        return;
    }
    
    if(pRes->bResult){
        if(pRes->bBaseIn){
            // 通路>基地
            if(!_enterSecretBaseStart(pRes->baseNo, netID)){
                _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;  // 秘密基地移動取り消し
                CommSendFixSizeData_ServerSide(CF_SECRETBASE_MOVE_FAILED,&id);
            }
        }
        else{  // 基地>通路
            _returnUnderGroundStart(pRes->baseNo, netID, FALSE);
        }
    }
    else{
        // クライアント側からのキャンセル
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;  // 秘密基地移動取り消し
        OHNO_PRINT("キャンせる受信\n");
    }
}

//==============================================================================
/**
 * @brief   通路<>秘密基地の移動イベントの結果を返す為のコマンドのサイズ
 * @param   none
 * @retval  サイズ
 */
//==============================================================================

int UgSecretBaseRecvJumpEventResSize(void)
{
    return sizeof(_UgJumpEventResult);
}

//==============================================================================
/**
 * 通路から秘密基地に入る実行関数
 * @param   secretBaseNo   秘密基地番号
 * @param   playerID       プレーヤー
 * @retval  動く場合TRUE
 */
//==============================================================================

static BOOL _enterSecretBaseStart(int secretBaseNo, int playerID)
{
    _Pos outDoorPos;
    int i;

    SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    if(!SecretBaseIsSecretBaseMake(pSecret)){  // できていない秘密基地への移動は破棄
        return FALSE;
    }

    if(CommIsSendCommand_ServerSize(CF_SECRETBASE_DATA_SERVER)){  // 自分が一個でも送ろうとしている場合破棄
        return FALSE;
    }
    

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(CommIsConnect(i)){
            if(_pCommSecretBaseWork->travelingBaseSend[i] == secretBaseNo){ // すでに同じ基地へ移動中
                OHNO_PRINT("基地移動失敗 %d \n", playerID,secretBaseNo);
                return FALSE;
            }
        }
    }
    _getSecretBaseOutPos(secretBaseNo, &outDoorPos);

    // 秘密基地を相手に送信
    pBase->moveID = playerID;
    CommSecretBaseInfoParentSendStart(secretBaseNo); // iの秘密基地を子機に送信
    _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // jさんがiの秘密基地に行こうとしている
    _pCommSecretBaseWork->travelingBaseSend[playerID]  = secretBaseNo;

    CommPlayerBaseTeleportServer(playerID, outDoorPos.xpos, outDoorPos.zpos, DIR_UP);
    OHNO_PRINT("%dが%dの秘密基地へ移動開始 %d %d\n", playerID, secretBaseNo,
               CommPlayerGetPosSX(playerID),CommPlayerGetPosSZ(playerID) );
    return TRUE;
}

//==============================================================================
/**
 * 秘密基地から通路に戻る実行関数
 * @param   secretBaseNo   秘密基地番号
 * @param   playerID       プレーヤー
 * @retval  動く場合TRUE
 */
//==============================================================================

static void _returnUnderGroundStart(int secretBaseNo, int playerID, BOOL bRemove)
{
    _SendPos sendPos;
    _Pos outDoorPos;
    int x,z,dir;
    SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    _getSecretBaseOutPos_local(secretBaseNo, &outDoorPos);
    _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // jさんがiの秘密基地からでようとしている
//    x = SecretBaseGetSecretBasePositionX(pSecret);
//    z = SecretBaseGetSecretBasePositionZ(pSecret);
//    dir = SecretBaseGetSecretBasePositionDir(pSecret);

    if(CommGetAloneMode()){
        x = _pCommSecretBaseWork->resquePosX;
        z = _pCommSecretBaseWork->resquePosZ;
        dir = _pCommSecretBaseWork->resqueDir;
    }
    else{
        x = _pCommSecretBaseWork->resquePosSX[playerID];
        z = _pCommSecretBaseWork->resquePosSZ[playerID];
        dir = _pCommSecretBaseWork->resqueSDir[playerID];
    }
//    x = _pCommSecretBaseWork->resquePosX;
//    z = _pCommSecretBaseWork->resquePosZ;
//    dir = _pCommSecretBaseWork->resqueDir;
    
    CommPlayerBaseTeleportServer(playerID, x, z, dir);
//    GF_ASSERT((x != 0) && (z != 0));
    OHNO_PRINT("%d が 秘密基地 からもどる %d %d %d\n", playerID, x, z , dir);
    x += FieldOBJ_DirAddValueGX( dir);
    z += FieldOBJ_DirAddValueGZ( dir);
    sendPos.xpos = x;
    sendPos.zpos = z;
    sendPos.netID = playerID;
    sendPos.dir = dir;
    sendPos.bRemove = bRemove;
    CommSendFixSizeData_ServerSide(CF_SECRETBASE_RETJUMP,&sendPos);
    CommPlayerSetMoveControl_Server(playerID, FALSE);
}

//==============================================================================
/**
 * 秘密基地フレーム処理  位置を確認して移動
 * @param   playerID   プレーヤー
 * @retval  動く場合TRUE
 */
//==============================================================================

BOOL CommSecretBaseSingleStepFunc(int playerID, int moveX, int moveZ)
{
    int secretBaseNo;
    _SendPos sendPos;
    _Pos outDoorPos;
    _JumpEventPacket jp;
    int x,z;

    if(!_pCommSecretBaseWork){
        return FALSE;
    }
    if((playerID != COMM_PARENT_ID) && !CommIsConnect(playerID) ){
        return FALSE;
    }
    if(CommPlayerIsTrapBind(playerID)){
        return FALSE;
    }
    if(_pCommSecretBaseWork->travelingBase[playerID] != _INVALID_BASE){ // すでに移動中
        return TRUE;
    }
    secretBaseNo = _getSecretBaseEnter(moveX, moveZ);
    if(secretBaseNo != INVALID_NETID){
		OHNO_PRINT("--移動 %d %d\n",playerID,secretBaseNo);
        _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // jさんがiの秘密基地へgo-
        jp.bEnterBase = TRUE;
        jp.x = moveX;
        jp.z = moveZ;
        jp.dir = DIR_UP;
        jp.netID = playerID;
        jp.baseID = secretBaseNo;
        CommSendFixSizeData_ServerSide(CF_SECRETBASE_EVENT_START,&jp);
        CommPlayerSetMoveControl_Server(playerID,FALSE);
        //        _enterSecretBaseEvent(_pCommSecretBaseWork->pFSys,
        //                              moveX, moveZ, DIR_UP, playerID);
        return TRUE;
    }
    for(secretBaseNo = 0; secretBaseNo <= COMM_MACHINE_MAX; secretBaseNo++){
        SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[secretBaseNo].secretBaseDataBuff;
        if(!SecretBaseIsSecretBaseMake(pSecret)){
            continue;
        }
        _getSecretBaseOutPos_local(secretBaseNo, &outDoorPos);
        if((moveX == outDoorPos.xpos) && (moveZ == outDoorPos.zpos) ){   // 位置ヒット
            _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // jさんがiの秘密基地からでようとしている
            jp.bEnterBase = FALSE;
            jp.x = moveX;
            jp.z = moveZ;
            jp.dir = DIR_UP;
            jp.netID = playerID;
            jp.baseID = secretBaseNo;
            CommSendFixSizeData_ServerSide(CF_SECRETBASE_EVENT_START,&jp);
            CommPlayerSetMoveControl_Server(playerID,FALSE);
            //            _returnUGMapEvent(_pCommSecretBaseWork->pFSys,
            //                              pBase->xpos, pBase->zpos, pBase->dir, playerID);
            return TRUE;
        }
    }
    if(_checkSecretBaseOutPos(moveX,moveZ)){  // 秘密基地はないが戻す場合
        sendPos.xpos = _pCommSecretBaseWork->resquePosSX[playerID];
        sendPos.zpos = _pCommSecretBaseWork->resquePosSZ[playerID];
        sendPos.netID = playerID;
        sendPos.dir = _pCommSecretBaseWork->resqueSDir[playerID];
        sendPos.bRemove = FALSE;
        _pCommSecretBaseWork->travelingBase[playerID] = COMM_PARENT_ID;  // 強制脱出
        CommPlayerBaseTeleportServer(playerID, sendPos.xpos, sendPos.zpos, sendPos.dir);
        CommSendFixSizeData_ServerSide(CF_SECRETBASE_RETJUMP,&sendPos);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * 秘密基地から炭鉱に戻る際のイベントを終了
 * @param   event イベントコントローラ
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEventForceDel(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }
    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
}


//==============================================================================
/**
 * 炭鉱から秘密基地へ行くのイベントを終了
 * @param   event イベントコントローラ
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEventForceDelEnterBaseCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    _UgJumpEventResult ugJump;

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }

    ugJump.bResult = FALSE;
    ugJump.baseNo = mcw->moveID;
    ugJump.bBaseIn = FALSE;
    CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);

    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
    _connectEnable();

}

//==============================================================================
/**
 * 秘密基地から炭鉱に戻る際のイベント
 * @param   event イベントコントローラ
 * @retval  none
 */
//==============================================================================

typedef enum {
    _RETURN_START,
    _ONLINE_MSGWAIT,
    _ONLINE_YESNO_WAIT,
    _OFFLINE_MSGWAIT,
    _OFFLINE_YESNO_WAIT,
    _CONNECT_CHKMSG,
    _CONNECT_YESNO_WAIT,
    _RETURN_UG,
} ReturnMapCheck_e;


static void GMEVENT_ReturnMapCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    FIELDSYS_WORK * fsys = mcw->pFSys;
    LOCATION_WORK locationWork;
    int x=0,z=0,msgNo,ret, bClose = FALSE;
    _UgJumpEventResult ugJump;


    switch (mcw->seq) {
      case _RETURN_START:
        if(CommMPIsConnectStalth()){   // 通信切断状態の場合
            msgNo = msg_underworld_47;
            mcw->seq = _OFFLINE_MSGWAIT;
        }
        else{
            msgNo = msg_underworld_50;
            mcw->seq = _ONLINE_MSGWAIT;
        }
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        break;
      case _ONLINE_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _ONLINE_YESNO_WAIT;
        }
        break;
      case _ONLINE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            mcw->pYesNoWork = NULL;
            mcw->seq = _RETURN_UG;
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _OFFLINE_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _OFFLINE_YESNO_WAIT;
        }
        break;
      case _OFFLINE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            mcw->pYesNoWork = NULL;
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_48, FALSE, NULL);
            mcw->seq = _CONNECT_CHKMSG;
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _CONNECT_CHKMSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _CONNECT_YESNO_WAIT;
        }
        break;
      case _CONNECT_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            mcw->pYesNoWork = NULL;
            mcw->seq = _RETURN_UG;
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _RETURN_UG:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        ugJump.bResult = TRUE;
        ugJump.baseNo = mcw->moveID;
        ugJump.bBaseIn = FALSE;
        CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);
        _returnUGMapEventForceDel(tcb,mcw);
        return;
    }

    if(!CommMPIsConnectStalth()){
        if((mcw->moveID < COMM_MACHINE_MAX) && !CommIsConnect(mcw->moveID)
           && (CommGetCurrentID() != COMM_PARENT_ID)){
            OHNO_PRINT("おいだし予約  %d \n",mcw->moveID);
            bClose = TRUE;
        }
    }
    if(bClose){
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        //        とりやめをさーばにそうしん
        _returnUGMapEventForceDelEnterBaseCheck(tcb,mcw);
        CommPlayerHoldEnd();
    }
}


//==============================================================================
/**
 * 秘密基地から炭鉱に戻る際のイベント
 * @param   pFSys フィールドシステム
 * @param   x,y,dir  移動先の位置
 * @param   netID 移動する人
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID)
{
    EVENT_UGCHG_WORK * mcw = NULL;

    _connectDisable();
    mcw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(EVENT_UGCHG_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
    mcw->next_door_id = DOOR_ID_JUMP_CODE;
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->netID = netID;
    mcw->moveID = moveID;
    mcw->next_zone_id = ZONE_ID_UG;
    mcw->nextDir = dir;
    mcw->pFSys = pFSys;

    mcw->pTCB = TCB_Add(GMEVENT_ReturnMapCheck, mcw,TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mcw,mcw->pTCB,_returnUGMapEventForceDelEnterBaseCheck);
    CommPlayerHold();
}

//==============================================================================
/**
 * 秘密基地から炭鉱に戻る際のイベントコンストラクタの生成
 * @param   pFSys フィールドシステム
 * @param   x,y,dir  移動先の位置
 * @param   netID 移動する人
 * @retval  コンストラクタ
 */
//==============================================================================

static EVENT_UGCHG_WORK* _createFactoryUGCHG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID)
{
    //ジャンプ
    EVENT_UGCHG_WORK * mcw = NULL;
    //イベント生成
    if(pFSys->event==NULL){
        mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
        MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
        mcw->next_door_id = DOOR_ID_JUMP_CODE;
        mcw->next_x = x;
        mcw->next_z = z;
        mcw->netID = netID;
        mcw->moveID = moveID;
        GF_ASSERT(pFSys->location->zone_id == ZONE_ID_UG); //今地下
        mcw->next_zone_id = ZONE_ID_UG;
        mcw->nextDir = dir;
    }
    return mcw;
}

//==============================================================================
/**
 * 自分の秘密基地に入っている人数を調べる
 * @param   netID   自分
 * @retval  人数
 */
//==============================================================================

static int _checkMySecretBaseEnterPlayersNum(int netID, BOOL bServer)
{
    int i,num=0,no,x,z;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(!CommIsConnect(i)){
            continue;
        }
        if(bServer){
            x = CommPlayerGetPosSX(i);
            z = CommPlayerGetPosSZ(i);
        }
        else{
            x = CommPlayerGetPosX(i);
            z = CommPlayerGetPosZ(i);
        }
        if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
        }
        else if(UgSecretBaseIsSecretBasePlace(x,z)){
            no = _getSecretIndex( x, z);
            OHNO_PRINT("%dさん %d基地 \n", i, no);
            if(no == netID){
                num++;
            }
        }
    }
    OHNO_PRINT("%dに入っているのは%d人です \n",netID,num);
    return num;
}

//--------------------------------------------------------------------------------------------
/**
 * あけておく・しめる ウィンドウセット
 *
 * @param	ini		BGLデータ
 * @param	data	ウィンドウデータ
 * @param	cgx		ウィンドウキャラ位置
 * @param	pal		ウィンドウパレット番号
 * @param	heap	ヒープID
 *
 * @return	BMPメニューワーク
 *
 * @li	BMPウィンドウとBMPメニューワークをAllocで取得している
 */
//--------------------------------------------------------------------------------------------
static BMPMENU_WORK * _connectSelectInit(
    GF_BGL_INI * ini, const BMPWIN_DAT * data, u16 cgx, u8 pal, u32 heap )
{
    BMPMENU_HEADER hed;
    MSGDATA_MANAGER * man = CommMsgGetMsgManager(CommUnderGetMsgUnderWorld());
    BMP_MENULIST_DATA * ld;

    ld  = BMP_MENULIST_Create( 2, heap );
    BMP_MENULIST_AddArchiveString( ld, man, msg_underworld_392, 0 );
    BMP_MENULIST_AddArchiveString( ld, man, msg_underworld_393, 1 );

    hed.menu     = ld;
    hed.win      = GF_BGL_BmpWinAllocGet( heap, 1 );
    hed.font     = FONT_SYSTEM;
    hed.x_max    = 1;
    hed.y_max    = 2;
    hed.line_spc = 0;
    hed.c_disp_f = 0;
    hed.line_spc = 0;

    GF_BGL_BmpWinAddEx( ini, hed.win, data );
    BmpMenuWinWrite( hed.win, WINDOW_TRANS_OFF, cgx, pal );
    return BmpMenuAddEx( &hed, 8, 0, 0, heap, PAD_BUTTON_CANCEL );
}

//==============================================================================
/**
 * 炭鉱から秘密基地に入る際のイベント 人のと自分のでは挙動が違う
 * @param   event イベントコントローラ
 * @retval  none
 */
//==============================================================================

typedef enum {
    _ENTER_START,
    _TARGET_MSGWAIT,
    _TARGET_YESNO_WAIT,
    _TARGET_ENTER_SB_WAIT,
    _MY_MSGWAIT,
    _MY_YESNO_WAIT,
    _MYSB_CHANGE_WAIT,
    _MYSB_CHANGE_YESNO_WAIT,
    _ENTER_MYSB_CHANGE_WAIT,
    _ENTER_MYSB_CHANGE,
    _ENTER_SB,
} EnterBaseCheck_e;


static void GMEVENT_EnterBaseCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    FIELDSYS_WORK * fsys = mcw->pFSys;
    LOCATION_WORK locationWork;
    int x=0,z=0,msgNo,ret, bClose = FALSE;
    _UgJumpEventResult ugJump;

    switch (mcw->seq) {
      case _ENTER_START:
        if(mcw->moveID != mcw->netID){
            msgNo = msg_underworld_45;   //
            mcw->seq = _TARGET_MSGWAIT;
        }
        else{
            msgNo = msg_underworld_41;
            mcw->seq = _MY_MSGWAIT;
        }
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        break;
      case _TARGET_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _TARGET_YESNO_WAIT;
        }
        break;
      case _TARGET_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            //            mcw->index = CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_46, FALSE, NULL);
            mcw->pYesNoWork = NULL;
            mcw->seq = _TARGET_ENTER_SB_WAIT;
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _TARGET_ENTER_SB_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->seq = _ENTER_SB;
        }
        break;
        // 自分の秘密基地に入る
      case _MY_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _MY_YESNO_WAIT;
        }
        break;
      case _MY_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            mcw->pYesNoWork = NULL;
            if(CommPlayerIsFlagData(mcw->moveID) || (_checkMySecretBaseEnterPlayersNum(mcw->moveID,FALSE) > 0) ){  // 旗を持っていっる
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_44, FALSE, NULL);
                mcw->seq = _TARGET_ENTER_SB_WAIT;
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_391, FALSE, NULL);
                mcw->seq = _MYSB_CHANGE_WAIT;
            }
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _MYSB_CHANGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = _connectSelectInit(fsys->bgl,
                                                 &_connectBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _MYSB_CHANGE_YESNO_WAIT;
        }
        break;
      case _MYSB_CHANGE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // あけておく
            mcw->pYesNoWork = NULL;
            mcw->seq = _TARGET_ENTER_SB_WAIT;
        }
        else if(ret == 1){ // 閉める
            mcw->pYesNoWork = NULL;
            mcw->seq = _ENTER_MYSB_CHANGE_WAIT;
        }
        else if(ret != BMPMENU_NULL){ // 閉める
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _ENTER_MYSB_CHANGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            // offline入場
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            CommFieldStateStalthUnderGround();
            mcw->seq = _ENTER_MYSB_CHANGE;
        }
        break;
      case _ENTER_MYSB_CHANGE:
        if(CommMPIsConnectStalth() && (CommGetCurrentID() == COMM_PARENT_ID)){
            u8 bFlag = _DRILL_START_REFORM;
            // 秘密基地作成をサーバーに送信 イベントは終了 ロックはかけたまま すでにOFFLINE
            CommSendFixSizeData(CF_DRILL_START, &bFlag);
            _returnUGMapEventForceDel(tcb,mcw);
            //CommPlayerHoldEnd();
            return; // TRUE;
        }
        break;
      case _ENTER_SB:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        // 普通に入るだけ ONLINE
        ugJump.bResult = TRUE;
        ugJump.baseNo = mcw->moveID;
        ugJump.bBaseIn = TRUE;
        CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);
        _returnUGMapEventForceDel(tcb,mcw);
        _pCommSecretBaseWork->moveTickets = _MOVE_TICKETS; // 発券
        return;
    }

    if((mcw->moveID != _SECRETBASE_MY_ID) && !CommPlayerIsActive(mcw->moveID)){
        if((_ENTER_MYSB_CHANGE_WAIT != mcw->seq) &&
           (_ENTER_MYSB_CHANGE != mcw->seq)){
            bClose = TRUE;
        }
    }
    if(bClose){  // とりやめ
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _returnUGMapEventForceDelEnterBaseCheck(tcb,mcw);
        CommPlayerHoldEnd();
//        return TRUE;
    }
//    return FALSE;
}

//==============================================================================
/**
 * @brief 炭鉱から秘密基地に行く際のイベント
 *        自分の秘密基地の場合レイアウトするかどうか聞かれる
 * @param   pFSys フィールドシステム
 * @param   x,y,dir  移動先の位置
 * @param   netID 移動する人
 * @retval  none
 */
//==============================================================================

static void _enterSecretBaseEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir,
                                  int netID, int moveID)
{
    EVENT_UGCHG_WORK * mcw = NULL;

    mcw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(EVENT_UGCHG_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
    mcw->next_door_id = DOOR_ID_JUMP_CODE;
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->netID = netID;
    mcw->moveID = moveID;
    mcw->next_zone_id = ZONE_ID_UG;
    mcw->nextDir = dir;
    mcw->pFSys = pFSys;
    mcw->timer = 0;

    _connectDisable();
    mcw->pTCB = TCB_Add(GMEVENT_EnterBaseCheck, mcw, TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mcw, mcw->pTCB, _returnUGMapEventForceDelEnterBaseCheck);
    CommPlayerHold();
}

//==============================================================================
/**
 * 秘密基地移動が完了したことをサーバーに伝えるコマンドのサイズ
 * @param   none
 * @retval  コマンドサイズ
 */
//==============================================================================

int CommSecretBaseInfoGetRetJumpSize(void)
{
    return sizeof(_SendPos);
}

//==============================================================================
/**
 * 秘密基地移動が完了したことをサーバーからもらった CF_SECRETBASE_RETJUMP
 * @param   x   位置
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvRetJump(int netID, int size, void* pData, void* pWork)
{
    _SendPos* pSendPos = pData;


    _pCommSecretBaseWork->travelBase[pSendPos->netID] = _INVALID_BASE;
    OHNO_PRINT("_pCommSecretBaseWork->travelBase[] %d %d\n",pSendPos->netID,_INVALID_BASE);

    if(CommGetCurrentID() == pSendPos->netID){
        UnderRecordReset();
        TalkAskForceReset();
        UgMgrForceExitNowTCB();
        UgTrapForceExit(CommGetCurrentID(), FALSE);
//        CommSendFixData(CF_TRAP_END);    // トラップ終わり
        CommSendFixData(CF_TRAP_END_FORCE);    // サーバー側も強制解除
        // 移動開始
        _pCommSecretBaseWork->bClientBaseIn = FALSE;
        OHNO_PRINT("秘密基地で無い移動開始 %d %d %d\n", pSendPos->netID,pSendPos->xpos,pSendPos->zpos);
        _jumpMapForUG(_pCommSecretBaseWork->pFSys, pSendPos->xpos, pSendPos->zpos, pSendPos->dir, pSendPos->netID, pSendPos->bRemove);
        _pCommSecretBaseWork->pNowMoveingBase = NULL;
    }
    else{  // キャラだけ移動
        UgTrapTurnDispEnd(pSendPos->netID);
        CommPlayerBaseTeleportClient(pSendPos->netID, pSendPos->xpos, pSendPos->zpos, pSendPos->dir);
    }
}

//==============================================================================
/**
 * 秘密基地移動が完了したことをサーバーに伝える
 * @param   x   位置
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoJumpEnd(void)
{
    OHNO_PRINT("秘密基地移動が完了 送信CF_SECRETBASE_JUMP_END\n");
    CommSendFixData(CF_SECRETBASE_JUMP_END);
}

//==============================================================================
/**
 * 秘密基地移動が完了   CF_SECRETBASE_JUMP_END
 * @param   x   位置
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvJumpEnd(int netID, int size, void* pData, void* pWork)
{
    OHNO_PRINT("受信\n");
    _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;
    _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
//    CommPlayerManagerReboot();
}

//==============================================================================
/**
 * 秘密基地移動を行っているかどうか
 * @param   netID プレーヤー
 * @retval  移動していたらTRUE
 */
//==============================================================================

BOOL CommSecretBaseIsTraveling(int netID)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->travelingBase[netID] != _INVALID_BASE){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 秘密基地情報を追加する
 * @param   x   位置
 * @param   y
 * @retval  none
 */
//==============================================================================

static void _insertBaseNetID(int x,int y, int dir, int netID)
{
    SecretBaseInfo* pWork = &_pCommSecretBaseWork->secretBaseData[netID];

    if(pWork){
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pWork->secretBaseDataBuff;
        SecretBaseSetSecretBasePosition(pSecret,x,y,CommPlayerGetReverseDir(dir));
        pWork->netID = netID;
    }
}

// 子機側のプログラム

//==============================================================================
/**
 * 子機側のプログラム  親機に秘密基地を送る
 *  とりあえず自分の一個だけ
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoChildSendStart(void)
{
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff;
    int i;
    u8 num=0;
    int id=CommGetCurrentID();

    /// 一個だけどキューにつんでおく
    OHNO_PRINT("秘密基地を送信したい-------------------%d-\n", id);

//    if(SecretBaseIsSecretBaseMake(pSecret)){

        OHNO_PRINT("秘密基地をキューに入れた----%d-\n", CF_SECRETBASE_DATA);
        CommSetSendQueue(CF_SECRETBASE_DATA,
                         &_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID],
                         sizeof(SecretBaseInfo));
//    }
}

// 親機側のプログラム

//==============================================================================
/**
 * 親機側のプログラム  子機に指定された秘密基地を送る
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoParentSendStart(int netID)
{
    OHNO_PRINT("子機に秘密基地を送ります %d \n", netID);
    CommSetSendQueue_ServerSide(CF_SECRETBASE_DATA_SERVER,
                                &_pCommSecretBaseWork->secretBaseData[netID],
                                sizeof(SecretBaseInfo));
}

//==============================================================================
/**
 * 子機側のプログラム  親機からきた今から移動する秘密基地データ CF_SECRETBASE_DATA_SERVER
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvDataServer(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SecretBaseInfo* pBase = pData;
    SECRETBASEDATA* pSecret;
    _Pos outDoorPos;
    int id,z;

    if(!_pCommSecretBaseWork){
        return;
    }

    if(CommGetCurrentID() == pBase->moveID){
        if(_pCommSecretBaseWork->moveTickets == _ERROR_TICKETS){
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;
            CommPlayerHoldEnd();
            CommSendFixData(CF_SECRETBASE_JUMP_END);
            CommPlayerSendPos(FALSE);
            OHNO_PRINT("エラーチケットなので座標を戻させる\n");
            return;
        }
    }
    _pCommSecretBaseWork->moveTickets = _TRANS_TICKETS;

    id = pBase->netID;
    OHNO_PRINT("移動可能   ---   秘密基地受信完了 %d\n",id);
    GF_ASSERT(id < _SECRETBASE_NUM_MAX);
    pBase = &_pCommSecretBaseWork->secretBaseData[id];
    MI_CpuCopy8(pData, pBase,  sizeof(SecretBaseInfo));

    _pCommSecretBaseWork->travelBase[pBase->moveID] = pBase->netID;
    OHNO_PRINT("_pCommSecretBaseWork->travelBase[pBase->moveID] %d %d\n",pBase->moveID,pBase->netID);
    // メッセージ表示
    if( pBase->netID != _SECRETBASE_MY_ID){
        _pCommSecretBaseWork->travelingBaseMessage[pBase->moveID] = pBase->netID;
    }
    // 移動する位置を計算
    _getSecretBaseOutPos(pBase->netID, &outDoorPos);
    if(CommGetCurrentID() == pBase->moveID){
        // 移動開始
        OHNO_PRINT("クライアント側秘密基地移動開始%d %d %d\n",pBase->netID, outDoorPos.xpos, outDoorPos.zpos-1);
        _pCommSecretBaseWork->bClientBaseIn = TRUE;
        _jumpMapForUG(_pCommSecretBaseWork->pFSys, outDoorPos.xpos, outDoorPos.zpos-1 , DIR_UP, pBase->moveID, FALSE);
        _pCommSecretBaseWork->pNowMoveingBase = pBase;

        pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;
        // 子機が戻る場所を記憶
        _pCommSecretBaseWork->resquePosX = SecretBaseGetSecretBasePositionX(pSecret);
        _pCommSecretBaseWork->resquePosZ = SecretBaseGetSecretBasePositionZ(pSecret);
        _pCommSecretBaseWork->resqueDir = SecretBaseGetSecretBasePositionDir(pSecret);
        OHNO_PRINT("戻る場所を記憶 %d %d %d\n",
                   _pCommSecretBaseWork->resquePosX,
                   _pCommSecretBaseWork->resquePosZ,
                   _pCommSecretBaseWork->resqueDir);
        UgInitialDataSend();
    }
    else{  // キャラだけ移動
        CommPlayerBaseTeleportClient(pBase->moveID, outDoorPos.xpos, outDoorPos.zpos, DIR_UP);
    }
}


//==============================================================================
/**
 * 親機側のプログラム  子機からきた秘密基地を格納する CF_SECRETBASE_DATA の受け取り側
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;

    if(!_pCommSecretBaseWork){
        return;
    }
    pBase = &_pCommSecretBaseWork->secretBaseData[netID];
    MI_CpuCopy8(pData,  pBase, sizeof(SecretBaseInfo));
    pBase->netID = netID;

    _pCommSecretBaseWork->bChildRecv = TRUE;  //子機データを受信した
    OHNO_PRINT("親機が秘密基地受け取った %d\n", netID);
    OHNO_SP_PRINT("親機が秘密基地受け取った %d\n", netID);
    pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    // 位置を差し替えて子機に分配
    _pCommSecretBaseWork->secretHDataServer[netID].xpos = SecretBaseGetSecretBasePositionX(pSecret);
    _pCommSecretBaseWork->secretHDataServer[netID].zpos = SecretBaseGetSecretBasePositionZ(pSecret);
    _pCommSecretBaseWork->secretHDataServer[netID].dir = SecretBaseGetSecretBasePositionDir(pSecret);
    _sendSecretBasePosition();

    // あたりデータ作成
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[netID]);
    //UgSecretBaseResetPlayer(netID);

    UgSecretBaseFirstConnectChild(netID);
    
}

//==============================================================================
/**
 * 秘密基地データサイズを返す
 * @param   none
 * @retval  サイズ
 */
//==============================================================================

int CommSecretBaseInfoGetDataSize(void)
{
    return sizeof(SecretBaseInfo);
}

BOOL CommSecretBaseInfoIsChildRecv(void)
{
    return _pCommSecretBaseWork->bChildRecv;
}

void CommSecretBaseResetChildRecv(void)
{
    _pCommSecretBaseWork->bChildRecv = FALSE;
}

BOOL CommSecretBaseInfoIsPosRecv(void)
{
    return _pCommSecretBaseWork->bPosRecv;
}

void CommSecretBaseResetPosRecv(void)
{
    _pCommSecretBaseWork->bPosRecv = FALSE;
}

//==============================================================================
/**
 *  秘密基地の位置のみをコンパクト化して送る
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _sendSecretBasePosition(void)
{
    int i,j;

    j = 0;
    for(i = 0; i < COMM_MACHINE_MAX;i++){
        _Pos* pHead = &_pCommSecretBaseWork->secretHDataServer[i];
        _pCommSecretBaseWork->sendBuff[j] = pHead->xpos & 0xff;
        j++;
        _pCommSecretBaseWork->sendBuff[j] = ((pHead->xpos >> 8) & 0xf) + ((pHead->zpos >> 4) & 0xf0);
        j++;
        _pCommSecretBaseWork->sendBuff[j] = pHead->zpos & 0xff;
        j++;
        _pCommSecretBaseWork->sendBuff[j] = pHead->dir;
        j++;
    }
    CommSetSendQueue_ServerSide(CF_SECRETBASE_POS,
                                &_pCommSecretBaseWork->sendBuff,
                                sizeof(_pCommSecretBaseWork->sendBuff));
}

//==============================================================================
/**
 *  秘密基地の位置のみを受信する   CF_SECRETBASE_POS
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvPos(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = (u8*)pData;
    _Pos aDoorData;
    _Pos* pHead;
    _Pos* pOldDoor;

    
    int i,j;
    if(!_pCommSecretBaseWork){
        return;
    }

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _doorPictDelete( i );
    }
    j = 0;
    for(i = 0; i < COMM_MACHINE_MAX;i++){
        pOldDoor = &_pCommSecretBaseWork->secretHeaderData[i];
        pHead = &aDoorData;
        pHead->xpos = pBuff[j];
        j++;
        pHead->xpos += ((int)pBuff[j] << 8 & 0xf00);
        pHead->zpos = ((int)pBuff[j] << 4 & 0xf00);
        j++;
        pHead->zpos += pBuff[j];
        j++;
        pHead->dir = pBuff[j];
        j++;
        if((_PLAYER_INVALID_GRID != pHead->xpos) && (_PLAYER_INVALID_GRID != pHead->zpos)){
//            if((pHead->xpos == pOldDoor->xpos) && (pHead->zpos == pOldDoor->zpos) && (pHead->dir == pOldDoor->dir)){
//                OHNO_PRINT("同じだから置かない\n");
//            }
//            else{
                MI_CpuCopy8(pHead, pOldDoor, sizeof(_Pos));
                _doorPictAdd(pHead->xpos, pHead->zpos, pHead->dir, i);
//            }
        }
    }
    _pCommSecretBaseWork->bPosRecv = TRUE;
    OHNO_PRINT("秘密基地位置受信\n");
}

//==============================================================================
/**
 *  秘密基地の位置データのサイズを返す
 * @param   none
 * @retval  none
 */
//==============================================================================

int CommSecretBaseInfoGetPosSize(void)
{
    return sizeof(_pCommSecretBaseWork->sendBuff);
}

//==============================================================================
/**
 * ドアを表示
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictAdd(int x, int z, int dir, int index)
{
    VecFx32 vtx;
    int px,pz;

    _pCommSecretBaseWork->doorActDir[index] = dir;
    _pCommSecretBaseWork->doorActX[index] = x;
    _pCommSecretBaseWork->doorActZ[index] = z;
}

//==============================================================================
/**
 * ドアを状態をみて表示
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _taskDoor(TCB_PTR tcb , void* work)
{
    int i,x,z,dir,px,pz;
    
    if(_pCommSecretBaseWork->bHalt){
        return;
    }
    if(!_pCommSecretBaseWork->bDoorON){
        return;
    }
    if(_pCommSecretBaseWork->pFSys->player==NULL){
        return;
    }
    
    px = Player_NowGPosXGet( _pCommSecretBaseWork->pFSys->player );
    pz = Player_NowGPosZGet( _pCommSecretBaseWork->pFSys->player );
    if(UgSecretBaseIsSecretBasePlace(px,pz)){
 //       OHNO_PRINT("秘密基地ではドアを作らない %d %d\n",px,pz);
        return;  //自分が秘密基地にいる場合生成しない
    }


    for(i = 0;i < _SECRETBASE_NUM_MAX; i++){

        if(i < COMM_MACHINE_MAX){
            if(NULL==CommInfoGetMyStatus(i)){
                UgSecretBaseDestroyDoor(i);
                UgSecretBaseTrapGoodsReset(i);
//                UgSecretBaseResetPlayer(i);
            }
        }

        if(_pCommSecretBaseWork->doorActDir[i] != (u8)DIR_NOT){
            dir = _pCommSecretBaseWork->doorActDir[i];
            x = _pCommSecretBaseWork->doorActX[i];
            z = _pCommSecretBaseWork->doorActZ[i];
            if(_pCommSecretBaseWork->doorAct[i] != _M3DO_NONE){
                M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[i],
                                   _pCommSecretBaseWork->pFSys->Map3DObjExp);
            }
            {
                VecFx32 vtx;
                vtx.x = (x) * (FX32_ONE*16) + (FX32_ONE*8);
                vtx.y = 0;
                vtx.z = (z) * (FX32_ONE*16) + (FX32_ONE*8);
                _pCommSecretBaseWork->doorAct[i] =
                    M3DO_SetMap3DObjExp(_pCommSecretBaseWork->pFSys->Map3DObjExp,
                                        _pCommSecretBaseWork->pFSys->MapResource,
                                        BMID_UG_HOLE_B+dir,
                                        &vtx, NULL,
                                        _pCommSecretBaseWork->pFSys->field_3d_anime);
            }
        }
    }
}


//==============================================================================
/**
 * ドアを消去
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictDelete(int netID)
{
    if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
        M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID],
                           _pCommSecretBaseWork->pFSys->Map3DObjExp);
        OHNO_PRINT("ドア消去^^^^^^ %d\n",netID);
        
        _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        _pCommSecretBaseWork->doorActDir[netID] = DIR_NOT;
    }
}

//==============================================================================
/**
 * ドアを消去
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictFinalize(void)
{
    int i;

    if(_pCommSecretBaseWork==NULL){
        return;
    }
    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        _doorPictDelete(i);
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL Sub_UgFadeOut(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

    switch (mcw->subseq) {
      case 0:
        GameSystem_FinishFieldProc(fsys);
        (mcw->subseq) ++;
        break;
      case 1:
        if (!GameSystem_CheckFieldProcExists(fsys)) {
            mcw->subseq = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL Sub_UgFadeIn(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

    switch (mcw->subseq) {
      case 0:
        GameSystem_CreateFieldProc(fsys);
        (mcw->subseq) ++;
        break;
      case 1:
        if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
            mcw->subseq = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}


//==============================================================================
/**
 *  指定位置へジャンプするイベント
 * @param   event イベントコントローラー
 * @retval  none
 */
//==============================================================================

static BOOL GMEVENT_JumpMapForUG(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
    LOCATION_WORK locationWork;
    int x=0,z=0;

    enum{
        _JP_START,
        _JP_START_WAIT,
        _RADAR_WAIT,
        _UG_FADE_WAIT,
        _MAP_CHANGE,
        _UG_FADEIN,
        _WIPE_IN,
        _FADE_END,
        _REMOVEPLAYER_MSGWAIT,
        _START_WALK,
        _START_TURN,
        _TURN_FRONT,
        _MESSAGE_WAIT,
        _END,

    };


    switch (mcw->seq) {
      case _JP_START:
        UgSecretBaseBootOn(FALSE);
        _connectDisable();
        mcw->connectNum = CommGetConnectNum();
        CommDisableSendMoveData();
        CommDigStoneManagerReset();  //タマが光っていると都合が悪い
        if( CommStateJumpUnderGround() ){
            mcw->seq = _JP_START_WAIT;
        }
		break;
      case _JP_START_WAIT:
        WIPE_SYS_ExeEnd(); 
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_HOLEOUT,WIPE_TYPE_TUNNELOUT,
                       WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        UnderGround_RadarEnd(fsys->UnderGroundRadar);
        Snd_SePlay(UG_SE_HOLE_IN);
        mcw->seq++;
        break;
      case _RADAR_WAIT:
        if(WIPE_SYS_EndCheck()){
            if (fsys->UnderGroundRadar == NULL){
                (mcw->seq) ++;
            }
        }
        break;
      case _UG_FADE_WAIT:
        if(Sub_UgFadeOut(event)){		// プロックChange
            (mcw->seq) ++;
        }
        break;
      case _MAP_CHANGE:
        locationWork.zone_id = mcw->next_zone_id;
        locationWork.door_id = mcw->next_door_id;
        OHNO_PRINT("---移動目標  %d %d \n",mcw->next_x,mcw->next_z);
        
        locationWork.grid_x = mcw->next_x;
        locationWork.grid_z = mcw->next_z;
        locationWork.dir = mcw->nextDir;
        //CommPlayerManagerReset();
        EventCmd_UgJumpByLocation(event, &locationWork);
        (mcw->seq) ++;
        break;
      case _UG_FADEIN:
        if(Sub_UgFadeIn(event)){		// プロックChange
            //CommPlayerManagerReboot();
            (mcw->seq) ++;
        }
        break;
      case _WIPE_IN:
        fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//炭鉱レーダー画面ＯＮ
        WIPE_SYS_ExeEnd();
        WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                       WIPE_TYPE_HOLEIN, WIPE_TYPE_TUNNELIN,
                       WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        (mcw->seq) ++;
        break;
      case _FADE_END:
        if(!WIPE_SYS_EndCheck()){
            break;
        }
        if( CommMPIsConnectStalth() && !UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z)){
            mcw->bMessage = FALSE;
        }
        else{
            mcw->bMessage = TRUE;
        }
        CommEnableSendMoveData();
        CommPlayerHold();
        // 暗いフォントパレット
        ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_MAIN_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);
        MenuWinGraphicSet(
            fsys->bgl, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
            MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );
        if(mcw->bRemove){
            CommPlayerHoldBitOff();
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_51, FALSE, NULL);
            mcw->seq = _REMOVEPLAYER_MSGWAIT;
        }
        else if(!_pCommSecretBaseWork->bClientBaseIn){
            mcw->seq = _END;
        }
        else{
            mcw->timer = 0;
            mcw->seq = _START_WALK;
        }
        break;
      case _START_WALK:
        mcw->timer++;
/*        if(mcw->timer > 20){
            int xpos = Player_NowGPosXGet( fsys->player );
            int zpos = Player_NowGPosZGet( fsys->player );
            if(!CommMPIsConnectStalth() || !mcw->bMessage){
                CommPlayerSendPosXZ(FALSE,xpos,zpos);
                mcw->timer = 0;
                mcw->seq = _START_TURN;
            }
            else{
                CommPlayerSendPosXZ(FALSE,xpos,zpos - 1);
                mcw->timer = 0;
                mcw->seq = _START_TURN;
            }
        }*/
        mcw->timer = 0;
        mcw->seq = _START_TURN;
        break;
      case _START_TURN:
        mcw->timer++;
        if(mcw->timer > 10){
            if(!CommMPIsConnectStalth() || !mcw->bMessage){
                mcw->seq = _END;
            }
            else{
                mcw->seq = _TURN_FRONT;
            }
        }
        break;
      case _TURN_FRONT:
        CommSetForceDir();
        Player_AcmdSet( fsys->player, FieldOBJ_AcmdCodeDirChange( DIR_DOWN, AC_STAY_WALK_U_4F ) );
        CommPlayerSetDir(DIR_DOWN);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_68, FALSE, NULL);
        Snd_SePlay(UG_SE_CLOSE_DOOR);
        mcw->seq = _MESSAGE_WAIT;
        break;
      case _MESSAGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                mcw->seq = _END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                CommPlayerSetDir(DIR_UP);
            }
        }
        break;
      case _END:
        if( CommMPIsConnectStalth() && !UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z)){
            CommFieldStateUnderGroundReConnect();  // 再接続する場合の処理
        }
        else{
            CommStateJumpEndUnderGround(); // 移動終了する場合の通信関連処理
        }
        CommPlayerHoldEnd();
        sys_FreeMemoryEz(mcw);
        if( CommMPIsConnectStalth() && UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z) ){
            UgMgrSetNoneRadarDisp();
        }
        else{
            UgMgrSetMyTrapRadarDisp();
        }
        OHNO_PRINT("移動終わり\n");
        if((_pCommSecretBaseWork->moveTickets == _DISCONECT_TICKETS) && (_pCommSecretBaseWork->bClientBaseIn)){
            OHNO_PRINT("エラーなら戻りに\n");
            _pCommSecretBaseWork->moveTickets = _RETURN_TICKETS;
        }
        else{
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;
        }
        _connectEnable();
        UgSecretBaseBootOn(TRUE);
        return TRUE;
      case _REMOVEPLAYER_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                mcw->seq = _END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                return FALSE;
            }
        }
        if((CommGetConnectNum() > 1)  && (mcw->connectNum==0)){  // 誰かとつながったら
            OHNO_PRINT("つながったのでウインドウ消します\n");
            mcw->seq = _END;
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        }
        break;
    }
    return FALSE;
}

//==============================================================================
/**
 *  指定位置へジャンプするイベント起動
 * @param   pFSys  FIELDSYS_WORK*
 * @param   int x, int z, int dir  移動する位置と方向
 * @retval  none
 */
//==============================================================================

static void _jumpMapForUG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, BOOL bRemove)
{
    EVENT_UGCHG_WORK * mcw = _createFactoryUGCHG(pFSys, x, z, dir, netID, netID);
    if(mcw){
        //イベント生成
        mcw->bRemove = bRemove;
        FieldEvent_Set(pFSys, GMEVENT_JumpMapForUG, mcw);
    }
}


//==============================================================================
/**
 *  ドリルで秘密基地を作る
 * @param   none
 * @retval  none
 */
//==============================================================================

typedef enum{
    _DRILL_ANIM,
    _ENTER_FIRST_WAIT,
    _HOLE_MODEL_PUT,
    _QUESTION_MSG,
    _NODIG_WAIT,
    _YESNO_MSG,
    _YESNO_WAIT,
    _SHUTDOWN_MSG,
    _SHUTDOWN_WAIT,
    _DISCONNECT_MSG_WAIT,
    _DISCONNECT_WAIT,
};

static void _GMEVENT_Drill(TCB_PTR tcb, void* work)
{
    _EVENT_DRILL_WORK * mdw = work;
    FIELDSYS_WORK* fsys = mdw->pFSys;
    LOCATION_WORK locationWork;
    u32 ret;
    BOOL bExit = FALSE;
    int msgNo;
    int x,z,dir;

    switch (mdw->seq) {
      case _DRILL_ANIM:
        {
            SECRETBASEDATA* pSecret = SaveData_GetSecretBaseData(fsys->savedata);
            mdw->bBaseDoor = SecretBaseIsSecretBaseMake(pSecret);
        }
        CommPlayerHold();
        CommMsgRegisterUGTrapName(CommUnderGetMsgUnderWorld(), UG_TRAPTYPE_DRILL);
        Snd_SePlay(UG_SE_DRILL);

        FE_FldOBJDrillSet( Player_FieldOBJGet(fsys->player), 0, 0, 0 );

        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_36, FALSE, NULL);
        mdw->seq = _ENTER_FIRST_WAIT;
        mdw->timer = 0;
        break;
      case _ENTER_FIRST_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mdw->timer++;
            if(mdw->timer > 30){
                mdw->seq = _HOLE_MODEL_PUT;
            }
        }
        break;
      case _HOLE_MODEL_PUT:
        {
            x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
            z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
            dir = CommPlayerGetReverseDir(Player_DirGet( fsys->player ));
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_37, FALSE, NULL);
            _doorPictAdd(x, z, dir, _SECRETBASE_MY_ID);  // 前の穴は開いたまま
            FE_FldOBJTrapsmogSet(fsys, x, 0, z);
            mdw->seq = _QUESTION_MSG;
        }
        break;
      case _QUESTION_MSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(_checkMySecretBaseEnterPlayersNum(CommGetCurrentID(),FALSE)){
                msgNo = msg_underworld_57;
                mdw->seq = _NODIG_WAIT;
            }
            else if(mdw->bBaseDoor){
                msgNo = msg_underworld_39;
                mdw->seq = _YESNO_MSG;
            }
            else{
                msgNo = msg_underworld_38;
                mdw->seq = _YESNO_MSG;
            }
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        }
        break;
      case _NODIG_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & PAD_BUTTON_DECIDE){
                bExit = TRUE;
            }
        }
        break;
      case _YESNO_MSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mdw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mdw->seq = _YESNO_WAIT;
        }
        break;
      case _YESNO_WAIT:
        ret = BmpYesNoSelectMain(mdw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // はいを選択した場合
            mdw->seq = _DISCONNECT_MSG_WAIT;
            mdw->pYesNoWork = NULL;
        }
        else if(ret != BMPMENU_NULL){ // いいえを選択した場合 終了
            bExit = TRUE;
            mdw->pYesNoWork = NULL;
        }
        break;
      case _DISCONNECT_MSG_WAIT:
        // offlineの基地へ移動 通信切断
        CommUnderBagDeleteTrap(UG_TRAPTYPE_DRILL);  // ドリルをここで消す
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
//        CommStateFieldEnableChange();
        CommFieldStateStalthUnderGround();
        mdw->seq = _DISCONNECT_WAIT;
        break;
      case _DISCONNECT_WAIT:
        if(CommMPIsConnectStalth() && (CommGetCurrentID() == COMM_PARENT_ID)){
            u8 bFlag = _DRILL_START_NEW;

            if(mdw->bBaseDoor){
                bFlag = _DRILL_START_RENEW;
            }
            // 秘密基地作成をサーバーに送信 イベントは終了 ロックはかけたまま すでにOFFLINE
            _createSecretBase();  // 新規作成
            CommSendFixSizeData(CF_DRILL_START, &bFlag);
            TCB_Delete(tcb);
            sys_FreeMemoryEz(mdw);
            UgMgrEndNowTCB();
            return;
        }
        break;
    }
    if(bExit){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_56, TRUE, _msgEndCallBack);
        _doorPictDelete(_SECRETBASE_MY_ID);
        {
            x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
            z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
            FE_FldOBJTrapsmogSet(fsys, x, 0, z);
        }
        TCB_Delete(tcb);
        sys_FreeMemoryEz(mdw);
        UgMgrEndNowTCB();
        _connectEnable();
    }
}

//==============================================================================
/**
 * @brief   秘密基地の穴を掘る
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseDrillStart(void)
{
    u8 bFlag = _DRILL_START_CHECK;
    CommSendFixSizeData(CF_DRILL_START, &bFlag);   // まずは掘っていいかどうか問い合わせ
}

//==============================================================================
/**
 * @brief   秘密基地の穴を掘る CF_DRILL_START
 * @param   none
 * @retval  none
 */
//==============================================================================

typedef struct{
    u8 netID;
    u8 result;
} _resultStruct;

typedef enum{
    _SB_CREATE_NG,
    _SB_CREATE_START,
    _SB_CREATED,
    _SB_CREATED_CHANGE,
    _SB_CREATED_NEW,
    _SB_CREATE_FAILED,
    _SB_INSB_FAILED,
};


int CommSecretBaseDrillStartResultSize(void)
{
    return sizeof(_resultStruct);
}

void CommSecretBaseRecvDrillStart(int netID, int size, void* pData, void* pWork)
{
    u8* pCreateFlag = pData;
    int x = CommPlayerGetPosSXDirAdd(netID);
    int z = CommPlayerGetPosSZDirAdd(netID);
    int x1,z1,x2,z2;
    int dir = CommPlayerGetSDir(netID);
    _resultStruct ret;
    int id;

    x2 = x - CommPlayerGetPosSX(netID);  //左右のあたりも見る
    z2 = z - CommPlayerGetPosSZ(netID);
    if(z2 != 0){
        x1 = x+1;
        x2 = x-1;
        z2 = z1 = z;
    }
    else{
        z1 = z+1;
        z2 = z-1;
        x2 = x1 = x;
    }
    ret.netID = netID;
    if(pCreateFlag[0] == FALSE){
        ret.result = _SB_CREATE_NG;
    }
    else{
        ret.result = _SB_CREATE_FAILED;
    }
    id = _getSecretBaseEnter(x, z);
//    if((id != INVALID_NETID) && (id != netID)){   // 誰かの秘密基地がある場合作れない
    if((pCreateFlag[0] == FALSE) && (id != INVALID_NETID)){   // 誰かの秘密基地がある場合作れない
        OHNO_PRINT("ここをとおるとほれない----\n");
    }
    else if(UgSecretBaseIsSecretBasePlace(x, z)){  // ここが秘密基地内の場合ほれない
        ret.result = _SB_INSB_FAILED;
    }
    else if(GetHitAttr(_pCommSecretBaseWork->pFSys,x,z) &&
            GetHitAttr(_pCommSecretBaseWork->pFSys,x1,z1) &&
            GetHitAttr(_pCommSecretBaseWork->pFSys,x2,z2)){  // あたりある場合
        if(pCreateFlag[0] == FALSE){    // 作るイベントを開始していい事を送信
            ret.result = _SB_CREATE_START;
        }
        else{
            _insertBaseNetID(x, z, dir, _SECRETBASE_MY_ID);  // 場作成
            if(_enterSecretBaseStart(_SECRETBASE_MY_ID,netID)){  // 場ジャンプ
                OHNO_PRINT("CF_DRILL_START 移動開始メッセージがきた %d\n",netID);
                switch(pCreateFlag[0]){
                  case _DRILL_START_REFORM:
                    ret.result = _SB_CREATED;
                    break;
                  case _DRILL_START_RENEW:
                    ret.result = _SB_CREATED_CHANGE;
                    break;
                  case _DRILL_START_NEW:
                    ret.result = _SB_CREATED_NEW;
                    break;
                }
            }
        }
    }
    CommSendFixSizeData_ServerSide(CF_DRILL_START_RESULT, &ret);
}



static void _returnDrillEventForceDel(TCB_PTR tcb,void* work)
{
    _EVENT_DRILL_WORK* mcw = work;


    _doorPictDelete(_SECRETBASE_MY_ID);

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }
    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
    CommPlayerHoldEnd();
    _connectEnable();
}

//==============================================================================
/**
 * @brief   ドリルイベントセット
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _drillEventStart(void)
{
    _EVENT_DRILL_WORK * mdw;

    _connectDisable();
    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_DRILL_WORK));
    MI_CpuClear8(mdw,sizeof(_EVENT_DRILL_WORK));
    mdw->seq = _DRILL_ANIM;
    mdw->netID = CommGetCurrentID();  // 開始する際のID これが食い違ったら強制終了
    mdw->pFSys = _pCommSecretBaseWork->pFSys;
    
    mdw->pTCB = TCB_Add( _GMEVENT_Drill, mdw, TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mdw, mdw->pTCB, _returnDrillEventForceDel);

}

//==============================================================================
/**
 * @brief   秘密基地の穴を掘る サーバーからの戻り   CF_DRILL_START_RESULT
 * @param   none
 * @retval  none
 */
//==============================================================================


void CommSecretBaseRecvDrillStartResult(int netID, int size, void* pData, void* pWork)
{
    _resultStruct* pRet = pData;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));

    if(pRet->netID != CommGetCurrentID()){  // 本人以外関係ない
        return;
    }
    OS_TPrintf("穴掘り結果 %d\n",pRet->result);
    if(pRet->result == _SB_CREATE_NG){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_54, TRUE, _msgEndCallBack);
        _connectEnable();
    }
    else if(pRet->result == _SB_CREATE_START){
        // 壁に穴あける演出開始
        _drillEventStart();
    }
    else if(pRet->result ==_SB_INSB_FAILED){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_74, TRUE, _msgEndCallBack);
        _connectEnable();
    }
    else if(pRet->result == _SB_CREATE_FAILED){  //何かの原因でほれなかった
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_88, TRUE, _msgEndCallBack);
        CommFieldStateUnderGroundReConnect();
        _connectEnable();
    }
    else if((pRet->result == _SB_CREATED) ||
            (pRet->result == _SB_CREATED_CHANGE) ||
            (pRet->result == _SB_CREATED_NEW)){  // 穴あけ完了   // MAPCHANGE     // 通信切断
        _Pos outDoorPos;
        int x = CommPlayerGetPosXDirAdd(pRet->netID);
        int z = CommPlayerGetPosZDirAdd(pRet->netID);
        int dir = CommPlayerGetDir(pRet->netID);
        _insertBaseNetID(x, z, dir, pRet->netID);        // 作成
        _insertBaseNetID(x, z, dir, _SECRETBASE_MY_ID);  // 作成

        if(pRet->result == _SB_CREATED_CHANGE){ // 穴あけ完了   // MAPCHANGE     // 通信切断
            SecretBaseRecordSetRelocateNum(pRec);  // 引越しした回数カウント
            OHNO_PRINT("引越しした回数カウント  %d\n",SecretBaseRecordGetRelocateNum(pRec));
        }
        if((pRet->result == _SB_CREATED_CHANGE) || (pRet->result == _SB_CREATED_NEW)){ // 穴あけ完了   // MAPCHANGE     // 通信切断
            void* pBuf = FNOTE_ActionUGBaseDataMake(HEAPID_WORLD);
            FNOTE_DataSave(_pCommSecretBaseWork->pFSys->fnote, pBuf, FNOTE_TYPE_ACTION);
            RECORD_Score_Add(SaveData_GetRecord(_pCommSecretBaseWork->pFSys->savedata), SCORE_ID_MAKE_BASE);
            OHNO_PRINT("作った+引越しした回数カウント\n");
        }
    }
}


//==============================================================================
/**
 * @brief   秘密基地に行った状況メッセージを返す
 * @param   message   メッセージ
 * @retval  メッセージがある場合TRUE
 */
//==============================================================================

BOOL CommSecretBaseInfoGetActionMessage(STRBUF* pStrBuf)
{
    int i,target;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCommSecretBaseWork){
        return FALSE;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCommSecretBaseWork->travelingBaseMessage[i] != _INVALID_BASE){
            target = _pCommSecretBaseWork->travelingBaseMessage[i];
            _pCommSecretBaseWork->travelingBaseMessage[i] = _INVALID_BASE;
            if(i != target ){
                pMy = CommInfoGetMyStatus(i);
                pTarget = CommInfoGetMyStatus(target);
                if(UgMgrRadarLogDouble(pMy,pTarget,UGSecretBaseIn01,pStrBuf)){
                    return TRUE;
                }
            }
        }
        if(_pCommSecretBaseWork->flagGetLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCommSecretBaseWork->flagGetLog[i]);
            _pCommSecretBaseWork->flagGetLog[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy,pTarget,UGGetflag01,pStrBuf)){
                return TRUE;
            }
        }
        if(_pCommSecretBaseWork->flagReverseLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            _pCommSecretBaseWork->flagReverseLog[i] = INVALID_NETID;
            if(UgMgrRadarLogSingle(pMy, 0, UGGetflag02, pStrBuf)){
                return TRUE;
            }
            break;
        }
        if(_pCommSecretBaseWork->flagConqureLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCommSecretBaseWork->flagConqureLog[i]);
            _pCommSecretBaseWork->flagConqureLog[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy, pTarget, UGGetflag03, pStrBuf)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * @brief   今からセットアップする秘密基地グッズデータを返す
 * @param   sv  SAVEDATA*
 * @retval  SECRETBASEDATA*
 */
//==============================================================================

SECRETBASEDATA* UgSetupSecretBaseData(SAVEDATA * sv)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return (SECRETBASEDATA*)_pCommSecretBaseWork->pNowMoveingBase->secretBaseDataBuff;
        }
        //        return SaveData_GetSecretBaseData(sv);
    }
    return NULL;
}

//==============================================================================
/**
 * @brief   今からセットアップする秘密基地のXブロックを返す
 * @param   none
 * @retval  Xグリッド
 */
//==============================================================================

int UgSetupSecretBaseBlockX(void)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return _blockToRoomX[_pCommSecretBaseWork->pNowMoveingBase->netID];
        }
    }
    return 0;
}

//==============================================================================
/**
 * @brief   今からセットアップする秘密基地のZブロックを返す
 * @param   none
 * @retval  Zグリッド
 */
//==============================================================================

int UgSetupSecretBaseBlockZ(void)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return _blockToRoomZ[_pCommSecretBaseWork->pNowMoveingBase->netID];
        }
    }
    return 0;
}

//==============================================================================
/**
 * @brief   秘密基地グッズに当たっていないかどうか検査
 * @param   x,z 位置
 * @retval  いける場合TRUE
 */
//==============================================================================

BOOL UgSecretBaseMoveing(int x, int z)
{
    int blockX,blockZ,i;

    if(!_pCommSecretBaseWork){
        return TRUE;
    }
    if(z >= (_SECRETBASE_ATTR_MAX*2)){
        return TRUE;
    }
    blockX = x / _SECRETBASE_ATTR_MAX;
    blockZ = z / _SECRETBASE_ATTR_MAX;

    for(i = 0; i < _SECRETBASE_NUM_MAX;i++){
        if((blockX == _blockToRoomX[i]) &&
           (blockZ == _blockToRoomZ[i])){
            blockX = x % _SECRETBASE_ATTR_MAX;
            blockZ = z % _SECRETBASE_ATTR_MAX;
            if(_pCommSecretBaseWork->aAttr[i][blockZ] & (0x1 << blockX)){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
    }
    return TRUE;
}

//==============================================================================
/**
 * @brief   新規に部屋を作る場合岩だらけにする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _createSecretBase(void)
{
    SECRETBASEDATA* pSBData = SaveData_GetSecretBaseData(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));
    int px = CommPlayerGetPosSXDirAdd(COMM_PARENT_ID);
    int pz = CommPlayerGetPosSZDirAdd(COMM_PARENT_ID);
    int dir = CommPlayerGetSDir(COMM_PARENT_ID);
    int i, ansX, ansZ, bOk, chk;
    const int x1 = 10,x2 = 18,z = 12, xMod = 5, zMod=6;
    MATHRandContext32 sRand;
    int add[SECRETBASE_LOCK_NUM_MAX+1][2];

    add[0][0] = 16; // パソコンとかぶる位置
    add[0][1] = 12;

    SysFlag_UgBaseSet(SaveData_GetEventWork(_pCommSecretBaseWork->pFSys->savedata));

    SecretBaseData_Reform(pSBData);  // 配置していない状態にする

    UnderGroundTrashAllGoodsPCItem(pUGData);

    CommRandSeedInitialize(&sRand);
    for(i = 0; i < SECRETBASE_LOCK_NUM_MAX; i++){
        ansX = MATH_Rand32(&sRand, xMod);
        if(ansX < 2){
            ansX = ansX * 2 + x1;
        }
        else{
            ansX = (ansX-3) * 2 + x2;
        }
        ansZ = MATH_Rand32(&sRand, zMod) * 2 + z;
        OHNO_PRINT("乱数検査 %d %d\n",ansX,ansZ);
        bOk=TRUE;
        for(chk = 0; chk <= i; chk++){
            if((add[chk][0] == ansX) && (add[chk][1] == ansZ)){
                bOk = FALSE;
                break;
            }
        }
        if(!bOk){
            i--;
            continue;
        }
        SecretBaseData_ChangeGoodsPosition(pSBData,
                                           SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX+i,
                                           ansX, ansZ);
        add[i+1][0] = ansX;
        add[i+1][1] = ansZ;
    }

    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );
    SecretBaseSetSecretBasePosition(pSBData,px,pz,CommPlayerGetReverseDir(dir));
    MI_CpuCopy8(pSBData,_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    // あたりを作る
    _makeAttr(pSBData,_pCommSecretBaseWork->aAttr[_SECRETBASE_MY_ID]);
}

//--------------------------------------------------------------
/**
 * @brief   もようがえメッセージ開始
 * @param   messageNo   gmmラベル
 * @retval  メッセージインデックス
 */
//--------------------------------------------------------------

int UgSecretBaseTalkStart(int messageNo)
{
    return CommMsgTalkWindowStart(CommUnderGetMsgUnderEdit(),messageNo,FALSE,NULL);

}

//--------------------------------------------------------------
/**
 * @brief   もようがえの会話終了
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkEnd(void)
{
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderEdit());
}

//--------------------------------------------------------------
/**
 * @brief   グッズの名前をメッセージに表示させる場合の関数
 * @param   type     グッズタイプ = gmm番号
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkRegisterGoodsName(int type)
{
    CommMsgRegisterUGGoodsNameIndex(CommUnderGetMsgUnderEdit(),0,type);
}

//--------------------------------------------------------------
/**
 * @brief   ２桁の数字をメッセージに表示させる場合の関数
 * @param   number     数字
 * @param   index      元メッセージに書いてある番号
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkRegisterNum2(int number,int index)
{
    CommMsgRegisterNumber2Index(CommUnderGetMsgUnderEdit(),index,number);
}



//==============================================================================
/**
 * このあたりが何のグッズか返す
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

static int _getAttrGoodsType(SECRETBASEDATA* pSecret,int xa,int za)
{
    int i,x,z;
    const u8* pBuff;

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        if(i == 0){
            continue;  // いらない
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            continue;  // いらない
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        x = xa - x;
        z = za - z;
        if((x < 0) || (x > 2)){
            continue;
        }
        if((z < 0) || (z > 2)){
            continue;
        }
        if(pBuff[z*3+x]){
            return type;
        }
    }
    return GOODS_INVALID;
}

//--------------------------------------------------------------
/**
 * @brief   グッズが目の前にあるかどうか検査
 * @param   type     グッズタイプ = gmm番号
 * @retval  none
 */
//--------------------------------------------------------------

BOOL UgSecretBaseGoodsCheck(int netID, Grid* pTouch)
{
    int x = pTouch->xpos;
    int z = pTouch->zpos;
    int roomID, type , msg;
    SECRETBASEDATA* pSecret;

    if(UgSecretBaseMoveing(x,z) == FALSE){
        u8 ret[2];
        ret[0] = netID;

        roomID = _getSecretIndex(x,z);
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[roomID].secretBaseDataBuff;

        type = _getAttrGoodsType(pSecret,x % _SECRETBASE_ATTR_MAX,z % _SECRETBASE_ATTR_MAX);
        ret[1] = GOODS_GetMessageNo(type);
        if(ret[1]!=0){
            CommPlayerSetMoveControl_Server(netID,FALSE);
            CommSendFixSizeData_ServerSide(CF_SECRETBASE_GOODS_CHECK,&ret);
            return TRUE;
        }
    }
    return FALSE;


}

//--------------------------------------------------------------
/**
 * @brief   グッズが目の前にあったので通信が送られてきた CF_SECRETBASE_GOODS_CHECK
 * @param   コールバック引数
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseRecvGoodsCheck(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->pNowMoveingBase->secretBaseDataBuff;
    SB_RECORD_DATA* pRec = SecretBaseGetSecretBaseRecord(pSecret);

    if(pBuff[0] == CommGetCurrentID()){
    //    int msg = GOODS_GetMessageNo(pBuff[1]);
        UgRecordGoodsMessage(pRec, pBuff[1]);
    }
}

//--------------------------------------------------------------
/**
 * @brief   サイズを返す
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

int UgSecretBaseGetRecvGoodsCheckSize(void)
{
    return 2;
}


//--------------------------------------------------------------
/**
 * @brief   旗をとったLOGをながす
 * @param   コールバック引数
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseSetFlagGetLog(int netID, int targetPCNetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagGetLog[netID] = targetPCNetID;
    }
}

//
//--------------------------------------------------------------
/**
 * @brief   うばったLOG
 * @param   コールバック引数
 * @retval  none
 */
//--------------------------------------------------------------
void UgSecretBaseSetFlagConquerLog(int myNetID, int targetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagConqureLog[myNetID] = targetID;
    }
}

//
//--------------------------------------------------------------
/**
 * @brief   とりもどしたLOG
 * @param   コールバック引数
 * @retval  none
 */
//--------------------------------------------------------------
void UgSecretBaseSetFlagReverseLog(int myNetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagReverseLog[myNetID] = TRUE;
    }
}


typedef struct{
    int seq;
    u8 msgIndex;      ///< メッセージインデックス メッセージ終了待ちに使用
    u8 type; //LVUPTYPE
} _DELIVERY_PLAYER;

//--------------------------------------------------------------
/**
 * @brief   パソコン変更
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _pcChange(_DELIVERY_PLAYER* pDeliv)
{
    VecFx32 vtx;
    M3DO_PTR pM3DO = M3DO_GetMap3DObjData(_pCommSecretBaseWork->pFSys->Map3DObjExp, 0);
    vtx = M3DO_GetGlobalVec(pM3DO);
    M3DO_CleanMap3DObj(0,_pCommSecretBaseWork->pFSys->Map3DObjExp);
    M3DO_SetMap3DObjExp(_pCommSecretBaseWork->pFSys->Map3DObjExp,
                        _pCommSecretBaseWork->pFSys->MapResource,
                        BMID_UG_TABLE_L02+pDeliv->type,
                        &vtx, NULL,
                        _pCommSecretBaseWork->pFSys->field_3d_anime);
}

#if GT384_060815_FIX
//--------------------------------------------------------------
/**
 * @brief   パソコン変える処理の強制終了
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _deliveryForceEnd(TCB_PTR tcb, void* work)
{
    sys_FreeMemoryEz(work);
    TCB_Delete(tcb);
}
#endif //GT384_060815_FIX

//--------------------------------------------------------------
/**
 * @brief   ランクが上がったのでパソコンを変える
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _deliveryPlayer(TCB_PTR tcb, void* work)
{
    _DELIVERY_PLAYER* pDeliv = work;

    enum{
        _DELIV_INIT,
        _DELIV_MSGWAIT1,
        _DELIV_MSGWAIT2,
        _DELIV_FADEOUT,
        _DELIV_END,
    };

    switch(pDeliv->seq){
      case _DELIV_INIT:
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                               mes_uw_flag_12, FALSE, NULL);
        Snd_SePlay(UG_SE_LEVELUP_FLAG);
        pDeliv->seq = _DELIV_MSGWAIT1;
        break;
      case _DELIV_MSGWAIT1:
//        if(Snd_MePlayCheckBgmPlay() == 0){
            if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
                if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                    int type = pDeliv->type;
                    CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                           mes_uw_flagLV_01+type, FALSE, NULL);
                    pDeliv->seq = _DELIV_MSGWAIT2;
                }
            }
//        }
        break;
      case _DELIV_MSGWAIT2:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                _pcChange(pDeliv);
                pDeliv->seq = _DELIV_END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderFlag());
                CommPlayerHoldEnd();
            }
        }
        break;
      case _DELIV_FADEOUT:
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_FADEOUT,
                       WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        break;
      case _DELIV_END:
        sys_FreeMemoryEz(work);
        TCB_Delete(tcb);
#if GT384_060815_FIX
        UgMgrEndNowTCB();
#endif //GT384_060815_FIX
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   パソコンLVUP  CF_LVUP_FLAG
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSBRecvLVUPFlag(int netID, int size, void* pData, void* pWork)
{
    u8 sBuff[2];
    u8* pRet = pData;

    sBuff[0] = netID;
    sBuff[1] = pRet[0];  //LV
    CommSendFixSizeData_ServerSide(CF_LVUP_FLAG_RET,sBuff);
}



//--------------------------------------------------------------
/**
 * @brief   パソコンLVUP  CF_LVUP_FLAG_RET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSBRecvLVUPFlagRet(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pBuff = pData;
#if GT384_060815_FIX
    TCB_PTR pTCB;
#endif //GT384_060815_FIX

    if(pBuff[0] == CommGetCurrentID()){
        _DELIVERY_PLAYER* pDeliv = sys_AllocMemory(HEAPID_WORLD, sizeof(_DELIVERY_PLAYER));
        MI_CpuClear8(pDeliv,sizeof(pDeliv));
        pDeliv->seq = 0;
        pDeliv->type = pBuff[1];
#if GT384_060815_FIX
        pTCB = TCB_Add(_deliveryPlayer, pDeliv, TCB_PRIORITY_NORMAL);
        UgMgrSetNowTCB(pDeliv, pTCB, _deliveryForceEnd);
#else  //GT384_060815_FIX
        TCB_Add(_deliveryPlayer, pDeliv, TCB_PRIORITY_NORMAL);
#endif //GT384_060815_FIX
    }
    else{
#if GT384_060815_FIX 
#else  //GT384_060815_FIX
        int x = CommPlayerGetPosX(CommGetCurrentID());
        int z = CommPlayerGetPosZ(CommGetCurrentID());
        if(_getSecretIndex(x,z) == pBuff[0]){ // 自分が変更のあった秘密基地にいる
            _DELIVERY_PLAYER* pDeliv = sys_AllocMemory(HEAPID_WORLD, sizeof(_DELIVERY_PLAYER));
            MI_CpuClear8(pDeliv,sizeof(pDeliv));
            pDeliv->seq = 0;
            pDeliv->type = pBuff[1];
            OHNO_SP_PRINT("一緒にいたのでパソコン更新 \n");
            _pcChange(pDeliv);
            sys_FreeMemoryEz(pDeliv);
        }
#endif  //GT384_060815_FIX
    }
}

//--------------------------------------------------------------
/**
 * @brief   パソコンLVUP  コマンドのサイズ
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

int UgSBGetLVUPFlagRetSize(void)
{
    return 2;
}

//==============================================================================
/**
 * この足元が何のグッズか返す
 * @param   ワークポインタ
 * @retval  none
 */
//==============================================================================

static int _getFootGoodsType(SECRETBASEDATA* pSecret,int xa,int za)
{
    int i,x,z;
    const u8* pBuff;

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        if(i == 0){
            continue;  // いらない
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            continue;  // いらない
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        x = xa - x;
        z = za - z;
        if((x == 0) && (z == 0)){
            return type;
        }
    }
    return GOODS_INVALID;
}

static int _trap2trap(int goodsTrap)
{
    switch(goodsTrap){
      case GOODS_UG_TRAP_03://	(62) // あなそうち
        return UG_TRAPTYPE_HOLE;
      case GOODS_UG_TRAP_04://	(63) // おおあなそうち
        return UG_TRAPTYPE_BIG_HOLE;
      case GOODS_UG_TRAP_10://	(66) // けむりそうち
        return UG_TRAPTYPE_SMOG;
      case GOODS_UG_TRAP_11://	(67) // えんまくそうち
        return UG_TRAPTYPE_BIG_SMOG;
      case GOODS_UG_TRAP_12://	(68) // いわそうち
        return UG_TRAPTYPE_ROCK;
      case GOODS_UG_TRAP_13://	(69) // らくせきそうち
        return UG_TRAPTYPE_ROCKFALL;
      case GOODS_UG_TRAP_14://	(70) // あわそうち
        return UG_TRAPTYPE_SUDS;
      case GOODS_UG_TRAP_15://	(71) // バブルそうち
        return UG_TRAPTYPE_BUBBLE;
      case GOODS_UG_TRAP_16://	(72) // あいずトラップ１
        return UG_TRAPTYPE_ALART1;
      case GOODS_UG_TRAP_17://	(73) // あいずトラップ２
        return UG_TRAPTYPE_ALART2;
      case GOODS_UG_TRAP_18://	(74) // あいずトラップ３
        return UG_TRAPTYPE_ALART3;
      case GOODS_UG_TRAP_19://	(75) // あいずトラップ４
        return UG_TRAPTYPE_ALART4;
      case GOODS_UG_TRAP_20://	(76) // このはそうち
        return UG_TRAPTYPE_LEAF;
      case GOODS_UG_TRAP_21://	(77) // はなびらそうち
        return UG_TRAPTYPE_DIRTY_BLOSSOMS;
      case GOODS_UG_TRAP_22://	(78) // ひのこそうち
        return UG_TRAPTYPE_FIRE;
      case GOODS_UG_TRAP_23://	(79) // ほのおそうち
        return UG_TRAPTYPE_BLAZE;
    }
    return UG_TRAPTYPE_NONE;
}


//--------------------------------------------------------------
/**
 * @brief   トラップグッズを踏んだかどうか
 * @param   netID  踏んだ人
 * @param   pTouch 位置
 * @retval  踏んでたらTRUE
 */
//--------------------------------------------------------------

BOOL UgSecretBaseTrapGoodsCheck(int netID)
{
    int trapType;
    int roomID;
    SECRETBASEDATA* pSecret;
    int x = CommPlayerGetPosSX(netID);
    int z = CommPlayerGetPosSZ(netID);
    int dir = CommPlayerGetSDir(netID);

    if(!UgSecretBaseIsSecretBasePlace(x,z)){
        return FALSE;
    }
    if((UgSecretBaseMoveing(x,z) == TRUE)
       && (!_pCommSecretBaseWork->bGoodsTrap[netID])){
        u8 ret[2];
        ret[0] = netID;

        roomID = _getSecretIndex(x,z);
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[roomID].secretBaseDataBuff;

        ret[1] = _getFootGoodsType(pSecret,x % _SECRETBASE_ATTR_MAX,z % _SECRETBASE_ATTR_MAX);
        trapType = _trap2trap( ret[1] );
        if(UG_TRAPTYPE_NONE != trapType){
            _pCommSecretBaseWork->bGoodsTrap[netID] = TRUE;
            UgTrapGoodsBind(netID, INVALID_NETID, trapType, x, z, dir);
            OHNO_SP_PRINT("装置にかかる%d x,z \n",netID,x,z);
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   トラップグッズを踏みおわった
 * @param   netID  踏んだ人
 * @retval  踏んでたらTRUE
 */
//--------------------------------------------------------------

BOOL UgSecretBaseTrapGoodsReset(int netID)
{
    BOOL bit = 0;

    if(_pCommSecretBaseWork){
        BOOL bit = _pCommSecretBaseWork->bGoodsTrap[netID];
        _pCommSecretBaseWork->bGoodsTrap[netID] = FALSE;
    }
    return bit;
}

//--------------------------------------------------------------
/**
 * @brief   秘密基地にいる人を追い出す（親機がいる場合）常に呼び出される
 * @param   netID    この人の秘密基地にいる場合追い出す
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseRemovePlayer(int netID)
{
    int i,no=0;
    int x,z;
    u8 buff[COMM_MACHINE_MAX];

    MI_CpuClear8(buff,COMM_MACHINE_MAX);
    

/*    for(i = 0 ; i < COMM_MACHINE_MAX ; i++){
        if((_pCommSecretBaseWork->travelBase[i] == netID)){
            if((_pCommSecretBaseWork->travelingBase[i] == _INVALID_BASE) &&
               (_pCommSecretBaseWork->travelingBaseSend[i] == _INVALID_BASE)){  // 秘密基地移動をしていない
                OHNO_PRINT("%d を %d からおいだす---1\n",i, _pCommSecretBaseWork->travelBase[i]);
                if(!buff[i]){
                    _returnUnderGroundStart(_pCommSecretBaseWork->travelBase[i],i, TRUE);
                    buff[i]=TRUE;
                }
            }
        }
    } */
    for(i = 0 ; i < COMM_MACHINE_MAX ; i++){
        if(CommIsConnect(i)){
            x = CommPlayerGetPosSX(i);
            z = CommPlayerGetPosSZ(i);
            if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
                continue;
            }
            no = _getSecretIndex(x,z);
            if((i == no) || (no == _SECRETBASE_MY_ID)){
                continue;
            }
            if(CommIsConnect(no)){
                continue;
            }
            if((_pCommSecretBaseWork->travelingBase[i] == _INVALID_BASE) &&
               (_pCommSecretBaseWork->travelingBaseSend[i] == _INVALID_BASE)){  // 秘密基地移動をしていない
                if(UgSecretBaseIsSecretBasePlace(x,z)){
                    OHNO_PRINT("%d を %d からおいだす\n",i, no);
                    if(!buff[i]){
                        _returnUnderGroundStart(no, i, TRUE);
                        buff[i]=TRUE;
                    }
                }
            }
        }
    }
    i = CommGetCurrentID();
    if(_pCommSecretBaseWork->moveTickets == _RETURN_TICKETS){
        x = CommPlayerGetPosSX(i);
        z = CommPlayerGetPosSZ(i);
        if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
        }
        else if(UgSecretBaseIsSecretBasePlace(x,z)){
            no = _getSecretIndex(x,z);
            OHNO_PRINT("%d を %d からescape\n",i, no);
            if(!buff[i]){
                _returnUnderGroundStart(no, i, TRUE);
                buff[i]=TRUE;
            }
        }
        if(buff[i]){  // 帰ることが決まっていた場合破棄
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;//
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   秘密基地にいる人を追い出す（親機がきえた場合）
 * @param   netID    この人の秘密基地
 * @retval  none
 */
//--------------------------------------------------------------

BOOL UgSecretBaseRemovePlayer_Client(int playerID, BOOL bRemove)
{
    _SendPos sendPos;
    _Pos outDoorPos;
    int x,z,dir,escapePlace;
    _Pos* pHead;


    if(_pCommSecretBaseWork->travelBase[playerID] == _INVALID_BASE){
        return FALSE;
    }
    escapePlace = _pCommSecretBaseWork->travelBase[playerID];
    x = CommPlayerGetPosX(CommGetCurrentID());
    z = CommPlayerGetPosZ(CommGetCurrentID());
    if(!UgSecretBaseIsSecretBasePlace(x,z)){
        _pCommSecretBaseWork->travelBase[playerID] = _INVALID_BASE; // ここで消す
        OHNO_PRINT("秘密基地外");
        return FALSE;
    }
    UnderRecordReset();
    TalkAskForceReset();
    UgMgrForceExitNowTCB();
    UgTrapForceExit(CommGetCurrentID(),FALSE);

//    pHead = &_pCommSecretBaseWork->secretHeaderData[escapePlace];
//    x = pHead->xpos;
//    z = pHead->zpos;
//    dir = pHead->dir;

    x = _pCommSecretBaseWork->resquePosX;
    z = _pCommSecretBaseWork->resquePosZ;
    dir = _pCommSecretBaseWork->resqueDir;

    OHNO_PRINT("切断なので  %d %d %d にもどります\n", playerID,escapePlace , x, z , dir);
    GF_ASSERT((x != 0) && (z != 0));
    x += FieldOBJ_DirAddValueGX( dir);
    z += FieldOBJ_DirAddValueGZ( dir);

    _pCommSecretBaseWork->bClientBaseIn = FALSE;
    _jumpMapForUG(_pCommSecretBaseWork->pFSys, x, z, dir, playerID, bRemove);
    CommStateJumpUnderGround();
    _pCommSecretBaseWork->pNowMoveingBase = NULL;
    _pCommSecretBaseWork->travelBase[playerID] = _INVALID_BASE;
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   秘密基地に入っているかどうかを返す
 * @param   netID    この人の秘密基地
 * @retval  
 */
//--------------------------------------------------------------

BOOL UgSecretBaseIsOtherEnter(void)
{
    int id = _pCommSecretBaseWork->travelBase[COMM_PARENT_ID];
    switch(id){
      case _INVALID_BASE:
      case _SECRETBASE_MY_ID:
      case COMM_PARENT_ID:
        return FALSE;
    }
    return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief   秘密基地データ受信中のエラー対処
 * @param   netID    この人の秘密基地
 * @retval  
 */
//--------------------------------------------------------------

void UgSecretBaseErrorMoveTickets(void)
{
    if(_pCommSecretBaseWork->moveTickets == _MOVE_TICKETS){
        _pCommSecretBaseWork->moveTickets = _ERROR_TICKETS;
        CommPlayerMyDataInitialize();
        UgSecretBaseResetPlayer(COMM_PARENT_ID);
        OHNO_PRINT("エラーチケットなのでリセット\n");
    }
}

//--------------------------------------------------------------
/**
 * @brief   秘密基地移動中のエラー
 * @param   netID    この人の秘密基地
 * @retval  
 */
//--------------------------------------------------------------

void UgSecretBaseErrorDisconnectTickets(void)
{
    if(_pCommSecretBaseWork->moveTickets == _TRANS_TICKETS){
        _pCommSecretBaseWork->moveTickets = _DISCONECT_TICKETS;
        OHNO_PRINT("エラーなのでリセット\n");
    }
}

//--------------------------------------------------------------
/**
 * @brief   子機になった人が秘密基地にいた場合、いったん外に出てもらう
 * @param   void
 * @retval  void
 */
//--------------------------------------------------------------

void UgSecretBaseFirstConnectChild(int netID)
{
    int x,z,no,id = netID;
    _UgJumpEventResult ugJump;

    x = CommPlayerGetPosSXOrg(id);
    z = CommPlayerGetPosSZOrg(id);

    if(!GetHitAttr(_pCommSecretBaseWork->pFSys, x, z)){   // 変な位置にいると強制退去
        if(netID == COMM_PARENT_ID){
            return;
        }
        if(CommMPIsConnectStalth()){
            return;
        }
    }
    OHNO_PRINT("子機　%d の位置  %d %d\n",id, x, z); //
    if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
#ifdef DEBUG_ONLY_FOR_ohno
//        GF_ASSERT(0);
#endif
        _returnUnderGroundStart(id, id, TRUE);
    }
    else if(UgSecretBaseIsSecretBasePlace(x, z) || GetHitAttr(_pCommSecretBaseWork->pFSys, x, z)){
        _returnUnderGroundStart(id, id, TRUE);
        OHNO_PRINT("%d を %d から いったんそとにだす\n",id, id);
    }
}



int UgSecretBaseEscapePosX(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resquePosX;
    }
    return _RESQUE_POSX;
}

int UgSecretBaseEscapePosZ(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resquePosZ;
    }
    return _RESQUE_POSZ;
}

int UgSecretBaseEscapeDir(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resqueDir;
    }
    return DIR_DOWN;
}

void UgSecretBaseEscapePosSXSet(int netID,int x)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resquePosSX[netID] = x;  // 入る時に出る時の位置を記憶
    }
}

void UgSecretBaseEscapePosSZSet(int netID,int z)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resquePosSZ[netID] = z;  // 入る時に出る時の位置を記憶
    }
}

void UgSecretBaseEscapeDirSet(int netID,int dir)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resqueSDir[netID] = dir;  // 入る時に出る時の位置を記憶
    }
}

void UgSecretBaseBootOn(BOOL bOn)
{
    OHNO_PRINT("ドアだす\n");
    _pCommSecretBaseWork->bDoorON = bOn;
}

//--------------------------------------------------------------
/**
 * @brief   接続禁止
 * @param   void
 * @retval  void
 */
//--------------------------------------------------------------

static void _connectDisable(void)
{
    WHChildConnectPause(TRUE);
    WHParentConnectPause(TRUE);
    CommStaetUnderPause(TRUE);
    CommMPFlashMyBss();
}


static void _connectEnable(void)
{
    WHChildConnectPause(FALSE);
    WHParentConnectPause(FALSE);
    CommStaetUnderPause(FALSE);
    CommMPFlashMyBss();
}

