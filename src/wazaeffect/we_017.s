//==============================================================================
/**
 * @file	we_017.s
 * @brief	Ç¬ÇŒÇ≥Ç≈Ç§Ç¬			17
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TUBASADEUTU
	
// =============================================================================
//
//
//	Å°Ç¬ÇŒÇ≥Ç≈Ç§Ç¬			17
//
//
// =============================================================================
WEST_TUBASADEUTU:
	
	LOAD_PARTICLE_DROP	0,W_017_SPA
	ADD_PARTICLE 	0,W_017_HIT_HANE, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_017_HIT_MARK02, EMTFUNC_DEFENCE_POS

	SE_REPEAT_R		SEQ_SE_DP_W017,2,2
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
