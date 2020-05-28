
//==============================================================================
/**
 * @file	waza_153.s
 * @brief	‚¾‚¢‚Î‚­‚Í‚Â
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_153:
	INC_RECORD	SIDE_ATTACK,CLIENT_BOOT_TYPE_MINE,RECID_WAZA_DAIBAKUHATU
	JUMP_BE_SEQ
