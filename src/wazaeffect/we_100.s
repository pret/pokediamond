//==============================================================================
/**
 * @file	we_100.s
 * @brief	テレポート			100
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TEREPOOTO
	
// =============================================================================
//
//
//	■テレポート			100
//
//
// =============================================================================
WEST_TEREPOOTO:

	LOAD_PARTICLE_DROP	0,W_100_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_100, 0,0,0,0,0,0,0,0,0

	SE_L			SEQ_SE_DP_W100

	WAIT			10

	ADD_PARTICLE 	0,W_100_100_TELEPO_KIRA, EMTFUNC_ATTACK_POS

	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG

	SEQEND
