
//============================================================================
/**
 *
 *@file		sub_053.s
 *@brief	�퓬�V�[�P���X
 *			���ה������ʃV�[�P���X�i�Ђ���̂��ׁA���t���N�^�[�Ȃǁj
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_053:
	GOSUB			SUB_SEQ_WAZA_OUT_EFF
	MESSAGE_WORK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
