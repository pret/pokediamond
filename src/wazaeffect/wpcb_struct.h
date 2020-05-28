//==============================================================================
/**
 * @file	wpcb_struct.h
 * @brief	��{�\���� wpcb_xxx.c �����Ainclude���Ă͂����Ȃ�
 * @author	goto
 * @date	2006.02.12(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef __WPCB_STRUCT_H__
#define __WPCB_STRUCT_H__

#include "we_sys.h"

// -----------------------------------------
//
//	�� ���[�h��
//
// -----------------------------------------
enum ECB_OPERATOR_MODE {
	
	ECB_MODE_PRI	= 0,	///< �D��x
	ECB_MODE_TARGET,		///< �Ώ�
	ECB_MODE_POS,			///< ���W
	ECB_MODE_AXIS,			///< ������
	ECB_MODE_FIELD,			///< �t�B�[���h
	ECB_MODE_CAMERA,		///< �J����
	
	ECB_MODE_MAX,
	ECB_MODE_NUM = ECB_MODE_MAX,

};


//------------------------------------------
/**
 *
 * @brief	operator�\����
 *
 */
//------------------------------------------
typedef struct {
	
	WE_SYS_PTR	wsp;				///< we_sys
	PTC_PTR		ptc;				///< ptc
	s8	reverce_flag;				///< ���]�t���O
	int mode[ ECB_MODE_NUM ];		///< mode
	int s_client;					///< �J�n�N���C�A���g
	int e_client;					///< �I���N���C�A���g
	
	VecFx32		pos;				///< ���ۂ̍��W
	
} ECB_OPERATOR_DATA;

#endif

