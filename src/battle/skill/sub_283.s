
//============================================================================
/**
 *
 *@file		sub_283.s
 *@brief	�퓬�V�[�P���X
 *			�ʐM�ΐ폟�s�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.07.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_283:
	WIN_LOSE_SET
	WIN_LOSE_MESSAGE
	SERVER_WAIT
	WAIT				MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	SEQ_END

