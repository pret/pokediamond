//============================================================================
/**
 *
 *@file		be_108.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			108　ちいさくなる
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_108:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_CHIISAKUNARU|ADD_STATUS_ATTACK
	SEQ_END
