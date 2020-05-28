//==============================================================================
/**
 * @file	dance_tcb_pri.h
 * @brief	�r�W���A�������TCB�v���C�I���e�B��`
 * @author	matsuda
 * @date	2005.12.10(�y)
 */
//==============================================================================
#ifndef __DANCE_TCB_PRI_H__
#define __DANCE_TCB_PRI_H__


///FightUpdate(�A�N�^�[Update�����s���Ă���)	���C�����[�v�̍Ō�Ŏ��s
#define TCBPRI_DANCE_UPDATE		(80000)

///���ߎ��s�T�u�^�X�N�̔ėp�v���C�I���e�B
#define TCBPRI_DANCE_ORDERSUB	(30000)

///AI���s�̃v���C�I���e�B(�ꉞ�v���C���[���������Ɏ��s������)
#define TCBPRI_DANCE_AI_CALC	(TCBPRI_DANCE_ORDERSUB + 10)
///�_���X�������̃p�����[�^���M�^�X�N�̃v���C�I���e�B
#define TCBPRI_DANCE_DANCING_PARAM_SEND		(TCBPRI_DANCE_ORDERSUB + 100)

///�|�P�����풓�A�j���[�V�������s�^�X�N�̃v���C�I���e�B
#define TCBPRI_DANCE_DEFANM				(TCBPRI_DANCE_ORDERSUB + 9000)
///�|�P�����_���X�A�j���[�V�������s�^�X�N�̃v���C�I���e�B
#define TCBPRI_DANCE_MOVE				(TCBPRI_DANCE_DEFANM + 10)

///�G�t�F�N�g�p�̊�{�v���C�I���e�B(�������͊�{�I�ɃV�X�e���n)
#define TCBPRI_DANCE_EFFECT_BASE_PRI	(TCBPRI_DANCE_ORDERSUB + 10000)

///���[�e�[�V�������̊e�u���[�_�[����^�X�N�̃v���C�I���e�B
#define TCBPRI_DANCE_ROTATION	(TCBPRI_DANCE_EFFECT_BASE_PRI + 100)
///�������w���J�[�\���̓���^�X�N�v���C�I���e�B
#define TCBPRI_DANCE_MY_CURSOR	(TCBPRI_DANCE_ROTATION + 10)

///�e�̓���v���C�I���e�B(�|�P�����̏풓�A�j���A���[�e�[�V����������ɐݒ�)
#define TCBPRI_DANCE_SHADOW		(TCBPRI_DANCE_ROTATION + 1000)

///�]���p�l���G�t�F�N�g�v���C�I���e�B
#define TCBPRI_DANCE_REVIEWPANEL	(TCBPRI_DANCE_EFFECT_BASE_PRI + 200)

///�v��������^�X�N
#define TCBPRI_PRIN_MAIN			(TCBPRI_DANCE_EFFECT_BASE_PRI + 15)


//--------------------------------------------------------------
//	�T�u���
//--------------------------------------------------------------
///���͉�ʃG�t�F�N�gTCB
#define TCBPRI_DINPUT_EFFECT	(1300)



#endif	//__DANCE_TCB_PRI_H__

