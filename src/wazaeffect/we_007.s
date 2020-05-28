//==============================================================================
/**
 * @file	we_007.s
 * @brief	ほのおのパンチ			7
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HONOONOPANTI
	
// =============================================================================
//
//
//	■ほのおのパンチ			7
//
//
// =============================================================================
WEST_HONOONOPANTI:
	
	LOAD_PARTICLE_DROP	0,W_007_SPA
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_RED_BROWN,

	ADD_PARTICLE 	0,W_007_007_FIRE_PUNCH, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_007_007_FIRE_BURN,  EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_007_007_FIRE_UP,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP
	
	SE_R			SEQ_SE_DP_BASI

	SE_WAITPLAY_R	SEQ_SE_DP_W053B,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_RED_BROWN,
	WAIT_FLAG
	
	SEQEND
