//==============================================================================
/**
 * @file	wpcb_common.h
 * @brief	�ȒP�Ȑ���������
 * @author	goto
 * @date	2006.02.12(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================
#ifndef __WPCB_COMMON_H__
#define __WPCB_COMMON_H__

//--------------------------------------------------------------
/**
 *
 * @brief	wpcb_xxx.c �� include ����ׂ��w�b�_�[�Q
 *
 */
//--------------------------------------------------------------
#include "wpcb_struct.h"
#include "wpcb_def.h"
#include "wpcb.h"

// -----------------------------------------
//
//	���f�o�b�O��` [ �錾���ɗL�� ]
//
// -----------------------------------------
#ifdef PM_DEBUG

#define WPCB_FLD_POS_MESSAGE		///< �t�B�[���h�ƍ��W��\������

#define WPCB_AXIS_POS_MSG			///< �������ʒu�̕\��
#define WPCB_AXIS_CLIENT_TYPE_MSG	///< �N���C�A���g�^�C�v�\��

#define WPCB_NONE_DATA_MSG			///< ���������b�Z�[�W

#endif

#endif

