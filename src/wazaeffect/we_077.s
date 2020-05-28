//==============================================================================
/**
 * @file	we_077.s
 * @brief	Ç«Ç≠ÇÃÇ±Ç»			77
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOKUNOKONA
	
// =============================================================================
//
//
//	Å°Ç«Ç≠ÇÃÇ±Ç»			77
//
//
// =============================================================================
WEST_DOKUNOKONA:
	
	LOAD_PARTICLE_DROP	0,W_077_SPA
	ADD_PARTICLE 	0,W_077_KONA_PUR, EMTFUNC_DEFENCE_POS

	SE_REPEAT_R		SEQ_SE_DP_W077B,4,6
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 2, WE_PAL_POISON, 10,10

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
