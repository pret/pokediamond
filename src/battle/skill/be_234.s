//============================================================================
/**
 *
 *@file		be_234.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			234　自分の受けている状態異常（どく、どくどく、ねむり、まひ、やけど）を、敵、味方を選んで相手を同じ状態にする。
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_234:
	SURIKOMI	Umakukimaran
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SURIKOMI|ADD_STATUS_DEFENCE
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
