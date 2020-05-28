//==============================================================================
/**
 * @file	we_107.s
 * @brief	ÇøÇ¢Ç≥Ç≠Ç»ÇÈ			107
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TIISAKUNARU
	
// =============================================================================
//
//
//	Å°ÇøÇ¢Ç≥Ç≠Ç»ÇÈ			107
//
//
// =============================================================================
WEST_TIISAKUNARU:

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_0,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
	
	FUNC_CALL			WEST_SP_WE_107,	1, 0
	SE_REPEAT_L			SEQ_SE_DP_W107,18,3

	WAIT_FLAG
	
	POKEOAM_RES_FREE

	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2
	PT_DROP_RESET_EX
	
	SEQEND
