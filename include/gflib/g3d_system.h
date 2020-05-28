//=============================================================================================
/**
 * @file	g3d_system.h
 * @brief	�R�c�`��Ǘ��V�X�e���v���O����
 */
//=============================================================================================
#ifndef _G3D_SYSTEM_H_
#define _G3D_SYSTEM_H_

#undef GLOBAL
#ifdef __G3D_SYSTEM_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif


//=============================================================================================
//	�^�錾
//=============================================================================================
/**
 * @brief	�R�c�V�X�e���}�l�[�W���\����
 */
typedef struct GF_G3DMAN_tag
{
	int		heapID;		///<�q�[�v�h�c

	void*	plt_memory;	///<�p���b�g�}�l�[�W���p������
	void*	tex_memory;	///<�e�N�X�`���}�l�[�W���p������

}GF_G3DMAN;

/**
 * @brief	�}�l�[�W�����[�h��`	
 */
typedef enum {
	GF_G3DMAN_LNK = 0,		///<�����N�h���[�h
	GF_G3DMAN_FRM,			///<�t���[�����[�h
}GF_G3DMAN_MODE;

/**
 * @brief	�e�N�X�`���}�l�[�W���T�C�Y��`	
 */
typedef enum {
	GF_G3DTEX_128K = 1,		///<128KB(1�u���b�N)
	GF_G3DTEX_256K = 2,		///<256KB(2�u���b�N)
	GF_G3DTEX_384K = 3,		///<384KB(3�u���b�N)
	GF_G3DTEX_512K = 4,		///<512KB(4�u���b�N)
}GF_G3DMAN_TEXSIZE;

/**
 * @brief	�p���b�g�}�l�[�W���T�C�Y��`	
 */
typedef enum {
	GF_G3DPLT_16K = 1,		///<16KB
	GF_G3DPLT_32K = 2,		///<32KB
	GF_G3DPLT_64K = 4,		///<64KB
	GF_G3DPLT_80K = 5,		///<80KB
	GF_G3DPLT_96K = 6,		///<96KB
}GF_G3DMAN_PLTSIZE;

/**
 * @brief	�Z�b�g�A�b�v�֐��^
 */
typedef void (*GF_G3DSETUP_FUNC)( void );

//=============================================================================================
//	�ݒ�֐�
//=============================================================================================
//=============================================================================================
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
GLOBAL GF_G3DMAN*  GF_G3DMAN_Init(	u32 heapID, 
									GF_G3DMAN_MODE texmanMode, GF_G3DMAN_TEXSIZE texmanSize, 
									GF_G3DMAN_MODE pltmanMode, GF_G3DMAN_PLTSIZE pltmanSize,
									GF_G3DSETUP_FUNC setup );

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
GLOBAL void	GF_G3D_Exit( GF_G3DMAN*  man );

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
GLOBAL void GF_G3D_Draw_1mat1shape(	NNSG3dRenderObj* object_p,
									VecFx32* trans_p,
									MtxFx33* rot_p,
									VecFx32* scale_p);
#undef GLOBAL
#endif

