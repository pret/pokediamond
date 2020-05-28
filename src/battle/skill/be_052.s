//============================================================================
/**
 *
 *@file		be_052.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			052　使用したポケモンの「すばやさ」を２段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_052:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AGIUP2|ADD_STATUS_ATTACK
	SEQ_END
