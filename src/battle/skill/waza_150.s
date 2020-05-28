
//==============================================================================
/**
 * @file	waza_150.s
 * @brief	‚Í‚Ë‚é
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_150:
	INC_RECORD	SIDE_ATTACK,CLIENT_BOOT_TYPE_MINE,RECID_WAZA_HANERU
	JUMP_BE_SEQ
