
//============================================================================
/**
 *
 *@file		sub_122.s
 *@brief	戦闘シーケンス
 *			テレポート発動シーケンス
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_122:
	//2vs2野生は失敗
	IF			IF_FLAG_EQ,BUF_PARA_FIGHT_TYPE,FIGHT_TYPE_2vs2_YASEI,Umakukimaran
	TELEPORT	Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		TeleportMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	FADE_OUT
	SERVER_WAIT
	VALUE		VAL_BIT,BUF_PARA_WIN_LOSE_FLAG,FIGHT_ESCAPE
	INC_RECORD	SIDE_ATTACK,CLIENT_BOOT_TYPE_NOMINE,RECID_NIGERARETA
	SEQ_END

Umakukimaran:
	VALUE		VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
