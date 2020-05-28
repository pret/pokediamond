//==============================================================================
/**
 * @file	we_171.s
 * @brief	Ç†Ç≠Çﬁ			171
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_AKUMU
	
// =============================================================================
//
//
//	Å°Ç†Ç≠Çﬁ			171
//
//
// =============================================================================
WEST_AKUMU:

	POKEOAM_RES_INIT
	POKEOAM_RES_LOAD	WEDEF_POKE_RES_0,

	POKEOAM_DROP		WEDEF_DROP_E1, WEDEF_POKE_AUTO_OFF, WEDEF_POKE_CAP_ID_0, WEDEF_POKE_RES_0,
//	PT_DROP_EX			WEDEF_DROP_E2, WEDEF_DROP_E2,

	HAIKEI_CHG			BG_ID_171, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	HAIKEI_HALF_WAIT
	
	FUNC_CALL			WEST_SP_LASTER,		1,		130
	
	HAIKEI_CHG_WAIT
	
	WAIT			45
	
	FUNC_CALL			WEST_SP_WE_171,	1, 0
	
	SE_REPEAT_R			SEQ_SE_DP_W171,2,4

	WAIT				15
	FUNC_CALL			WEST_SP_WT_SHAKE, 5, SHAKE_M_X, 0, SHAKE_M_WAIT, SHAKE_M_NUM*3,  WE_TOOL_E1 | WE_TOOL_SSP,
	WAIT				15
	
	POKE_OAM_ENABLE		WEDEF_POKE_CAP_ID_0, 0

	WAIT				30
	
	HAIKEI_RECOVER		BG_ID_171, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	
	WAIT_FLAG
	
	HAIKEI_CHG_WAIT
	
	POKEOAM_DROP_RESET	WEDEF_POKE_CAP_ID_0
	POKEOAM_RES_FREE
//	PT_DROP_RESET_EX
	
	SEQEND
