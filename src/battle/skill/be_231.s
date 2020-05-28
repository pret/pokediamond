//============================================================================
/**
 *
 *@file		be_231.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			231　そのターンにダメージを受けている相手に大ダメージを与える。威力２倍
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_231:
	WAZA_PARAM_GET	ID_WTD_damage
	VALUE_WORK		VAL_SET,BUF_PARA_DAMAGE_POWER,BUF_PARA_CALC_WORK
	IF				IF_FLAG_EQ,BUF_PARA_DAMEOSHI_DAMAGE_DEFENCE,0,BE_231_NEXT
	VALUE_WORK		VAL_SET,BUF_PARA_DAMAGE_POWER,BUF_PARA_CALC_WORK
	VALUE			VAL_MUL,BUF_PARA_DAMAGE_POWER,2
BE_231_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
