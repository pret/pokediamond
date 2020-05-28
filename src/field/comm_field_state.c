//=============================================================================
/**
 * @file	comm_field_state.c
 * @brief	通信状態を管理するサービス  通信の上位にある
 *          スレッドのひとつとして働き、自分の通信状態や他の機器の
 *          開始や終了を管理する
 *          フィールド上で直接管理したいのでcommunicationからfieldに移動 2005.09.28
 * @author	Katsumi Ohno
 * @date    2005.08.02
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "system/gamedata.h"
#include "system/pm_str.h"

#include "comm_field_state.h"
#include "underground/ug_manager.h"
#include "field/field.h"
#include "fieldsys.h"
#include "comm_command_field.h"
#include "comm_direct_counter.h"
#include "comm_vsroom.h"
#include "sysflag.h"

#include "script.h"							//StartFieldScript
#include "..\fielddata\script\common_scr_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\connect_def.h"		//SCRID_CONNECT_COLOSSEUM
#include "../fielddata/script/battle_room_def.h"
#include "savedata/trainercard_data.h"
#include "application/trainer_card.h"
#include "tr_card_setup.h"
#include "system/wipe.h"
#include "system/pm_overlay.h"
#include "system/brightness.h"

#include "field/union_beacon_tool.h"
#include "field_encount.h"

#ifdef PM_DEBUG
#include "d_ohno.h"
#include "fld_debug.h"
#endif
//==============================================================================
//	型宣言
//==============================================================================
// コールバック関数の書式
typedef void (*PTRStateFunc)(void);

#define _TRAINER_CARD_NUM_MAX (4)

//==============================================================================
// ワーク
//==============================================================================

typedef struct{
    TR_CARD_DATA* pTRCard[_TRAINER_CARD_NUM_MAX];  // トレーナーカードを受信するバッファのポインタ
    u8 bTRCard[_TRAINER_CARD_NUM_MAX];
    COMM_MESSAGE* pCMess;
    FIELDSYS_WORK* pFSys;
    MATHRandContext32 sRand; ///< 親子機ネゴシエーション用乱数キー
    PTRStateFunc state;
    TCB_PTR pTcb;
    u16 timer;
    u8 connectIndex;   // 子機が接続する親機のindex番号
    u8 bStalth;
    u8 bStateNoChange;
    u8 bUGOverlay;
    u8 bReturnBattle; // バトルから戻ってきた場合は１ 入ってきた場合は０
    u8 bBattleMoveRoom; // 開始位置についたことを受信

    POKEPARTY*  party;	// ミックスバトル用パーティ

#ifdef PM_DEBUG		// Debug ROM
    u16 debugTimer;
#endif
} _COMM_FSTATE_WORK;

static _COMM_FSTATE_WORK* _pCommFState = NULL;  ///<　ワーク構造体のポインタ

//==============================================================================
// 定義
//==============================================================================
#define _START_TIME (50)     // 開始時間
#define _CHILD_P_SEARCH_TIME (12) ///子機として親を探す時間
#define _PARENT_WAIT_TIME (40) ///親としてのんびり待つ時間
#define _FINALIZE_TIME (2)
#define _EXIT_SENDING_TIME (5)
#define _PARENT_END_TIME (2)
#define _SEND_NAME_TIME (10)
#define _PARENTSCAN_PA (3)  // 親機として検索する確立は1/3

#define _TCB_COMMCHECK_PRT   (10)    ///< フィールドを歩く通信の監視ルーチンのPRI


//==============================================================================
// static宣言
//==============================================================================

// ステートの初期化

static void _commStateInitialize(FIELDSYS_WORK* pFSys);  // 初期化
static void _commCheckFunc(TCB_PTR tcb, void* work);  // ステートを実行しているタスク
static void _changeState(PTRStateFunc state, int time);  // ステートを変更する
static void _changeStateDebug(PTRStateFunc state, int time, int line);  // ステートを変更する

#ifdef PM_DEBUG
#if 1
#define   _CHANGE_STATE(state, time)  _changeStateDebug(state, time, __LINE__)
#else
#define   _CHANGE_STATE(state, time)  _changeState(state, time)
#endif
#else  //PM_DEBUG
#define   _CHANGE_STATE(state, time)  _changeState(state, time)
#endif //PM_DEBUG


// 地下関連ステート
static void _underStart(void);           // 初期化 + システムの初期化
static void _underOpenning(void);       //イベント中
static void _underConnecttingAloneSend(void);  // 初期化転送完了
static void _underConnectting(void);     // 接続中
static void _underChildConnecting(void);   // 子機が親機に接続中
static void _underChildConnectInfoWait(void);  // 子機として接続中 info収集
static void _underChildConnectFlagWait(void);
static void _underChildConnectSecret(void);    // 子機として接続中
static void _underChildConnectDig(void);    // 子機として接続中
static void _underChildConnect(void);    // 子機として接続中
static void _underChildConnect_JumpFieldStart(void);    // 子機として接続中 Jump開始
static void _underChildConnect_JumpField(void);    // 子機として接続中 Jump中
static void _underChildConnect_JumpFieldEnd(void);    // 子機として接続中 Jumpおわり
static void _underParentRestart(void);
#if T1645_060815_FIX
static void _underParentRestartAloneWait(void);
#endif //T1645_060815_FIX
static void _underChildRestart(void);
static void _underChildRestart_Base(void);
static void _underChildStalth(void);

static void _underParentWait(void);      // 親機として待機状態
static void _underParentConnect(void);   // 親機として接続中
static void _underParentConnect_JumpFieldStart(void);  // 親機として接続中 Jump開始
static void _underParentConnect_JumpField(void);  // 親機として接続中 Jump中
static void _underParentConnect_JumpFieldEnd(void);  // 親機として接続中 Jump終わり
static void _stateUnderGroundConnectEnd(void);  // 地下切断

static void _underSoloConnect_JumpFieldStart(void);    // solo機として接続中 Jump開始
static void _underSoloConnect_JumpField(void);    // solo機として接続中 Jump中
static void _underSoloConnect_JumpFieldEnd(void);    // solo機として接続中 Jumpおわり
static void _underStalthConnect_JumpFieldStart(void);    // stalth機として接続中 Jump開始
static void _underStalthConnect_JumpField(void);    // stalth機として接続中 Jump中
static void _underStalthConnect_JumpFieldEnd(void);    // stalth機として接続中 Jumpおわり

static void _underChildStalthDeadLoop(void);


// バトル関連ステート
static void _battleParentInit(void);     // 戦闘用親機として初期化
static void _battleParentWaiting(void);  // 戦闘用親機として待機中

static void _battleChildInit(void);     // 戦闘用子機として初期化
static void _battleChildBconScanning(void);  // 戦闘用子機として親機選択中
static void _battleChildConnecting(void);  // 接続許可もらい中
static void _battleChildSendName(void);  // 自分の名前をみんなに送信
static void _battleChildWaiting(void);  // ダイレクト用子機待機中
static void _battleMoveRoomEnter(void); // 戦闘前の部屋に入って待機中
static void _battleMoveRoomEnter2(void); // 戦闘前の部屋に入って待機中
static void _battleMoveRoomReturn(void); // 戦闘前の部屋に入って待機中
static void _battleMoveRoomReturn2(void); // 戦闘前の部屋に入って待機中
static void _battleMoveRoomReturn3(void); // 戦闘前の部屋に入って待機中
static void _battleMoveRoomWait(void);
static void _battleMoveRoom(void); // 戦闘前の部屋に入って待機中
static void _battleChildReTry(void);   // 子機を中断
static void _battleChildReInit(void);   // 子機を再起動
static void _battleMoveRoomEnd_Tim(void);   //バトルルーム終了 戦闘開始
static void _battleMoveRoomEnd(void);   //バトルルーム終了 戦闘開始
static void _battleQuit(void);   //バトルルーム強制終了
static void _trCardCopyEnd(void);
static void _dsChangeTiming(void);
static void _trCardCopyStart(void);
static void _dsChangeEndWaitStart(void);
static void _dsChangeEndWaitEnd(void);

// その他一般的なステート
static void _stateNone(void);            // 何もしない
static void _stateConnectError(void);    // 接続エラー状態
static void _stateEnd(void);             // 終了処理
static void _stateConnectEnd(void);      // 切断処理開始
static void _directEndTiming(void);
static void _directEndNoTiming(void);
static void _stateConnectAutoEnd(void);  // 自動切断処理開始
static void _underChildRebootFunc(void);

#ifdef PM_DEBUG		// Debug ROM
static void _debugTimerStart(void);   // デバッグ用
static void _debugTimerDisp(char* msg);
#else
static void _debugTimerStart(void){}   // デバッグ用
static void _debugTimerDisp(char* msg){}
#endif


//==============================================================================
/**
 * 通信管理ステートの初期化処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _commStateInitialize(FIELDSYS_WORK* pFSys)
{
    void* pWork;

    if(_pCommFState!=NULL){   // すでに動作中の場合必要ない
        return;
    }
    CommCommandFieldInitialize((void*)pFSys);
    // 初期化
    _pCommFState = (_COMM_FSTATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_FSTATE_WORK));
    MI_CpuFill8(_pCommFState, 0, sizeof(_COMM_FSTATE_WORK));
//    _pCommFState->state = NULL;   // 何もしない
    _pCommFState->timer = _START_TIME;
    _pCommFState->pTcb = TCB_Add(_commCheckFunc, NULL, _TCB_COMMCHECK_PRT);
    _pCommFState->pFSys = pFSys;
    _pCommFState->party = NULL;
//    _pCommFState->bStalth = FALSE;
//    _pCommFState->bUGOverlay = FALSE;
//    _pCommFState->bStateNoChange = FALSE;
    _debugTimerStart();
    CommRandSeedInitialize(&_pCommFState->sRand);
}

//==============================================================================
/**
 * 通信管理ステートの終了処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateFinalize(void)
{
    void* pWork;
    int i;

    if(_pCommFState==NULL){  // すでに終了している
        return;
    }
    TCB_Delete(_pCommFState->pTcb);

    for(i = 0;i < _TRAINER_CARD_NUM_MAX; i++){
        if(_pCommFState->pTRCard[i]){
            sys_FreeMemoryEz(_pCommFState->pTRCard[i]);
        }
//        sys_DeleteHeap(HEAPID_VSROOM);
    }

    if( _pCommFState->party )
    {
		sys_FreeMemoryEz( _pCommFState->party );
	}

    sys_FreeMemoryEz(_pCommFState);
//    sys_DeleteHeap(HEAPID_COMMUNICATION);
    _pCommFState = NULL;
}

//==============================================================================
/**
 * 地下にはいった時の通信処理
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterUnderGround(FIELDSYS_WORK* pFSys)
{
    if(_pCommFState!=NULL){ // つながっている場合今は除外する
        return;
    }
    // 接続実行
    CommStateEnterUnderGround(GameSystem_GetSaveData(pFSys));
    _commStateInitialize(pFSys);
    sys_CreateHeap( HEAPID_BASE_APP, HEAPID_UNDERGROUND, 0xe800 );  //グッズメニューでかなり確保
    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        OS_TPrintf("初回地下イベント\n");
        CommStateSetFirstEvent();
    }

}

//==============================================================================
/**
 * 地下にはいって、フィールドが地下に変わった時の処理
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================

void CommFieldStateArrivalUnderGround(void)
{
    _pCommFState->bUGOverlay = TRUE;
    RECORD_Score_Add(SaveData_GetRecord(_pCommFState->pFSys->savedata), SCORE_ID_MINE_IN);

    CommUnderOptionInitialize(_pCommFState->pFSys);  // 地下サービスの起動

#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    
    _CHANGE_STATE(_underStart, 0);
}

//==============================================================================
/**
 * 地下を出る場合の通信処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitUnderGround(void)
{
    if(_pCommFState==NULL){  // すでに終了している
        return;
    }
    // 切断ステートに移行する  すぐに切れない
    
    _CHANGE_STATE(_stateUnderGroundConnectEnd, 3);
}

//==============================================================================
/**
 * 地下を通信停止にする場合の通信処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateStalthUnderGround(void)
{
    OHNO_PRINT("stalth \n");
//    CommUnderOptionFinalize();  // ここをはずす@@OO
    CommStateUnderGroundOfflineSecretBase();
    _CHANGE_STATE(_underChildStalth, 0);
}

//==============================================================================
/**
 * 地下を再接続する場合の処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthEndCheck(void)
{
    if(!CommMPIsConnectStalth()){
        CommSecretBaseInfoJumpEnd();
        _CHANGE_STATE(_underStart,0);
    }

}


void CommFieldStateUnderGroundReConnect(void)
{
//    CommSecretBaseInfoChildSendStart();
    //_underChildConnect_JumpFieldEnd();
    CommStateUnderGroundOnlineSecretBase();  // 通信状態をONLINEにもどす

    _CHANGE_STATE(_underStalthEndCheck,0);
//    _CHANGE_STATE(_underStart,1)
    
//    CommTrapInfoChildSendStart();  //Trapを自分自身に送信開始
//    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}

//==============================================================================
/**
 * 地下をJUMPする場合の通信処理
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateJumpUnderGround(void)
{
    int i;
    u32 stateAddr = (u32)_pCommFState->state;
    u32 parentAddr = (u32)_underParentConnect;
    u32 childAddr = (u32)_underChildConnect;
    u32 soloAddr = (u32)_underConnectting;
    u32 stalthAddr = (u32)_underChildStalthDeadLoop;
    u32 jumpState[] = {
        (u32)_underParentConnect_JumpFieldStart,
        (u32)_underChildConnect_JumpFieldStart,
        (u32)_underSoloConnect_JumpFieldStart,
        (u32)_underStalthConnect_JumpFieldStart,
    };


    
    if(stateAddr == parentAddr){
        _CHANGE_STATE(_underParentConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(childAddr == stateAddr){
        _CHANGE_STATE(_underChildConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(soloAddr == stateAddr){
        _CHANGE_STATE(_underSoloConnect_JumpFieldStart, 0);
        return TRUE;
    }
    else if(stalthAddr == stateAddr){
        _CHANGE_STATE(_underStalthConnect_JumpFieldStart, 0);
        return TRUE;
    }
    for(i = 0 ; i < NELEMS(jumpState); i++){
        if(jumpState[i] == stateAddr){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 地下をJUMPし終わった場合の処理 ステートがActive状態になる
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommStateJumpEndUnderGround(void)
{
    u32 stateAddr = (u32)_pCommFState->state;
    u32 parentAddr = (u32)_underParentConnect_JumpField;
    u32 childAddr = (u32)_underChildConnect_JumpField;
    u32 soloAddr = (u32)_underSoloConnect_JumpField;
    u32 stalthAddr = (u32)_underStalthConnect_JumpField;

    if(stateAddr == parentAddr){
        _CHANGE_STATE(_underParentConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(childAddr == stateAddr){
        _CHANGE_STATE(_underChildConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(soloAddr == stateAddr){
        _CHANGE_STATE(_underSoloConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    else if(stalthAddr == stateAddr){
        _CHANGE_STATE(_underStalthConnect_JumpFieldEnd, 0);
        return TRUE;
    }
    {
//        GF_ASSERT(0 && "想定外のstate:要修正");
    }
    return FALSE;
}

//==============================================================================
/**
 * 移動可能ステートなのかどうか返す
 * @param   none
 * @retval  移動可能ならTRUE
 */
