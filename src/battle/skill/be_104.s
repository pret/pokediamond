//============================================================================
/**
 *
 *@file		be_104.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			104　３回連続で敵を攻撃する、攻撃が命中する度にダメージは大きくなる（１０、２０、３０）、
 *				 １度攻撃が外れると技はそこで止まる
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_104:
	RENZOKU			3,TRIPLEKICK_HIT_OFF
	//ServerWazaOutAfterMessageのタイプをループ用にする
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	//１０ずつあげていく
	VALUE			VAL_ADD,BUF_PARA_DAMAGE_POWER,10
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
