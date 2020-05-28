
//============================================================================
/**
 *
 *@file		sub_155.s
 *@brief	戦闘シーケンス
 *			ねむりをなおすシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_155:
	//HP0なら効果なし
	IF_PSP			IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,0,SUB_155_END
	PSP_VALUE		VAL_NBIT,SIDE_DEFENCE,ID_PSP_condition,CONDITION_NEMURI
	MESSAGE			WakeupMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	STATUS_SET		SIDE_DEFENCE,STATUS_NORMAL
	WAIT			MSG_WAIT
SUB_155_END:
	SEQ_END
