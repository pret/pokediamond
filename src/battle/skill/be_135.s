//============================================================================
/**
 *
 *@file		be_135.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			135�@�Z���g���|�P�����ɂ���āA�^�C�v�A�З͂��ς��
 *
 *@author	HisashiSogabe
 *@data		2006.02.02
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_135:
	MEZAMERU_POWER
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
