
//============================================================================
/**
 *
 *@file		sub_040.s
 *@brief	�퓬�V�[�P���X
 *			�����񂪂Ƃ����V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.07
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_040:
	MESSAGE		KonranEndMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
