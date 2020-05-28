//=============================================================================
/**
 * @file	comm_union.c
 * @brief	ユニオンルーム制御処理
 * @author	Akito Mori
 * @date    2005.12.10
 */
//=============================================================================

//#define OEKAKI_ONLY_TALK
//#define	RECORD_ONLY_TALK

#include "common.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "communication/wh_config.h"
#include "communication/wh.h"
#include "fieldsys.h"
#include "field/field.h"
#include "../fielddata/script/connect_def.h"
#include "../fielddata/script/union_def.h"
#include "system/wordset.h"
#include "system/pms_data.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_trtype.h"
#include "msgdata/msg_union.h"

#include "comm_command_field.h"
#include "comm_union_def.h"
#include "script.h"
#include "comm_union_beacon.h"
#include "application/trainer_card.h"
#include "tr_card_setup.h"
#include "field/union_beacon_tool.h"


#include "../application/oekaki/comm_command_oekaki.h"


#define UNION_PRINT_ON

#ifdef UNION_PRINT_ON

#define PRINT( str ) 			OS_Printf( str )
#define PRINT2( str , param) 	OS_Printf( str , param )

#else

#define PRINT( str ) 
#define PRINT2( str , param) 


#endif

//==============================================================================
//	定数宣言
//==============================================================================
#define TALK_OBJ_MAX			( 10 )
#define SUB_OBJ_MAX				( TALK_OBJ_MAX*4 )
#define _PARENT_WAIT_TIME 	 	( 40 ) ///親としてのんびり待つ時間
#define _CHILD_P_SEARCH_TIME 	( 12 )
#define _FINALIZE_TIME 			(  2 )
#define _EXIT_SENDING_TIME 		(  5 )
#define _CONNECT_RETRY_NUM 		(  2 )
#define _CHILD_CONNECT_WAIT		( 3*60 )

#define PARENT_UNIONROOM_TGID	( 0x1234 )

#define UNION_CHILD_STATUS_SEND_RETRY_WAIT	( 120 )

enum{
	NO_OBJ=0,
	FALL_OBJ,
	TALKOK_OBJ,
	RISE_OBJ,
};

#define START_TIME ( 40 )
#define _TCB_UNIONSTATE_PRT   (10)    ///< フィールドを歩く通信の監視ルーチンのPRI

enum{
	DS_CONNECT_START=1,
	MP_CONNECT_START,
};

//==============================================================================
//	型宣言
//==============================================================================

// コールバック関数の書式
typedef void (*PUnionRoomFunc)(COMM_UNIONROOM_WORK *cuw);


// 話しかけられるOBJの構造体
typedef struct{
	u16 arrow;
	u16 status;
}MAIN_OBJ_CONT;

// 話しかけOBJの周りにつくサブOBJの構造体
typedef struct{
	u16 arrow;
	u16 status;
}SUB_OBJ_CONT;

// ユニオンルーム用ワーク構造体
struct COMM_UNIONROOM_WORK{
	FIELDSYS_WORK		*fsys;
	SAVEDATA			*savedata;
	MYSTATUS			*mystatus;
	
	TCB_PTR	           UnionStateTask;
	PUnionRoomFunc     state;
	int                timer;

	u32					CommConnectId;				// 接続しにいくOBJID
	u32					CommConnectResult;			// 接続結果を返す
	int 				CommConnectStartFlag;
	int 				CommConnectStartWait;
	int					CommConnectRetry;
	int					CommNextProcOn;
	u32					CommChildSelectEvent;
	u32					ScriptSelectWork;			// 選択結果を保存
	u32					InviteWork;					// 通信で提示された内容を保存
	u32					ScriptYesNoWork;			// はい・いいえの結果を保存

	u32					UnionEventWork;				// 行う内容（カード・戦闘・交換・チャット）
	u32					UnionEndConnectFlag;		// 通信終了
	
	MAIN_OBJ_CONT	   MainObjCont[TALK_OBJ_MAX];		// 話しかけられる１０人
	SUB_OBJ_CONT	   SubObjCont[SUB_OBJ_MAX];		// メインの周りにいる４人（ｘ１０）
	WMBssDesc		   *UnionBeaconTbl[SCAN_PARENT_COUNT_MAX];

	MATHRandContext32  pRand;						// WEPキー乱数
	int connectIndex;

	int objwork;
	int objwait;

	u16 busyflag;
	u8  battleSelect[2];							// 戦闘前のポケモンリストの結果を受信する

	PMS_DATA			MyPmsData;					// スタートメニューの「チャット」で簡易会話を設定した場合
	BOOL				MyPmsPutFlag;				// この領域に作成した簡易会話がコピーされる

	TR_CARD_DATA 		*my_trcard;					// 自分のトレーナーカード
	TR_CARD_DATA 		*recv_trcard[2];			// 相手のトレーナーカード

#ifdef PM_DEBUG
    u32					debugTimer;
#endif
};


/*** 関数プロトタイプ ***/
static COMM_UNIONROOM_WORK* _commStateInitialize(FIELDSYS_WORK* fsys);
static void _UnionStart(COMM_UNIONROOM_WORK *cuw);
static void _UnionRestart( COMM_UNIONROOM_WORK *cuw );
static void _changeState(COMM_UNIONROOM_WORK *cuw, PUnionRoomFunc state, int time);
static void _stateConnectEnd(COMM_UNIONROOM_WORK *cuw);
static void _stateEnd(COMM_UNIONROOM_WORK *cuw);
static void CommStateFinalize(COMM_UNIONROOM_WORK *cuw);
static void _underChildConnecting(COMM_UNIONROOM_WORK *cuw);
static void _underParentInfoSend(COMM_UNIONROOM_WORK *cuw);
static void _underParentConnect(COMM_UNIONROOM_WORK *cuw);
static void _underChildSelectWait(COMM_UNIONROOM_WORK *cuw);
static void _underChildInfoSendSuccess( COMM_UNIONROOM_WORK *cuw );
static void _ConnectInfoClear( COMM_UNIONROOM_WORK *cuw );
static void _underChildEndEventState( COMM_UNIONROOM_WORK *cuw );
static void CommUnion_EventFlagClear( COMM_UNIONROOM_WORK *cuw);
static int  MyStatusCheck( void );
static int GetGroupTalk_ListenNo( COMM_UNIONROOM_WORK *cuw, int no );
static int GetStartTalk_No(int event, int sex, WORDSET *wordset );
static void _UnionBeaconSet( COMM_UNIONROOM_WORK *cuw );


static void UnionBeaconClear( UNION_BEACON_STATE *beacon );






//==============================================================================
/**
 * ユニオンルームにはいった時の通信処理
 * @param   pFSys FIELDSYS_WORK
 * @retval  none
 */
//==============================================================================
COMM_UNIONROOM_WORK *Comm_UnionRoomInit(FIELDSYS_WORK* fsys)
{

	COMM_UNIONROOM_WORK *cuw = NULL;

	GF_ASSERT(fsys!=NULL && "fsysがNULL");

    if(fsys->union_work!=NULL){ // つながっている場合今は除外する
        return NULL;
    }
    // 通信ヒープ作成
    if(sys_CreateHeapLo( HEAPID_BASE_APP, HEAPID_UNIONROOM, 0xa80 )){
		OS_Printf("HEAPID_UNION 作成成功\n");
	}

	// ユニオンルームワーク確保
    cuw = _commStateInitialize(fsys);
	if(cuw==NULL){
		cuw = fsys->union_work;
	}

	// フィールド用通信コマンドコールバック設定
    CommCommandFieldInitialize((void*)fsys);

	// 通信接続人数を２人に制限
    CommStateSetLimitNum(2);
	

//  CommStateUnionBconCollection( SaveData_GetMyStatus(GameSystem_GetSaveData(fsys)) );

    // 地下ステートの遷移のため初期化
	PRINT("Union子機検索開始\n");
    _changeState(cuw, _UnionBeaconSet, START_TIME);
	OS_Printf("sizeof(MYSTATUS)=%d \n",MyStatus_GetWorkSize());

	OS_Printf("COMM_UNIONROOM_WORK =%d \n",sizeof(COMM_UNIONROOM_WORK));

	return cuw;
}
#ifdef PM_DEBUG

static COMM_UNIONROOM_WORK *debug_cuw;

#endif
//==============================================================================
/**
 * ユニオンルームから出るとき
 *
 * @param   fsys		
 *
 * @retval  none		
 */
//==============================================================================
void Comm_UnionFinalize(FIELDSYS_WORK *fsys)
{
    if(fsys->union_work==NULL){  // すでに終了している
       return;
    }
    _changeState(fsys->union_work, _stateConnectEnd, _EXIT_SENDING_TIME);
}


//------------------------------------------------------------------
/**
 * ユニオンルーム初期化シーケンス
 *
 * @param   fsys		
 *
 * @retval  COMM_UNIONROOM_WORK*		
 */
