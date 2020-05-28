//============================================================================
/**
 *
 *@file		be_051.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			051　使用したポケモンの「ぼうぎょ」を２段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_051:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP2|ADD_STATUS_ATTACK
	SEQ_END
