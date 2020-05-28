//==============================================================================
/**
 * @file	we_135.s
 * @brief	タマゴうみ			135
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TAMAGOUMI
	
// =============================================================================
//
//
//	■タマゴうみ			135
//
//
// =============================================================================
WEST_TAMAGOUMI:

	LOAD_PARTICLE_DROP	0,W_135_SPA
	
	SE_L			SEQ_SE_DP_112

	ADD_PARTICLE 	0,W_135_135_EGG_EGG1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_135_135_EGG_EGG2, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_135_135_EGG_EGG3, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_135_135_EGG_RING, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_135_135_EGG_KIRA, EMTFUNC_ATTACK_POS

	SE_WAITPLAY_L	SEQ_SE_DP_W030,40
	
	WAIT			40
	//SE_WAITPLAY_L	SEQ_SE_DP_W234,5
	SE_WAITPLAY_L	SEQ_SE_DP_W071B,5
	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_PAL_FADE, 6,  WE_TOOL_M1, 0, 1, WE_PAL_WHITE, 10,0

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
