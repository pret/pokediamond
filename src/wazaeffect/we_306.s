//==============================================================================
/**
 * @file	we_232.s
 * @brief	メタルクロー			232
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_METARUKUROO
	
// =============================================================================
//
//
//	■メタルクロー			232
//
//
// =============================================================================
#define W232_OAM_MAX	(4)
#define MOVE_VAL_X1		(WE_MOVE_X_VAL_DEF)

WEST_METARUKUROO:
	
	///< OAM
	CATS_RES_INIT			0, W232_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_232_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_306_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_232_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_232_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_232,  EFFECT_232_NCGR_BIN, EFFECT_306_NCLR, EFFECT_232_NCER_BIN, EFFECT_232_NANR_BIN, 0, 0, 1, W232_OAM_MAX
//	WAIT				55
	
	WAIT					1
	
	// 突撃
	LOOP_LABEL		2
		SE_R			SEQ_SE_DP_W013
		FUNC_CALL		WEST_SP_WE_T05, 3, 3, MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			2
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
		WAIT			2
		FUNC_CALL		WEST_SP_WE_T05, 3, 3, -MOVE_VAL_X1, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			4
	LOOP
	
	WAIT_FLAG
	CATS_RES_FREE			0

	SEQEND
