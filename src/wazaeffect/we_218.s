//==============================================================================
/**
 * @file	we_218.s
 * @brief	Ç‚Ç¬Ç†ÇΩÇË			218
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YATUATARI
	
// =============================================================================
//
//
//	Å°Ç‚Ç¬Ç†ÇΩÇË			218
//
//
// =============================================================================
WEST_YATUATARI:
	
	LOAD_PARTICLE_DROP	0,W_218_SPA
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_RED, 10, 10
	SE_L			SEQ_SE_DP_W082
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_175,	1, 0
	
	ADD_PARTICLE 	0,W_218_218_YATU_HIT,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_218_218_YATU_LINE,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_REPEAT_R		SEQ_SE_DP_W025B,2,3
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
