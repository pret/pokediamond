//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_snd_def.h
 *	@brief		�T�E���h�萔	
 *	@author		tomoya takahashi
 *	@data		2005.10.24
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_SND_DEF_H__
#define __IMC_SND_DEF_H__

#include "system/snd_play.h"
#include "system/snd_tool.h"

#undef GLOBAL
#ifdef	__IMC_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_SELECT)			// �؂�ւ��{�^������������
//#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_TARARARAN)		// �؂�ւ��{�^������������
#define IMC_SE_RET_BUTTON_ON	(SEQ_SE_DP_MAZYO3)			// �؂�ւ��{�^������������

//#define IMC_SE_BG_CHANGE		(SEQ_SE_DP_SELECT)			// �w�i���ς�����Ƃ��̉�
#define IMC_SE_BG_CHANGE		(SEQ_SE_DP_SYARAAN)			// �w�i���ς�����Ƃ��̉�

//#define IMC_SE_BUTTON_ON		(SEQ_SE_DP_SELECT)			// �{�^������������
#define IMC_SE_BUTTON_ON		(SEQ_SE_DP_PASO)			// �{�^������������

//#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_SELECT)			// ���{�b�N�X�ŉ����I��������
//#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_DECIDE2)			// ���{�b�N�X�ŉ����I��������
#define IMC_SE_HAVE_SAMETHING	(SEQ_SE_DP_BOX02)			// ���{�b�N�X�ŉ����I��������

//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_SELECT)		// ���{�b�N�X�ŕ�������
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_PIKO2)		// ���{�b�N�X�ŕ�������
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_BUTTON3)		// ���{�b�N�X�ŕ�������
//#define IMC_SE_TAKE_OFF			(SEQ_SE_DP_DECIDE2)		// ���{�b�N�X�ŕ�������
#define IMC_SE_TAKE_OFF				(SEQ_SE_DP_BOX02)		// ���{�b�N�X�ŕ�������

//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_SELECT)		// �͈͂��ŃA�N�Z�T��������č��{�b�N�X�ɃA�N�Z�T�����߂�Ƃ��̉�
//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_DANSA9)		// �͈͂��ŃA�N�Z�T��������č��{�b�N�X�ɃA�N�Z�T�����߂�Ƃ��̉�
//#define IMC_SE_RET_LBOX			(SEQ_SE_DP_BEYON)		// �͈͂��ŃA�N�Z�T��������č��{�b�N�X�ɃA�N�Z�T�����߂�Ƃ��̉�
#define IMC_SE_RET_LBOX			(SEQ_SE_DP_HYUN2)			// �͈͂��ŃA�N�Z�T��������č��{�b�N�X�ɃA�N�Z�T�����߂�Ƃ��̉�

//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DENSI02)		// �E�{�b�N�X�ɂ������Ƃ�
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DENSI05)		// �E�{�b�N�X�ɂ������Ƃ�
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_PIKO)		// �E�{�b�N�X�ɂ������Ƃ�
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_BUTTON3)		// �E�{�b�N�X�ɂ������Ƃ�
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_DECIDE2)		// �E�{�b�N�X�ɂ������Ƃ�
//#define IMC_SE_ON_RBOX			(SEQ_SE_DP_IMC_001)		// �E�{�b�N�X�ɂ������Ƃ�
#define IMC_SE_ON_RBOX				(SEQ_SE_DP_BOX01)		// �E�{�b�N�X�ɂ������Ƃ�

//#define IMC_SE_BUTTON_ENDON		(SEQ_SE_DP_PASO)		// �I���{�^������������
#define IMC_SE_BUTTON_ENDON			(SEQ_SE_DP_PIRORIRO)	// �I���{�^������������

//����ʂ̋��ʁu�͂��A�������v�ɂȂ����̂Ŗ��g�p
//#define IMC_SE_RET_BUTTON_FINISH	(SEQ_SE_DP_TARARARAN)	// �ŏI�������������
#define IMC_SE_RET_BUTTON_FINISH	(SEQ_SE_DP_MAZYO)		// �ŏI�������������


/////////////////////////////////////
// �R���e�X�g
#define IMC_SE_CON_10COUNT			(SEQ_SE_DP_HYUN2)		// ���X�g�P�O�J�E���g
#define IMC_SE_CON_FINISH			(SEQ_SE_DP_MAZYO)		// �I�`���`

#define IMC_SE_CON_DOOR_CLOSE		(SEQ_SE_DP_CON_017)	// �h�A�܂艹
#define IMC_SE_CON_START			(SEQ_SE_DP_CON_016)		// �N���b�v�J�n��



#undef	GLOBAL
#endif		// __IMC_SND_DEF_H__

