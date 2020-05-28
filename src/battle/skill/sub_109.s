
//============================================================================
/**
 *
 *@file		sub_109.s
 *@brief	戦闘シーケンス
 *			しんぴのまもりシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_109:
	SHINPI			Umakukimaran
	GOSUB			SUB_SEQ_KABE
Umakukimaran:
	SEQ_END

