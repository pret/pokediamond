//============================================================================
/**
 *
 *@file		be_269.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			269�@�G�ɗ^�����_���[�W�̂Q���̂P���������󂯂�
 *
 *@author	HisashiSogabe
 *@data		2006.05.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_269:
	//�������Ắ݂A�����_���[�W�n���󂯂�Z�̈З͂�2����������
	TOKUSEI_CHECK	TOKUSEI_NO_HAVE,SIDE_ATTACK,TOKUSYU_SUTEMI,BE_269_NEXT
	VALUE			VAL_SET,BUF_PARA_DAMAGE_VALUE,12
BE_269_NEXT:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_HANEKAERI3|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
