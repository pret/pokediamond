
//============================================================================
/**
 *
 *@file		sub_285.s
 *@brief	�퓬�V�[�P���X
 *			�����v���b�V���[�������b�Z�[�W
 *@author	HisashiSogabe
 *@data		2006.07.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_285:
	MESSAGE			PressureMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
