//============================================================================
/**
 *
 *@file		be_033.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			033�@�G���u�ǂ��v��Ԃɂ���A���̓ł̃_���[�W�̓^�[�����Ƃɑ����Ă���
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_033:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_DOKUDOKU|ADD_STATUS_DEFENCE
	SEQ_END
