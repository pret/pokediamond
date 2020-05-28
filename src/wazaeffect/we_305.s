//==============================================================================
/**
 * @file	we_305.s
 * @brief	どくどくのキバ			305
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DOKUDOKUNOKIBA
	
// =============================================================================
//
//
//	■どくどくのキバ			305
//
//
// =============================================================================
WEST_DOKUDOKUNOKIBA:
	
	LOAD_PARTICLE_DROP	0,W_305_SPA
	ADD_PARTICLE 	0,W_305_305_KIBA_UP,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_305_305_KIBA_DOWN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_305_305_DOKU_BURN,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_305_305_DOKU_UP,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_305_305_KIBA_UP2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_305_305_KIBA_DOWN2,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 5, WE_TOOL_E1, 1, 1, WE_PAL_POISON, 12,

	WAIT			1
	SE_R			SEQ_SE_DP_W044
	WAIT			9

	SE_REPEAT_R		SEQ_SE_DP_W092D,8,4
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
