//============================================================================
/**
 *
 *@file		be_203.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			203�@�V�C�ɂ���ă^�C�v���ς��@�͂�F���@���߁F���@���Ȃ��炵�F��@�����F�X�@�V�C��Ԃ̎��A�З͂��{�ɂȂ�
 *
 *@author	HisashiSogabe
 *@data		2006.02.09
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_003:
	WEATHER_BALL
	CRITICAL_CHECK
	DAMAGE_CALC
	SEQ_END
