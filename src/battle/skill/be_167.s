//============================================================================
/**
 *
 *@file		be_167.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			167　相手をやけど状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_167:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	SEQ_END
