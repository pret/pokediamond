//============================================================================
/**
 *
 *@file		be_200.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			200�@�}���ɓ�����₷���{�ǉ����ʂł₯�ǂɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_200:
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
