//============================================================================
/**
 *
 *@file		be_068.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			068　追加効果で相手の攻撃力を１ランク下げる
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_068:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWDOWN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
