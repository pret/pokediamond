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

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	■フェインと
//
//
// =============================================================================
WEST_364:

	LOAD_PARTICLE_DROP	0,W_364_SPA
	ADD_PARTICLE 	0,W_364_364_FEI_HAND1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_364_364_FEI_HAND2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_364_364_FEI_HAND3,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_364_364_FEI_HIT,	EMTFUNC_DEFENCE_POS
	
	SE_REPEAT_R		SEQ_SE_DP_W104,4,2

	WAIT			30
	SE_R			SEQ_SE_DP_030
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*2,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
