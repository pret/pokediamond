//==============================================================================
/**
 * @file	we_022.s
 * @brief	つるのムチ			22
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TURUNOMUTI
	
// =============================================================================
//
//
//	■つるのムチ			22
//
//
// =============================================================================
WEST_TURUNOMUTI:
	
	LOAD_PARTICLE_DROP	0,W_022_SPA

	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP

	ADD_PARTICLE 	0,W_022_022_LEAF_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_022_022_LINE_SLASH, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_022_022_HIT_MARK,	EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_MUCHI
	WAIT			5
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_PASA2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	WAIT_FLAG
	
	SEQEND
