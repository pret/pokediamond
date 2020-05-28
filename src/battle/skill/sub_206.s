
//============================================================================
/**
 *
 *@file		sub_206.s
 *@brief	戦闘シーケンス
 *			状態異常回復装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_206:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemNoHukusuuMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	STATUS_SET		SIDE_WORK,STATUS_NORMAL
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_SET,SIDE_WORK,ID_PSP_condition,0
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_AKUMU
	PSP_VALUE		VAL_NBIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_KONRAN
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

