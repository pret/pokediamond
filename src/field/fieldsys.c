//===========================================================================
/**
 * @file	fieldsys.c
 * @brief	ゲームメイン制御
 * @author	tamada	GAME FREAK Inc.
 *
 */
//===========================================================================
#include "common.h"

#define __FIELDSYS_H_GLOBAL__
#include "fieldsys.h"

#include "field/field.h"
#include "system/main.h"
#include "system\render_oam.h"

#include "fieldmap.h"
#include "fieldmap_work.h"

#include "field_event.h"

#include "system/savedata.h"

#include "ev_mapchange.h"		//EventSet_FirstMapIn

#include "zonedata.h"
#include "fielddata/maptable/zone_id.h"

#include "system/pm_overlay.h"
#include "field/situation.h"
#include "field/situation_local.h"

#include "communication/communication.h"  // 通信処理のため
#include "comm_player.h"  // 通信処理のため
#include "comm_field_state.h"// 通信処理のため

#include "ev_check.h"		//EV_REQUEST

#include "demo/title.h"


#include "field_poketch.h"
#include "eventdata.h"

#ifdef PM_DEBUG

#define WORLD_HEAP_LEAK_CHECK	//ワールドヒープリークチェック用
#define	EVENT_HEAP_LEAK_CHECK	//イベントヒープリークチェック用
#define	SYSTEM_HEAP_LEAK_CHECK	//システムヒープリークチェック用

static u32 SystemHeapFreeSize = 0;
static u32 WorldHeapFreeSize = 0;
static u32 EventHeapFreeSize = 0;

#endif


FS_EXTERN_OVERLAY( title );
FS_EXTERN_OVERLAY( fieldmap );
//FS_EXTERN_OVERLAY( fieldmap2 );

static FIELDSYS_WORK * GameSystem_Init(PROC * proc);
static BOOL GameSystem_Main(FIELDSYS_WORK * fsys);
static void GameSystem_End(PROC * proc);


static void FieldMap_Control(FIELDSYS_WORK * fsys);
/*---------------------------------------------------------------------------*
 *---------------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * @brief	制御ワーク用構造体定義
 */
//------------------------------------------------------------------
typedef struct _CONTROL_WORK{
	PROC * mainproc;		///<メインプロセス保持ワーク
	PROC * subproc;			///<サブプロセス保持ワーク
	BOOL pause_flag;		///<ポーズフラグ（デバッグ用）
	BOOL end_flag;			///<終了フラグ（デバッグ用？）
};

//------------------------------------------------------------------
/**
 * @brief	メイン制御ワーク
 */
//------------------------------------------------------------------
static FIELDSYS_WORK	* FieldSysWork;


//===========================================================================
//
//
//		ゲームメインプロセス関数
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゲームメインプロセス：初期化：コンティニュー
 */
//------------------------------------------------------------------
static PROC_RESULT ContinueGameMainProc_Init(PROC * proc, int * seq)
{
	MAINWORK * main = PROC_GetParentWork(proc);

	FieldSysWork = GameSystem_Init(proc);
	if (main->comm_error_flag) {
		EventSet_ErrorContinueMapIn(FieldSysWork);
	} else {
		EventSet_ContinueMapIn(FieldSysWork);
	}
	main->comm_error_flag = FALSE;
	return PROC_RES_FINISH;
}

//------------------------------------------------------------------
/**
 * @brief	ゲームメインプロセス：初期化：さいしょから
 */
//------------------------------------------------------------------
static PROC_RESULT FirstGameMainProc_Init(PROC * proc, int * seq)
{
	FieldSysWork = GameSystem_Init(proc);
	EventSet_FirstMapIn(FieldSysWork);
	return PROC_RES_FINISH;
}


//------------------------------------------------------------------
/**
 * @brief	ゲームメインプロセス：メイン
 */
//------------------------------------------------------------------
static PROC_RESULT GameMainProc_Main(PROC * proc, int * seq)
{
	FIELDSYS_WORK * fsys = PROC_GetWork(proc);

	if (GameSystem_Main(fsys)) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}
//------------------------------------------------------------------
/**
 * @brief	ゲームメインプロセス：終了
 *
 * 実際には呼ばれることはないと考えられる
 */
