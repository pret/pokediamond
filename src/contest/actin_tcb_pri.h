//==============================================================================
/**
 * @file	actin_tcb_pri.h
 * @brief	���Z�����TCB�v���C�I���e�B��`
 * @author	matsuda
 * @date	2005.11.16(��)
 */
//==============================================================================
#ifndef __ACTIN_TCB_PRI_H__
#define __ACTIN_TCB_PRI_H__


///FightUpdate(�A�N�^�[Update�����s���Ă���)	���C�����[�v�̍Ō�Ŏ��s
#define TCBPRI_ACTIN_UPDATE		(60000)

///�Z�G�t�F�N�g���s�^�X�N
#define TCBPRI_ACTIN_WAZAEFF	(5)

///���ߎ��s�T�u�^�X�N�̔ėp�v���C�I���e�B
#define TCBPRI_ACTIN_ORDERSUB	(30000)
///�e��G�t�F�N�g�̔ėp�v���C�I���e�B
#define TCBPRI_ACTIN_EFFECT		(40000)

///�Z�I�����s�^�X�N
#define TCBPRI_ACTIN_WAZASELECT	(100)

///��b�E�B���h�E�X�N���[���^�X�N
#define TCBPRI_ACTIN_TALKWIN_SLIDE	(1000)
///�u���[�_�[�p�l�����G�t�F�N�g�^�X�N
#define TCBPRI_ACTIN_BRDPANEL_ALPHA	(1000)
///�u���[�_�[�p�l�����G�t�F�N�g�FV�u�����N�]���^�X�N
#define TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK	(10)

///�ϋqBG�A�j���^�X�N
#define TCBPRI_ACTIN_AUDIENCE_ANIME		(3000)

///�u���[�_�[�p�l���t���b�V���G�t�F�N�g
#define TCBPRI_ACTIN_BRDPANEL_FLASH		(TCBPRI_ACTIN_EFFECT + 100)


//--------------------------------------------------------------
//	�T�u���
//--------------------------------------------------------------
///���͉�ʃG�t�F�N�gTCB
#define TCBPRI_AINPUT_EFFECT	(1300)
///���͉�ʃJ���[�G�t�F�N�gTCB
#define TCBPRI_AINPUT_COLOR_EFFECT	(1320)



#endif	//__ACTIN_TCB_PRI_H__

