//==============================================================================
/**
 * @file	we_183.s
 * @brief	マッハパンチ			183
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MAHHAPANTI
	
// =============================================================================
//
//
//	■マッハパンチ			183
//
//
// =============================================================================
WEST_MAHHAPANTI:

	LOAD_PARTICLE_DROP	0,W_183_SPA
	
	SE_R			SEQ_SE_DP_W010

	ADD_PARTICLE 	0,W_183_183_MAHHAPUN_HAND, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_183_183_MAHHAPUN_HIT,  EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_183_183_MAHHAPUN_BALL, EMTFUNC_DEFENCE_POS


	WAIT			15
	SE_R			SEQ_SE_DP_W030
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
