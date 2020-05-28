//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		smptm_statuseffect.h
 *	@brief		�T���v�� �X�e�[�^�X �G�t�F�N�g
 *	@author		tomoya takahashi
 *	@data		2005.12.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __SMPTM_STATUSEFFECT_H__
#define __SMPTM_STATUSEFFECT_H__

#include "system/clact_tool.h"
#include "system/softsprite.h"

#undef GLOBAL
#ifdef	__SMPTM_STATUSEFFECT_H_GLOBAL
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
// �K�v��GRAPHICS�f�[�^
typedef struct{
	SOFT_SPRITE*		ss;
	CATS_SYS_PTR		csp;
	PALETTE_FADE_PTR	pfd;
} SMPTM_GRAPHIC_PARAM;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�X�e�[�^�X�@�G�t�F�N�g�@�J�n
 *
 *	@param	status			�X�e�[�^�X
 *	@param	client_type		�N���C�A���g�^�C�v
 *	@param	p_end			�I���`�F�b�N�t���O
 *	@param	gra				�O���t�B�b�N�p�����[�^
 *	@param	heap			�g�p�q�[�v
 *
 *	@return	none
 *
 * status
 *		STATUS_NORMAL	(0)		//��Ԉُ�Ȃ�
 * 		STATUS_NEMURI	(1)		//����
 *		STATUS_DOKU		(2)		//��
 *		STATUS_YAKEDO	(3)		//�₯��
 * 		STATUS_KOORI	(4)		//������
 *		STATUS_MAHI		(5)		//�܂�
 *
 * p_end
 *		TRUE	�I��
 *		FALSE	�G�t�F�N�g��
 */
//-----------------------------------------------------------------------------
GLOBAL void STATUSEFF_SampStart( int status, int client_type, BOOL* p_end, const SMPTM_GRAPHIC_PARAM* cp_gra, int heap );

#if 0
// �f�o�b�O
GLOBAL void Debug_SmpTm( WE_SYS_PTR we_sys );
#endif

#undef	GLOBAL
#endif		// __SMPTM_STATUSEFFECT_H__
