//============================================================================================
/**
 * @file	poketch_a13c.c
 * @bfief	ポケッチ（アプリNoa13：トレーナーランチャー）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"


#include "system\snd_play.h"
#include "poketch_sound.h"

#include "poketch_button.h"
#include "poketch_a13.h"
#include "poketch_prv.h"


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

	POKETCH_BUTTON_MAN*  button;
	u32                  button_event;
	u32                  button_id;

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
static BOOL Poketch_A13_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void ButtonCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs );
static void Poketch_A13_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A13_Quit(void *wk_adrs);
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
	PoketchSetAppProc(Poketch_A13_Init, Poketch_A13_Quit);
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
static BOOL Poketch_A13_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A13_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
	if( Poketch_A13_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		static const TP_HIT_TBL hit_tbl[] = {
			{ BUTTON0_TOP, BUTTON0_BOTTOM, BUTTON0_LEFT, BUTTON0_RIGHT },
			{ BUTTON1_TOP, BUTTON1_BOTTOM, BUTTON1_LEFT, BUTTON1_RIGHT },
			{ BUTTON2_TOP, BUTTON2_BOTTOM, BUTTON2_LEFT, BUTTON2_RIGHT },
			{ BUTTON3_TOP, BUTTON3_BOTTOM, BUTTON3_LEFT, BUTTON3_RIGHT },
			{ BUTTON4_TOP, BUTTON4_BOTTOM, BUTTON4_LEFT, BUTTON4_RIGHT },
			{ BUTTON5_TOP, BUTTON5_BOTTOM, BUTTON5_LEFT, BUTTON5_RIGHT },
		};

		int i;

		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;
		wk->conwk = conwk;

		wk->button = PBTN_Create(hit_tbl, NELEMS(hit_tbl), ButtonCallback, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;

		// 現状は全てオンにしているが、いずれはフィールドと共通処理を通じて
		// オン・オフ判定を行う
		for(i=0; i<BUTTON_MAX; i++)
		{
			wk->vpara.button_enable_flag[i] = TRUE;
		}


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
	if( wk->button )
	{
		PBTN_Delete( wk->button );
	}
	Poketch_A13_DeleteViewWork( wk->vwk );
	sys_FreeMemoryEz( wk );
}

static void ButtonCallback( u32 btn_idx, u32 event, u32 touch_event, void *wk_adrs )
{
	APPWORK* wk = wk_adrs;
	wk->button_event = event;
	wk->button_id = btn_idx;
}

//------------------------------------------------------------------
/**
 * アプリメイン関数
 *
 * @param   wk_adrs		ワークアドレス
 *
 */
//------------------------------------------------------------------
static void Poketch_A13_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A13_Quit(void *wk_adrs)
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
		Poketch_A13_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A13_WaitViewCommand( wk->vwk, CMD_INIT ))
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
 * シーケンス：なんもしない
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
			if( wk->vpara.button_enable_flag[ wk->button_id ] )
			{
				wk->vpara.button_id = wk->button_id;
				Poketch_A13_SetViewCommand( wk->vwk, CMD_BUTTON_PUSH );
				PoketchSePlay(POKETCH_SE_TRANER_BUTTON);
				wk->seq++;
			}
			else
			{
				PoketchSePlay(POKETCH_SE_TRANER_BUTTON_DISABLE);
			}
		}
		break;

	case 1:
		if( wk->button_event == BMN_EVENT_OUT )
		{
			Poketch_A13_SetViewCommand( wk->vwk, CMD_BUTTON_RELEASE );
			wk->seq = 0;
			break;
		}
		if( wk->button_event == BMN_EVENT_TAP )
		{
			Poketch_A13_SetViewCommand( wk->vwk, CMD_BUTTON_RELEASE );
			wk->seq = 0;
			break;
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
		Poketch_A13_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A13_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
