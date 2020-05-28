
//============================================================================
/**
 *
 *@file		sub_238.s
 *@brief	戦闘シーケンス
 *			じゅうりょくが終了したメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_238:
	MESSAGE		JuuryokuEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
