//============================================================================
/**
 *
 *@file		be_019.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			019�@�G�|�P�����́u�ڂ�����v���P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_019:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFDOWN|ADD_STATUS_DEFENCE
	SEQ_END
