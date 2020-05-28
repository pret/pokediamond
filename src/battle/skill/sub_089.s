
//============================================================================
/**
 *
 *@file		sub_089.s
 *@brief	戦闘シーケンス
 *			みがわりシーケンス
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_089:
	ATTACK_MESSAGE
	SERVER_WAIT
	//すでにみがわりがでている場合は、失敗
	IF_PSP			IF_FLAG_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MIGAWARI,MigawariAlready
	MIGAWARI		MigawariNG
//	WAZA_EFFECT		SIDE_ATTACK
	STATUS_EFFECT	SIDE_ATTACK,STATUS_ACTION_DOLL_ON
	SERVER_WAIT
	//みがわりフラグを立てる
	PSP_VALUE		VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MIGAWARI
	//ダメージエフェクトで点滅しないフラグを立てる
	VALUE			VAL_BIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_NO_BLINK
	//HP操作対象をAttackClientに
	VALUE_WORK		VAL_SET,BUF_PARA_CLIENT_WORK,BUF_PARA_ATTACK_CLIENT
	GOSUB			SUB_SEQ_HP_CALC
	MESSAGE			MigawariMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

MigawariNG:
	WAIT			MSG_WAIT
	MESSAGE			MigawariNGMsg,TAG_NONE
	BRANCH			SUB_089_END
MigawariAlready:
	WAIT			MSG_WAIT
	MESSAGE			AlreadyMigawariMineMsg,TAG_NICK,SIDE_ATTACK
SUB_089_END:
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_SIPPAI
	SEQ_END