//------------------------------------------------------------------
static COMM_UNIONROOM_WORK* _commStateInitialize(FIELDSYS_WORK* fsys)
{
    void* pWork;
	SAVEDATA *savedata;
	COMM_UNIONROOM_WORK *cuw = NULL;

    if(fsys->union_work!=NULL){   // すでにユニオン動作中の場合は後ろのメモリ確保初期化必要ない
        return NULL;
    }
	savedata    = GameSystem_GetSaveData(fsys);

    // UNIONルームBCON収集開始
    CommStateUnionBconCollection( savedata );


    // 初期化
    cuw = (COMM_UNIONROOM_WORK*)sys_AllocMemory(HEAPID_UNIONROOM, sizeof(COMM_UNIONROOM_WORK));
	MI_CpuClear8(cuw, sizeof(COMM_UNIONROOM_WORK) );
    cuw->state = NULL;   // 何もしない
    cuw->timer = START_TIME;
    cuw->UnionStateTask = TCB_Add(_commCheckFunc, cuw, _TCB_UNIONSTATE_PRT);
    cuw->fsys     = fsys;
	cuw->savedata = savedata;
	cuw->mystatus    = SaveData_GetMyStatus(savedata);
//	cuw->partner_trcard = (TR_CARD_DATA*)sys_AllocMemory(HEAPID_BASE_SYSTEM, 1624+16);
//	cuw->my_trcard      = (TR_CARD_DATA*)sys_AllocMemory(HEAPID_BASE_SYSTEM, 1624+16);
	

	CommUnion_EventFlagClear(cuw);

//    _debugTimerStart();
    CommRandSeedInitialize(&cuw->pRand);

#ifdef PM_DEBUG
	debug_cuw = cuw;
#endif
	return cuw;
}	



//------------------------------------------------------------------
/**
 * @brief   ユニオンルーム開始時にビーコンを代入する
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _UnionBeaconSet( COMM_UNIONROOM_WORK *cuw )
{
	PMS_DATA pmsdata;

	if(CommMPIsInitialize()){
		// ユニオンルームデフォルト会話セット
		PMSDAT_SetupDefaultUnionMessage( &pmsdata );
		// ビーコンデータに反映させる
		Union_PMSReWrite( &pmsdata );		
		Union_SetMyPmsData( cuw, &pmsdata );		// ユニオンワークで保存しておき下画面に表示させる
	    _changeState(cuw, _UnionStart, START_TIME);
	}
}

static int debug_parent;

//==============================================================================
/**
 * ユニオンルームスタート【ユニオンタスク遷移】
 * @param   none
 * @retval  none
 */
//==============================================================================

#define _FIRST_SEND	( 0 )

static void _UnionStart(COMM_UNIONROOM_WORK *cuw)
{
	// 親機接続されたか？
    if(CommStateIsUnionParentConnectSuccess()){
        OS_TPrintf("親機接続\n");
		debug_parent = 0;
		_changeState(cuw, _underParentInfoSend, _FIRST_SEND);
        return;
    }

	// 話しかけを始めたか？
    if(cuw->CommConnectStartFlag!=0){
        cuw->CommConnectRetry = _CONNECT_RETRY_NUM;
        /// indexで接続を開始します
		if(cuw->CommConnectStartFlag == DS_CONNECT_START){
				if(cuw->CommChildSelectEvent==UNION_CHILD_SELECT_RECORD){
					// レコードコーナー子機乱入接続開始
					CommStateUnionRecordCornerChild(cuw->CommConnectId);
				}else {
					// 通常子機接続開始
			        CommStateUnionConnectStart(cuw->CommConnectId);   
				}
		}else if(cuw->CommConnectStartFlag == MP_CONNECT_START){
            // 通信コマンドを交換リスト用に変更
            CommCommandOekakiBoardInitialize( NULL );
			CommStateUnionPictureBoardChild(cuw->CommConnectId);
		}
		
        _changeState(cuw, _underChildConnecting, _CHILD_P_SEARCH_TIME);
		return;
	}
}

//------------------------------------------------------------------
/**
 * $brief   通信終了後切断する遊びから戻ってきたときのシーケンス
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _UnionRestart( COMM_UNIONROOM_WORK *cuw )
{
	// 通信システム再開をまつ
    if(CommStateUnionIsRestartSuccess()==TRUE){
		
	    // フィールド用通信コマンドコールバックに戻す
    	CommCommandFieldInitialize((void*)cuw->fsys);

        _changeState(cuw, _UnionStart, _FINALIZE_TIME);
		
	}
}

//------------------------------------------------------------------
/**
 * $brief   現在子機が何人接続しているか？
 *
 * @param   none		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int MyStatusCheck( void )
{
	int i,result;
	MYSTATUS *status;

	result = 0;

	// 1～４なので子機のステータスを受信するのを検知したい
	for(i=1;i<5;i++){
		status = CommInfoGetMyStatus(i);
		if(status!=NULL){
			result++;
		}
	}

	// 誰か子機からきたか？
	return (result>=1);
}


//==============================================================================
/**
 * 親機になる 会話をする【ユニオンタスク遷移】
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _underParentInfoSend(COMM_UNIONROOM_WORK *cuw)
{
    if(cuw->timer>0){
        cuw->timer--;
        return;
    }
	
	OS_Printf("親機接続%d回目\n", debug_parent);
	debug_parent++;
    if(CommIsChildsConnecting() && MyStatusCheck()==1){   // 
		// 親の基本データ送信
        CommInfoSendPokeData();
		
		// 子機がいないのをエラー扱いにするかどうかをSET
        CommStateSetErrorCheck(TRUE,TRUE);

		// ここのfsysがNULLのことがある。
		// 親機としての接続イベント開始
//		EventSet_Script( cuw->fsys, SCRID_CONNECT_UNION_RECEIVE_OBJ, NULL );

		// 「パーティーになったよ」ビーコンに変える
		Union_BeaconChange( UNION_PARENT_MODE_PARTY );
		_changeState(cuw,_underParentConnect, _FIRST_SEND);
	}

	// 切断していたら元にもどす
	if(CommStateIsUnionParentConnectSuccess()==0){
    	CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
	    _changeState(cuw,_UnionRestart, _FINALIZE_TIME);
		
	}

}


//------------------------------------------------------------------
/**
 * $brief   親機接続中(あとはコールバックにおまかせ）
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underParentConnect(COMM_UNIONROOM_WORK *cuw)
{
    if(CommIsChildsConnecting()){   // 自分以外がつながったら親機固定
		
	}else{
	
	}

	// 切断したので元の操作に戻る
    if(0 == CommIsChildsConnecting()){
		// 接続失敗したので、終了して元の親子切り替えの流れに戻る
//    	CommCommandFieldInitialize((void*)cuw->fsys);
		OS_TPrintf("子機が切れたから bitmap=%02x status=%d connectnum=%d childconnect=%d\n", WH_GetBitmap(), MyStatusCheck(), CommGetConnectNum(), CommIsChildsConnecting());
    	CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
	    _changeState(cuw,_UnionRestart, _FINALIZE_TIME);
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

static void _changeState(COMM_UNIONROOM_WORK *cuw, PUnionRoomFunc state, int time)
{
	
    cuw->state = state;
    cuw->timer = time;
}

//==============================================================================
/**
 * 通信管理ステートの処理
 * @param
 * @retval  none
 */
//==============================================================================

static WMBssDesc *debugBsstable[16];

void _commCheckFunc(TCB_PTR tcb, void* work)
{
	COMM_UNIONROOM_WORK *cuw = (COMM_UNIONROOM_WORK*)work;
#ifdef PM_DEBUG
    cuw->debugTimer++;
#endif

#ifdef PM_DEBUG

	if(sys.trg&PAD_BUTTON_START){
		UNION_BEACON_STATE state;
//		if(cuw->busyflag = UNION_PARENT_MODE_FREE){
//			cuw->busyflag = UNION_PARENT_MODE_BUSY;

//			MI_CpuClear8(&state, sizeof(UNION_BEACON_STATE) );
//			state.c_face[0] = 1;
//			state.mode      = UNION_PARENT_MODE_BUSY;

//		}else{
//			cuw->busyflag = UNION_PARENT_MODE_FREE;
//			state.mode = UNION_PARENT_MODE_FREE;
//		}
//		CommMPSetMyRegulation(&state);	// 「忙しい」にビーコン書き換え
//		CommMPFlashMyBss();
	}

	if(sys.trg&PAD_BUTTON_SELECT){
		OS_Printf("自分の国番号 %d \n",MyStatus_GetRegionCode( cuw->mystatus ));
	}
#endif

    if(cuw==NULL){
        TCB_Delete(tcb);
    }
    else{
		int i;
		WMBssDesc *tmp;

		for(i=0;i<SCAN_PARENT_COUNT_MAX;i++){
			cuw->UnionBeaconTbl[i] = CommMPGetWMBssDesc(i);
			debugBsstable[i]       = cuw->UnionBeaconTbl[i]; 
		}


        if(cuw->state != NULL){
            cuw->state(cuw);
        }
    }
}


