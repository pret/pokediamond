//============================================================================
/**
 *
 *@file		be_024.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			024　敵ポケモンの「回避率」を１段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_024:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AVOIDDOWN|ADD_STATUS_DEFENCE
	SEQ_END
