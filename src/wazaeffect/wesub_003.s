//==============================================================================
/**
 * @file	wesub_001.s
 * @brief	Ç‚ÇØÇ«
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusYakedo
	
// =============================================================================
//
//
//	Å°Ç‚ÇØÇ«
//
//
// =============================================================================
WEST_StatusYakedo:

	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF
	
	SE_L			SEQ_SE_DP_W172

	ADD_PARTICLE 	0, STATUS_EFF_TURN_FIRE, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_RED, WEDEF_FADE_PARAM,0
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
