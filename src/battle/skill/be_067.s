//============================================================================
/**
 *
 *@file		be_067.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			067�@�G���u�}�q�v��Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_067:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	SEQ_END
