//==============================================================================
/**
 * @file	we_044.s
 * @brief	Ç©Ç›Ç¬Ç≠			44
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAMITUKU
	
// =============================================================================
//
//
//	Å°Ç©Ç›Ç¬Ç≠			44
//
//
// =============================================================================
WEST_KAMITUKU:

	LOAD_PARTICLE_DROP	0,W_044_SPA

	ADD_PARTICLE 	0,W_044_044_HIT_MARK,	 EMTFUNC_DEFENCE_POS	
	ADD_PARTICLE 	0,W_044_044_KIBA_UP,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_044_044_KIBA_DOWN,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_044_044_KIBA_UP2,	 EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_044_044_KIBA_DOWN2,	 EMTFUNC_DEFENCE_POS

	WAIT			2
	SE_R			SEQ_SE_DP_W044
	WAIT			8
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	SEQEND
