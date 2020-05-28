//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		renderer_pack.c
 *@brief	�����_���[�p�b�N�֐�
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#define __RENDERER_PACK_H_GLOBAL
#include "renderer_pack.h"

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
void RNDP_InitRenderer(NNSG2dRendererInstance* p_renderer, fx32 Zoffs)
{
	NNS_G2dInitRenderer( p_renderer );
	// Z �I�t�Z�b�g�������w��
	NNS_G2dSetRendererSpriteZoffset( p_renderer, Zoffs );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��������
 *
 *@param	pSurface		����������T�[�t�F�[�X�̎��̂̃|�C���^
 *@param	pRect			�T�[�t�F�[�X�̋�`
 *@param	OamSetFunc		OAM�ݒ�R�[���o�b�N�֐�
 *@param	AffineSetFunc	�A�t�B���s��ݒ�R�[���o�b�N�֐�
 *@param	cullFunc		�J�����O�R�[���o�b�N�֐�
 *@param	type			�T�[�t�F�[�X�^�C�v
 *@param	pSetRenderer	���̃T�[�t�F�[�X��ݒ肷�郌���_���[�i�ݒ肵�Ȃ��Ƃ��́@NULL�j
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_InitSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dOamRegisterFunction OamSetFunc,
		NNSG2dAffineRegisterFunction AffineSetFunc,
		NNSG2dRndCellCullingFunction cullFunc,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer )
{
	NNS_G2dInitRenderSurface(pSurface);
	
	// ��`�ݒ�
	pSurface->viewRect = *pRect;

	// �R�[���o�b�N�֐�
	pSurface->pFuncOamRegister          = OamSetFunc;
	pSurface->pFuncOamAffineRegister    = AffineSetFunc;
	pSurface->pFuncVisibilityCulling    = cullFunc;

	// �\����
	pSurface->type                      = type;
	
	// �����_���[�ɐݒ�
	if(pSetRenderer){
	    NNS_G2dAddRendererTargetSurface( pSetRenderer, pSurface );
	}
}

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
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceRect(NNSG2dRenderSurface* pSurface, NNSG2dViewRect* pRect)
{
	pSurface->viewRect = *pRect;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��OAM�̐ݒ�֐���ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	OamSetFunc		OAM�ݒ�֐�
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceOamSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dOamRegisterFunction OamSetFunc)
{
	pSurface->pFuncOamRegister          = OamSetFunc;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X�ɃA�t�B���s��̐ݒ�֐���ݒ�
 *
 *@param	pSurface		�T�[�t�F�[�X
 *@param	AffineSetFunc		�A�t�B���s��ݒ�֐�
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceAffineSetFunc(NNSG2dRenderSurface* pSurface, NNSG2dAffineRegisterFunction AffineSetFunc)
{
	pSurface->pFuncOamAffineRegister    = AffineSetFunc;
}
	
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
void RNDP_SetSurfaceCullingFunc(NNSG2dRenderSurface* pSurface, NNSG2dRndCellCullingFunction CullFunc)
{
	pSurface->pFuncVisibilityCulling    = CullFunc;
}

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
 *
 */
//-----------------------------------------------------------------------------
void RNDP_SetSurfaceType(NNSG2dRenderSurface* pSurface, NNSG2dSurfaceType type)
{
	pSurface->type = type;
}

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
void RNDP_SetSurfaceRenderer(NNSG2dRenderSurface* pSurface, NNSG2dRendererInstance* pSetRenderer)
{
	NNS_G2dAddRendererTargetSurface( pSetRenderer, pSurface );
}

//-----------------------------------------------------------------------------
/**
 *@brief	�T�[�t�F�C�X���ɃZ�������邩���`�F�b�N���A�J�����O����
 *			�J�����O�͋��ʂ�OK�Ȃ̂ō쐬
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
BOOL RNDP_CallBackCulling( const NNSG2dCellData* pCell, const MtxFx32* pMtx, const NNSG2dViewRect* pViewRect )
{
	// �R���o�[�^�ɂ��v�Z���ꂽ���E�����a���擾����
	const NNSG2dCellBoundingRectS16* Rect = NNS_G2dGetCellBoundingRect( pCell );
    const fx32  R = NNS_G2dGetCellBoundingSphereR( pCell );

    // �Z���̕\���ʒu���_�����߂�
    const fx32  px = pMtx->_20 - pViewRect->posTopLeft.x;
    const fx32  py = pMtx->_21 - pViewRect->posTopLeft.y;

	// �Z����`
	fx32  minY; 
	fx32  maxY; 
	fx32  minX; 
	fx32  maxX; 
	fx32  work;


	// �Z���̋��E���������`�����߂�
	// �Z����`�ʒu�𒆐S�ʒu�ɂ����Ƃ�
	if( NNS_G2dCellHasBR( pCell ) == TRUE ){
		minY = Rect->minY << FX32_SHIFT;
		maxY = Rect->maxY << FX32_SHIFT;
		minX = Rect->minX << FX32_SHIFT;
		maxX = Rect->maxX << FX32_SHIFT;
	}else{
		minY = -R << FX32_SHIFT;
		maxY = R << FX32_SHIFT;
		minX = -R << FX32_SHIFT;
		maxX = R << FX32_SHIFT;
	}
	

	
	// ���W�v�Z�ōs��v�Z��̍��W�ɕϊ�
	minY = FX_Mul(minY, pMtx->_01) + FX_Mul(minY, pMtx->_11) + py;
	maxY = FX_Mul(maxY, pMtx->_01) + FX_Mul(maxY, pMtx->_11) + py;
	
	minX = FX_Mul(minX, pMtx->_00) + FX_Mul(minX, pMtx->_10) + px;
	maxX = FX_Mul(maxX, pMtx->_00) + FX_Mul(maxX, pMtx->_10) + px;

	// ���W���t�]���Ă���\��������̂Ń`�F�b�N
	if( maxY < minY ){
		work = maxY;
		maxY = minY;
		minY = work;
	}

	if( maxX < minX ){
		work = maxX;
		maxX = minX;
		minX = work;
	}

    if( (maxY > 0) && (minY < pViewRect->sizeView.y) ){
        if( (maxX > 0) && (minX < pViewRect->sizeView.x) ){
			return TRUE;
        }
    }
	
	return FALSE;
}
