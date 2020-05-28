//==============================================================================
/**
 * @file	we_301.s
 * @brief	アイスボール			301
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AISUBOORU
	
// =============================================================================
//
//
//	■アイスボール			301
//
//
// =============================================================================
WEST_AISUBOORU:

	LOAD_PARTICLE_DROP	0,W_301_SPA

	SE_FLOW_LR		SEQ_SE_DP_W196

	ADD_PARTICLE 	0,W_301_301_ICEBALL_BEAM1, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, 6, 0, 0, 0, 0, 14, 64,

	ADD_PARTICLE 	0,W_301_301_ICEBALL_BEAM2, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, 6, 0, 0, 0, 0, 16, 64,
	
	WAIT			14
	
	ADD_PARTICLE 	0,W_301_301_ICEBALL_BURN, EMTFUNC_DEFENCE_POS

	WAIT			5
	SE_R			SEQ_SE_DP_W280

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 2, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_WHITE, WEDEF_FADE_PARAM,0
	
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
