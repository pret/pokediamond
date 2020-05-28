//=============================================================================
/**
 * @file	comm_mystery_state.c
 * @brief	通信状態を管理するサービス  通信の上位にある
 *          	スレッドのひとつとして働き、自分の通信状態や他の機器の
 *          	開始や終了を管理する
 *		※comm_field_state.cの真似っ子
 * @author	Satoshi Mitsuhara
 * @date    	2006.05.17
 */
//=============================================================================
#include "common.h"
#include "system/main.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "comm_command_mystery.h"
#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"

//==============================================================================
//	型宣言
//==============================================================================
// コールバック関数の書式
typedef void (*PTRStateFunc)(void);
//==============================================================================
// ワーク
//==============================================================================
typedef struct{
  MYSTERYGIFT_WORK *pMSys;
  MATHRandContext32 sRand; 			//< 親子機ネゴシエーション用乱数キー
  TCB_PTR pTcb;
  PTRStateFunc state;
  u16 timer;
  u8 bStateNoChange;
  u8 connectIndex;   				// 子機が接続する親機のindex番号
  MYSTATUS *status[SCAN_PARENT_COUNT_MAX];

  GIFT_DATA recv_data;				// 受信したデータ
  u8 recv_flag;					// 受信したフラグ
  u8 result_flag[SCAN_PARENT_COUNT_MAX];	// ちゃんと受信しました返事

  //  u8 beacon_data[MYSTERY_BEACON_DATA_SIZE];	// ビーコンデータ
  
} _COMM_STATE_WORK;

static _COMM_STATE_WORK *_pCommStateM = NULL;  ///<　ワーク構造体のポインタ

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
static void _commCheckFunc(TCB_PTR tcb, void* work);  // ステートを実行しているタスク
static void _mysteryParentInit(void);
static void _mysteryParentWaiting(void);

static void _mysteryChildInit(void);
static void _mysteryChildBconScanning(void);
static void _mysteryChildConnecting(void);
static void _mysteryChildSendName(void);
static void _mysteryChildWaiting(void);

#define   _CHANGE_STATE(state, time)  _changeState(state, time)

//==============================================================================
/**
 * 通信管理ステートの初期化処理
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _commStateInitialize(MYSTERYGIFT_WORK *pMSys)
{
  void* pWork;

  if(_pCommStateM != NULL)		// すでに動作中の場合必要ない
    return;

  CommCommandMysteryInitialize((void *)pMSys);
  // 初期化
  _pCommStateM = (_COMM_STATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_STATE_WORK));
  MI_CpuFill8(_pCommStateM, 0, sizeof(_COMM_STATE_WORK));
  _pCommStateM->timer = _START_TIME;
  _pCommStateM->pTcb = TCB_Add(_commCheckFunc, NULL, _TCB_COMMCHECK_PRT);
  _pCommStateM->pMSys = pMSys;
  CommRandSeedInitialize(&_pCommStateM->sRand);
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
    _pCommStateM->state = state;
    _pCommStateM->timer = time;
}


//==============================================================================
/**
 * 親機として初期化を行う
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryParentInit(void)
{
  int i;
  //  MYSTERYGIFT_WORK *wk;
  
  // まずは自分と接続をする
  if(!CommIsConnect(CommGetCurrentID()))
    return;

  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++)
    _pCommStateM->result_flag[i] = FALSE;
  // 親機としての準備が完了したので、ビーコン情報を添付する
  //  wk = PROC_GetWork(MyseryGiftGetProcp());
  // ↓このデータは送らねば
  CommInfoSendPokeData();
  _CHANGE_STATE(_mysteryParentWaiting, 0);
}


//==============================================================================
/**
 * 親機として待機中
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryParentWaiting(void)
{
  int i;
  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
    if(_pCommStateM->status[i] == NULL && CommIsConnect(i) == TRUE){
      _pCommStateM->status[i] = CommInfoGetMyStatus(i);
      if(_pCommStateM->status[i]){
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("子機 %d から返信がありました！\n", i);
#endif
      }
    }
  }
}


//==============================================================================
/**
 * 子機の初期化
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildInit(void)
{
  if(!CommIsVRAMDInitialize()){
    return;
  }
  _CHANGE_STATE(_mysteryChildBconScanning, 0);
}


//==============================================================================
/**
 * 子機待機状態  親機ビーコン収集中
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildBconScanning(void)
{
  //  CommParentBconCheck();
}


//==============================================================================
/**
 * 子機待機状態  親機に許可もらい中
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildConnecting(void)
{
  CommStateConnectBattleChild(_pCommStateM->connectIndex);
  _CHANGE_STATE(_mysteryChildSendName, 0);
}


//==============================================================================
/**
 * 子機待機状態  親機に情報を送信
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildSendName(void)
{
  if(!CommIsBattleConnectingState())
    return;

  _pCommStateM->recv_flag = 0;
  CommInfoSendPokeData();
  CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
  _CHANGE_STATE(_mysteryChildWaiting, 0);
}


//==============================================================================
/**
 * 子機待機状態
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildWaiting(void)
{
  //Exitを受け取ったら子機切断
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
  if(_pCommStateM==NULL){
    TCB_Delete(tcb);
  } else {
    if(_pCommStateM->state != NULL){
      PTRStateFunc state = _pCommStateM->state;
      if(!_pCommStateM->bStateNoChange){
	state();
      }
    }
  }
}


//==============================================================================
/**
 * 「ふしぎなおくりもの」の親としての通信処理開始
 * @param   serviceNo  通信サービス番号
 * @retval  none
 */
