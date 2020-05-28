//==============================================================================
/**
 * @file	we_075.s
 * @brief	はっぱカッター			75
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HAPPAKATTAA
	
// =============================================================================
//
//
//	■はっぱカッター			75
//
//
// =============================================================================
WEST_HAPPAKATTAA:

	LOAD_PARTICLE_DROP	0,W_075_SPA
	
	SE_L			SEQ_SE_DP_KAZE
	
	ADD_PARTICLE 	0,W_075_075_LEAF_BURN, EMTFUNC_ATTACK_POS
	ADD_PARTICLE	0,W_075_075_LEAF_BEAM, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_DF_SIDE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			15
	SE_STOP			SEQ_SE_DP_KAZE
	WAIT			50
	SE_FLOW_LR		SEQ_SE_DP_209
	WAIT			10

	ADD_PARTICLE 	0,W_075_075_HIT_MARK, EMTFUNC_DF_SIDE
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E2 | WE_TOOL_SSP,

	WAIT			7
	SE_REPEAT_R		SEQ_SE_DP_HURU,3,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
