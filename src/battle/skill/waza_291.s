
//==============================================================================
/**
 * @file	waza_291.s
 * @brief	ダイビング
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_291:
	MESSAGE_PARAM	DivingMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
