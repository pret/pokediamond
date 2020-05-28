//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		motion_bl.c
 *@brief	モーションブラー
 *@author	 tomoya takahashi
 *@data		2005.07.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#define __MOTION_BL_H_GLOBAL
#include "motion_bl.h"
#include "system/lib_pack.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	モーションブラーオブジェクト
//	
//=====================================
typedef struct _MOTION_BL_TASK{
	GXVRamLCDC		lcdc;		// 元のLCDC
	MOTION_BL_DATA	data;
	BOOL			init_flg;
	TCB_PTR			tcb;	
} MOTION_BL_TASK;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void VBlankLCDCChange(TCB_PTR tcb, void* work);	// LCDCの状態を設定するタスク
static void MOTION_BL_Task(TCB_PTR tcb, void* work);		// モーションブラータスク
static void MOTION_BL_Capture( MOTION_BL_DATA* p_data );



//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラーを使える状態に初期化
 *
 *@param	init		初期化データ
 *
 *@return	MOTION_BL_PTR	モーションブラーオブジェクト
 *
 *
 */
//-----------------------------------------------------------------------------
MOTION_BL_PTR MOTION_BL_Init(MOTION_BL_DATA* init)
{
	TCB_PTR task;
	MOTION_BL_PTR mb;
	
	// モーションブラータスクをセット
	task = PMDS_taskAdd(MOTION_BL_Task, sizeof(MOTION_BL_TASK), 5, init->heap_id);
	mb = TCB_GetWork(task);

	mb->data = *init;
	mb->tcb = task;
	mb->init_flg = FALSE;

	mb->lcdc = GX_GetBankForLCDC();

	MOTION_BL_Capture( &mb->data );

	// LCDCチェンジ
	VWaitTCB_Add( VBlankLCDCChange, mb, 0 );
//	addVBlankData(mb, VBlankLCDCChange);

	return mb;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラーの解除
 *
 *@param	data		モーションブラーオブジェ
 *@param	dispMode	解除後のディスプレイモード
 *@param	bgMode		解除後のBGモード
 *@param	bg0_2d3d	解除後のBG０を３Dに使用するか
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void MOTION_BL_Delete(MOTION_BL_PTR* data, GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d)
{
	

	// グラフィックモードを戻す
	GX_SetGraphicsMode(dispMode, bgMode,bg0_2d3d);

	GX_SetBankForLCDC((*data)->lcdc);
	
	switch((*data)->data.dispMode){
	case GX_DISPMODE_VRAM_A:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_A, HW_VRAM_A_SIZE );
		break;
	case GX_DISPMODE_VRAM_B:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_B, HW_VRAM_B_SIZE );
		break;
	case GX_DISPMODE_VRAM_C:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE );
		break;
	case GX_DISPMODE_VRAM_D:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_D, HW_VRAM_D_SIZE );
		break;
	default:
		GX_SetBankForLCDC(GX_VRAM_LCDC_NONE);
		break;
	}
		
	
	// タスク破棄
	PMDS_taskDel((*data)->tcb);
	*data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	途中でパラメータを変更
 *
 *@param	data	モーションブラーオブジェ
 *@param	eva		ブレンド係数A
 *@param	evb		ブレンド係数B
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void MOTION_BL_ParamChg(MOTION_BL_PTR data, int eva, int evb)
{
	data->data.eva = eva;
	data->data.evb = evb;
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラー　キャプチャタスク
 *
 *@param	tcb		タスクポインタ
 *@param	work	モーションブラーデータ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void MOTION_BL_Task(TCB_PTR tcb, void* work)
{
	MOTION_BL_PTR mb = work;
	
	//初期化完了待ち
	if( mb->init_flg ){
		GX_SetCapture(
				mb->data.sz,			// キャプチャサイズ
				mb->data.mode,			// キャプチャモード
				mb->data.a,				// キャプチャブレンドA
				mb->data.b,				// キャプチャブレンドB
				mb->data.dest,			// 転送Vram
				mb->data.eva,			// ブレンド係数A
				mb->data.evb);			// ブレンド係数B
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	LCDCの状態を設定するタスク
 *
 *@param	work	設定する値が入っている
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void VBlankLCDCChange(TCB_PTR tcb, void* work)
{
	MOTION_BL_PTR mb = (MOTION_BL_PTR)work;

	// 描画Vram設定
	switch(mb->data.dispMode){
	case GX_DISPMODE_VRAM_A:
		GX_SetBankForLCDC(GX_VRAM_LCDC_A);
		break;
	case GX_DISPMODE_VRAM_B:
		GX_SetBankForLCDC(GX_VRAM_LCDC_B);
		break;
	case GX_DISPMODE_VRAM_C:
		GX_SetBankForLCDC(GX_VRAM_LCDC_C);
		break;
	case GX_DISPMODE_VRAM_D:
		GX_SetBankForLCDC(GX_VRAM_LCDC_D);
		break;
	default:
		GX_SetBankForLCDC(GX_VRAM_LCDC_NONE);
		break;
	}

	// グラフィックモード設定
	GX_SetGraphicsMode(mb->data.dispMode, mb->data.bgMode,mb->data.bg0_2d3d);	

	// 初期化完了
	mb->init_flg = TRUE;

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Capture関数
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void MOTION_BL_Capture( MOTION_BL_DATA* p_data )
{
	// 描画Vram初期化
	switch(p_data->dispMode){
	case GX_DISPMODE_VRAM_A:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_A, HW_VRAM_A_SIZE );
		break;
	case GX_DISPMODE_VRAM_B:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_B, HW_VRAM_B_SIZE );
		break;
	case GX_DISPMODE_VRAM_C:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE );
		break;
	case GX_DISPMODE_VRAM_D:
		MI_CpuClearFast( (void*)HW_LCDC_VRAM_D, HW_VRAM_D_SIZE );
		break;
	default:
		break;
	}

	GX_SetCapture(
			p_data->sz,			// キャプチャサイズ
			p_data->mode,			// キャプチャモード
			p_data->a,				// キャプチャブレンドA
			p_data->b,				// キャプチャブレンドB
			p_data->dest,			// 転送Vram
			16,						// ブレンド係数A
			0);						// ブレンド係数B	
}
