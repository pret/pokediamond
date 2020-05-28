//============================================================================
/**
 *
 *@file		be_049.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			049　敵を「こんらん」状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_049:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	SEQ_END
