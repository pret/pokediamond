//============================================================================
/**
 *
 *@file		be_140.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			140�@�ǉ����ʂłT�̃X�e�[�^�X���P�i�K�オ��
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_140:
	VALUE			VAL_SET,BUF_PARA_ADD_STATUS_INDIRECT,ADD_COND2_GENSHINOCHIKARA|ADD_STATUS_ATTACK
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
