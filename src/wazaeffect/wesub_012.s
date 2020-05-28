//==============================================================================
/**
 * @file	wesub_006.s
 * @brief	
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_StatusKonran
	
// =============================================================================
//
//
//	Å°è„è∏
//
//
// =============================================================================
WEST_StatusUP:

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_1,

	FUNC_CALL	ST_EFF_UP, 2, STEFF_GRA_UP, 0

	SE_L				SEQ_SE_DP_W287

	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2

	POKEOAM_RES_FREE
	SEQEND
