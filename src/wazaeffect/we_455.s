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

	LOAD_PARTICLE_DROP	0,W_455_SPA
	
	ADD_PARTICLE		0, W_455_455_KEMURI_BURN01, EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_455_455_KEMURI_BURN02, EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_455_455_BEE_PARTY01,	EMTFUNC_ATTACK_POS
	ADD_PARTICLE		0, W_455_455_BEE_PARTY02,	EMTFUNC_ATTACK_POS
	
	SE_REPEAT_L			SEQ_SE_DP_W456,6,12

	WAIT				50
	SE_L				SEQ_SE_DP_W109
	WAIT				40
	
	SE_L				SEQ_SE_DP_W082

	ADD_PARTICLE		0, W_455_455_RING_BIG,		EMTFUNC_ATTACK_POS
	FUNC_CALL			WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_RED, WEDEF_FADE_PARAM,0
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
