//============================================================================
/**
 *
 *@file		be_194.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			194　対象の相手の技のダメージで瀕死状態になった場合、その技のＰＰを０にする。
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_194:
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_ONNEN,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_ONNEN
	MESSAGE_PARAM	OnnenMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
