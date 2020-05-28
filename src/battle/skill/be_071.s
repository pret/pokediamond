//============================================================================
/**
 *
 *@file		be_071.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			071　追加効果で相手の特殊攻撃力を１ランク下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_071:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWDOWN|ADD_STATUS_DEFENCE
	SEQ_END
