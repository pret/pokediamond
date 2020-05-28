//==============================================================================
/**
 * @file	we_170.s
 * @brief	Ç±Ç±ÇÎÇÃÇﬂ			170
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOKORONOME
	
// =============================================================================
//
//
//	Å°Ç±Ç±ÇÎÇÃÇﬂ			170
//
//
// =============================================================================
WEST_KOKORONOME:
	
	LOAD_PARTICLE_DROP	0,W_170_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG

	ADD_PARTICLE 	0,W_170_170_KOKORO_DOUKOU, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_170_170_KOKORO_SIROME, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_170_170_KOKORO_FLASH1, EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W109
	SE_WAITPLAY_R	SEQ_SE_DP_W043,30

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	
	
	SEQEND
