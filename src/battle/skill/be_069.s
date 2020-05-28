//============================================================================
/**
 *
 *@file		be_069.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			069　追加効果で相手の防御力を１ランク下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_069:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_DEFDOWN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