//==============================================================================
void CommMysteryStateEnterGiftParent(MYSTERYGIFT_WORK *pMSys, SAVEDATA *sv, int serviceNo)
{
  if(CommIsInitialize())
    return;      // つながっている場合今は除外する

  CommStateEnterMysteryParent(sv, serviceNo);
  _commStateInitialize(pMSys);
  _CHANGE_STATE(_mysteryParentInit, 0);
}

//==============================================================================
/**
 * 準備が完了した子の数を返す
 * @param   none
 * @retval  none
 */
//==============================================================================
int CommMysteryGetCommChild(void)
{
  int i, max;
  for(max = 0, i = 1; i < SCAN_PARENT_COUNT_MAX; i++)
    if(_pCommStateM->status[i])	max++;
  return max;
}

//==============================================================================
/**
 * 親機：繋がっている子機へデータを送る
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommMysterySendGiftDataParent(const void *p, int size)
{
  CommSendHugeData_ServerSide(CM_GIFT_DATA, p, size);
}










//==============================================================================
/**
 * 「ふしぎなおくりもの」の子としての通信処理開始
 * @param   serviceNo  通信サービス番号
 * @retval  none
 */
//==============================================================================
void CommMysteryStateEnterGiftChild(MYSTERYGIFT_WORK *pMSys, int serviceNo)
{
  SAVEDATA *sv;
  if(CommIsInitialize())
    return;      // つながっている場合今は除外する

  // 通信ヒープ作成
  sv = ((MAINWORK *)PROC_GetParentWork(MyseryGiftGetProcp()))->savedata;
  CommStateEnterMysteryChild(sv, serviceNo);
    _commStateInitialize(pMSys);
    _CHANGE_STATE(_mysteryChildInit, 0);
}


//==============================================================================
/**
 * 「ふしぎなおくりもの」の子としての通信処理開始
 * @param   connectIndex 接続する親機のIndex
 * @retval  none
 */
