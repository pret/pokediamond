//============================================================================
/**
 *
 *@file		be_212.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			212　攻撃と素早さが上がる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_212:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_RYUUNOMAI|ADD_STATUS_ATTACK
	SEQ_END
