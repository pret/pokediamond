//============================================================================
/**
 *
 *@file		be_230.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			230�@�U�����鑊�����ɍU�������Ƃ��З͂��キ�A�x���ꍇ�͈З͂��Q�{�ɂȂ�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_230:
	TAMEUCHI
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
