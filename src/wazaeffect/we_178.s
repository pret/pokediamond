//==============================================================================
/**
 * @file	we_178.s
 * @brief	ÇÌÇΩÇŸÇ§Çµ			178
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_WATAHOUSI
	
// =============================================================================
//
//
//	Å°ÇÌÇΩÇŸÇ§Çµ			178
//
//
// =============================================================================
WEST_WATAHOUSI:
	
	LOAD_PARTICLE_DROP	0,W_178_SPA
	ADD_PARTICLE 	0,W_178_178_WATAHOU_KONA, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 3, WE_PAL_WHITE, 10, 10

	//SE_REPEAT_R	SEQ_SE_DP_W077,3,6
	SE_REPEAT_R		SEQ_SE_DP_W199,3,8

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
