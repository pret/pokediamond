//============================================================================
/**
 *
 *@file		be_202.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			202�@�ǉ����ʂłǂ��ǂ���Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_202:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKUDOKU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
