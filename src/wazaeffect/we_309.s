//==============================================================================
/**
 * @file	we_309.s
 * @brief	コメットパンチ			309
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KOMETTOPANTI
	
// =============================================================================
//
//
//	■コメットパンチ			309
//
//
// =============================================================================
WEST_KOMETTOPANTI:
	
	LOAD_PARTICLE_DROP	0,W_309_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK
	WAIT_FLAG
	
	ADD_PARTICLE 	0,W_309_309_SHOOTING_STAR,	EMTFUNC_DEFENCE_POS
	SE_FLOW_LR		SEQ_SE_DP_W112
	
	WAIT			15
	
	ADD_PARTICLE 	0,W_309_309_YELL_PUNCH1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_309_309_YELL_PUNCH2,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_309_309_STAR_BURN,		EMTFUNC_DEFENCE_POS
	
	WAIT			7
	SE_R			SEQ_SE_DP_030
	WAIT			8
	SE_FLOW_RL		SEQ_SE_DP_351

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 5, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK
	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
