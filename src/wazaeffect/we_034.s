//==============================================================================
/**
 * @file	we_034.s
 * @brief	ÇÃÇµÇ©Ç©ÇË			34
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_NOSIKAKARI
	
// =============================================================================
//
//
//	Å°ÇÃÇµÇ©Ç©ÇË			34
//
//
// =============================================================================
WEST_NOSIKAKARI:

	LOAD_PARTICLE_DROP	0,W_034_SPA
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, 0, +16, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, 0, -16, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	SE_R			SEQ_SE_DP_W036
	SE_WAITPLAY_R	SEQ_SE_DP_W025B,6

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG	
	ADD_PARTICLE 	0,W_034_034_HIT_MARK,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_034_034_BALL_BURN,	EMTFUNC_DEFENCE_POS
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 3, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -WE_MOVE_X_VAL_DEF, 0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG	

	SEQEND
