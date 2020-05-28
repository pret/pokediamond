//==============================================================================
/**
 * @file	we_152.s
 * @brief	クラブハンマー			152
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KURABUHANMAA
	
// =============================================================================
//
//
//	■クラブハンマー			152
//
//
// =============================================================================
WEST_KURABUHANMAA:
	
	LOAD_PARTICLE_DROP	0,W_152_SPA

	SE_R			SEQ_SE_DP_W233B

	ADD_PARTICLE 	0,W_152_152_CLBHAMMER_BUBBLE, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_152_152_CLBHAMMER_HIT,	EMTFUNC_DEFENCE_POS
	
	ADD_PARTICLE 	0,W_152_152_CLBHAMMER_BALL,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 8, WE_PAL_BLUE
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 8, 0, WE_PAL_BLUE
/*
	FUNC_CALL		WEST_SP_WE_T10,	4, 1, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG


	FUNC_CALL		WEST_SP_WE_T10,	4, 1, +WE_MOVE_X_VAL_DEF, 0, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG
*/
	SE_R			SEQ_SE_DP_W152	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 4, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
