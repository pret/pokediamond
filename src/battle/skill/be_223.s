//============================================================================
/**
 *
 *@file		be_223.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			223�@�u�܂���v�u�݂���v�����Ă��鑊��ɂ̂ݍU����������A�܂�����ʂ���������B
 *				 ����́A�܂���͉�������邪�����I�ɂ͐����������ƂɂȂ�B�܂���쓮��Ƀt�F�C���g�̓�������s�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.16
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_223:
	FEINT			Umakukimaran
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_FEINT|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END

Umakukimaran:
	VALUE			VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
