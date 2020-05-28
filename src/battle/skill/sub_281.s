
//============================================================================
/**
 *
 *@file		sub_281.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			攻撃対象がいなくて当たらない
 *
 *@author	HisashiSogabe
 *@data		2006.07.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_281:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			NoPokemonMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ため系フラグを落とす
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
