//============================================================================
/**
 *
 *@file		be_211.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			211　特攻、特防が上がる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_211:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MEISOU|ADD_STATUS_ATTACK
	SEQ_END
