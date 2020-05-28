//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			001　敵を「ねむり」状態にする
 *
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_001:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_NEMURI|ADD_STATUS_DEFENCE
	SEQ_END
