//============================================================================
/**
 *
 *@file		be_209.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			209　急所に当たりやすい。１０％の確率で相手をどく状態にする。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_209:
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
