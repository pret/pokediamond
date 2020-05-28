
//==============================================================================
/**
 * @file	waza_120.s
 * @brief	‚¶‚Î‚­
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_120:
	INC_RECORD	SIDE_ATTACK,CLIENT_BOOT_TYPE_MINE,RECID_WAZA_ZIBAKU
	JUMP_BE_SEQ
