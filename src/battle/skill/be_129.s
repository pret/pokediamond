//============================================================================
/**
 *
 *@file		be_129.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			129�@�u���߂��v�u�܂����v���̘A���Z���甲���o�����Ƃ��o����B�u��ǂ肬�̃^�l�v�u�܂��т��v�������������
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_129:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_KOUSOKUSPIN|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
