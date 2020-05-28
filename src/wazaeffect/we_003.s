//==============================================================================
/**
 * @file	we_003.s
 * @brief	おうふくビンタ			3
 * @author	goto
 * @date	2005.07.13(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_OUHUKUBINTA
	
// =============================================================================
//
//
//	■おうふくビンタ			3
//
//
// =============================================================================
WEST_OUHUKUBINTA:
	
	LOAD_PARTICLE_DROP	0,W_003_SPA
	ADD_PARTICLE 	0,W_003_BINTA_R,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_003_BINTA_L,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_003_BINTA_HIT01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_003_003_HIT_KONA,	EMTFUNC_DEFENCE_POS
	
	//SE_R			SEQ_SE_DP_007
	SE_R			SEQ_SE_DP_030C
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,
	WAIT			15
	//SE_R			SEQ_SE_DP_007
	SE_R			SEQ_SE_DP_030C
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
