//============================================================================
/**
 *
 *@file		be_260.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			260�@������̒ǉ�����+������Ԃ̂Ƃ��A�Z���K����������B
 *
 *@author	HisashiSogabe
 *@data		2006.04.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_260:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_KOORI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
