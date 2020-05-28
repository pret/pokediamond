//============================================================================
/**
 *
 *@file		be_010.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			010　使用したポケモンの「こうげき」を１段階上げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_010:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_POWUP|ADD_STATUS_ATTACK
	SEQ_END
