//============================================================================
/**
 *
 *@file		be_107.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			107�@�G���u�˂ނ�v��Ԃ̎��������ʂ̂���Z�i�u�˂ނ�v��ԂłȂ��ƋZ�͎��s����j�A
 *				 �G�|�P���������ޏ�Ԃɂ���	
 *
 *@author	HisashiSogabe
 *@data		2006.01.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_107:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AKUMU|ADD_STATUS_WAZAKOUKA
	SEQ_END
