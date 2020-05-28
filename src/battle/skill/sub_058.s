
//============================================================================
/**
 *
 *@file		sub_058.s
 *@brief	戦闘シーケンス
 *			しめつけ系追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_058:
	//みがわりがいる場合は、なにもしない
	MIGAWARI_CHECK	SIDE_TSUIKA,SUB_058_END
	//すでに締め付けられている時は、なにもしない
	IF_PSP			IF_FLAG_BIT,SIDE_DEFENCE,ID_PSP_condition2,CONDITION2_SHIME,SUB_058_END
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//２～５ターンの乱数を取得
	RANDOM_GET		3,3
	//装備効果でまきつく系のカウンタアップは、カウンタを最大にする
	SOUBI_CHECK		SOUBI_NO_HAVE,SIDE_ATTACK,SOUBI_MAKITUKUKEIUP,SUB_058_NEXT
	VALUE			VAL_SET,BUF_PARA_CALC_WORK,6
SUB_058_NEXT:
	//しめカウンタになるようにビットシフト
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,SHIME_SHIFT
	PSP_VALUE_WORK	VAL_BIT,SIDE_DEFENCE,ID_PSP_condition2,BUF_PARA_CALC_WORK
	//誰にしめつけられたか、ワークに格納
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_shime_client_no,BUF_PARA_ATTACK_CLIENT
	//何の技でしめつけられたか、ワークに格納
	PSP_VALUE_WORK	VAL_SET,SIDE_DEFENCE,ID_PSP_wkw_shime_wazano,BUF_PARA_WAZA_NO_NOW
SUB_058_END:
	SEQ_END
