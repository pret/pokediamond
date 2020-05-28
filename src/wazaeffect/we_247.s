//==============================================================================
/**
 * @file	we_247.s
 * @brief	シャドーボール			247
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SYADOOBOORU
	
// =============================================================================
//
//
//	■シャドーボール			247
//
//
// =============================================================================
#define W247_EMIT_WAIT	(8)
WEST_SYADOOBOORU:
	
	LOAD_PARTICLE_DROP	0,W_247_SPA

	ADD_PARTICLE 	0,W_247_247_SHADOW_MINI,	EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_247_247_SHADOW_BALL1,	EMTFUNC_DUMMY
	ADD_PARTICLE 	0,W_247_247_SHADOW_BALL2,	EMTFUNC_DUMMY

	SE_REPEAT_C		SEQ_SE_DP_W028,2,12
	WAIT			55
	
	ADD_PARTICLE 	0,W_247_247_SHADOW_BEAM,	EMTFUNC_DUMMY
	FUNC_CALL		WEST_SP_EMIT_STRAIGHT, W247_EMIT_WAIT, 0, 0, 0, 0, W247_EMIT_WAIT, 0xFF, 0, ((W247_EMIT_WAIT / 2) << 16) | 0

	ADD_PARTICLE 	0,W_247_247_SHADOW_HIT,		EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	SE_R			SEQ_SE_DP_480
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
