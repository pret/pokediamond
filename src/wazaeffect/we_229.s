//==============================================================================
/**
 * @file	we_229.s
 * @brief	こうそくスピン			229
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOUSOKUSUPIN
	
// =============================================================================
//
//
//	■こうそくスピン			229
//
//
// =============================================================================
WEST_KOUSOKUSUPIN:
	LOAD_PARTICLE_DROP	0,W_229_SPA
		
	SE_L			SEQ_SE_DP_207

	ADD_PARTICLE 	0,W_229_229_KOUSPIN_KAITEN1, 	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_229_229_KOUSPIN_KAITEN2,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_229_229_KOUSPIN_HIT,		EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 8,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_REPEAT_R		SEQ_SE_DP_143,6,3

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
