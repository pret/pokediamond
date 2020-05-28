//==============================================================================
/**
 * @file	we_293.s
 * @brief	ÇŸÇ≤ÇµÇÂÇ≠			293
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_HOGOSYOKU
	
// =============================================================================
//
//
//	Å°ÇŸÇ≤ÇµÇÂÇ≠			293
//
//
// =============================================================================
#define HOGOSYOKU_CAP_BIT	( 1 )
#define HOGOSYOKU_FADE_OUT_SYNC	( 48 )
#define HOGOSYOKU_FADE_IN_SYNC	( 24 )
WEST_HOGOSYOKU:

	SEPLAY_PAN		SEQ_SE_DP_W185, WAZA_SE_PAN_AT

/// åıäwñ¿ç ÇÃÇÊÇ§Ç…å©Ç¶ÇÈ
	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	0
	
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,

	FUNC_CALL			WEST_SP_WE_293, 0,0,0,0,0,0,0,0

	WAIT_FLAG

	POKEOAM_RES_FREE
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	PT_DROP_RESET_EX
	
	SEQEND
