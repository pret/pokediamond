//==============================================================================
/**
 * @file	res_tcb_pri.h
 * @brief	�R���e�X�g���ʔ��\��ʂ�TCB�v���C�I���e�B��`
 * @author	matsuda
 * @date	2006.03.17(��)
 */
//==============================================================================
#ifndef __RES_TCB_PRI_H__
#define __RES_TCB_PRI_H__


///FightUpdate(�A�N�^�[Update�����s���Ă���)	���C�����[�v�̍Ō�Ŏ��s
#define TCBPRI_CONRES_UPDATE		(80000)

///���ߎ��s�T�u�^�X�N�̔ėp�v���C�I���e�B
#define TCBPRI_CONRES_ORDERSUB	(30000)

///���ʔ��\��ʐ؂�ւ����̃v���C�I���e�B
#define TCBPRI_CONRES_RESULT_CHANGE		(1000)


///�G�t�F�N�g�p�̊�{�v���C�I���e�B(�������͊�{�I�ɃV�X�e���n)
#define TCBPRI_CONRES_EFFECT_BASE_PRI	(TCBPRI_CONRES_ORDERSUB + 10000)

///�E�B���h�E�@�\�̊J��������s�^�X�N
#define TCBPRI_CONRES_WNDOPEN		(TCBPRI_CONRES_EFFECT_BASE_PRI + 1000)

///�e��G�t�F�N�g�p�̔ėp�v���C�I���e�B
#define TCBPRI_CONRES_EFFECT		(50000)

///���ӂԂ������^�X�N�̃v���C�I���e�B
#define TCBPRI_CONRES_CONFETTI_SYS	(TCBPRI_CONRES_EFFECT + 10)
///���ӂԂ��A�N�^�[����^�X�N�̃v���C�I���e�B
#define TCBPRI_CONRES_CONFETTI_ACTOR	(TCBPRI_CONRES_CONFETTI_SYS + 1)

///�|�P�����A�C�R���A�j���X�V����
#define TCBPRI_POKEICON_UPDATE		(TCBPRI_CONRES_EFFECT + 1000)

///�t���b�V���G�t�F�N�g
#define TCBPRI_CONRES_FLASH_EFF		(TCBPRI_CONRES_EFFECT + 5000)


//--------------------------------------------------------------
//	�T�u���
//--------------------------------------------------------------



#endif	//__RES_TCB_PRI_H__

