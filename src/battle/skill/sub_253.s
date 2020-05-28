
//============================================================================
/**
 *
 *@file		sub_253.s
 *@brief	戦闘シーケンス
 *			おみとおしシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_253:
	WAIT		MSG_WAIT/2
	MESSAGE		OmitoosiMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
