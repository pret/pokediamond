
//============================================================================
/**
 *
 *@file		sub_177.s
 *@brief	�퓬�V�[�P���X
 *			������Ԃ蔭�����b�Z�[�W
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_177:
	MESSAGE		KatayaburiMineMsg,TAG_NICK_TOKU,SIDE_WORK,SIDE_CLIENT_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
