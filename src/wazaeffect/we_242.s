//==============================================================================
/**
 * @file	we_242.s
 * @brief	Ç©Ç›Ç≠ÇæÇ≠			242
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAMIKUDAKU
	
// =============================================================================
//
//
//	Å°Ç©Ç›Ç≠ÇæÇ≠			242
//
//
// =============================================================================
WEST_KAMIKUDAKU:
	
	LOAD_PARTICLE_DROP	0,W_242_SPA
	ADD_PARTICLE 	0,W_242_242_KIBA_BURN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_242_242_KIBA_UP,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_242_242_KIBA_UP2, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_242_242_KIBA_DOWN, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_242_242_KIBA_DOWN2, EMTFUNC_DEFENCE_POS

	WAIT			10
	SE_R			SEQ_SE_DP_W044
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_WAITPLAY_R	SEQ_SE_DP_W088,4
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
