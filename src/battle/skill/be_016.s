//============================================================================
/**
 *
 *@file		be_016.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			016�@�g�p�����|�P�����́u��𗦁v���P�i�K�グ��
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_016:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_AVOIDUP|ADD_STATUS_ATTACK
	SEQ_END
