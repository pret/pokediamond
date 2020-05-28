//==============================================================================
/**
 * @file	we_241.s
 * @brief	Ç…ÇŸÇÒÇŒÇÍ			241
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NIHONBARE
	
// =============================================================================
//
//
//	Å°Ç…ÇŸÇÒÇŒÇÍ			241
//
//
// =============================================================================
WEST_NIHONBARE:
	LOAD_PARTICLE_DROP	0,W_241_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 10, WE_PAL_YELLOW,

	ADD_PARTICLE 	0,W_241_241_SUN_LINE01, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_241_241_SUN_LINE02, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_241_241_SUN_BALL,	EMTFUNC_DUMMY

	SE_C			SEQ_SE_DP_W080

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 10, 0, WE_PAL_YELLOW,
	WAIT_FLAG	

	SEQEND
