//============================================================================
/**
 *
 *@file		be_094.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			094�@���̃^�[���̍U����K������������
 *
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_094:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_LOCKON|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT
	SEQ_END
