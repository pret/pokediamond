//============================================================================================
/**
 * @file	poketch_c.c
 * @bfief	ポケッチ（メイン）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\lib_pack.h"
#include "system\pm_overlay.h"
#include "gflib\touchpanel.h"
#include "system\snd_tool.h"
#include "savedata\mystatus.h"
#include "..\field_event.h"

#include "field\poketch.h"
#include "poketch_sound.h"
#include "poketch_prv.h"
#include "poketch_main.h"
#include "poketch_button.h"


//#define POKETCH_PROC_PRINT_ENABLE

#ifdef POKETCH_PROC_PRINT_ENABLE
static void PoketchProcPrintf(const char* fmt, ...)
{
	va_list vlist;

	va_start( vlist, fmt );
	OS_TVPrintf( fmt, vlist );
	va_end(vlist);
}
#else
#define PoketchProcPrintf(...)	/* */
#endif


//====================================================
// アプリオーバーレイモジュール宣言
//====================================================
FS_EXTERN_OVERLAY(poketch_app_dwatch);
FS_EXTERN_OVERLAY(poketch_app_awatch);
FS_EXTERN_OVERLAY(poketch_app_stopwatch);
FS_EXTERN_OVERLAY(poketch_app_calc);
FS_EXTERN_OVERLAY(poketch_app_memo);
FS_EXTERN_OVERLAY(poketch_app_dotart);
FS_EXTERN_OVERLAY(poketch_app_simple_pokelist);
FS_EXTERN_OVERLAY(poketch_app_dummy);
FS_EXTERN_OVERLAY(poketch_app_natsuki_checker);
FS_EXTERN_OVERLAY(poketch_app_dowsing);
FS_EXTERN_OVERLAY(poketch_app_counter);
FS_EXTERN_OVERLAY(poketch_app_pedometer);
FS_EXTERN_OVERLAY(poketch_app_cointoss);
FS_EXTERN_OVERLAY(poketch_app_trainer_launcher);
FS_EXTERN_OVERLAY(poketch_app_wazaeff);
FS_EXTERN_OVERLAY(poketch_app_color_changer);
FS_EXTERN_OVERLAY(poketch_app_sodateya_camera);
FS_EXTERN_OVERLAY(poketch_app_love_tester);
FS_EXTERN_OVERLAY(poketch_app_alarm);
FS_EXTERN_OVERLAY(poketch_app_roulette);
FS_EXTERN_OVERLAY(poketch_app_kitchen);
FS_EXTERN_OVERLAY(poketch_app_comm_search);
FS_EXTERN_OVERLAY(poketch_app_backlight);
FS_EXTERN_OVERLAY(poketch_app_dummy_monitor);
FS_EXTERN_OVERLAY(poketch_app_mark_map);
FS_EXTERN_OVERLAY(poketch_app_seed_map);
FS_EXTERN_OVERLAY(poketch_app_calendar);
FS_EXTERN_OVERLAY(poketch_app_pokemon_counter);
FS_EXTERN_OVERLAY(poketch_app_pokemon_history);

