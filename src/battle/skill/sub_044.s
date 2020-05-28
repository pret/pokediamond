
//============================================================================
/**
 *
 *@file		sub_044.s
 *@brief	戦闘シーケンス
 *			あばれる追加効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.01.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_044:
	//２～３の乱数を生成
	RANDOM_GET		1,2
	//あばれるビットになるように、左シフト
	VALUE			VAL_LSH,BUF_PARA_CALC_WORK,ABARERU_SHIFT
	//あばれるビットを立てる
	PSP_VALUE_WORK	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,BUF_PARA_CALC_WORK
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	SEQ_END
