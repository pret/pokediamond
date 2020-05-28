
//============================================================================
/**
 *
 *@file		sub_163.s
 *@brief	戦闘シーケンス
 *			いえきシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_163:
	//みがわりを出されているときは、失敗する
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_IEKI,Umakukimaran
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	//特性マルチタイプは、うまくきまらん
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_speabino,TOKUSYU_MARUTITAIPU,Umakukimaran

	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_waza_kouka,WAZAKOUKA_IEKI
	MESSAGE			IekiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