//==============================================================================

BOOL CommIsUnderGroundMoveState(void)
{
    int i;
    u32 funcTbl[]={
        (u32)_battleMoveRoom,
        (u32)_underChildConnect,
        (u32)_underParentConnect,
        (u32)_underChildConnectInfoWait,
        (u32)_underChildConnectFlagWait,
        (u32)_underChildConnectSecret,
        (u32)_underChildConnectDig,
        (u32)_underChildConnect_JumpFieldStart,
        (u32)_underChildConnect_JumpField,
        (u32)_underChildConnect_JumpFieldEnd,
        (u32)_underParentConnect_JumpFieldStart,
        (u32)_underParentConnect_JumpField,
        (u32)_underParentConnect_JumpFieldEnd,
        0,
    };
    u32 stateAddr = (u32)_pCommFState->state;

    if(_pCommFState==NULL){  // すでに終了している
        return FALSE;
    }
    for(i = 0; funcTbl[i] != 0; i++ ){
        if(stateAddr == funcTbl[i]){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * バトル時の親としての通信処理開始
 * @param   serviceNo  通信サービス番号
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleParent(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // つながっている場合今は除外する
    }
#ifdef PM_DEBUG
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE, SOLO_DEBUG_NO);
#else
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleParentInit, 0);
}

