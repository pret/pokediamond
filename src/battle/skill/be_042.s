//============================================================================
/**
 *
 *@file		be_042.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			042　２～５ターンの間ダメージを与える。その間、相手は逃げられない
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_042:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SHIME|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_CHECK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
