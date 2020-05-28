//==============================================================================
/**
 * @file	we_054.s
 * @brief	ÇµÇÎÇ¢Ç´ÇË			54
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SIROIKIRI
	
// =============================================================================
//
//
//	Å°ÇµÇÎÇ¢Ç´ÇË			54
//
//
// =============================================================================
WEST_SIROIKIRI:
	
	LOAD_PARTICLE_DROP	0,W_054_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_WHITE,
	SE_REPEAT_L		SEQ_SE_DP_W109,4,3

	ADD_PARTICLE 	0,W_054_MIST_WHITE, EMTFUNC_AT_SIDE
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10, 60
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M2, 0, 1, WE_PAL_WHITE, 10, 60

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_WHITE,
	WAIT_FLAG
	
	SEQEND
