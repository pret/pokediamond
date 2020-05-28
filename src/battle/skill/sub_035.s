
//============================================================================
/**
 *
 *@file		sub_035.s
 *@brief	戦闘シーケンス（BattleEffect）
 *			がまんシーケンス
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_035:
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
//	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,GAMAN_TURN|CONDITION2_KEEP
//	VALUE_WORK	VAL_SET,BUF_PARA_WAZA_NO_KEEP_ATTACK,BUF_PARA_WAZA_NO_NOW
	KEEP_ON		SIDE_ATTACK
	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,GAMAN_TURN
	VALUE		VAL_SET,BUF_PARA_STORE_DAMAGE_ATTACK,0
	SEQ_END

