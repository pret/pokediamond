//==============================================================================
/**
 * @file	we_289.s
 * @brief	ÇÊÇ±Ç«ÇË			289
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_YOKODORI
	
// =============================================================================
//
//
//	Å°ÇÊÇ±Ç«ÇË			289
//
//
// =============================================================================
WEST_YOKODORI:

	TURN_CHK	WEST_289_TURN_1, WEST_289_TURN_2


	SEQEND


WEST_289_TURN_1:

	SE_L			SEQ_SE_DP_W036

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -8, +4, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	FUNC_CALL		WEST_SP_WE_T10,	4, 4, -8, -4, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_T10,	4, 4, +16, +0, WE_TOOL_M1 | WE_TOOL_SSP
	WAIT_FLAG

	SEQEND

WEST_289_TURN_2:
	
	FUNC_CALL		WEST_SP_289, 1, WE_TOOL_M1
	
	SE_L			SEQ_SE_DP_W054
	SE_WAITPLAY_R	SEQ_SE_DP_210,15
	SE_WAITPLAY_L	SEQ_SE_DP_W054,30

	WAIT			20
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,
	
	WAIT_FLAG
	
	SEQEND