//==============================================================================
/**
 * @brief  終了処理開始
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _stateConnectEnd(COMM_UNIONROOM_WORK *cuw)
{
    if(cuw->timer != 0){
        cuw->timer--;
        return;
    }
    // 切断する
    CommStateExitUnion();
    _changeState(cuw,_stateEnd, 0);
}

//------------------------------------------------------------------
/**
 * 通信終了シーケンス
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _stateEnd(COMM_UNIONROOM_WORK *cuw)
{
    if(CommIsInitialize()){
        return;
    }
    CommStateFinalize(cuw);
}

//==============================================================================
/**
 * 子機となって接続中【ユニオンタスク遷移】
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _underChildConnecting(COMM_UNIONROOM_WORK *cuw)
{
    if(1 == CommStateIsUnionConnectSuccess()){
        
//      CommStateSetErrorCheck(TRUE,TRUE);

		// 接続成功なら親機に情報を送る
        CommInfoSendPokeData();
		_changeState(cuw,_underChildInfoSendSuccess, 3);
        OS_TPrintf("親機に接続したので子機情報送信\n");
        return;
    }else if(CommIsChildsConnecting()){   
		// 逆に親として繋がった。(もう無い）
		cuw->CommConnectStartFlag = 0;
		cuw->CommConnectResult    = UNION_CONNECT_PARENT;
		
        OS_TPrintf("接続にいったつもりが親機接続\n");
        _changeState(cuw,_underParentInfoSend, 0);
	}
    if(0 == CommStateIsUnionConnectSuccess()){
		// 接続待機中
        OS_TPrintf("接続が成功しない\n");
        return;
    }
	// 接続失敗したので、イベントの終了待ちをして元の親子切り替えの流れに戻る
   	_changeState(cuw,_underChildEndEventState, _FINALIZE_TIME);
	cuw->CommConnectStartWait = 0;
	cuw->CommConnectResult    = UNION_CONNECT_FAILED;
	cuw->CommConnectStartFlag = 0;
	cuw->UnionEndConnectFlag  = 0;
}

//------------------------------------------------------------------
/**
 * @brief   子機接続に失敗したらイベント終了を待つ
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underChildEndEventState( COMM_UNIONROOM_WORK *cuw )
{
	if(!FieldEvent_Check(cuw->fsys)){

	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
		Union_BeaconChange( UNION_PARENT_MODE_FREE );
   		_changeState(cuw,_UnionRestart, _FINALIZE_TIME);

	}
	
}

//------------------------------------------------------------------
/**
 * @brief   子機の情報送信が成功した
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _underChildInfoSendSuccess( COMM_UNIONROOM_WORK *cuw )
{

	// 接続中
    if(1 == CommStateIsUnionConnectSuccess()){
		if(CommInfoGetMyStatus(CommGetCurrentID())!=NULL){
			PRINT("接続成功！！！！\n");
			cuw->CommConnectStartFlag = 0;
			cuw->CommConnectResult    = UNION_CONNECT_SUCCESS;
			cuw->UnionEndConnectFlag  = 0;

	        CommStateSetErrorCheck(TRUE,TRUE);
			_changeState(cuw,_underChildSelectWait, 3);
		}
		OS_Printf("子機接続中\n");
    }else if(0 == CommStateIsUnionConnectSuccess()){
	// 接続が切れた
		
		OS_Printf("接続が切れたけどもしかしてイベント中じゃない？\n");
		
    	//CommCommandFieldInitialize((void*)cuw->fsys);
	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
    	_changeState(cuw,_UnionRestart, _FINALIZE_TIME);

		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_FAILED;
		cuw->CommConnectStartFlag = 0;
		cuw->UnionEndConnectFlag  = 0;
	}
	
}

//------------------------------------------------------------------
/**
 * $brief   子機として通信接続した後はコールバック関数内で
 *          処理することが多いので、切断だけは検地するようにする【ユニオンタスク遷移】
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void  _underChildSelectWait(COMM_UNIONROOM_WORK *cuw)
{
//    if(cuw->timer==1){
//        CommInfoSendPokeData();
//    }

    if(0 == CommStateIsUnionConnectSuccess()){
    	//CommCommandFieldInitialize((void*)cuw->fsys);
	    CommStateUnionBconCollectionRestart();
		CommUnion_EventFlagClear(cuw);
    	_changeState(cuw,_UnionRestart, _FINALIZE_TIME);
		return ;
	}
    // 接続タイムアウト
//    if(cuw->timer!=0){
//        cuw->timer--;
//        return;
//    }
}

//------------------------------------------------------------------
/**
 * ユニオン通信用ワーク解放
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommStateFinalize(COMM_UNIONROOM_WORK *cuw)
{
    void* pWork;

    if(cuw==NULL){  // すでに終了している
        return;
    }
    TCB_Delete(cuw->UnionStateTask);
//    sys_FreeMemoryEz(cuw->partner_trcard);
  //  sys_FreeMemoryEz(cuw->my_trcard);
    sys_FreeMemoryEz(cuw);
    sys_DeleteHeap(HEAPID_UNIONROOM);
//    cuw = NULL;
}



//==============================================================================
/**
 * COMM_UNIONROOM_WORKが持っているFIELDSYS_WORKのポインタを返す
 *
 * @param   cuw		
 *
 * @retval  FIELDSYS_WORK*		
 */
//==============================================================================
FIELDSYS_WORK* Union_FielsSysPtrGet(COMM_UNIONROOM_WORK *cuw)
{
	return cuw->fsys;
}

//==============================================================================
/**
 * 通信から取得したビーコンのポインタを返す(comm_union_view.c用)
 *
 * @param   cuw		
 * @param   no		
 *
 * @retval  WMBssDesc*		
 */
//==============================================================================
WMBssDesc* Union_BeaconPtrGet(COMM_UNIONROOM_WORK *cuw, int no)
{
	return cuw->UnionBeaconTbl[no];
}

//==============================================================================
/**
 * $brief   
 *
 * @param   cuw		
 *
 * @retval  int		
 */
//==============================================================================
int Union_ConnectIndexGet(COMM_UNIONROOM_WORK *cuw)
{
	return cuw->connectIndex;
}

static UNION_BEACON_STATE *debug_beacon;

//==============================================================================
/**
 * 話しかけOBJのIDを貰って接続のために情報として使う
 *
 * @param   cuw			COMM_UNIONROOM_WORK
 * @param   no			OBJID(扱うときは-1する）
 *
 * @retval  int			通信開始できるか？どうかを返す
 *						UNION_PARENT_CONNECT_OK:話掛け通信ができる
 *						UNION_PARENT_OEKAKI_OK:お絵かき乱入通信ができる
 *						UNION_PARENT_CONNECT_NG:通信できない
 */
//==============================================================================
int Union_ConnectIdSet( COMM_UNIONROOM_WORK *cuw, int no )
{
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	// スクリプトからは＋１でくるので１引く
	no--;
	
	status       = CommMPGetBconMyStatus( no );

	// 話し掛け前もワーククリア
	Union_CommWorkClear( cuw );

	// statusがNULLだった場合は話し掛けに失敗する（ごめんいそがしいんだ）
	if(status==NULL){
		return UNION_PARENT_CONNECT_NG;
	}

	gfbssdata    = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[no]->gameInfo.userGameInfo;
	beaconState  = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;
	debug_beacon = beaconState;

	OS_Printf("ビーコンは%d \n",beaconState->mode);

#ifdef OEKAKI_ONLY_TALK
	return UNION_PARENT_OEKAKI_OK;
#endif

	switch(beaconState->mode){
	case UNION_PARENT_MODE_FREE:
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_OEKAKI_FREE:
		return UNION_PARENT_OEKAKI_OK;
		break;
	case UNION_PARENT_MODE_RECORD_FREE:
		return UNION_PARENT_RECORD_OK;
		break;
	case UNION_PARENT_MODE_GURUGURU_FREE:
		return UNION_PARENT_GURUGURU_OK;
		break;
	case UNION_PARENT_MODE_BUSY:		case UNION_PARENT_MODE_CARDNOW:	case UNION_PARENT_MODE_BATTLENOW:
	case UNION_PARENT_MODE_TRADENOW:	case UNION_PARENT_MODE_OEKAKINOW: case UNION_PARENT_MODE_PARTY:
		return UNION_PARENT_CONNECT_NG;
		break;
	}
	return UNION_PARENT_CONNECT_NG;
}


//==============================================================================
/**
 * $brief   相手のビーコン状態を確認した上で接続に行く
 *
 * @param   cuw		
 * @param   no		OBJID（＋１されているので-1して扱う）
 *
 * @retval  int		UNION_CONNECT_OKかUNION_CONNECT_NG
 */
