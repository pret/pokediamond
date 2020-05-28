//==============================================================================
/**
 * @file	dance_snd_def.h
 * @brief	�R���e�X�g�F�_���X����@SE��`�t�@�C��
 * @author	matsuda
 * @date	2006.03.01(��)
 */
//==============================================================================
#ifndef __DANCE_SND_DEF_H__
#define __DANCE_SND_DEF_H__

#include "system/snd_tool.h"


//--------------------------------------------------------------
/**
 * �f�o�b�O�pSE��Đ���`
 *
 * ���̒�`������ƁA�����Ă��Ă���SE�͍Đ�����܂���
 * ��check
 */
//--------------------------------------------------------------
//#define DEBUG_DANCE_SE_PLAY

//--------------------------------------------------------------
//
//--------------------------------------------------------------
///�J�[�\������
#define DSE_DECIDE			(SEQ_SE_DP_DECIDE)

///�I�[�v�j���O���̃��C�g��������SE
#define DSE_LIGHT_ON		(SEQ_SE_DP_CON_019)	// SE-DP-POKETCH-006

//--------------------------------------------------------------
//	PLAYER3
//--------------------------------------------------------------
///�_���X���傪�J�n�������̊���
#define DSE_START_SHOUT		(SEQ_SE_DP_CON_007)
///Finish�p�[�e�B�N�����o���Ƃ��̊���
#define DSE_FINISH_DANCE	(SEQ_SE_DP_CON_007)
///�_���X���傪�I���������̊���
#define DSE_END_SHOUT		(SEQ_SE_DP_CON_007)

//--------------------------------------------------------------
//	PLAYER4
//--------------------------------------------------------------
//��`�L���ŁA�|�P�����̓����ŉ�����
#define DEBUG_DANCE_SE_PLAY_POKE_MOVE

///�|�P�����_���X�A�j���F�ʏ�
//#define DSE_STEP_NORMAL	(SEQ_SE_DP_CON_027)	//SE-DP-POKELIST-001
//#define DSE_STEP_NORMAL		(SEQ_SE_DP_CON_027_2)	//SE-DP-POKELIST-001
#define DSE_STEP_NORMAL		(SEQ_SE_DP_CON_027_3)	//SE-DP-POKELIST-001

///�|�P�����_���X�A�j���F����
#define DSE_STEP_FINISH		(SEQ_SE_DP_CON_028)	//SE-DP-W030

//--------------------------------------------------------------
//	PLAYER1
//--------------------------------------------------------------
///�_���X�{�^���F�W�����v
#define DSE_BUTTON_JUMP		(SEQ_SE_DP_CON_009)

///�_���X�{�^���F�O�i
#define DSE_BUTTON_ADVANCE	(SEQ_SE_DP_CON_010)

///�_���X�{�^���F��
#define DSE_BUTTON_LEFT		(SEQ_SE_DP_CON_011)

///�_���X�{�^���F�E
#define DSE_BUTTON_RIGHT	(SEQ_SE_DP_CON_012)

//--------------------------------------------------------------
//	PLAYER2
//--------------------------------------------------------------
///Excellent1���
#define DSE_EXCELLENT_1		(SEQ_SE_DP_CON_021)	//SE-DP-KIRAKIRA3

///Excellent2���
#define DSE_EXCELLENT_2		(SEQ_SE_DP_CON_022)	//SE-DP-KIRAKIRA

///Excellent3���
#define DSE_EXCELLENT_3		(SEQ_SE_DP_CON_023)	//SE-DP-KIRAKIRA4

///Good
#define DSE_GOOD			(SEQ_SE_DP_CON_024)	//SE-DP-UG-004

///Failed
//#define DSE_FAILED		(SEQ_SE_DP_CON_025)	//SE-DP-CARD10
#define DSE_FAILED			(SEQ_SE_DP_CARD10)	//SE-DP-CARD10

///�Ⴄ�{�^���������Ă���
#define DSE_FAILED_BUTTON	(SEQ_SE_DP_CON_026)	//SE-DP-UG-003

//--------------------------------------------------------------
//
//--------------------------------------------------------------
///�����̃^�[���ɂȂ���
#define DSE_MY_TURN			(SEQ_SE_DP_CON_031)
///���[�e�[�V�����ɍ��킹��
#define DSE_ROTATION		(SEQ_SE_DP_CON_030)


#endif	//__DANCE_SND_DEF_H__
