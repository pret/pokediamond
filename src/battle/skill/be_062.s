//============================================================================
/**
 *
 *@file		be_062.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			062�@�G�|�P�����́u�Ƃ��ڂ��v���Q�i�K������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_062:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEDEFDOWN2|ADD_STATUS_DEFENCE
	SEQ_END
