//==============================================================================
/**
 * @file	wesub_002.s
 * @brief	ì≈
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusDoku
	
// =============================================================================
//
//
//	Å°ì≈
//
//
// =============================================================================
WEST_StatusDoku:
	
	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF
	
	//SE_L			SEQ_SE_DP_154
	SE_REPEAT_L		SEQ_SE_DP_W092D,3,3

	ADD_PARTICLE 	0, STATUS_EFF_TURN_POISEN, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_POISON, WEDEF_FADE_PARAM,0
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
