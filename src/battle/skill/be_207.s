//============================================================================
/**
 *
 *@file		be_207.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			207　そらを飛んでいる相手にもダメージを与えられる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_207:
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_SORAWOTOBU_HIT
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
