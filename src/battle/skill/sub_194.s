
//============================================================================
/**
 *
 *@file		sub_194.s
 *@brief	戦闘シーケンス
 *			きけんよちシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_194:
	MESSAGE			KikenyochiMineMsg,TAG_TOKU_NICK,SIDE_CLIENT_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

