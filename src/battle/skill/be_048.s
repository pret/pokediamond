//============================================================================
/**
 *
 *@file		be_048.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			048�@�G�ɗ^�����_���[�W�̂S���̂P���������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_048:
	//�������Ắ݂A�����_���[�W�n���󂯂�Z�̈З͂�2����������
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_048_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_048_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANEKAERI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
