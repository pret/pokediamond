//============================================================================
/**
 *
 *@file		be_101.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			101�@�G�̂g�o��K���P�c���i�݂˂����ł͓|���܂���j
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_101:
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
