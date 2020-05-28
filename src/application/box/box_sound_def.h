//============================================================================================
/**
 * @file	box_sound_def.h
 * @bfief	�{�b�N�X��ʃT�E���h�i���o�[��`
 * @author	taya
 * @date	06.02.15
 */
//============================================================================================

#ifndef __BOX_SOUND_DEF_H__
#define __BOX_SOUND_DEF_H__

#include "system\snd_tool.h"


#define  SOUND_LOG_IN			(SEQ_SE_DP_PC_LOGIN)	// �{�b�N�X��ʊJ�n
#define  SOUND_LOG_OFF			(SEQ_SE_DP_PC_LOGOFF)	// �{�b�N�X��ʏI��
#define  SOUND_MOVE_CURSOR		(SEQ_SE_DP_SELECT)		// �J�[�\���ړ�
#define  SOUND_DECIDE			(SEQ_SE_DP_DECIDE)		// ���艹
//#define  SOUND_DECIDE			(SEQ_SE_DP_BUTTON3)		// ���艹
#define  SOUND_CANCEL			(SEQ_SE_DP_DECIDE)		// �L�����Z����
#define  SOUND_CHANGE_TRAY		(SEQ_SE_DP_SELECT)		// �g���C�؂�ւ�
//#define  SOUND_CHANGE_TRAY		(SEQ_SE_DP_CLOSE2)		// �g���C�؂�ւ�
//#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_DECIDE)		// �莝���E�B���h�E���J��
//#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_OPEN2)		// �莝���E�B���h�E���J��
#define  SOUND_OPEN_PARTY_TRAY	(SEQ_SE_DP_OPEN7)		// �莝���E�B���h�E���J��
//#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_DECIDE)		// �莝���E�B���h�E�����
//#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_CLOSE2)		// �莝���E�B���h�E�����
#define  SOUND_CLOSE_PARTY_TRAY	(SEQ_SE_DP_CLOSE7)		// �莝���E�B���h�E�����


#define  SOUND_DISP_MENU		(SOUND_DECIDE)			// ���j���[���ڕ\��
#define  SOUND_SELECT_MENU		(SOUND_MOVE_CURSOR)		// ���j���[�I�����ڕύX

//#define  SOUND_SUB_BUTTON		(SOUND_DECIDE)			// �T�u��ʃ{�^��������
#define  SOUND_SUB_BUTTON		(SEQ_SE_DP_BUTTON9)		// �T�u��ʃ{�^��������

#define  SOUND_SUB_MOVE_ICON	(SOUND_MOVE_CURSOR)		// �T�u��ʃA�C�R���ړ���

//#define  SOUND_POKE_CATCH		(SEQ_SE_DP_SELECT)	// �|�P��������
#define  SOUND_POKE_CATCH		(SEQ_SE_DP_BOX02)	// �|�P��������

//#define  SOUND_POKE_PUT		(SEQ_SE_DP_SELECT)	// �|�P��������
#define  SOUND_POKE_PUT			(SEQ_SE_DP_BOX01)	// �|�P��������

#define  SOUND_POKE_SWAP		(SEQ_SE_DP_SELECT)	// �|�P��������ւ���


#define  SOUND_ITEM_WITHDRAW	(SOUND_DECIDE)		// �A�C�e����������
#define  SOUND_ITEM_SET			(SOUND_DECIDE)		// �A�C�e����������
#define  SOUND_ITEM_SWAP		(SOUND_DECIDE)		// �A�C�e���Ƃ肩����

//#define  SOUND_DISABLE_BUTTON	(SOUND_DECIDE)		// �����Ȃ��{�^�����������Ƃ�
#define  SOUND_DISABLE_BUTTON	(SEQ_SE_DP_BOX03)	// �����Ȃ��{�^�����������Ƃ�

#define  SOUND_WARNING			(SEQ_SE_DP_BOX03)	// �Ō�̂P�̂𓦂������Ƃ������Ȃǂ̌x����



#endif
