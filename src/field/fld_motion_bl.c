//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fld_motion_bl.c
 *@brief	フィールドモーションブラー
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"

#define __FLD_MOTION_BL_H_GLOBAL
#include "fld_motion_bl.h"


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
//	フィールドモーションブラー
//	構造体
//	
//=====================================
typedef struct _FLD_MOTION_BL_DATA{
	MOTION_BL_PTR	motion_bl;			// モーションブラーオブジェデータ
//	void*			vram_data;			// Vram内保存用	メモリを食うので廃止
} FLD_MOTION_BL_DATA;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	フィールド用にモーションブラーを初期化
 *
 *@param	eva		ブレンド係数A
 *@param	evb		ブレンド係数B
 *
 *@return	FLD_MOTION_BL_PTR	モーションブラーポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
FLD_MOTION_BL_DATA_PTR FLDMotionBl_Init(int eva, int evb)
{
	FLD_MOTION_BL_DATA_PTR ret;

	// BG面の描画を廃止
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1,VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2,VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3,VISIBLE_OFF);
	GX_ResetBankForBG();
	
	// フィールドモーションブラー作成
	ret = sys_AllocMemory(HEAPID_FIELD, sizeof(FLD_MOTION_BL_DATA));
	SDK_ASSERT(ret);
	MI_CpuClear32(ret, sizeof(FLD_MOTION_BL_DATA));
/*	
	// Vramの状態を保存
	ret->vram_data = sys_AllocMemory(HEAPID_FIELD, HW_VRAM_C_SIZE);
	SDK_ASSERT(ret->vram_data);
	MI_CpuCopy32((void*)HW_LCDC_VRAM_C, ret->vram_data, HW_VRAM_C_SIZE);
//*/
	// モーションブラー設定
	{
		MOTION_BL_DATA mb = {
			GX_DISPMODE_VRAM_C,
			GX_BGMODE_0,
			GX_BG0_AS_3D,
			
			GX_CAPTURE_SIZE_256x192,
			GX_CAPTURE_MODE_AB,
			GX_CAPTURE_SRCA_2D3D,
			GX_CAPTURE_SRCB_VRAM_0x00000,
			GX_CAPTURE_DEST_VRAM_C_0x00000,
			0,
			0,
			HEAPID_FIELD
		};
		mb.eva = eva;
		mb.evb = evb;

		ret->motion_bl = MOTION_BL_Init(&mb);
	}	
		

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラー破棄
 *
 *@param	data	モーションブラーデータ
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void FLDMotionBl_Delete(FLD_MOTION_BL_DATA_PTR* data)
{
	// 元に戻す
	MOTION_BL_Delete(&(*data)->motion_bl, GX_DISPMODE_GRAPHICS, GX_BGMODE_0,GX_BG0_AS_3D);
/*
	// 復帰させる
	MI_CpuCopy32((*data)->vram_data, (void*)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE);
//*/
	GX_SetBankForBG(GX_VRAM_BG_128_C);
	
	// BG面描画
	GF_Disp_GX_VisibleControl(
			GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3,
			VISIBLE_ON);

	// データ破棄
//	sys_FreeMemory(HEAPID_FIELD, (*data)->vram_data);
	sys_FreeMemory(HEAPID_FIELD, *data);
	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラー設定の変更
 *
 *@param	data	データ
 *@param	eva		ブレンド係数A
 *@param	evb		ブレンド係数B
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void FLDMotionBl_ParamChg(FLD_MOTION_BL_DATA_PTR data, int eva, int evb)
{
	MOTION_BL_ParamChg(data->motion_bl, eva, evb);
}

