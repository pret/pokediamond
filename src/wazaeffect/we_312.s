//==============================================================================
/**
 * @file	we_312.s
 * @brief	アロマセラピー			312
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AROMASERAPII
	
// =============================================================================
//
//
//	■アロマセラピー			312
//
//
// =============================================================================
WEST_AROMASERAPII:
	
	LOAD_PARTICLE_DROP	0,W_312_SPA
	
	///< 背景アニメ
	ADD_PARTICLE 	0,W_312_312_AROMA_BALL,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_312_312_HANABIRA,	 EMTFUNC_DEFENCE_POS

	///< フェードIN
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 8, WE_PAL_GREEN_2,
	WAIT_FLAG
	
	SE_C			SEQ_SE_DP_W080
	WAIT			60
	SE_L			SEQ_SE_DP_W234

	///< フェードOUT
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 8, 0, WE_PAL_GREEN_2,
	WAIT_FLAG

	SE_WAITPLAY_L	SEQ_SE_DP_REAPOKE,23

	///< 回復アニメ
	ADD_PARTICLE 	0,W_312_312_KIRA_BURN, 	 EMTFUNC_AT_SIDE
	ADD_PARTICLE 	0,W_312_312_CIRCLE_BURN, EMTFUNC_AT_SIDE
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M2, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