//==============================================================================
/**
 * バトル時の子としての通信処理開始
 * @param   serviceNo  通信サービス番号
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleChild(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // つながっている場合今は除外する
    }
    // 通信ヒープ作成
#ifdef PM_DEBUG
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE, SOLO_DEBUG_NO);
#else
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleChildInit, 0);
}

//==============================================================================
/**
 * バトル時の子としての通信処理開始
 * @param   connectIndex 接続する親機のIndex
 * @retval  none
 */
//==============================================================================

void CommFieldStateConnectBattleChild(int connectIndex)
{
    _pCommFState->connectIndex = connectIndex;
    _CHANGE_STATE(_battleChildConnecting, 0);
}

//==============================================================================
/**
 * バトル時の子としての通信再起動処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateRebootBattleChild(void)
{
    _CHANGE_STATE(_battleChildReTry, 0);
}

//==============================================================================
/**
 * バトル時に移動できる部屋に入る時の処理
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleRoom(FIELDSYS_WORK* pFSys)
{
    OHNO_PRINT("部屋に入った\n");
    WIPE_SetWndMask(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
    WIPE_SetWndMask(WIPE_DISP_SUB,WIPE_FADE_BLACK);
    CommStateSetErrorCheck(TRUE,TRUE);

    if(!CommStateIsInitialize()){  // 通信状態で無いなら終わり
        return;
    }
    if(_pCommFState==NULL){// 動いてない場合動作させる
        _commStateInitialize(pFSys);
        _pCommFState->bReturnBattle = TRUE;
    }
    else{
        _pCommFState->bReturnBattle = FALSE;
    }
    _pCommFState->bBattleMoveRoom = FALSE;

    {  // トレーナーカードのデータ準備
        int i,id = CommGetCurrentID();
        MYSTATUS *my_st = CommInfoGetMyStatus(CommGetCurrentID());
        for(i = 0; i < CommGetConnectNum(); i++){
            if(_pCommFState->pTRCard[i]==NULL){
                _pCommFState->pTRCard[i] = sys_AllocMemory(HEAPID_BASE_SYSTEM,sizeof(TR_CARD_DATA));
            }
        }
        TRCSET_MakeTrainerInfo( BADGE_BRUSH_OFF, TIME_UPDATE_OFF, GYM_READER_MASK_NONE, UNION_TR_NONE,
//                                UnionView_GetTrainerInfo( MyStatus_GetMySex(my_st),
//                                                          MyStatus_GetTrainerView(my_st), UNIONVIEW_ICONINDEX ),
                                _pCommFState->pFSys,
                                _pCommFState->pTRCard[id] );
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_TR);
    _CHANGE_STATE(_trCardCopyStart, 0);
}

//==============================================================================
/**
 * データコピーが終わったかどうか
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommFieldStateIsCopyEnd(void)
{
    if(_pCommFState->state == _trCardCopyStart){
        return FALSE;
    }
    if(_pCommFState->state == _trCardCopyEnd){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * バトル時の通信処理終了手続き
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitBattle(void)
{
    if(_pCommFState==NULL){
        return;      // すでに終了している場合は除外
    }
    CommStateSetErrorCheck(FALSE,FALSE);
    _CHANGE_STATE(_directEndNoTiming, _EXIT_SENDING_TIME);
}


//==============================================================================
/**
 * バトル時の通信処理終了手続き  最後に同期を取って終了
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommFieldStateExitBattleTiming(void)
{
    if(_pCommFState==NULL){
        return;      // すでに終了している場合は除外
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_EXIT2);
    _CHANGE_STATE(_directEndTiming, _EXIT_SENDING_TIME);
}




//==============================================================================
/**
 * 通信管理ステートの処理
 * @param
 * @retval  none
 */
//==============================================================================

void _commCheckFunc(TCB_PTR tcb, void* work)
{
#ifdef PM_DEBUG
    _pCommFState->debugTimer++;
#endif

    if(_pCommFState==NULL){
        TCB_Delete(tcb);
    }
    else{
        if(_pCommFState->state != NULL){
            PTRStateFunc state = _pCommFState->state;
            if(!_pCommFState->bStateNoChange){
                state();
            }
        }
    }
}

//==============================================================================
/**
 * 通信管理ステートの変更
 * @param   state  変えるステートの関数
 * @param   time   ステート保持時間
 * @retval  none
 */
//==============================================================================

static void _changeState(PTRStateFunc state, int time)
{
    _pCommFState->state = state;
    _pCommFState->timer = time;
}

#ifdef PM_DEBUG
static void _changeStateDebug(PTRStateFunc state, int time, int line)
{
    OHNO_PRINT("CF field_state: %d %d\n",line, CommGetCurrentID());
    _changeState(state, time);
}
#endif

