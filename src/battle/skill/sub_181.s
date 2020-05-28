
//============================================================================
/**
 *
 *@file		sub_181.s
 *@brief	戦闘シーケンス
 *			ぼうおんシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_181:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			BouonMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
