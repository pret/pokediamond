//============================================================================
/**
 *
 *@file		be_051.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			051�@�g�p�����|�P�����́u�ڂ�����v���Q�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_051:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_DEFUP2|ADD_STATUS_ATTACK
	SEQ_END
