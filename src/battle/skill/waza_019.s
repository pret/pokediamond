
//==============================================================================
/**
 * @file	waza_019.s
 * @brief	‚»‚ç‚ð‚Æ‚Ô
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_019:
	MESSAGE_PARAM	SorawotobuMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
