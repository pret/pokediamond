//============================================================================
/**
 *
 *@file		be_066.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			066�@�G���u�ǂ��v��Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.12.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_066:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	SEQ_END
