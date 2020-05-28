
//============================================================================
/**
 *
 *@file		sub_006.s
 *@brief	戦闘シーケンス
 *			気絶シーケンス
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_006:
	INC_RECORD		SIDE_KIZETSU,CLIENT_BOOT_TYPE_NOMINE,RECID_KILL_POKE
	INC_RECORD		SIDE_KIZETSU,CLIENT_BOOT_TYPE_MINE,RECID_TEMOTI_KIZETU
	KIZETSU_EFFECT
	SERVER_WAIT
	HP_GAUGE_OUT	SIDE_KIZETSU
	MESSAGE			KizetsuMineMsg,TAG_NICK,SIDE_KIZETSU
	SERVER_WAIT
	WAIT			MSG_WAIT
	//通常の気絶処理からは、経験値取得処理を発生させない
	IF				IF_FLAG_BIT,BUF_PARA_SERVER_STATUS_FLAG2,SERVER_STATUS_FLAG2_NO_EXP_KIZETSU,NoExpGet
//	GOSUB			SUB_SEQ_GET_EXP
NoExpGet:
	SEQ_END
