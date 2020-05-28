//==============================================================================
/**
 * @file	we_287.s
 * @brief	リフレッシュ			287
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RIHURESSYU
	
// =============================================================================
//
//
//	■リフレッシュ			287
//
//
// =============================================================================
WEST_RIHURESSYU:
	LOAD_PARTICLE_DROP	0,W_287_SPA
		
	SE_L			SEQ_SE_DP_W287

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_WHITE,
	WAIT_FLAG


	ADD_PARTICLE 	0,W_287_287_KIRA_BURN,	 EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_287_287_CIRCLE_BURN, EMTFUNC_ATTACK_POS

	WAIT			30
	SE_L			SEQ_SE_DP_W234

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_WHITE,
	WAIT_FLAG
	
	SEQEND
