
//============================================================================
/**
 *
 *@file		sub_028.s
 *@brief	�퓬�V�[�P���X
 *			������Â��ōU���ł��Ȃ��V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_028:
	MESSAGE			FreezingMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_KOORI
	SERVER_WAIT
	SEQ_END
