
//============================================================================
/**
 *
 *@file		sub_087.s
 *@brief	戦闘シーケンス
 *			まもる、みきり、こらえるなどチェックシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_087:
	GUARD_SUCCESS_CHECK		Umakukimaran
	GOSUB					SUB_SEQ_WAZA_OUT_EFF
	GOSUB					SUB_SEQ_MESSAGE_WORK
	SEQ_END

Umakukimaran:
	VALUE	VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
