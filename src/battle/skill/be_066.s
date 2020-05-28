//============================================================================
/**
 *
 *@file		be_066.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			066　敵を「どく」状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.12.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_066:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	SEQ_END
