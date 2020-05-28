//==============================================================================
/**
 * @file	we_278.s
 * @brief	リサイクル			278
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RISAIKURU
	
// =============================================================================
//
//
//	■リサイクル			278
//
//
// =============================================================================
WEST_RISAIKURU:
	
	LOAD_PARTICLE_DROP	0,W_278_SPA
	ADD_PARTICLE 	0,W_278_278_RECYCLE, EMTFUNC_ATTACK_POS
	
	SE_L			SEQ_SE_DP_W278
	//SE_REPEAT_L		SEQ_SE_DP_W036,24,3
	WAIT			10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 12

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
