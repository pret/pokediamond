//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			124　５ターンの間、特殊状態（どく・マヒ等）にならなくなる、使用したポケモンが交代してもターン分は効果が受け継がれる
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_124:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SHINPI|ADD_STATUS_WAZAKOUKA
	SEQ_END
