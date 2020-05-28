//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		touch_subwindow.h
 *	@brief		�T�u��ʁ@�G���E�B���h�E�{�^���V�X�e��
 *	@author		tomoya takahashi
 *	@data		2006.03.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __TOUCH_SUBWINDOW_H__
#define __TOUCH_SUBWINDOW_H__

#include "include/gflib/bg_system.h"

#undef GLOBAL
#ifdef	__TOUCH_SUBWINDOW_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *	�y�������̒��ӎ����z
 *	
 *	VBlank���Ԓ���
 *		gflib/bg_system.h
 *		GLOBAL void GF_BGL_VBlankFunc( GF_BGL_INI * ini );
 *	���Ă�ł��������B	�X�N���[���]�����s���܂��B
 */
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�X�e������@�߂�l
//=====================================
enum{
	TOUCH_SW_RET_NORMAL,	// �����Ȃ�
	TOUCH_SW_RET_YES,		// �͂�
	TOUCH_SW_RET_NO,		// ������
	TOUCH_SW_RET_YES_TOUCH,	// �͂������ꂽ�u��
	TOUCH_SW_RET_NO_TOUCH,	// �����������ꂽ�u��
	TOUCH_SW_RET_NUM
};

// �p���b�g�]���T�C�Y
#define TOUCH_SW_USE_PLTT_NUM	(2)			// �p���b�g�{���P��
// �L�����N�^�f�[�^�T�C�Y
#define TOUCH_SW_USE_CHAR_NUM	(29*4)		// �L�����N�^�P��
// �X�N���[���T�C�Y
#define TOUCH_SW_USE_SCRN_X		(6)			// �L�����N�^�P��
#define TOUCH_SW_USE_SCRN_Y		(4)			// �L�����N�^�P��

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�X�e���������f�[�^
//=====================================
typedef struct {
	GF_BGL_INI* p_bgl;		// BGL�V�X�e�����[�N
	u32 bg_frame;			// BG�i���o�[
	u32 char_offs;			// �L�����N�^�]���I�t�Z�b�g (��׸��P�� 1/32byte)
	u32 pltt_offs;			// �p���b�g�]���I�t�Z�b�g�i��گ�1�{���P�� 1/32byte�j
	u8 x;					// x���W�i��׸��P�ʁj
	u8 y;					// y���W�i��׸��P�ʁj
} TOUCH_SW_PARAM;


//-------------------------------------
//	�V�X�e�����[�N
//=====================================
typedef struct _TOUCH_SW_SYS TOUCH_SW_SYS;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����[�N�쐬
 *	
 *	@param	heapid	�g�p�q�[�vID 
 *	
 *	@return	���[�N�|�C���^
 */
//-----------------------------------------------------------------------------
GLOBAL TOUCH_SW_SYS* TOUCH_SW_AllocWork( u32 heapid );

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����[�N�j��
 *	
 *	@param	p_touch_sw	�V�X�e�����[�N
 */
//-----------------------------------------------------------------------------
GLOBAL void TOUCH_SW_FreeWork( TOUCH_SW_SYS* p_touch_sw );

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e��������
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *	@param	cp_param	�V�X�e������f�[�^
 */
//-----------------------------------------------------------------------------
GLOBAL void TOUCH_SW_Init( TOUCH_SW_SYS* p_touch_sw, const TOUCH_SW_PARAM* cp_param );

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e�����C������
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *
 *	@retval	TOUCH_SW_RET_NORMAL	// �����Ȃ�
 *	@retval	TOUCH_SW_RET_YES	// �͂�
 *	@retval	TOUCH_SW_RET_NO		// ������
 *
 *	TOUCH_SW_MainMC�̂Ƃ��ȉ��̒l���A���Ă��܂��B(MC=Moment Check)
 *	@retval	TOUCH_SW_RET_YES_TOUCH	// �͂��������u��
 *	@retval	TOUCH_SW_RET_NO_TOUCH	// �������������u��
 *	
 */
//-----------------------------------------------------------------------------
GLOBAL u32 TOUCH_SW_Main( TOUCH_SW_SYS* p_touch_sw );
GLOBAL u32 TOUCH_SW_MainMC( TOUCH_SW_SYS* p_touch_sw );

//----------------------------------------------------------------------------
/**
 *	@brief	�V�X�e���f�[�^���Z�b�g	(Init�̑O�̏�Ԃɂ���@����Ȃ���������Ȃ�)
 *
 *	@param	p_touch_sw	�V�X�e�����[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void TOUCH_SW_Reset( TOUCH_SW_SYS* p_touch_sw );

#undef	GLOBAL
#endif		// __TOUCH_SUBWINDOW_H__

