
//============================================================================
/**
 *
 *@file		sub_157.s
 *@brief	�퓬�V�[�P���X
 *			���イ��傭NG�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.13
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_157:
	MESSAGE			JuuryokuNGMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
