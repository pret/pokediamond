
//============================================================================
/**
 *
 *@file		sub_276.s
 *@brief	�퓬�V�[�P���X
 *			�o���l�擾�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.06.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_276:
	GET_EXP_CHECK	NoExpGet		//�o���l�Q�b�g�������Ȃ��Ƃ��̂Ƃѐ���w��
GetExpLoop:
	GET_EXP_INIT
	GET_EXP
	GET_EXP_LOOP	GetExpLoop		//�o���l�Q�b�g�������J��Ԃ��Ƃ��̂Ƃѐ���w��
NoExpGet:
	SEQ_END
