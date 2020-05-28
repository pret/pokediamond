//==============================================================================
/**
 * @file	we_319.s
 * @brief	Ç´ÇÒÇºÇ≠Ç®ÇÒ			319
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KINZOKUON
	
// =============================================================================
//
//
//	Å°Ç´ÇÒÇºÇ≠Ç®ÇÒ			319
//
//
// =============================================================================
WEST_KINZOKUON:

	LOAD_PARTICLE_DROP	0,W_319_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG

	//SE_REPEAT_R		SEQ_SE_DP_W103,4,5
	SE_WAITPLAY_C		SEQ_SE_DP_W103,1
	SE_WAITPLAY_C		SEQ_SE_DP_W103,3
	SE_WAITPLAY_C		SEQ_SE_DP_W103,5
	SE_WAITPLAY_C		SEQ_SE_DP_W103,7
	SE_WAITPLAY_C		SEQ_SE_DP_W103,10
	SE_WAITPLAY_C		SEQ_SE_DP_W103,15
	SE_WAITPLAY_C		SEQ_SE_DP_W103,20
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_M1 | WE_TOOL_SSP,
	
	ADD_PARTICLE 	0,W_319_319_METAL_BEAM, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, 6, 0, 0, 0, 0, 20, 64,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG	
	SE_STOP			SEQ_SE_DP_W103
	SEQEND