//====================================================
// アプリオーバーレイＩＤテーブル
//====================================================
static const struct {
	int          appID;
	FSOverlayID  overlayID;
}OverlayID[] = {

	{ POKETCH_APPID_DWATCH,				FS_OVERLAY_ID(poketch_app_dwatch) },			// 00: デジタル時計
	{ POKETCH_APPID_STOPWATCH,			FS_OVERLAY_ID(poketch_app_stopwatch) },			// 01: ストップウォッチ
	{ POKETCH_APPID_CALC,				FS_OVERLAY_ID(poketch_app_calc) },				// 02: 電卓
	{ POKETCH_APPID_MEMO,				FS_OVERLAY_ID(poketch_app_memo) }, 				// 03: メモ帳
	{ POKETCH_APPID_AWATCH,				FS_OVERLAY_ID(poketch_app_awatch) },			// 04: アナログ時計
	{ POKETCH_APPID_DOTART,				FS_OVERLAY_ID(poketch_app_dotart) },			// 05: ドットアート
	{ POKETCH_APPID_POKELIST,			FS_OVERLAY_ID(poketch_app_simple_pokelist) },	// 06: 簡易ポケモンリスト
	{ POKETCH_APPID_NATSUKI_CHECK,		FS_OVERLAY_ID(poketch_app_natsuki_checker) },	// 07: なつき度チェッカー
	{ POKETCH_APPID_DOWSING,			FS_OVERLAY_ID(poketch_app_dowsing) },			// 08: ダウジングマシン
	{ POKETCH_APPID_COUNTER,			FS_OVERLAY_ID(poketch_app_counter) },			// 09: カウンター
	{ POKETCH_APPID_PEDOMETER,			FS_OVERLAY_ID(poketch_app_pedometer) },			// 10: 万歩計
	{ POKETCH_APPID_SODATEYA_CAMERA,	FS_OVERLAY_ID(poketch_app_sodateya_camera) },	// 15: そだてやカメラ
	{ POKETCH_APPID_ROULETTE,			FS_OVERLAY_ID(poketch_app_roulette) },			// 16: ルーレット
	{ POKETCH_APPID_COINTOSS,			FS_OVERLAY_ID(poketch_app_cointoss) },			// 17: コイントス
	{ POKETCH_APPID_WAZA_EFF_CHECK,		FS_OVERLAY_ID(poketch_app_wazaeff) },			// 18: わざ効果チェッカー
	{ POKETCH_APPID_LOVETESTER,			FS_OVERLAY_ID(poketch_app_love_tester) },		// 19: ラブテスター
	{ POKETCH_APPID_ALARM_WATCH,		FS_OVERLAY_ID(poketch_app_alarm) },				// 20: アラーム時計
	{ POKETCH_APPID_KITCHEN_TIMER,		FS_OVERLAY_ID(poketch_app_kitchen) },			// 21: キッチンタイマー
	{ POKETCH_APPID_MAP_MARKING,		FS_OVERLAY_ID(poketch_app_mark_map) },			// 22: マーキングマップ
	{ POKETCH_APPID_SEED_SEARCHER,		FS_OVERLAY_ID(poketch_app_seed_map) },			// 23: きのみマップ
	{ POKETCH_APPID_COLOR_CHANGER,		FS_OVERLAY_ID(poketch_app_color_changer) },		// 24: カラーチェンジャー
	{ POKETCH_APPID_CALENDER,			FS_OVERLAY_ID(poketch_app_calendar) },			// 25: カレンダー
	{ POKETCH_APPID_COMM_SEARCHER,		FS_OVERLAY_ID(poketch_app_comm_search) },		// 27: つうしんサーチャー
	{ POKETCH_APPID_POKEMON_COUNTER,	FS_OVERLAY_ID(poketch_app_pokemon_counter) },	// 28: ポケモンカウンター
	{ POKETCH_APPID_POKEMON_HISTORY,	FS_OVERLAY_ID(poketch_app_pokemon_history) },	// 29: ポケモンヒストリー

};


//====================================================
// シーケンス
//====================================================
enum {
	SEQ_INIT = 0,
	SEQ_APP_MAIN,
	SEQ_APPCHANGE_NORMAL,
	SEQ_CLEANUP,
	SEQ_QUIT,
};

// スリープ以降時のシーケンス
enum {
	SLEEP_SEQ_NULL,	// 何もない
	SLEEP_SEQ_REQ,	// スリープリクエストあり
	SLEEP_SEQ_MAIN,	// スリープ中です
	SLEEP_SEQ_WAKE,	// ウェイクリクエストあり
};

// アプリ状態
enum {
	APP_STATE_CLEAN = 0,	///< 何も動いていない状態
	APP_STATE_INIT,			///< 初期化処理実行中
	APP_STATE_RUN,			///< 動作中
	APP_STATE_QUIT,			///< 終了処理実行中
};

//====================================================
// ヒープ使用サイズ
//====================================================
enum {
	HEAPSIZE_MAIN = 0xc000,
	HEAPSIZE_APP = 0xc000,
};
//====================================================
// そのた定数
//====================================================
enum {
	APP_SKIP_TIMER = 30,
	APP_FIRST_SKIP_TIMER = 3,
};

//====================================================
// メインワーク
//====================================================
struct _POKETCH_WORK {
	u8	main_seq;
	u8	seq;
	u8	app_state;

	u8	touch_flag;
	u8	player_move_flag;
	u8  app_changing_flag;
	u8  appchange_button_disable_flag;
	u8  pedometer_update_flag;

	u32  button_action;
	BOOL app_skip_flag;
	u32  app_skip_timer;
	int  load_app_id;
	FSOverlayID  load_app_overlay_id;

	POKETCH_VIEW_WORK	*view_wk;
	POKETCH_MAIN_VPARAM  vpara;
	void				*app_work;

	POKETCH_BUTTON_MAN*				button;
	u32						button_cmd_req;
	u32						button_prev_cmd;

	struct _POKETCH_WORK**  this_work_adrs;	// 消去時用に自分のアドレスを持つ
	TCB_PTR                 tail_task;

	// アプリケーションの制御関数
	pAppInitProc	app_init_proc;
	pAppQuitProc	app_quit_proc;
	pAppSaveProc	app_save_proc;
	void*			app_save_arg;

	GF_BGL_INI*						bgl;
	NNSG2dOamManagerInstance*		oamm;

	SAVEDATA*       savedata;
	POKETCH_DATA*   poketch_savedata;
	FIELDSYS_WORK*  fieldsys;
};

