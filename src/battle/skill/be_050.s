//============================================================================
/**
 *
 *@file		be_050.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			050�@�g�p�����|�P�����́u���������v���Q�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_050:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_POWUP2|ADD_STATUS_ATTACK
	SEQ_END
