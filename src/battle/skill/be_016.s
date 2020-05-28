//============================================================================
/**
 *
 *@file		be_016.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			016　使用したポケモンの「回避率」を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_016:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AVOIDUP|ADD_STATUS_ATTACK
	SEQ_END
