//==============================================================================
/**
 * @file	we_146.s
 * @brief	ピヨピヨパンチ			146
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_PIYOPIYOPANTI
	
// =============================================================================
//
//
//	■ピヨピヨパンチ			146
//
//
// =============================================================================
WEST_PIYOPIYOPANTI:
	LOAD_PARTICLE_DROP	0,W_146_SPA

	LOOP_LABEL		2
		
		WAIT			6
		
		FUNC_CALL		WEST_SP_WE_T10,	4, 3, +WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT_FLAG
		
		SE_R			SEQ_SE_DP_W004
	
		ADD_PARTICLE 	0,W_146_146_PIYOPIYO_HAND, EMTFUNC_DEFENCE_POS
		ADD_PARTICLE 	0,W_146_146_PIYOPIYO_KIRA, EMTFUNC_DEFENCE_POS
		
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP,
		FUNC_CALL		WEST_SP_WE_T10,	4, 3, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
		
		WAIT_FLAG
		//SE_R			SEQ_SE_DP_W092
		SE_R			SEQ_SE_DP_W146

		SE_REPEAT_R		SEQ_SE_DP_W146,4,4

	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
