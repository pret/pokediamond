
//============================================================================
/**
 *
 *@file		sub_256.s
 *@brief	�퓬�V�[�P���X
 *			�������Ƃ𕷂����ɕʂ̋Z���o���V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_256:
	WAIT			MSG_WAIT/2
	MESSAGE			OrderIgnoreMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
