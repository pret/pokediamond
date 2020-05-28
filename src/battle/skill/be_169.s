//============================================================================
/**
 *
 *@file		be_169.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			169　どく、まひ、やけど状態になると威力が倍になる
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_169:
	IF_PSP			IF_FLAG_NBIT,SIDE_ATTACK,ID_PSP_condition,CONDITION_KARAGENKI,BE_169_NEXT				
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,20
BE_169_NEXT:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
