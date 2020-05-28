//============================================================================
/**
 *
 *@file		be_275.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			275　まひの追加効果＋怯ませる。間接追加効果確率をみて、それぞれチェックする。
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_275:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MAHI_HIRUMU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
