
//============================================================================
/**
 *
 *@file		sub_180.s
 *@brief	�퓬�V�[�P���X
 *			�Ђ炢���񁕂�т݂��V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.02.20
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_180:
	ATTACK_MESSAGE
	SERVER_WAIT
	WAIT			MSG_WAIT/2
	MESSAGE			HiraishinMineMsg,TAG_NICK_TOKU,SIDE_DEFENCE,SIDE_DEFENCE
	SERVER_WAIT
	WAIT			MSG_WAIT
	SEQ_END
