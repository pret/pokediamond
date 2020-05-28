//==============================================================================
/**
 * @file	we_415.s
 * @brief	トリック			415
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TORIKKU
	
// =============================================================================
//
//
//	■			415
//
//
// =============================================================================

#define W271_OAM_MAX	(2)

WEST_SURIKAE:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	
	SE_L			SEQ_SE_DP_166

	CATS_RES_INIT			0, W271_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_271_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_415_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_271_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_271_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_271,  EFFECT_271_NCGR_BIN, EFFECT_415_NCLR, EFFECT_271_NCER_BIN, EFFECT_271_NANR_BIN, 0, 0, 1, W271_OAM_MAX

	SE_WAITPLAY_C			SEQ_SE_DP_W145B,73
	SE_WAITPLAY_C			SEQ_SE_DP_W104,80
	SE_WAITPLAY_C			SEQ_SE_DP_W104,95
	SE_WAITPLAY_C			SEQ_SE_DP_W104,108
	SE_WAITPLAY_C			SEQ_SE_DP_W104,122
	SE_WAITPLAY_C			SEQ_SE_DP_W104,130
	WAIT_FLAG
	
	CATS_RES_FREE			0
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG	
	
	SEQEND
