//============================================================================
/**
 *
 *@file		be_235.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			235�@�o�o���c�肪���Ȃ��قǈЗ͂������Ȃ�B�З͗ʁi40�A50�A60�A80�A200�j����86
 *
 *@author	HisashiSogabe
 *@data		2005.10.03
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_235:
	KIRIHUDA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
