//==============================================================================
/**
 * @file	we_125.s
 * @brief	ホネこんぼう			125
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HONEKONBOU
	
// =============================================================================
//
//
//	■ホネこんぼう			125
//
//
// =============================================================================
WEST_HONEKONBOU:
	LOAD_PARTICLE_DROP	0,W_125_SPA
	
	SE_R			SEQ_SE_DP_W155

	ADD_PARTICLE 	0,W_125_125_HONEKO_BORN1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_125_125_HONEKO_BORN2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_125_125_HONEKO_HIT,		EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W233B
	SE_WAITPLAY_R	SEQ_SE_DP_030,4
	
	WAIT			3
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	SEQEND
