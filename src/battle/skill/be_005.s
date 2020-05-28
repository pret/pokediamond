//============================================================================
/**
 *
 *@file		be_005.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			005　こおりの追加効果
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_005:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_KOORI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
