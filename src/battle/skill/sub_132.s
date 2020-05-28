
//============================================================================
/**
 *
 *@file		sub_132.s
 *@brief	戦闘シーケンス
 *			ちょうはつシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_132:
	//すでにちょうはつされている時は、うまくきまらん
	IF_PSP			IF_FLAG_NE,SIDE_DEFENCE,ID_PSP_wkw_chouhatsu_count,0,Umakukimaran
	IF				IF_FLAG_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_NOHIT_CHG,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	RANDOM_GET		2,3
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_chouhatsu_count,BUF_PARA_CALC_WORK
	MESSAGE			ChouhatsuMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
