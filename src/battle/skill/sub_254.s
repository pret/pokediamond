
//============================================================================
/**
 *
 *@file		sub_254.s
 *@brief	戦闘シーケンス
 *			ねむりながらいうことをきかないシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_254:
	WAIT		MSG_WAIT/2
	MESSAGE		OrderIgnoreSleepMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
