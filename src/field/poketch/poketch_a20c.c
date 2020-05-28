//============================================================================================
/**
 * @file	poketch_a20c.c
 * @bfief	ポケッチ（アプリNoa20：アラーム時計）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "system\pm_rtc.h"

#include "poketch_a20.h"
#include "poketch_prv.h"
#include "poketch_button.h"
#include "poketch_sound.h"

//==============================================================
// button
//==============================================================
enum {
	BTN_ON,
	BTN_OFF,
	BTN_HOUR_UP,
	BTN_HOUR_DOWN,
	BTN_MIN_UP,
	BTN_MIN_DOWN,
};

enum {
	BUTTON_REPEAT_FRAMES = 4,
};
//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;

	u8        quit_req_flag;

	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;
	POKETCH_DATA*  savedata;

	POKETCH_BUTTON_MAN*  button;
	u32                  button_id;
	u32                  button_event;


	RTCTime         rtc_time;
	BOOL            rtc_req_flag;
	BOOL            rtc_success_flag;

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_SWITCH_OFF,
	SEQ_SWITCH_ON,
	SEQ_ALARM,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A20_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void set_now_time( VIEWPARAM* vpara );
static void CleanupWork( APPWORK *wk );
static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void Poketch_A20_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A20_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqSwitchOff(APPWORK *wk);
static BOOL SeqSwitchOn(APPWORK *wk);
static BOOL SeqAlarm(APPWORK* wk );
static BOOL check_rtc_waiting( APPWORK* wk );
static void rtc_req( APPWORK* wk );
static BOOL rtc_get_latest_time( APPWORK* wk, u32* hour, u32* minute );
static BOOL SeqQuit(APPWORK *wk);
static BOOL check_alarm_time( VIEWPARAM* vpara );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A20_Init, Poketch_A20_Quit);
}

//------------------------------------------------------------------
/**
 * アプリ初期化関数
 *
 * @param   wk_ptr		ワークアドレスを保存するポインタのアドレス
 * @param   conwk		アプリが本体から情報を取得する際に必要となるワーク（アプリへは非公開）
 * @param   bgl			BGLモジュールヘッダ
 * @param   param		カラー・モノクロなど動作タイプ（アプリ依存）
 */
//------------------------------------------------------------------
static BOOL Poketch_A20_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A20_Main, wk, POKETCH_APP_TASKPRI) != NULL )
			{
				*wk_ptr = wk;
				return TRUE;
			}
		}
		sys_FreeMemoryEz( wk );
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワークのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param )
{
	static const TP_HIT_TBL hit_tbl[] = {
		{  72, 104, 176, 208, },	// ON
		{ 104, 136, 176, 208, },	// OFF
		{ 112, 128,  64,  80, },	// HOUR UP
		{ 160, 176,  64,  80, },	// HOUR DOWN
		{ 112, 128, 112, 128, },	// MIN UP
		{ 160, 176, 112, 128, },	// MIN DOWN

	};

	u32       hour, minute;

	wk->savedata = PoketchGetSaveData(conwk);

	wk->vpara.switch_on = PoketchData_GetAlarmSwitchFlag(wk->savedata);
	PoketchData_GetAlarmTime(wk->savedata, &hour, &minute);
	wk->vpara.hour_set = hour;
	wk->vpara.min_set = minute;

	set_now_time( &wk->vpara );

	if( Poketch_A20_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->button =  PBTN_Create( hit_tbl, NELEMS(hit_tbl), ButtonCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

		PBTN_SetRepeatTime(wk->button, BTN_HOUR_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_HOUR_DOWN, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_MIN_UP, BUTTON_REPEAT_FRAMES);
		PBTN_SetRepeatTime(wk->button, BTN_MIN_DOWN, BUTTON_REPEAT_FRAMES);


		wk->rtc_req_flag = FALSE;
		wk->rtc_success_flag = FALSE;
		wk->conwk = conwk;
		return TRUE;
	}

	return FALSE;
}

static void set_now_time( VIEWPARAM* vpara )
{
	RTCTime   time;


	// 時間取得。ヘンな値が入ってきた時のために丸めておく
	GF_RTC_GetTime( &time );
	if( time.hour >= 24 ){
		time.hour %= 24;
	}
	if( time.minute >= 60 ){
		time.hour %= 60;
	}

	vpara->hour_now = time.hour;
	vpara->min_now = time.minute;
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
	PBTN_Delete( wk->button );
	Poketch_A20_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}




static void ButtonCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs )
{
	APPWORK* wk = wk_adrs;
	wk->button_id = idx;
	wk->button_event = event;
}


