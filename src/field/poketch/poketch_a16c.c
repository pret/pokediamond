//============================================================================================
/**
 * @file	poketch_a16c.c
 * @bfief	ポケッチ（アプリNoa16：ルーレット）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"

#include "poketch_sound.h"
#include "poketch_button.h"
#include "poketch_a16.h"
#include "poketch_prv.h"

//==============================================================
// 定数
//==============================================================
enum {
	AREA_START_X = 16,
	AREA_START_Y = 16,
	AREA_END_X = 171,
	AREA_END_Y = 165,
};


//==============================================================
// Work
//==============================================================
typedef struct {
	u8        main_seq;
	u8        seq;

	u8        quit_req_flag;
	u8        prevFrameWriteFlag;


	VIEWPARAM  vpara;
	VIEWWORK*  vwk;
	CONTACT_WORK*  conwk;

	POKETCH_BUTTON_MAN*	button;
	u32                 button_event;
	u32                 button_id;

}APPWORK;


//==============================================================
// ボタン配置
//==============================================================

enum BUTTON_ID {
	BUTTON_START,
	BUTTON_STOP,
	BUTTON_CLEAR,
};


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
static BOOL Poketch_A16_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A16_Main(TCB_PTR tcb, void *wk_adrs);
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs );
static void Poketch_A16_Quit(void *wk_adrs);
static void ChangeSeq(APPWORK *wk, u32 seq);
static BOOL SeqInit(APPWORK *wk);
static BOOL SeqIdle(APPWORK *wk);
static BOOL CheckOverWrite( APPWORK* wk );
static BOOL CheckWriteCont( APPWORK* wk );
static void InterpolateCommandSet( APPWORK* wk, u32 sx, u32 sy, u32 ex, u32 ey );
static BOOL SeqQuit(APPWORK *wk);
static void clear_pixel_data( VIEWPARAM* vpara );



//------------------------------------------------------------------
/**
 * アプリの制御関数アドレスをメインコントロールに渡す
 */
