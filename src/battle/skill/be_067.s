//============================================================================
/**
 *
 *@file		be_067.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			067　敵を「マヒ」状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_067:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	SEQ_END
