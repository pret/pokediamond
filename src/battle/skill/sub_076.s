
//============================================================================
/**
 *
 *@file		sub_076.s
 *@brief	�퓬�V�[�P���X
 *			ATTACK_MESSAGE�ƋZ�G�t�F�N�g���Z�b�g�ɂȂ����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.23
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_076:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAZA_EFFECT		SIDE_ATTACK
	SERVER_WAIT
	SEQ_END
