
//============================================================================
/**
 *
 *@file		sub_245.s
 *@brief	戦闘シーケンス
 *			いかりのボルテージアップメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_245:
	MESSAGE		IkariMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
