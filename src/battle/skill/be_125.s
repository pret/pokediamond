//============================================================================
/**
 *
 *@file		be_125.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			125�@�₯�ǂ̒ǉ����ʁ{�������Ԃ��Ƃ���B�������������Ԃł��Z���o����B
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_125:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
