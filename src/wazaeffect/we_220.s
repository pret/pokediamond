//==============================================================================
/**
 * @file	we_220.s
 * @brief	Ç¢ÇΩÇ›ÇÌÇØ			220
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ITAMIWAKE
	
// =============================================================================
//
//
//	Å°Ç¢ÇΩÇ›ÇÌÇØ			220
//
//
// =============================================================================
WEST_ITAMIWAKE:
	
	LOAD_PARTICLE_DROP	0,W_220_SPA

	ADD_PARTICLE 	0,W_220_220_ITAMI_HIT1, EMTFUNC_ATTACK_POS
	ADD_PARTICLE 	0,W_220_220_ITAMI_HIT2, EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*4,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*4,  WE_TOOL_M1 | WE_TOOL_SSP,

	//SE_WAITPLAY_L	SEQ_SE_DP_W207B

	SE_WAITPLAY_L	SEQ_SE_DP_W025B,1
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,5
	SE_WAITPLAY_L	SEQ_SE_DP_W025B,10
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,15
	SE_WAITPLAY_L	SEQ_SE_DP_W025B,20
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,25

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
