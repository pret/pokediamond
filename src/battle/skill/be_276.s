
//============================================================================
/**
 *
 *@file		be_276.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			276�@�ǉ����ʂŎ����̓��U���P�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2006.05.18
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_276:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWUP|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END


