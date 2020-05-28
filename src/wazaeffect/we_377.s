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

	LOAD_PARTICLE_DROP	0,W_377_SPA

	SE_R			SEQ_SE_DP_W377

	ADD_PARTICLE 	0,W_377_377_HBLOCK_KIRA, EMTFUNC_DF_SIDE
	
	WAIT			30
		
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 1
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_BLACK, WEDEF_FADE_PARAM, 15
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E2, 0, 1, WE_PAL_BLACK, WEDEF_FADE_PARAM, 15
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_PALCOL_CHANGE, 1, 0	

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
		
	SEQEND

