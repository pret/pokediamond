
//============================================================================
/**
 *
 *@file		sub_230.s
 *@brief	戦闘シーケンス
 *			逃げるシーケンス
 *@author	HisashiSogabe
 *@data		2006.04.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_230:
	SE_PLAY			SIDE_ATTACK,BSE_ESCAPE
	MESSAGE_NO_DIR	EnemyEscapeMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	VALUE			VAL_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_ESCAPE
	INC_RECORD		SIDE_ATTACK,CLIENT_BOOT_TYPE_NOMINE,RECID_NIGERARETA
	SEQ_END
