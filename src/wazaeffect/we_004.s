//==============================================================================
/**
 * @file	we_004.s
 * @brief	れんぞくパンチ			4
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RENZOKUPANTI
	
// =============================================================================
//
//
//	■れんぞくパンチ			4
//
//
// =============================================================================
WEST_RENZOKUPANTI:
	
	LOAD_PARTICLE_DROP	0,W_004_SPA
	ADD_PARTICLE 	0,W_004_PUNCH_REPEAT, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE	0,W_004_PUNCH_HIT01,	 EMTFUNC_DEFENCE_POS
	
	LOOP_LABEL		4
	
		FUNC_CALL	WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
		SE_R		SEQ_SE_DP_030
		WAIT		6
	
	LOOP

	WAIT_PARTICLE

	EXIT_PARTICLE	0,
	
	SEQEND
