
//============================================================================
/**
 *
 *@file		sub_190.s
 *@brief	戦闘シーケンス
 *			だっぴシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_190:
	PSP_VALUE	VAL_SET,SIDE_WORK,ID_PSP_condition,0
	PSP_VALUE	VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_AKUMU
	MESSAGE		DappiMineMsg,TAG_NICK_TOKU_COND,SIDE_WORK,SIDE_CLIENT_WORK,SIDE_WORK
	SERVER_WAIT
	STATUS_SET	SIDE_WORK,STATUS_NORMAL
	WAIT		MSG_WAIT
	SEQ_END
