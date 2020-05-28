
//============================================================================
/**
 *
 *@file		sub_283.s
 *@brief	戦闘シーケンス
 *			通信対戦勝敗シーケンス
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

