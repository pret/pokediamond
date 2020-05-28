//==============================================================================
/**
 * @file	we_279.s
 * @brief	リベンジ			279
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RIBENZI
	
// =============================================================================
//
//
//	■リベンジ			279
//
//
// =============================================================================
WEST_RIBENZI:
	
	LOAD_PARTICLE_DROP	0,W_279_SPA

FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
WAIT_FLAG

	ADD_PARTICLE 	0,W_279_279_KEMURI_UP,		EMTFUNC_ATTACK_POS
	
	SE_L			SEQ_SE_DP_W036
	WAIT			45
	SE_R			SEQ_SE_DP_030
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +16, -8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT			2
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 8, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	ADD_PARTICLE 	0,W_279_279_REVENGE_PUNCH,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_279_279_BALL_BURN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_279_279_HITMARK,		EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -16, +8, WE_TOOL_M1 | WE_TOOL_SSP
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
