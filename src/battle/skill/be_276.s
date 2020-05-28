
//============================================================================
/**
 *
 *@file		be_276.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			276　追加効果で自分の特攻を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2006.05.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_276:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWUP|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END


