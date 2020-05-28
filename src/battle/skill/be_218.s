//============================================================================
/**
 *
 *@file		be_218.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			218　威力はあるが、攻撃する度に疲れてしまい、素早さが落ちていく。１回の攻撃につき１段階落ちる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_218:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
