//============================================================================
/**
 *
 *@file		be_260.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			260　こおりの追加効果+あられ状態のとき、技が必ず命中する。
 *
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_260:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_KOORI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
