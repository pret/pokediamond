
//============================================================================
/**
 *
 *@file		sub_258.s
 *@brief	戦闘シーケンス
 *			いうことを聞かずに自分を攻撃シーケンス
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_258:
	MESSAGE		IukotowokikanaiMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	MESSAGE		KonranMsg2,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	//ため系のフラグを落とす
	KEEP_OFF	SIDE_ATTACK
	JUMP		SUB_SEQ_HP_CALC
