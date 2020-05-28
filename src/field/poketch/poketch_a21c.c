//============================================================================================
/**
 * @file	poketch_a21c.c
 * @bfief	ポケッチ（アプリNoa21：キッチンタイマー）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "gflib\apptimer.h"
#include "system\lib_pack.h"


#include "poketch_sound.h"
#include "poketch_button.h"
#include "poketch_a21.h"
#include "poketch_prv.h"

//==============================================================
// Button
//==============================================================
enum {
	BTN_START,
	BTN_STOP,
	BTN_RESET,
	BTN_MIN10_UP,
	BTN_MIN1_UP,
	BTN_MIN10_DOWN,
	BTN_MIN1_DOWN,
	BTN_SEC10_UP,
	BTN_SEC1_UP,
	BTN_SEC10_DOWN,
	BTN_SEC1_DOWN,
};

typedef struct {
	VIEWPARAM   vpara;
	BOOL        button_enable[PUSH_BUTTON_MAX];
	u64         start_tick;
	u64         stop_tick;
	u64         prev_sec;
	u64         count_sec;
	BOOL        counter_working_flag;
	int         main_seq;
}BACKUP_WORK;




//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;

	u8        reserve_main_seq;
	u8        quit_req_flag;

	u32       appNumber;

	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	POKETCH_BUTTON_MAN*  button;
	u32                  button_id;
	u32                  button_event;

	u64         timer_sec;
	u64         passed_sec;
	u64         timer_backup;

	u64         start_tick;
	u64         stop_tick;

	BOOL        button_update_flag;

	BACKUP_WORK   backup;

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_INPUT,
	SEQ_COUNTDOWN,
	SEQ_PAUSE,
	SEQ_ALARM,
	SEQ_STOP_ALARM,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A21_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber);
static void init_button_state( APPWORK* wk );
static void set_button_enable( APPWORK* wk, u32 button, BOOL flag );
static void set_button_state( APPWORK* wk, u32 button, u32 state );
static void store_backup( APPWORK* wk, BACKUP_WORK* backup );
static void restore_backup( APPWORK* wk );
static void init_backup_states( APPWORK* wk );
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber );
static void CleanupWork( APPWORK *wk );
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void Poketch_A21_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A21_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqInput(APPWORK *wk);
static BOOL SeqCountDown(APPWORK *wk);
static BOOL SeqPause(APPWORK *wk);
static BOOL SeqAlarm(APPWORK *wk);
static BOOL SeqStopAlarm(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);
static u64 start_counter( APPWORK* wk );
static void pause_counter( APPWORK* wk );
static void restart_counter( APPWORK* wk );
static BOOL check_counter_end( APPWORK* wk );
static BOOL update_counter( APPWORK* wk );
static void reset_counter( APPWORK* wk );
static void set_counter_value( APPWORK* wk, u64 total_sec );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A21_Init, Poketch_A21_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 * @param   conwk		アプリが本体から情報を取得する際に必要となるワーク（アプリへは非公開）
 * @param   bgl			BGLモジュールヘッダ
 * @param   appNumber	アプリナンバー
 */
//------------------------------------------------------------------
static BOOL Poketch_A21_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, appNumber ))
		{
			if( TCB_Add(Poketch_A21_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				return TRUE;
			}
		}
		sys_FreeMemoryEz( wk );
	}

	return FALSE;
}



static void init_button_state( APPWORK* wk )
{
	int i;

	for(i=0; i<PUSH_BUTTON_MAX; i++)
	{
		wk->backup.button_enable[i] = TRUE;
		wk->backup.vpara.button[i] = BUTTON_OFF;
	}

	wk->button_update_flag = TRUE;
}

static void set_button_enable( APPWORK* wk, u32 button, BOOL flag )
{
	wk->backup.button_enable[button] = flag;
	wk->backup.vpara.button[button] =(flag)? BUTTON_OFF : BUTTON_ON;
	wk->button_update_flag = TRUE;
}

