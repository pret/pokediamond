//============================================================================
/**
 *
 *@file		be_080.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			080�@�g�p�������̃^�[���͍s�����o���Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_080:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANDOU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
