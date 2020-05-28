//============================================================================
/**
 *
 *@file		be_182.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			182　攻撃がヒットすると、自分の攻撃力、防御力が１段階下がる
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_182:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_BAKADIKARA|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
