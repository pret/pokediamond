
//============================================================================
/**
 *
 *@file		sub_073.s
 *@brief	戦闘シーケンス
 *			アンコール効果発動シーケンス
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_073:
	ENCORE		Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		EncoreMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
Umakukimaran:
	SEQ_END
