
//============================================================================
/**
 *
 *@file		sub_001.s
 *@brief	�퓬�V�[�P���X
 *			�Z�����V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.07.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_001:
//���ڒǉ��̏ꍇ�A�ǉ����ʃV�[�P���X�Ń��b�Z�[�W��Z�G�t�F�N�g���o���̂ł����ł͏o���Ȃ�
	IF			IF_FLAG_EQ,BUF_PARA_TSUIKA_TYPE,ADD_STATUS_DIRECT,NoWazaEffect
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
NoWazaEffect:
	SEQ_END
