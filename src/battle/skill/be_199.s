//============================================================================
/**
 *
 *@file		be_199.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			199　すべてのポケモンが混乱状態になる
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_199:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	SEQ_END
