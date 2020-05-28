
//============================================================================
/**
 *
 *@file		sub_064.s
 *@brief	戦闘シーケンス
 *			はんどう追加効果シーケンス
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_064:
	//はんどうフラグを立てる
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_HANDOU
	VALUE_WORK		VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	//現在の総ターン数を保持（＋１の時だけ反動状態になればいい）
	PSP_VALUE_WORK	VAL_SET,SIDE_ATTACK,ID_PSP_wkw_handou_count,BUF_PARA_TOTAL_TURN
	SEQ_END

