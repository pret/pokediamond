//============================================================================
/**
 *
 *@file		be_006.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			006�@�܂Ђ̒ǉ�����
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_006:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_MAHI|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
