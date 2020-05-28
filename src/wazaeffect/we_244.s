//==============================================================================
/**
 * @file	we_244.s
 * @brief	Ç∂Ç±Ç†ÇÒÇ∂			244
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ZIKOANZI
	
// =============================================================================
//
//
//	Å°Ç∂Ç±Ç†ÇÒÇ∂			244
//
//
// =============================================================================
WEST_ZIKOANZI:
	LOAD_PARTICLE_DROP	0,W_244_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
	
	SE_L			SEQ_SE_DP_W060B

	ADD_PARTICLE 	0,W_244_244_SPIRAL, EMTFUNC_ATTACK_POS

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	

	SEQEND
