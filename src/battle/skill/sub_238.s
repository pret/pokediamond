
//============================================================================
/**
 *
 *@file		sub_238.s
 *@brief	�퓬�V�[�P���X
 *			���イ��傭���I���������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.04
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_238:
	MESSAGE		JuuryokuEndMsg,TAG_NONE
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
