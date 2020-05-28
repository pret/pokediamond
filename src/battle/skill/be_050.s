//============================================================================
/**
 *
 *@file		be_050.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			050　使用したポケモンの「こうげき」を２段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_050:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_POWUP2|ADD_STATUS_ATTACK
	SEQ_END
