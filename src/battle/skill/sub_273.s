
//============================================================================
/**
 *
 *@file		sub_273.s
 *@brief	戦闘シーケンス
 *			フィールド天候ですなあらし
 *@author	HisashiSogabe
 *@data		2006.06.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_273:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_SAND
	SERVER_WAIT
	MESSAGE			SunaarashiMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_SUNAOKOSHI
	SEQ_END
