
//============================================================================
/**
 *
 *@file		sub_260.s
 *@brief	戦闘シーケンス
 *			おしゃべり追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.05.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_260:
	OSYABERI		SUB_260_END
	GOSUB			SUB_SEQ_KONRAN
SUB_260_END:
	SEQ_END
