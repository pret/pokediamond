//==============================================================================
/**
 * @file	we_234.s
 * @brief	Ç†Ç≥ÇÃÇ–Ç¥Çµ			234
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ASANOHIZASI
	
// =============================================================================
//
//
//	Å°Ç†Ç≥ÇÃÇ–Ç¥Çµ			234
//
//
// =============================================================================
WEST_ASANOHIZASI:
	LOAD_PARTICLE_DROP	0,W_234_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, 0x67FF,
	
	ADD_PARTICLE 	0,W_234_HIZASHI01, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_234_HIZASHI02, EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_234_HIZASHI03, EMTFUNC_DUMMY

	SE_C			SEQ_SE_DP_W234

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
			
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, 0x67FF,
	WAIT_FLAG
	
	SEQEND
