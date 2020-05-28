//==============================================================================
/**
 * @file	we_295.s
 * @brief	ラスターパージ			295
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_RASUTAAPAAZI
	
// =============================================================================
//
//
//	■ラスターパージ			295
//
//
// =============================================================================
#define W295_BG_PAL_FADE		(0)
#define W295_BG_PAL_FADE_WAIT	(1)
#define W295_BG_PAL_FADE_COL	(WE_PAL_WHITE)

WEST_RASUTAAPAAZI:
	LOAD_PARTICLE_DROP	0,W_295_SPA
		
	SE_L			SEQ_SE_DP_W076
	
	ADD_PARTICLE 	0,W_295_295_LIGHT_BURN,	 EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_295_295_LIGHT_LINE1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_295_295_LIGHT_LINE2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_295_295_LIGHT_LINE3, EMTFUNC_ATTACK_POS

	WAIT			60

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W295_BG_PAL_FADE, W295_BG_PAL_FADE_WAIT, 0, 16, W295_BG_PAL_FADE_COL,
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6, WE_TOOL_A, 0, 1, WE_PAL_WHITE, 16, 30
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6, WE_TOOL_B, 0, 1, WE_PAL_WHITE, 16, 30
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6, WE_TOOL_C, 0, 1, WE_PAL_WHITE, 16, 30
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6, WE_TOOL_D, 0, 1, WE_PAL_WHITE, 16, 30
	
	WAIT			20
	SE_REPEAT_R		SEQ_SE_DP_W030,4,8

	ADD_PARTICLE 	0,W_295_295_HIT_MARK,	 EMTFUNC_DEFENCE_POS	
	WAIT			20
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, W295_BG_PAL_FADE, W295_BG_PAL_FADE_WAIT, 16, 0, W295_BG_PAL_FADE_COL,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 6,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
