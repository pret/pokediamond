//============================================================================
/**
 *
 *@file		be_125.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			125　やけどの追加効果＋こおり状態がとける。自分がこおり状態でも技が出せる。
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_125:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
