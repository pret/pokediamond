//==============================================================================
/**
 * @file	we_112.s
 * @brief	バリアー			112
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_BARIAA
	
// =============================================================================
//
//
//	■バリアー			112
//
//
// =============================================================================
WEST_BARIAA:
	
	LOAD_PARTICLE_DROP	0,W_112_SPA
	ADD_PARTICLE 	0,W_112_112_BARRI_MIRRROR1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_112_112_BARRI_KIRA,		EMTFUNC_ATTACK_POS

	//SE_L			SEQ_SE_DP_W112
	SE_L			SEQ_SE_DP_W112B

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
