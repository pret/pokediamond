//============================================================================
/**
 *
 *@file		be_253.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			253�@�G�ɗ^�����_���[�W�̂R���̂P���������󂯂�{�ǉ����ʂł₯�ǂɂȂ�{�������Ԃ��Ƃ���B
 *				 �������������Ԃł��Z���o����B
 *
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_253:
	//�������Ắ݂A�����_���[�W�n���󂯂�Z�̈З͂�2����������
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_253_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_253_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HEAT_ATTACK|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_PROB
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
