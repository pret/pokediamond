//==============================================================================
/**
 * @file	we_149.s
 * @brief	サイコウェーブ			149
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SAIKOWHEEBU
	
// =============================================================================
//
//
//	■サイコウェーブ			149
//
//
// =============================================================================
WEST_SAIKOWHEEBU:
	
	LOAD_PARTICLE_DROP			0,W_149_SPA
	ADD_PARTICLE_EMIT_SET 	0,0,W_149_149_PCYWAVE_BIO1, EMTFUNC_ATTACK_POS
	FUNC_CALL				WEST_SP_EMIT_STRAIGHT, 9, 0, 0, 0, 0, 19, 64, 0, 0, 1
	
	SE_FLOW_LR				SEQ_SE_DP_181
	WAIT					8
	SE_FLOW_LR				SEQ_SE_DP_181
	WAIT					10

	ADD_PARTICLE		 	0,W_149_149_PCYWAVE_BIO2, EMTFUNC_DEFENCE_POS
	SE_WAITPLAY_R			SEQ_SE_DP_161,2

	WAIT					10
	FUNC_CALL				WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
