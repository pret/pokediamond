//============================================================================
/**
 *
 *@file		be_080.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			080　使用した次のターンは行動が出来ない
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_080:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANDOU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
