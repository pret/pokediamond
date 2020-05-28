//==============================================================================
/**
 * @file	we_060.s
 * @brief	サイケこうせん			60
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SAIKEKOUSEN
	
// =============================================================================
//
//
//	■サイケこうせん			60
//
//
// =============================================================================
WEST_SAIKEKOUSEN:

	LOAD_PARTICLE_DROP	0,W_060_SPA
	
	//SE_FLOW_LR		SEQ_SE_DP_W060B
	SE_FLOW_LR		SEQ_SE_DP_W060C

	ADD_PARTICLE 	0,W_060_060_PSYCHE_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_L3SP, OPERATOR_AXIS_AT_3, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 8, 10

	LOOP_LABEL		2
		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		8
		FUNC_CALL		WEST_SP_WE_T05, 3, 16, -16, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		16
		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		8
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
