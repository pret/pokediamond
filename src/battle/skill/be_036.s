
//============================================================================
/**
 *
 *@file		be_036.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			036�@�Q���̊m���œG���u�}�q�v�A�u�₯�ǁv�A�u������v�̂ǂꂩ�̏�Ԃɂ���
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_036:
	RANDOM_GET		2,ADD_COND_YAKEDO
	VALUE			VAL_ADD,BUF_PARA_CALC_WORK,ADD_STATUS_DEFENCE
	VALUE_WORK		VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,BUF_PARA_CALC_WORK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
