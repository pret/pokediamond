
//============================================================================
/**
 *
 *@file		sub_237.s
 *@brief	戦闘シーケンス
 *			あられが終了したメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_237:
	VALUE		VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_ARARE
	MESSAGE		ArareEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
