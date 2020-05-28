
//============================================================================
/**
 *
 *@file		sub_041.s
 *@brief	戦闘シーケンス
 *			戦闘中にトレーナーが登場してメッセージシーケンス
 *@author	HisashiSogabe
 *@data		2005.12.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_041:
	TRAINER_IN				SIDE_ENEMY,POS_MSG
	SERVER_WAIT
	TRAINER_MESSAGE_WORK	SIDE_ENEMY
	SERVER_WAIT
	WAIT					MSG_WAIT*2
	TRAINER_OUT				SIDE_ENEMY
	SERVER_WAIT
	SEQ_END
