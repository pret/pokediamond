//=============================================================================
/**
 * @file	comm_player.c
 * @bfief	通信で相手側のプレーヤーを表示する
 *            コミュニケーションプレーヤー
 * @author	katsumi ohno
 * @date	05/07/14
 */
//=============================================================================

#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_field_state.h"
#include "underground/ug_manager.h"

#include "system/bmp_menu.h"
#include "worldmap.h"
#include "fieldobj.h"
#include "fieldobj_code.h" //AC_WALK...等 アニメーションコードがまとめてあります。
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/window.h"

#include "player.h"
#include "comm_player_condition.h"
#include "comm_direct_counter.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "msgdata/msg_underworld.h"
#include "msgdata/msg_uwflag.h"

#include "field_effect.h"
#include "syswork.h"

#include "talk_msg.h"
#include "fldeff_flag.h"
#include "system/clact_tool.h"
#include "field_clact.h"
#include "fld_comact.h"
#include "underground/ug_local.h"
#include "eventdata.h"
#include "tv_topic.h"
#include "sysflag.h"

#include "d_ohno.h"  // デバッグ用

#include <nnsys/g3d/glbstate.h>


//==============================================================================
// 定義
//==============================================================================


/// 無効なフィールドマップアクター番号
#define _NULL_FIELD_MAP_ACT_ID (-1)
/// ネットプレーヤーはタスクは後方でいい
#define _TASK_PRI_NET_PLAYER  (100)
/// ネットプレーヤー生成はさらに後
#define _TASK_PRI_NET_PLAYER_CREATE  (_TASK_PRI_NET_PLAYER+100)
/// BLACT_HEADER workの　親子機IDを入れておく場所
/// ０と１は本物のヒーローアニメで使用しているので２番になっている
#define _WORK_MACHINE_ID (2)

#define _NAME_DISP (0)   ///< プレーヤーに名前を表示する

#define _NO_PLACE_INITIALIZE (0xff)  ///< 移動の初期化が終わっていない場合

#define _PLACEDATA_SEND_SIZE (5)  ///< 場所データを送信する場合のサイズ
#define _IDPLACEDATA_SEND_SIZE (4)  ///< IDつき場所データを送信する場合のサイズ

//#define _BLOW_STOP_COUNT (15)  // 最初に動かない数
#define _BLOW_COUNTER_NUM_MAX   (27)  // ふき飛ばされるフレーム数
#define _BIGBLOW_COUNTER_NUM_MAX   (45)  // ふき飛ばされるフレーム数
#define _BLOW_COUNTER_STOP   (0xff)  // 止めておく区間の値

#define _TALK_TARGET_INDEX_WORK (0)  ///< 会話データ　話相手のIDの位置
#define _TALK_MY_INDEX_WORK (1)  ///< 会話データ　話しているIDの位置

#define _FLAG_TVTOPIC_NUM (5)  ///TVに流れる場合の旗の数

// メニュー＆ウインドウをタスクに登録していく際のプライオリティー
enum menuTaskPri_e {
    _TALK_WINDOW_PRI = 10001,
};


enum _player_speed {
    _SPEED_2,
    _SPEED_4,
    _SPEED_8,
    _SPEED_16,
    _SPEED_HITWALL,
    _SPEED_MAX,
};


enum hedFieldEffect {
    _HFE_NONE,
    _HFE_FLAG,
    _HFE_EXCLAMATION,
    _HFE_OK,
};


#define _LOCAL_WIN_PX (2)   // GF_BGL_BmpAddで使用する 文字ウインドウのPX値
#define _LOCAL_WIN_PY (19)   // GF_BGL_BmpAddで使用する 文字ウインドウのPY値
#define _LOCAL_WIN_SX (28)   // GF_BGL_BmpAddで使用する 文字ウインドウのSX値
#define _LOCAL_WIN_SY (4)   // GF_BGL_BmpAddで使用する 文字ウインドウのSY値

#define _DASH_BIT (0x80)
#define _DEBUG_DASH_BIT (0x40)

#define _MSG_MAX  (50*GLOBAL_MSGLEN)    ///<

#define _KEEP_FLAG_MAX (5)  // 記憶しておくID

//==============================================================================
//	型宣言
//==============================================================================

typedef struct{
    int timer;
    int targetID;
} _FREEZE_PLAYER;



typedef struct{
    u8 mystatus[COMM_SEND_MYSTATUS_SIZE];
    u16 netID;
} _SEND_FLAG;


typedef struct{
    u16 xpos;
    u16 zpos;
    s8 dir;
    u8 speed;
    u8 speedKey;
    u8 bHit;
} _PlayerPlace;

typedef struct{
    u16 xpos;
    u16 zpos;
} _Grid;

typedef struct{
    u8 netID:4;      // 話している人
    u8 targetID:4;   // 話しかけられている人
    u8 bItemMenu:1;      //  アイテムメニューを開きにいっている
    u8 bPersonalInformation:1;      // 個人情報を開いている
} _talkMenuInfo;

typedef struct{
    u32 holdBit;
    PLAYER_CONDITION_MGR_PTR pCondMgr;
    PLAYER_STATE_PTR pPlayer[COMM_MACHINE_MAX];   // プレーヤーのポインタ
    EOA_PTR pMark[COMM_MACHINE_MAX];  //まんぷ
    u8 bActive[COMM_MACHINE_MAX];     // プレーヤーが存在するかどうか
    TCB_PTR pTask;          // 処理タスクのポインタ
    FIELDSYS_WORK* pFSys;
    _talkMenuInfo talkMenuInfo;   // 自分がどういう会話状態にあるかどうか記憶 サーバには無い
    u8 handCount[COMM_MACHINE_MAX];
    _PlayerPlace sPlayerPlaceServer[ COMM_MACHINE_MAX ];  // サーバーのプレーヤーの位置情報
    _PlayerPlace sPlayerPlace[ COMM_MACHINE_MAX ];  // プレーヤーの位置情報
    u8 bMoveControl[ COMM_MACHINE_MAX ]; ///< 機のコントロール状態
    u8 bMoveControlFlag[ COMM_MACHINE_MAX ]; ///< 機のコントロール状態 ハタ専用
    u8 bMoveControlVS[ COMM_MACHINE_MAX ];
    u8 hedFE[ COMM_MACHINE_MAX ]; ///< 頭の上のフィールドエフェクト管理
    s8 blowDir[COMM_MACHINE_MAX];
    u8 blowCounterS[COMM_MACHINE_MAX];   // 吹き飛ばしカウンタ
    u8 blowDirS[COMM_MACHINE_MAX];
    u8 giddyCounter[COMM_MACHINE_MAX];
    u8 countHole[COMM_MACHINE_MAX];
    u8 bBlowBigS[COMM_MACHINE_MAX];
    u8 bMoveChange[COMM_MACHINE_MAX]; // 移動したので送信するためのフラグ
    u8 walkCount[COMM_MACHINE_MAX];   // 歩き速度
    u8 walkCountClient[COMM_MACHINE_MAX];   // 歩き速度 クライアント
    _SEND_FLAG sendFlagData[COMM_MACHINE_MAX+1];
  //  u8 sendFlagDataID[COMM_MACHINE_MAX];
    MYSTATUS* pKeepFlag[_KEEP_FLAG_MAX];  // 5つ分ありこの時に重複しなければ記録
    MYSTATUS* pNowFlag[COMM_MACHINE_MAX];  //みんなから送信されたものはここに入る
//    MYSTATUS* pMyFlag;   //自分が持っているはた これを送信しあう
    u16 oldPad;
    u16 myDeliveryFlagNum;
    u8 bStartLineChk[4]; //
    u8 bTalkMenuDisp;   ///<< 会話ウインドウ表示中TRUE
//    u8 msgIndex;      ///< メッセージインデックス メッセージ終了待ちに使用
    u8 bFlagDataRecv;
    u8 moveSync;     ///< 移動位置同期
    u8 bPosAllSend;  ///< 全員の位置を再送信するフラグ
    u8 bMyMoveControl; ///< 自機のコントロール
    u8 bResetting;   ///< リセット中の場合勝手に動かないように
    u8 bUnder;    // 地下かどうか
    u8 bFirstMoveEnable;  // 親機がいなくなった場合、親機に接続した場合 開始を送信するためのFLG
    u8 forceDirFlg;  //強制角度調整
    u8 bMoveControlVSRoom; //対戦部屋での移動
    u8 bDataSendFlag; // 旗の動き制御
} CommPlayerWork;

// シングルトン
static CommPlayerWork* _pCommPlayerWork = NULL;

//==============================================================================
// static宣言
//==============================================================================

static void _setFlagDisp(int netID);
static int _getBlowMoveCount( int counter,int bBigBlow );
static BOOL _blowMove( int netID, int cnt );
static BOOL _blowAnim( int netID,int padTrg,int padCont,int speed );
static void _commPlayerDataSendTask(void *work);
static void _commPlayerDataSendTaskToChild(void *work);
static void _commPlayerAdd(u8 netID);
static void _commPlayerMove(TCB_PTR tcb, void *work);
static void _commPlayerTask(TCB_PTR tcb, void *work);
static void _commPlayerAutoStep(void *work);
static void _talkMenuEnd(int selectNo);
static void _talkWindowFunc(TCB_PTR tcb, void* work);
static void _playerMoveClient(int netID);
static void CommPlayerCheckBattleJump_Server(void);

#ifdef PM_DEBUG
static void _debugGyoeDisp(void);
#endif

//==============================================================================
// 関数
//==============================================================================

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーの初期化
 *   ネットプレーヤーの子機IDとグラフィックを結びつけて管理している
 * @param   work_area  ワークエリア
 * @retval  BOOL TRUE 成功   FALSE 失敗 ワークエリアを消してください
 */
//==============================================================================

BOOL CommPlayerManagerInitialize(void* work_area, FIELDSYS_WORK* pFSys, BOOL bUnder)
{
    int i,j;

    if(_pCommPlayerWork){  // 今のところ何度も初期化されるので
        return FALSE;
    }
    if(_pCommPlayerWork == NULL){
        _pCommPlayerWork = work_area;
        MI_CpuFill8(_pCommPlayerWork,0,sizeof(CommPlayerWork));
    }
    _pCommPlayerWork->bUnder = bUnder;
    _pCommPlayerWork->pCondMgr = NULL;
    if(bUnder){
        _pCommPlayerWork->pCondMgr = sys_AllocMemory(HEAPID_COMMUNICATION,
                                                     CommPlayCondGetWorkSize());
        CommPlayerCondInitialize(_pCommPlayerWork->pCondMgr);
    }
    _pCommPlayerWork->pFSys = pFSys;
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCommPlayerWork->sPlayerPlace[i].dir = DIR_NOT;
        _pCommPlayerWork->sPlayerPlace[i].xpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlace[i].zpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlace[i].speed = _SPEED_8;
        _pCommPlayerWork->sPlayerPlaceServer[i].dir = DIR_NOT;
        _pCommPlayerWork->sPlayerPlaceServer[i].xpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlaceServer[i].zpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlaceServer[i].speed = _SPEED_8;
        _pCommPlayerWork->blowDir[i] = DIR_NOT;
        _pCommPlayerWork->bMoveControl[i] = FALSE;
        _pCommPlayerWork->bMoveControlFlag[i] = TRUE;
        _pCommPlayerWork->bMoveControlVS[ i ] = FALSE;

        _pCommPlayerWork->sendFlagData[i].netID = INVALID_NETID;
 //       _pCommPlayerWork->sendFlagDataID[i] = i;
    }
    _pCommPlayerWork->bMyMoveControl = FALSE;//TRUE;
    _pCommPlayerWork->bFirstMoveEnable = FALSE;

    _pCommPlayerWork->pTask = TCB_Add(_commPlayerTask, NULL, _TASK_PRI_NET_PLAYER_CREATE);
    CommEnableSendMoveData();

    CommPlayerMyDataInitialize();



    return TRUE;
}

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーの中断処理
 *   表示していたネットプレーヤーを消す
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerReset(void)
{
    int i;
    if(_pCommPlayerWork==NULL){
        return;
    }
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->bUnder){
            CommPlayerDestroy( i, TRUE ,FALSE);
            OHNO_PRINT("CommPlayerDestroy--2 %d\n", i);
        }
        else{
            CommPlayerDestroy( i, TRUE ,TRUE);
        }
    }
    if(_pCommPlayerWork->bUnder){
        _pCommPlayerWork->bResetting = TRUE;
    }
    OHNO_PRINT("CommPlayerManagerReset\n");
}

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーの復帰処理
 *   消していたネットプレーヤーを再表示
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerReboot(void)
{
    int x,z;
    
    if(_pCommPlayerWork==NULL){
        return;
    }
    _pCommPlayerWork->bPosAllSend = TRUE;
    _pCommPlayerWork->bResetting = FALSE;
    CommPlayerMyDataInitialize();
    CommPlayerSendPos(TRUE);

    OHNO_PRINT("自分の位置C  %d %d \n",CommPlayerGetPosX(CommGetCurrentID()),CommPlayerGetPosZ(CommGetCurrentID()));
    x = Player_NowGPosXGet( _pCommPlayerWork->pFSys->player );
    z = Player_NowGPosZGet( _pCommPlayerWork->pFSys->player );
    OHNO_PRINT("自分の位置F  %d %d \n",x,z);
}

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーの終了処理
 *   表示していたネットプレーヤーを消す
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerFinalize(BOOL bDel)
{
    int i,j;
    if(_pCommPlayerWork){

        for(j = 0; j < _KEEP_FLAG_MAX; j++){
            if(_pCommPlayerWork->pKeepFlag[j]){
                sys_FreeMemoryEz(_pCommPlayerWork->pKeepFlag[j]);
                _pCommPlayerWork->pKeepFlag[j] = NULL;
            }
        }

        if(_pCommPlayerWork->myDeliveryFlagNum >= _FLAG_TVTOPIC_NUM){
            TVTOPIC_Entry_Record_GetFlag(_pCommPlayerWork->pFSys,_pCommPlayerWork->myDeliveryFlagNum);
        }
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            CommPlayerDestroy( i, FALSE ,bDel);
            OHNO_PRINT("CommPlayerDestroy--3 %d\n", i);
        }
        TCB_Delete(_pCommPlayerWork->pTask);
        if(_pCommPlayerWork->pCondMgr){
            CommPlayerCondFinalize(_pCommPlayerWork->pCondMgr);
            sys_FreeMemoryEz(_pCommPlayerWork->pCondMgr);
        }
        sys_FreeMemoryEz(_pCommPlayerWork);
        _pCommPlayerWork = NULL;
    }
}

