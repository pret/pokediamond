//============================================================================
/**
 *
 *@file		be_076.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			076�@�ǉ����ʂő��������������
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_076:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KONRAN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
