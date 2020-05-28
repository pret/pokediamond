//==============================================================================
/**
 * @file	we_254.s
 * @brief	ÇΩÇ≠ÇÌÇ¶ÇÈ			254
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TAKUWAERU
	
// =============================================================================
//
//
//	Å°ÇΩÇ≠ÇÌÇ¶ÇÈ			254
//
//
// =============================================================================

#define Y_TOP		(160)
#define FWAIT		(1)
#define IWAIT		(5)
#define OWAIT		(5)
#define TWAIT		(IWAIT + OWAIT)

WEST_TAKUWAERU:
		
	LOAD_PARTICLE_DROP	0,W_254_SPA
	ADD_PARTICLE 	0,W_254_254_STOCK, EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M1, FWAIT, 1, WE_PAL_WHITE, 16,
	
	LOOP_LABEL		2

		SE_L		SEQ_SE_DP_W025

		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 80, 100, Y_TOP, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
		FUNC_CALL	WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 120, 100, 80, 100, 1, (IWAIT << 16) | OWAIT
		WAIT		TWAIT
	LOOP
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
