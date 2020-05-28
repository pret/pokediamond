//==============================================================================
/**
 * @file	we_115.s
 * @brief	リフレクター			115
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RIHUREKUTAA
	
// =============================================================================
//
//
//	■リフレクター			115
//
//
// =============================================================================
WEST_RIHUREKUTAA:

	LOAD_PARTICLE_DROP	0,W_115_SPA
	ADD_PARTICLE 	0,W_115_115_REFRCT_MIRRROR, EMTFUNC_AT_SIDE
	ADD_PARTICLE 	0,W_115_115_REFRCT_KIRA02,  EMTFUNC_AT_SIDE
	SE_L			SEQ_SE_DP_W115

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