static void set_button_state( APPWORK* wk, u32 button, u32 state )
{
	if( wk->backup.button_enable[button] )
	{
		wk->backup.vpara.button[button] = state;
		wk->button_update_flag = TRUE;
	}
}


static void store_backup( APPWORK* wk, BACKUP_WORK* backup )
{
	backup->vpara.alarm_pause_anim = Poketch_A21_GetAlarmAnimState(wk->vwk);
	PoketchWork_Save( wk->appNumber, backup, sizeof(BACKUP_WORK) );
}

static void restore_backup( APPWORK* wk )
{
	if( PoketchWork_Load( wk->appNumber, &wk->backup, sizeof(BACKUP_WORK) ) )
	{
		if( wk->backup.main_seq == SEQ_COUNTDOWN )
		{
			update_counter( wk );
			if( check_counter_end(wk) )
			{
				wk->backup.main_seq = SEQ_ALARM;
				wk->backup.vpara.arrow_disp_flag = FALSE;
				wk->backup.vpara.alarm_state = ALARM_STATE_ACT;
			}
		}
	}
	else
	{
		init_backup_states( wk );
	}
}

static void init_backup_states( APPWORK* wk )
{
	wk->backup.main_seq = SEQ_INPUT;

	wk->backup.vpara.min10 = 0;
	wk->backup.vpara.min1  = 0;
	wk->backup.vpara.sec10 = 0;
	wk->backup.vpara.sec1  = 0;

	wk->backup.vpara.arrow_disp_flag = TRUE;
	wk->backup.vpara.alarm_state = ALARM_STATE_STOP;
	wk->backup.vpara.alarm_pause_anim = 0;

	init_button_state( wk );
	set_button_enable( wk, BTN_STOP, FALSE );
}

//------------------------------------------------------------------
/**
 * ワークのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber )
{
	static const TP_HIT_TBL hit_tbl[] = {
		{ START_TOUCH_TOP, START_TOUCH_BOTTOM, START_TOUCH_LEFT, START_TOUCH_RIGHT },
		{ STOP_TOUCH_TOP, STOP_TOUCH_BOTTOM, STOP_TOUCH_LEFT, STOP_TOUCH_RIGHT },
		{ RESET_TOUCH_TOP, RESET_TOUCH_BOTTOM, RESET_TOUCH_LEFT, RESET_TOUCH_RIGHT },
		{ MIN10_UP_TOP, MIN10_UP_BOTTOM, MIN10_UP_LEFT, MIN10_UP_RIGHT },
		{ MIN1_UP_TOP, MIN1_UP_BOTTOM, MIN1_UP_LEFT, MIN1_UP_RIGHT },
		{ MIN10_DOWN_TOP, MIN10_DOWN_BOTTOM, MIN10_DOWN_LEFT, MIN10_DOWN_RIGHT },
		{ MIN1_DOWN_TOP, MIN1_DOWN_BOTTOM, MIN1_DOWN_LEFT, MIN1_DOWN_RIGHT },
		{ SEC10_UP_TOP, SEC10_UP_BOTTOM, SEC10_UP_LEFT, SEC10_UP_RIGHT },
		{ SEC1_UP_TOP, SEC1_UP_BOTTOM, SEC1_UP_LEFT, SEC1_UP_RIGHT },
		{ SEC10_DOWN_TOP, SEC10_DOWN_BOTTOM, SEC10_DOWN_LEFT, SEC10_DOWN_RIGHT },
		{ SEC1_DOWN_TOP, SEC1_DOWN_BOTTOM, SEC1_DOWN_LEFT, SEC1_DOWN_RIGHT },
	};


	wk->appNumber = appNumber;
	restore_backup( wk );

	if( Poketch_A21_SetViewWork( &(wk->vwk), &(wk->backup.vpara), bgl ) )
	{
		enum {
			BUTTON_REPEAT_FRAMES = 4,
		};

		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->button = PBTN_Create(hit_tbl, NELEMS(hit_tbl), ButtonCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;
		PBTN_SetRepeatTime(wk->button, BTN_MIN10_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_MIN10_DOWN, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_MIN1_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_MIN1_DOWN, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_SEC10_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_SEC10_DOWN, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_SEC1_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_SEC1_DOWN, BUTTON_REPEAT_FRAMES);

		wk->conwk = conwk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワークのクリーンアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CleanupWork( APPWORK *wk )
{
	store_backup( wk, &wk->backup );
	PBTN_Delete( wk->button );
	Poketch_A21_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}


//------------------------------------------------------------------
/**
 * 
 *
 * @param   idx				
 * @param   event			
 * @param   touch_event		
 * @param   wk_adrs			
 *
 */
