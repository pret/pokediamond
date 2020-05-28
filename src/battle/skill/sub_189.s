
//============================================================================
/**
 *
 *@file		sub_189.s
 *@brief	戦闘シーケンス
 *			さめはだダメージシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_189:
	//だめおしが有効になるようにLAST_DAMAGEにダメージ値を格納
//	VALUE_WORK		VAL_SET,BUF_PARA_LAST_DAMAGE_ATTACK,BUF_PARA_HP_CALC_WORK
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			SamehadaM2MMsg,TAG_NICK_TOKU_NICK,SIDE_DEFENCE,SIDE_DEFENCE,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

