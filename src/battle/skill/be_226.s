//============================================================================
/**
 *
 *@file		be_226.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			226　敵、味方、自分を選択して実行。ランダムでステータスのいずれかの値をぐーんと上げる。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_226:
	//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran

	TUBOWOTUKU		Umakukimaran

	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
