
//============================================================================
/**
 *
 *@file		sub_172.s
 *@brief	�퓬�V�[�P���X
 *			����͂炢���b�Z�[�W�V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.15
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_172:
	MESSAGE		KiriharaiKoukaEndMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_WORK
	SERVER_WAIT
	WAIT		MSG_WAIT
	SEQ_END
