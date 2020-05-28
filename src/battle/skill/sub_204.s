
//============================================================================
/**
 *
 *@file		sub_204.s
 *@brief	戦闘シーケンス
 *			PP回復装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_204:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	MESSAGE			ItemPPKaifukuMineMsg,TAG_NICK_ITEM_WAZA,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END

