
//============================================================================
/**
 *
 *@file		sub_248.s
 *@brief	�퓬�V�[�P���X
 *			������{�Ђ�ނ̒ǉ����ʃV�[�P���X�i�^�����_���[�W��1/2�j
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_248:
	ADD_STATUS_CHECK	SUB_248_NEXT
	GOSUB				SUB_SEQ_KOORI
SUB_248_NEXT:
	ADD_STATUS_CHECK	SUB_248_END
	GOSUB				SUB_SEQ_HIRUMU
SUB_248_END:
	SEQ_END
