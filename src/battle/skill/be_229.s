//============================================================================
/**
 *
 *@file		be_229.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			229�@�З͂̍����U�����J��o�������o���邪�u�ڂ�����v�u�Ƃ��ڂ��v���P�i�K�������Ă��܂��B
 *				 �U����A�X�e�[�^�X�_�E�������B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_229:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_INFIGHT|ADD_STATUS_ATTACK|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
