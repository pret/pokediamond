
//============================================================================
/**
 *
 *@file		sub_130.s
 *@brief	戦闘シーケンス
 *			まひをなおすシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_130:
	//HP0なら効果なし
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,SUB_130_END
	PSP_VALUE		VAL_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_MAHI
	MESSAGE			RecoverMahiMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	STATUS_SET		SIDE_DEFENCE,STATUS_NORMAL
	WAIT			MSG_WAIT
SUB_130_END:
	SEQ_END
