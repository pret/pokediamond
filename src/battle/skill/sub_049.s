
//============================================================================
/**
 *
 *@file		sub_049.s
 *@brief	戦闘シーケンス
 *			ひかりのかべシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_049:
	HIKARINOKABE	Umakukimaran
	GOSUB			SUB_SEQ_KABE
Umakukimaran:
	SEQ_END