//==============================================================================
int Union_ConnectStart( COMM_UNIONROOM_WORK *cuw, int objno, u16 type )
{
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;
	// スクリプトからは＋１でくるので１引く
	objno--;
	
	status      = CommMPGetBconMyStatus( objno );
	gfbssdata   = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[objno]->gameInfo.userGameInfo;
	beaconState = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;
	debug_beacon = beaconState;


	// 相手の通信状態を確認して接続ONかNGかを判断する
	switch(beaconState->mode){
	// フリー・レコードコーナー募集中・ぐるぐる交換募集中の場合はデータシェアリング通信
	case UNION_PARENT_MODE_GURUGURU_FREE:
		if(type!=UNION_PARENT_GURUGURU_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommChildSelectEvent = UNION_CHILD_SELECT_GURUGURU;
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = MP_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_RECORD_FREE:
		if(type!=UNION_PARENT_RECORD_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommChildSelectEvent = UNION_CHILD_SELECT_RECORD;
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = DS_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	case UNION_PARENT_MODE_FREE:
		if(type!=UNION_PARENT_CONNECT_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = DS_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	// おえかき募集中の場合はMP通信
	case UNION_PARENT_MODE_OEKAKI_FREE:
		if(type!=UNION_PARENT_OEKAKI_OK){
			return UNION_PARENT_CONNECT_NG;
		}
		cuw->CommConnectId        = objno;
		cuw->CommConnectStartFlag = MP_CONNECT_START;
		cuw->CommConnectStartWait = 0;
		cuw->CommConnectResult    = UNION_CONNECT_BUSY;
		return UNION_PARENT_CONNECT_OK;
		break;
	// もう通信中の場合もしくは受け入れ状態に無いときは接続しない
	case UNION_PARENT_MODE_BUSY:		case UNION_PARENT_MODE_CARDNOW:	case UNION_PARENT_MODE_BATTLENOW:
	case UNION_PARENT_MODE_TRADENOW:	case UNION_PARENT_MODE_OEKAKINOW: case UNION_PARENT_MODE_PARTY:
		return UNION_PARENT_CONNECT_NG;
		break;

	}
	GF_ASSERT(0);

	return 0;
}

//==============================================================================
/**
 * 話しかけで接続してみた結果を返す
 *
 * @param   cuw		COMM_UNIONROOM_WORK
 *
 * @retval  u32		0:途中	1:成功	2:失敗	3:自分が親になった
 */
//==============================================================================
u32 Union_ConnectResultGet(COMM_UNIONROOM_WORK *cuw )
{
	return cuw->CommConnectResult;
}



//==============================================================================
/**
 * スクリプトにユニオンルームから実行する内容を返す
 *
 * @param   cuw		
 *
 * @retval  u32		
 */
//==============================================================================
u32 Union_ParentStartCommandSet( COMM_UNIONROOM_WORK *cuw )
{
//	u8 start;
//	if(cuw->CommNextProcOn){
//		cuw->CommNextProcOn = 0;
//		start = 1;
//		return cuw->UnionEventWork;
//	}

	// 通信が繋がっている間は親機のコマンドを返すが、切断された場合はすぐに終了を渡す
	if(cuw->UnionEndConnectFlag){
		return UNION_CHILD_SELECT_CANCEL;
	}

	if(CommGetConnectNum()<2){
		return UNION_CHILD_SELECT_CANCEL;
	}

	if(CommGetCurrentID()==0){
		// 親機接続の時の接続確認
		if(CommStateIsUnionParentConnectSuccess()==TRUE){
			return cuw->UnionEventWork;
		}
	}else{
		// 子機接続の時の接続確認
		if(CommStateIsUnionConnectSuccess()==TRUE){
			return cuw->UnionEventWork;
		}
	}
	return UNION_CHILD_SELECT_CANCEL;
	
}


//==============================================================================
/**
 * 子機の選択内容をスクリプトに通知する
 *
 * @param   cuw		
 *
 * @retval  u32		
 */
//==============================================================================
u32 Union_ChildSelectCommandSet( COMM_UNIONROOM_WORK *cuw )
{
	OS_TPrintf("親機が子機の選択待ち 接続状態=%d\n",CommStateIsUnionParentConnectSuccess());

	// 親機接続の時の接続確認
	if(CommStateIsUnionParentConnectSuccess()==TRUE){
		return cuw->CommChildSelectEvent;
	}
	
	// 繋がっていないので、キャンセル
	return UNION_CHILD_SELECT_CANCEL;
}
//==============================================================================
/**
 * スクリプト内で処理された選択肢の結果をもらう
 *
 * @param   cuw			COMM_UNIONROOM_WORK
 * @param   var			スクリプトが実行した選択の種類
 * @param   result		結果（選択によって違う）
 *
 * @retval  none		
 */
//==============================================================================
void Union_ScriptResultGet( COMM_UNIONROOM_WORK *cuw, int var, u32 result)
{
	u8 command = (u8)result;
	
	switch(var){
	case 0:
		if(cuw->UnionEndConnectFlag==0){
			PRINT2("選択内容は%d\n",result);
			cuw->ScriptSelectWork = command;
			CommSendData(CU_PLAYER_SELECT,&command,1);
		}
		break;
	case 1:
		// 親のはい・いいえによる
		if(result==0){
			u8 start = cuw->CommChildSelectEvent;
			CommSendData_ServerSide(CU_START_NEXT, &start, 1);
			cuw->ScriptYesNoWork = result;
		}else{
			u8 start = UNION_CHILD_SELECT_CANCEL;					//親機はいいえを選んだので「キャンセル」を送信
			CommSendData_ServerSide(CU_START_NEXT, &start, 1);
			cuw->ScriptYesNoWork = result;
		}
		break;
	}
}


















//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// comm_command_field.cに登録している通信コールバック関数群
//------------------------------------------------------------------------------


void CommUnionRecvStatus(int netID, int size, void* pBuff, void* pWork)
{
	PRINT("ステータス受信完了\n");
}

void CommUnionRecvTalk(int netID, int size, void* pBuff, void* pWork)
{
	PRINT2("%dからの会話受信完了\n",netID);	
}


//==============================================================================
/**
 * $brief   親がイエス（今はいってない）
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvYes(int netID, int size, void* pBuff, void* pWork)
{
	PRINT2("%dからの  ＹＥＳ\n",netID);	
	
}
//==============================================================================
/**
 * $brief   親がＮＯと言ってきたときのコールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvNo(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;

	PRINT2("%dからの  ＮＯ\n",netID);
	// キャンセルしたので切断・ビーコン収集へ復帰
	//	CommStateExitUnion();
   	_changeState(fsys->union_work, _UnionStart, _FINALIZE_TIME);
	CommUnion_EventFlagClear(fsys->union_work);

}

static int debug_union_select;

//==============================================================================
/**
 * 子機の選択内容を受信する
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvSelect(int netID, int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;
	u8 *no = (u8*)pBuff;
	
	// 終了コマンドを受け取っていなければ選択イベントを採用する
	if(fsys->union_work->UnionEndConnectFlag==0){
		fsys->union_work->CommChildSelectEvent = *no;
		debug_union_select = *no;
	}

	PRINT("選択肢受信完了\n");
	

}

//==============================================================================
/**
 * スタートデータ受信コールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionStartNext(int netID ,int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;
	u8 *no = (u8*)pBuff;
	
	PRINT("イベント開始コマンド到着\n");

	// イベント開始フラグをたてる（親機にイベント開始コマンドを発行させる）
	fsys->union_work->CommNextProcOn = 1;

	// 親機から開始するイベントの種類が送られてくる（親機にも届く）
	fsys->union_work->UnionEventWork = *no;

	if(*no == UNION_CHILD_SELECT_OEKAKI){
		CommStateUnionPictureBoardChange();
//		_changeState(fsys->union_work, _UnionRestart, 0);
	}

}

//==============================================================================
/**
 * 通信終了データ受信コールバック
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionEndConnect(int netID ,int size, void* pBuff, void* pWork)
{
	FIELDSYS_WORK *fsys = (FIELDSYS_WORK *)pWork;

	// 通信終了コマンド
	fsys->union_work->UnionEndConnectFlag = 1;

	OS_TPrintf("親機から終了コマンドを受け取った\n");
}


//==============================================================================
/**
 * @brief   接続終了フラグを返す
 *
 * @param   cuw		
 *
 * @retval  int		
 */
//==============================================================================
int Union_CancelRecv( COMM_UNIONROOM_WORK *cuw )
{
	return cuw->UnionEndConnectFlag;
}

//==============================================================================
/**
 * @brief   親機からキャンセルを送信する
 *
 * @param   core->fsys->union_work		
 *
 * @retval  none		
 */
//==============================================================================
int Union_ParentSendCancel( COMM_UNIONROOM_WORK *cuw, int mes )
{
	// 子機からのイベント選択が到着していなければ送信する
	if(cuw->CommChildSelectEvent==0){
		CommSendData( CU_END_CONNECT_SERVER, NULL, 0);
		return mes;
	}

	return 0;
}

//==============================================================================
/**
 * $brief   トレーナーカードデータのコピー
 *
 * @param   netID		
 * @param   size		
 * @param   pBuff		
 * @param   pWork		
 *
 * @retval  none		
 */
//==============================================================================
void CommUnionRecvTrainerCard(int netID ,int size, void* pBuff, void* pWork )
{
	FIELDSYS_WORK *fsys      = (FIELDSYS_WORK *)pWork;
	TR_CARD_DATA  *trcard    = (TR_CARD_DATA*)pBuff;
	MYSTATUS	  *friend    = CommInfoGetMyStatus(CommGetCurrentID()^1);
	void          *fnoteWork;

//	OS_Printf("id = %d  size = %d ",netID, size);
	// 自分と違うＩＤの人のトレーナーカードデータをコピー
//	if(netID!=CommGetCurrentID()){
//		MI_CpuCopyFast( pBuff, fsys->union_work->recv_trcard[ne,  size );
//	}

	{
		int i,tmp=0;
		u8 *p = (u8*)pBuff;
		for(i=0;i<sizeof(TR_CARD_DATA);i++){
			tmp ^= p[i];
		}
		OS_Printf(" recv id = %d  xor %d \n", netID, tmp);
	}
	trcard->reached = 1;

	// 冒険ノート処理
	if(netID!=CommGetCurrentID()){
		fnoteWork = FNOTE_SioUnionGreetDataMake(  (STRCODE*)MyStatus_GetMyName(friend),  MyStatus_GetMySex(friend), HEAPID_UNIONROOM );
		FNOTE_DataSave( fsys->fnote, fnoteWork, FNOTE_TYPE_SIO );
	}
}


//------------------------------------------------------------------
/**
 * $brief   トレーナーカードデータ受信コールバック関数
 *
 * @param   netID		
 * @param   pWork		
 * @param   size		
 *
 * @retval  u8*		
 */
//------------------------------------------------------------------
u8* getTrainerCardRecvBuff( int netID, void* pWork, int size)
{
	FIELDSYS_WORK *fsys       = (FIELDSYS_WORK *)pWork;
	COMM_UNIONROOM_WORK *cuw  = fsys->union_work;

	
	return (u8*)cuw->recv_trcard[netID];
}


//------------------------------------------------------------------
/**
 * $brief   戦闘前ポケモンリスト結果取得関数
 *
 * @param   netID		
 * @param   pWork		
 * @param   size		
 *
 * @retval  u8*		
 */
//------------------------------------------------------------------
void CommUnionRecvBattlePokeListResult(int netID ,int size, void* pBuff, void* pWork )
{
	FIELDSYS_WORK *fsys       = (FIELDSYS_WORK *)pWork;
	COMM_UNIONROOM_WORK *cuw  = fsys->union_work;
	u8 *result				  = (u8*)pBuff;

	OS_TPrintf("id = %d は  %d\n", netID, *result);

	cuw->battleSelect[netID] = *result;

}



//==============================================================================
/**
 * @brief   戦闘前ポケモンリストを呼んだ結果はどうだったか？
 *
 * @param   cuw		
 *
 * @retval  u16		
 */
//==============================================================================
u16  Union_GetBattleStartCheckResult( COMM_UNIONROOM_WORK *cuw )
{
	int myid = CommGetCurrentID();
	
	// 自分がキャンセルした
	if(cuw->battleSelect[myid]==UNION_BATTLE_POKELIST_NG){
		return UNION_BATTLE_MY_CANCEL;
	}

	// 相手にキャンセルされた
	if(cuw->battleSelect[myid^1]==UNION_BATTLE_POKELIST_NG){
		return UNION_BATTLE_PARTNER_CANCEL;
	}

	// 双方OK
	return UNION_BATTLE_OK;
}

//==============================================================================
/**
 * @brief   ユニオンルーム前のポケモンリストの選択結果を送信する
 *
 * @param   result		
 *
 * @retval  none		
 */
//==============================================================================
void Union_BattlePokeListResult( int result )
{
	u8	command = result;
	CommSendData( CU_BATTLE_PLIST_RET,&command, 1 );
}






//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// ユニオンルーム用ツール
//------------------------------------------------------------------------------


#define TALK_CARD_MAX		( 2 )
#define TALK_TRADE_MAX		( 2 )
#define TALK_BATTLE_MAX		( 4 )
#define TALK_OEKAKI_MAX		( 4 )
#define TALK_RECORD_MAX		( 4 )
#define TALK_GURUGURU_MAX	( 4 )

static const talk_table_card[TALK_CARD_MAX][2]={
	{	msg_union_talkboy_01_03,msg_union_talkgirl_01_03},
	{	msg_union_talkboy_01_04,msg_union_talkgirl_01_04},
};
static const talk_table_oekaki[TALK_OEKAKI_MAX][2]={
	{	msg_union_talkboy_02_09,msg_union_talkgirl_02_09},
	{	msg_union_talkboy_02_10,msg_union_talkgirl_02_10},
	{	msg_union_talkboy_02_11,msg_union_talkgirl_02_11},
	{	msg_union_talkboy_02_12,msg_union_talkgirl_02_12},
};
static const talk_table_battle[TALK_BATTLE_MAX][2]={
	{	msg_union_talkboy_03_05,msg_union_talkgirl_03_05},
	{	msg_union_talkboy_03_06,msg_union_talkgirl_03_06},
	{	msg_union_talkboy_03_07,msg_union_talkgirl_03_07},
	{	msg_union_talkboy_03_08,msg_union_talkgirl_03_08},
};
static const talk_table_trade[TALK_TRADE_MAX][2]={
	{	msg_union_talkboy_04_04,msg_union_talkgirl_04_04},
	{	msg_union_talkboy_04_05,msg_union_talkgirl_04_05},
};
static const talk_table_record[TALK_RECORD_MAX][2]={
	{	msg_union_talkboy_06_09,msg_union_talkgirl_06_09},
	{	msg_union_talkboy_06_10,msg_union_talkgirl_06_10},
	{	msg_union_talkboy_06_11,msg_union_talkgirl_06_11},
	{	msg_union_talkboy_06_12,msg_union_talkgirl_06_12},
};
static const talk_table_guruguru[TALK_GURUGURU_MAX][2]={
	{	msg_union_talkboy_07_10,msg_union_talkgirl_07_10},
	{	msg_union_talkboy_07_11,msg_union_talkgirl_07_11},
	{	msg_union_talkboy_07_12,msg_union_talkgirl_07_12},
	{	msg_union_talkboy_07_13,msg_union_talkgirl_07_13},
};
// ゲーム開始時のメッセージ
static const talk_start_table[][2]={
	{ msg_union_talkboy_01_03,msg_union_talkgirl_01_03,},	// カード
	{ msg_union_talkboy_03_02,msg_union_talkgirl_03_02,},	// たいせん
	{ msg_union_talkboy_04_02,msg_union_talkgirl_04_02,},	// こうかん
	{ msg_union_talkboy_02_02,msg_union_talkgirl_02_02,},	// おえかき」
	{ msg_union_talkboy_06_02,msg_union_talkgirl_06_02,},	// レコード」
	{ msg_union_talkboy_07_02,msg_union_talkgirl_07_02,},	// ぐるぐる交換」
};
// 話しかけが成功したとき
static const talk_start_child_table[2]={
	msg_union_talkboy_00_02,msg_union_talkgirl_00_02
};
// 話しかけがしっぱいしたとき
static const talk_failed_child_table[2]={
	msg_union_talkboy_00_05,msg_union_talkgirl_00_05
};

// 遊びを断られたとき
static const talk_failed_table[][2]={
	{msg_union_talkboy_01_02,msg_union_talkgirl_01_02},
	{msg_union_talkboy_02_03,msg_union_talkgirl_02_03},
	{msg_union_talkboy_03_03,msg_union_talkgirl_03_03},
	{msg_union_talkboy_04_03,msg_union_talkgirl_04_03},
	{msg_union_talkboy_07_03,msg_union_talkgirl_07_03},
	{msg_union_talkboy_06_03,msg_union_talkgirl_06_03},
};

// 条件を満たしていないので、誘えない
static const event_reject_table[][2]={
	{msg_union_talkboy_03_04,msg_union_talkgirl_03_04},	// LV30以下が２匹いないので対戦できない
	{msg_union_talkboy_04_06,msg_union_talkgirl_04_06},	// 2匹以上てもちがいないので交換できない
	{msg_union_talkboy_07_04,msg_union_talkgirl_07_04},	// タマゴを持っていないのでぐるぐるできない
};

static const talk_anster_wait_table[][2]={
	{ msg_union_talkboy_01_01,msg_union_talkgirl_01_01,},	// カード
	{ msg_union_talkboy_03_01,msg_union_talkgirl_03_01,},	// たいせん
	{ msg_union_talkboy_04_01,msg_union_talkgirl_04_01,},	// こうかん
	{ msg_union_talkboy_02_01,msg_union_talkgirl_02_01,},	// おえかき」
	{ msg_union_talkboy_06_01,msg_union_talkgirl_06_01,},	// レコード」
	{ msg_union_talkboy_07_01,msg_union_talkgirl_07_01,},	// ぐるぐる交換」

};
static const talk_joinus_table[][2]={
	{ msg_union_talkboy_02_05,msg_union_talkgirl_02_05,},	// おえかき」
	{ msg_union_talkboy_06_05,msg_union_talkgirl_06_05,},	// レコード」
	{ msg_union_talkboy_07_05,msg_union_talkgirl_07_05,},	// ぐるぐる交換」
};
static const talk_join_success_table[][2]={
	{ msg_union_talkboy_02_07,msg_union_talkgirl_02_07,},	// おえかき」
	{ msg_union_talkboy_06_07,msg_union_talkgirl_06_07,},	// レコード」
	{ msg_union_talkboy_07_07,msg_union_talkgirl_07_07,},	// ぐるぐる交換」
};
static const talk_join_no_table[][2]={
	{ msg_union_talkboy_02_06,msg_union_talkgirl_02_06,},	// おえかき」
	{ msg_union_talkboy_06_06,msg_union_talkgirl_06_06,},	// レコード」
	{ msg_union_talkboy_07_06,msg_union_talkgirl_07_06,},	// ぐるぐる交換」
};
// ほかにもなにかする？
static const int talk_next_selct_table[]={
	msg_union_talkboy_00_04,msg_union_talkgirl_00_04
};

//またこえをかけてくれよ
static const int talk_connect_cancel_table[2]={
	msg_union_talkboy_05_01,msg_union_talkgirl_05_01
};

static const int talk_connect_canceled_table[2]={
	msg_union_talkboy_00_03,msg_union_talkgirl_00_03
};

// SXY上でのOBJの配置が正しくないので補正用テーブル
const u16 Union_GroupObjTable[]={
	10,14,18,22,26,30,34,38,42,46
};

//------------------------------------------------------------------
/**
 * @brief   話しかけたOBJの親機のIDを返す
 *
 * @param   no		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ChildToParentNo(int no)
{
	int i,r,result;
	for(i=0;i<TALK_OBJ_MAX;i++){
		if(Union_GroupObjTable[i]<=no && (Union_GroupObjTable[i]+4)>no){
			return i;
		}
	}
	return -1;
}


//------------------------------------------------------------------
/**
 * $brief   接続にはならない相手との会話番号を取得
 *
 * @param   cuw		
 * @param   no		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int GetGroupTalk_ListenNo( COMM_UNIONROOM_WORK *cuw, int no )
{
	int sex,target;
	MYSTATUS *status;
	_GF_BSS_DATA_INFO *gfbssdata;
	UNION_BEACON_STATE *beaconState;

	// 10以上は子機なので、親機の会話にぶらさがるようにする
	if(no>9){
		// 誰の子機か
		target = ChildToParentNo( no );
		GF_ASSERT( no!=-1 && "子機OBJIDは親機をひけなかった" );
		OS_Printf("代替返事 %d →  %d\n",no, target);
	}else{
		target = no;
	}
	
	// 会話取得開始
	status      = CommMPGetBconMyStatus( target );
	gfbssdata   = (_GF_BSS_DATA_INFO *)cuw->UnionBeaconTbl[target]->gameInfo.userGameInfo;
	beaconState = (UNION_BEACON_STATE *)gfbssdata->regulationBuff;

	// ビーコン情報が無かった
	if(status==NULL){
		return msg_union_talkboy_00_05;
	}

	// 親の時のは親の性別、子の時は子の性別
	if(no>9){
		sex = beaconState->c_face[(no-10)%4];
		sex = sex>>7;	// 最上位が性別
	}else{
		sex = MyStatus_GetMySex(status);
	}
	
	OS_Printf("返事モード %d \n",beaconState->mode);
	switch(beaconState->mode){
	// とりこみ中のようだ…
	case UNION_PARENT_MODE_BUSY:
	case UNION_PARENT_MODE_PARTY:

//		OS_Printf("国番号 = %d   地域 = %d \n",beaconState->nation, beaconState->city);

		return talk_failed_child_table[sex];
		break;
	case UNION_PARENT_MODE_CARDNOW:
		return talk_table_card[gf_rand()%TALK_CARD_MAX][sex];
		break;
	case UNION_PARENT_MODE_BATTLENOW:
		return talk_table_battle[gf_rand()%TALK_BATTLE_MAX][sex];
		break;
	case UNION_PARENT_MODE_TRADENOW: 
		return talk_table_trade[gf_rand()%TALK_TRADE_MAX][sex];
		break;
	
	
	case UNION_PARENT_MODE_OEKAKINOW:
	case UNION_PARENT_MODE_OEKAKI_FREE:
		return talk_table_oekaki[gf_rand()%TALK_OEKAKI_MAX][sex];
		break;
	case UNION_PARENT_MODE_RECORDNOW:
	case UNION_PARENT_MODE_RECORD_FREE:
		return talk_table_record[gf_rand()%TALK_RECORD_MAX][sex];
		break;
	case UNION_PARENT_MODE_GURUGURUNOW:
	case UNION_PARENT_MODE_GURUGURU_FREE:
		return talk_table_guruguru[gf_rand()%TALK_GURUGURU_MAX][sex];
		break;
	}
	// 親機の接続モードがおかしい
	return msg_union_talkboy_00_05;

}


//==============================================================================
/**
 * $brief   カードを見せる前の文字列設定（国・地域を参照して判定する）
 *
 * @param   wordset		
 *
 * @retval  int		
 */
//==============================================================================
int Union_GetCardTalkNo( WORDSET *wordset )
{
	u8 myNation,partnerNation;
	u8 myArea,  partnerArea; 

	//自分と相手の国・居住地を得る
	myNation      = CommInfoGetMyNation(CommGetCurrentID());
	partnerNation = CommInfoGetMyNation(CommGetCurrentID()^1);
	myArea        = CommInfoGetMyArea(CommGetCurrentID());
	partnerArea   = CommInfoGetMyArea(CommGetCurrentID()^1);

	OS_Printf("自分の国   %d 相手の国   %d\n",myNation, partnerNation);
	OS_Printf("自分の地域 %d 相手の地域 %d\n",myArea, partnerArea);

	// 相手が国を入力していない
	if(partnerNation==0){
		return msg_union_connect_01_02_3;
	}

	// 国番号が存在している場合は文字列をセット
	if(partnerNation!=0){
		WORDSET_RegisterCountryName( wordset, 3, partnerNation );

		// 地域番号が存在している場合は文字列をセット
		if(partnerArea!=0){
			WORDSET_RegisterLocalPlaceName( wordset, 4, partnerNation, partnerArea );
		}

	}

	// 表示文字列判定
	
	// 国が違う
	if(myNation!=partnerNation){
		// 地域がない
		if(partnerArea==0){
			return msg_union_connect_01_02_1;
		}
		// 地域がおなじ
		if(myArea==partnerArea){
			return msg_union_connect_01_02_1; 
		}
		// 地域が違う
		return msg_union_connect_01_02;
	}

	// 国が同じ
	if(myArea!=partnerArea){
		// 地域が違う
		return msg_union_connect_01_02_2;
	}
	
	//地域が同じ
	return msg_union_connect_01_02_3;

}

//------------------------------------------------------------------
/**
 * $brief   遊び始めるときの会話（カードの時だけ住んでいる場所に対応する）
 *
 * @param   event		ユニオンを行う遊び
 * @param   sex			性別
 *
 * @retval  int			会話番号
 */
//------------------------------------------------------------------
static int GetStartTalk_No(int event, int sex, WORDSET *wordset )
{
	
	// カードじゃないときはテーブルからそれぞれ参照する
	if( event!=(UNION_CHILD_SELECT_CARD-1) ){
		OS_Printf("eventno = %d \n", event);
		return talk_start_table[event][sex];
	}

	// カードを見せる前に国・地域情報から判定して文字列を設定する
	return Union_GetCardTalkNo( wordset );

}
//==============================================================================
/**
 * $brief   話掛けで通信接続できない時に出す会話のインデックスを渡す処理
 *
 * @param   cuw		ユニオンワーク
 * @param   no		話しかける対象のOBJの番号
 *
 * @retval  int		メッセージインデックス
 */
//==============================================================================
int Union_GetTalkNumber( COMM_UNIONROOM_WORK *cuw, int no, int mode, WORDSET *wordset )
{
	int sex;
	MYSTATUS *status;

	// スクリプトからは＋１でくるので１引く
	no--;

	OS_Printf("会話取得行動 OBJNO = %d  mode=%d  ScriptWork=%d \n",no,mode,cuw->ScriptSelectWork-1);

	// 接続はできないグループとの会話
	if(mode==UNION_NO_CONNECT_TALK){
		return GetGroupTalk_ListenNo( cuw, no );
	}

	status = CommMPGetBconMyStatus( no );
	sex    = MyStatus_GetMySex(status);

	switch(mode){
	// 接続が成功した後で、行う内容がきまった時の会話
	case UNION_CONNECTED_START_TALK:
		return GetStartTalk_No( cuw->ScriptSelectWork-1, sex, wordset );
//		return talk_start_table[cuw->ScriptSelectWork-1][sex];
		break;

	// 話しかけで接続できたとき（子機側で）
	case UNION_CONNECT_SUCCESS_TALK:
		return talk_start_child_table[sex];
		break;
	// たいせん・こうかん等を持ちかけたときに流れるセリフ(子機側で）
	case UNION_CONNECT_ANSWER_WAIT:
		// 既にキャンセルされている
		if(cuw->ScriptSelectWork==0){
			OS_Printf("キャンセルされているのでスキップ\n");
			return 0;
		}
		// 自分の選択が有効になっている
		return talk_anster_wait_table[cuw->ScriptSelectWork-1][sex];
		break;

	//ポケモンを２匹以上持っていないと交換はできないよ
	case UNION_CONNECT_BATTLE_REJECT:
	case UNION_CONNECT_TRADE_REJECT:
	case UNION_CONNECT_GURUGURU_REJECT:
		return event_reject_table[mode-UNION_CONNECT_BATTLE_REJECT][sex];
		break;
	// 「うーん、いまはつごうわるいんだ、また今度ね」
	case UNION_TALK_CANCEL_CARD:	case UNION_TALK_CANCEL_OEKAKI:
	case UNION_TALK_CANCEL_BATTLE:	case UNION_TALK_CANCEL_TRADE:
	case UNION_TALK_CANCEL_GURUGURU:	case UNION_TALK_CANCEL_RECORD:
		return talk_failed_table[mode-UNION_TALK_CANCEL_CARD][sex];
		break;

	// 「いっしょに●●しない？」
	case  UNION_JOIN_OEKAKI_TALK:
	case  UNION_JOIN_RECORD_TALK:
	case  UNION_JOIN_GURUGURU_TALK:
		return talk_joinus_table[mode-UNION_JOIN_OEKAKI_TALK][sex];
		break;

	// 「じゃ、はいってきなよ！」
	case  UNION_SUCCESS_OEKAKI_JOIN:
	case  UNION_SUCCESS_RECORD_JOIN	:
	case  UNION_SUCCESS_GURUGURU_JOIN:
		return talk_join_success_table[mode-UNION_SUCCESS_OEKAKI_JOIN][sex];
		break;

	// 「そう、じゃまたきてね…」
	case  UNION_JOIN_OEKAKI_NO:
	case  UNION_JOIN_RECORD_NO:
	case  UNION_JOIN_GURUGURU_NO:
		return talk_join_no_table[mode-UNION_JOIN_OEKAKI_NO][sex];
		break;

	// ほかにもなにかする？
	case UNION_SELECT_NEXT_TALK:
		return talk_next_selct_table[sex];
		break;

	// 「なにかしたくなったらまた声をかけてくれよ」
	case UNION_TALK_CONNECT_CANCEL:
		return talk_connect_cancel_table[sex];
		break;

	// 「あ、ごめんようじがあるから」
	case UNION_TALK_CONNECT_CANCELED:
		return talk_connect_canceled_table[sex];
		break;

	}
	
	// ここまで降りてくる事があってはいけない
	GF_ASSERT(0);
	return msg_union_talkboy_00_05;

}


//------------------------------------------------------------------
/**
 * $brief   接続中の友達の姿を現すビーコンを作成する
 *
 * @param   state	
 * @param   num		接続人数
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void ConnectChildViewSet( UNION_BEACON_STATE  *state, int num )
{
	MYSTATUS *friendstatus;
	int i,count=0;

	// 2人接続でもIDは1じゃないかもしれない
	for(i=1;i<UNION_CONNECT_CHILD_MAX+1;i++){
		int pos = i-1;
		friendstatus = CommInfoGetMyStatus(i);
		
		if(friendstatus!=NULL){
			state->c_id[pos]   = MyStatus_GetID( friendstatus );
			state->c_face[pos] = MyStatus_GetTrainerView( friendstatus ) | (MyStatus_GetMySex( friendstatus )<<7);
		}else{
			state->c_id[pos]   = 0;
			state->c_face[pos] = 0;
		}
	}
}

//------------------------------------------------------------------
/**
 * $brief   現在行っているビーコンに書き換える
 *
 * @param   flag		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
void Union_BeaconChange( int flag )
{
	UNION_BEACON_STATE state;

	MI_CpuClear8( &state, sizeof(UNION_BEACON_STATE) );
	switch(flag){
	// 話しかけ可能状態
	case UNION_PARENT_MODE_FREE:
		break;
	// メニュー等開いて相手ができない
	case UNION_PARENT_MODE_BUSY:
		break;
	// 話しかけに成功し、2人接続になった状態
	case UNION_PARENT_MODE_PARTY:	
		ConnectChildViewSet( &state, 2 );
		break;
	// 現在交換画面にいる（のでもう繋がらない）
	case UNION_PARENT_MODE_TRADENOW:
	case UNION_PARENT_MODE_CARDNOW:
	case UNION_PARENT_MODE_BATTLENOW:
		ConnectChildViewSet( &state, 2 );
		break;

	// 現在おえかきボードにいて、すでに5人埋まっている（のでもう繋がらない）
	case UNION_PARENT_MODE_OEKAKINOW:
		ConnectChildViewSet( &state, 5 );
		break;
	// 現在お絵かきボードにいてまだ空きがあるので、話しかけれる
	case UNION_PARENT_MODE_OEKAKI_FREE:
		ConnectChildViewSet( &state, 4 );
		break;

	// 現在レコードコーナーにいて、すでに5人埋まっている（のでもう繋がらない）
	case UNION_PARENT_MODE_RECORDNOW:
		ConnectChildViewSet( &state, 5 );
		break;
	// 現在レコードコーナーにいてまだ空きがあるので、話しかけれる
	case UNION_PARENT_MODE_RECORD_FREE:
		ConnectChildViewSet( &state, 4 );
		break;

	// 現在ぐるぐる交換にいて、すでに5人埋まっている（のでもう繋がらない）
	case UNION_PARENT_MODE_GURUGURUNOW:
		ConnectChildViewSet( &state, 4 );
		break;
	// 現在ぐるぐる交換にいてまだ空きがあるので、話しかけれる
	case UNION_PARENT_MODE_GURUGURU_FREE:
		ConnectChildViewSet( &state, 4 );
		break;
	}
	state.mode    = flag;

	CommMPSetMyRegulation(&state);	// ビーコン書き換え
	CommMPFlashMyBss();
	
}


//==============================================================================
// ユニオンルームの左上の人の「おはなし」選択時の会話内容テーブル
//==============================================================================
static const int InfomationTalkTable[]={
	msg_union_info_02_04,
	msg_union_info_02_05,
	msg_union_info_02_06,
	msg_union_info_02_07,
	msg_union_info_02_08,
	msg_union_info_02_09,
	msg_union_info_02_10,
	msg_union_info_02_11,
	msg_union_info_02_12,
	msg_union_info_02_13,
	msg_union_info_02_14,
	msg_union_info_02_15,
	msg_union_info_02_16,
	msg_union_info_02_17,
	msg_union_info_02_18,
	msg_union_info_02_19,
	msg_union_info_02_20,
	msg_union_info_02_21,
	msg_union_info_02_22,
	msg_union_info_02_23,
};

// 簡易会話のユニオンルーム用あいさつの上限
#define PMS_DATA_UNION_TALK_NO_MAX		( 20 )

//==============================================================================
/**
 * $brief   ユニオンルームの左上の人が喋る内容をきめる
 *
 * @param   cuw		
 *
 * @retval  int		対応したメッセージNOが返る
 */
//==============================================================================
int Union_GetInfomationTalkNo( COMM_UNIONROOM_WORK *cuw,  WORDSET *wordset )
{
	int i,ret=0,pmsid;
	PMS_WORD pmsword;

	// ユニオンルームでビーコンをつかんでいるか？
	for(i=0;i<10;i++){
		if(cuw->UnionBeaconTbl[i]!=NULL){
			ret++;
		}
	}
	
	// だれかいる
	if(ret!=0){
		// 「ともだちがいるよ！」と終了
		return msg_union_info_02_01;
	}

	// 誰もいないので簡易会話を見に行く
	
	OS_Printf("簡易会話ＩＤ = %d\n",PMSDAT_GetSentenceType( &cuw->MyPmsData ));

	// 有効な文章か？
	if(!PMSDAT_IsEnabled( &cuw->MyPmsData )){
		
		return msg_union_info_02_02;
	}
	
	// ユニオン会話か？
	if(PMSDAT_GetSentenceType( &cuw->MyPmsData )!=PMS_TYPE_UNION){
		// ユニオン会話じゃない

		//トレーナーの見た目文字列を格納する
		int view_type = MyStatus_GetTrainerView(cuw->mystatus);
		int sex       = MyStatus_GetMySex(cuw->mystatus);
		
		WORDSET_RegisterTrTypeName( wordset, 0, UnionView_GetTrainerInfo( sex, view_type, UNIONVIEW_MSGTYPE) );

		return msg_union_info_02_03;
	}
	
	pmsid = PMSDAT_GetSentenceID( &cuw->MyPmsData );
	
	// ユニオン会話は２０個らしいので、超えていたら補正する
	if(pmsid >= PMS_DATA_UNION_TALK_NO_MAX){
		pmsid = 0;
	}
	
	// きちんと簡易会話単語が入っているならば登録する
	// (ユニオン会話には単語が無いものも存在する）
	if((pmsword=PMSDAT_GetWordNumber( &cuw->MyPmsData, 0 ))!=PMS_WORD_NULL){
		// 簡易会話言葉を格納する
//		WORDSET_RegisterTrTypeName( wordset, 0, PMSDAT_GetWordNumber( &cuw->MyPmsData, 0 ) );
		WORDSET_RegisterPMSWord( wordset, 0, pmsword );
	}
	
	// ユニオン会話番号に対応したメッセージNOを返す
	return InfomationTalkTable[ pmsid ];
}


//------------------------------------------------------------------
/**
 * $brief   親機の時の周りメンバーを表すビーコン情報をクリアする
 *
 * @param   beacon		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void UnionBeaconClear( UNION_BEACON_STATE *beacon )
{
	int i;
	beacon->mode = 0;
	for(i=0;i<4;i++){
		beacon->c_id[i]     = 0;
		beacon->c_face[i]   = 0;
		beacon->c_rom[i]    = 0;
		beacon->c_region[i] = 0;
	}
}

//==============================================================================
/**
 * $brief   ユニオンルームでスタートメニューからチャットが追加された時の処理
 *
 * @param   cuw		
 * @param   pms		「チャット」メニューで作成した簡易会話
 *
 * @retval  none
 */
//==============================================================================
void Union_SetMyPmsData( COMM_UNIONROOM_WORK *cuw, PMS_DATA *pms )
{
	PMSDAT_Copy( &cuw->MyPmsData, pms  );
	cuw->MyPmsPutFlag = 1;
}

//==============================================================================
/**
 * $brief   自分で作成した簡易会話が下画面から参照されるようにする
 *
 * @param   cuw			
 *
 * @retval  PMS_DATA *	自分で作成した簡易会話文
 */
//==============================================================================
PMS_DATA * Union_GetMyPmsData( COMM_UNIONROOM_WORK *cuw )
{
	if(cuw->MyPmsPutFlag==0){
		return NULL;
	}
	cuw->MyPmsPutFlag = 0;
	return &cuw->MyPmsData;
}


//==============================================================================
/**
 * $brief   ユニオンルーム内で使用する会話用にトレーナー名をセットする
 *          自分の名前もセットする
 *
 * @param   wordset		WORDSETへのポインタ
 * @param   type		UNION_TRAINER_REGIST_CHILD:「話しかけ用」	1:「話しかけられ用」
 * @param   no			「話しかけ用」の時に指定しているOBJをもらうために必要
 *
 * @retval  none		
 */
//==============================================================================
void Union_TrainerNameRegist( WORDSET *wordset, int type, int no, MYSTATUS *mystatus, PMSW_SAVEDATA *pmssave )
{
	MYSTATUS *status;
	STRBUF   *greeting;
	MSGDATA_MANAGER*  msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_union_dat, HEAPID_FIELD );
	int      region,msgno;

	OS_Printf("NameRegist type=%d objid=%d\n",type, no);
	no--;		// スクリプトは＋１でくるので１引く
	
	// 話しかけはビーコンからMYSTATUSを取得
	if(type==UNION_TALK_CHILD){
		status      = CommMPGetBconMyStatus( no );
	}else{
	// 話しかけられは接続済みなのでConnectID^1からMYSTATUSを取得
		status = CommInfoGetMyStatus(CommGetCurrentID()^1);

	}

//	OS_Printf("名前登録　%d\n", type);
//	GF_ASSERT(status!=NULL && "取得したMYSTATUSはNULL");

	if(status==NULL){
		return;
	}

	// トレーナー名を登録
	WORDSET_RegisterPlayerName( wordset, 0, status );		// 相手の名前を登録
	WORDSET_RegisterPlayerName( wordset, 1, mystatus );		// 自分の名前も登録する

	// 国コード取得
	region   = MyStatus_GetRegionCode( status );

	OS_Printf("国番号 %d \n", region);

	// 各言語カートリッジにあわせて簡易会話フラグを追加する
	if(region>=LANG_JAPAN && region <=LANG_SPAIN){
		static const int AisatsuFlagTable[] = {
			PMSW_AISATSU_JP,	// 日本語
			PMSW_AISATSU_EN,	// 英語
			PMSW_AISATSU_FR,	// フランス語
			PMSW_AISATSU_IT,	// イタリア語
			PMSW_AISATSU_GE,	// ドイツ語
			-1,					// 無効言語ナンバー
			PMSW_AISATSU_SP,	// スペイン語
		};

		u16 lang = region - LANG_JAPAN;
		if( (lang < NELEMS(AisatsuFlagTable)) && (AisatsuFlagTable[lang] >= 0) )
		{
			PMSW_SetAisatsuFlag( pmssave,  AisatsuFlagTable[lang] );
			OS_Printf("簡易会話に %d　を追加\n", PMSW_AISATSU_JP+( region - LANG_JAPAN ) );
		}
	}

	OS_Printf("クリアフラグ = %d, 全国図鑑フラグ = %d\n", MyStatus_GetDpClearFlag(status),MyStatus_GetDpZenkokuFlag(status));

	// 相手の言語によって挨拶が変わる
	switch(region){
	case LANG_JAPAN: 	msgno = msg_union_greeting_01;	break;
	case LANG_ENGLISH: 	msgno = msg_union_greeting_02;	break;
	case LANG_FRANCE: 	msgno = msg_union_greeting_03;	break;
	case LANG_ITALY	: 	msgno = msg_union_greeting_04;	break;
	case LANG_GERMANY: 	msgno = msg_union_greeting_05;	break;
	case LANG_SPAIN	: 	msgno = msg_union_greeting_06;	break;
	default:
		msgno = msg_union_greeting_07;
	}
	greeting = MSGMAN_AllocString( msgman, msgno );

	// 各国の「こんにちは」を格納する
	WORDSET_RegisterWord( wordset, 2, greeting, 0, 1, region );

	sys_FreeMemoryEz(greeting);
	MSGMAN_Delete( msgman );
}

//==============================================================================
/**
 * $brief   ユニオンルームで簡易会話を書き換える（話しかけOKしかないと思うので１択で）
 *
 * @param   pms		
 *
 * @retval  none		
 */
//==============================================================================
void Union_PMSReWrite( PMS_DATA *pms )
{
	UNION_BEACON_STATE state;

	UnionBeaconClear( &state );
	state.mode = UNION_PARENT_MODE_FREE;
	

	CommMPSetMyPMS( pms );
	CommMPSetMyRegulation(&state);	// ビーコン書き換え
	CommMPFlashMyBss();
	
}

//==============================================================================
/**
 * $brief   こうかん・たいせんから戻ってきた時用にワークを初期化しておく
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_CommWorkClear( COMM_UNIONROOM_WORK *cuw)
{
	cuw->CommChildSelectEvent = 0;
	cuw->UnionEventWork       = 0;
	cuw->UnionEndConnectFlag  = 0;
}
//------------------------------------------------------------------
/**
 * $brief   ユニオンルーム通信開始用のワーククリア
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void CommUnion_EventFlagClear( COMM_UNIONROOM_WORK *cuw)
{
	cuw->CommConnectStartFlag = 0;
	cuw->CommConnectStartWait = 0;
	cuw->CommNextProcOn       = 0;
	cuw->CommChildSelectEvent = 0;
	cuw->UnionEventWork       = 0;
	cuw->busyflag			  = 0;
	cuw->MyPmsPutFlag         = 0;
	cuw->UnionEndConnectFlag  = 0;
}

//==============================================================================
/**
 * $brief   トレーナーカード領域をallocする
 *
 * @param   cuw		
 *
 * @retval  void *		
 *
 *  トレーナーカードを確保する領域がHEAPID_UNIONROOMから作れなかったので、
 *  BASE_SYSTEMから取る事にした。
 *  別アプリへの影響が怖いので、トレーナーカードを見る直前に確保して
 *  カード閲覧直後に解放する
 */
//==============================================================================
void *Union_TrainerCardWorkInit( COMM_UNIONROOM_WORK *cuw )
{
	cuw->my_trcard      = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );
	cuw->recv_trcard[0] = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );
	cuw->recv_trcard[1] = TRCSET_AllocTrainerCardData( HEAPID_BASE_SYSTEM );

	TRCSET_MakeTrainerInfo( 0, 0, 0,
							UnionView_GetTrainerInfo( MyStatus_GetMySex(cuw->mystatus),
												MyStatus_GetTrainerView(cuw->mystatus), UNIONVIEW_ICONINDEX ),
							cuw->fsys, cuw->my_trcard );

	OS_Printf("my_trcard = %08x\n",cuw->my_trcard);
	OS_Printf("trcard[0] = %08x\n",cuw->recv_trcard[0]);
	OS_Printf("trcard[1] = %08x\n",cuw->recv_trcard[1]);

	//自分のＩＤと違うバッファを返す（相手のトレーナーカード到着を監視できるように）
	return (void*)cuw->recv_trcard[CommGetCurrentID()^1];
}


//==============================================================================
/**
 * $brief   トレーナーカードのために確保した領域を解放する
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_trainerCardWorkFree( COMM_UNIONROOM_WORK *cuw )
{
    sys_FreeMemoryEz(cuw->recv_trcard[0]);
    sys_FreeMemoryEz(cuw->recv_trcard[1]);
    sys_FreeMemoryEz(cuw->my_trcard);

}


//==============================================================================
/**
 * $brief   トレーナーカードデータを送信する
 *
 * @param   cuw		
 *
 * @retval  none		
 */
//==============================================================================
void Union_SendTrainerCardData( COMM_UNIONROOM_WORK *cuw )
{

	// 親だけ送信する
//	if(CommGetCurrentID()==0){
		CommSendHugeData( CU_TRAINER_CARD, cuw->my_trcard, sizeof(TR_CARD_DATA) );

		OS_Printf("send size = %d   xor = %d\n",sizeof(TR_CARD_DATA), cuw->my_trcard->_xor);
//	}

}


