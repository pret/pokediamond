//============================================================================
/**
 *
 *@file		be_100.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			100　敵の最後に出した技のＰＰを2～5ランダムで減らす
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_100:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_URAMI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
