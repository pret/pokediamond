//============================================================================
/**
 *
 *@file		be_220.s
 *@brief	�퓬�V�[�P���X�iBattleEffect�j
 *			220�@�m���ɂȂ邪�A���ɏo�Ă���|�P�����̗̑͂Ə�Ԉُ��S�񕜂�����B�y�����݂₰�z�̉񕜔ŁB
 *				 �T���|�P���������Ȃ��ꍇ�͎��s�B
 *
 *@author	HisashiSogabe
 *@data		2006.02.14
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

BE_220:
	RESHUFFLE_CHECK		SIDE_ATTACK,POKE_LIST_ON,Umakukimaran
	VALUE				VAL_SET,BUF_PARA_ADD_STATUS_DIRECT,ADD_COND2_IYASINONEGAI|ADD_STATUS_WAZAKOUKA
	SEQ_END

Umakukimaran:
	VALUE				VAL_BIT,BUF_PARA_WAZA_STATUS_FLAG,WAZA_STATUS_FLAG_UMAKUKIMARAN
	SEQ_END
