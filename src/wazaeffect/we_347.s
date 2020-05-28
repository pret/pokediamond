//==============================================================================
/**
 * @file	we_347.s
 * @brief	ÇﬂÇ¢ÇªÇ§			347
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MEISOU
	
// =============================================================================
//
//
//	Å°ÇﬂÇ¢ÇªÇ§			347
//
//
// =============================================================================
WEST_MEISOU:
	
	LOAD_PARTICLE_DROP	0,W_347_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG

	SE_REPEAT_L		SEQ_SE_DP_W048,2,4

	ADD_PARTICLE 	0,W_347_347_BALL_BURN, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_347_347_RING_BURN, EMTFUNC_ATTACK_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	SEQEND
