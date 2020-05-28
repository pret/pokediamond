//==============================================================================
/**
 * @file	we_167.s
 * @brief	トリプルキック			167
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TORIPURUKIKKU
	
// =============================================================================
//
//
//	■トリプルキック			167
//
//
// =============================================================================
WEST_TORIPURUKIKKU:

	LOAD_PARTICLE_DROP	0,W_167_SPA

	//SE_REPEAT_R	SEQ_SE_DP_W007,2,3
	SE_REPEAT_R		SEQ_SE_DP_W007,2,2
	SE_WAITPLAY_R	SEQ_SE_DP_030,4
	
	ADD_PARTICLE 	0,W_167_167_TRPLKICK_FOOT01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_167_167_TRPLKICK_HIT, EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
