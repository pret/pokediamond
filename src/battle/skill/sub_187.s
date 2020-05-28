
//============================================================================
/**
 *
 *@file		sub_187.s
 *@brief	戦闘シーケンス
 *			トレースシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_187:
	WAIT				MSG_WAIT/2
	PSP_VALUE_WORK		VAL_GET,SIDE_DEFENCE_WORK,ID_PSP_speabino,BUF_PARA_CALC_WORK
	PSP_VALUE_WORK		VAL_SET,SIDE_WORK,ID_PSP_speabino,BUF_PARA_CALC_WORK
	MESSAGE				TraceM2MMsg,TAG_NICK_NICK_TOKU,SIDE_WORK,SIDE_DEFENCE_WORK,SIDE_DEFENCE_WORK
	SERVER_WAIT
	WAIT				MSG_WAIT
SUB_187_END:
	SEQ_END