//------------------------------------------------------------------
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs )
{
	APPWORK* wk = wk_adrs;
	wk->button_id = idx;
	wk->button_event = event;

	if( idx < PUSH_BUTTON_MAX )
	{
		if( event == BMN_EVENT_TOUCH )
		{
			set_button_state( wk, idx, BUTTON_ON );
		}
		else if( event == BMN_EVENT_OUT || event == BMN_EVENT_TAP )
		{
			set_button_state( wk, idx, BUTTON_OFF );
		}
	}
}



//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A21_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqInput,
		SeqCountDown,
		SeqPause,
		SeqAlarm,
		SeqStopAlarm,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		PoketchButtonMainCall( wk->conwk, wk->button );
		if( wk->button_update_flag )
		{
			Poketch_A21_SetViewCommand(wk->vwk, CMD_UPDATE_BUTTON);
			wk->button_update_flag = FALSE;
		}

		if( seqtbl[wk->main_seq](wk) )
		{
			CleanupWork( wk );
			TCB_Delete(tcb);
			PoketchNoticeAppEnd( wk->conwk );
		}
	}
	else
	{
		SDK_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * アプリ終了関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A21_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
}

//------------------------------------------------------------------
/**
 * シーケンス変更
 *
 * @param   wk		ワークポインタ
 * @param   seq		変更後のシーケンスナンバー
 *
 */
//------------------------------------------------------------------
static void ChangeSeq(APPWORK *wk, u32 seq)
{
	u32 prev_seq = wk->main_seq;

	if(wk->quit_req_flag)
	{
		seq = SEQ_QUIT;
	}

	wk->main_seq = seq;
	if( (seq != SEQ_INIT) && (seq != SEQ_QUIT) )
	{
		wk->backup.main_seq = prev_seq;
	}

	switch( seq ){
	case SEQ_INPUT:
		wk->backup.vpara.arrow_disp_flag = TRUE;
		wk->backup.vpara.alarm_state = ALARM_STATE_STOP;
		break;

	case SEQ_COUNTDOWN:
		wk->backup.vpara.arrow_disp_flag = FALSE;
		wk->backup.vpara.alarm_state = ALARM_STATE_COUNTDOWN;
		break;

	case SEQ_PAUSE:
		wk->backup.vpara.arrow_disp_flag = FALSE;
		wk->backup.vpara.alarm_state = ALARM_STATE_COUNTDOWN;
		break;

	case SEQ_ALARM:
		wk->backup.vpara.arrow_disp_flag = FALSE;
		wk->backup.vpara.alarm_state = ALARM_STATE_ACT;
		break;

	case SEQ_STOP_ALARM:
		wk->backup.vpara.arrow_disp_flag = FALSE;
		wk->backup.vpara.alarm_state = ALARM_STATE_ACT_PAUSE;
		break;

	case SEQ_QUIT:
		wk->backup.main_seq = prev_seq;
		break;
	}

	wk->seq = 0;
}


