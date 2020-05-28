//============================================================================
/**
 *
 *@file		be_029.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			029 ２～５回連続で攻撃する
 *
 *@author	HisashiSogabe
 *@data		2005.10.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_029:
	RENZOKU			0,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessageのタイプをループ用にする
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
