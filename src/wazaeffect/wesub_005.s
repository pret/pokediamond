//==============================================================================
/**
 * @file	wesub_005.s
 * @brief	Ç‹Ç–
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusMahi
	
// =============================================================================
//
//
//	Å°Ç‹Ç–
//
//
// =============================================================================
WEST_StatusMahi:

	LOAD_PARTICLE_DROP	0,W_084_SPA
	
	SE_L			SEQ_SE_DP_W085C

	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_BLACK, 15, 0
	
	ADD_PARTICLE 	0,W_084_084_THUNDER_SPARK01,	EMTFUNC_ATTACK_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND

