//==============================================================================
/**
 * @file	we_206.s
 * @brief	Ç›ÇÀÇ§Çø			206
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_MINEUTI
	
// =============================================================================
//
//
//	Å°Ç›ÇÀÇ§Çø			206
//
//
// =============================================================================
WEST_MINEUTI:

	LOAD_PARTICLE_DROP	0,W_206_SPA
	
	SE_R			SEQ_SE_DP_W104

	ADD_PARTICLE 	0,W_206_206_MINEUTI_LINE1,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_206_206_MINEUTI_LINE2,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	WAIT			3
	SE_R			SEQ_SE_DP_BRADE

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
