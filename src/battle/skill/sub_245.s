
//============================================================================
/**
 *
 *@file		sub_245.s
 *@brief	�퓬�V�[�P���X
 *			������̃{���e�[�W�A�b�v���b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_245:
	MESSAGE		IkariMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
