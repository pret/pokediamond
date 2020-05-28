
//==============================================================================
/**
 * @file	waza_353.s
 * @brief	‚Í‚ß‚Â‚Ì‚Ë‚ª‚¢
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_353:
	MESSAGE_PARAM	HametunonegaiMineMsg,TAG_NICK_WAZA,SIDE_ATTACK,SIDE_ATTACK
	JUMP_BE_SEQ
