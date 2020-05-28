
//============================================================================
/**
 *
 *@file		sub_210.s
 *@brief	戦闘シーケンス
 *			能力2段階UP装備アイテム効果シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_210:
	STATUS_EFFECT	SIDE_WORK,STATUS_ITEM_POKE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	STATUS_EFFECT	SIDE_WORK,STATUS_EFF_UP
	SERVER_WAIT
	MESSAGE			ItemCondUp2MineMsg,TAG_NICK_ITEM_STAT,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_SET,BUF_PARA_TEMP_WORK,ID_PSP_abiritycnt_hp
	VALUE_WORK		VAL_ADD,BUF_PARA_TEMP_WORK,BUF_PARA_MSG_WORK
	PSP_VALUE		VAL_ADD,SIDE_WORK,ID_PSP_work,2
	IF_PSP			IF_FLAG_NC,SIDE_WORK,ID_PSP_work,12,SUB_210_NEXT
	PSP_VALUE		VAL_SET,SIDE_WORK,ID_PSP_work,12
SUB_210_NEXT:
	GOSUB			SUB_SEQ_TSUIBAMU_CHECK
	SEQ_END
