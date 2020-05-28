//==============================================================================
/**
 * @file	we_228.s
 * @brief	Ç®Ç¢Ç§Çø			228
 * @author	goto
 * @date	2005.07.13(êÖ)
 *
 * Ç±Ç±Ç…êFÅXÇ»âê‡ìôÇèëÇ¢ÇƒÇ‡ÇÊÇ¢
 *
 */
//==============================================================================
	
	.text
	
	.include	"west.h"

	.global		WEST_OIUTI
	
// =============================================================================
//
//
//	Å°Ç®Ç¢Ç§Çø			228
//
//
// =============================================================================
WEST_OIUTI:
	LOAD_PARTICLE_DROP	0,W_228_SPA
	
	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 0, 12, WE_PAL_BLACK,
	WAIT_FLAG
	
//	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE,  0
//	HAIKEI_CHG		BG_ID_069, WEDEF_HAIKEI_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
	SE_WAITPLAY_R	SEQ_SE_DP_209,15
//	HAIKEI_CHG_WAIT

	ADD_PARTICLE 	0,W_228_228_OIUTI_HIT,	EMTFUNC_DEFENCE_POS
	ADD_PARTICLE 	0,W_228_228_OIUTI_RING, EMTFUNC_DEFENCE_POS
	
	WAIT			5
	FUNC_CALL		WEST_SP_WT_SHAKE, 5, SHAKE_S_X, 0, SHAKE_S_WAIT, SHAKE_S_NUM,  WE_TOOL_E1 | WE_TOOL_SSP,

	SE_R			SEQ_SE_DP_030

	WAIT_PARTICLE
	EXIT_PARTICLE	0,

	FUNC_CALL		WEST_SP_WE_HAIKEI_PAL_FADE, 5, 0, 1, 12, 0, WE_PAL_BLACK,
	WAIT_FLAG
//	WORK_SET		WEDEF_GP_INDEX_FADE_TYPE,  0
//	HAIKEI_RECOVER	BG_ID_069, WEDEF_HAIKEI_RC_MODE_FADE | WEDEF_HAIKEI_SBIT_NONE
//	HAIKEI_CHG_WAIT

	SEQEND