//------------------------------------------------------------------
static void NitroStaticInit(void)
{
	PoketchSetAppProc(Poketch_A16_Init, Poketch_A16_Quit);
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
static BOOL Poketch_A16_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, appNumber ))
		{
			if( TCB_Add(Poketch_A16_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 appNumber )
{
	static const TP_HIT_TBL hit_tbl[] = {
		{ BUTTON_START_TOP, BUTTON_START_BOTTOM, BUTTON_START_LEFT, BUTTON_START_RIGHT },
		{ BUTTON_STOP_TOP, BUTTON_STOP_BOTTOM, BUTTON_STOP_LEFT, BUTTON_STOP_RIGHT },
		{ BUTTON_CLEAR_TOP, BUTTON_CLEAR_BOTTOM, BUTTON_CLEAR_LEFT, BUTTON_CLEAR_RIGHT },
	};

	wk->vpara.appNumber = appNumber;
	wk->vpara.start_button = FALSE;
	wk->vpara.stop_button = TRUE;
	wk->vpara.clear_button = FALSE;

	if( Poketch_A16_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->prevFrameWriteFlag = FALSE;

		clear_pixel_data( &wk->vpara );


		wk->button = PBTN_Create( hit_tbl, NELEMS(hit_tbl), BmnCallback, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

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
	PBTN_Delete( wk->button );
	Poketch_A16_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}
//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A16_Main(TCB_PTR tcb, void *wk_adrs)
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
 * ボタンマネージャコールバック関数
 *
 * @param   btn_idx		
 * @param   event		
 * @param   touch_event		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void BmnCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs )
{
	APPWORK* wk = (APPWORK*)wk_adrs;

	wk->button_event = event;
	wk->button_id = btn_idx;
}
//------------------------------------------------------------------
/**
 * アプリ終了関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A16_Quit(void *wk_adrs)
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
		Poketch_A16_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A16_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * シーケンス：メイン処理
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEでアプリ終了
 */
//------------------------------------------------------------------
static BOOL SeqIdle(APPWORK *wk)
{
	enum {
		SEQ_WAIT_DEFAULT,
		SEQ_WAIT_ARROW,
		SEQ_WAIT_ARROW_STOP,
		SEQ_WAIT_CLEAR_BUTTON,
	};

	if(wk->quit_req_flag)
	{
		ChangeSeq( wk, SEQ_QUIT );
	}

	switch( wk->seq ){
	case 0:
		if( PoketchIsSleepMode( wk->conwk ) )
		{
			break;
		}
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			switch( wk->button_id ){
			case BUTTON_START:
				wk->vpara.start_button = TRUE;
				wk->vpara.stop_button = FALSE;
				wk->vpara.clear_button = TRUE;
				Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
				Poketch_A16_SetViewCommand( wk->vwk, CMD_START_ARROW );
				PoketchSePlay(POKETCH_SE_ROULETTE_BUTTON);
				wk->seq = SEQ_WAIT_ARROW;
				break;

			case BUTTON_STOP:
				PoketchSePlay(POKETCH_SE_ROULETTE_BUTTON_DISABLE);
				break;

			case BUTTON_CLEAR:
				wk->vpara.clear_button = TRUE;
				Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
				PoketchSePlay(POKETCH_SE_ROULETTE_BUTTON);
				wk->seq = SEQ_WAIT_CLEAR_BUTTON;
				break;
			}
			wk->button_event = BMN_EVENT_NULL;
			break;
		}

		if( wk->prevFrameWriteFlag )
		{
			u32  prev_x, prev_y;

			prev_x = wk->vpara.pixel_update_x;
			prev_y = wk->vpara.pixel_update_y;
			if( CheckWriteCont( wk ) )
			{
				InterpolateCommandSet( wk, prev_x, prev_y, wk->vpara.pixel_update_x, wk->vpara.pixel_update_y );
			}
			else
			{
				wk->prevFrameWriteFlag = FALSE;
			}
		}
		else
		{
			if( CheckOverWrite( wk ) )
			{
				Poketch_A16_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				wk->prevFrameWriteFlag = TRUE;
			}
		}
		break;


	case SEQ_WAIT_ARROW:
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			switch( wk->button_id ){
			case BUTTON_CLEAR:
			case BUTTON_START:
				PoketchSePlay(POKETCH_SE_ROULETTE_BUTTON_DISABLE);
				break;

			case BUTTON_STOP:
				wk->vpara.start_button = TRUE;
				wk->vpara.stop_button = TRUE;
				wk->vpara.clear_button = TRUE;
				Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
				Poketch_A16_SetViewCommand( wk->vwk, CMD_STOP_ARROW );
				PoketchSePlay(POKETCH_SE_ROULETTE_BUTTON);
				wk->seq = SEQ_WAIT_ARROW_STOP;
				break;
			}
			wk->button_event = BMN_EVENT_NULL;
			break;
		}
		break;

	case SEQ_WAIT_ARROW_STOP:
		if( Poketch_A16_WaitViewCommand( wk->vwk, CMD_STOP_ARROW ) )
		{
			wk->vpara.start_button = FALSE;
			wk->vpara.stop_button = TRUE;
			wk->vpara.clear_button = FALSE;
			Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			wk->seq = SEQ_WAIT_DEFAULT;
		}
		break;

	case SEQ_WAIT_CLEAR_BUTTON:
		if( wk->button_event == BMN_EVENT_OUT )
		{
			wk->vpara.clear_button = FALSE;
			Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			wk->seq = SEQ_WAIT_DEFAULT;
			break;
		}
		if( wk->button_event == BMN_EVENT_TAP )
		{
			wk->vpara.clear_button = FALSE;
			clear_pixel_data( &wk->vpara );
			Poketch_A16_SetViewCommand( wk->vwk, CMD_UPDATE_BUTTON );
			Poketch_A16_SetViewCommand( wk->vwk, CMD_CLEAR_PIXELS );
			wk->seq = SEQ_WAIT_DEFAULT;
			break;
		}
		break;

	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * 現在のピクセルと異なる状態に上書きされようとしているかチェック
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL CheckOverWrite( APPWORK* wk )
{
	u32 x, y;

	// タッチパネルに触れてる
	if( PoketchGetTPCont( &x, &y ) )
	{
		// 描画有効範囲である
		if( ((u32)( x - AREA_START_X) < (u32)(AREA_END_X - AREA_START_X))
		&	((u32)( y - AREA_START_Y) < (u32)(AREA_END_Y - AREA_START_Y))
		){
			// DSのドット単位からポケッチピクセル単位へ
			x = (x - AREA_START_X) >> 1;
			y = (y - AREA_START_Y) >> 1;
			// 現在のピクセルと違う状態が書き込まれようとしているなら描画パラメータセット
			if( wk->vpara.pixel[x][y] == 0 )
			{
				wk->vpara.pixel[x][y] = 1;
				wk->vpara.pixel_update_x = x;
				wk->vpara.pixel_update_y = y;
				return TRUE;
			}
		}
	}
	return FALSE;
}

static BOOL CheckWriteCont( APPWORK* wk )
{
	u32 x, y;
	// タッチパネルに触れてる
	if( PoketchGetTPCont( &x, &y ) )
	{
		// 描画有効範囲である
		if( ((u32)( x - AREA_START_X) < (u32)(AREA_END_X - AREA_START_X))
		&	((u32)( y - AREA_START_Y) < (u32)(AREA_END_Y - AREA_START_Y))
		){
			x = (x - AREA_START_X) >> 1;
			y = (y - AREA_START_Y) >> 1;
			wk->vpara.pixel_update_x = x;
			wk->vpara.pixel_update_y = y;
			return TRUE;
		}
	}
	return FALSE;
}

static void InterpolateCommandSet( APPWORK* wk, u32 sx, u32 sy, u32 ex, u32 ey )
{
	extern void Poketch_A16_SetViewCommandVintr(VIEWWORK* wk, u32 cmd);

	u32   diffX, diffY, add, intVal;
	fx32  fxval, fxadd;

	if( (sy == ey) && (sx == ex ) ){
		return;
	}

	diffX = (ex > sx)? (ex - sx) : (sx - ex);
	diffY = (ey > sy)? (ey - sy) : (sy - ey);

	if( diffX > diffY )
	{
		add = (ex > sx)? 1 : -1;
		if( diffX ){
			fxadd = ((ey-sy) * FX32_ONE);
			fxadd /= (s32)(diffX);
		}else{
			fxadd = 0;
		}

		fxval = (sy << FX32_SHIFT) + fxadd;
		sx += add;

		while( sx != ex )
		{
			intVal = fxval >> FX32_SHIFT;

			if( sx < PIXEL_H_MAX && intVal < PIXEL_V_MAX )
			{
				if(wk->vpara.pixel[sx][intVal] == 0)
				{
					wk->vpara.pixel[sx][intVal] = 0;
					wk->vpara.pixel_update_x = sx;
					wk->vpara.pixel_update_y = intVal;
					Poketch_A16_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				}
			}
			sx += add;
			fxval += fxadd;
		}
	}
	else
	{
		add = (ey > sy)? 1 : -1;
		if( diffY ){
			fxadd = (ex-sx) * FX32_ONE;
			fxadd /= (s32)diffY;
		}else{
			fxadd = 0;
		}
		fxval = (sx << FX32_SHIFT) + fxadd;
		sy += add;

		while( sy != ey )
		{
			intVal = fxval >> FX32_SHIFT;
			if( sy < PIXEL_V_MAX && intVal < PIXEL_H_MAX )
			{
				if(wk->vpara.pixel[intVal][sy] == 0 )
				{
					wk->vpara.pixel[intVal][sy] = 1;
					wk->vpara.pixel_update_x = intVal;
					wk->vpara.pixel_update_y = sy;
					Poketch_A16_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
				}
			}
			sy += add;
			fxval += fxadd;
		}
	}

	if( ey < PIXEL_V_MAX && ex < PIXEL_H_MAX )
	{
		wk->vpara.pixel_update_x = ex;
		wk->vpara.pixel_update_y = ey;
		Poketch_A16_SetViewCommand( wk->vwk, CMD_PIXEL_SET );
	}
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
		Poketch_A16_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A16_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}






static void clear_pixel_data( VIEWPARAM* vpara )
{
	int x, y;
	for(x = 0; x < PIXEL_H_MAX; x++){
		for(y = 0; y < PIXEL_V_MAX; y++){
			vpara->pixel[x][y] = 0;
		}
	}
}
