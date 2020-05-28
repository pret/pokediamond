//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			000 普通攻撃
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_000:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
