
//============================================================================
/**
 *
 *@file		sub_226.s
 *@brief	�퓬�V�[�P���X
 *			�{���e�b�J�[�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_226:
	GOSUB		SUB_SEQ_HANEKAERI2
	IF			IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TSUIKA,SUB_226_END
	GOSUB		SUB_SEQ_MAHI
SUB_226_END:
	SEQ_END
