//============================================================================
/**
 *
 *@file		be_111.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			111　そのターンの敵の攻撃を防御する。連続で出すと成功率が下がっていく
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_111:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GUARD|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
