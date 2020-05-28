//==============================================================================
/**
 * @file	we_238.s
 * @brief	クロスチョップ			238
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KUROSUTYOPPU
	
// =============================================================================
//
//
//	■クロスチョップ			238
//
//
// =============================================================================
WEST_KUROSUTYOPPU:
	LOAD_PARTICLE_DROP	0,W_238_SPA
		
	SE_R			SEQ_SE_DP_W025

	ADD_PARTICLE 	0,W_238_238_CHOP_L1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_238_238_CHOP_R1, EMTFUNC_DEFENCE_POS
	
	WAIT			10
	
	ADD_PARTICLE 	0,W_238_238_CHOP_L2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_238_238_CHOP_R2, EMTFUNC_DEFENCE_POS

	WAIT			55
	ADD_PARTICLE 	0,W_238_033_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_238_033_BALL_BURN,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_W013

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
