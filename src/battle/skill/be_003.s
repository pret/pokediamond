//============================================================================
/**
 *
 *@file		be_003.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			003�@�G�ɗ^�����_���[�W�̔����̐��l�����g�o���񕜂���
 *
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_003:
	//�Z���ʂ�ǉ����ăV�[�P���X�𔭓�
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SUITORI|ADD_STATUS_WAZAKOUKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
