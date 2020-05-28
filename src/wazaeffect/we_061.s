//==============================================================================
/**
 * @file	we_061.s
 * @brief	バブルこうせん			61
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_BABURUKOUSEN
	
// =============================================================================
//
//
//	■バブルこうせん			61
//
//
// =============================================================================
WEST_BABURUKOUSEN:

	LOAD_PARTICLE_DROP	0,W_061_SPA
	ADD_PARTICLE 	0,W_061_061_BUBBLE_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_CONVERGENCE_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_SET_DF, OPERATOR_EX_REVERCE_ON, 2, 5, 0, 
	
	//SE_FLOW_LR		SEQ_SE_DP_AWA
	SE_REPEAT_C		SEQ_SE_DP_AWA,4,8

	LOOP_LABEL		2

		SE_REPEAT_R		SEQ_SE_DP_W145,2,2

		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		8
		FUNC_CALL		WEST_SP_WE_T05, 3, 16, -16, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		16
		FUNC_CALL		WEST_SP_WE_T05, 3,  8,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		8		
	LOOP

	SE_REPEAT_R		SEQ_SE_DP_W202B,4,6

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
