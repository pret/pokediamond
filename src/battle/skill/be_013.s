//============================================================================
/**
 *
 *@file		be_013.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			013�@�g�p�����|�P�����́u�Ƃ������v���P�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_013:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_SPEPOWUP|ADD_STATUS_ATTACK
	SEQ_END
