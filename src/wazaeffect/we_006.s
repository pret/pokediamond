//==============================================================================
/**
 * @file	we_006.s
 * @brief	ネコにこばん			6
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

	.text
	
	.include	"west.h"

	.global		WEST_NEKONIKOBAN
	
// =============================================================================
//
//
//	■ネコにこばん			6
//
//
// =============================================================================
WEST_NEKONIKOBAN:
	
	LOAD_PARTICLE_DROP	0,W_006_SPA
	ADD_PARTICLE 	0,W_006_006_COIN_BEAM,EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_FLOW_LR		SEQ_SE_DP_W013B

	WAIT			10
	
	ADD_PARTICLE 	0,W_006_006_COIN_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_006_006_KIRA_BURN, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	SE_R			SEQ_SE_DP_W006

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
