//==============================================================================
/**
 * @file	we_123.s
 * @brief	スモッグ			123
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUMOGGU
	
// =============================================================================
//
//
//	■スモッグ			123
//
//
// =============================================================================
WEST_SUMOGGU:
	
	LOAD_PARTICLE_DROP	0,W_123_SPA
	ADD_PARTICLE 	0,W_123_DOKU, EMTFUNC_DEFENCE_POS

	SE_REPEAT_R		SEQ_SE_DP_W109,4,3

	WAIT			10
	//SE_C			SEQ_SE_DP_W054
	WAIT			10
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_BLACK, 10,0

	
	//SE_C			SEQ_SE_DP_W092
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