//==============================================================================
void CommMysteryStateConnectGiftChild(int connectIndex)
{
  _pCommStateM->connectIndex = connectIndex;
  _CHANGE_STATE(_mysteryChildConnecting, 0);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	有効なビーコン情報を受け取ったか返す
 * @param	NONE
 * @return	0～15: 受け取った -1: 受け取らなかった
 *		※受け取った場合はbeacon_dataに情報がコピーされる
*/
//--------------------------------------------------------------------------------------------
int CommMysteryCheckParentBeacon(MYSTERYGIFT_WORK *wk)
{
  int i;
  GIFT_BEACON *p;

  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
    p = (GIFT_BEACON *)CommMPGetBeaconTempData(i);
    if(p){
      if(p->event_id){
#if 0
	memcpy(&wk->gift_data.gd2.b, p, sizeof(GIFT_DATA2_B));
#endif
	memcpy(&wk->gift_data.beacon, p, sizeof(GIFT_BEACON));
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("ビーコンデータを %d に受け取りました！\n", i);
	OS_Printf("event_id = %d\n", p->event_id);
	OS_Printf("have_card = %d\n", p->have_card);
#endif
	return i;
      }
    }
  }
  return -1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ちゃんとデータを受け取れた事を親機へ伝達
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
void CommMysteryResultRecvData(void)
{
  CommSendData(CM_RECV_RESULT, NULL, 0);
}


//==============================================================================
/**
 * おくりもの　のデータを受け取った際に呼ばれるコールバック
 * @param   netID    送信してきたID
 * @param   size     送られてきたデータサイズ
 * @param   pData    おくりものへのデータポインタ
 * @retval  none
 */
//==============================================================================
void CommMysteryGiftRecvPlace(int netID, int size, void* pBuff, void* pWork)
{
  /* 知らない相手からデータが送られてきたら無視 */
  if(_pCommStateM->connectIndex != netID)
    return;
  _pCommStateM->recv_flag = 1;
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("おくりもののデータを受け取りました！\n");
#endif
}

//==============================================================================
/**
 * @brief	おくりもののデータが送られてきたか返す
 * @param	NONE
 * @return	TRUE: 送られてきた : FALSE: 送られてきていない
 */
//==============================================================================
int CommMysteryCheckRecvData(void)
{
  return _pCommStateM->recv_flag;
}

//==============================================================================
/**
 * おくりもの　のデータサイズを返す
 * @param   none
 * @retval  データサイズ
 */
//==============================================================================
int CommMysteryGetRecvPlaceSize(void)
{
  return sizeof(GIFT_DATA);
}

//==============================================================================
/**
 * おくりもの　を格納するポインタを返す
 * @param   none
 * @retval  ポインタ
 */
//==============================================================================
u8* CommGetMysteryGiftRecvBuff( int netID, void* pWork, int size)
{
  return (u8 *)&_pCommStateM->recv_data;
}

//==============================================================================
/**
 * おくりもの　が送られてきたことを送る
 * @param   none
 * @retval  ポインタ
 */
//==============================================================================
void CommMysterySendRecvResult(int netID, int size, void* pBuff, void* pWork)
{
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("%d %d %08X %08X\n", netID, size, pBuff, pWork);
#endif

  _pCommStateM->result_flag[netID] = TRUE;
}

//==============================================================================
/**
 * 接続されているすべての子機から返事が返ってきたか返す
 * @param   none
 * @retval  TRUE: 返ってきた : FALSE: 返ってきていない
 */
//==============================================================================
int CommMysteryGiftGetRecvCheck(void)
{
  int i;
  for(i = 1; i < SCAN_PARENT_COUNT_MAX; i++){
    if(CommInfoGetMyStatus(i) && _pCommStateM->status[i] && _pCommStateM->result_flag[i] != TRUE)
      return FALSE;
  }
  return TRUE;
}


//==============================================================================
/**
 * 通信を終了させる
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommMysteryExitGift(void)
{
  sys_FreeMemory(HEAPID_COMMUNICATION, _pCommStateM);
  _pCommStateM = NULL;
  CommStateExitBattle();
}

/*  */
