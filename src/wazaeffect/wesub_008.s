//==============================================================================
/**
 * @file	wesub_009.s
 * @brief	LVUP
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusLVUP
	
// =============================================================================
//
//
//	Å°Lvup
//
//
// =============================================================================
WEST_StatusLVUP:

	LOAD_PARTICLE_DROP	0, LEVEL_SPA
	
	//SE_L			SEQ_SE_DP_EXPMAX
	SE_L			SEQ_SE_DP_EXPMAX2

	ADD_PARTICLE 	0, LEVEL_LV_UP1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0, LEVEL_LV_UP2, EMTFUNC_ATTACK_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