//------------------------------------------------------------------
/**
 * シーケンス：画面構築
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A21_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A21_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, wk->backup.main_seq );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：時間入力
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqInput(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( Poketch_A21_WaitViewCommandAll(wk->vwk)==FALSE )
	{
		return FALSE;
	}
	if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id <= BTN_RESET)
	{
		wk->button_event = BMN_EVENT_NULL;

		switch( wk->button_id ){
		case BTN_RESET:
			reset_counter( wk );
			Poketch_A21_SetViewCommand(wk->vwk, CMD_UPDATE_NUM);
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);
			break;
		case BTN_START:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);
			if( start_counter( wk ) )
			{
				set_button_enable( wk, BTN_START, FALSE );
				set_button_enable( wk, BTN_STOP, TRUE );
				Poketch_A21_SetViewCommand(wk->vwk, CMD_CHANGE_COUNTDOWN);

				ChangeSeq( wk, SEQ_COUNTDOWN );
			}
			break;
		case BTN_STOP:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON_DISABLE);
			break;
		}
		return FALSE;
	}

	if( wk->button_event == BMN_EVENT_TOUCH || wk->button_event == BMN_EVENT_REPEAT )
	{
		VIEWPARAM* vpara = &(wk->backup.vpara);
		switch( wk->button_id ){
		case BTN_MIN10_UP:	if(++(vpara->min10)>9){ vpara->min10=0; } break;
		case BTN_MIN1_UP:	if(++(vpara->min1)>9){ vpara->min1=0; } break;
		case BTN_MIN10_DOWN:if(--(vpara->min10)<0){ vpara->min10=9; } break;
		case BTN_MIN1_DOWN:	if(--(vpara->min1)<0){ vpara->min1=9; } break;
		case BTN_SEC10_UP:	if(++(vpara->sec10)>5){ vpara->sec10=0; } break;
		case BTN_SEC1_UP:	if(++(vpara->sec1)>9){ vpara->sec1=0; } break;
		case BTN_SEC10_DOWN:if(--(vpara->sec10)<0){ vpara->sec10=5; } break;
		case BTN_SEC1_DOWN:	if(--(vpara->sec1)<0){ vpara->sec1=9; } break;
		}

		Poketch_A21_SetViewCommand(wk->vwk, CMD_UPDATE_NUM);
		wk->button_event = BMN_EVENT_NULL;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：カウントダウン
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqCountDown(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( update_counter(wk) )
	{
		Poketch_A21_SetViewCommand(wk->vwk, CMD_UPDATE_NUM);
		if( check_counter_end(wk) )
		{
			set_button_enable(wk, BTN_START, FALSE);
			Poketch_A21_SetViewCommand( wk->vwk, CMD_START_ALARM );

			ChangeSeq( wk, SEQ_ALARM );
			return FALSE;
		}
	}

	if( wk->button_event == BMN_EVENT_TOUCH )
	{
		wk->button_event = BMN_EVENT_NULL;

		switch( wk->button_id ){
		case BTN_START:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON_DISABLE);
			break;

		case BTN_STOP:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_STOP, FALSE );
			set_button_enable( wk, BTN_START, TRUE );
			pause_counter( wk );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );

			ChangeSeq( wk, SEQ_PAUSE );
			break;

		case BTN_RESET:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, TRUE );
			set_button_enable( wk, BTN_STOP, FALSE );
			reset_counter( wk );

			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_NUM );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_CHANGE_INPUT );

			ChangeSeq( wk, SEQ_INPUT );
			break;
		}
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：一時停止
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqPause(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( wk->button_event == BMN_EVENT_TOUCH )
	{
		wk->button_event = BMN_EVENT_NULL;

		switch( wk->button_id ){
		case BTN_START:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_STOP, TRUE );
			set_button_enable( wk, BTN_START, FALSE );
			restart_counter( wk );

			ChangeSeq( wk, SEQ_COUNTDOWN );
			break;

		case BTN_STOP:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON_DISABLE);
			break;

		case BTN_RESET:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, TRUE );
			set_button_enable( wk, BTN_STOP, FALSE );
			reset_counter( wk );

			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_NUM );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_CHANGE_INPUT );

			ChangeSeq( wk, SEQ_INPUT );
			break;
		}
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：アラーム鳴り
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqAlarm(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( wk->button_event == BMN_EVENT_TOUCH )
	{
		wk->button_event = BMN_EVENT_NULL;
		switch(wk->button_id){
		case BTN_START:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON_DISABLE);
			break;
		case BTN_STOP:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, TRUE );
			set_button_enable( wk, BTN_STOP,  FALSE );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_STOP_ALARM );

			ChangeSeq( wk, SEQ_STOP_ALARM );
			wk->seq++;
			break;
		case BTN_RESET:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, TRUE );
			set_button_enable( wk, BTN_STOP, FALSE );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_STOP_ALARM );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_CHANGE_INPUT );

			ChangeSeq( wk, SEQ_INPUT );
			break;
		}
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：アラーム一時停止
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqStopAlarm(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	if( wk->button_event == BMN_EVENT_TOUCH )
	{
		wk->button_event = BMN_EVENT_NULL;
		switch(wk->button_id){
		case BTN_START:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, FALSE );
			set_button_enable( wk, BTN_STOP,  TRUE );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_START_ALARM );

			ChangeSeq( wk, SEQ_ALARM );
			break;
		case BTN_STOP:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON_DISABLE);
			break;
		case BTN_RESET:
			PoketchSePlay(POKETCH_SE_KITCHEN_BUTTON);

			set_button_enable( wk, BTN_START, TRUE );
			set_button_enable( wk, BTN_STOP, FALSE );
			reset_counter( wk );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_STOP_ALARM );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_UPDATE_NUM );
			Poketch_A21_SetViewCommand( wk->vwk, CMD_CHANGE_INPUT );

			ChangeSeq( wk, SEQ_INPUT );
			break;
		}
	}

	return FALSE;
}


//------------------------------------------------------------------
/**
 * シーケンス：終了処理
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqQuit(APPWORK *wk)
{
	switch(wk->seq){
	case 0:
		Poketch_A21_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A21_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}








static u64 start_counter( APPWORK* wk )
{
	VIEWPARAM* vpara = &(wk->backup.vpara);
	wk->backup.start_tick = APTM_GetData();
	wk->backup.stop_tick = 0;
	wk->backup.counter_working_flag = TRUE;
	wk->backup.prev_sec = 0;
	wk->backup.count_sec = (vpara->min10*10 + vpara->min1) * 60
							+ (vpara->sec10*10 + vpara->sec1);

	set_counter_value( wk, wk->backup.count_sec );

	OS_TPrintf("count sec = %ld\n", wk->backup.count_sec);

	return wk->backup.count_sec;
}

static void pause_counter( APPWORK* wk )
{
	wk->backup.counter_working_flag = FALSE;
	wk->backup.stop_tick = APTM_GetData();
}

static void restart_counter( APPWORK* wk )
{
	wk->backup.start_tick += (APTM_GetData() - wk->backup.stop_tick);
	wk->backup.counter_working_flag = TRUE;
}

static BOOL check_counter_end( APPWORK* wk )
{
	return (wk->backup.counter_working_flag == FALSE);
}

static BOOL update_counter( APPWORK* wk )
{
	if( wk->backup.counter_working_flag )
	{
		u64  sec = APTM_CalcSec( APTM_GetData() - wk->backup.start_tick );

		if( sec >= wk->backup.count_sec )
		{
			reset_counter( wk );
			return TRUE;
		}
		else if( sec != wk->backup.prev_sec )
		{
			set_counter_value( wk, (wk->backup.count_sec - sec) );
			wk->backup.prev_sec = sec;
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

static void reset_counter( APPWORK* wk )
{
	wk->backup.counter_working_flag = FALSE;
	wk->backup.vpara.min10 = 0;
	wk->backup.vpara.min1 = 0;
	wk->backup.vpara.sec10 = 0;
	wk->backup.vpara.sec1 = 0;
}

static void set_counter_value( APPWORK* wk, u64 total_sec )
{
	u32 min, sec;

	CP_SetDiv64_32( total_sec, 60 );

	min = CP_GetDivResult64();
	sec = CP_GetDivRemainder64();

	CP_SetDiv32_32( min, 10 );
	wk->backup.vpara.min10 = CP_GetDivResult32();
	wk->backup.vpara.min1 = CP_GetDivRemainder32();

	CP_SetDiv32_32( sec, 10 );
	wk->backup.vpara.sec10 = CP_GetDivResult32();
	wk->backup.vpara.sec1 = CP_GetDivRemainder32();

}
