
//============================================================================
/**
 *
 *@file		sub_214.s
 *@brief	戦闘シーケンス
 *			HPマイナス装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_214:
	VALUE		VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB		SUB_SEQ_HP_CALC
	SEQ_END

