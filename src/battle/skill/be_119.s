//============================================================================
/**
 *
 *@file		be_119.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			119�@�g�p����x�ɋZ�̈З͂��{�ɂȂ��Ă����A�U�����P�x�ł��͂����ƈЗ͖͂߂�
 *
 *@author	HisashiSogabe
 *@data		2005.01.31
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_119:
	RENZOKUGIRI
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
