//==============================================================================
/**
 * @file	we_024.s
 * @brief	Ç…Ç«Ç∞ÇË			24
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NIDOGERI
	
// =============================================================================
//
//
//	Å°Ç…Ç«Ç∞ÇË			24
//
//
// =============================================================================
WEST_NIDOGERI:

	LOAD_PARTICLE_DROP	0,W_024_SPA
	ADD_PARTICLE 	0,W_024_024_FOOT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_024_024_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_024_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	SE_R			SEQ_SE_DP_030
	
	WAIT			10
	
	ADD_PARTICLE 	0,W_024_024_FOOT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_024_024_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_024_001_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 1, 0, 1, 2,  WE_TOOL_E1 | WE_TOOL_SSP,	
	SE_R			SEQ_SE_DP_030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
