
//============================================================================
/**
 *
 *@file		sub_240.s
 *@brief	�퓬�V�[�P���X
 *			���킬�Â��Ă��郁�b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_240:
	MESSAGE		NoisyMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
