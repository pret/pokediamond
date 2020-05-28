//==============================================================================
/**
 * @file	we_058.s
 * @brief	れいとうビーム			58
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_REITOUBIIMU
	
// =============================================================================
//
//
//	■れいとうビーム			58
//
//
// =============================================================================
#define C58		(WE_PAL_ICE_BLUE)//(WE_PAL_BLACK)
#define EVY58	(8)
WEST_REITOUBIIMU:
	LOAD_PARTICLE_DROP	0,W_058_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, EVY58, C58,
	WAIT_FLAG

	ADD_PARTICLE 	0,W_058_ICE_BEAM01, EMTFUNC_FIELD_OPERATOR
	EX_DATA			OPERATOR_DEF_DATA_NUM, OPERATOR_PRI_NONE, OPERATOR_TARGET_DF, OPERATOR_POS_LSP, OPERATOR_AXIS_AT, OPERATOR_FLD_NONE, OPERATOR_CAMERA_NONE
	
	SE_FLOW_LR		SEQ_SE_DP_025

	WAIT 			15
	ADD_PARTICLE 	0,W_058_KEMURI_ICE,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_058_058_ICE_PIECE,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, EVY58, 0, C58,
	WAIT_FLAG	
	
	SEQEND

