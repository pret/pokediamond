//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:
	LOAD_PARTICLE_DROP	0,W_381_SPA
	
	ADD_PARTICLE 	0,W_381_381_MAJINAI_STAR, EMTFUNC_AT_SIDE	
	ADD_PARTICLE 	0,W_381_381_MAJINAI_RING, EMTFUNC_AT_SIDE
	
	//SE_L			SEQ_SE_DP_381
	SE_WAITPLAY_L	SEQ_SE_DP_163,2

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM, 10
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,	
	
	SEQEND

