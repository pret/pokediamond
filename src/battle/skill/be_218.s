//============================================================================
/**
 *
 *@file		be_218.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			218�@�З͂͂��邪�A�U������x�ɔ��Ă��܂��A�f�����������Ă����B�P��̍U���ɂ��P�i�K������B
 *
 *@author	HisashiSogabe
 *@data		2006.02.10
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_218:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_AGIDOWN|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
