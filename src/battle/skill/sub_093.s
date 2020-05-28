
//============================================================================
/**
 *
 *@file		sub_093.s
 *@brief	戦闘シーケンス
 *			あくむ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_093:
	//みがわりがでていたら、うまくきまらん
	MIGAWARI_CHECK	SIDE_DEFENCE,Umakukimaran
	//すでにあくむにかかっていたら、うまくきまらん
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_AKUMU,Umakukimaran
	//ねむっていなかったら、うまくきまらん
	IF_PSP			IF_FLAG_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_NEMURI,Umakukimaran
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	PSP_VALUE		VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_AKUMU
	MESSAGE			AkumuBeginMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
