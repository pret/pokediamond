//============================================================================
/**
 *
 *@file		be_043.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			043 �N���e�B�J���q�b�g���o�₷��
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_043:
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