//==============================================================================
/**
 * 地下スタート
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsInitialize()){
        return;  //
    }
//    if(!CommGetAloneMode()){   // aloneモードの場合
//        return;
//    }    
    CommUnderOptionReInit(_pCommFState->pFSys);  // 地下サービス再度初期化

    // 自分自身にいったん送る
    CommInfoSendPokeData();
    CommPlayerSendPos(FALSE);
    CommTrapInfoChildSendStart();  //Trapを自分自身に送信開始
    CommSecretBaseInfoChildSendStart(); // 自分の秘密基地データ自分の親側に送信開始

    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        // ひょうたようステート
        _CHANGE_STATE(_underOpenning, 0);
    }
    else{
        CommPlayerFirstMoveEnable();
        _CHANGE_STATE(_underConnecttingAloneSend, _CHILD_P_SEARCH_TIME*2);
    }
}

//==============================================================================
/**
 * openiingが終わるまでなにもしない  つながらないようにする為
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underOpenning(void)
{
    if(!SysFlag_UgFirstCheck(SaveData_GetEventWork(_pCommFState->pFSys->savedata))){
        return;
    }
    CommStateUnderRestart();
    CommPlayerFirstMoveEnable();
    
    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}



//==============================================================================
/**
 * 自分で自分にデータを送信し終わるまで待つ
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underConnecttingAloneSend(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    _CHANGE_STATE(_underConnectting, _CHILD_P_SEARCH_TIME*2);
}

//==============================================================================
/**
 * ネットワークがつながるまで待機
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underConnectting(void)
{
    CommUnderProcess();

    CommPlayerFirstMoveEnable();
    
    if(CommIsUnderGroundConnectingState()){  // 接続するまで呼び続ける
        if(CommGetCurrentID() == COMM_PARENT_ID){
            OHNO_PRINT("親になった\n");
            CommSecretBaseInfoParentDel();

            _CHANGE_STATE(_underParentWait, 60);
        }
        else{
            OHNO_PRINT("子になった\n");
            _CHANGE_STATE(_underChildConnecting, 120);
        }
    }
}

//==============================================================================
/**
 * 子機となって接続中
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _underChildConnecting(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }

    if(CommMPParentDisconnect() || CommIsError() || (_pCommFState->timer==0) ){
        CommStateUnderRestart();
        _CHANGE_STATE(_underChildRestart, 0);  // 子機になる前にエラーになった
    }
    else if(CommIsConnect(CommGetCurrentID())){   // 自分自身が接続していることが確認できたら
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
            if(CommGetSendRestSize() != COMM_COMMAND_SEND_SIZE_MAX){  // 空になるまで待つ タイマーつき
                return;
            }
        }
        UgMgrForceExitNowTCB();
        CommPlayerMyDataCopy( COMM_PARENT_ID );  // 親データから自分を持ってくる
        CommTrapRecvForceEnd(COMM_PARENT_ID,0,NULL,NULL);  // 罠を止める
        UgTrapForceExit(COMM_PARENT_ID,TRUE);
        CommInfoDeletePlayer(COMM_PARENT_ID);   // 自分が親だったのでそれを消す
        CommPlayerDestroy( COMM_PARENT_ID, FALSE, FALSE );
//        CommPlayerSendPos(FALSE);
        //_debugTimerDisp("子機接続----!!!-----");
        OHNO_PRINT("子機になった %d \n",CommGetCurrentID());
        CommPlayerFirstMoveDisable();
        _CHANGE_STATE(_underChildConnectInfoWait, 10);
        return;
    }
//    _pCommFState->timer--;
}

//==============================================================================
/**
 * 親機になり、子機が接続してくるのを待つ
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentWait(void)
{
    CommUnderProcess();

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }

    if(CommIsChildsConnecting() || (_pCommFState->timer==0)){
        // 自分以外がつながったら親機固定
        // もしくは子機が切断してしまった場合のタイムアウトエラー的に移動
        if(UgMgrForceExitNowTCB()){
            CommPlayerHoldEnd();
        }
        _debugTimerDisp("親機接続");
//        CommInfoSendPokeData();
        CommPlayerSendPos(FALSE);
//        CommTrapInfoChildSendStart();  //Trapを自分自身に送信開始
        CommPlayerNowFlagSend();
        CommSecretBaseInfoChildSendStart(); // 自分の秘密基地データ自分の親側に送信開始
//        UgDigFossilPlayerInit();
        UgInitialDataSend();   // 化石＋エスケープ場所を送信
        _CHANGE_STATE(_underParentConnect, 0);
        return;
    }

}

//==============================================================================
/**
 * 親機として接続中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect(void)
{
    CommUnderProcess();

    // 全員接続が切れたら巡回に戻るがイベント中は禁止
//    if((_pCommFState->pFSys->event != NULL) || UgSecretBaseIsMoveTickets()){  // 地下移動イベント時にステートを変えるのは禁止
    if(_pCommFState->pFSys->event != NULL){  // 地下移動イベント時にステートを変えるのは禁止
        return;
    }

    if(CommIsError() || !CommMPIsChildsConnecting() || ((!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode())) ){

        OHNO_PRINT("なぜか子機が切断する %d %d\n",CommIsError(),CommMPIsChildsConnecting());
        
        // 秘密基地から戻るウインドウが出ていると親機の移動フラグがたっているのでここでリセット
        UgSecretBaseResetPlayer(COMM_PARENT_ID); // イベントが動いてないならリセット

        CommPlayerParentFlagDataReset();
        UgSecretBaseErrorMoveTickets();
        CommSendFixData(CF_TRAP_END_FORCE);    // サーバー側も強制解除
        UgTrapForceExit(CommGetCurrentID(),TRUE);
        UgMgrForceExitNowTCB();
        CommStateUnderParentRestart();
#if T1645_060815_FIX
        _CHANGE_STATE(_underParentRestartAloneWait, 0);
#else
        _CHANGE_STATE(_underParentRestart, 1);
#endif
    }
}

//==============================================================================
/**
 * 親機として接続中   秘密基地への移動開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpFieldStart(void)
{
    //CommSecretBaseInfoReset();
    //CommTrapInfoReset();
    CommPlayerManagerReset();
    _CHANGE_STATE(_underParentConnect_JumpField, 0);
}

//==============================================================================
/**
 * 親機として接続中   秘密基地への移動中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpField(void)
{
    CommUnderProcess();
}

//==============================================================================
/**
 * 親機として接続中   秘密基地への移動終わり
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    //CommSecretBaseInfoReboot();
    //CommTrapInfoReboot();
    CommPlayerManagerReboot();

#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underParentConnect, 0);
}

//==============================================================================
/**
 * 子機として接続完了していて　infoデータを集めているところ
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectInfoWait(void)
{
    if(_pCommFState->timer == 9){
        CommInfoSendPokeData();  //infoデータを送る
        UgInitialDataSend();   // 化石＋エスケープ場所を送信
    }
    if(_pCommFState->timer == 1){
        //UgDigFossilPlayerInit();// 化石掘ってるかどうかを送る
        CommPlayerSendPosServer(FALSE);  //テスト
    }
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommInfoIsInfoCollected()){
        _debugTimerDisp("infoデータ受信完了");
        CommPlayerNowFlagSend();
        _CHANGE_STATE(_underChildConnectFlagWait,200);
        return;
    }
    _underChildConnect();
}


//==============================================================================
/**
 * 子機として接続完了していて　ハタデータを送る所
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectFlagWait(void)
{
    if(CommPlayerIsNowFlagDataEnd()){
        CommTrapInfoChildSendStart();  // 罠情報送信
        _CHANGE_STATE(_underChildConnectSecret,0);
    }
    else{
        _underChildConnect();
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        else{
            // タイムアウトによる切断
            OHNO_PRINT("うけとってない\n");
            _underChildRebootFunc();
        }
    }
}

//==============================================================================
/**
 * 子機として接続  罠送信完了
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectSecret(void)
{
    if(CommTrapInfoIsParentRecv()){
        _debugTimerDisp("親機罠データ届いたらしい");
        CommTrapInfoResetParentRecv();
        CommSecretBaseInfoChildSendStart(); // 子機の秘密基地データ送信開始
        _CHANGE_STATE(_underChildConnectDig,0);
        return;
    }
    _underChildConnect();
}

//==============================================================================
/**
 * 子機として接続 秘密基地送信完了
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnectDig(void)
{
    if(CommSecretBaseInfoIsPosRecv()){
        _debugTimerDisp("秘密基地の位置がきた");
        CommSecretBaseResetPosRecv();
     //   CommPlayerSetMoveControl(TRUE);
        CommPlayerSendPos(TRUE);  // キャラを出す為にもう一回送る　テスト中
        CommSendFixData(CF_PLAYER_INIT_END);  // 初期化完了を送信
        _CHANGE_STATE(_underChildConnect,0);
        return;
    }
    _underChildConnect();
}

#if T1645_060815_FIX

//==============================================================================
/**
 * 親機として切断をする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestartAloneWait(void)
{
    if(!CommGetAloneMode()){
        OHNO_PRINT("s wait\n");
        return;
    }
    _CHANGE_STATE(_underParentRestart,10);
}

//==============================================================================
/**
 * 親機として切断をするのを待つ
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        if(!CommIsEmptyQueue()){
            OHNO_PRINT("not e\n");
            return;
        }
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){  // 親になった
        OHNO_PRINT("再スタート\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

#else

//==============================================================================
/**
 * 親機として切断をする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentRestart(void)
{
//    if(CommIsUnderResetState()){
  //      return;
 //   }
//    if(!CommIsConnect(CommGetCurrentID()) && !CommGetAloneMode()){
    if(!CommGetAloneMode()){
        OHNO_PRINT("s wait\n");
        return;
    }
    if(!CommIsEmptyQueue()){
        OHNO_PRINT("not e\n");
        return;
    }
    
    if(CommGetCurrentID() == COMM_PARENT_ID){  // 親になった
        OHNO_PRINT("再スタート\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

#endif //T1645_060815_FIX

//==============================================================================
/**
 * 子機として切断をする
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildRestart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){  // 親になった
        OHNO_PRINT("再スタート\n");
        _CHANGE_STATE(_underStart, 0);
    }
}

static void _underChildRestart_Base(void)
{
    if(_pCommFState->pFSys->event == NULL ){  // 地下移動イベント終了
        CommStateUnderRestart();  // 地下の通信を親子切り替えに
        _CHANGE_STATE(_underChildRestart, 0);
    }
}



static void _underChildStalthDeadLoop(void)
{
    CommUnderProcess();
}

static void _underChildStalth(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
//        CommUnderOptionInitialize(_pCommFState->pFSys);  // 地下サービスの起動

        CommUnderOptionReInit(_pCommFState->pFSys);  // 地下サービス再度初期化

        // 自分自身にいったん送る
        CommInfoSendPokeData();
        CommPlayerSendPos(FALSE);
        CommTrapInfoChildSendStart();  //Trapを自分自身に送信開始
        CommSecretBaseInfoChildSendStart(); // 自分の秘密基地データ自分の親側に送信開始
        _CHANGE_STATE(_underChildStalthDeadLoop, 0);
    }
}

//==============================================================================
/**
 * 子機として接続完了
 * @param   none
 * @retval  none
 */
