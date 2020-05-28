//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		render_oam.h
 *@brief	�����_���[�p�O���[�o��OAM�}�l�[�W���V�X�e��
 *@author	tomoya takahashi
 *@data		2005.09.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __RENDER_OAM_H__
#define __RENDER_OAM_H__

#include "renderer_pack.h"

#undef GLOBAL
#ifdef	__RENDER_OAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
enum{
	REND_OAM_MAIN,
	REND_OAM_SUB,
};

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
 *@brief	�����_�����g��OAM�}�l�[�W���̍쐬
 *
 *@param	mainOamStart		���C��OAM�Ǘ��J�n�ԍ�
 *@param	mainOamNum			���C��OAM�Ǘ���
 *@param	mainAffineStart		���C���A�t�B���Ǘ��J�n�ԍ�
 *@param	mainAffineNum		���C���A�t�B���Ǘ���
 *@param	subOamStart			�T�uOAM�Ǘ��J�n�ԍ�
 *@param	subOamNum			�T�uOAM�Ǘ���
 *@param	subAffineStart		�T�u�A�t�B���Ǘ��J�n�ԍ�
 *@param	subAffineNum		�T�u�A�t�B���Ǘ���
 *@param	heap				�g�p�q�[�v
 *
 *@return	none
 *
 * �����ō쐬���ꂽOAM�}�l�[�W�����F�Ŏg�p���鎖�ɂȂ�܂��B
 *
 * ���C���ʂ�0�`4��ʐM�A�C�R�����g�p���邽�߁@
 * �������Ȃ��Ă��f�t�H���g�ŒʐM�p�Ɋm�ۂ��܂�
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void	REND_OAMInit(int mainOamStart, int mainOamNum, int mainAffineStart, int mainAffineNum,  int subOamStart, int subOamNum, int subAffineStart, int subAffineNum, int heap);



//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���p�̃O���[�o��OAM�}�l�[�W���f�[�^��j��
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_Delete(void);


//----------------------------------------------------------------------------
/**
 *
 *@brief	�T�[�t�F�[�X��������
 *
 *@param	pSurface		����������T�[�t�F�[�X�̎��̂̃|�C���^
 *@param	pRect			�T�[�t�F�[�X�̋�`
 *@param	type			�T�[�t�F�[�X�^�C�v
 *@param	pSetRenderer	���̃T�[�t�F�[�X��ݒ肷�郌���_���[�i�ݒ肵�Ȃ��Ƃ��́@NULL�j
 *
 *@return	none
 *
 * �����_�����g�p����Ƃ��͂��̊֐��ŃT�[�t�F�[�X������������
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_SetSurface(NNSG2dRenderSurface* pSurface,
		NNSG2dViewRect* pRect,
		NNSG2dSurfaceType type,
		NNSG2dRendererInstance* pSetRenderer);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_�����g�p����OAM�}�l�[�W����OAM�]�����s���܂��B
 *
 *@param	none
 *
 *@return	none
 *
 * �S�̂łP��s�������ő��v�ł��B
 * ���̊֐����P�t���[���ŕ�����ĂԂƐ���ɕ\������܂���B
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAMTrans(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	�����_���p�̃O���[�o��OAM�}�l�[�W���f�[�^���쐬�ς݂��`�F�b�N
 *
 *@param	none
 *
 *@retval	TURE		�쐬����Ă���
 *@retval	FALSE		�쐬����Ă��Ȃ�
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL REND_OAM_Live(void);

//----------------------------------------------------------------------------
/**
 *	@brief	OAM�}�l�[�W���C���X�^���X�擾
 *
 *	@param	flag	���C����ʗp���T�u��ʗp��
 *
 *	@return	OAM�}�l�[�W���[�C���X�^���X
 *
 * flag
	REND_OAM_MAIN,		// ���C�����
	REND_OAM_SUB,		// �T�u���
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dOamManagerInstance* REND_OAM_GetOamManagerInstance( int flag );


//-----------------------------------------------------------------------------
/**
 *		OAM�}�l�[�W�����g�p���Ȃ����A�ėp�I�Ɏg�p�ł���֐�
 */
//-----------------------------------------------------------------------------
GLOBAL void REND_OAM_UtilOamRamClear_Main( int heap );
GLOBAL void REND_OAM_UtilOamRamClear_Sub( int heap );


#undef	GLOBAL
#endif		// __RENDER_OAM_H__

