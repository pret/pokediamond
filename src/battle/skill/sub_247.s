
//============================================================================
/**
 *
 *@file		sub_247.s
 *@brief	�퓬�V�[�P���X
 *			�₯�ǁ{�Ђ�ނ̒ǉ����ʃV�[�P���X�i�^�����_���[�W��1/2�j
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_247:
	ADD_STATUS_CHECK	SUB_247_NEXT
	GOSUB				SUB_SEQ_YAKEDO
SUB_247_NEXT:
	ADD_STATUS_CHECK	SUB_247_END
	GOSUB				SUB_SEQ_HIRUMU
SUB_247_END:
	SEQ_END
