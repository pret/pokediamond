//============================================================================
/**
 *
 *@file		be_238.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			238�@�����̍U���͂Ɩh��͂����ւ���B�⏕���ʂ͓���ւ��Ȃ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_238:
	VALUE		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWER_TRICK|ADD_STATUS_WAZAKOUKA
	SEQ_END
