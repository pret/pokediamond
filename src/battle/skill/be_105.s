//============================================================================
/**
 *
 *@file		be_105.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			105�@���肪�������Ă���ǂ����𓐂�
 *
 *@author	HisashiSogabe
 *@data		2006.01.25
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_105:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_DOROBOU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHP
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
