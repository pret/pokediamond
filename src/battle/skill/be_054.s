//============================================================================
/**
 *
 *@file		be_054.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			054　使用したポケモンの「とくぼう」を２段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_054:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEDEFUP2|ADD_STATUS_ATTACK
	SEQ_END
