//============================================================================
/**
 *
 *@file		be_023.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			023�@�G�|�P�����́u�������v���P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_023:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_HITDOWN|ADD_STATUS_DEFENCE
	SEQ_END
