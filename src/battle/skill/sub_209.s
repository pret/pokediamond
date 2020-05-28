
//============================================================================
/**
 *
 *@file		sub_209.s
 *@brief	戦闘シーケンス
 *			クリティカルアップ装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_209:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemCriticalUpMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_WORK	
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_BIT,SIDE_WORK,ID_PSP_condition2,CONDITION2_KIAIDAME
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END
