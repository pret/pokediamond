//==============================================================================
/**
 * @file	we_190.s
 * @brief	オクタンほう			190
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_OKUTANHOU
	
// =============================================================================
//
//
//	■オクタンほう			190
//
//
// =============================================================================
WEST_OKUTANHOU:

	LOAD_PARTICLE_DROP	0,W_190_SPA	
	
	SE_FLOW_LR			SEQ_SE_DP_W025B

	ADD_PARTICLE	0,W_190_190_OKTNHOU_KEMURI2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_190_190_OKTNHOU_BALL, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF,	\
					OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_DF, OPERATOR_EX_REVERCE_ON, 0,0,0
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	
	
	WAIT			5
	ADD_PARTICLE	0,W_190_190_OKTNHOU_KEMURI, EMTFUNC_DEFENCE_POS
	SE_R			SEQ_SE_DP_W120
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*5,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_T05, 3, 3, +WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
