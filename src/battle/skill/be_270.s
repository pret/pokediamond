//============================================================================
/**
 *
 *@file		be_270.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			270�@�m���ɂȂ邪�A���ɏo�Ă���|�P�����̗̑͂Ə�Ԉُ�Ƃo�o��S�񕜂�����B�T���|�P���������Ȃ��ꍇ�͎��s�B
 *
 *@author	HisashiSogabe
 *@data		2006.05.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_270:
	RESHUFFLE_CHECK		SIDE_ATTACK,POKE_LIST_ON,Umakukimaran
	VALUE				VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_MIKADUKINOMAI|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
