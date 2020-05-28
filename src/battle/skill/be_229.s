//============================================================================
/**
 *
 *@file		be_229.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			229　威力の高い攻撃を繰り出す事が出来るが「ぼうぎょ」「とくぼう」も１段階下がってしまう。
 *				 攻撃後、ステータスダウン処理。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_229:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_INFIGHT|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
