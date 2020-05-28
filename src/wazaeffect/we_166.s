//==============================================================================
/**
 * @file	we_166.s
 * @brief	スケッチ			166
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_SUKETTI
	
// =============================================================================
//
//
//	■スケッチ			166
//
//
// =============================================================================

WEST_SUKETTI:
	
	LOAD_PARTICLE_DROP	0,W_166_SPA
	
	ADD_PARTICLE 	0,W_166_166_SKETCH_PEN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_166_166_SKETCH_KIRA,	EMTFUNC_DEFENCE_POS
	
	POKEBG_DROP		WEDEF_DROP_E1,	WEDEF_POKE_AUTO_OFF

	FUNC_CALL		WEST_SP_166, 1, 0
	
	WAIT			5
	
	SE_REPEAT_R		SEQ_SE_DP_W092,4,20

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,	
	POKEBG_DROP_RESET 0
	
	SEQEND

/*
WEST_SUKETTI:
	
	LOAD_PARTICLE_DROP	0,W_166_SPA
	ADD_PARTICLE 	0,W_166_166_SKETCH_PEN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_166_166_SKETCH_KIRA,	EMTFUNC_DEFENCE_POS
	
	//SE_REPEAT_R	SEQ_SE_DP_W092,2,8
	SE_REPEAT_R		SEQ_SE_DP_W092,2,10
	
	FUNC_CALL		WEST_SP_RECT_VIEW, 6, WE_TOOL_E1, 0, 0, +4, 5, 1
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
*/

