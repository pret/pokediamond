//============================================================================
/**
 *
 *@file		be_179.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			179　ねがいごとをした次のターン終了時、自分のＨＰの半分の値を回復する。ポケモンが入れ替わっても効果がある
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_179:
	NEGAIGOTO		Umakukimaran
	SEQ_END

Umakukimaran:
	VALUE			VAL_SET,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
