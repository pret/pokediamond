//============================================================================
/**
 *
 *@file		be_011.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			011�@�g�p�����|�P�����́u�ڂ�����v���P�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_011:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP|ADD_STATUS_ATTACK
	SEQ_END
