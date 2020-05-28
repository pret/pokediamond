//============================================================================================
/**
 * @file	poketch_sound.h
 * @bfief	�|�P�b�`�iSE�w��j�w�b�_
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef __POKETCH_SOUND_H__
#define __POKETCH_SOUND_H__


#include "system\snd_tool.h"

enum {
// ��{����
	POKETCH_SE_BUTTON_PUSH		= SEQ_SE_DP_DENSI01,		// �\�t�g�؂�ւ�
	POKETCH_SE_BEEP				= SEQ_SE_DP_BEEP,			// ���b�N��

	//POKETCH_SE_BUTTON_ROCK	= SEQ_SE_DP_POKETCH_005,	// ���b�N���\�t�g�؂�ւ�
	//POKETCH_SE_BUTTON_ROCK	= SEQ_SE_DP_BEEP,			// ���b�N���\�t�g�؂�ւ�
	POKETCH_SE_BUTTON_ROCK		= SEQ_SE_DP_DENSI04,		// ���b�N���\�t�g�؂�ւ�

// ������
	POKETCH_SE_MEMO_BUTTON		= SEQ_SE_DP_POKETCH_003,	// �{�^��������

// �d��
	POKETCH_SE_CALC_BUTTON		= SEQ_SE_DP_POKETCH_003,	// �{�^��������

// �J�E���^�[
	//POKETCH_SE_COUNTER_BUTTON	= SEQ_SE_DP_POKETCH_003,	// �{�^��������
	POKETCH_SE_COUNTER_BUTTON	= SEQ_SE_DP_POKETCH_010,	// �{�^��������

// �����v
	//POKETCH_SE_PEDOMETER_BUTTON = SEQ_SE_DP_POKETCH_003,	// �{�^��������
	POKETCH_SE_PEDOMETER_BUTTON = SEQ_SE_DP_POKETCH_010,	// �{�^��������

// �R�C���g�X
	POKETCH_SE_COINTOSS_START	= SEQ_SE_DP_DENSI09,		// �R�C���͂�����
	POKETCH_SE_COINTOSS_BOUND	= SEQ_SE_DP_DENSI10,		// �R�C���o�E���h����

// �킴�����`�F�b�J�[
	POKETCH_SE_AISYOU_BUTTON	= SEQ_SE_DP_POKETCH_003,	// �{�^��������

// �A���[�����v
	POKETCH_SE_ALARM_BUTTON		= SEQ_SE_DP_POKETCH_003,	// �{�^��������
	POKETCH_SE_ALARM_BUTTON_DISABLE = SEQ_SE_DP_BEEP,		// �����ȃ{�^��������

// �L�b�`���^�C�}�[
	POKETCH_SE_KITCHEN_BUTTON	= SEQ_SE_DP_POKETCH_003,	// �{�^��������
	POKETCH_SE_KITCHEN_BUTTON_DISABLE = SEQ_SE_DP_BEEP,		// �����ȃ{�^��������
	POKETCH_SE_KITCHEN_POKO		= SEQ_SE_DP_DENSI11,		// �J�r�S�����|�R�|�R��������

// �J���[�`�F���W���[
	POKETCH_SE_CHANGER_CHANGE	= SEQ_SE_DP_POKETCH_003,	// �F�ς���

// ������T�[�`���[
	POKETCH_SE_TUSIN_SWITCH_MODE = SEQ_SE_DP_POKETCH_003,	// ��ʐ؂�ւ��i�ʏ�j
	POKETCH_SE_TUSIN_SWITCH_MODE_ERR = SEQ_SE_DP_BEEP,		// ��ʐ؂�ւ��i�G���[�j

// �X�g�b�v�E�H�b�`
	//POKETCH_SE_STOPWATCH_PUSH = SEQ_SE_DP_POKETCH_007,
	POKETCH_SE_STOPWATCH_PUSH = SEQ_SE_DP_POKETCH_010,
	//POKETCH_SE_STOPWATCH_RESET = SEQ_SE_DP_POKETCH_007,
	POKETCH_SE_STOPWATCH_RESET	= SEQ_SE_DP_POKETCH_010,
	POKETCH_SE_STOPWATCH_BOMB	= SEQ_SE_DP_POKETCH_006,

// �����Ă�J����
	POKETCH_SE_SODATE_UPDATE	= SEQ_SE_DP_DENSI12,		// ��ʍX�V

// ���[���b�g
	POKETCH_SE_ROULETTE_BUTTON = SEQ_SE_DP_POKETCH_003,		// �{�^��������
	//POKETCH_SE_ROULETTE_BUTTON	= SEQ_SE_DP_POKETCH_010,// �{�^��������
	POKETCH_SE_ROULETTE_BUTTON_DISABLE = SEQ_SE_DP_BEEP,	// �����ȃ{�^��������
	//POKETCH_SE_ROULETTE_STOP = SEQ_SE_DP_POKETCH_007,		// ���[���b�g�~�܂���
	POKETCH_SE_ROULETTE_STOP	= SEQ_SE_DP_POKETCH_011,	// ���[���b�g�~�܂���

// �g���[�i�[�����`���[
	POKETCH_SE_TRANER_BUTTON	= SEQ_SE_DP_POKETCH_003,	// �{�^��������
	POKETCH_SE_TRANER_BUTTON_DISABLE = SEQ_SE_DP_BEEP,		// �����ȃ{�^����������

// ���u�e�X�^�[
	//POKETCH_SE_LOVE_BUTTON = SEQ_SE_DP_POKETCH_003,		// �{�^��������
	POKETCH_SE_LOVE_BUTTON		= SEQ_SE_DP_POKETCH_010,	// �{�^��������
	POKETCH_SE_LOVE_BUTTON_DISABLE = SEQ_SE_DP_BEEP,		// �{�^��������Ԃŉ�����
	POKETCH_SE_LOVE_CHANGE_POKE = SEQ_SE_DP_POKETCH_003,	// �|�P�����؂�ւ�
	//POKETCH_SE_LOVE_MOVE_POKE_1 = SEQ_SE_DP_POKETCH_003,	// �ړ����P�i�K��
	POKETCH_SE_LOVE_MOVE_POKE_1 = SEQ_SE_DP_POKETCH_012,	// �ړ����P�i�K��
	//POKETCH_SE_LOVE_MOVE_POKE_2 = SEQ_SE_DP_POKETCH_003,	// �ړ����Q�i�K��
	POKETCH_SE_LOVE_MOVE_POKE_2 = SEQ_SE_DP_POKETCH_012,	// �ړ����Q�i�K��
	//POKETCH_SE_LOVE_MOVE_POKE_3 = SEQ_SE_DP_POKETCH_003,	// �ړ����R�i�K��
	POKETCH_SE_LOVE_MOVE_POKE_3 = SEQ_SE_DP_POKETCH_012,	// �ړ����R�i�K��
	//POKETCH_SE_LOVE_LV_0 = SEQ_SE_DP_POKETCH_007,			// ���x������Œ�
	POKETCH_SE_LOVE_LV_0		= SEQ_SE_DP_POKETCH_013,	// ���x������Œ�
	//POKETCH_SE_LOVE_LV_MAX = SEQ_SE_DP_POKETCH_006,		// ���x������ō�
	POKETCH_SE_LOVE_LV_MAX		= SEQ_SE_DP_POKETCH_014,	// ���x������ō�


// �o�b�N���C�g�X�C�b�`
	POKETCH_SE_BACKLIGHT_SWITCH	= SEQ_SE_DP_POKETCH_003,		// �{�^��������

// �_�E�W���O�}�V��
	//POKETCH_SE_DOWSING_TOUCH	= SEQ_SE_DP_POKETCH_003,		// ��ʃ^�b�`����
	POKETCH_SE_DOWSING_TOUCH	= SEQ_SE_DP_POKETCH_009,		// ��ʃ^�b�`����

// �Ȃ��ǃ`�F�b�J�[
	POKETCH_SE_NATSUKI_JUMP = SEQ_SE_DP_POKETCH_010,				// �_�u���^�b�v�őS�|�P�W�����v

// ������T�[�`���[
	POKETCH_SE_TUSHIN_WARNING = SEQ_SE_DP_BEEP,			// �ʐM�����������O�ɊJ�n���悤�Ƃ���

// ���񂢃��X�g
	POKETCH_SE_LIST_UPDATE = SEQ_SE_DP_POKETCH_010,		// ��ʍX�V
};


#endif
