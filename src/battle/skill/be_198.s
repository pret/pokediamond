//============================================================================
/**
 *
 *@file		be_198.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			198�@�G�ɗ^�����_���[�W�̂R���̂P���������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_198:
	//�������Ắ݂A�����_���[�W�n���󂯂�Z�̈З͂�2����������
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_198_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_198_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANEKAERI2|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
