//============================================================================
/**
 *
 *@file		be_099.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			099�@�c��̂g�o�����Ȃ����A�G�ɑ傫�ȃ_���[�W��^����
 *
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_099:
	JITABATA
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
