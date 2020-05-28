//==============================================================================
/**
 * @file	we_128.s
 * @brief	Ç©ÇÁÇ≈ÇÕÇ≥Çﬁ			128
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KARADEHASAMU
	
// =============================================================================
//
//
//	Å°Ç©ÇÁÇ≈ÇÕÇ≥Çﬁ			128
//
//
// =============================================================================
WEST_KARADEHASAMU:
	
	LOAD_PARTICLE_DROP	0,W_128_SPA
	ADD_PARTICLE 	0,W_128_128_KARA_GIZAL, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_128_128_KARA_GIZAR, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_050
	WAIT	10	

	ADD_PARTICLE 	0,W_128_128_KARA_HIT, EMTFUNC_ATTACK_POS

	SE_L			SEQ_SE_DP_W011
	SE_WAITPLAY_L	SEQ_SE_DP_030,13

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
