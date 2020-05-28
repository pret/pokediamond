
//==============================================================================
/**
 * @file	waza_467.s
 * @brief	シャドーダイブ
 * @author	soga
 * @date	2006.05.05
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_467:
	MESSAGE_PARAM	ShadowdiveMineMsg,TAG_NICK,SIDE_ATTACK
	JUMP_BE_SEQ
