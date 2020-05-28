//============================================================================
/**
 *
 *@file		be_225.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			225　３ターンの間、自分の場にいるポケモンの素早さを２倍にする。
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_225:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_OIKAZE|ADD_STATUS_WAZAKOUKA
	SEQ_END
