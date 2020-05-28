//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_obj_list_func.h
 *	@brief		��R�̃V�X�e�����g�p����I�u�W�F���X�g�p�֐���錾
 *	@author		tomoya takahashi
 *	@data		2005.09.30
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_OBJ_LIST_FUNC_H__
#define __IMC_OBJ_LIST_FUNC_H__

#include "include/application/imageClip/imc_obj_list.h"

#undef GLOBAL
#ifdef	__IMC_OBJ_LIST_FUNC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define IMC_OBJ_LIST_FUNC_TP_NOW	(0xffffffff)

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

//-----------------------------------------------------------------------------
/**
*	�A�N�Z�T���ƃ|�P�����I�u�W�F�̕\���D�揇�ʁA�����蔻��A���W�ύX
*	���s���֐�
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�\���D�揇�ʐݒ�
 *
 *	@param	work	�I�u�W�F���X�g���[�N
 *	@param	pri		�\���D�揇��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_Pri( IMC_OBJLIST* work, int pri );
//----------------------------------------------------------------------------
/**
 *
 *	@brief	�^�b�`�p�l�������蔻��
 *
 *	@param	work	�I�u�W�F���X�g���[�N
 *	@param	x		���肘���W	�i���̏�Ԃ����悤{sys}IMC_OBJ_LIST_FUNC_TP_NOW �j
 *	@param	y		���肙���W
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_OBJLIST_ACCEPOKE_Hit( IMC_OBJLIST* work, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�ׂ����^�b�`�p�l�������蔻��
 *
 *	@param	work	�I�u�W�F���X�g���[�N
 *	@param	offs_x	���ォ��̃I�t�Z�b�g�����W
 *	@param	offs_y	���ォ��̃I�t�Z�b�g�����W 
 *	@param	drawData �L�����N�^�f�[�^�e�[�u��
 *
 *	@retval	TRUE	��������
 *	@retval	FALSE	������Ȃ�����
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_OBJLIST_ACCEPOKE_HitEx( IMC_OBJLIST* work, int* offs_x, int* offs_y, NNSG2dCharacterData** drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W�ݒ�
 *
 *	@param	work	�I�u�W�F�N�g���X�g���[�N
 *	@param	x		�����W
 *	@param	y		�����W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_Mat( IMC_OBJLIST* work, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���W���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_MatGet( IMC_OBJLIST* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		���T�C�Y�i�[��
 *	@param	y		���T�C�Y�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_SizeGet( IMC_OBJLIST* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�H������ł悢�T�C�Y���擾
 *
 *	@param	obj		�I�u�W�F���[�N
 *	@param	x		���T�C�Y�i�[��
 *	@param	y		���T�C�Y�i�[��
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_InSizeGet( IMC_OBJLIST* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	���X�g���Ƒ����Z�ړ�������
 *	
 *	@param	top		���X�g�擪�|�C���^
 *	@param	x		����X���W
 *	@param	y		����Y���W
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_ACCEPOKE_ListMove( IMC_OBJLIST* top, int x, int y );


//----------------------------------------------------------------------------
/**
 *	@brief	�I�u�W�F�N�g��`�擾�@�H������ł悢�T�C�Y�����炵�ς�
 *	
 *	@param	p_obj	���[�N
 *	@param	top		��
 *	@param	bottom	��
 *	@param	left	��
 *	@param	right	�E
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_GetObjRectSubInSize( IMC_OBJLIST* p_obj, int* top, int* bottom, int* left, int* right );

//----------------------------------------------------------------------------
/**
 *	@brief	���S���W���擾����
 *
 *	@param	p_obj	�I�u�W�F�N�g
 *	@param	x		�����W�i�[��
 *	@param	y		�����W�i�[��
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_OBJLIST_GetObjCenterMat( IMC_OBJLIST* p_obj, int* x, int* y );
	

#undef	GLOBAL
#endif		// __IMC_OBJ_LIST_FUNC_H__

