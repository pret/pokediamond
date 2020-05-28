
//============================================================================
/**
 *
 *@file		sub_247.s
 *@brief	戦闘シーケンス
 *			やけど＋ひるむの追加効果シーケンス（与えたダメージの1/2）
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_247:
	ADD_STATUS_CHECK	SUB_247_NEXT
	GOSUB				SUB_SEQ_YAKEDO
SUB_247_NEXT:
	ADD_STATUS_CHECK	SUB_247_END
	GOSUB				SUB_SEQ_HIRUMU
SUB_247_END:
	SEQ_END