//==============================================================================
/**
 * びっくりマークを消す関数
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _markDelete(int netID)
{
    if(_pCommPlayerWork->pMark[netID] != NULL){
        if(EOA_StatusBit_UseCheck( _pCommPlayerWork->pMark[netID] )){
            EOA_Delete(_pCommPlayerWork->pMark[netID]);
        }
        else{
            GF_ASSERT(0);
        }
        _pCommPlayerWork->pMark[netID] = NULL;
    }
}

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーの最初期化  COMM_PARENT_IDに戻す
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerReInit(void)
{
    int i,j;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        CommPlayerResetCondition(i);

        _markDelete(i);
        if(i != COMM_PARENT_ID){
            CommPlayerDeleteFlagData(i);
        }

        if(_pCommPlayerWork->pPlayer[i] != NULL){
            if(_pCommPlayerWork->pFSys->player != _pCommPlayerWork->pPlayer[i]){
                if(_pCommPlayerWork->bUnder){
                    Player_DeleteAll(_pCommPlayerWork->pPlayer[i]);
                }
            }
            _pCommPlayerWork->pPlayer[i] = NULL;
        }

        _pCommPlayerWork->bActive[i] = FALSE;
        _pCommPlayerWork->sPlayerPlace[i].dir = DIR_NOT;
        _pCommPlayerWork->sPlayerPlace[i].xpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlace[i].zpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlace[i].speed = _SPEED_8;
        _pCommPlayerWork->sPlayerPlaceServer[i].dir = DIR_NOT;
        _pCommPlayerWork->sPlayerPlaceServer[i].xpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlaceServer[i].zpos = COMM_PLAYER_INVALID_GRID;
        _pCommPlayerWork->sPlayerPlaceServer[i].speed = _SPEED_8;
        _pCommPlayerWork->blowDir[i] = DIR_NOT;
        _pCommPlayerWork->blowCounterS[i] = 0;
        _pCommPlayerWork->bMoveControl[i] = FALSE;
        _pCommPlayerWork->bMoveControlFlag[i] = TRUE;
        _pCommPlayerWork->bMoveControlVS[ i ] = FALSE;
        _pCommPlayerWork->walkCount[i] = 0;
        _pCommPlayerWork->walkCountClient[i] = 0;
    }
    _pCommPlayerWork->bFirstMoveEnable = FALSE;
    CommPlayerMyDataInitialize();
    if(_pCommPlayerWork->pTask == NULL){
        _pCommPlayerWork->pTask = TCB_Add(_commPlayerTask, NULL, _TASK_PRI_NET_PLAYER_CREATE);
    }
}

//==============================================================================
/**
 * タスクを緊急停止
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerStop(void)
{
    if(_pCommPlayerWork->pTask){
        _commPlayerTask(NULL,NULL);
        TCB_Delete(_pCommPlayerWork->pTask);
    }
    _pCommPlayerWork->pTask = NULL;
}

//==============================================================================
/**
 * 秘密基地に穴を閉じていく場合の消去
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommPlayerManagerDeletePlayers(void)
{
    int i;
    if(_pCommPlayerWork==NULL){
        return;
    }
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        CommPlayerDestroy( i, FALSE ,FALSE);
        OHNO_SP_PRINT("あなけします %d \n",i);
        CommPlayerResetHole( i );
    }
    _pCommPlayerWork->bResetting = TRUE;
}

//==============================================================================
/**
 * このクラスが初期化されたかどうかを返す
 * @retval  初期化されていればTRUE
 */
//==============================================================================

BOOL CommPlayerManagerIsInitialize(void)
{
    return (_pCommPlayerWork!=NULL);
}

//==============================================================================
/**
 * 自分のデータを初期化
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommPlayerMyDataInitialize(void)
{
    _pCommPlayerWork->pPlayer[CommGetCurrentID()] = _pCommPlayerWork->pFSys->player;
    _pCommPlayerWork->bActive[CommGetCurrentID()] = TRUE;
    _pCommPlayerWork->sPlayerPlace[CommGetCurrentID()].xpos = Player_NowGPosXGet( _pCommPlayerWork->pFSys->player );
    _pCommPlayerWork->sPlayerPlace[CommGetCurrentID()].zpos = Player_NowGPosZGet( _pCommPlayerWork->pFSys->player );
    _pCommPlayerWork->sPlayerPlace[CommGetCurrentID()].dir = Player_DirGet( _pCommPlayerWork->pFSys->player );
    _pCommPlayerWork->sPlayerPlaceServer[CommGetCurrentID()].xpos = Player_NowGPosXGet( _pCommPlayerWork->pFSys->player );
    _pCommPlayerWork->sPlayerPlaceServer[CommGetCurrentID()].zpos = Player_NowGPosZGet( _pCommPlayerWork->pFSys->player );
    _pCommPlayerWork->sPlayerPlaceServer[CommGetCurrentID()].dir = Player_DirGet( _pCommPlayerWork->pFSys->player );

    OHNO_PRINT("----------CommGetCurrentID() == %d  %d %d %d \n",
               CommGetCurrentID(),Player_DirGet( _pCommPlayerWork->pFSys->player ),
               _pCommPlayerWork->sPlayerPlace[CommGetCurrentID()].xpos,
               _pCommPlayerWork->sPlayerPlace[CommGetCurrentID()].zpos);

    
}

//==============================================================================
/**
 * 自分のデータをコピー
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommPlayerMyDataCopy(int netID)
{
    int id;

    _pCommPlayerWork->bFirstMoveEnable = FALSE;
    id = CommGetCurrentID();

    _pCommPlayerWork->pPlayer[id] = _pCommPlayerWork->pFSys->player;
    _pCommPlayerWork->bActive[id] = TRUE;
    _pCommPlayerWork->sPlayerPlace[id].xpos = _pCommPlayerWork->sPlayerPlace[netID].xpos;
    _pCommPlayerWork->sPlayerPlace[id].zpos = _pCommPlayerWork->sPlayerPlace[netID].zpos;
    _pCommPlayerWork->sPlayerPlace[id].dir = _pCommPlayerWork->sPlayerPlace[netID].dir;
    _pCommPlayerWork->sPlayerPlaceServer[id].xpos = _pCommPlayerWork->sPlayerPlaceServer[netID].xpos;
    _pCommPlayerWork->sPlayerPlaceServer[id].zpos = _pCommPlayerWork->sPlayerPlaceServer[netID].zpos;
    _pCommPlayerWork->sPlayerPlaceServer[id].dir = _pCommPlayerWork->sPlayerPlaceServer[netID].dir;

    _pCommPlayerWork->pNowFlag[id] = _pCommPlayerWork->pNowFlag[netID];
    _pCommPlayerWork->pNowFlag[netID] = NULL;

    if(_pCommPlayerWork->pNowFlag[id]){
        MyStatus_Copy(_pCommPlayerWork->pNowFlag[id],
                      (MYSTATUS*)&_pCommPlayerWork->sendFlagData[id].mystatus);
    }
    _pCommPlayerWork->sendFlagData[netID].netID = INVALID_NETID;
    
    OHNO_PRINT("----------copy() == %d  %d %d \n",
               CommGetCurrentID(),
               _pCommPlayerWork->sPlayerPlace[id].xpos,
               _pCommPlayerWork->sPlayerPlace[id].zpos);

    
}

//==============================================================================
/**
 * 現在の位置を送信  子機が親機に自分の位置を伝える
 * @param   none
 * @retval  none
 */
//==============================================================================

#define _BIT_LIVE (0x80)

void CommPlayerSendPosXZ(BOOL bLiveMessage,int xpos,int zpos)
{
    u8 data[_PLACEDATA_SEND_SIZE+1];
    int dir = Player_DirGet( _pCommPlayerWork->pFSys->player );

    data[0] = xpos;
    data[1] = xpos >> 8;
    data[2] = zpos;
    data[3] = zpos >> 8;
    data[4] = dir;

    if(bLiveMessage){
        data[4] = data[4] | _BIT_LIVE;
    }
    
    CommSendFixSizeData(CF_PLAYER_POS, data);
    _pCommPlayerWork->bPosAllSend = TRUE;
 //   _pCommPlayerWork->bMyMoveControl = FALSE;
  //  CommPlayerSetMoveControl(TRUE);
//    _pCommPlayerWork->bMyMoveControl = TRUE;
//    CommSendFixSizeData(CF_MOVE_CONTROL,&_pCommPlayerWork->bMyMoveControl);   // 送信する
   OHNO_SP_PRINT("子機側移動データ送信 %d %d %d\n",CommGetCurrentID(), xpos, zpos);
}

//==============================================================================
/**
 * 現在の位置を送信  子機が親機に自分の位置を伝える
 * @param   none
 * @retval  none
 */
//==============================================================================

#define _BIT_LIVE (0x80)

void CommPlayerSendPos(BOOL bLiveMessage)
{
    int xpos = Player_NowGPosXGet( _pCommPlayerWork->pFSys->player );
    int zpos = Player_NowGPosZGet( _pCommPlayerWork->pFSys->player );
    OHNO_PRINT("いち送信 %d %d %d\n",xpos,zpos,bLiveMessage);
    CommPlayerSendPosXZ(bLiveMessage, xpos, zpos);
}

//==============================================================================
/**
 * 現在の位置を送信  子機が親機に自分の位置を伝える
 * @param   none
 * @retval  none
 */
//==============================================================================

//#define _BIT_LIVE (0x80)

void CommPlayerSendPosServer(BOOL bLiveMessage)
{
//    int xpos = Player_NowGPosXGet( _pCommPlayerWork->pFSys->player );
//    int zpos = Player_NowGPosZGet( _pCommPlayerWork->pFSys->player );
    int xpos = _pCommPlayerWork->sPlayerPlaceServer[CommGetCurrentID()].xpos;
    int zpos = _pCommPlayerWork->sPlayerPlaceServer[CommGetCurrentID()].zpos;
    OHNO_PRINT("いち送信S %d %d %d\n",xpos,zpos,bLiveMessage);
    CommPlayerSendPosXZ(bLiveMessage, xpos, zpos);
}

//==============================================================================
/**
 * 現在の位置　指令を送信
 * @param   netID  キャラのID
 * @param   xpos  グローバルX座標
 * @param   zpos  グローバルY座標
 * @param   dir   向き
 * @param   dash  ダッシュ中1
 * @retval  none
 */
//==============================================================================
static void _sendIDPlayerPos(int netID,const _PlayerPlace* pPP)
{
    u8 data[_IDPLACEDATA_SEND_SIZE+1];
    int x = pPP->xpos,z = pPP->zpos;

    if(pPP->xpos < 0){   // 範囲外のデータは補正する
        x = 0;
    }
    else if(pPP->xpos >= 0xf000){
        x = 0xf000-1;
    }
    if(pPP->zpos < 0){
        z = 0;
    }
    else if(pPP->zpos >= 0xf000){
        z = 0xf000-1;
    }

    data[0] = netID & 0xf;

    data[1] = x;
    data[2] = ((x >> 8)&0x1) + ((z >> 7)&0x02);
    data[3] = z;

    if(pPP->bHit){
        data[2] |= 0x80;
    }
    
    data[0] += ((pPP->dir % DIR_4_MAX) << 4);
    data[0] += (pPP->speed << 6);

//    OHNO_PRINT("サーバー側プレーヤーデータ送信 %d  %d %d\n",netID, x, z);
    CommSendData_ServerSide(CF_PLAYER_POS_ID, data, 0);
}

//==============================================================================
/**
 * 自分のプレーヤーの位置情報を定期的に送信するためのタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		none
 * @retval  none
 */
//==============================================================================
void _commPlayerDataSendTask(void *work)
{
    // addの時しか使用されていないので、位置補正はかかっていない 05.09.01
    // 位置情報を送信
    int mv = Player_MoveValueGet( _pCommPlayerWork->pFSys->player );
    int ms = Player_MoveStateGet( _pCommPlayerWork->pFSys->player );
    
    
    if( (OBJ_MOVE_VALUE_STOP == mv) && CommIsConnect(CommGetCurrentID())){
        if(!_pCommPlayerWork->moveSync){
            CommPlayerSendPos(TRUE);
            _pCommPlayerWork->moveSync = TRUE;
        }
    }
    if((OBJ_MOVE_VALUE_WALK == mv )&&(OBJ_MOVE_STATE_START == ms)){
        // DS処理の場合ここをはずす
        _pCommPlayerWork->moveSync = FALSE;
    }
}

//==============================================================================
/**
 * 自分のプレーヤーの位置情報を子機に常に送信するためのタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		none
 * @retval  none
 */
//==============================================================================
static void _commPlayerDataSendTaskToChild(void *work)
{
    int i;  // 位置情報を送信

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->bActive[i]){
            _PlayerPlace* pPP = &_pCommPlayerWork->sPlayerPlaceServer[i];

            if(_pCommPlayerWork->bMoveChange[i] || _pCommPlayerWork->bPosAllSend){
                _pCommPlayerWork->bMoveChange[i]= FALSE;
                _sendIDPlayerPos( i, pPP);
            }
        }
    }
    _pCommPlayerWork->bPosAllSend = FALSE; // フラグを落としておく
}

//==============================================================================
/**
 * 会話リストが終わった時に呼び出してもらう
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _talkMenuEnd(int selectNo)
{
    if(_pCommPlayerWork){
        _pCommPlayerWork->bTalkMenuDisp=FALSE;
    }
}

//==============================================================================
/**
 * ネットプレーヤー管理マネージャーのワークサイズ取得
 * @param   none
 * @retval  u32   ワークサイズ
 */
//==============================================================================

u32 CommPlayerGetWorkSize(void)
{
    return sizeof(CommPlayerWork);
}

//==============================================================================
/**
 * ネットプレーヤーを追加
 * @param   netID  子機親機のID
 * @retval  none
 */
//==============================================================================

static void _commPlayerAdd(u8 netID)
{
    fx32 xpos, zpos;
    PLAYER_STATE_PTR pPlayer;

    if(_pCommPlayerWork->pPlayer[netID]!=NULL){
        return;  //すでにいる場合
    }
    if(_pCommPlayerWork->bResetting){
        OHNO_PRINT("reset中 %d  \n", netID);
        return;  // 
    }
    {
        MYSTATUS* pMy = CommInfoGetMyStatus(netID);
        if(pMy==NULL){
            OHNO_PRINT("mystatusがなかった %d\n",netID);
        }
        if(pMy){
            if(!_pCommPlayerWork->bUnder){
                if(netID != CommGetCurrentID()){
                    // もし前のものがいたら
                    FIELD_OBJ_PTR pObj = FieldOBJSys_OBJIDSearch(_pCommPlayerWork->pFSys->fldobjsys,FLDOBJ_ID_PLAYER+netID+1);
                    if(pObj){
                        FieldOBJ_Delete(pObj);
                    }
                }
            }
            pPlayer = Player_Init( _pCommPlayerWork->pFSys->fldobjsys,
                                   _pCommPlayerWork->sPlayerPlace[netID].xpos,
                                   _pCommPlayerWork->sPlayerPlace[netID].zpos,
                                   _pCommPlayerWork->sPlayerPlace[netID].dir,
                                   HERO_FORM_NORMAL, MyStatus_GetMySex(pMy), NULL );
            OHNO_SP_PRINT("性別  id %d=%d ",netID,MyStatus_GetMySex(pMy));
            OHNO_SP_PRINT("x %d y %d\n",
                          _pCommPlayerWork->sPlayerPlace[netID].xpos,
                          _pCommPlayerWork->sPlayerPlace[netID].zpos);
            GF_ASSERT_RETURN(pPlayer && "NetPlayer生成できなかった",);
            _pCommPlayerWork->pPlayer[netID] = pPlayer;
     //      _pCommPlayerWork->hedFE[netID] = _HFE_NONE;

                                                   //判別ID
            FieldOBJ_OBJIDSet(Player_FieldOBJGet(pPlayer),FLDOBJ_ID_PLAYER+netID+1);
            if(_pCommPlayerWork->bUnder){
                UgMgrSetReturnLog(netID);  //LOG
            }
            if(_pCommPlayerWork->bUnder && !_pCommPlayerWork->bActive[netID]){
                if(!_pCommPlayerWork->bResetting){
                    FE_FldOBJTrapsmogSet(_pCommPlayerWork->pFSys,
                                         _pCommPlayerWork->sPlayerPlace[netID].xpos,
                                         0,
                                         _pCommPlayerWork->sPlayerPlace[netID].zpos);
                }
                _pCommPlayerWork->bActive[netID] = TRUE;
            }
            else if(!_pCommPlayerWork->bUnder){
                _pCommPlayerWork->bActive[netID] = TRUE;
            }
        }
    }
	
    // 位置情報を送り返す
//    _pCommPlayerWork->moveSync = FALSE;
 /*   OHNO_PRINT("ネットキャラを登録 %d (%d,%d)\n", netID,
               _pCommPlayerWork->sPlayerPlace[netID].xpos,
               _pCommPlayerWork->sPlayerPlace[netID].zpos);
*/
}

//==============================================================================
/**
 * ネットプレーヤーを削除
 * @param   netID  子機親機のID
 * @retval  none
 */
