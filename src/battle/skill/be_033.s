//============================================================================
/**
 *
 *@file		be_033.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			033　敵を「どく」状態にする、この毒のダメージはターンごとに増えていく
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_033:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_DOKUDOKU|ADD_STATUS_DEFENCE
	SEQ_END
