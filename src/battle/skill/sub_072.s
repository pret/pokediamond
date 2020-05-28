
//============================================================================
/**
 *
 *@file		sub_072.s
 *@brief	戦闘シーケンス
 *			かなしばり終了シーケンス

 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_072:
	MESSAGE		KanashibariEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
