
//============================================================================
/**
 *
 *@file		sub_057.s
 *@brief	戦闘シーケンス
 *			MESSAGE_WORK表示シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_057:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
