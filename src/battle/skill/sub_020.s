
//============================================================================
/**
 *
 *@file		sub_020.s
 *@brief	�퓬�V�[�P���X
 *			�˂ނ�V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.11.30
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_020:
	MESSAGE			SleepMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_NEMURI
	SERVER_WAIT
	SEQ_END
