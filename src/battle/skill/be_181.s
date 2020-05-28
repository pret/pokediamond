//============================================================================
/**
 *
 *@file		be_181.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			181　毎ターンチェックに１／１６づつ回復。ポケモン入れ替えができなくなる。ほえるなども効かなくなる
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_181:
	//すでにねをはっている場合は、うまくきまらん
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU,Umakukimaran
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_waza_kouka,WAZAKOUKA_NEWOHARU
	MESSAGE_PARAM	NewoharuMineMsg,TAG_NICK,SIDE_ATTACK
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MESSAGE_WORK|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
