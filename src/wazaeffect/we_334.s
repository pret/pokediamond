//==============================================================================
/**
 * @file	we_334.s
 * @brief	ÇƒÇ¡ÇÿÇ´			334
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_TEPPEKI
	
// =============================================================================
//
//
//	Å°ÇƒÇ¡ÇÿÇ´			334
//
//
// =============================================================================
WEST_TEPPEKI:

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 12, WE_PAL_WHITE,
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 12, 0, WE_PAL_WHITE,
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 0, 12, WE_PAL_WHITE,
	WAIT_FLAG
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 0, 12, 0, WE_PAL_WHITE,
	
	SE_REPEAT_L		SEQ_SE_DP_W231,8,2

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M2, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_1,

	FUNC_CALL	ST_EFF_METAL, 2, STEFF_GRA_METAL, 0

	WAIT_FLAG
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2

	POKEOAM_RES_FREE
	WAIT_FLAG
	
	SEQEND
