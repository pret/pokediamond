//==============================================================================
/**
 * @file	we_005.s
 * @brief	メガトンパンチ			5
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEGATONPANTI
	
// =============================================================================
//
//
//	■メガトンパンチ			5
//
//
// =============================================================================
WEST_MEGATONPANTI:
	
	LOAD_PARTICLE_DROP	0,W_005_SPA
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	
	ADD_PARTICLE 	0,W_005_PUNCH_MEGA, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_005_B_BURN_RED2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_005_PUNCH_HIT02, EMTFUNC_DEFENCE_POS

	SE_WAITPLAY_R	SEQ_SE_DP_140,1

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
