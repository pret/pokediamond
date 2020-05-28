//==============================================================================
/**
 * @file	we_342.s
 * @brief	ポイズンテール			342
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_POIZUNTEERU
	
// =============================================================================
//
//
//	■ポイズンテール			342
//
//
// =============================================================================
WEST_POIZUNTEERU:
	
	LOAD_PARTICLE_DROP	0,W_342_SPA

	SE_R			SEQ_SE_DP_BRADE
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,6
	
	ADD_PARTICLE 	0,W_342_342_BALL_UP, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_EP, OPERATOR_AXIS_NONE, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	ADD_PARTICLE 	0,W_342_407_LINE_L,		 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_342_407_LINE_R,		 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_342_407_KEMURI_BURN, EMTFUNC_DEFENCE_POS
	
	WAIT			5

	SE_WAITPLAY_R	SEQ_SE_DP_W092D,10
	SE_WAITPLAY_R	SEQ_SE_DP_W092D,18
	SE_WAITPLAY_R	SEQ_SE_DP_W092D,26
	SE_WAITPLAY_R	SEQ_SE_DP_W092D,34

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_E1, 1, 1, WE_PAL_POISON, 12,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
