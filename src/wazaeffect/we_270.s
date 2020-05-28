//==============================================================================
/**
 * @file	we_270.s
 * @brief	ÇƒÇæÇ∑ÇØ			270
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TEDASUKE
	
// =============================================================================
//
//
//	Å°ÇƒÇæÇ∑ÇØ			270
//
//
// =============================================================================
#define MOVE_VAL_X1		(12)

#define W270_OAM_MAX	(6)

WEST_TEDASUKE:

	CATS_RES_INIT			0, W270_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_270_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_270_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_270_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_270_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_270,  EFFECT_270_NCGR_BIN, EFFECT_270_NCLR, EFFECT_270_NCER_BIN, EFFECT_270_NANR_BIN, 0, 0, 1, W270_OAM_MAX
	SE_WAITPLAY_C		SEQ_SE_DP_W227,20
	WAIT	14
	
	LOOP_LABEL		2
		FUNC_CALL		WEST_SP_WE_T05, 3, 2, MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_M2 | WE_TOOL_SSP,
		WAIT			3
		FUNC_CALL		WEST_SP_WE_T05, 3, 2, -MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			2
		SE_C			SEQ_SE_DP_W227
	LOOP

	WAIT			1
	FUNC_CALL		WEST_SP_WE_T05, 3, 2, MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_M2 | WE_TOOL_SSP,
	WAIT			3
	FUNC_CALL		WEST_SP_WE_T05, 3, 2, -MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT			1
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_M2, 0, 2, WE_PAL_GREEN_2, 8
	
	WAIT_FLAG
	CATS_RES_FREE			0

	SEQEND
