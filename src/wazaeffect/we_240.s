//==============================================================================
/**
 * @file	we_240.s
 * @brief	Ç†Ç‹Ç≤Ç¢			240
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AMAGOI
	
// =============================================================================
//
//
//	Å°Ç†Ç‹Ç≤Ç¢			240
//
//
// =============================================================================
WEST_AMAGOI:
	LOAD_PARTICLE_DROP	0,W_240_SPA
		
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,	
	
	ADD_PARTICLE 	0,W_240_240_RAIN_SHOWER, EMTFUNC_DUMMY

	SE_C			SEQ_SE_DP_W240

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
	SEQEND
