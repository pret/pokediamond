//============================================================================
/**
 *
 *@file		be_187.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			187�@�g�p�������̃^�[���I�����A�g�p�����Ώۂ���Ɏc���Ă����Ȃ�΁A���̑Ώۂ͖����ԂɂȂ�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.08
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_187:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AKUBI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
