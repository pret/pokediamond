
//============================================================================
/**
 *
 *@file		sub_034.s
 *@brief	�퓬�V�[�P���X
 *			���낢����V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_034:
	KUROIKIRI
	MESSAGE		KuroikiriMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
