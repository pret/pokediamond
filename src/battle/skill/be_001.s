//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			001�@�G���u�˂ނ�v��Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_001:
	VALUE	VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_NEMURI|ADD_STATUS_DEFENCE
	SEQ_END
