
//============================================================================
/**
 *
 *@file		sub_272.s
 *@brief	�퓬�V�[�P���X
 *			�t�B�[���h�V��ł����
 *@author	HisashiSogabe
 *@data		2006.06.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_272:
	STATUS_EFFECT	SIDE_MINE,STATUS_WEATHER_ICE
	SERVER_WAIT
	MESSAGE			ArareMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	VALUE			VAL_BIT,BUF_PARA_FIELD_CONDITION,FIELD_CONDITION_YUKIHURASHI
	SEQ_END
