//==============================================================================
/**
 * @file	we_083.s
 * @brief	ÇŸÇÃÇ®ÇÃÇ§Ç∏			83
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HONOONOUZU
	
// =============================================================================
//
//
//	Å°ÇŸÇÃÇ®ÇÃÇ§Ç∏			83
//
//
// =============================================================================
WEST_HONOONOUZU:
	
	LOAD_PARTICLE_DROP	0,W_083_SPA

	SE_L			SEQ_SE_DP_W221B
	
	ADD_PARTICLE 	0,W_083_083_FIRE_CIRCLE01, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_083_083_FIRE_CIRCLE02, EMTFUNC_ATTACK_POS
	
	LOOP_LABEL		2
	
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_NUM_LONG2,  WE_TOOL_M1 | WE_TOOL_SSP,
		WAIT_FLAG
	
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
