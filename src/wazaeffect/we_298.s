//==============================================================================
/**
 * @file	we_298.s
 * @brief	フラフラダンス			298
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HURAHURADANSU
	
// =============================================================================
//
//
//	■フラフラダンス			298
//
//
// =============================================================================
#define MOVE_X_1	(12)
#define MOVE_X_2	(24)
#define MOVE_X_3	(MOVE_X_1+MOVE_X_2)

WEST_HURAHURADANSU:
	LOAD_PARTICLE_DROP	0,W_298_SPA
		
	SE_REPEAT_L		SEQ_SE_DP_W298,4,6

	ADD_PARTICLE 	0,W_298_298_ONPU_BURN, EMTFUNC_ATTACK_POS

	FUNC_CALL		WEST_SP_WE_T05, 3, 8, +MOVE_X_2, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 8, +MOVE_X_1, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 8, -MOVE_X_3, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T05, 3, 8, -MOVE_X_2, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 8, -MOVE_X_1, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 8, +MOVE_X_3, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -4, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, +4, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
