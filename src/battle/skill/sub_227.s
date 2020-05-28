
//============================================================================
/**
 *
 *@file		sub_227.s
 *@brief	戦闘シーケンス
 *			サファリゾーンでエサを投げるシーケンス
 *@author	HisashiSogabe
 *@data		2006.04.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_227:
	MESSAGE_NO_DIR		SafariZoneEsaMsg1,TAG_TRNAME_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT				MSG_WAIT
	TRAINER_THROW		SIDE_MINE,TT_TYPE_SAFARI_FOOD
	SERVER_WAIT
	STATUS_EFFECT		SIDE_ENEMY,STATUS_ACTION_JOY
	SERVER_WAIT
	STATUS_EFFECT		SIDE_ENEMY,STATUS_ACTION_EAT
	SERVER_WAIT
	IF					IF_FLAG_EQ,BUF_PARA_TEMP_WORK,0,AtariMsg
	MESSAGE_NO_DIR		SafariZoneEsaMsg2,TAG_NICK,SIDE_DEFENCE
	BRANCH				SUB_227_NEXT
AtariMsg:
	MESSAGE_NO_DIR		SafariZoneEsaMsg3,TAG_NICK,SIDE_DEFENCE
SUB_227_NEXT:
	SERVER_WAIT
	WAIT				MSG_WAIT
	SEQ_END
