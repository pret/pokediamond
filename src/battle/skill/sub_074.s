

//============================================================================
/**
 *
 *@file		sub_074.s
 *@brief	�퓬�V�[�P���X
 *			�A���R�[���I���V�[�P���X

 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_074:
	MESSAGE			EncoreEndMineMsg,TAG_NICK,SIDE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
