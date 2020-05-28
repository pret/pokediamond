//============================================================================
/**
 *
 *@file		be_076.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			076　追加効果で相手を混乱させる
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_076:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
