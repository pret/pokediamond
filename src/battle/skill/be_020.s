//============================================================================
/**
 *
 *@file		be_020.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			020�@�G�|�P�����́u���΂₳�v���P�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_020:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_DEFENCE
	SEQ_END
