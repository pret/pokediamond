
//============================================================================
/**
 *
 *@file		sub_041.s
 *@brief	�퓬�V�[�P���X
 *			�퓬���Ƀg���[�i�[���o�ꂵ�ă��b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_041:
	TRAINER_IN				SIDE_ENEMY,POS_MSG
	SERVER_WAIT
	TRAINER_MESSAGE_WORK	SIDE_ENEMY
	SERVER_WAIT
	WAIT					MSG_WAIT*2
	TRAINER_OUT				SIDE_ENEMY
	SERVER_WAIT
	SEQ_END
