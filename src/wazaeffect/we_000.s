//==============================================================================
/**
 * @file	we_000.s
 * @brief	we_xxx.sの登録方法と、サンプル
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

// =============================================================================
//
//
//	■サンプル
//
//
// =============================================================================
WEST_Sample:
	
	LOAD_PARTICLE_DROP	0,W_166_SPA
	
	
	ADD_PARTICLE 	0,W_166_166_SKETCH_PEN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_166_166_SKETCH_KIRA,	EMTFUNC_DEFENCE_POS
	
	POKEBG_DROP		WEDEF_DROP_E1,	WEDEF_POKE_AUTO_OFF
	
	SE_REPEAT_R		SEQ_SE_DP_W092,2,10

	FUNC_CALL		WEST_SP_166, 1, 0

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,	
	POKEBG_DROP_RESET 0

	SEQEND


