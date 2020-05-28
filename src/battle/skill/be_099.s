//============================================================================
/**
 *
 *@file		be_099.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			099　残りのＨＰが少ない程、敵に大きなダメージを与える
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_099:
	JITABATA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
