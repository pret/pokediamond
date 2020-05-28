
//==============================================================================
/**
 * @file	waza_128.s
 * @brief	‚©‚ç‚Å‚Í‚³‚Þ
 * @author	soga
 * @date	2005.10.06
 */
//==============================================================================

	.text

	.include	"waza_seq_def.h"

WAZA_128:
	MESSAGE_PARAM	KaraM2MMsg,TAG_NICK_NICK,SIDE_DEFENCE,SIDE_ATTACK
	JUMP_BE_SEQ
