//============================================================================================
/**
 * @file	pmsiv_tool.c
 * @bfief	簡易会話入力画面（描画下請け：共有ツール類）
 * @author	taya
 * @date	06.02.10
 */
//============================================================================================
#include "common.h"
#include "gflib\heapsys.h"
#include "system\arc_util.h"
#include "system\window.h"
#include "system\buflen.h"
#include "system\pms_word.h"
#include "system\winframe.naix"
#include "system\msgdata.h"
#include "msgdata\msg_pms_category.h"

#include "msgdata\msg.naix"


#include "pms_input_prv.h"
#include "pms_input_view.h"
#include "pmsiv_tool.h"


//==============================================================
// Prototype
//==============================================================
static void bg_scroll_task( TCB_PTR tcb, void* wk_adrs );
static void fade_task( TCB_PTR tcb, void* wk_adrs );
static void bright_task( TCB_PTR tcb, void* wk_adrs );



//------------------------------------------------------------------
/**
 * スクロール処理ワークセットアップ
 *
 * @param   wk			ワークポインタ
 * @param   bgl			bglポインタ
 * @param   bg_frame	対象BGフレーム
 * @param   direction	スクロール方向（PMSIV_TOOL_SCROLL_DIRECTION）
 * @param   vector		スクロール量
 * @param   wait		スクロールに要するフレーム数
 *
 */
//------------------------------------------------------------------
void PMSIV_TOOL_SetupScrollWork( PMSIV_TOOL_SCROLL_WORK* wk, GF_BGL_INI* bgl, u32 bg_frame, int direction, int vector, int wait )
{
	wk->bgl = bgl;
	wk->bg_frame = bg_frame;

	if( direction == PMSIV_TOOL_SCROLL_DIRECTION_X )
	{
		wk->pos = GF_BGL_ScrollGetX( bgl, bg_frame );
		wk->scroll_param = GF_BGL_SCROLL_X_SET;
	}
	else
	{
		wk->pos = GF_BGL_ScrollGetY( bgl, bg_frame );
		wk->scroll_param = GF_BGL_SCROLL_Y_SET;
	}

	wk->end_pos = (wk->pos + vector) & 0x01ff;
	wk->pos *= FX32_ONE;
	wk->add_value = (vector * FX32_ONE) / wait;
	wk->timer = wait;

	wk->seq = 0;
}

//------------------------------------------------------------------
/**
 * スクロール処理終了待ち
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIV_TOOL_WaitScroll( PMSIV_TOOL_SCROLL_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		wk->tcb = PMSIView_AddVTask( bg_scroll_task, wk, VTASKPRI_COMMAND );
		wk->seq++;
		break;

	case 1:
		if( wk->timer == 0 )
		{
			TCB_Delete( wk->tcb );
			wk->seq++;
			return TRUE;
		}
		break;

	case 2:
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * スクロール処理タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void bg_scroll_task( TCB_PTR tcb, void* wk_adrs )
{
	PMSIV_TOOL_SCROLL_WORK* wk = wk_adrs;

	if( wk->timer )
	{
		wk->pos += wk->add_value;
		GF_BGL_ScrollSet( wk->bgl, wk->bg_frame, wk->scroll_param, (wk->pos >> FX32_SHIFT) );
		wk->timer--;
	}
	else
	{
		GF_BGL_ScrollSet( wk->bgl, wk->bg_frame, wk->scroll_param, wk->end_pos );
	}
}


//------------------------------------------------------------------
/**
 * 半透明エフェクト開始
 *
 * @param   wk		
 * @param   plane1		
 * @param   plane2		
 * @param   start		
 * @param   end		
 * @param   wait		
 *
 */
//------------------------------------------------------------------
void PMSIV_TOOL_SetupBlendWork( PMSIV_TOOL_BLEND_WORK* wk, int plane1, int plane2, int start, int end, int wait )
{
	wk->plane1 = plane1;
	wk->plane2 = plane2;
	wk->wait = wait;
	wk->ev = start;
	wk->ev_step = (fx32)((end - start)) / wait;

	wk->ev_end = end;

	wk->seq = 0;
	wk->tcb = PMSIView_AddVTask( fade_task, wk, VTASKPRI_COMMAND );
}

BOOL PMSIV_TOOL_WaitBlend( PMSIV_TOOL_BLEND_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		if( wk->wait == 0 )
		{
			TCB_Delete( wk->tcb );
			wk->seq++;
			return TRUE;
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}


static void fade_task( TCB_PTR tcb, void* wk_adrs )
{
	PMSIV_TOOL_BLEND_WORK* wk = wk_adrs;
	int ev1, ev2;
	if( wk->wait )
	{
		wk->ev += wk->ev_step;
		ev1 = wk->ev >> 3;
		wk->wait--;
	}
	else
	{
		ev1 = wk->ev_end >> 3;
	}

	if( ev1 > 16 )
	{
		ev1 = 16;
	}

	ev2 = 16 - ev1;

	G2_SetBlendAlpha( wk->plane1, wk->plane2, ev1, ev2 );
}






//------------------------------------------------------------------
/**
 * 輝度エフェクト開始
 *
 * @param   wk			
 * @param   bg_plane	
 * @param   start		
 * @param   end			
 * @param   wait		
 *
 */
//------------------------------------------------------------------
void PMSIV_TOOL_SetupBrightWork( PMSIV_TOOL_BLEND_WORK* wk, int bg_plane, int start, int end, int wait )
{
	G2_SetBlendBrightness( bg_plane, start );

	wk->plane1 = bg_plane;
	wk->wait = wait;
	wk->ev = start * FX32_ONE;
	wk->ev_end = end * FX32_ONE;
	wk->ev_step = (fx32)((wk->ev_end - wk->ev)) / wait;

	wk->seq = 0;
	wk->tcb = PMSIView_AddVTask( bright_task, wk, VTASKPRI_COMMAND );
}

//------------------------------------------------------------------
/**
 * 輝度エフェクト終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL PMSIV_TOOL_WaitBright( PMSIV_TOOL_BLEND_WORK* wk )
{
	switch( wk->seq ){
	case 0:
		if( wk->wait == 0 )
		{
			TCB_Delete( wk->tcb );
			wk->seq++;
			return TRUE;
		}
		break;

	default:
		return TRUE;
	}
	return FALSE;
}

static void bright_task( TCB_PTR tcb, void* wk_adrs )
{
	PMSIV_TOOL_BLEND_WORK* wk = wk_adrs;

	int ev;

	if( wk->wait )
	{
		wk->ev += wk->ev_step;
		ev = wk->ev >> FX32_SHIFT;
		wk->wait--;
	}
	else
	{
		ev = wk->ev_end >> FX32_SHIFT;
	}

	G2_SetBlendBrightness( wk->plane1, ev );
}


