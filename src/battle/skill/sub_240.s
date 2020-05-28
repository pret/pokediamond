
//============================================================================
/**
 *
 *@file		sub_240.s
 *@brief	戦闘シーケンス
 *			さわぎつづけているメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_240:
	MESSAGE		NoisyMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
