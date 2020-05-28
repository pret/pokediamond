//==============================================================================
/**
 * @file	we_078.s
 * @brief	ÇµÇ—ÇÍÇ≤Ç»			78
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SIBIREGONA
	
// =============================================================================
//
//
//	Å°ÇµÇ—ÇÍÇ≤Ç»			78
//
//
// =============================================================================
WEST_SIBIREGONA:
	
	LOAD_PARTICLE_DROP	0,W_078_SPA
	ADD_PARTICLE 	0,W_078_KONA_YEL, EMTFUNC_DEFENCE_POS

	SE_REPEAT_R		SEQ_SE_DP_W077B,4,6
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 2, WE_PAL_YELLOW, 10,10
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
