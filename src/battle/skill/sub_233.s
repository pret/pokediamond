
//============================================================================
/**
 *
 *@file		sub_233.s
 *@brief	�퓬�V�[�P���X
 *			�����������I���������b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.05.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_233:
	MESSAGE		OikazeMineEndMsg,TAG_NONE_DIR,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
