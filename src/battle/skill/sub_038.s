
//============================================================================
/**
 *
 *@file		sub_038.s
 *@brief	戦闘シーケンス
 *			こんらんシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_038:
	MESSAGE		ConfusedMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_KONRAN
	SERVER_WAIT
	SEQ_END
