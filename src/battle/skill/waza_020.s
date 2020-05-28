
//==============================================================================
/**
 * @file	waza_020.s
 * @brief	‚µ‚ß‚Â‚¯‚é
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_020:
	MESSAGE_PARAM	ShimeM2MMsg,TAG_NICK_NICK,SIDE_DEFENCE,SIDE_ATTACK
	JUMP_BE_SEQ
