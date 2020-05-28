//==============================================================================
/**
 * @file	we_142.s
 * @brief	あくまのキッス			142
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AKUMANOKISSU
	
// =============================================================================
//
//
//	■あくまのキッス			142
//
//
// =============================================================================
WEST_AKUMANOKISSU:
	
	LOAD_PARTICLE_DROP	0,W_142_SPA
	ADD_PARTICLE 	0,W_142_142_AKUMAKISS_BALL, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_142_142_AKUMAKISS_HART, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W213
	
	WAIT			15
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
