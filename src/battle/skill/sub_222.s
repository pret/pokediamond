
//============================================================================
/**
 *
 *@file		sub_222.s
 *@brief	戦闘シーケンス
 *			アイテムによる戦闘離脱
 *@author	HisashiSogabe
 *@data		2006.06.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_222:
	MESSAGE			Dougu_UseMsg,TAG_ITEM,SIDE_WORK
	SERVER_WAIT
	STATUS_EFFECT	SIDE_MINE,STATUS_EFF_ITEM_POUCH
	SERVER_WAIT
	SE_PLAY			SIDE_ATTACK,BSE_ESCAPE
	MESSAGE			EscapeMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_ESCAPE
	SEQ_END

