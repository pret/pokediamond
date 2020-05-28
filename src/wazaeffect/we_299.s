//==============================================================================
/**
 * @file	we_299.s
 * @brief	ブレイズキック			299
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_BUREIZUKIKKU
	
// =============================================================================
//
//
//	■ブレイズキック			299
//
//
// =============================================================================
WEST_BUREIZUKIKKU:
	LOAD_PARTICLE_DROP	0,W_299_SPA
		
	SE_R			SEQ_SE_DP_W172

	ADD_PARTICLE 	0,W_299_299_FOOT_KICK1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_299_299_FOOT_KICK2, EMTFUNC_DEFENCE_POS
	
	ADD_PARTICLE 	0,W_299_299_FIRE_BURN,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6, WE_TOOL_E1, 0, 1, WE_PAL_WHITE, 8, 0

	WAIT			10
	SE_R			SEQ_SE_DP_W007
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_RED, WEDEF_FADE_PARAM,0
	
	WAIT_FLAG
	

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
