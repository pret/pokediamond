
//============================================================================
/**
 *
 *@file		sub_197.s
 *@brief	�퓬�V�[�P���X
 *			�X���[�X�^�[�g�I���V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_197:
	MESSAGE			SlowStartEndMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END

