//==============================================================================
/**
 * @file	we_104.s
 * @brief	Ç©Ç∞Ç‘ÇÒÇµÇÒ			104
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_KAGEBUNSIN
	
// =============================================================================
//
//
//	Å°Ç©Ç∞Ç‘ÇÒÇµÇÒ			104
//
//
// =============================================================================
WEST_KAGEBUNSIN:

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_1,

	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_1, WEDEF_POKE_RES_0,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_2, WEDEF_POKE_RES_1,
	POKEOAM_DROP		WEDEF_DROP_M1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_3, WEDEF_POKE_RES_1,
	PT_DROP_EX			WEDEF_DROP_M2, WEDEF_DROP_M2,
	
	FUNC_CALL	WEST_SP_WE_104,	1, 0

	SE_REPEAT_L		SEQ_SE_DP_053,4,14
	
	FUNC_CALL		WEST_SP_WE_T03, 2, 50, 0,
	
	WAIT_FLAG

	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_1
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_2
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_3	
	POKEOAM_RES_FREE
	PT_DROP_RESET_EX
	
	SEQEND
