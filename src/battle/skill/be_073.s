//============================================================================
/**
 *
 *@file		be_073.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			073　追加効果で相手の「命中率」を１段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_073:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HITDOWN|ADD_STATUS_DEFENCE
	SEQ_END
