
//============================================================================
/**
 *
 *@file		sub_032.s
 *@brief	�퓬�V�[�P���X
 *			�܂ЂōU���ł��Ȃ��V�[�P���X
 *@author	HisashiSogabe
 *@data		2005.12.05
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_032:
	MESSAGE			ParalyzedMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	STATUS_EFFECT	SIDE_ATTACK,STATUS_MAHI
	SERVER_WAIT
	KEEP_OFF		SIDE_ATTACK
	SEQ_END