//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A20_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqSwitchOff,
		SeqSwitchOn,
		SeqAlarm,
		SeqQuit,
	};

	APPWORK *wk = (APPWORK*)wk_adrs;

	if( wk->main_seq < NELEMS(seqtbl) )
	{
		PoketchButtonMainCall( wk->conwk, wk->button );

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
static void Poketch_A20_Quit(void *wk_adrs)
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
	if(wk->quit_req_flag == FALSE)
	{
		wk->main_seq = seq;
	}
	else
	{
		wk->main_seq = SEQ_QUIT;
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
		Poketch_A20_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A20_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			if( wk->vpara.switch_on )
			{
				ChangeSeq( wk, SEQ_SWITCH_ON );
			}
			else
			{
				ChangeSeq( wk, SEQ_SWITCH_OFF );
			}
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：スイッチオフ時
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqSwitchOff(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id == BTN_ON )
		{
			wk->vpara.switch_on = TRUE;
			set_now_time(&wk->vpara);
			PoketchData_SetAlarm( wk->savedata, TRUE, wk->vpara.hour_set, wk->vpara.min_set );
			Poketch_A20_SetViewCommand( wk->vwk, CMD_CHANGE_ON );
			wk->button_event = BMN_EVENT_NULL;
			wk->seq++;
			break;
		}
		if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id == BTN_OFF )
		{
			wk->button_event = BMN_EVENT_NULL;
			PoketchSePlay( POKETCH_SE_ALARM_BUTTON_DISABLE );
			break;
		}
		if( wk->button_event == BMN_EVENT_TOUCH || wk->button_event == BMN_EVENT_REPEAT )
		{
			switch( wk->button_id ){
			case BTN_HOUR_UP:
				if( ++(wk->vpara.hour_set) > 23 ){ wk->vpara.hour_set = 0; } break;

			case BTN_HOUR_DOWN:
				if( --(wk->vpara.hour_set) < 0 ){ wk->vpara.hour_set = 23; } break;

			case BTN_MIN_UP:
				if( ++(wk->vpara.min_set) > 59 ){ wk->vpara.min_set = 0; } break;

			case BTN_MIN_DOWN:
				if( --(wk->vpara.min_set) < 0 ){ wk->vpara.min_set = 59; } break;
			}

			wk->button_event = BMN_EVENT_NULL;
			Poketch_A20_SetViewCommand( wk->vwk, CMD_UPDATE_TIME );
			break;
		}
		
		break;

	case 1:
		if( Poketch_A20_WaitViewCommand( wk->vwk, CMD_CHANGE_ON ) )
		{
			ChangeSeq( wk, SEQ_SWITCH_ON );
		}
		break;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：スイッチオン時
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqSwitchOn(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}


	switch( wk->seq ){
	case 0:
		if( check_alarm_time( &(wk->vpara) ) )
		{
			ChangeSeq( wk, SEQ_ALARM );
			return FALSE;
		}

		if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id == BTN_OFF )
		{
			wk->vpara.switch_on = FALSE;
			Poketch_A20_SetViewCommand( wk->vwk, CMD_CHANGE_OFF );
			wk->button_event = BMN_EVENT_NULL;
			ChangeSeq( wk, SEQ_SWITCH_OFF );
			break;
		}
		if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id == BTN_ON )
		{
			PoketchSePlay( POKETCH_SE_ALARM_BUTTON_DISABLE );
			break;
		}

		if( check_rtc_waiting(wk) == FALSE )
		{
			rtc_req( wk );
		}

		{
			u32 hour, min;

			if( rtc_get_latest_time( wk, &hour, &min ) )
			{
				if( min != wk->vpara.min_now )
				{
					wk->vpara.min_now = min;
					wk->vpara.hour_now = hour;
					Poketch_A20_SetViewCommand( wk->vwk, CMD_UPDATE_TIME );
					wk->seq++;
					break;
				}
			}
		}
		break;


		break;


	case 1:
		if( Poketch_A20_WaitViewCommand( wk->vwk, CMD_UPDATE_TIME ) )
		{
			wk->seq = 0;
		}
		break;

	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * シーケンス：アラーム稼働時
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqAlarm(APPWORK* wk )
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		Poketch_A20_SetViewCommand( wk->vwk, CMD_ALARM );
		wk->seq++;
		break;

	case 1:
		if( check_alarm_time( &(wk->vpara) ) == FALSE )
		{
			Poketch_A20_ForceStopAlarm( wk->vwk );
			Poketch_A20_SetViewCommand( wk->vwk, CMD_CHANGE_ON );
			ChangeSeq( wk, SEQ_SWITCH_ON );
			return FALSE;
		}

		if( wk->button_event == BMN_EVENT_TOUCH && wk->button_id == BTN_OFF )
		{
			wk->vpara.switch_on = FALSE;
			Poketch_A20_ForceStopAlarm( wk->vwk );
			Poketch_A20_SetViewCommand( wk->vwk, CMD_CHANGE_OFF );
			wk->button_event = BMN_EVENT_NULL;
			ChangeSeq( wk, SEQ_SWITCH_OFF );
			return FALSE;
		}

		if( check_rtc_waiting(wk) == FALSE )
		{
			rtc_req( wk );
		}

		{
			u32 hour, min;

			if( rtc_get_latest_time( wk, &hour, &min ) )
			{
				if( min != wk->vpara.min_now )
				{
					wk->vpara.min_now = min;
					wk->vpara.hour_now = hour;
					Poketch_A20_SetViewCommand( wk->vwk, CMD_UPDATE_TIME );
				}
			}
		}
		break;
	}

	return FALSE;
}


static BOOL check_rtc_waiting( APPWORK* wk )
{
	return wk->rtc_req_flag;
}

static void rtc_req( APPWORK* wk )
{
	if( wk->rtc_req_flag == FALSE )
	{
		GF_RTC_GetTime( &(wk->rtc_time) );
		wk->rtc_success_flag = TRUE;
	}
}

static BOOL rtc_get_latest_time( APPWORK* wk, u32* hour, u32* minute )
{
	if( wk->rtc_success_flag )
	{
		*hour = wk->rtc_time.hour;
		*minute = wk->rtc_time.minute;
		return TRUE;
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
		Poketch_A20_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A20_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}


static BOOL check_alarm_time( VIEWPARAM* vpara )
{
	return (vpara->hour_now == vpara->hour_set && vpara->min_now == vpara->min_set);
}

