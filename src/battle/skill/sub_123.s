
//============================================================================
/**
 *
 *@file		sub_123.s
 *@brief	�퓬�V�[�P���X
 *			�ӂ��낾�����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_123:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE_WORK
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	SEQ_END
