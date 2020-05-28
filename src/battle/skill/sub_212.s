
//============================================================================
/**
 *
 *@file		sub_212.s
 *@brief	戦闘シーケンス
 *			メロメロ回復装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_212:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemNoJoutaiijouMineMsg,TAG_NICK_ITEM_COND,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_MEROMERO
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

