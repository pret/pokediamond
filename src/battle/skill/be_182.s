//============================================================================
/**
 *
 *@file		be_182.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			182�@�U�����q�b�g����ƁA�����̍U���́A�h��͂��P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_182:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_BAKADIKARA|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
