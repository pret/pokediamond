//============================================================================
/**
 *
 *@file		be_073.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			073�@�ǉ����ʂő���́u�������v���P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_073:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HITDOWN|ADD_STATUS_DEFENCE
	SEQ_END
