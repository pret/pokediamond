//============================================================================
/**
 *
 *@file		be_111.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			111�@���̃^�[���̓G�̍U����h�䂷��B�A���ŏo���Ɛ��������������Ă���
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_111:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_GUARD|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
