//==============================================================================
/**
 * @file	wesub_006.s
 * @brief	Ç±ÇÒÇÁÇÒ
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_DispIn
	
// =============================================================================
//
//
//	Å°Ç›Ç™ÇÌÇËOFF
//
//
// =============================================================================
WEST_Migawari:

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	0
	
	SE_L			SEQ_SE_DP_W107

	POKEOAM_DROP	WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	FUNC_CALL		WEST_SP_WE_CAP_ALPHA_FADE, 6, 1, 16, 0, 0, 16, 8, 0, 0
	WAIT			1	
	FUNC_CALL		WEST_SP_WE_SSP_POKE_VANISH, 2, WE_TOOL_M1, 1,	
	
	WAIT_FLAG

	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1

	SEQEND
