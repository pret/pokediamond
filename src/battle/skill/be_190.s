//============================================================================
/**
 *
 *@file		be_190.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			190�@�����̂g�o������ƁA����ɔ�Ⴕ�ċZ�̈З͂�������B�З́��З́~�i�c�g�o�^�l�`�w�g�o�j
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_190:
	HUNKA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
