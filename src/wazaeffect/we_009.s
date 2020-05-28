//==============================================================================
/**
 * @file	we_009.s
 * @brief	かみなりパンチ			9
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAMINARIPANTI
	
// =============================================================================
//
//
//	■かみなりパンチ			9
//
//
// =============================================================================
WEST_KAMINARIPANTI:
	
	LOAD_PARTICLE_DROP	0,W_009_SPA

	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,

	ADD_PARTICLE 	0,W_009_009_DENKI_PUNCH,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_009_009_DENKI_BURN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_009_009_LIGH_BURN,		EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	SE_R			SEQ_SE_DP_BASI

	SE_WAITPLAY_R	SEQ_SE_DP_W161B,5
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