//==============================================================================

void CommPlayerDestroy(u8 netID, BOOL bExit,BOOL bDel)
{
    int i;

    if(_pCommPlayerWork == NULL){
        return;
    }
    MI_CpuClear8(_pCommPlayerWork->handCount,COMM_MACHINE_MAX);
    _markDelete(netID);

    if(_pCommPlayerWork->pPlayer[netID] != NULL){
        if(_pCommPlayerWork->pFSys->player != _pCommPlayerWork->pPlayer[netID]){
            if(_pCommPlayerWork->bUnder || bDel){
                Player_DeleteAll(_pCommPlayerWork->pPlayer[netID]);
            }
            else{
                Player_Delete(_pCommPlayerWork->pPlayer[netID]);
            }
        }
        _pCommPlayerWork->pPlayer[netID] = NULL;
    }
    if((_pCommPlayerWork->bActive[netID]) && (!bExit)){
        _pCommPlayerWork->bActive[netID] = FALSE;
    }
    _pCommPlayerWork->bMoveChange[netID]=TRUE;

    if(!bExit){
        CommPlayerDeleteFlagData(netID);
        _pCommPlayerWork->hedFE[netID] = _HFE_NONE;
        if(_pCommPlayerWork->bUnder){
            if(netID != COMM_PARENT_ID){
//                UgSecretBaseDestroyDoor(netID);
//                UgSecretBaseTrapGoodsReset(netID);
            }
        }
    }
}


static void _speedSend()
{
    u8 speed = _SPEED_8;

    if(PAD_BUTTON_B & sys.cont){
        speed = _SPEED_4;
    }
#ifdef DEBUG_ONLY_FOR_ohno  // デバッグダッシュはいろいろ災いしそうなのでコメントにしました
    else if(PAD_BUTTON_R & sys.cont){
        speed = _SPEED_2;
    }
#endif
    CommSetSpeed(speed);
}


//==============================================================================
/**
 * CommPlayerの通常処理
 * @param   netID  子機親機のID
 * @retval  none
 */
//==============================================================================

static void _commPlayerTask(TCB_PTR tcb, void *work)
{
    int i;

    if(CommIsInitialize()){
        _speedSend();
        if(CommGetCurrentID() == COMM_PARENT_ID){
            _commPlayerDataSendTaskToChild(work); // 子機に位置送信
            _commPlayerDataSendTask(work); // 話しかけ管理
            if(_pCommPlayerWork->pCondMgr){
                CommPlayerCondStep(_pCommPlayerWork->pCondMgr);  // 親機でコンディション処理
            }
        }
        else{
            _commPlayerDataSendTask(work); // 話しかけ管理
        }
        _commPlayerAutoStep(work);  // プレイヤーのadd delete管理
    }

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->bUnder){
            if(CommGetCurrentID() == COMM_PARENT_ID){
                if(NULL==CommInfoGetMyStatus(i) ){
                    UgSecretBaseResetPlayer(i);
                }
            }
        }
    }
}


//==============================================================================
/**
 * 通信状態を見て、ネットプレーヤーを配置したりはずしたりする
 * @param   tcb			TCBへのポインタ
 * @param   work		none
 * @retval  none
 */
//==============================================================================

static void _commPlayerAutoStep(void *work)
{
    int i, dir;
    

    for(i = 0; i < COMM_MACHINE_MAX; i++){
#ifdef PM_DEBUG
        if(sys.trg & PAD_BUTTON_L){
            if(CommPlayerIsTrapBind(i)){
                OHNO_PRINT("コンディション異常 %d\n",i);
            }
        }
#endif
        if(!CommIsConnect(i)){
            if(!(CommGetAloneMode() && (i == COMM_PARENT_ID))){
                if((CommGetCurrentID() == COMM_PARENT_ID) && (_pCommPlayerWork->bUnder)){
                    // 常に監視 消す人の秘密基地にいる人を追い出す
                    UgSecretBaseRemovePlayer( i );
                }
            }
        }
        if(CommIsConnect(i)  || (CommGetAloneMode() && (i == COMM_PARENT_ID)) ){  // オンラインなら
            _playerMoveClient(i);
            _setFlagDisp(i);
        }
        else{  // オフラインなら
            if(_pCommPlayerWork->bActive[i]){
                if((CommGetCurrentID() == COMM_PARENT_ID) && (_pCommPlayerWork->bUnder)){
                    // 消す人の罠情報をなくす
                    CommTrapDeletePlayer_Server(i);
                    UgDigFossilResetPlayer(i);
                }
                {
                    u8 creatureID = i;  // 勝手に消す
                    CommPlayerRecvDelete(0, 1, &creatureID, _pCommPlayerWork->pFSys);
                }
            }
        }
    }
}

//==============================================================================
/**
 * 自機の移動可能状態かどうかを調べる
 * @param   none
 * @retval  自機が移動可能状態の場合TRUE
 */
//==============================================================================

BOOL CommPlayerIsMyMoveControl(void)
{
    if(_pCommPlayerWork != NULL){
        return _pCommPlayerWork->bMyMoveControl;
    }
    return FALSE;
}

//==============================================================================
/**
 * 自機の移動可能状態かどうかを設定する
 *    状態を記憶しておいて トリガーを親機に送信する
 * @param   bMoveControl  自機が移動可能状態かどうか
 * @retval  none
 */
//==============================================================================

void CommPlayerSetMoveControl(BOOL bMoveControl)
{
    if(_pCommPlayerWork != NULL){
        if(_pCommPlayerWork->bMyMoveControl != bMoveControl){
            _pCommPlayerWork->bMyMoveControl = bMoveControl;
        //    CommSendFixSizeData(CF_MOVE_CONTROL,&_pCommPlayerWork->bMyMoveControl);   // 送信する
        }
        OHNO_PRINT("CF_MOVE_CONTROL \n");
        CommSendFixSizeData(CF_MOVE_CONTROL,&_pCommPlayerWork->bMyMoveControl);   // 送信する
    }
}

//==============================================================================
/**
 * 自機の移動可能状態かどうかを設定する
 *    状態を記憶しておいて トリガーを親機に送信する
 * @param   bMoveControl  自機が移動可能状態かどうか
 * @retval  none
 */
//==============================================================================

static void _setMoveControlVSRoom(BOOL bMoveControl)
{
    if(_pCommPlayerWork != NULL){
        if(_pCommPlayerWork->bMyMoveControl != bMoveControl){
            _pCommPlayerWork->bMyMoveControl = bMoveControl;
            CommSendFixSizeData(CF_MOVE_CONTROL,&_pCommPlayerWork->bMyMoveControl);   // 送信する
        }
    }
}

//==============================================================================
/**
 * 移動可能状態かどうかを受信する   CF_MOVE_CONTROL
 * @param   netID    送信してきたID
 * @param   size     送られてきたデータサイズ
 * @param   pData    情報のポインタ
 * @retval  none
 */
//==============================================================================

void CommPlayerRecvMoveControl(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = (u8*)pData;

    if(_pCommPlayerWork){
        GF_ASSERT_RETURN(size == 1,);
        GF_ASSERT_RETURN(netID < COMM_MACHINE_MAX,);
        GF_ASSERT_RETURN((pBuff[0] == TRUE)||(pBuff[0] == FALSE),);
        CommPlayerSetMoveControl_Server(netID,pBuff[0]);
        OHNO_PRINT("recvMoveControl %d \n",netID);
    }
}

//==============================================================================
/**
 * 全員移動する
 * @param   repw		  FIELDSYS_WORKのポインタ
 * @retval  none
 */
//==============================================================================

void CommPlayersMove(FIELDSYS_WORK * repw, BOOL bMoveControl)
{

    if(_pCommPlayerWork==NULL){
        return;
    }
    if(!_pCommPlayerWork->bUnder){
        _setMoveControlVSRoom(bMoveControl);  // 自機の移動状態を設定
        _pCommPlayerWork->bMoveControlVSRoom = bMoveControl;
    }
    if(repw->player){
        _pCommPlayerWork->pPlayer[CommGetCurrentID()] = repw->player;
    }
    if(CommIsInitialize() && (CommGetCurrentID() == COMM_PARENT_ID)){
        // 親機=SERVERだけ移動処理を行い、子機はその結果で動く
        _commPlayerMove(NULL, _pCommPlayerWork);
    }
    if(CommIsInitialize() && (CommGetCurrentID() == COMM_PARENT_ID)){
        if(!_pCommPlayerWork->bUnder){
            CommPlayerCheckBattleJump_Server();
        }
    }
    
#ifdef PM_DEBUG
   // _debugGyoeDisp();
#endif
}

//--------------------------------------------------------------
/**
 * キートリガ、プレスから押されている方向を取得
 * @param	key_trg 	キートリガ
 * @param	key_prs		キープレス
 * @retval	int			押されている方向。DIR_UP等
 */
//--------------------------------------------------------------
static int _keyDirGet( u16 key_trg, u16 key_cont )
{
	if( (key_cont & PAD_KEY_LEFT) ){
		return( DIR_LEFT );
	}
	
	if( (key_cont & PAD_KEY_RIGHT) ){
		return( DIR_RIGHT );
	}
	
	if( (key_cont & PAD_KEY_UP) ){
		return( DIR_UP );
	}
	
	if( (key_cont & PAD_KEY_DOWN) ){
		return( DIR_DOWN );
	}
	
	return( DIR_NOT );
}

//--------------------------------------------------------------
/**
 * 方向からキーを返す
 * @param	dir 	方向
 * @retval	int		押されているキー
 */
//--------------------------------------------------------------
static int _dirKeyGet( u16 dir )
{
    switch(dir){
      case DIR_LEFT:
        return PAD_KEY_LEFT;
      case DIR_RIGHT:
        return PAD_KEY_RIGHT;
      case DIR_UP:
        return PAD_KEY_UP;
      case DIR_DOWN:
        return PAD_KEY_DOWN;
	}
    return 0;
}

//==============================================================================
/**
 * NPCがいるかどうかの検査
 * @param   limit   テーブルの限界
 * @param   pFunc   テーブルにアクセスするための関数
 * @retval  none
 */
//==============================================================================

