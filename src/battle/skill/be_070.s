//============================================================================
/**
 *
 *@file		be_070.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			070�@�ǉ����ʂő���̑f�������P�����N������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_070:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_DEFENCE
	SEQ_END
