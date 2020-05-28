//==============================================================================
/**
 * @file	we_002.s
 * @brief	からてチョップ			2
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARATETYOPPU
	
// =============================================================================
//
//
//	■からてチョップ			2
//
//
// =============================================================================
WEST_KARATETYOPPU:
	
	LOAD_PARTICLE_DROP	0,W_002_SPA	

	ADD_PARTICLE 	0,W_002_002_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_002_002_BALL_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_002_002_HAND_DOWN,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	//SE_R			SEQ_SE_DP_007
	SE_R			SEQ_SE_DP_HURU
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,5

	WAIT_PARTICLE
	
	EXIT_PARTICLE	0,
	
	SEQEND
