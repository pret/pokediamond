//============================================================================
/**
 *
 *@file		be_000.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			000 ���ʍU��
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_000:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
