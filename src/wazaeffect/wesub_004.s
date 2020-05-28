//==============================================================================
/**
 * @file	wesub_004.s
 * @brief	ïX
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusKoori
	
// =============================================================================
//
//
//	Å°ïX
//
//
// =============================================================================
WEST_StatusKoori:
	LOAD_PARTICLE_DROP	0, SPA_STATUS_EFF

	SE_REPEAT_L		SEQ_SE_DP_W258, 8, 2

	ADD_PARTICLE 	0, STATUS_EFF_TURN_ICE1, EMTFUNC_ATTACK_POS
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
