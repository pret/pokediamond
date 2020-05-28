
//============================================================================
/**
 *
 *@file		sub_185.s
 *@brief	戦闘シーケンス
 *			ひでりシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_185:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_SUN
	SERVER_WAIT
	MESSAGE			HideriMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HIDERI
	SEQ_END
