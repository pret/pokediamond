//=============================================================================================
/**
 * @file	display.c                                                  
 * @brief	�\���V�X�e���ݒ�
 */
//=============================================================================================
#include <nitro.h>
#include <nnsys.h>

#define	__DISPLAY_H_GLOBAL
#include "display.h"
#include "system.h"

//=============================================================================================
//	�v���g�^�C�v�錾
//=============================================================================================
//=============================================================================================
//	���[�J���ϐ��錾
//=============================================================================================
static	int				MainVisiblePlane;
static	int				SubVisiblePlane;

//=============================================================================================
//	�ݒ�֐�
//=============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * �u�q�`�l�o���N�S�̐ݒ�
 *
 * @param	data	�ݒ�f�[�^
 */
//--------------------------------------------------------------------------------------------
void	GF_Disp_SetBank( const GF_BGL_DISPVRAM* dispvram )
{
	// VRAM�ݒ胊�Z�b�g
	GX_ResetBankForBG();			// ���C��2D�G���W����BG
	GX_ResetBankForBGExtPltt();		// ���C��2D�G���W����BG�g���p���b�g
	GX_ResetBankForSubBG();			// �T�u2D�G���W����BG
	GX_ResetBankForSubBGExtPltt();	// �T�u2D�G���W����BG�g���p���b�g
	GX_ResetBankForOBJ();			// ���C��2D�G���W����OBJ
	GX_ResetBankForOBJExtPltt();	// ���C��2D�G���W����OBJ�g���p���b�g
	GX_ResetBankForSubOBJ();		// �T�u2D�G���W����OBJ
	GX_ResetBankForSubOBJExtPltt();	// �T�u2D�G���W����OBJ�g���p���b�g
	GX_ResetBankForTex();			// �e�N�X�`���C���[�W
	GX_ResetBankForTexPltt();		// �e�N�X�`���p���b�g

	GX_SetBankForBG( dispvram->main_bg );
	GX_SetBankForBGExtPltt( dispvram->main_bg_expltt );

	GX_SetBankForSubBG( dispvram->sub_bg );
	GX_SetBankForSubBGExtPltt( dispvram->sub_bg_expltt );

	GX_SetBankForOBJ( dispvram->main_obj );
	GX_SetBankForOBJExtPltt( dispvram->main_obj_expltt );

	GX_SetBankForSubOBJ( dispvram->sub_obj );
	GX_SetBankForSubOBJExtPltt( dispvram->sub_obj_expltt );

	GX_SetBankForTex( dispvram->teximage );
	GX_SetBankForTexPltt( dispvram->texpltt );
}

//--------------------------------------------------------------------------------------------
/**
 * ���C����ʂ̊e�ʂ̕\���R���g���[��������
 *
 * @param	
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GX_VisibleControlInit( void )
{
	MainVisiblePlane = 0;
	//GX_SetVisiblePlane( MainVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * ���C����ʂ̊e�ʂ̕\���R���g���[��
 *
 * @param	gxplanemask		�ݒ��
 * @param	flg				�R���g���[���t���O
 *
 * @li	flg = VISIBLE_ON	: �\��
 * @li	flg = VISIBLE_OFF	: ��\��
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GX_VisibleControl( u8 gxplanemask, u8 flg )
{
	if( flg == VISIBLE_ON ){
		if( MainVisiblePlane & gxplanemask ){ return; }
	}else{
		if( !(MainVisiblePlane & gxplanemask) ){ return; }
	}
	MainVisiblePlane ^= gxplanemask;
	GX_SetVisiblePlane( MainVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * ���C����ʂ̊e�ʂ̕\���R���g���[���i���A�Ƃ��j
 *
 * @param	prm		�\���p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GX_VisibleControlDirect( int prm )
{
	MainVisiblePlane = prm;
	GX_SetVisiblePlane( MainVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʂ̊e�ʂ̕\���R���g���[��������
 *
 * @param	
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GXS_VisibleControlInit( void )
{
	SubVisiblePlane = 0;
	//GXS_SetVisiblePlane( MainVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʂ̊e�ʂ̕\���R���g���[��
 *
 * @param	gxplanemask		�ݒ��
 * @param	flg				�R���g���[���t���O
 *
 * @li	flg = VISIBLE_ON	: �\��
 * @li	flg = VISIBLE_OFF	: ��\��
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GXS_VisibleControl( u8 gxplanemask, u8 flg )
{
	if( flg == VISIBLE_ON ){
		if( SubVisiblePlane & gxplanemask ){ return; }
	}else{
		if( !(SubVisiblePlane & gxplanemask) ){ return; }
	}
	SubVisiblePlane ^= gxplanemask;
	GXS_SetVisiblePlane( SubVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʂ̊e�ʂ̕\���R���g���[���i���A�Ƃ��j
 *
 * @param	prm		�\���p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_GXS_VisibleControlDirect( int prm )
{
	SubVisiblePlane = prm;
	GXS_SetVisiblePlane( SubVisiblePlane );
}

//--------------------------------------------------------------------------------------------
/**
 * �\���L���ݒ�
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void	GF_Disp_DispOn( void )
{
	GX_DispOn();
	GXS_DispOn();
}

//--------------------------------------------------------------------------------------------
/**
 * �\�������ݒ�
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void	GF_Disp_DispOff( void )
{
	GX_DispOff();
	GXS_DispOff();
}


//--------------------------------------------------------------------------------------------
/**
 * ��ʂ̕\���T�C�h�ݒ�
 *
 * @param	
 */
//--------------------------------------------------------------------------------------------
void GF_Disp_DispSelect( void )
{
	if(sys.disp3DSW == DISP_3D_TO_MAIN){
		GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
	}else{
		GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ���C����ʂ̕\���󋵎擾
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int GF_Disp_MainVisibleGet(void)
{
	return MainVisiblePlane;
}

//--------------------------------------------------------------------------------------------
/**
 * �T�u��ʂ̕\���󋵎擾
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
int GF_Disp_SubVisibleGet(void)
{
	return SubVisiblePlane;
}
