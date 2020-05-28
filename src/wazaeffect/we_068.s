//==============================================================================
/**
 * @file	we_068.s
 * @brief	カウンター			68
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAUNTAA
	
// =============================================================================
//
//
//	■カウンター			68
//
//
// =============================================================================
WEST_KAUNTAA:

	LOAD_PARTICLE_DROP	0,W_068_SPA
	
	SE_L			SEQ_SE_DP_BASI
	
	FUNC_CALL		WEST_SP_WE_KAITEN, 3, WE_TOOL_M1, 1, 10
	WAIT_FLAG
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	SE_REPEAT_R		SEQ_SE_DP_030,2,4
	ADD_PARTICLE 	0,W_068_068_HIT_MARK,		 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_068_068_BALL_BURN,		 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_068_068_COUNTER_PUNCH01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_068_068_COUNTER_PUNCH02, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_NUM_LONG2,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
