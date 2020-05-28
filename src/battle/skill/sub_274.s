
//============================================================================
/**
 *
 *@file		sub_274.s
 *@brief	戦闘シーケンス
 *			フィールド天候でふかいきり
 *@author	HisashiSogabe
 *@data		2006.06.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_274:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_MIST
	SERVER_WAIT
	MESSAGE			HukaiKiriMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_HUKAIKIRI
	SEQ_END
