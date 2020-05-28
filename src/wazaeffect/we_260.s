//==============================================================================
/**
 * @file	we_260.s
 * @brief	Ç®ÇæÇƒÇÈ			260
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_ODATERU
	
// =============================================================================
//
//
//	Å°Ç®ÇæÇƒÇÈ			260
//
//
// =============================================================================
WEST_ODATERU:
	LOAD_PARTICLE_DROP	0,W_260_SPA
		
	SE_C			SEQ_SE_DP_W227B
	
	ADD_PARTICLE 	0,W_260_260_PAPER_BURN1, EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_260_260_PAPER_BURN2, EMTFUNC_DEFENCE_POS
	
	SIDE_JP		0, SIDE_MINE, SIDE_ENEMY
	
	SEQEND


SIDE_MINE:

	WAIT			15

	LOOP_LABEL		2
		SE_R			SEQ_SE_DP_001
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  -8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
	LOOP
	
	WAIT			30

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
	
SIDE_ENEMY:

	WAIT			15
	
	LOOP_LABEL		2
		SE_R			SEQ_SE_DP_001
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  -8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
		FUNC_CALL		WEST_SP_WE_T10, 4,  4, 0,  +8, WE_TOOL_E1 | WE_TOOL_SSP
		WAIT		4
	LOOP
	
	WAIT			30

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
