//============================================================================
/**
 *
 *@file		be_102.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			102�@�����|�P�����S�ẴX�e�[�^�X�ُ���񕜂���
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_102:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_IYASINOSUZU|ADD_STATUS_WAZAKOUKA
	SEQ_END
