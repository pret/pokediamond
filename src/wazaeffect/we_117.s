//==============================================================================
/**
 * @file	we_117.s
 * @brief	Ç™Ç‹ÇÒ			117
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_GAMAN
	
// =============================================================================
//
//
//	Å°Ç™Ç‹ÇÒ			117
//
//
// =============================================================================
WEST_GAMAN:


	TURN_CHK	TURN_1, TURN_2

	
	SEQEND

TURN_1:

	LOAD_PARTICLE_DROP	0,W_117_SPA
	
	SE_REPEAT_L		SEQ_SE_DP_W036,3,4

	ADD_PARTICLE 	0,W_117_117_GAMAN_KEMURI, EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_NUM_LONG,  WE_TOOL_M1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_RED, 10,0

	WAIT_FLAG
	
	
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

TURN_2:
	
	LOAD_PARTICLE_DROP	0,W_021_SPA
	ADD_PARTICLE 	0,W_021_021_HIT_MARK, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_021_B_BURN_RED2, EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, +14, +4, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT			1
	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, -4, WE_TOOL_E1 | WE_TOOL_SSP
	
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T10,	4, 2, -14, -4, WE_TOOL_M1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +14, +4, WE_TOOL_E1 | WE_TOOL_SSP

	SE_R			SEQ_SE_DP_W025B

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND