//============================================================================
/**
 *
 *@file		be_049.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			049�@�G���u������v��Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_049:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	SEQ_END
