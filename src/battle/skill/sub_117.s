
//============================================================================
/**
 *
 *@file		sub_117.s
 *@brief	戦闘シーケンス
 *			こうそくスピンによるやどりぎのたねなどからの開放シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_117:
	MESSAGE		KousokuspinEscapeMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
