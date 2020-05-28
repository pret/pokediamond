//============================================================================
/**
 *
 *@file		be_011.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			011　使用したポケモンの「ぼうぎょ」を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_011:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	SEQ_END
