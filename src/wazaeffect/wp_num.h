//==============================================================================
/**
 * @file	wp_num.h
 * @brief	�Z�G�t�F�N�g�p�[�e�B�N���f�[�^�e�[�u���̃f�[�^�ԍ���`
 * @author	matsuda
 * @date	2005.07.22(��)
 */
//==============================================================================
#ifndef __WP_NUM_H__
#define __WP_NUM_H__


//==============================================================================
//	�G�~�b�^�������̃R�[���o�b�N�֐��̃|�C���^�e�[�u���̒�`�@��EmitterCallbackFunc�̕��тɍ��킹��
//==============================================================================
#define EMTFUNC_START			(0)

#define EMTFUNC_DUMMY					(0 + EMTFUNC_START)
#define EMTFUNC_CAMERA_REVERSE_ATTACK	(1 + EMTFUNC_DUMMY)
#define EMTFUNC_CAMERA_REVERSE_DEFENCE	(1 + EMTFUNC_CAMERA_REVERSE_ATTACK)
#define EMTFUNC_ATTACK_POS				(1 + EMTFUNC_CAMERA_REVERSE_DEFENCE)
#define EMTFUNC_DEFENCE_POS				(1 + EMTFUNC_ATTACK_POS)
#define EMTFUNC_AXIS_ATTACK				(1 + EMTFUNC_DEFENCE_POS)
#define EMTFUNC_AXIS_DEFENCE			(1 + EMTFUNC_AXIS_ATTACK)

#define EMTFUNC_AXIS_DEFAULT_CNV		(1 + EMTFUNC_AXIS_DEFENCE)
#define EMTFUNC_AXIS_CENTER_CNV			(1 + EMTFUNC_AXIS_DEFAULT_CNV)
#define EMTFUNC_AXIS_TP_CNV				(1 + EMTFUNC_AXIS_CENTER_CNV)
#define EMTFUNC_AXIS_PP_CNV				(1 + EMTFUNC_AXIS_TP_CNV)
#define EMTFUNC_AXIS_SET_CNV			(1 + EMTFUNC_AXIS_PP_CNV)

#define EMTFUNC_AXIS_DEFAULT_MAG		(1 + EMTFUNC_AXIS_SET_CNV)
#define EMTFUNC_AXIS_CENTER_MAG			(1 + EMTFUNC_AXIS_DEFAULT_MAG)
#define EMTFUNC_AXIS_TP_MAG				(1 + EMTFUNC_AXIS_CENTER_MAG)
#define EMTFUNC_AXIS_PP_MAG				(1 + EMTFUNC_AXIS_TP_MAG)
#define EMTFUNC_AXIS_SET_MAG			(1 + EMTFUNC_AXIS_PP_MAG)

#define EMTFUNC_FIELD_OPERATOR			(1 + EMTFUNC_AXIS_SET_MAG)			///< operator�֐�
#define EMTFUNC_SEP_POS					(1 + EMTFUNC_FIELD_OPERATOR)		///< Sep�p �� ���W
#define EMTFUNC_AT_SIDE					(1 + EMTFUNC_SEP_POS)				///< 2�ΑI��p
#define EMTFUNC_DF_SIDE					(1 + EMTFUNC_AT_SIDE)				///< 2�ΑI��p
#define EMTFUNC_ATTACK_POS_CR			(1 + EMTFUNC_DF_SIDE)				///< �J�������]���Ă�Ƃ�

#define EMTFUNC_DEBUG_START				(1 + EMTFUNC_DF_SIDE)
#define EMTFUNC_DEBUG					(EMTFUNC_DEBUG_START)

#endif	//__WP_NUM_H__


