//============================================================================
/**
 *
 *@file		be_192.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			192　自分が覚えている技を、相手のポケモンに出させなくする。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_192:
	HUUIN			Umakukimaran
	MESSAGE_PARAM	HuuinMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
