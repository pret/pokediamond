//==============================================================================
/**
 * @file	we_010.s
 * @brief	Ç–Ç¡Ç©Ç≠			10
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HIKKAKU
	
// =============================================================================
//
//
//	Å°Ç–Ç¡Ç©Ç≠			10
//
//
// =============================================================================
WEST_HIKKAKU:
	
	LOAD_PARTICLE_DROP	0,W_010_SPA
	ADD_PARTICLE 	0,W_010_010_3SLASH,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_010_010_HIT_MARK,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP
	
	SE_R			SEQ_SE_DP_W010

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
