//============================================================================
/**
 *
 *@file		be_072.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			072�@�ǉ����ʂő���̓���h��͂��P�����N������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_072:
	CRITICAL_CHECK
	DAMAGE_CALC
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SPEDEFDOWN|ADD_STATUS_DEFENCE
	SEQ_END
