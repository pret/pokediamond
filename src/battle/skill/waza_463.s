
//==============================================================================
/**
 * @file	waza_463.s
 * @brief	マグマストーム
 * @author	soga
 * @date	2006.07.13
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_463:
	MESSAGE_PARAM	StormMineMsg,TAG_NICK,SIDE_DEFENCE
	JUMP_BE_SEQ
