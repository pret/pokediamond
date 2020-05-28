//==============================================================================
/**
 * @file	we_249.s
 * @brief	Ç¢ÇÌÇ≠ÇæÇ´			249
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_IWAKUDAKI
	
// =============================================================================
//
//
//	Å°Ç¢ÇÌÇ≠ÇæÇ´			249
//
//
// =============================================================================
WEST_IWAKUDAKI:
	
	LOAD_PARTICLE_DROP	0,W_249_SPA
	ADD_PARTICLE 	0,W_249_IWA_BREAK01,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_249_001_HIT_MARK,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SE_R			SEQ_SE_DP_W233B
	WAIT			5
	SE_R			SEQ_SE_DP_W088

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
