//============================================================================
/**
 *
 *@file		be_044.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			044 ２回連続で攻撃する
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_044:
	RENZOKU			2,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessageのタイプをループ用にする
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
