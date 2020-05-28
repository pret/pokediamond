//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_light.h
 *@brief	���C�g�R���g���[��
 *@author	tomoya takahashi
 *@data		2005.04.01
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include <nitro.h>
#include "field_glb_state.h"

#ifndef __LIGHT_CONT_H__
#define	__LIGHT_CONT_H__

#undef	GLOBAL
#ifdef	__LIGHT_CONT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define		DEB_MATE_ADD		(FX16_CONST( 0.10f ))

enum { 
	LIGHT_TYPE1,	// ��O
	LIGHT_TYPE2,	// ����
	LIGHT_TYPE3,	// �C�A�G�A�C�x���g
	LIGHT_TYPE_MAX
};


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
typedef struct _LIGHT_CONT_SET* LIGHT_CONT_PTR;		// ���C�g�V�X�e���̃f�[�^�|�C���^
typedef const struct  _LIGHT_CONT_SET* CONST_LIGHT_CONT_PTR;		// ���C�g�V�X�e���̃f�[�^�|�C���^


//-------------------------------------
//	�P���C�g�f�[�^�e�[�u��
//=====================================
typedef struct{
	u32			lightEnd;	// ���C�g���ɕύX����
	
	u8			lightFlag;		// ���C�g�`��t���O
	GXRgb		lightColor[4];	// ���C�g�̐F
	VecFx16		lightVec[4];	// ���C�g�̕���
	
	GXRgb		diffuse;		// �f�B�t���[�Y�F	�i���̂̐F�j
    GXRgb		ambient;		// �A���r�G���g�F	�i�����j
	GXRgb		specular;		// �X�y�L�����[�F	�i�����������������Ƃ���̐F�j
	GXRgb		emission;		// ���ːF
}LIGHT_CONT_DATA;



// ���f���f�[�^�Ƀ��C�g�ݒ肪����Ă��Ȃ��������邽�߁A���C�g�t���O��ݒ肷��悤�ɂ���
// �������A���̒��������Ă���̂��`�F�b�N����Ƃ��́A���FIELD_LIGHT_MASK���I���ɂ���
#define		FIELD_LIGHT_MASK	(GLST_LIGHTVEC_1|GLST_LIGHTVEC_2|GLST_LIGHTCOL_1|GLST_LIGHTCOL_2|GLST_DIFF|GLST_AMB|GLST_SPEC|GLST_EMI)		// field_glb_state�Őݒ肷��f�[�^�̃}�X�N

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
GLOBAL LIGHT_CONT_PTR InitLightCont(GLST_DATA_PTR glb, const u8 light_index/*const char* path*/);	// ���C�g�V�X�e����������
GLOBAL void DellLightCont(LIGHT_CONT_PTR* pLight);					// ���C�g�V�X�e����j��

GLOBAL void MainLightCont(LIGHT_CONT_PTR Light);	// ���C�g�𓮂���
GLOBAL void SetLightContReflect( LIGHT_CONT_PTR Light, BOOL reflect );	// ���C�g�f�[�^���t�B�[���h�ɔ��f�����邩�ݒ� TREU���f
GLOBAL BOOL GetLightContReflect( CONST_LIGHT_CONT_PTR Light );
GLOBAL void DataSetLightCont( const LIGHT_CONT_DATA* move, GLST_DATA_PTR pGlst );	// 1���C�g�f�[�^�ݒ�

GLOBAL void SetGlbLightMdl(NNSG3dResMdl* Mdl);	// ���f���ɃO���[�o���X�e�[�g�̃��C�g�����f����悤�ɂ���
GLOBAL void RemGlbLightMdl(NNSG3dResMdl* Mdl);	// ���f�����O���[�o���X�e�[�g�̃��C�g�𔽉f���Ȃ��悤�ɂ���


//----------------------------------------------------------------------------
/**
 * ���f�o�b�N�p	�l���ƒf�ƕΌ��Ŗ邩�������f���Ă��܂�
 *
 *	@brief	�邩�`�F�b�N
 *
 *	@param	cont	���C�g�R���g���[���V�X�e��
 *
 *	@retval	TRUE	��
 *	@retval	FALSE	��
 *
 *
 */
//-----------------------------------------------------------------------------
//GLOBAL BOOL GetLightNight( LIGHT_CONT_PTR cont );
GLOBAL BOOL GetLightNight( void );

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif

