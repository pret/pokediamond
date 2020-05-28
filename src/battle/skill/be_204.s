//============================================================================
/**
 *
 *@file		be_204.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			204　自分の特攻が、がくっと下がる。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_204:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWDOWN2|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
