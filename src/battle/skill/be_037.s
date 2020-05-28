//============================================================================
/**
 *
 *@file		be_037.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			037　ねむる　ＨＰを全回復して、自分を２ターン眠らせる
 *
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_037:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_NEMURU|ADD_STATUS_WAZAKOUKA
	SEQ_END
