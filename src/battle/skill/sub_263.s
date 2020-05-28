
//============================================================================
/**
 *
 *@file		sub_263.s
 *@brief	戦闘シーケンス
 *			ナイトメアダメージシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_263:
	VALUE			VAL_SET,BUF_PARA_ATTACK_CLIENT_WORK,0
SUB_263_LOOP:
	IF				IF_FLAG_NBIT,BUF_PARA_TEMP_WORK,1,SUB_263_NEXT
	MESSAGE			NightmareM2MMsg,TAG_NICK_TOKU_NICK,SIDE_ATTACK_WORK,SIDE_ATTACK_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
SUB_263_NEXT:
	VALUE			VAL_ADD,BUF_PARA_ATTACK_CLIENT_WORK,1
	VALUE			VAL_RSH,BUF_PARA_TEMP_WORK,1
	IF				IF_FLAG_NE,BUF_PARA_TEMP_WORK,0,SUB_263_LOOP
	SEQ_END
