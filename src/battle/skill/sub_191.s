
//============================================================================
/**
 *
 *@file		sub_191.s
 *@brief	�퓬�V�[�P���X
 *			�Ȃ܂��Ă���V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_191:
	MESSAGE		NamakeMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	KEEP_OFF	SIDE_ATTACK
	SEQ_END
