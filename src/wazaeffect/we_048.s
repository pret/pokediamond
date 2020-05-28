//==============================================================================
/**
 * @file	we_048.s
 * @brief	ÇøÇÂÇ§Ç®ÇÒÇœ			48
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TYOUONPA
	
// =============================================================================
//
//
//	Å°ÇøÇÂÇ§Ç®ÇÒÇœ			48
//
//
// =============================================================================
WEST_TYOUONPA:
	
	LOAD_PARTICLE_DROP	0,W_048_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
		
	ADD_PARTICLE_EMIT_SET 	0, 1, W_048_048_RING_BIG, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, 6, 1, 0, 0, 0, 14, 64,	
	
	WAIT			10
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_FLOW_LR		SEQ_SE_DP_W048

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
		
	SEQEND
