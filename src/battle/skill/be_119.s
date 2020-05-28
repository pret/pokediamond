//============================================================================
/**
 *
 *@file		be_119.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			119　使用する度に技の威力が倍になっていく、攻撃を１度でもはずすと威力は戻る
 *
 *@author	HisashiSogabe
 *@data		2005.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_119:
	RENZOKUGIRI
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
