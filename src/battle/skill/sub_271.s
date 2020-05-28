
//============================================================================
/**
 *
 *@file		sub_271.s
 *@brief	戦闘シーケンス
 *			フィールド天候で雨
 *@author	HisashiSogabe
 *@data		2006.06.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_271:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_RAIN
	SERVER_WAIT
	MESSAGE			AmeMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_AMEHURASHI
	SEQ_END
