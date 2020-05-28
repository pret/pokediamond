
//============================================================================
/**
 *
 *@file		sub_116.s
 *@brief	戦闘シーケンス
 *			こうそくスピンによるしめ系の技からの開放シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_116:
	MESSAGE		ShimeEscapeM2MMsg,TAG_NICK_NICK_WAZA,SIDE_ATTACK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
