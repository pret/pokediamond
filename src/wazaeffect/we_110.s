//==============================================================================
/**
 * @file	we_110.s
 * @brief	Ç©ÇÁÇ…Ç±Ç‡ÇÈ			110
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARANIKOMORU
	
// =============================================================================
//
//
//	Å°Ç©ÇÁÇ…Ç±Ç‡ÇÈ			110
//
//
// =============================================================================
WEST_KARANIKOMORU:
	
	LOAD_PARTICLE_DROP	0,W_110_SPA
	ADD_PARTICLE 	0,W_110_110_KARA_GIZA1,  EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_110_110_KARA_GIZA2,	 EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_110_110_KARA_BUBBLE, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_110_110_KARA_BALL,	 EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W029
	WAIT			17
	SE_REPEAT_L		SEQ_SE_DP_W145C,3,5

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