//==============================================================
// Prototype
//==============================================================
static void PoketchProcPrintf(const char* fmt, ...);
static POKETCH_WORK* GetMainWorkPtr(void);
static BOOL PoketchWorkSetup( POKETCH_WORK* wk );
static void PoketchWorkCleanup( POKETCH_WORK* wk );
static void PoketchMain(TCB_PTR tcb, void *wk_adrs);
static void PoketchTail( TCB_PTR tcb, void* wk_adrs );
static void ChangeSeq( POKETCH_WORK *wk, u32 seq );
static void SeqInit(POKETCH_WORK *wk);
static void SeqAppMain(POKETCH_WORK *wk);
static void SeqAppChange(POKETCH_WORK *wk);
static void SeqCleanUp( POKETCH_WORK *wk );
static void LoadApplication( POKETCH_WORK* wk, int appID);
static void UnloadApplication( POKETCH_WORK* wk );
static void InitApplication( POKETCH_WORK* wk, u32 app_no );
static BOOL WaitInitApplication( POKETCH_WORK* wk );
static void QuitApplication( POKETCH_WORK* wk );
static BOOL WaitQuitApplication( POKETCH_WORK* wk );
static BOOL BmnSetup( POKETCH_WORK* wk );
static void BmnCleanup( POKETCH_WORK *wk );
static void ButtonUpdate( POKETCH_WORK *wk );
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static BOOL ButtonViewReq( POKETCH_VIEW_WORK *vwk, u32 cmd );
static inline BOOL check_inside_poketch_screen( u32 x, u32 y );


extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);



//------------------------------------------------------------------
/**
 * メインワークポインタを返す
 *
 * @retval  POKETCH_WORK*		メインワークポインタ
 */
//------------------------------------------------------------------
static POKETCH_WORK* GetMainWorkPtr(void)
{
	#ifdef PM_DEBUG
	extern POKETCH_WORK* GetPoketchMainWorkPtrDebug(void);
	#endif

	return  GetPoketchMainWorkPtr();
}

//------------------------------------------------------------------
/**
 * ポケッチ初期化開始（フィールド開始時にのみ呼ばれる）
 *
 * @param   wk_adrs		ワークアドレスを保存する変数のポインタ
 * @param   savedata	ポケッチセーブデータポインタ
 * @param   bgl			画面構築に使うBGLシステムポインタ
 *
 */
//------------------------------------------------------------------
void PoketchInit( FIELDSYS_WORK* fsys, POKETCH_WORK **wk_adrs, SAVEDATA* savedata,  GF_BGL_INI* bgl, NNSG2dOamManagerInstance* oamm )
{
	POKETCH_WORK *wk;

	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKETCH_MAIN, HEAPSIZE_MAIN );
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKETCH_APP,  HEAPSIZE_APP );

	wk = sys_AllocMemory(POKETCH_MAIN_CTRL_HEAPID, sizeof(POKETCH_WORK));

	if(wk != NULL)
	{
		*wk_adrs = wk;

		wk->fieldsys = fsys;
		wk->savedata = savedata;
		wk->poketch_savedata = SaveData_GetPoketchData( savedata );
		wk->bgl = bgl;
		wk->oamm = oamm;

		if( PoketchWorkSetup( wk ) )
		{
			InitTPSystem();			// タッチパネルシステム初期化
			InitTPNoBuff(4);

			wk->this_work_adrs = wk_adrs;
			wk->tail_task = TCB_Add( PoketchTail, wk, POKETCH_TAIL_TASKPRI );
			TCB_Add( PoketchMain, wk, POKETCH_MAIN_TASKPRI );
		}
	}
}

//------------------------------------------------------------------
/**
 * ポケッチ終了処理開始
 *
 * @param   wk		ポケッチワークポインタ（PoketchInitで渡したもの）
 *
 */
//------------------------------------------------------------------
void PoketchQuitReq(POKETCH_WORK *wk)
{
	PoketchProcPrintf("ポケッチ終了通知\n");
	if( (wk->main_seq != SEQ_CLEANUP) && (wk->main_seq != SEQ_QUIT) )
	{
		ChangeSeq( wk, SEQ_CLEANUP );
	}
}
//------------------------------------------------------------------
/**
 * ポケッチ終了待ち
 *
 * @param   wk		ポケッチワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PoketchQuitWait( POKETCH_WORK *wk )
{
	return (wk == NULL);
}

//==============================================================================================
//
// フィールドとのやりとり
//
//==============================================================================================

//------------------------------------------------------------------
/**
 * フィールドからポケッチへ各種状況変化の通知を受け取る
 *
 * @param   wk		
 * @param   id		
 * @param   value		
 *
 */
