//============================================================================
/**
 *
 *@file		be_197.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			197　通常の打撃攻撃に、地形の種類による追加効果が加わります。
 *
 *@author	HisashiSogabe
 *@data		2006.03.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_197:
	CRITICAL_CHECK
	DAMAGE_CALC
	HIMITSUNOCHIKARA
	SEQ_END