//==============================================================================



//==============================================================================
/**
 * 子機として接続完了
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildRebootFunc(void)
{
    UgTrapForceExit(CommGetCurrentID(),TRUE);
    if(UgSecretBaseRemovePlayer_Client(CommGetCurrentID(),TRUE)){
        CommPlayerManagerStop();  // 移動停止
        UgMgrForceExitNowTCB();   // 登録イベントを終了させる
        CommStateUnderRestart();  // 地下の通信を親子切り替えに
        CommPlayerFlagChange();   // 自分のハタを挿げ替える
        _CHANGE_STATE(_underChildRestart, 0);//
    }
    else{
        OHNO_PRINT("切断再起動 %d\n",CommGetCurrentID());
        CommPlayerManagerStop();  // 移動停止
        UgMgrForceExitNowTCB();   // 登録イベントを終了させる
        CommStateUnderRestart();  // 地下の通信を親子切り替えに
        CommPlayerFlagChange();   // 自分のハタを挿げ替える
        _CHANGE_STATE(_underChildRestart, 0);
    }
}


static void _underChildConnect(void)
{
    CommUnderProcess();

    CommPlayerFirstMoveEnable();
    
    // 親機がいなくなったら終了処理をして別親を探しにいく
    if(_pCommFState->pFSys->event != NULL ){  // 地下移動イベント時にステートを変えるのは禁止
        return;
    }
    if(CommMPParentDisconnect() || CommIsError()){
        _underChildRebootFunc();  // 再起動
    }
}

//==============================================================================
/**
 * 子機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpFieldStart(void)
{
    //CommSecretBaseInfoReset();
    //CommTrapInfoReset();
    CommPlayerManagerReset();
    _CHANGE_STATE(_underChildConnect_JumpField,0);
}

//==============================================================================
/**
 * 子機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpField(void)
{
    // 出来るだけ何もしない
    UgSecretBaseErrorDisconnectTickets();
}

//==============================================================================
/**
 * 子機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underChildConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
 //   CommSecretBaseInfoReboot();
//    CommTrapInfoReboot();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif

    if(CommMPParentDisconnect() || CommIsError()){
        OHNO_PRINT("切断再起動 %d\n",CommGetCurrentID());
        
        CommSecretBaseInfoReInit();  // 
        CommPlayerManagerStop();  // 移動停止
        UgMgrForceExitNowTCB();   // 登録イベントを終了させる
        CommStateUnderRestart();  // 地下の通信を親子切り替えに
        CommPlayerFlagChange();   // 自分のハタを挿げ替える
        _CHANGE_STATE(_underChildRestart, 0);
    }
    else{
        _CHANGE_STATE(_underChildConnect, 0);
    }
}



//==============================================================================
/**
 * solo機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpFieldStart(void)
{
    CommPlayerManagerReset();
    _CHANGE_STATE(_underSoloConnect_JumpField,0);
}

//==============================================================================
/**
 * solo機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpField(void)
{
}

//==============================================================================
/**
 * solo機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underSoloConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underConnectting, 0);
}

//==============================================================================
/**
 * stalth機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpFieldStart(void)
{
    CommPlayerManagerDeletePlayers();
    _CHANGE_STATE(_underStalthConnect_JumpField,0);
}

//==============================================================================
/**
 * stalth機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpField(void)
{
}

//==============================================================================
/**
 * solo機として接続中　　　JUMP処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underStalthConnect_JumpFieldEnd(void)
{
    CommSecretBaseInfoJumpEnd();
    CommPlayerManagerReboot();
#ifdef PM_DEBUG
    if(DebugOhnoGetCommDebugDisp()){
        DebugIchiCheckOn(_pCommFState->pFSys);
    }
#endif
    _CHANGE_STATE(_underChildStalthDeadLoop, 0);
}


//==============================================================================
/**
 * 親機として初期化を行う
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentInit(void)
{
    if(!CommIsConnect(CommGetCurrentID())){
//    if(!CommIsVRAMDInitialize()){
        return;
    }
    CommChildListWindowOpen();
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleParentWaiting, 0);
}

//==============================================================================
/**
 * 親機として待機中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentWaiting(void)
{
  //  if(CommGetCurrentID() == COMM_PARENT_ID){
    //    CommInfoSendArray_ServerSide();  // 子機から問い合わせがあったらinfoを送信
   // }
}

//==============================================================================
/**
 * 子機の初期化
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildInit(void)
{
    if(!CommIsVRAMDInitialize()){
        return;
    }
    
    CommParentSelectParentWindowOpen();
    _CHANGE_STATE(_battleChildBconScanning, 0);
}

//==============================================================================
/**
 * 子機待機状態  親機ビーコン収集中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildBconScanning(void)
{
//    CommParentBconCheck();
}

//==============================================================================
/**
 * 子機待機状態  親機に許可もらい中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildConnecting(void)
{
    CommStateConnectBattleChild(_pCommFState->connectIndex);
    _CHANGE_STATE(_battleChildSendName, 0);
}

//==============================================================================
/**
 * 子機待機状態  親機に情報を送信
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildSendName(void)
{
    if(!CommIsBattleConnectingState()){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleChildWaiting, 0);
}

//==============================================================================
/**
 * 子機待機状態
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildWaiting(void)
{
    //Exitを受け取ったら子機切断
}



//==============================================================================
/**
 * 子機enter状態  移動ルーム内に戻ってきた
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomReturn(void)
{
    void* pWork;
    if(CommIsTimingSync(DBC_TIM_BATTLE_DSEND)){
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommPlayerGetWorkSize());
        CommPlayerManagerInitialize(pWork, _pCommFState->pFSys, FALSE);
        CommPlayerFirstMoveEnable();
        CommDisableSendMoveData();  // 移動禁止
        CommTimingSyncStart(DBC_TIM_BATTLE_PAUSE);
        _CHANGE_STATE(_battleMoveRoomReturn2, 0);
        return;
    }
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }
    else{
        _pCommFState->timer=30;
        CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    }
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomReturn2(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
        CommInfoSendArray_ServerSide();  // 子機から問い合わせがあったらinfoを送信
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_PAUSE)){
        
        WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );

        WIPE_ResetWndMask(WIPE_DISP_MAIN);
        WIPE_ResetWndMask(WIPE_DISP_SUB);

        CommPlayerManagerReboot();
        CommPlayerSendPos(FALSE);
        _CHANGE_STATE(_battleMoveRoomReturn3,1);
    }
}

static void _battleMoveRoomReturn4(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_BACK)){
        CommEnableSendMoveData();  // 移動OK
        _CHANGE_STATE(_battleMoveRoomWait,0);
    }
}


static void _battleMoveRoomReturn3(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){
        if(FALSE == CommPlayerMoveBattlePos()){
            return;
        }
        CommTimingSyncStart(DBC_TIM_BATTLE_BACK);
    }
    else{
        CommTimingSyncStart(DBC_TIM_BATTLE_BACK);
    }
    _CHANGE_STATE(_battleMoveRoomReturn4,20);
}


//==============================================================================
/**
 * 子機enter状態  移動ルーム内にはいってきた
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnter(void)
{
    void* pWork;

    if(CommIsTimingSync(DBC_TIM_BATTLE_DSEND)){
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommPlayerGetWorkSize());
        CommPlayerManagerInitialize(pWork, _pCommFState->pFSys, FALSE);
        CommPlayerFirstMoveEnable();
        CommTimingSyncStart(DBC_TIM_BATTLE_PAUSE);
        _CHANGE_STATE(_battleMoveRoomEnter2, 0);
        return;
    }

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
    }
    else{
        _pCommFState->timer=30;
        CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    }
    
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnter2(void)
{
    if(CommGetCurrentID() == COMM_PARENT_ID){
        CommInfoSendArray_ServerSide();  // 子機から問い合わせがあったらinfoを送信
    }
    if(CommIsTimingSync(DBC_TIM_BATTLE_PAUSE)){
        CommPlayerManagerReboot();
        CommPlayerSendPos(FALSE);
        {
            u8 bit = TRUE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }

        WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
        WIPE_ResetWndMask(WIPE_DISP_MAIN);
        WIPE_ResetWndMask(WIPE_DISP_SUB);

        _CHANGE_STATE(_battleMoveRoom,0);
    }
}


static void _exitCheck(void)
{
    int i,k;

    for(i = 0;i < CommGetConnectNum();i++){
        if(i != CommGetCurrentID()){
            if(CommGetTimingSyncNo(i) == DBC_TIM_BATTLE_EXIT){
                if(_pCommFState->pFSys->event==NULL){
                    for(k = 0;k < _TRAINER_CARD_NUM_MAX; k++){
                        if(_pCommFState->pTRCard[k]){
                            sys_FreeMemoryEz(_pCommFState->pTRCard[k]);
                            _pCommFState->pTRCard[k]=NULL;
                        }
                    }
                    EventSet_Script( _pCommFState->pFSys, SCRID_BATTLE_ROOM_FORCEEND, NULL );
                }
            }
        }
    }
    CommErrorCheck(HEAPID_FIELD,_pCommFState->pFSys->bgl);
}


//==============================================================================
/**
 *  移動ルーム内  キャンセルしたか、全員そろったかのコールバック
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomWait(void)
{
    if(!CommPlayerCheckBattleJump()){
        _pCommFState->bBattleMoveRoom = FALSE;
        {
            u8 bit = TRUE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
        _CHANGE_STATE(_battleMoveRoom, 0);
    }
    _exitCheck();  // 一斉に終了する検査
}

// スタートライン時の終了コールバック
static void _startLineCallBack(BOOL bStart, const POKEPARTY* party)
{
	if( party )
	{
		_pCommFState->party = PokeParty_AllocPartyWork( HEAPID_WORLD );
		PokeParty_Copy( party, _pCommFState->party );
    }

    if(bStart){
        _CHANGE_STATE(_battleMoveRoomEnd_Tim, 3);
    }
    else{  // もういちど動く場合
        {
            u8 bit = 3;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
        _CHANGE_STATE(_battleMoveRoomWait, 0);
    }
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
    回転させて待機イベント起動
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomNop(void)
{
    // スタートラインコールバックの返事を待つ
    _CHANGE_STATE(_battleMoveRoomWait,0);
}


static void _battleMoveRoomEventSet(void)
{
    if(CommSysIsMoveKey() || (0 != CommPlayerGetWalkCount(CommGetCurrentID()))){
        return;
    }

    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
    CommPlayerHold();
    EventCmd_StartLine(_pCommFState->pFSys, _startLineCallBack);

    _CHANGE_STATE(_battleMoveRoomNop,0);
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoom(void)
{
    if( _pCommFState->bBattleMoveRoom ){  // 開始位置についたことを受信
        _CHANGE_STATE(_battleMoveRoomEventSet, 5);  // 移動、スタートラインイベント
        {
            u8 bit = FALSE;
            CommSendFixSizeData(CF_DIRECT_START_SET,&bit);
        }
    }
    _exitCheck();
}

//CF_DIRECT_STARTPOS
void CommDirectRecvStartPos(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(pBuff[0] == CommGetCurrentID()){
        _pCommFState->bBattleMoveRoom = TRUE;
    }
}

BOOL CommDirectIsMoveState(void)
{
    if(_pCommFState ){
        if((_pCommFState->state == _battleMoveRoom) ||
           (_pCommFState->state == _battleMoveRoomWait)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd(void)
{
    BOOL bDSMode = TRUE;
    int type;
    u8 sel[6];

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    type = FIGHT_TYPE_1vs1_SIO;
    switch(CommStateGetServiceNo()){
      case COMM_MODE_BATTLE_MULTI:
      case COMM_MODE_BATTLE_MIX_2ON2:
        type = FIGHT_TYPE_MULTI_SIO;
        break;
      case COMM_MODE_BATTLE_DOUBLE:
        type = FIGHT_TYPE_2vs2_SIO;
        break;
    }
    CommStateGetPokemon(sel);

	if( _pCommFState->party == NULL )
	{
		EventSet_CommDirectBattle(_pCommFState->pFSys,sel, type);
	}
	else
	{
		EventSet_CommDirectMixBattle( _pCommFState->pFSys, _pCommFState->party, type );
		sys_FreeMemoryEz( _pCommFState->party );
		_pCommFState->party = NULL;
	}

//    EventSet_Script( _pCommFState->pFSys, SCRID_CONNECT_COLOSSEUM_BATTLE_START, NULL );
//    CommPlayerManagerFinalize(FALSE);
//    CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //バトルモードに変更する
    _stateFinalize();
}



//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_4(void)
{
    if(CommIsTransmissonDSType()){
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        if(_pCommFState->timer  == 90){
            CommTimingSyncStart(DBC_TIM_BATTLE_DSOK);
        }
        if(CommIsTimingSync(DBC_TIM_BATTLE_DSOK)){
            _CHANGE_STATE(_battleMoveRoomEnd,0);
        }
    }
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_3(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommSetTransmissonTypeDS();
    _CHANGE_STATE(_battleMoveRoomEnd_4,120);
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_2(void)
{
    BOOL bDSMode = TRUE;

    if(CommIsTimingSync(DBC_TIM_BATTLE_MPDS)){
//        if(CommGetCurrentID() == COMM_PARENT_ID){
//            CommSendFixSizeData(CS_DSMP_CHANGE, &bDSMode);  //バトルモードに変更する
//        }
        _CHANGE_STATE(_battleMoveRoomEnd_3,2);
    }
}

//==============================================================================
/**
 * 子機待機状態  移動ルーム内
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleMoveRoomEnd_Tim(void)
{
    BOOL bDSMode = TRUE;

    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommPlayerManagerFinalize(FALSE);
    CommTimingSyncStart(DBC_TIM_BATTLE_MPDS);
    _CHANGE_STATE(_battleMoveRoomEnd_2,0);
}

//==============================================================================
/**
 * エラーによるバトルの強制終了
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleQuit(void)
{
}

//==============================================================================
/**
 * 子機をいったん終了
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReTry(void)
{
    CommStateRebootBattleChild();
    _CHANGE_STATE(_battleChildReInit, _FINALIZE_TIME);
}

//==============================================================================
/**
 * 子機をいったん終了し再起動をかける
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildReInit(void)
{
    if(!CommMPIsStateIdle()){  /// 終了処理がきちんと終わっていることを確認
        return;
    }
    _CHANGE_STATE(_battleChildSendName, _SEND_NAME_TIME);
}






void CommDCRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork )
{
    OHNO_SP_PRINT("CommDCRecvTrainerCard %d\n",netID);
    _pCommFState->bTRCard[netID] = TRUE;
}

u8* CommDCGetTrainerCardRecvBuff( int netID, void* pWork, int size)
{
    GF_ASSERT_RETURN(netID < _TRAINER_CARD_NUM_MAX,NULL);
    return (u8*)_pCommFState->pTRCard[netID];
}





//==============================================================================
/**
 * データシェアリング中にトレーナーカードをコピーしあう
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _trCardCopyStart(void)
{
    int i,id = CommGetCurrentID();

    if(CommIsTimingSync(DBC_TIM_BATTLE_TR)){
        CommSendHugeData(CF_TRAINER_CARD, _pCommFState->pTRCard[id], sizeof(TR_CARD_DATA));
        _CHANGE_STATE(_trCardCopyEnd,0);
    }
}

//==============================================================================
/**
 * データシェアリング中にトレーナーカードをコピーしあう
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _trCardCopyEnd(void)
{
    int i;

    for(i = 0; i < CommGetConnectNum(); i++){
        if(!_pCommFState->bTRCard[i]){
            return;
        }
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_DSCHANGE);
    _CHANGE_STATE(_dsChangeTiming,0);
}


static void _dsChangeEndWaitStart_3(void)
{

    if(!CommIsTransmissonDSType()){
        if(_pCommFState->timer!=0){
            _pCommFState->timer--;
        }
        if(_pCommFState->timer  == 90){
            CommTimingSyncStart(DBC_TIM_BATTLE_MPOK);
        }
        if(CommIsTimingSync(DBC_TIM_BATTLE_MPOK)){
            _CHANGE_STATE(_dsChangeEndWaitStart,0);
        }
    }


}


static void _dsChangeEndWaitStart_2(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommSetTransmissonTypeMP();
    _CHANGE_STATE(_dsChangeEndWaitStart_3,120);
}

static void _dsChangeTiming(void)
{
    if(CommIsTimingSync(DBC_TIM_BATTLE_DSCHANGE)){
        _CHANGE_STATE(_dsChangeEndWaitStart_2,2);
    }
}

static void _dsChangeEndWaitStart(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    CommTimingSyncStart(DBC_TIM_BATTLE_DSEND);
    if(_pCommFState->bReturnBattle){
        _CHANGE_STATE(_battleMoveRoomReturn, 30);
    }
    else{
        _CHANGE_STATE(_battleMoveRoomEnter, 30);
    }
}


//==============================================================================
/**
 * 何もしないステート
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateNone(void)
{
    // なにもしていない
}

//==============================================================================
/**
 * @brief エラー処理
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectError(void)
{
}

//==============================================================================
/**
 * @brief  終了処理中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateEnd(void)
{
    if(CommIsInitialize()){
        return;
    }
    _stateFinalize();
}

//==============================================================================
/**
 * @brief  地下離脱処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateUnderGroundConnectEnd(void)
{
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }

    CommUnderOptionFinalize();
    CommStateExitUnderGround();

    sys_DeleteHeap(HEAPID_UNDERGROUND);

    _pCommFState->bUGOverlay = FALSE; // 地下を止める

    _stateFinalize();   // stateはここで終了 通信は後から切れる
}

//==============================================================================
/**
 * @brief  自動終了処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _directEndTiming(void)
{
    if(CommIsTimingSync(DBC_TIM_BATTLE_EXIT2)){
        CommStateSetErrorCheck(FALSE,FALSE);
        OHNO_PRINT("終了同期を取った---\n");
        CommPlayerManagerFinalize(TRUE);
        _CHANGE_STATE(_stateConnectAutoEnd, _EXIT_SENDING_TIME);
    }
}

//==============================================================================
/**
 * @brief  自動終了処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _directEndNoTiming(void)
{
    CommPlayerManagerFinalize(TRUE);
    _CHANGE_STATE(_stateConnectAutoEnd, _EXIT_SENDING_TIME);
}

//==============================================================================
/**
 * @brief  自動終了処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectAutoEnd(void)
{
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
//    if(CommIsConnect(CommGetConnectNum())){
//        CommSendFixData(CS_AUTO_EXIT);
  //  }
    //else{
        CommStateExitBattle();
        _CHANGE_STATE(_stateFinalize, 0);
   // }
}

//==============================================================================
/**
 * @brief  終了処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _stateConnectEnd(void)
{
    if(_pCommFState->timer != 0){
        _pCommFState->timer--;
        return;
    }
    // 切断する
    CommFinalize();
    _CHANGE_STATE(_stateEnd, 0);
}

#ifdef PM_DEBUG
static void _debugTimerStart(void)
{
    _pCommFState->debugTimer=0;
}

static void _debugTimerDisp(char* msg)
{
    OHNO_PRINT("%s 開始から %d sync かかりました\n", msg, _pCommFState->debugTimer * 2);
}

#endif


#ifdef PM_DEBUG


static BOOL GMEVENT_BattleDebug(GMEVENT_CONTROL * event)
{
    if(CommIsInitialize()){
        return FALSE;
    }
    return TRUE;
}

//==============================================================================
/**
 * 子機待機状態  親機に情報を送信
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildWaiting_Debug(void)
{
    
    OHNO_PRINT("接続検査中 CommGetConnectNum=%d CommMPGetServiceNo=%d \n",CommGetConnectNum(),CommStateGetServiceNo() );
    if(CommGetConnectNum() == (CommGetMaxEntry(CommStateGetServiceNo()))){
        CommDirectConnect_Debug();
        _CHANGE_STATE(_battleChildWaiting, 0);
    }
}

//==============================================================================
/**
 * 子機待機状態  親機に情報を送信
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildSendName_Debug(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsConnect(CommGetCurrentID())){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleChildWaiting_Debug, 0);
}

//==============================================================================
/**
 * 子機待機状態  親機に許可もらい中（デバッグ）
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleChildConnecting_Debug(void)
{
    if(CommMPGetGFBss(_pCommFState->connectIndex)!=NULL){
        CommStateConnectBattleChild(_pCommFState->connectIndex);  // 接続
        _CHANGE_STATE(_battleChildSendName_Debug, _SEND_NAME_TIME);
    }
}

//==============================================================================
/**
 * バトル時の子としての通信処理開始
 * @param   connectIndex 接続する親機のIndex
 * @retval  none
 */
