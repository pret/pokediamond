//============================================================================
/**
 *
 *@file		be_139.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			139�@�ǉ����ʂŎ����̍U���͂��P�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_139:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_POWUP|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