//------------------------------------------------------------------
static PROC_RESULT GameMainProc_End(PROC * proc, int * seq)
{
	GameSystem_End(proc);
	Main_SetNextProc(FS_OVERLAY_ID(title), &TitleProcData);
	return PROC_RES_FINISH;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
const PROC_DATA FirstGameProcData = {
	FirstGameMainProc_Init,
	GameMainProc_Main,
	GameMainProc_End,
	NO_OVERLAY_ID
};

//------------------------------------------------------------------
//------------------------------------------------------------------
const PROC_DATA ContinueGameProcData = {
	ContinueGameMainProc_Init,
	GameMainProc_Main,
	GameMainProc_End,
	NO_OVERLAY_ID
};
//===========================================================================
//
//	操作関数
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	フィールドマップメイン生成
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void GameSystem_CreateFieldProc(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->ctrl->subproc == NULL);
	GF_ASSERT(fsys->ctrl->mainproc == NULL);
	Overlay_Load( FS_OVERLAY_ID( fieldmap ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	//Overlay_Load( FS_OVERLAY_ID( fieldmap2 ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
	fsys->main_mode_flag = FALSE;
	fsys->ctrl->pause_flag = FALSE;
	fsys->ctrl->mainproc = PROC_Create(&FieldProcData, fsys, HEAPID_WORLD);
}

//------------------------------------------------------------------
/**
 * @brief	フィールドマップメイン終了リクエスト
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void GameSystem_FinishFieldProc(FIELDSYS_WORK * fsys)
{
	fsys->main_mode_flag = FALSE;
}
//------------------------------------------------------------------
/**
 * @brief	フィールドマップメインの存在チェック
 * @param	fsys	フィールド制御ワークへのポインタ
 * @retval	TRUE	フィールドマップメインが存在している
 * @retval	FALSE	フィールドマップメインは存在していない
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckFieldProcExists(FIELDSYS_WORK * fsys)
{
	return (fsys->ctrl->mainproc != NULL);
}

//------------------------------------------------------------------
/**
 * @brief	フィールドマップメイン動作チェック
 * @param	fsys	フィールド制御ワークへのポインタ
 * @retval	TRUE	フィールドマップメインが動作している
 * @retval	FALSE	フィールドマップメインは動作していない
 *					（サブプロセス動作中か、初期化・終了処理中）
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckFieldMain(FIELDSYS_WORK * fsys)
{
	if (fsys->ctrl->mainproc != NULL && fsys->main_mode_flag) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	フィールドサブプロセスの存在チェック
 * @param	fsys	フィールド制御ワークへのポインタ
 * @retval	TRUE	フィールドサブプロセスが存在している
 * @retval	FALSE	フィールドサブプロセスは存在していない
 */
//------------------------------------------------------------------
BOOL GameSystem_CheckSubProcExists(FIELDSYS_WORK * fsys)
{
	return (fsys->ctrl->subproc != NULL);
}

//------------------------------------------------------------------
/**
 * @brief	フィールドサブプロセスの生成処理
 * @param	fsys	フィールド制御ワークへのポインタ
 * @param	pdata	プロセスデータ
 * @param	param	プロセスに渡すパラメータ
 */
//------------------------------------------------------------------
void GameSystem_StartSubProc(FIELDSYS_WORK * fsys, const PROC_DATA * pdata, void * param)
{
	GF_ASSERT(fsys->ctrl->subproc == NULL);
	GameSystem_FinishFieldProc(fsys);
	fsys->ctrl->subproc = PROC_Create(pdata, param, HEAPID_WORLD);
}

//------------------------------------------------------------------
/**
 * @brief	ゲームメインの終了
 * @param	fsys	フィールド制御ワークへのポインタ
 */
//------------------------------------------------------------------
void GameSystem_FinishGame(FIELDSYS_WORK * fsys)
{
	fsys->ctrl->end_flag = TRUE;
}

//===========================================================================
//
//
//		初期化関数
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゲーム初期化処理
 * @param	proc		プロセスへのポインタ
 * @return	FIELDSYS_WORK	フィールドメイン制御ワークへのポインタ
 */
//------------------------------------------------------------------
static FIELDSYS_WORK * GameSystem_Init(PROC * proc)
{
	MAINWORK * main;
	FIELDSYS_WORK * fsys;

	//ワールドヒープ確保(確保しっぱなし)
	//sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WORLD, 0x20000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_WORLD, 0x1c000 );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_EVENT, 0x04000 );
	sys_CreateHeap( HEAPID_BASE_SYSTEM, HEAPID_COMMICON, 0x300 );

	//フィールドメイン制御ワークを確保
	fsys = PROC_AllocWork(proc, sizeof(FIELDSYS_WORK), HEAPID_WORLD);
	MI_CpuClear8(fsys, sizeof(FIELDSYS_WORK));

	//フィールド制御用ワークを確保
	fsys->ctrl = sys_AllocMemory(HEAPID_WORLD, sizeof(CONTROL_WORK));
	fsys->ctrl->mainproc = NULL;
	fsys->ctrl->subproc = NULL;
	fsys->ctrl->pause_flag = FALSE;
	fsys->ctrl->end_flag = FALSE;

	//セーブデータへのポインタを割り当て
	main = PROC_GetParentWork(proc);
	fsys->savedata = main->savedata;

	fsys->event = NULL;

	fsys->location = Situation_GetNowLocation(SaveData_GetSituation(fsys->savedata));

	//ゲーム制御用のワーク確保
	//ゲーム中、常に確保されているワークはここで確保する
	fsys->World = WorldMapInit();								//ワールドマップ構造体確保
	EventData_Sys_Create(fsys, HEAPID_WORLD);					//イベントデータ制御生成
	fsys->bag_cursor = MyItem_BagCursorAlloc(HEAPID_WORLD);		//バッグのカーソル情報
	fsys->SwayGrass = SwayGrass_AllocSwayGrass(HEAPID_WORLD);	//揺れ草構造体メモリ確保
	SwayGrass_InitSwayGrass(fsys->SwayGrass);	//揺れ草初期化
	fsys->p_zukandata = ZKN_DW_Alloc( HEAPID_WORLD );	// 図鑑リスト位置保存領域


	return fsys;
}

//===========================================================================
//
//
//		終了関数
//
//
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	ゲーム終了処理
 * @param	proc		プロセスへのポインタ
 */
//------------------------------------------------------------------
static void GameSystem_End(PROC * proc)
{
	FIELDSYS_WORK * fsys = PROC_GetWork(proc);

	//ゲーム制御用のワーク解放
	//ゲーム中、常に確保されているワークはここで解放する
	WorldMapRelease(fsys->World);				// ワールドマップ構造体解放
	EventData_Sys_Delete(fsys);					// イベントデータ制御解放
	sys_FreeMemoryEz(fsys->bag_cursor);			// バッグのカーソル情報
	SwayGrass_FreeSwayGrass(fsys->SwayGrass);	//揺れ草ワーク解放
	ZKN_DW_Free( fsys->p_zukandata );			// 図鑑リスト位置保存領域

	sys_FreeMemoryEz(fsys->ctrl);
	PROC_FreeWork(proc);
	sys_DeleteHeap(HEAPID_COMMICON);
	sys_DeleteHeap(HEAPID_WORLD);
	sys_DeleteHeap(HEAPID_EVENT);
}


//===========================================================================
/**
 * 
 * メイン関数
 *
 */
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	サブプロセス呼び出し処理
 * @param	proc	サブプロセスポインタを保持するワークへのポインタ
 */
//------------------------------------------------------------------
static void ProcCall(PROC ** proc)
{
	if (*proc) {
		if (ProcMain(*proc)) {
			PROC_Delete(*proc);
			*proc = NULL;
		}
	}
}
//------------------------------------------------------------------
/**
 * @brief	ゲームメイン処理
 * @param	fsys	フィールドメイン制御ワークへのポインタ
 * @retval	TRUE	終了
 * @retval	FALSE	継続動作
 */
//------------------------------------------------------------------
BOOL GameSystem_Main(FIELDSYS_WORK * fsys)
{
	BOOL event_end;

    FieldMap_Control(fsys);
	event_end = FieldEvent_Control(fsys);
	if(event_end == TRUE && fsys->fldmap != NULL)
	{
		//ポケッチスリープ解除処理
		Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, FALSE );
	}


	if (fsys->ctrl->mainproc) {
		ProcCall(&fsys->ctrl->mainproc);
		if (fsys->ctrl->mainproc == NULL) {
			Overlay_UnloadID( FS_OVERLAY_ID(fieldmap) );
			//Overlay_UnloadID( FS_OVERLAY_ID(fieldmap2) );
		}
	} else if (fsys->ctrl->subproc) {
		ProcCall(&fsys->ctrl->subproc);
	}

	if (fsys->ctrl->end_flag && !fsys->event
			&& !fsys->ctrl->mainproc && !fsys->ctrl->subproc) {
		//終了リクエストがあり、イベントもサブプロセスもメインプロセスも
		//なければ終了させる
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 自機操作、イベントチェック
 *
 * @param	fsys		FIELDSYS_WORK
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldMap_Control(FIELDSYS_WORK * fsys)
{
	int map_mode;
	EV_REQUEST	req;
    BOOL bMoveControl = FALSE;

    //ポーズ状態でなく、
    //フィールドメインが動作していて
    //イベントが発生していない場合、
    //	各種処理を実行する
    if (!fsys->ctrl->pause_flag
        && fsys->main_mode_flag
        && FieldEvent_Check(fsys) == FALSE) {
        bMoveControl = TRUE;
    }

#ifdef	PM_DEBUG
	if (bMoveControl) {
		if (MAP_MODE_GROUND == fsys->MapMode){
#ifdef SYSTEM_HEAP_LEAK_CHECK
			if (SystemHeapFreeSize == 0) {
				SystemHeapFreeSize = sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM);
			} else if (SystemHeapFreeSize != sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM)) {
				sys_DeleteHeap(HEAPID_BASE_SYSTEM);
				GF_ASSERT_MSG(0, "SYSTEM HEAP SIZE %d < %d\n",
						SystemHeapFreeSize, sys_GetHeapFreeSize(HEAPID_BASE_SYSTEM));
			}
#endif

#ifdef WORLD_HEAP_LEAK_CHECK		
			if (WorldHeapFreeSize == 0) {
				WorldHeapFreeSize = sys_GetHeapFreeSize(HEAPID_WORLD);
			} else if (WorldHeapFreeSize != sys_GetHeapFreeSize(HEAPID_WORLD)){
				bMoveControl = FALSE;
			}
#endif	//WORLD_HEAP_LEAK_CHECK

#ifdef	EVENT_HEAP_LEAK_CHECK
			if (EventHeapFreeSize == 0) {
				EventHeapFreeSize = sys_GetHeapFreeSize(HEAPID_EVENT);
			} else if (EventHeapFreeSize != sys_GetHeapFreeSize(HEAPID_EVENT)) {
				bMoveControl = FALSE;
			}
#endif	//EVENT_HEAP_LEAK_CHECK

			if (bMoveControl == FALSE) {
				//ヒープのリークを検出したらタイトルに戻る
				//→タイトルでヒープを開放するのでリーク箇所がわかる
				EventSet_ReturnToTitle(fsys);
			}
		}
	}
#endif

    if(bMoveControl){
		Player_MoveStateUpdate( fsys->player );
        SetRequest( &req, fsys, sys.trg, sys.cont );
    }
	map_mode = fsys->MapMode;

	if(fsys->location->zone_id == ZONE_ID_D31R0201){
		//タワー受付のマップモードはMAP_MODE_BTOWERだが
		//イベントチェックはノーマルに行う
		map_mode = MAP_MODE_GROUND;
	}
    switch(map_mode){
      case MAP_MODE_UNDER:
        if(bMoveControl){
            if(CommPlayerIsControl()){
                if( CheckRequestUG( &req, fsys ) == TRUE ){  // 炭鉱
                }
            }
        }
        CommPlayersMove(fsys, bMoveControl);  // 通信移動
        break;
      case MAP_MODE_COLOSSEUM:
        if(bMoveControl){
            if(CommPlayerIsControl()){
                if( CheckRequestVSRoom( &req, fsys ) == TRUE ){  // 対戦部屋
                    bMoveControl = FALSE;
                }
            }
            else{
                bMoveControl = FALSE;
            }
        }
        CommPlayersMove(fsys, bMoveControl);  // 通信移動
        break;
      case MAP_MODE_UNION:
        if(bMoveControl){
            if( CheckRequestUnion( &req, fsys ) == TRUE ){
                //イベント起動したら、の処理をここに入れる
            }else{
                Player_MoveControl( fsys->player,
						fsys->map_cont_dat,DIR_NOT, req.trg, req.cont, FALSE );
            }
        }
        break;
	  case MAP_MODE_BTOWER:
        if(bMoveControl){
            if( CheckRequestBTower( &req, fsys ) == TRUE ){
                StopPlaceName(fsys->fldmap->place_name_cont);	//地名表示キャンセル
                BoardSetDirect( fsys, BOARD_REQ_DEL );	// 看板処理破棄（即消去）
				Player_EventPoketchCancel( fsys->player );	//自機ポケッチ状態キャンセル
                //ポケッチスリープ処理
                Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, TRUE );
            }
            else{
                //イベントが発生しなくても、決定ボタンを押したら地名表示はキャンセルする
                if (sys.trg & PAD_BUTTON_DECIDE){
                    StopPlaceName(fsys->fldmap->place_name_cont);	//地名表示キャンセル
                }
				
				{
					BOOL touch = FALSE;
					POKETCH_WORK *poketch = GetPoketchMainWorkPtr();
					if( poketch != NULL ){ touch = Poketch_CheckTouch( poketch ); }
					
                	Player_MoveControl(
						fsys->player, fsys->map_cont_dat, DIR_NOT, req.trg, req.cont, touch );
				}
            }
        }
		break;
      default: // 通信していない普通の状態
        if(bMoveControl){
            if( CheckRequest( &req, fsys ) == TRUE ){
                StopPlaceName(fsys->fldmap->place_name_cont);	//地名表示キャンセル
                BoardSetDirect( fsys, BOARD_REQ_DEL );	// 看板処理破棄（即消去）
				Player_MoveStateClear( fsys->player );	//自機動作状態（自転車速度など）クリア
				Player_EventPoketchCancel( fsys->player );	//自機ポケッチ状態キャンセル
                //ポケッチスリープ処理
                Field_SendPoketchInfo( fsys, POKETCH_SEND_SLEEP, TRUE );
            }
            else{
                //イベントが発生しなくても、決定ボタンを押したら地名表示はキャンセルする
                if (sys.trg & PAD_BUTTON_DECIDE){
                    StopPlaceName(fsys->fldmap->place_name_cont);	//地名表示キャンセル
                }
				
				{
					BOOL touch = FALSE;
					POKETCH_WORK *poketch = GetPoketchMainWorkPtr();
					if( poketch != NULL ){ touch = Poketch_CheckTouch( poketch ); }
					
                	Player_MoveControl(
						fsys->player, fsys->map_cont_dat, DIR_NOT, req.trg, req.cont, touch );
				}
            }
        }
        break;
    }
}

