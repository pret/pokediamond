//============================================================================
/**
 *
 *@file		be_058.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			058�@�G�|�P�����́u���������v���Q�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_058:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_POWDOWN2|ADD_STATUS_DEFENCE
	SEQ_END
