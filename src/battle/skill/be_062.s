//============================================================================
/**
 *
 *@file		be_062.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			062　敵ポケモンの「とくぼう」を２段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_062:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEDEFDOWN2|ADD_STATUS_DEFENCE
	SEQ_END
