
//============================================================================
/**
 *
 *@file		sub_054.s
 *@brief	�퓬�V�[�P���X
 *			���낢����V�[�P���X
 *@author	HisashiSogabe
 *@data		2006.01.17
 *
 */
//============================================================================
	.text

	.include	"waza_seq_def.h"

SUB_054:
	SIROIKIRI		Umakukimaran
	MESSAGE_PARAM	ShiroikiriMineMsg,TAG_NONE_DIR,SIDE_ATTACK
	GOSUB			SUB_SEQ_KABE
Umakukimaran:
	SEQ_END
