//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		field_glb_state.h
 *@brief	�t�B�[���h�I�u�W�F�ɉe����^����f�[�^�S	
 *@author	tomoya takahashi
 *@data		2005.06.07
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __FIELD_GLB_STATE_H__
#define	__FIELD_GLB_STATE_H__

#include "nnsys.h"

#undef	GLOBAL
#ifdef	__FIELD_GLB_STATE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
//---------------------------
//	�O���[�o���X�e�[�g�ɔ��f�t���O
//
//	���𔽉f�����邩�̃t���O
//===========================
enum{
	GLST_LIGHTVEC_1		=1,
	GLST_LIGHTVEC_2		=1<<1,
	GLST_LIGHTVEC_3		=1<<2,
	GLST_LIGHTVEC_4		=1<<3,
	GLST_LIGHTCOL_1		=1<<4,
	GLST_LIGHTCOL_2		=1<<5,
	GLST_LIGHTCOL_3		=1<<6,
	GLST_LIGHTCOL_4		=1<<7,
	GLST_DIFF			=1<<8,
	GLST_AMB			=1<<9,
	GLST_SPEC			=1<<10,
	GLST_EMI			=1<<11,
	GLST_LIGHT_FLAG		=1<<12,
	GLST_POLYGON_MODE	=1<<13,
	GLST_CULL_MODE		=1<<14,
	GLST_POLYGON_ID		=1<<15,
	GLST_ALPHA			=1<<16,
	GLST_FOG			=1<<17,
	GLST_DEPTH_TEST		=1<<18,
	GLST_1DOT			=1<<19,
	GLST_FAR_CLIP		=1<<20,
	GLST_XLDEPTH_UPDATE	=1<<21,
	GLST_ALL			=1<<22
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
typedef struct _GLST_DATA*	GLST_DATA_PTR;		// ���C�g�E�}�e���A���̃O���[�o����ԕۑ��\���̃|�C���^


// ���A�v���P�[�V�����ł��̍\���̂��g�p�������Ȃ����̂ŁA�O�����J
// GLST_DATA_PTR�́A������ς���̂͑�ςȂ̂ŁA���̂܂܂ɂ��܂��B
//-------------------------------------
//	���C�g�E�}�e���A��
//	�O���[�o����ԕۑ��\����
//=====================================
typedef struct _GLST_DATA{
	// ���C�g
	VecFx16	lightVec[4];	// �x�N�g��
	GXRgb	Color[4];		// �F
	
	// �}�e���A���J���[
	GXRgb	Diff;		// �f�B�t���[�Y�F	(0:�� 1:�� 2:��	�e0�`31)
	GXRgb	Amb;		// �A���r�G���g�F
	GXRgb	Spec;		// �X�y�L�����[�F
	GXRgb	Emi;		// �G�~�b�V�����F
	BOOL IsSetVtxColor;	// �f�B�t���[�Y�F�𒸓_�J���[�Ɏg�p���邩
	BOOL IsShininess;	// ���ʔ��ˋP�x�e�[�u�����g�p���邩

	// �|���S���A�g���r���[�g
	int				LightFlag;			// ���C�g�t���O
	GXPolygonMode	polyMode;			// �|���S�����[�h
	GXCull			cullMode;			// �J�����O���[�h
	int				polygonID;			// �|���S��ID
	int				alpha;				// �A���t�@
	int				misc;				// ���̑��̃t���O
} GLST_DATA;



//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�ۑ��̈�̍쐬/�j��
//-------------------------------------
GLOBAL GLST_DATA_PTR GLST_Init(void);
GLOBAL void GLST_Delete(GLST_DATA_PTR* pGLST_Data);

//-------------------------------------
//	�ݒ�f�[�^�𔽉f
//-------------------------------------
GLOBAL void GLST_Reflect(GLST_DATA_PTR GLST_Data, int flag);								// �O���[�o���X�e�[�g�ɔ��f������
GLOBAL void GLST_ReflectMdl(GLST_DATA_PTR GLST_Data, NNSG3dResMdl* pMdl, int flag);			// ���f�����\�[�X�ɔ��f������

//-------------------------------------
//	�ݒ�f�[�^�擾
//-------------------------------------
GLOBAL void GLST_GetRGB(GXRgb dat, u8* r, u8* g, u8* b);			// GXRgb�̐F��ԗΐɕ���
//-- ���C�g --//
GLOBAL VecFx16 GLST_GetLightVector(GLST_DATA_PTR GLST_Data, int lightID);	// ���C�g�x�N�g��
GLOBAL GXRgb GLST_GetLightColor(GLST_DATA_PTR GLST_Data, int lightID);		// ���C�g�J���[

//-- �}�e���A�� --//
GLOBAL GXRgb GLST_GetMaterialDiff(GLST_DATA_PTR GLST_Data);					// �f�B�t���[�Y
GLOBAL BOOL GLST_GetMaterialDiffVtxColor(GLST_DATA_PTR GLST_Data);			// �f�B�t���[�Y�F�𒸓_�J���[�Ɏg�p���邩
GLOBAL GXRgb GLST_GetMaterialAmb(GLST_DATA_PTR GLST_Data);					// �A���r�G���g
GLOBAL GXRgb GLST_GetMaterialSpec(GLST_DATA_PTR GLST_Data);					// �X�y�L�����[
GLOBAL BOOL GLST_GetMaterialSpecShininess(GLST_DATA_PTR GLST_Data);			// ���ʔ��ˋP�x�e�[�u�����g�p���邩
GLOBAL GXRgb GLST_GetMaterialEmi(GLST_DATA_PTR GLST_Data);					// �G�~�b�V����

//-- ���f���A�g���r���[�g --//
GLOBAL int GLST_GetMdlLightFlag(GLST_DATA_PTR GLST_Data);			// ���C�g�t���O
GLOBAL GXPolygonMode GLST_GetMdlPolyMode(GLST_DATA_PTR GLST_Data);	// �|���S�����[�h
GLOBAL GXCull GLST_GetMdlCullMode(GLST_DATA_PTR GLST_Data);			// �J�����O���[�h
GLOBAL int GLST_GetMdlPolyID(GLST_DATA_PTR GLST_Data);				// �|���S��ID
GLOBAL int GLST_GetMdlAlpha(GLST_DATA_PTR GLST_Data);				// ���l
GLOBAL int GLST_GetMdlMisc(GLST_DATA_PTR GLST_Data);				// ���̑��̃t���O


//-------------------------------------
// �l��ݒ�
//-------------------------------------
//-- ���C�g --//
GLOBAL void GLST_LightVector(GLST_DATA_PTR GLST_Data, int lightID, fx16 x, fx16 y, fx16 z);	// ���C�g�x�N�g���Z�b�g
GLOBAL void GLST_LightColor(GLST_DATA_PTR GLST_Data, int lightID, GXRgb rgb);				// ���C�g�J���[�Z�b�g

//-- �}�e���A�� --//
GLOBAL void GLST_MaterialDiff(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsSetVtxColor, BOOL setDiffAmb);	// �f�B�t���[�Y
GLOBAL void GLST_MaterialAmb(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setDiffAmb);						// �A���r�G���g

GLOBAL void GLST_MaterialSpec(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL IsShininess, BOOL setSpecEmi);	// �X�y�L�����[
GLOBAL void GLST_MaterialEmi(GLST_DATA_PTR GLST_Data, GXRgb rgb, BOOL setSpecEmi);						// �G�~�b�V����

//-- ���f���A�g���r���[�g --//
GLOBAL void GLST_MdlLightFlag(GLST_DATA_PTR GLST_Data, int light, BOOL on_off, BOOL setPolyAttr);	// ���C�g�t���O
GLOBAL void GLST_MdlPolyMode(GLST_DATA_PTR GLST_Data, GXPolygonMode polyMode, BOOL setPolyAttr);	// �|���S�����[�h
GLOBAL void GLST_MdlCullMode(GLST_DATA_PTR GLST_Data, GXCull cullMode, BOOL setPolyAttr);			// �J�����O���[�h
GLOBAL void GLST_MdlPolyID(GLST_DATA_PTR GLST_Data, int polygonID, BOOL setPolyAttr);				// �|���S��ID
GLOBAL void GLST_MdlAlpha(GLST_DATA_PTR GLST_Data, int alpha, BOOL setPolyAttr);					// ���l
GLOBAL void GLST_MdlMisc(GLST_DATA_PTR GLST_Data, int flag, BOOL on_off, BOOL setPolyAttr);			// ���̑��̃t���O

//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

