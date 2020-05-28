
//============================================================================
/**
 *
 *@file		sub_228.s
 *@brief	戦闘シーケンス
 *			サファリゾーンでドロを投げるシーケンス
 *@author	HisashiSogabe
 *@data		2006.04.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_228:
	MESSAGE_NO_DIR		SafariZoneDoroMsg1,TAG_TRNAME_NICK,SIDE_ATTACK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT				MSG_WAIT
	TRAINER_THROW		SIDE_MINE,TT_TYPE_SAFARI_STONE
	SERVER_WAIT
	STATUS_EFFECT		SIDE_ENEMY,STATUS_ACTION_ANGER
	SERVER_WAIT
	IF					IF_FLAG_EQ,BUF_PARA_TEMP_WORK,0,AtariMsg
	MESSAGE_NO_DIR		SafariZoneDoroMsg2,TAG_NICK,SIDE_DEFENCE
	BRANCH				SUB_228_NEXT
AtariMsg:
	MESSAGE_NO_DIR		SafariZoneDoroMsg3,TAG_NICK,SIDE_DEFENCE
SUB_228_NEXT:
	SERVER_WAIT
	WAIT				MSG_WAIT
	SEQ_END
