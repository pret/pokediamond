//==============================================================================
/**
 * @file	we_337.s
 * @brief	ドラゴンクロー			337
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DORAGONKUROO
	
// =============================================================================
//
//
//	■ドラゴンクロー			337
//
//
// =============================================================================
#define W337_OAM_MAX	(4)
WEST_DORAGONKUROO:
	
	LOAD_PARTICLE_DROP	0,W_337_SPA
	ADD_PARTICLE 	0,W_337_337_BALL_UP, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_337_337_LINE_UP, EMTFUNC_ATTACK_POS
	
	SE_L			SEQ_SE_DP_W221B
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 2, WE_PAL_RED, 10,0
	
	WAIT			30
	
	///< OAM
	CATS_RES_INIT			0, W337_OAM_MAX, 1,1,1,1,0,0
	CATS_CAHR_RES_LOAD		0, EFFECT_232_NCGR_BIN
	CATS_PLTT_RES_LOAD		0, EFFECT_232_NCLR, 1
	CATS_CELL_RES_LOAD		0, EFFECT_232_NCER_BIN
	CATS_CELL_ANM_RES_LOAD	0, EFFECT_232_NANR_BIN
	CATS_ACT_ADD			0, WEST_CSP_WE_232,  EFFECT_232_NCGR_BIN, EFFECT_232_NCLR, EFFECT_232_NCER_BIN, EFFECT_232_NANR_BIN, 0, 0, 1, W337_OAM_MAX
//	WAIT				55
	
	WAIT					1
	
	// 突撃
	LOOP_LABEL		2
		SE_R			SEQ_SE_DP_W013
//		ADD_PARTICLE 	0,W_337_337_SLASH,	 EMTFUNC_DEFENCE_POS
		FUNC_CALL		WEST_SP_WE_T05, 3, 2, WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			2
		FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
		WAIT			2
		FUNC_CALL		WEST_SP_WE_T05, 3, 2, -WE_MOVE_X_VAL_DEF, WE_TOOL_M1 | WE_TOOL_SSP
		WAIT			4
	LOOP

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
