//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		renderer_pack.h
 *@brief	�����_���[�p�b�N�֐�
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 * �����_���̓R�[���o�b�N���g�p���Ă��邽�߁A�O���[�o���̈悪�K�v��
 * �Ȃ��Ă��Ă��܂��܂��B
 *
 * �K�v�ȃO���[�o���f�[�^��system/render_oam�ɂ܂Ƃ߂Ă���܂��B
 *�@�����_�����g�p����Ƃ��́Asystem/render_oam���g�p���Ă��������B
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __RENDERER_PACK_H__
#define __RENDERER_PACK_H__

#include "nnsys.h"

#undef GLOBAL
#ifdef	__RENDERER_PACK_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

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

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���[�g�p�������s���܂��B
 *
 *@param	p_renderer	�����_���[�̎��̂̃|�C���^
 *@param	Zoffs		Z�I�t�Z�b�g�̑���
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_InitRenderer(NNSG2dRendererInstance* p_renderer, fx32 Zoffs);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��������
 *
 *@param	pSurface		����������T�[�t�F�[�X�̎��̂̃|�C���^
 *@param	pRect			�T�[�t�F�[�X�̋�`
 *@param	OamSetFunc		OAM�ݒ�R�[���o�b�N�֐�				�쐬��i�@CallBackAddOamMain�@�����ɂ���܂��j
 *@param	AffineSetFunc	�A�t�B���s��ݒ�R�[���o�b�N�֐�	�쐬��i�@CallBackAddAffineMain�@�������ɂ���܂��j
 *@param	cullFunc		�J�����O�R�[���o�b�N�֐�
 *@param	type			�T�[�t�F�[�X�^�C�v
 *@param	pSetRenderer	���̃T�[�t�F�[�X��ݒ肷�郌���_���[�i�ݒ肵�Ȃ��Ƃ��́@NULL�j
 *
 *@return	none
 *
 * 
 * NNSG2dViewRect�\����
 *	typedef struct NNSG2dViewRect
	{
		NNSG2dFVec2            posTopLeft;      // ���̈� ����ʒu
		NNSG2dFVec2            sizeView;        // �r���[�̃T�C�Y
	}NNSG2dViewRect;
 *
 * NNSG2dFVec2�\����
	typedef struct NNSG2dFVec2
	{
		fx32     x;        
		fx32     y;
		
	}NNSG2dFVec2;
 * 
 *
 * �T�[�t�F�[�X�^�C�v
	typedef enum NNSG2dSurfaceType
	{
		NNS_G2D_SURFACETYPE_MAIN3D = 0x00,  // 3D �O���t�B�b�N�X�G���W��   ���g�p
		NNS_G2D_SURFACETYPE_MAIN2D = 0x01,  // 2D �O���t�B�b�N�X�G���W�� A ���g�p
		NNS_G2D_SURFACETYPE_SUB2D  = 0x02,  // 2D �O���t�B�b�N�X�G���W�� B ���g�p
		NNS_G2D_SURFACETYPE_MAX    = 0x03
		
	}NNSG2dSurfaceType;
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_InitSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dOamRegisterFunction OamSetFunc,
		NNSG2dAffineRegisterFunction AffineSetFunc,
		NNSG2dRndCellCullingFunction cullFunc,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer );

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�ɋ�`�f�[�^��ݒ肷��
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	pRect			�ݒ肷���`�f�[�^	
 *
 *@return	none
 *
 * NNSG2dViewRect�\����
 *	typedef struct NNSG2dViewRect
	{
		NNSG2dFVec2            posTopLeft;      // ���̈� ����ʒu
		NNSG2dFVec2            sizeView;        // �r���[�̃T�C�Y
	}NNSG2dViewRect;
 *
 * NNSG2dFVec2�\����
	typedef struct NNSG2dFVec2
	{
		fx32     x;        
		fx32     y;
		
	}NNSG2dFVec2;
 * 
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceRect(NNSG2dRenderSurface* pSurface,NNSG2dViewRect* pRect);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��OAM�̐ݒ�֐���ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	OamSetFunc		OAM�ݒ�֐�			�쐬��i�@CallBackAddOamMain�@�����ɂ���܂��j
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceOamSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dOamRegisterFunction OamSetFunc);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�ɃA�t�B���s��̐ݒ�֐���ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	AffineSetFunc		�A�t�B���s��ݒ�֐�		�쐬��i�@CallBackAddAffineMain�@�����ɂ���܂��j
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceAffineSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dAffineRegisterFunction AffineSetFunc);
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�ɃJ�����O�֐���ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	CullFunc		�J�����O�֐�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceCullingFunc(NNSG2dRenderSurface* pSurface, NNSG2dRndCellCullingFunction CullFunc);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�^�C�v��ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	type			�T�[�t�F�[�X�^�C�v
 *
 *@return	none
 *
	typedef enum NNSG2dSurfaceType
	{
		NNS_G2D_SURFACETYPE_MAIN3D = 0x00,  // 3D �O���t�B�b�N�X�G���W��   ���g�p
		NNS_G2D_SURFACETYPE_MAIN2D = 0x01,  // 2D �O���t�B�b�N�X�G���W�� A ���g�p
		NNS_G2D_SURFACETYPE_SUB2D  = 0x02,  // 2D �O���t�B�b�N�X�G���W�� B ���g�p
		NNS_G2D_SURFACETYPE_MAX    = 0x03
		
	}NNSG2dSurfaceType;
 *
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceType(NNSG2dRenderSurface* pSurface, NNSG2dSurfaceType type);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�������_���[�ɐݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	pSetRenderer	�ݒ肷�郌���_���[
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void RNDP_SetSurfaceRenderer(NNSG2dRenderSurface* pSurface, NNSG2dRendererInstance* pSetRenderer);


//-----------------------------------------------------------------------------
/**
 *@brief	�T�[�t�F�C�X���ɃZ�������邩���`�F�b�N���A�J�����O����
 *			�J�����O�̃R�[���o�b�N�֐��͋��ʂ�OK�Ȃ̂ō쐬
 *
 *@param	pCell�F����Ώۂ̃Z�����ւ̃|�C���^
 *@param	pMtx�F����Ώۂ̃Z���ɓK�p�������W�ϊ��s��
 *@param	pViewRect�F�o�͐�T�[�t�F�C�X�̕\����`
 *
 *@retval	�ΏۃZ����\������FTRUE
 *@retval	�ΏۃZ����\�����Ȃ��FFALSE
 *
 */
 //----------------------------------------------------------------------------
BOOL RNDP_CallBackCulling( const NNSG2dCellData* pCell, const MtxFx32* pMtx, const NNSG2dViewRect* pViewRect );


//-----------------------------------------------------------------------------
/**
*		�R�[���o�b�N�֐��쐬��
*/
//-----------------------------------------------------------------------------
#if 0
//	Oam Affine �o�^�֐��쐬��
//-----------------------------------------------------------------------------
/**
 *@brief				OAM��ǉ����邽�߂ɌĂ΂��R�[���o�b�N�֐�
 *
 *@param	pOam�F�ǉ����ׂ�OAM�ւ̃|�C���^
 *@param	affineIndex�F����OAM���g�p����Affine�C���f�b�N�X
 *@param	BOOL �F�{�pAffine���ǂ���
 *
 *@retval	�����FTRUE
 *@retval	���s�FFALSE
 *
 ----------------------------------------------------------------------------*/
// ���C����ʗp
static BOOL CallBackAddOamMain( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	// OAM�}�l�[�W���Ɉ����œn���Ă���OAM�f�[�^��o�^���܂��B
	
	return NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->MainMan, pOam, affineIndex );
										//			�����C����ʗpOAM�}�l�[�W��
}

// �T�u��ʗp
static BOOL CallBackAddOamSub( const GXOamAttr* pOam, u16 affineIndex, BOOL /*bDoubleAffine*/ )
{
	// OAM�}�l�[�W���Ɉ����œn���Ă���OAM�f�[�^��o�^���܂��B
    return NNS_G2dEntryOamManagerOamWithAffineIdx( &RendOam->SubMan, pOam, affineIndex );
										//			���T�u��ʗpOAM�}�l�[�W��
}

//-----------------------------------------------------------------------------
/**
 *@brief	Affine�p�����[�^��ǉ����邽�߂ɌĂ΂��֐��ł��B
 *
 *@param	mtx�F�ǉ����ׂ�Affine�ϊ��s��ւ̃|�C���^
 *
 *@return	�ǉ�����Affine�p�����[�^��Index
 *
 */
 //----------------------------------------------------------------------------
// ���C����ʗp
static u16 CallBackAddAffineMain( const MtxFx22* mtx )
{
	// OAM�}�l�[�W���Ɉ����œn���Ă����A�t�B���p�����[�^��o�^���܂��B
    return NNS_G2dEntryOamManagerAffine( &RendOam->MainMan, mtx );
}

// �T�u��ʗp
static u16 CallBackAddAffineSub( const MtxFx22* mtx )
{
	// OAM�}�l�[�W���Ɉ����œn���Ă����A�t�B���p�����[�^��o�^���܂��B
    return NNS_G2dEntryOamManagerAffine( &RendOam->SubMan, mtx );
}

#endif

#undef	GLOBAL
#endif		// __RENDERER_PACK_H__

