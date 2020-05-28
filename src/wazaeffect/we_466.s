//==============================================================================
/**
 * @file	we_001.s
 * @brief	ÇÕÇΩÇ≠
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_Hataku
	
// =============================================================================
//
//
//	Å°ÇÕÇΩÇ≠
//
//
// =============================================================================
WEST_Hataku:

	LOAD_PARTICLE_DROP	0,W_466_SPA

	SE_R			SEQ_SE_DP_W466
	
	SIDE_JP		0, WEST_466_SIDE_MINE, WEST_466_SIDE_ENEMY
	
	SEQEND

WEST_466_SIDE_MINE:

	ADD_PARTICLE	0, W_466_466_DARK_WIND01,	EMTFUNC_DEFENCE_POS

	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT			35
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG

	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND

WEST_466_SIDE_ENEMY:
	
	ADD_PARTICLE	0, W_466_466_DARK_WIND02,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 3,  WE_TOOL_E1 | WE_TOOL_SSP
	
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 4, -20, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT			35
	
	FUNC_CALL		WEST_SP_WE_T05, 3, 5, +20, WE_TOOL_E1 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT_PARTICLE
	EXIT_PARTICLE	0,
	
	SEQEND
