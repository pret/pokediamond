
//============================================================================
/**
 *
 *@file		sub_249.s
 *@brief	�퓬�V�[�P���X
 *			�܂Ё{�Ђ�ނ̒ǉ����ʃV�[�P���X�i�^�����_���[�W��1/2�j
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_249:
	ADD_STATUS_CHECK	SUB_249_NEXT
	GOSUB				SUB_SEQ_MAHI
SUB_249_NEXT:
	ADD_STATUS_CHECK	SUB_249_END
	GOSUB				SUB_SEQ_HIRUMU
SUB_249_END:
	SEQ_END
