//==============================================================================
/**
 * @file	we_131.s
 * @brief	とげキャノン			131
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOGEKYANON
	
// =============================================================================
//
//
//	■とげキャノン			131
//
//
// =============================================================================
WEST_TOGEKYANON:
	
	LOAD_PARTICLE_DROP	0,W_131_SPA
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 2, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_131_131_TOGECAN_NEEDLE, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF,	\
					OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_DF, OPERATOR_EX_REVERCE_ON, 0,0,0

	SE_REPEAT_R		SEQ_SE_DP_W013,2,8

	FUNC_CALL		WEST_SP_WE_T05, 3, 2, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT	10
	ADD_PARTICLE 	0,W_131_131_TOGECAN_HIT1, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 6,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_FLAG
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

