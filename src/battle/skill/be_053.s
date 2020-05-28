//============================================================================
/**
 *
 *@file		be_053.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			053　使用したポケモンの「とくこう」を２段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_053:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEPOWUP2|ADD_STATUS_ATTACK
	SEQ_END
