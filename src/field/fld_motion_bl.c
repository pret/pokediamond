//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fld_motion_bl.c
 *@brief	�t�B�[���h���[�V�����u���[
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
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�t�B�[���h���[�V�����u���[
//	�\����
//	
//=====================================
typedef struct _FLD_MOTION_BL_DATA{
	MOTION_BL_PTR	motion_bl;			// ���[�V�����u���[�I�u�W�F�f�[�^
//	void*			vram_data;			// Vram���ۑ��p	��������H���̂Ŕp�~
} FLD_MOTION_BL_DATA;



//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�t�B�[���h�p�Ƀ��[�V�����u���[��������
 *
 *@param	eva		�u�����h�W��A
 *@param	evb		�u�����h�W��B
 *
 *@return	FLD_MOTION_BL_PTR	���[�V�����u���[�|�C���^
 *
 *
 */
//-----------------------------------------------------------------------------
FLD_MOTION_BL_DATA_PTR FLDMotionBl_Init(int eva, int evb)
{
	FLD_MOTION_BL_DATA_PTR ret;

	// BG�ʂ̕`���p�~
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1,VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2,VISIBLE_OFF);
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3,VISIBLE_OFF);
	GX_ResetBankForBG();
	
	// �t�B�[���h���[�V�����u���[�쐬
	ret = sys_AllocMemory(HEAPID_FIELD, sizeof(FLD_MOTION_BL_DATA));
	SDK_ASSERT(ret);
	MI_CpuClear32(ret, sizeof(FLD_MOTION_BL_DATA));
/*	
	// Vram�̏�Ԃ�ۑ�
	ret->vram_data = sys_AllocMemory(HEAPID_FIELD, HW_VRAM_C_SIZE);
	SDK_ASSERT(ret->vram_data);
	MI_CpuCopy32((void*)HW_LCDC_VRAM_C, ret->vram_data, HW_VRAM_C_SIZE);
//*/
	// ���[�V�����u���[�ݒ�
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
 *@brief	���[�V�����u���[�j��
 *
 *@param	data	���[�V�����u���[�f�[�^
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void FLDMotionBl_Delete(FLD_MOTION_BL_DATA_PTR* data)
{
	// ���ɖ߂�
	MOTION_BL_Delete(&(*data)->motion_bl, GX_DISPMODE_GRAPHICS, GX_BGMODE_0,GX_BG0_AS_3D);
/*
	// ���A������
	MI_CpuCopy32((*data)->vram_data, (void*)HW_LCDC_VRAM_C, HW_VRAM_C_SIZE);
//*/
	GX_SetBankForBG(GX_VRAM_BG_128_C);
	
	// BG�ʕ`��
	GF_Disp_GX_VisibleControl(
			GX_PLANEMASK_BG1|GX_PLANEMASK_BG2|GX_PLANEMASK_BG3,
			VISIBLE_ON);

	// �f�[�^�j��
//	sys_FreeMemory(HEAPID_FIELD, (*data)->vram_data);
	sys_FreeMemory(HEAPID_FIELD, *data);
	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�V�����u���[�ݒ�̕ύX
 *
 *@param	data	�f�[�^
 *@param	eva		�u�����h�W��A
 *@param	evb		�u�����h�W��B
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

