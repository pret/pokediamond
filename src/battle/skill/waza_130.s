
//==============================================================================
/**
 * @file	waza_130.s
 * @brief	���P�b�g����
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_130:
	MESSAGE_PARAM	RocketzutukiMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
