//==============================================================================
/**
 * @file	we_008.s
 * @brief	れいとうパンチ			8
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_REITOUPANTI
	
// =============================================================================
//
//
//	■れいとうパンチ			8
//
//
// =============================================================================
WEST_REITOUPANTI:
		
	LOAD_PARTICLE_DROP	0,W_008_SPA

	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 8, WE_PAL_ICE_BLUE,

	ADD_PARTICLE 	0,W_008_008_ICE_PUNCH,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_008_008_ICE_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_008_008_ICE_MIST,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	SE_R			SEQ_SE_DP_BASI

	SE_WAITPLAY_R	SEQ_SE_DP_W280,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 8, 0, WE_PAL_ICE_BLUE,
	WAIT_FLAG
	
	SEQEND
