
//============================================================================
/**
 *
 *@file		sub_256.s
 *@brief	戦闘シーケンス
 *			いうことを聞かずに別の技を出すシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_256:
	WAIT			MSG_WAIT/2
	MESSAGE			OrderIgnoreMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
