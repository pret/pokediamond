//==============================================================================
/**
 * @file	we_001.s
 * @brief	はたく
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_358
	
// =============================================================================
//
//
//	■めざましビンタ
//
//
// =============================================================================
WEST_358:
	
	LOAD_PARTICLE_DROP	0,W_358_SPA
	ADD_PARTICLE 	0,W_358_358_BINTA_HAND, EMTFUNC_DEFENCE_POS	
	ADD_PARTICLE 	0,W_358_358_BINTA_HIT,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_358_358_BINTA_BALL, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_358_358_BINTA_HIT2, EMTFUNC_DEFENCE_POS

	//SE_REPEAT_R	SEQ_SE_DP_007,6,4
	SE_REPEAT_R		SEQ_SE_DP_030C,6,4
	SE_WAITPLAY_R	SEQ_SE_DP_W092,4
	SE_WAITPLAY_R	SEQ_SE_DP_W092,8
	SE_WAITPLAY_R	SEQ_SE_DP_W092,16
	SE_WAITPLAY_R	SEQ_SE_DP_W092,25

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*4,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
