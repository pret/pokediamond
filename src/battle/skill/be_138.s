//============================================================================
/**
 *
 *@file		be_138.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			138　追加効果で自分の防御力を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_138:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
