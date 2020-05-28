
//============================================================================
/**
 *
 *@file		sub_207.s
 *@brief	戦闘シーケンス
 *			HP回復装備アイテム効果シーケンス（嫌いな味だとこんらんする）
 *@author	HisashiSogabe
 *@data		2006.02.28
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_207:
	GOSUB			SUB_SEQ_EQPITEM_HP_KAIHUKU
	MESSAGE			SeedKonranMineMsg,TAG_ITEM_NICK_TASTE,SIDE_WORK,SIDE_WORK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	//これ以降は、ATTACK_MESSAGEとWAZA_EFFECTは出ないようにする
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG|SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	VALUE_WORK		VAL_SET,BUF_PARA_TSUIKA_CLIENT,BUF_PARA_CLIENT_WORK
	VALUE			VAL_SET,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_SOUBIITEM
	GOSUB			SUB_SEQ_KONRAN
	//ATTACK_MESSAGEとWAZA_EFFECTを出さないようにしていたのを解除
	VALUE			VAL_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_ATTACK_MSG|SERVER_STATUS_FLAG_NO_WAZA_EFFECT
	SEQ_END

