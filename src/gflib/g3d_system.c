//=============================================================================================
/**
 * @file	g3d_system.c                                                  
 * @brief	�R�c�`��Ǘ��V�X�e���v���O����
 * @date	2006/4/26
 */
//=============================================================================================
#include "system.h"
#include "display.h"
#include "gflib_os_print.h"

#define	__G3D_SYSTEM_H_GLOBAL
#include "g3d_system.h"

#ifdef PM_DEBUG
#include "debug_3d_draw_count.h"
#endif	//PM_DEBUG

//=============================================================================================
//	�^�錾
//=============================================================================================
#define TEX_BLOCKNUM	(128)
#define PLT_BLOCKNUM	(256)

#define TEX_SLOTSIZ		(0x20000)
#define PLT_SLOTSIZ		(0x2000)
//=============================================================================================
//	�v���g�^�C�v�錾
//=============================================================================================
static void		GF_G3D_DefaultSetUp( void );
//--------------------------------------------------------------------------------------------
/**
 * �V�X�e���}�l�[�W���ݒ�
 *
 * @param	heapID			�������擾�p�q�[�v�G���A
 * @param	texmanMode		�e�N�X�`���}�l�[�W���g�p���[�h
 * @param	texmanSize		�e�N�X�`���}�l�[�W���g�p�̈�T�C�Y�ibyte�j
 * @param	palmanMode		�p���b�g�}�l�[�W���g�p���[�h
 * @param	palmanSize		�p���b�g�}�l�[�W���g�p�̈�T�C�Y�ibyte�j
 * @param	setUp			�Z�b�g�A�b�v�֐�(NULL�̎���DefaultSetUp)
 *
 * @return	�}�l�[�W�����[�N�|�C���^
 */
//--------------------------------------------------------------------------------------------
GF_G3DMAN*  GF_G3DMAN_Init(	u32 heapID, 
							GF_G3DMAN_MODE texmanMode, GF_G3DMAN_TEXSIZE texmanSize, 
							GF_G3DMAN_MODE pltmanMode, GF_G3DMAN_PLTSIZE pltmanSize,
							GF_G3DSETUP_FUNC setup )
{
	int	tex_size,plt_size;
	GF_G3DMAN* man = sys_AllocMemory( heapID, sizeof(GF_G3DMAN) );

	man->heapID = heapID;

	// NitroSystem:�R�c�G���W���̏�����
	NNS_G3dInit();
	// �}�g���N�X�X�^�b�N�̏�����
    G3X_InitMtxStack();

	// �W�I���g���G���W���N����K���Ă΂�Ȃ���΂Ȃ�Ȃ�
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	//�u�q�`�l�e�N�X�`���}�l�[�W���̐ݒ�
	if( texmanMode == GF_G3DMAN_LNK ){
		//�����N�h���[�h�̐ݒ�
		tex_size = NNS_GfdGetLnkTexVramManagerWorkSize( TEX_BLOCKNUM * texmanSize );
		man->tex_memory = sys_AllocMemory( man->heapID, tex_size );

		// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
		NNS_GfdInitLnkTexVramManager( TEX_SLOTSIZ*texmanSize, 0, man->tex_memory, tex_size, TRUE);
	} else {
		//�t���[�����[�h�̐ݒ�
		NNS_GfdInitFrmTexVramManager( texmanSize, TRUE);
	}

	//�u�q�`�l�p���b�g�}�l�[�W���̐ݒ�
	if( pltmanMode == GF_G3DMAN_LNK ){
		//�����N�h���[�h�̐ݒ�
		plt_size = NNS_GfdGetLnkPlttVramManagerWorkSize( PLT_BLOCKNUM * pltmanSize );
		man->plt_memory = sys_AllocMemory( man->heapID, plt_size );

		// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��T�C�Y���Ǘ��ł���悤�ɂ���
		NNS_GfdInitLnkPlttVramManager( PLT_SLOTSIZ * pltmanSize, man->plt_memory, plt_size, TRUE);
	} else {
		//�t���[�����[�h�̐ݒ�
		NNS_GfdInitFrmTexVramManager( PLT_SLOTSIZ * pltmanSize, TRUE);
	}

	if( setup != NULL ){
		setup();
	} else {
		GF_G3D_DefaultSetUp();
	}
	return man;
}

//--------------------------------------------------------------------------------------------
/**
 * �I��
 *
 * @param	man		�}�l�[�W�����[�N�|�C���^
 *
 * @return	none
 *
 */
//--------------------------------------------------------------------------------------------
void		GF_G3D_Exit( GF_G3DMAN*  man )
{
	sys_FreeMemoryEz( man->plt_memory );
	sys_FreeMemoryEz( man->tex_memory );

	sys_FreeMemoryEz( man );
}

//--------------------------------------------------------------------------------------------
/**
 * �e�탂�[�h�f�t�H���g�Z�b�g�A�b�v
 *
 * @param	none
 * @return	none
 *
 */
//--------------------------------------------------------------------------------------------
static void		GF_G3D_DefaultSetUp( void )
{
	// �R�c�g�p�ʂ̐ݒ�(�\�����v���C�I���e�B�[)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(0);

	// �e��`�惂�[�h�̐ݒ�(�V�F�[�h���A���`�G�C���A�X��������)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( FALSE );
	G3X_AlphaTest( FALSE, 0 );	// �A���t�@�e�X�g�@�@�I�t
	G3X_AlphaBlend( FALSE );		// �A���t�@�u�����h�@�I��
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// �N���A�J���[�̐ݒ�
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// �r���[�|�[�g�̐ݒ�
    G3_ViewPort(0, 0, 255, 191);
}

//------------------------------------------------------------------
//  �����R�c�a�f�`��֐�
//  
//  @param		object_p		�����_�[�n�a�i
//  @param		trans_p			�g�����X���[�g
//  @param		rot_p			���[�e�[�V����
//  @param		scale_p			�X�P�[��
//
//  @return		none
//  
//------------------------------------------------------------------
void GF_G3D_Draw_1mat1shape(NNSG3dRenderObj* object_p,
							VecFx32* trans_p,
							MtxFx33* rot_p,
							VecFx32* scale_p)
{
#ifdef DEBUG_3DDRAW_COUNT
	D_3D_DC_CountNum(object_p);
#endif// DEBUG_3DDRAW_COUNT

	// �ʒu�ݒ�
	NNS_G3dGlbSetBaseTrans(trans_p);
	// �p�x�ݒ�
	NNS_G3dGlbSetBaseRot(rot_p);
	// �X�P�[���ݒ�
	NNS_G3dGlbSetBaseScale(scale_p);

	NNS_G3dGlbFlush();
    
    NNS_G3dDraw1Mat1Shp(object_p->resMdl,0,0,TRUE);
    
    NNS_G3dGeFlushBuffer();
}

