
//============================================================================
/**
 *
 *@file		sub_008.s
 *@brief	�퓬�V�[�P���X
 *			�����鎸�s�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.07.29
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_008:
	MESSAGE			EscapeNGMsg,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
