//============================================================================
/**
 *
 *@file		be_082.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			082�@�G���Ō�Ɏg�����Z���A���̐퓬�������R�s�[���Ďg����i�R�s�[�Z�̂o�o�͂T�j�A�G���Z���g���O�Ɏg���ƋZ�͎��s����
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_082:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MONOMANE|ADD_STATUS_WAZAKOUKA
	SEQ_END
