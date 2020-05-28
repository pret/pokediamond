//==============================================================================
/**
 * @file	we_113.s
 * @brief	Ç–Ç©ÇËÇÃÇ©Ç◊			113
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HIKARINOKABE
	
// =============================================================================
//
//
//	Å°Ç–Ç©ÇËÇÃÇ©Ç◊			113
//
//
// =============================================================================
WEST_HIKARINOKABE:
	
	LOAD_PARTICLE_DROP	0,W_113_SPA
	ADD_PARTICLE 	0,W_113_113_HIKARIKABE_MIRRROR, EMTFUNC_AT_SIDE
	ADD_PARTICLE 	0,W_113_113_HIKARIKABE_KIRA01,  EMTFUNC_AT_SIDE

	SE_L			SEQ_SE_DP_W115

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
