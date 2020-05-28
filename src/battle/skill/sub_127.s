
//============================================================================
/**
 *
 *@file		sub_127.s
 *@brief	戦闘シーケンス
 *			いちゃもんシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_127:
	//すでにいちゃもんをつけられている時は、うまくきまらん
	IF_PSP		IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_ICHAMON,Umakukimaran
	IF			IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE	VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_ICHAMON
	MESSAGE		IchamonMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
