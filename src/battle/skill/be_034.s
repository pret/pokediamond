//============================================================================
/**
 *
 *@file		be_034.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			034�@�퓬�I����Ɏg�p�����|�P�����̃��x���~�U���񐔁~5�̂�������ɓ���
 *
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_034:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_NEKONIKOBAN|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
