//============================================================================
/**
 *
 *@file		be_135.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			135　技を使うポケモンによって、タイプ、威力が変わる
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_135:
	MEZAMERU_POWER
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
