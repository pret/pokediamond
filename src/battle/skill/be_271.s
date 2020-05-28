//============================================================================
/**
 *
 *@file		be_271.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			271　追加効果で特防を２ランク下げる
 *
 *@author	HisashiSogabe
 *@data		2006.06.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_271:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEDEFDOWN2|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
