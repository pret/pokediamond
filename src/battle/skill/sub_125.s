
//============================================================================
/**
 *
 *@file		sub_125.s
 *@brief	�퓬�V�[�P���X
 *			�݂̂��ރV�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.06
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_125:
	ATTACK_MESSAGE
	SERVER_WAIT
	GOSUB			SUB_SEQ_KAIFUKU
	MESSAGE			TakuwaeruEndMineMsg,TAG_NICK,SIDE_ATTACK
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
