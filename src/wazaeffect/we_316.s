//==============================================================================
/**
 * @file	we_316.s
 * @brief	Ç©Ç¨ÇÌÇØÇÈ			316
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAGIWAKERU
	
// =============================================================================
//
//
//	Å°Ç©Ç¨ÇÌÇØÇÈ			316
//
//
// =============================================================================
WEST_KAGIWAKERU:
	
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,

	POKEOAM_DROP		WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	PT_DROP_EX			WEDEF_DROP_E2, WEDEF_DROP_E2,
	
//	FUNC_CALL			WEST_SP_WE_316,	1, 0
	FUNC_CALL			WEST_SP_WT_SHAKE,	5, -20, 0, 1, 10, WE_TOOL_C0 | WE_TOOL_CAP
	FUNC_CALL			WEST_SP_WT_SHAKE,	5, +20, 0, 1, 10, WE_TOOL_C1 | WE_TOOL_CAP
	
	SE_REPEAT_R			SEQ_SE_DP_W207,2,3
	WAIT				10
	SE_L				SEQ_SE_DP_W043
	
	FUNC_CALL			WEST_SP_WT_SHAKE,	5, 4, 0, 1, 2, WE_TOOL_M1 | WE_TOOL_SSP

	WAIT_FLAG
	
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_RES_FREE
	PT_DROP_RESET_EX
	
	SEQEND
