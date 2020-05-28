
//============================================================================
/**
 *
 *@file		sub_144.s
 *@brief	戦闘シーケンス
 *			ふういんで技がだせないシーケンス

 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_144:
	MESSAGE			HuuinNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
