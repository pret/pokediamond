//============================================================================
/**
 *
 *@file		be_004.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			004�@�₯�ǂ̒ǉ�����
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_004:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
