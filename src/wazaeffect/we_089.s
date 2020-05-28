//==============================================================================
/**
 * @file	we_089.s
 * @brief	Ç∂ÇµÇÒ			89
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZISIN
	
// =============================================================================
//
//
//	Å°Ç∂ÇµÇÒ			89
//
//
// =============================================================================
WEST_ZISIN:

	LOAD_PARTICLE_DROP	0,W_089_SPA
		
//	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
//	WAIT_FLAG

	FUNC_CALL	WEST_SP_WE_089,	1, 0
	
	WAIT		2
	
	SE_C			SEQ_SE_DP_W089
	
	
	ADD_PARTICLE 	0,W_089_089_JISIN_STONE01, EMTFUNC_DEFENCE_POS
	
	WAIT_FLAG

//	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
//	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
