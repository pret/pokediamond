//============================================================================
/**
 *
 *@file		be_020.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			020　敵ポケモンの「すばやさ」を１段階下げる
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_020:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_DEFENCE
	SEQ_END
