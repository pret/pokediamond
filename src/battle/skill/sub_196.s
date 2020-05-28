
//============================================================================
/**
 *
 *@file		sub_196.s
 *@brief	戦闘シーケンス
 *			スロースタートシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_196:
	MESSAGE			SlowStartMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

