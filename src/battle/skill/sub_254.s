
//============================================================================
/**
 *
 *@file		sub_254.s
 *@brief	�퓬�V�[�P���X
 *			�˂ނ�Ȃ��炢�����Ƃ������Ȃ��V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_254:
	WAIT		MSG_WAIT/2
	MESSAGE		OrderIgnoreSleepMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