//==============================================================================

void CommFieldStateConnectBattleChild_Debug( FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo, int connectIndex)
{
    if(CommIsInitialize()){
        return;      // つながっている場合今は除外する
    }
#ifdef PM_DEBUG
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE, SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
#else
    CommStateEnterBattleChild(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo, pFSys->regulation,FALSE);
#endif
    _commStateInitialize(pFSys);
    _pCommFState->connectIndex = connectIndex;
    _CHANGE_STATE(_battleChildConnecting_Debug, 0);
}


//==============================================================================
/**
 * 親機として待機中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentWaiting_Debug(void)
{
    if(CommIsChildsConnecting()){
        OHNO_PRINT("接続検査中 CommGetConnectNum=%d CommMPGetServiceNo=%d \n",CommGetConnectNum(),CommStateGetServiceNo() );
        if(CommGetConnectNum() == (CommGetMaxEntry(CommStateGetServiceNo()))){
            CommDirectConnect_Debug();
            _CHANGE_STATE(_battleParentWaiting, 0);
        }
    }
}

//==============================================================================
/**
 * 子機待機状態  親機を選択中
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentSendName_Debug(void)
{
    if(_pCommFState->timer!=0){
        _pCommFState->timer--;
        return;
    }
    if(!CommIsConnect(CommGetCurrentID())){
        return;
    }
    CommInfoSendPokeData();
    _CHANGE_STATE(_battleParentWaiting_Debug, 0);
}

//==============================================================================
/**
 * 親機として初期化を行う
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _battleParentInit_Debug(void)
{
    MYSTATUS* pMyStatus;
    
    if(!CommIsVRAMDInitialize()){
        return;
    }
    _CHANGE_STATE(_battleParentSendName_Debug, _SEND_NAME_TIME);
}

//==============================================================================
/**
 * バトル時の親としての通信処理開始
 * @param   pFSys  フィールド構造体
 * @param   serviceNo  通信サービス番号
 * @param   regulationNo  通信サービス番号
 * @retval  none
 */
