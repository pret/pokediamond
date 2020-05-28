//==============================================================================
/**
 * @file	we_210.s
 * @brief	ÇÍÇÒÇºÇ≠Ç¨ÇË			210
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RENZOKUGIRI
	
// =============================================================================
//
//
//	Å°ÇÍÇÒÇºÇ≠Ç¨ÇË			210
//
//
// =============================================================================
#define W210_BG_PAL_FADE		(0)
#define W210_BG_PAL_FADE_WAIT	(0)
#define W210_BG_PAL_FADE_COL	(WE_PAL_BLACK)

WEST_RENZOKUGIRI:
	
	LOAD_PARTICLE_DROP	0,W_210_SPA

	LOOP_LABEL		2	
		SE_C			SEQ_SE_DP_W043
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W210_BG_PAL_FADE, W210_BG_PAL_FADE_WAIT, 0, 8, W210_BG_PAL_FADE_COL,
		WAIT_FLAG
		FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W210_BG_PAL_FADE, W210_BG_PAL_FADE_WAIT, 8, 0, W210_BG_PAL_FADE_COL,
		WAIT_FLAG
	LOOP
	
	ADD_PARTICLE 	0,W_210_210_RENGIRI_LINE,	EMTFUNC_DEFENCE_POS	
	ADD_PARTICLE 	0,W_210_210_RENGIRI_HIT,	EMTFUNC_DEFENCE_POS
	
	WAIT			5
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 0, 2, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_W013

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
