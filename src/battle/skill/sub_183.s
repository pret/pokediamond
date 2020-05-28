
//============================================================================
/**
 *
 *@file		sub_183.s
 *@brief	戦闘シーケンス
 *			あめふらしシーケンス
 *@author	HisashiSogabe
 *@data		2006.02.22
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_183:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_RAIN
	SERVER_WAIT
	MESSAGE		AmehurashiMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	VALUE		VAL_NBIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_TENKI
	VALUE		VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_AMEHURASHI
	SEQ_END
