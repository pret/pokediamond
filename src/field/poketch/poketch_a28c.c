//============================================================================================
/**
 * @file	poketch_a28c.c
 * @bfief	ポケッチ（アプリNoa28：ポケモンカウンター）　コントロール
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include <nitro/sinit.h>
#include "common.h"
#include "system\lib_pack.h"
#include "..\sway_grass_hist.h"

#include "poketch_a28.h"
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
static BOOL Poketch_A28_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param);
static BOOL SetupWork( APPWORK *wk, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param );
static void CleanupWork( APPWORK *wk );
static void Poketch_A28_Main(TCB_PTR tcb, void *wk_adrs);
static void Poketch_A28_Quit(void *wk_adrs);
static void BmnCallBack( u32 idx, u32 event, u32 touch_event, void* wk_adrs );
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
	PoketchSetAppProc(Poketch_A28_Init, Poketch_A28_Quit);
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
static BOOL Poketch_A28_Init(void **wk_ptr, CONTACT_WORK* conwk, GF_BGL_INI* bgl, u32 param)
{
	APPWORK* wk = (APPWORK*)sys_AllocMemory( POKETCH_APP_CTRL_HEAPID, sizeof(APPWORK));

	if(wk != NULL)
	{
		if(SetupWork( wk, conwk, bgl, param ))
		{
			if( TCB_Add(Poketch_A28_Main, wk, POKETCH_APP_TASKPRI) != NULL )
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
		{ ICON_TOP(ICON_RANK1_YPOS), ICON_BOTTOM(ICON_RANK1_YPOS), ICON_LEFT(ICON_RANK1_XPOS), ICON_RIGHT(ICON_RANK1_XPOS) },
		{ ICON_TOP(ICON_RANK2_YPOS), ICON_BOTTOM(ICON_RANK2_YPOS), ICON_LEFT(ICON_RANK2_XPOS), ICON_RIGHT(ICON_RANK2_XPOS) },
		{ ICON_TOP(ICON_RANK3_YPOS), ICON_BOTTOM(ICON_RANK3_YPOS), ICON_LEFT(ICON_RANK3_XPOS), ICON_RIGHT(ICON_RANK3_XPOS) },
	};

	FIELDSYS_WORK* fsys;
	int i;

	OS_TPrintf("start get status\n");

	fsys = PoketchGetFieldSysWork( conwk );
	wk->vpara.now_count = SwayGrassHist_GetNowChain( fsys );
	if(wk->vpara.now_count)
	{
		wk->vpara.now_monsno = SwayGrassHist_GetNowMonsNo( fsys );
	}
	else
	{
		wk->vpara.now_monsno = 0;
	}
	OS_TPrintf("  now: count=%d, monsno=%d\n", wk->vpara.now_count, wk->vpara.now_monsno);
	for(i=0; i<3; i++)
	{
		wk->vpara.rank_count[i] = SwayGrassHist_GetChain( fsys, i );
		wk->vpara.rank_monsno[i] = SwayGrassHist_GetMonsNo( fsys, i );
		OS_TPrintf("  rank(%d): count=%d, monsno=%d\n", i+1, wk->vpara.rank_count[i], wk->vpara.rank_monsno[i]);
	}
	wk->vpara.rank_max = SwayGrassHist_GetHistNum( fsys );

	OS_TPrintf("rankd max = %d\n", wk->vpara.rank_max);

	if( Poketch_A28_SetViewWork( &(wk->vwk), &(wk->vpara), bgl ) )
	{
		wk->main_seq = SEQ_INIT;
		wk->seq = 0;
		wk->quit_req_flag = FALSE;

		wk->button =  PBTN_Create( hit_tbl, NELEMS(hit_tbl), BmnCallBack, wk, POKETCH_APP_CTRL_HEAPID );
		wk->button_event = BMN_EVENT_NULL;
		wk->button_id = 0;

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
	Poketch_A28_DeleteViewWork( wk->vwk );
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
static void Poketch_A28_Main(TCB_PTR tcb, void *wk_adrs)
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
static void Poketch_A28_Quit(void *wk_adrs)
{
	((APPWORK*)wk_adrs)->quit_req_flag = TRUE;
	OS_TPrintf("a28 quit req\n");
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
		Poketch_A28_SetViewCommand( wk->vwk, CMD_INIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A28_WaitViewCommand( wk->vwk, CMD_INIT ))
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

//	if( PoketchGetPlayerMoveTrg( wk->conwk ) )
	// 歩かなくても毎フレームチェック
	{
		FIELDSYS_WORK* fsys;
		int monsno;

		fsys = PoketchGetFieldSysWork( wk->conwk );

		wk->vpara.now_count = SwayGrassHist_GetNowChain( fsys );
		if( wk->vpara.now_count == 0 )
		{
			monsno = 0;
		}
		else
		{
			monsno = SwayGrassHist_GetNowMonsNo( fsys );
		}

		if( monsno != wk->vpara.now_monsno )
		{
			wk->vpara.now_monsno = monsno;
			Poketch_A28_SetViewCommand( wk->vwk, CMD_UPDATE );
			return FALSE;
		}
	}

	if( Poketch_A28_WaitViewCommand( wk->vwk, CMD_TOUCH ) )
	{
		if( wk->button_event == BMN_EVENT_TOUCH )
		{
			if( wk->button_id < wk->vpara.rank_max )
			{
				int  p = wk->button_id;
				if( wk->vpara.rank_count[p] )
				{
					wk->vpara.touch_poke = p;
					Poketch_A28_SetViewCommand( wk->vwk, CMD_TOUCH );
				}
			}
			wk->button_event = BMN_EVENT_NULL;
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
		Poketch_A28_SetViewCommand( wk->vwk, CMD_QUIT );
		wk->seq++;
		break;

	case 1:
		if(Poketch_A28_WaitViewCommandAll( wk->vwk ))
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}
