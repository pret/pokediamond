
//============================================================================
/**
 *
 *@file		sub_042.s
 *@brief	�퓬�V�[�P���X
 *			PP���Ȃ��ċZ�������Ȃ��V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_042:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT
	MESSAGE			PPNoneMsg2,TAG_NONE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
