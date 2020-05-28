//==============================================================================
/**
 * @file	we_124.s
 * @brief	ヘドロこうげき			124
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HEDOROKOUGEKI
	
// =============================================================================
//
//
//	■ヘドロこうげき			124
//
//
// =============================================================================
WEST_HEDOROKOUGEKI:

	LOAD_PARTICLE_DROP	0,W_124_SPA
	LOAD_PARTICLE_DROP	1,W_124_SPA
	
	SE_FLOW_LR		SEQ_SE_DP_W145C

	ADD_PARTICLE_EMIT_SET 	0,1,W_124_124_HEDOKO_KEMURI, EMTFUNC_ATTACK_POS
	FUNC_CALL		WEST_SP_EMIT_PARABOLIC, 6, 1, 0, 0, 0, 14, 64,

	WAIT			10
	SE_R			SEQ_SE_DP_W291
	SE_WAITPLAY_R	SEQ_SE_DP_W092D,12
	SE_WAITPLAY_R	SEQ_SE_DP_W092D,15

	ADD_PARTICLE 	1,W_124_124_HEDOKO_BUBBLE, EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_POISON, 10,0

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	EXIT_PARTICLE	1,
	
	SEQEND
