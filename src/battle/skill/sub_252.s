
//============================================================================
/**
 *
 *@file		sub_252.s
 *@brief	戦闘シーケンス
 *			ゆきふらしシーケンス
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_252:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_ICE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			YukihurasiMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_YUKIHURASHI
	SEQ_END
