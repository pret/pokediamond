//============================================================================
/**
 *
 *@file		be_058.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			058　敵ポケモンの「こうげき」を２段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_058:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_POWDOWN2|ADD_STATUS_DEFENCE
	SEQ_END
