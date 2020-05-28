//============================================================================
/**
 *
 *@file		be_043.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			043 クリティカルヒットが出やすい
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_043:
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
