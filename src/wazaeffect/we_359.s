//==============================================================================
/**
 * @file	we_001.s
 * @brief	はたく
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_359
	
// =============================================================================
//
//
//	■アームハンマー
//
//
// =============================================================================
WEST_359:

	LOAD_PARTICLE_DROP	0,W_359_SPA
	
	SE_R			SEQ_SE_DP_W011

	ADD_PARTICLE 	0,W_359_359_HAMMERI_HAND1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	ADD_PARTICLE 	0,W_359_359_HAMMERI_HAND2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	ADD_PARTICLE 	0,W_359_359_HAMMERI_KEMURI, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			5
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 5, 0, 5, 0
	
	FUNC_CALL			WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_E1 | WE_TOOL_SSP), 100, 100, 100, 70, 100, (20 << 16) | 1, (4 << 16) | 4
	
	SE_R			SEQ_SE_DP_W070
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
