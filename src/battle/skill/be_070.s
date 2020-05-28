//============================================================================
/**
 *
 *@file		be_070.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			070　追加効果で相手の素早さを１ランク下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_070:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_DEFENCE
	SEQ_END
