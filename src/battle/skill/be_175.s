//============================================================================
/**
 *
 *@file		be_175.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			175�@�T�^�[���̊ԁA����͍U���Z�����o���Ȃ��Ȃ�B
 *				 ���̋Z��I�ڂ��Ƃ���Ɓu�����������́@���傤�͂@����ā@���������������@�������Ȃ��I�v�ƂȂ�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_175:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_CHOUHATSU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA
	SEQ_END
