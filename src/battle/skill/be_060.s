//============================================================================
/**
 *
 *@file		be_060.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			060�@�G�|�P�����́u���΂₳�v���Q�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_060:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AGIDOWN2|ADD_STATUS_DEFENCE
	SEQ_END
