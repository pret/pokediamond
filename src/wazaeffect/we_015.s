//==============================================================================
/**
 * @file	we_015.s
 * @brief	Ç¢Ç†Ç¢Ç¨ÇË			15
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IAIGIRI
	
// =============================================================================
//
//
//	Å°Ç¢Ç†Ç¢Ç¨ÇË			15
//
//
// =============================================================================
WEST_IAIGIRI:
	
	LOAD_PARTICLE_DROP	0,W_015_SPA
	ADD_PARTICLE 	0,W_015_SLASH01, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_015_B_BURN_YEL, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W015
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
