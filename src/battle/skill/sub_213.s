
//============================================================================
/**
 *
 *@file		sub_213.s
 *@brief	戦闘シーケンス
 *			HP回復装備アイテム効果シーケンス（毎ターン）
 *@author	HisashiSogabe
 *@data		2006.03.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_213:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			ItemHPKaifukuEveryTurnMineMsg,TAG_NICK_ITEM,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

