
//============================================================================
/**
 *
 *@file		sub_060.s
 *@brief	戦闘シーケンス
 *			しめつけ終了シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_060:
	MESSAGE			ShimeEndMineMsg,TAG_NICK_WAZA,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
