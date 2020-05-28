
//==============================================================================
/**
 * @file	waza_076.s
 * @brief	ソーラービーム
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_076:
	MESSAGE_PARAM	SolarbeamMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
