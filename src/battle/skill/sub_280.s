
//============================================================================
/**
 *
 *@file		sub_280.s
 *@brief	�퓬�V�[�P���X
 *			AttackClient��DefenceClient�̕��A
 *@author	HisashiSogabe
 *@data		2006.07.01
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_280:
	VALUE_WORK	VAL_GET,BUF_PARA_ATTACK_CLIENT_TEMP,BUF_PARA_ATTACK_CLIENT
	VALUE_WORK	VAL_GET,BUF_PARA_DEFENCE_CLIENT_TEMP,BUF_PARA_DEFENCE_CLIENT
	SEQ_END

