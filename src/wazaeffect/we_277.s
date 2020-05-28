//==============================================================================
/**
 * @file	we_277.s
 * @brief	マジックコート			277
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MAZIKKUKOOTO
	
// =============================================================================
//
//
//	■マジックコート			277
//
//
// =============================================================================
WEST_MAZIKKUKOOTO:
	
	LOAD_PARTICLE_DROP	0,W_277_SPA
	ADD_PARTICLE 	0,W_277_277_MIRROR_KIRA,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_277_277_MIRROR_BOARD,	EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W112

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