//==============================================================================

void CommFieldStateEnterBattleParent_Debug(FIELDSYS_WORK* pFSys, int serviceNo, int regulationNo)
{
    if(CommIsInitialize()){
        return;      // つながっている場合今は除外する
    }
#ifdef PM_DEBUG
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE,
                               SOLO_DEBUG_NO + COMMDIRECT_DEBUG_NO);
#else
    CommStateEnterBattleParent(GameSystem_GetSaveData(pFSys), serviceNo, regulationNo,pFSys->regulation, FALSE);
#endif
    _commStateInitialize(pFSys);
    _CHANGE_STATE(_battleParentInit_Debug, 0);

}

#endif


//==============================================================================
/**
 * @brief   今からセットアップする秘密基地グッズデータを返す
 * @param   sv  SAVEDATA*
 * @retval  SECRETBASEDATA*
 */
//==============================================================================

SECRETBASEDATA* CommUgSetupSecretBaseData(SAVEDATA * sv)
{
    if(!_pCommFState || !_pCommFState->bUGOverlay){
        return NULL;
    }
    return UgManUgSetupSecretBaseData(sv);
}



BOOL CommFieldStateIsUnder(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
        return TRUE;
    }
    return FALSE;
}

void CommStateFieldUnderOptionReset(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
       // CommSystemRecvStop(TRUE);
    //    OHNO_PRINT("通信止めました\n");
        CommUnderOptionReset();
    }
}

void CommStateFieldUnderOptionReboot(void)
{
    if(_pCommFState && _pCommFState->bUGOverlay){
        CommUnderOptionReboot();
   //    OHNO_PRINT("通信許可しました\n");
       // CommSystemRecvStop(FALSE);
    }
}

