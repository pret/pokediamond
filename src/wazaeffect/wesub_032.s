//==============================================================================
/**
 * @file	we_073.s
 * @brief	やどりぎのタネ			73
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YADORIGINOTANE
	
// =============================================================================
//
//
//	■やどりぎのタネ			73
//
//
// =============================================================================
WEST_YADORIGINOTANE:
	LOAD_PARTICLE_DROP	0,W_071_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	///< 本来
	ADD_PARTICLE 	0,W_071_071_SUITORU1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_AT, OPERATOR_FLD_MAGNET_POS, OPERATOR_CAMERA_NONE
	EX_DATA			OPERATOR_FLD_EX_DATA_NUM, OPERATOR_FLD_AT,OPERATOR_EX_REVERCE_ON,0,0,0

	SE_REPEAT_C		SEQ_SE_DP_W152,2,16

	WAIT_PARTICLE

	ADD_PARTICLE 	0,W_071_071_SUITORU_KIRA, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_SP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0
	SE_L			SEQ_SE_DP_W071B

	WAIT_PARTICLE

	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	

	SEQEND