//===========================================================================
/**
 * 
 * アプリタスク設定(フィールドはホールド状態になる)
 *
 */
//===========================================================================
void FieldSystemProc_SeqHold(void)
{
	FieldSysWork->ctrl->pause_flag = TRUE;
    CommDisableSendMoveData();  // 移動禁止
}


//===========================================================================
/**
 * 
 * アプリタスク終了(フィールド復帰)
 *
 */
//===========================================================================
void FieldSystemProc_SeqHoldEnd(void)
{
	FieldSysWork->ctrl->pause_flag = FALSE;
    CommEnableSendMoveData();  //移動許可
}


//===========================================================================
//
// ポケッチ関連
//
//===========================================================================

struct _POKETCH_WORK* GetPoketchMainWorkPtr(void)
{
	if (FieldSysWork->fldmap == NULL) {
		return NULL;
	}
	return FieldSysWork->fldmap->poketch;
}


//===========================================================================
//
//
//
//===========================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
GF_BGL_INI * FieldBglIniGet( void * fsys )
{
	FIELDSYS_WORK * wk = (FIELDSYS_WORK *)fsys;

	return wk->bgl;
}

//------------------------------------------------------------------
/**
 * @brief	セーブデータへのポインタ取得
 * @param	fsys		フィールド制御ワークへのポインタ
 * @return	SAVEDATA	セーブデータへのポインタ
 */
//------------------------------------------------------------------
SAVEDATA * GameSystem_GetSaveData(void * fsys)
{
	return ((FIELDSYS_WORK *)fsys)->savedata;
}

