//============================================================================
/**
 *
 *@file		be_068.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			068�@�ǉ����ʂő���̍U���͂��P�����N������
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_068:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWDOWN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
