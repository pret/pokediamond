
//============================================================================
/**
 *
 *@file		sub_178.s
 *@brief	戦闘シーケンス
 *			特性によるHP回復シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_178:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	PSP_VALUE_WORK	VAL_GET,SIDE_DEFENCE,ID_PSP_hpmax,BUF_PARA_CALC_WORK
	IF_PSP_WORK		IF_FLAG_EQ,SIDE_DEFENCE,ID_PSP_hp,BUF_PARA_CALC_WORK,Mantan
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_DEFENCE_CLIENT
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			TokuseiHPKaifukuMineMsg,TAG_NICK_TOKU,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

Mantan:
	MESSAGE			TokuseiHPKaifukuNGMineMsg,TAG_NICK_TOKU_WAZA,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