BOOL CommPlayerNPCHitCheck(int x,int z)
{
    int num,i;
    const FIELD_OBJ_H* pFObj;

    num = EventData_GetNpcCount(_pCommPlayerWork->pFSys);
    pFObj = EventData_GetNpcData(_pCommPlayerWork->pFSys);
    for(i = 0; i < num; i++){
        if((pFObj[i].gx == x) && (pFObj[i].gz == z)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 地形とネットプレーヤーのあたりを判定
 * @param   tcb      タスクポインタ
 * @param   work     ワーク構造体のポインタ
 * @retval  HIT存在する場合TRUE  動ける場合はFALSE
 */
//==============================================================================

static BOOL _commGetHitAttr(int x, int z, int netID)
{
    int i;

    if((x != COMM_PLAYER_INVALID_GRID) && (z != COMM_PLAYER_INVALID_GRID)){
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            if(i == netID){
                continue;
            }
            if((x == CommPlayerGetPosSX(i)) && (z == CommPlayerGetPosSZ(i))){
                OHNO_PRINT("プレーヤー同士のあたり\n");
                return TRUE;
            }
        }
        if(CommPlayerNPCHitCheck(x,z)){
            return TRUE;
        }
        if(_pCommPlayerWork->bUnder){
            if(!UgSecretBaseMoveing(x, z)){
                return TRUE;
            }
        }
    }
    return GetHitAttr(_pCommPlayerWork->pFSys, x, z);
}

//==============================================================================
/**
 * 罠にかかってるかどうか
 * @param   targetID
 * @retval  かかっていたらTRUE
 */
//==============================================================================

BOOL CommPlayerIsTrapBind(int targetID)
{
    if(_pCommPlayerWork->pCondMgr){
        return !CommPlayerIsNormalCondition_ServerSide(
            CommPlayerCondGetWork(_pCommPlayerWork->pCondMgr, targetID));
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの移動カウント
 * @param	netID  id
 * @retval	移動値
 */
//--------------------------------------------------------------

static int _getBlowMoveCount( int counter, int bBigBlow)
{
    int max;

    if(counter < 5){
        return 8;
    }
    else if(counter < 10){
        return 4;
    }
    //if(bBigBlow){
      //  max = _BIGBLOW_COUNTER_NUM_MAX;
    //}
    //else{
      //  max = _BLOW_COUNTER_NUM_MAX;
//    }
//    if(counter < (max - _BLOW_STOP_COUNT)){
        return 2;
  //  }
    //return 1;
}

//==============================================================================
/**
 * スピードにあわせて移動するフレーム数を返す
 * @param   speed  移動速度
 * @retval  移動するフレーム数
 */
//==============================================================================

static int _getWalkCount(int speed)
{
    int speedCount[_SPEED_MAX]={2,4,8,16,2};

    GF_ASSERT_RETURN(speed < _SPEED_MAX, 8);
    return speedCount[speed];
}

//==============================================================================
/**
 * 受信したキーデータを元に移動する
 * @param   tcb      タスクポインタ
 * @param   work     ワーク構造体のポインタ
 * @retval  none
 */
//==============================================================================

static void _commPlayerMove(TCB_PTR tcb, void *work)
{
    u16 cont;
    u8 speed;
    int dir, x, z, i, cnt;
    _PlayerPlace* pPP;
    PLAYER_CONDITION_PTR pCond=NULL;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->bActive[i] && _pCommPlayerWork->bMoveControl[i] &&
            _pCommPlayerWork->bMoveControlFlag[i] ){
            pPP = &_pCommPlayerWork->sPlayerPlaceServer[i];
            if(_pCommPlayerWork->pCondMgr){
                pCond = CommPlayerCondGetWork(_pCommPlayerWork->pCondMgr, i);
            }
            if(_pCommPlayerWork->bUnder){
                if(CommSecretBaseIsTraveling(i)){   // 場所移動中
#ifdef DEBUG_ONLY_FOR_ohno
                    if(sys.cont & PAD_BUTTON_START){
                        OHNO_PRINT("--秘密基地移動中\n");
                    }
#endif
                    continue;
                }
            }
            if(_pCommPlayerWork->walkCount[i] != 0){
                _pCommPlayerWork->walkCount[i]--;
            }

            if(_pCommPlayerWork->walkCount[i] == 0){
                if(_pCommPlayerWork->bUnder){
                    if(CommTrapCheckAndSendMessage( i )){ // 罠処理
                        continue;
                    }
                    if(!CommPlayerIsTrapBind(i)){
                        if(UgSecretBaseTrapGoodsCheck( i )){ // 罠処理
                            continue;
                        }
                    }
                }
            }

            if(pCond){
                if(!CommPlayerIsMoveCondition_ServerSide(pCond)){
                    continue;
                }
            }
            if(!_pCommPlayerWork->bMoveControlVS[i]){
                cont = CommGetPadCont(i);
            }
            else{
                cont = 0;
            }
            pPP->speed = CommGetSpeed(i);
            if(_pCommPlayerWork->walkCount[i]!=0){
                continue;
            }
            cnt = _getBlowMoveCount(_pCommPlayerWork->blowCounterS[i],_pCommPlayerWork->bBlowBigS[i] );
            if(_blowMove(i, cnt)){
                _pCommPlayerWork->walkCount[i] = cnt;
                _pCommPlayerWork->bMoveChange[i]=TRUE;
                continue;
            }
            if(pPP->bHit == TRUE){
                _pCommPlayerWork->bMoveChange[i] = TRUE;
            }
            pPP->bHit = FALSE;
//            if(_pCommPlayerWork->countHole[i] == 1){   //穴の罠
//                u8 bRet = TRUE;
//                CommTrapRecvEnd(i, 1, &bRet,NULL);
//                _pCommPlayerWork->countHole[i] = 0;
//            }
            if(_pCommPlayerWork->countHole[i] == 2){
                u8 id = i;
                _pCommPlayerWork->countHole[i] = 1;
                CommSendFixSizeData_ServerSide(CF_TRAP_PRIEND,&id);
                continue;
            }
            dir = _keyDirGet(cont,cont);
            x = CommPlayerGetPosSXDirAdd(i);
            z = CommPlayerGetPosSZDirAdd(i);
            if((x!=COMM_PLAYER_INVALID_GRID) && (z !=COMM_PLAYER_INVALID_GRID) && (dir != DIR_NOT)){
                if(pPP->dir != dir){
                    // 移動方向変換のみ
                    pPP->dir = dir;
                    _pCommPlayerWork->walkCount[i] = 4;
                    _pCommPlayerWork->bMoveChange[i]=TRUE;
                    if(_pCommPlayerWork->countHole[i] > 2){
                        _pCommPlayerWork->countHole[i]--;
                        continue;
                    }
                }
                else if(_pCommPlayerWork->countHole[i] != 0){
                    continue;
                }
                else if( _pCommPlayerWork->bUnder && (CommSecretBaseSingleStepFunc(i,x,z) == TRUE)){
                    continue;  // 秘密基地移動開始
                }
#ifdef PM_DEBUG
                else if(_commGetHitAttr( x, z, i) && !(pPP->speed == _SPEED_2)){
#else
                else if(_commGetHitAttr( x, z, i)){
#endif
                    pPP->bHit = TRUE;
                    _pCommPlayerWork->bMoveChange[i] = TRUE;
                    _pCommPlayerWork->walkCount[i] = 4;
                }
                else{
                    _pCommPlayerWork->bMoveChange[i]=TRUE;
                    pPP->xpos = x;
                    pPP->zpos = z;
                    pPP->dir = dir;
                    OHNO_SP_PRINT("サーバー  MOVE  %d %d \n",x,z);
                    _pCommPlayerWork->walkCount[i] = _getWalkCount(pPP->speed);
                    if(_pCommPlayerWork->giddyCounter[i]!=0){
                        _pCommPlayerWork->giddyCounter[i]--;
                        if(_pCommPlayerWork->giddyCounter[i]==0){
                            u8 bRet = TRUE;
                            CommTrapRecvEnd(i, 1, &bRet,NULL);
                        }
                    }
                }
            }
        }
    }
}

//==============================================================================
/**
 * 位置の情報を受信した   CF_PLAYER_POS
 * @param   netID    送信してきたID
 * @param   size     送られてきたデータサイズ
 * @param   pData    移動情報ポインタ
 * @retval  none
 */
//==============================================================================

void CommPlayerRecvPlace(int netID, int size, void* pBuff, void* pWork)
{
    u8* pData = (u8*)pBuff;
    _PlayerPlace* pPP;

    if(_pCommPlayerWork==NULL){
        return;
    }
    pPP = &_pCommPlayerWork->sPlayerPlaceServer[netID];

    if(pData[4] & _BIT_LIVE){
       // if(_pCommPlayerWork->bActive[netID]){
            _pCommPlayerWork->bPosAllSend = TRUE;
//            _pCommPlayerWork->bMoveChange[netID] = TRUE;
            return;
     //   }
    }
    if(pPP->dir == DIR_NOT){  // まだ初期状態の場合に
        // 位置データを子機に送信する
//        _pCommPlayerWork->bPosAllSend = TRUE;
        int i;
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            _pCommPlayerWork->bMoveChange[i] = TRUE;
        }

    }
    pPP->xpos = 0;
    pPP->zpos = 0;
    pPP->xpos += ((u32)pData[0]) & 0xff;
    pPP->xpos += ((u32)pData[1] << 8) & 0xff00;
    pPP->zpos += ((u32)pData[2]) & 0xff;
    pPP->zpos += ((u32)pData[3] << 8) & 0xff00;
    pPP->dir = pData[4] & 0x0f;

    OHNO_SP_PRINT("移動命令 %d %d %d %d\n", netID, pPP->xpos, pPP->zpos,pPP->dir);
    _pCommPlayerWork->bActive[netID] = TRUE;
    _pCommPlayerWork->bMoveChange[netID] = TRUE;


    if( GetHitAttr(_pCommPlayerWork->pFSys, pPP->xpos, pPP->zpos) ){ // 送られてきた座標が不正
        GF_ASSERT(0);
    }
}


//==============================================================================
/**
 * プレーヤーを消す命令を受信した  CF_PLAYER_DELETE
 * @param   netID    送信してきたID
 * @param   size     送られてきたデータサイズ
 * @param   pData    移動情報ポインタ
 * @retval  none
 */
//==============================================================================

void CommPlayerRecvDelete(int netID, int size, void* pBuff, void* pWork)
{
    u8* pData = (u8*)pBuff;
    u8 creatureID = pData[0];
    
    if(_pCommPlayerWork == NULL){
        return;
    }
    if(creatureID == CommGetCurrentID()){
        return;
    }
    OHNO_SP_PRINT("プレーヤーを消す命令を受信 %d \n",creatureID);

    if(_pCommPlayerWork->bUnder){
        UgMgrStartReturnLog(creatureID);
        if(!_pCommPlayerWork->bResetting){
            FE_FldOBJTrapsmogSet(_pCommPlayerWork->pFSys,
                                 _pCommPlayerWork->sPlayerPlace[creatureID].xpos,
                                 0,
                                 _pCommPlayerWork->sPlayerPlace[creatureID].zpos);

        }
    }
    CommPlayerDestroy(creatureID, FALSE, FALSE);
    OHNO_PRINT("CommPlayerDestroy--1 %d\n", creatureID);
    CommInfoDeletePlayer(creatureID);
}

//==============================================================================
/**
 * 場所を送るデータのサイズを返します
 * @param   none
 * @retval  データサイズ
 */
//==============================================================================

int CommPlayerGetRecvPlaceSize(void)
{
    return _PLACEDATA_SEND_SIZE;
}


//==============================================================================
/**
 * ID指定で位置の情報を受信した CF_PLAYER_POS_ID
 * @param   netID    送信してきたID
 * @param   size     送られてきたデータサイズ
 * @param   pData    移動情報ポインタ
 * @retval  none
 */
//==============================================================================

void CommPlayerRecvIDPlace(int netID, int size, void* pBuff, void* pWork)
{
    u16 pad;
    u8* pData = (u8*)pBuff;
    _PlayerPlace* pPP;
    int creatureID;

    creatureID = pData[0] & 0xf;
    if(_pCommPlayerWork == NULL){
        OHNO_SP_PRINT("----------受け取らなかった PlaceID %d\n", creatureID);
        return;
    }
    
    pPP = &_pCommPlayerWork->sPlayerPlace[creatureID];

    if(pData[2] & 0x80){
        pPP->bHit = TRUE;
    }
    else{
        pPP->bHit = FALSE;
    }

    pPP->xpos = 0;
    pPP->zpos = 0;
    pPP->xpos += ((u32)pData[1]) & 0xff;
    pPP->xpos += ((u32)pData[2] << 8) & 0x0100;
    pPP->zpos += ((u32)pData[3]) & 0xff;
    pPP->zpos += ((u32)pData[2] << 7) & 0x0100;
    pPP->dir = ((pData[0] >> 4) & 0x3);
    pPP->speed = ((pData[0] >> 6) & 0x3);

    _commPlayerAdd(creatureID);
//    OHNO_PRINT("CF_PLAYER_POS_ID %d %d %d %d\n",creatureID,pPP->xpos,pPP->zpos,pPP->dir);
}

//--------------------------------------------------------------
/**
 * 歩いた歩数をカウントする
 * @param	dir		移動する方向。DIR_UP等
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------

static void _walkCount(int netID)
{
    UNDERGROUNDDATA* pUGD = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommPlayerWork->pFSys));
    SB_RECORD_DATA* pSBD = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommPlayerWork->pFSys));

    if(_pCommPlayerWork->bUnder){
        if(netID == CommGetCurrentID()){
            UnderGroundCountWalk(pUGD);
            if(UnderGroundGetWalkNum(pUGD)==50){
                RECORD_Score_Add(SaveData_GetRecord(_pCommPlayerWork->pFSys->savedata),
                                 SCORE_ID_WLAK_100);
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を踏んだ場合の移動
 * @param	dir		移動する方向。DIR_UP等
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
static BOOL _blowAnim( int netID,int padTrg,int padCont,int speed )
{
    FIELD_OBJ_PTR fldobj;
    int idx, dir;
    u8 walkcmd[]={
        AC_WALK_U_2F,				///<上に移動　2フレーム
        AC_WALK_D_2F,				///<下に移動　2フレーム
        AC_WALK_L_2F,				///<左に移動　2フレーム
        AC_WALK_R_2F,				///<右に移動　2フレーム
        AC_WALK_U_4F,				///<上に移動　4フレーム
        AC_WALK_D_4F,				///<下に移動　4フレーム
        AC_WALK_L_4F,				///<左に移動　4フレーム
        AC_WALK_R_4F,				///<右に移動　4フレーム
        AC_WALK_U_8F,				///<上に移動　8フレーム
        AC_WALK_D_8F,				///<下に移動　8フレーム
        AC_WALK_L_8F,				///<左に移動　8フレーム
        AC_WALK_R_8F,				///<右に移動　8フレーム
    };

#if T1662_060815_FIX
    if((_pCommPlayerWork->blowDir[netID]==DIR_NOT) ||
       (_pCommPlayerWork->pPlayer[netID]==NULL)){
        return FALSE;
    }
    if(padTrg == 0){
        return TRUE;
    }
#else //T1662_060815_FIX
    if((_pCommPlayerWork->blowDir[netID]==DIR_NOT) ||
       (padTrg == 0) ||
       (_pCommPlayerWork->pPlayer[netID]==NULL)){
        return FALSE;
    }
#endif //T1662_060815_FIX

    // 動き出す時に方向が違っていたら変化させる
    fldobj = Player_FieldOBJGet( _pCommPlayerWork->pPlayer[netID] );   //自機のフィールドOBJポインタ取得
    if(Player_DirGet(_pCommPlayerWork->pPlayer[netID])!=CommPlayerGetReverseDir(_pCommPlayerWork->blowDir[netID])){
        FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
        Player_DirSet(_pCommPlayerWork->pPlayer[netID], CommPlayerGetReverseDir(_pCommPlayerWork->blowDir[netID]));
        FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
    }

    if( FieldOBJ_AcmdEndCheck(fldobj) == TRUE ){ //アニメ終了チェック

	}

    if( FieldOBJ_AcmdSetCheck(fldobj) == TRUE ){//アニメセットできるか?
        _walkCount(netID);
        OHNO_SP_PRINT("吹き飛ばし動作C %d %d \n",netID, speed);
        switch( speed  ){
          case _SPEED_2:
            FieldOBJ_AcmdSet( fldobj, walkcmd[_pCommPlayerWork->blowDir[netID]] ); //出来る。下方向に移動
            break;
          case _SPEED_4:
            FieldOBJ_AcmdSet( fldobj, walkcmd[_pCommPlayerWork->blowDir[netID]+4] ); //出来る。下方向に移動
            break;
          case _SPEED_8:
            FieldOBJ_AcmdSet( fldobj, walkcmd[_pCommPlayerWork->blowDir[netID]+8] ); //出来る。下方向に移動
            break;
        }
    }else{
        OHNO_SP_PRINT("アニメセットできなかった\n");
        //　　　　　　他のアニメ実行中により出来ない。出来るまで待つ
    }
    return TRUE;
}

//==============================================================================
/**
 * クライアント側の移動処理  １マスづつしか動かないようになっている
 * @param   netID
 * @retval  none
 */
//==============================================================================

static void _playerMoveClient(int netID)
{
    BOOL bNoMove = FALSE, bHit = TRUE;
    u16 pad=0;
    _PlayerPlace* pPP;
    PLAYER_STATE_PTR pPlayerState;
    int speed;

    pPP = &_pCommPlayerWork->sPlayerPlace[netID];

    if(_pCommPlayerWork->walkCountClient[netID] != 0){  // 現状
        _pCommPlayerWork->walkCountClient[netID]--;
        return;
    }

    if((pPP->xpos == COMM_PLAYER_INVALID_GRID) || (pPP->zpos == COMM_PLAYER_INVALID_GRID)){
        return;
    }
    if(_pCommPlayerWork->bResetting){
        return;
    }
    if(!_pCommPlayerWork->bUnder){
        if(netID == CommGetCurrentID()){
            if(!_pCommPlayerWork->bMoveControlVSRoom){
                return;
            }
        }
    }
    
    pPlayerState = _pCommPlayerWork->pPlayer[netID];
    if( pPlayerState ){
        int x = Player_NowGPosXGet( pPlayerState ) - pPP->xpos;
        int z = Player_NowGPosZGet( pPlayerState ) - pPP->zpos;
        int dir = Player_DirGet( pPlayerState );

        if((x == 0) && (z == 0)){
            pad = 0;
        }
        else if(abs(x) > abs(z)){
            if(x > 0){
                pad = PAD_KEY_LEFT;
            }
            else{
                pad = PAD_KEY_RIGHT;
            }
        }
        else{
            if(z > 0){
                pad = PAD_KEY_UP;
            }
            else{
                pad = PAD_KEY_DOWN;
            }
        }
        if(abs(x) + abs(z) > 2){
            bHit = FALSE;
        }

        if(_blowAnim(netID,pad,pad,pPP->speed)){
            return;
        }

        {
            u32 code = ACMD_NOT;
            int sp;

            speed = pPP->speed;
            switch( pPP->speed  ){
              case _SPEED_2:
                sp = JIKI_FRAME_SPEED_2F;
                break;
              case _SPEED_4:
                sp = JIKI_FRAME_SPEED_4F;
                pad |= PAD_BUTTON_B;
                break;
              case _SPEED_8:
                sp = JIKI_FRAME_SPEED_8F;
                break;
              case _SPEED_16:
                sp = JIKI_FRAME_SPEED_16F;
                break;
            }
            if(_pCommPlayerWork->forceDirFlg && (netID == CommGetCurrentID())){
                _pCommPlayerWork->forceDirFlg--;
//                code = FieldOBJ_AcmdCodeDirChange( pPP->dir, AC_STAY_WALK_U_4F );
            }
            else if(!CommIsSendMoveData() && _pCommPlayerWork->bUnder && (netID==CommGetCurrentID())){ //移動ロック時には移動アニメしない
                code = Player_KeyMoveSelectAcmdCodeGet(
                    pPlayerState, pad, pad, sp, TRUE, JIKI_MOVE_HIT_BIT_NON);
            }
            else if(((pad & ~PAD_BUTTON_B) == 0)  && (pPP->bHit) ){  // 移動しなくて良くてあたりがある場合
                speed = _SPEED_16;
                switch(pPP->dir){
                  case DIR_UP:
                    code = AC_STAY_WALK_U_16F;
                    break;
                  case DIR_DOWN:
                  default:
                    code = AC_STAY_WALK_D_16F;
                    break;
                  case DIR_LEFT:
                    code = AC_STAY_WALK_L_16F;
                    break;
                  case DIR_RIGHT:
                    code = AC_STAY_WALK_R_16F;
                    break;
                }
            }
            else if(((pad & ~PAD_BUTTON_B) == 0)  && (pPP->dir != dir) ){
                code = FieldOBJ_AcmdCodeDirChange( pPP->dir, AC_STAY_WALK_U_4F );
            }
            else{
                code = Player_KeyMoveSelectAcmdCodeGet(
                    pPlayerState, pad, pad, sp, TRUE, JIKI_MOVE_HIT_BIT_NON);
            }
            if( Player_AcmdSetCheck(pPlayerState) == FALSE ){          //アニメーションコマンド中
                if( Player_MoveCancellCheck(pPlayerState) == FALSE ){  //キャンセル不可
                    return;
                }
            }
            if(code != ACMD_NOT){
                Player_AcmdSet( pPlayerState, code );
                if(pad & ~PAD_BUTTON_B){
                    if(_pCommPlayerWork->walkCountClient[netID] == 0){
                        _pCommPlayerWork->walkCountClient[netID] = _getWalkCount(speed);
                    }
                    if(_pCommPlayerWork->walkCountClient[netID] != 0){
                        _pCommPlayerWork->walkCountClient[netID]--;
                    }
                    _walkCount(netID);
                }
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を踏んだ場合のサーバー移動
 * @param	netID  id
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
static BOOL _blowMove( int netID , int cnt)
{
    int x,z;
    _PlayerPlace* pPP;
    
    if(_pCommPlayerWork->blowCounterS[netID]==0){
        return FALSE;
    }
    if(_pCommPlayerWork->blowCounterS[netID]==_BLOW_COUNTER_STOP){
        return TRUE;
    }
    _pCommPlayerWork->blowCounterS[netID]--;
    if(1 == cnt){        // 停止中
        return TRUE;
    }
    x = CommPlayerGetPosSX(netID);
    z = CommPlayerGetPosSZ(netID);
    x += FieldOBJ_DirAddValueGX(_pCommPlayerWork->blowDirS[netID]);
    z += FieldOBJ_DirAddValueGZ(_pCommPlayerWork->blowDirS[netID]);

    if(_pCommPlayerWork->blowCounterS[netID]!=0){
        if(_commGetHitAttr(x, z, netID)){
            _pCommPlayerWork->blowCounterS[netID] = 1;
        }
    }
    if(_pCommPlayerWork->blowCounterS[netID]==1){
        return TRUE;
    }
    else if(_pCommPlayerWork->blowCounterS[netID]==0){
        u8 bRet = TRUE;
        CommTrapRecvEnd(netID, 1, &bRet,NULL);
        return TRUE;
    }
    pPP = &_pCommPlayerWork->sPlayerPlaceServer[netID];
    pPP->xpos = x;
    pPP->zpos = z;
    switch(cnt){
      case 2:
        pPP->speed = _SPEED_2;
        break;
      case 4:
        pPP->speed = _SPEED_4;
        break;
      case 8:
        pPP->speed = _SPEED_8;
        break;
    }
    OHNO_SP_PRINT("吹き飛ばし動作 %d %d %d \n",netID, pPP->speed, _pCommPlayerWork->blowCounterS[netID]);
    return TRUE;
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を踏んだ場合のサーバ側移動を開始
 * @param	netID   i
 * @param	dir		移動する方向。DIR_UP等
 * @param	bBig    吹き飛ばされる大きさ
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
void CommPlayerBlowStart( int netID, int dir , BOOL bBig)
{
    _PlayerPlace* pPP = &_pCommPlayerWork->sPlayerPlaceServer[netID];
    u8 buff[3];
    
    pPP->dir = CommPlayerGetReverseDir(dir);  // 向く方向
    _pCommPlayerWork->blowDirS[netID] = dir;  // 飛ばされる方向
    if(bBig){
        _pCommPlayerWork->bBlowBigS[netID] = TRUE;
        _pCommPlayerWork->blowCounterS[netID] = _BIGBLOW_COUNTER_NUM_MAX;// + _BLOW_STOP_COUNT;
    }
    else{
        _pCommPlayerWork->bBlowBigS[netID] = FALSE;
        _pCommPlayerWork->blowCounterS[netID] = _BLOW_COUNTER_NUM_MAX;// + _BLOW_STOP_COUNT;
    }
/*    buff[0]=netID;
    buff[1]=dir;
    buff[2]=bBig;
    CommSendFixSizeData_ServerSide(CF_TRAP_SECOND_START_RET,buff);*/
    _pCommPlayerWork->bMoveChange[netID]=TRUE;
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を強制終了する場合の処理
 * @param   victimNetID   被害者ID
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
void CommPlayerBlowExit(int victimNetID)
{
    _pCommPlayerWork->blowCounterS[victimNetID] = 0;
}


//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を開始する
 * @param   victimNetID   被害者ID
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
void CommPlayerBlowFirst(int victimNetID)
{
    _pCommPlayerWork->blowCounterS[victimNetID] = _BLOW_COUNTER_STOP;
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を踏んだ場合の移動を開始
 * @param	dir		移動する方向。DIR_UP等
 * @retval	終了したらTRUE
 */
//--------------------------------------------------------------
void CommPlayerBlowAnimStart( int netID, int dir , BOOL bBig)
{
	FIELD_OBJ_PTR fldobj;

    if(_pCommPlayerWork->pPlayer[netID]==NULL){
      return;
    }
    fldobj = Player_FieldOBJGet( _pCommPlayerWork->pPlayer[netID] );   //自機のフィールドOBJポインタ取得

    FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
    FieldOBJ_StatusBit_ON( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
//    FE_DirTrap_Add(_pCommPlayerWork->pFSys,
  //                 CommPlayerGetPosX(netID),CommPlayerGetPosZ(netID),dir);

    _pCommPlayerWork->blowDir[netID] =dir;
}

//--------------------------------------------------------------
/**
 * 吹き飛ばしの罠を踏んだ場合の移動を停止
 * @param	netID   id
 * @retval	none
 */
//--------------------------------------------------------------
void CommPlayerBlowAnimStop( int netID)
{
	FIELD_OBJ_PTR fldobj;
    if(_pCommPlayerWork->pPlayer[netID]==NULL){
      return;
    }
    
    if(_pCommPlayerWork->blowDir[netID] != DIR_NOT){
        fldobj = Player_FieldOBJGet( _pCommPlayerWork->pPlayer[netID] );   //自機のフィールドOBJポインタ取得
        FieldOBJ_AcmdEnd(fldobj); 			 //アニメ完全終了
        FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_DIR );
        FieldOBJ_StatusBit_OFF( fldobj, FLDOBJ_STA_BIT_PAUSE_ANM );
        _pCommPlayerWork->blowDir[netID] = DIR_NOT;
    }
}

//==============================================================================
/**
 * IDつきで場所を送るデータのサイズを返します
 * @param   none
 * @retval  データサイズ
 */
//==============================================================================

int CommPlayerGetRecvIDPlaceSize(void)
{
    return _IDPLACEDATA_SEND_SIZE;
}

//==============================================================================
/**
 * 会話データを受信します
 * @param   netID         会話を送信してきた相手
 * @param   size          受信データサイズ
 * @param   pData         メッセージが含まれているデータ
 * @retval  none
 */
//==============================================================================

//static void _recvTalk(int netID, int size, void* pData, void* pWork)
//{
//}

//void CommPlayerRecvTalk(int netID, int size, void* pData, void* pWork)
//{
    // すぐにみんなに返信
//    CommSendData_ServerSide(CF_TALK_DISP_SERVER_SIDE, pData, size);
//}

//void CommPlayerRecvTalk_ServerSide(int netID, int size, void* pData, void* pWork)
//{
///    _recvTalk(netID, size, pData, pWork);
//}

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

static void _msgEndCallBackDel(int num)
{
    CommPlayerHoldEnd();
}

static void _msgEndCallBackNoTalk(int num)
{
    CommPlayerHoldBitEnd(_HOLD_FLAG_NO_TALK);
}

static void _msgEndCallBackNoDig(int num)
{
    CommPlayerHoldBitEnd(_HOLD_FLAG_NO_DIG);
}

static void _msgEndCallBackRipOff(int num)
{
    CommPlayerHoldBitEnd(_HOLD_FLAG_RIP_OFF);
}


static void _msgEndCallBackStolenMy(int num)
{
    CommPlayerHoldBitEnd(_HOLD_FLAG_STOLEN_MY);
}




//--------------------------------------------------------------
/**
 * @brief   子機からNPCに話しかけた際に飛んできます
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void CommPlayerRecvOtherTalk(int netID, int size, void* pData, void* pWork)
{
    u8 id = netID;
    
//    CommPlayerSetMoveControl_Server(netID,TRUE);
    CommSendFixSizeData_ServerSide(CF_OTHER_TALK_SERVER_SIDE,&id);
}

//--------------------------------------------------------------
/**
 * @brief   親機からNPCに話しかけた子機がいた際に飛んできます CF_OTHER_TALK_SERVER_SIDE
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
void CommPlayerRecvOtherTalk_ServerSide(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    UgMgrSetTalkOtherLog(pBuff[0]);  //LOG
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラが通信による移動状態にあるかどうか
 * @param   none
 * @retval  通信で移動させる場合TRUE
 */
//--------------------------------------------------------------

BOOL CommPlayerIsControl(void)
{
    if(CommGetAloneMode()){
        return TRUE;
    }
    if(!_pCommPlayerWork){
        return FALSE;
    }
    if(!CommIsConnect(CommGetCurrentID()) ){  // オンラインならOK
        return FALSE;
    }
    if(_pCommPlayerWork->bUnder && !CommIsUnderGroundMoveState()){
        return FALSE;
    }
    return TRUE;

}

//--------------------------------------------------------------
/**
 * @brief   生きてるかどうか
 * @param   netID ネットワークでのID
 * @retval  ActiveFlg
 */
//--------------------------------------------------------------

BOOL CommPlayerIsActive(int netID)
{
    return _pCommPlayerWork->bActive[netID];
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのXの位置を返す  かせき掘り専用
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosDigFossilX(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlace[netID].xpos;
    }
    else if(!CommPlayerIsControl()){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].xpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのZの位置を返す  かせき掘り専用
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosDigFossilZ(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlace[netID].zpos;
    }
    else if(!CommPlayerIsControl()){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].zpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのXの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosX(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlace[netID].xpos;
    }
    else if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].xpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのZの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosZ(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlace[netID].zpos;
    }
    else if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].zpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのXの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosXOrg(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].xpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのZの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosZOrg(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].zpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラの目の前の位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosXDirAdd(int netID)
{
    if(CommPlayerGetPosX(netID) == COMM_PLAYER_INVALID_GRID){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].xpos +
        FieldOBJ_DirAddValueGX(_pCommPlayerWork->sPlayerPlace[netID].dir);
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラの目の前の位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosZDirAdd(int netID)
{
    if(CommPlayerGetPosZ(netID) == COMM_PLAYER_INVALID_GRID){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].zpos +
        FieldOBJ_DirAddValueGZ(_pCommPlayerWork->sPlayerPlace[netID].dir);
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのXの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSX(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlaceServer[netID].xpos;
    }
    else if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].xpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのZの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSZ(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    else if(CommGetCurrentID() == netID){
        return _pCommPlayerWork->sPlayerPlaceServer[netID].zpos;
    }
    else if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].zpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのXの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSXOrg(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].xpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのZの位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSZOrg(int netID)
{
    if(!_pCommPlayerWork){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].zpos;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラの目の前の位置を返す
 * @param   netID ネットワークでのID
 * @retval  Xの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSXDirAdd(int netID)
{
    if(CommPlayerGetPosSX(netID) == COMM_PLAYER_INVALID_GRID){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].xpos +
        FieldOBJ_DirAddValueGX(_pCommPlayerWork->sPlayerPlaceServer[netID].dir);
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラの目の前の位置を返す
 * @param   netID ネットワークでのID
 * @retval  Zの場所
 */
//--------------------------------------------------------------

int CommPlayerGetPosSZDirAdd(int netID)
{
    if(CommPlayerGetPosSZ(netID) == COMM_PLAYER_INVALID_GRID){
        return COMM_PLAYER_INVALID_GRID;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].zpos +
        FieldOBJ_DirAddValueGZ(_pCommPlayerWork->sPlayerPlaceServer[netID].dir);
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのdirを返す
 * @param   netID ネットワークでのID
 * @retval  dir
 */
//--------------------------------------------------------------

int CommPlayerGetDir(int netID)
{
    if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return DIR_NOT;
    }
    return _pCommPlayerWork->sPlayerPlace[netID].dir;
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーキャラのdirを返す
 * @param   netID ネットワークでのID
 * @retval  dir
 */
//--------------------------------------------------------------

int CommPlayerGetSDir(int netID)
{
    if(!CommPlayerIsControl() || !_pCommPlayerWork->bActive[netID]){
        return DIR_NOT;
    }
    return _pCommPlayerWork->sPlayerPlaceServer[netID].dir;
}

//--------------------------------------------------------------
/**
 * @brief   ターゲットの角度をnetIDと逆方向にする  すると向かい合うはず
 * @param   netID ネットワークでのID
 * @param   targetID ネットワークでのターゲットのID
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetLook_Server(int netID, int targetID)
{
    int dir = CommPlayerGetReverseDir(_pCommPlayerWork->sPlayerPlaceServer[netID].dir);

    _pCommPlayerWork->sPlayerPlaceServer[targetID].dir = dir;
    _pCommPlayerWork->bMoveChange[targetID] = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ターゲットの角度をnetIDと逆方向にする  すると向かい合うはず
 * @param   netID ネットワークでのID
 * @param   targetID ネットワークでのターゲットのID
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetLook(int netID, int targetID)
{
    int dir = CommPlayerGetReverseDir(_pCommPlayerWork->sPlayerPlace[netID].dir);
    _pCommPlayerWork->sPlayerPlace[targetID].dir = dir;
}

//--------------------------------------------------------------
/**
 * @brief   罠にかかった時のプレーヤーの状態をセットすいる
 * @param   victimNetID  罠にかかった人
 * @param   trapType     罠タイプ
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetCondition(int victimNetID, int condition)
{
    OHNO_PRINT("setコンディション %d \n", victimNetID);
    CommPlayerCondSetCondition(
        CommPlayerCondGetWork(_pCommPlayerWork->pCondMgr, victimNetID),
        condition);
}

//--------------------------------------------------------------
/**
 * @brief   罠にかかった時のプレーヤーの状態を消す
 * @param   victimNetID  罠にかかった人
 * @param   trapType     罠タイプ
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerResetCondition(int victimNetID)
{
    OHNO_PRINT("リセットコンディション %d \n", victimNetID);
    CommPlayerCondSetCondition(
        CommPlayerCondGetWork(_pCommPlayerWork->pCondMgr, victimNetID),
        PLAYER_COND_NONE);
}

//--------------------------------------------------------------
/**
 * @brief   場所移動する
 * @param   netID
 * @param   x
 * @param   y
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerBaseTeleportServer(int netID, int x, int z, int dir)
{
    _PlayerPlace* pPP = &_pCommPlayerWork->sPlayerPlaceServer[netID];
    pPP->xpos = x + FieldOBJ_DirAddValueGX(dir);
    pPP->zpos = z + FieldOBJ_DirAddValueGZ(dir);
    pPP->dir = dir;
 //   _pCommPlayerWork->bMoveChange[netID]=TRUE;  // 煙を秘密基地に入る時に出したいので この瞬間はclientに通知しない 2006.05.16
}

//--------------------------------------------------------------
/**
 * @brief   場所移動する
 * @param   netID
 * @param   x
 * @param   y
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerBaseTeleportClient(int netID, int x, int z, int dir)
{
    _PlayerPlace* pPP;
    
    if(!_pCommPlayerWork){
        return;
    }
    pPP = &_pCommPlayerWork->sPlayerPlace[netID];
    if(!_pCommPlayerWork->bResetting){
        FE_FldOBJTrapsmogSet(_pCommPlayerWork->pFSys, pPP->xpos, 0, pPP->zpos);
    }
    pPP->xpos = x;
    pPP->zpos = z;
    pPP->dir = dir;
    if(_pCommPlayerWork->pPlayer[netID]){
        Player_GPosInit( _pCommPlayerWork->pPlayer[netID],
                         x, z, dir );
    }
    if(!_pCommPlayerWork->bResetting){
        FE_FldOBJTrapsmogSet(_pCommPlayerWork->pFSys, pPP->xpos, 0, pPP->zpos);
    }
}

typedef struct{
    u8 bOpen;
    u8 netID;
    u8 targetID;
} _ugMenuOpen;

//--------------------------------------------------------------
/**
 * @brief   炭鉱フィールドメニューを開いてよいかどうか  CF_CHECK_FIELDMENU_OPEN
 * @param   コールバックパラメーター
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerRecvCheckFieldMenuOpen(int netID, int size, void* pData, void* pWork)
{
    _ugMenuOpen menuOpen;

    menuOpen.bOpen = _RESULT_NG;
    menuOpen.netID = netID;

    if(_pCommPlayerWork->bMoveControl[ netID ] && !CommPlayerIsTrapBind(netID)){
        if(CommPlayerIsFlagData(netID)){
            menuOpen.bOpen = _RESULT_DELFLAG_OPEN;
        }
        else{
            menuOpen.bOpen = _RESULT_OK;
        }
    }
    if(CommSendData_ServerSide(CF_RESULT_FIELDMENU_OPEN, &menuOpen, 2)){
        if(menuOpen.bOpen!=_RESULT_NG){
            CommPlayerSetMoveControl_Server(netID, FALSE);            
//            _pCommPlayerWork->bMoveControl[ netID ] = FALSE;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーがそこにいるかどうか
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

int CommPlayerIsAlive(int xpos, int zpos)
{
    int i,x,y;

    if(!_pCommPlayerWork){
        return COMM_INVALID_ID;
    }
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->bActive[i] == FALSE){
            continue;
        }
        x = _pCommPlayerWork->sPlayerPlaceServer[i].xpos;
        y = _pCommPlayerWork->sPlayerPlaceServer[i].zpos;

        if((xpos == x) && (zpos == y)){
            return i;
        }
    }
    return COMM_INVALID_ID;
}

//--------------------------------------------------------------
/**
 * @brief   STARTメニューを開いていいかどうかのコールバック CF_RESULT_FIELDMENU_OPEN
 * @param   
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerRecvResultFieldMenuOpen(int netID, int size, void* pData, void* pWork)
{
    _ugMenuOpen* pMenuOpen = pData;

    if(!CommIsSendMoveData()){
        return;
    }
    if((pMenuOpen->bOpen == _RESULT_OK) && (pMenuOpen->netID == CommGetCurrentID())){
        if(!_pCommPlayerWork->bTalkMenuDisp){
            _pCommPlayerWork->bTalkMenuDisp = TRUE;
            //地下専用メニューを出す
            CommUnderBagInit(_talkMenuEnd, _pCommPlayerWork->pFSys);
        }
    }
    else if((pMenuOpen->bOpen == _RESULT_DELFLAG_OPEN) && (pMenuOpen->netID == CommGetCurrentID())){
        if(!_pCommPlayerWork->bTalkMenuDisp){
            _pCommPlayerWork->bTalkMenuDisp = TRUE;
            CommUnderBagFlagStart(_talkMenuEnd, _pCommPlayerWork->pFSys);
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   問いかけメニューを開いていいかどうかのコールバック
 *          CF_RESULT_UGMENU_OPEN
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerRecvResultUGMenuOpen(int netID, int size, void* pData, void* pWork)
{
    _ugMenuOpen* pMenuOpen = pData;
    EVENTWORK* pEV = SaveData_GetEventWork( _pCommPlayerWork->pFSys->savedata );
    GF_ASSERT_RETURN(pMenuOpen->netID < COMM_MACHINE_MAX,);

    OHNO_PRINT("会話開始 クライアント\n");

    if((pMenuOpen->bOpen == _RESULT_FOSSIL) && (pMenuOpen->netID == CommGetCurrentID())){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_72,TRUE,_msgEndCallBack);
    }
    if(pMenuOpen->bOpen == _RESULT_OK){    // 向かい合う方向に
        CommPlayerSetLook(pMenuOpen->netID, pMenuOpen->targetID);
    }
    if((pMenuOpen->bOpen == _RESULT_OK) && (pMenuOpen->netID == CommGetCurrentID())){
        CommUnderTalkInit(pMenuOpen->targetID , _talkMenuEnd, _pCommPlayerWork->pFSys);
        _pCommPlayerWork->talkMenuInfo.netID = pMenuOpen->netID ;
        _pCommPlayerWork->talkMenuInfo.targetID = pMenuOpen->targetID;
        _pCommPlayerWork->talkMenuInfo.bItemMenu = FALSE;
        _pCommPlayerWork->talkMenuInfo.bPersonalInformation = FALSE;
        if(_pCommPlayerWork->handCount[pMenuOpen->targetID] == 0){
            SecretBaseRecordSetTalkNum(SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommPlayerWork->pFSys)),pMenuOpen->targetID); // 話しかけ開始
            SysWork_UGTalkCountSet(pEV,SysWork_UGTalkCountGet(pEV)+1);
            SysWork_UGTalkCount2Set(pEV,SysWork_UGTalkCount2Get(pEV)+1);
            _pCommPlayerWork->handCount[pMenuOpen->targetID]++;
        }
    }
    if((pMenuOpen->bOpen == _RESULT_OK) && (pMenuOpen->targetID == CommGetCurrentID())){
        CommUnderTalkBind(pMenuOpen->targetID, pMenuOpen->netID, _pCommPlayerWork->pFSys);
    }
    if((pMenuOpen->bOpen == _RESULT_NG) && (pMenuOpen->netID == CommGetCurrentID())){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_03,TRUE,_msgEndCallBack);
    }
    if(pMenuOpen->bOpen == _RESULT_OK){
        UgMgrSetTalkLog(pMenuOpen->netID, pMenuOpen->targetID);
    }
}

//--------------------------------------------------------------
/**
 * @brief   移動制御フラグの設定
 * @param   
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetMoveControl_Server(int netID, BOOL bMoveControl)
{
    if(_pCommPlayerWork->bMoveControl[ netID ] != bMoveControl){
        _pCommPlayerWork->bMoveControl[ netID ] = bMoveControl;
        OHNO_PRINT("ommPlayerSetMoveControl_Server %d  id %d\n",bMoveControl,netID);
        _pCommPlayerWork->sPlayerPlaceServer[netID].bHit = FALSE;
        _pCommPlayerWork->bMoveChange[netID] = TRUE;
        _pCommPlayerWork->sPlayerPlaceServer[netID].speed = _SPEED_8;

    }

}

//--------------------------------------------------------------
/**
 * @brief   プレーヤーがげんきにいるかどうか
 * @param   netID
 * @retval  コントロールできるならTRUE 取り込み中ならFALSE
 */
//--------------------------------------------------------------

BOOL CommPlayerGetMoveControl(int netID)
{
    if(_pCommPlayerWork->bDataSendFlag){
        return FALSE;
    }
    if(!_pCommPlayerWork->bMoveControlFlag[ netID ]){
        return FALSE;
    }
    return _pCommPlayerWork->bMoveControl[ netID ];
}


//--------------------------------------------------------------
/**
 * @brief   バトルルーム内でプレイヤーが正しい位置についたかどうか
 * @param   none
 * @retval  位置についたらTRUE
 */
//--------------------------------------------------------------

BOOL CommPlayerCheckBattleJump(void)
{
    _Grid battleGrid2[]={{4,7},{11,7}};
    _Grid battleGrid4[]={{4,6},{11,6},{4,8},{11,8}};
    int machineMax = CommGetMaxEntry(CommStateGetServiceNo());
    int i,j,count=0,stand[4],w;
    int ret = FALSE;
    _Grid* pBattleGrid;

    if(machineMax==2){
        pBattleGrid = battleGrid2;
    }
    else{
        pBattleGrid = battleGrid4;
    }

    for(i = 0; i < machineMax; i++){
        for(j = 0; j < machineMax; j++){
            if((CommPlayerGetPosX(j) == pBattleGrid[i].xpos) &&
               (CommPlayerGetPosZ(j) == pBattleGrid[i].zpos)){
                count++;
                stand[ j ] = i;
                if(j == CommGetCurrentID()){
                    ret = TRUE;
                }
                break;
            }
        }
    }
    if(count == machineMax){
        for(i = 0; i < machineMax; i++){
            CommSetStandNo(stand[ i ], i);
        }
    }
    return ret;
}

//--------------------------------------------------------------
/**
 * @brief   子機から スタートライン検査可能フラグが到着
 * @param   none
 * @retval  位置についたらTRUE
 */
//--------------------------------------------------------------

void CommPlayerRecvStartLineSet(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(pBuff[0] == 3){
        _pCommPlayerWork->bMoveControlVS[ netID ] = FALSE;
    }
    else{
        _pCommPlayerWork->bStartLineChk[netID] = pBuff[0];
    }
}

//--------------------------------------------------------------
/**
 * @brief   バトルルーム内でプレイヤーが正しい位置についたかどうか
 * @param   none
 * @retval  位置についたらTRUE
 */
//--------------------------------------------------------------

static _Grid battleGrid2[]={{4,7},{11,7}};
static _Grid battleGrid4[]={{4,6},{11,6},{4,8},{11,8}};

static void CommPlayerCheckBattleJump_Server(void)
{
    int machineMax = CommGetMaxEntry(CommStateGetServiceNo());
    int i,j,count=0,stand[4];
    int ret = FALSE;
    _Grid* pBattleGrid;
    u8 netID;
    
    if(machineMax==2){
        pBattleGrid = battleGrid2;
    }
    else{
        pBattleGrid = battleGrid4;
    }

    for(netID = 0; netID < machineMax; netID++){
        if(!_pCommPlayerWork->bStartLineChk[netID]){
            continue;
        }
        for(i = 0; i < machineMax; i++){
            if((CommPlayerGetPosSX(netID) == pBattleGrid[i].xpos) &&
               (CommPlayerGetPosSZ(netID) == pBattleGrid[i].zpos)){
                _pCommPlayerWork->bMoveControlVS[ netID ] = TRUE;
                CommSendFixSizeData_ServerSide(CF_DIRECT_STARTPOS, &netID);
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   バトルルーム内でプレイヤーが正しい位置についた時の方向換え
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerBattleDirSet(void)
{
    int id = CommGetCurrentID();
    int code;
    
    if(CommPlayerGetPosX(id) > 8){
        CommPlayerSetDir(DIR_LEFT);
        code = FieldOBJ_AcmdCodeDirChange( DIR_LEFT, AC_STAY_WALK_U_4F );
    }
    else{
        CommPlayerSetDir(DIR_RIGHT);
        code = FieldOBJ_AcmdCodeDirChange( DIR_RIGHT, AC_STAY_WALK_U_4F );
    }
    Player_AcmdSet( _pCommPlayerWork->pPlayer[id], code );
    CommSetForceDir();
}

//--------------------------------------------------------------
/**
 * @brief   バトルルーム内でポジションの後ろに移動
 * @param   none
 * @retval  位置についたらTRUE
 */
//--------------------------------------------------------------

BOOL CommPlayerMoveBattlePos(void)
{
    int machineMax = CommGetMaxEntry(CommStateGetServiceNo());
    int i,j,count=0,stand[4],dir;
    int ret = FALSE;

    for(i = 0; i < machineMax; i++){  // 全員のデータがあることを検査
        _PlayerPlace* pPP = &_pCommPlayerWork->sPlayerPlaceServer[i];
        if(pPP->dir == DIR_NOT){
            return FALSE;
        }
    }
    for(i = 0; i < machineMax; i++){
        _PlayerPlace* pPP = &_pCommPlayerWork->sPlayerPlaceServer[i];
        dir = CommPlayerGetReverseDir(pPP->dir);
        pPP->xpos += FieldOBJ_DirAddValueGX(dir);
        pPP->zpos += FieldOBJ_DirAddValueGZ(dir);
        pPP->speed = _SPEED_8;
        _pCommPlayerWork->bMoveChange[i] = TRUE;
        CommPlayerSetMoveControl_Server( i, TRUE);
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * 旗を消す
 * @param	netID   playerID
 * @retval	消したらTRUE
 */
//--------------------------------------------------------------
BOOL CommPlayerDeleteFlagData(int netID)
{
    if(_pCommPlayerWork->pNowFlag[netID] != NULL){
        sys_FreeMemoryEz(_pCommPlayerWork->pNowFlag[netID]);
        _pCommPlayerWork->pNowFlag[netID] = NULL;
        _pCommPlayerWork->hedFE[netID] = _HFE_NONE;
        _pCommPlayerWork->sendFlagData[netID].netID = INVALID_NETID;
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * 旗を保存する
 * @param	netID   playerID
 * @retval	消したらTRUE
 */
//--------------------------------------------------------------
static void _commPlayerDeliveryFlagData(int netID)
{
    int i;

    if(netID == CommGetCurrentID()){  // 記録
        if(_pCommPlayerWork->pNowFlag[netID] != NULL){

            RECORD_Score_Add(SaveData_GetRecord(_pCommPlayerWork->pFSys->savedata), SCORE_ID_NEW_FLAG_TAKE_OUT);

            for(i = 0; i < _KEEP_FLAG_MAX; i++){
                if(_pCommPlayerWork->pKeepFlag[i]){
                    if(MyStatus_Compare(_pCommPlayerWork->pNowFlag[netID], _pCommPlayerWork->pKeepFlag[i]) == TRUE){
                        // 完全一致 は今の旗を消すだけ
                        CommPlayerDeleteFlagData(netID);
                        return;
                    }
                }
            }
            if(_pCommPlayerWork->pKeepFlag[_KEEP_FLAG_MAX-1]){
                sys_FreeMemoryEz(_pCommPlayerWork->pKeepFlag[_KEEP_FLAG_MAX-1]);
            }
            for(i = _KEEP_FLAG_MAX - 1; i >= 1; i--){
                _pCommPlayerWork->pKeepFlag[i] = _pCommPlayerWork->pKeepFlag[i-1];
            }
            _pCommPlayerWork->pKeepFlag[0] = _pCommPlayerWork->pNowFlag[netID];
            UnderGroundAddFlag(SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommPlayerWork->pFSys)),
                               _pCommPlayerWork->pNowFlag[netID]);
            _pCommPlayerWork->pNowFlag[netID] = NULL;
            _pCommPlayerWork->sendFlagData[netID].netID = INVALID_NETID;
        }
    }
    else{
        CommPlayerDeleteFlagData(netID);
    }
}

//--------------------------------------------------------------
/**
 * 旗を持っているかどうか
 * @param	netID   playerID
 * @retval	持っていたらTRUE
 */
//--------------------------------------------------------------
BOOL CommPlayerIsFlagData(int netID)
{
    if(_pCommPlayerWork->pNowFlag[netID] != NULL){
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   相手のパソコンから旗を取る
 * @param   myNetID   旗をとる人
 * @param   targetID  旗をとられる人
 * @retval  none
 */
//--------------------------------------------------------------

BOOL CommPlayerGetFlag(int myNetID, int targetNetID)
{
    if(_pCommPlayerWork->pNowFlag[myNetID] == NULL){
        MYSTATUS* pTargetStatus = CommInfoGetMyStatus(targetNetID);
        if(pTargetStatus){
            _pCommPlayerWork->pNowFlag[myNetID] = MyStatus_AllocWork(HEAPID_COMMUNICATION);
            MyStatus_Copy(pTargetStatus, _pCommPlayerWork->pNowFlag[myNetID]);
            _pCommPlayerWork->hedFE[myNetID] = _HFE_FLAG;
            OHNO_PRINT("はたtor %d\n",myNetID);
            _pCommPlayerWork->sendFlagData[myNetID].netID = myNetID;
            MyStatus_Copy(pTargetStatus, (MYSTATUS*)&_pCommPlayerWork->sendFlagData[myNetID].mystatus);
            if(targetNetID == CommGetCurrentID()){
                SB_RECORD_DATA* pSBD = SaveData_GetSecretBaseRecord(_pCommPlayerWork->pFSys->savedata);
                SecretBaseRecordSetFlagStealNum(pSBD);  // とられた
            }
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   相手の頭から旗を取る
 * @param   myNetID   旗をとる人
 * @param   targetID  旗をとられる人
 * @retval  とったらTRUE
 */
//--------------------------------------------------------------

static BOOL _getHeadFlag(int myNetID, int targetNetID)
{
    if((_pCommPlayerWork->pNowFlag[myNetID] == NULL) &&
       (_pCommPlayerWork->pNowFlag[targetNetID] != NULL)){
        _pCommPlayerWork->pNowFlag[myNetID] = _pCommPlayerWork->pNowFlag[targetNetID];
        _pCommPlayerWork->pNowFlag[targetNetID] = NULL;
        _pCommPlayerWork->hedFE[myNetID] = _HFE_FLAG;
        _pCommPlayerWork->hedFE[targetNetID] = _HFE_NONE;
        OHNO_PRINT("はたとり\n");
        _pCommPlayerWork->sendFlagData[myNetID].netID = myNetID;
        _pCommPlayerWork->sendFlagData[targetNetID].netID = INVALID_NETID;
        MyStatus_Copy(_pCommPlayerWork->pNowFlag[myNetID], (MYSTATUS*)&_pCommPlayerWork->sendFlagData[myNetID].mystatus);
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   指定の人に旗を出す
 * @param   netID        旗がつく人
 * @retval  none
 */
//--------------------------------------------------------------

static void _setFlagDisp(int netID)
{
    if(!_pCommPlayerWork->bResetting){
        if(_pCommPlayerWork->pPlayer[netID]){
            switch(_pCommPlayerWork->hedFE[netID]){
              case _HFE_OK:
                if(_pCommPlayerWork->pMark[netID]==NULL){
                    _pCommPlayerWork->pMark[netID] = FE_Ok_Add( Player_FieldOBJGet(_pCommPlayerWork->pPlayer[netID]) );
                }
                _pCommPlayerWork->hedFE[netID] = _HFE_NONE;
                break;
              case _HFE_EXCLAMATION:
                if(_pCommPlayerWork->pMark[netID]==NULL){
                    _pCommPlayerWork->pMark[netID] =
                        FE_Exclamation_Add( Player_FieldOBJGet(_pCommPlayerWork->pPlayer[netID]) );
                }
                break;
              case _HFE_FLAG:
                if(_pCommPlayerWork->pMark[netID]==NULL){
                    _pCommPlayerWork->pMark[netID] =
                        FE_Flag_Add( Player_FieldOBJGet(_pCommPlayerWork->pPlayer[netID]) );
                }
                break;
              case _HFE_NONE:
                _markDelete(netID);
                break;
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   指定の人にびっくりマークを出す
 * @param   netID        びっくりマークがつく人
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetFEExclamationAdd(int netID)
{
    OHNO_PRINT("びっくりマークを出す\n");
    if(_pCommPlayerWork->hedFE[ netID ] != _HFE_FLAG){
        _pCommPlayerWork->hedFE[ netID ] = _HFE_EXCLAMATION;
    }
}

//--------------------------------------------------------------
/**
 * @brief   指定の人にOKマークを出す
 * @param   netID        びっくりマークがつく人
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetFEOkAdd(int netID)
{
    if(_pCommPlayerWork->hedFE[ netID ] != _HFE_FLAG){
        _pCommPlayerWork->hedFE[ netID ] = _HFE_OK;
    }
    _markDelete(netID);
}

//--------------------------------------------------------------
/**
 * @brief   指定の人にマークを消す
 * @param   netID        けす人
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetFENoneAdd(int netID)
{
    if(_pCommPlayerWork->hedFE[ netID ] != _HFE_FLAG){
        _pCommPlayerWork->hedFE[ netID ] = _HFE_NONE;
    }
    _markDelete(netID);
}

//--------------------------------------------------------------
/**
 * @brief   旗に関する状態をサーバーから返す場合のコマンドサイズ
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

typedef struct{
    u8 state;
    u8 myNetID;
    u8 targetID;
} _flagStateCallBack;

int CommPlayerRecvFlagStateServerRetGetSize(void)
{
    return sizeof(_flagStateCallBack);
}

//--------------------------------------------------------------
/**
 * @brief   旗に関する状態がサーバーに届いた  CF_FLAG_STATE
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerRecvFlagState(int netID, int size, void* pData, void* pWork)
{
    u8* pState = pData;
    _flagStateCallBack ret;

    ret.myNetID = netID;
    switch(pState[0]){
      case UNDER_FLAG_DEL:
        ret.state = UNDER_FLAG_DEL;
        CommSendFixSizeData_ServerSide(CF_FLAG_STATE_RET,&ret);  // 旗を消す為にクライアントに送信
//        CommPlayerSetMoveControl_Server(netID,FALSE);
        break;
      case UNDER_FLAG_DELIVERY:
        ret.state = UNDER_FLAG_DELIVERY;
        CommSendFixSizeData_ServerSide(CF_FLAG_STATE_RET,&ret);  // 旗を消す為にクライアントに送信
        CommPlayerSetMoveControl_Server(netID,FALSE);
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   旗に関する状態がサーバーに届いた  CF_PLAYER_FREEZE_END
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

//void CommPlayerRecvFreezeEnd(int netID, int size, void* pData, void* pWork)

static void _commPlayerFreeze(int num)
{
//    u8* pBuff = pData;

    CommPlayerSetFENoneAdd(CommGetCurrentID()); // ！けし
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderFlag());
    CommPlayerHoldBitEnd(_HOLD_FLAG_STOLEN);
}


//--------------------------------------------------------------
/**
 * @brief   ハタを取られたので一秒以上固まる
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

static void _freezePlayer(TCB_PTR tcb, void* work)
{
    _FREEZE_PLAYER* pFreeze = work;
    u8 id = pFreeze->targetID;
    u8 bEnd = FALSE;

    if(!CommIsConnect(id)){
        sys_FreeMemoryEz(pFreeze);
        TCB_Delete(tcb);
        return;
    }
    else{
        pFreeze->timer++;
        if(pFreeze->timer > 60){
            bEnd = TRUE;
        }
    }
    if(bEnd){
        _pCommPlayerWork->bMoveControlFlag[ id ]=TRUE;
        sys_FreeMemoryEz(pFreeze);
        TCB_Delete(tcb);
    }
}

//--------------------------------------------------------------
/**
 * @brief   ハタを取られたので一秒以上固まる
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

static void _freezeConditionStart(int targetID)
{
    _FREEZE_PLAYER* pFreeze = sys_AllocMemory(HEAPID_WORLD, sizeof(_FREEZE_PLAYER));
    pFreeze->timer = 0;
    pFreeze->targetID = targetID;
    _pCommPlayerWork->bMoveControlFlag[ targetID ] = FALSE;
    TCB_Add(_freezePlayer, pFreeze, TCB_PRIORITY_NORMAL);
    CommPlayerSetMoveControl_Server(targetID,FALSE);
    
}

//--------------------------------------------------------------
/**
 * @brief   旗を持っている人との検査
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

BOOL CommPlayerFlagTalkCheck(int netID, int targetID, BOOL bNPCTalk)
{
    _flagStateCallBack ret;

    if(bNPCTalk & 0x01){
        ret.state = UNDER_FLAG_NOTALK;
    }
    else if(CommPlayerIsFlagData(netID)){ // 自分が旗を持っている場合はこれ
        ret.state = UNDER_FLAG_NOTALK;
    }
    else{
        if(targetID == COMM_INVALID_ID){
            return FALSE;
        }
        else if(!CommPlayerIsFlagData(targetID)){ // 相手が旗を持ってない
            return FALSE;
        }
        else{
            ret.state = UNDER_FLAG_RIP_OFF;
            _freezeConditionStart(targetID);
        }
    }
    ret.myNetID = netID;
    ret.targetID = targetID;
    CommPlayerSetMoveControl_Server(netID,FALSE);
    CommSendFixSizeData_ServerSide(CF_FLAG_STATE_RET,&ret);  // クライアントに送信
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ほれるかどうか  旗持ってたらほれない
 * @param   id     人
 * @retval  通信を返したらTRUE
 */
//--------------------------------------------------------------

BOOL CommPlayerFlagDigCheck(int netID)
{
    _flagStateCallBack ret;

    if(CommPlayerIsFlagData(netID)){ // 自分が旗を持っている場合はこれ
        ret.state = UNDER_FLAG_NODIG;
    }
    else{
        return FALSE;
    }
    ret.myNetID = netID;
    CommSendFixSizeData_ServerSide(CF_FLAG_STATE_RET,&ret);  // クライアントに送信
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ハタを盗まれた人の処理  
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

static void _stolenFlagPlayerFunc(_flagStateCallBack* pRet, BOOL bGet, SB_RECORD_DATA* pSBD)
{
    UgMgrForceExitNowTCB();
#if T1656_060815_FIX
    CommPlayerSetMoveControl(FALSE);  // サーバーに送信
#endif  //T1656_060815_FIX
    CommPlayerHoldBit(_HOLD_FLAG_STOLEN);
    CommMsgRegisterTargetName(CommUnderGetMsgUnderFlag(),CommInfoGetMyStatus(pRet->myNetID));
    if(bGet){
        _pCommPlayerWork->hedFE[CommGetCurrentID()] = _HFE_NONE;
        CommPlayerSetFENoneAdd(CommGetCurrentID()); // 旗消し
        CommPlayerSetFEExclamationAdd(CommGetCurrentID()); //!
        CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),  // 奪われた
                               mes_uw_flag_15, TRUE, _commPlayerFreeze);
    }
    else{
        CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),  // 奪われた
                               mes_uw_flag_16, TRUE, _commPlayerFreeze);
    }
    Snd_FadeOutNextPlaySet(SND_SCENE_FIELD,SEQ_TANKOU,BGM_FADE_TANKOU_TIME,0,0xff,NULL);
    Snd_SePlay(UG_SE_FLAG_STEAL);
}


//--------------------------------------------------------------
/**
 * @brief   旗に関する状態がクライアントに届いた  CF_FLAG_STATE_RET
 * @param   通信コールバック
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerRecvFlagStateServerRet(int netID, int size, void* pData, void* pWork)
{
    _flagStateCallBack* pRet = pData;
    BOOL bDeliv;
    int point = 0;
    SB_RECORD_DATA* pSBD = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommPlayerWork->pFSys));

    switch(pRet->state){
      case UNDER_FLAG_DEL:
        if(_pCommPlayerWork->pNowFlag[pRet->myNetID]){ // 自分のハタがある場合
            CommPlayerDeleteFlagData(pRet->myNetID);
            CommPlayerSetFENoneAdd(pRet->myNetID);
            if(pRet->myNetID == CommGetCurrentID()){
                CommPlayerHold();
                CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                       mes_uw_flag_07, TRUE, _msgEndCallBackDel);
                Snd_FadeOutNextPlaySet(SND_SCENE_FIELD,SEQ_TANKOU,BGM_FADE_TANKOU_TIME,0,0xff,NULL);
            }
        }
        OHNO_PRINT("はた捨てた\n");
        break;
      case UNDER_FLAG_RIP_OFF:  // 奪い合い
        // クライアント管理なので自分が持ってたら取れたことにする
        if(CommInfoGetMyStatus(pRet->myNetID)==NULL){
            //奪った人がいない場合  相手のハタだけ消して完了
            CommPlayerDeleteFlagData(pRet->targetID);
            OHNO_PRINT("奪い合いけしておわり\n");
            return;
        }
        if(_pCommPlayerWork->pNowFlag[pRet->targetID]==NULL){ // 相手のハタが無い場合
            // 終了
            if(pRet->myNetID==CommGetCurrentID()){
                CommPlayerHoldEnd();
            }
            OHNO_PRINT("はたない\n");
            return;
        }
        if(MyStatus_Compare(_pCommPlayerWork->pNowFlag[pRet->targetID],
                            CommInfoGetMyStatus(pRet->myNetID)) == TRUE){  // 実は自分の旗だった
            // 相手の旗を消す
            CommPlayerDeleteFlagData(pRet->targetID);
            if(pRet->myNetID == CommGetCurrentID()){
                SecretBaseRecordSetFlagReverseNum(pSBD);   // 奪った旗を取り戻した
                CommPlayerHold();
                CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),  // とりもどした
                                              mes_uw_flag_18, TRUE, _msgEndCallBack);
                Snd_SePlay(UG_SE_FLAG_CONQUER);
            }
            else if(pRet->targetID == CommGetCurrentID()){
                _stolenFlagPlayerFunc(pRet, FALSE, pSBD); // 取られた側
            }
            UgSecretBaseSetFlagReverseLog(pRet->myNetID);//とりもどした
        }
        else if(_getHeadFlag(pRet->myNetID,pRet->targetID)){  // ハタを取れた
            if(pRet->myNetID == CommGetCurrentID()){
                SecretBaseRecordSetFlagConquerNum(pSBD);  // 奪った
                CommPlayerHoldBit(_HOLD_FLAG_RIP_OFF);
                CommMsgRegisterTargetName(CommUnderGetMsgUnderFlag(),CommInfoGetMyStatus(pRet->targetID));
                CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),  // 奪った
                                              mes_uw_flag_17, TRUE, _msgEndCallBackRipOff);
                Snd_BgmPlay( SEQ_HATANIGE );
                Snd_SePlay(UG_SE_FLAG_CONQUER);
            }
            else if(pRet->targetID == CommGetCurrentID()){
                _stolenFlagPlayerFunc(pRet, TRUE, pSBD); // 取られた側
            }
            OHNO_PRINT("奪った\n");
            UgSecretBaseSetFlagConquerLog(pRet->myNetID, pRet->targetID);//うばった
        }
        break;
      case UNDER_FLAG_NOTALK:
        if(pRet->myNetID == CommGetCurrentID()){
            CommPlayerHoldBit(_HOLD_FLAG_NO_TALK);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                   mes_uw_flag_11, TRUE, _msgEndCallBackNoTalk);
            //UgMgrSetNowTCB();//
        }
        break;
      case UNDER_FLAG_NODIG:
        if(pRet->myNetID == CommGetCurrentID()){
            CommPlayerHoldBit(_HOLD_FLAG_NO_DIG);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                   mes_uw_flag_10, TRUE, _msgEndCallBackNoDig);
        }
        break;
      case UNDER_FLAG_DELIVERY:
        _pCommPlayerWork->hedFE[pRet->myNetID] = _HFE_NONE;
        CommPlayerSetFENoneAdd(pRet->myNetID); // 旗消し

        if(pRet->myNetID == CommGetCurrentID()){  // 表示
            SB_RECORD_DATA* pSBD = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommPlayerWork->pFSys));
            u8 type = SecretBaseRecordGetFlagType(pSBD);
            SecretBaseRecordSetFlagDeliveryNum(pSBD);  // 運んだ
            SysFlag_UgHataSet(SaveData_GetEventWork(_pCommPlayerWork->pFSys->savedata)); // 運んだ
            if(_pCommPlayerWork->pNowFlag[pRet->myNetID]){            // ハタを運ぶたびに呼ばれる
                TVTOPIC_Entry_Watch_GetFlag(_pCommPlayerWork->pFSys,_pCommPlayerWork->pNowFlag[pRet->myNetID]);
                if(_pCommPlayerWork->myDeliveryFlagNum!=0xffff){
                    _pCommPlayerWork->myDeliveryFlagNum++;
                }
            }
            CommPlayerHold();
            Snd_SePlay(UG_SE_FLAG_DELIVERY);
            if(type == SecretBaseRecordGetFlagType(pSBD)){  // ハタ同じだった
                CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                       mes_uw_flag_12, TRUE, _msgEndCallBack);
            }
            else{
                CommSendFixSizeData(CF_LVUP_FLAG, &type);  // LVUP演出
            }
            Snd_FadeOutNextPlaySet(SND_SCENE_FIELD,SEQ_TANKOU,BGM_FADE_TANKOU_TIME,0,0xff,NULL);
        }
        if(_pCommPlayerWork->pNowFlag[pRet->myNetID]){
            if(MyStatus_Compare(_pCommPlayerWork->pNowFlag[pRet->myNetID],
                                CommInfoGetMyStatus(CommGetCurrentID())) == TRUE){  // 実は自分の旗だった
                TVTOPIC_Entry_Watch_LoseFlag(_pCommPlayerWork->pFSys,CommInfoGetMyStatus(pRet->myNetID));
            }
        }
        _commPlayerDeliveryFlagData(pRet->myNetID);  // 記録
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   今の方向と反対の方向を返す
 * @param   dir 方向
 * @retval  反対の方向
 */
//--------------------------------------------------------------

int CommPlayerGetReverseDir(int dir)
{
    if(dir == DIR_UP){
        return DIR_DOWN;
    }
    else if(dir == DIR_DOWN){
        return DIR_UP;
    }
    else if(dir == DIR_LEFT){
        return DIR_RIGHT;
    }
    else if(dir == DIR_RIGHT){
        return DIR_LEFT;
    }
    GF_ASSERT(0 && "NOT DIR CODE");
    return DIR_LEFT;
}


//--------------------------------------------------------------
/**
 * @brief   こんらん・はんてんが続く時間タイマーセット
 * @param   netID   ID
 * @param   count   カウント
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetGiddyStep(int netID,int count)
{
    _pCommPlayerWork->giddyCounter[netID] = count;
    _pCommPlayerWork->walkCount[netID] = 15;
}

//--------------------------------------------------------------
/**
 * @brief   こんらん・はんてんが続く時間タイマーを強制終了
 * @param   netID   ID
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerResetGiddyStep(int netID)
{
    _pCommPlayerWork->giddyCounter[netID] = 0;
}

//--------------------------------------------------------------
/**
 * @brief   あな用　　方向のみ許可フラグのセット
 * @param   netID   ID
 * @param   count   カウント
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetHole(int netID,int count)
{
    OHNO_SP_PRINT("CommPlayerSetHole %d %d\n",netID,count);
    _pCommPlayerWork->countHole[netID] = count;
    _pCommPlayerWork->walkCount[netID] = 15;
}

//--------------------------------------------------------------
/**
 * @brief   あな用　　方向のみ許可フラグのリセット
 * @param   netID   ID
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerResetHole(int netID)
{
    _pCommPlayerWork->countHole[netID] = 0;
}

//--------------------------------------------------------------
/**
 * @brief   WalkCountをかえす  止まってるのか動いているのかに使用
 * @param   netID   ID
 * @retval  WalkCount
 */
//--------------------------------------------------------------

int CommPlayerGetWalkCount(int netID)
{
    return _pCommPlayerWork->walkCountClient[netID];
}

//--------------------------------------------------------------
/**
 * @brief   WalkCountをかえす  止まってるのか動いているのかに使用
 * @param   netID   ID
 * @retval  WalkCount
 */
//--------------------------------------------------------------

int CommPlayerGetWalkCountServer(int netID)
{
    return _pCommPlayerWork->walkCount[netID];
}


//--------------------------------------------------------------
/**
 * @brief   WalkCountを入れる  一時停止に使う
 * @param   netID   ID
 * @retval  WalkCount
 */
//--------------------------------------------------------------

void CommPlayerSetWalkCount(void)
{
    if(_pCommPlayerWork){
        if(!_pCommPlayerWork->bUnder){
            _pCommPlayerWork->walkCountClient[CommGetCurrentID()] = 112;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   通信した上でプレーヤーの方向を変更する
 * @param   int dir
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetDir(int dir)
{
    Player_DirSet(_pCommPlayerWork->pFSys->player, dir);
    _pCommPlayerWork->sPlayerPlace[ CommGetCurrentID() ].dir = dir;
    CommPlayerSendPos(FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   見た目のプレーヤーの方向を変更する
 * @param   int netID
 * @param   int dir
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerSetClientDir(int netID, int dir)
{
    _pCommPlayerWork->sPlayerPlace[netID].dir = dir;
    Player_DirSet(_pCommPlayerWork->pPlayer[netID], dir);
}

//--------------------------------------------------------------
/**
 * @brief   見た目のプレーヤーの方向を得る
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

int CommPlayerGetClientDir(int netID)
{
    if(!_pCommPlayerWork->pPlayer[netID]){
        return DIR_NOT;
    }
    return Player_DirGet(_pCommPlayerWork->pPlayer[netID]);
}

//--------------------------------------------------------------
/**
 * @brief   動きを止める
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

void CommPlayerHoldBit(int bit)
{
    if(_HOLD_ALL != bit){
        _pCommPlayerWork->holdBit |= bit;
    }
    FieldSystemProc_SeqHold();
    _pCommPlayerWork->bMyMoveControl = FALSE; // 自機の設定のみ　送信しない
}

//--------------------------------------------------------------
/**
 * @brief   見た目のプレーヤーの方向を得る
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------


void CommPlayerHoldBitEnd(int bit)
{
    if(_HOLD_ALL != bit){
        _pCommPlayerWork->holdBit &= ~(bit);
    }
    OHNO_PRINT("bitend %x\n",_pCommPlayerWork->holdBit);

    if(_pCommPlayerWork->holdBit == _HOLD_TRAP){  // トラップのみにかかっている
        u8 bTRUE = TRUE;
        OHNO_PRINT("サーバー解除のみ送信\n");
        CommSendFixSizeData(CF_MOVE_CONTROL,&bTRUE);   // サーバー解除のみ送信する
    }
    if(_pCommPlayerWork->holdBit == 0){
        if(_HOLD_TRAP != bit){
            FieldSystemProc_SeqHoldEnd();
            OHNO_PRINT("----CommPlayerHoldBitEnd- %d--\n",bit);
            CommPlayerSetMoveControl(TRUE);  // 自機の移動状態を設定
        }
        else{  // トラップ解除時にはフラグ解除をサーバーには送らない
            FieldSystemProc_SeqHoldEnd();
            _pCommPlayerWork->bMyMoveControl = TRUE;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   動きを止める
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

void CommPlayerHoldBitOff(void)
{
    _pCommPlayerWork->holdBit = 0;
}

//--------------------------------------------------------------
/**
 * @brief   動きを止める
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

void CommPlayerHold(void)
{
    FieldSystemProc_SeqHold();
    _pCommPlayerWork->bMyMoveControl = FALSE; // 自機の設定のみ　送信しない
}

//--------------------------------------------------------------
/**
 * @brief   動きを止める
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

void CommPlayerHold_Control(void)
{
    _pCommPlayerWork->bMyMoveControl = FALSE; // 自機の設定のみ　送信しない
}

//--------------------------------------------------------------
/**
 * @brief   見た目のプレーヤーの方向を得る
 * @param   int netID
 * @retval  dir
 */
//--------------------------------------------------------------

void CommPlayerHoldEnd(void)
{
    OHNO_PRINT("CommPlayerHoldEnd\n");
    FieldSystemProc_SeqHoldEnd();
    CommPlayerSetMoveControl(TRUE);  // 自機の移動状態を設定
}

//--------------------------------------------------------------
/**
 * @brief   最初のコントロールを許可する
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerFirstMoveEnable(void)
{
    if(_pCommPlayerWork->bFirstMoveEnable == FALSE){
        if(!_pCommPlayerWork->bUnder){
            CommPlayerHoldEnd();
            _pCommPlayerWork->bFirstMoveEnable = TRUE;
        }
        else if(UgMgrIsFirstMoveControlEnable(CommGetCurrentID())){
            CommPlayerHoldEnd();
            _pCommPlayerWork->bFirstMoveEnable = TRUE;
        }
        else{
//            CommPlayerSetMoveControl(FALSE); // 接続禁止
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   最初のコントロールを禁止
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerFirstMoveDisable(void)
{
    if(_pCommPlayerWork->bFirstMoveEnable == FALSE){
        if(_pCommPlayerWork->bUnder){
            if(!UgMgrIsFirstMoveControlEnable(CommGetCurrentID())){
                CommPlayerSetMoveControl(FALSE); // 接続禁止
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   メニューを閉じた際にプレーヤー見た目位置を設定する
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerSetForcePos(void)
{
    int i,x,z,dir;
    FIELD_OBJ_PTR pFOBJ;
    
    if(!_pCommPlayerWork){
        return;
    }
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommPlayerWork->pPlayer[i] == NULL){
            continue;
        }
        if(CommGetCurrentID()==i){
            continue;
        }
        pFOBJ = Player_FieldOBJGet(_pCommPlayerWork->pPlayer[i]);
        x = _pCommPlayerWork->sPlayerPlace[i].xpos;
        z = _pCommPlayerWork->sPlayerPlace[i].zpos;
        dir = _pCommPlayerWork->sPlayerPlace[i].dir;
        OHNO_PRINT("位置を再設定 %d = %d %d\n",i,x,z);
        FieldOBJ_NowPosGX_Set(pFOBJ, x);
        FieldOBJ_NowPosGZ_Set(pFOBJ, z);
        FieldOBJ_GPosDirInit(pFOBJ,x,0,z,dir);
    }
}

//--------------------------------------------------------------
/**
 * @brief   誰のMYSTATUSなのか返す
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

static int _getWhoMyStatus(MYSTATUS* pMy)
{
    int i;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(_pCommPlayerWork->bActive[i]){
            if(MyStatus_Compare(pMy, CommInfoGetMyStatus(i))){
                return i;
            }
        }
    }
    return INVALID_NETID;
}

//--------------------------------------------------------------
/**
 * @brief   親機側のハタプールデータを消す
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerParentFlagDataReset(void)
{
    int i;
    
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCommPlayerWork->sendFlagData[i].netID = INVALID_NETID;
    }
}

//--------------------------------------------------------------
/**
 * @brief   現状のハタデータ送信
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerNowFlagSend(void)
{
    _pCommPlayerWork->bFlagDataRecv = FALSE;
    if(_pCommPlayerWork->pNowFlag[CommGetCurrentID()]){
        CommSendFixSizeData(CF_FLAG_NOWARRAY_REQ, _pCommPlayerWork->pNowFlag[CommGetCurrentID()]); //ハタ情報更新
    }
    else{
        MYSTATUS* pMy = MyStatus_AllocWork(HEAPID_COMMUNICATION);
        STRBUF* pBuf = STRBUF_Create(20,HEAPID_COMMUNICATION);
        GF_ASSERT(pMy);
        GF_ASSERT(pBuf);
        MyStatus_SetMyNameFromString(pMy,pBuf);
        CommSendFixSizeData(CF_FLAG_NOWARRAY_REQ, pMy); //ハタ情報更新
        STRBUF_Delete(pBuf);
        sys_FreeMemoryEz(pMy);
    }
}

//--------------------------------------------------------------
/**
 * @brief   現状のハタデータサイズをえる
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

int CommPlayerNowFlagSize(void)
{
    return COMM_SEND_MYSTATUS_SIZE;
}

//--------------------------------------------------------------
/**
 * @brief   現状のハタデータを全員に送る
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerRecvNowFlagDataReq(int netID, int size, void* pData, void* pWork)
{
    int i;
    const MYSTATUS* pMyStatus = pData;
    STRBUF* pStrBuf;
    u8 id = netID;

    OHNO_PRINT("size %d\n",size);
    

    if(_pCommPlayerWork){
        MyStatus_Copy(pMyStatus, (MYSTATUS*)_pCommPlayerWork->sendFlagData[netID].mystatus);

        pStrBuf = MyStatus_CreateNameString(pMyStatus, HEAPID_COMMUNICATION);
        if(STRBUF_GetLen(pStrBuf)!=0){  // 名前があれば正しいデータ
            _pCommPlayerWork->sendFlagData[netID].netID = netID;
        }
        for(i = 0; i < COMM_MACHINE_MAX;i++){
            OHNO_PRINT("旗検査 %d\n", _pCommPlayerWork->sendFlagData[i].netID);
            if(_pCommPlayerWork->sendFlagData[i].netID != INVALID_NETID){


                _pCommPlayerWork->sendFlagData[i].netID = i;
                CommSendHugeData_ServerSide(CF_FLAG_NOWARRAY,
                                            &_pCommPlayerWork->sendFlagData[i],
                                            sizeof(_SEND_FLAG));
            }
        }
        CommSendData_ServerSide(CF_FLAG_NOWARRAY_END, &id,1);
        STRBUF_Delete(pStrBuf);
        _pCommPlayerWork->bDataSendFlag = TRUE;
    }
    else{
        GF_ASSERT(0);
    }
}

//--------------------------------------------------------------
/**
 * @brief   ハタを受け取るバッファ
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

u8* CommPlayerGetFlagRecvBuff( int netID, void* pWork, int size)
{
    return (u8*)&_pCommPlayerWork->sendFlagData[COMM_MACHINE_MAX];
}

//--------------------------------------------------------------
/**
 * @brief   現状のハタデータが到着
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommPlayerRecvNowFlagDataArray(int netID, int size, void* pData, void* pWork)
{
    _SEND_FLAG* pBuff = pData;
    int i,id;

    if(_pCommPlayerWork){
        id = pBuff->netID;
        if(_pCommPlayerWork->pNowFlag[id]){
            sys_FreeMemoryEz(_pCommPlayerWork->pNowFlag[id]);
        }
        _pCommPlayerWork->pNowFlag[id] = MyStatus_AllocWork(HEAPID_COMMUNICATION);
        MyStatus_Copy((MYSTATUS*)pBuff->mystatus, _pCommPlayerWork->pNowFlag[id]);

        _pCommPlayerWork->hedFE[id] = _HFE_FLAG;
    }
}

//--------------------------------------------------------------
/**
 * @brief   現状のハタデータサイズ
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

int CommPlayerNowFlagDataArraySize(void)
{
    return sizeof(_SEND_FLAG);
}


void CommPlayerRecvNowFlagDataEnd(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    OHNO_PRINT("CommPlayerRecvNowFlagDataEndコマンド受信 %d\n",pBuff[0]);
    if(pBuff[0] == CommGetCurrentID()){
        _pCommPlayerWork->bFlagDataRecv = TRUE;
    }
    _pCommPlayerWork->bDataSendFlag = FALSE;
}


BOOL CommPlayerIsNowFlagDataEnd(void)
{
    return _pCommPlayerWork->bFlagDataRecv;
}

//--------------------------------------------------------------
/**
 * @brief   角度調整を可能にする
 * @param   xpos  場所
 * @param   zpos
 * @retval  playerのnetID
 */
//--------------------------------------------------------------

void CommSetForceDir(void)
{
    _pCommPlayerWork->forceDirFlg = 8;
}

//--------------------------------------------------------------
/**
 * @brief   子機として持っていた旗を親機（ソロ）に繋ぐ
 *          自分の以外は抹消
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommPlayerFlagChange(void)
{
    MYSTATUS* pMy = NULL;
    int i,j;
    int id = CommGetCurrentID();

    // 旗を持ってたら置いておく
    if(_pCommPlayerWork->pNowFlag[id]){
        OHNO_PRINT("自分が旗を持っている\n");
        pMy = _pCommPlayerWork->pNowFlag[id];
        _pCommPlayerWork->pNowFlag[id] = NULL;
        _pCommPlayerWork->hedFE[id] = _HFE_NONE;
        _pCommPlayerWork->sendFlagData[id].netID = INVALID_NETID;
    }
    // 全部消す
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        CommPlayerDeleteFlagData(i);
    }
    if(pMy){
        OHNO_PRINT("切断　ハタ譲渡\n");
        _pCommPlayerWork->pNowFlag[COMM_PARENT_ID] = pMy;
        _pCommPlayerWork->hedFE[COMM_PARENT_ID] = _HFE_FLAG;
        MyStatus_Copy(pMy, (MYSTATUS*)&_pCommPlayerWork->sendFlagData[COMM_PARENT_ID].mystatus);
        _pCommPlayerWork->sendFlagData[COMM_PARENT_ID].netID = COMM_PARENT_ID;
    }
}

