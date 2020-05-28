//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_acce_hand.h
 *	@brief		�C���[�W�N���b�v �A�N�Z�T���n���h �V�X�e��	
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ACCE_HAND_H__
#define __IMC_ACCE_HAND_H__

#include <nnsys.h>
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_hand.h"
#include "include/application/imageClip/imc_right_box.h"
#include "include/application/imageClip/imc_left_box.h"
#include "include/application/imageClip/imc_drawsys.h"
#include "include/application/imageClip/imc_subwin.h"

#undef GLOBAL
#ifdef	__IMC_ACCE_HAND_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�������ꏊ�萔
//	
//=====================================
enum{
	IMC_ACCE_HAND_FROM_LBOX,		// ���{�b�N�X
	IMC_ACCE_HAND_FROM_RBOX,		// �E�{�b�N�X
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
 *	@brief	�A�N�Z�T���n���h�쐬
 *
 *	@param	hand		�n���h�\����
 *	@param	rbox		�E�{�b�N�X�\����
 *	@param	lbox		���{�b�N�X�\����
 *	@param	drawData	�`��f�[�^�\����
 *	@param	subwin		�T�u�E�B���h�E�\����
 *	@param	poketouch	�|�P�����ɂӂ�邩�ǂ���
 *	
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_HAND_Init( IMC_HAND* hand, IMC_RIGHT_BOX* rbox, IMC_LEFT_BOX* lbox, IMC_DRAW_DATA* drawData, IMC_SUBWIN* subwin, BOOL poketouch );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	�A�N�Z�T���n���h�j��
 *
 *	@param	hand	�n���h�\����
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_HAND_Delete( IMC_HAND* hand );

#undef	GLOBAL
#endif		// __IMC_ACCE_HAND_H__

