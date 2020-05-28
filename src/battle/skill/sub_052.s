
//============================================================================
/**
 *
 *@file		sub_052.s
 *@brief	戦闘シーケンス
 *			リフレクターシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_052:
	RIHUREKUTAA		Umakukimaran
	GOSUB			SUB_SEQ_KABE
Umakukimaran:
	SEQ_END

