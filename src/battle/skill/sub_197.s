
//============================================================================
/**
 *
 *@file		sub_197.s
 *@brief	戦闘シーケンス
 *			スロースタート終了シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_197:
	MESSAGE			SlowStartEndMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

