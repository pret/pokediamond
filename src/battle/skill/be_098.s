//============================================================================
/**
 *
 *@file		be_098.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			098　この技を使った後に敵のダメージで戦闘不能になると、敵のポケモンも戦闘不能になる
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_098:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MICHIDURE|ADD_STATUS_WAZAKOUKA
	SEQ_END
