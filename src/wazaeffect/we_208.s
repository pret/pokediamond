//==============================================================================
/**
 * @file	we_208.s
 * @brief	ミルクのみ			208
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MIRUKUNOMI
	
// =============================================================================
//
//
//	■ミルクのみ			208
//
//
// =============================================================================
WEST_MIRUKUNOMI:

	LOAD_PARTICLE_DROP	0,W_208_SPA
	
	//SE_R			SEQ_SE_DP_W208

	ADD_PARTICLE 	0,W_208_208_MILKNOMI_MILK1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_208_208_MILKNOMI_MILK2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_208_208_MILKNOMI_RING,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_208_208_MILKNOMI_KIRA,	EMTFUNC_DEFENCE_POS

	WAIT			5
	SE_R			SEQ_SE_DP_W152
	WAIT			25
	SE_R			SEQ_SE_DP_052
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_E1, 0, 1, WE_PAL_WHITE, 10,0
	SE_WAITPLAY_R	SEQ_SE_DP_W071B,15

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
