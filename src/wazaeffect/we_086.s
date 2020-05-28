//==============================================================================
/**
 * @file	we_086.s
 * @brief	Ç≈ÇÒÇ∂ÇÕ			86
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DENZIHA
	
// =============================================================================
//
//
//	Å°Ç≈ÇÒÇ∂ÇÕ			86
//
//
// =============================================================================
WEST_DENZIHA:
	
	LOAD_PARTICLE_DROP	0,W_086_SPA

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG
		
	ADD_PARTICLE 	0,W_086_086_DENJI_BURN, 	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_086_086_DENJI_BURN2, 	EMTFUNC_DEFENCE_POS
	
	WAIT			5
	SE_R			SEQ_SE_DP_W085C

	ADD_PARTICLE 	0,W_086_086_DENJI_SPARK, 	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_WAITPLAY_R	SEQ_SE_DP_W063B,2
	WAIT			47
	SE_REPEAT_R		SEQ_SE_DP_W063B,2,2

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	SEQEND
