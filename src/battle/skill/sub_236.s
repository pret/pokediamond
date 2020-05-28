
//============================================================================
/**
 *
 *@file		sub_236.s
 *@brief	戦闘シーケンス
 *			にほんばれが終了したメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_236:
	VALUE		VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HARE
	MESSAGE		NihonbareEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
