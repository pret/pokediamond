//============================================================================
/**
 *
 *@file		be_246.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			246　威力は高いが、他の３つの技を出していないと外れる。
 *				 ３つ出した後は場にいる間、有効。現在の手持ちの技を全て出し切れば有効。
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_246:
	TOTTEOKI		Umakukimaran
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
