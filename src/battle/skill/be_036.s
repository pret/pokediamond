
//============================================================================
/**
 *
 *@file		be_036.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			036　２割の確率で敵を「マヒ」、「やけど」、「こおり」のどれかの状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_036:
	RANDOM_GET		2,ADD_COND_YAKEDO
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,ADD_STATUS_DEFENCE
	VALUE_WORK		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,BUF_PARA_CALC_WORK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
