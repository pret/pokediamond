//============================================================================
/**
 *
 *@file		be_071.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			071�@�ǉ����ʂő���̓���U���͂��P�����N������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_071:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEPOWDOWN|ADD_STATUS_DEFENCE
	SEQ_END
