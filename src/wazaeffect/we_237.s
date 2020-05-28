//==============================================================================
/**
 * @file	we_237.s
 * @brief	めざめるパワー			237
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEZAMERUPAWAA
	
// =============================================================================
//
//
//	■めざめるパワー			237
//
//
// =============================================================================
WEST_MEZAMERUPAWAA:
	LOAD_PARTICLE_DROP	0,W_237_SPA
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	SE_L			SEQ_SE_DP_W036

	ADD_PARTICLE 	0,W_237_237_POWER_BALL1, EMTFUNC_ATTACK_POS
	
	WAIT			40
	SE_L			SEQ_SE_DP_W179
	WAIT			40
	
	ADD_PARTICLE 	0,W_237_237_POWER_BURN1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_237_237_POWER_BURN2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_237_237_POWER_BURN3, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_237_237_KIRA_BURN4,	 EMTFUNC_ATTACK_POS

	SE_FLOW_LR		SEQ_SE_DP_W115
	
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
WAIT_FLAG	
	SEQEND
