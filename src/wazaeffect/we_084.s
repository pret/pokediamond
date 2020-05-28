//==============================================================================
/**
 * @file	we_084.s
 * @brief	でんきショック			84
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DENKISYOKKU
	
// =============================================================================
//
//
//	■でんきショック			84
//
//
// =============================================================================
WEST_DENKISYOKKU:
	
	LOAD_PARTICLE_DROP	0,W_084_SPA
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG

	SE_R			SEQ_SE_DP_W085
	

	ADD_PARTICLE 	0,W_084_084_THUNDER_LINE01,	EMTFUNC_DEFENCE_POS
	
	WAIT			5
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_BLACK, 15, 0
	
	ADD_PARTICLE 	0,W_084_084_THUNDER_SPARK01,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	SEQEND
