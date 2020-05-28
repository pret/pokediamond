//==============================================================================
/**
 * @file	battle_tcb_pri.h
 * @brief	�퓬��ʂœ��삷��TCB�̃v���C�I���e�B��`
 * @author	matsuda
 * @date	2005.09.29(��)
 */
//==============================================================================
#ifndef __BATTLE_TCB_PRI_H__
#define __BATTLE_TCB_PRI_H__


///FightUpdate(�A�N�^�[Update�����s���Ă���)	���C�����[�v�̍Ō�Ŏ��s
#define TCBPRI_FIGHT_UPDATE		(60000)

//�s���`SE�̃`�F�b�N
#define TCBPRI_PINCH_SE_CHECK	(50000)

///HP�Q�[�WIN ������^�X�N
#define TCBPRI_HP_GAUGE_IN_TASK	(990)
///HP�Q�[�WIN
#define TCBPRI_HP_GAUGE_IN		(1000)
///HP�Q�[�W�v�Z
#define TCBPRI_HP_GAUGE_CALC	(1000)
///HP�Q�[�WSin�J�[�u�G�t�F�N�g���s�^�X�N
#define TCBPRI_HP_GAUGE_SIN_CURVE	(1010)
///�I�𒆂̃|�P�����h��Sin�J�[�u�G�t�F�N�g���s�^�X�N
#define TCBPRI_HP_POKEYURE_SIN_CURVE	(1010)

///�{�[���G�t�F�N�g
#define TCBPRI_BALL_EFFECT		(1000)

///�w�i�؂�ւ�TCB
#define TCBPRI_HAIKEI_CHANGE	(1100)

///�T�E���h�R���g���[��TCB
#define TCBPRI_SE_CONTROL		(1100)

///�G�t�F�N�g�T�|�[�g�֐��pTCB
#define TCBPRI_WE_SUPPORT		(1100)

///�Q�[�W���x���A�b�v�G�t�F�N�g
#define TCBPRI_GAUGE_LEVELUP_EFF	(1000)

///�莝���Q�[�W�F��󓮍�
#define TCBPRI_TEMOTIGAUGE_ARROW	(500)
///�莝���Q�[�W�F�{�[������
#define TCBPRI_TEMOTIGAUGE_BALL		(TCBPRI_TEMOTIGAUGE_ARROW + 1)

#define TCBPRI_MSG_WIN_MOVE			( 1200 )

//--------------------------------------------------------------
//	�퓬���͉��
//--------------------------------------------------------------
///�퓬���͉�ʃv���C���[�w�i�X�N���[���G�t�F�N�gTCB
#define TCBPRI_BINPUT_PLAYER_SCROLL_EFFECT	(1200)
///�퓬���͉�ʁF�R�}���h�I���X�N���[���G�t�F�N�gTCB
#define TCBPRI_BINPUT_COMMAND_IN_EFFECT		(1210)

///�퓬���͉�ʃG�t�F�N�gTCB
#define TCBPRI_BINPUT_EFFECT	(1300)
///�퓬���͉�ʏ풓�J���[�G�t�F�N�gTCB
#define TCBPRI_BINPUT_DEF_COLOR_EFFECT	(1310)
///�퓬���͉�ʃJ���[�G�t�F�N�gTCB
#define TCBPRI_BINPUT_COLOR_EFFECT	(1320)

///�퓬���͉�ʁF���g�g��G�t�F�N�gTCB
#define TCBPRI_BINPUT_BLACK_WAKU_EFFECT	(1200)
///�퓬���͉�ʁF�w�i�t�F�[�hTCB
#define TCBPRI_BINPUT_BACKFADE			(3000)

///�퓬���͉�ʁF�J�[�\��OBJUpdate
#define TCBPRI_BCURSOR					(40000)

///�퓬���͉�ʁF�w�i�p���b�g�؂�ւ�
#define TCBPRI_BACKGROUND_PAL			(55000)

///�퓬���͉�ʁF�ߊl�f���p�w�J�[�\��
#define TCBPRI_FINGER					(999)


#endif	//__BATTLE_TCB_PRI_H__

