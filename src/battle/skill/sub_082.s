
//============================================================================
/**
 *
 *@file		sub_082.s
 *@brief	�퓬�V�[�P���X
 *			�݂��Â�ǉ����ʃV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.24
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_082:
	MESSAGE		MichidureMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	//�݂��Â�t���O��ON
	PSP_VALUE	VAL_BIT,SIDE_ATTACK,ID_PSP_condition2,CONDITION2_MICHIDURE
	SEQ_END
