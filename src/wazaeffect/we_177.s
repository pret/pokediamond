//==============================================================================
/**
 * @file	we_177.s
 * @brief	エアロブラスト			177
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_EAROBURASUTO
	
// =============================================================================
//
//
//	■エアロブラスト			177
//
//
// =============================================================================
WEST_EAROBURASUTO:

	LOAD_PARTICLE_DROP	0,W_177_SPA

	HAIKEI_CHG		BG_ID_177, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	
	FUNC_CALL		WEST_SP_BG_SHAKE, 5, 0, 4, 0, 28, 0
		
	SE_REPEAT_L		SEQ_SE_DP_W013,2,5

	ADD_PARTICLE 	0,W_177_177_AIRBRST_LINE1, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE

	ADD_PARTICLE 	0,W_177_177_AIRBRST_LINE2, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	WAIT			22
	SE_FLOW_LR		SEQ_SE_DP_KAZE
	WAIT			18

	ADD_PARTICLE 	0,W_177_177_AIRBRST_HIT,	 EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 8,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	HAIKEI_RECOVER	BG_ID_177, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	HAIKEI_CHG_WAIT
	SEQEND
