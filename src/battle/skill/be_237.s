//============================================================================
/**
 *
 *@file		be_237.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			237�@����̂g�o���܂񂽂�ȂقǈЗ͂������B�З͌v�Z���F�P+150�~�i�G�̌��݂̂g�o���G�̍ő�g�o�j
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_237:
	SIBORITORU
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
