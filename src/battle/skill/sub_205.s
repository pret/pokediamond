
//============================================================================
/**
 *
 *@file		sub_205.s
 *@brief	戦闘シーケンス
 *			こんらん回復装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_205:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemNoKonranMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_KONRAN
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

