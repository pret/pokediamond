
//============================================================================
/**
 *
 *@file		sub_073.s
 *@brief	�퓬�V�[�P���X
 *			�A���R�[�����ʔ����V�[�P���X
 *
 *@author	HisashiSogabe
 *@data		2006.01.19
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_073:
	ENCORE		Umakukimaran
	GOSUB		SUB_SEQ_WAZA_OUT_EFF
	MESSAGE		EncoreMineMsg,TAG_NICK,SIDE_DEFENCE
	SERVER_WAIT
	WAIT		MSG_WAIT
Umakukimaran:
	SEQ_END
