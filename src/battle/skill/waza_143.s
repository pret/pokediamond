
//==============================================================================
/**
 * @file	waza_143.s
 * @brief	ゴッドバード
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_143:
	MESSAGE_PARAM	GodbirdMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
