//============================================================================
/**
 *
 *@file		be_188.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			188�@�Ώۂ���������������Ă��Ȃ���Ԃɂ��܂��B�퓬�I���㓹��͌��ɖ߂�B
 *				�i���̏�Ԃ̎��ɂʂ��ނ��g�p���Ă��K�����s����j
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_188:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HATAKIOTOSU|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
