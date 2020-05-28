//============================================================================
/**
 *
 *@file		be_195.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			195　対象の相手がそのターンに使用した回復技、能力変化技の効果を奪う。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_195:
	YOKODORI		Umakukimaran
	MESSAGE_PARAM	YokodoriMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_SET,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
