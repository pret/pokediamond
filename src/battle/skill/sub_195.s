
//============================================================================
/**
 *
 *@file		sub_195.s
 *@brief	戦闘シーケンス
 *			よちむシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_195:
	MESSAGE			YochimuMineMsg,TAG_NICK_TOKU_WAZA,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

