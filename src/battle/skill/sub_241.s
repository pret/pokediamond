
//============================================================================
/**
 *
 *@file		sub_241.s
 *@brief	戦闘シーケンス
 *			さわぎおわったメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_241:
	MESSAGE		OtonashikuMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
