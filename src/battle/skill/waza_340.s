
//==============================================================================
/**
 * @file	waza_340.s
 * @brief	�Ƃт͂˂�
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_340:
	MESSAGE_PARAM	TobihaneruMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
