
//============================================================================
/**
 *
 *@file		sub_057.s
 *@brief	�퓬�V�[�P���X
 *			MESSAGE_WORK�\���V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_057:
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
