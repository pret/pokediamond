
//============================================================================
/**
 *
 *@file		sub_278.s
 *@brief	戦闘シーケンス
 *			先制系のアイテム効果発動チェック
 *@author	HisashiSogabe
 *@data		2006.06.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_278:
	VALUE_WORK		VAL_GET,BUF_PARA_CLIENT_SET_MAX,BUF_PARA_TEMP_WORK
	VALUE			VAL_SUB,BUF_PARA_TEMP_WORK,1
	//最後のClientはチェックしない
	IF_WORK			IF_FLAG_EQ,BUF_PARA_TEMP_WORK,BUF_PARA_AGI_CNT,SUB_278_END
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_wkw_sensei_flag,1,SUB_278_NEXT
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_wkw_once_agi_up,0,SUB_278_END
SUB_278_NEXT:
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ITEM_POKE
	SERVER_WAIT
	IF_PSP			IF_FLAG_EQ,SIDE_ATTACK,ID_PSP_wkw_once_agi_up,1,SUB_278_ONCE_AGI_UP
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_sensei_flag,0
	BRANCH			SUB_278_END
SUB_278_ONCE_AGI_UP:
	MESSAGE			ItemSenseiMineMsg,TAG_NICK_ITEM,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	PSP_VALUE		VAL_SET,SIDE_ATTACK,ID_PSP_wkw_once_agi_up,0
	KILL_ITEM		SIDE_ATTACK
SUB_278_END:
	SEQ_END
