//============================================================================
/**
 *
 *@file		be_025.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			025�@�G�Ǝ����̃|�P�����̃X�e�[�^�X�i�̂���傭�j�ُ̈�����ɖ߂�
 *
 *@author	HisashiSogabe
 *@data		2005.12.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_025:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KUROIKIRI|ADD_STATUS_WAZAKOUKA
	SEQ_END
