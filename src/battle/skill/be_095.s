//============================================================================
/**
 *
 *@file		be_095.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			095�@�G���Ō�Ɏg�p�����Z���R�s�[����i�R�s�[�����Z�̂o�o�͊�{�l�j�A
 *				 �R�s�[�����Z�͐퓬�I������c��X�P�b�`�̋Z���Ȃ��Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_095:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SKETCH|ADD_STATUS_WAZAKOUKA
	SEQ_END
