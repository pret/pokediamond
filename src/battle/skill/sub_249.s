
//============================================================================
/**
 *
 *@file		sub_249.s
 *@brief	戦闘シーケンス
 *			まひ＋ひるむの追加効果シーケンス（与えたダメージの1/2）
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_249:
	ADD_STATUS_CHECK	SUB_249_NEXT
	GOSUB				SUB_SEQ_MAHI
SUB_249_NEXT:
	ADD_STATUS_CHECK	SUB_249_END
	GOSUB				SUB_SEQ_HIRUMU
SUB_249_END:
	SEQ_END