//------------------------------------------------------------------
void Poketch_SendRequest( POKETCH_WORK* wk, FIELD_POKETCH_SEND_ID  id, u32 value )
{
	switch( id ){
	case POKETCH_SEND_SLEEP:
		break;

	case POKETCH_SEND_MOVE_PLAYER:
		wk->player_move_flag = TRUE;
		break;

	case POKETCH_SEND_PEDOMATER:
		{
			u32 count = PoketchData_GetPedometer( wk->poketch_savedata );
			if( ++count > 99999 )
			{
				count = 0;
			}
			PoketchData_SetPedometer( wk->poketch_savedata, count );
			wk->pedometer_update_flag = TRUE;
			
		}
		break;

	case POKETCH_SEND_SAVE:
		if( wk->app_state == APP_STATE_RUN )
		{
			if( wk->app_save_proc )
			{
				wk->app_save_proc( wk->app_save_arg );
			}
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * フィールド側から呼び出され、
 * ポケッチのボタン・スクリーンをタッチしているかチェック
 *
 * @param   wk			ポケッチワークポインタ
 *
 * @retval  BOOL		TRUEでタッチしている
 */
//------------------------------------------------------------------
BOOL Poketch_CheckTouch( POKETCH_WORK* wk )
{
	return wk->touch_flag;
}

//------------------------------------------------------------------
/**
 * ポケッチで現在稼働中のアプリナンバーを返す
 *
 * @param   wk		ポケッチワークポインタ
 *
 * @retval  int		アプリナンバー
 */
//------------------------------------------------------------------
int Poketch_GetRunningApplication( POKETCH_WORK* wk )
{
	return wk->load_app_id;
}


//------------------------------------------------------------------
/**
 * メインワークセットアップ
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
static BOOL PoketchWorkSetup( POKETCH_WORK* wk )
{
	if(Poketch_MAIN_SetViewWork( &(wk->view_wk), &(wk->vpara), wk->oamm, wk ))
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;

		wk->touch_flag = FALSE;
		wk->player_move_flag = FALSE;
		wk->pedometer_update_flag = FALSE;
		wk->app_changing_flag = FALSE;
		wk->appchange_button_disable_flag = FALSE;
		wk->load_app_id = POKETCH_APP_NONE;
		wk->app_state = APP_STATE_CLEAN;

		wk->button_action = BMN_EVENT_NULL;

		if( BmnSetup( wk ) )
		{
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * メインワーククリーンアップ
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void PoketchWorkCleanup( POKETCH_WORK* wk )
{
	TCB_Delete( wk->tail_task );
	BmnCleanup( wk );
	UnloadApplication( wk );
	Poketch_MAIN_DeleteViewWork( wk->view_wk );
}

//------------------------------------------------------------------
/**
 * ポケッチメインタスク
 *8+
 * @param   tcb			TCBポインタ
 * @param   wk_adrs		ワークアドレス
 */
//------------------------------------------------------------------
static void PoketchMain(TCB_PTR tcb, void *wk_adrs)
{
	static void (* const seq_tbl[])(POKETCH_WORK *) = {
		SeqInit,
		SeqAppMain,
		SeqAppChange,
		SeqCleanUp,
	};

	POKETCH_WORK *wk;

	wk = (POKETCH_WORK *)wk_adrs;

	if( wk->main_seq < NELEMS(seq_tbl) )
	{
		if( wk->main_seq != SEQ_INIT )
		{
			ButtonUpdate( wk );
		}
		seq_tbl[ wk->main_seq ]( wk );
	}
	else
	{
		GF_ASSERT( wk->main_seq == SEQ_QUIT );
		*(wk->this_work_adrs) = NULL;
		PoketchWorkCleanup( wk );
		sys_FreeMemoryEz( wk );
		TCB_Delete( tcb );

		sys_DeleteHeap( HEAPID_POKETCH_MAIN );
		sys_DeleteHeap( HEAPID_POKETCH_APP );

	}
}

//------------------------------------------------------------------
/**
 * メイン、描画等、全ての処理が終わった後に１回回ってくるタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PoketchTail( TCB_PTR tcb, void* wk_adrs )
{
	POKETCH_WORK* wk = wk_adrs;

	wk->player_move_flag = FALSE;
	wk->pedometer_update_flag = FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス切り替え
 *
 * @param   wk		ワークポインタ
 * @param   seq		次のシーケンス
 *
 */
//------------------------------------------------------------------
static void ChangeSeq( POKETCH_WORK *wk, u32 seq )
{
	wk->main_seq = seq;
	wk->seq = 0;
}


//------------------------------------------------------------------
/**
 * シーケンス：画面構築
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void SeqInit(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_MAIN_SetCommand(wk->view_wk, CMD_MAIN_INIT);
		wk->seq++;
		break;

	case 1:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_INIT))
		{
			u32 appID = PoketchData_GetNowApplication(wk->poketch_savedata);
			LoadApplication( wk, appID );
			InitApplication( wk, appID );
			wk->seq++;
		}
		break;

	case 2:
		if( WaitInitApplication(wk) == FALSE )
		{
			break;
		}
		Poketch_MAIN_SetCommand(wk->view_wk, CMD_MAIN_FIRSTOPEN);
		wk->seq++;
		/* fallthru */
	case 3:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_FIRSTOPEN))
		{
			ChangeSeq(wk, SEQ_APP_MAIN);
		}
	}
}
//------------------------------------------------------------------
/**
 * シーケンス：アプリメイン
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SeqAppMain(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		if( PoketchIsSleepMode(wk) )
		{
			return;
		}

		switch( wk->button_action ){
		case BMN_EVENT_TAP:
		case BMN_EVENT_TIMER0:
			PoketchProcPrintf("タップされた\n");
			wk->app_skip_flag = FALSE;
			wk->app_changing_flag = TRUE;
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_EFFCLOSE );
			wk->seq++;
			break;
		}
		break;

	case 1:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			PoketchProcPrintf("スキップフラグON\n");
			wk->app_skip_flag = TRUE;
		}

		if(Poketch_MAIN_WaitCommandAll( wk->view_wk ))
		{
			wk->vpara.app_pos = PoketchData_SetApplicationPosNext( wk->poketch_savedata );
			if( wk->app_skip_flag )
			{
				Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_DISP );
				wk->app_skip_timer = APP_SKIP_TIMER;
				wk->app_skip_flag = FALSE;
				wk->seq = 4;
			}
			else
			{
				PoketchProcPrintf("ＳＥＱ２へ\n");
				wk->app_skip_timer = APP_FIRST_SKIP_TIMER;
				wk->seq = 2;
			}
		}
		break;

	case 2:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_DISP );
			wk->app_skip_timer = APP_SKIP_TIMER;
			wk->app_skip_flag = FALSE;
			wk->seq = 4;
			break;
		}

		if( wk->app_skip_timer )
		{
			wk->app_skip_timer--;
		}
		else
		{
			QuitApplication( wk );
			wk->seq = 3;
		}
		break;

	case 3:
		if( WaitQuitApplication(wk) )
		{
			PoketchProcPrintf("アプリ終わったので切り替えシーケンスへ\n");
			UnloadApplication( wk );
			PoketchWork_Reset();
			ChangeSeq(wk, SEQ_APPCHANGE_NORMAL);
		}
		break;

	// 連打受付開始
	case 4:
		if( wk->button_action == BMN_EVENT_TAP || wk->button_action == BMN_EVENT_TIMER0 )
		{
			wk->vpara.app_pos = PoketchData_SetApplicationPosNext( wk->poketch_savedata );
			wk->app_skip_timer = APP_SKIP_TIMER;
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_UPDATE );
			break;
		}

		if(wk->app_skip_timer)
		{
			wk->app_skip_timer--;
		}
		else
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_SKIPNUM_END );
			QuitApplication( wk );
			wk->seq = 3;
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * シーケンス：アプリ切り替え
 *
 * @param   wk		
 */
