//============================================================================
/**
 *
 *@file		be_085.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			085　効果なし（はねる）
 *
 *@author	HisashiSogabe
 *@data		2005.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_085:
	VALUE	VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NANIMOOKORAN
	SEQ_END
