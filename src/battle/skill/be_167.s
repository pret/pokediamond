//============================================================================
/**
 *
 *@file		be_167.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			167�@������₯�Ǐ�Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_167:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND_YAKEDO|ADD_STATUS_DEFENCE
	SEQ_END
