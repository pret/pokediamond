//============================================================================
/**
 *
 *@file		be_031.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			031 追加効果で相手がひるむ
 *
 *@author	HisashiSogabe
 *@data		2005.11.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_031:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HIRUMU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
