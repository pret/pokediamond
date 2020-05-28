//============================================================================
/**
 *
 *@file		be_208.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			208　攻撃、防御が上がる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_208:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_BUILD_UP|ADD_STATUS_ATTACK
	SEQ_END
