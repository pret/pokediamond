//============================================================================
/**
 *
 *@file		be_069.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			069�@�ǉ����ʂő���̖h��͂��P�����N������
 *
 *@author	HisashiSogabe
 *@data		2005.10.27
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_069:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_DEFDOWN|ADD_STATUS_DEFENCE
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
