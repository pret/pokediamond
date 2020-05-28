//============================================================================
/**
 *
 *@file		be_238.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			238　自分の攻撃力と防御力を入れ替える。補助効果は入れ替わらない。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_238:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWER_TRICK|ADD_STATUS_WAZAKOUKA
	SEQ_END
