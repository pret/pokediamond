//==============================================================================
/**
 * @file	we_227.s
 * @brief	アンコール			227
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ANKOORU
	
// =============================================================================
//
//
//	■アンコール			227
//
//
// =============================================================================
WEST_ANKOORU:

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
WAIT_FLAG

	
	LOAD_PARTICLE_DROP	0,W_227_SPA
	ADD_PARTICLE 	0,W_227_227_ANKO_LIGT1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_227_227_ANKO_BALL1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_227_227_ANKO_DUST1, EMTFUNC_DEFENCE_POS

	SEPLAY_PAN		SEQ_SE_DP_W227B, WAZA_SE_PAN_DF
	
	LOOP_LABEL		5

		SEPLAY_PAN		SEQ_SE_DP_W227,  WAZA_SE_PAN_DF

		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  -8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
		
	LOOP
		

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
WAIT_FLAG
	
	SEQEND
