//============================================================================
/**
 *
 *@file		be_204.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			204�@�����̓��U���A�������Ɖ�����B
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_204:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWDOWN2|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
