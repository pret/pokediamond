//============================================================================
/**
 *
 *@file		be_121.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			121　なつき度で技の威力が変化する、なつき度が高いほど威力が高い
 *
 *@author	HisashiSogabe
 *@data		2006.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_121:
	PSP_VALUE_WORK	VAL_GET,SIDE_ATTACK,ID_PSP_friend,BUF_PARA_DAMAGE_POWER
	VALUE			VAL_MUL,BUF_PARA_DAMAGE_POWER,10
	VALUE			VAL_DIV,BUF_PARA_DAMAGE_POWER,25
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
