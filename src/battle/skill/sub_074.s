

//============================================================================
/**
 *
 *@file		sub_074.s
 *@brief	戦闘シーケンス
 *			アンコール終了シーケンス

 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_074:
	MESSAGE			EncoreEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
