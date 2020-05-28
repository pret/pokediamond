//==============================================================================
/**
 * @file	we_014.s
 * @brief	Ç¬ÇÈÇ¨ÇÃÇ‹Ç¢			14
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TURUGINOMAI
	
// =============================================================================
//
//
//	Å°Ç¬ÇÈÇ¨ÇÃÇ‹Ç¢			14
//
//
// =============================================================================
WEST_TURUGINOMAI:
	
	LOAD_PARTICLE_DROP	0,W_014_SPA
	ADD_PARTICLE 	0,W_014_SWORD_ROLL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_014_BALL_ROLL, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_SHUSHU

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
