//============================================================================
/**
 *
 *@file		be_212.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			212�@�U���Ƒf�������オ��B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_212:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_RYUUNOMAI|ADD_STATUS_ATTACK
	SEQ_END
