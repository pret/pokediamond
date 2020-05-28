//==============================================================================
/**
 * @file	we_129.s
 * @brief	スピードスター			129
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUPIIDOSUTAA
	
// =============================================================================
//
//
//	■スピードスター			129
//
//
// =============================================================================
WEST_SUPIIDOSUTAA:
	
	LOAD_PARTICLE_DROP	0,W_129_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	//SE_L			SEQ_SE_DP_W129
	SE_FLOW_LR		SEQ_SE_DP_165

	ADD_PARTICLE 	0,W_129_129_SPSTAR_STAR1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_129_129_SPSTAR_SHOOT, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_DF_SIDE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_129_129_SPSTAR_HIT, EMTFUNC_DF_SIDE

	WAIT			2
	//SE_FLOW_LR		SEQ_SE_DP_164
	WAIT			18
	SE_REPEAT_R		SEQ_SE_DP_143,4,3

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E2 | WE_TOOL_SSP,
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	
	SEQEND
