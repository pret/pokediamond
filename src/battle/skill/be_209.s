//============================================================================
/**
 *
 *@file		be_209.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			209�@�}���ɓ�����₷���B�P�O���̊m���ő�����ǂ���Ԃɂ���B
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_209:
	VALUE			VAL_ADD,BUF_PARA_CRITICAL_COUNT,1
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND_DOKU|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
