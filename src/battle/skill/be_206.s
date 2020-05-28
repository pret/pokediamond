//============================================================================
/**
 *
 *@file		be_206.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			206　防御、特防が上がる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_206:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_COSMO_POWER|ADD_STATUS_ATTACK
	SEQ_END
