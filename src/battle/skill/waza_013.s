
//==============================================================================
/**
 * @file	waza_013.s
 * @brief	‚©‚Ü‚¢‚½‚¿
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_013:
	MESSAGE_PARAM	KamaitachiMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
