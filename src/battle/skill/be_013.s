//============================================================================
/**
 *
 *@file		be_013.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			013　使用したポケモンの「とくこう」を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_013:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEPOWUP|ADD_STATUS_ATTACK
	SEQ_END
