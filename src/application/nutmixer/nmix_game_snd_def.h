//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_snd_def.h
 *	@brief		�܂��܂���
 *	@author		tomoya takahashi
 *	@data		2006.06.06
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_SND_DEF_H__
#define __NMIX_GAME_SND_DEF_H__

#include "system/snd_play.h"
#include "system/snd_tool.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_SND_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


// �X�[�v���
#define NMIXGAME_SE_SOOP_ROTA		(SEQ_SE_DP_NM01)			// �X�[�v��������
#define NMIXGAME_SE_SOOP_KOBORE		(SEQ_SE_DP_NM02)			// �X�[�v���ڂ�
#define NMIXGAME_SE_SOOP_KOGE		(SEQ_SE_DP_NM03)			// �X�[�v�����鉹

// �N���[�����
//#define NMIXGAME_SE_CREAM_ROTA	(SEQ_SE_DP_NM04)			// �N���[����������
#define NMIXGAME_SE_CREAM_ROTA		(SEQ_SE_DP_NM04_2)			// �N���[����������
#define NMIXGAME_SE_CREAM_KOBORE	(SEQ_SE_DP_NM05)			// �N���[�����ڂ�
#define NMIXGAME_SE_CREAM_KOGE		(SEQ_SE_DP_NM03)			// �N���[�������鉹

// ���ڂ���
//#define NMIXGAME_SE_SOBORO_ROTA	(SEQ_SE_DP_NM07)			// ���ڂ납������
#define NMIXGAME_SE_SOBORO_ROTA		(SEQ_SE_DP_NM07_2)			// ���ڂ납������
#define NMIXGAME_SE_SOBORO_KOGE		(SEQ_SE_DP_NM08)			// ���ڂ낱���鉹

// ���̑��̉�
#define NMIXGAME_SE_NUTS_SOOP_IN	(SEQ_SE_DP_NM09)			// �؂̎��X�[�v�C��
#define NMIXGAME_SE_COUNT_DOWN		(SEQ_SE_DP_NM10)			// �J�E���g�_�E��
#define NMIXGAME_SE_GAME_START		(SEQ_SE_DP_NM10_2)			// �J�n��
#define NMIXGAME_SE_GAME_KIRAKIRA	(SEQ_SE_DP_NM11)			// �L���L���G�t�F�N�g��
//#define NMIXGAME_SE_GAME_ROTAWAY_ON	(SEQ_SE_DP_NM12)		// ��]�����ύX��
#define NMIXGAME_SE_GAME_ROTAWAY_ON	(SEQ_SE_DP_NM12_2)			// ��]�����ύX��
#define NMIXGAME_SE_GAME_END		(SEQ_SE_DP_NM13)			// �I����
#define NMIXGAME_SE_GAME_RESULT_ON	(SEQ_SE_DP_NM14)			// ���ʕ\���e�L�X�g���o��Ƃ��ɏo����




#undef	GLOBAL
#endif		// __NMIX_GAME_SND_DEF_H__

