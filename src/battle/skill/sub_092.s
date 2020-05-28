
//============================================================================
/**
 *
 *@file		sub_092.s
 *@brief	戦闘シーケンス
 *			へんしんシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.26
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_092:
	//消えている相手では、うまくきまらん（ロックオンしていても外れる）
	IF_PSP		IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_KIE,Umakukimaran
	//へんしんしている相手は、うまくきまらん
	IF_PSP		IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_HENSHIN,Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	HENSIN
	MESSAGE		HenshinMineMsg,TAG_NICK_POKE,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
