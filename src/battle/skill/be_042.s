//============================================================================
/**
 *
 *@file		be_042.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			042�@�Q�`�T�^�[���̊ԃ_���[�W��^����B���̊ԁA����͓������Ȃ�
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_042:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_SHIME|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_CHECK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
