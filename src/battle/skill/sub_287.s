
//============================================================================
/**
 *
 *@file		sub_287.s
 *@brief	戦闘シーケンス
 *			消えていたポケモンを出現させるシーケンス
 *@author	HisashiSogabe
 *@data		2006.07.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_287:
	VANISH_ON_OFF	SIDE_WORK,SW_VANISH_OFF
	SERVER_WAIT
	SEQ_END
