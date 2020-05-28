//============================================================================
/**
 *
 *@file		be_077.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			077　連続で２回攻撃し、追加効果で相手をどく状態にする
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_077:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	RENZOKU			2,RENZOKU_HIT_OFF
	//ServerWazaOutAfterMessageのタイプをループ用にする
	VALUE			VAL_SET,BUF_PARA_SWOAM_TYPE,SWOAM_LOOP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
