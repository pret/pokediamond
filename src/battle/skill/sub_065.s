
//============================================================================
/**
 *
 *@file		sub_065.s
 *@brief	戦闘シーケンス
 *			反動で技がだせないシーケンス
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_065:
	MESSAGE			HandouMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
