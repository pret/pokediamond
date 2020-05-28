//==============================================================================
/**
 * @file	actin_snd_def.h
 * @brief	�R���e�X�g�F�r�W���A������@SE��`�t�@�C��
 * @author	matsuda
 * @date	2006.03.01(��)
 */
//==============================================================================
#ifndef __ACTIN_SND_DEF_H__
#define __ACTIN_SND_DEF_H__

#include "system/snd_tool.h"


///�J�[�\������
#define ASE_DECIDE			(SEQ_SE_DP_DECIDE)
///���͉�ʃJ�[�\���ړ���
#define ASE_CCURSOR_MOVE_SE			(SEQ_SE_DP_SELECT)

///�{���e�[�W�㏸SE
#define ASE_VOLTAGE_UP		(SEQ_SE_DP_CON_002)	//(SEQ_SE_DP_CON_006)
///�{���e�[�W���~SE
#define ASE_VOLTAGE_DOWN		(SEQ_SE_DP_CON_001)	//(SEQ_SE_DP_CON_005)
///AP�㏸SE
#define ASE_AP_UP			(SEQ_SE_DP_CON_003)	//(SEQ_SE_DP_CON_004)
///���A�C�R����\��t��������SE
#define ASE_NEXTICON			(SEQ_SE_DP_CON_004)
///�ϋq����オ�莞��SE
#define ASE_AUDIENCE			(SEQ_SE_DP_CON_007)

//�R�����A�N�V�����A�C�R���_�����ɂȂ�SE�F�w��
#define ASE_ICON_NOMINATION		(SEQ_SE_DP_CON_003)
//�R�����A�N�V�����A�C�R���_�����ɂȂ�SE�F���
#define ASE_ICON_WEAR			(SEQ_SE_DP_CON_001)
//�R�����A�N�V�����A�C�R���_�����ɂȂ�SE�F�{���e�[�W
#define ASE_ICON_VOLTAGE		(SEQ_SE_DP_DECIDE)
//�R�����A�N�V�����A�C�R���_�����ɂȂ�SE�F�{���e�[�WMAX
#define ASE_ICON_VOLTAGE_MAX	(SEQ_SE_DP_DECIDE)

///�R�����̐R���̔������F+0
#define ASE_JUDGE_SUFFER_FAILED		(SEQ_SE_DP_CON_001)
///�R�����̐R���̔������F+1
#define ASE_JUDGE_SUFFER_SMALL		(SEQ_SE_DP_CON_021)
///�R�����̐R���̔������F+2
#define ASE_JUDGE_SUFFER_MIDDLE		(SEQ_SE_DP_CON_022)
///�R�����̐R���̔������F+3
#define ASE_JUDGE_SUFFER_BIG		(SEQ_SE_DP_CON_023)

///AP�n�[�g���p�l���Ɉ��ݍ��܂�鎞�̉�
#define ASE_APHEART_PANEL_IN	(SEQ_SE_DP_SELECT5)
///�{���e�[�W���p�l���Ɉ��ݍ��܂�鎞�̉�
#define ASE_VOLTAGE_PANEL_IN	(SEQ_SE_DP_SELECT5)
///�{���e�[�WMAX�ŃG�t�F�N�g�N�����R���{�b�N�X���灙���o�Ă��鎞�ɖ炷��
#define ASE_VOLTAGE_EFF_START	(SEQ_SE_DP_W234)
///���~���������{���e�[�W���p�l���ɒ��i���Ĕ��ł������ɖ炷��
#define ASE_VOLTAGE_STRAIGHT_MOVE	(SEQ_SE_DP_CON_013)

///�ŏI�^�[����m�点�鉹
#define ASE_FINAL_TURN			(SEQ_SE_DP_CON_029)
///�����̃|�P�������o��
#define ASE_MY_POKEMON			(SEQ_SE_DP_CON_031)
///�R���́u�����܂Ł[�I�v�̎�
#define ASE_ACTIN_STOP			(SEQ_SE_DP_CON_032)


#endif	//__ACTIN_SND_DEF_H__
