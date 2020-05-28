//==============================================================================
/**
 * @file	we_198.s
 * @brief	ボーンラッシュ			198
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_BOONRASSYU
	
// =============================================================================
//
//
//	■ボーンラッシュ			198
//
//
// =============================================================================
WEST_BOONRASSYU:
	
	LOAD_PARTICLE_DROP	0,W_198_SPA
	ADD_PARTICLE 	0,W_198_198_HONE_BORN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_198_198_HONE_HIT,  EMTFUNC_DEFENCE_POS

	SE_R			SEQ_SE_DP_W155
	WAIT			4
	SE_R			SEQ_SE_DP_030
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
