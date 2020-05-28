//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		motion_bl.c
 *@brief	���[�V�����u���[
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
//	���[�V�����u���[�I�u�W�F�N�g
//	
//=====================================
typedef struct _MOTION_BL_TASK{
	GXVRamLCDC		lcdc;		// ����LCDC
	MOTION_BL_DATA	data;
	BOOL			init_flg;
	TCB_PTR			tcb;	
} MOTION_BL_TASK;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static void VBlankLCDCChange(TCB_PTR tcb, void* work);	// LCDC�̏�Ԃ�ݒ肷��^�X�N
static void MOTION_BL_Task(TCB_PTR tcb, void* work);		// ���[�V�����u���[�^�X�N
static void MOTION_BL_Capture( MOTION_BL_DATA* p_data );



//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�V�����u���[���g�����Ԃɏ�����
 *
 *@param	init		�������f�[�^
 *
 *@return	MOTION_BL_PTR	���[�V�����u���[�I�u�W�F�N�g
 *
 *
 */
//-----------------------------------------------------------------------------
MOTION_BL_PTR MOTION_BL_Init(MOTION_BL_DATA* init)
{
	TCB_PTR task;
	MOTION_BL_PTR mb;
	
	// ���[�V�����u���[�^�X�N���Z�b�g
	task = PMDS_taskAdd(MOTION_BL_Task, sizeof(MOTION_BL_TASK), 5, init->heap_id);
	mb = TCB_GetWork(task);

	mb->data = *init;
	mb->tcb = task;
	mb->init_flg = FALSE;

	mb->lcdc = GX_GetBankForLCDC();

	MOTION_BL_Capture( &mb->data );

	// LCDC�`�F���W
	VWaitTCB_Add( VBlankLCDCChange, mb, 0 );
//	addVBlankData(mb, VBlankLCDCChange);

	return mb;
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	���[�V�����u���[�̉���
 *
 *@param	data		���[�V�����u���[�I�u�W�F
 *@param	dispMode	������̃f�B�X�v���C���[�h
 *@param	bgMode		�������BG���[�h
 *@param	bg0_2d3d	�������BG�O���RD�Ɏg�p���邩
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void MOTION_BL_Delete(MOTION_BL_PTR* data, GXDispMode dispMode, GXBGMode bgMode, GXBG0As bg0_2d3d)
{
	

	// �O���t�B�b�N���[�h��߂�
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
		
	
	// �^�X�N�j��
	PMDS_taskDel((*data)->tcb);
	*data = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�r���Ńp�����[�^��ύX
 *
 *@param	data	���[�V�����u���[�I�u�W�F
 *@param	eva		�u�����h�W��A
 *@param	evb		�u�����h�W��B
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
 *@brief	���[�V�����u���[�@�L���v�`���^�X�N
 *
 *@param	tcb		�^�X�N�|�C���^
 *@param	work	���[�V�����u���[�f�[�^
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void MOTION_BL_Task(TCB_PTR tcb, void* work)
{
	MOTION_BL_PTR mb = work;
	
	//�����������҂�
	if( mb->init_flg ){
		GX_SetCapture(
				mb->data.sz,			// �L���v�`���T�C�Y
				mb->data.mode,			// �L���v�`�����[�h
				mb->data.a,				// �L���v�`���u�����hA
				mb->data.b,				// �L���v�`���u�����hB
				mb->data.dest,			// �]��Vram
				mb->data.eva,			// �u�����h�W��A
				mb->data.evb);			// �u�����h�W��B
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	LCDC�̏�Ԃ�ݒ肷��^�X�N
 *
 *@param	work	�ݒ肷��l�������Ă���
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void VBlankLCDCChange(TCB_PTR tcb, void* work)
{
	MOTION_BL_PTR mb = (MOTION_BL_PTR)work;

	// �`��Vram�ݒ�
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

	// �O���t�B�b�N���[�h�ݒ�
	GX_SetGraphicsMode(mb->data.dispMode, mb->data.bgMode,mb->data.bg0_2d3d);	

	// ����������
	mb->init_flg = TRUE;

	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	Capture�֐�
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void MOTION_BL_Capture( MOTION_BL_DATA* p_data )
{
	// �`��Vram������
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
			p_data->sz,			// �L���v�`���T�C�Y
			p_data->mode,			// �L���v�`�����[�h
			p_data->a,				// �L���v�`���u�����hA
			p_data->b,				// �L���v�`���u�����hB
			p_data->dest,			// �]��Vram
			16,						// �u�����h�W��A
			0);						// �u�����h�W��B	
}
