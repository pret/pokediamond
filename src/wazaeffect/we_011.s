//==============================================================================
/**
 * @file	we_011.s
 * @brief	ÇÕÇ≥Çﬁ			11
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HASAMU
	
// =============================================================================
//
//
//	Å°ÇÕÇ≥Çﬁ			11
//
//
// =============================================================================
WEST_HASAMU:

	LOAD_PARTICLE_DROP	0,W_011_SPA
	ADD_PARTICLE 	0,W_011_BOARD_R, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_011_BOARD_L, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_011_011_BALL_BURN, EMTFUNC_DEFENCE_POS
	
	SE_R			SEQ_SE_DP_W011
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP
	

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