//------------------------------------------------------------------
static void SeqAppChange(POKETCH_WORK *wk)
{
	switch(wk->seq){
	case 0:
		{
			u32 appID;
			wk->appchange_button_disable_flag = TRUE;

			appID = PoketchData_GetNowApplication( wk->poketch_savedata );
			LoadApplication( wk, appID );
			InitApplication( wk, appID );

			wk->seq++;
		}
		break;

	case 1:
		if( WaitInitApplication(wk) )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_EFFOPEN );
			wk->seq++;
		}
		break;

	case 2:
		if(Poketch_MAIN_WaitCommand(wk->view_wk, CMD_MAIN_EFFOPEN))
		{
			wk->app_changing_flag = FALSE;
			wk->appchange_button_disable_flag = FALSE;
			ChangeSeq(wk, SEQ_APP_MAIN);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * シーケンス：ポケッチ終了
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SeqCleanUp( POKETCH_WORK *wk )
{
	enum {
		SEQ_INIT = 0,
		SEQ_WAIT_APP_INIT,
		SEQ_WAIT_APP_QUIT,
		SEQ_WAIT_VIEW_QUIT,
	};

	switch( wk->seq ){
	case SEQ_INIT:
		switch( wk->app_state ){
		case APP_STATE_INIT:
			wk->seq = SEQ_WAIT_APP_INIT;
			break;
		case APP_STATE_RUN:
			QuitApplication( wk );
			wk->seq = SEQ_WAIT_APP_QUIT;
			break;
		case APP_STATE_QUIT:
		case APP_STATE_CLEAN:
			wk->seq = SEQ_WAIT_APP_QUIT;
			break;
		}
		break;

	case SEQ_WAIT_APP_INIT:
		if( WaitInitApplication(wk) )
		{
			QuitApplication( wk );
			wk->seq = SEQ_WAIT_APP_QUIT;
		}
		break;

	case SEQ_WAIT_APP_QUIT:
		if( WaitQuitApplication(wk) )
		{
			Poketch_MAIN_SetCommand( wk->view_wk, CMD_MAIN_QUIT );
			wk->seq = SEQ_WAIT_VIEW_QUIT;
		}
		break;

	case SEQ_WAIT_VIEW_QUIT:
		if( Poketch_MAIN_WaitCommandAll( wk->view_wk ) )
		{
			UnloadApplication( wk );
			StopTP();
			ChangeSeq( wk, SEQ_QUIT );
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * アプリケーションのオーバーレイモジュールをロード
 *
 * @param   app_no		アプリケーションナンバー
 *
 */
//------------------------------------------------------------------
static void LoadApplication( POKETCH_WORK* wk, int appID)
{
	GF_ASSERT( appID >= 0 && appID < NELEMS(OverlayID) );

	if( wk->load_app_id == POKETCH_APP_NONE )
	{
		int i;
		PoketchProcPrintf("アプリ Load します\n");

		for(i=0; i<NELEMS(OverlayID); i++)
		{
			if( OverlayID[i].appID == appID )
			{
				Overlay_Load( OverlayID[i].overlayID, OVERLAY_LOAD_NOT_SYNCHRONIZE);
				wk->load_app_id = appID;
				wk->load_app_overlay_id = OverlayID[i].overlayID;
				break;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * アプリケーションのオーバーレイモジュールをアンロード
 *
 * @param   app_no		
 *
 */
//------------------------------------------------------------------
static void UnloadApplication( POKETCH_WORK* wk )
{
	if( wk->load_app_id != POKETCH_APP_NONE )
	{
		PoketchProcPrintf("アプリ Unload します\n");
		Overlay_UnloadID( wk->load_app_overlay_id );
		wk->load_app_id = POKETCH_APP_NONE;
	}
}


//------------------------------------------------------------------
/**
 * ロードしたアプリの初期化開始
 *
 * @param   wk		
 * @param   app_no		
 *
 */
//------------------------------------------------------------------
static void InitApplication( POKETCH_WORK* wk, u32 app_no )
{
	GF_ASSERT(wk->app_state == APP_STATE_CLEAN);
	PoketchProcPrintf("アプリ初期化開始します\n");
	wk->app_init_proc( &(wk->app_work), wk, wk->bgl, wk->load_app_id );
	wk->app_state = APP_STATE_INIT;
}
//------------------------------------------------------------------
/**
 * ロードしたアプリの初期化終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL WaitInitApplication( POKETCH_WORK* wk )
{
	if( wk->app_state == APP_STATE_RUN )
	{
		PoketchProcPrintf("アプリ初期化完了しました\n");
		return TRUE;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * ロードしたアプリの終了処理開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void QuitApplication( POKETCH_WORK* wk )
{
	GF_ASSERT(wk->app_state == APP_STATE_RUN);
	PoketchProcPrintf("アプリ終了処理開始します\n");
	wk->app_quit_proc( wk->app_work );
	wk->app_state = APP_STATE_QUIT;
}
//------------------------------------------------------------------
/**
 * ロードしたアプリの終了処理待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL WaitQuitApplication( POKETCH_WORK* wk )
{
	if( wk->app_state == APP_STATE_CLEAN )
	{
		PoketchProcPrintf("アプリ終了処理完了しました\n");
		return TRUE;
	}
	return FALSE;
}

/*====================================================================================*/
/*                                                                                    */
/*  各アプリから通知を受け取る関数群                                                  */
/*                                                                                    */
/*====================================================================================*/

//------------------------------------------------------------------
/**
 * 各アプリモジュールのロード後、NitroStaticInitにより呼び出されて
 * アプリの各種制御関数アドレスを受け取る
 *
 * @param   initproc		初期化関数
 * @param   quitproc		終了関数
 *
 */
//------------------------------------------------------------------
void PoketchSetAppProc( pAppInitProc initproc, pAppQuitProc quitproc)
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	wk->app_init_proc = initproc;
	wk->app_quit_proc = quitproc;
	wk->app_save_proc = NULL;
}
//------------------------------------------------------------------
/**
 * 各アプリからの初期化完了通知を受け取る
 */
//------------------------------------------------------------------
void PoketchNoticeAppStart(CONTACT_WORK* wk)
{
	PoketchProcPrintf("アプリ開始通知うけとり\n");

	GF_ASSERT(wk->app_state==APP_STATE_INIT);
	wk->app_state = APP_STATE_RUN;
}
//------------------------------------------------------------------
/**
 * 各アプリからの終了通知を受け取る
 */
//------------------------------------------------------------------
void PoketchNoticeAppEnd(CONTACT_WORK* wk)
{
	PoketchProcPrintf("アプリ終了通知うけとり\n");

	GF_ASSERT(wk->app_state==APP_STATE_QUIT);
	wk->app_state = APP_STATE_CLEAN;
}

//------------------------------------------------------------------
/**
 * 各アプリのデータセーブ用関数アドレスを受け取る
 *（レポート時にセーブが必要なアプリのみ利用する）
 *
 * @param   saveproc	セーブ関数アドレス
 * @param   arg			関数呼び出しに必要な引数
 *
 */
//------------------------------------------------------------------
void PoketchSetAppSaveProc( pAppSaveProc saveproc, void* arg )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	wk->app_save_proc = saveproc;
	wk->app_save_arg = arg;
}


/*====================================================================================*/
/*                                                                                    */
/*  ボタン状態ワーク処理                                                              */
/*                                                                                    */
/*====================================================================================*/

// enum POKETCH_BUTTON_VIEW の並びと同期
static const u32 ButtonViewCmd[] = {
	CMD_MAIN_BUTTONFREE,
	CMD_MAIN_BUTTONLOCK,
	CMD_MAIN_BUTTONPUSH,
};

enum {
	BUTTON_TIMER_TAP = 7,
	BUTTON_TIMER_DOUBLETAP = 8,		// 最初のタップからダブルタップ判定を行うフレーム数
};

enum {
	BUTTON_ID_MAIN,		///< メインのボタン
	BUTTON_ID_SCREEN,	///< 画面全体をボタンとして扱う…
};

//------------------------------------------------------------------
/**
 * ボタン管理マネージャセットアップ
 *
 * @param   wk			アプリワーク
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
static BOOL BmnSetup( POKETCH_WORK* wk )
{
	// ボタン位置（viewに持った方が良いのか…?）
	static const TP_HIT_TBL ButtonRectData[] = {
		{ 96, 172, 220, 244 },
		{ POKETCH_MONITOR_DOT_YORG, POKETCH_MONITOR_DOT_YEND, POKETCH_MONITOR_DOT_XORG, POKETCH_MONITOR_DOT_XEND },
	};

	wk->button = PBTN_Create( ButtonRectData, NELEMS(ButtonRectData), BmnCallBack, wk, POKETCH_MAIN_CTRL_HEAPID );
	if( wk->button != NULL )
	{
		PBTN_SetEventTime( wk->button, 0, 0, BUTTON_TIMER_TAP );
		wk->button_cmd_req = CMD_NULL;
		wk->button_prev_cmd = CMD_NULL;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ボタン管理マネージャクリーンアップ
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void BmnCleanup( POKETCH_WORK *wk )
{
	PBTN_Delete( wk->button );
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void ButtonUpdate( POKETCH_WORK *wk )
{
	wk->button_action = BMN_EVENT_NULL;
	PBTN_Main( wk->button );
}
//------------------------------------------------------------------
/**
 * ボタン管理マネージャからのコールバック関数
 *
 * @param   idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs )
{
	POKETCH_WORK *wk = (POKETCH_WORK*)wk_adrs;

	// フィールド側に通知する「ポケッチ触ってるフラグ」の更新
	if( PoketchIsSleepMode(wk) == FALSE )
	{
		switch( touch_event ){
		case BMN_TOUCH_ON:
			wk->touch_flag = TRUE;
			break;
		case BMN_TOUCH_OFF:
			wk->touch_flag = FALSE;
			break;
		}
	}
	else
	{
		wk->touch_flag = FALSE;
	}

	// スクリーン部を触られた時の処理
	if( idx == BUTTON_ID_SCREEN )
	{
		if( PoketchIsSleepMode(wk) )
		{
			if(touch_event == BMN_TOUCH_ON)
			{
				Snd_SePlay( POKETCH_SE_BEEP );
			}
		}
	}
	// ボタン部を触られた時の処理
	else
	{
		u32 v_cmd = CMD_NULL;

		switch(touch_event){
		case BMN_TOUCH_OFF:
			v_cmd = CMD_MAIN_BUTTONFREE;
			PoketchProcPrintf( "@@BTN  off\n");
			break;
		case BMN_TOUCH_ON:
			if( PoketchIsSleepMode(wk) || wk->appchange_button_disable_flag )
			{
				v_cmd = CMD_MAIN_BUTTONLOCK;
				event = BMN_EVENT_NULL;
				PoketchProcPrintf( "@@BTN  on, sleep\n");
			}
			else
			{
				v_cmd = CMD_MAIN_BUTTONPUSH;
				PoketchProcPrintf( "@@BTN  on, wake\n");
			}
			break;
		}

		if( wk->button_cmd_req != CMD_NULL )
		{
			u32 tmp = v_cmd;
			PoketchProcPrintf( "@@BTN  cmd_swap %d->%d\n", v_cmd, wk->button_cmd_req);
			v_cmd = wk->button_cmd_req;
			wk->button_cmd_req = tmp;
		}

		if(v_cmd != CMD_NULL)
		{
			PoketchProcPrintf( "@@BTN  vcmd:%d\n", v_cmd);
			if( ButtonViewReq( wk->view_wk, v_cmd ) )
			{
				if( v_cmd == CMD_MAIN_BUTTONLOCK || v_cmd == CMD_MAIN_BUTTONPUSH )
				{
					wk->button_prev_cmd = v_cmd;
				}
			}
		}

		switch( event ){
		case BMN_EVENT_TIMER0:
			PBTN_ResetState( wk->button, 0 );
			break;
		case BMN_EVENT_TAP:
			// スリープ中に押下されてロック→タップ時はスリープじゃないのでボタンイベント有効
			// みたいなことを防ぐ
			if( wk->button_prev_cmd == CMD_MAIN_BUTTONLOCK )
			{
				event = BMN_EVENT_NULL;
			}
			break;
		case BMN_EVENT_OUT:
			// 押したんだったらスライドアウトでも反応させる
			if( wk->button_prev_cmd == CMD_MAIN_BUTTONPUSH )
			{
				event = BMN_EVENT_TAP;
			}
			break;
		}

		PoketchProcPrintf( "@@BTN  event=%d\n", event);
		wk->button_action = event;
	}
}
//------------------------------------------------------------------
/**
 * ボタン表示更新コマンドをview側に伝える
 *
 * @param   wk		ポケッチワーク
 * @param   cmd		コマンド
 *
 * @retval  TRUEでコマンド発行した／FALSEだと前のコマンド処理中なので無視した
 */
//------------------------------------------------------------------
static BOOL ButtonViewReq( POKETCH_VIEW_WORK *vwk, u32 cmd )
{
	u32 i;

	for(i = 0; i < NELEMS(ButtonViewCmd); i++)
	{
		if( Poketch_MAIN_WaitCommand( vwk, cmd ) == FALSE )
		{
			return FALSE;
		}
	}
	Poketch_MAIN_SetCommand( vwk, cmd );
	return TRUE;
}



/*====================================================================================*/
/*                                                                                    */
/*  描画ｺﾝﾄﾛｰﾙ側から呼び出される関数                                                  */
/*                                                                                    */
/*====================================================================================*/

POKETCH_VIEW_WORK* PoketchGetMainViewWork( void )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	return wk->view_wk;
}


void PoketchSePlay( u32 se )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		Snd_SePlay( se );
	}
}

void PoketchVoicePlay( u32 pokeno )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		Snd_PMVoicePlay( pokeno );
	}
}
static inline BOOL check_inside_poketch_screen( u32 x, u32 y )
{
	if( ((u32)(x - POKETCH_MONITOR_DOT_XORG) < (u32)(POKETCH_MONITOR_DOT_XEND - POKETCH_MONITOR_DOT_XORG))
	&	((u32)(y - POKETCH_MONITOR_DOT_YORG) < (u32)(POKETCH_MONITOR_DOT_YEND - POKETCH_MONITOR_DOT_YORG))
	){
		return TRUE;
	}
	return FALSE;
}


BOOL PoketchGetTPCont( u32* x, u32 *y )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		if( GF_TP_GetPointCont(x, y) )
		{
			return check_inside_poketch_screen(*x, *y);
		}
	}
	return FALSE;
}

BOOL PoketchGetTPTrg( u32* x, u32 *y )
{
	POKETCH_WORK *wk = GetMainWorkPtr();

	if(	(wk->app_changing_flag == FALSE)
	&&	(PoketchIsSleepMode( wk ) == FALSE)
	){
		if( GF_TP_GetPointTrg( x, y ) )
		{
			return check_inside_poketch_screen(*x, *y);
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * スリープモードかどうかチェック
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL PoketchIsSleepMode( const CONTACT_WORK* wk )
{
	return FieldEvent_Check( wk->fieldsys );
}

//------------------------------------------------------------------
/**
 * ボタンマネージャ処理呼び出し
 *
 * @param   man
 */
//------------------------------------------------------------------
void PoketchButtonMainCall( const CONTACT_WORK* wk, POKETCH_BUTTON_MAN* man )
{
	if(	(PoketchIsSleepMode(wk) ==  FALSE)
	&&	(wk->app_changing_flag == FALSE)
	){
		PBTN_Main( man );
	}
}

//------------------------------------------------------------------
/**
 * プレイヤー移動フラグを取得
 *
 * @param   wk		
 *
 * @retval  BOOL	
 */
//------------------------------------------------------------------
BOOL PoketchGetPlayerMoveTrg( const CONTACT_WORK* wk )
{
	return wk->player_move_flag;;
}
//------------------------------------------------------------------
/**
 * 万歩計更新フラグを取得
 *
 * @param   wk		
 *
 * @retval  BOOL	
 */
//------------------------------------------------------------------
BOOL PoketchGetPedometerUpdateFlag( const CONTACT_WORK* wk )
{
	return wk->pedometer_update_flag;
}

FIELDSYS_WORK* PoketchGetFieldSysWork( const CONTACT_WORK* wk )
{
	return wk->fieldsys;
}

POKETCH_DATA* PoketchGetSaveData( const CONTACT_WORK* wk )
{
	return (POKETCH_DATA*)(wk->poketch_savedata);
}

SAVEDATA* PoketchGetSystemSaveData( const CONTACT_WORK* wk )
{
	return (SAVEDATA*)(wk->savedata);
}

int PoketchGetBoardType( const CONTACT_WORK* wk )
{
	MYSTATUS* myst = SaveData_GetMyStatus( wk->savedata );

	if( MyStatus_GetMySex(myst) == PM_FEMALE )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

