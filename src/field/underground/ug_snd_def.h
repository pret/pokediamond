//=============================================================================
/**
 * @file	ug_snd_def.h
 * @brief	�n���p�T�E���h��`�u�������t�@�C��
 * @author	Katsumi Ohno
 * @date    2006.3.28
 */
//=============================================================================

#ifndef __UG_SND_DEF_H__
#define __UG_SND_DEF_H__

#include "system/snd_tool.h"


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define UG_SE_HOLE_IN			(SEQ_SE_DP_KAIDAN2)		// ���ɓ�����
#define UG_SE_CLOSE_DOOR		(SEQ_SE_DP_DOOR)		// �h�A��߂�
//#define UG_SE_RADAR_USE		(SEQ_SE_DP_UG_006)		// ���[�_�[�g���Ă��鎞 ???�łĂȂ����H
#define UG_SE_SMOG_ANIM			(SEQ_SE_DP_UG_008)		// �����o����

//-----------------------------------------------------------------------------
//	���Ό@��
//-----------------------------------------------------------------------------
#define UG_SE_PICK				(SEQ_SE_DP_UG_002)		//�s�b�P��������
#define UG_SE_HUMMER			(SEQ_SE_DP_UG_003)		//�n���}�[������
#define UG_SE_HARD_ROCK			(SEQ_SE_DP_UG_004)		//�d���΂�����
#define UG_SE_FIND_FOSSIL		(SEQ_SE_DP_KIRAKIRA3)	//���Ό���

//#define UG_SE_DIG_FOSSIL		(SEQ_SE_DP_KIRAKIRA)	//���Ί��S�Ɍ���
#define UG_SE_DIG_FOSSIL		(SEQ_SE_DP_KIRAKIRA4)	//���Ί��S�Ɍ���

#define UG_SE_BLOKEN_WALL		(SEQ_SE_DP_UG_001)		//�ǉ��
#define UG_SE_TOUCH_BUTTON		(SEQ_SE_DP_SELECT)		//�s�b�P���A�n���}�[�؂�ւ��{�^��

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#define UG_SE_RADAR				(SEQ_SE_DP_UG_005)		//���[�_�[
#define UG_SE_RADAR_ECHO		(SEQ_SE_DP_UG_006)		//�G�R�[
#define UG_SE_SMOKE				(SEQ_SE_DP_UG_008)		//���A㩂��d�|����
#define UG_SE_ALARM				(SEQ_SE_DP_UG_007)		//�A���[��
#define UG_SE_DRILL				(SEQ_SE_DP_DORIRU)		//�h����

#define UG_SE_BURY				(SEQ_SE_DP_SUTYA)		// ���̂𖄂߂���

//#define UG_SE_FLAG_DELIVERY	(SEQ_SE_DP_UG_020)		// �n�^���^��
#define UG_SE_FLAG_DELIVERY		(SEQ_SE_DP_UG_027)		// �n�^���^��

#define UG_SE_FLAG_CONQUER		(SEQ_SE_DP_UG_021)		// �͂��D����  �{�@�Ƃ肩������
#define UG_SE_FLAG_STEAL		(SEQ_SE_DP_CARD10)		// �͂��D��ꂽ

#define UGT_SE_BUBBLE			(SEQ_SE_DP_UG_022)		// ����
#define UGT_SE_HUMMER			(SEQ_SE_DP_UG_023)		// ���킱�킵
#define UGT_SE_BLOKEN			(SEQ_SE_DP_UG_026)		// ���킱��ꂽ
#define UGT_SE_SMOG				(SEQ_SE_DP_UG_025)		// ���ނ�ӂ�
#define UGT_SE_FIER				(SEQ_SE_DP_UG_024)		// �΂��h��Ă���
#define UGT_SE_TRAPEND			(SEQ_SE_DP_WIN_OPEN2)	// 㩉���

//-----------------------------------------------------------------------------
//	ME
//-----------------------------------------------------------------------------
#define UG_SE_FANFA				(SEQ_SE_DP_PIRORIRO2)   // �n���̋��ʃt�@���t�@�[��
#define UG_SE_FIND				(UG_SE_FANFA)			// ������������(ME)
#define UG_SE_SEND_GOODS		(UG_SE_FANFA)			// ������������(ME)
#define UG_SE_LEVELUP_FLAG		(UG_SE_FANFA)			// �t�@���t�@�[��
#define UG_SE_FOSSIL_CLEAR		(UG_SE_FANFA)            // �S���@��o����


#endif  //__UG_SND_DEF_H__
