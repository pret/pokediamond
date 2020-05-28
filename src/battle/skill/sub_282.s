
//============================================================================
/**
 *
 *@file		sub_282.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			がまん発動時に攻撃対象がいないシーケンス
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_282:
//がまんがとかれた
	MESSAGE			GamanOverMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//ためフラグを落とす
	PSP_VALUE		VAL_NBIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_KEEP
	MESSAGE			NoPokemonMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

