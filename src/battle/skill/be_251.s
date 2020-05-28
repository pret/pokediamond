//============================================================================
/**
 *
 *@file		be_251.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			251　毎ターンチェックに１／１６づつ回復。【ねをはる】同じで交換が可能。
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_251:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_AQUARING,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_AQUARING
	MESSAGE_PARAM	AquaRingMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
