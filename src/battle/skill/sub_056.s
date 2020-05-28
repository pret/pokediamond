
//============================================================================
/**
 *
 *@file		sub_056.s
 *@brief	戦闘シーケンス
 *			さわぐ追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_056:
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	//２～５の乱数を生成
	RANDOM_GET		3,3
	//さわぐビットになるように、左シフト
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,SAWAGU_SHIFT
	//さわぐビットを立てる
	PSP_VALUE_WORK	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,BUF_PARA_CALC_WORK
	//さわいでいるClientNoのビットを立てる
	VALUE_WORK		VAL_TO_BIT,BUF_PARA_CALC_WORK,BUF_PARA_ATTACK_CLIENT
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,FIELD_SAWAGU_SHIFT
	VALUE_WORK		VAL_BIT,BUF_PARA_FIELD_CONDITION,BUF_PARA_CALC_WORK
	MESSAGE			SawaguMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
