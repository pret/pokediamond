//==============================================================================
/**
 * @file	we_303.s
 * @brief	Ç»Ç‹ÇØÇÈ			303
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NAMAKERU
	
// =============================================================================
//
//
//	Å°Ç»Ç‹ÇØÇÈ			303
//
//
// =============================================================================
WEST_NAMAKERU:
	

	LOAD_PARTICLE_DROP	0,W_303_SPA
	
	SE_L			SEQ_SE_DP_W281
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_SCALE_UPDOWN, 8, (WE_TOOL_M1 | WE_TOOL_SSP), 100, 100, 100, 60, 100, (20 << 16) | 1, (4 << 16) | 4
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_303_303_KIRA_UP, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	
	SE_L			SEQ_SE_DP_W071B
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
