//============================================================================
/**
 *
 *@file		be_205.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			205　相手の攻撃、防御が下がる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_205:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KUSUGURU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
