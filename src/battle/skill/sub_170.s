
//============================================================================
/**
 *
 *@file		sub_170.s
 *@brief	�퓬�V�[�P���X
 *			�q�[�g�A�^�b�N�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_170:
	GOSUB		SUB_SEQ_HANEKAERI2
	IF			IF_FLAG_NBIT,BUF_PARA_SERVER_STATUS_FLAG,SERVER_STATUS_FLAG_TSUIKA,SUB_170_END
	GOSUB		SUB_SEQ_YAKEDO
SUB_170_END:
	SEQ_END
