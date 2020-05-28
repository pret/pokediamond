//==============================================================================
/**
 * @file	we_036.s
 * @brief	Ç∆Ç¡ÇµÇÒ			36
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TOSSIN
	
// =============================================================================
//
//
//	Å°Ç∆Ç¡ÇµÇÒ			36
//
//
// =============================================================================
WEST_TOSSIN:

	LOAD_PARTICLE_DROP	0,W_036_SPA

	SE_L			SEQ_SE_DP_W029
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -16, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	WAIT			15
	
	SE_R			SEQ_SE_DP_140

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +32, -16, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	ADD_PARTICLE 	0,W_036_036_HIT_MARK,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_036_036_BALL_BURN,		EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_036_036_KEMURI_BOMB,	EMTFUNC_DEFENCE_POS
	
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, 4, 0, 1, 4,  WE_TOOL_E1 | WE_TOOL_SSP,

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -16, +8, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	SEQEND
