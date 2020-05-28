//============================================================================================
/**
 * @file	poketch_a25c.c
 * @bfief	ポケッチ（アプリNoa25：カレンダー）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "system\pm_rtc.h"

#include "poketch_a25.h"
#include "poketch_prv.h"
#include "poketch_button.h"

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

	POKETCH_DATA*        poketchData;

	POKETCH_BUTTON_MAN*  button;
	u32                  button_event;
	u32                  button_id;

	u32                  first_pos;
	u32                  last_pos;

}APPWORK;

//==============================================================
// シーケンス
//==============================================================
enum {
	SEQ_INIT,
	SEQ_IDLE,
	SEQ_QUIT,
};

//==============================================================
// Prototype
//==============================================================
static void NitroStaticInit(void);
static BOOL Poketch_A25_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void setup_vparam( VIEWPARAM* vpara, APPWORK* wk, const RTCDate* date );
static void CleanupWork( APPWORK *wk );
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
static void Poketch_A25_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A25_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL SeqQuit(APPWORK *wk);



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A25_Init, Poketch_A25_Quit);
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
static BOOL Poketch_A25_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A25_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(2), TOUCH_RIGHT(2) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(3), TOUCH_RIGHT(3) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(4), TOUCH_RIGHT(4) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(5), TOUCH_RIGHT(5) },
		{ TOUCH_TOP(0), TOUCH_BOTTOM(0), TOUCH_LEFT(6), TOUCH_RIGHT(6) },

		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(2), TOUCH_RIGHT(2) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(3), TOUCH_RIGHT(3) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(4), TOUCH_RIGHT(4) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(5), TOUCH_RIGHT(5) },
		{ TOUCH_TOP(1), TOUCH_BOTTOM(1), TOUCH_LEFT(6), TOUCH_RIGHT(6) },

		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(2), TOUCH_RIGHT(2) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(3), TOUCH_RIGHT(3) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(4), TOUCH_RIGHT(4) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(5), TOUCH_RIGHT(5) },
		{ TOUCH_TOP(2), TOUCH_BOTTOM(2), TOUCH_LEFT(6), TOUCH_RIGHT(6) },

		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(2), TOUCH_RIGHT(2) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(3), TOUCH_RIGHT(3) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(4), TOUCH_RIGHT(4) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(5), TOUCH_RIGHT(5) },
		{ TOUCH_TOP(3), TOUCH_BOTTOM(3), TOUCH_LEFT(6), TOUCH_RIGHT(6) },

		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(2), TOUCH_RIGHT(2) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(3), TOUCH_RIGHT(3) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(4), TOUCH_RIGHT(4) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(5), TOUCH_RIGHT(5) },
		{ TOUCH_TOP(4), TOUCH_BOTTOM(4), TOUCH_LEFT(6), TOUCH_RIGHT(6) },

		{ TOUCH_TOP(5), TOUCH_BOTTOM(5), TOUCH_LEFT(0), TOUCH_RIGHT(0) },
		{ TOUCH_TOP(5), TOUCH_BOTTOM(5), TOUCH_LEFT(1), TOUCH_RIGHT(1) },
	};

	RTCDate  date;
	GF_RTC_GetDate(&date);

	wk->poketchData = PoketchGetSaveData(conwk);

	setup_vparam( &(wk->vpara), wk, &date );
	wk->first_pos = wk->vpara.day_param[0].pos;
	wk->last_pos = wk->first_pos + (wk->vpara.last_day - 1);

	if( Poketch_A25_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->button =  PBTN_Create( hit_tbl, NELEMS(hit_tbl), BmnCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

		wk->conwk = conwk;
		return TRUE;
	}

	return FALSE;
}

static void setup_vparam( VIEWPARAM* vpara, APPWORK* wk, const RTCDate* date )
{
	static const u8 maxday[12] = {
		31,28,31,30,31,30,31,31,30,31,30,31,
	};

	u32 i, week;

	vpara->month = date->month;
	vpara->today = date->day;
	vpara->last_day = maxday[vpara->month-1];
	if( vpara->month == 2 )
	{
		if( ((date->year%400)==0)
		||	((date->year%100)!=0) && ((date->year%4)==0)
		){
			vpara->last_day = 29;
		}
	}

	week = date->week + (7-((date->day-1)%7));
	if(week >= RTC_WEEK_MAX)
	{
		week %= RTC_WEEK_MAX;
	}

	for(i=0; i<(vpara->last_day); i++)
	{
		vpara->day_param[i].day = i+1;
		vpara->day_param[i].mark = PoketchData_Calendar_GetMark( wk->poketchData, vpara->month, i+1 );
		vpara->day_param[i].pos = week + i;
	}
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
	Poketch_A25_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
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
	APPWORK *wk = (APPWORK*)wk_adrs;

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
static void Poketch_A25_Main(TCB_PTR tcb, void *wk_adrs)
{
	static BOOL (* const seqtbl[])(APPWORK*) = {
		SeqInit,
		SeqIdle,
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
static void Poketch_A25_Quit(void *wk_adrs)
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
		Poketch_A25_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A25_WaitViewCommand( wk->vwk, CMD_INIT ))
		{
			PoketchNoticeAppStart( wk->conwk );
			ChangeSeq( wk, SEQ_IDLE );
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * シーケンス：入力待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
		return FALSE;
	}

	switch( wk->seq ){
	case 0:
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			wk->button_event = BMN_EVENT_NULL;

			if(	(wk->button_id >= wk->first_pos)
			&&	(wk->button_id <= wk->last_pos )
			){
				int day = (wk->button_id - wk->first_pos);
				if( PoketchData_Calendar_GetMark(wk->poketchData, wk->vpara.month, day+1) )
				{
					PoketchData_Calendar_ClearMark( wk->poketchData, wk->vpara.month, day+1 );
				}
				else
				{
					PoketchData_Calendar_SetMark( wk->poketchData, wk->vpara.month, day+1 );
				}
				wk->vpara.day_param[day].mark ^= 1;
				wk->vpara.update_day = day;
				Poketch_A25_SetViewCommand( wk->vwk, CMD_UPDATE );
				wk->seq++;
			}
		}
		break;

	case 1:
		if( Poketch_A25_WaitViewCommand( wk->vwk, CMD_UPDATE ) )
		{
			wk->seq = 0;
		}
		break;
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
		Poketch_A25_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A25_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
